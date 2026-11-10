#ifndef _GSPDG_H__
#define _GSPDG_H__

#include <qpolygon.h>
#include <qvector.h>
#include "xobject.h"
#include "xdata_global.h"

class GSSection;
class CX3DSurvey;

class XDATA_EXPORT GSPDG : public CXObject
{
public:
	GSPDG();
	GSPDG(CX3DSurvey *, const QString& sName, QPointF);		//	Created from a map.
	GSPDG(GSSection *, const QString& sName, QPolygonF);	//	Created from a section.
	~GSPDG();

	virtual bool SerializeData(CXArchive& ar);
	virtual QString GetTypeString();
	virtual QStringList GetDescription();

	QPolygonF GetTrajectoryPoints()
	{
		return m_trajectory;
	}

	QVector<float>& GetStressPoints()
	{
		return m_vecStressPoints;
	}
		
	QList<QUuid> GetHorizonsID()
	{
		return m_listHID;
	}

protected:
	void calculateStressPoints(CX3DSurvey *);
	virtual void _SetSelfDimension();

	QUuid			m_refID;			//	Create on section?  then the section ID.
	QPolygonF		m_trajectory;		//	If one point, then it's x, y; otherwise they are trace idx (on a special section) and z.
	QVector<float>	m_vecStressPoints;	//	6 values for each point: horizon IDX, depth, pp, Sv, SH, Sh.
	QList<QUuid>	m_listHID;			//	The list of depth horizon ID that the PDG traverse.
};

#endif