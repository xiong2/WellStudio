#ifndef X3DSURFACE_H
#define X3DSURFACE_H

#include "xdata_global.h"
#include "xobject.h"
#include "xutmtool.h"

///@brief	The class provides data structure for 3-D surface
///@author	Yong Shu
///@date	Mar, 2014
///@see	

class XDATA_EXPORT CX3DSurface : public CXObject
{
public:
	CX3DSurface();
	CX3DSurface(const CXUTMTool& utm, const QString& strName);
	CX3DSurface(const CX3DSurface& other);
	~CX3DSurface();

	///@brief Get UTM
	virtual CXUTMTool& GetUTM() {return m_utm;}

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	virtual QString GetTypeString();
	virtual QStringList GetDescription();

	///@brief Set and get the data
	void SetData(float* pData);
	float* GetData();

	///@brief Set the data at (i, j)
	void SetData(int i, int j, float fData);

	///@brief Calculate intersection between 3-D surface/horizon and inline, xline or random section
	static void CalcIntersection(vector<double>& vecZ, CX3DSurface* p3DSurface, CXObject* pSection);

	virtual CX3DSurface* GetGeometryObject();

	///@brief Set the get dimension info	
	virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

	void TraceBoundaryPolygons();

protected:
	virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);
	virtual void _SetSelfDimension();

	virtual void _WriteData();
	virtual void _ReadData();

	CXUTMTool m_utm;

	float* m_pDataInMem;
};

#endif // RL3DSURFACE_H
