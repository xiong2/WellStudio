#include "xalgorithmutility.h"
#include "xobject.h"
#include "xthreadcalchistogram.h"
#include "xdlgcalculatingprogress.h"
#include <qwidget.h>
#include "xbaseconsole.h"
#include "xglobal.h"
#include "xwellcurve.h"
#include "xcubicspline.h"
#include "xwell.h"
#include "xutility.h"
#include "Dsp/Dsp.h"

void CXAlgorithmUtility::CalculateHistogram(const QString& strFileName, int nK, CXObject* pbj)
{

	CXThreadCalcHistogram* pThread = new CXThreadCalcHistogram(strFileName, nK);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread, pParentWidget);

	pProgress->show();
	pThread->start();
	pProgress->exec();

	// set histogram
	if (!pThread->IsStopped())
	{
		pbj->SetHistogram(pThread->GetHistogram());
	}

	delete pThread;
}

bool CXAlgorithmUtility::GetFilteredData(CXWellCurve* pCurve, double* pBuffer, int nType, double lowPassFreq, double lowPassOvap, double highPassFreq, double highPassOvap)
{
	int nSamplingNum = pCurve->GetPointNumber();
	double* pData = pCurve->GetData();
	if (!pData || nSamplingNum == 0)
		return false;

	double dStart = pCurve->GetStart();
	double dStep = pCurve->GetStep();

	if (nType == 0)
	{
		memcpy(pBuffer, pData, sizeof(double)*nSamplingNum);
		return true;
	}

	CXWell* pWell = dynamic_cast<CXWell*>(pCurve->GetAncient(EXWell));
	if (!pWell)
		return false;

	vector<double> vecX, vecY, vecOldTWT, vecOldMD;
	if (!pWell->GetXYAndTWT(vecX, vecY, vecOldTWT, vecOldMD) || vecOldTWT.size() < 2)
	{
		vecOldTWT.resize(nSamplingNum);
		vecOldMD.resize(nSamplingNum);

		vecOldTWT[0] = dStart;
		vecOldMD[0] = dStart;
		for (int i = 1; i < nSamplingNum; i++)
		{
			vecOldTWT[i] = vecOldTWT[i - 1] + dStep;
			vecOldMD[i] = vecOldTWT[i];
		}
	}

	// Get value	
	double fEPSInv = ::GetEPSofInvalidData(::g_dInvalidData);
	vector<double> vecInMD, vecInData;
	for (int i = 0; i < nSamplingNum; ++i)
	{
		if (qAbs(pData[i] - g_dInvalidData) >  fEPSInv)
		{
			vecInMD.push_back(dStart + i*dStep);
			vecInData.push_back(pData[i]);
		}
	}

	// get valid data range
	vector<double> vecMD, vecTWT, vecData;
	for (int i = 0; i < vecOldMD.size(); ++i)
	{
		if (vecOldMD[i] < vecInMD.front() || vecOldMD[i] > vecInMD.back())
			continue;

		vecMD.push_back(vecOldMD[i]);
		vecTWT.push_back(vecOldTWT[i]);
	}

	if (vecMD.empty())
		return false;

	vecData.resize(vecMD.size());
	NXUtility::ReSample(vecInMD.size(), &vecInMD[0], &vecInData[0], vecMD.size(), &vecMD[0], &vecData[0], g_dInvalidData, true);


	// search minimum time interval
	int nSize = (int)vecTWT.size();
	double dTWTInterval = vecTWT[1] - vecTWT[0];
	for (int i = 1; i < nSize; ++i)
	{
		if (vecTWT[i] - vecTWT[i - 1] < dTWTInterval)
			dTWTInterval = vecTWT[i] - vecTWT[i - 1];
	}
	dTWTInterval /= 4;

	// evenly distributed twt
	double dTWTStart = vecTWT[0];
	int nNewSize = static_cast<int>((vecTWT.back() - dTWTStart) / dTWTInterval) + 1;
	vector<double> vecNewTWT(nNewSize), vecNewMD(nNewSize);
	for (int i = 0; i < nNewSize; ++i)
		vecNewTWT[i] = dTWTStart + i*dTWTInterval;

	NXUtility::ReSample(vecTWT.size(), &vecTWT[0], &vecMD[0], vecNewTWT.size(), &vecNewTWT[0], &vecNewMD[0], g_dInvalidData, true);

	// get new value
	vector<double> vecNewData(vecNewMD.size());
	NXUtility::ReSample(vecMD.size(), &vecMD[0], &vecData[0], vecNewMD.size(), &vecNewMD[0], &vecNewData[0], g_dInvalidData, true);

	// filter
	int nLength = (int)vecNewData.size();
	int nFFTSize = NXUtility::LengthofFFT(nLength*2);
	vector<double> vecFFTBuffer(2 * nFFTSize), vecH1(nFFTSize), vecH2(nFFTSize), vecOutput(nLength);
	double dFreq = 1000.f / dTWTInterval;

	if (nType == 1) // low pass
	{
		NXUtility::DigitalFilter(nLength, &vecNewData[0], &vecOutput[0], dTWTInterval, 0, 0, lowPassFreq, lowPassOvap, &vecFFTBuffer[0], &vecH1[0], &vecH2[0]);			
	}
	else if (nType == 2) // band pass)
	{
		NXUtility::DigitalFilter(nLength, &vecNewData[0], &vecOutput[0], dTWTInterval, highPassFreq, highPassOvap, lowPassFreq, lowPassOvap, &vecFFTBuffer[0], &vecH1[0], &vecH2[0]);		
	}
	else if (nType == 3) // high pass
	{
		NXUtility::DigitalFilter(nLength, &vecNewData[0], &vecOutput[0], dTWTInterval, highPassFreq, highPassOvap, 0, 0, &vecFFTBuffer[0], &vecH1[0], &vecH2[0]);
	}

	// resampling to original data
	CXCubicSpline spline(nLength, &vecNewMD[0], &vecOutput[0]);
	for (int i = 0; i < nSamplingNum; ++i)
	{
		double dMD = dStart + i*dStep;
		if (qAbs(pData[i] - g_dInvalidData) < fEPSInv)
			pBuffer[i] = g_dInvalidData;
		else if (dMD < vecNewMD.front() || dMD > vecNewMD.back())
			pBuffer[i] = g_dInvalidData;
		else
		{
			pBuffer[i] = spline.GetY(dMD);
		}
	}

	return true;
}
