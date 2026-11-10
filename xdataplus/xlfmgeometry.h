#ifndef XLFMGEOMETRY_H
#define XLFMGEOMETRY_H

#include "xdataplus_global.h"
#include "xobject.h"
#include "xseismicutmtool.h"

template<typename T> class CXRegularDataReader;

/**
* @class CXLFMGeometry provided in the file "kelfmgeometry.h"
* @brief The class provides data structure for geometry of the low frequency model
* @author Yong Shu
* @date 11/18/2015
*
* @see
* @bug No known bugs so far.
*/


class XDATAPLUS_EXPORT CXLFMGeometry : public CXObject
{
public:
	CXLFMGeometry();
	CXLFMGeometry(const QUuid& uuidSurveyID, const CXSeismicUTMTool& utm, int nK, const QString& strName);
	~CXLFMGeometry();

	///@brief Get UTM
	CXSeismicUTMTool& GetUTM();

	virtual QString GetTypeString() { return "Structure Model"; }

	///@brief Get slice Number
	int GetNK() { return m_nK; }

	///@brief Get Survey ID
	QUuid GetSurveyID() { return m_uuidSurveyID; }

	///@brief Get a slice data. The data buffer must be pre-allocated
	bool ReadOneSlice(int iIndex, float* pBuffer);
	
	///@brief Read a inline section data. The data buffer must be pre-allocated
	bool ReadOneSection(int iIndex, float* pBuffer);

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	///@brief Get the description info
	virtual QStringList GetDescription();

	///@brief Set and get horizon indices
	void SetHorizonIndex(const std::vector<int>& vecHorizonIndex) {	m_vecHorizonIndex = vecHorizonIndex; }
	std::vector<int> GetHorizonIndex() { return m_vecHorizonIndex; }

	///@brief Set and get zone name list
	void SetZoneNameList(const QStringList& strListZoneName) { m_strListZoneName = strListZoneName; }
	QStringList GetZoneNameList() { return m_strListZoneName; }

protected:
	//virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);
	virtual void _SetSelfDimension();


private:
	void _Init();
	CXRegularDataReader<float>* _GetReader();

private:
	CXRegularDataReader<float>* m_pReader;

	QUuid m_uuidSurveyID;

	CXSeismicUTMTool m_utm;

	int m_nK;

	std::vector<int> m_vecHorizonIndex;
	QStringList m_strListZoneName;
	
};

#endif // KELFMGEOMETRY_H
