#ifndef _CXSeismicSection_H__
#define _CXSeismicSection_H__

#include "xdata_global.h"
#include "xobject.h"
#include "xdef.h"
#include "xseismicutmtool.h"

class CXSeismicDataVolume;

/*
* @brief The class provides data structure for a seismic section (inline, crossline or time slice).
* 
* @author Xiong Xiong 
* @date Apr, 2014
* @see 
*/
class  XDATA_EXPORT CXSeismicSection: public CXObject
{
public:
	CXSeismicSection(){}
	CXSeismicSection(EXSectionType eSectionType, double dLineNumber);
	CXSeismicSection(QString strPictureFile, int iLineID, int iStartTrace, int iEndTrace, double dStartTime, double dEndTime);

	QUuid GetSurveyID();

	virtual QString GetTypeString();

	EXSectionType GetSectionType() const { return m_eSectionType; }

	double GetSectionNumber() const { return m_dSectionLineNumber; }
	void SetSectionNumber(double lineNumber);

	CXSeismicDataVolume* GetDefaultDataVolume(bool bIncludePrestack = true);

	CXSeismicUTMTool GetUTM();

	///@brief For inline profile, get the file name.
	QString GetPictureFile() { return m_sPictureFile; }

	///@brief For inline profile, get geometry info.
	bool GetProfileGeometry(int& iLineNum, int& iStartTrace, int& iEndTrace, double& dStartTime, double& dEndTime);

	///@brief Reimplement to save/load the data
    virtual bool SerializeData(CXArchive &ar);

	void SetSectionRange(int iSTrace, int iETrace)
	{
		m_iStartTrace = iSTrace;
		m_iEndTrace = iETrace;
	}

	void GetSectionRange(int& iSTrace, int& iETrace)
	{
		iSTrace = m_iStartTrace;
		iETrace = m_iEndTrace;
	}

	int GetSectionIndex();
    double GetSectionIndexF();

	double GetLineStep();

protected:
	virtual void _SetSelfDimension();
	virtual CXObject* _GetHistogramObject();

protected:
	EXSectionType	m_eSectionType;
	double			m_dSectionLineNumber;
	int				m_iStartTrace = -1;
	int				m_iEndTrace = -1;

	//	Below members only used by eInlineProfile section.
	QString			m_sPictureFile;
	double			m_dStartTime;
	double			m_dEndTime;
};

#endif
