#pragma warning( push ,0 )
#include "xthreadseismicfiltering.h"
#include "xparameterseismicfiltering.h"
#include "xseismicdatavolume.h"
#include <QCoreApplication>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>
#include "xglobal.h"
#include "xmathmacro.h"
#include "xproject.h"
#include "xutility.h"
#include <QFile>
#include "xregulardatareader.h"
#include "xregulardatawriter.h"
#include "xsysteminfo.h"
#include <qtconcurrentmap.h>

#pragma warning( pop )

class CSeismicFiltering
{
public:
	CSeismicFiltering(CXParameterSeismicFiltering* pPara)
	{
		m_f1 = pPara->GetLowCutFreq();
		m_f1over = pPara->GetLowCutOverlapped();
		m_f2 = pPara->GetHighCutFreq();
		m_f2over = pPara->GetHighCutOverlapped();
		m_dt = pPara->GetSamplingRate();
		m_bZeroInvalid = pPara->GetTreatZeroInvalid();

		m_pIn = m_pOut = NULL;
		m_pFFT = m_pH1 = m_pH2 = NULL;
	}

	~CSeismicFiltering()
	{
		if (m_pFFT) delete[]m_pFFT;
		if (m_pH1) delete[]m_pH1;
		if (m_pH2) delete[]m_pH2;
		if (m_pIn) delete[]m_pIn;
		if (m_pOut) delete[]m_pOut;
	}

	bool InitBuffer(int nMax)
	{
		m_nMax = nMax;

		int nFFTSize = NXUtility::LengthofFFT(2 * nMax);		
		try
		{
			m_pFFT = new double[2 * nFFTSize];
			m_pH1 = new double[ nFFTSize];
			m_pH2 = new double[ nFFTSize];

			m_pIn = new double[nMax];
			m_pOut = new double[nMax];
		}
		catch (std::bad_alloc)
		{
			return false;
		}
		return true;
	}

	void SetData(float* pIn, float* pOut)
	{
		m_pInData = pIn;
		m_pOutData = pOut;
	}

	void Calculate()
	{
		// calculate min and max
		float finvalid = ::g_dInvalidData;
		float finvalideps = ::GetEPSofInvalidData(finvalid);
		int imin(m_nMax - 1), imax(0);

		// imin
		for (int i = 0; i < m_nMax; ++i)
		{
			if (m_pInData[i] == 0.f && m_bZeroInvalid || qAbs(m_pInData[i] - finvalid) < finvalideps)
				continue;
			else
			{
				imin = i;
				break;
			}
		}

		// imax
		for (int i = m_nMax-1; i >= 0; --i)
		{
			if (m_pInData[i] == 0.f && m_bZeroInvalid || qAbs(m_pInData[i] - finvalid) < finvalideps)
				continue;
			else
			{
				imax = i;
				break;
			}
		}

		int n = imax - imin + 1;
		if (n < 2)
			return;

		for (int i = imin; i <= imax; ++i)
		{
			m_pIn[i - imin] = m_pInData[i];
		}

		NXUtility::DigitalFilter(n, m_pIn, m_pOut, m_dt, m_f1, m_f1over, m_f2, m_f2over, m_pFFT, m_pH1, m_pH2);

		//write back
		for (int i = 0; i < m_nMax; ++i)
		{
			if (i<imin || i>imax)
				m_pOutData[i] = finvalid;
			else
				m_pOutData[i] = (float)m_pOut[i - imin];
		}
	}


private:	
	double m_f1, m_f1over, m_f2, m_f2over, m_dt;
	bool m_bZeroInvalid;	
	double *m_pIn, *m_pOut, *m_pFFT, *m_pH1, *m_pH2;
	int m_nMax;
	float* m_pInData, *m_pOutData;

};

// in order to use qt concurrent
void CalculateSeismicFiltering(CSeismicFiltering* pCalculation)
{
	pCalculation->Calculate();
}


CXThreadSeismicFiltering::CXThreadSeismicFiltering(CXParameterSeismicFiltering* pPara, CXSeismicDataVolume* pDV)
{
	m_pPara = pPara;
	m_pInDV = pDV;
	assert(m_pPara && m_pInDV);
		
	m_pOutDV = NULL;

	m_p2DInData = NULL;
	m_p2DOutData = NULL;

	_Init();
}

CXThreadSeismicFiltering::~CXThreadSeismicFiltering()
{
	wait();

	// unlock object
	if (m_pInDV)	UnlockRead(m_pInDV);


	if (m_p2DInData) NXUtility::Free2DMatrix<float>(m_p2DInData);
	if (m_p2DOutData) NXUtility::Free2DMatrix<float>(m_p2DOutData);

	// calculation
	qDeleteAll(m_vecCalculation);
	m_vecCalculation.clear();

	if (IsStopped())
	{
		QFile::remove(m_pOutDV->GetTraceFileName());
		delete m_pOutDV;
	}
}

void CXThreadSeismicFiltering::_Init()
{
	if (m_pInDV)
		m_pInDV->LockObject(this);
}

void CXThreadSeismicFiltering::_CreateDV()
{
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pInDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	// output
	m_pOutDV = new CXSeismicDataVolume(m_pInDV->GetUTM(), dSamplingStart, dSamplingEnd, dSamplingRate, m_pPara->GetFilteringName());
}



void CXThreadSeismicFiltering::_Calc()
{
	_CreateDV();

	this->EmitResetProgressBar();
	this->EmitSetTaskName("Calculating");
	QCoreApplication::instance()->processEvents();

	// target DV UTM
	int nI = m_pOutDV->GetInlineQty();
	int nJ = m_pOutDV->GetXlineQty();
	int nK = m_pOutDV->GetSamplingQty();

	// reader
	CXRegularDataReader<float> reader = CXRegularDataReader<float>(m_pInDV->GetTraceFileName(), nI, nJ, nK);
	if (!reader.Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the seismic data.");
		return;
	}

	// writer
	CXRegularDataWriter<float> writer = CXRegularDataWriter<float>(m_pOutDV->GetTraceFileName(), nI, nJ, nK);
	if (!writer.Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the file to write data.");
		return;
	}

	m_pPara->SetSamplingRate(m_pInDV->GetSampleInterval());

	//int nThread = 1;
	int nThread = CXSystemInfo::GetCPUNum();
	for (int i = 0; i < nThread; ++i)
	{
		CSeismicFiltering* pCalculation = new CSeismicFiltering(m_pPara);
		pCalculation->InitBuffer(nK);
		m_vecCalculation.push_back(pCalculation);
	}

	// buffers
	m_p2DInData = NXUtility::New2DMatrix<float>(nThread, nK);
	m_p2DOutData = NXUtility::New2DMatrix<float>(nThread, nK);
	if (!m_p2DInData || !m_p2DOutData)
	{
		this->EmitMemoryNotEnough();
		return;
	}

	int nCurrentThread = 0;
	QList<CSeismicFiltering*> listCalculation;
	for (int i = 0; i < nI; ++i)
	{
		for (int j = 0; j < nJ; ++j)
		{
			// read
			// seismic
			if (!reader.ReadUVTrace(i, j, m_p2DInData[nCurrentThread]))
			{
				this->EmitGeneralErrorMsg("Cannot read data from the seismic file.");
				return;
			}

			m_vecCalculation[nCurrentThread]->SetData(m_p2DInData[nCurrentThread], m_p2DOutData[nCurrentThread]);
			++nCurrentThread;

			if (nCurrentThread < nThread && !(i == nI-1 && j == nJ-1))
				continue;

			if (IsStopped())
				return;
			else
			{
				this->EmitUpdateProgress(i*nJ+ j, nI*nJ);
			}

			listCalculation.clear();
			for (int iCalc = 0; iCalc < nCurrentThread; ++iCalc)
				listCalculation.append(m_vecCalculation[iCalc]);

			// calculate			
			QtConcurrent::blockingMap<QList<CSeismicFiltering*> >(listCalculation, CalculateSeismicFiltering);

			//write data
			for (int ii = 0; ii < listCalculation.size(); ++ii)
			{
				if (!writer.Append(nK, m_p2DOutData[ii]))
				{
					this->EmitGeneralErrorMsg("Cannot write data to the disk.");
					return;
				}
			}

			if (IsStopped())
				return;

			nCurrentThread = 0;
		}
	}
}

void CXThreadSeismicFiltering::RunThread()
{
	if (!m_pInDV)
	{
		this->EmitGeneralErrorMsg("The seismic data volume has been deleted.");
		return;
	}

	this->EmitSetWindowName("Seismic Filtering");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();


	_Calc();
}



