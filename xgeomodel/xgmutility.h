#ifndef XGMUTILITY_H
#define XGMUTILITY_H

namespace NXGMUtility
{
	bool LineSegIntersect(double x1, double y1, double x2, double y2, 
		                  double x3, double y3, double x4, double y4,
						  double& x, double& y, double dTolerance = 1.0E-7);

};

#endif // RFGMUTILITY_H
