#ifndef XTHREADFRACTUREATTRIBUTE_H
#define XTHREADFRACTUREATTRIBUTE_H


#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameterFractureAttribute;
class CXSeismicDataVolume;

template<typename T> class CXRegularDataWriter;
template<typename T> class CXRegularDataReader;

/**
* @class CXThreadFractureAttribute provided in the file "kethreadfractureattribute.h"
* @brief The Class provides a thread for fracture attribute
*
* @author Yong Shu
* @date 12/28/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadFractureAttribute : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadFractureAttribute(CXParameterFractureAttribute* pPara);
	virtual ~CXThreadFractureAttribute();

	vector<CXSeismicDataVolume*> GetOutput() { return m_vecOutputDV; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	bool _CreateDV();

	void _Calculate();
	void _CalcMinMax(int nThread, int nK, vector<QPair<int, int> > & vecPair);

	bool _GetAzimuth();

	bool _InitFilters();
	bool _Filtering(int iInline, int iXline, int iKOffset, int nKAziDV, int nK, vector<float*>& vecData);
	void _CalcKMinMax(int nK, int&kmin, int& kmax);
	void _CalcKMinMax2(int nK, int&kmin, int& kmax, vector<float*>& vecData);

private:
	CXParameterFractureAttribute* m_pPara;

	CXSeismicDataVolume* m_pInDV;

	vector<CXSeismicDataVolume*> m_vecOutputDV;

	int m_nMaxNK, m_nMaxFold;

	CXSeismicUTMTool m_utm;

	vector<double> m_vecAzimuth;	

	// filtered
private:
	bool m_bFilter;

	vector<CXSeismicDataVolume*> m_vecLFMDV;

	// post stack seismic data volume
	vector<CXRegularDataReader<float>* > m_vecLFMReader;

	vector<double> m_vecEr, m_vecDr, m_vecGr, m_vecK, m_vecLow, m_vecBand;
	vector<float>   m_vecVp, m_vecVs, m_vecE, m_vecD, m_vecG, m_vecAzi;
	vector<double> m_vecB1, m_vecA, m_vecB1Calc, m_vecACalc;
	CXSeismicUTMTool m_utmIn;

	double *m_pFFTBuffer, *m_pH1, *m_pH2, *m_pFFTOut1, *m_pFFTOut2;
	double m_df1, m_df1ovp, m_df2, m_df2ovp, m_dt;
};

#endif // KETHREADFRACTUREATTRIBUTE_H
