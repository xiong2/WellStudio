#ifndef XLFMATTRIBUTE_H
#define XLFMATTRIBUTE_H


#include "xdataplus_global.h"
#include "xobject.h"
#include "xseismicutmtool.h"

template<typename T> class CXRegularDataReader;
class CXLFMGeometry;

/**
* @class CXLFMAttribute provided in the file "kelfmattribute.h"
* @brief The class provides data structure for attribute of the low frequency model
* @author Yong Shu
* @date 11/18/2015
*
* @see
* @bug No known bugs so far.
*/


class XDATAPLUS_EXPORT CXLFMAttribute : public CXObject
{
public:
	CXLFMAttribute();
	CXLFMAttribute(CXLFMGeometry* pLFMGeo,const QString& strName);
	~CXLFMAttribute();

	///@brief Get slice Number
	int GetNI() { return m_nI; }
	int GetNJ() { return m_nJ; }
	int GetNK() { return m_nK; }

	///@brief Get a slice data. The data buffer must be pre-allocated
	bool ReadOneSlice(int iIndex, float* pBuffer);

	///@brief Read a inline section data. The data buffer must be pre-allocated
	bool ReadOneSection(int iIndex, float* pBuffer);

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	///@briff Get LFM
	CXLFMGeometry* GetLFM();

	///@brief Get the description info
	virtual QStringList GetDescription();

	///@brief Set the get dimension info	
	virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

    virtual CXObject* GetGeometryObject();

private:
	void _Init();
	CXRegularDataReader<float>* _GetReader();

private:
	CXRegularDataReader<float>* m_pReader;

	QUuid m_uuidLFM;
	int m_nI, m_nJ, m_nK;

};

#endif // KELFMATTRIBUTE_H
