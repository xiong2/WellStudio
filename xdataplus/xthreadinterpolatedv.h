#ifndef XTHREADINTERPOLATEDV_H
#define XTHREADINTERPOLATEDV_H

#include "xbasethread.h"
#include "xdataplus_global.h"

class CXSeismicDataVolume;

/**
* @class CXThreadInterpolateDV provided in the file "kethreadinterpolatedv.h"
* @brief The Class provides a thread to interpolate data volume
*
* @author Yong Shu
* @date 11/19/2015
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadInterpolateDV : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadInterpolateDV(CXSeismicDataVolume* pDV);
	virtual ~CXThreadInterpolateDV();

	CXSeismicDataVolume* GetOutput() { return m_pOutDV; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	CXSeismicDataVolume* m_pDV;
	CXSeismicDataVolume* m_pOutDV;


};

#endif // KETHREADINTERPOLATEDV_H
