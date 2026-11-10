#ifndef _CXLOAD2DSEGYTHREAD_H__
#define _CXLOAD2DSEGYTHREAD_H__

#include "xdata_global.h"
#include "xbasethread.h"

class CXSEGYLoadParameters;
class CX2DSeismicLine;

/**
*@brief		This class is a thread that generate ZXY file from 2D SEGY.
*@author	Xiong Xiong
*@date		Sep, 2015
*/
class XDATA_EXPORT CXLoad2DSEGYThread : public CXBaseThread
{
public:
	///@brief Constructor
	CXLoad2DSEGYThread(CXSEGYLoadParameters* pLoadParameters);

	///@brief Destructor
	virtual ~CXLoad2DSEGYThread();

	CX2DSeismicLine* GetImportedLine() { return m_p2DSeismicLine; }

protected:
	///@brief Reimplementation of run()
	virtual void RunThread();

private:
	CXSEGYLoadParameters*		m_pLoadParameters;		//	Pointer to the load parameters instance.
	CX2DSeismicLine*			m_p2DSeismicLine;		//	The 2D line being imported.
};

#endif