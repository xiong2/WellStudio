#include "xasynregularwriter.h"
#include <qfile.h>
#include "xregulardatawriter.h"
#include "xglobal.h"

CXAsynRegularWriter::CXAsynRegularWriter(const QStringList& listFileName, int nI, int nJ, int nK, int nOneBuffSize) :
	m_nMaxOneBuffSize(nOneBuffSize)
{
	m_bStop = false;
	m_nDataLength = 0;
	m_Semaphore.release();

	for (int i = 0; i < listFileName.size(); ++i)
	{
		CXRegularDataWriter<float>* pWriter = new CXRegularDataWriter<float>(listFileName[i], nI, nJ, nK);
		m_vecWriter.push_back(pWriter);
	}
}

CXAsynRegularWriter::~CXAsynRegularWriter()
{
	wait();

	for (int i = 0; i < m_vecWriter.size(); ++i)
	{
		delete m_vecWriter[i];
	}
	m_vecWriter.clear();

	for (int i = 0; i < m_vecBuff.size(); ++i)
	{
		delete []m_vecBuff[i];
	}
	m_vecBuff.clear();
}

void CXAsynRegularWriter::StopThread()
{
	m_Mutex.lock();
	m_bStop = true;
	m_bStartReading = true;
	m_Condition.wakeOne();
	m_Mutex.unlock();

	this->wait();
}

bool CXAsynRegularWriter::Init()
{
	for (int i = 0; i < m_vecWriter.size(); ++i)
	{
		if (!m_vecWriter[i]->Open())
			return false;
	}

	try
	{
		for (int i = 0; i < m_vecWriter.size(); ++i)
		{
			float* pData = new float[m_nMaxOneBuffSize];
			m_vecBuff.push_back(pData);
		}
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	return true;
}

void CXAsynRegularWriter::WaitWriteData()
{
	m_Semaphore.acquire();
}

void CXAsynRegularWriter::WriteData(vector<float*>& vecData, int nLength)
{
	QMutexLocker locker(&m_Mutex);

	m_nDataLength = nLength;
	for (int i = 0; i < vecData.size(); ++i)
	{
		memcpy(m_vecBuff[i], vecData[i], sizeof(float)*nLength);
	}

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

void CXAsynRegularWriter::run()
{
	for (;;)
	{
		m_Mutex.lock();
		while (!m_bStartReading)
			m_Condition.wait(&m_Mutex);
		m_Mutex.unlock();

		if (m_bStop)
			break;

		if (m_nDataLength)
		{
			for (int i = 0; i < m_vecWriter.size(); ++i)
			{
				m_vecWriter[i]->Append(m_nDataLength, m_vecBuff[i]);
			}

			m_nDataLength = 0;
		}
		

		m_Mutex.lock();
		m_bStartReading = false;
		m_Mutex.unlock();
		m_Semaphore.release();

		if (m_bStop)
			break;	

	}

	m_Semaphore.release();
}


