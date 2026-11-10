#ifndef CRLTHREADMAKEREVATTRIBUTE_H_H
#define CRLTHREADMAKEREVATTRIBUTE_H_H

#include "xalgorithm_global.h"
#include "xbasethread.h"
//#include "xutmtool.h"
#include "xkdtreet.h"
#include "xparametermakerevinterpolation.h"


class CXObject;
class CXPropertyModel;


//class Point{
//public:
//	typedef double coordinate_type;
//
//	Point(){X=0;Y=0;Z=0;};
//	Point(double x, double y,double z): X(x), Y(y),Z(z) {};
//	double& operator[](int i){
//		if(i==1) return X;
//		if(i==2) return Y;
//		if(i==3) return Z;
//	}
//
//	const double& operator[](int i) const {
//		if(i==1) return X;
//		if(i==2) return Y;
//		if(i==3) return Z;
//	}
//
//	double X;
//	double Y;
//	double Z;
//
//};


#include "GsTL/geometry/geometry.h"

class Node{
public:
	typedef double property_type;
	typedef location_3d<double> location_type;

	Node():pval_(0) {loc_=location_type();}
	Node(double x, double y, double z, double pval){loc_=location_type(x,y,z);pval_=pval;}
	inline location_type location() const { return loc_;};
	inline property_type& property_value(){return pval_;}
	inline const property_type& property_value() const {return pval_;}

private:
	location_type loc_;
	property_type pval_;
};

class neighborhood{
public:
	typedef std::vector<Node>::iterator iterator;
	typedef std::vector<Node>::const_iterator const_iterator;
	typedef Node value_type;
	
	void add_node(Node n){neigh_.push_back(n);};
	iterator begin(){return neigh_.begin();};
	iterator end(){return neigh_.end();};
	const_iterator begin() const {return neigh_.begin();};
	const_iterator end() const {return neigh_.end();};
	unsigned int size() const {return neigh_.size();}
	bool is_empty() const {return neigh_.empty();}

private:
	void find_neighbors(location_3d<double> & u);

	std::vector<Node> neigh_;
};

//-------------------------------
//class covariance{
//public:
//  inline double operator()(const Point& P1,const Point& P2) const {
//    double h=sqrt(double((P1.X-P2.X)*(P1.X-P2.X)+(P1.Y-P2.Y,2)*(P1.Y-P2.Y,2)));
//    double a=10;
//    double c=1.0;
//    return c * exp(-3*h/a);
//  } 
//};

inline double id(location_3d<double>  loc){
	return 1.0 ;}

inline double fx(location_3d<double>  loc){
	return loc[0];}

inline double fy(location_3d<double>  loc){
	return loc[1];}

inline double fz(location_3d<double>  loc){
	return loc[2];}

inline double fxy(location_3d<double>  loc){
	return loc[0] * loc[1];}

class functor{
public:
	functor() : fp(0) {}
	functor(double (*f)(location_3d<double> )) : fp(f) {}

	inline double operator()(location_3d<double>  loc) const {
		return (*fp)(loc);}

private:
	double (*fp) (location_3d<double> );
};

class CRLThreadMakeRevAttribute:public CXBaseThread
{

public:
	CRLThreadMakeRevAttribute(CXParameterMakeRevInterpolation* pPara,CXObject* pCurveCells);
	~CRLThreadMakeRevAttribute();

	double *GetAttData(){return m_pSliceData;}
private:
	int m_nInputNum, m_nNPNum, m_nCovNum;

	CXKDTree3D* m_pKDTree;

	int* m_pIndex;
	double* m_pSliceData;
	int* m_pGridIndex;

	double *m_pX, *m_pY, *m_pZ,*m_pAtt;
	double **m_p2DCov, **m_p2DInv, **m_p2DTmp;
	double *m_pG, *m_pZBar;
	double *m_pEigenValue, *m_p1DTmp;

private:	
	int m_iMethod, m_iVariogramType, m_nMaxNum;
	double m_dRadius, m_dPower;
	double m_dAnis[4], m_dSill, m_dNugget, m_dRange, m_dRangeRatio;
	bool _InterpolateOneCellWithKriging();
	int _SearchIndex(int index);
	double _CalcCov(double deltaX, double deltaY, double deltaZ);
	void _CalcInverseMatrix();
private:
	CXParameterMakeRevInterpolation* m_pPara;

	CXObject* m_pSourceObj;
	CXPropertyModel *m_pPropObj;
	int m_nI, m_nJ, m_nK;

	//CXUTMTool m_utm;	

	int m_nRefNumCell;

	int m_nSampleCell;
	std::vector<Node> m_vNodes;

protected:
	virtual void RunThread();
	bool _InitData();
};



#endif