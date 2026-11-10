#ifndef XSEISMICDATAVOLUME_H
#define XSEISMICDATAVOLUME_H

#include "xseismicobject.h"
#include "xdata_global.h"

template<typename T> class CXRegularDataReader;
class CXSeismicSection;
class CXSeismicRandomSection;
class CXSeismicSubVolume;

/**
* @class CXSeismicDataVolume in the file "rlseismicdatavolume.h"
* @brief The class provides data structure for a post-stack seismic data volume
* 
* @author Yong Shu 
* @date 4/22/2014
* @see 
*/
class  XDATA_EXPORT CXSeismicDataVolume : public CXSeismicObject
{
	friend class CXSeismicSection;
	friend class CXSeismicRandomSection;
	friend class CXSeismicSubVolume;
public:
	///@brief Constructor and destructor
    CXSeismicDataVolume ();
	CXSeismicDataVolume (const CXSeismicUTMTool& utm, double dSamplingStart, double dSamplingEnd, double dSamplingRate, 
		const QString& strName = "", int iMaxFold = 1, float fStartOffset = 0., float fOffsetStep = 0., bool bAzimuth = false);
	CXSeismicDataVolume(const CXSeismicDataVolume& other);
	
    virtual ~CXSeismicDataVolume (); 

	virtual QString GetTypeString();

	virtual unsigned int GetTraceNumber();	

	///@brief Get three dimensions
	int GetInlineQty();
	int GetXlineQty();

	///	For poststack volume, the same as inline/xline qty; for prestack, multiple by offset number; for irregular volume...
	int GetInlineTraceQty(int iXline = -1);
	int GetXlineTraceQty(int iInline = -1);

	///	Section may use its own trace range.
	virtual int GetSectionTraceQty(CXSeismicSection *);

	int GetRandomSectionTraceQty(CXSeismicRandomSection *);

	///	For regular volume, it's inline * xline * offset number; for irregular volume...
	qint64 GetTotalTraceQty();

	///@brief Tell if there are some specific format data available
	bool HasTraceFile();
	bool HasSliceFile();
	bool HasBrickFile();

	///@brief Get file names
	QString GetSliceFileName();
	QString GetBrickFileName();

	///@brief Reader data. The buffer must be pre-allocated
	bool ReadInline(int iInlineNumber, float* pBuffer, SKETraceInfo* pTraceInfo = NULL);
	bool ReadXline(int iXlineNumber, float* pBuffer, SKETraceInfo* pTraceInfo = NULL);
	bool ReadSlice(double dZValue, float* pBuffer);
	bool ReadRandomSection(CXSeismicRandomSection* pRandomSec, float* pBuffer, SKETraceInfo* pTraceInfo = NULL);

	///@brief Read partial section data. The buffer must be pre-allocated
	virtual bool ReadSection(CXSeismicSection *, float* pBuffer, SKETraceInfo* pTraceInfo = NULL);
	bool ReadInline(int iInlineNum, int iXlineMinNum, int iXlineMaxNum, double dStart, double dEnd, float* pBuffer, SKETraceInfo* pTraceInfo = NULL);
	bool ReadXline(int iXlineNum, int iInlineMinNum, int iInlineMaxNum, double dStart, double dEnd, float* pBuffer, SKETraceInfo* pTraceInfo = NULL);
	bool ReadSlice(double dSampling, int iInlineMinNum, int iInlineMaxNumx, int iXlineMinNum, int iXlineMaxNum, float* pBuffer);

	///@brief Get the survey ID
	QUuid GetSurveyID();

	///@brief Get the max value
	float GetMaxValue();

	virtual QStringList GetDescription(); 

	///@brief Tell if two volumes are same size
	bool IsSameSizeWith(CXSeismicDataVolume* pOther);

	///@brief Get all volumes with the same size, including itself.
	void GetAllDVWithSameSize(QList<CXObject *>& listDV);

	///@brief	Fill the map (length is nI * nJ, pre-allocated by caller.) with fold number of each CDP.
	///	Note the blank CDP filled by 0 while importing will have the fold number of 0. 
	void GetFoldMap(unsigned short *pFoldMap);

	///@brief	Get the trace number of the specified CDP.
	int GetTraceNumberAt(int iInline, int iXline);

	///@brief	Get the trace data and offset/azimuth info of the specified CDP.
	///			The space of pData should be pre-allocated and mananged by the caller.
	bool GetTraceDataAt(int iInline, int iXline, float *pData, QVector<float>& vecOffsetAziPair);

	///@brief Get offset according to specific inline and xline numbers
	void GetOffset(int iInline, int iXline, vector<int>& vecOffset);

	///@brief Get the instance of trace info, only used by irregular offsets prestack volume.
	virtual CXSeismicIrregularReader* GetIrregularReader();

	///@brief Tell if it only constains azimuth info
	bool ContainsAzimuthOnly();

	///@brief 
	static void GetFractureInfo(const QUuid& uuidDensity, const QUuid& uuidAzimuth, double dSliceNum, int ndX, int ndY, float fMinThreshold, float fMaxThreshold, vector<float>& vecDensity, vector<float>& vecAzimth, vector<float>& vecColor);

protected:
	//virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);
	virtual void _SetSelfDimension();

private:
	bool _GetTraceReader();
	bool _GetSliceReader();

	void _ConvertNumToIndex(int iInlineNum, int iXlineNum, double dSampling, int& iInline, int& iXline, int& iSamling);

private:
	CXRegularDataReader<float>* m_pTraceReader;

	CXRegularDataReader<float>* m_pSliceReader;
};

#endif // RLSEISMICDATAVOLUME_H
