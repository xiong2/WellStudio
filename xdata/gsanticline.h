#ifndef _GSANTICLINE_H__
#define _GSANTICLINE_H__

#include <qpoint.h>
#include <xobject.h>
#include "xdata_global.h"

class CX3DHorizon;

class XDATA_EXPORT GSAnticline: public CXObject
{
public:
	GSAnticline() {}
	GSAnticline(QPointF end0, QPointF end1, double dRmaR, double dLength, bool bAnticline);

	virtual bool SerializeData(CXArchive& ar);

	void GetEndPoints(QPointF& end0, QPointF& end1)
	{
		end0 = m_end0;
		end1 = m_end1;
	}

	bool IsAnticline()
	{
		return m_bAnticline;
	}

	float GetVolume(CX3DHorizon *);
	double GetLength()
	{
		return m_dLength;
	}

	double GetRmaR()
	{
		return m_dRmaR;
	}

	QPolygonF GetBoundaryPolygon();

protected:
	bool			m_bAnticline;
	QPointF			m_end0;
	QPointF			m_end1;
	float			m_fVolume;
	double			m_dRmaR;
	double			m_dLength;

	virtual void _SetSelfDimension();
};

#endif