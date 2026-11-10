#ifndef XMATH3D_H_
#define XMATH3D_H_

#include "xbasic_global.h"

#include <cfloat>
#include <cmath>
#include <vector>

class QVector3D;

/**
 * @namespace	NXMath3D provided in the file "rlmath3d.h"
 * @brief		The namespace provides basic 3d math operator.
 * 
 * @author		Pezy
 * @date		3/24/2015
 * @see			NXUtility
 */

namespace NXMath3D
{
	XBASIC_EXPORT void		Vec3Sub		(double (&dest)[3],		double const (&v1)[3],	double const (&v2)[3]);
	XBASIC_EXPORT void		Vec3Add		(double (&dest)[3],		double const (&v1)[3],	double const (&v2)[3]);
	XBASIC_EXPORT void		Vec3Mul		(double (&dest)[3],		double const (&v)[3],	double factor);
	XBASIC_EXPORT void		Vec3Cross	(double (&dest)[3],		double const (&v1)[3],	double const (&v2)[3]);
	XBASIC_EXPORT double	Vec3Dot		(double const (&v1)[3], double const (&v2)[3]);
	XBASIC_EXPORT double	Vec3Len		(double const (&v)[3]);
	XBASIC_EXPORT void		Vec3Normal	(double (&v)[3]);

	XBASIC_EXPORT bool		CompareTwoVec(double const (&lhs)[3], double const (&rhs)[3]);
	XBASIC_EXPORT void		QVector2Array(QVector3D const& vec, double (&v)[3]);

	XBASIC_EXPORT void		QuadTriangleStrips		(int const (&orig)[4], int (&ret)[4]);
	XBASIC_EXPORT void		PentagonTriangleStrips	(int const (&orig)[5], int (&ret)[5]);
	XBASIC_EXPORT void		HexagonTriangleStrips	(int const (&orig)[5], int (&ret)[5]);
	XBASIC_EXPORT void		TriangleStrips			(std::vector<unsigned> &vec);

	//! @brief	find the 3D intersection of a segment and a plane
	//! @param	- Input:	segment point0 and point1, plane point and normal
	//!			- Output:	the intersect point(when it exists)
	//! @return	0 = disjoint (no intersection)
	//!			1 = intersection in the unique point
	//!			2 = the segment lies in the plane
	//! @author	Pezy<chenpeizhe@cnpc.com.cn>

	XBASIC_EXPORT int Intersect_SegmentPlane(double const (&)[3], double const (&)[3], double const (&)[3], double const (&)[3], double (&)[3]);
};

inline void NXMath3D::Vec3Sub(double (&dest)[3], double const (&v1)[3], double const (&v2)[3])
{
	dest[0] = v1[0] - v2[0];
	dest[1] = v1[1] - v2[1];
	dest[2] = v1[2] - v2[2];
}

inline void NXMath3D::Vec3Add(double (&dest)[3], double const (&v1)[3], double const (&v2)[3])
{
	dest[0] = v1[0] + v2[0];
	dest[1] = v1[1] + v2[1];
	dest[2] = v1[2] + v2[2];
}

inline void NXMath3D::Vec3Mul(double (&dest)[3], double const (&v)[3], double factor)
{
	dest[0] = v[0] * factor;
	dest[1] = v[1] * factor;
	dest[2] = v[2] * factor;
}

inline void NXMath3D::Vec3Cross(double (&dest)[3], double const (&v1)[3], double const (&v2)[3])
{
	dest[0] = v1[1] * v2[2] - v1[2] * v2[1];
	dest[1] = v1[2] * v2[0] - v1[0] * v2[2];
	dest[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

inline double NXMath3D::Vec3Dot(double const (&v1)[3], double const (&v2)[3])
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline double NXMath3D::Vec3Len(double const (&v)[3])
{
	return std::sqrt( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] );
}

inline void NXMath3D::Vec3Normal(double (&v)[3])
{
	double dLen = Vec3Len(v);
	v[0] /= dLen;
	v[1] /= dLen;
	v[2] /= dLen;
}

inline int NXMath3D::Intersect_SegmentPlane(double const (&p0)[3], double const (&p1)[3], double const (&v)[3], double const (&n)[3], double (&pi)[3])
{
	double u[3], w[3];
	Vec3Sub(u, p1, p0);
	Vec3Sub(w, p0, v);

	double D = Vec3Dot(n, u);
	double N = -Vec3Dot(n ,w);

	if (std::fabs(D) < DBL_EPSILON) {
		if (N == 0) return 2;
		return 0;
	}

	// they are not parallel, compute intersect param
	double dI = N / D;
	if ( dI < 0.0 || dI > 1.0 ) return 0;

	Vec3Mul(pi, u, dI);
	Vec3Add(pi, p0, pi);
	return 1;
}

inline bool NXMath3D::CompareTwoVec(double const (&lhs)[3], double const (&rhs)[3])
{
	if ( std::fabs(lhs[0] - rhs[0]) < DBL_EPSILON && std::fabs(lhs[1] - rhs[1]) < DBL_EPSILON && std::fabs(lhs[2] - rhs[2]) < DBL_EPSILON )
		return true;
	
	return false;
}

inline void	NXMath3D::QuadTriangleStrips(int const (&origin)[4], int (&ret)[4])
{
//  3   2
//	+---+
//	|  /|
//	| / |  ==>  1023
//	|/  |
//	+---+
//	0   1

	ret[0] = origin[1];
	ret[1] = origin[0];
	ret[2] = origin[2];
	ret[3] = origin[3];
}

inline void	NXMath3D::PentagonTriangleStrips(int const (&origin)[5], int (&ret)[5])
{
//	4  3
//	+---
//	|   \
//	|    \   ==>  12034
//	|    | 2
//	+----+
//  0    1

	ret[0] = origin[1];
	ret[1] = origin[2];
	ret[2] = origin[0];
	ret[3] = origin[3];
	ret[4] = origin[4];
}

inline void	NXMath3D::HexagonTriangleStrips(int const (&origin)[5], int (&ret)[5])
{
//     4    3  
//	   -----+
//	  /		|
//	5/		|
//	|	   /2  ==>  102534
//	|	  /
//	+-----
//	0     1

	ret[0] = origin[1];
	ret[1] = origin[0];
	ret[2] = origin[2];
	ret[3] = origin[5];
	ret[4] = origin[3];
	ret[5] = origin[4];
}

inline void NXMath3D::TriangleStrips(std::vector<unsigned> &vec)
{
	if ( 4 == vec.size() ) { std::swap(vec[0], vec[1]); }
	else if ( 5 == vec.size() ) {
		std::swap(vec[0], vec[1]);
		std::swap(vec[1], vec[2]);
	}
	else if ( 6 == vec.size() ) {
		std::swap(vec[0], vec[1]);
		std::swap(vec[3], vec[5]);
		std::swap(vec[4], vec[5]);
	}
	else throw "out of range";
}

#endif	// RLMATH3D_H_
