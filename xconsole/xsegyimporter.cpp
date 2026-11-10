#include <qfile.h>
#include "xsegyimporter.h"
#include "xsegyloadparameters.h"
#include "x3dsurvey.h"
#include "xseismicdatavolume.h"
#include "xseismicsubvolume.h"
#include "xseismicutmtool.h"
#include "xproject.h"
#include "xtree.h"
#include "xloadsegytozxythread.h"
#include "xdlgcalculatingprogress.h"
#include "xglobal.h"
#include "xprocessengine.h"
#include "xalgorithmutility.h"

#include "x2dsurvey.h"
#include "x2dseismicline.h"
#include "xseismicdataline.h"
#include "xload2dsegythread.h"

bool CXSEGYImporter::ImportSEGY(CXSEGYLoadParameters* pLoadParameters)
{
	CXLoadSEGYToZXYThread* pThread = new CXLoadSEGYToZXYThread(pLoadParameters);
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread);

	pProgress->show();
	pThread->start();
	bool bAccept = false;
	CXSeismicDataVolume* pDV = NULL;
	if ( pProgress->exec() == QDialog::Accepted)
	{
		pDV = pLoadParameters->GetDataVolume();
		pDV->SetObjectName(pLoadParameters->GetDVName());

		QString strSurvey = pLoadParameters->GetDestSurveyName();
		CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(::GetProject()->GetChild(strSurvey, EX3DSurvey));

		if(!pSurvey)
		{
			//	Create the survey.
			pSurvey = new CX3DSurvey(*pLoadParameters->GetUTMTool(), strSurvey);
			::GetProject()->AddChild(pSurvey);

			//	DV folder and DV.
			CXObject *pDVFolder = pSurvey->GetFolder(EXSeismicDVFolder);
			pDVFolder->AddChild(pDV);

			//	Create inline/crossline section for the survey.
			pSurvey->CreateDefaultSection(eInlineSection);
			pSurvey->CreateDefaultSection(eCrosslineSection);
			pSurvey->CreateDefaultSection(eTimeSlice);
			pSurvey->CreateDefaultSubVolume();

			::AddObjectEvent(pSurvey);
		}
		else
		{
			//	May need expand the survey's UTM.
			CXSeismicUTMTool& utm = pDV->GetUTM();
			pSurvey->GetUTM().MergeUTM(utm);
			pSurvey->SetModifiedFlag();

			if ((utm.GetNI() == 1 || utm.GetNJ() == 1) && pLoadParameters->IsDataLine())
			{
				//Add it as data line.
				CXObject *pDLFolder = pSurvey->GetFolder(EXSeismicDataLineFolder);
				QString sName = pDLFolder->GetUnallocatedName(pDV->GetObjectName());
				

				int iLineNumber, iStartTrace, iTraceStep, iNumTrace, iMaxFold;
				double dSamplingStart, dSamplingEnd, dSamplingRate;
				float fSOffset, fOffsetStep;
				pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
				pDV->GetOffsetInfo(fSOffset, fOffsetStep, iMaxFold);

				CXSeismicDataLine *pDL = new CXSeismicDataLine(utm, dSamplingStart, dSamplingEnd, dSamplingRate, sName);
				pDL->SetOffsetInfo(iMaxFold, fSOffset, fOffsetStep);

				QFile::rename(pDV->GetTraceFileName(), pDL->GetTraceFileName());
				QFile::rename(pDV->GetTraceInfoFileName(), pDL->GetTraceInfoFileName());
				CXAlgorithmUtility::CalculateHistogram(pDL->GetTraceFileName(), pDL->GetSamplingQty(), pDL);
				pDLFolder->AddChild(pDL);
				::AddObjectEvent(pDL);

				delete pDV;
				delete pThread;
				return true;
			}
			else
			{
				//	Add it as data volume.
				CXObject *pDVFolder = pSurvey->GetFolder(EXSeismicDVFolder);

				//	Check name again.
				pDV->SetObjectName(pDVFolder->GetUnallocatedName(pDV->GetObjectName()));
				pDVFolder->AddChild(pDV);
				::AddObjectEvent(pDV);
			}
		}

		delete pThread;
		bAccept = true;	
	}

	// calculate histogram
	if (bAccept)
	{		
		CXAlgorithmUtility::CalculateHistogram(pDV->GetTraceFileName(), pDV->GetSamplingQty(), pDV);	
	}

	// Create slice file
	bool bCreateSlice = false;
	if (bAccept && pLoadParameters->GetCreateSliceFile())
	{
		CXProcessEngine process(pDV, ETraceToSlice);
		process.CalculateOnly();
		if (pDV->HasSliceFile())
			bCreateSlice = true;
	}
	else
	{
		bCreateSlice = true;
	}

	// create brick file
	if (bAccept && bCreateSlice && pLoadParameters->GetCreateBrickFile())
	{
		CXProcessEngine process(pDV, ETraceToBrick);
		process.CalculateOnly();
	}

	return true;
}

void CXSEGYImporter::Import2DSEGY(QList<CXSEGYLoadParameters*> listPara, const QString& strSurveyName)
{
	//	Create or find the 2D survey.
	CX2DSurvey *p2DSurvey = (CX2DSurvey *)::GetProject()->GetChild(strSurveyName, EX2DSurvey);
	if (!p2DSurvey)
	{
		p2DSurvey = new CX2DSurvey(strSurveyName);
		::GetProject()->AddChild(p2DSurvey);

		::AddObjectEvent(p2DSurvey);
	}

	//	A loop to import each line.
	QList<CXSeismicDataLine*> listSection;
	for (int i = 0; i < listPara.size(); i++)
	{
		CXLoad2DSEGYThread* pThread = new CXLoad2DSEGYThread(listPara[i]);
		CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread, NULL);

		pProgress->show();
		pThread->start();
		if (pProgress->exec() == QDialog::Accepted)
		{
			p2DSurvey->AddChild(pThread->GetImportedLine());

			listSection.append(pThread->GetImportedLine()->GetDefaultSection(true));

			::AddObjectEvent(pThread->GetImportedLine());
		}		
		delete pThread;
	}

	//calculate histogram
	for (int i = 0; i < listSection.size(); ++i)
	{
		CXAlgorithmUtility::CalculateHistogram(listSection[i]->GetDataFileName(), listSection[i]->GetSamplingQty(), listSection[i]);
	}

	
}