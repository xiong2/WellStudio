#ifndef XTHREADWELLHORIZONINTERSECT_H
#define XTHREADWELLHORIZONINTERSECT_H

#include "xbasethread.h"
#include <vector>
#include "xutmtool.h"

class CXParameterWellHorzionIntersect;
class CX3DSurface;
class CXWell;

/**
 * @class CXThreadWellHorizonIntersect provided in the file "rlthreadwellhorizonintersect.h"
 * @brief The Class provides a thread to calculate intersection between the verital well profile 
 * @breif and 3-D horizon
 * 
 * @author Yong Shu 
 * @date 6/6/2014
 * @see 
 * @bug	No Known bugs so far
 */

class CXThreadWellHorizonIntersect : public CXBaseThread
{
public:
    ///@brief Constructor and destructor
	CXThreadWellHorizonIntersect(CXWell* pWell, CXParameterWellHorzionIntersect* pPara);
	virtual ~CXThreadWellHorizonIntersect();

protected:
	/// Reimplementation of run()
	virtual void RunThread();			

private:
	void _Init();

	bool _CalcZ(double x, double y, float* pData, double& z);

	void _WriteToFile(double x0, double y0, CXWell* pWell, std::vector<std::vector<double> >& vecVecIntersect);

	void _CalcIntersection();

private:
	CXWell* m_pWell;

	// parameter
	CXParameterWellHorzionIntersect* m_pPara;

	// Intput surfaces
	std::vector<CX3DSurface*> m_vecInputSurface;

	// UTM
	CXUTMTool m_utm;
 
};

#endif // RLTHREADWELLHORIZONINTERSECT_H
