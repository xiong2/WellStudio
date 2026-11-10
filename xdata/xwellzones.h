#ifndef XWELLZONES_H
#define XWELLZONES_H

#include "xobject.h"
#include "xdata_global.h"
#include <qvariant.h>
#include <QVector3D>
#include <QPen>

class CXDBInMemory;
class CX3DPoints;

///@brief	The class to represent well tops.
///@author	Yong Shu
///@date	Sep. 2013
///@see		

class XDATA_EXPORT CXWellZones : public CXObject
{
public:
	CXWellZones(const QString& strName = "");
	~CXWellZones();

	///@breif Serialize function
	virtual bool Serialize(bool bSave);

	virtual QString GetTypeString() { return "Well Zones"; }
	
	///@brief Generate formations
	void GenerateFormations();

	///@brief Add one record
	bool AddOneRecord( QString strFormation, QPointF vt);
	bool AddOneRecord( QString strFormation, QString str1,QString str2,QColor cr = Qt::blue);
	bool DelOneRecord( QString strFormation);
	//bool AddOneRecord(const QStringList& strListFieldName, const QList<QVariant>& listVt);

	///@brief Get one record 
	QPair<QString, QString> GetOneRecord( QString strFormation);
	QColor GetOneRecordColor(QString strFormation);

	///@brief GetTopsByWell
	QStringList GetZonesByWell(QString strWellName);

	///@brief Get one record 
	int GetOneRecordIndex( QString strFormation);
	///@brief Get number of records
	int GetRecordNum();

	///@brief Get well names and formation names
	void GetFormation( QStringList& strListFormation);

	virtual bool IsFolder() {return true;}

	virtual bool SerializeData(CXArchive& ar);

	void ClearData();
private:
	QStringList m_lstTopNames;
	QList<QPair<QString,QString>> m_lstData;
	QMap<QString, QPen> m_mapPen;
};

#endif // RLWELLTOPS_H
