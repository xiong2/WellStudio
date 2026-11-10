#ifndef XTHREADCSSINVERSION_H
#define XTHREADCSSINVERSION_H

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameterCSSInversion;
class CXSeismicDataVolume;
class CXCSSInversion;

template<typename T> class CXRegularDataReader;
template<typename T> class CXRegularDataWriter;

/**
* @class CXThreadCSSInversion provided in the file "kethreadcssinversion.h"
* @brief The Class provides a thread to make CSSI
*
* @author Yong Shu
* @date 1/18/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadCSSInversion : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadCSSInversion(CXParameterCSSInversion* pPara);
	virtual ~CXThreadCSSInversion();

	vector<CXSeismicDataVolume*> GetOutput() { return m_vecOutputDV; }


protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	bool _GetWaveletData();
	bool _GetReaders();
	bool _CreateDV();

	void _Calc();
	void _CalcMinMax(vector<float>& vecZp, int nK, int& kMin, int& kMax);
	void _RearrangeSeismicData(vector<float>& vecPreTrace, vector<float>& vecSeismic, int nK, int iKOffset);
	
	bool _WriterData(QList<CXCSSInversion*>& listCalc, int nZ, bool bExportR, bool bExportSeismic);



private:
	CXParameterCSSInversion* m_pPara;

	CXSeismicDataVolume* m_pInputDV;
	CXSeismicDataVolume* m_pZp0DV;

	vector<CXCSSInversion*> m_vecCalculation;

	vector<CXRegularDataReader<float>* > m_vecDVReader;
	CXSeismicUTMTool m_utmSeismicDV, m_utmZP0;

private:
	//outout
	vector<CXSeismicDataVolume*> m_vecOutputDV;
	vector<CXRegularDataWriter<float>* > m_vecWriter;

private:
	int m_nWaveletSize;
	vector<float> m_vecWavelet;
};


#endif // KETHREADCSSINVERSION_H
