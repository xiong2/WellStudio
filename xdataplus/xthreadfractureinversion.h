#ifndef XTHREADFRACTUREINVERSION_H
#define XTHREADFRACTUREINVERSION_H

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include <qmap.h>
#include "xseismicutmtool.h"

using std::vector;

class CXParameter3TermInversion;
class CXSeismicDataVolume;
class CX3DHorizon;
class CXAVOSSInversion;
class CXAsynRegularWriter;

template<typename T> class CXRegularDataReader;

/**
* @class CXThreadFractureInversion provided in the file "kethreadfractureinversion.h"
* @brief The Class provides a thread for fracture inversion
*
* @author Yong Shu
* @date 12/19/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadFractureInversion : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadFractureInversion(CXParameter3TermInversion* pPara);
	virtual ~CXThreadFractureInversion();

	CXSeismicDataVolume* GetOutput() { return m_pOutputDV; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();
	bool _CreateDV();

	void _Calculate();

	bool _GetWaveletDataAndAziInfo();
	void _GetHorizonData();
	bool _GetReaders();

	void _GetNextIJLineNum(CXSeismicUTMTool& utm, int iInline, int iXline, int& iInlineNext, int& iXlineNext);
	void _CalcMinMax(int nK, int& kMin, int& kMax);
	void _CalcHorizonKRange(int iInline, int iXline, double dImpedSamplingStart, int nKImped, int& kminnew, int& kmaxnew);
	void _ParseSeismicData(int iAzi, float* pGather, float* pOffAzi, int nFold, int nK, vector<float>& vecSeismic);
	bool _WriterData(CXAsynRegularWriter* pWriter, int nK);
	void _Write2Buffer(qint64 iCount, int iInlineNum, int iXlineNum);
	bool _WriteInfoFile();

	void _CalcZpZsRhoWithAzi(int kmin, int kmax, int nK);

private:
	struct sDVInfo
	{
		sDVInfo() { reader = NULL; }

		CXRegularDataReader<float>* reader;

		CXSeismicUTMTool utm;

		double samplingRate;

		double samplingStart, samplingEnd;

		vector<float> vecTraceData;
	};


private:
	CXParameter3TermInversion* m_pPara;

	CXSeismicDataVolume* m_pAziDV;
	CXSeismicDataVolume* m_pZpDV;
	CXSeismicDataVolume* m_pZsDV;
	CXSeismicDataVolume* m_pRhoDV;	

	CXSeismicDataVolume* m_pEpsilonDV;
	CXSeismicDataVolume* m_pDeltaDV;
	CXSeismicDataVolume* m_pGammaDV;
	CXSeismicDataVolume* m_pSymAziDV;

	vector<sDVInfo> m_vecDVInfo;

	int m_nMaxNK, m_nMaxFold;

	CXSeismicUTMTool m_utm;

private:
	//outout
	CXSeismicDataVolume* m_pOutputDV;

private:
	// wavelet
	vector<vector<float> > m_vec2DWavelet;
	// DV info buffer
	char* m_pInfoBuffer;

private:
	// calculation
	struct sAziInfo
	{
		float azimuth;

		vector<float> vecOffset;
		vector<vector<float> > vec2DWavelet;
		vector<float> vecZp, vecZs, vecRho;
	};

	vector<sAziInfo> m_vecAziInfo;
	int m_nMaxAngleNum;

	vector<CXAVOSSInversion*> m_vecCalculation;

	vector<float> m_vecEpsilonR, m_vecDeltaR, m_vecGammaR;


private:
	// horizon
	bool m_bHorizon;
	CX3DHorizon *m_pTopHor, *m_pBotHor;
	vector<float> m_vecTopHorData, m_vecBotHorData;
	CXSeismicUTMTool m_utmTop, m_utmBot;
	double m_dSamplingStart, m_dSamplingEnd, m_dSamplingRate;
	int m_iWriterOffset;
};



#endif // KETHREADFRACTUREINVERSION_H
