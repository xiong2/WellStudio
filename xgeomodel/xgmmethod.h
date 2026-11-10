#ifndef XGMMETHOD_H
#define XGMMETHOD_H

#include "xgeomodel_global.h"
#include <osg/Array>
#include <vector>

using std::vector;

class CXGeneralFolder;
class CXObject;
class CXGMFault;


class XGEOMODEL_EXPORT CXGMMethod
{
public:
	static void ExtractFaultPillars(CXObject* pFaultFolder);

	static void AutoConnectFaults(CXObject* pModelFaultFolder);

	static bool CalcVerticesAndIndex(CXGMFault* pFault, std::vector<osg::Vec3d>& vecVertices, 
		                             vector<vector<int> >& vecVecIndex, vector<int>& vecCount, double dDistance=50);


private:
	
};

#endif // RFGMMETHOD_H
