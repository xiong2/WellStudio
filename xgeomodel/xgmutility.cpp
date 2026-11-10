#include "xgmutility.h"
#include <qglobal.h>

bool NXGMUtility::LineSegIntersect(double x1, double y1, double x2, double y2, 
								  double x3, double y3, double x4, double y4,
						          double& x, double& y, double dTolerance)
{
	if ( qMin(x1,x2) > qMax(x3,x4) || 
		qMin(x3,x4) > qMax(x1,x2) || 
		qMin(y1,y2) > qMax(y3,y4) ||
		qMin(y3,y4) > qMax(y1,y2)   )
		return false;

	if (dTolerance < 1.0E-7)
		dTolerance = 1.0E-7;

	double a1, a2, a3, Ua, b1, b2, b3, Ub, det, det1, det2;
	/// first line Pa = P1 + Ua*(P2 - P1)	
	/// second line Pb = P3 + Ub*(P4 - P3)
	/// Ua(P2-P1) + Ub(P3-P4) = P3-P1 
	a1 = x2 - x1;
	a2 = x3 - x4;
	a3 = x3 - x1;
	b1 = y2 - y1;
	b2 = y3 - y4;
	b3 = y3 - y1;

	det = a1*b2 - a2*b1;
	det1 = a3*b2 - a2*b3;
	det2 = a1*b3 - a3*b1;

	if (qAbs(det) < dTolerance)	/// parallel
	{
		if (qAbs(det1) < dTolerance || qAbs(det2) < dTolerance)	///coincident
		{
			if (qAbs(a1) > qAbs(b1))
			{
				if ( (y1 > y3 && y1 > y4 && y2 > y3 && y2 > y4) || (y1 < y3 && y1 < y4 && y2 < y3 && y2 < y4) )
					return false;
				else
				{
					x = x1;
					y = y1;
					return true;
				}
			}
			else
			{
				if ( (x1 > x3 && x1 > x4 && x2 > x3 && x2 > x4) || (x1 < x3 && x1 < x4 && x2 < x3 && x2 < x4) )
					return false;
				else
				{
					x = x1;
					y = y1;
					return true;
				}
			}
		}
		else
			return false;
	}
	else
	{
		Ua  = det1/det;
		Ub = det2/det;

		if ( Ua>=0 && Ua <=1 && Ub>=0 && Ub<=1)
		{
			x = x1 + Ua*(x2 - x1);
			y = y1 + Ua*(y2 - y1);
			return true;
		}
		else
			return false;
	}

}
