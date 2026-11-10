#ifndef XASYNREGULARWRITER_H
#define XASYNREGULARWRITER_H

#include <qthread.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#include <qsemaphore.h>
#include <qstringlist.h>
#include <vector>
#include "xdataplus_global.h"
#include "xseismicutmtool.h"

using std::vector;

template<typename T> class CXRegularDataWriter;

/**
* @class CXAsynRegularWriter provided in the file "keasynregularwriter.h"
* @brief The Class provides a thread to write 3-D regular seismic data
*
* @author Yong Shu
* @date 10/24/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXAsynRegularWriter : public QThread
{
public:
	CXAsynRegularWriter(const QStringList& listFileName, int nI, int nJ, int nK, int nOneBuffSize);
	~CXAsynRegularWriter();

	bool Init();

	void WriteData(vector<float*>& vecData, int nLength);

	void WaitWriteData();

	///@brief  Stop the thread
	void StopThread();

protected:
	virtual void run();

private:
	vector<CXRegularDataWriter<float>*> m_vecWriter;

	vector<float*> m_vecBuff;

	int m_nMaxOneBuffSize;

	int m_nDataLength;

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

#endif // KEASYNREGULARWRITER_H
