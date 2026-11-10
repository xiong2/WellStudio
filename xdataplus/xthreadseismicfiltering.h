#ifndef XTHREADSEISMICFILTERING_H
#define XTHREADSEISMICFILTERING_H


#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameterSeismicFiltering;
class CXSeismicDataVolume;
class CSeismicFiltering;

/**
* @class CXThreadSeismicFiltering provided in the file "kethreadseismicfiltering.h"
* @brief The Class provides a thread to do seismic filtering
*
* @author Yong Shu
* @date 5/18/2016
*/

class XDATAPLUS_EXPORT CXThreadSeismicFiltering : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadSeismicFiltering(CXParameterSeismicFiltering* pPara, CXSeismicDataVolume* pDV);
	virtual ~CXThreadSeismicFiltering();

	CXSeismicDataVolume* GetOutput() { return m_pOutDV; }


protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();
	void _CreateDV();

	void _Calc();


private:
	CXParameterSeismicFiltering* m_pPara;

	CXSeismicDataVolume* m_pInDV;
	CXSeismicDataVolume* m_pOutDV;

	float **m_p2DInData, **m_p2DOutData;

	std::vector<CSeismicFiltering*> m_vecCalculation;
};


#endif // KETHREADSEISMICFILTERING_H
