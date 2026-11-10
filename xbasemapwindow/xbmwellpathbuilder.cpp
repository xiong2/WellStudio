#include "xbmwellpathbuilder.h"

#include <QGLWidget>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/PolygonMode>
#include <osg/AutoTransform>
#include <osg/Camera>
#include <osgText/Text>
#include <osg/LineWidth>

#include "xwell.h"
#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include "x3dbuilderfactory.h"
#include "xviewinfowellpath.h"
#include "xbasemapwindow.h"
#include "xwellpath.h"
#include "xgraphicsapi.h"
#include "x3dutility.h"

// As a solution that use texture to show well symbol, which type icon should we use?
// The well symbol icon in current sln cannot change color of every well.
// Thus, we still use circle to show well.
// The following code to use texture.

//osg::ref_ptr<osg::Texture2D> pTexture = new osg::Texture2D;
//pTexture->setDataVariance(osg::Object::DYNAMIC);
//const QColor& wellColor = pWell->GetColor();
//pTexture->setBorderColor(osg::Vec4(wellColor.redF(), wellColor.greenF(), wellColor.blueF(), wellColor.alphaF()));
//pTexture->setImage(osgDB::readRefImageFile("symbol/" + pWell->GetIconName().toStdString()));

//osg::StateSet* pStateSet = pSymbolNode->getOrCreateStateSet();
//pStateSet->setTextureAttributeAndModes(0, pTexture, osg::StateAttribute::ON);
//pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
//pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
//pStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXBMWellPathBuilder)
{ EXWell, e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CXBMWellPathBuilder)

CXBMWellPathBuilder::CXBMWellPathBuilder()
	: CX3DBuilderAbstract()
{

}

CXBMWellPathBuilder::~CXBMWellPathBuilder()
{

}

osg::ref_ptr<osg::Group> CXBMWellPathBuilder::Build(QUuid objId)
{
	m_pViewInfo = dynamic_cast<CXViewInfoWellPath*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pViewInfo)
		return nullptr;

	SetObjectID(objId);

	m_pBuilderNode = new osg::Group;

	m_pBuilderNode->addChild(_BuildWellSymbol());
	m_pBuilderNode->addChild(_BuildWellPath());

	return m_pBuilderNode;
}

void CXBMWellPathBuilder::UpdateNode(EEventType eType)
{
	if (eType == EDataChanged)
	{
		if (!_UpdateLatestWellData())
			return;

		if (m_pWellSymbolAutoTransform)
		{
			m_pWellSymbolAutoTransform->setPosition(m_vecWellPos);
		}

		if (m_pWellNameLegend.valid())
		{
			m_pWellNameLegend->setText(m_wellName);
		}

		_UpdateLatestWellPathData();
	}
	else if (eType == EInfoChanged)
	{
		_UpdateWellInfo();
	}
}

osg::Geode* CXBMWellPathBuilder::_BuildWellPath()
{
	if (!_UpdateLatestWellPathData())
		return nullptr;

	bool bVisible = m_pViewInfo->GetWellPathVisible();
	const QColor& color = m_pViewInfo->GetWellPathColor();
	int radius = m_pViewInfo->GetWellPathRadius();

	if (!bVisible)
		return nullptr;

	osg::ref_ptr<osg::Geometry> pWellPathGeom = new osg::Geometry;
	pWellPathGeom->setVertexArray(m_pWellPathVertex.get());

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
	(*colors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	pWellPathGeom->setColorArray(colors.get());
	pWellPathGeom->setColorBinding(osg::Geometry::BIND_OVERALL);

	pWellPathGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, m_pWellPathVertex->size()));

	m_pWellPathNode = new osg::Geode;
	m_pWellPathNode->addDrawable(pWellPathGeom.get());

	osg::StateSet* pStateSet = m_pWellPathNode->getOrCreateStateSet();

	osg::ref_ptr<osg::LineWidth> pWellPathLineWidth = new osg::LineWidth;
	pWellPathLineWidth->setWidth(radius);
	pStateSet->setAttributeAndModes(pWellPathLineWidth.get(), osg::StateAttribute::ON);
	pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	pStateSet->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
	pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);

	return m_pWellPathNode.get();
}

osg::Node* CXBMWellPathBuilder::_BuildWellSymbol()
{
	if (!_UpdateLatestWellData())
		return nullptr;

	// Drawing geometry.

	m_pSymbolNode = new osg::Geode;
	m_pSymbolNode->setUserValue("objID", m_objID.toString().toStdString());
	m_pSymbolNode->setName("WellHeader_" + m_wellName);

	m_pSymbolNode->addDrawable(_BuildSymbolGeometry());
	m_pSymbolNode->addDrawable(_BuildLabelGeometry(m_wellName));

	// smooth lines

	osg::StateSet* pStateSet = m_pSymbolNode->getOrCreateStateSet();
	pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	pStateSet->setRenderBinDetails(11, "RenderBin"); // last to render

	// keep position.

	m_pWellSymbolAutoTransform = new osg::AutoTransform;
	m_pWellSymbolAutoTransform->setAutoScaleToScreen(true);
	m_pWellSymbolAutoTransform->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
	m_pWellSymbolAutoTransform->setPosition(m_vecWellPos);
	m_pWellSymbolAutoTransform->addChild(m_pSymbolNode.get());

	return m_pWellSymbolAutoTransform.get();
}

osg::Geometry* CXBMWellPathBuilder::_BuildSymbolGeometry()
{
	// viewinfo

	bool bVisable = m_pViewInfo->GetWellSymbolVisible();
	const QColor& color = m_pViewInfo->GetWellSymbolColor();
	int radius = m_pViewInfo->GetWellSymbolRadius();

	if (!bVisable)
		return nullptr;

	// build circle

	m_pWellSymbolGeom = new osg::Geometry;

	const int cVectexSize = 64;
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(cVectexSize + 2);

	// efficient way to draw approximate circle
	// see http://slabode.exofire.net/circle_draw.shtml

	float theta = (2 * osg::PI) / cVectexSize;
	float x = radius;
	float y = 0;

	(*vertices)[0].set(0.0, 0.0, 0.0);
	for (int i = 1; i != cVectexSize + 2; ++i)
	{
		(*vertices)[i].set(x, y, 0.0);

		float t = x;
		x = cosf(theta) * x - sinf(theta) * y;
		y = sinf(theta) * t + cosf(theta) * y;
	}
	m_pWellSymbolGeom->setVertexArray(vertices.get());

	NX3DUtility::SetSingleColor(m_pWellSymbolGeom, color);
	m_pWellSymbolGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_FAN, 0, cVectexSize + 2));

	return m_pWellSymbolGeom.get();
}

osgText::Text* CXBMWellPathBuilder::_BuildLabelGeometry(const std::string& wellName)
{
	// viewinfo

	bool bVisable = m_pViewInfo->GetWellNameVisible();
	int size = m_pViewInfo->GetWellNameFontSize();
	const QString& name = m_pViewInfo->GetWellNameFontFamily();
	const QColor& color = m_pViewInfo->GetWellNameColor();
	int position = m_pViewInfo->GetWellNamePosition();
	const float offset = position ? -15.f : 15.f;

	if (!bVisable)
		return nullptr;

	// draw text

	m_pWellNameLegend = new osgText::Text;
	m_pWellNameLegend->setFont(osgText::readFontFile("fonts/" + name.toStdString() + ".ttf"));
	m_pWellNameLegend->setText(wellName);
	m_pWellNameLegend->setColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	m_pWellNameLegend->setCharacterSize(size);
	m_pWellNameLegend->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	m_pWellNameLegend->setPosition(osg::Vec3(0.f, offset, 0.f));
	m_pWellNameLegend->setAlignment(osgText::Text::CENTER_CENTER);

	return m_pWellNameLegend.get();
}

bool CXBMWellPathBuilder::_UpdateLatestWellData()
{
	CXWell* pWell = dynamic_cast<CXWell*>(::GetObjectByID(m_objID));
	if (!pWell)
		return false;

	double dX, dY;
	pWell->GetWellPosition(dX, dY);

	double dZ = pWell->GetZMin();

	osg::Vec3 vecWellPosition;
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dY, dZ), vecWellPosition);

	const std::string& wellName = pWell->GetObjectName().toStdString();

	if (vecWellPosition == m_vecWellPos && wellName == m_wellName)
		return false;
	
	m_vecWellPos = vecWellPosition;
	m_wellName = wellName;

	return true;
}

bool CXBMWellPathBuilder::_UpdateLatestWellPathData()
{
	CXWell* pWell = dynamic_cast<CXWell*>(::GetObjectByID(m_objID));
	if (!pWell)
		return false;

	CXWellPath* pWellPath = pWell->GetWellPath();
	if (!pWellPath)
		return false;

	uint nSize;
	double *pData = pWellPath->GetData(nSize);
	if (!pData || nSize == 0)
		return false;

	uint nPoint = nSize / 3;
	if (nPoint < 2)
		return false;

	double* pX = new double[nPoint];
	double* pY = new double[nPoint];
	double* pZ = new double[nPoint];

	for (uint i = 0; i != nPoint; ++i)
	{
		pX[i] = pData[3 * i + 0];
		pY[i] = pData[3 * i + 1];
		pZ[i] = pData[3 * i + 2];
	}

	std::vector<int> vecIndex;
	CXGraphicsAPI::SegmentSimplification(pX, pY, pZ, nPoint, vecIndex);

	m_pWellPathVertex = new osg::Vec3Array;
	for (auto i : vecIndex)
	{
		osg::Vec3 vecPathPoints;
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(pX[i], pY[i], pZ[i]), vecPathPoints);
		m_pWellPathVertex->push_back(vecPathPoints);
	}

	delete[] pX;
	delete[] pY;
	delete[] pZ;

	return true;
}

void CXBMWellPathBuilder::_UpdateWellInfo()
{
	// viewinfo - well symbol

	bool bVisible = m_pViewInfo->GetWellSymbolVisible();
	
	if (bVisible)
	{
		if (m_pWellSymbolGeom.valid()) // update
		{
			m_pSymbolNode->removeDrawable(m_pWellSymbolGeom);
			m_pSymbolNode->addDrawable(_BuildSymbolGeometry());
		}
		else // init
		{
			m_pSymbolNode->addDrawable(_BuildSymbolGeometry());
		}
	}
	else
	{
		m_pSymbolNode->removeDrawable(m_pWellSymbolGeom);
		m_pWellSymbolGeom = nullptr;
	}

	// viewinfo - well name

	bVisible = m_pViewInfo->GetWellNameVisible();

	if (bVisible)
	{
		if (m_pWellNameLegend.valid()) // update
		{
			int size = m_pViewInfo->GetWellNameFontSize();
			const QString& name = m_pViewInfo->GetWellNameFontFamily();
			const QColor& color = m_pViewInfo->GetWellNameColor();
			int position = m_pViewInfo->GetWellNamePosition();
			const float offset = position ? -15.f : 15.f;

			m_pWellNameLegend->setCharacterSize(size);
			m_pWellNameLegend->setFont(osgText::readFontFile("fonts/" + name.toStdString() + ".ttf"));
			m_pWellNameLegend->setColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
			m_pWellNameLegend->setPosition(osg::Vec3(0.f, offset, 0.f));
		}
		else // init
		{
			m_pSymbolNode->addDrawable(_BuildLabelGeometry(m_wellName));
		}
	}
	else
	{
		m_pSymbolNode->removeDrawable(m_pWellNameLegend);
		m_pWellNameLegend = nullptr;
	}

	// viewinfo - well path

	bVisible = m_pViewInfo->GetWellPathVisible();

	if (bVisible)
	{
		if (m_pWellPathNode.valid()) // update
		{
			m_pBuilderNode->removeChild(m_pWellPathNode);
			m_pBuilderNode->addChild(_BuildWellPath());
		}
		else // init
		{
			m_pBuilderNode->addChild(_BuildWellPath());
		}
	}
	else
	{
		m_pBuilderNode->removeChild(m_pWellPathNode);
		m_pWellPathNode = nullptr;
	}
}