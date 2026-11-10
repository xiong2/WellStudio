#ifndef XKDTREE_H
#define XKDTREE_H

#include "xbasic_global.h"

/**
 * @ Class CXKDTree in the file "rldtree.h"
 * @brief The file provides interface for a k-d tree (2-D)
 * 
 * @author Yong Shu 
 * @date 5/20/2014
 * @see 
 * @bug	No Known bugs so far
 */

class XBASIC_EXPORT CXKDTree
{
public:
	///@brief Constructor and destructor
	CXKDTree (double* pX, double* pY, int nPtNum);
	~CXKDTree();

public:
	///@brief Create the KD tree (2-D)
	bool CreateKDTree();

	///@brief Get the n nearest points to the point (dX, dY). 
	///@para[in] (dX, dY) : the center point, n : the number of the nearest points
	///@para[out] nn : the nearest points indices among the array of points
	///@para[out] dn : the nearest distance
	///@brief return -1 if there is an error, 0 : the point belongs to the set of the points; 1 : calculation is successful.
	int NNearest(double dX, double dY, int *nn, double *dn, int n);

	///@brief Get the n nearest points within a radius dRadius of (dX, dY) 
	///@para[in] (dX, dY) : the center point, n : the number of the nearest points
	///@para[in] dRadius : the radius
	///@para[out] nn : the nearest points indices among the array of points
	///@brief return the number of the nearest points
	int NNearest(double dX, double dY, double dRadius, int *nn, int n);

private:
	// 2-D point
	class Point2D
	{
	public:
		double x[2];
		Point2D (double x0=0., double x1=0.) 	{ x[0] = x0;	 x[1] = x1;}
		Point2D (const Point2D& p)		{ x[0] = p.x[0]; x[1] = p.x[1]; }
		Point2D& operator= (const Point2D& p)
		{
			x[0] = p.x[0]; 
			x[1] = p.x[1];
			return *this;
		}
		bool operator== (const Point2D &p) const
		{
			if (x[0] != p.x[0] ) return false;
			if (x[1] != p.x[1] ) return false;
			return true;
		}			
	};

	// 2-D box
	class Box
	{
	public:
		Point2D lo, hi;
		Box() {}
		Box (const Point2D& mylo, const Point2D& myhi) : lo(mylo), hi(myhi) {}
	};

	// 2-D box node
	class BoxNode : public Box
	{
	public:
		int mom, dau1, dau2, ptlo, pthi;
		BoxNode() {}
		BoxNode (Point2D& lo, Point2D& hi, int mymom, int myd1, int myd2, int myptlo, int mypthi):
		Box(lo, hi), mom(mymom), dau1(myd1), dau2(myd2), ptlo(myptlo), pthi(mypthi) {}			
	};

private:
	int select(int k, int* index, int n, double* pArray);
	double dist (double x0, double y0, double x1, double y1);
	double dist (const Box& b, double x, double y);
	double disti (int i, int j);
	void sift_down(double *heap, int *ndx, int nn);
	int locate(double dX, double dY) ;


private:	
	double* m_pX;
	double* m_pY;
	int m_nPtNum;
	int m_nBoxNum;
	BoxNode* m_pBoxNode;	

	int* m_pPtIndex;
	int* m_pRevPtIndex;
};

#endif // RLKDTREE_H
