#pragma warning( push ,0 )
#include "xthreadfractureattribute.h"
#include "xparameterfractureattribute.h"
#include "xseismicdatavolume.h"
#include "xasynregularwriter.h"
#include "xprestackasynreader.h"
#include <QCoreApplication>
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xutility.h"
#include <qtconcurrentmap.h>
#include <qfile.h>
#include "mkl.h"
#include "xmathmacro.h"
#include <cmath>
#include "xfractureattributeone.h"
#include "xregulardatareader.h"
#include "xfunctiontemplate.h"
#include "xutility.h"

#pragma warning( pop )


void Calculate(CXFractureAttributeOne* pMethod)
{
	pMethod->Calculate();
}


CXThreadFractureAttribute::CXThreadFractureAttribute(CXParameterFractureAttribute* pPara)
{
	m_pPara = pPara;
	m_pInDV = nullptr;

	m_pFFTBuffer = nullptr;
	m_pH1 = nullptr;
	m_pH2 = nullptr;
	m_pFFTOut1 = nullptr;
	m_pFFTOut2 = nullptr;

	_Init();
}

CXThreadFractureAttribute::~CXThreadFractureAttribute()
{
	wait();

	delete []m_pFFTBuffer;
	delete []m_pH1;
	delete []m_pH2;
	delete []m_pFFTOut1;
	delete []m_pFFTOut2;

	if (m_pInDV)
		UnlockRead(m_pInDV);

	// lfm
	for (int i = 0; i < m_vecLFMDV.size(); ++i)
		UnlockRead(m_vecLFMDV[i]);

	// readers
	qDeleteAll(m_vecLFMReader);
	m_vecLFMReader.clear();

	if (IsStopped())
	{
		for (int i = 0; i < m_vecOutputDV.size(); ++i)
		{
			QFile::remove(m_vecOutputDV[i]->GetTraceFileName());
		}
		qDeleteAll(m_vecOutputDV);
		m_vecOutputDV.clear();
	}
}

void CXThreadFractureAttribute::_Init()
{
	m_pInDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetAzimuthDVID()));

	if (m_pInDV)
		LockRead(m_pInDV);
}


bool CXThreadFractureAttribute::_CreateDV()
{
	if (!m_pInDV)
	{
		this->EmitGeneralErrorMsg("There is no valid seismic data volume.");
		return false;
	}

	m_utmIn = m_pInDV->GetUTM();
	m_utm = m_utmIn;;


	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	double dSamplingStart, dSamplingEnd, dSamplingRate;

	iInlineMin = m_pPara->GetMinInlineNum();
	iInlineMax = m_pPara->GetMaxInlineNum();
	iInlineInc = m_pPara->GetInlineInc();
	iXlineMin = m_pPara->GetMinXlineNum();
	iXlineMax = m_pPara->GetMaxXlineNum();
	iXlineInc = m_pPara->GetXlineInc();

	dSamplingStart = m_pPara->GetSamplingStart();
	dSamplingEnd = m_pPara->GetSamplingEnd();
	dSamplingRate = m_pPara->GetSamplingRate();

	int nInlineNum = (iInlineMax - iInlineMin) / iInlineInc + 1;
	int nXlineNum = (iXlineMax - iXlineMin) / iXlineInc + 1;
	m_utm.Resize(iInlineMin, iXlineMin, nInlineNum, nXlineNum);
	int nK = static_cast<int>((dSamplingEnd - dSamplingStart) / dSamplingRate + 0.01) + 1;


	// two output DVs
	QStringList listDVName;
	listDVName << "Bani" << "Azimuth";

	for (int i = 0; i < listDVName.size(); ++i)
	{
		CXSeismicDataVolume* pNewDv = new CXSeismicDataVolume(m_utm, dSamplingStart, dSamplingEnd, dSamplingRate, listDVName[i]);
		m_vecOutputDV.push_back(pNewDv);
	}

	if (IsStopped())
		return false;
	else
		return true;
}

bool CXThreadFractureAttribute::_GetAzimuth()
{
	int iInline, iXline;
	m_utm.IJToLine(0, 0, iInline, iXline);

	int nK = m_pInDV->GetSamplingQty();
	int nMaxFold = m_pInDV->GetMaxFold();
	vector<float> vecGather(nK*nMaxFold);
	QVector<float> vecOffAzi;
	m_pInDV->GetTraceDataAt(iInline, iXline, &vecGather[0], vecOffAzi);
	if (vecOffAzi.isEmpty())
		return false;

	for (int i = 1; i < vecOffAzi.size(); i += 2)
		m_vecAzimuth.push_back(vecOffAzi[i]);

	return true;
}

void CXThreadFractureAttribute::_Calculate()
{
	this->EmitSetTaskName("Calculating");
	QCoreApplication::instance()->processEvents();

	int nMinimumFold = m_pPara->GetMinimumFold();
	int nMaxFold = m_pInDV->GetMaxFold();

	// new dimension
	int nI = m_vecOutputDV[0]->GetInlineQty();
	int nJ = m_vecOutputDV[0]->GetXlineQty();
	int nK = m_vecOutputDV[0]->GetSamplingQty();

	// reader
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_vecOutputDV[0]->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	CXPrestackAsynReader reader(m_pInDV, 0, 0);
	if (!reader.Init(dSamplingStart, nK))
	{
		this->EmitMemoryNotEnough();
		return;
	}

	// K offset
	double dSamplingStart1, dSamplingEnd1, dSamplingRate1;
	m_pInDV->GetSamplingRange(dSamplingStart1, dSamplingEnd1, dSamplingRate1);
	int kOffset = static_cast<int>((dSamplingStart1 - dSamplingStart) / dSamplingRate + 0.01);
	int nKAziDV = m_pInDV->GetSamplingQty();


	// Writer
	QStringList listFileName;
	for (int i = 0; i < m_vecOutputDV.size(); ++i)
		listFileName << m_vecOutputDV[i]->GetTraceFileName();
	CXAsynRegularWriter writer(listFileName, nI, nJ, nK, nK);
	if (!writer.Init())
	{
		this->EmitGeneralErrorMsg("Cannot open the file to write.");
		return;
	}

	//method
	vector<QPair<int, int> > vecPair;
	int nThread = m_pPara->GetCPUNumber();
	_CalcMinMax(nThread, nK, vecPair);
	
	vector<float> vecGather(nK*nMaxFold), vecOffAzi(2 * nMaxFold), vecBani(nK), vecAzi(nK);
	
	//// test codes
	//vector<float> vecBaniF(nK), vecAziF(nK);

	QList<CXFractureAttributeOne*> listMethod;
	for (int i = 0; i < vecPair.size(); ++i)
	{
		CXFractureAttributeOne* pMethod = new CXFractureAttributeOne(nK);
		pMethod->InitMethod(m_vecAzimuth.size(), 4, 100);
		pMethod->InitInputData(vecPair[i].first, vecPair[i].second, &vecGather[0], &m_vecAzimuth[0]);
		pMethod->InitOutputData(&vecBani[0], &vecAzi[0]);
		listMethod.append(pMethod);
	}

	// calc
	int iInline, iXline, iInlineNext, iXlineNext, nFold, iNext, jNext;
	vector<float*> vecOutData;	
	vecOutData.push_back(&vecBani[0]);
	vecOutData.push_back(&vecAzi[0]);

	//// test codes
	//vecOutData.push_back(&vecBaniF[0]);
	//vecOutData.push_back(&vecAziF[0]);

	bool bBreak = false;
	for (int i = 0; i < nI; ++i)
	{
		if (bBreak)
			break;

		for (int j = 0; j < nJ; ++j)
		{
			if (IsStopped())
			{
				bBreak = true;
				break;
			}
			else
			{
				this->EmitUpdateProgress(i*nJ + j, nI*nJ);
			}

			m_utm.IJToLine(i, j, iInline, iXline);

			// next indice
			iNext = i;
			jNext = j + 1;
			if (jNext == nJ)
			{
				jNext = 0;
				++iNext;
			}
			if (iNext == nI)
			{
				iNext = -1;
				jNext = -1;
			}
			m_utm.IJToLine(iNext, jNext, iInlineNext, iXlineNext);
			if (iNext == -1)
			{
				iInlineNext = -1;
				iXlineNext = -1;
			}

			// reading
			reader.ReadData(iInline, iXline, &vecGather[0], &vecOffAzi[0], &nFold, iInlineNext, iXlineNext);
			reader.WaitReadData();

			// calculate			
			QtConcurrent::blockingMap<QList<CXFractureAttributeOne*> >(listMethod, Calculate);

			//if (m_bFilter)
			//{
			//	_Filtering(iInline, iXline, kOffset, nKAziDV, nK, vecOutData);

			//	// test codes

			//}

			//writing
			writer.WaitWriteData();
			writer.WriteData(vecOutData, nK);
		}
	}

	writer.WaitWriteData();
	reader.StopThread();
	writer.StopThread();

	qDeleteAll(listMethod);

}

void CXThreadFractureAttribute::_CalcMinMax(int nThread, int nK, vector<QPair<int, int> > & vecPair)
{
	int kStep = nK / nThread;
	if (kStep == 0)
	{
		for (int i = 0; i < nK; ++i)
		{
			vecPair.push_back(qMakePair(i, i));
		}
	}
	else
	{
		for (int i = 0; i < nThread - 1; ++i)
		{
			vecPair.push_back(qMakePair(i*kStep, (i + 1)*kStep - 1));
		}
		vecPair.push_back(qMakePair((nThread - 1)*kStep, nK - 1));
	}
}

bool CXThreadFractureAttribute::_InitFilters()
{
	m_bFilter = false;  m_pPara->GetApplyFiltering();
	if (!m_bFilter)
		return true;


	// Get input dvs
	CXSeismicDataVolume* pVpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetVpDVID()));
	CXSeismicDataVolume* pVsDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetVsDVID()));
	CXSeismicDataVolume* pEpsDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetEpsilonDVID()));
	CXSeismicDataVolume* pDeltaDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetDeltaDVID()));
	CXSeismicDataVolume* pGammaDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetGammaDVID()));
	CXSeismicDataVolume* pAziDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetAziSymDVID()));

	if (!pVpDV || !pVsDV || !pEpsDV || !pDeltaDV || !pGammaDV || !pAziDV)
	{
		this->EmitGeneralErrorMsg("One of selected low frequency model has been removed.");
		return false;
	}

	m_vecLFMDV.push_back(pVpDV);
	m_vecLFMDV.push_back(pVsDV);
	m_vecLFMDV.push_back(pEpsDV);
	m_vecLFMDV.push_back(pDeltaDV);
	m_vecLFMDV.push_back(pGammaDV);
	m_vecLFMDV.push_back(pAziDV);

	//reader
	for (int i = 0; i < m_vecLFMDV.size(); ++i)
	{
		CXRegularDataReader<float>* pReader = new CXRegularDataReader<float>(m_vecLFMDV[i]->GetTraceFileName(), m_vecLFMDV[i]->GetInlineQty(),
			m_vecLFMDV[i]->GetXlineQty(), m_vecLFMDV[i]->GetSamplingQty());

		m_vecLFMReader.push_back(pReader);

		if (!pReader->Open())
		{
			this->EmitGeneralErrorMsg("Cannot open the low frequency model file.");
			return false;
		}
	}

	// lock objects
	for (int i = 0; i < m_vecLFMDV.size(); ++i)
		LockRead(m_vecLFMDV[i]);	

	int nK = m_vecLFMDV[0]->GetSamplingQty();
	m_vecEr.resize(nK);
	m_vecDr.resize(nK);
	m_vecGr.resize(nK);
	m_vecK.resize(nK);	
	m_vecLow.resize(nK);	
	m_vecBand.resize(nK);
	
	m_vecVp.resize(nK);
	m_vecVs.resize(nK);
	m_vecE.resize(nK);
	m_vecD.resize(nK);
	m_vecG.resize(nK);
	m_vecAzi.resize(nK);

	m_vecA.resize(nK);
	m_vecB1.resize(nK);
	m_vecB1Calc.resize(nK);
	m_vecACalc.resize(nK);

	// fft
	int nFFTSize = NXUtility::LengthofFFT(2 * nK);
	m_pFFTBuffer = new double[2 * nFFTSize];
	m_pH1 = new double[nFFTSize];
	m_pH2 = new double[nFFTSize];
	m_pFFTOut1 = new double[nK];
	m_pFFTOut2 = new double[nK];

	m_df1 = m_pPara->GetLowCut();
	m_df1ovp = m_pPara->GetLowOverlap();
	m_df2 = m_pPara->GetHighCut();
	m_df2ovp = m_pPara->GetHighOverlap();
	m_dt = m_pPara->GetSamplingRate();

	return true;
}

bool CXThreadFractureAttribute::_Filtering(int iInline, int iXline, int iKOffset, int nKAziDV, int nK, vector<float*>& vecData)
{
	// reading data
	int i, j;
	m_utmIn.LineToIJ(iInline, iXline, i, j);

	if (!m_vecLFMReader[0]->ReadUVTrace(i, j, &m_vecVp[0]) ||
		!m_vecLFMReader[1]->ReadUVTrace(i, j, &m_vecVs[0]) ||
		!m_vecLFMReader[2]->ReadUVTrace(i, j, &m_vecE[0]) ||
		!m_vecLFMReader[3]->ReadUVTrace(i, j, &m_vecD[0]) ||
		!m_vecLFMReader[4]->ReadUVTrace(i, j, &m_vecG[0]) ||
		!m_vecLFMReader[5]->ReadUVTrace(i, j, &m_vecAzi[0]))
	{
		this->EmitGeneralErrorMsg("Cannot read the low frequency model.");
		return false;
	}

	// calc kmin and max from input dv
	int kminIn(0), kmaxIn(nKAziDV - 1);
	_CalcKMinMax(nKAziDV, kminIn, kmaxIn);

	// calc kmin and kmax from output dv
	int kminOut(0), kmaxOut(nK - 1);
	_CalcKMinMax2(nK, kminOut, kmaxOut, vecData);

	int kmin = qMax(kminIn, kminOut + iKOffset);
	int kmax = qMin(kmaxIn, kmaxOut + iKOffset);

	int n = kmax - kmin + 1;
	if (n < 2)
		return true;

	// calc relative thomson parameters
	double dmean, dmean2;
	for (int k = kmin; k < kmax; ++k)
	{
		dmean = 0.5*(m_vecE[k] + m_vecE[k + 1]);
		m_vecEr[k- kmin] = (m_vecE[k] + 1. - dmean) / (1. - dmean);

		dmean = 0.5*(m_vecD[k] + m_vecD[k + 1]);
		m_vecDr[k - kmin] = (m_vecD[k] + 1. - dmean) / (1. - dmean);

		dmean = 0.5*(m_vecG[k] + m_vecG[k + 1]);
		m_vecGr[k - kmin] = (m_vecG[k] + 1. - dmean) / (1. - dmean);

		dmean = 0.5*(m_vecVp[k] + m_vecVp[k + 1]);
		dmean2 = 0.5*(m_vecVs[k] + m_vecVs[k + 1]);
		m_vecK[k - kmin] = SQR(dmean2 / dmean);

		m_vecA[k - kmin] = m_vecAzi[k];
	}

	m_vecEr[kmax - kmin] = 1;
	m_vecDr[kmax - kmin] = 1;
	m_vecGr[kmax - kmin] = 1;
	m_vecK[kmax - kmin] = m_vecK[kmax - kmin - 1];
	m_vecA[kmax - kmin] = m_vecAzi[kmax];

	// calc B1
	for (int i = 0; i < n; ++i)
	{
		m_vecB1[i] = 0.5*log(m_vecGr[i]) + 1. / (16.*m_vecK[i])*log(m_vecDr[i]) + (4 * m_vecK[i] - 1) / (16 * m_vecK[i])*log(m_vecEr[i]);
		m_vecB1Calc[i] = vecData[0][kmin + i - iKOffset];
		m_vecACalc[i] = vecData[1][kmin + i - iKOffset];
	}

	for (int k = 0; k < nK; ++k)
	{
		vecData[2][k] = (float)g_dInvalidData;
		vecData[3][k] = (float)g_dInvalidData;
	}
	for (int i = 0; i < n; ++i)
	{
		vecData[2][kmin + i - iKOffset] = m_vecB1[i];
		vecData[3][kmin + i - iKOffset] = m_vecA[i];
	}


	/*

	// B1
	// low pass
	NXUtility::DigitalFilter(n, &m_vecB1[0], m_pFFTOut1, m_dt, 0, 0, m_df1, m_df1ovp, m_pFFTBuffer, m_pH1, m_pH2);

	// band pass
	NXUtility::DigitalFilter(n, &m_vecB1Calc[0], m_pFFTOut2, m_dt, m_df1, m_df1ovp, m_df2, m_df2ovp, m_pFFTBuffer, m_pH1, m_pH2);

	for (int k = kmin; k <= kmax; ++k)
	{
		vecData[0][k - iKOffset] = static_cast<float>(m_pFFTOut1[k - kmin] + m_pFFTOut2[k - kmin]);
	}

	// Azi
	// low pass
	NXUtility::DigitalFilter(n, &m_vecA[0], m_pFFTOut1, m_dt, 0, 0, m_df1, m_df1ovp, m_pFFTBuffer, m_pH1, m_pH2);

	// band pass
	NXUtility::DigitalFilter(n, &m_vecACalc[0], m_pFFTOut2, m_dt, m_df1, m_df1ovp, m_df2, m_df2ovp, m_pFFTBuffer, m_pH1, m_pH2);

	for (int k = kmin; k <= kmax; ++k)
	{
		vecData[1][k - iKOffset] = static_cast<float>(m_pFFTOut1[k - kmin] + m_pFFTOut2[k - kmin]);
	}	

	*/

	return true;
	
}

void CXThreadFractureAttribute::_CalcKMinMax(int nK, int&kmin, int& kmax)
{
	float fInvalid = g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

	for (int k = 0; k < nK; ++k)
	{
		if (qAbs(m_vecVp[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecVs[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecE[k] - fInvalid) > fInvalidEPS && 
			qAbs(m_vecD[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecG[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecAzi[k] - fInvalid) > fInvalidEPS )
		{
			kmin = k;
			break;
		}
	}

	for (int k = nK - 1; k >= 0; --k)
	{
		if (qAbs(m_vecVp[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecVs[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecE[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecD[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecG[k] - fInvalid) > fInvalidEPS &&
			qAbs(m_vecAzi[k] - fInvalid) > fInvalidEPS)
		{
			kmax = k;
			break;
		}		
	}
}

void CXThreadFractureAttribute::_CalcKMinMax2(int nK, int&kmin, int& kmax, vector<float*>& vecData)
{
	float fInvalid = g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

	for (int k = 0; k < nK; ++k)
	{
		if (qAbs(vecData[0][k] - fInvalid) > fInvalidEPS &&
			qAbs(vecData[1][k] - fInvalid) > fInvalidEPS )
		{
			kmin = k;
			break;
		}
	}

	for (int k = nK - 1; k >= 0; --k)
	{
		if (qAbs(vecData[0][k] - fInvalid) > fInvalidEPS &&
			qAbs(vecData[1][k] - fInvalid) > fInvalidEPS)
		{
			kmax = k;
			break;
		}
	}
}

void CXThreadFractureAttribute::RunThread()
{
	mkl_set_num_threads(1);

	this->EmitSetWindowName("Calclature Fracture Attributes");
	this->EmitSetTaskName("Calculating");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();


	if (!_CreateDV())
		return;

	if (!_InitFilters())
		return;

	_GetAzimuth();

	_Calculate();
}




