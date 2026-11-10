#include "x3dcurvelogbuilder.h"
#include "xwellcurve.h"
#include "xglobal.h"
#include "x3dbuilderfactory.h"
#include "xwell.h"
#include "xwellpath.h"
#include <osg/Geometry>
#include <osg/Switch>
#include "x3dwellpathbuilder.h"
#include "x3dwindow.h"
#include "xlinearitymap.h"
#include "xcolormap.h"
#include "xviewinfowellcurve.h"
#include "x3dglobalcoordmap.h"
#include "x3dutility.h"
BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DCurveLogBuilder)
{EXWellCurve,e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CX3DCurveLogBuilder)


CX3DCurveLogBuilder::CX3DCurveLogBuilder(void)
{
	m_bScalable = false;
	m_pCurveNode = NULL;
	m_pCylinderNode = NULL;

}
CX3DCurveLogBuilder::~CX3DCurveLogBuilder(void)
{
}
ref_ptr<Group> CX3DCurveLogBuilder::Build(QUuid objId)
{
	CXViewInfoObject *pObjViewInfo= m_pCurWin->GetObjectViewInfo(objId);
	m_pViewInfo=dynamic_cast<CXViewInfoWellCurve*>(pObjViewInfo);
	m_pWellCurve = dynamic_cast<CXWellCurve *>(::GetObjectByID(objId));
	if(m_pWellCurve == NULL)
		return NULL;
	ref_ptr<Group> pCurveNode = _CreateShapeStucture();
		return pCurveNode;
}
void CX3DCurveLogBuilder::_InitData()
{
	CXWell *pWell = dynamic_cast<CXWell*>(m_pWellCurve->GetParent());
	CXWellPath *pWellPath = dynamic_cast<CXWellPath*>(pWell->GetWellPath());
	double dX,dY;
	pWellPath->GetWellPosition(dX,dY);
	if(dX == g_dInvalidData || dY == g_dInvalidData)
		return ;

	unsigned int iNumber(0);
	double *pValue = m_pWellCurve->GetData();
	iNumber = m_pWellCurve->GetPointNumber();
	double dStep = m_pWellCurve->GetStep();
	double dStart,dEnd;
	m_pWellCurve->GetDepthRange(dStart,dEnd);
	double *pX = new double[iNumber];
	double *pY = new double[iNumber];
	double *pZ = new double[iNumber];
	for (int iPointIdx = 0 ; iPointIdx < iNumber ; ++iPointIdx)
	{
		QVector3D vecCoord;
		pWellPath->MapAttrPointToCoord(dStart + iPointIdx*dStep,vecCoord);
		pX[iPointIdx] = vecCoord.x();
		pY[iPointIdx] =vecCoord.y();
		pZ[iPointIdx] = vecCoord.z();
	}	
	vector<int> vecIndex;	
	vector<pair<int,int> >vecPathSegments;
	double dDataMin,dDataMax;
	m_pWellCurve->GetDataRange(dDataMin,dDataMax);
	int nWidth = m_pViewInfo->GetFillWidth();
	m_pLinearMap = new CXLinearityMap (dDataMin<1?dDataMin:log10(dDataMin),dDataMin <1?dDataMax:log10(dDataMax),0,nWidth);	
	CX3DWellPathBuilder::_SegmentWellPillar(pX,pY,pZ,iNumber,vecPathSegments);
	if (CXViewInfoWellCurve::EFlat == m_pViewInfo->GetDisplayMode3D())
	{	
		_BuildCurve(pX,pY,pZ,vecPathSegments);
	}
	else
	{
		//NX3DUtility::CurveSegmentationTwo(iNumber,pX,pY,pZ,vecIndex,0.000001);
		//int nCount = vecIndex.size();
		//double *pDataX = new double[nCount];
		//double *pDataY = new double[nCount];
		//double *pDataZ = new double[nCount];
		//double *pDataV = new double[nCount];
		//for (int i = 0  ; i < nCount; ++i)
		//{
		//	int iIdx = vecIndex[i];
		//	pDataX[i] = pX[iIdx];
		//	pDataY[i] = pY[iIdx];
		//	pDataZ[i] = pZ[iIdx];
		//	pDataV[i] = pValue[iIdx];
		//}	
		//CX3DWellPathBuilder::SegmentWellPillar(pDataX,pDataY,pDataZ,nCount,vecPathSegments);
		_CreateCylinderShape(iNumber,pX,pY,pZ,pValue,vecPathSegments);
		//delete[] pDataX;
		//delete[] pDataY;
		//delete[] pDataZ;
		//delete[] pDataV;
	}
	delete[] pX;
	delete[] pY;
	delete[] pZ;
}

ref_ptr<Group> CX3DCurveLogBuilder::_CreateShapeStucture()
{
	ref_ptr<Group> curveLogNode = new Group;
	m_pCurveNode = new osg::Geode;
	m_pCylinderNode = new osg::Geode;
	curveLogNode->addChild(m_pCurveNode);
	curveLogNode->addChild(m_pCylinderNode);
	_InitData();
	return curveLogNode;
}

void CX3DCurveLogBuilder:: _BuildCurve(double *pX,double *pY,double *pZ,std::vector<std::pair<int,int> > &segment)
{
	CX3DWindow* pOsgWin=dynamic_cast<CX3DWindow*>(m_pCurWin);
	if(!pOsgWin)
		return ;
	double dDataMin,dDataMax;
	m_pWellCurve->GetDataRange(dDataMin,dDataMax);
	double *pValue = m_pWellCurve->GetData();
	unsigned int nCount = m_pWellCurve->GetPointNumber();

	int iLineColorMode = m_pViewInfo->GetLineColorMode();
	int iFillColorMode = m_pViewInfo->GetFillColorMode();
	QColor wellFillColor= m_pViewInfo->GetFillColor();
	QColor FrameColor=Qt::white;
	QColor CurveColor= m_pViewInfo->GetLineColor();

	float fZScale = pOsgWin->GetZScale();
	
	osg::ref_ptr<osg::Vec3Array> pCurveVertex=new osg::Vec3Array();
	osg::ref_ptr<osg::Vec4Array> pVertexcolors = new osg::Vec4Array();	
	osg::ref_ptr<osg::Vec4Array> pCurvecolors = new osg::Vec4Array();	
	osg::ref_ptr<osg::Vec3Array> pFrameVertex1=new osg::Vec3Array();
	osg::ref_ptr<osg::Vec3Array> pFillVertex	=new osg::Vec3Array();

	vector<int> FillIndex; 
	vector<int> curveIndex;
	for (int nSeg = 0 ; nSeg < segment.size(); ++nSeg)
	{
		Vec3d transVertexD, transVertexNextD;
		Vec3f transVertex, transVertexNext;
		std::pair<int ,int> segPair = segment[nSeg];
		int iStart = segPair.first;
		int iEnd = segPair.second;	
		transVertexD.set(pX[iStart],pY[iStart],pZ[iStart]);
		m_pCoordMap->MapWorldToLocal(transVertexD, transVertex);

		transVertexNextD.set(pX[iEnd],pY[iEnd],pZ[iEnd]);
		m_pCoordMap->MapWorldToLocal(transVertexNextD, transVertexNext);
		transVertex[2] *=fZScale;
		transVertexNext[2] *= fZScale;
		
		osg::Matrixd matTransVertex;	
		Vec3f dirVec =transVertex -transVertexNext ;
		dirVec.normalize();

		if (nSeg == segment.size()-1)
		{
			iEnd+=1;
		}
		for (int i = iStart; i < iEnd ; ++i)
		{		
			Vec3d transVertexD1;
			Vec3f transVertex1;
			transVertexD1.set(pX[i],pY[i],pZ[i]);
			m_pCoordMap->MapWorldToLocal(transVertexD1, transVertex1);
			transVertex1[2] *= fZScale;
			matTransVertex.makeIdentity();
			matTransVertex.makeRotate(Vec3f(0.0,0.0,1.0),dirVec);	
			matTransVertex.postMultTranslate(transVertex1);	

			double dValue = pValue[i];
			if (dValue == ::g_dInvalidData)
			{
				dValue = dDataMin;
			}	
			if(iFillColorMode == 2) 
			{
				wellFillColor = _GetVertexColor(dValue);
			}
			if(dDataMin > 1)
			{
				dValue = ::log10(dValue);
			}
			float curradians=0;
			float fCurveWidth=m_pLinearMap->GetOutputValue(dValue);
			Vec3f oneCurveVertex(fCurveWidth*cosf(curradians),fCurveWidth*sinf(curradians),0.0f);
			Vec3f CurveSenceVertex=matTransVertex.preMult(oneCurveVertex);
			
			pFrameVertex1->push_back(transVertex1);
			pCurveVertex->push_back(CurveSenceVertex);
			curveIndex.push_back(i);
			pFillVertex->push_back(CurveSenceVertex);
			pVertexcolors->push_back(osg::Vec4f((float)wellFillColor.redF(),(float)wellFillColor.greenF(),(float)wellFillColor.blueF(),(float)wellFillColor.alphaF()));
			pCurvecolors->push_back(osg::Vec4f((float)CurveColor.redF(),(float)CurveColor.greenF(),(float)CurveColor.blueF(),(float)CurveColor.alphaF()));
		}

	}
	int iLoop = nCount-1;
	int iIndex = 0;
	for (int i = nCount -1 ; i >= 0 ; --i)
	{
		pFillVertex->push_back(pFrameVertex1->at(i));
		FillIndex.push_back(i);
		FillIndex.push_back(++iLoop);
		pVertexcolors->push_back(pVertexcolors->at(i));
	}
	if(m_pViewInfo->GetLineVisible())
	{
		osg::ref_ptr<osg::Geometry> curveGeometry=new osg::Geometry;
		curveGeometry->setVertexArray(pCurveVertex);
		curveGeometry->setColorArray(pCurvecolors, osg::Array::BIND_PER_VERTEX);
		curveGeometry->addPrimitiveSet(new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_STRIP,curveIndex.begin(),curveIndex.end()));	
		m_pCurveNode->addDrawable(curveGeometry);
		curveGeometry->setUseVertexBufferObjects(true);
	}
	if(m_pViewInfo->GetFillVisible())
	{
		osg::ref_ptr<osg::Geometry>FillGeometry=new osg::Geometry;
		FillGeometry->setVertexArray(pFillVertex);
		FillGeometry->setColorArray(pVertexcolors, osg::Array::BIND_PER_VERTEX);
		FillGeometry->addPrimitiveSet(new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP,FillIndex.begin(),FillIndex.end()));	
		m_pCurveNode->addDrawable(FillGeometry);
		FillGeometry->setUseVertexBufferObjects(true);
	}
}
QColor CX3DCurveLogBuilder::_GetVertexColor(double dValue,bool bLineColor)
{
	CXColormap *pColorMap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());
	if (pColorMap == NULL)
	{
		return QColor();
	}
	double dDataMin,dDataMax;
	m_pWellCurve->GetDataRange(dDataMin,dDataMax);
	CXLinearityMap linearMap(dDataMin,dDataMax,0,255);
	int nIndex = linearMap.GetOutputValue(dValue);
	return pColorMap->GetColorAt(nIndex);
}

void CX3DCurveLogBuilder::_CreateCylinderShape(int nCount ,double *pX,double *pY,double *pZ, double *pValue,vector<pair<int,int> >&segment)
{
	CX3DWindow* pOsgWin=dynamic_cast<CX3DWindow*>(m_pCurWin);
	if(!pOsgWin)
		return ;
	double dDataMin,dDataMax;
	m_pWellCurve->GetDataRange(dDataMin,dDataMax);
	float fZScale = pOsgWin->GetZScale();

	ref_ptr<Vec3Array> pCylinderVertex=new Vec3Array();
	ref_ptr<Vec4Array>  pVertexColors = new Vec4Array();	

	for (int nSeg = 0 ; nSeg < segment.size(); ++nSeg)
	{
		Vec3d transVertexD, transVertexNextD;
		Vec3f transVertex, transVertexNext;
		std::pair<int ,int> segPair = segment[nSeg];
		int iStart = segPair.first;
		int iEnd = segPair.second;	
		transVertexD.set(pX[iStart],pY[iStart],pZ[iStart]);
		m_pCoordMap->MapWorldToLocal(transVertexD, transVertex);
		transVertex[2] *=fZScale;
		transVertexNextD.set(pX[iEnd],pY[iEnd],pZ[iEnd]);
		m_pCoordMap->MapWorldToLocal(transVertexNextD, transVertexNext);
		transVertexNext[2] *= fZScale;

		Vec3f dirVec = transVertex -transVertexNext;
		dirVec.normalize();
		if (nSeg == segment.size()-1)
		{
			iEnd+=1;
		}
		for (int i = iStart; i < iEnd ; ++i)
		{	
			double dValue = pValue[i];
			if (dValue == ::g_dInvalidData)
			{
				dValue = dDataMin;
			}	
			if(dDataMin > 1)
			{
				dValue = ::log10(dValue);
			}
			float fCurveWidth=m_pLinearMap->GetOutputValue(dValue);
			osg::Matrixd matTransVertex;	
			Vec3d transVertexD1;
			Vec3f transVertex1;
			transVertexD1.set(pX[i],pY[i],pZ[i]);
			m_pCoordMap->MapWorldToLocal(transVertexD1, transVertex1);
			transVertex1[2] *= fZScale;
			matTransVertex.makeRotate(Vec3f(0.0,0.0,1.0),dirVec);	
			matTransVertex.postMultTranslate(transVertex1);	
		
			Vec3f vecFristVer;
			for(int iAngle=0; iAngle<360; iAngle+=18)
			{
				double curradians=DegreesToRadians((double)iAngle);
				Vec3f oneCircleVertex(fCurveWidth*cosf(curradians),fCurveWidth*sinf(curradians),0.0f);
				Vec3f onSeneVertex=matTransVertex.preMult(oneCircleVertex);
				pCylinderVertex->push_back(onSeneVertex);
				if(iAngle == 0)
				{
					vecFristVer = onSeneVertex;
				}
			}
			pCylinderVertex->push_back(vecFristVer);	
		}
	}
	int nCircleVerNum = pCylinderVertex->size()/nCount;
	std::vector<vector<int> >allIndex; 
	int  iFillColorMode = m_pViewInfo->GetFillColorMode();
	QColor wellFillColor = m_pWellCurve->GetColor();
	for(int i=0;i<nCount-1;i++)
	{
		std::vector<int>OneTriTripIndex;
		if(iFillColorMode == 2)
		{
			wellFillColor = _GetVertexColor(pValue[i]);
		}
		for(int j=0;j<nCircleVerNum;j++)
		{
			int curIndex=i*(nCircleVerNum)+j;
			int curIndexNext=(i+1)*(nCircleVerNum)+j;
			OneTriTripIndex.push_back(curIndex);
			OneTriTripIndex.push_back(curIndexNext);
			pVertexColors->push_back(Vec4f((double)wellFillColor.redF(),(double)wellFillColor.greenF(),(double)wellFillColor.blueF(),(double)wellFillColor.alphaF()));
		}
		allIndex.push_back(OneTriTripIndex);
	}	
	wellFillColor = _GetVertexColor(pValue[nCount-1]);
	for(int j=0;j<nCircleVerNum;j++)
	{
		pVertexColors->push_back(Vec4f((double)wellFillColor.redF(),(double)wellFillColor.greenF(),(double)wellFillColor.blueF(),(double)wellFillColor.alphaF()));
	}

	//shape structure	
	ref_ptr<Geometry> geom=new Geometry();
	m_pCylinderNode->addDrawable(geom);
	geom->setVertexArray(pCylinderVertex);
	geom->setColorArray(pVertexColors, Array::BIND_PER_VERTEX);
	for(int i=0;i<allIndex.size();i++)
	{
		geom->addPrimitiveSet(new DrawElementsUInt(PrimitiveSet::TRIANGLE_STRIP,allIndex[i].begin(),allIndex[i].end()));	
	}
}

 void CX3DCurveLogBuilder::UpdateNode(EEventType eType)
 {
	 if (eType == EDataChanged ||
		 eType == EInfoChanged)
	 {
		 if (m_pCurveNode)
			 m_pCurveNode->removeDrawables(0, m_pCurveNode->getNumDrawables());

		 if (m_pCylinderNode)
			 m_pCylinderNode->removeDrawables(0, m_pCylinderNode->getNumDrawables());
		 _InitData();
	 }
 }
