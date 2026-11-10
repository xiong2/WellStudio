#ifndef XSEISMICRANDOMSECTION_H
#define XSEISMICRANDOMSECTION_H

#include "xdata_global.h"
#include "xobject.h"
#include "xseismicutmtool.h"
#include <vector>

class CXSeismicDataVolume;
class CXSeismicUTMTool;

using std::vector;
// Each trace info
struct STraceLocation
{
	STraceLocation(int iInlineNum, int iXlineNum, double dX, double dY)
	{
		m_iInlineNum = iInlineNum;
		m_iXlineNum = iXlineNum;
		m_dX = dX;
		m_dY = dY;
	}
	int m_iInlineNum;
	int m_iXlineNum;
	double m_dX;
	double m_dY;
};

/*
* @brief The class provides data structure for a seismic random section.
* 
* @author Yong Shu
* @date Agu. 12th, 2014
* @see 
*/
class  XDATA_EXPORT CXSeismicRandomSection: public CXObject
{
public:
	CXSeismicRandomSection(const QString& strName = QString());
	~CXSeismicRandomSection();

	CXSeismicDataVolume* GetDefaultDataVolume(bool bIncludePrestack = true);

	CXSeismicUTMTool GetUTM();

	virtual QString GetTypeString() { return "Seismic Random Section"; }

	///@brief Set a polyline as the path of a random section
	void SetPolyline(const vector<double>& vecX, const vector<double>& vecY);
	
	///@brief Append a point at the end of a random section path.
	void Append(double, double);

	///@brief Set a turing point coordinate by index
	bool SetXYByIndex(uint i, double dX, double dY);

	///@brief Reimplement to save/load the data
    virtual bool SerializeData(CXArchive &ar) override;

	///@brief Get turn points number (including end points)
	int GetTurnPointNumber()
	{
		return m_vecTurningPoint.size() / 2;
	}

	///@brief Get the X and Y of the turning points
	void GetXYofTuringPoint(vector<double>& vecX, vector<double>& vecY);

	///@brief Get the inline and xline numbers
	void GetLineNumbers(vector<int>& vecInline, vector<int>& vecXline);

	///@brief Get the X and Y
	void GetXY(vector<double>& vecX, vector<double>& vecY);

	///@brief Get the trace number
	int GetTraceNum(CXSeismicDataVolume *pDV = NULL);

	///@brief Get trace information by index
	bool GetTraceInfo(int iIDX, int& iLine, int& iCDP, double& dX, double& dY);

	///@brief Get the index of the turing point in all traces
	int GetTPTraceIndex(int iPoint);
	bool IsTPTraceIndex(int index);

	std::vector<int>& GetVecTPIndex() { return m_vecTPTraceIndex; }

	virtual QStringList GetDescription();

	QUuid GetSurveyID();

protected:
	virtual void _SetSelfDimension() override;
	// set histogram from another object
	virtual CXObject* _GetHistogramObject();

	// Calculate the each trace along the incremented path of the random section
	void _AddOneTurningPoint(CXSeismicUTMTool& UTM, double dXNext, double dYNext);
	void _CreateTraceLocations();


	// The turning points x0, y0, x1, y1, ...
	std::vector<double> m_vecTurningPoint;

	// The each trace info
	std::vector<STraceLocation> m_vecTraceLocation;	

	// The turning point trace index
	std::vector<int> m_vecTPTraceIndex;
};

#endif // RLSEISMICRANDOMSECTION_H