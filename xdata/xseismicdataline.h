#ifndef _CX2DSEISMICSECTION_HH_
#define _CX2DSEISMICSECTION_HH_

#include "xseismicobject.h"
#include "xdef.h"

///@brief	The class provides one 2d line's seismic data.
///@author	Xiong Xiong
///@date	Sep, 2015
class XDATA_EXPORT CXSeismicDataLine: public CXSeismicObject
{
public:
	CXSeismicDataLine();
	CXSeismicDataLine(CXObject *pRefObj, double dSamplingStart, double dSamplingEnd, double dSamplingRate, const QString& strName = "Poststack Amplitude");
	CXSeismicDataLine(CXSeismicUTMTool utm, double dSamplingStart, double dSamplingEnd, double dSamplingRate, const QString& strName = "Poststack Amplitude");
	~CXSeismicDataLine();

	void SetOffsetInfo(int iMaxFold, float fStartOffset, float fOffsetStep)
	{
		m_iMaxFold = iMaxFold;
		m_fStartOffset = fStartOffset;
		m_fOffsetStep = fOffsetStep;
	}

	virtual unsigned int GetTraceNumber();

	///	Section may use its own trace range.
	virtual int GetSectionTraceQty(CXSeismicSection *);	

	virtual QStringList GetDescription();

	virtual QString GetTypeString();

	virtual CXObject* GetGeometryObject();

	EXSectionType GetDataLineType();

	int GetLineNumber();

	QUuid GetRefID()
	{
		return m_refID;
	}
	
	float* GetData();

	QUuid GetSurveyID() override;

	///@brief Reimplement to save/load the data
	virtual bool SerializeData(CXArchive &ar);

	///@brief Get the instance of trace info, only used by irregular offsets prestack volume.
	virtual CXSeismicIrregularReader* GetIrregularReader();

	///@brief Read partial section data. The buffer must be pre-allocated
	virtual bool ReadSection(CXSeismicSection *, float* pBuffer, SKETraceInfo* pTraceInfo = NULL);

protected:
	//virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);
	virtual void _SetSelfDimension();

	virtual void _WriteData();
	virtual void _ReadData();
	virtual void _freeMemory();

	float*			m_pDataInMem;

	QUuid			m_refID;			//	For 2D line or 3D random section.
};

#endif