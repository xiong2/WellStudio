#ifndef _GSGEOLOGICSTAGE_H__
#define _GSGEOLOGICSTAGE_H__

#include <QPointF>
#include "xobject.h"
#include "xdata_global.h"

class XDATA_EXPORT GSGeologicStage : public CXObject
{
public:
	GSGeologicStage();
	GSGeologicStage(const QString& strName);

	virtual bool SerializeData(CXArchive& ar);
	virtual QStringList GetDescription();
	virtual QString GetTypeString()
	{
		return "Geologic Stage";
	}

	QList<qreal>& GetAllSources()
	{
		return m_listSources;
	}

	QList<QUuid>& GetAllHID()
	{
		return m_listHFID;
	}

protected:
	QList<qreal>	m_listSources;	//	triples of x, y, azimuth.
	QList<QUuid>	m_listHFID;		//	ID of horizon folders belong to this stage.
};

#endif