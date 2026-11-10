#ifndef _CXSEISMICTRACEINFO_HH_
#define _CXSEISMICTRACEINFO_HH_

#include "xdata_global.h"
#include <qstring.h>

class CXSeismicUTMTool;
class CXSeismicObject;
class CXSeismicDataVolume;
class CXSeismicSection;
struct SKETraceInfo;

using std::vector;

/**
* @class CXSeismicIrregularReader
* @brief The class provides traces information for irregular offsets pre-stack seismic data.
*
* @author Yong Shu
* @date 4/22/2014
* @see
*/
class XDATA_EXPORT CXSeismicIrregularReader
{
public:
	CXSeismicIrregularReader(unsigned short iMaxfold, CXSeismicUTMTool *pUTM, QString sFileName, int iGatherNum = 0);
	~CXSeismicIrregularReader();

	bool SaveToFile();

	char* GetBuffer();

	void SetAzimuth(bool bAzimuth)
	{
		m_bAzimuth = bAzimuth;
	}

	bool IsAzimuthVolume()
	{
		return m_bAzimuth;
	}

	unsigned short GetMaxFold()
	{
		return m_iMaxFold;
	}

	unsigned short GetMinOffset();
	unsigned short GetMaxOffset();
	short GetMinAzimuth();
	short GetMaxAzimuth();

	int GetInlineTraceQty(int iXline);

	int GetXlineTraceQty(int iInline);

	int GetSectionTraceQty(CXSeismicSection *);

	int GetRandomSectionTraceQty(vector<int>& vecInline, vector<int>& vecXline);

	bool ReadInline(CXSeismicObject *pDV, int iInlineNumber, float* pBuffer, SKETraceInfo* pTraceInfo);
	bool ReadXline(CXSeismicObject *pDV, int iXlineNumber, float* pBuffer, SKETraceInfo* pTraceInfo);
	bool ReadRandomSection(CXSeismicObject *pDV, vector<int>& vecInline, vector<int>& vecXline, float* pBuffer, SKETraceInfo* pTraceInfo);

	bool ReadInline(CXSeismicObject *pDV, int iInlineNumber, int iXlineMinNum, int iXlineMaxNum, double dStart, double dEnd, float* pBuffer, SKETraceInfo* pTraceInfo);
	bool ReadXline(CXSeismicObject *pDV, int iXlineNumber, int iInlineMinNum, int iInlineMaxNum, double dStart, double dEnd, float* pBuffer, SKETraceInfo* pTraceInfo);

	///@brief	Fill the map (length is nI * nJ, pre-allocated by caller.) with fold number of each CDP.
	void GetFoldMap(unsigned short *pFoldMap);

	///@brief	Get the trace number of the specified CDP.
	int GetTraceNumberAt(int iInline, int iXline);

	///@brief	Get the trace data and offset/azimuth info of the specified CDP.
	///			The space of pData should be pre-allocated and mananged by the caller.
	bool GetTraceDataAt(CXSeismicDataVolume *pDV, int iInline, int iXline, float *pData, QVector<float>& vecOffsetAziPair);

	///@brief Get offset according to specific inline and xline numbers
	void GetOffset(int iInline, int iXline, vector<int>& vecOffset);

	///@brief Tell if it only constains azimuth info
	bool ContainsAzimuthOnly();

private:
	bool				m_bAzimuth;
	unsigned short		m_iMinOffset;
	unsigned short		m_iMaxOffset;
	short				m_iMinAzi;
	short				m_iMaxAzi;
	unsigned short		m_iMaxFold;			//	Maximum fold count of the whole volume.
	
	int					m_iGatherNum;		//	NI * NJ, in case UTM not available.
	CXSeismicUTMTool*	m_pUTM;
	char*				m_pBuff;			//	Each CDP need 8 bytes position, 2 bytes actual trace number, 
											//	and 1(+1) * m_iMaxfold for offsets( + azimuth).
	QString				m_sFileName;
};

#endif