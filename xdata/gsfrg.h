#ifndef _GSFRG_H__
#define _GSFRG_H__

#include <qvector.h>
#include "xobject.h"
#include "xdata_global.h"

class CX3DSurvey;
class CXFaultSticks;

class XDATA_EXPORT GSFRG : public CXObject
{
public:
	GSFRG() 
	{
	}

	GSFRG(CX3DSurvey *, CXFaultSticks *);

	virtual bool SerializeData(CXArchive& ar);
	virtual QString GetTypeString();
	virtual QStringList GetDescription();
	int GetTraverseHorizonNum();

	QVector<float>& GetVecData(int i)
	{
		if(i == 0)
			return m_vecDepth;
		else if(i == 1)
			return m_vecRP;
		else if(i == 2)
			return m_vecDE;
		else if(i == 3)
			return m_vecAV;

		return m_vecFD;
	}

protected:
	QVector<float>	m_vecDepth;	//	Depth.
	QVector<float>	m_vecRP;	//	Reverse percentage.
	QVector<float>	m_vecDE;	//	Dip Effective.
	QVector<float>	m_vecAV;	//	Dip Average.
	QVector<float>	m_vecFD;	//	Dip Average.
};

#endif