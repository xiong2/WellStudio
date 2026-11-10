#ifndef XPRESTACKASYNREADER_H
#define XPRESTACKASYNREADER_H

#include <qthread.h>
#include <qmutex.h>
#include <qwaitcondition.h>
#include <qsemaphore.h>
#include <qstring.h>
#include <vector>
#include <qmap.h>
#include <qpair.h>
#include <qvector.h>
#include "xdataplus_global.h"
#include "xseismicutmtool.h"

using std::vector;

class CXSeismicDataVolume;

/**
* @class CXPrestackAsynReader provided in the file "keprestackasynreader.h"
* @brief The Class provides a thread to read 3-D prestack seismic data
*
* @author Yong Shu
* @date 10/24/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXPrestackAsynReader : public QThread
{
public:
	CXPrestackAsynReader(CXSeismicDataVolume* pDV, int nHalfWinI, int nHalfWinJ);
	~CXPrestackAsynReader();

	bool Init(double dSamplingStart, int nK);

	void ReadData(int iInline, int iXline, float* pOutGather, float* pOutOffAZi, int* pFold, int iInlineNext, int iXlineNext);

	void WaitReadData();

	///@brief  Stop the thread
	void StopThread();

protected:
	virtual void run();

private:
	bool _ReadAndStackData();
	void _StackData();

private:
	CXSeismicDataVolume* m_pDV;

	CXSeismicUTMTool m_utm;
	
	int m_nKDV, m_iKOffset, m_nK, m_nMaxFold;

	int m_nHalfWinI, m_nHalfWinJ;

private:
	vector<float*> m_vecpGatherBuff, m_vecpOffAziBuff;

	float *m_pGather, *m_pOffAzi;
	int m_nFold;
	
	int m_iInline, m_iXline;
	QMap<QPair<int, int>, int> m_mapPreIndex, m_mapIndex, m_mapPreFold, m_mapFold;

	//output
	float *m_pOutGather, *m_pOutOffAzi;
	int m_iInlineNext, m_iXlineNext;
	int *m_pFold;

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

#endif // KEPRESTACKASYNREADER_H
