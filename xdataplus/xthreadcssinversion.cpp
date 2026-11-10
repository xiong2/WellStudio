#pragma warning( push ,0 )
#include "xthreadcssinversion.h"
#include "xparametercssinversion.h"
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
#include "xcssinversion.h"
#include <QFile>
#include "xregulardatareader.h"
#include "xregulardatawriter.h"
#include "xsysteminfo.h"
#include <qtconcurrentmap.h>
#include "mkl.h"
#include "xwavelet.h"

#pragma warning( pop )

// in order to use qt concurrent
void CalculateCSSInversion(CXCSSInversion* pCalculation)
{
	pCalculation->Calculate();
}


CXThreadCSSInversion::CXThreadCSSInversion(CXParameterCSSInversion* pPara)
{
	m_pPara = pPara;

	_Init();
}

CXThreadCSSInversion::~CXThreadCSSInversion()
{
	wait();

	// unlock object
	if (m_pInputDV)	UnlockRead(m_pInputDV);
	if (m_pZp0DV)	UnlockRead(m_pZp0DV);

	//dv readers
	qDeleteAll(m_vecDVReader);
	m_vecDVReader.clear();

	// writers
	qDeleteAll(m_vecWriter);
	m_vecWriter.clear();

	// calculation
	qDeleteAll(m_vecCalculation);
	m_vecCalculation.clear();

	if (IsStopped())
	{
		for (int i = 0; i < m_vecOutputDV.size(); ++i)
		{
			QFile::remove(m_vecOutputDV[i]->GetTraceFileName());
		}
		qDeleteAll(m_vecOutputDV);
		m_vecOutputDV.clear();
	}
}

void CXThreadCSSInversion::_Init()
{
	m_pInputDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetDVID()));

	m_pZp0DV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetImpedanceID()));

	if (m_pInputDV)		LockRead(m_pInputDV);
	if (m_pZp0DV)		LockRead(m_pZp0DV);

}

bool CXThreadCSSInversion::_GetWaveletData()
{
	QString strFileName = m_pPara->GetWaveletFileName();
	QUuid uuidWavelet = m_pPara->GetWaveletID();
	
	if (QFile::exists(strFileName))
	{
		QFile qFile(strFileName);
		if (!qFile.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			this->EmitGeneralErrorMsg("Cannot read wavelet data from the disk.");
			return false;
		}
		float fValue;
		bool b;
		while (!qFile.atEnd())
		{
			QString strLine = qFile.readLine();
			fValue = strLine.toFloat(&b);
			if (b)
			{
				m_vecWavelet.push_back(fValue);
			}
		}
	}
	else
	{
		CXWavelet* pWavelet = dynamic_cast<CXWavelet*>(::GetObjectByID(uuidWavelet));
		if (pWavelet)
		{
			unsigned int ndataLength;
			double *pData = pWavelet->CXObject::GetData(ndataLength);
			m_vecWavelet.resize(ndataLength);
			if (pData)
				std::transform(pData, pData + ndataLength, m_vecWavelet.begin(), [](double d) {return static_cast<float>(d); });
		}
	}
	m_nWaveletSize = (int)m_vecWavelet.size();

	if (m_nWaveletSize == 0)
	{
		this->EmitGeneralErrorMsg("Cannot read wavelet data.");
		return false;
	}

	if (IsStopped())
		return false;
	else
		this->EmitUpdateProgress(10, 30);

	return true;
}

bool CXThreadCSSInversion::_GetReaders()
{
	// seismic
	if (m_pInputDV)
	{
		CXRegularDataReader<float>* pReader = new CXRegularDataReader<float>(m_pInputDV->GetTraceFileName(), m_pInputDV->GetInlineQty(),
			m_pInputDV->GetXlineQty(), m_pInputDV->GetSamplingQty());

		m_vecDVReader.push_back(pReader);

		m_utmSeismicDV = m_pInputDV->GetUTM();

		if (!pReader->Open())
		{
			this->EmitGeneralErrorMsg("Cannot open the seismic data file.");
			return false;
		}
	}

	// impedance
	if (m_pZp0DV)
	{
		CXRegularDataReader<float>* pReader = new CXRegularDataReader<float>(m_pZp0DV->GetTraceFileName(), m_pZp0DV->GetInlineQty(),
			m_pZp0DV->GetXlineQty(), m_pZp0DV->GetSamplingQty());

		m_vecDVReader.push_back(pReader);

		m_utmZP0 = m_pZp0DV->GetUTM();

		if (!pReader->Open())
		{
			this->EmitGeneralErrorMsg("Cannot open the impedance file.");
			return false;
		}
	}	

	if (IsStopped())
		return false;
	else
		this->EmitUpdateProgress(20, 30);

	return true;
}

bool CXThreadCSSInversion::_CreateDV()
{
	CXSeismicUTMTool utm = m_utmSeismicDV;

	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	iInlineMin = m_pPara->GetMinInlineNum();
	iInlineMax = m_pPara->GetMaxInlineNum();
	iInlineInc = m_pPara->GetInlineInc();
	iXlineMin = m_pPara->GetMinXlineNum();
	iXlineMax = m_pPara->GetMaxXlineNum();
	iXlineInc = m_pPara->GetXlineInc();

	int nInlineNum = (iInlineMax - iInlineMin) / iInlineInc + 1;
	int nXlineNum = (iXlineMax - iXlineMin) / iXlineInc + 1;

	utm.Resize(iInlineMin, iXlineMin, nInlineNum, nXlineNum);

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pZp0DV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	// Zp output
	CXSeismicDataVolume* pNewZpDv = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, "Zp");
	CXSeismicDataVolume* pNewZpBPDv = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, "Zp bp");
	CXSeismicDataVolume* pNewZpMergeDv = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, "Zp merged");

	m_vecOutputDV.push_back(pNewZpDv);
	m_vecOutputDV.push_back(pNewZpBPDv);
	m_vecOutputDV.push_back(pNewZpMergeDv);

	// reflectivity
	if (m_pPara->GetExportReflectivity())
	{
		CXSeismicDataVolume* pDV = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, "R");
		m_vecOutputDV.push_back(pDV);
	}

	// seismic
	if (m_pPara->GetExportSeismic())
	{
		CXSeismicDataVolume* pDV = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, "Seismic");
		m_vecOutputDV.push_back(pDV);
	}

	//writer
	for (int i = 0; i < m_vecOutputDV.size(); ++i)
	{
		CXRegularDataWriter<float>* pWriter = new CXRegularDataWriter<float>(m_vecOutputDV[i]->GetTraceFileName(), nInlineNum, nXlineNum, m_vecOutputDV[i]->GetSamplingQty());
		m_vecWriter.push_back(pWriter);

		if (!pWriter->Open())
		{
			this->EmitGeneralErrorMsg("Cannot open the file to write data.");
			return false;
		}
	}

	if (IsStopped())
		return false;
	else
		this->EmitUpdateProgress(30, 30);

	return true;
}

void CXThreadCSSInversion::_CalcMinMax(vector<float>& vecZp, int nK, int& kMin, int& kMax)
{
	float fInvalid = g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

	for (int k = 0; k < nK; ++k)
	{
		if (qAbs(vecZp[k] - fInvalid) < fInvalidEPS || vecZp[k] <= 0.f )
		{
			continue;
		}
		else
		{
			kMin = k;
			break;
		}
	}

	for (int k = nK - 1; k >= 0; --k)
	{
		if (qAbs(vecZp[k] - fInvalid) < fInvalidEPS || vecZp[k] <= 0.f)
		{
			continue;
		}
		else
		{
			kMax = k;
			break;
		}
	}
}

void CXThreadCSSInversion::_RearrangeSeismicData(vector<float>& vecPreTrace, vector<float>& vecSeismic, int nK, int iKOffset)
{
	memcpy(&vecSeismic[0], &vecPreTrace[0] + iKOffset, sizeof(float)*nK);	
}

void CXThreadCSSInversion::_Calc()
{
	this->EmitResetProgressBar();
	this->EmitSetTaskName("Calculating");
	QCoreApplication::instance()->processEvents();

	// target DV UTM
	CXSeismicUTMTool utm = m_vecOutputDV[0]->GetUTM();

	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	iInlineMin = m_pPara->GetMinInlineNum();
	iInlineMax = m_pPara->GetMaxInlineNum();
	iInlineInc = m_pPara->GetInlineInc();
	iXlineMin = m_pPara->GetMinXlineNum();
	iXlineMax = m_pPara->GetMaxXlineNum();
	iXlineInc = m_pPara->GetXlineInc();

	int nKSeismic = m_pInputDV->GetSamplingQty();
	int nKImped = m_pZp0DV->GetSamplingQty();

	double dSamplingStartDV, dSamplingEndDV, dSamplingRateDV;
	double dSamplingStartZp, dSamplingEndZp, dSamplingRateZp;
	m_pInputDV->GetSamplingRange(dSamplingStartDV, dSamplingEndDV, dSamplingRateDV);
	m_pZp0DV->GetSamplingRange(dSamplingStartZp, dSamplingEndZp, dSamplingRateZp);

	int iOffset = static_cast<int>((dSamplingStartZp - dSamplingStartDV) / dSamplingRateZp + 0.01);

	vector<float> vecZp(nKImped), vecSeismic(nKImped), vecPreTrace(nKSeismic);

	// init
	//int nThread = 1;
	int nThread = 1;// m_pPara->GetCPUNumber();
	bool bExportRCoef = m_pPara->GetExportReflectivity();
	bool bExportSeismic = m_pPara->GetExportSeismic();

	//CXSystemInfo::GetCPUNum();	
	for (int i = 0; i < nThread; ++i)
	{
		CXCSSInversion* pCalculation = new CXCSSInversion;

		pCalculation->InitInversionPara(m_pPara);

		//pCalculation->InitInversionPara(m_pPara->GetAlpha(), m_pPara->GetBeta(), m_pPara->GetMu(), m_pPara->GetSigma(), m_pPara->GetWaveletFactor(), m_pPara->GetTolerance(), m_pPara->GetMaxLoopNum());
		pCalculation->InitWaveletPara(m_nWaveletSize, m_vecWavelet);		
		pCalculation->CreateBuffers(nKImped, bExportRCoef, bExportSeismic);
		m_vecCalculation.push_back(pCalculation);
	}

	int nCurrentThread = 0;
	for (int i = iInlineMin; i <= iInlineMax; i += iInlineInc)
	{
		for (int j = iXlineMin; j <= iXlineMax; j += iXlineInc)
		{
			if (IsStopped())
				return;

			// read
			// seismic
			int iI, iJ;
			m_utmSeismicDV.LineToIJ(i, j, iI, iJ);
			m_vecDVReader[0]->ReadUVTrace(iI, iJ, &vecPreTrace[0]);

			// zp0
			m_utmZP0.LineToIJ(i, j, iI, iJ);
			m_vecDVReader[1]->ReadUVTrace(iI, iJ, &vecZp[0]);

			int kMin(0), kMax(0);
			_CalcMinMax(vecZp, nKImped, kMin, kMax);
			_RearrangeSeismicData(vecPreTrace, vecSeismic, nKImped, iOffset);


			m_vecCalculation[nCurrentThread]->SetDataBuffer(kMin, kMax, &vecZp[0], &vecSeismic[0]);


			++nCurrentThread;

			if (nCurrentThread < nThread && !(i == iInlineMax && j == iXlineMax))
				continue;

			if (IsStopped())
				return;
			else
			{
				int ii, jj;
				utm.LineToIJ(i, j, ii, jj);
				this->EmitUpdateProgress(ii*utm.GetNJ() + jj, utm.GetNI()*utm.GetNJ());
			}

			QList<CXCSSInversion*> listCalculation;
			for (int iCalc = 0; iCalc < nCurrentThread; ++iCalc)
				listCalculation.append(m_vecCalculation[iCalc]);

			// calculate			
			QtConcurrent::blockingMap<QList<CXCSSInversion*> >(listCalculation, CalculateCSSInversion);

			//write data
			if (!_WriterData(listCalculation, nKImped, bExportRCoef, bExportSeismic))
			{
				this->EmitGeneralErrorMsg("Cannot write data to the disk.");
				return;
			}

			if (IsStopped())
				return;

			nCurrentThread = 0;
		}
	}
}


bool CXThreadCSSInversion::_WriterData(QList<CXCSSInversion*>& listCalc, int nZ, bool bExportR, bool bExportSeismic)
{
	for (int iTrace = 0; iTrace < listCalc.size(); ++iTrace)
	{
		// zp
		float* pZpData = listCalc[iTrace]->GetImpedance();
		float* pZpBPData = listCalc[iTrace]->GetImpedanceBP();
		float* pZpMergedData = listCalc[iTrace]->GetImpedanceMerged();

		if (!m_vecWriter[0]->Append(nZ, pZpData) ||
			!m_vecWriter[1]->Append(nZ, pZpBPData) ||
			!m_vecWriter[2]->Append(nZ, pZpMergedData))
			return false;

		// R
		int index = 3;
		if (bExportR)
		{
			float* pR = listCalc[iTrace]->GetR();
			assert(pR);

			if (!m_vecWriter[index]->Append(nZ, pR))
				return false;

			++index;
		}
		
		// seismic
		if (bExportSeismic)
		{
			float* pSeismic = listCalc[iTrace]->GetSeismic();
			assert(pSeismic);

			if (!m_vecWriter[index]->Append(nZ, pSeismic))
				return false;
		}
	}

	return true;
}

void CXThreadCSSInversion::RunThread()
{
	mkl_set_num_threads(m_pPara->GetCPUNumber());

	if (!m_pZp0DV)
	{
		this->EmitGeneralErrorMsg("The selected impedance data volume has been deleted.");
		return;
	}

	if (!m_pInputDV)
	{
		this->EmitGeneralErrorMsg("The selected seismic data volume has been deleted.");
		return;
	}

	this->EmitSetWindowName("Constrained Sparse-Spike Inversion");
	this->EmitSetTaskName("Reading wavelet data");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	// Get wavelet data
	if (!_GetWaveletData())
		return;

	if (!_GetReaders())
		return;

	if (!_CreateDV())
		return;
	
	_Calc();
	
}



