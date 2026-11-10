#ifndef _CXTRACEHEADERSCANTHREAD_H__
#define _CXTRACEHEADERSCANTHREAD_H__

#include <qhash.h>
#include "xdata_global.h"
#include "xbasethread.h"

class CXSEGYLoadParameters;

struct SKETraceOffsets;

/**
*@class		CRLTraceHeaderScanThread "gmtraceheaderscanthread.h"
*@brief		This class is a thread to scan the trace header of one or multiple SEGY file.
*@author	Xiong Xiong
*@date		Apr, 2014
*/
class XDATA_EXPORT CXTraceHeaderScanThread: public CXBaseThread
{
public:
	CXTraceHeaderScanThread(CXSEGYLoadParameters* pLoadParameters, bool bIrregular = false, bool bAzimuth = false);
    virtual ~CXTraceHeaderScanThread(){}

	int GetErrorCode()
	{
		return m_iErrorCode;
	}

protected:
	virtual void RunThread();

private:
	bool	scanOneFile(QString strSEGYFile, int iFileNo);			//	Scan one file.
	bool	scanOneIrreFile(QString strSEGYFile, int iFileNo);		//	Scan one file.
	bool	scanOneGatherFile(QString strSEGYFile, int iFileNo);	//	Scan one file.

	CXSEGYLoadParameters*		m_pLoadParameters;				//	Pointer to the load parameters instance.

	//	Indiates error type: 
	//	0	No error.
	//	1	Parameters error.
	//	2	SEGY file open error.
	//	3	Offset not regular.
	//	4	Multiple UTM not compatible.
	//	5	Can not open file to write!
	int		m_iErrorCode;		

	//	Below members only used for irregular prestack 3D data.
	int		m_iInlineMin, m_iInlineMax, m_iXlineMin, m_iXlineMax, m_iInlineInc, m_iXlineInc;
	int		m_iMaxFold;
	bool	m_bIrregularPrestack;
	bool	m_bAzimuth;
};

#endif