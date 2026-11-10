#ifndef XTHREADLFMINTERPOLATION_H
#define XTHREADLFMINTERPOLATION_H


#include "xbasethread.h"
#include "xdataplus_global.h"
#include "xseismicutmtool.h"

class CXParameterLFMInterpolation;
class CXLFMUpscalingAttribute;
class CXLFMGeometry;
class CXLFMAttribute;

class CXKDTree;

template<typename T> class CXRegularDataWriter;

/**
* @class CXThreadLFMInterpolation in the file "kethreadlfminterpolation.h"
* @brief The class provides a thread to interpolate LFM
*
* @author Yong Shu
* @date 11/26/2015
* @see
*/
class XDATAPLUS_EXPORT CXThreadLFMInterpolation : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadLFMInterpolation(CXParameterLFMInterpolation* pPara, CXLFMUpscalingAttribute* pUpscalingAtt);
	~CXThreadLFMInterpolation();

	///@brief Get output
	CXLFMAttribute* GetOutput() { return m_pLFMAttribute; }

protected:
	virtual void RunThread();

private:
	void _ParseParameter();

	inline double _CalcCov(double deltaX, double deltaY);
	void _CalcInverseMatrix();

	bool _InitData();
	bool _InitOneSlice(int iSlice);
	bool _InterpolateOneSliceWithKriging(int iSlice);
	bool _InterpolateOneSliceWithIDP(int iSlice);
	inline int _SearchIndex(int index);

	void _CalcAverageVelocity();

	bool _IsEnoughPoints();

private:
	CXParameterLFMInterpolation* m_pPara;

	CXLFMUpscalingAttribute* m_pUpscalingAtt;

	CXLFMGeometry* m_pLFMGeometry;

	CXSeismicUTMTool m_utm;

	int m_nI, m_nJ, m_nK;

private:
	int m_pInputNum, m_nNPNum, m_nCovNum;

	CXLFMAttribute* m_pLFMAttribute;

	CXRegularDataWriter<float>* m_pWriter;

	CXKDTree* m_pKDTree;

	int* m_pIndex;
	float* m_pSliceData;
	int* m_pGridIndex;

	double *m_pX, *m_pY, *m_pZ;
	double **m_p2DCov, **m_p2DInv, **m_p2DTmp;
	double *m_pG, *m_pZBar;
	double *m_pEigenValue, *m_p1DTmp;

	double m_dGlobalMean;

private:
	int m_iMethod, m_iVariogramType, m_nMaxNum;
	double m_dRadius, m_dPower;
	double m_dAnis[4], m_dSill, m_dNugget, m_dRange, m_dRangeRatio;

private:
	int m_iCurrent;
};

#endif // KETHREADLFMINTERPOLATION_H
