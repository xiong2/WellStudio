#include "xdlgproperty.h"
#include "xglobal.h"
#include "xbaseconsole.h"
#include "xpagegeneral.h"
#include "xpagehistogram.h"
#include "xwellvisualizationpage.h"
#include "xpage3dwellcurvevis.h"
#include "xpagesectionwellcurvevis.h"
#include "xviewinfowellcurve.h"
#include "xpagewelltopformation.h"
#include "xfaultsticksvispage.h"
#include "xobject.h"
#include "xpageformationvisonsec.h"
#include "xeventconsole.h"
#include "xfaultsticksvissec.h"
#include "xpagecolormap.h"
#include "xpagesurfacevis.h"
#include "xpagegridmodelvis.h"
#include "xseismicsection.h"
#include "xpagetimeslicevis.h"
#include "xwellconditionvispage.h"
#include "x2dseismiclinevispage.h"
#include "xviewinfomanager.h"
#include "xpagelfmgeometryvis.h"
#include "xpagewellvis.h"
#include "xpagesectionsurfacevis.h"
#include "xpagesection3dhorizonvis.h"
#include "xparametermanager.h"
#include "xbaseparameter.h"
#include "xprocessfactory.h"
#include "xpagebm3dsurvey.h"
#include "xpagesectionseismicsection.h"
#include "xpageseismicdatavolumevis.h"
#include "xpagebm2dpolygon.h"
#include "xpagetimeslicevis.h"
#include "xviewinfoseismicdv.h"
#include "xwindow.h"
#include "xpageprestackgathervis.h"
#include "xpage3dpoints.h"

#include "gsbm3dhorizonvispage.h"
#include "gsbmrosediagramvispage.h"
#include "gsbmstressmapvispage.h"
#include "gsbmsectionvispage.h"
#include "gssecsectionvispage.h"
#include "xpagediagram.h"

CXDlgProperty::CXDlgProperty(QWidget *parent,CXObject *pObject, CXWindow* pWindow)
	: QDialog(parent), m_pObj(pObject), m_pWin(pWindow)
{
	m_ui.setupUi(this);
	Q_ASSERT(m_pObj);

	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Properties for ["+m_pObj->GetObjectName()+"]");	

	// Save to all button
	m_ui.m_pPushBtnApply2All->setIcon(QIcon(::GetIconPath()+"Apply2All.png"));
	m_ui.m_pPushBtnApply2All->setToolTip("Apply to all of the same type in current window");
	m_ui.m_pPushBtnApply2All->setVisible(false);

	// connection
	connect(m_ui.m_pPushBtnApply2All,SIGNAL(clicked() ),this,SLOT(slotApply2All()));
	connect(m_ui.m_TabWidget,SIGNAL(currentChanged(int)),this,SLOT(slotTabChanged(int)));
	connect(m_ui.m_pDlgButtonBox,SIGNAL(clicked(QAbstractButton*)),this, SLOT(slotButtonClicked(QAbstractButton*)));

	_AddGeneralPage();
	_AddVisPage();
	_AddHistogram();
	_AddColormap();
	_AddCalcParaPage();
	_AddDiagramPage();
}

CXDlgProperty::~CXDlgProperty(void)
{
	CXPropertyDialogFactory::Instance().ClosePropertyDialog(m_pObj);
}

void CXDlgProperty::slotApply()
{

}


void CXDlgProperty::ShowColormapPage()
{
    if (m_pColormapPage)
    {
        m_ui.m_TabWidget->setCurrentWidget(m_pColormapPage);
    }
}

void CXDlgProperty::UpdateView(const CXEventParameter& eventPara)
{
	if (EDataChanged == eventPara.m_eEventType)
	{
		setWindowTitle("Properties for [" + m_pObj->GetObjectName() + "]");
	}
}

void CXDlgProperty::_AddCalcParaPage()
{
	if (!m_pObj)
		return;

	CXBaseParameter* pPara = CXParameterManager::Instance().GetParameterByID(m_pObj->GetObjectID());
	if (!pPara)
		return;

	QWidget* pWidget = CXProcessFactory::Instance().CreateProcessWidget(pPara->GetObjectType(), pPara, m_pObj);
	if (!pWidget)
		return;

	m_ui.m_TabWidget->addTab(pWidget, "Calculation Parameters");
}

void CXDlgProperty::_AddGeneralPage()
{
	m_pGeneral = new CXPageGeneral(this, m_pObj);
	m_ui.m_TabWidget->addTab(m_pGeneral, "General");
}

void CXDlgProperty::_AddVisPage()
{
	if (!m_pWin)
		return;

	CXViewInfoObject* pViewInfo = m_pWin->GetObjectViewInfo(m_pObj->GetObjectID());
	if (!pViewInfo) 
		return;

	EXWindowType eWinType = m_pWin->GetWindowType();
	switch (m_pObj->GetObjectType())
	{
	case EXWell:
		if (eWinType == e3DWindow || eWinType == e3DBaseMap)
		{
			m_pVisPage = new CXPageWellVis3D(this, pViewInfo);
		}
		else if (eWinType == eSectionWindow || eWinType == eSectionWindowBlank)
		{
			m_pVisPage = new CXPageWellVis(this, pViewInfo);
		}
		break;
	case EXWellCurve:
		if (eWinType == e3DWindow)
		{
			m_pVisPage = new CXPage3DWellCurveVis(this, pViewInfo);
		}
		else if(eWinType == eSectionWindow || eWinType == eSectionWindowBlank)
		{
			m_pVisPage = new CXPageSectionWellCurveVis(this, pViewInfo);
		}
		break;
	case EXWellTopFormation:
		if (eWinType == eSectionWindow || eWinType == eSectionWindowBlank)
		{
			m_pVisPage = new CXPageFormationVisOnSec(this, pViewInfo);
		}
		else if (eWinType == e3DWindow)
		{
			m_pVisPage = new CXPageWellTopFormation(this, pViewInfo);
		}
		break;
	case EXFaultSticks:
	case EXGMFault:
		if (eWinType == eSectionWindow || eWinType == eSectionWindowBlank)
		{
			m_pVisPage = new CXFaultSticksVisSec(this, pViewInfo);
		}
		else if (eWinType == e3DWindow)
		{
			m_pVisPage = new CXFaultSticksVisPage(this, pViewInfo);
		}
		break;
	case EXFracturePatch:
		if (eWinType == e3DWindow)
		{
			m_pVisPage = new CXFaultSticksVisPage(this, pViewInfo);
		}
		break;
	case EX3DSurface:
		if (eWinType == e3DWindow || eWinType == e3DBaseMap)
		{
			m_pVisPage = new CXPageSurfaceVis(this, pViewInfo, m_pObj, eWinType);
		}
		else if (eWinType == eSectionWindow || eWinType == eSectionWindowBlank)
		{
			m_pVisPage = new CXPageSectionSurfaceVis(this, pViewInfo);
		}
		break;
	case EX3DHorizon:
		if (eWinType == e3DWindow || eWinType == e3DBaseMap)
		{
			m_pVisPage = new CXPageSurfaceVis(this, pViewInfo, m_pObj, eWinType);
		}
		if (eWinType == eSectionWindow || eWinType == eSectionWindowBlank)
		{
			m_pVisPage = new CXPageSection3DHorizonVis(this, pViewInfo);
		}
		break;
	case EXGS3DHorizonTWT:
	case EXGS3DHorizonDepth:
	case EXGS3DHorizonIso:
	case EXGS3DHorizonAtt:
		if (eWinType == eGSBaseMap)
		{
			m_pVisPage = new GSBM3DHorizonVisPage(pViewInfo);
		}
		break;
	case EXGSSection:
		if (eWinType == eGSBaseMap)
		{
			m_pVisPage = new GSBMSectionVisPage(pViewInfo);
		}
		if (eWinType == eGSSectionWindow)
		{
			m_pVisPage = new GSSecSectionVisPage(pViewInfo);
		}
		break;
	case EXGSStressMap:
		if (eWinType == eGSBaseMap)
		{
			m_pVisPage = new GSBMStressMapVisPage(pViewInfo);
		}
		break;
	case EXGSRoseDiagram:
		if (eWinType == eGSBaseMap)
		{
			m_pVisPage = new GSBMRoseDiagramVisPage(pViewInfo);
		}
		break;
	case EXGridModel:
	case EXIntersectionGrid:
		if (eWinType == e3DWindow)
		{
			m_pVisPage = new CXPageGridModelVis(this, pViewInfo);
		}
		break;
	case EXWellCondition:
		if (eWinType == e3DWindow)
		{
			m_pVisPage = new CXWellConditionVisPage(this, pViewInfo);
		}
		break;
	case EXSeismicSection:
		if (eWinType == eSectionWindow || eWinType == eSectionWindowBlank)
		{
			CXSeismicSection* pSection = dynamic_cast<CXSeismicSection*>(m_pObj);
			if (!pSection)
				break;

			EXSectionType type = pSection->GetSectionType();

			if (eInlineSection == type || eCrosslineSection == type)
			{
				m_pVisPage = new CXPageSectionSeismicSection(this, m_pObj);
			}
			else if (eTimeSlice == type)
			{
				m_pVisPage = new CXPageTimeSliceVis(this, pViewInfo, m_pObj, eWinType);
			}
		}
		break;
	case EXSeismicDataVolume:
		if (eWinType == e3DWindow || eWinType == e3DBaseMap)
		{
			m_pVisPage = new CXPageSeismicDataVolumeVis(this, pViewInfo);
		}
		break;
	case EX2DSeismicLine:
		{
			if (eWinType == e3DBaseMap)
			{
				m_pVisPage = new CX2DSeismicLineVisPage(this, pViewInfo);
			}
		}
		break;
    case EXLowFrequencyModel:
    {
        if (e3DWindow == eWinType || eSectionWindow == eWinType || eWinType == eSectionWindowBlank)
        {
            m_pVisPage = new CXPageLFMGeometryVis(this, pViewInfo, m_pObj, eWinType);
        }
		break;
    }
	case EX3DSurvey:
	{
		if (eWinType == e3DBaseMap)
		{
			m_pVisPage = new CXPageBM3DSurvey(this, pViewInfo);
		}
		break;
	}
	case EX2DPolygon:
	{
		if (eWinType == e3DBaseMap)
		{
			m_pVisPage = new CXPageBM2DPolygon(this, pViewInfo);
		}
		break;
	}
	case EXPrestackGather:
	{
		if (eWinType == e3DBaseMap)
		{
			m_pVisPage = new CXPagePreStackGatherVis(pViewInfo, m_pObj, this);
		}
		break;
	}
	case EX3DPoints:
	{
		if (eWinType == e3DBaseMap || eWinType == e3DWindow)
		{
			m_pVisPage = new CXPage3DPoints(pViewInfo, this);
		}
		break;
	}
	default:
		break;
	}

	if (m_pVisPage)
	{
		auto pGeneral = dynamic_cast<CXPageGeneral*>(m_ui.m_TabWidget->widget(0));
		m_pVisPage->SetObjectColorBuddyButton(pGeneral->GetObjColorButton());

		m_ui.m_TabWidget->addTab(m_pVisPage, "Visualization");
	}
}

void CXDlgProperty::_AddHistogram()
{
	CXBaseConsole* pCurConsol = reinterpret_cast<CXBaseConsole *>(::GetConsole());
	CXViewInfoObject* pViewInfo = pCurConsol->GetViewInfoForActiveWindow(m_pObj->GetObjectID());
	auto pViewInfoDV = dynamic_cast<CXViewInfoSeismicDV*>(pViewInfo);

	if(m_pObj->HasHistogram())
	{	
		if (_IsSeismicFoldMap(pViewInfoDV))
		{
			CXPageHistogram *pHisgram = new CXPageHistogram(this, pViewInfoDV->GetFoldHistogram());
			m_ui.m_TabWidget->addTab(pHisgram, "Fold Map Histogram");
		}
		else
		{
			CXPageHistogram *pHisgram = new CXPageHistogram(this, m_pObj->GetHistogram());
			m_ui.m_TabWidget->addTab(pHisgram, "Histogram");
		}
	}
}

void CXDlgProperty::_AddDiagramPage()
{
	//	So far only wavelet need diagram page.
	if (m_pObj->GetObjectType() != EXWavelet)
		return;

	CXPageDiagram *pDPage = new CXPageDiagram(m_pObj, this);
	m_ui.m_TabWidget->addTab(pDPage, "Diagram");
}

void CXDlgProperty::_AddColormap()
{
	if (!m_pWin)
		return;

	CXViewInfoObject* pViewInfo = m_pWin->GetObjectViewInfo(m_pObj->GetObjectID());
	if (!pViewInfo)
		return;

	if ((m_pObj->GetObjectType() == EX3DSurface || m_pObj->GetObjectType() == EX3DHorizon
		|| m_pObj->GetObjectType() == EXGS3DHorizonTWT || m_pObj->GetObjectType() == EXGS3DHorizonDepth
		|| m_pObj->GetObjectType() == EXGS3DHorizonIso || m_pObj->GetObjectType() == EXGS3DHorizonAtt)
		&& pViewInfo->GetAttributeObjID() != m_pObj->GetObjectID())
		return;

	auto pViewInfoDV = dynamic_cast<CXViewInfoSeismicDV*>(pViewInfo);

	if (m_pObj->HasHistogram() && pViewInfo->GetNeedColormap())
	{
		if (_IsSeismicFoldMap(pViewInfoDV))
		{
			m_pColormapPage = new CXPageColormap(this, m_pObj, pViewInfoDV->GetFoldHistogram());
			m_ui.m_TabWidget->addTab(m_pColormapPage, "Fold Map Colormap");
		}
		else
		{
			m_pColormapPage = new CXPageColormap(this, m_pObj);
			m_ui.m_TabWidget->addTab(m_pColormapPage, "Colormap");
		}
	}
}

void CXDlgProperty::slotTabChanged(int index)
{
	if (index == -1 || (m_pVisPage == NULL && m_pColormapPage == NULL) )
		return;

	int iVisPageIndex = m_ui.m_TabWidget->indexOf(m_pVisPage);
	int iColPageIndex = m_ui.m_TabWidget->indexOf(m_pColormapPage);
	if (index == iVisPageIndex || index == iColPageIndex)
	{
		m_ui.m_pPushBtnApply2All->setVisible(true);
	}
	else
	{
		m_ui.m_pPushBtnApply2All->setVisible(false);
	}
}

void CXDlgProperty::slotApply2All()
{
	// Get the first-level parent object
	CXObject* pCurrentObj = m_pObj->GetParent();
	CXObject* pParentObj = nullptr;
	while(pCurrentObj)
	{
		pParentObj = pCurrentObj->GetParent();
		if (pParentObj && (pParentObj->GetObjectType() == EXProject))
		{
			pParentObj = pCurrentObj;
			break;
		}
		pCurrentObj = pParentObj;
	}
	Q_ASSERT(pParentObj);

	// Get all children with the same type	
	QList<CXObject*> listChild = pParentObj->GetChildren(m_pObj->GetObjectType(), true);
	listChild.removeAll(m_pObj);
	if (listChild.empty())
		return;

	// Get current view info
	CXBaseConsole *pCurConsol = reinterpret_cast<CXBaseConsole *>(::GetConsole());
	CXViewInfoObject* pCurrentViewInfo = pCurConsol->GetViewInfoForActiveWindow(m_pObj->GetObjectID());
	if (!pCurrentViewInfo)
		return;

	// Apply to others
	CXProcessEvent eventProcess;
	for (int i=0; i<listChild.size(); ++i)
	{
		CXViewInfoObject* pViewInfo = pCurConsol->GetViewInfoForActiveWindow(listChild.at(i)->GetObjectID());
		if (!pViewInfo)
			continue;

		if (pViewInfo->ApplyToCurrentViewInfo(pCurrentViewInfo))
			listChild.at(i)->AddEvent(EInfoChanged);
	}
}

void CXDlgProperty::accept()
{
	QDialog::accept();

	_Update();	
}

void CXDlgProperty::slotButtonClicked(QAbstractButton* pButton)
{
	if (m_ui.m_pDlgButtonBox->standardButton(pButton) == QDialogButtonBox::Apply)
	{
		_Update();
	}
}

bool CXDlgProperty::_IsSeismicFoldMap(CXViewInfoSeismicDV* pViewInfoDV)
{
	CXBaseConsole* pCurConsol = reinterpret_cast<CXBaseConsole *>(::GetConsole());

	if (m_pObj->GetObjectType() != EXSeismicDataVolume || pCurConsol->GetActiveWinowType() != e3DBaseMap)
		return false;

	CXObject* pObjSurvey = m_pObj->GetAncient(EX3DSurvey);
	if (!pObjSurvey)
		return false;

	// If timeslice displayed on base map, we should base on the seismic data.
	QList<CXObject*> listSection = pObjSurvey->GetChildren(EXSeismicSection, true);
	for (CXObject* pObjSection : listSection)
	{
		auto pSection = dynamic_cast<CXSeismicSection*>(pObjSection);
		if (pSection->GetSectionType() != eTimeSlice)
			continue;

		CXViewInfoObject* pViewInfoSection = pCurConsol->GetViewInfoForActiveWindow(pSection->GetObjectID());
		if (pViewInfoSection && pViewInfoSection->GetVisible())
			return false;
	}

	if (!pViewInfoDV || !pViewInfoDV->HasFold())
		return false;

	return true;
}

void CXDlgProperty::_Update()
{
	if (m_pGeneral)
	{
		m_pGeneral->Apply();
	}

	if (m_pVisPage)
	{
		m_pVisPage->Apply();
		CXProcessEvent processEvent;
		m_pObj->AddEvent(EInfoChanged);
	}

	if (m_pColormapPage)
	{
		m_pColormapPage->Apply();
	}
}

CXDlgProperty * CXPropertyDialogFactory::CreatePropertyDialog(CXObject * pObj)
{
	CXDlgProperty* pDialog = m_hashDialog.value(pObj->GetObjectID(), nullptr);

	if (!pDialog)
	{
		auto pConsole = reinterpret_cast<CXBaseConsole*>(::GetConsole());
		auto pActiveWindow = dynamic_cast<CXWindow*>(pConsole->GetActiveWinow());

		pDialog = new CXDlgProperty(pConsole->GetMainWindowWidget(), pObj, pActiveWindow);
		m_hashDialog.insert(pObj->GetObjectID(), pDialog);
	}

	return pDialog;
}

void CXPropertyDialogFactory::ClosePropertyDialog(CXObject * pObj)
{
	m_hashDialog.remove(pObj->GetObjectID());
}
