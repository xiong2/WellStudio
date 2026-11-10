#pragma once

#include "xbasic_global.h"
#include "xvec.h"
#include "xmatrix.h"
#include <array>
#include <memory>
#include <numeric>
#include <vector>

class XBASIC_EXPORT XLine2d
{
public:
    XLine2d() = default;
    XLine2d(double x, double y, const XVec2d& dir);
    XLine2d(const XVec2d& p1, const XVec2d& p2);
    XLine2d(double x1, double y1, double x2, double y2);
    // ax + by + c = 0
    XLine2d(double a, double b, double c);
    // y = ax + b;
    XLine2d(double a, double b);

    // T is the distance to m_p0;
    double TforXY(double x, double y) const;
    double XforT(double t) const;
    double YforT(double t) const;
    double TforX(double x) const;
    double TforY(double y) const;
    double YforX(double x) const;
    double XforY(double y) const;
    XVec2d PforT(double t) const;

    XVec2d PointPerp(double t, double tt) const;
	bool PointProjects(double x, double y, double t0, double t1, bool begExtend, bool endExtend, double* pt);
	double Angle() const;
	XVec2d Direction() const;

private:
#pragma warning(push)
#pragma warning(disable: 4251)
    XVec2d m_dir; // normalized direction vector: (p1 - p0).normalized()
    XVec2d m_p0;  // a point on the line
#pragma warning(pop)
};

class XBASIC_EXPORT XPlane
{
public:
    XPlane(const XVec3d& p1, const XVec3d& p2, const XVec3d& p3);

    double ZforXY(double x, double y) const;
	double PointDist(const XVec3d& p) const;
	const XVec3d Normal() const;

private:
#pragma warning(push)
#pragma warning(disable: 4251)
    XVec3d m_n; // normal vector
#pragma warning(pop)
    double m_d;
};

class XBASIC_EXPORT XTriangle3d
{
public:
	XTriangle3d() = default;
    XTriangle3d(const XVec3d& p1, const XVec3d& p2, const XVec3d& p3);
    XTriangle3d(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

    void ZSort();
    void SetVertex(int index, const XVec3d& p);
    XVec3d Vertex(int index) const;
	double ZMin() const;
	double ZMax() const;
	bool ContainsPoint(const XVec3d& p) const;

	friend XBASIC_EXPORT std::istream& operator>>(std::istream& is, XTriangle3d& triangle);
	friend XBASIC_EXPORT std::ostream& operator<<(std::ostream& os, const XTriangle3d& triangle);

private:
#pragma warning(push)
#pragma warning(disable: 4251)
    XVec3d m_p1;
    XVec3d m_p2;
    XVec3d m_p3;
#pragma warning(pop)
};

class XBASIC_EXPORT XRMA
{
public:
    void Clean();
    void Add(double x, double y);
    void Solve();

    double XMean() const;
    double YMean() const;
    double PointDist(double x, double y) const;
    const XLine2d& Line();

    XVec2d GetPoint(int idx) const;
    void TRange(double* t0, double* t1);
    double SStotal();
    double SSmodel();
    double R();

private:
#pragma warning(push)
#pragma warning(disable: 4251)
    std::vector<XVec2d> m_pnts;
#pragma warning(pop)
    XLine2d m_line;

    double m_sumx  = 0.0; /* SUM X */
    double m_sumy  = 0.0; /* SUM Y */
    double m_sumxx = 0.0; /* SUM XX */
    double m_sumyy = 0.0; /* SUM YY */
    double m_sumxy = 0.0; /* SUM XY */
};

namespace XGeom
{

double XBASIC_EXPORT Dip(const XVec3d& p1, const XVec3d& p2);

std::vector<XVec2d> XBASIC_EXPORT ConvexHull2D(const std::vector<XVec2d>& origin);

bool SameSide(const XVec3d& x, const XVec3d& e1, const XVec3d& e0, const XVec3d& n);
bool IsSamePoint(const XVec3d& p1, const XVec3d& p2, double tol);

double XBASIC_EXPORT Lerp(double v1, double v2, double r);
XPoint XBASIC_EXPORT Lerp(const XPoint& p1, const XPoint& p2, double r);
XVec3d XBASIC_EXPORT Lerp(const XVec3d& p1, const XVec3d& p2, double r);
XVec2d XBASIC_EXPORT Lerp(const XVec2d& p1, const XVec2d& p2, double r);

enum EIntersection
{
    eNoIntersection,
    eIntersectOnePoint,
    eAllOn
};

/** @brief find the 2D intersection of 2 finite segments

@param [In]: two finite segments (p1, p2), (q1, q2)
@param [Out]: *c = intersection point (when it exists)
@param [Out]: *u that is (*c = p1 + *u * (p2 - p1))
@param [Out]: *v that is (*c = q1 + *v * (q2 - q1))
*/
bool XBASIC_EXPORT IntersectionTwoSegments(const XVec2d& p1, const XVec2d& p2, const XVec2d& q1, const XVec2d& q2, XVec2d* c, double* u, double* v);
bool XBASIC_EXPORT IntersectionTwoSegments(const XVec2d& p1, const XVec2d& p2, const XVec2d& q1, const XVec2d& q2);
bool XBASIC_EXPORT IntersectionTwoSegments(const XVec2d& p1, const XVec2d& p2, const XVec2d& q1, const XVec2d& q2, XVec2d* c);
EIntersection XBASIC_EXPORT IntersectionSegmentPlane(const XVec3d& p1, const XVec3d& p2, const XVec3d& v, const XVec3d& n, XVec3d* c);

// If there is only one common point, return false, and 1 for the count;
// If there are no common points, return false, and 0 for the count;
bool XBASIC_EXPORT IntersectionTwoTriangle(const XTriangle3d& t1, const XTriangle3d& t2, XPoint* p1, XPoint* p2, int* count = nullptr);

double XBASIC_EXPORT Distance(const XVec2d& p1, const XVec2d& p2);
double XBASIC_EXPORT Distance(const XVec2d& p, const XLine2d& line);
double XBASIC_EXPORT Distance(const XVec2d& p, const std::vector<XVec2d>& polyline);
XVec2d XBASIC_EXPORT RotateAbout(const XVec2d& origin, double angle, const XVec2d& p);
bool XBASIC_EXPORT PointInside(const XVec2d& p, const std::vector<XVec2d>& polygon);
void XBASIC_EXPORT Reduce(std::vector<XVec2d>& vecP, int* use, float dTol);

XPoint XBASIC_EXPORT ClosestPoint(const std::vector<XPoint>& vec, double x, double y);
}

namespace XGeom
{
template <typename It>
typename It::value_type MeanPoint(It begin, It end)
{
    using value_type = typename It::value_type;
    value_type sum   = std::accumulate(begin, end, value_type(), [](const auto& a, const auto& b) { return a + b; });

    auto n = std::distance(begin, end);
    sum /= static_cast<int>(n);
    return sum;
}
}
