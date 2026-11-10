#ifndef GSROSEDIAGRAM_H__
#define GSROSEDIAGRAM_H__

#include <QPolygonF>
#include "xobject.h"
#include "xdata_global.h"

class GSStressMap;

class XDATA_EXPORT GSRoseDiagram : public CXObject
{
public:
	GSRoseDiagram(){}
	GSRoseDiagram(const QString& sName, QPolygonF);
	GSRoseDiagram(const QString& sName, QPointF, double);
	~GSRoseDiagram(){}

	virtual bool SerializeData(CXArchive& ar);
	virtual QString GetTypeString();
	virtual QStringList GetDescription();

	QVector<float>& GetVecData()
	{
		return m_vecData;
	}

	int GetMode()
	{
		return m_iMode;
	}

	QPointF GetCentre()
	{
		return m_centre;
	}

	QVector<float>& GetPetalVector(int);

protected:
	int			m_iMode;	//	0: circle range;	1: polygon range.
	QPolygonF	m_polygon;
	QPointF		m_centre;
	double		m_dRadius;

	QVector<float>	m_vecData;
	QVector<float>	m_vecPetal;
};

#endif