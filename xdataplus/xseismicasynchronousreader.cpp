#include "xseismicasynchronousreader.h"
#include "xregulardatareader.h"

CXSeismicAsynchronousReader::CXSeismicAsynchronousReader(const QString& strFileName, int nI, int nJ, int nK, int nExpectedTraceNum):
m_nI(nI), m_nJ(nJ), m_nK(nK), m_nExpectedTraceNum(nExpectedTraceNum)
{
	m_pReader = new CXRegularDataReader<float>(strFileName, nI, nJ, nK);

	m_pCacheBuffer = NULL;

	m_bStop = false;	
}

CXSeismicAsynchronousReader::~CXSeismicAsynchronousReader()
{
	wait();

	delete[]m_pCacheBuffer;

	delete m_pReader;
}

void CXSeismicAsynchronousReader::StopThread()
{
	m_Mutex.lock();
	m_bStop = true;
	m_bStartReading = true;
	m_Condition.wakeOne();
	m_Mutex.unlock();

	this->wait();
}

bool CXSeismicAsynchronousReader::Init(int iMin, int iMax, int jMin, int jMax)
{
	m_iMin = iMin;
	m_iMax = iMax;
	m_jMin = jMin;
	m_jMax = jMax;

	m_iCurrentIndex = iMin*m_nJ + jMin;

	if (!m_pReader->Open())
		return false;

	try
	{
		m_pCacheBuffer = new float[m_nK*m_nExpectedTraceNum];
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	return true;	
}

void CXSeismicAsynchronousReader::WaitReadData()
{
	m_Semaphore.acquire();
}

void CXSeismicAsynchronousReader::ReadData(int* pTraceNum, float* pData)
{
	QMutexLocker locker(&m_Mutex);

	m_pTraceNum = pTraceNum;

	m_pInBuffer = pData;

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

bool CXSeismicAsynchronousReader::_ReadCacheData()
{
	for (int i = 0; i < m_listCacheIndex.size(); ++i)
	{
		int iI = m_iCurrentIndex / m_nJ;
		int iJ = m_iCurrentIndex % m_nJ;

		if (!m_pReader->ReadUVTrace(iI, iJ, m_pCacheBuffer + i*m_nK))
			return false;
	}

	return true;
}

void CXSeismicAsynchronousReader::_CalcCacheIndex()
{
	while (m_iCurrentIndex <= m_iMax*m_nJ + m_jMax && m_listCacheIndex.size() < m_nExpectedTraceNum)
	{
		int iI = m_iCurrentIndex / m_nJ;
		int iJ = m_iCurrentIndex % m_nJ;

		m_listCacheIndex.append(m_iCurrentIndex);

		if (iJ == m_jMax)
		{
			++iI;
			iJ = m_jMin;
			
		}
		else
		{
			++iJ;
		}
		m_iCurrentIndex = iI*m_nJ + m_jMin;
	}

}

void CXSeismicAsynchronousReader::run()
{
	forever
	{
		m_Mutex.lock();
		while (!m_bStartReading)
			m_Condition.wait(&m_Mutex);
		m_Mutex.unlock();

		if (m_bStop)
			break;

		if (m_listCacheIndex.isEmpty())
		{
			_CalcCacheIndex();
			_ReadCacheData();
		}
		else
		{
			memcpy(m_pInBuffer, m_pCacheBuffer, sizeof(double)*m_nK*m_listCacheIndex.size());
		}

		m_Mutex.lock();
		*m_pTraceNum = m_listCacheIndex.size();
		m_bStartReading = false;
		m_Mutex.unlock();
		m_Semaphore.release();

		if (m_bStop)
			break;

		m_listCacheIndex.clear();
		_CalcCacheIndex();
		_ReadCacheData();
	}

	m_Semaphore.release();
}
