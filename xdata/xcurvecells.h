#ifndef XCURVECELLS_H
#define XCURVECELLS_H

#include "xdata_global.h"
#include "xobject.h"

class CXWellCurveAlias;
class CXWellCurve;
class CXWellCondition;

//!@brief	The class used to holds a list of reservoir cells a well curve alias pass through.
//!@author	Pezy
//!@date	Feb, 9th, 2015
//!@see		Reservoir.uml

class XDATA_EXPORT CXCurveCells : public CXObject
{
public:
	CXCurveCells();
	CXCurveCells(CXWellCurveAlias *);
	~CXCurveCells() {}

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar) override;

	const QUuid &GetWellCurveAliasID()
	{
		return m_curveAliasID;
	}

	// Calculate all well curve.
	void CalculateCurve(CXWellCondition *pWellCondition);

	// Calculate cells along one curve.
	void CalculateOneCurve(CXWellCurve *pCurve, CXWellCondition *pWellCondition, QList<double> &listValue);

	///@brief Get geometry object
	virtual CXObject* GetGeometryObject() override;

	///@brief Set the get dimension info
	//virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

	virtual QStringList GetDescription() override;

protected:
	virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);

private:
	QUuid m_curveAliasID;

};

#endif // RLCURVECELLS_H
