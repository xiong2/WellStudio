#ifndef XWELLTOPS_H
#define XWELLTOPS_H

#include "xobject.h"
#include "xdata_global.h"
#include <qvariant.h>
#include <QVector3D>

class CXDBInMemory;
class CX3DPoints;

///@brief	The class to represent well tops.
///@author	Yong Shu
///@date	Sep. 2013
///@see		
class XDATA_EXPORT CXWellTops : public CXObject
{
public:
	CXWellTops(const QString& strName = "");
	~CXWellTops();

	///@breif Serialize function
	virtual bool Serialize(bool bSave);

	virtual QString GetTypeString() { return "Well Tops"; }
	
	///@brief Generate formations
	void GenerateFormations();

	///@brief Add one record
	bool AddOneRecord(QString strWellName, QString strFormation, double dMD);
	bool AddOneRecord(QString strWellName, QString strFormation, QVector3D point3);
	bool DelOneRecord(QString strWellName, QString strFormation);

	///@brief Get one record 
	double GetOneRecord(QString strWellName, QString strFormation);
	QVector3D GetOneRecordXYZ(QString strWellName, QString strFormation);

	///@brief GetTopsByWell
	QStringList GetTopsByWell(QString strWellName);

	///@brief Get one record 
	int GetOneRecordIndex(QString strWellName, QString strFormation);
	///@brief Get number of records
	int GetRecordNum();

	///@brief Get well names and formation names
	void GetWellAndFormation(QStringList& strListWell, QStringList& strListFormation);

	///@brief Get the a 3-D points according to the specific formation
	CX3DPoints* Get3DPointsFromFormation(const QString& strFormation);

	virtual bool IsFolder() {return true;}

	virtual bool SerializeData(CXArchive& ar);

	void ClearData();

	//	Below two functions just for data sheet using.
	QStringList GetAllStringRecord();
	double* GetAllFigureRecord();

private:
	QStringList m_lstWellNames;
	QStringList m_lstTopNames;
	QList<double> m_lstMD;
	QList<QVector3D> m_lstXYZ;
};

#endif 