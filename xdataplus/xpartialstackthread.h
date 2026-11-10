#ifndef _CXPARTIALSTACKTHREAD_H__
#define _CXPARTIALSTACKTHREAD_H__ 

#include "xdataplus_global.h"
#include "xbasethread.h"

class CXParametersPartialStack;
class CXSeismicDataVolume;

/**
*@brief		This class is a thread that do the partial stack of azimuth seismic data.
*@author	Xiong Xiong
*@date		Sep, 2016
*/
class XDATAPLUS_EXPORT CXPartialStackThread : public CXBaseThread
{
public:
	///@brief Constructor
	CXPartialStackThread(CXParametersPartialStack* pStackParameters);

	///@brief Destructor
	virtual ~CXPartialStackThread();

	CXSeismicDataVolume* GetOuputDV()
	{
		return m_pOutputDV;
	}

protected:
	///@brief Reimplementation of run()
	virtual void RunThread();

private:
	CXParametersPartialStack*	m_pStackParameters;		//	Pointer to the load parameters instance.

	CXSeismicDataVolume*	m_pOutputDV;
};

#endif