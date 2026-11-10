#ifndef XLFMUPSCALINGATTRIBUTE_H
#define XLFMUPSCALINGATTRIBUTE_H

#include "xdataplus_global.h"
#include "xobject.h"
#include <QMap>
#include <vector>

using std::vector;

class CXLFMUpscalingGeometry;


/**
* @class CXLFMUpscalingAttribute provided in the file "kelfmupscalingattribute.h"
* @brief The class provides data structure for upscaling attribute
* @author Yong Shu
* @date 11/124/2015
*
* @see
* @bug No known bugs so far.
*/


class XDATAPLUS_EXPORT CXLFMUpscalingAttribute : public CXObject
{
public:
	CXLFMUpscalingAttribute();
	CXLFMUpscalingAttribute(CXLFMUpscalingGeometry* pGeo, const QString& strName);
	~CXLFMUpscalingAttribute();	

	///@brief Add one well attribute
	void AddOneWell(const QUuid& uuidWell, vector<double>& vecData);

	///@brief Get one well info
	void GetOneWellInfo(const QUuid& uuidWell, vector<double>& vecData);

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	///@brief Get the description info
	virtual QStringList GetDescription();

	///@brief Get LFM geometry
	CXLFMUpscalingGeometry* GetUpscalingGeometry();

	///@brief Get All Well list 
	QList<QUuid> GetAllWellList() { return m_mapWellToCellNum.keys(); }

	///@brief Get one slice 
	bool GetOneSliceInfo(int iSliceIndex, int& nCellNum, int* pIndex, double* pX, double* pY, double* pValue);

	///@brief Set the get dimension info	
	virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

	virtual CXObject* GetGeometryObject() override;

protected:
	virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);

private:
	void _Init();
	void _FreeMemory();

private:
	QUuid m_uuidGeometry;

	QMap<QUuid, int> m_mapWellToCellNum;

	QMap<QUuid, double*> m_mapWellToData; // data length : nCellNum

};

#endif // KELFMUPSCALINGATTRIBUTE_H
