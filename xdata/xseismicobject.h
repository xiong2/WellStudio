#ifndef _CXSEISMICOBJECT_H__
#define _CXSEISMICOBJECT_H__

#include "xobject.h"
#include "xdata_global.h"
#include "xseismicutmtool.h"

class CXSeismicIrregularReader;
class CXSeismicSection;

struct XDATA_EXPORT SKETraceInfo
{
	int	m_iLine;
	int m_iCDP;
	int m_iOffset;
	int m_iAzimuth;
	double m_dX;
	double m_dY;
};

class XDATA_EXPORT CXSeismicTraceHeader
{
public:
	int	m_iLine;
	int m_iCDP;
	double m_dX;
	double m_dY;
	double m_dOffset;
};

class  XDATA_EXPORT CXSeismicObject: public CXObject
{
public:
	CXSeismicObject();
	CXSeismicObject(double dSamplingStart, double dSamplingEnd, double dSamplingRate, const QString& strName = "");
	CXSeismicObject(const CXSeismicObject& other);
	~CXSeismicObject();

	virtual unsigned int GetTraceNumber() = 0;

	///	Section may use its own trace range.
	virtual int GetSectionTraceQty(CXSeismicSection *) = 0;

	virtual bool IsPrestack()
	{
		return m_iMaxFold > 1;
	}

	unsigned int GetMaxFold()
	{
		return m_iMaxFold;
	}

	void GetOffsetInfo(float& fStartOffset, float& fOffsetStep, int& iNumOffset)
	{
		fStartOffset = m_fStartOffset;
		fOffsetStep = m_fOffsetStep;
		iNumOffset = m_iMaxFold;
	}

	bool IsAzimuth();

	bool IsIrregular()
	{
		return m_iMaxFold > 1 && m_fOffsetStep == 0.;
	}

	int GetSamplingQty();

	float GetSampleInterval() { return m_dSamplingRate; }

	void ShiftStartSamplingTo(double dStartZ);

	void GetSamplingRange(double& dStartZ, double& dStopZ, double& dStep);

	///@brief Reimplement to save/load the data
	virtual bool SerializeData(CXArchive &ar);

	virtual QUuid GetSurveyID() = 0;

	QString GetTraceFileName();

	///@brief Only used by irregular offsets pre-stack volume.
	QString GetTraceInfoFileName();

	///@brief Get the instance of trace info, only used by irregular offsets prestack volume.
	virtual CXSeismicIrregularReader* GetIrregularReader() = 0;

	///@brief Read partial section data. The buffer must be pre-allocated
	virtual bool ReadSection(CXSeismicSection *, float* pBuffer, SKETraceInfo* pTraceInfo = NULL) = 0;

	///@brief Get the UTM
	CXSeismicUTMTool& GetUTM() { return m_utm; };

protected:
	//	below parameters used for prestack volume.
	float	m_fStartOffset;
	float	m_fOffsetStep;				//	For pre-stack, if the step is 0, means irregular offsets.
	int		m_iMaxFold;					//	number of offsets greater than 1 means pre-stack.

	CXSeismicUTMTool m_utm;

	double	m_dSamplingStart;
	double	m_dSamplingEnd;
	double	m_dSamplingRate;

	CXSeismicIrregularReader*		m_pIrregularReader;		//	Only used by irregular offsets prestack volume.
};

#endif