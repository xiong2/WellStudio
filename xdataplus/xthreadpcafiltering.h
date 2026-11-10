#ifndef XTHREADPCAFILTERING_H
#define XTHREADPCAFILTERING_H

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameterPCAFiltering;
class CXSeismicDataVolume;
class CXCSSInversion;

template<typename T> class CXRegularDataReader;
template<typename T> class CXRegularDataWriter;

/**
* @class CXThreadPCAFiltering provided in the file "kethreadpcafiltering.h"
* @brief The Class provides a thread to Calculate PCA filtering
*
* @author Yong Shu
* @date 6/8/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadPCAFiltering : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadPCAFiltering(CXParameterPCAFiltering* pPara, CXSeismicDataVolume* pDV);
	virtual ~CXThreadPCAFiltering();

	CXSeismicDataVolume* GetOutput() { return m_pOutDV; }


protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	bool _GetReaders();
	bool _CreateDV();

	void _Calc();

	bool _ReadData(int iIndex, int nIold, int nJold, int nK, int jMin, int jMax, int nWinNI, float* pInData, float* pTmpBuff, int& nTrueWinNI);
	bool _GetOutputIndex(int nThreadNum, int iThreadIndex, int nJ, int& jMin, int& jMax);



private:
	CXParameterPCAFiltering* m_pPara;

	CXSeismicDataVolume* m_pInDV;
	CXSeismicDataVolume* m_pOutDV;

	CXRegularDataReader<float>* m_pReader;
	CXRegularDataWriter<float>*  m_pWriter;

	CXSeismicUTMTool m_utmSeismicDV, m_utmZP0;

	QList<int> m_listIndex;

};

#endif // KETHREADPCAFILTERING_H
