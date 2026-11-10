#ifndef _CXSeismicSubVolume_H__
#define _CXSeismicSubVolume_H__

#include "xdata_global.h"
#include "xobject.h"
#include "xseismicutmtool.h"

class CXSeismicDataVolume;

/*
* @brief The class provides data structure for a seismic sub-volume
* 
* @author Xiong Xiong 
* @date May, 2014
* @see 
*/
class  XDATA_EXPORT CXSeismicSubVolume: public CXObject
{
public:
	CXSeismicSubVolume() {}
	CXSeismicSubVolume(QString sName, int iStartInline, int iEndInline, int iStartXline, int iEndXline, double dStartTime, double dEndTime);

	///@brief Get the survey ID
	QUuid GetSurveyID();

	///@brief Get current using data volume.
	CXSeismicDataVolume* GetDefaultDataVolume();

	virtual QString GetTypeString() { return "Sub Volume"; }

	///@brief Get the UTM (The UTM of the survey.
	CXSeismicUTMTool GetUTM();

	void GetDataRange(int& iStartInline, int& iEndInline, int& iStartXline, int& iEndXline, double& dStartTime, double& dEndTime);

	///	Change data range, iType from 0 to 5, means start/end inline/xline/time, dVal is the new value. 
	///	Return false while iType beyond 0~5 or new end inline less than start inline and so on...
	bool SetDataRange(unsigned char iType, double dVal);

	///@brief Reimplement to save/load the data
    virtual bool SerializeData(CXArchive &ar);

	virtual QStringList GetDescription();

protected:
	virtual void _SetSelfDimension();

	// set histogram from another object
	virtual CXObject* _GetHistogramObject();

	int			m_iStartInline;
	int			m_iEndInline;
	int			m_iStartXline;
	int			m_iEndXline;
	double		m_dStartTime;
	double		m_dEndTime;
};

#endif