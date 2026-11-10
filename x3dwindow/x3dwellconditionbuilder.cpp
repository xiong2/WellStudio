#include "x3dwellconditionbuilder.h"
#include "x3dwindow.h"
#include "xglobal.h"
#include "x3dbuilderfactory.h"
#include "xwellcondition.h"
#include "xgridmodel.h"
#include "xwellcells.h"
#include "xgridcell.h"
#include "x3dglobalcoordmap.h"
#include "xviewinfowellcondition.h"
#include "xcurvecells.h"
#include "xwellcurvecells.h"
#include "xcolormap.h"

#include <QDebug>
#include <cassert>

#include <osg/Geometry>
#include <osg/Point>
#include <osg/PolygonMode>
#include <osg/LineWidth>

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DWellConditionBuilder)
{EXWellCondition, e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CX3DWellConditionBuilder)

unsigned CX3DWellConditionBuilder::m_arrayIndex[24] = {	
	0,3,2,1,	// top
	0,4,7,3,	// left
	0,1,5,4,	// front
	1,2,6,5,	// right
	2,3,7,6,	// back
	4,5,6,7		// below)
};

unsigned CX3DWellConditionBuilder::m_arrayLines[24] = {
	0,1,1,2,2,3,3,0,
	4,5,5,6,6,7,7,4,
	0,4,1,5,2,6,3,7
};

CX3DWellConditionBuilder::CX3DWellConditionBuilder()
	: CX3DBuilderAbstract()
{
	m_pCellGeom = NULL;
	m_pGridGeom = NULL;
	m_pVertices = NULL;
}

CX3DWellConditionBuilder::~CX3DWellConditionBuilder()
{
	CX3DWindow* pWin = dynamic_cast<CX3DWindow*>(m_pCurWin);
	pWin->SetGridModelControl(false);
}

osg::ref_ptr<osg::Group> CX3DWellConditionBuilder::Build(QUuid objId)
{
	if (m_pBuilderNode == nullptr)
		m_pBuilderNode=new osg::Group;

	// Get object
	m_pWellCondition = dynamic_cast<CXWellCondition*>(::GetObjectByID(objId));
	if (!m_pWellCondition) 
		return NULL;

	// Get viewinfo
	m_pViewInfo = dynamic_cast<CXViewInfoWellCondition*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pViewInfo)
		return NULL;

	m_pCellGeom = new osg::Geometry;
	m_pCellGeom->setName("Well Condition Cell Geometry");
	m_pCellGeom->setUseVertexBufferObjects(true);

	m_pGridGeom = new osg::Geometry;
	m_pGridGeom->setName("Well Condition Grid Line");
	m_pGridGeom->setUseVertexBufferObjects(true);

	_CalcVertices();
	_CalcNormal();
	_CalcIndices(true);
	_CalcColor();

	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	pGeode->setName(m_pWellCondition->GetObjectName().toLatin1().data());
	pGeode->addDrawable(m_pCellGeom.get());
	pGeode->addDrawable(m_pGridGeom.get());
	m_pBuilderNode->addChild(pGeode.get());

	return m_pBuilderNode.get();
}

void CX3DWellConditionBuilder::UpdateNode(EEventType eType)
{
	if (eType == EInfoChanged || eType == EColormapChanged)
	{
		_CalcPropertyColor();
	}
}

void CX3DWellConditionBuilder::_CalcVertices()
{
	// Get datas from grid model
	CXObject *pModel = m_pWellCondition->GetParent();
	CXGridModel *pGridModel = dynamic_cast<CXGridModel*>(pModel->GetChildren(EXGridModel).at(0));
	const QList<CXGridCell*> &listCells = pGridModel->GetAllCells();
	m_pWellCondition->SetColor(pGridModel->GetColor());

	// Calculate vertices
	// Each cell has 8 vertices.
	m_pVertices = new osg::Vec3Array;
	m_pVertices->reserve(listCells.size() * 8);
	
	for (CXGridCell* pCell : listCells)
	{
		double *dVertex = pCell->GetVertex();
		for (int i=0; i<24; i+=3)
		{
			osg::Vec3 vecLocal;
			m_pCoordMap->MapWorldToLocal(osg::Vec3d(dVertex[i], dVertex[i+1], dVertex[i+2]), vecLocal);
			m_pVertices->push_back(vecLocal);
		}
	}

	m_pCellGeom->setVertexArray(m_pVertices.get());
	m_pGridGeom->setVertexArray(m_pVertices.get());
}

void CX3DWellConditionBuilder::_CalcIndices(bool bInit)
{
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

	// Get well condition cell index list
	m_listWellCellIndexes.clear();
	const std::vector<int> &vecVisible = m_pViewInfo->GetWellVisibleList();
	const std::vector<QUuid> &vecWellId = m_pViewInfo->GetWellList();

	QList<CXObject *> listWellCells = m_pWellCondition->GetChildren(EXWellCells);
	for (CXObject *pObj : listWellCells)
	{
		CXWellCells *pWellCells = dynamic_cast<CXWellCells *>(pObj);
		auto found = std::find(vecWellId.begin(), vecWellId.end(), pWellCells->GetWellID());
		if (found != vecWellId.end())
		{
			int idx = std::distance(vecWellId.begin(), found);
			if (vecVisible[idx])
				m_listWellCellIndexes.append(pWellCells->GetCellList());
		}
	}
	
	for (unsigned i : m_listWellCellIndexes)
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

void CX3DWellConditionBuilder::_CalcColor()
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

void CX3DWellConditionBuilder::_CalcNormal()
{
	osg::ref_ptr<osg::Vec3Array> pNormalize = new osg::Vec3Array;

	for (int i=0; i<m_pVertices->size()/8; ++i)
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

void CX3DWellConditionBuilder::_CalcPropertyColor()
{
	CXCurveCells *pCurveCells = dynamic_cast<CXCurveCells*>(::GetObjectByID(m_pViewInfo->GetAttributeObjID()));
	if (pCurveCells == NULL)
	{
		_CalcColor();
		return;
	}

	osg::DrawElementsUInt* pCellPrimitive = dynamic_cast<osg::DrawElementsUInt*>(m_pCellGeom->getPrimitiveSet(0));

	unsigned uNum;
	double *pData = pCurveCells->GetData(uNum);
	assert(uNum == m_listWellCellIndexes.size());

	// Color
	double dMin = m_pViewInfo->GetDisplayDataMin();
	double dMax = m_pViewInfo->GetDisplayDataMax();
	double dRange = dMax - dMin;
	CXColormap *pColorMap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());
	
	osg::ref_ptr<osg::Vec4Array> pPropColor = new osg::Vec4Array(m_pVertices->size());

	for (int i=0; i<uNum; ++i)
	{
		if (pData[i] != ::g_dInvalidData)
		{
			double dPercent = (pData[i] - dMin)/dRange;
			int index = qBound(0, (int)(dPercent*255), 255);
			const QColor &rColor = pColorMap->GetColorAt(index);

			for (int j=0; j<8; ++j)
			{
				(*pPropColor)[m_listWellCellIndexes.at(i)*8+j].set(rColor.redF(), rColor.greenF(), rColor.blueF(), rColor.alphaF());
			}
		}
	}

	m_pCellGeom->setColorArray(pPropColor.get());
	m_pCellGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
}