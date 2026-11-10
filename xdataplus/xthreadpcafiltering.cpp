#pragma warning( push ,0 )
#include "xthreadpcafiltering.h"
#include "xparameterpcafiltering.h"
#include "xseismicdatavolume.h"
#include <QCoreApplication>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>
#include "xglobal.h"
#include "xmathmacro.h"
#include "xproject.h"
#include "xutility.h"
#include "xmethodpcafiltering.h"
#include <QFile>
#include "xregulardatareader.h"
#include "xregulardatawriter.h"
#include "xsysteminfo.h"
#include <qtconcurrentmap.h>

#pragma warning( pop )

// in order to use qt concurrent
void CalculatePCAFiltering(CXMethodPCAFiltering* pCalculation)
{
	pCalculation->Calculate();
}


CXThreadPCAFiltering::CXThreadPCAFiltering(CXParameterPCAFiltering* pPara, CXSeismicDataVolume* pDV)
{
	m_pPara = pPara;
	m_pInDV = pDV;

	m_pReader = NULL;
	m_pWriter = NULL;
	m_pOutDV = NULL;

	_Init();
}

CXThreadPCAFiltering::~CXThreadPCAFiltering()
{
	wait();

	// unlock object
	if (m_pInDV)	UnlockRead(m_pInDV);

	if (m_pReader)	delete m_pReader;
	if (m_pWriter)	delete m_pWriter;
	
	if (IsStopped())
	{
		if (m_pOutDV)
		{
			QFile::remove(m_pOutDV->GetTraceFileName());
			delete m_pOutDV;

		}
	}
}

void CXThreadPCAFiltering::_Init()
{
	if (!m_pInDV)
	{
		m_pInDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetDVID()));
	}
}

bool CXThreadPCAFiltering::_GetReaders()
{
	// seismic
	if (m_pInDV)
	{
		m_pReader = new CXRegularDataReader<float>(m_pInDV->GetTraceFileName(), m_pInDV->GetInlineQty(),
			m_pInDV->GetXlineQty(), m_pInDV->GetSamplingQty());

		if (!m_pReader->Open())
		{
			this->EmitGeneralErrorMsg("Cannot open the seismic data file.");
			return false;
		}
	}

	return true;
}

bool CXThreadPCAFiltering::_CreateDV()
{
	CXSeismicUTMTool utm = m_pInDV->GetUTM();

	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	iInlineMin = m_pPara->GetMinInlineNum();
	iInlineMax = m_pPara->GetMaxInlineNum();
	iInlineInc = m_pPara->GetInlineInc();
	iXlineMin = m_pPara->GetMinXlineNum();
	iXlineMax = m_pPara->GetMaxXlineNum();
	iXlineInc = m_pPara->GetXlineInc();

	int nInlineNum = (iInlineMax - iInlineMin) / iInlineInc + 1;
	int nXlineNum = (iXlineMax - iXlineMin) / iXlineInc + 1;

	utm.Resize(iInlineMin, iXlineMin, nInlineNum, nXlineNum);

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pInDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	// output
	m_pOutDV = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, m_pInDV->GetObjectName()+"_filtering");

	//writer
	m_pWriter = new CXRegularDataWriter<float>(m_pOutDV->GetTraceFileName(), nInlineNum, nXlineNum, m_pOutDV->GetSamplingQty());
	if (!m_pWriter->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the file to write data.");
		return false;
	}

	if (IsStopped())
		return false;

	return true;
}

bool CXThreadPCAFiltering::_ReadData(int iIndex, int nIold, int nJold, int nK, int jMin, int jMax, int nWinNI, float* pInData, float* pTmpBuff, int& nTrueWinNI)
{
	int nJ = jMax - jMin + 1;
	int nHalfWinNI = nWinNI / 2;
	int iMin = qMax(0, iIndex - nHalfWinNI);
	int iMax = qMin(nIold - 1, iIndex + nHalfWinNI);
	nTrueWinNI = iMax - iMin + 1;

	QList<int> listIndexNew;
	for (int i = iMin; i <= iMax; ++i)
	{
		// already in the memory
		int index = m_listIndex.indexOf(i);
		if (index >= 0 )
		{
			if (index != i - iMin)
			{
				memcpy(pInData + (i - iMin)*nJ*nK, pInData + index*nJ*nK, sizeof(float)*nJ*nK);
			}			
		}
		else
		{
			if (!m_pReader->ReadUSection(i, pTmpBuff))
			{			
				return false;
			}
			if (nJ == nJold)
				memcpy(pInData + (i - iMin)*nJ*nK, pTmpBuff, sizeof(float)*nJ*nK);
			else
			{
				float* pData = pInData + (i - iMin)*nJ*nK;
				for (int j = jMin; j <= jMax; ++j)
				{
					memcpy(pData + (j - jMin)*nK, pTmpBuff + j*nK, sizeof(float)*nK);
				}
			}
		}
		listIndexNew.append(i);
	}

	m_listIndex = listIndexNew;
	return true;
}

bool CXThreadPCAFiltering::_GetOutputIndex(int nThreadNum, int iThreadIndex, int nJ, int& jMin, int& jMax)
{
	int nJStep = nJ / nThreadNum;

	if (nJStep == 0)
	{
		if (iThreadIndex < nJ)
		{
			jMin = iThreadIndex;
			jMax = iThreadIndex;
		}
		else
		{
			jMin = -1;			
			jMax = -1;
		}
	}
	else
	{
		jMin = iThreadIndex*nJStep;

		if (iThreadIndex != nThreadNum - 1)
		{
			jMax = (iThreadIndex + 1)*nJStep - 1;
		}
		else
		{
			jMax = nJ - 1;
		}
	}

	if (jMin < 0 || jMax < 0)
		return false;
	else
		return true;

}

void CXThreadPCAFiltering::_Calc()
{
	// input dv
	CXSeismicUTMTool utm = m_pInDV->GetUTM();

	int iInlineMin, iInlineMax, iXlineMin, iXlineMax;
	iInlineMin = m_pPara->GetMinInlineNum();
	iInlineMax = m_pPara->GetMaxInlineNum();
	iXlineMin = m_pPara->GetMinXlineNum();
	iXlineMax = m_pPara->GetMaxXlineNum();


	double dSamplingStartDV, dSamplingEndDV, dSamplingRateDV;
	m_pInDV->GetSamplingRange(dSamplingStartDV, dSamplingEndDV, dSamplingRateDV);

	int nIOld = utm.GetNI();
	int nJOld = utm.GetNJ();
	int nKOld = m_pInDV->GetSamplingQty();
	int iMin = (iInlineMin - utm.GetFirstInline()) / utm.GetInlineIncrement();
	int iMax = (iInlineMax - utm.GetFirstInline()) / utm.GetInlineIncrement();
	int jMin = (iXlineMin - utm.GetFirstCrossline()) / utm.GetCrosslineIncrement();
	int jMax = (iXlineMax - utm.GetFirstCrossline()) / utm.GetCrosslineIncrement();

	int nI = iMax - iMin + 1;
	int nJ = jMax - jMin + 1;
	int nK = nKOld;
	int nWinNI = qMin(m_pPara->GetWinNI(), nI) / 2 * 2 + 1;
	int nWinNJ = qMin(m_pPara->GetWinNJ(), nJ) / 2 * 2 + 1;
	if (nWinNI > nI)
		nWinNI -= 2;
	if (nWinNJ > nJ)
		nWinNJ -= 2;

	// data buffers
	std::vector<float> vecSection(nJOld*nKOld), vecInData(nWinNI*nJ*nK), vecOutData(nJ*nK);

	// init methods
	int nThreadNum = QThread::idealThreadCount();
	QList<CXMethodPCAFiltering*> listMethod;
	for (int iThread = 0; iThread < nThreadNum; ++iThread)
	{
		int joutmin, joutmax;
		if (!_GetOutputIndex(nThreadNum, iThread, nJ, joutmin, joutmax))
			continue;

		CXMethodPCAFiltering* pMethod = new CXMethodPCAFiltering(nJ, nK, joutmin, joutmax, nWinNI, nWinNJ);
		pMethod->SetBuffers(&vecInData[0], &vecOutData[0]);
		listMethod.append(pMethod);
	}

	// calc
	for (int i = 0; i < nI; ++i)
	{
		if (IsStopped())
		{
			qDeleteAll(listMethod);
		}
		else
		{
			this->EmitUpdateProgress(i, nI);
		}

		// read
		int index = i + iMin;
		int nTrueWinNI;
		if (!_ReadData(index, nIOld, nJOld, nK, jMin, jMax, nWinNI, &vecInData[0], &vecSection[0], nTrueWinNI))
		{
			this->EmitGeneralErrorMsg("Cannot read the seismic data.");
			return;
		}

		for (int iMethod = 0; iMethod < listMethod.size(); ++iMethod)
			listMethod[iMethod]->SetTrueWinNI(nTrueWinNI);


		// calculate			
		QtConcurrent::blockingMap<QList<CXMethodPCAFiltering*> >(listMethod, CalculatePCAFiltering);

		//write
		m_pWriter->Append(nK*nJ, &vecOutData[0]);
	}

	qDeleteAll(listMethod);
}

void CXThreadPCAFiltering::RunThread()
{
	if (!m_pInDV)
	{
		this->EmitGeneralErrorMsg("The selected seismic data volume has been deleted.");
		return;
	}

	this->EmitSetWindowName("PCA Filtering");
	this->EmitSetTaskName("Calculating...");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	if (!_GetReaders())
		return;

	if (!_CreateDV())
		return;

	_Calc();

}



