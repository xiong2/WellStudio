#ifndef XOBJECT_H
#define XOBJECT_H

#include "xio.h"
#include "xdata_global.h"
#include <qcolor.h>
#include <vector>
#include "xhistogram.h"
#include "xdef.h"

using std::vector;

class XDATA_EXPORT CXObject : public IKEIO
{
public:
	CXObject(const QString& strName=QString(), const QUuid& uuid=QUuid());
	virtual ~CXObject();

	///@brief Copy constructor
	CXObject(const CXObject& other);
	///@brief Assignment operation
	CXObject& operator=(CXObject& other);

	///@brief Add one child
	bool AddChild(CXObject* pChild);

	///@brief Insert one child
	bool InsertChild(CXObject* pChild, int index);

	///@brief Find named child, return NULL if not found.
	CXObject* GetChild(QString sName, EXObjectType eObjType = EXBegin);

	///@brief Find child with specified ID, return NULL if not found.
	CXObject* GetChild(QUuid objID);

	///@brief Find the 1st child with the specified template, return NULL if not found.
	CXObject* GetChild(unsigned int iTemplateID);

	///@brief Get children list, and not include grandchildren
	QList<CXObject*> GetChildrenList() {return m_listChildren;}

	///@brief Get the children list according to the object type
	QList<CXObject*> GetChildren(EXObjectType eObjType, bool bIncludingGrandchildren = false);

	///@brief Get the name list of children according to the object type
	QStringList  GetChildrenNames(EXObjectType eObjType, bool bIncludingGrandchildren = false);

	///@brief Remove one child
	virtual bool RemoveOneChild(CXObject* pChild);

	///@brief Set and get the parent
	virtual bool SetParent(CXObject* pParent);
	CXObject* GetParent();

	///@Brief Set and get the object name
	void SetObjectName(const QString& strName) { m_strObjName = strName.simplified(); SetModifiedFlag(); }
	const QString& GetObjectName()const {return m_strObjName;}

	///@brief Set and get the icon name
	void SetIconName(const QString& strIconName) { m_strIconName = strIconName; SetModifiedFlag(); }
	virtual QString GetIconName() const {return m_strIconName;}

	///@brief Set and get the template ID
	void SetTemplateID(unsigned int iTemplateID) {m_iTemplateID = iTemplateID;}
	virtual unsigned int GetTemplateID() const {return m_iTemplateID;}

	///@brief Get the unallocated name
	virtual QString GetUnallocatedName(const QString& strName);

	///@brief Get the description info
	virtual QStringList GetDescription();

	///@brief Tell if the object is locked or not
	bool IsLocked();

	///@brief Set the get the object color
	void SetColor(const QColor& color) {m_color = color;}
	QColor GetColor() const {return m_color;}

	///@brief Tell if the object is the node or not
	void SetNodeFlag(bool bIsNode) {m_bIsNode = bIsNode;}
	bool GetNodeFlag() {return m_bIsNode;}

	///@brief Get the object data file name
	QString GetDataFileName() const;

	///@brief Tell if the object is folder-like class
	virtual bool IsFolder() {return false;}

	///@brief Get geometry object
	virtual CXObject* GetGeometryObject() {return this;}

	///@brief Domain type
	void SetDomainType(EDomainType eType) { m_bDomainType = eType; }
	virtual EDomainType GetDomainType() { return m_bDomainType;}

	///@brief Get an ancient according to object type
	CXObject* GetAncient(EXObjectType eObjType);

	QUuid GetSurveyID();

public:
	///@brief Methods are related to the dimension and histogram.

	///@brief Set the get dimension info	
	virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

	///@brief This info used to show the object type on the general page, need be overwritten by almost all sub classes.
	virtual QString GetTypeString() { return ""; }

	///@brief Set need re-calculate histogram
	void SetNeedCalculateHistogram() {m_bCalculated = false;}

	///@brief Get the data min and max
	void GetDataRange(double& dDataMin, double& dDataMax);

	///@brief Tell if the object has the histogram
	bool HasHistogram();

	///@brief Get the histogram
	void GetHistogram(vector<double>& vecHorizontal, vector<double>& vecVertical);
	const CXHistogram& GetHistogram() { return m_histogram; }

	///@brief	Get the data.
	virtual double* GetData(unsigned int& iNumber);

	///@brief Serialization using the database
	virtual bool Serialize(bool bSave);

	///@brief Tell the instance its dimension need be re-calculated.
	void SetNeedCalcDimension() {m_bDimensionCalculated = false;}

	///@brief Load data from the file
	void LoadData();

	///@brief Get Z min 
	double GetZMin();

	///@brief Get Z max
	double GetZMax();

	///@brief Set histogram
	void SetHistogram(const CXHistogram& histogram);

protected:	
	// Set the self dimension
	virtual void _SetSelfDimension();

	// Calculate histogram
	virtual  float* _GetHistogramData(int& nDataNum, bool& bDeleted);

	// set histogram from another object
	virtual CXObject* _GetHistogramObject();

	// Set dimension
	void _SetDimension(double dXMin, double dXMax, double dYMin, double dYMax, double dZMin, double dZMax);

	// Write data into the file or read data from the file
	virtual void _WriteData();
	virtual void _ReadData();

	void _LoadBaseData();

private:
	void _Init();
	void _CopyOwnData(const CXObject& other);
	void _CalcHistogram();	

	bool _GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);	

private:
	QList<CXObject*> m_listChildren;

	QUuid m_parentID;

	QString m_strObjName;

	QString m_strIconName;

	unsigned int m_iTemplateID;

	QColor m_color;

	bool m_bIsNode;

	EDomainType m_bDomainType;
protected:
	unsigned int	 m_nSamplingNum; //	Number of points.
	double*	m_pBaseData;			//	The points.

	bool m_bDimensionCalculated;

	double m_dXMin, m_dXMax, m_dYMin, m_dYMax, m_dZMin, m_dZMax;	

private:
	// Histogram and dimension
	bool m_bHasHistogram;

	bool m_bCalculated;

	bool m_bDiscrete;

	bool m_bLog;

	CXHistogram m_histogram;

	// histogram from database
	bool m_bDBHistogram;
	

};

#endif // RLOBJECT_H
