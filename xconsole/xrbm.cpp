#include "xrbm.h"
#include <qmenu.h>
#include "xobject.h"
#include <cassert>
#include "xtreewidgetitem.h"
#include "xtree.h"
#include "xconsole.h"
#include "xglobal.h"
#include "xdlgproperty.h"
#include "xprocessengine.h"
#include "xeventconsole.h"
#include "xdataimporter.h"

#include "x3dsurvey.h"
#include "x3dhorizon.h"
#include "xseismicsection.h"
#include "xseismicsubvolume.h"
#include "xseismicdatavolume.h"
#include "xdlgattachprofile.h"

#include "xreservoirmodel.h"
#include "xpagewellcondition.h"
#include "xwellcondition.h"
#include "xpagewellconditionupscale.h"

#include "xgeobodycollection.h"
#include "xdlgmergegeobody.h"

#include "xlfmgeometry.h"
#include "xdlglfmtohorizon.h"

#include "xdlgrosediagram.h"
#include "x2dsectionwindow.h"
#include "xconsole.h"

#include "xgmmethod.h"
#include <QProcess>
#include <QFile>
#include "xproject.h"
#include <QTextStream>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <typeinfo>
#include "xversion.h"
#include "x3dpoints.h"
#include "xpagemakefaultsticksbysurveyfrompoints.h"
#include "xlog.h"

#include "xalgorithmutility.h"
#include "xwellcurve.h"
#include "xtemplate.h"

#include "xdlgwlintegration.h"
#include "xdlgvolumeintegration.h"
#include "xdlgcalbiot.h"
#include "xdlgcalsh.h"

#include "tracesurfaceboundingpolygons.h"
#include "x2dpolygon.h"
#include "xdlgtdcalculate.h"
#include "xwell.h"
#include "xwelltd.h"
#include "xdlgwelltie.h"
#include "xdlgpyramid.h"
#include "xdlgmergedv.h"
#include "xdlgfracgridintr.h"

#include "xdlgfactory.h"
#include "xguiplusutil.h"

#include "xdlggatherwin.h"
#include "xdlggatherflatten.h"

CXRBM::CXRBM(QMenu& menu, CXObject* pObj)
:m_menu(menu), m_pObject(pObj)
{
}

CXRBM::~CXRBM()
{
}

void CXRBM::AddAction()
{
	EXObjectType eObjType = m_pObject->GetObjectType();

	switch(eObjType)
	{				
	case EXWellFolder:
		{
		m_menu.addAction(QIcon(::GetIconPath() + "WellFile.png"), "Export Wells Trajectory...", this, SLOT(slotExport()));
		m_menu.addSeparator();
			break;
		}

	case EXWell:
	{
		QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Path Spreadsheet...", this, SLOT(slotSpreadsheet()));
		pAction->setData(EXWellPath);
		pAction = m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "TD Spreadsheet...", this, SLOT(slotSpreadsheet()));
		pAction->setData(EXWellTD);
		m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Log Spreadsheet...", this, SLOT(slotSpreadsheet()));
		m_menu.addAction(QIcon(::GetIconPath() + "TD.png"), "TD Calculate...", this, SLOT(slotTDCalculate()));
		m_menu.addAction(QIcon(::GetIconPath() + "WellTie.png"), "Well Tie...", this, SLOT(slotWellTie()));
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Calculator...", this, SLOT(slotCalculator()));


		if (CXVersion::Instance().ContainsInVersion(0))
		{

			QAction* pACtion = m_menu.addAction(QIcon(::GetIconPath() + "WellStrata.png"), "Intersect Well Profile with 3-D Horizon...", this, SLOT(slotCalculateModal()));
			pACtion->setData(EWellHorizonIntersect);

			m_menu.addAction(QIcon(::GetIconPath() + "MicroSeismic.png"), "Import Micro Seismic Data...", this, SLOT(slotImport()));
		}

		m_menu.addAction(QIcon(::GetIconPath() + "WellFile.png"), "Export Logs...", this, SLOT(slotExport()));
		m_menu.addSeparator();

		break;
	}
		
	case EXWellCurve:
	{
		m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Spreadsheet...", this, SLOT(slotSpreadsheet()));
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Calculator...", this, SLOT(slotCalculator()));
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Filter", this, SLOT(slotFilter()));
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Integration...", this, SLOT(slotIntegration()));
		m_menu.addSeparator();
		
		break;
		}
	case EXMicroSeismicData:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Spreadsheet...", this, SLOT(slotSpreadsheet()));
			m_menu.addSeparator();
		}
		break;
	}
	case EXWellTops:
	{

		m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Spreadsheet...", this, SLOT(slotSpreadsheet()));
		QAction* pAction = m_menu.addAction(QIcon(::GetIconPath()), "Make 2-D Grid...", this, SLOT(slotCalculateModal()));
		pAction->setData(EMake2DGRid);
		m_menu.addSeparator();

		break;
	}
	case EX3DPoints:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Spreadsheet...", this, SLOT(slotSpreadsheet()));
			m_menu.addAction(QIcon(::GetIconPath()), "Make Fault Sticks according to survey", this, &CXRBM::slotMakeFaultSticksAccordingToSurvey);
			m_menu.addSeparator();
			break;
		}
	}
	case EXSurfaceFolder:
	case EX3DSurface:
	{
		m_menu.addAction(QIcon(::GetIconPath() + "Horizon4.png"), "Calculate Maximum Slope", this, SLOT(slotCalSurfaceSlope()));
		if (CXVersion::Instance().ContainsInVersion(ERockLab | ERockInv | ERockFrac))
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Save.png"), "Export to ASCII File...", this, SLOT(slotExport()));
			m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Calculator...", this, SLOT(slotCalculator()));
			m_menu.addSeparator();
			break;
		}
	}

	case EXHorizonFolder:
	{
		if (CXVersion::Instance().ContainsInVersion(ERockLab | ERockInv | ERockFrac))
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Save.png"), "Export to ASCII File...", this, SLOT(slotExport()));
			m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Calculator...", this, SLOT(slotCalculator()));
			m_menu.addSeparator();

			m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Biot coefficient volume ...", this, SLOT(slotBiot()));
			m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Calculate horizontal stresses ...", this, SLOT(slotSh()));

			break;
		}
	}

	case EX3DHorizon:
	{
		if (CXVersion::Instance().ContainsInVersion(ERockLab | ERockInv | ERockFrac))
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Save.png"), "Export to ASCII File...", this, SLOT(slotExport()));
			m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Calculator...", this, SLOT(slotCalculator()));
			m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Trac Wireframe boundary", this, SLOT(slotWireframe()));
			m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Trac Boundary Polygons", this, SLOT(slotTraceBPolygons()));
		}

		if (CXVersion::Instance().ContainsInVersion(ERockInv | ERockFrac))
		{
			QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "ResGeometryModel.png"), "Build LFM Framework...", this, SLOT(slotCalculateNonModal()));
			pAction->setData(EBuildLowFreuqencyModel);
			m_menu.addSeparator();
			QAction* pAttAction = m_menu.addAction(QIcon(::GetIconPath()), "Extract Attributes...", this, SLOT(slotCalculateNonModal()));
			pAttAction->setData(EExtractHorizonAttribute);
			m_menu.addSeparator();
		}
		
		break;
	}

	case EX3DSurvey:
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Inline.png"), "Create Inline Section", this, SLOT(slotCreateSection())); 			  			  
			m_menu.addAction(QIcon(::GetIconPath() + "Crossline.png"), "Create Crossline Section", this, SLOT(slotCreateSection())); 			  			  
			m_menu.addAction(QIcon(::GetIconPath() + "TimeSlice.png"), "Create Time Slice", this, SLOT(slotCreateSection()));
			m_menu.addAction(QIcon(::GetIconPath() + "SubVolume.png"), "Create Sub-Volume", this, SLOT(slotCreateSection()));
			m_menu.addAction(QIcon(::GetIconPath() + "InlinePic.png"), "Create Inline Profile...", this, SLOT(slotCreateSection()));
			m_menu.addAction(QIcon(::GetIconPath() ), "Create Flat Horizon...", this, SLOT(slotCreateFlatHorizon()));
			m_menu.addSeparator();  

			if (CXVersion::Instance().ContainsInVersion(ERockInv | ERockFrac))
			{
				QAction* pAVOAction = m_menu.addAction(QIcon(::GetIconPath()), "Prestack AVO Inversion...", this, SLOT(slotCalculateNonModal()));
				pAVOAction->setData(EAVOInversion);

				QAction* pCSSIAction = m_menu.addAction(QIcon(::GetIconPath()), "Constrained Sparse-Spike Inversion", this, SLOT(slotCalculateNonModal()));
				pCSSIAction->setData(ECSSInversion);

				QAction* pAVOSSIAction = m_menu.addAction(QIcon(::GetIconPath()), "Prestack AVO Sparse Spike Inversion...", this, SLOT(slotCalculateNonModal()));
				pAVOSSIAction->setData(EAVOSSInversion);
				m_menu.addSeparator();
				QAction* pAVAzAction = m_menu.addAction(QIcon(::GetIconPath()), "AVAz Analysis...", this, SLOT(slotCalculateNonModal()));
				pAVAzAction->setData(EFractureAnalysisAVO);

				QAction* pForwardingAction = m_menu.addAction(QIcon(::GetIconPath()), "Seismic Anisotropy Forwarding...", this, SLOT(slotCalculateNonModal()));
				pForwardingAction->setData(EAnisotrpicForwarding);

				m_menu.addSeparator();
			}
			
			break;
		}
	case EXSeismicDVFolder:
	{
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Biot coefficient volume ...", this, SLOT(slotBiot()));
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Biot coefficient volume ...", this, SLOT(slotBiot()));
		m_menu.addAction(QIcon(::GetIconPath() + "GeobodyCollection.png"), "Merge data volumes ...", this, SLOT(slotGeneral()));
		break;
	}
	case EXSeismicSection:
	{
		auto pSection = dynamic_cast<CXSeismicSection*>(m_pObject);
		if (eInlineSection == pSection->GetSectionType() || eCrosslineSection == pSection->GetSectionType())
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Seismic.png"), "Show in section window...", this, SLOT(slotShowInSectionWindow()));
		}
		break;
	}
	case EXSeismicDataVolume:
	{
		CXSeismicDataVolume *pDV = (CXSeismicDataVolume *)m_pObject;

		m_menu.addAction(QIcon(::GetIconPath() + "Save.png"), "Export to SEGY File...", this, SLOT(slotExport()));
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Calculator...", this, SLOT(slotCalculator()));
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Integration...", this, SLOT(slotIntegration()));

		if (CXVersion::Instance().ContainsInVersion(ERockInv | ERockFrac))
		{
			QAction* pInterpolAction = m_menu.addAction(QIcon(::GetIconPath()), "Interpolate...", this, SLOT(slotCalculateOnly()));
			pInterpolAction->setData(ESeismicInterpolation);
		}

		m_menu.addSeparator();
		if (!pDV->IsPrestack())
		{
			if (!pDV->HasSliceFile())
			{
				QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "SliceVolume.png"), "Generate Slice File", this, SLOT(slotCalculateOnly()));
				pAction->setData(ETraceToSlice);
			}
			if (!pDV->HasBrickFile())
			{
				QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "BrickFile.png"), "Generate Brick File", this, SLOT(slotCalculateOnly()));
				pAction->setData(ETraceToBrick);
			}
			else
			{
				if (CXVersion::Instance().ContainsInVersion(0))
				{
					QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "Geobody.png"), "Geobody Detection...", this, SLOT(slotCalculateNonModal()));
					pAction->setData(EDetectGeobody);
				}
			}
			m_menu.addAction(QIcon(::GetIconPath() + "Pyramid.png"), "Pyramid Filter...", this, SLOT(slotGeneral()));

			m_menu.addAction(QIcon(::GetIconPath()), "Remove Footprint...", this, SLOT(slotRemovefp()));

			if (CXVersion::Instance().ContainsInVersion(ERockInv | ERockFrac))
			{
				QAction* pFilteringAction = m_menu.addAction(QIcon(::GetIconPath()), "Seismic Filtering...", this, SLOT(slotCalculateModal()));
				pFilteringAction->setData(ESeismicFiltering);

				QAction* pPCAAction = m_menu.addAction(QIcon(::GetIconPath()), "PCA Filtering...", this, SLOT(slotCalculateModal()));
				pPCAAction->setData(ESeismicPCAFiltering);
			}
		}
		else
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Gather Flattening...", this, SLOT(slotGeneral()));

			if (CXVersion::Instance().ContainsInVersion(ERockInv | ERockFrac))
			{

				QAction* pAVOAction = m_menu.addAction(QIcon(::GetIconPath()), "Prestack AVO Inversion...", this, SLOT(slotCalculateNonModal()));
				pAVOAction->setData(EAVOInversion);

				QAction* pAction = m_menu.addAction(QIcon(::GetIconPath()), "Prestack AVO Sparse Spike Inversion...", this, SLOT(slotCalculateNonModal()));
				pAction->setData(EAVOSSInversion);

				if (pDV->IsAzimuth())
				{
					QAction* pAction = m_menu.addAction(QIcon(::GetIconPath()), "Partial Stack...", this, SLOT(slotCalculateNonModal()));
					pAction->setData(EPartialStack);

					QAction* pFracAction = m_menu.addAction(QIcon(::GetIconPath()), "AVAz Analysis...", this, SLOT(slotCalculateNonModal()));
					pFracAction->setData(EFractureAnalysisAVO);

					QAction* pFracInvAction = m_menu.addAction(QIcon(::GetIconPath()), "Seismic Anisotropy Inversion...", this, SLOT(slotCalculateNonModal()));
					pFracInvAction->setData(EAnisotropyInversion);

					if (pDV->ContainsAzimuthOnly())
					{
						QAction* pFracAttAction = m_menu.addAction(QIcon(::GetIconPath()), "Calculte Fracture Attributes...", this, SLOT(slotCalculateNonModal()));
						pFracAttAction->setData(EFractureAttribute);
					}

					m_menu.addAction(QIcon(::GetIconPath()), "Rose Diagram...", this, SLOT(slotRoseDiagram()));
				}
			}
		}
		m_menu.addSeparator();

		if (Qt::AltModifier == QApplication::queryKeyboardModifiers()) // security mode
		{
			QAction* pAction = m_menu.addAction(QIcon(::GetIconPath()), "Recalculate Histogram...", this, SLOT(slotCalculateOnly()));
			pAction->setData(ERecalcHistogram);
			m_menu.addSeparator();
		}

		break;
	}

	case EXRandomSection:
	{
		m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Spreadsheet...", this, SLOT(slotSpreadsheet()));
		m_menu.addSeparator();
		break;
	}
	case EXSeismicDataLine:
	{
		m_menu.addAction(QIcon(::GetIconPath() + "Save.png"), "Export to SEGY File...", this, SLOT(slotExport()));
		m_menu.addAction(QIcon(::GetIconPath() + "Calculator.png"), "Integration...", this, SLOT(slotIntegration()));
		m_menu.addSeparator();
		break;
	}
	case EXPrestackGather:
	{
		m_menu.addAction(QIcon(::GetIconPath() + "Prestack3D.png"), "Show the gather...", this, SLOT(slotGeneral()));
		m_menu.addSeparator();
		break;
	}
	case EXGeobodyCollection:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			m_menu.addAction(QIcon(::GetIconPath() + "GeobodyWhole.png"), "Merge Geobodies...", this, SLOT(slotGeneral()));
			m_menu.addSeparator();
		}
		break;
	}
	case EXReservoirModel:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{

			m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Well Condition...", this, SLOT(slotWellCondition()));
			m_menu.addSeparator();
		}
		break;
	}
	case EXFracturePatch:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{

			m_menu.addAction(QIcon(::GetIconPath() + "FracGrid.png"), "Intersect with grid...", this, SLOT(slotGeneral()));
			m_menu.addSeparator();
		}
		break;
	}
	case EXFaultFolder:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			m_menu.addAction(QIcon(::GetIconPath()), "Extract Fault Pillars...", this, SLOT(slotExtractFaultPillars()));
			m_menu.addSeparator();
		}
		break;
	}
	case EXFaultPolygonFolder:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Save.png"), "Export to ASCII File...", this, SLOT(slotExport()));
			m_menu.addSeparator();
		}
		break;
	}
	case EXGMFaultFolder:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			m_menu.addAction(QIcon(::GetIconPath()), "Auto Connect...", this, SLOT(slotAutoConnectFaults()));
			m_menu.addSeparator();
		}
		break;
	}
	case EXWellCondition:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Upscale...", this, SLOT(slotWellConditionUpscale()));
			m_menu.addSeparator();
		}
		break;
	}
	case EXGridModel:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "sectionerase.png"), "InterSection...", this, SLOT(slotCalculateModal()));
			pAction->setData(EModelIncision);
			m_menu.addSeparator();
		}
		break;
	}
	case EXCurveCells:
	{
		if (CXVersion::Instance().ContainsInVersion(0))
		{
			QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "Spreadsheet.png"), "Make Interpolation", this, SLOT(slotCalculateModal()));
			pAction->setData(EMakePropertyModel);
			m_menu.addSeparator();
		}
		break;
	}

	case EXLowFrequencyModel:
	{
		if (CXVersion::Instance().ContainsInVersion(ERockInv | ERockFrac))
		{
			QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "UpscaleGeometry.png"), "Intersect With Wells", this, SLOT(slotCalculateModal()));
			pAction->setData(EIntersectLFMAndWell);
			m_menu.addAction(QIcon(::GetIconPath() + "Horizon.png"), "Convert to Horizons...", this, SLOT(slotGeneral()));
			QAction* pInvAction = m_menu.addAction(QIcon(::GetIconPath()), "Geostatistical Pre-stack Inversion", this, SLOT(slotCalculateNonModal()));
			pInvAction->setData(EGSInversion);
			m_menu.addSeparator();
		}
		break;
	}

	case EXLFMUpscalingGeometry:
	{
		if (CXVersion::Instance().ContainsInVersion(ERockInv | ERockFrac))
		{
			QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "UpscaleResult.png"), "Upscale Well Curve", this, SLOT(slotCalculateModal()));
			pAction->setData(ECalculateUpscaling);
			m_menu.addSeparator();
		}
		break;
	}

	case EXLFMUpscalingAttribute:
	{
		if (CXVersion::Instance().ContainsInVersion(ERockInv | ERockFrac))
		{
			QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "ResPropertyModel.png"), "Make Low Frequency Model", this, SLOT(slotCalculateModal()));
			pAction->setData(ELFMInterpolation);
			m_menu.addSeparator();
		}
		break;
	}	

	default:
		break;
	}

	// Add delete , delete content and rename
	_AddDefaultAction();

	// add debug info
#ifndef NDEBUG
#ifdef WIN32
	m_menu.addSeparator();
	m_menu.addAction(QIcon(::GetIconPath()), "Debug Info", this, SLOT(slotShowDebugInfo()));
#endif
#endif
}

void CXRBM::slotWellTie()
{
	CXDlgWellTie *pDlg = new CXDlgWellTie((CXWell *)m_pObject, ::GetConsole()->GetMainWindowWidget());
	pDlg->show();
}

void CXRBM::slotRoseDiagram()
{
	CXDlgRoseDiagram *pDlg = new CXDlgRoseDiagram(m_pObject);
	pDlg->setWindowTitle("Rose Diagram");
	pDlg->show();
}

void CXRBM::slotGeneral()
{
	QAction *pAction = qobject_cast<QAction *>(sender());
	if (pAction->iconText().contains("Merge Geobodies"))
	{
		CXGeobodyCollection *pGCollection = dynamic_cast<CXGeobodyCollection *>(m_pObject);
		if (pGCollection)
		{
			CXDlgMergeGeobody dlg(pGCollection);
			dlg.exec();
		}
	}
	else if (pAction->iconText().contains("Gather Flattening"))
	{
		CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(m_pObject);
		if (pDV)
		{
			XDlgGatherFlatten dlg(pDV);
			dlg.exec();
		}
	}
	else if (pAction->iconText().contains("Convert to Horizons"))
	{
		CXLFMGeometry *pGeometry = dynamic_cast<CXLFMGeometry *>(m_pObject);
		if (pGeometry)
		{
			CXDlgLFMToHorizon dlg(pGeometry);
			dlg.exec();
		}
	}
	else if (pAction->iconText().contains("Pyramid"))
	{
		XDlgPyramid *pDlg = new XDlgPyramid((CXSeismicDataVolume *)m_pObject);
		pDlg->show();
	}
	else if (pAction->iconText().contains("Merge data volumes"))
	{
		XDlgMergeDV *pDlg = new XDlgMergeDV(m_pObject);
		pDlg->show();
	}
	else if (pAction->iconText().contains("Intersect with grid"))
	{
		CXDlgFracGridIntr *pDlg = new CXDlgFracGridIntr(m_pObject);
		pDlg->show();
	}
	else if (pAction->iconText().contains("Show the gather"))
	{
		XDlgGatherWin *pDlg = new XDlgGatherWin(m_pObject);
		pDlg->show();
	}
}

void CXRBM::slotCalSurfaceSlope()
{
	CX3DSurface* pSurf = dynamic_cast<CX3DSurface*>(m_pObject);
	CXUTMTool& utm = pSurf->GetUTM();
	double dDeltI = utm.GetIInterval(), dDeltJ = utm.GetJInterval();
	double dDeltD = sqrtf(dDeltI * dDeltI + dDeltJ * dDeltJ);
	int i, j, nI = utm.GetNI(), nJ = utm.GetNJ();
	int iSize = nI * nJ;
	float* pData = pSurf->GetData();

	float* pNData = new float[iSize];
	for (i = 0; i < iSize; i++)
		pNData[i] = ::g_dInvalidData;

	float fSMax, fS, v1, v2 ;
	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			v1 = pData[i * nJ + j];
			if (v1 == ::g_dInvalidData)
				continue;

			fSMax = 0.;
			if (i > 0)
			{
				if (j > 0)
				{
					v2 = pData[(i - 1) * nJ + j - 1];			//	bottom left.
					if (v2 == ::g_dInvalidData)
						fS = 0;
					else
						fS = qAbs(v1 - v2) / dDeltD;
					fSMax = qMax(fS, fSMax);
				}

				v2 = pData[(i - 1) * nJ + j ];			//	bottom.
				if (v2 == ::g_dInvalidData)
					fS = 0;
				else
					fS = qAbs(v1 - v2) / dDeltD;
				fSMax = qMax(fS, fSMax);

				if (j < nJ - 1)
				{
					v2 = pData[(i - 1) * nJ + j + 1];			//	bottom right.
					if (v2 == ::g_dInvalidData)
						fS = 0;
					else
						fS = qAbs(v1 - v2) / dDeltD;
					fSMax = qMax(fS, fSMax);
				}
			}

			if (j > 0)
			{
				v2 = pData[i * nJ + j - 1];			//	left.
				if (v2 == ::g_dInvalidData)
					fS = 0;
				else
					fS = qAbs(v1 - v2) / dDeltD;
				fSMax = qMax(fS, fSMax);
			}

			if (j < nJ - 1)
			{
				v2 = pData[i * nJ + j + 1];			//	right.
				if (v2 == ::g_dInvalidData)
					fS = 0;
				else
					fS = qAbs(v1 - v2) / dDeltD;
				fSMax = qMax(fS, fSMax);
			}

			if (i < nI - 1)
			{
				if (j > 0)
				{
					v2 = pData[(i + 1) * nJ + j - 1];			//	top left.
					if (v2 == ::g_dInvalidData)
						fS = 0;
					else
						fS = qAbs(v1 - v2) / dDeltD;
					fSMax = qMax(fS, fSMax);
				}

				v2 = pData[(i + 1) * nJ + j];			//	top.
				if (v2 == ::g_dInvalidData)
					fS = 0;
				else
					fS = qAbs(v1 - v2) / dDeltD;
				fSMax = qMax(fS, fSMax);

				if (j < nJ - 1)
				{
					v2 = pData[(i + 1) * nJ + j + 1];			//	top right.
					if (v2 == ::g_dInvalidData)
						fS = 0;
					else
						fS = qAbs(v1 - v2) / dDeltD;
					fSMax = qMax(fS, fSMax);
				}
			}

			pNData[i * nJ + j] = atan(fSMax);
		}
	}

	CXObject *pParent = pSurf->GetParent();
	CX3DSurface* pNewSurf = new CX3DSurface(utm, pParent->GetUnallocatedName(pSurf->GetObjectName() + "_Slope"));
	pNewSurf->SetData(pNData);
	delete[]pNData;

	pParent->AddChild(pNewSurf);

	::AddObjectEvent(pParent);
}

void CXRBM::slotSpreadsheet()
{
	QAction* pSender = dynamic_cast<QAction*>(sender());
	assert(pSender);

	EXObjectType eType = static_cast<EXObjectType>(pSender->data().toInt());
	CXObject *pObj = m_pObject;
	if (eType == EXWellPath || eType == EXWellTD)
	{
		QList<CXObject *> listObj = m_pObject->GetChildren(eType);
		if (listObj.isEmpty())
			return;

		pObj = listObj.first();
	}

	auto pDlgDataSheet = CXDlgFactory::Instance().CreateDialog(pObj->GetObjectID(), eDataSheetDialog);
	pDlgDataSheet->show();

}

void CXRBM::slotCalculator()
{
	::GetConsole()->OpenCalculator(m_pObject->GetObjectID());
}

void CXRBM::slotFilter()
{
	CXWellCurve *pWellCurve = dynamic_cast<CXWellCurve *>(m_pObject);
	unsigned int iNumber = pWellCurve->GetPointNumber();
	double dStep = pWellCurve->GetStep();
	double dStart, dEnd;
	pWellCurve->GetDepthRange(dStart, dEnd);
	vector<double> vecData(iNumber);

	if (!CXAlgorithmUtility::GetFilteredData(pWellCurve, &vecData[0], 1, 60, 10, 10, 3))
		return;

	CXObject *pWell = pWellCurve->GetParent();
	CXWellCurve *pCurve = new CXWellCurve(pWell->GetUnallocatedName(pWellCurve->GetObjectName()));

	double *pBuff = new double[iNumber];
	memcpy(pBuff, &vecData[0], sizeof(double) * iNumber);
	pCurve->ResetData(dStart, dStep, iNumber, pBuff);
	CXTemplate *pTemplate = CXTemplate::GetTemplate(pWellCurve->GetTemplateID());
	pCurve->SetTemplateID(pTemplate->GetID());
	pWell->AddChild(pCurve);

	::AddObjectEvent(pCurve);
}

void CXRBM::slotIntegration()
{
	if (m_pObject->GetObjectType() == EXWellCurve)
	{
		XDlgWLIntegration dlg(m_pObject);
		dlg.exec();
	}
	else if (m_pObject->GetObjectType() == EXSeismicDataVolume
		|| m_pObject->GetObjectType() == EXSeismicDataLine)
	{
		XDlgVolumeIntegration dlg(m_pObject);
		dlg.exec();
	}
}

void CXRBM::slotTDCalculate()
{
	CXDlgTDCalculate dlg((CXWell *)m_pObject);
	dlg.exec();
}

void CXRBM::slotBiot()
{
	XDlgCalBiot dlg(m_pObject);
	dlg.exec();
}

void CXRBM::slotSh()
{
	XDlgCalSH dlg(m_pObject);
	dlg.exec();
}

void CXRBM::slotImport()
{
	CXDataImporter importer;

	QAction *pAction = qobject_cast<QAction *>(sender());
	if(pAction->iconText().contains("Micro Seismic"))
	{
		importer.ImportData(eMicroSeismicASCII, m_pObject);
	}
}

void CXRBM::slotExport()
{
	::GetConsole()->ExportDialog(m_pObject);
}

void CXRBM::AddDeleteAction()
{
	// Delete 
	QAction* pActionDelete = m_menu.addAction(QIcon(::GetIconPath() + "Delete.png"),"Delete...",this,SLOT(slotDelete()));
	if (m_pObject->IsLocked() || !m_pObject->GetDeletableFlag())
		pActionDelete->setDisabled(true);
}

void CXRBM::_AddDefaultAction()
{
	AddDeleteAction();

	// Delete content
	QAction* pActionDeleteContent = m_menu.addAction(QIcon(::GetIconPath() + "Delete.png"),"Delete Content...",this,SLOT(slotDeleteContent()));
	QList<CXObject*> listChildren = m_pObject->GetChildrenList();
	if (listChildren.empty() || !m_pObject->GetDeletableFlag())
		pActionDeleteContent->setDisabled(true);
	else
	{
		for (int i=0; i<listChildren.size(); ++i)
		{
			if (listChildren.at(i)->IsLocked())
			{
				pActionDeleteContent->setDisabled(true);
				break;
			}
		}
	}

	// rename
	QAction* pActionRename = m_menu.addAction(QIcon(), "Rename", this, SLOT(slotRename()));
	if (m_pObject->IsLocked() || !m_pObject->GetDeletableFlag())
		pActionRename->setDisabled(true);

	m_menu.addSeparator();
	m_menu.addAction("Properties...", this, SLOT(slotProperties()));

}

void CXRBM::slotProperties()
{
	CXDlgProperty *pDlg = CXPropertyDialogFactory::Instance().CreatePropertyDialog(m_pObject);
	pDlg->show();
}

void CXRBM::slotDelete()
{
	if (!m_pObject)
		return;

	QList<QUuid> listID = CXTree::Instance().GetSelectedSiblingIDs(m_pObject->GetObjectID());
	for (int i=0; i<listID.size(); ++i)
	{
		CXObject* pObj = ::GetObjectByID(listID.at(i));
		if (pObj)
		{
			_DeleteObj(pObj);
		}
	}	
}

void CXRBM::_DeleteObj(CXObject* pObj)
{
	if (!pObj)
		return;

	if (pObj->IsLocked())
		return;

	CXObject* pParentObj = pObj->GetParent();
	if (!pParentObj)
		return;

	QList<CXObject*> listChildren = pObj->GetChildrenList();
	for (int i=0; i<listChildren.size(); ++i)
	{
		_DeleteObj(listChildren.at(i));
	}

	pParentObj->RemoveOneChild(pObj);
	{
		CXProcessEvent processEvent;
		pObj->AddEvent(EDeleted);
	}

	delete pObj;
}

void CXRBM::slotMakeFaultSticksAccordingToSurvey()
{
	auto pPoints = dynamic_cast<CX3DPoints*>(m_pObject);
	if (!pPoints) return;

	{
		uint n = 0;
		if (!pPoints->GetData(n) || n == 0)
		{
			CXLog::AddLog("The points is empty.", true);
			return;
		}
	}

	if (::GetProject()->GetChildren(EX3DSurvey).isEmpty())
	{
		CXLog::AddLog("The project should have a survey at least.", true);
		return;
	}

	CXPageMakeFaultSticksBySurveyFromPoints page(pPoints);
	page.exec();
}

void CXRBM::slotDeleteContent()
{
	QList<CXObject*> listChildren = m_pObject->GetChildrenList();
	QList<QUuid> listObjID;

	for (int i=0; i<listChildren.size(); ++i)
	{
		_DeleteObj(listChildren.at(i));
	}
}

void CXRBM::slotRename()
{
	CXTreeWidgetItem* pTreeItem = CXTree::Instance().GetTreeItemFromID(m_pObject->GetObjectID());
	if (!pTreeItem)
		return;
	else
	{
		pTreeItem->setFlags(pTreeItem->flags() | Qt::ItemIsEditable);
		pTreeItem->treeWidget()->editItem(pTreeItem, 0);
	}
}

void CXRBM::slotCreateSection()
{
	CX3DSurvey *pSurvey = (CX3DSurvey *)m_pObject;
	CXSeismicSection *pSection = NULL;

	QAction *pAction = qobject_cast<QAction *>(sender());
	if(pAction->iconText().contains("Inline Section"))
	{
		pSection = pSurvey->CreateDefaultSection(eInlineSection);
	}
	else if(pAction->iconText().contains("Crossline"))
	{
		pSection = pSurvey->CreateDefaultSection(eCrosslineSection);
	}
	else if (pAction->iconText().contains("Time Slice"))
	{
		pSection = pSurvey->CreateDefaultSection(eTimeSlice);
	}
	else if (pAction->iconText().contains("Sub-Volume"))
	{
		CXSeismicSubVolume *pSDV = pSurvey->CreateDefaultSubVolume();

		if (pSDV)
			::AddObjectEvent(pSDV);
	}
	else if (pAction->iconText().contains("Inline Profile"))
	{
		CXDlgAttachProfile dlgAttachProfile(m_pObject);
		dlgAttachProfile.exec();
	}
			
	if(pSection )
		::AddObjectEvent(pSection );
}

void CXRBM::slotCreateFlatHorizon()
{
	CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey*>(m_pObject);
	if (!pSurvey)
		return;

	CXSeismicUTMTool utm = pSurvey->GetUTM();
	CX3DHorizon* pHorizon = new CX3DHorizon(pSurvey->GetObjectID(), utm, "Horizon");
	int nSize = utm.GetNI()*utm.GetNJ();
	float* pData = pHorizon->GetData();
	for (int i = 0; i < nSize; ++i)
		pData[i] = 0.;

	CXObject* pFolder = pSurvey->GetFolder(EXHorizonFolder, true);
	if (!pFolder)
		return;

	pFolder->AddChild(pHorizon);
	::AddObjectEvent(pHorizon);


}

void CXRBM::slotWellCondition()
{
	CXReservoirModel *pModel = (CXReservoirModel *)m_pObject;
	if (pModel)
	{
		CXPageWellCondition dlg(pModel);
		dlg.exec();
	}	
}

void CXRBM::slotWellConditionUpscale()
{
	CXWellCondition *pWellCondition = dynamic_cast<CXWellCondition*>(m_pObject);
	if (pWellCondition)
	{
		CXPageWellConditionUpscale dlg(pWellCondition);
		dlg.exec();
	}
}

void CXRBM::slotExtractFaultPillars()
{
	CXGMMethod::ExtractFaultPillars(m_pObject);
}

void CXRBM::slotAutoConnectFaults()
{
	CXGMMethod::AutoConnectFaults(m_pObject);
}
void CXRBM::slotCalculateModal()
{
	QAction* pSender = dynamic_cast<QAction*>(sender());
	assert(pSender);

	EXObjectType eType = static_cast<EXObjectType>(pSender->data().toInt());

	CXProcessEngine process(m_pObject, eType);
	process.Calculate();
}

void CXRBM::slotCalculateNonModal()
{
	QAction* pSender = dynamic_cast<QAction*>(sender());
	assert(pSender);

	EXObjectType eType = static_cast<EXObjectType>(pSender->data().toInt());

	CXProcessEngine process(m_pObject, eType);
	process.Calculate(false);
}

void CXRBM::slotCalculateOnly()
{
	QAction* pSender = dynamic_cast<QAction*>(sender());
	assert(pSender);

	EXObjectType eType = static_cast<EXObjectType>(pSender->data().toInt());

	CXProcessEngine process(m_pObject, eType);
	process.CalculateOnly();
}

void CXRBM::slotShowDebugInfo()
{
	QString strFileName = ::GetProject()->GetProjectPath() + "debufinfo.txt";
	int i = 2;
	while (QFile::exists(strFileName))
	{
		strFileName = ::GetProject()->GetProjectPath() + "debufinfo" + QString::number(i++) + ".txt";
	}

	QFile qFile(strFileName);
	qFile.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream stream(&qFile);

	stream << "Object Name :" << typeid(*m_pObject).name() << '\n';
	stream << "Object ID :"   << m_pObject->GetObjectID().toString() <<endl;

	qFile.close();

	QProcess* pProcess = new QProcess(::GetConsole()->GetMainWindowWidget());
	pProcess->start("notepad.exe", QStringList() << strFileName);
}

void CXRBM::slotShowInSectionWindow()
{
	CXWindow *pSectionWindow = GetConsole()->CreateNewWindow(eSectionWindow);
	if (!pSectionWindow)
		return;

	auto pMainWindow = dynamic_cast<QMainWindow*>(GetConsole()->GetMainWindowWidget());
	if (!pMainWindow)
		return;

	QMdiArea *pMDI = dynamic_cast<QMdiArea *>(pMainWindow->centralWidget());
	if (pMDI)
	{
		QMdiSubWindow *pSubWindow = pMDI->addSubWindow(pSectionWindow);
		pSubWindow->show();
		pMDI->viewport()->update();
	}
	else
	{
		pSectionWindow->show();
	}

	pSectionWindow->InitOpenGL();
	pSectionWindow->SetObjectVisibility(m_pObject->GetObjectID(), true);
}

void CXRBM::slotWireframe()
{
	CX3DHorizon *pSurf = dynamic_cast<CX3DHorizon *>(m_pObject);
	if (!pSurf)
		return;

	CX3DHorizon *pNewSurf = new CX3DHorizon(pSurf->GetSurveyID(), pSurf->GetUTM(), pSurf->GetParent()->GetUnallocatedName(pSurf->GetObjectName() + "_WF"));

	float *pData = pSurf->GetData();
	int i, j, nI = pSurf->GetUTM().GetNI(), nJ = pSurf->GetUTM().GetNJ(), iCount = -1;
	float *pNData = new float[nI * nJ];
	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			iCount++;
			pNData[iCount] = pData[iCount];
			if (pData[iCount] != g_dInvalidData)
			{
				if (i == 0 || i == nI - 1 || j == 0 || j == nJ - 1)
					continue;
				else if (pData[(i - 1) * nJ + j] == g_dInvalidData
					|| pData[(i + 1) * nJ + j] == g_dInvalidData
					|| pData[i * nJ + j - 1] == g_dInvalidData
					|| pData[i * nJ + j + 1] == g_dInvalidData
					|| pData[(i - 1) * nJ + j - 1] == g_dInvalidData
					|| pData[(i + 1) * nJ + j - 1] == g_dInvalidData
					|| pData[(i - 1) * nJ + j + 1] == g_dInvalidData
					|| pData[(i + 1) * nJ + j + 1] == g_dInvalidData)
					continue;
				else
					pNData[iCount] = g_dInvalidData;
			}
		}
	}

	pNewSurf->SetData(pNData);
	pSurf->GetParent()->AddChild(pNewSurf);
	::AddObjectEvent(pSurf->GetParent());
}

void CXRBM::slotTraceBPolygons()
{
	CX3DSurface *pSurf = dynamic_cast<CX3DSurface *>(m_pObject);
	if(!pSurf)
		return;

	TraceSurfaceBoundingPolygons traceSBP(pSurf->GetUTM(), pSurf->GetData());
	traceSBP.TracePolygons();
	QVector<QPolygonF>& vecPolygons = traceSBP.GetPolygons();

	CXObject *pPolygonFolder = ::GetRootObjectFolder(EXPolygonFolder);

	foreach(QPolygonF polygon, vecPolygons)
	{
		auto p2DPolygon = new CX2DPolygon(pPolygonFolder->GetUnallocatedName(pSurf->GetObjectName()), EX2DPolygon);

		int nSize = polygon.size() * 2;
		double *pData = new double[nSize];
		for (int i = 0; i < nSize; i += 2)
		{
			pData[i] = polygon[i / 2].x();
			pData[i + 1] = polygon[i / 2].y();
		}

		p2DPolygon->ResetData(pData, nSize);
		pPolygonFolder->AddChild(p2DPolygon);
	}
	::AddObjectEvent(pPolygonFolder);
}

void CXRBM::slotRemovefp()
{
	auto pDV = dynamic_cast<CXSeismicDataVolume*>(m_pObject);
	if (!pDV)
		return;

	if (!pDV->HasSliceFile())
	{
		QAction* pAction = m_menu.addAction(QIcon(::GetIconPath() + "SliceVolume.png"), "Generate Slice File", this, SLOT(slotCalculateOnly()));
		pAction->setData(ETraceToSlice);
	}

	NGuiPlusUtil::RemoveFootprint(pDV);

}