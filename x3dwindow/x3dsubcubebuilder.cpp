#include "x3dsubcubebuilder.h"
#include "x3dbuilderfactory.h"
#include "xobject.h"
#include "xseismicsubvolume.h"
#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/StateSet>
#include <osg/PolygonMode>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/BlendFunci>
#include <osgDB/WriteFile>
#include <osgManipulator/TabBoxDragger>
#include <osg/MatrixTransform>
#include <osg/Depth>
#include "x3dwindow.h"
#include "x3dglobalcoordmap.h"
#include "xcolormap.h"
#include "xsubvolumedragercallback.h"
#include "xviewinfoobject.h"
#include "xdbio.h"
#include "xeventconsole.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DSubCubeBuilder)
{ EXSeismicSubVolume, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CX3DSubCubeBuilder)

CX3DSubCubeBuilder::CX3DSubCubeBuilder()
{

}

CX3DSubCubeBuilder::~CX3DSubCubeBuilder()
{

}

osg::ref_ptr<osg::Group> CX3DSubCubeBuilder::Build(QUuid objId)
{
	m_pBuilderNode = new osg::Group();
	m_pSubVolume = dynamic_cast<CXSeismicSubVolume*>(::GetObjectByID(objId));

	m_pChairSwitch = _BuildSubCube(m_pSubVolume);
	m_pBuilderNode->addChild(m_pChairSwitch);

	return m_pBuilderNode.get();
}

void CX3DSubCubeBuilder::UpdateNode(EEventType eType)
{
	if (eType == EDataChanged || (eType == EInfoChanged) || eType == EColormapChanged)
	{
		m_bChairMode = false;
		UpdateDrager(m_DragerCube);
	}
	if (eType == EChairmode)
	{
		m_bChairMode = true;
		UpdateDrager(m_DragerCube);
	}
}

bool CX3DSubCubeBuilder::UpdateDrager(vector<osg::Vec3f> DragerCube)
{
	CXSeismicDataVolume* dv = _GetDV();
	if (!dv)
		return false;

	CXSeismicUTMTool& utmTool = dv->GetUTM();
	int firstInline = utmTool.GetFirstInline();
	int lastInline = utmTool.GetLastInline();
	int firstCrossline = utmTool.GetFirstCrossline();
	int lastCrossline = utmTool.GetLastCrossline();
	double sampleStart, sampleEnd, sampleInterval;
	dv->GetSamplingRange(sampleStart, sampleEnd, sampleInterval);

	std::vector<Vec3d> worldVertex;
	int startInline, endInline, startCrossline, endCrossline;
	double timestart, timeend;
	for (int i = 0; i < DragerCube.size(); i++)
	{
		int iInline = 0;
		int iXline = 0;
		osg::Vec3d curWorldVertex;
		m_pCoordMap->MapLocalToWorld(DragerCube[i], curWorldVertex);

		bool ifSucess = utmTool.XYToLine(curWorldVertex.x(), curWorldVertex.y(), iInline, iXline);
		if (ifSucess)
		{
			if (i == 0)
			{
				startInline = iInline;
				startCrossline = iXline;
				timestart = curWorldVertex.z();
			}
			if (i == 1)
			{
				timeend = curWorldVertex.z();
			}
			if (i == 2)
			{
				endCrossline = iXline;
			}
			if (i == 6)
			{
				endInline = iInline;
			}
		}
		else
		{
			return false;
		}
	}
	m_DragerCube = DragerCube;

	CX3DWindow* pOSGWin = dynamic_cast<CX3DWindow*>(m_pCurWin);
	Q_ASSERT(pOSGWin);

	{
		CXProcessEvent processEvent;

		if (startInline == firstInline || endInline == lastInline
			|| startCrossline == firstCrossline || endCrossline == lastCrossline
			|| qFuzzyCompare(timestart, sampleStart) || qFuzzyCompare(timeend, sampleEnd))
			m_pSubVolume->AddEvent(EChairmode);
		else
			m_pSubVolume->AddEvent(EDataChanged);
	}

	m_pChairSwitch->setChildValue(m_pChairGeode, m_bChairMode);

	if (startInline >= firstInline&&startInline <= lastInline&&endInline >= firstInline&&endInline <= lastInline
		&&startCrossline >= firstCrossline&&startCrossline <= lastCrossline&&endCrossline >= firstCrossline&&endCrossline <= lastCrossline
		&& (timestart > sampleStart || qFuzzyCompare(timestart, sampleStart)) &&
		(timestart<sampleEnd || qFuzzyCompare(timestart, sampleEnd)) &&
		(timeend>sampleStart || qFuzzyCompare(timeend, sampleStart)) &&
		(timeend < sampleEnd || qFuzzyCompare(timeend, sampleEnd)))
	{
		if (!m_bChairMode)//NORMAL MODE
		{
			m_pChairSwitch->setChildValue(m_pChairGeode, false);
			osg::ref_ptr<osg::StateSet> pStateIS = new osg::StateSet;
			pStateIS = _GenerateTextureState((startInline), (startInline), (endInline), (startCrossline), (endCrossline), timestart, timeend, eInlineSection);
			m_pGeoInlineSectionStart->setStateSet(pStateIS);

			osg::ref_ptr<osg::StateSet> pStateIE = new osg::StateSet;
			pStateIE = _GenerateTextureState((endInline), (startInline), (endInline), (startCrossline), (endCrossline), timestart, timeend, eInlineSection);
			m_pGeoInlineSectionEnd->setStateSet(pStateIE);

			osg::ref_ptr<osg::StateSet> pStateXS = new osg::StateSet;
			pStateXS = _GenerateTextureState((startCrossline), (startInline), (endInline), (startCrossline), (endCrossline), timestart, timeend, eCrosslineSection);
			m_pGeoXlineSectionStart->setStateSet(pStateXS);

			osg::ref_ptr<osg::StateSet> pStateXE = new osg::StateSet;
			pStateXE = _GenerateTextureState((endCrossline), (startInline), (endInline), (startCrossline), (endCrossline), timestart, timeend, eCrosslineSection);
			m_pGeoXlineSectionEnd->setStateSet(pStateXE);

			osg::ref_ptr<osg::StateSet> pStateTS = new osg::StateSet;
			pStateTS = _GenerateTextureState(timestart, (startInline), (endInline), (startCrossline), (endCrossline), timestart, timeend, eTimeSlice);
			m_pGeoTimeSliceStart->setStateSet(pStateTS);

			osg::ref_ptr<osg::StateSet> pStateTE = new osg::StateSet;
			pStateTE = _GenerateTextureState(timeend, (startInline), (endInline), (startCrossline), (endCrossline), timestart, timeend, eTimeSlice);
			m_pGeoTimeSliceEnd->setStateSet(pStateTE);
		}
		else//CHAIR MODE 
		{
			//if(startInline>firstInline&&startInline<lastInline&&endInline>firstInline&&endInline<lastInline
			//	&&startCrossline>firstCrossline&&startCrossline<lastCrossline&&endCrossline>firstCrossline&&endCrossline<lastCrossline
			//	&&timestart>sampleStart&&timestart<sampleEnd&&timeend>sampleStart&&timeend<sampleEnd)
			//{
			//	osg::Depth *chairDepth=new osg::Depth;
			//	chairDepth->setWriteMask(true );
			//	chairDepth->setFunction(osg::Depth::ALWAYS);
			//	//m_pCubeGeode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);

			//	m_pChairGeode->getOrCreateStateSet()->setRenderBinDetails(-1,"RenderBin");

			//	m_pCubeGeode->getOrCreateStateSet()->setAttribute(chairDepth,osg::StateAttribute::PROTECTED);
			//	
			//	osg::PolygonMode *pm=new osg::PolygonMode;
			//	pm->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);
			//	//m_pCubeGeode->getOrCreateStateSet()->setAttribute(pm,osg::StateAttribute::PROTECTED);
			//	m_pGeoInlineSectionStart->getOrCreateStateSet()->clear();
			//	m_pGeoInlineSectionStart->getOrCreateStateSet()->setAttribute(pm,osg::StateAttribute::PROTECTED);
			//	m_pGeoInlineSectionEnd->getOrCreateStateSet()->clear();
			//	m_pGeoInlineSectionEnd->getOrCreateStateSet()->setAttribute(pm,osg::StateAttribute::PROTECTED);
			//	m_pGeoXlineSectionStart->getOrCreateStateSet()->clear();
			//	m_pGeoXlineSectionStart->getOrCreateStateSet()->setAttribute(pm,osg::StateAttribute::PROTECTED);
			//	m_pGeoXlineSectionEnd->getOrCreateStateSet()->clear();
			//	m_pGeoXlineSectionEnd->getOrCreateStateSet()->setAttribute(pm,osg::StateAttribute::PROTECTED);
			//	m_pGeoTimeSliceStart->getOrCreateStateSet()->clear();
			//	m_pGeoTimeSliceStart->getOrCreateStateSet()->setAttribute(pm,osg::StateAttribute::PROTECTED);
			//	m_pGeoTimeSliceEnd->getOrCreateStateSet()->clear();
			//	m_pGeoTimeSliceEnd->getOrCreateStateSet()->setAttribute(pm,osg::StateAttribute::PROTECTED);
			//	
			//	
			//	if(m_pChairSwitch->getChildValue(m_pChairGeode)==true)
			//	{
			//		return true;
			//	}else
			//	{
			//		m_pChairSwitch->setChildValue(m_pChairGeode,true);
			//	}

			//	osg::ref_ptr<osg::StateSet> pStateISChair=new osg::StateSet;
			//	pStateISChair=_GenerateTextureState((firstInline),(firstInline),(lastInline),(firstCrossline),(lastCrossline),sampleStart,sampleEnd,eInlineSection);
			//	m_pGeoInlineSectionChairStart->setStateSet(pStateISChair);

			//	osg::ref_ptr<osg::StateSet> pStateIEChair=new osg::StateSet;
			//	pStateIEChair=_GenerateTextureState((lastInline),(firstInline),(lastInline),(firstCrossline),(lastCrossline),sampleStart,sampleEnd,eInlineSection);
			//	m_pGeoInlineSectionChairEnd->setStateSet(pStateIEChair);

			//	osg::ref_ptr<osg::StateSet> pStateXSChair=new osg::StateSet;
			//	pStateXSChair=_GenerateTextureState((firstCrossline),(firstInline),(lastInline),(firstCrossline),(lastCrossline),sampleStart,sampleEnd,eCrosslineSection);
			//	m_pGeoXlineSectionChairStart->setStateSet(pStateXSChair);

			//	osg::ref_ptr<osg::StateSet> pStateXEChair=new osg::StateSet;
			//	pStateXEChair=_GenerateTextureState((lastCrossline),(firstInline),(lastInline),(firstCrossline),(lastCrossline),sampleStart,sampleEnd,eCrosslineSection);
			//	m_pGeoXlineSectionChairEnd->setStateSet(pStateXEChair);

			//	osg::ref_ptr<osg::StateSet> pStateTSChair=new osg::StateSet;
			//	pStateTSChair=_GenerateTextureState((sampleStart),(firstInline),(lastInline),(firstCrossline),(lastCrossline),sampleStart,sampleEnd,eTimeSlice);
			//	m_pGeoTimeSliceChairStart->setStateSet(pStateTSChair);

			//	osg::ref_ptr<osg::StateSet> pStateTEChair=new osg::StateSet;
			//	pStateTEChair=_GenerateTextureState((sampleEnd),(firstInline),(lastInline),(firstCrossline),(lastCrossline),sampleStart,sampleEnd,eTimeSlice);
			//	m_pGeoTimeSliceChairEnd->setStateSet(pStateTEChair);

			//	
			//	return true;
			//}
			//m_pChairGeode->getOrCreateStateSet()->setRenderBinDetails(0,"");
			m_pChairSwitch->getOrCreateStateSet()->setMode(GL_ALPHA_TEST, osg::StateAttribute::ON);
			m_pChairGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
			/*osg::Depth *chairDepth=new osg::Depth;
			chairDepth->setWriteMask(true) ;
			chairDepth->setFunction(osg::Depth::LESS);
			m_pCubeGeode->getOrCreateStateSet()->setAttribute(chairDepth,osg::StateAttribute::PROTECTED);*/

			BuildChairMode(dv, m_pGeoInlineSectionStart, m_pGeoInlineSectionChairStart, startInline, firstInline, startInline, endInline, startCrossline, endCrossline, timestart, timeend, eInlineSection);
			BuildChairMode(dv, m_pGeoInlineSectionEnd, m_pGeoInlineSectionChairEnd, endInline, lastInline, startInline, endInline, startCrossline, endCrossline, timestart, timeend, eInlineSection);
			BuildChairMode(dv, m_pGeoXlineSectionStart, m_pGeoXlineSectionChairStart, startCrossline, firstCrossline, startInline, endInline, startCrossline, endCrossline, timestart, timeend, eCrosslineSection);
			BuildChairMode(dv, m_pGeoXlineSectionEnd, m_pGeoXlineSectionChairEnd, endCrossline, lastCrossline, startInline, endInline, startCrossline, endCrossline, timestart, timeend, eCrosslineSection);
			BuildChairMode(dv, m_pGeoTimeSliceStart, m_pGeoTimeSliceChairStart, timestart, sampleStart, startInline, endInline, startCrossline, endCrossline, timestart, timeend, eTimeSlice);
			BuildChairMode(dv, m_pGeoTimeSliceEnd, m_pGeoTimeSliceChairEnd, timeend, sampleEnd, startInline, endInline, startCrossline, endCrossline, timestart, timeend, eTimeSlice);

		}
	}
	else
	{
		return false;
	}

	return true;
}

void CX3DSubCubeBuilder::BuildChairMode(CXSeismicDataVolume *dv, osg::ref_ptr<osg::Geometry> pSectionGeom, osg::ref_ptr<osg::Geometry> pSectionChairGeom, float curSection, float curChairSection, int startInline, int endInline, int startCrossline, int endCrossline, double timestart, double timeend, EXSectionType secType)
{
	CXSeismicUTMTool& utmTool = dv->GetUTM();
	int firstInline = utmTool.GetFirstInline();
	int lastInline = utmTool.GetLastInline();
	int firstCrossline = utmTool.GetFirstCrossline();
	int lastCrossline = utmTool.GetLastCrossline();
	double sampleStart, sampleEnd, sampleInterval;
	dv->GetSamplingRange(sampleStart, sampleEnd, sampleInterval);
	bool bSectionChair;
	if (secType == eInlineSection)
		bSectionChair = ((int)curSection > firstInline) && (curSection < lastInline);
	if (secType == eCrosslineSection)
		bSectionChair = ((int)curSection > firstCrossline) && (curSection < lastCrossline);
	if (secType == eTimeSlice)
		bSectionChair = ((int)curSection > sampleStart) && (curSection < sampleEnd);

	if (bSectionChair)
	{
		osg::ref_ptr<osg::StateSet> pStateIS = new osg::StateSet;
		pStateIS = _GenerateTextureState((curSection), (startInline), (endInline), (startCrossline), (endCrossline), timestart, timeend, secType);
		pSectionGeom->setStateSet(pStateIS);
		osg::ref_ptr<osg::StateSet> pStateISChair = new osg::StateSet;
		pStateISChair = _GenerateTextureState((curChairSection), (firstInline), (lastInline), (firstCrossline), (lastCrossline), sampleStart, sampleEnd, secType);
		pSectionChairGeom->setStateSet(pStateISChair);
	}
	else
	{
		pSectionGeom->getOrCreateStateSet()->clear();
		osg::PolygonMode *pPolygonMode = new osg::PolygonMode;
		pPolygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
		pSectionGeom->getOrCreateStateSet()->setAttribute(pPolygonMode, osg::StateAttribute::PROTECTED);
		pSectionChairGeom->getOrCreateStateSet()->clear();
		osg::ref_ptr<osg::StateSet> pStateISChair = new osg::StateSet;

		pStateISChair = _GenerateTextureState((curSection), (startInline), (endInline), (startCrossline), (endCrossline), timestart, timeend, secType, true);
		pSectionChairGeom->setStateSet(pStateISChair);
	}
}

osg::ref_ptr<osg::Geode>  CX3DSubCubeBuilder::_BuildSubVolume(int inlineStart, int inlineEnd, int xlineStart, int xlineEnd, double timeStart, double timeEnd, float zScale)
{
	m_pCubeGeode = new osg::Geode;
	m_pGeoInlineSectionStart = _BuildSectionGeom(inlineStart, inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd, eInlineSection);
	m_pGeoInlineSectionEnd = _BuildSectionGeom(inlineEnd, inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd, eInlineSection);
	m_pGeoXlineSectionStart = _BuildSectionGeom(xlineStart, inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd, eCrosslineSection);
	m_pGeoXlineSectionEnd = _BuildSectionGeom(xlineEnd, inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd, eCrosslineSection);
	m_pGeoTimeSliceStart = _BuildSectionGeom(timeStart, inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd, eTimeSlice);
	m_pGeoTimeSliceEnd = _BuildSectionGeom(timeEnd, inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd, eTimeSlice);

	m_pCubeGeode->addDrawable(m_pGeoInlineSectionStart.get());
	m_pCubeGeode->addDrawable(m_pGeoInlineSectionEnd.get());
	m_pCubeGeode->addDrawable(m_pGeoXlineSectionStart.get());
	m_pCubeGeode->addDrawable(m_pGeoXlineSectionEnd.get());
	m_pCubeGeode->addDrawable(m_pGeoTimeSliceStart.get());
	m_pCubeGeode->addDrawable(m_pGeoTimeSliceEnd.get());
	m_pCubeGeode->setUserValue("objID", m_pSubVolume->GetObjectID().toString().toStdString());
	return m_pCubeGeode.get();
}

osg::ref_ptr<osg::Switch>  CX3DSubCubeBuilder::_BuildSubCube(CXSeismicSubVolume *pSubVolume)
{
	int inlineStart;
	int inlineEnd;
	int xlineStart;
	int xlineEnd;
	double timeStart;
	double timeEnd;
	pSubVolume->GetDataRange(inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd);
	if (timeStart == -999.)
		return NULL;

	osg::ref_ptr<osg::Switch> dragerRoot = new osg::Switch;
	osg::ref_ptr<osg::MatrixTransform> matrixTransform = new osg::MatrixTransform;

	matrixTransform->addChild(_BuildSubVolume(inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd));

	osg::ref_ptr<osgManipulator::TabBoxDragger> boxDrager = new osgManipulator::TabBoxDragger;
	osg::StateSet *pStatSet = boxDrager->getOrCreateStateSet();
	pStatSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
	boxDrager->setupDefaultGeometry();
	boxDrager->setPlaneColor(osg::Vec4(0.0, 1.0, 1.0, 1.0));
	boxDrager->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3), osg::StateAttribute::PROTECTED);
	boxDrager->setName("BoxDrager");

	CXSubvolumeDragerCallBack *pSubVolumDragerCallBack = new CXSubvolumeDragerCallBack(matrixTransform);
	m_DragerCube = _BuildDragerCube(pSubVolume->GetDefaultDataVolume(), inlineStart, inlineEnd, xlineStart, xlineEnd, timeStart, timeEnd);
	pSubVolumDragerCallBack->SetDragerCube(m_DragerCube, this, boxDrager);

	boxDrager->setMatrix(_InitDrager(m_DragerCube));
	boxDrager->addDraggerCallback(pSubVolumDragerCallBack);
	boxDrager->setHandleEvents(true);
	boxDrager->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_LEFT_CTRL);

	dragerRoot->addChild(matrixTransform);
	dragerRoot->addChild(boxDrager, false);


	CXSeismicDataVolume* dv = _GetDV();
	if (!dv)
		return nullptr;

	CXSeismicUTMTool& utmTool = dv->GetUTM();
	int firstInline = utmTool.GetFirstInline();
	int lastInline = utmTool.GetLastInline();
	int firstCrossline = utmTool.GetFirstCrossline();
	int lastCrossline = utmTool.GetLastCrossline();
	double sampleStart, sampleEnd, sampleInterval;
	dv->GetSamplingRange(sampleStart, sampleEnd, sampleInterval);
	m_pChairGeode = new osg::Geode;
	m_pGeoInlineSectionChairStart = _BuildSectionGeom(firstInline, firstInline, lastInline, firstCrossline, lastCrossline, sampleStart, sampleEnd, eInlineSection);
	m_pGeoInlineSectionChairEnd = _BuildSectionGeom(lastInline, firstInline, lastInline, firstCrossline, lastCrossline, sampleStart, sampleEnd, eInlineSection);
	m_pGeoXlineSectionChairStart = _BuildSectionGeom(firstCrossline, firstInline, lastInline, firstCrossline, lastCrossline, sampleStart, sampleEnd, eCrosslineSection);
	m_pGeoXlineSectionChairEnd = _BuildSectionGeom(lastCrossline, firstInline, lastInline, firstCrossline, lastCrossline, sampleStart, sampleEnd, eCrosslineSection);
	m_pGeoTimeSliceChairStart = _BuildSectionGeom(sampleStart, firstInline, lastInline, firstCrossline, lastCrossline, sampleStart, sampleEnd, eTimeSlice);
	m_pGeoTimeSliceChairEnd = _BuildSectionGeom(sampleEnd, firstInline, lastInline, firstCrossline, lastCrossline, sampleStart, sampleEnd, eTimeSlice);


	m_pChairGeode->addDrawable(m_pGeoInlineSectionChairStart.get());
	m_pChairGeode->addDrawable(m_pGeoInlineSectionChairEnd.get());
	m_pChairGeode->addDrawable(m_pGeoXlineSectionChairStart.get());
	m_pChairGeode->addDrawable(m_pGeoXlineSectionChairEnd.get());
	m_pChairGeode->addDrawable(m_pGeoTimeSliceChairStart.get());
	m_pChairGeode->addDrawable(m_pGeoTimeSliceChairEnd.get());
	m_pChairGeode->setName("ChairCube");

	dragerRoot->addChild(m_pChairGeode, false);
	return dragerRoot.get();
}

osg::Matrixd CX3DSubCubeBuilder::_InitDrager(std::vector<osg::Vec3> dragerVertex)
{
	int numVertex = dragerVertex.size();
	osg::Vec3d vecXline = dragerVertex[2] - dragerVertex[0];
	osg::Vec3d vecInline = dragerVertex[6] - dragerVertex[0];
	osg::Vec3d vecSample = dragerVertex[1] - dragerVertex[0];
	double scaleX = vecInline.length();
	double scaleY = vecXline.length();
	double scaleZ = vecSample.length();
	vecXline.normalize(); vecInline.normalize(); vecSample.normalize();
	osg::Vec3d centerTrans = dragerVertex[0] + vecInline*(scaleX / 2) + vecXline*(scaleY / 2) + vecSample*(scaleZ / 2);

	CXSeismicUTMTool& utmTool = m_pSubVolume->GetDefaultDataVolume()->GetUTM();
	double iDir = utmTool.GetIDirection();

	osg::Matrixd rotateMat;
	rotateMat.makeRotate(osg::DegreesToRadians(iDir), osg::Vec3d(0, 0, 1.0));
	double minX, maxX, minY, maxY;
	double timeStart, timeEnd;

	osg::Matrixd transMat;
	transMat.makeTranslate(centerTrans);

	osg::Matrixd scaleMat;
	scaleMat.makeScale(Vec3d(scaleX + 0.2, scaleY + 0.2, scaleZ + 0.2));
	return	scaleMat*rotateMat*transMat;
}

CXSeismicDataVolume* CX3DSubCubeBuilder::_GetDV()
{
	auto pDv = dynamic_cast<CXSeismicDataVolume*>(::GetAttributeFromGeometry(m_pSubVolume, m_pCurWin));
	if (pDv)
		return pDv;
	
	pDv = m_pSubVolume->GetDefaultDataVolume();
	if (pDv)
		return pDv;
	else
		return nullptr;
}

osg::ref_ptr<osg::Geometry> CX3DSubCubeBuilder::_BuildSectionGeom(double currentSection, int inLineStart, int inLineEnd, int xLineStart, int xLineEnd, double timeStart, double timeEnd, EXSectionType curSecType)
{
	CXSeismicDataVolume* dv = _GetDV();
	if (!dv)
		return nullptr;

	CXSeismicUTMTool& utmTool = dv->GetUTM();
	Vec3d vecWorld;
	osg::Vec3f vecLocal;
	double xValue = 0.0f;
	double yValue = 0.0f;
	osg::ref_ptr<osg::Vec3Array> PolyVertex = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> NormalArray = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec2Array> PolyTexCorrd = new osg::Vec2Array;
	if (curSecType == eInlineSection)
	{
		utmTool.LineToXY((int)currentSection, xLineStart, xValue, yValue);
		// 1
		vecWorld.set(xValue, yValue, timeStart);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(0, 0));
		// 2
		vecWorld.set(xValue, yValue, timeEnd);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(0, 1));

		utmTool.LineToXY((int)currentSection, xLineEnd, xValue, yValue);
		// 3
		vecWorld.set(xValue, yValue, timeEnd);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(1, 1));
		// 4
		vecWorld.set(xValue, yValue, timeStart);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(1, 0));
	}
	else if (curSecType == eCrosslineSection)
	{
		utmTool.LineToXY(inLineStart, (int)currentSection, xValue, yValue);

		// 1
		vecWorld.set(xValue, yValue, timeStart);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(0, 0));

		// 2
		vecWorld.set(xValue, yValue, timeEnd);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(0, 1));

		utmTool.LineToXY(inLineEnd, (int)currentSection, xValue, yValue);

		// 3
		vecWorld.set(xValue, yValue, timeEnd);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(1, 1));

		// 4
		vecWorld.set(xValue, yValue, timeStart);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(1, 0));

	}
	else
	{
		// 1
		utmTool.LineToXY(inLineStart, xLineStart, xValue, yValue);
		vecWorld.set(xValue, yValue, currentSection);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(0, 0));

		// 2
		utmTool.LineToXY(inLineStart, xLineEnd, xValue, yValue);
		vecWorld.set(xValue, yValue, currentSection);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(0, 1));

		// 3
		utmTool.LineToXY(inLineEnd, xLineEnd, xValue, yValue);
		vecWorld.set(xValue, yValue, currentSection);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(1, 1));

		// 4
		utmTool.LineToXY(inLineEnd, xLineStart, xValue, yValue);
		vecWorld.set(xValue, yValue, currentSection);
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		PolyVertex->push_back(vecLocal);
		PolyTexCorrd->push_back(osg::Vec2(1, 0));
	}


	osg::Vec3f vec1 = (*PolyVertex)[0] - (*PolyVertex)[1];
	osg::Vec3f vec2 = (*PolyVertex)[1] - (*PolyVertex)[2];
	osg::Vec3f sectionNormal = vec1^vec2;
	sectionNormal.normalize();
	NormalArray->push_back(sectionNormal);

	osg::ref_ptr<osg::Geometry> geomSection = new osg::Geometry();

	geomSection->setVertexArray(PolyVertex.get());
	geomSection->setNormalArray(NormalArray.get());
	geomSection->setNormalBinding(osg::Geometry::BIND_OVERALL);
	geomSection->setTexCoordArray(0, PolyTexCorrd.get());
	geomSection->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, PolyVertex.get()->size()));
	//generate texture
	osg::ref_ptr<osg::StateSet> pSectionStatSet = new osg::StateSet;
	pSectionStatSet = _GenerateTextureState(currentSection, inLineStart, inLineEnd, xLineStart, xLineEnd, timeStart, timeEnd, curSecType);
	if (pSectionStatSet != NULL)
	{
		osg::PolygonMode *pm = new osg::PolygonMode;
		pm->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
		pSectionStatSet->setAttribute(pm, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
		geomSection->setStateSet(pSectionStatSet);
	}
	geomSection->setName("Section");

	return geomSection.get();
}

osg::ref_ptr<osg::StateSet> CX3DSubCubeBuilder::_GenerateTextureState(int currentSection, int inLineStart, int inLineEnd, int xLineStart, int xLineEnd, double timeStart, double timeEnd, EXSectionType curSecType, bool ifChairMode)
{
	CXSeismicDataVolume* dv = _GetDV();
	if (!dv)
		return nullptr;

	CXSeismicUTMTool& utmTool = dv->GetUTM();
	int firstInline = utmTool.GetFirstInline();
	int lastInline = utmTool.GetLastInline();
	int firstCrossline = utmTool.GetFirstCrossline();
	int lastCrossline = utmTool.GetLastCrossline();

	CXViewInfoObject *pViewInfo = m_pCurWin->GetObjectViewInfo(dv->GetObjectID());
	double dMin = pViewInfo->GetDisplayDataMin();
	double dMax = pViewInfo->GetDisplayDataMax();

	double sampleStart, sampleEnd, sampleInterval;
	dv->GetSamplingRange(sampleStart, sampleEnd, sampleInterval);
	int traceNum, sampleNum;
	float texCoordXS, texCoordXE;
	float texCoordYS, texCoordYE;
	float *pSectionData = NULL;
	bool success = true;
	if (curSecType == eInlineSection)
	{
		if (!ifChairMode)
		{
			traceNum = abs(xLineEnd - xLineStart) / utmTool.GetCrosslineIncrement() + 1;
			int iSampleStart = static_cast<int>((qAbs(timeStart - sampleStart) + 0.01*sampleInterval) / sampleInterval);
			int iSampleEnd = static_cast<int>((qAbs(timeEnd - sampleStart) + 0.01*sampleInterval) / sampleInterval);
			sampleNum = iSampleEnd - iSampleStart + 1;
			pSectionData = new float[traceNum*sampleNum];
			success = dv->ReadInline(currentSection, xLineStart, xLineEnd, timeStart, timeEnd, pSectionData);
			texCoordXS = 0;
			texCoordXE = 1;
			texCoordYS = 0;
			texCoordYE = 1;
		}
		else{
			traceNum = abs(lastCrossline - firstCrossline) / utmTool.GetCrosslineIncrement() + 1;
			int iSampleStart = static_cast<int>((qAbs(sampleStart - sampleStart) + 0.01*sampleInterval) / sampleInterval);
			int iSampleEnd = static_cast<int>((qAbs(sampleEnd - sampleStart) + 0.01*sampleInterval) / sampleInterval);
			sampleNum = iSampleEnd - iSampleStart + 1;
			pSectionData = new float[traceNum*sampleNum];
			success = dv->ReadInline(currentSection, firstCrossline, lastCrossline, sampleStart, sampleEnd, pSectionData);
			texCoordXS = float(xLineStart - firstCrossline) / (lastCrossline - firstCrossline);
			texCoordXE = float(xLineEnd - firstCrossline) / (lastCrossline - firstCrossline);
			texCoordYS = float(timeStart - sampleStart) / (sampleEnd - sampleStart);
			texCoordYE = float(timeEnd - sampleStart) / (sampleEnd - sampleStart);
		}
		/*	pSectionData=new float[traceNum*sampleNum];
		success=dv->ReadInline(currentSection,xLineStart,xLineEnd,timeStart,timeEnd,pSectionData);*/
	}
	else if (curSecType == eCrosslineSection)
	{
		if (!ifChairMode)
		{
			traceNum = abs(inLineEnd - inLineStart) / utmTool.GetInlineIncrement() + 1;
			int iSampleStart = static_cast<int>((qAbs(timeStart - sampleStart) + 0.01*sampleInterval) / sampleInterval);
			int iSampleEnd = static_cast<int>((qAbs(timeEnd - sampleStart) + 0.01*sampleInterval) / sampleInterval);
			sampleNum = iSampleEnd - iSampleStart + 1;
			pSectionData = new float[traceNum*sampleNum];
			success = dv->ReadXline(currentSection, inLineStart, inLineEnd, timeStart, timeEnd, pSectionData);
			texCoordXS = 0;
			texCoordXE = 1;
			texCoordYS = 0;
			texCoordYE = 1;
		}
		else
		{
			traceNum = abs(lastInline - firstInline) / utmTool.GetInlineIncrement() + 1;
			int iSampleStart = static_cast<int>((qAbs(sampleStart - sampleStart) + 0.01*sampleInterval) / sampleInterval);
			int iSampleEnd = static_cast<int>((qAbs(sampleEnd - sampleStart) + 0.01*sampleInterval) / sampleInterval);
			sampleNum = iSampleEnd - iSampleStart + 1;
			pSectionData = new float[traceNum*sampleNum];
			success = dv->ReadXline(currentSection, firstInline, lastInline, sampleStart, sampleEnd, pSectionData);
			texCoordXS = float(inLineStart - firstInline) / (lastInline - firstInline);
			texCoordXE = float(inLineEnd - firstInline) / (lastInline - firstInline);
			texCoordYS = float(timeStart - sampleStart) / (sampleEnd - sampleStart);
			texCoordYE = float(timeEnd - sampleStart) / (sampleEnd - sampleStart);
		}
	}
	else
	{
		if (!ifChairMode)
		{
			sampleNum = abs(xLineEnd - xLineStart) / utmTool.GetCrosslineIncrement() + 1;
			traceNum = abs(inLineEnd - inLineStart) / utmTool.GetInlineIncrement() + 1;
			pSectionData = new float[traceNum*sampleNum];
			success = dv->ReadSlice(currentSection, inLineStart, inLineEnd, xLineStart, xLineEnd, pSectionData);
			texCoordXS = 0;
			texCoordXE = 1;
			texCoordYS = 0;
			texCoordYE = 1;
		}
		else
		{
			sampleNum = abs(lastCrossline - firstCrossline) / utmTool.GetCrosslineIncrement() + 1;
			traceNum = abs(lastInline - firstInline) / utmTool.GetInlineIncrement() + 1;
			pSectionData = new float[traceNum*sampleNum];
			success = dv->ReadSlice(currentSection, firstInline, lastInline, firstCrossline, lastCrossline, pSectionData);
			texCoordYS = float(xLineStart - firstCrossline) / (lastCrossline - firstCrossline);
			texCoordYE = float(xLineEnd - firstCrossline) / (lastCrossline - firstCrossline);
			texCoordXS = float(inLineStart - firstInline) / (lastInline - firstInline);
			texCoordXE = float(inLineEnd - firstInline) / (lastInline - firstInline);
		}
	}
	if (!success)
	{
		return NULL;
	}

	CXColormap *pColormap = CXColormap::GetColormap(pViewInfo->GetColormapName());
	if (pColormap == NULL)
		return nullptr;

	auto pImageData = new unsigned int[traceNum * sampleNum];

	for (auto i = 0; i < traceNum; ++i)
	{
		for (auto j = 0; j < sampleNum; ++j)
		{
			double dCurrValue = static_cast<double>(pSectionData[i * sampleNum + j]);
			int index;
			if (qFuzzyCompare(dMin, dMax))
			{
				index = 0;
			}
			else if (qFuzzyCompare(dCurrValue, ::g_dInvalidData) || (pViewInfo->GetBZeroIsInvalid() && dCurrValue == 0.0))
			{
				pImageData[j * traceNum + i] = pColormap->GetInvalidColor().rgba();
				continue;
			}
			else
			{
				index = static_cast<int>((dCurrValue - dMin) / (dMax - dMin) * pColormap->GetColorNum());
				index = qBound(0, index, pColormap->GetColorNum());
			}

			pImageData[j * traceNum + i] = QColor(index, index, index).rgba();
		}
	}

	osg::ref_ptr<osg::Image> texImage = new osg::Image;
	texImage->setImage(traceNum, sampleNum, 1, GL_RGBA32F_ARB, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)pImageData, osg::Image::NO_DELETE);
	/*texImage->allocateImage(traceNum, sampleNum, 1, GL_RGBA, GL_FLOAT);
	texImage->setInternalTextureFormat(GL_RGBA32F_ARB);
	float *texData = (float*)(texImage->data());*/
	//_GenerateTexture(pSectionData, fMin, fMax, traceNum, sampleNum, texData);
	//osgDB::writeImageFile(*texImage, "subcube.png");

	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D(texImage);
	tex->setUnRefImageDataAfterApply(true);
	tex->setResizeNonPowerOfTwoHint(false);
	tex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	tex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	tex->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	tex->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

	osg::ref_ptr<osg::StateSet> st = new osg::StateSet;
	st->setTextureAttributeAndModes(0, tex, osg::StateAttribute::ON);
	st->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::ref_ptr<osg::BlendFunci> blend0 = new osg::BlendFunci(0, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	st->setAttributeAndModes(blend0.get());

	osg::Uniform *ColorMap = new osg::Uniform(osg::Uniform::FLOAT_VEC4, "colorTable", 256);
	for (int i = 0; i < 256; i++)
	{
		QColor color = (i == 255) ? pColormap->GetInvalidColor() : pColormap->GetColorAt(i);
		ColorMap->setElement(i, osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}
	
	osg::Program* program = new osg::Program;

	std::string strVertex = QString(CXDBIO::GetShaderFilePath() + "section.vert").toStdString();
	std::string strFrag = QString(CXDBIO::GetShaderFilePath() + "section.frag").toStdString();

	program->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, strVertex));
	program->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, strFrag));

	st->setAttribute(program, osg::StateAttribute::ON);
	st->addUniform(new osg::Uniform("sectionTex", 0));
	st->addUniform(ColorMap);
	st->addUniform(new osg::Uniform("coordXS", texCoordXS));
	st->addUniform(new osg::Uniform("coordXE", texCoordXE));
	st->addUniform(new osg::Uniform("coordYS", texCoordYS));
	st->addUniform(new osg::Uniform("coordYE", texCoordYE));
	st->addUniform(new osg::Uniform("ifChairMode", ifChairMode));

	if (pSectionData)
	{
		delete[] pSectionData;
		pSectionData = NULL;
	}

	return st.get();
}

void CX3DSubCubeBuilder::_GenerateTexture(float *sectionData, float dataMin, float dataMax, int traceNum, int sampleNum, float *texData)
{
	float fDataRange = dataMax - dataMin;
	for (int j = 0; j < traceNum; j++)
	{
		for (int i = 0; i < sampleNum; i++)
		{
			float fAttr = sectionData[j*sampleNum + i];
			float fAttrInterpolate = (fAttr - dataMin) / fDataRange;
			texData[i*traceNum + j] = fAttrInterpolate;
		}
	}
}

std::vector<osg::Vec3> CX3DSubCubeBuilder::_BuildDragerCube(CXSeismicDataVolume *dv, int firstInLine, int lastInLine, int firstCrossLine, int lastCrossLine, double sampleStart, double sampleEnd)
{
	osg::ref_ptr<osg::Geometry> geomDv = new osg::Geometry();
	double xValue = 0.0f;
	double yValue = 0.0f;
	Vec3d vecWorld;
	osg::Vec3f vecLocal;
	CXSeismicUTMTool& utmTool = dv->GetUTM();
	std::vector<osg::Vec3> allDragerVertex;
	// 1
	utmTool.LineToXY(firstInLine, firstCrossLine, xValue, yValue);
	vecWorld.set(xValue, yValue, sampleStart);
	m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
	allDragerVertex.push_back(vecLocal);

	vecWorld.set(xValue, yValue, sampleEnd);
	m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
	allDragerVertex.push_back(vecLocal);

	// 2
	utmTool.LineToXY(firstInLine, lastCrossLine, xValue, yValue);
	vecWorld.set(xValue, yValue, sampleStart);
	m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
	allDragerVertex.push_back(vecLocal);

	vecWorld.set(xValue, yValue, sampleEnd);
	m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
	allDragerVertex.push_back(vecLocal);

	// 3
	utmTool.LineToXY(lastInLine, lastCrossLine, xValue, yValue);
	vecWorld.set(xValue, yValue, sampleStart);
	m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
	allDragerVertex.push_back(vecLocal);

	vecWorld.set(xValue, yValue, sampleEnd);
	m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
	allDragerVertex.push_back(vecLocal);

	// 4
	utmTool.LineToXY(lastInLine, firstCrossLine, xValue, yValue);
	vecWorld.set(xValue, yValue, sampleStart);
	m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
	allDragerVertex.push_back(vecLocal);

	vecWorld.set(xValue, yValue, sampleEnd);
	m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
	allDragerVertex.push_back(vecLocal);

	return allDragerVertex;
}