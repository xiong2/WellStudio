#ifndef XTHREADMAKE2DGRID_H
#define XTHREADMAKE2DGRID_H

#include "xalgorithm_global.h"
#include "xbasethread.h"
#include "xutmtool.h"
#include <vector>

class CXParameterMake2DGrid;
class CX3DSurface;
class CXObject;

class CXKDTree;
class CXWell;


/**
* @class CXThreadMake2DGrid in the file "rlthreadmake2dgrid.h"
* @brief The class provides a thread to make a 2-D grid
* 
* @author Yong Shu
* @date 5/20/2014
* @see 
*/
class XALGORITHM_EXPORT CXThreadMake2DGrid : public CXBaseThread
{ 
public:
	///@brief Constructor and destructor
    CXThreadMake2DGrid(CXParameterMake2DGrid* pPara, CXObject* pWellTops);
    ~CXThreadMake2DGrid();

	std::vector<CX3DSurface*> GetOutput3DSurface() {return m_vecOutput;}


protected:
    virtual void RunThread();

private:
	void _ParseParameter();
	void _InitLock();
	void _CreateObj();

	inline double _CalcCov(double deltaX, double deltaY);
	void _CalcInverseMatrix();

	bool _InitData();
	bool _InitOneSlice(int iSlice);
	bool _InterpolateOneSliceWithKriging(int iSlice);
	bool _InterpolateOneSliceWithIDP(int iSlice);
	inline int _SearchIndex(int index);

	void _CalcIntersection();

	bool _CalcZ(double x, double y, float* pData, double& z);

	void _WriteToFile(double x0, double y0, CXWell* pWell, std::vector<std::vector<double> >& vecVecIntersect);

private:
	CXParameterMake2DGrid* m_pPara;

	CXObject* m_pSourceObj;

	int m_nI, m_nJ, m_nK;

	CXUTMTool m_utm;	

private:
	// output 
	std::vector<CX3DSurface*> m_vecOutput;

private:
	int m_nInputNum, m_nNPNum, m_nCovNum;

	CXKDTree* m_pKDTree;

	int* m_pIndex;
	float* m_pSliceData;
	int* m_pGridIndex;

	double *m_pX, *m_pY, *m_pZ;
	double **m_p2DCov, **m_p2DInv, **m_p2DTmp;
	double *m_pG, *m_pZBar;
	double *m_pEigenValue, *m_p1DTmp;

private:	
	int m_iMethod, m_iVariogramType, m_nMaxNum;
	double m_dRadius, m_dPower;
	double m_dAnis[4], m_dSill, m_dNugget, m_dRange, m_dRangeRatio;

private:
	// progress bar
	qint64 m_nTotal;
	qint64 m_iCurrent;
};

#endif // RLTHREADMAKE2DGRID_H
