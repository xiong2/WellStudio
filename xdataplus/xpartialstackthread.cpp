#include <QCoreApplication>
#include <qvector.h>
#include "xpartialstackthread.h"
#include "xparameterspartialstack.h"
#include "xseismicdatavolume.h"
#include "xseismicirregularreader.h"
#include "xseismicsection.h"
#include "xtracecontainer.h"
#include "x3dsurvey.h"
#include "xglobal.h"
#include "xtree.h"

CXPartialStackThread::CXPartialStackThread(CXParametersPartialStack* pStackParameters)
{
	m_pStackParameters = pStackParameters;
	m_pOutputDV = NULL;
}

CXPartialStackThread::~CXPartialStackThread()
{

}

void CXPartialStackThread::RunThread()
{
	if (IsStopped())
		return;

	this->EmitSetWindowName("Partial Stack");
	this->EmitSetTaskName("Calculating...");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	//	Parameters of original data volume.
	CXSeismicDataVolume *pOriDV = dynamic_cast<CXSeismicDataVolume *>(::GetObjectByID(m_pStackParameters->GetInputDVID()));
	int iInlineInc = pOriDV->GetUTM().GetInlineIncrement();
	int iXlineInc = pOriDV->GetUTM().GetCrosslineIncrement();
	int iSOriInline = pOriDV->GetUTM().GetFirstInline();
	int iEOriInline = pOriDV->GetUTM().GetLastInline();
	int iSOriXline = pOriDV->GetUTM().GetFirstCrossline();
	int iEOriXline = pOriDV->GetUTM().GetLastCrossline();
	int iOriTimeInc = pOriDV->GetSampleInterval();
	CXSeismicIrregularReader *pReader = pOriDV->GetIrregularReader();

	//	Parameters of destination data volume.
	int iSInline = m_pStackParameters->GetStartInline();
	int iEInline = m_pStackParameters->GetEndInline();
	int iNumInline = (iEInline - iSInline) / iInlineInc + 1;
	int iSDstXline = m_pStackParameters->GetStartXline();
	int iEDstXline = m_pStackParameters->GetEndXline();
	int iNumXline = (iEDstXline - iSDstXline) / iXlineInc + 1;
	int iSTime = m_pStackParameters->GetStartZ();
	int iETime = m_pStackParameters->GetEndZ();
	int iTimeInc = m_pStackParameters->GetZInterval();
	iETime = ((iETime - iSTime) / iTimeInc) * iTimeInc + iSTime;
	int iTimeStep = iTimeInc / iOriTimeInc;
	int iRInlines = m_pStackParameters->GetRollingInlines();
	int iRXlines = m_pStackParameters->GetRollingXlines();
	int iOriTraceLen = (iETime - iSTime) / iOriTimeInc + 1;

	//	Range of reading data.
	int iSXline = iSDstXline - iXlineInc * (iRXlines / 2);
	iSXline = iSXline > iSOriXline ? iSXline : iSOriXline;
	int iEXline = iEDstXline + iXlineInc * (iRXlines / 2);
	iEXline = iEXline < iEOriXline ? iEXline : iEOriXline;
	CXSeismicSection *pSection = new CXSeismicSection(eInlineSection, iSInline);
	pSection->SetSectionRange(iSXline, iEXline);

	int i, j, m, n;
	QVector<int> vecInline;
	QVector<int> vecTraceNum;
	QVector<float *> vecPDataBuffer;
	QVector<SKETraceInfo *> vecPTraceInfo;

	//	Calculate the output bins.

	std::vector<int> vecOffsets = m_pStackParameters->GetVectorOffsets();
	std::vector<int> vecAzimuths = m_pStackParameters->GetVectorAzimuth();
	if (vecOffsets.empty())
	{
		int iMinOffset = pReader->GetMinOffset();
		int iMaxOffset = pReader->GetMaxOffset();
		vecOffsets.push_back(iMinOffset);
		vecOffsets.push_back(iMaxOffset);
		vecOffsets.push_back((iMaxOffset + iMinOffset) / 2);
	}
	if (vecAzimuths.empty())
	{
		int iMinAzimuth = pReader->GetMinAzimuth();
		int iMaxAzimuth = pReader->GetMaxAzimuth();
		vecAzimuths.push_back(iMinAzimuth);
		vecAzimuths.push_back(iMaxAzimuth);
		vecAzimuths.push_back((iMaxAzimuth + iMinAzimuth) / 2);
	}

	bool bOffsetFirst = m_pStackParameters->GetOffsetFirst();
	int iNumFold = vecOffsets.size() * vecAzimuths.size() / 9;

	//	Create the output DV.
	CX3DSurvey *pSurvey = (CX3DSurvey *)::GetObjectByID(pOriDV->GetSurveyID());
	CXObject *pDVFolder = pSurvey->GetFolder(EXSeismicDVFolder);
	QString sDVName = pDVFolder->GetUnallocatedName(m_pStackParameters->GetOutputDVName());

	CXSeismicUTMTool newUTM(pOriDV->GetUTM());
	newUTM.Resize(iSInline, iSDstXline, iNumInline, iNumXline);
	m_pOutputDV = new CXSeismicDataVolume(newUTM, iSTime, iETime, iTimeInc, sDVName, iNumFold, 0., 0., true);
	QString sDataFile = m_pOutputDV->GetTraceFileName();
	QString sTIFile = m_pOutputDV->GetTraceInfoFileName();

	//	Instance to do the partial stack.
	CXTraceContainer traceContainer(iTimeStep, iOriTraceLen, vecOffsets, vecAzimuths, 
		m_pStackParameters->GetOffsetFirst(), sDataFile, sTIFile);

	//	Prepare the data before the loop.
	for (i = - iRInlines / 2; i < iRInlines / 2; i++)
	{
		int iInline = iSInline + i * iInlineInc;
		if (iInline < iSOriInline)
			continue;
		if (iInline > iEOriInline)
			break;

		pSection->SetSectionNumber(iInline);
		int iTraceNum = pReader->GetSectionTraceQty(pSection);
		SKETraceInfo *pTraceInfo = new SKETraceInfo[iTraceNum];
		float *pData = new float[iTraceNum * iOriTraceLen];

		pReader->ReadInline(pOriDV, iInline, iSXline, iEXline, iSTime, iETime, pData, pTraceInfo);
		vecInline << iInline;
		vecTraceNum << iTraceNum;
		vecPDataBuffer << pData;
		vecPTraceInfo << pTraceInfo;
	}

	//	Initialize the progress bar.
	this->EmitSetWindowName("Partial stack for azimuth seismic data");
	this->EmitSetTaskName("Stacking...");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	int nCurrentPer, nPercent = 0, iCurrentStep = 0, iVolumeSize = iNumInline * iNumXline;

	//	Loop to iterate each inline.
	for (i = iSInline; i <= iEInline; i += iInlineInc)
	{
		//	Read in the last inline data.
		int iLastInline = i + (iRInlines / 2) * iInlineInc;
		if (iLastInline <= iEOriInline)
		{
			pSection->SetSectionNumber(iLastInline);
			int iTraceNum = pReader->GetSectionTraceQty(pSection);
			SKETraceInfo *pTraceInfo = new SKETraceInfo[iTraceNum];
			float *pData = new float[iTraceNum * iOriTraceLen];

			pReader->ReadInline(pOriDV, iLastInline, iSXline, iEXline, iSTime, iETime, pData, pTraceInfo);
			vecInline << iLastInline;
			vecTraceNum << iTraceNum;
			vecPDataBuffer << pData;
			vecPTraceInfo << pTraceInfo;
		}

		//	Check whether the 1st inline data should be freed.
		if (vecInline[0] < i - (iRInlines / 2) * iInlineInc)
		{
			float *pData = vecPDataBuffer.first();
			SKETraceInfo *pTraceInfo = vecPTraceInfo.first();
			delete[]pData;
			delete[]pTraceInfo;

			vecInline.removeFirst();
			vecTraceNum.removeFirst();
			vecPDataBuffer.removeFirst();
			vecPTraceInfo.removeFirst();
		}

		//	Now loop to iterate each CDP.
		for (j = iSDstXline; j <= iEDstXline; j += iXlineInc)
		{
			//Update the progress bar.
			nCurrentPer = static_cast<int>((++iCurrentStep) * 100 / iVolumeSize);
			if (nCurrentPer > nPercent)
			{
				nPercent++;
				if (IsStopped())
				{
					//	Free all data.
					for (i = 0; i < vecInline.size(); i++)
					{
						float *pData = vecPDataBuffer.first();
						SKETraceInfo *pTraceInfo = vecPTraceInfo.first();
						delete[]pData;
						delete[]pTraceInfo;

						vecInline.removeFirst();
						vecTraceNum.removeFirst();
						vecPDataBuffer.removeFirst();
						vecPTraceInfo.removeFirst();
					}
				
					return;
				}
				else
				{
					EmitUpdateProgress(nPercent, 100);
				}
			}

			//	First collect all relevant traces.
			int iSRXline = j - (iRXlines / 2) * iXlineInc;
			int iERXline = j + (iRXlines / 2) * iXlineInc;

			//	Iterate all rolling inlines.
			for (m = 0; m < vecInline.size(); m++)
			{
				for (n = 0; n < vecTraceNum[m]; n++)
				{
					if (vecPTraceInfo[m][n].m_iCDP < iSRXline)
						continue;
					if (vecPTraceInfo[m][n].m_iCDP > iERXline)
						break;

					SKEOneTrace oneTrace;
					oneTrace.m_pTraceInfo = &(vecPTraceInfo[m][n]);
					oneTrace.m_pData = vecPDataBuffer[m] + n * iOriTraceLen;
					traceContainer.AddOneTrace(oneTrace);
				}
			}

			//	Now stack the CDP.
			traceContainer.StackOneCDP();
		}
	}

	//	Free all data.
	for (i = 0; i < vecInline.size(); i++)
	{
		float *pData = vecPDataBuffer.first();
		SKETraceInfo *pTraceInfo = vecPTraceInfo.first();
		delete[]pData;
		delete[]pTraceInfo;

		vecInline.removeFirst();
		vecTraceNum.removeFirst();
		vecPDataBuffer.removeFirst();
		vecPTraceInfo.removeFirst();
	}

	delete pSection;

	pDVFolder->AddChild(m_pOutputDV);
	::AddObjectEvent(m_pOutputDV);
}