#ifndef XTHREADFRACTUREAVAZ_H
#define XTHREADFRACTUREAVAZ_H


#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameterFractureAVO;
class CXSeismicDataVolume;
class CXAVAZRuger;
class CXAVAZFCs;

template<typename T> class CXRegularDataWriter;

/**
* @class CXThreadFractureAVAZ provided in the file "kethreadfractureavaz.h"
* @brief The Class provides a thread for AVO fracture analysis
*
* @author Yong Shu
* @date 10/26/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadFractureAVAZ : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadFractureAVAZ(CXParameterFractureAVO* pPara);
	virtual ~CXThreadFractureAVAZ();

	vector<CXSeismicDataVolume*> GetOutput() { return m_vecOutputDV; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	bool _CreateDV();

	void _Calculate();
	void _CalcMinMax(int nThread, int nK, vector<QPair<int, int> > & vecPair);


private:
	CXParameterFractureAVO* m_pPara;

	CXSeismicDataVolume* m_pAziDV;

	int m_nMaxNK, m_nMaxFold;

	CXSeismicUTMTool m_utm;

	QList<CXAVAZRuger*> m_listMethod;
	QList<CXAVAZFCs*> m_listMethodFC;

private:
	//outout
	vector<CXSeismicDataVolume*> m_vecOutputDV;
};

#endif // KETHREADFRACTUREAVAZ_H
