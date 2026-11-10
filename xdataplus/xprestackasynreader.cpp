#include "xprestackasynreader.h"
#include "xseismicdatavolume.h"
#include "xglobal.h"

CXPrestackAsynReader::CXPrestackAsynReader(CXSeismicDataVolume* pDV, int nHalfWinI, int nHalfWinJ) :
	m_pDV(pDV), m_nHalfWinI(nHalfWinI), m_nHalfWinJ(nHalfWinJ)
{
	m_nFold = 0;

	m_bStop = false;
}

CXPrestackAsynReader::~CXPrestackAsynReader()
{
	wait();

	for (int i = 0; i < m_vecpGatherBuff.size(); ++i)
		delete[]m_vecpGatherBuff[i];
	m_vecpGatherBuff.clear();

	for (int i = 0; i < m_vecpOffAziBuff.size(); ++i)
		delete[]m_vecpOffAziBuff[i];
	m_vecpOffAziBuff.clear();

	delete []m_pGather;
	delete []m_pOffAzi;

}

void CXPrestackAsynReader::StopThread()
{
	m_Mutex.lock();
	m_bStop = true;
	m_bStartReading = true;
	m_Condition.wakeOne();
	m_Mutex.unlock();

	this->wait();
}

bool CXPrestackAsynReader::Init(double dSamplingStart, int nK)
{
	if (!m_pDV)
		return false;

	m_nK = nK;
	
	m_utm = m_pDV->GetUTM();

	double dSamplingStartDV, dSamplingEndDV, dSamplingRateDV;
	m_pDV->GetSamplingRange(dSamplingStartDV, dSamplingEndDV, dSamplingRateDV);
	m_nKDV = m_pDV->GetSamplingQty();
	m_iKOffset = static_cast<int>((dSamplingStart- dSamplingStartDV)/ dSamplingRateDV + 0.01);

	m_nMaxFold = m_pDV->GetMaxFold();

	int nWinSize = (2 * m_nHalfWinI + 1)*(2 * m_nHalfWinJ + 1);
	try
	{
		for (int i = 0; i < nWinSize; ++i)
		{
			float* pGather = new float[m_nK*m_nMaxFold];
			float* pOffAzi = new float[m_nMaxFold * 2];

			m_vecpGatherBuff.push_back(pGather);
			m_vecpOffAziBuff.push_back(pOffAzi);
		}

		// *2 : merged gather fold may be great than the max fold
		m_pGather = new float[nWinSize*m_nKDV*m_nMaxFold];
		m_pOffAzi = new float[nWinSize*m_nMaxFold * 2];
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	return true;
}

void CXPrestackAsynReader::WaitReadData()
{
	m_Semaphore.acquire();
}

void CXPrestackAsynReader::ReadData(int iInline, int iXline, float* pOutGather, float* pOutOffAZi, int* pFold, int iInlineNext, int iXlineNext)
{
	QMutexLocker locker(&m_Mutex);

	m_iInline = iInline;
	m_iXline = iXline;

	m_pOutGather = pOutGather;
	m_pOutOffAzi = pOutOffAZi;
	m_pFold = pFold;

	m_iInlineNext = iInlineNext;
	m_iXlineNext = iXlineNext;

	if (!isRunning())
	{
		m_bStartReading = true;
		start();
	}
	else
	{
		m_bStartReading = true;
		m_Condition.wakeOne();
	}

}

void CXPrestackAsynReader::run()
{
	for (;;)
	{
		m_Mutex.lock();
		while (!m_bStartReading)
			m_Condition.wait(&m_Mutex);
		m_Mutex.unlock();

		if (m_bStop)
			break;

		if (m_nFold == 0)
		{
			_ReadAndStackData();
		}

		memcpy(m_pOutGather, m_pGather, sizeof(float)*m_nFold*m_nK);
		memcpy(m_pOutOffAzi, m_pOffAzi, sizeof(float)*m_nFold * 2);
		*m_pFold = m_nFold;
		m_nFold = 0;


		m_Mutex.lock();
		m_bStartReading = false;
		m_Mutex.unlock();
		m_Semaphore.release();

		if (m_bStop)
			break;

		// next reading cycle
		m_iInline = m_iInlineNext;
		m_iXline = m_iXlineNext;

		_ReadAndStackData();

	}

	m_Semaphore.release();
}

bool CXPrestackAsynReader::_ReadAndStackData()
{	
	int i, j;
	if (!m_utm.LineToIJ(m_iInline, m_iXline, i, j))
		return false;

	int nI = m_utm.GetNI();
	int nJ = m_utm.GetNJ();

	int iMin = qBound(0, i - m_nHalfWinI, nI - 1);
	int iMax = qBound(0, i + m_nHalfWinI, nI - 1);
	int jMin = qBound(0, j - m_nHalfWinJ, nJ - 1);
	int jMax = qBound(0, j + m_nHalfWinJ, nJ - 1);

	
	m_mapIndex.clear();
	m_mapFold.clear();

	QList<int> listPotential;
	for (i = 0; i < m_vecpGatherBuff.size(); ++i)
		listPotential.append(i);

	int iInline, iXline;
	// already in the memory
	for (i = iMin; i <= iMax; ++i)
	{
		for (j = jMin; j <= jMax; ++j)
		{
			m_utm.IJToLine(i, j, iInline, iXline);

			QPair<int, int> pairKey = qMakePair(iInline, iXline);
			if (m_mapPreIndex.contains(pairKey))
			{
				int index = m_mapPreIndex.value(pairKey);
				m_mapIndex.insert(pairKey, index);
				m_mapFold.insert(pairKey, m_mapPreFold.value(pairKey));
				listPotential.removeOne(index);
			}
		}
	}

	// not in the memory
	QVector<float> vecOffAzi;
	for (i = iMin; i <= iMax; ++i)
	{
		for (j = jMin; j <= jMax; ++j)
		{
			m_utm.IJToLine(i, j, iInline, iXline);

			QPair<int, int> pairKey = qMakePair(iInline, iXline);
			if (m_mapIndex.contains(pairKey))
				continue;

			int iPotentialIndex = listPotential.front();
			listPotential.pop_front();
			vecOffAzi.clear();
			
			if (!m_pDV->GetTraceDataAt(iInline, iXline, m_pGather, vecOffAzi))
				return false;			

			int nFold = vecOffAzi.size() / 2;

			if (nFold == 0)
				continue;
	
			for (int iFold = 0; iFold < nFold; ++iFold)
				memcpy(m_vecpGatherBuff[iPotentialIndex] + iFold*m_nK, m_pGather + iFold*m_nKDV + m_iKOffset, sizeof(float)*m_nK);

			memcpy(m_vecpOffAziBuff[iPotentialIndex], &vecOffAzi[0], sizeof(float)*nFold * 2);

			m_mapIndex.insert(pairKey, iPotentialIndex);
			m_mapFold.insert(pairKey, nFold);
		}
	}

	_StackData();	

	m_mapPreIndex = m_mapIndex;
	m_mapPreFold = m_mapFold;

	return true;
}

void CXPrestackAsynReader::_StackData()
{
	// Get the position <Offset, Azi>
	QMultiMap<QPair<float, float>, int> mapPosition;

	QMap<QPair<int, int>, int>::iterator it;
	for (it = m_mapIndex.begin(); it != m_mapIndex.end(); ++it)
	{
		int iGatherIndex = it.value();
		int nGatherFold = m_mapFold.value(it.key());
		float* pOffsetAzi = m_vecpOffAziBuff[iGatherIndex];

		for (int iFold = 0; iFold < nGatherFold; ++iFold)
		{
			mapPosition.insert(qMakePair(pOffsetAzi[2*iFold], pOffsetAzi[2 * iFold+1]), iGatherIndex*m_nMaxFold+ iFold);
		}
	}

	// stack
	float fInvalid = ::g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	QList<QPair<float, float> > listKey = mapPosition.uniqueKeys();
	int iCount = 0;
	for (int i=0; i<listKey.size(); ++i)
	{
		m_pOffAzi[iCount * 2] = listKey.at(i).first;
		m_pOffAzi[iCount * 2 + 1] = listKey.at(i).second;
		float* pTrace = m_pGather + iCount*m_nK;

		QList<int> listPos = mapPosition.values(listKey.at(i));
		int nPosNum = listPos.size();

		double dSum;
		float fValue;
		int iTotalNum;
		for (int k = 0; k < m_nK; ++k)
		{
			dSum = 0;
			iTotalNum = 0;

			for (int iIndex = 0; iIndex < nPosNum; ++iIndex)
			{
				int iGatherIndex = listPos[iIndex] / m_nMaxFold;
				int iFold = listPos[iIndex] % m_nMaxFold;

				fValue = *(m_vecpGatherBuff[iGatherIndex] + iFold*m_nK + k);
				if (fValue == 0 || qAbs(fValue - fInvalid) < fInvalidEPS)
					continue;

				dSum += fValue;
				++iTotalNum;
			}
			if (iTotalNum == 0)
				pTrace[k] = fInvalid;
			else
				pTrace[k] = static_cast<float>(dSum / iTotalNum);
		}
		++iCount;
	}

	m_nFold = iCount;
}
