#pragma once
#include "xbaseparameter.h"
#include "xbasethread.h"

class CXSeismicDataVolume;

namespace Pyramid_Filter
{
	void conv3x3(int nx, int ny, double* pin, double* pout, double kernel[][3]);
	void get_x_y_kernels(double kernel_x[][3], double kernel_y[][3]);
	void S_Filtering(int nx, int ny, float* pIn, float* pOut, double theta);
}

class XParameterPyramid : public CXBaseParameter
{
public:
	X_PROPERTY(QUuid, DVID);
	X_PROPERTY(int, InputInlineS);
	X_PROPERTY(int, InputInlineE);
	X_PROPERTY(int, InputXlineS);
	X_PROPERTY(int, InputXlineE);
	X_PROPERTY(double, InputTimeS);
	X_PROPERTY(double, InputTimeE);
	X_PROPERTY(int, FDirection);
	X_PROPERTY(int, FDegree);
	X_PROPERTY(int, ODegree);
	X_PROPERTY(bool, UsingPolygon);
	X_PROPERTY(std::vector<double>, VecPoints);
	X_PROPERTY(QString, ODVName);
};

class XThreadPyramid : public CXBaseThread
{
public:
	XThreadPyramid(XParameterPyramid *pPara) : m_pPara(pPara) {}

	CXSeismicDataVolume* GetOutputDV() { return m_pODV; }

protected:
	virtual void RunThread() override;

private:
	void calculate();

	XParameterPyramid*		m_pPara;
	CXSeismicDataVolume*	m_pODV = nullptr;
};