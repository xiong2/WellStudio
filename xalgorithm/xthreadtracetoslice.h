#ifndef XTHREADTRACETOSLICE_H
#define XTHREADTRACETOSLICE_H

#include "xbasethread.h"


class CXSeismicDataVolume;

/**
 * @class CXThreadTraceToSlice provided in the file "rlthreadtracetoslice.h"
 * @brief The Class provides a thread to convert a trace file to a slice file
 * 
 * @author Yong Shu 
 * @date 5/27/2014
 * @see 
 * @bug	No Known bugs so far
 */

class CXThreadTraceToSlice : public CXBaseThread
{
public:
    ///@brief Constructor and destructor
	CXThreadTraceToSlice(CXSeismicDataVolume* pDV);
	virtual ~CXThreadTraceToSlice();

protected:
	/// Reimplementation of run()
	virtual void RunThread();			

private:
    // Overall Initialization
    bool _Initialization();

    // Release one converison semaphore when catching an memory exception
    void _ReleaseData(bool bWithSemaphore = true);

private:
    // The list of current data volumes
    CXSeismicDataVolume* m_pDV;

    // ZXY volume dimension
    int m_nInlineDim;
    int m_nCrosslineDim;
    int m_nTimeDim;	

	QString m_strTraceFileName, m_strSliceFileName;	

private:
	float* m_pSectionBuff;
	float** m_p2DSliceData;
	int m_nSliceNum;

	//progress bar
	qint64 m_nTotalStep, m_iCurrent;
};

#endif // RLTHREADTRACETOSLICE_H
