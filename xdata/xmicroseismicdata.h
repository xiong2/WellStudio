#ifndef XMICROSEISMICDATA_H
#define XMICROSEISMICDATA_H

#include "xobject.h"
#include "xdata_global.h"
#include <qvariant.h>
#include <vector>

using std::vector;

class CXDBInMemory;

///@brief	The class to represent microseismic data
///@author	Yong Shu
///@date	Sep. 2013
///@see		

class XDATA_EXPORT CXMicroSeismicData : public CXObject
{
public:
	CXMicroSeismicData(const QString& strName = "");
	~CXMicroSeismicData();

	virtual QString GetTypeString() { return "Micro Seismic"; }

	///@breif Serialize function
	virtual bool Serialize(bool bSave);

	///@brief Initialize data structure of well tops. The other column names rather than columns with primary index.
	bool InitTables(const QStringList& strListOtherColumnName);

	///@brief Add one record
	bool AddOneRecord(const QStringList& strListFieldName, QList<QVariant>& listVt);

	///@brief Get number of records
	int GetPointNum();

	///@brief Get all field names (excluding well name and formation)
	QStringList GetAllFieldNames();
	
	///@brief Get the position
	void GetPointPosition(vector<double>& vecX, vector<double>& vecY, vector<double>& vecZ);

	///@brief Get the other attribute (other than X, Y or Z)
	void GetOtherAttribute(const QString& strAttName, vector<QVariant>& vecVariant);

	virtual bool IsFolder() {return false;}

	///@brief Get the description info
	virtual QStringList GetDescription();

protected:
	virtual void _SetSelfDimension();

private:
	CXDBInMemory* m_pDBInMemory;

	QString m_strTableName;
	QStringList m_strListKeyName;

	int m_nRecordNum;
	
};


#endif // RLMICROSEISMICDATA_H
