#include "xgeometry.h"
#include "xfunctiontemplate.h"
#include "xmath.h"
#include "xmathmacro.h"
#include <algorithm>
#include <cassert>
#include <functional>
#include <unordered_set>

/*
* Ken Clarkson wrote this.  Copyright (c) 1996 by AT&T..
* Permission to use, copy, modify, and distribute this software for any
* purpose without fee is hereby granted, provided that this entire notice
* is included in all copies of any software which is or includes a copy
* or modification of this software and in all copies of the supporting
* documentation for such software.
* THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
* WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR AT&T MAKE ANY
* REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
* OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
*/

/*
* two-dimensional convex hull
* read points from stdin,
*      one point per line, as two numbers separated by whitespace
* on stdout, points on convex hull in order around hull, given
*      by their numbers in input order
* the results should be "robust", and not return a wildly wrong hull,
*	despite using floating point
* works in O(n log n); I think a bit faster than Graham scan;
* 	somewhat like Procedure 8.2 in Edelsbrunner's "Algorithms in Combinatorial
*	Geometry".
*/

//! http://www3.cs.stonybrook.edu/~algorith/implement/clarkson/distrib/2dch.c

std::vector<XVec2d> XGeom::ConvexHull2D(const std::vector<XVec2d>& origin)
{
	using InputIt = std::vector<XVec2d>::iterator;

	auto isCounterClockWise = [](InputIt i, InputIt j, InputIt k) {
		return (i->x() - j->x()) * (k->y() - j->y()) <= (i->y() - j->y()) * (k->x() - j->x());
	};

	auto makeChain = [isCounterClockWise](InputIt begin, InputIt end, std::function<bool(const XVec2d& p1, const XVec2d& p2)> compare) {
		std::sort(begin, end, compare);
		auto s = begin + 1;
		for (InputIt it = begin + 2; it < end; ++it)
		{
			auto j = s;
			while (j > begin && isCounterClockWise(it, j, j - 1))
				--j;
			s = j + 1;
			std::swap(*s, *it);
		}
		return s;
	};

	std::vector<XVec2d> result{ origin.begin(), origin.end() };

	if (result.empty())
		return result;

	auto u = makeChain(result.begin(), result.end(), [](const XVec2d& p1, const XVec2d& p2) {
		if (p1.x() == p2.x())
			return p1.y() > p2.y();
		return p1.x() < p2.x();
	});

	auto uDiff = std::distance(result.begin(), u);
	result.push_back(result.front());
	u = std::next(result.begin(), uDiff);

	auto e = makeChain(u, result.end(), [](const XVec2d& p1, const XVec2d& p2) {
		if (p1.x() == p2.x())
			return p1.y() < p2.y();
		return p1.x() > p2.x();
	});

	return std::vector<XVec2d>{ result.begin(), e };
}

double XGeom::Dip(const XVec3d& p1, const XVec3d& p2)
{
	double dPerp = p1[2] - p2[2] > 0 ? p1[2] - p2[2] : p2[2] - p1[2];
	double dHypo = sqrt((p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]) + dPerp * dPerp);
	return std::acos(dPerp / dHypo);
}

bool XGeom::SameSide(const XVec3d& x, const XVec3d& e1, const XVec3d& e0, const XVec3d& n)
{
	// Is ((e1 - e0) x (x - e0))'s normal same as n?
    return (XVec3d(e1 - e0) ^ (x - e0)) * n >= 0;
}

bool XGeom::IsSamePoint(const XVec3d & p1, const XVec3d & p2, double tol)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();
	double dz = p2.z() - p1.z();

	return (dx * dx + dy * dy + dz * dz) < tol * tol;
}

double XBASIC_EXPORT XGeom::Lerp(double v1, double v2, double r)
{
	if (std::isnan(v1) && std::isnan(v2))
		return std::numeric_limits<double>::quiet_NaN();
	else if (std::isnan(v1))
		return v2;
	else if (std::isnan(v2))
		return v1;
	else
		return (1 - r) * v1 + r * v2;
}

XPoint XGeom::Lerp(const XPoint& p1, const XPoint& p2, double r)
{
	return Lerp(XVec3d(p1), XVec3d(p2), r).ToPoint();
}

XVec3d XGeom::Lerp(const XVec3d& p1, const XVec3d& p2, double r)
{
	if (r <= 0.0)
		return p1;
	if (r >= 1.0)
		return p2;
	return p1 + (p2 - p1) * r;
}

XVec2d XGeom::Lerp(const XVec2d& p1, const XVec2d& p2, double r)
{
	return p1 + (p2 - p1) * r;
}

bool XGeom::IntersectionTwoSegments(const XVec2d& p1, const XVec2d& p2, const XVec2d& q1, const XVec2d& q2, XVec2d* c, double* u, double* v)
{
	// http://geomalgorithms.com/a05-_intersect-1.html

	double dp = (p2 - p1) * XVec2d(q2 - q1).Perpendicular();
	double dq = (q2 - q1) * XVec2d(p2 - p1).Perpendicular();

	if (fabs(dp) <= M_TOL_DOUBLE)
		return false;

	*u = -(p1 - q1) * XVec2d(q2 - q1).Perpendicular() / dp;
	*v = (p1 - q1) * XVec2d(p2 - p1).Perpendicular() / dq;
	*c = p1 + (p2 - p1) * *u;

	return 0 <= *u && *u <= 1 && 0 <= *v && *v <= 1;
}

bool XBASIC_EXPORT XGeom::IntersectionTwoSegments(const XVec2d& p1, const XVec2d& p2, const XVec2d& q1, const XVec2d& q2)
{
	double dp = (p2 - p1) * XVec2d(q2 - q1).Perpendicular();
	double dq = (q2 - q1) * XVec2d(p2 - p1).Perpendicular();

	if (fabs(dp) <= M_TOL_DOUBLE)
		return false;

	double u = -(p1 - q1) * XVec2d(q2 - q1).Perpendicular() / dp;
	double v = (p1 - q1) * XVec2d(p2 - p1).Perpendicular() / dq;

	return 0 <= u && u <= 1 && 0 <= v && v <= 1;
}

bool XBASIC_EXPORT XGeom::IntersectionTwoSegments(const XVec2d& p1, const XVec2d& p2, const XVec2d& q1, const XVec2d& q2, XVec2d* c)
{
	double dp = (p2 - p1) * XVec2d(q2 - q1).Perpendicular();
	double dq = (q2 - q1) * XVec2d(p2 - p1).Perpendicular();

	if (fabs(dp) <= M_TOL_DOUBLE)
		return false;

	double u = -(p1 - q1) * XVec2d(q2 - q1).Perpendicular() / dp;
	double v = (p1 - q1) * XVec2d(p2 - p1).Perpendicular() / dq;
	*c = p1 + (p2 - p1) * u;

	return 0 <= u && u <= 1 && 0 <= v && v <= 1;
}

XGeom::EIntersection XBASIC_EXPORT XGeom::IntersectionSegmentPlane(const XVec3d& p1, const XVec3d& p2, const XVec3d& v, const XVec3d& n, XVec3d* c)
{
	// http://geomalgorithms.com/a05-_intersect-1.html

	XVec3d u = p2 - p1;
	XVec3d w = p1 - v;

	double d = n * u;
	double a = -(n * w);

	if (fabs(d) < M_TOL_DOUBLE) // segment is parallel to plane
	{
		if (a == 0)
			return XGeom::eAllOn; // segment lies in plane
		return XGeom::eNoIntersection;
	}

	// compute intersect param
	double sI = a / d;
	if (sI < 0 || sI > 1)
		return XGeom::eNoIntersection;

	*c = p1 + u * sI;
	return XGeom::eIntersectOnePoint;
}

bool XGeom::IntersectionTwoTriangle(const XTriangle3d& t1, const XTriangle3d& t2, XPoint* p1, XPoint* p2, int* count)
{
    if (count) *count = 0;

    XPlane plane1(t1.Vertex(0), t1.Vertex(1), t1.Vertex(2));

    // Calculate the distance to triangle 1 plane for each triangle 2 vertex
    double d11 = plane1.PointDist(t2.Vertex(0));
    double d12 = plane1.PointDist(t2.Vertex(1));
    double d13 = plane1.PointDist(t2.Vertex(2));

    // Must have sign difference for intersection
    if (d11 * d12 >= 0.0 && d12 * d13 >= 0.0 && d13 * d11 >= 0.0)
        return false;

    XPlane plane2(t2.Vertex(0), t2.Vertex(1), t2.Vertex(2));

    // Calculate the distance to triangle 2 plane for each triangle 1 vertex
    double d21 = plane2.PointDist(t1.Vertex(0));
    double d22 = plane2.PointDist(t1.Vertex(1));
    double d23 = plane2.PointDist(t1.Vertex(2));

    // Must have sign difference for intersection
    if (d21 * d22 >= 0.0 && d22 * d23 >= 0.0 && d23 * d21 >= 0.0)
        return false;

	using PointsTable = std::unordered_set<XPoint, XPointHashFunc>;
	PointsTable cp;

	auto checkIntersectionPoint = [](const XTriangle3d& t, double d1, double d2, int v1, int v2, const XTriangle3d& tt, PointsTable* cp)
	{
		if (d1 * d2 >= 0.0)
			return;

		XVec3d ip = XGeom::Lerp(t.Vertex(v1), t.Vertex(v2), fabs(d1) / (fabs(d1) + fabs(d2)));
		if (!tt.ContainsPoint(ip))
			return;

		cp->insert(ip.ToPoint());
	};

	auto setIntersectionPoint = [&cp, p1, p2, count]()
	{
		if (count) *count = 2;

		std::vector<XPoint> vec(cp.cbegin(), cp.cend());
		*p1 = vec[0];
		*p2 = vec[1];
	};

	checkIntersectionPoint(t2, d11, d12, 0, 1, t1, &cp);
    checkIntersectionPoint(t2, d12, d13, 1, 2, t1, &cp);
	if (2 == cp.size())
	{
		setIntersectionPoint();
		return true;
	}

	checkIntersectionPoint(t2, d13, d11, 2, 0, t1, &cp);
	if (2 == cp.size())
	{
		setIntersectionPoint();
		return true;
	}

	// Try the intersections from the other triangle
	checkIntersectionPoint(t1, d21, d22, 0, 1, t2, &cp);
	if (2 == cp.size())
	{
		setIntersectionPoint();
		return true;
	}

	checkIntersectionPoint(t1, d22, d23, 1, 2, t2, &cp);
	if (2 == cp.size())
	{
		setIntersectionPoint();
		return true;
	}

	checkIntersectionPoint(t1, d23, d21, 2, 0, t2, &cp);
	if (2 == cp.size())
	{
		setIntersectionPoint();
		return true;
	}

	if (1 == cp.size())
	{
		if (count) *count = 1;
		*p1 = *p2 = *cp.cbegin();
		return false;
	}

    return false;
}

double XBASIC_EXPORT XGeom::Distance(const XVec2d& p1, const XVec2d& p2)
{
	double dx = p2.x() - p1.x();
	double dy = p2.y() - p1.y();

	return sqrt(dx * dx + dy * dy);
}

double XGeom::Distance(const XVec2d& p, const XLine2d& line)
{
	// http://geomalgorithms.com/a02-_lines.html#Distance-to-Infinite-Line

	//		(y0 - y1) x + (x1 - x0) y + (x0 y1 - x1 y0)
	//	d = -------------------------------------------
	//		    sqrt( (x1 - x0)^2 + (y1 - y0)^2 )

	XVec2d p0 = line.PforT(0);
	XVec2d p1 = line.PforT(1);

	double d = (p0.y() - p1.y()) * p.x() + (p1.x() - p0.x()) * p.y() + (p0.x() * p1.y() - p1.x() * p0.y());
	return d;
}

double XGeom::Distance(const XVec2d& p, const std::vector<XVec2d>& polyline)
{
    if (polyline.empty())
        return 0.0;

    size_t closestId          = 0; // closest point
    double closestDistance = Distance(p, polyline.front());
    double closestT        = 0.0; // position within the segment
    double closestR        = 0.0; // radio within the segment

    for (size_t i = 1; i != polyline.size(); ++i)
    {
        auto p0 = polyline.at(i - 1);
        auto p1 = polyline.at(i);

        double d = Distance(p, p1);
        if (d < fabs(closestDistance))
        {
            closestId       = i;
            closestDistance = d;
            closestT        = 0.0;
            closestR        = 0.0;
        }

        // Fit a line to the points
        XLine2d line(p0, p1);
        double t0 = line.TforXY(p0.x(), p0.y());
        double t1 = line.TforXY(p1.x(), p1.y());

        double t;
        if (line.PointProjects(p.x(), p.y(), t0, t1, false, false, &t)) // Point projects on current segment?
        {
            d = Distance(p, line); // work out the distance to the segment
            if (fabs(d) < fabs(closestDistance))
            {
                closestId       = i - 1;
                closestDistance = d;
                closestT        = t;
                closestR        = (t - t0) / (t1 - t0);
            }
        }

        // skip some of work
        if (d > 5 * fabs(closestDistance))
            break;

        if (i - closestId > 5)
            break;
    }

    // Work out the direction if the closest projection is a corner point
    if (closestT == 0.0 && closestDistance >= M_TOL_DOUBLE)
    {
        // only one point?
        if (polyline.size() == 1 && p.x() <= polyline.front().x())
        {
            return -closestDistance;
        }

        if (closestId == 0) // first segment?
        {
            XLine2d line(polyline.at(0), polyline.at(1));
            closestDistance = Distance(p, line);
        }
        else if (closestId == polyline.size() - 1) // last segment
        {
            XLine2d line(polyline.at(polyline.size() - 2), polyline.at(polyline.size() - 1));
            closestDistance = Distance(p, line);
        }
        else
        {
            const auto& prev = polyline.at(closestId - 1);
            const auto& curr = polyline.at(closestId);
            const auto& next = polyline.at(closestId + 1);

            std::vector<XVec2d> rhsPolygon(5);
            XLine2d line(prev, next);
            rhsPolygon[0] = line.PointPerp(line.TforXY(curr.x(), curr.y()), 100000);
            line          = XLine2d(prev, curr);
            rhsPolygon[1] = line.PforT(-100000);
            rhsPolygon[2] = curr;
            line          = XLine2d(curr, next);
            rhsPolygon[3] = line.PforT(100000);
            rhsPolygon[4] = rhsPolygon[0]; // close to the start point.

            if (PointInside(p, rhsPolygon)) // point in the RHS polygon?
                closestDistance = fabs(closestDistance);
            else
                closestDistance = -fabs(closestDistance); // else point on the LHS -ve direction.
        }
    }

	return closestDistance;
}

XVec2d XBASIC_EXPORT XGeom::RotateAbout(const XVec2d& origin, double angle, const XVec2d& p)
{
	if (angle == 0.0)
		return p;

	// Translate to the origin
	XVec2d t(p.x() - origin.x(), p.y() - origin.y());

	// Do the rotation
	XVec2d rt(t.x() * cos(angle) - t.y() * sin(angle), t.y() * cos(angle) + t.x() * sin(angle));

	// Translate back
	XVec2d rp(rt.x() + origin.x(), rt.y() + origin.y());

	return rp;
}

bool XGeom::PointInside(const XVec2d & p, const std::vector<XVec2d>& polygon)
{
	bool bInside = false;

	for (auto p1 = polygon.cbegin(), p2 = std::next(p1); p2 != polygon.cend(); ++p1, ++p2)
	{
		if (p1->y() < p.y() && p2->y() >= p.y() || p1->y() >= p.y() && p2->y() < p.y())
		{
			double r = (p.y() - p1->y()) / (p2->y() - p1->y());
			double xx = p1->x() + r * (p2->x() - p1->x());
			if (fabs(xx - p.x()) < M_TOL_SAMEPOINT)
				return false;
			if (xx < p.x())
				bInside = !bInside;
		}
	}

	return bInside;
}

// Copyright 2002 softSurfer, 2012 Dan Sunday
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.

// http://geomalgorithms.com/a16-_decimate-1.html

// poly_decimate(): - remove vertices to get a smaller approximate polygon
//    Input:  tol = approximation tolerance
//            V[] = polyline array of vertex points
//            n   = the number of points in V[]
//    Output: sV[]= reduced polyline vertexes (max is n)
//    Return: m   = the number of points in sV[]
template <typename T, size_t D>
int poly_decimate(float tol, XVec<T, D>* V, int n, XVec<T, D>* sV)
{
	int i, k, m, pv;            // misc counters
	float tol2 = tol * tol;     // tolerance squared
	XVec3d* vt = new XVec3d[n]; // vertex buffer
	int* mk = new int[n];    // marker  buffer

	// STAGE 1.  Vertex Reduction within tolerance of  prior vertex cluster
	vt[0] = V[0]; // start at the beginning
	for (i = k = 1, pv = 0; i < n; i++)
	{
		if ((V[i] - V[pv]) * (V[i] - V[pv]) < tol2)
			continue;
		vt[k++] = V[i];
		pv = i;
	}
	if (pv < n - 1)
		vt[k++] = V[n - 1]; // finish at the end

	// STAGE 2.  Douglas-Peucker polyline reduction
	mk[0] = mk[k - 1] = 1; //  mark the first and last vertexes
	poly_decimateDP(tol, vt, 0, k - 1, mk);

	// copy marked vertices to the reduced polyline
	for (i = m = 0; i < k; i++)
	{
		if (mk[i])
			sV[m++] = vt[i];
	}
	delete vt;
	delete mk;
	return m; //  m vertices in reduced polyline
}

// poly_decimateDP():
//  This is the Douglas-Peucker recursive reduction routine
//  It marks vertexes that are part of the reduced polyline
//  for approximating the polyline subchain v[j] to v[k].
//    Input:  tol  = approximation tolerance
//            v[]  = polyline array of vertex points
//            j,k  = indices for the subchain v[j] to v[k]
//    Output: mk[] = array of markers matching vertex array v[]
template <typename T, size_t D>
void poly_decimateDP(float tol, XVec<T, D>* v, int j, int k, int* mk)
{
	if (k <= j + 1) // there is nothing to decimate
		return;

	// check for adequate approximation by segment S from v[j] to v[k]
	int maxi = j;              // index of vertex farthest from S
	float maxd2 = 0;              // distance squared of farthest vertex
	float tol2 = tol * tol;      // tolerance squared
	XSegment<T, D> S = { v[j], v[k] }; // segment from v[j] to v[k]
	XVec<T, D> u = S.p1 - S.p0;    // segment direction vector
	double cu = u * u;          // segment length squared

	// test each vertex v[i] for max distance from S
	// compute using the Algorithm dist_Point_to_Segment()
	// Note: this works in any dimension (2D, 3D, ...)
	XVec<T, D> w;
	XVec<T, D> Pb;         // base of perpendicular from v[i] to S
	double b, cw, dv2; // dv2 = distance v[i] to S squared

	for (int i = j + 1; i < k; i++)
	{
		// compute distance squared
		w = v[i] - S.p0;
		cw = w * u;
		if (cw <= 0)
			dv2 = (v[i] - S.p0) * (v[i] - S.p0);
		else if (cu <= cw)
			dv2 = (v[i] - S.p1) * (v[i] - S.p1);
		else
		{
			b = cw / cu;
			Pb = S.p0 + u * b;
			dv2 = (v[i] - Pb) * (v[i] - Pb);
		}
		// test with current max distance  squared
		if (dv2 <= maxd2)
			continue;
		// v[i] is a new max vertex
		maxi = i;
		maxd2 = (float)dv2;
	}
	if (maxd2 > tol2) // error is worse than the tolerance
	{
		// split the polyline at the farthest  vertex from S
		mk[maxi] = 1; // mark v[maxi] for the reduced polyline
		// recursively decimate the two subpolylines at v[maxi]
		poly_decimateDP(tol, v, j, maxi, mk); // polyline v[j] to v[maxi]
		poly_decimateDP(tol, v, maxi, k, mk); // polyline v[maxi] to v[k]
	}
	// else the approximation is OK, so ignore intermediate vertexes
	return;
}

void XGeom::Reduce(std::vector<XVec2d>& vecP, int* use, float fTol)
{
	use[0] = 1;
	use[vecP.size() - 1] = 1;

	int beg = 0;
	int end = 0;

	while (beg < vecP.size())
	{
		while (beg < vecP.size() && !use[beg])
			++beg;

		end = beg + 1;
		while (end < vecP.size() && !use[end])
			++end;

		poly_decimateDP(fTol, &vecP[0], beg, end, use);
		beg = end;
	}
}

XPoint XGeom::ClosestPoint(const std::vector<XPoint>& vec, double x, double y)
{
	double minDist = std::numeric_limits<double>::max();
	XPoint retP = vec.front();
	for (auto&& p : vec)
	{
		double d = (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
		if (d < minDist)
		{
			minDist = d;
			retP = p;
		}
	}
	return retP;
}

void XRMA::Clean()
{
	m_sumx = m_sumy = m_sumxx = m_sumyy = m_sumxy = 0.0;
	m_pnts.clear();
}

void XRMA::Add(double x, double y)
{
	m_sumx += x;
	m_sumy += y;
	m_sumxx += x * x;
	m_sumyy += y * y;
	m_sumxy += x * y;

	m_pnts.emplace_back(x, y);
}

void XRMA::Solve()
{
	double ssxy = m_sumxy - (m_sumx * m_sumy) / m_pnts.size();
	double ssx = m_sumxx - (m_sumx * m_sumx) / m_pnts.size();
	double ssy = m_sumyy - (m_sumy * m_sumy) / m_pnts.size();
	double xmean = m_sumx / m_pnts.size();
	double ymean = m_sumy / m_pnts.size();

	if (m_pnts.size() == 1) // one point? make it a horizontal line.
	{
		m_line = XLine2d(0, ymean);
		return;
	}

	if (fabs(ssx) < M_TOL_DOUBLE) // almost a vertical line?
	{
		m_line = XLine2d(xmean, ymean, xmean, ymean + 1);
		return;
	}

	double a = Sign(ssxy) * sqrt(fabs(ssy / ssx));
	double b = ymean - a * xmean;

	m_line = XLine2d(a, b);
}

XVec2d XRMA::GetPoint(int idx) const
{
	return m_pnts.at(idx);
}

void XRMA::TRange(double* t0, double* t1)
{
	double tMin = std::numeric_limits<double>::max();
	double tMax = std::numeric_limits<double>::min();

	for (auto&& p : m_pnts)
	{
		double t = m_line.TforXY(p.x(), p.y());
		tMin = std::min(t, tMin);
		tMax = std::max(t, tMax);
	}

	*t0 = tMin;
	*t1 = tMax;
}

double XRMA::SStotal()
{
	double SSt = 0.0; // Total sum of squares
	double xMean = XMean();
	double yMean = YMean();

	for (auto&& p : m_pnts)
	{
		double dX = p.x() - xMean;
		double dY = p.y() - yMean;
		SSt += dX * dX + dY * dY;
	}

	return SSt;
}

double XRMA::SSmodel()
{
	double SSm = 0.0; // Model sum of squares
	double xMean = XMean();
	double yMean = YMean();

	for (auto&& p : m_pnts)
	{
		double t = m_line.TforXY(p.x(), p.y());
		double dX = m_line.XforT(t) - xMean;
		double dY = m_line.YforT(t) - yMean;
		SSm += dX * dX + dY * dY;
	}

	return SSm;
}

double XRMA::R()
{
	double rr = SSmodel() / SStotal();
	return rr <= 0.0 ? 0.0 : rr;
}

double XRMA::XMean() const
{
	return m_sumx / m_pnts.size();
}

double XRMA::YMean() const
{
	return m_sumy / m_pnts.size();
}

double XRMA::PointDist(double x, double y) const
{
	return XGeom::Distance(XVec2d(x, y), m_line);
}

const XLine2d& XRMA::Line()
{
	return m_line;
}

XTriangle3d::XTriangle3d(const XVec3d& p1, const XVec3d& p2, const XVec3d& p3)
	: m_p1(p1), m_p2(p2), m_p3(p3)
{
}

XTriangle3d::XTriangle3d(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
	: m_p1(x1, y1, z1), m_p2(x2, y2, z2), m_p3(x3, y3, z3)
{
}

void XTriangle3d::ZSort()
{
	if (m_p1.z() > m_p2.z())
		std::swap(m_p1, m_p2);
	if (m_p2.z() > m_p3.z())
		std::swap(m_p2, m_p3);
	if (m_p1.z() > m_p2.z())
		std::swap(m_p1, m_p2);

	assert(m_p1.z() <= m_p2.z());
	assert(m_p2.z() <= m_p3.z());
}

void XTriangle3d::SetVertex(int index, const XVec3d& p)
{
	switch (index)
	{
	case 0:
		m_p1 = p;
		break;
	case 1:
		m_p2 = p;
		break;
	case 2:
		m_p3 = p;
		break;
	default:
		assert(!"out of range.");
	}
}

XVec3d XTriangle3d::Vertex(int index) const
{
	switch (index)
	{
	case 0:
		return m_p1;
	case 1:
		return m_p2;
	case 2:
		return m_p3;
	default:
		assert(!"out of range.");
		return m_p3;
	}
}

double XTriangle3d::ZMin() const
{
	return std::min({m_p1.z(), m_p2.z(), m_p3.z()});
}

double XTriangle3d::ZMax() const
{
	return std::max({m_p1.z(), m_p2.z(), m_p3.z()});
}

bool XTriangle3d::ContainsPoint(const XVec3d & p) const
{
	XVec3d nv = XPlane(m_p1, m_p2, m_p3).Normal();

	if (!XGeom::SameSide(p, m_p2, m_p1, nv)) return false;
	if (!XGeom::SameSide(p, m_p3, m_p2, nv)) return false;
	if (!XGeom::SameSide(p, m_p1, m_p3, nv)) return false;

	return true;
}

std::istream& operator >> (std::istream& is, XTriangle3d& triangle)
{
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;
	is >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
	triangle = XTriangle3d(x1, y1, z1, x2, y2, z2, x3, y3, z3);

	return is;
}

std::ostream& operator<<(std::ostream& os, const XTriangle3d& triangle)
{
	os << triangle.m_p1.x() << triangle.m_p1.y() << triangle.m_p1.z()
		<< triangle.m_p2.x() << triangle.m_p2.y() << triangle.m_p2.z()
		<< triangle.m_p3.x() << triangle.m_p3.y() << triangle.m_p3.z();

	return os;
}

XPlane::XPlane(const XVec3d& p1, const XVec3d& p2, const XVec3d& p3)
{
	XVec3d v1(p1);
	XVec3d u(p2 - p1);
	XVec3d v(p3 - p1);

	m_n = (u ^ v).Normalized();
	m_d = -m_n * v1;
}

double XPlane::ZforXY(double x, double y) const
{
	// ax + by + cz + d = 0
	double z = -(m_d + m_n.x() * x + m_n.y() * y) / m_n.z();
	return z;
}

double XPlane::PointDist(const XVec3d & p) const
{
	return m_n.x() * p.x() + m_n.y() * p.y() + m_n.z() * p.z() + m_d;
}

const XVec3d XPlane::Normal() const
{
	return m_n;
}

XLine2d::XLine2d(double x, double y, const XVec2d& dir)
	: m_p0(x, y), m_dir(dir.Normalized())
{
}

XLine2d::XLine2d(const XVec2d& p1, const XVec2d& p2)
	: m_p0(p1), m_dir(XVec2d(p2 - p1).Normalized())
{
}

XLine2d::XLine2d(double x1, double y1, double x2, double y2)
	: XLine2d(XVec2d(x1, y1), XVec2<double>(x2, y2))
{
}

XLine2d::XLine2d(double a, double b, double c)
	: XLine2d(XVec2d(0, -c / b), XVec2<double>(1, (a + c) / (-b)))
{
}

XLine2d::XLine2d(double a, double b)
	: XLine2d(XVec2d(0, b), XVec2d(1, a + b))
{
}

double XLine2d::TforXY(double x, double y) const
{
	XLine2d perpendicularLine(x, y, m_dir.Perpendicular());

	XVec2d otherPoint(XforT(1), YforT(1));
	XVec2d perpendicularOtherPoint(perpendicularLine.XforT(1), perpendicularLine.YforT(1));
	XVec2d intersectionPoint;
	double u, v;
	XGeom::IntersectionTwoSegments(m_p0, otherPoint, XVec2d(x, y), perpendicularOtherPoint, &intersectionPoint, &u, &v);

	return fabs(m_dir.x()) > 0.001 ? TforX(intersectionPoint.x()) : TforY(intersectionPoint.y());
}

double XLine2d::XforT(double t) const
{
	return m_p0.x() + t * m_dir.x();
}

double XLine2d::YforT(double t) const
{
	return m_p0.y() + t * m_dir.y();
}

double XLine2d::TforX(double x) const
{
	return (x - m_p0.x()) / m_dir.x();
}

double XLine2d::TforY(double y) const
{
	return (y - m_p0.y()) / m_dir.y();
}

double XLine2d::YforX(double x) const
{
	double t = TforX(x);
	return YforT(t);
}

double XLine2d::XforY(double y) const
{
	double t = TforY(y);
	return XforT(t);
}

XVec2d XLine2d::PforT(double t) const
{
	return XVec2d(m_p0.x() + t * m_dir.x(), m_p0.y() + t * m_dir.y());
}

XVec2d XLine2d::PointPerp(double t, double tt) const
{
	XLine2d perpLine(XforT(t), YforT(t), m_dir.Perpendicular());
	return XVec2d(perpLine.XforT(tt), perpLine.YforT(tt));
}

bool XLine2d::PointProjects(double x, double y, double t0, double t1, bool begExtend, bool endExtend, double* pt)
{
    // put into the correct order
    if (t1 < t0)
    {
        std::swap(t0, t1);
        std::swap(begExtend, endExtend);
    }

    double t = TforXY(x, y);
	*pt = t;

	if (t0 <= t && t < t1)
		return true;
	
	if (t < t0 && begExtend)
		return true;

	if (t >= t1 && endExtend)
		return true;

	return false;
}

double XLine2d::Angle() const
{
	return std::atan2(m_dir.y(), m_dir.x());
}

XVec2d XLine2d::Direction() const
{
	return m_dir;
}
