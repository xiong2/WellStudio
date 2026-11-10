#ifndef XTHREADAVOSSINVERSION_H
#define XTHREADAVOSSINVERSION_H

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameter3TermInversion;
class CXSeismicDataVolume;
class CXAVOSSInversion;
class CX3DHorizon;

template<typename T> class CXRegularDataReader;
template<typename T> class CXRegularDataWriter;

/**
* @class CXThreadAVOSSInversion provided in the file "kethreadavossinversion.h"
* @brief The Class provides a thread to make 3-term avo inversion
*
* @author Yong Shu
* @date 3/14/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadAVOSSInversion : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadAVOSSInversion(CXParameter3TermInversion* pPara);
	virtual ~CXThreadAVOSSInversion();

	vector<CXSeismicDataVolume*> GetOutput() { return m_vecOutputDV; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	void _GetHorizonData();
	bool _GetWaveletData();
	bool _GetReaders();
	bool _CreateDV();

	void _CalcPrestack();
	void _CalcPostack();
	void _CalcPostack2();
	void _CalcMinMax(vector<float>& vecZp, vector<float>& vecZs, vector<float>& vecRho, int nK, int& kMin, int& kMax);
	void _RearrangeSeismicData(vector<float>& vecPreTrace, vector<float>& vecSeismic, int nKSeismic, int nK, int iKOffset);
	void _CalcHorizonKRange(int iInline, int iXline, double dImpedSamplingStart, int nKImped, int& kminnew, int& kmaxnew);
		
	bool _WriterData(QList<CXAVOSSInversion*>& listCalc, int iOutputType, bool bExportR, bool bExportSeismic);


private:
	struct sDVInfo
	{
		sDVInfo() { reader = NULL; }

		CXRegularDataReader<float>* reader;

		CXSeismicUTMTool utm;

		double samplingRate;

		double samplingStart, samplingEnd;
	};

private:
	CXParameter3TermInversion* m_pPara;

	CXSeismicDataVolume* m_pPrestackDV;

	CXSeismicDataVolume* m_pZpDV;
	CXSeismicDataVolume* m_pZsDV;
	CXSeismicDataVolume* m_pRhoDV;

	vector<sDVInfo> m_vecDVInfo;

	vector<CXAVOSSInversion*> m_vecCalculation;

	// post stack seismic data volume
	vector<CXSeismicDataVolume*> m_vecPSDV;
	vector<CXRegularDataReader<float>* > m_vecPSDVReader;
	CXSeismicUTMTool m_utmPSDV;

private:
	//outout
	vector<CXSeismicDataVolume*> m_vecOutputDV;
	vector<CXRegularDataWriter<float>* > m_vecWriter;

private:
	int m_nAngleNum, m_nWaveletSize;
	vector<vector<float> > m_vec2DWavelet;
	vector<float> m_vecAngle;
	vector<int> m_vecAngleIndex;

	vector<double> m_vecMaxValue;

private:
	// horizon
	bool m_bHorizon;
	CX3DHorizon *m_pTopHor, *m_pBotHor;
	vector<float> m_vecTopHorData, m_vecBotHorData;
	CXSeismicUTMTool m_utmTop, m_utmBot;
	double m_dSamplingStart, m_dSamplingEnd, m_dSamplingRate;
	int m_iWriterOffset;
};

#endif // KETHREADAVOSSINVERSION_H
