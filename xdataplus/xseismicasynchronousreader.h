#ifndef XSEISMICASYNCHRONOUSREADER_H
#define XSEISMICASYNCHRONOUSREADER_H

#include <qthread.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#include <qsemaphore.h>
#include <qstring.h>
#include <qlist.h>
#include "xdataplus_global.h"

template<typename T> class CXRegularDataReader;

/**
* @class CXSeismicAsynchronousReader provided in the file "keseismicasynchronousreader.h"
* @brief The Class provides a thread to read 3-D seismic data 
*
* @author Yong Shu
* @date 3/14/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXSeismicAsynchronousReader : public QThread
{
public:
	CXSeismicAsynchronousReader(const QString& strFileName, int nI, int nJ, int nK, int nExpectedTraceNum = 1);
	~CXSeismicAsynchronousReader();

	bool Init(int iMin, int iMax, int jMin, int jMax);

	void ReadData(int* pTraceNum, float* pData);

	void WaitReadData();

	///@brief  Stop the thread
	void StopThread();	

protected:
	virtual void run();

private:
	bool _ReadCacheData();

	void _CalcCacheIndex();


private:
	CXRegularDataReader<float>* m_pReader;

	int m_nI, m_nJ, m_nK;
	int m_nExpectedTraceNum;

	int m_iMin, m_iMax, m_jMin, m_jMax;
	
	int* m_pTraceNum;
	QList<int> m_listCacheIndex;

	int m_iCurrentIndex;

	float *m_pInBuffer;
	float *m_pCacheBuffer;

private:
	bool m_bStartReading;

	volatile bool m_bStop;

	// local mutex
	QMutex m_Mutex;

	// local wait condition
	QWaitCondition m_Condition;

	// local semephore
	QSemaphore m_Semaphore;
	
};

#endif // KESEISMICASYNCHRONOUSREADER_H
