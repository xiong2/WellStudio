#ifndef XTHREADANISOTROPYFORWARDING_H
#define XTHREADANISOTROPYFORWARDING_H

#include "xbasethread.h"
#include "xdataplus_global.h"
#include <QList>
#include <vector>
#include "xseismicutmtool.h"

using std::vector;

class CXParameterAnisotropyForwarding;
class CXSeismicDataVolume;

template<typename T> class CXRegularDataReader;

/**
* @class CXThreadAVOSSInversion provided in the file "kethreadavossinversion.h"
* @brief The Class provides a thread to make 3-term avo inversion
*
* @author Yong Shu
* @date 12/26/2016
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadAnisotropyForwarding : public CXBaseThread
{
public:
	///@brief Constructor and destructor
	CXThreadAnisotropyForwarding(CXParameterAnisotropyForwarding* pPara);
	virtual ~CXThreadAnisotropyForwarding();

	CXSeismicDataVolume* GetOutput() { return m_pOutputDV; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	void _Init();
	bool _GetWaveletData();
	bool _CreateBuffers();

	bool _GetReaders();
	bool _CreateDV();
	void _CalcW(int nK);

	void _Calculate();

	void _FindValidRange(int nReaderNum);
	bool _WriteInfoFile();

	void _Interpolation(int nReaderNum);


private:
	CXParameterAnisotropyForwarding* m_pPara;

	vector<CXSeismicDataVolume*> m_vecInputDV;

	CXSeismicDataVolume* m_pOutputDV;

	// post stack seismic data volume
	vector<CXRegularDataReader<float>* > m_vecReader;

	CXSeismicUTMTool m_utmIn, m_utmOut;

private:
	int m_nIIn, m_nJIn, m_nKIn;
	int m_nIOut, m_nJOut, m_nKOut;
	int m_nAziNum, m_nIncNum, m_nFold;
	int m_nWaveletSize;

	vector<double> m_vecAzimuth, m_vecIncidence;
	vector<int> m_vecWaveletPeakIndex;

private:
	vector<double*> m_vecInputwaveletData;
	vector<double*> m_vecpW;
	vector<float*> m_vecInput;
	vector<float> m_vecOutput;
	vector<double*> m_vecR;
	
	char* m_pInfoBuffer;

	// interpolation
	vector<double> m_vecX, m_vecY, m_vecX2, m_vecY2;

private:
	int m_kMin, m_kMax, m_nK;



};

#endif // KETHREADANISOTROPYFORWARDING_H
