#ifndef XLFMUPSCALINGGEOMETRY_H
#define XLFMUPSCALINGGEOMETRY_H

#include "xdataplus_global.h"
#include "xobject.h"
#include <QMap>
#include <vector>

using std::vector;

class CXLFMGeometry;


/**
* @class CXLFMUpscalingGeometry provided in the file "kelfmupscalinggeometry.h"
* @brief The class provides data structure for geometry of intersection between well and low frequency model
* @author Yong Shu
* @date 11/124/2015
*
* @see
* @bug No known bugs so far.
*/


class XDATAPLUS_EXPORT CXLFMUpscalingGeometry : public CXObject
{
public:
	CXLFMUpscalingGeometry();
	CXLFMUpscalingGeometry(CXLFMGeometry* pLFM, const QString& strName);
	~CXLFMUpscalingGeometry();

	///@brief Add one well data
	///@brief pXYZ length: 8*3*nCellNum, pTopZ length: nCellNum, pBotZ length: nCellNum
	void AddOneWell(const QUuid& uuidWell, int nCellNum, qint64* pIndex, double* pXYZ, double* pTopZ, double* pBotZ);

	///@brief Get one well info
	void GetOneWellInfo(const QUuid& uuidWell, vector<qint64>& vecIndex, vector<double>& vecXYZ, vector<double>& vecTopZ, vector<double>& vecBotZ);

	///@brief Get one well info
	void GetOneWellInfo(const QUuid& uuidWell, vector<double>& vecTopZ, vector<double>& vecBotZ);

	///@brief Get number of the total cells
	int GetTotalCellNum();

	///@brief Get LFM geometry
	CXLFMGeometry* GetLFMGeometry();

	///@brief Get all well IDs
	QList<QUuid> GetAllWellID();

	///@brief Get cell number for given well
	int GetCellNum(const QUuid& uuidWell) { return m_mapWellToCellNum.value(uuidWell); }

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	///@brief Get the description info
	virtual QStringList GetDescription();

	///@brief Get map to index
	QMap<QUuid, qint64*>& GetWellMapToIndex() { return m_mapWellToDIndex; }

	///@brief Set the get dimension info	
	virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

protected:
	virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);
private:
	void _Init();
	void _FreeMemory();

private:
	QUuid m_uuidLFM;

	QMap<QUuid, int> m_mapWellToCellNum;
	QMap<QUuid, qint64*> m_mapWellToDIndex;
	QMap<QUuid, double*> m_mapWellToData; //8*3*cellNum (xyz) + cellNum (topZ) + cellNum (bottomZ)
};

#endif // KELFMUPSCALINGGEOMETRY_H
