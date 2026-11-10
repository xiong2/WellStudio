#ifndef XOCTREE_H
#define XOCTREE_H

#include "xbasic_global.h"
#include <vector>

//! @class	CRLOctree
//!
//! @brief	3-Dimensional tree 
//! 		a 3d-space-partitioning data structure for organizing points in a 3-dimensional space.
//!
//! @author	Pezy
//! @date	2014/12/24

class XBASIC_EXPORT CX3dtree
{
public:
	CX3dtree(double *pPts, int nPtNum);
	CX3dtree(double *pX, double *pY, double *pZ, int nPtNum);

	~CX3dtree() { delete [] m_pNodes;}

	//! @fn	int CRLOctree::nearest(double x, double y, double z);
	//!
	//! @brief	Given an arbitrary location pt, return the index of the nearest point in the kdtree.
	//!
	//! @author	Pezy
	//! @date	2014/12/30
	//!
	//! @param	x	The x coordinate.
	//! @param	y	The y coordinate.
	//! @param	z	The z coordinate.
	//!
	//! @return	An int.

	int nearest(double x, double y, double z);

	//! @fn	void CRLOctree::nnearest(int jpt, int *nn, double *dn, int n);
	//!
	//! @brief	Given the index jpt of a point in a kdtree, 
	//! 		return a list nn[0..n-1] of the indices of the n points in the tree nearest to point j, 
	//! 		and a list dd[0..n-1] of their distances.
	//!
	//! @author	Pezy
	//! @date	2014/12/30
	//!
	//! @param	jpt		  	The jpt.
	//! @param [in,out]	nn	If non-null, the nn.
	//! @param [in,out]	dn	If non-null, the dn.
	//! @param	n		  	The int to process.

	void nnearest(int jpt, int *nn, double *dn, int n);

	//! @fn	int CRLOctree::locatenear(double x, double y, double z, double r, int *list, int nmax);
	//!
	//! @brief	Given a point pt and radius r, 
	//! 		returns a value nret such that list[0..nret-1] is a list of all kdtree points 
	//! 		within a radius r of pt, up to a user-speciﬁed maximum of nmax points.
	//!
	//! @author	Pezy
	//! @date	2014/12/30
	//!
	//! @param	x				The x coordinate.
	//! @param	y				The y coordinate.
	//! @param	z				The z coordinate.
	//! @param	r				The double to process.
	//! @param [in,out]	list	If non-null, the list.
	//! @param	nmax			The nmax.
	//!
	//! @return	An int.

	int locatenear(double x, double y, double z, double r, int *list, int nmax);

public:
	static const double BIG;

private:

	bool Create3DTree();

	//! @struct	Point3D
	//!
	//! @brief	A 3d point.
	//!
	//! @author	Pezy
	//! @date	2014/12/25

	struct Point3D {
		double x[3];
		Point3D(const Point3D &p) 
		{
			for (int i=0; i<3; ++i)
				x[i] = p.x[i];
		}
		Point3D& operator= (const Point3D &p)
		{
			for (int i=0; i<3; ++i)
				x[i] = p.x[i];
			return *this;
		}
		bool operator== (const Point3D &p) const 
		{
			for (int i=0; i<3; ++i)
				if (x[i] != p.x[i]) return false;
			return true;
		}
		Point3D(double x0 = 0.0, double x1 = 0.0, double x2 = 0.0)
		{
			x[0] = x0; x[1] = x1; x[2] = x2;
		}
	};

	//! @fn	double CRLOctree::dist(const Point3D &p, const Point3D &q);
	//!
	//! @brief	Distance of two point.
	//!
	//! @author	Pezy
	//! @date	2014/12/25
	//!
	//! @param	p	The const Point3D &amp; to process.
	//! @param	q	The const Point3D &amp; to process.
	//!
	//! @return	A double.

	double dist(const Point3D &p, const Point3D &q);

	//! @struct	Box3D
	//!
	//! @brief	A 3d box. (Bounding Box)
	//!
	//! @author	Pezy
	//! @date	2014/12/25.

	struct Box3D {
		Point3D lo, hi;
		Box3D() {}
		Box3D(const Point3D &low, const Point3D &high):lo(low), hi(high) {}
	};

	//! @fn	double CRLOctree::dist(const Box3D &b, const Point3D &p);
	//!
	//! @brief	Distance of Box and Point.
	//! 		if point lies outside box, the distance to the [nearest point] on box is returned.
	//! 		if point inside box or on its surface, [zero] is returned.
	//!
	//! @author	Pezy
	//! @date	2014/12/25
	//!
	//! @param	b	The const Box3D &amp; to process.
	//! @param	p	The const Point3D &amp; to process.
	//!
	//! @return	A double.

	double dist(const Box3D &b, const Point3D &p);

	struct BoxNode : Box3D {
		int mom, dau1, dau2, ptlo, pthi;
		BoxNode() {}
		BoxNode(Point3D low, Point3D high, int mother, int d1, int d2, int ptlow, int pthigh) :
		Box3D(low, high), mom(mother), dau1(d1), dau2(d2), ptlo(ptlow), pthi(pthigh) {}
	};

	//! @fn	double CRLOctree::disti(int jpt, int kpt);
	//!
	//! @brief	Distis.
	//!
	//! @author	Pezy
	//! @date	2014/12/25
	//!
	//! @param	jpt	The jpt.
	//! @param	kpt	The kpt.
	//!
	//! @return	A double.

	double disti(int jpt, int kpt);

	//! @fn	int CRLOctree::locate(Point3D pt);
	//!
	//! @brief	Locates the given point.
	//!
	//! @author	Pezy
	//! @date	2014/12/25
	//!
	//! @param	pt	The point.
	//!
	//! @return	An int.

	int locate(Point3D pt);

	//! @fn	int CRLOctree::locate(int jpt);
	//!
	//! @brief	Locates.
	//!
	//! @author	Pezy
	//! @date	2014/12/25
	//!
	//! @param	jpt	The jpt.
	//!
	//! @return	An int.

	int locate(int jpt);

	//! @fn	int CRLOctree::selecti(const int k, int *indx, int n, double *arr);
	//!
	//! @brief	Permutes indx[0..n-1] to make 
	//! 		arr[indx[0..k-1]] <= arr[indx[k]] <= arr[indx[k+1..n-1]]. 
	//! 		The array arr is not modiﬁed.
	//!
	//! @author	Pezy
	//! @date	2014/12/25
	//!
	//! @param	k				The const int to process.
	//! @param [in,out]	indx	If non-null, the indx.
	//! @param	n				The int to process.
	//! @param [in,out]	arr 	If non-null, the array.
	//!
	//! @return	An int.

	int selecti(const int k, int *indx, int n, double *arr);

	//! @fn	static void CRLOctree::slft_down(double *heap, int *ndx, int nn);
	//!
	//! @brief	Fix heap[0..nn-1], whose ﬁrst element (only) may be wrongly ﬁled. 
	//! 		Make a corresponding permutation in ndx[0..nn-1]. 
	//! 		The algorithm is identical to that used by sift_down in hpsort.
	//!
	//! @author	Pezy
	//! @date	2014/12/30
	//!
	//! @param [in,out]	heap	If non-null, the heap.
	//! @param [in,out]	ndx 	If non-null, the ndx.
	//! @param	nn				The nn.

	static void sift_down(double *heap, int *ndx, int nn);
	
	int m_nBoxes, m_nPts; // number of boxes and points
	std::vector<Point3D> m_vecPts; // the vector of points in the octree
	BoxNode *m_pNodes; // the array of boxnodes that from the tree
	std::vector<int> m_vecPtIndex, m_vecRptIndex; // index of points and reserse index
	double *m_pCoord;	// point coordinates rearranged contiguously.
};

#endif // RLOCTREE_H