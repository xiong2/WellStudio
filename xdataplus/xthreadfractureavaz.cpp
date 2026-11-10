#pragma warning( push ,0 )
#include "xthreadfractureavaz.h"
#include "xparameterfractureavo.h"
#include "xseismicdatavolume.h"
#include "xasynregularwriter.h"
#include "xprestackasynreader.h"
#include "xavazruger.h"
#include "xavazfcs.h"
#include <QCoreApplication>
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xutility.h"
#include <qtconcurrentmap.h>
#include <qfile.h>
#include "mkl.h"

#pragma warning( pop )

// in order to use qtconcurrent
void CalculateAVAZMethod(CXAVAZRuger* pCalculation)
{
	pCalculation->Calculate2();
}
void CalculateAVAZMethodFC(CXAVAZFCs* pCalculation)
{
	pCalculation->Calculate2();
}

CXThreadFractureAVAZ::CXThreadFractureAVAZ(CXParameterFractureAVO* pPara)
{
	m_pPara = pPara;
	m_pAziDV = nullptr;

	_Init();
}

CXThreadFractureAVAZ::~CXThreadFractureAVAZ()
{
	wait();

	if (m_pAziDV)
		UnlockRead(m_pAziDV);

	if (IsStopped())
	{
		for (int i = 0; i < m_vecOutputDV.size(); ++i)
		{
			QFile::remove(m_vecOutputDV[i]->GetTraceFileName());
		}
		qDeleteAll(m_vecOutputDV);
		m_vecOutputDV.clear();
	}

	qDeleteAll(m_listMethod);
	m_listMethod.clear();

	qDeleteAll(m_listMethodFC);
	m_listMethodFC.clear();
}

void CXThreadFractureAVAZ::_Init()
{
	m_pAziDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetAzimuthDVID()));

	if (m_pAziDV)
		LockRead(m_pAziDV);
}


bool CXThreadFractureAVAZ::_CreateDV()
{
	if (!m_pAziDV)
	{
		this->EmitGeneralErrorMsg("There is no valid seismic data volume.");
		return false;
	}

	m_utm = m_pAziDV->GetUTM();;


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

void CXThreadFractureAVAZ::_Calculate()
{
	this->EmitSetTaskName("Calculating");
	QCoreApplication::instance()->processEvents();

	int nMinimumFold = m_pPara->GetMinimumFold();
	int nMaxFold = m_pAziDV->GetMaxFold();

	// new dimension
	int nI = m_vecOutputDV[0]->GetInlineQty();
	int nJ = m_vecOutputDV[0]->GetXlineQty();
	int nK = m_vecOutputDV[0]->GetSamplingQty();

	// reader
	int nHalfWinI = qMax(0, m_pPara->GetDy() / 2);
	int nHalfWinJ = qMax(0, m_pPara->GetDx() / 2);
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_vecOutputDV[0]->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	CXPrestackAsynReader reader(m_pAziDV, nHalfWinI, nHalfWinJ);
	if (!reader.Init(dSamplingStart, nK))
	{
		this->EmitMemoryNotEnough();
		return;
	}

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

	CXParameterFractureAVO::EMethodType eMethod = (CXParameterFractureAVO::EMethodType)m_pPara->GetMethodType();
	
	int nWinSize = (2 * nHalfWinI + 1)*(2 * nHalfWinJ + 1);
	vector<float> vecGather(nK*nMaxFold*nWinSize), vecOffAzi(2 * nMaxFold*nWinSize), vecBani(nK), vecAzi(nK);
	for (int i = 0; i < vecPair.size(); ++i)
	{
		if (eMethod == CXParameterFractureAVO::eRuger)
		{
			CXAVAZRuger* pMethod = new CXAVAZRuger(nK, nMaxFold);
			pMethod->InitInputData(vecPair[i].first, vecPair[i].second, &vecGather[0], &vecOffAzi[0]);
			if (!pMethod->InitOutputData(&vecBani[0], &vecAzi[0]))
			{
				this->EmitMemoryNotEnough();
				return;
			}
			m_listMethod.append(pMethod);
		}
		else if (eMethod == CXParameterFractureAVO::eFCs)
		{
			CXAVAZFCs* pMethod = new CXAVAZFCs(nK, nMaxFold, m_pPara->GetIncidenceAngle());
			pMethod->InitInputData(vecPair[i].first, vecPair[i].second, &vecGather[0], &vecOffAzi[0]);
			if (!pMethod->InitOutputData(&vecBani[0], &vecAzi[0]))
			{
				this->EmitMemoryNotEnough();
				return;
			}
			m_listMethodFC.append(pMethod);
		}
	}


	// calc
	int iInline, iXline, iInlineNext, iXlineNext, nFold, iNext, jNext;
	vector<float*> vecOutData;
	vecOutData.push_back(&vecBani[0]);
	vecOutData.push_back(&vecAzi[0]);

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

			// calculating
			if (eMethod == CXParameterFractureAVO::eRuger)
			{
				for (int iMethod = 0; iMethod < m_listMethod.size(); ++iMethod)
				{
					m_listMethod[iMethod]->SetFold(nFold);
				}

				// calculate			
				QtConcurrent::blockingMap<QList<CXAVAZRuger*> >(m_listMethod, CalculateAVAZMethod);
			}
			else if (eMethod == CXParameterFractureAVO::eFCs)
			{
				for (int iMethod = 0; iMethod < m_listMethodFC.size(); ++iMethod)
				{
					m_listMethodFC[iMethod]->SetFold(nFold);
				}

				// calculate			
				QtConcurrent::blockingMap<QList<CXAVAZFCs*> >(m_listMethodFC, CalculateAVAZMethodFC);
			}

			//writing
			writer.WaitWriteData();
			writer.WriteData(vecOutData, nK);
		}
	}

	reader.StopThread();
	writer.WaitWriteData();
	writer.StopThread();

}

void CXThreadFractureAVAZ::_CalcMinMax(int nThread, int nK, vector<QPair<int, int> > & vecPair)
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
		for (int i = 0; i < nThread-1; ++i)
		{
			vecPair.push_back(qMakePair(i*kStep, (i+1)*kStep-1));
		}
		vecPair.push_back(qMakePair((nThread-1)*kStep, nK - 1));
	}
}

void CXThreadFractureAVAZ::RunThread()
{
	mkl_set_num_threads(1);

	this->EmitSetWindowName("AVAz Analysis");
	this->EmitSetTaskName("Calculating");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();


	if (!_CreateDV())
		return;

	_Calculate();
}



