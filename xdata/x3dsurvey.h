#ifndef _CX3DSurvey_H__
#define _CX3DSurvey_H__

#include "xdata_global.h"
#include "xobject.h"
#include "xseismicutmtool.h"
#include "xdef.h"

class CXSeismicSection;
class CXSeismicSubVolume;
class CXSeismicDataVolume;

///@brief	The class provides data structure for 3-D survey
///@author	Xiong Xiong
///@date	Apr, 2014
class XDATA_EXPORT CX3DSurvey : public CXObject
{
public:
	CX3DSurvey();
	CX3DSurvey(const CXSeismicUTMTool& utm, const QString& strName);

	///@brief Get UTM
	CXSeismicUTMTool& GetUTM() { return m_utm; }

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	///@brief Get the default DV ID of the survey.
	CXSeismicDataVolume* GetDefaultDV(bool bIncludePrestack = true);

	///@brief Create default section.
	CXSeismicSection* CreateDefaultSection(EXSectionType eSectionType);

	///@brief Create default sub volume.
	CXSeismicSubVolume* CreateDefaultSubVolume();

	QList<CXObject*> FetchAllSections();

	virtual QStringList GetDescription();
	virtual QString GetTypeString() { return "3D Seismic Survey"; }
	CXObject* GetFolder(EXObjectType, bool bCreate = true);

	///@brief Serialize function
	virtual bool Serialize(bool bSave);

	///@brief Datum and replacement velocity
	void SetDatum(double dDatum);
	void SetRepVelocity(double dRepVel);
	void GetDatumAndRepVelocity(double& dDatum, double &dRepVel);

	///@breif Get all candidate volumes and lines that hold the given section.
	QList<CXObject *> GetAllCandidates(CXObject *);

private:
	CXSeismicUTMTool	m_utm;

	double m_dDatum, m_dRepVel;
};

#endif