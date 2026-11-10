#ifndef XSURFACEAPI_H
#define XSURFACEAPI_H

#include "xdata_global.h"
#include <vector>
#include "xutmtool.h"

using std::vector;

class CX3DSurface;
class CX3DHorizon;
class CXSeismicUTMTool;

class XDATA_EXPORT CXSurfaceAPI
{
public:
	///@brief Interpolate one 3-D surface
	static void Interpolate(CX3DSurface* p3DSurface);

	///@brief Interpolate one newly allocated 3-D horizon into one specific seismic utm. The new 3-D horizon must be deleted from outside.
	static CX3DHorizon* InterpolateWithUTM(CX3DHorizon* p3DHorizon, CXSeismicUTMTool* pUTMTool);


	///@brief vecX, vecY, vecZ : well path
	///@brief utm : horizon utm
	///@breif pData: horizon data, data length from utm
	///@brief vecXYZ : one intersection point
	///@brief return true  if intersecting, false otherwise
	static bool CalcWellHorizonIntersection(vector<double>& vecX, vector<double>& vecY, vector<double>& vecZ, CXUTMTool& utm, float* pData, vector<double>& vecXYZ);

private:
	static void _Interpolation(float* pTargetData, int nI, int nJ, bool bWithValidIndex, int iValidIndex, int jValidIndex);
	
};

#endif // KESURFACEAPI_H
