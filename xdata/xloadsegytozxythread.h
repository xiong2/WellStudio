#ifndef _CXLOADSEGYTOZXYTHREAD_H__
#define _CXLOADSEGYTOZXYTHREAD_H__ 

#include "xdata_global.h"
#include "xbasethread.h"

class CXSEGYLoadParameters;
template<typename T> class CXRegularDataWriter;

/**
*@brief		This class is a thread that generate ZXY file from SEGY.
*@author	Xiong Xiong
*@date		Apr, 2014
*/
class XDATA_EXPORT CXLoadSEGYToZXYThread: public CXBaseThread
{
public:
	 ///@brief Constructor
    CXLoadSEGYToZXYThread(CXSEGYLoadParameters* pLoadParameters);

     ///@brief Destructor
	virtual ~CXLoadSEGYToZXYThread();

protected:
	///@brief Reimplementation of run()
	virtual void RunThread();

private:
	
	void _regularImport();
	void _irregularImport();

	//	Import one file.
	bool	_importOneFile(QString strSEGYFile);
	bool	_importOneIrreFile(QString strSEGYFile, char *);

	CXSEGYLoadParameters*		m_pLoadParameters;		//	Pointer to the load parameters instance.

	CXRegularDataWriter<float>*		m_pDataWriter;			//	Data writer to generate ZXY file.
};

#endif