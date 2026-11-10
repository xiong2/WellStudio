#ifndef _GSTHREADSTRESSCALCULATION_H__
#define _GSTHREADSTRESSCALCULATION_H__

#include "xbasethread.h"
#include "xdata_global.h"

class CX3DHorizon;
class GSAnticline;
class GSStructure;
class GSStressMap;
class GSStressParameters;

class XDATA_EXPORT GSThreadStressCalculation: public CXBaseThread
{
public:
	GSThreadStressCalculation(GSStressParameters *);
	void SetHorizon(CX3DHorizon *pIsoHor, GSStressMap *pMap)
	{
		m_pIsoHor = pIsoHor;
		m_pMap = pMap;
	}

protected:
	virtual void RunThread() override;


	CX3DHorizon *m_pIsoHor;
	GSStressMap *m_pMap;

	GSStressParameters *m_pParas;
};

#endif