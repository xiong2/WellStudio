#ifndef XTHREAD3TERMAVOINVERSION_H
#define XTHREAD3TERMAVOINVERSION_H


#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameter3TermInversion;
class CXSeismicDataVolume;
class CXAVOInversion;

template<typename T> class CXRegularDataReader;
template<typename T> class CXRegularDataWriter;

class CX2DSeismicLine;

/**
* @class CXThread3TermAVOInversion provided in the file "kethread3termavoinversion.h"
* @brief The Class provides a thread to make 3-term avo inversion
*
* @author Yong Shu
* @date 12/14/2015
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThread3TermAVOInversion : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThread3TermAVOInversion(CXParameter3TermInversion* pPara);
	virtual ~CXThread3TermAVOInversion();

	vector<CXSeismicDataVolume*> GetOutput() { return m_vecOutputDV; }

	CX2DSeismicLine* Get2DLine() { return m_p2DLine; }


protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();

	bool _GetWaveletData();
	bool _GetReaders();
	bool _CreateDV();	

	void _CalcPrestack();
	void _CalcPostack();
	void _CalcMinMax(vector<float>& vecZp, vector<float>& vecZs, vector<float>& vecRho, int nK, int& kMin, int& kMax);
	void _RearrangeSeismicData(vector<float>& vecPreTrace, vector<float>& vecSeismic, int nKSeismic, int nK, int iKOffset);	

	bool _WriteThreeComponents(float* pZp, float* pZs, float* pRho, vector<float>& vecBuffer, int nZ, int iOutputType);
	bool _WriterData(QList<CXAVOInversion*>& listCalc, vector<float>& vecBuffer, int nZ, int iOutputType, bool bExportR, bool bExportSeismic);

	//codes for test data
	void _Calc_Test();
	bool _GetWaveletData_Test();
	void _ReadTestCode(vector<float>& vecSeismic, vector<float>& vecZp, vector<float>& vecZs, vector<float>& vecRho, int index);
	bool _Create2DDVAndReaders();
	void _ConvertData(char* pChar, float* fData, int nDataLength);


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

	vector<CXAVOInversion*> m_vecCalculation;

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

	bool m_bTest;
	CX2DSeismicLine* m_p2DLine;

	vector<double> m_vecMaxValue;

};


#endif // KETHREAD3TERMAVOINVERSION_H
