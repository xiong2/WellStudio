#pragma warning( push ,0 )
#include <QtGlobal>
#include "xmathmacro.h"
#include "xgraphicsapi.h"
#include <cmath>
#include "xutility.h"
#include "xfunctiontemplate.h"

#pragma warning( pop )


bool CXGraphicsAPI::SegmentsPerpendicular(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double dToleranceAngle)
{
	double dotResult = (x2 - x1) * (x4 - x3) + (y2 - y1) * (y4 - y3);
	double scalarMul = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) * sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
	double angle = acos(dotResult / scalarMul);
	angle = angle / M_PI * 180;

	if (angle >= 90 - dToleranceAngle && angle <= 90 + dToleranceAngle)
		return true;

	return false;
}

double*  CXGraphicsAPI::_Add(double *p, const double *p1, const double *p2)
{
	p[0] = p1[0] + p2[0];
	p[1] = p1[1] + p2[1];
	p[2] = p1[2] + p2[2];
	return p;
}

double*  CXGraphicsAPI::_Subtract(double *p, const double *p1, const double *p2)
{
	p[0] = p1[0] - p2[0];
	p[1] = p1[1] - p2[1];
	p[2] = p1[2] - p2[2];
	return p;
}

double*  CXGraphicsAPI::_Multiply(double *p, const double *p1, double a)
{
	p[0] = p1[0]*a;
	p[1] = p1[1]*a;
	p[2] = p1[2]*a;
	return p;
}

double  CXGraphicsAPI::_Dot(const double *p1, const double *p2)
{
	return p1[0]*p2[0]+p1[1]*p2[1]+p1[2]*p2[2];
}

double*  CXGraphicsAPI::_Cross(double *p, const double *p1, const double *p2)
{
	p[0] = p1[1]*p2[2]- p1[2]*p2[1];
	p[1] = p1[2]*p2[0]- p1[0]*p2[2];
	p[2] = p1[0]*p2[1]- p1[1]*p2[0];
	return p;
}

bool CXGraphicsAPI::IsPointInsidePolygon(const double x, const double y, const double *pPolygonX, 
																	const double *pPolygonY, const int nPoints, double dTolerance)
{	
	int i, j;

	for (i=0; i<nPoints; i++)
	{
		if (qAbs(x - pPolygonX[i]) < dTolerance && qAbs(y - pPolygonY[i]) < dTolerance)
			return true;
	}

	bool bInside = false;
	for (i=0, j=nPoints-1; i<nPoints; j=i++)
	{
		if ( (pPolygonY[i] <= y && y < pPolygonY[j] || pPolygonY[j] <= y && y < pPolygonY[i]) &&
			 x < pPolygonX[i] + (pPolygonX[j] - pPolygonX[i])/(pPolygonY[j] - pPolygonY[i])*(y - pPolygonY[i]))
			 bInside = !bInside;
	}

	return bInside;
}

bool CXGraphicsAPI::IsPointInsidePolygon(const double x, const double y, const double *pDataXYZ, const int nPoints, double dTolerance)
{
    int i, j;

	for (i=0; i<nPoints; i++)
	{
		if (qAbs(x - pDataXYZ[3*i]) < dTolerance && qAbs(y - pDataXYZ[3*i+1]) < dTolerance)
			return true;
	}

	bool bInside = false;
	for (i=0, j=nPoints-1; i<nPoints; j=i++)
	{
		if ( (pDataXYZ[3*i+1] <= y && y < pDataXYZ[3*j+1] || pDataXYZ[3*j+1] <= y && y < pDataXYZ[3*i+1]) &&
			 x < pDataXYZ[3*i] + (pDataXYZ[3*j] - pDataXYZ[3*i])/(pDataXYZ[3*j+1] - pDataXYZ[3*i+1])*(y - pDataXYZ[3*i+1]))
			 bInside = !bInside;
	}

	return bInside;

}
bool CXGraphicsAPI::AreTwoLineSegmentsIntersecting(const double x1, const double y1, const double x2, const double y2, 
																	const double x3, const double y3, const double x4, const double y4, double dTolerance)
{
	if ( qMin(x1,x2) > qMax(x3,x4) || 
		 qMin(x3,x4) > qMax(x1,x2) || 
		 qMin(y1,y2) > qMax(y3,y4) ||
		 qMin(y3,y4) > qMax(y1,y2)   )
		 return false;
	
	if (dTolerance < 1.0E-8)
		dTolerance = 1.0E-8;

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
					return true;
			}
			else
			{
				if ( (x1 > x3 && x1 > x4 && x2 > x3 && x2 > x4) || (x1 < x3 && x1 < x4 && x2 < x3 && x2 < x4) )
					return false;
				else
					return true;
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
			return true;
		else
			return false;
	}
}

bool CXGraphicsAPI::IntersectionOfTwoLines(const float x1,const float y1,const float x2,const float y2,const float x3,const float y3,
		                     const float x4,const float y4,float& x, float& y,float fTolerance)
{	
	if ( qMin(x1,x2) > qMax(x3,x4) || 
		 qMin(x3,x4) > qMax(x1,x2) || 
		 qMin(y1,y2) > qMax(y3,y4) ||
		 qMin(y3,y4) > qMax(y1,y2)   )
		 return false;
	
	if (fTolerance < 1.0E-6f)
		fTolerance = 1.0E-6f;

	float a1, a2, a3, Ua, b1, b2, b3, Ub, det, det1, det2;
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

	if (qAbs(det) < fTolerance)	/// parallel
	{
		if (qAbs(det1) < fTolerance || qAbs(det2) < fTolerance)	///coincident
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

bool CXGraphicsAPI::IntersectionOfTwoLines(const double x1,const double y1,const double x2,const double y2,const double x3,const double y3,
		            const double x4,const double y4, double& x, double& y, double fTolerance)
{
	if ( qMin(x1,x2) > qMax(x3,x4) || 
		qMin(x3,x4) > qMax(x1,x2) || 
		qMin(y1,y2) > qMax(y3,y4) ||
		qMin(y3,y4) > qMax(y1,y2)   )
		return false;

	if (fTolerance < 1.0E-7)
		fTolerance = 1.0E-7;

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

	if (qAbs(det) < fTolerance)	/// parallel
	{
		if (qAbs(det1) < fTolerance || qAbs(det2) < fTolerance)	///coincident
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

void CXGraphicsAPI::AreLineSegmentPlaneIntersecting(int &iFlag, double *pIntersect, const double *p1, const double *p2, const double *p3, 
																		const double *pNorm, double dTolerance)
{
	/// the intersection point: P
	/// Norm dot (P - P3) = 0
	/// P = P1 + u(P2 - P1)
	/// Intersection: Norm dot (P1 + u(P2 - P1)) = N dot P3
	/// u = (Norm dot (P3 - P1) ) / (Norm dot (P2 -P1))
	/// point P1 must be different from point P2

	double temp[3], numer, denom, len0, len1, len2;

	len0 = _Dot(pNorm, pNorm);

	_Subtract(temp, p2, p1);
	len1 = _Dot(temp, temp);
	denom = _Dot(pNorm, temp);

	_Subtract(temp, p3, p1);
	len2 = _Dot(temp, temp);
	numer = _Dot(pNorm, temp);		

	if (qAbs(denom*denom/(len0*len1)) < dTolerance)
	{
		if (qAbs(numer*numer/(len0*len2)) < dTolerance) ///< line inside the plane
			iFlag = 0;
		else												///< parallel and outside the plane	
			iFlag = -1;
	}
	else													///< intersect 
	{
		double u;
		u = numer/denom;

		if (u>=0 && u<=1)
		{
			double temp1[3];
			iFlag = 1;
			_Multiply(temp1, _Subtract(temp, p2, p1), u);
			_Add(pIntersect, p1, temp1);
		}
		else
			iFlag = -1;
	}	
}

void CXGraphicsAPI::AreLineRectangleIntersecting(int &iFlag, double Intersect[3], double A[3], double B[3], double p0[3], 
		double p1[3], double p2[3], double p3[3], double dTolerance)
{
	double lineMin[3], lineMax[3], rectMin[3], rectMax[3];

	for (int i=0; i<3; ++i)
	{
		lineMin[i] = qMin(A[i], B[i]);
		lineMax[i] = qMax(A[i], B[i]);
		rectMin[i] = qMin(qMin(p0[i], p1[i]), qMin(p2[i], p3[i]));
		rectMax[i] = qMax(qMax(p0[i], p1[i]), qMax(p2[i], p3[i]));
	}

	if (!AreTwoBoxesIntersecting (lineMin[0],lineMin[1],lineMin[2], lineMax[0],lineMax[1],lineMax[2], 
														rectMin[0],rectMin[1],rectMin[2], rectMax[0],rectMax[1],rectMax[2]))
	{
		iFlag = -1;
		return;
	}

	double norm[3], pDiff1[3], pDiff2[2];

	_Subtract(pDiff1, p0, p1);
	_Subtract(pDiff2, p0, p3);
	_Cross(norm, pDiff1, pDiff2);

	AreLineSegmentPlaneIntersecting(iFlag, Intersect, A, B, p2, norm, dTolerance);

	if (iFlag != 1)
		return;

	if ( Intersect[0] < lineMin[0] || Intersect[0] > lineMax[0] ||
		  Intersect[1] < lineMin[1] || Intersect[1] > lineMax[1]  ||
		  Intersect[2] < lineMin[2] || Intersect[2] > lineMax[2]
	)
	{
		iFlag = -1;
		return;
	}			  
}

bool CXGraphicsAPI::AreTwoBoxesIntersecting(double x1min, double y1min, double z1min, double x1max, double y1max, double z1max,
																double x2min, double y2min, double z2min, double x2max, double y2max, double z2max)
{
	if( x1max < x1min ) qSwap( x1min,x1max );
	if( y1max < y1min ) qSwap( y1min,y1max );
	if( z1max < z1min ) qSwap( z1min,z1max );

	if( x2max < x2min ) qSwap( x2min,x2max );
	if( y2max < y2min ) qSwap( y2min,y2max );
	if( z2max < z2min ) qSwap( z2min,z2max );
	 
	if( x2min > x1max )
		return false;

	if( x1min > x2max )
		return false;

	if( y2min > y1max )
		return false;

	if( y1min > y2max )
		return false;

	if( z2min > z1max )
		return false;

	if( z1min > z2max )
		return false;

	return true;
}
bool CXGraphicsAPI::IsPointOnPolyline(int& ind, const float x, const float y, const float *pDataXY,
	const int nPoints, float fTolerance)
{
    if (nPoints <2)
    { 
        ind = -1;
        return false;
    }

    double p1[2], p2[2], p[2];
    int i, j;

    for (i=0, j=nPoints-1; i<nPoints; j=i++)
    {        
        // P1 = Point - Point1
		p1[0] = x - pDataXY[2 * i];
		p1[1] = y - pDataXY[2 * i + 1];

        // P2 = Point - Point2
		p2[0] = x - pDataXY[2 * j];
		p2[1] = y - pDataXY[2 * j + 1];

		double d1 = sqrt(p1[0] * p1[0] + p1[1] * p1[1]);
		double d2 = sqrt(p2[0] * p2[0] + p2[1] * p2[1]);
		double d = sqrt((p2[0] - p1[0]) * (p2[0] - p1[0]) + (p2[1] - p1[1]) * (p2[1] - p1[1]));

		if (d == 0 && d1 != 0)
			continue;
		else
		{
			if (qAbs(d - (d1 + d2)) / d < fTolerance)
			{
				ind = j;
				return true;
			}

		}

    }

    ind = -1;
    return false;
}

bool CXGraphicsAPI::IsPointOnPolyline(int& ind, const double x, const double y, const double *pDataXY,
	const int nPoints, float fTolerance)
{
	if (nPoints <2)
	{
		ind = -1;
		return false;
	}

	double p1[2], p2[2], p[2];
	int i, j;

	for (i = 0, j = nPoints - 1; i<nPoints; j = i++)
	{
		// P1 = Point - Point1
		p1[0] = x - pDataXY[2 * i];
		p1[1] = y - pDataXY[2 * i + 1];

		// P2 = Point - Point2
		p2[0] = x - pDataXY[2 * j];
		p2[1] = y - pDataXY[2 * j + 1];

		double d1 = sqrt(p1[0] * p1[0] + p1[1] * p1[1]);
		double d2 = sqrt(p2[0] * p2[0] + p2[1] * p2[1]);
		double d = sqrt((p2[0] - p1[0]) * (p2[0] - p1[0]) + (p2[1] - p1[1]) * (p2[1] - p1[1]));

		if (d == 0 && d1 != 0)
			continue;
		else
		{
			if (qAbs(d - (d1 + d2)) / d < fTolerance)
			{
				ind = j;
				return true;
			}

		}

	}

	ind = -1;
	return false;
}


bool CXGraphicsAPI::IsPointInsidePolygon(const float x, const float y, const float z, const float *pDataXYZ, 
		const int nPoints, float fTolerance)
{
    int i, j;

    for (i=0; i<nPoints; i++)
    {
        if (qAbs(x - pDataXYZ[3*i]) < fTolerance && qAbs(y - pDataXYZ[3*i+1]) < fTolerance)
            return true;
    }

    bool bInside = false;
    for (i=0, j=nPoints-1; i<nPoints; j=i++)
    {
        if ( (pDataXYZ[3*i+1] <= y && y < pDataXYZ[3*j+1] || pDataXYZ[3*j+1] <= y && y < pDataXYZ[3*i+1]) &&
            x < pDataXYZ[3*i] + (pDataXYZ[3*j] - pDataXYZ[3*i])/(pDataXYZ[3*j+1] - pDataXYZ[3*i+1])*(y - pDataXYZ[3*i+1]))
            bInside = !bInside;
    }

    return bInside;

}

bool CXGraphicsAPI::IsPointInsidePolygon(const float x, const float y, const float *pDataXY, const int nPoints, float fTolerance)
{
    int i, j;

    for (i=0; i<nPoints; ++i)
    {
        if (qAbs(x - pDataXY[2*i]) < fTolerance && qAbs(y - pDataXY[2*i+1]) < fTolerance)
            return true;
    }

    bool bInside = false;
    for (i=0, j=nPoints-1; i<nPoints; j=i++)
    {
        if ( (pDataXY[2*i+1] <= y && y < pDataXY[2*j+1] || pDataXY[2*j+1] <= y && y < pDataXY[2*i+1]) &&
            x < pDataXY[2*i] + (pDataXY[2*j] - pDataXY[2*i])/(pDataXY[2*j+1] - pDataXY[2*i+1])*(y - pDataXY[2*i+1]))
            bInside = !bInside;
    }

    return bInside;

}

bool CXGraphicsAPI::IsPointInsidePolygon(const int nPoints, const double x, const double y, const double *pDataXY, float fTolerance)
{
	int i, j;

	for (i = 0; i < nPoints; ++i)
	{
		if (qAbs(x - pDataXY[2 * i]) < fTolerance && qAbs(y - pDataXY[2 * i + 1]) < fTolerance)
			return true;
	}

	bool bInside = false;
	for (i = 0, j = nPoints - 1; i < nPoints; j = i++)
	{
		if ((pDataXY[2 * i + 1] <= y && y < pDataXY[2 * j + 1] || pDataXY[2 * j + 1] <= y && y < pDataXY[2 * i + 1]) &&
			x < pDataXY[2 * i] + (pDataXY[2 * j] - pDataXY[2 * i]) / (pDataXY[2 * j + 1] - pDataXY[2 * i + 1])*(y - pDataXY[2 * i + 1]))
			bInside = !bInside;
	}

	return bInside;

}
void CXGraphicsAPI::GetSplinePoints(std::vector<QPointF>& vecPoints, std::vector<QPointF> orgPoints, bool bClosed, int nInsertPoints, int nCurveRate)
{
	vecPoints.clear();
	int nNumPoints = orgPoints.size();
	if (nNumPoints <= 2)
	{
		for (int i=0; i< nNumPoints; ++i)
			vecPoints.push_back(orgPoints[i]);
	}
	else
	{
		double fCurveRate = (nCurveRate - 50.0)/50.0;
		double Point1[2], Point2[2], Point3[2], Point4[2];
		int i1, i2, i3, i4; 		
		for (int i=0; i<nNumPoints; ++i)
		{
			vecPoints.push_back(orgPoints[i]);
			i1 = i -1;
			i2 = i;
			i3 = i+1;
			i4 = i+2;

			if (i1 < 0)
				i1 += nNumPoints;
			if (i3 >=  nNumPoints)
				i3 -= nNumPoints;
			if (i4 >= nNumPoints)
				i4 -= nNumPoints;

			Point1[0] = orgPoints[i1].x();
			Point1[1] = orgPoints[i1].y();

			Point2[0] = orgPoints[i2].x();
			Point2[1] = orgPoints[i2].y();

			Point3[0] = orgPoints[i3].x();
			Point3[1] = orgPoints[i3].y();

			Point4[0] = orgPoints[i4].x();
			Point4[1] = orgPoints[i4].y();
			if (!bClosed)
			{
				if (i == nNumPoints - 1)
					continue;
				else if ( (i == 0) || (i ==  nNumPoints -2))
				{
					double fLength = NXUtility::CalDistance2D(Point2, Point3)*2;

					if (i == 0)
						NXUtility::ExtendLine2D(Point3, Point2, fLength, Point1);
					else
						NXUtility::ExtendLine2D(Point2, Point3, fLength, Point4);
				}
			}
			double fStep = 1.0/(nInsertPoints+1);
			double s, u3, u2, coef1, coef2, coef3, coef4, u =0.0;
			for(int nIpx = 0; nIpx < nInsertPoints; ++nIpx)
			{
				s = (1 - fCurveRate)*0.5;
				u += fStep;
				u2 = u*u;
				u3 = u2*u;
				coef1 = -s*u3 + 2*s*u2 - s*u;
				coef2 = (2 - s)*u3 + (s - 3)*u2 + 1;
				coef3 = (s - 2)*u3 + (3 - 2*s)*u2 + s*u;
				coef4 = s*(u3 - u2);
				float fX = static_cast<float>(Point1[0]*coef1+ Point2[0]*coef2+ Point3[0]*coef3+Point4[0]*coef4);
				float fY = static_cast<float>(Point1[1]*coef1+ Point2[1]*coef2+ Point3[1]*coef3+Point4[1]*coef4);				
				vecPoints.push_back(QPointF(fX,fY));
			}
		}
	}


}
void CXGraphicsAPI::GetSplinePoints(std::vector<float>& vecPoints, float* pRawPoints, int nNumPoints, bool bClosed, int nInsertPoints, int nCurveRate)
{
    if (!vecPoints.empty())
        vecPoints.clear();

    if (nNumPoints <= 2)
    {
        for (int i=0; i<nNumPoints*3; ++i)
            vecPoints.push_back(pRawPoints[i]);
    }
    else
    {
        double fCurveRate = (nCurveRate - 50.0)/50.0;
        double Point1[3], Point2[3], Point3[3], Point4[3];
        float Point[3];

		vecPoints.reserve(nNumPoints*(nInsertPoints+1)*3);

        int i1, i2, i3, i4;
        for (int i=0; i<nNumPoints; ++i)
        {
            for (int j=0; j<3; ++j)
                vecPoints.push_back(pRawPoints[i*3+j]);

            i1 = i -1;
            i2 = i;
            i3 = i+1;
            i4 = i+2;

            if (i1 < 0)
                i1 += nNumPoints;
            if (i3 >=  nNumPoints)
                i3 -= nNumPoints;
            if (i4 >= nNumPoints)
                i4 -= nNumPoints;

            Point1[0] = pRawPoints[i1*3];
            Point1[1] = pRawPoints[i1*3+1];
            Point1[2] = pRawPoints[i1*3+2];

            Point2[0] = pRawPoints[i2*3];
            Point2[1] = pRawPoints[i2*3+1];
            Point2[2] = pRawPoints[i2*3+2];

            Point3[0] = pRawPoints[i3*3];
            Point3[1] = pRawPoints[i3*3+1];
            Point3[2] = pRawPoints[i3*3+2];

            Point4[0] = pRawPoints[i4*3];
            Point4[1] = pRawPoints[i4*3+1];
            Point4[2] = pRawPoints[i4*3+2];

            // Handle the points on the edge
            if (!bClosed)
            {
                if (i == nNumPoints - 1)
                    continue;
                else if ( (i == 0) || (i ==  nNumPoints -2))
                {
                    double fLength = NXUtility::CalDistance(Point2, Point3)*2;
                    
                    if (i == 0)
                        NXUtility::ExtendLine(Point3, Point2, fLength, Point1);
                    else
                        NXUtility::ExtendLine(Point2, Point3, fLength, Point4);
                }
            }

            double fStep = 1.0/(nInsertPoints+1);
            double s, u3, u2, coef1, coef2, coef3, coef4, u =0.0;

            for (int j=0; j<nInsertPoints; ++j)
            {
                s = (1 - fCurveRate)*0.5;
                u += fStep;
                u2 = u*u;
                u3 = u2*u;
                coef1 = -s*u3 + 2*s*u2 - s*u;
                coef2 = (2 - s)*u3 + (s - 3)*u2 + 1;
                coef3 = (s - 2)*u3 + (3 - 2*s)*u2 + s*u;
                coef4 = s*(u3 - u2);

                Point[0] = static_cast<float>(Point1[0]*coef1+ Point2[0]*coef2+ Point3[0]*coef3+Point4[0]*coef4);
                Point[1] = static_cast<float>(Point1[1]*coef1+ Point2[1]*coef2+ Point3[1]*coef3+Point4[1]*coef4);
                Point[2] = static_cast<float>(Point1[2]*coef1+ Point2[2]*coef2+ Point3[2]*coef3+Point4[2]*coef4);

                vecPoints.push_back(Point[0]);
                vecPoints.push_back(Point[1]);
                vecPoints.push_back(Point[2]);
            }

        }
    }
}

void CXGraphicsAPI::LineSegmentRectIntersect(std::vector<double>& vecInside, double x[2], double y[2], double xRect[4], double yRect[4])
{
	bool b1 = IsPointInsidePolygon(x[0], y[0], xRect, yRect, 4);
	bool b2 = IsPointInsidePolygon(x[1], y[1], xRect, yRect, 4);

	if (b1 && b2)
	{
		vecInside.push_back (x[0]);
		vecInside.push_back (y[0]);
		vecInside.push_back (x[1]);
		vecInside.push_back (y[1]);
	}
	else if ( b1 || b2)
	{
		if (b1)
		{
			vecInside.push_back (x[0]);
			vecInside.push_back (y[0]);
		}
		int i, j;
		for (i=0; i<4; ++i)
		{
			j = i+1;
			if (j==4)
				j = 0;
			double xIntersect, yIntersect;
			if (IntersectionOfTwoLines(x[0], y[0], x[1], y[1], xRect[i], yRect[i], xRect[j], yRect[j], xIntersect, yIntersect))
			{
				vecInside.push_back (xIntersect);
				vecInside.push_back (yIntersect);
				break;
			}
		}
		if (b2)
		{
			vecInside.push_back (x[1]);
			vecInside.push_back (y[1]);
		}
	}
	else
	{
		int i, j, count = 2;
		for (i=0; i<4; ++i)
		{
			j = i+1;
			if (j==4)
				j = 0;
			double xIntersect, yIntersect;
			if (IntersectionOfTwoLines(x[0], y[0], x[1], y[1], xRect[i], yRect[i], xRect[j], yRect[j], xIntersect, yIntersect))
			{
				vecInside.push_back (xIntersect);
				vecInside.push_back (yIntersect);
				count--;
			}
			if (count == 0)
				break;
		}
	}
}

void CXGraphicsAPI::GetSegmentVertexIndices(std::vector<int>& vec, int nPointNum, double* pX, double* pY, float fEPS)
{
	if (nPointNum < 2)
		return;

	if (nPointNum == 2)
	{
		vec.push_back (0);
		vec.push_back (1);
		return;
	}

	vec.push_back (0);

	float fRadius = (qAbs(pX[0]) + qAbs(pY[0]))/2.0f*fEPS;

	float* pLineAngle = new float [nPointNum-1];
	float* pSideAngle = new float [nPointNum-1];

	int i=0, j=0;

	float x1, y1, x2, y2;
	float fDEG = (float)M_DEG;
	float fLineAnglePre, fSideAnglePre, fAngleDiff;

	while (i != nPointNum-1 )
	{
		for (j=i+1; j<nPointNum; ++j)
		{
			if (j == nPointNum -1)
			{
				vec.push_back(j);
				i = j ;
				break;
			}

			x1 = pX[j-1]; 
			x2 = pX[j];
			y1 = pY[j-1];
			y2 = pY[j];
			float fLineRangle = _GetDirection(x1, y1, x2, y2);
			float fLineLength = sqrt(SQR(x2-x1) + SQR(y2-y1));
			float fSideAngle = asin(fRadius/fLineLength)*fDEG;

			if (j == i+1)
			{
				pLineAngle[0] = fLineRangle;
				pSideAngle[0] = fSideAngle;
				continue;
			}

			int nLength = j-i-1;
			bool bIntersect = true;
			for (int k=0; k<nLength; ++k)
			{
				fLineAnglePre = pLineAngle[k];
				fSideAnglePre = pSideAngle[k];

				fAngleDiff = qAbs (fLineRangle - fLineAnglePre);
				if (fAngleDiff > 180.0f)
					fAngleDiff = 360.0f - fAngleDiff;

				if (fAngleDiff > fSideAnglePre + fSideAngle)
				{
					bIntersect = false;
					break;
				}					
			}

			if (bIntersect)
			{
				pLineAngle[j-i-1] = fLineRangle;
				pSideAngle[j-i-1] = fSideAngle;
			}
			else // polyline vertex
			{
				vec.push_back(j);
				i = j ;
				break;
			}
		} //j

	} //i

	delete []pLineAngle;
	delete []pSideAngle;
}

float CXGraphicsAPI::_GetDirection (float x1, float y1, float x2, float y2)
{
	float fAngle = atan2(y2-y1, x2-x1)*static_cast<float>(M_DEG);
	if (fAngle < 0.0f)
		fAngle += 360.0f;

	return fAngle;
}


double CXGraphicsAPI::GetPointToPolygonDistance(QVector3D vecPoint, double p0[3], double p1[3], double p2[3])
{
	QVector3D vecP0(p0[0],p0[1],p0[2]);
	QVector3D vecP1(p1[0],p1[1],p1[2]);
	QVector3D vecP2(p2[0],p2[1],p2[2]);

	if (vecP0.isNull() || vecP1.isNull()|| vecP2.isNull())
	{
		return -1;
	}

	QVector3D vecNormal = QVector3D::crossProduct((vecP0 - vecP1),(vecP0 - vecP2));
	//return vecPoint.distanceToPlane(vecP0,vecNormal);
	qreal real1 = QVector3D::dotProduct((vecPoint- vecP0),vecNormal);
	double dDistance = fabs(real1)/sqrt(QVector3D::dotProduct(vecNormal,vecNormal));
	return dDistance;
}

bool CXGraphicsAPI::IntersectLineSegmentAndTriangle(const CXVector3D& v1, const CXVector3D& v2, const CXVector3D& v3, const CXVector3D& lineStart,
	const CXVector3D& lineEnd, CXVector3D& intersection, double eps)
{
	CXVector3D edge12(v1, v2);
	CXVector3D edge13(v1, v3);
	CXVector3D lineDir(lineStart, lineEnd);

	CXVector3D lineDirXedge13 = lineDir.Cross(edge13);

	double factor = lineDirXedge13.Dot(edge12);
	if (qAbs(factor) < eps)
		return false;

	factor = 1.0 / factor;

	CXVector3D v1ToLineStart(v1, lineStart);
	double uPara = factor * v1ToLineStart.Dot(lineDirXedge13);
	if (uPara<0.0 || uPara>1.0)
		return false;

	CXVector3D v1ToLineStart_X_edge12 = v1ToLineStart.Cross(edge12);
	double vPara = factor * lineDir.Dot(v1ToLineStart_X_edge12);
	if (vPara<0.0 || vPara>1.0 || uPara + vPara > 1.0)
		return false;

	double tPara = factor * edge13.Dot(v1ToLineStart_X_edge12);
	if (tPara<0.0 || tPara>1.0)
		return false;

	intersection.SetValue(lineStart[0] + tPara*lineDir[0],
		lineStart[1] + tPara*lineDir[1],
		lineStart[2] + tPara*lineDir[2]);

	return true;

}

void CXGraphicsAPI::SegmentSimplification(double *pX, double *pY, double *pZ, int nSampleNum, std::vector<int>& vecIndex)
{
    const double MAX_DISTANCE = 1.0;
    vecIndex.assign(1, 0);

    uint nFirst = 0, nLast = nSampleNum - 1;

    while (nFirst < nLast)
    {
        double fMaxDistance = 0.0f;
        uint nMaxNum = -1;
        double dTotalDistance = (pX[nLast] - pX[nFirst])*(pX[nLast] - pX[nFirst]) + (pY[nLast] - pY[nFirst])*(pY[nLast] - pY[nFirst]) + (pZ[nLast] - pZ[nFirst])*(pZ[nLast] - pZ[nFirst]);

        //get the max distance that point (pX[i],pY[i],pZ[i]) to the line
        for (int i = nFirst + 1; i < nLast; i++)
        {
            double dCurDistance = (pX[i] - pX[nFirst])*(pX[i] - pX[nFirst]) + (pY[i] - pY[nFirst])*(pY[i] - pY[nFirst]) + (pZ[i] - pZ[nFirst])*(pZ[i] - pZ[nFirst]);
            double fTmp = (pX[nLast] - pX[nFirst])*(pX[i] - pX[nFirst]) + (pY[nLast] - pY[nFirst])*(pY[i] - pY[nFirst]) + (pZ[nLast] - pZ[nFirst])*(pZ[i] - pZ[nFirst]);
            fTmp *= fTmp / dTotalDistance;
            dCurDistance -= fTmp;
            if (dCurDistance > fMaxDistance)
            {
                fMaxDistance = dCurDistance;
                nMaxNum = i;
            }
        }
        if (fMaxDistance >= MAX_DISTANCE)
        {
            nLast = nMaxNum;
        }
        else//if abs(max or min)<MAX_DISTANCE then push it back 
        {
            vecIndex.push_back(nLast);
            nFirst = nLast;
            nLast = nSampleNum - 1;
        }
    }
}