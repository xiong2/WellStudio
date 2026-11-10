#include "x3dgridmodelbuilder.h"
#include "xglobal.h"
#include "x3dbuilderfactory.h"
#include "xgridmodel.h"
#include "xgridcell.h"
#include "x3dglobalcoordmap.h"
#include "x3dwindow.h"
#include "xviewinfo3dgridmodel.h"
#include "xpropertymodel.h"
#include "xcolormap.h"
#include "xwellcondition.h"
#include "xwellcells.h"

#include <QDebug>
#include <cassert>

#include <osg/Geometry>
#include <osg/Point>
#include <osg/PolygonMode>
#include <osg/LineWidth>

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DGridModelBuilder)
{EXGridModel, e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CX3DGridModelBuilder)

unsigned CX3DGridModelBuilder::m_arrayIndex[24] = {	
0,3,2,1,	// top
0,4,7,3,	// left
0,1,5,4,	// front
1,2,6,5,	// right
2,3,7,6,	// back
4,5,6,7		// below)
};

unsigned CX3DGridModelBuilder::m_arrayLines[24] = {
0,1,1,2,2,3,3,0,
4,5,5,6,6,7,7,4,
0,4,1,5,2,6,3,7
};

CX3DGridModelBuilder::CX3DGridModelBuilder()
{
	m_pVecIJK = NULL;
	m_pCellGeom = NULL;
	m_pGridGeom = NULL;
	m_pVertices = NULL;
}

CX3DGridModelBuilder::~CX3DGridModelBuilder()
{
	// remove the Toolbar of gridmodel
	CX3DWindow* pWin = dynamic_cast<CX3DWindow*>(m_pCurWin);
	pWin->SetGridModelControl(false);
}

osg::ref_ptr<osg::Group> CX3DGridModelBuilder::Build(QUuid objId)
{
	// add the Toolbar of gridmodel
	m_pOSGWindow = dynamic_cast<CX3DWindow*>(m_pCurWin);
	m_pOSGWindow->SetGridModelControl(true);

	if (m_pBuilderNode == nullptr)
		m_pBuilderNode=new osg::Group;

	// Get object
	CXGridModel *pGridModel = dynamic_cast<CXGridModel*>(::GetObjectByID(objId));
	if (!pGridModel) 
		return NULL;

	// Get viewinfo
	m_pViewInfo = dynamic_cast<CXViewInfo3DGridModel*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pViewInfo)
		return NULL;

	m_pCellGeom = new osg::Geometry;
	m_pCellGeom->setName("Grid model cell geometry");
	m_pCellGeom->setUseVertexBufferObjects(true);

	m_pGridGeom = new osg::Geometry;
	m_pGridGeom->setName("Grid model border line");
	m_pGridGeom->setUseVertexBufferObjects(true);

	_CalcVertices(pGridModel->GetAllCells());
	_CalcIndices(true);
	_CalcColor();
	_CalcNormal();

	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	pGeode->setName(pGridModel->GetObjectName().toLatin1().data());
	pGeode->addDrawable(m_pCellGeom.get());
	pGeode->addDrawable(m_pGridGeom.get());
	m_pBuilderNode->addChild(pGeode.get());

	return m_pBuilderNode.get();
}

void CX3DGridModelBuilder::UpdateNode(EEventType eType)
{
	if (eType == EInfoChanged || eType == EColormapChanged)
	{
		_CalcColor();
		_CalcPropertyIndicesAndColor();
	}
}

void CX3DGridModelBuilder::_CalcNormal()
{
	osg::ref_ptr<osg::Vec3Array> pNormalize = new osg::Vec3Array;

	for (int i=0; i<m_pVecIJK->size(); ++i)
	{
		// Calculate the normal vector, number is the following line index.
		//	     __ __
		// top^	/    /| 
		//    |/_  _/_|
		//	   |    | | 
		//	   |____|/|
		//            v
		//			  below

		osg::Vec3 normal_top = (m_pVertices->at(8*i+1) - m_pVertices->at(8*i+0)) ^ (m_pVertices->at(8*i+3) - m_pVertices->at(8*i+0));
		osg::Vec3 normal_blw = (m_pVertices->at(8*i+5) - m_pVertices->at(8*i+6)) ^ (m_pVertices->at(8*i+7) - m_pVertices->at(8*i+6));

		normal_top.normalize();
		normal_blw.normalize();

		// Each Cell have 6 normal vector
		pNormalize->push_back(normal_top);
		pNormalize->push_back(normal_top);
		pNormalize->push_back(normal_top);
		pNormalize->push_back(normal_top);
		pNormalize->push_back(normal_blw);
		pNormalize->push_back(normal_blw);
		pNormalize->push_back(normal_blw);
		pNormalize->push_back(normal_blw);
	}

	m_pCellGeom->setNormalArray(pNormalize.get(), osg::Array::BIND_PER_VERTEX);
}

void CX3DGridModelBuilder::_CalcVertices(const QList<CXGridCell*> &listCells)
{
	m_pVertices = new osg::Vec3Array;
	m_pVecIJK = new osg::Vec3usArray(listCells.size());

	for (int i=0; i!=listCells.size(); ++i)
	{
		unsigned short usI, usJ, usK;

		double *d = listCells[i]->GetVertex();
		listCells[i]->GetIJK(usI, usJ, usK);

		(*m_pVecIJK)[i]._v[0] = usI;
		(*m_pVecIJK)[i]._v[1] = usJ;
		(*m_pVecIJK)[i]._v[2] = usK;

		for (int j=0; j<24; j+=3)
		{
			osg::Vec3 vecLocal;
			m_pCoordMap->MapWorldToLocal(osg::Vec3d(d[j], d[j+1], d[j+2]), vecLocal);
			m_pVertices->push_back(vecLocal);
		}		
	}

	m_pCellGeom->setVertexArray(m_pVertices.get());
	m_pGridGeom->setVertexArray(m_pVertices.get());
}

void CX3DGridModelBuilder::_CalcColor()
{
	QColor geomColor = m_pViewInfo->GetGeomColor();
	QColor lineColor = m_pViewInfo->GetLineColor();

	// Geometry
	osg::ref_ptr<osg::Vec4Array> pGeomColor = new osg::Vec4Array(1);
	(*pGeomColor)[0].set(geomColor.redF(), geomColor.greenF(), geomColor.blueF(), geomColor.alphaF());
	m_pCellGeom->setColorArray(pGeomColor);
	m_pCellGeom->setColorBinding(osg::Geometry::BIND_OVERALL);

	// Grid line
	osg::Vec4Array *pLineColor = dynamic_cast<osg::Vec4Array *>(m_pGridGeom->getColorArray());
	if (pLineColor)
	{
		osg::Vec4 &color = pLineColor->at(0);
		color.set(lineColor.redF(), lineColor.greenF(), lineColor.blueF(), lineColor.alphaF());
	}
	else
	{
		pLineColor = new osg::Vec4Array(1);
		(*pLineColor)[0].set(lineColor.redF(),lineColor.greenF(),lineColor.blueF(),lineColor.alphaF());
		m_pGridGeom->setColorArray(pLineColor);
		m_pGridGeom->setColorBinding(osg::Geometry::BIND_OVERALL);

		// Grid line width
		m_pGridGeom->getOrCreateStateSet()->setMode( GL_LINE_SMOOTH, osg::StateAttribute::ON );
		osg::LineWidth* linewidth = new osg::LineWidth();
		linewidth->setWidth(1.0f);
		m_pGridGeom->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);
	}
}

void CX3DGridModelBuilder::_CalcIndices(bool bInit)
{
	unsigned uMinI = m_pViewInfo->GetMinI()-1;
	unsigned uMinJ = m_pViewInfo->GetMinJ()-1;
	unsigned uMinK = m_pViewInfo->GetMinK()-1;
	unsigned uMaxI = m_pViewInfo->GetMaxI()-1;
	unsigned uMaxJ = m_pViewInfo->GetMaxJ()-1;
	unsigned uMaxK = m_pViewInfo->GetMaxK()-1;

	bool bDisplayGrid = m_pViewInfo->GetDisplayLine();

	osg::ref_ptr<osg::DrawElementsUInt> pCellPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	if (bInit)
		m_pCellGeom->addPrimitiveSet(pCellPrimitive.get());
	else
		m_pCellGeom->setPrimitiveSet(0, pCellPrimitive.get());

	osg::ref_ptr<osg::DrawElementsUInt> pGridPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
	if (bInit)
		m_pGridGeom->addPrimitiveSet(pGridPrimitive.get());
	else
		m_pGridGeom->setPrimitiveSet(0, pGridPrimitive.get());

	for (int i=0; i<m_pVecIJK->size(); ++i)
	{
		const osg::Vec3us &vec = m_pVecIJK->at(i);

		if (vec.z() <= uMaxK && vec.z() >= uMinK && vec.y() <= uMaxJ && vec.y() >= uMinJ && vec.x() <= uMaxI && vec.x() >= uMinI)
		{
			// Draw the grid geometry
			for (int j=0; j<24; ++j)
			{
				pCellPrimitive->push_back(m_arrayIndex[j] + 8*i);
				if (bDisplayGrid)
					pGridPrimitive->push_back(m_arrayLines[j] + 8*i);
			}
		}
	}
}

void CX3DGridModelBuilder::_CalcPropertyIndicesAndColor()
{
	CXPropertyModel *pPropModel = dynamic_cast<CXPropertyModel *>(::GetObjectByID(m_pViewInfo->GetAttributeObjID()));
	if (pPropModel == NULL)
	{
		_CalcIndices();
		return;
	}

	unsigned uNum;
	double *pData = pPropModel->GetData(uNum);
	assert(uNum == m_pVecIJK->size());

	unsigned uMinI = m_pViewInfo->GetMinI()-1;
	unsigned uMinJ = m_pViewInfo->GetMinJ()-1;
	unsigned uMinK = m_pViewInfo->GetMinK()-1;
	unsigned uMaxI = m_pViewInfo->GetMaxI()-1;
	unsigned uMaxJ = m_pViewInfo->GetMaxJ()-1;
	unsigned uMaxK = m_pViewInfo->GetMaxK()-1;

	// Geometry
	bool bDisplayGrid = m_pViewInfo->GetDisplayLine();

	osg::ref_ptr<osg::DrawElementsUInt> pCellPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	osg::ref_ptr<osg::DrawElementsUInt> pGridPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
	
	for (int i=0; i<uNum; ++i)
	{
		const osg::Vec3us &vec = m_pVecIJK->at(i);

		if (pData[i] != -999.25 && vec.z() <= uMaxK && vec.z() >= uMinK && vec.y() <= uMaxJ && vec.y() >= uMinJ && 
			vec.x() <= uMaxI && vec.x() >= uMinI)
		{
			// Draw the grid geometry
			for (int j=0; j<24; ++j)
				pCellPrimitive->push_back(m_arrayIndex[j] + 8*i);

			if (bDisplayGrid)
			{
				// Draw the top and below lines.
				for (int j=0; j<24; ++j)
					pGridPrimitive->push_back(m_arrayLines[j] + 8*i);
			}
		}
	}

	m_pCellGeom->setPrimitiveSet(0, pCellPrimitive.get());
	m_pGridGeom->setPrimitiveSet(0, pGridPrimitive.get());

	// Color
	double dMin = m_pViewInfo->GetDisplayDataMin();
	double dMax = m_pViewInfo->GetDisplayDataMax();
	double dRange = dMax - dMin;
	CXColormap *pColorMap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());

	osg::ref_ptr<osg::Vec4Array> pPropColor = new osg::Vec4Array(m_pVertices->size());

	for (int i=0; i<uNum; ++i)
	{
		QColor color;
		if (pData[i] != ::g_dInvalidData)
		{
			double dPercent = (pData[i] - dMin)/dRange;
			color = pColorMap->GetColorAt(255 * dPercent);
		}
		else
		{
			color = m_pViewInfo->GetGeomColor();
		}

		for (int j=0; j<8; ++j)
			(*(pPropColor.get()))[i*8+j].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	}

	m_pCellGeom->setColorArray(pPropColor.get());
	m_pCellGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

}