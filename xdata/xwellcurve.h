#ifndef _CXWellCurve_H__
#define	_CXWellCurve_H__

#include "xdata_global.h"
#include "xobject.h"

///@brief	The class to represent a well curve.
///@author	Xiong Xiong
///@date	May, 2013
///@see		

class XDATA_EXPORT CXWellCurve: public CXObject
{
public:
	CXWellCurve(QString sName = "");
	~CXWellCurve();

	virtual QString GetTypeString() { return "Well Log Curve"; }

	///	Re-set the data by given points.
	void ResetData(double fStart, double fStep, unsigned int iNumPoints, double*pData);

	/// Re-set the data by Resample.
	void ResetDataByResample(double fStart, double fStep, unsigned int iNumPoints, double*pData);

	///	Get data range.
	void GetDepthRange(double& fStart, double& fEnd);

	///	Get sample start.
	double GetStart()
	{
		return m_dStart;
	}
	///	Get sample stop.
	double GetStop()
	{
		return m_dStart + (m_nSamplingNum - 1) * m_dStep;;
	}
	///	Get sample step.
	double GetStep()
	{
		return m_dStep;
	}

	///	Get the data pointer.
	double* GetData();

	///	Copy the data to the given pointer (space already allocated), INVALID value be used if beyond the data range.
	bool GetData(double *pData, double dStartDepth, unsigned int iNumPoints);

	///	Copy the data to the given pointer (space already allocated) by Resample, INVALID value be used if beyond the data range.
	bool GetDataByResample(float *pData, double dStartDepth, double dStartStep, unsigned int iNumPoints);

	/// Copy the data to the given vector by range MD.
	void GetData(double dStartDepth, double dEndDepth, vector<double> &vec);

	///	Get point number.
	unsigned int GetPointNumber()
	{
		return m_nSamplingNum;
	}

	///	Overwrite basic function, to return template icon.
	virtual QString GetIconName() const;

	///	Get unit (from the template actually.
	QString GetUnit();

	///@breif Serialize function
	virtual bool Serialize(bool bSave);

	///@brief	Get the tempalte ID of the curve.
	virtual unsigned int GetTemplateID() const;

	///@brief	Get the alias ID of the curve.
	QUuid GetAliasID()
	{
		return m_aliasID;
	}

	///@bref	Set alias ID.
	void SetAliasID(QUuid aliasID)
	{
		m_aliasID = aliasID;
		SetModifiedFlag();
	}

	virtual QStringList GetDescription();

	void setSelfUnit(QString unit){ m_unit = unit; }
	QString getSelfUnit(){ return m_unit; }
	virtual bool SerializeData(CXArchive& ar);

	///@brief Set the get dimension info	
	virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

	void GetValidRange(double& dStart, double& dStop);


	QList<QPair<double, double> >	GetTableData();
	void SetTableData(QList<QPair<double, double> >		lstTableData);

protected:
	virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);

protected:	
	QUuid				m_aliasID;			//	ID of the curve alias.
	double				m_dStep;			//	The step of each point along the well (in MD).
	double				m_dStart;			//	The start of measured points (in MD)	
	QString				m_unit;// self unit for shown only

	QList<QPair<double,double> >		m_lstTableData;
public:
	static bool IsValid(double v);
	void SetData(int index,double& value); //set data ,for rocklab
	double GetDepth(int index);//get depth by index
	double GetData(int index);//get data by index
	int GetIndex(float depth);//由深度返回index
	bool IsDepthDomain(){ return true; };//now always return true
	void GetDepthRange(float& fStart, float& fEnd);	//	Get data range.
	int GetCount()
	{
		return m_nSamplingNum;
	}
};

#endif