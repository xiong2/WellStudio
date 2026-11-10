#ifndef _CXWell_H__
#define _CXWell_H__

#include "xdata_global.h"

#include "xobject.h"
#include "xglobal.h"
#include <vector>

using std::vector;

class CXWellPath;
class CXWellTD;
class CXWellCurve;
class CXWellNMR;
class CXWellCompData;
class CXWellComp;

///@brief	The class to represent a well.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XDATA_EXPORT CXWell: public CXObject
{
public:
	CXWell(); 

	CXWell(QString sName, double dX = g_dInvalidData, double dY = g_dInvalidData);

	virtual QString GetTypeString() { return "Well"; }

	virtual QString GetIconName() const;

	CXObject* GetFolder(EXObjectType, bool bCreate = false);

	///	Get the x, y coordinate of the well header.
	void GetWellPosition(double& dX, double& dY);

	//	set the X, Y coordinate of the well.
	void SetWellPosition(double dX, double dY);

	///	Add one attribute to this well, return false if it's not a standard attribute.
	bool AddAttribute(QString sAttName, QString sAttValue);

	///	Get one attribute, return "" if not found.
	QString GetAttribute(QString sAttName) const;

	///	Get what attributes were added.
	QStringList GetExistAttribute();

	///	Set the step of the well, it will cause all the exist curves re-sample.
	//void SetWellStep(double fStep);

	///	Get the well step.
	double GetWellStep()
	{
		return m_dStep;
	}

	unsigned GetWellCurveSample();


	///	Initialize well data range.
	//void InitializeRange(double dStart, double dStop);

	///	Expand the start and end, no changing if the range within exist range.
	void ExpandWellRange(double dStart, double dStop,double dStep);

	///	Get the well data range.
	void GetDepthRange(double& dStart, double& dEnd)
	{
		dStart	= m_dStart;
		dEnd	= m_dEnd;
	}

	///@brief Serialize function
	virtual bool Serialize(bool bSave);

	virtual bool SerializeData(CXArchive& ar);

	virtual QStringList GetDescription();

	virtual bool RemoveOneChild(CXObject* pChild) override;

	///@brief Get well path instance.
	CXWellPath* GetWellPath();

	///@brief Get well TD instance.
	CXWellTD* GetWellTD();

	///@brief Get well CXWellCompData instance.
	CXWellComp* GetWellComp();

	void updateTDWellPath(CXWellCurve* pTD, CXWellCurve* pTVD,
		CXWellCurve* pDevX, CXWellCurve* pDevY,
		CXWellCurve* pDX, CXWellCurve* pDY,
		CXWellCurve* pAzi, CXWellCurve* pDip );

	///@brief Get X, Y and TWT if one T-D curve exists
	bool GetXYAndTWT(vector<double>& vecX, vector<double>& vecY, vector<double>& vecTWT, vector<double>& vecMD);

	///@brief For KB
	double GetKB() { return m_dKB; }
	void SetKB(double dKB);

	CXWellCurve* findOrCreateTrack( QString name);
	CXWellCurve* CoypCurve(CXWellCurve* pOri, QString strName);

	void SetActivatedTDName(QString sTDName);

	QString GetActivatedTDName()
	{
		return m_sTD;
	}

	QList<CXObject *> GetSpecialCurveList(unsigned int iTemplateID);

protected:
	QMap<QString, QString>	m_mapAttributes;		//	A map contains the attributes.

	double					m_dStep;				//	The step of each point along the well (in MD).
	double					m_dStart;				//	The start of measured points (in MD)
	double					m_dEnd;					//	The end of measured points (in MD).

	double					m_dKB;

	QString					m_sTD = "";				//	Name of activated T-D curve.

	static QStringList		m_staSListAttribute;	//	List of standard attributes' name.
	static QStringList		m_staSListWellIcon;		//	List of standard well icon.

	//	Get the list of standard attributes' name.
	const QStringList&	getStandardAttributes();

public:
	CXWellCurve* getCurve(QString strName);// find curve by name (ignore match case)
	CXWellNMR* getNMR(QString strName);// find curve by name (ignore match case)
	QList<CXWellCurve*> getCurveList();
};

#endif