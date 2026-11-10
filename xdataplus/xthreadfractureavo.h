#ifndef XTHREADFRACTUREAVO_H
#define XTHREADFRACTUREAVO_H

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameterFractureAVO;
class CXSeismicDataVolume;

template<typename T> class CXRegularDataWriter;

/**
* @class CXThreadFractureAVO provided in the file "kethreadfractureavo.h"
* @brief The Class provides a thread for AVO fracture analysis
*
* @author Yong Shu
* @date 9/27/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadFractureAVO : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadFractureAVO(CXParameterFractureAVO* pPara);
	virtual ~CXThreadFractureAVO();

	vector<CXSeismicDataVolume*> GetOutput() { return m_vecOutputDV; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	bool _GetReaders();
	bool _CreateDV();

	void _CalcPostack();


private:
	CXParameterFractureAVO* m_pPara;

	// input data volumes
	vector<CXSeismicDataVolume*> m_vecInDV;

	CXSeismicDataVolume* m_pAziDV;

	int m_nMaxNK, m_nMaxFold;

private:
	//outout
	vector<CXSeismicDataVolume*> m_vecOutputDV;
	vector<CXRegularDataWriter<float>* > m_vecWriter;
};


#endif // KETHREADFRACTUREAVO_H
