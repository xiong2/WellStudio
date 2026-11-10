#ifndef X3DHORIZON_H
#define X3DHORIZON_H

#include "xdata_global.h"
#include "x3dsurface.h"
#include "xseismicutmtool.h"
#include "xdef.h"
#include "gshorizongrid.h"

using std::vector;

enum EHorizonType
{
	eConformable,
	eUnconformable,
	eErosional,
	eBasement,
};

///@brief	The class provides data structure for 3-D horizon
///@author	Yong Shu
///@date	Oct., 2014
///@see	

class XDATA_EXPORT CX3DHorizon : public CX3DSurface
{
public:
	CX3DHorizon();
	CX3DHorizon(const QUuid& uuidSurvey, const CXSeismicUTMTool& utm, const QString& strName);
	CX3DHorizon(const CX3DHorizon& other);
	~CX3DHorizon();

	///@brief Get UTM
	CXSeismicUTMTool& GetUTM() { return m_utm; }

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	virtual QString GetTypeString();

	virtual QStringList GetDescription();


	///@brief Set and get survey ID
	void SetSurveyID(const QUuid& uuidSurvey) { m_uuidSurvey = uuidSurvey; }
	QUuid GetSurveyID() { return m_uuidSurvey; }

	virtual CX3DHorizon* GetGeometryObject();

	static void GetFractureInfo(const QUuid& uuidDensity, const QUuid& uuidAzimuth, int ndX, int ndY, float fMinThreshold, float fMaxThreshold, vector<float>& vecDensity, vector<float>& vecAzimth, vector<float>& vecColor);

	void SetObjectType(EXObjectType eObjType);

	///	Resample to the new UTM and interpolate the data, if the parameter is null, resample on original UTM.
	void Resample(CXSeismicUTMTool* pUTM = nullptr);

	///	Resample to the new UTM with the specified bin size.
	void Resample(float fBinSize);

	int GetBaseSHDirection()
	{
		return m_iSHDir;
	}

	void SetBaseSHDirection(int iBaseSHDir)
	{
		m_iSHDir = iBaseSHDir;
	}

	unsigned int GetPulse()
	{
		return m_iPulse;
	}

	void SetPulse(unsigned int iPulse)
	{
		m_iPulse = iPulse;
		SetModifiedFlag();
	}

	float GetPorePressure()
	{
		return m_fPorePressure;
	}

	void SetPorePressure(float fPp)
	{
		m_fPorePressure = fPp;
	}

	float GetIntervalVelocity()
	{
		return m_fIntervalVelocity;
	}

	void SetIntervalVelocity(float fVol)
	{
		m_fIntervalVelocity = fVol;
		SetModifiedFlag();
	}

	float GetHydroGradient()
	{
		return m_fHydroGradient;
	}

	void SetHydroGradient(float fGradient)
	{
		m_fHydroGradient = fGradient;
	}

	float GetLithoGradient()
	{
		return m_fLithoGradient;
	}

	void SetLithoGradient(float fGradient)
	{
		m_fLithoGradient = fGradient;
	}

	EHorizonType GetHorizonType()
	{
		return m_eHType;
	}

	void SetHorizonType(EHorizonType eType)
	{
		m_eHType = eType;
	}

	bool UsedByPP()
	{
		return m_bUsedByPP;
	}

	void SetUsedByPP(bool bUse)
	{
		m_bUsedByPP = bUse;
		SetModifiedFlag();
	}

	GSHorizonGrid& GetGrid()
	{
		return m_grid;
	}

private:
	CXSeismicUTMTool m_utm;

	QUuid m_uuidSurvey;

	QUuid			m_topHID;		//	Only valid for isopach.
	QUuid			m_bottomHID;	//	Only valid for isopach.
	unsigned int	m_iPulse = 0;
	int				m_iSHDir = -999.25;		//	Basic SHMax direction.
	float			m_fIntervalVelocity = 2000.;
	float			m_fHydroGradient = 10.;
	float			m_fLithoGradient = 22.;
	float			m_fPorePressure = 1.;
	bool			m_bUsedByPP = false;
	EHorizonType	m_eHType = eConformable;
	GSHorizonGrid	m_grid;
};


#endif // RL3DHORIZON_H
