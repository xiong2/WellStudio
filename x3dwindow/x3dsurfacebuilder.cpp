#include "x3dsurfacebuilder.h"
#include "x3dsurface.h"
#include "xglobal.h"
#include "x3dbuilderfactory.h"
#include "xcolormap.h"
#include "x3dhorizon.h"
#include <QDebug>
#include <QtMath>

#include <osg/Point>
#include <osg/Group>
#include <osg/Vec3d>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Switch>
#include <osgUtil/SmoothingVisitor>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/FrontFace>
#include <osg/LightModel>
#include <osg/Material>
#include <osg/LineWidth>
#include <osgUtil/TriStripVisitor>
#include <osg/PolygonOffset>
#include <osgText/Text>
#include "x3dglobalcoordmap.h"
#include "xdbio.h"
#include "xviewinfosurface.h"
#include "x3dwindow.h"
#include "x3dscene.h"
#include "x3dutility.h"
#define MAX_DISTANCE2 10.0

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DSurfaceBuilder)
{EX3DSurface,e3DWindow},
{EX3DSurface,e3DBaseMap},
{ EX3DHorizon,e3DWindow },
{ EX3DHorizon,e3DBaseMap },
{ EXGS3DHorizonTWT,e3DWindow },
{ EXGS3DHorizonTWT,e3DBaseMap },
{ EXGS3DHorizonDepth,e3DWindow },
{ EXGS3DHorizonDepth,e3DBaseMap },
{ EXGS3DHorizonIso,e3DWindow },
{ EXGS3DHorizonIso,e3DBaseMap },
{ EXGS3DHorizonAtt,e3DWindow },
{ EXGS3DHorizonAtt,e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CX3DSurfaceBuilder)

CX3DSurfaceBuilder::CX3DSurfaceBuilder()
{
	m_pSurface = NULL;
	m_pIosSwitch=NULL;
	m_pVertices = NULL;
	m_ulightState=NULL;
}

CX3DSurfaceBuilder::~CX3DSurfaceBuilder()
{
	m_listValid.clear();
	m_vCell.clear();
}

osg::LineStipple* CX3DSurfaceBuilder::SetLineStyle(Qt::PenStyle curStyle)
{
	osg::LineStipple *pStipple=new osg::LineStipple();
	pStipple->setFactor(1);
	switch ( curStyle )
	{
	case Qt::SolidLine:
		pStipple->setPattern( 0xFFFF ) ; // solid
		break ;
	case Qt::DashLine:
		pStipple->setPattern( 0xfcfc ) ; // dash
		break;
	case Qt::DotLine:
		pStipple->setPattern( 0xcccc ) ; // dot
		break;
	case Qt::DashDotLine:
		pStipple->setPattern( 0xf99f ) ; // dash-dot 
		break;
	case Qt::DashDotDotLine:
		pStipple->setPattern( 0xf24f ) ; // dash-dot-dot
		break;
	default:
		break;
	}
	return pStipple;
}

osg::ref_ptr<osg::Switch> CX3DSurfaceBuilder::_BuildIOSCurve(float startValue,float endValue,float incValue,CRLContourInfo contourInfo)
{
	float datamin=startValue;
	float datamax=endValue;
	
	float* pData = m_pSurface->GetData();
	double xMin,xMax,yMin,yMax,zMin,zMax;
	m_pSurface->GetDimension(xMin,xMax,yMin,yMax,zMin,zMax);
	
	
	float interval=incValue;
	int majorCount=0;
	
	osg::ref_ptr<osg::Switch> pIOSCurveGroup=new osg::Switch;
	for(float begin=datamin+interval;begin<datamax;begin+=interval)
	{
		
		/*if(begin==1900)
		{
		osg::ref_ptr<osg::Geode> ptGeode= new osg::Geode;
		osg::Vec3 worldone(xMin,yMin,begin);
		osg::Vec3 worldtwo(xMin,yMax,begin);
		osg::Vec3 worldthree(xMax,yMax,begin);
		osg::Vec3 worldfour(xMax,yMin,begin);

		osg::Vec3 localone,localtwo,localthree,localfour;
		m_pCoordMap->MapWorldToLocal(worldone, localone);
		m_pCoordMap->MapWorldToLocal(worldtwo, localtwo);
		m_pCoordMap->MapWorldToLocal(worldthree, localthree);
		m_pCoordMap->MapWorldToLocal(worldfour, localfour);
		osg::Vec3Array *pArry=new osg::Vec3Array;
		osg::Vec4Array *pColor=new osg::Vec4Array;
		pColor->push_back(osg::Vec4(1.0,1.0,1.0,0.3));
		pArry->push_back(localone);
		pArry->push_back(localtwo);
		pArry->push_back(localthree);
		pArry->push_back(localfour);
		osg::Geometry *pGeo=new osg::Geometry;
		pGeo->setVertexArray(pArry);
		pGeo->setColorArray(pColor,osg::Array::BIND_OVERALL);
		pGeo->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));
		pGeo->getOrCreateStateSet()->setRenderingHint(2);
		ptGeode->addDrawable(pGeo);
		pIOSCurveGroup->addChild(ptGeode);
		}*/
		//if(begin==1900)
		{osg::ref_ptr<osg::Geode> pGeode=_CalIOSCurve(-begin);
		if(majorCount%contourInfo.m_MajorInterval==0)
		{
			
			osg::LineWidth *plineWidth=new osg::LineWidth;
			plineWidth->setWidth(contourInfo.m_MajorWeight);
			//osg::Material *pMaterial=new osg::Material;
			//pMaterial->setDiffuse(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(contourInfo.m_MajorColor.redF(),contourInfo.m_MajorColor.greenF(),contourInfo.m_MajorColor.blueF(),contourInfo.m_MajorColor.alphaF()));
			osg::StateSet *pState=pGeode->getOrCreateStateSet();
			pState->setAttribute(plineWidth,osg::StateAttribute::PROTECTED);
			//pState->setAttribute(pMaterial,osg::StateAttribute::PROTECTED);
			pState->setAttribute(SetLineStyle(contourInfo.m_MajorStyle),osg::StateAttribute::PROTECTED);
		}
		else
		{
			osg::LineWidth *plineWidth=new osg::LineWidth;
			plineWidth->setWidth(contourInfo.m_MinorWeight);
			//osg::Material *pMaterial=new osg::Material;
			//pMaterial->setDiffuse(osg::Material::Face::FRONT_AND_BACK,osg::Vec4(contourInfo.m_MinorColor.redF(),contourInfo.m_MinorColor.greenF(),contourInfo.m_MinorColor.blueF(),contourInfo.m_MinorColor.alphaF()));
			osg::StateSet *pState=pGeode->getOrCreateStateSet();
			pState->setAttribute(plineWidth,osg::StateAttribute::PROTECTED);
			//pState->setAttribute(pMaterial,osg::StateAttribute::PROTECTED);
			pState->setAttribute(SetLineStyle(contourInfo.m_MinorStyle),osg::StateAttribute::PROTECTED);
		}	
		pIOSCurveGroup->addChild(pGeode);
		majorCount++;
		}
	}
	pIOSCurveGroup->setNodeMask(2);
	return pIOSCurveGroup;
}
osg::ref_ptr<osg::Geode> CX3DSurfaceBuilder::_CalIOSCurve(float plotValue)
{

	osg::ref_ptr<osg::IntArray> StateArrayJ=new osg::IntArray(m_nJ*(m_nI+1));//vertical
	osg::ref_ptr<osg::IntArray> StateArrayI=new osg::IntArray(m_nI*(m_nJ+1));//horizon	
	osg::ref_ptr<osg::IntArray> StateArrayK=new osg::IntArray(m_nI*m_nJ);//slice
	std::vector<std::pair<int,int> >cellIntersect;

	for(unsigned int i=0;i<m_nI+1;i++)
	{ 
		for(unsigned int j=0;j<m_nJ;j++)
		{
			float zvb=(*m_pVertices)[i*(m_nJ+1)+j].z();
			float zve=(*m_pVertices)[i*(m_nJ+1)+j+1].z();
			float max=qMax(zvb,zve); float min=qMin(zvb,zve);
			float qBoundValue=qBound(min,plotValue,max);
			if(qBoundValue==plotValue)
			{
				(*StateArrayJ)[i*(m_nJ)+j]=1;
			}else
			{
				(*StateArrayJ)[i*(m_nJ)+j]=0;
			}
		}
	}

	for(unsigned int j=0;j<m_nJ+1;j++)
	{ 
		for(unsigned int i=0;i<m_nI;i++)
		{
			float zvb=(*m_pVertices)[i*(m_nJ+1)+j].z();
			float zve=(*m_pVertices)[(i+1)*(m_nJ+1)+j].z();
			float max=qMax(zvb,zve); float min=qMin(zvb,zve);
			float qBoundValue=qBound(min,plotValue,max);
			if(qBoundValue==plotValue)
			{
				(*StateArrayI)[j*(m_nI)+i]=1;
			}else
			{
				(*StateArrayI)[j*(m_nI)+i]=0;
			}
		}
	}

	for(unsigned int j=0;j<m_nJ;j++)
	{ 
		for(unsigned int i=0;i<m_nI;i++)
		{
			float zvb=(*m_pVertices)[(i+1)*(m_nJ+1)+j].z();
			float zve=(*m_pVertices)[(i)*(m_nJ+1)+j+1].z();

		
			float max=qMax(zvb,zve); float min=qMin(zvb,zve);
			float qBoundValue=qBound(min,plotValue,max);
			if(qBoundValue==plotValue)
			{
				(*StateArrayK)[j*(m_nI)+i]=1;
			}else
			{
				(*StateArrayK)[j*(m_nI)+i]=0;
			}
		}

	}
	for(unsigned int i=0;i<m_nI;i++)
	{
		for(unsigned int j=0;j<m_nJ;j++)
		{	
			CXCell onCell;
			
			onCell.left=i*m_nJ+j;
			onCell.right=(i+1)*m_nJ+j;
			onCell.top=j*m_nI+i;
			onCell.bottom=(j+1)*m_nI+i;
			onCell.slice=j*m_nI+i;
			onCell.ifTraced=false;
			onCell.traceCount=0;
			
			if(m_listValid[i*m_nJ+j]==true)
			{
				if((*StateArrayJ)[i*(m_nJ)+j]==1)			
					onCell.ifLeft=8;			
				if((*StateArrayJ)[(i+1)*m_nJ+j]==1)
					onCell.ifRight=4;
				if((*StateArrayI)[j*(m_nI)+i]==1)	
					onCell.ifTop=2;	
				if((*StateArrayI)[(j+1)*(m_nI)+i]==1)
					onCell.ifBottom=1;	
				if((*StateArrayK)[j*m_nI+i]==1)
					onCell.ifSlice=16;

				if(((onCell.ifLeft|onCell.ifRight|onCell.ifTop|onCell.ifBottom)&15)!=0)
                    cellIntersect.push_back(std::make_pair<int, int>(static_cast<int>(i), static_cast<int>(j)));
			}
			m_vCell.push_back(onCell);
		}
	}
	
	osg::ref_ptr<osg::Geode> pIosCurve=new osg::Geode;
	for(int k=0;k<cellIntersect.size();k++)
	{
		int i=cellIntersect[k].first;
		int j=cellIntersect[k].second;
		if(m_vCell[i*m_nJ+j].ifTraced)
		{
			continue;
		}
		std::vector<int> dirTrace;
		if(m_vCell[i*m_nJ+j].ifBottom!=0&&m_vCell[i*m_nJ+j].ifRight!=0&&m_vCell[i*m_nJ+j].ifSlice==0)
		{	
			if(m_vCell[i*m_nJ+j].ifRightBottom==1)
			{
				continue;
			}
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifBottom);
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifRight);
		}else if(m_vCell[i*m_nJ+j].ifLeft!=0&&m_vCell[i*m_nJ+j].ifTop!=0&&m_vCell[i*m_nJ+j].ifSlice==0)
		{	
			if(m_vCell[i*m_nJ+j].ifLeftTop==1)
			{
				continue;
			}
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifLeft);
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifTop);
		}else if(m_vCell[i*m_nJ+j].ifTop!=0&&m_vCell[i*m_nJ+j].ifBottom!=0&&m_vCell[i*m_nJ+j].ifSlice!=0)
		{	
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifTop);
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifBottom);
		}else if(m_vCell[i*m_nJ+j].ifLeft!=0&&m_vCell[i*m_nJ+j].ifRight!=0&&m_vCell[i*m_nJ+j].ifSlice!=0)
		{
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifLeft);
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifRight);
		}else if(m_vCell[i*m_nJ+j].ifLeft!=0&&m_vCell[i*m_nJ+j].ifBottom!=0&&m_vCell[i*m_nJ+j].ifSlice!=0)
		{
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifLeft);
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifBottom);
		
		}else if(m_vCell[i*m_nJ+j].ifTop!=0&&m_vCell[i*m_nJ+j].ifRight!=0&&m_vCell[i*m_nJ+j].ifSlice!=0)
		{
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifTop);
			dirTrace.push_back(m_vCell[i*m_nJ+j].ifRight);
		}else
		{
				continue;
		}
		/*
		if(dirTrace.size()>2&&m_vCell[i*nJ+j].ifSlice==false)
		{


		}*/
		
		osg::ref_ptr<osg::Vec3Array> traceInto=new osg::Vec3Array;
		osg::ref_ptr<osg::Vec3Array> traceOut=new osg::Vec3Array;
		/*osg::ref_ptr<osg::Vec3Array> cellNormalInto=new osg::Vec3Array;
		osg::ref_ptr<osg::Vec3Array> cellNormalOut=new osg::Vec3Array;*/
		std::vector<int>tracedCellIndexInto;
		std::vector<int>tracedCellIndexOut;
		
		bool ifLoop=_TraceCell(traceInto,tracedCellIndexInto,i*m_nJ+j,i*m_nJ+j,plotValue,dirTrace[0]);
		osg::Vec4Array *color=new osg::Vec4Array;
		color->push_back(osg::Vec4(1.0,0.0,0.0,1.0));
		if(!ifLoop)
		{	
			
			m_vCell[i*m_nJ+j].ifTraced=false;
			ifLoop =_TraceCell(traceOut,tracedCellIndexOut,i*m_nJ+j,i*m_nJ+j,plotValue,dirTrace[1]);
			m_vCell[i*m_nJ+j].ifTraced=true;
			if(ifLoop)
			{
				//assert(ifLoop);
				continue;
			}

			osg::ref_ptr<osg::Vec3Array> traceIntoRev=new osg::Vec3Array(traceInto->rbegin(),traceInto->rend());
			osg::ref_ptr<osg::Vec3Array> trace=new osg::Vec3Array;
			trace->insert(trace->begin(),traceIntoRev->begin(),traceIntoRev->end());
			trace->insert(trace->end(),traceOut->begin(),traceOut->end());

		
			osg::Geometry *pTraceLine=new osg::Geometry;
			pTraceLine->setVertexArray(trace);
			pTraceLine->setColorArray(color,osg::Array::BIND_OVERALL);
			pTraceLine->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP,0,trace->size()));
			pIosCurve->addDrawable(pTraceLine);

			std::vector<int> tracedCellIndexInto(tracedCellIndexInto.rbegin(),tracedCellIndexInto.rend());
			std::vector<int> tracedCellIndex;
			tracedCellIndex.insert(tracedCellIndex.begin(),tracedCellIndexInto.begin(),tracedCellIndexInto.end());
			tracedCellIndex.insert(tracedCellIndex.end(),tracedCellIndexOut.begin(),tracedCellIndexOut.end());

			osg::Vec3 beginVertex,endVertex;
			std::vector<std::pair<int,int> >annotationIndex;
			if(trace->size()>2)
			{
				
				SegmentIOSCurve(trace,annotationIndex,beginVertex,endVertex);
				
				for(int i=0;i<annotationIndex.size();i=i+2)
				{osg::Vec3f dir=(*trace)[annotationIndex[i].first]-(*trace)[annotationIndex[i].second];
				float length=dir.normalize();
				osg::ref_ptr<osgText::Text> annoGeom=new osgText::Text;
				QString qStr=QString::number(plotValue);
				osgText::String annoName(qStr.toStdString());
				osg::ref_ptr<osgText::Font> font=new osgText::Font;
				font=osgText::readFontFile("fonts/arial.ttf");
				annoGeom->setFont(font.get());
				annoGeom->setText(annoName);
				annoGeom->setCharacterSize(100);
				annoGeom->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS);
				annoGeom->setAutoRotateToScreen(false);
				
				annoGeom->setColor(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
				annoGeom->setPosition((*trace)[annotationIndex[i].second]+dir*(length/2));

				osg::Matrixd rot=osg::Matrixd::rotate(osg::Vec3f(1,0,0),(dir));
				osg::Quat rotQuat;
				rotQuat.set(rot);
				annoGeom->setRotation(rotQuat);
				pIosCurve->addDrawable(annoGeom);
				}
				
			}
			
			/*osg::Geometry *pTraceSample=new osg::Geometry;
			pTraceSample->setVertexArray(traceSample);
			osg::Vec4Array *colorsample=new osg::Vec4Array;
			colorsample->push_back(osg::Vec4(1.0,0.0,1.0,1.0));
			pTraceSample->setColorArray(colorsample,osg::Array::BIND_OVERALL);
			pTraceSample->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP,0,traceSample->size()));
			pIosCurve->addDrawable(pTraceSample);*/

		}else
		{
			if(traceInto->size()!=0)
			{
				osg::Geometry *pTraceInto=new osg::Geometry;
				pTraceInto->setVertexArray(traceInto);
				pTraceInto->setColorArray(color,osg::Array::BIND_OVERALL);
				pTraceInto->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP,0,traceInto->size()));
				pIosCurve->addDrawable(pTraceInto);
			}
		}

	}
	osg::LineWidth *pWidth=new osg::LineWidth;
	pWidth->setWidth(2);
	pIosCurve->getOrCreateStateSet()->setAttribute(pWidth,osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
	m_vCell.clear();
	return pIosCurve.get();
}

void CX3DSurfaceBuilder::SegmentIOSCurve(osg::Vec3Array *tracePoint,std::vector<std::pair<int,int> > &annotationIndex,osg::Vec3 &beginVertex,osg::Vec3 &endVertex)
{
	std::vector<int> vecPoints;
	//get new curve
	int nSampleNum=tracePoint->getNumElements();
	if(nSampleNum<=1)
	{
		return; //vecPoints;
	}
	unsigned int nFirst=0,nLast=nSampleNum-1;//nSampleNum must > 0
	/*double fFirstPoint[3]={(*tracePoint)[nFirst].x,(*tracePoint)[nFirst].y,(*tracePoint)[nFirst].z};
	double fLastPoint[3]={(*tracePoint)[nLast].x,(*tracePoint)[nLast].y,(*tracePoint)[nLast].z};*/
	
	vecPoints.push_back(0);
	while(nFirst<nLast)
	{
		double fMaxDistance2=0.0f;
		unsigned int nMaxNum=-1;
		unsigned int nMinNum=-1;
		//double fDis2=(pX[nLast]-pX[nFirst])*(pX[nLast]-pX[nFirst])+(pY[nLast]-pY[nFirst])*(pY[nLast]-pY[nFirst])+(pZ[nLast]-pZ[nFirst])*(pZ[nLast]-pZ[nFirst]);
		double fDis2=((*tracePoint)[nLast]-(*tracePoint)[nFirst])*((*tracePoint)[nLast]-(*tracePoint)[nFirst]);
		//get the max distance that point (pX[i],pY[i],pZ[i]) to the line
		for(int i=nFirst+1;i<nLast;i++)
		{
			//double fDistance2=(pX[i]-pX[nFirst])*(pX[i]-pX[nFirst])+(pY[i]-pY[nFirst])*(pY[i]-pY[nFirst])+(pZ[i]-pZ[nFirst])*(pZ[i]-pZ[nFirst]);
			double fDistance2=((*tracePoint)[i]-(*tracePoint)[nFirst])*((*tracePoint)[i]-(*tracePoint)[nFirst]);
			//double fTmp=(pX[nLast]-pX[nFirst])*(pX[i]-pX[nFirst])+(pY[nLast]-pY[nFirst])*(pY[i]-pY[nFirst])+(pZ[nLast]-pZ[nFirst])*(pZ[i]-pZ[nFirst]);
			double fTmp=((*tracePoint)[nLast]-(*tracePoint)[nFirst])*((*tracePoint)[i]-(*tracePoint)[nFirst]);
			fTmp *= fTmp/fDis2;
			fDistance2 -= fTmp;
			if(fDistance2>fMaxDistance2)
			{
				fMaxDistance2=fDistance2;
				nMaxNum=i;
			}
		}
		if(fMaxDistance2>=MAX_DISTANCE2)
		{
			nLast=nMaxNum;
		}
		else//if abs(max or min)<MAX_DISTANCE2 then push it back 
		{
			vecPoints.push_back(nLast);
			nFirst=nLast;
			nLast=nSampleNum-1;
		}
	}
	float maxlength=0.0f;
	//std::pair<int,int> pa;
	QMap<float,QPair<int,int> >traceIndexMap;
	int maxDiffIndex=0;
	int minDiffIndex=0;
	float sumLength=0.0f;
	
	for (int i = 0 ; i < vecPoints.size()-1; ++i)
	{
		
		int index=vecPoints[i];
		int indexNext=vecPoints[i+1];
		float diffLength=((*tracePoint)[indexNext]-(*tracePoint)[index]).length();
		sumLength=sumLength+diffLength;
		traceIndexMap.insert(diffLength,qMakePair<int,int>(index,indexNext));
	}
	float accumLength=0.0f;
	for(QMap<float,QPair<int,int> >::Iterator it=traceIndexMap.end()-1;it!=traceIndexMap.begin();it--)
	{
		float onelength=(float)it.key();
		float tempAccumLength=accumLength+onelength;
		float precentOfAnnoLength=tempAccumLength/sumLength;
		if(precentOfAnnoLength>0.4f)
		{
            annotationIndex.push_back(std::make_pair(it.value().first, it.value().second));
			break;
		}else 
		{
            annotationIndex.push_back(std::make_pair(it.value().first, it.value().second));
			accumLength=tempAccumLength;
		}

	}
	
}

osg::Vec3f CX3DSurfaceBuilder::_ComputeTracePoint(osg::Vec3f startPoint,osg::Vec3f endPoint,float plotValue)
{
	
	float zPer=(plotValue-startPoint[2])/(endPoint[2]-startPoint[2]);
	Q_ASSERT(zPer<=1.0);
	float xValue=zPer*(endPoint[0]-startPoint[0])+startPoint[0];
	float yValue=zPer*(endPoint[1]-startPoint[1])+startPoint[1];
	return osg::Vec3f(xValue,yValue,plotValue);
}
bool CX3DSurfaceBuilder::_TraceCell(osg::Vec3Array *vTrace,std::vector<int> &tracedCell,int cellIndex,int preCellIndex ,float plotValue,int traceDir)
{
	bool ifLoop=false;
	if(m_vCell[cellIndex].ifTraced)
		return ifLoop;
	//m_vCell[cellIndex].ifTraced=false;
	
	int leftIndex=m_vCell[cellIndex].left;
	int rightIndex=m_vCell[cellIndex].right;
	int topIndex=m_vCell[cellIndex].top;
	int bottomIndex=m_vCell[cellIndex].bottom;
	/*osg::Vec3f interPoint;*/
	//osg::Vec3f normalDir;
	tracedCell.push_back(cellIndex);
	if((m_vCell[cellIndex].ifLeft&traceDir)&&m_vCell[preCellIndex].right!=leftIndex){	
		
		if(cellIndex!=preCellIndex)
		{
			if(m_vCell[cellIndex].ifSlice)
			{	
				int sliceIndex=m_vCell[cellIndex].slice;
				int j=sliceIndex/m_nI;
				int i=sliceIndex%m_nI;
				
				osg::Vec3f interPoint=_ComputeTracePoint((*m_pVertices)[(i+1)*(m_nJ+1)+j],(*m_pVertices)[(i)*(m_nJ+1)+j+1],plotValue);
				vTrace->push_back(interPoint);

				/*int sumNum=(vTrace->size());
				osg::Vec3f traceDir=(interPoint-(*vTrace)[sumNum-2]);
				traceDir.normalize();
				osg::Vec3f sliceDir=(*m_pVertices)[(i+1)*(nJ+1)+j]-(*m_pVertices)[(i)*(nJ+1)+j+1];
				sliceDir.normalize();
				osg::Vec3f normalDir=traceDir^sliceDir;
				normalDir.normalize();			
				vNormal->push_back(normalDir);*/

				m_vCell[cellIndex].ifTraced=true;
			}else
			{
				m_vCell[cellIndex].traceCount++;
				if(m_vCell[cellIndex].traceCount==2)
				{
					m_vCell[cellIndex].ifTraced=true;
				}else
				{
					if(m_vCell[preCellIndex].ifBottom)
					{
						m_vCell[cellIndex].ifLeftTop=1;
						m_vCell[cellIndex].ifLeft=0;
					}
				}
			}
		}

		
		int i=m_vCell[cellIndex].left/m_nJ;
		int j=m_vCell[cellIndex].left%m_nJ;
		osg::Vec3f interLeft=_ComputeTracePoint((*m_pVertices)[i*(m_nJ+1)+j],(*m_pVertices)[i*(m_nJ+1)+j+1],plotValue);
		if(vTrace->size()!=0&&interLeft==(*vTrace)[0])// loop curve 
		{
			ifLoop=true;
			return ifLoop;
		}
		vTrace->push_back(interLeft);
		/**/

		/*if(vTrace->size()>1)
		{
		
			osg::Vec3f leftTraceDir=(interLeft-(*vTrace)[vTrace->size()-1]);
			leftTraceDir.normalize();	
			osg::Vec3f leftNormalDir=leftTraceDir^leftDir;
			leftNormalDir.normalize();
			vNormal->push_back(leftNormalDir);
		}
		else*/
	/*	{
			osg::Vec3f leftDir=((*m_pVertices)[i*(nJ+1)+j]-(*m_pVertices)[i*(nJ+1)+j+1]);
			leftDir.normalize();
			osg::Vec3f topDir=((*m_pVertices)[(i+1)*(nJ+1)+j]-(*m_pVertices)[i*(nJ+1)+j]);
			topDir.normalize();
			osg::Vec3f leftNormalDir=leftDir^topDir;
			leftNormalDir.normalize();
			vNormal->push_back(leftNormalDir);	
		}*/
	
		if((cellIndex-m_nJ)>0&& m_listValid[cellIndex-m_nJ])//not trace to boundary 
		{	
			return _TraceCell(vTrace,tracedCell,cellIndex-m_nJ,cellIndex,plotValue);
		}else{
			return ifLoop;
		}
	}else if((m_vCell[cellIndex].ifRight&traceDir)&&m_vCell[preCellIndex].left!=rightIndex)
	{
		if(cellIndex!=preCellIndex)
		{
			if(m_vCell[cellIndex].ifSlice)
			{	
				int sliceIndex=m_vCell[cellIndex].slice;
				int j=sliceIndex/m_nI;
				int i=sliceIndex%m_nI;
				
				osg::Vec3f interPoint=_ComputeTracePoint((*m_pVertices)[(i+1)*(m_nJ+1)+j],(*m_pVertices)[(i)*(m_nJ+1)+j+1],plotValue);
				vTrace->push_back(interPoint);

				//assert((vTrace->size()!=0));
				//int sumNum=(vTrace->size());
				//osg::Vec3f traceDir=(interPoint-(*vTrace)[sumNum-2]);
				//traceDir.normalize();
				//osg::Vec3f sliceDir=(*m_pVertices)[(i+1)*(nJ+1)+j]-(*m_pVertices)[(i)*(nJ+1)+j+1];
				//sliceDir.normalize();
				//osg::Vec3f normalDir=traceDir^sliceDir;
				//normalDir.normalize();
				//vNormal->push_back(normalDir);

				m_vCell[cellIndex].ifTraced=true;
			}else
			{
				m_vCell[cellIndex].traceCount++;
				if(m_vCell[cellIndex].traceCount==2)
				{
					m_vCell[cellIndex].ifTraced=true;
				}else
				{
					if(m_vCell[preCellIndex].ifTop)
					{
						m_vCell[cellIndex].ifRightBottom=1;
						m_vCell[cellIndex].ifRight=0;
					}
				}
			}
		}
		
		
		int i=m_vCell[cellIndex].right/m_nJ;
		int j=m_vCell[cellIndex].right%m_nJ;
		osg::Vec3f interRight=_ComputeTracePoint((*m_pVertices)[i*(m_nJ+1)+j],(*m_pVertices)[i*(m_nJ+1)+j+1],plotValue);
		if(vTrace->size()!=0&&(interRight==(*vTrace)[0]))
		{
			ifLoop=true;
			return ifLoop;
		}
		vTrace->push_back(interRight);
			
	
		/*if(vTrace->size()>1)
		{

		osg::Vec3f rightTraceDir=(interRight-(*vTrace)[vTrace->size()-1]);
		rightTraceDir.normalize();
		osg::Vec3f rightnormalDir=rightTraceDir^rightDir;
		rightnormalDir.normalize();
		vNormal->push_back(rightnormalDir);
		}
		else*/
		//{
		//osg::Vec3f rightDir=(*m_pVertices)[i*(nJ+1)+j]-(*m_pVertices)[i*(nJ+1)+j+1];
		//rightDir.normalize();
		//osg::Vec3f bottomDir=(*m_pVertices)[(i-1)*(nJ+1)+j+1]-(*m_pVertices)[i*(nJ+1)+j+1];
		//bottomDir.normalize();
		//osg::Vec3f rightnormalDir=rightDir^bottomDir;
		//rightnormalDir.normalize();
		////vNormal->push_back(rightnormalDir);
		//}
	
		if((cellIndex+m_nJ)<(m_nI*m_nJ)&& m_listValid[cellIndex+m_nJ])
			return _TraceCell(vTrace,tracedCell,cellIndex+m_nJ,cellIndex,plotValue);
		else return ifLoop;
	}
	else if((m_vCell[cellIndex].ifTop&traceDir)&&m_vCell[preCellIndex].bottom!=topIndex)
	{	
		if(cellIndex!=preCellIndex)
		{
			if(m_vCell[cellIndex].ifSlice)
			{	
				int sliceIndex=m_vCell[cellIndex].slice;
				int j=sliceIndex/m_nI;
				int i=sliceIndex%m_nI;
				//assert((vTrace->size()!=0));
				osg::Vec3f interPoint=_ComputeTracePoint((*m_pVertices)[(i+1)*(m_nJ+1)+j],(*m_pVertices)[(i)*(m_nJ+1)+j+1],plotValue);
				vTrace->push_back(interPoint);

				/*int sumNum=(vTrace->size());
				osg::Vec3f traceDir=(interPoint-(*vTrace)[sumNum-2]);
				traceDir.normalize();
				osg::Vec3f sliceDir=(*m_pVertices)[(i+1)*(nJ+1)+j]-(*m_pVertices)[(i)*(nJ+1)+j+1];
				sliceDir.normalize();
				osg::Vec3f normalDir=traceDir^sliceDir;
				normalDir.normalize();
				vNormal->push_back(normalDir);*/

				m_vCell[cellIndex].ifTraced=true;
			}else
			{
				m_vCell[cellIndex].traceCount++;
				if(m_vCell[cellIndex].traceCount==2)
				{
					m_vCell[cellIndex].ifTraced=true;
				}else
				{
					if(m_vCell[preCellIndex].ifRight)
					{
						m_vCell[cellIndex].ifLeftTop=1;
						m_vCell[cellIndex].ifTop=0;
					}
				}
			}
		}
		
		int j=m_vCell[cellIndex].top/m_nI;
		int i=m_vCell[cellIndex].top%m_nI;
		osg::Vec3f interTop=_ComputeTracePoint((*m_pVertices)[(i)*(m_nJ+1)+j],(*m_pVertices)[(i+1)*(m_nJ+1)+j],plotValue);
		if(vTrace->size()!=0&&interTop==(*vTrace)[0])
		{
			ifLoop=true;
			return ifLoop;
		}
		vTrace->push_back(interTop);
		
		/**/
		/*	if(vTrace->size()>1)
		{

		osg::Vec3f toptraceDir=(interTop-(*vTrace)[vTrace->size()-1]);
		toptraceDir.normalize();
		osg::Vec3f topnormalDir=toptraceDir^topDir;
		topnormalDir.normalize();
		vNormal->push_back(topnormalDir);
		}
		else*/
		/*{
		osg::Vec3f topDir=(*m_pVertices)[(i+1)*(nJ+1)+j]-(*m_pVertices)[i*(nJ+1)+j];
		topDir.normalize();
		osg::Vec3f leftDir=(*m_pVertices)[i*(nJ+1)+j]-(*m_pVertices)[i*(nJ+1)+j+1];
		leftDir.normalize();
		osg::Vec3f topnormalDir=topDir^leftDir;
		topnormalDir.normalize();
		vNormal->push_back(topnormalDir);
		}*/
	
		if((cellIndex-1)%m_nJ!=0&& m_listValid[cellIndex-1])
			return _TraceCell(vTrace,tracedCell,cellIndex-1,cellIndex,plotValue);
		else return ifLoop;
	}
	else if((m_vCell[cellIndex].ifBottom&traceDir)&&m_vCell[preCellIndex].top!=bottomIndex)
	{	
		if(cellIndex!=preCellIndex)
		{
		if(m_vCell[cellIndex].ifSlice)
		{	
			int sliceIndex=m_vCell[cellIndex].slice;
			int j=sliceIndex/m_nI;
			int i=sliceIndex%m_nI;
			
			osg::Vec3f interPoint=_ComputeTracePoint((*m_pVertices)[(i+1)*(m_nJ+1)+j],(*m_pVertices)[(i)*(m_nJ+1)+j+1],plotValue);
			vTrace->push_back(interPoint);

			//int sumNum=(vTrace->size());	
			////osg::Vec3f traceDir=(interPoint-vTrace->back());
			//osg::Vec3f traceDir=(interPoint-(*vTrace)[sumNum-2]);
			//traceDir.normalize();
			//osg::Vec3f sliceDir=(*m_pVertices)[(i+1)*(nJ+1)+j]-(*m_pVertices)[(i)*(nJ+1)+j+1];
			//sliceDir.normalize();
			//osg::Vec3f normalDir=traceDir^sliceDir;
			//normalDir.normalize();
			//vNormal->push_back(normalDir);

			m_vCell[cellIndex].ifTraced=true;
		}else
		{
			m_vCell[cellIndex].traceCount++;
			if(m_vCell[cellIndex].traceCount==2)
			{
				m_vCell[cellIndex].ifTraced=true;
			}else
			 {
			 if(m_vCell[preCellIndex].ifLeft)
			 {
			 m_vCell[cellIndex].ifRightBottom=1;
			 m_vCell[cellIndex].ifBottom=0;
			 }
			 }
		}
		}

		int j=m_vCell[cellIndex].bottom/m_nI;
		int i=m_vCell[cellIndex].bottom%m_nI;

		osg::Vec3f interBottom=_ComputeTracePoint((*m_pVertices)[i*(m_nJ+1)+j],(*m_pVertices)[(i+1)*(m_nJ+1)+j],plotValue);
		if(vTrace->size()!=0&&interBottom==(*vTrace)[0])
		{
			ifLoop=true;
			return ifLoop;
		}
		vTrace->push_back(interBottom);
		
		/**/
		/*if(vTrace->size()>1)
		{

		osg::Vec3f bottomtraceDir=(interBottom-(*vTrace)[vTrace->size()-1]);
		bottomtraceDir.normalize();		
		osg::Vec3f bttomnormalDir=bottomtraceDir^bottomDir;
		bttomnormalDir.normalize();
		vNormal->push_back(bttomnormalDir);
		}
		else*/
		/*	{
		osg::Vec3f bottomDir=(*m_pVertices)[i*(nJ+1)+j]-(*m_pVertices)[(i+1)*(nJ+1)+j];
		bottomDir.normalize();
		osg::Vec3f rightDir=(*m_pVertices)[(i+1)*(nJ+1)+j]-(*m_pVertices)[(i+1)*(nJ+1)+j-1];
		rightDir.normalize();
		osg::Vec3f bttomnormalDir=rightDir^bottomDir;
		bttomnormalDir.normalize();
		vNormal->push_back(bttomnormalDir);
		}
		*/
		
		if((cellIndex+1)%m_nJ!=0&& m_listValid[cellIndex+1])
			return _TraceCell(vTrace,tracedCell,cellIndex+1,cellIndex,plotValue);
		else return ifLoop;
	}else
	{
		return ifLoop;
	}
}

osg::StateSet* CX3DSurfaceBuilder::_CalcStateSet()
{
	m_pStateSet = new osg::StateSet;

	m_pStateSet->setAttribute(_BuildShaderProgram(), osg::StateAttribute::ON);
	m_pStateSet->setAttributeAndModes(new osg::PolygonOffset(1.0, 1.0), osg::StateAttribute::PROTECTED);
	
	m_pStateSet->addUniform(_BuildLighting());
	m_pStateSet->addUniform(new osg::Uniform("baseMap", e3DBaseMap == m_pCurWin->GetWindowType()));
	m_pStateSet->addUniform(_BuildColorTable());

	return m_pStateSet.get();
}

osg::Geometry * CX3DSurfaceBuilder::_BuildGeometry()
{
	m_pGeom = new osg::Geometry;

	if (!_CheckDataValid())
		return nullptr;

	m_pGeom->setVertexAttribArray(0, _CalcVertex(), osg::Array::BIND_PER_VERTEX);
	m_pGeom->setVertexAttribArray(1, _CalcNormal(), osg::Array::BIND_PER_VERTEX);
	m_pGeom->setVertexAttribArray(2, _CalcTexcoord(), osg::Array::BIND_PER_VERTEX);
	for (auto pDrawElement : _CalcIndices()) m_pGeom->addPrimitiveSet(pDrawElement);
	m_pGeom->setStateSet(_CalcStateSet());

	return m_pGeom.get();
}

osg::Geometry * CX3DSurfaceBuilder::_BuildFractureGeometry()
{
	m_pFracGeom = new osg::Geometry;

	if (!_CheckDataValid())
		return nullptr;

	const QUuid& uuidAzimuth = m_pViewInfo->GetFracAzimuth();
	const QUuid& uuidDensity = m_pViewInfo->GetFracDensity();
	int ndX = m_pViewInfo->GetFracDX();
	int ndY = m_pViewInfo->GetFracDY();
	float fScale = m_pViewInfo->GetFracScale();
	float fMinThreshold = m_pViewInfo->GetFracMinThreshold();
	float fMaxThreshold = m_pViewInfo->GetFracMaxThreshold();
	int iWidth = m_pViewInfo->GetFracWidth();
	int iHeight = m_pViewInfo->GetFracHeight();
	float fOffset = m_pViewInfo->GetFracOffset();
	CXViewInfoObject* pViewInfoDensity = m_pCurWin->GetObjectViewInfo(uuidDensity);

	std::vector<float> vecDensity, vecAzimuth, vecColor;
	CX3DHorizon::GetFractureInfo(uuidDensity, uuidAzimuth, ndX, ndY, fMinThreshold, fMaxThreshold, vecDensity, vecAzimuth, vecColor);

	if (vecDensity.empty() || vecAzimuth.empty() || vecColor.empty())
		return nullptr;
	
	int nDX = qMax(1, ndX);
	int nDY = qMax(1, ndY);

	int nFracNI = m_nI / nDY;
	int nFracNJ = m_nJ / nDX;

	osg::Vec3Array* pVertex = new osg::Vec3Array;
	osg::Vec4Array* pColors = new osg::Vec4Array;
	for (int i = 0; i < nFracNI; ++i)
	{
		int iMin = i * nDY;
		int iMax = iMin + nDY - 1;
		for (int j = 0; j < nFracNJ; ++j)
		{
			int jMin = j * nDX;
			int jMax = jMin + nDX - 1;

			osg::Vec3d vecCenter;
			if (m_pCurWin->GetWindowType() == e3DWindow)
			{
				vecCenter = _IJToWorld(m_pSurface->GetData(), (iMin + iMax) * 0.5, (jMin + jMax) * 0.5);
			}
			else
			{
				m_utm.IJToXY2((iMin + iMax) * 0.5, (jMin + jMax) * 0.5, vecCenter.x(), vecCenter.y());
			}

			float fAzimuth = vecAzimuth.at(i * nFracNJ + j);
			float fDensity = vecDensity.at(i * nFracNJ + j);
			float fColor = vecColor.at(i * nFracNJ + j);

			if (fAzimuth == ::g_dInvalidData && fDensity == ::g_dInvalidData)
				continue;

			if (fAzimuth < 0)
			{
				fAzimuth += 360;
			}

			osg::Vec3d vecUnitNormal{ qCos(fAzimuth), qSin(fAzimuth), 0.0 };
			osg::Vec3d vecNormal = vecUnitNormal * fDensity * fScale * 0.5;

			osg::Vec3 vecHead, vecEnd;
			m_pCoordMap->MapWorldToLocal(vecCenter - vecNormal, vecHead);
			m_pCoordMap->MapWorldToLocal(vecCenter + vecNormal, vecEnd);

			QColor color = m_pViewInfo->GetFracColor();

			if (m_pViewInfo->GetFracColorType() && pViewInfoDensity)
			{
				float fDisplayMin = pViewInfoDensity->GetDisplayDataMin();
				float fDisplayMax = pViewInfoDensity->GetDisplayDataMax();
				fColor = qBound(fDisplayMin, fColor, fDisplayMax);

				CXColormap* pColormap = CXColormap::GetColormap(pViewInfoDensity->GetColormapName());
				color = pColormap->ColorAt((fColor - fDisplayMin) / (fDisplayMax - fDisplayMin) * (pColormap->GetColorNum() - 1));
			}

			if (m_pCurWin->GetWindowType() == e3DWindow)
			{
				vecHead += osg::Vec3(0, 0, fOffset);
				vecEnd  += osg::Vec3(0, 0, fOffset);

				pVertex->push_back(vecHead - osg::Vec3(0, 0, iHeight / 2.f));
				pVertex->push_back(vecHead + osg::Vec3(0, 0, iHeight / 2.f));
				pVertex->push_back(vecEnd + osg::Vec3(0, 0, iHeight / 2.f));
				pVertex->push_back(vecEnd - osg::Vec3(0, 0, iHeight / 2.f));

				for (int i = 0; i != 4; ++i)
				{
					pColors->push_back(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
				}
			}
			else
			{
				pVertex->push_back(vecHead);
				pVertex->push_back(vecEnd);
				pColors->push_back(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
				pColors->push_back(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
			}
		}
	}
	m_pFracGeom->setVertexArray(pVertex);
	m_pFracGeom->setColorArray(pColors, osg::Array::BIND_PER_VERTEX);
	m_pFracGeom->addPrimitiveSet(new osg::DrawArrays(m_pCurWin->GetWindowType() == e3DWindow ? GL_QUADS : GL_LINES, 0, pVertex->size()));
	m_pFracGeom->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(iWidth), osg::StateAttribute::ON);
	
	if (m_pCurWin->GetWindowType() == e3DBaseMap)
	{
		m_pFracGeom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	}

	return m_pFracGeom.get();
}

osg::Geometry* CX3DSurfaceBuilder::_BuildPointsGeometry()
{
	m_pPointsGeom = new osg::Geometry;

	if (!_CheckDataValid())
		return nullptr;

	float fDisplayMin = m_pViewInfo->GetDisplayDataMin();
	float fDisplayMax = m_pViewInfo->GetDisplayDataMax();
	CXColormap* pColormap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());

	auto pVertex = new osg::Vec3Array(m_nI * m_nJ);
	auto pColors = new osg::Vec4Array(m_nI * m_nJ);
	for (int i = 0; i != m_nI; ++i)
	{
		for (int j = 0; j != m_nJ; ++j)
		{
			if (!m_listValid.at(i * m_nJ + j))
				continue;

			osg::Vec3d vecWorld;
			m_utm.IJToXY(i, j, vecWorld.x(), vecWorld.y());
			vecWorld.z() = m_pSurface->GetData()[i * m_nJ + j];

			m_pCoordMap->MapWorldToLocal(vecWorld, (*pVertex)[i * m_nJ + j]);

			float fColor = qBound(fDisplayMin, static_cast<float>(vecWorld.z()), fDisplayMax);
			QColor color = pColormap->ColorAt((fColor - fDisplayMin) / (fDisplayMax - fDisplayMin) * (pColormap->GetColorNum() - 1));
			(*pColors)[i * m_nJ + j] = NX3DUtility::Color2Vec(color);
		}
	}
	m_pPointsGeom->setVertexArray(pVertex);
	m_pPointsGeom->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, pVertex->size()));
	m_pPointsGeom->getOrCreateStateSet()->setAttribute(new osg::Point(m_pViewInfo->GetPointSize()), osg::StateAttribute::ON);
	
	switch (m_pViewInfo->GetPointColorType())
	{
	case 0:
		NX3DUtility::SetSingleColor(m_pPointsGeom, m_pViewInfo->GetPointColor());
		break;
	case 1:
		NX3DUtility::SetSingleColor(m_pPointsGeom, m_pViewInfo->GetColor());
		break;
	case 2:
		m_pPointsGeom->setColorArray(pColors, osg::Array::BIND_PER_VERTEX);
		break;
	default:;
	}

	if (m_pCurWin->GetWindowType() == e3DBaseMap)
	{
		m_pPointsGeom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	}

	return m_pPointsGeom.get();
}

bool CX3DSurfaceBuilder::_HasAttribute()
{
	if (m_pViewInfo->GetAttributeObjID() == m_objID)
		return false;

	m_pSurfaceAtt = dynamic_cast<CX3DSurface*>(::GetObjectByID(m_pViewInfo->GetAttributeObjID()));

	return m_pSurfaceAtt;
}

bool CX3DSurfaceBuilder::_CheckDataValid()
{
	float* pData = m_pSurface->GetData();
	Q_ASSERT(pData);

	m_listValid.clear();

	for (int i = 0; i != m_nI * m_nJ; ++i)
	{
		m_listValid << !qFuzzyCompare(pData[i], (float)::g_dInvalidData);
	}

	return m_listValid.contains(true);
}

osg::Vec3Array* CX3DSurfaceBuilder::_CalcVertex()
{
	m_pVertices = new osg::Vec3Array((m_nI + 1)*(m_nJ + 1));

	for (int i = 0; i <= m_nI; ++i)
	{
		double dI = qBound(0., i - 0.5, m_nI - 1.);
		for (int j = 0; j <= m_nJ; ++j)
		{
			double dJ = qBound(0., j - 0.5, m_nJ - 1.);
			m_pCoordMap->MapWorldToLocal(_IJToWorld(m_pSurface->GetData(), dI, dJ), (*m_pVertices)[i*(m_nJ + 1) + j]);
		}
	}
	
	return m_pVertices.get();
}

osg::Vec3Array* CX3DSurfaceBuilder::_CalcNormal()
{
	m_pNormals = new osg::Vec3Array((m_nI + 1)*(m_nJ + 1));

	for (int i = 0; i <= m_nI; ++i)
	{
		for (int j = 0; j <= m_nJ; ++j)
		{
			if (j == m_nJ || i == m_nI)
			{
				int prevI = (i == m_nI) ? i - 1 : i;
				int prevJ = (j == m_nJ) ? j - 1 : j;
				(*m_pNormals)[i*(m_nJ + 1) + j].set(m_pNormals->at(prevI*(m_nJ + 1) + prevJ));
				continue;
			}

			osg::Vec3 currP = m_pVertices->at(i*(m_nJ + 1) + j);
			osg::Vec3 nextJ = m_pVertices->at(i*(m_nJ + 1) + (j + 1));
			osg::Vec3 nextI = m_pVertices->at((i + 1)*(m_nJ + 1) + j);

			(*m_pNormals)[i*(m_nJ + 1) + j].set((nextJ - currP) ^ (nextI - currP));
			(*m_pNormals)[i*(m_nJ + 1) + j].normalize();
		}
	}

	return m_pNormals.get();
}

osg::Vec3d CX3DSurfaceBuilder::_IJToWorld(float* pData, double dI, double dJ)
{
	std::vector<double> vecValue;

	auto _GetValue = [&](int i, int j, std::vector<double>& vec)
	{
		int index = i * m_nJ + j;
		if (!m_listValid.at(index))
			return;
		vec.push_back(pData[index]);
	};

	_GetValue(qBound(0., dI - 0.5, m_nI - 1.), qBound(0., dJ - 0.5, m_nJ - 1.), vecValue);
	_GetValue(qBound(0., dI - 0.5, m_nI - 1.), qBound(0., dJ + 0.5, m_nJ - 1.), vecValue);
	_GetValue(qBound(0., dI + 0.5, m_nI - 1.), qBound(0., dJ - 0.5, m_nJ - 1.), vecValue);
	_GetValue(qBound(0., dI + 0.5, m_nI - 1.), qBound(0., dJ + 0.5, m_nJ - 1.), vecValue);

	osg::Vec3d vecWorld;
	m_utm.IJToXY2(dI, dJ, vecWorld.x(), vecWorld.y());

	// z's value is the mean of near 4 points.
	vecWorld.z() = vecValue.empty() ? 0. : std::accumulate(vecValue.cbegin(), vecValue.cend(), 0.0) / vecValue.size();

	return vecWorld;
}

osg::Uniform* CX3DSurfaceBuilder::_BuildColorTable()
{
	m_uColorTable = new osg::Uniform(osg::Uniform::FLOAT_VEC4, "colorTable", 256);

	if (m_pViewInfo->GetFillColorType() == 3)
	{
		const QMap<CXRange<float>, QColor>& rangeColor = m_pViewInfo->GetDiscreteContourFillColor();
		float fDataMin = m_pViewInfo->GetMinLevel();
		float fDataMax = m_pViewInfo->GetMaxLevel();

		for (auto iter = rangeColor.cbegin(); iter != rangeColor.cend(); ++iter)
		{
			int iBeg = qRound((qBound(fDataMin, iter.key().min, fDataMax) - fDataMin) / (fDataMax - fDataMin) * 255.f);
			int iEnd = qRound((qBound(fDataMin, iter.key().max, fDataMax) - fDataMin) / (fDataMax - fDataMin) * 255.f);
			for (int i = iBeg; i != iEnd; ++i)
			{
				const QColor& color = iter.value();
				m_uColorTable->setElement(i, osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
			}
		}
	}
	else
	{
		CXColormap* pColormap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());
		if (!pColormap)
			return m_uColorTable.get();

		for (int i = 0; i < 256; i++)
		{
			const QColor& color = pColormap->GetColorAt(i);
			m_uColorTable->setElement(i, osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
		}
	}

	return m_uColorTable.get();
}

osg::Uniform* CX3DSurfaceBuilder::_BuildLighting()
{
	m_ulightState = new osg::Uniform(osg::Uniform::INT, "lightState", 4);

	CX3DWindow* pCurWin = dynamic_cast<CX3DWindow*>(m_pCurWin);
	if (pCurWin && m_pGeom.valid())
	{
		const QBitArray& lightState = pCurWin->GetWindowInfo()->GetLightSwitch();
		for (int i = 0; i < lightState.size(); i++)
		{
			m_ulightState->setElement(i, int(lightState[i]));
		}
	}

	return m_ulightState.get();
}

osg::Program * CX3DSurfaceBuilder::_BuildShaderProgram()
{
	osg::Program* program = new osg::Program;

	std::string strVertex = QString(CXDBIO::GetShaderFilePath() + "surface.vert").toStdString();
	std::string strFrag = QString(CXDBIO::GetShaderFilePath() + "surface.frag").toStdString();

	program->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, strVertex));
	program->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, strFrag));
	program->addBindAttribLocation("myVertex", 0);
	program->addBindAttribLocation("myNormal", 1);
	program->addBindAttribLocation("myAttr", 2);

	return program;
}

void CX3DSurfaceBuilder::_CheckFractureDisplay()
{
	m_pGeode->removeDrawable(m_pFracGeom);

	if (!_HasAttribute())
	{
		m_pGeode->removeDrawable(m_pGeom.release());
	}

	m_pGeode->addDrawable(_BuildFractureGeometry());
}

void CX3DSurfaceBuilder::_CheckPointsDisplay()
{
	m_pGeode->removeDrawable(m_pPointsGeom);

	if (!_HasAttribute())
	{
		m_pGeode->removeDrawable(m_pGeom.release());
	}

	m_pGeode->addDrawable(_BuildPointsGeometry());
}

void CX3DSurfaceBuilder::_UpdateColor()
{
	if (!m_pGeom.valid() || !m_pStateSet.valid())
	{
		if (_HasAttribute())
		{
			m_pGeode->addDrawable(_BuildGeometry());
		}

		return;
	}

	if (2 == m_pViewInfo->GetDisplayMode() && !_HasAttribute())
	{
		m_pGeode->removeDrawable(m_pGeom.release());
	}
	else
	{
		m_pGeom->setVertexAttribArray(2, _CalcTexcoord(), osg::Array::BIND_PER_VERTEX);
		m_pStateSet->removeUniform(m_uColorTable);
		m_pStateSet->addUniform(_BuildColorTable());
		m_pGeom->setStateSet(m_pStateSet);
	}
}

const std::vector<osg::ref_ptr<osg::DrawElementsUInt>>& CX3DSurfaceBuilder::_CalcIndices()
{
	// [i,j]---------[i+1,j]    ----> i
	//   |               |      |
	//   |      *[i,j]   |      |
	//   |               |      v
	// [i,j+1]-------[i+1,j+1]  j

	m_vecDrawElements.clear();
	std::vector<uint> indices;

	for (int i = 0; i != m_nI; ++i)
	{
		for (int j = 0; j != m_nJ; ++j)
		{
			if (!m_listValid.at(i * m_nJ + j) && indices.empty()) // [i,j] invalid and [i, j-1] invalid too.
				continue;

			// [i,j] valid or [i, j-1] valid, both case need push [i,j] and [i+1,j]
			indices.push_back(i * (m_nJ + 1) + j);
			indices.push_back((i + 1) * (m_nJ + 1) + j);

			if (!m_listValid.at(i * m_nJ + j)) // if [i,j] invalid, stop this indices.
			{
				m_vecDrawElements.push_back(new osg::DrawElementsUInt(GL_TRIANGLE_STRIP, indices.cbegin(), indices.cend()));
				indices.clear();
			}
			else if (j == m_nJ - 1) // For last CDP.(additional)
			{
				indices.push_back(i * (m_nJ + 1) + m_nJ);
				indices.push_back((i + 1) * (m_nJ + 1) + m_nJ);
			}
		}
		if (!indices.empty())
		{
			m_vecDrawElements.push_back(new osg::DrawElementsUInt(GL_TRIANGLE_STRIP, indices.cbegin(), indices.cend()));
			indices.clear();
		}
	}

	return m_vecDrawElements;
}

osg::FloatArray* CX3DSurfaceBuilder::_CalcTexcoord()
{
	double fDataMin = m_pViewInfo->GetDisplayDataMin();
	double fDataMax = m_pViewInfo->GetDisplayDataMax();

	m_pTexCoord = new osg::FloatArray((m_nI + 1)*(m_nJ + 1));
	float* pData = _HasAttribute() ? m_pSurfaceAtt->GetData() : m_pSurface->GetData();

	for (int i = 0; i <= m_nI; ++i)
	{
		double dI = qBound(0., i - 0.5, m_nI - 1.);
		for (int j = 0; j <= m_nJ; ++j)
		{
			double dJ = qBound(0., j - 0.5, m_nJ - 1.);
			(*m_pTexCoord)[i*(m_nJ + 1) + j] = (qBound(fDataMin, _IJToWorld(pData, dI, dJ).z(), fDataMax) - fDataMin) / (fDataMax - fDataMin);
		}
	}
	return m_pTexCoord.get();
}

osg::ref_ptr<osg::Group> CX3DSurfaceBuilder::Build(QUuid objId)
{
	m_pBuilderNode = new osg::Group;
	m_pSurface = dynamic_cast<CX3DSurface*>(::GetObjectByID(objId));
	Q_ASSERT(m_pSurface);

	SetObjectID(objId);
	
	m_utm = m_pSurface->GetUTM();
	m_nI = m_utm.GetNI();
	m_nJ = m_utm.GetNJ();

	m_pViewInfo = dynamic_cast<CXViewInfoSurface*>(m_pCurWin->GetObjectViewInfo(objId));
	Q_ASSERT(m_pViewInfo);

	m_pGeode = new osg::Geode;

	switch (m_pViewInfo->GetDisplayMode())
	{
	case 0:
		m_pGeode->addDrawable(_BuildPointsGeometry());
		break;
	case 1:
		m_pGeode->addDrawable(_BuildGeometry());
		break;
	case 2:
		m_pGeode->addDrawable(_BuildFractureGeometry());
		break;
	default:
		Q_ASSERT(!"Invalid display mode.");
	}

	m_pGeode->setUserValue("objID",m_pSurface->GetObjectID().toString().toStdString());

	m_pBuilderNode->addChild(m_pGeode);
	m_pBuilderNode->dirtyBound();
	
	return m_pBuilderNode;
}

void CX3DSurfaceBuilder::UpdateNode(EEventType eType)
{
	if (EInfoChanged == eType || EDataChanged == eType)
	{
		switch (m_pViewInfo->GetDisplayMode())
		{
		case 0: // Points
			_CheckPointsDisplay();
			break;
		case 1: // Surface
			m_pGeode->removeDrawables(0, m_pGeode->getNumDrawables());
			m_pGeode->addDrawable(_BuildGeometry());
			break;
		case 2: // Fracture
			_CheckFractureDisplay();
			break;
		default:
			Q_ASSERT(!"Invalid display mode.");
		}

		if (3 == m_pViewInfo->GetFillColorType()) // discrete contour fill.
		{
			_UpdateColor();
		}

		if (m_pViewInfo->GetContourVisible())
		{
			if (m_pIosSwitch)
			{
				m_pIosSwitch->setAllChildrenOff();
				if (m_pIosSwitch->getNumChildren() != 0)
					m_pIosSwitch->removeChildren(0, 1);
			}
			m_pIosSwitch = NULL;

			float contourStart = m_pViewInfo->GetContourStart();
			float contourEnd = m_pViewInfo->GetContourEnd();
			float contourInc = m_pViewInfo->GetContourInc();

			CRLContourInfo contourInfo;
			contourInfo.m_MajorColor = m_pViewInfo->GetMajorContourColor();
			contourInfo.m_MajorStyle = static_cast<Qt::PenStyle>(m_pViewInfo->GetMajorLineStyle());
			contourInfo.m_MajorWeight = m_pViewInfo->GetMajorLineWeight();
			contourInfo.m_MajorInterval = m_pViewInfo->GetMajorLineInterval();

			contourInfo.m_MinorColor = m_pViewInfo->GetMinorContourColor();
			contourInfo.m_MinorStyle = static_cast<Qt::PenStyle>(m_pViewInfo->GetMinorLineStyle());
			contourInfo.m_MinorWeight = m_pViewInfo->GetMinorLineWeight();

			m_pIosSwitch = _BuildIOSCurve(contourStart, contourEnd, contourInc, contourInfo);
			m_pIosSwitch->setAllChildrenOn();
			m_pBuilderNode->addChild(m_pIosSwitch);
		}
		else
		{
			if (m_pIosSwitch)
			{
				m_pIosSwitch->setAllChildrenOff();
			}
		}
	}
	else if (EColormapChanged == eType)
	{
		_UpdateColor();
	}
	else if(eType == ELightToggle)
	{
		if (!m_pGeom.valid() || e3DWindow != m_pCurWin->GetWindowType())
			return;

		m_pGeom->getOrCreateStateSet()->removeUniform(m_ulightState);
		m_pGeom->getOrCreateStateSet()->addUniform(_BuildLighting());
	}
}
