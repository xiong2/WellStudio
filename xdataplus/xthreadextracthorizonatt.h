#ifndef XTHREADEXTRACTHORIZONATT_H
#define XTHREADEXTRACTHORIZONATT_H

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>

using std::vector;

class CXParameterExtractHorizonAtt;
class CXSeismicDataVolume;
class CX3DHorizon;


/**
* @class CXThreadExtractHorizonAtt provided in the file "kethreadextracthorizonatt.h"
* @brief The Class provides a thread for extracting horizon attributes
*
* @author Yong Shu
* @date 9/27/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadExtractHorizonAtt : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadExtractHorizonAtt(CXParameterExtractHorizonAtt* pPara);
	virtual ~CXThreadExtractHorizonAtt();

	vector<CX3DHorizon*> GetOutput() { return m_vecOutputAtt; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	CX3DHorizon* _CreateAtt(int iDV);

	bool _Calc(int iDV);


private:
	CXParameterExtractHorizonAtt* m_pPara;

	CX3DHorizon* m_pParent;

	// input data volumes
	vector<CXSeismicDataVolume*> m_vecInDV;

private:
	//outout
	vector<CX3DHorizon*> m_vecOutputAtt;
};


#endif // KETHREADEXTRACTHORIZONATT_H
