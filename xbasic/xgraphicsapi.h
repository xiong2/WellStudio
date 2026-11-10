#ifndef XGRAPHICSAPI_H
#define XGRAPHICSAPI_H

#include "xbasic_global.h"
#include <vector>
#include <QVector3D>
#include "xvector3d.h"
#include "xmathmacro.h"

/**
* @class CXGraphicsAPI in the file "rlgraphicsapi.h"
* @brief The file defines some common functions for basic graphic operations.
* 
* @author Yong Shu 
* @date 5/21/2014
* @see 
* @bug	No Known bugs so far
*/

class XBASIC_EXPORT CXGraphicsAPI
{
public:

	static bool IsPointOnPolyline(int& ind, const double x, const double y, const double *pDataXY,
		const int nPoints, float fTolerance = 0.1f);
	/**
	* @brief	Whether the specific point on a line.
	* @param[out] ind: The index of the vertex that before the point, or -1 if not on the line.
	* @param[in] x:	x coordinate of the specific point.
	* @param[in] y: y coordinate of the specific point.
	* @param[in] z: z coordinate of the specific point.
	* @param[in] pDataXYZ: triplet of x, y, z to specify a 3-D polyline.
	* @param[in] nPoints: number of vertices of the polyline.
	* @return: True: specific point on the line.
	*/
	static bool IsPointOnPolyline(int& ind, const float x, const float y, const float *pDataXY, 
		const int nPoints, float fTolerance = 0.1f);

	/**
	* @brief	Whether the specific point inside a polygon.
	* @param[in] x:	x coordinate of the specific point.
	* @param[in] y: y coordinate of the specific point.
	* @param[in] z: z coordinate of the specific point.
	* @param[in] pDataXYZ: triplet of x, y, z to specify a 3-D polygon.
	* @param[in] nPoints: number of vertices of the polygon.
	* @return: True: specific point inside the polygon.
	*/
	static bool IsPointInsidePolygon(const float x, const float y, const float z, const float *pDataXYZ, 
		const int nPoints, float fTolerance = 1.0E-5);

	/**
	* @brief Tell if the point is inside the polygon or not 
	* @param[in] x:  abscissa of the point
	* @param[in] y: ordinate of the point 
	* @param[in] pPolygonX: an array of abscissas of the polygon 
	* @param[in] pPolygonY: an array of ordinates of the polygon
	* @param[in] nPoints: the number of vertices of the polygon
	* @param[in] dTolerance: the calculation tolerance
	* @return: True: inside or on the edge, False: outside
	* @see 
	*/
	static bool IsPointInsidePolygon(const double x, const double y, const double *pPolygonX, const double *pPolygonY, 
		const int nPoints, double dTolerance = 1.0E-5);

	/**
	* @brief Tell if the point is inside the polygon or not 
	* @param[in] x:  abscissa of the point
	* @param[in] y: ordinate of the point 
	* @param[in] pDataXYZ: an array of X0Y0Z0, X1Y1Z1, X2Y2Z2..., buffer length: 3*nPoints;
	* @param[in] nPoints: the number of vertices of the polygon
	* @param[in] dTolerance: the calculation tolerance
	* @return: True: inside or on the edge, False: outside
	* @see 
	*/
	static bool IsPointInsidePolygon(const double x, const double y, const double *pDataXYZ, const int nPoints, double dTolerance = 1.0E-5);


	/**
	* @brief Tell if the point is inside the polygon or not 
	* @param[in] x:  abscissa of the point
	* @param[in] y: ordinate of the point 
	* @param[in] pDataXY: an array of X0Y0, X1Y1, X2Y2..., buffer length: 2*nPoints;
	* @param[in] nPoints: the number of vertices of the polygon
	* @param[in] fTolerance: the calculation tolerance
	* @return: True: inside or on the edge, False: outside
	* @see 
	*/
	static bool IsPointInsidePolygon(const float x, const float y, const float *pDataXY, const int nPoints, float fTolerance = 1.0E-5);

	/**
	* @brief Tell if the point is inside the polygon or not
	* @param[in] x:  abscissa of the point
	* @param[in] y: ordinate of the point
	* @param[in] pDataXY: an array of X0Y0, X1Y1, X2Y2..., buffer length: 2*nPoints;
	* @param[in] nPoints: the number of vertices of the polygon
	* @param[in] fTolerance: the calculation tolerance
	* @return: True: inside or on the edge, False: outside
	* @see
	*/
	static bool IsPointInsidePolygon(const int nPoints, const double x, const double y, const double *pDataXY, float fTolerance = 1.0E-5);



	/**
	* @brief Tell if two line segments intersect or not
	* @param[in] x1, y1 : abscissa and ordinate of the start point of the first line segment
	* @param[in] x2, y2 : abscissa and ordinate of the end point of the first line segment
	* @param[in] x3, y3 : abscissa and ordinate of the start point of the second line segment
	* @param[in] x4, y4 : abscissa and ordinate of the end point of the second line segment
	* @param[in] dTolerance: the calculation tolerance
	* @return True: insection, False: not intersect
	* @see 
	*/
	static bool AreTwoLineSegmentsIntersecting(const double x1, const double y1, const double x2, const double y2, 
		const double x3, const double y3, const double x4, const double y4, double dTolerance = 1.0E-8);

	/**
	* @brief Tell if two line segments intersect or not
	* @param[in] x1, y1 : abscissa and ordinate of the start point of the first line segment
	* @param[in] x2, y2 : abscissa and ordinate of the end point of the first line segment
	* @param[in] x3, y3 : abscissa and ordinate of the start point of the second line segment
	* @param[in] x4, y4 : abscissa and ordinate of the end point of the second line segment
	* @param[in] dTolerance: the calculation tolerance
	* @param[out] x, y: abscissa and ordinate of the intersection
	* @return True: insection, False: not intersect
	* @see 
	*/
	static bool IntersectionOfTwoLines(const float x1,const float y1,const float x2,const float y2,const float x3,const float y3,
		const float x4,const float y4,float& x, float& y,float fTolerance = 1.0E-6);

	/**
	* @brief Tell if two line segments intersect or not
	* @param[in] x1, y1 : abscissa and ordinate of the start point of the first line segment
	* @param[in] x2, y2 : abscissa and ordinate of the end point of the first line segment
	* @param[in] x3, y3 : abscissa and ordinate of the start point of the second line segment
	* @param[in] x4, y4 : abscissa and ordinate of the end point of the second line segment
	* @param[in] dTolerance: the calculation tolerance
	* @param[out] x, y: abscissa and ordinate of the intersection
	* @return True: insection, False: not intersect
	* @see 
	*/
	static bool IntersectionOfTwoLines(const double x1,const double y1,const double x2,const double y2,const double x3,const double y3,
		const double x4,const double y4, double& x, double& y, double fTolerance = 1.0E-7);

	/**
	* @brief Tell if one line segment and one plane intersect
	* @param[out] iFlag : -1: not intersect, 0: inside the plane, 1: intersect
	* @param[out] pIntersect : return the intersection point if (iFlag == 1)
	* @param[in] p1 : the first point of the line segment
	* @param[in] p2 : the second point of the line segment
	* @param[in] p3 : the point in the plane
	* @param[in] pNorm : the normal direction of the plane
	* @param[in] dTolerance: the calculation tolerance
	* @prerequisite:  the point p1 must be different from the point p2 and the norm vector is non-zero
	* @return 
	* @see 
	*/
	static void AreLineSegmentPlaneIntersecting(int &iFlag, double *pIntersect, const double *p1, const double *p2, const double *p3, 
		const double *pNorm, double dTolerance = 1.0E-8);

	/**
	* @brief Tell if one line segment and one rectangle intersect
	* @param[out] iFlag : -1: not intersect, 0: inside the plane, 1: intersect
	* @param[out] pIntersect : return the intersection point if (iFlag == 1)
	* @param[in] A, B : the first and second points of the line segment
	* @param[in] p0, p1, p2, p3 : four vertices of the rectangle
	* @param[in] dTolerance: the calculation tolerance
	* @prerequisite:  the point p1 must be different from the point p2 and the norm vector is non-zero
	* @return 
	* @see 
	*/
	static void AreLineRectangleIntersecting(int &iFlag, double Intersect[3], double A[3], double B[3], double p0[3], 
		double p1[3], double p2[3], double p3[3], double dTolerance = 1.0E-8);

	/**
	* @brief Tell if two 3-D boxes are intersecting
	* @param[in] x1min, y1min, z1min : the minimum xyz coordinates for the first box
	* @param[in] x1max, y1max, z1max : the maximum xyz coordinates for the first box
	* @param[in] x2min, y2min, z2min : the minmum xyz coordinates for the first box
	* @param[in] x2max, y2max, z2max : the maximum xyz coordinates for the first box
	* @return true: if intersect; false otherwise
	*/
	static bool AreTwoBoxesIntersecting(double x1min, double y1min, double z1min, double x1max, double y1max, double z1max,
		double x2min, double y2min, double z2min, double x2max, double y2max, double z2max);

	/**
	* @brief Get the array of vertices of the smooth polyline generated from a polyline
	* @param[out] vecPoints :  smooth vertices
	* @param[in] pRawPoints : original vertices of the polyline 
	* @param[in] nNumPoints : number of the original vertices
	* @param[in] bClosed : if the polyline is closed
	* @param[in] nInsertPoints : number of the interpolation points between two adjacent vertices
	* @param[in] nCurveRate : curve rate
	*/
	static void GetSplinePoints(std::vector<float>& vecPoints, float* pRawPoints, int nNumPoints, bool bClosed=true, int nInsertPoints=20, int nCurveRate=50);

	static void GetSplinePoints(std::vector<QPointF>& vecPoints,std::vector<QPointF> orgPoints, bool bClosed=true, int nInsertPoints=20, int nCurveRate=50);

	/**
	* @brief Get the the end points of a line segment inside the rectangle 
	* @param[out] vecInside :  inside points
	* @param[in] x[2], y[2] : the first and second points of the line segment
	* @param[in] xRect[4], yRect[4] : the four vertices of the rectangle
	*/
	static void LineSegmentRectIntersect(std::vector<double>& vecInside, double x[2], double y[2], double xRect[4], double yRect[4]);

	static void GetSegmentVertexIndices (std::vector<int>& vec, int nPointNum, double* pX, double* pY, float fEPS);


	static double GetPointToPolygonDistance(QVector3D vecPoint, double p0[3], double p1[3], double p2[3]);

	///@brief Intersection between line segment and triangle
	///@brief three vertices: v1, v2, v3
	///@brief Line segment: lineStart, lineEnd
	///@brief Intersection point: intersection
	static bool IntersectLineSegmentAndTriangle(const CXVector3D& v1, const CXVector3D& v2, const CXVector3D& v3, const CXVector3D& lineStart,
										   const CXVector3D& lineEnd, CXVector3D& intersection, double eps = M_DEPS);

    ///@brief segment simplification.
    ///@param[out] vecIndex : point index list after simplification.
    ///@param[in] pX, pY, pZ : the point coordinates.
    ///@param[in] nSampleNum : the size of point array.
    static void SegmentSimplification(double *pX, double *pY, double *pZ, int nSampleNum, std::vector<int>& vecIndex);

	//!@brief segment0 perpendicular to segment1.
	//!@param[out] bool
	//!@param[in] double [(x1, y1), (x2, y2)], [(x3, y3), (x4, y4)]
	//!@param[in] double angle dTolerance.
	static bool SegmentsPerpendicular(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double dToleranceAngle = 1.0);

private:
	// Add two points P = P1 + P2
	static inline double*  _Add(double *p, const double *p1, const double *p2);

	// Subtract two points P = P1 - P2
	static inline double* _Subtract(double *p, const double *p1, const double *p2);

	// Multiply one point by a double P = P1*a
	static inline double *_Multiply(double *p, const double *p1, double a);

	// Dot product of two points  P1 dot P2
	static inline double _Dot(const double *p1, const double *p2);

	// Cross product of two points P = P1 x P2
	static inline double* _Cross(double *p, const double *p1, const double *p2);

	static float _GetDirection (float x1, float y1, float x2, float y2);


};

#endif // RLGRAPHICSAPI_H
