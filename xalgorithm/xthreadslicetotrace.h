#pragma once
#include "xbasethread.h"
#include "xalgorithm_global.h"

class CXSeismicDataVolume;

class XALGORITHM_EXPORT CXThreadSliceToTrace : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadSliceToTrace(CXSeismicDataVolume* pDV);
	virtual ~CXThreadSliceToTrace();

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
	float** m_pSectionData = nullptr;
	float*	m_pSliceBuff = nullptr;
	int		m_nLineNum = 0;

	//progress bar
	qint64 m_nTotalStep, m_iCurrent;
};