#include "xthreadanisotropyforwarding.h"
#include "xparameteranisotropyforwarding.h"
#include "xseismicdatavolume.h"
#include "xasynregularwriter.h"
#include <QCoreApplication>
#include <cassert>
#include <algorithm>
#include "xglobal.h"
#include "xproject.h"
#include "xutility.h"
#include <qfile.h>
#include "mkl.h"
#include "xwavelet.h"
#include "xregulardatareader.h"
#include "xnummethod.h"
#include "xsysteminfo.h"
#include "xutility.h"

CXThreadAnisotropyForwarding::CXThreadAnisotropyForwarding(CXParameterAnisotropyForwarding* pPara)
{
	m_pPara = pPara;

	m_pInfoBuffer = nullptr;
	m_pOutputDV = nullptr;

	_Init();
}

CXThreadAnisotropyForwarding::~CXThreadAnisotropyForwarding()
{
	wait();

	for (int i = 0; i < m_vecInputDV.size(); ++i)
	{
		UnlockRead(m_vecInputDV[i]);
	}

	if (m_pInfoBuffer) { delete[]m_pInfoBuffer; m_pInfoBuffer = nullptr; }

	for (int i = 0; i < m_vecInputwaveletData.size(); ++i)
		delete[]m_vecInputwaveletData[i];
	m_vecInputwaveletData.clear();

	for (int i = 0; i < m_vecpW.size(); ++i)
		delete[]m_vecpW[i];
	m_vecpW.clear();

	for (int i = 0; i < m_vecInput.size(); ++i)
		delete[]m_vecInput[i];
	m_vecInput.clear();

	for (int i = 0; i < m_vecR.size(); ++i)
		delete[]m_vecR[i];
	m_vecR.clear();

	// readers
	qDeleteAll(m_vecReader);
	m_vecReader.clear();


	// DV
	if (IsStopped())
	{
		QFile::remove(m_pOutputDV->GetTraceFileName());
		delete m_pOutputDV;
		m_pOutputDV = NULL;
	}
}

void CXThreadAnisotropyForwarding::_Init()
{

	// Get input dvs	
	CXSeismicDataVolume* pVpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetVpDVID()));
	CXSeismicDataVolume* pVsDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetVsDVID()));
	CXSeismicDataVolume* pEpsDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetEpsilonDVID()));
	CXSeismicDataVolume* pDeltaDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetDeltaDVID()));
	CXSeismicDataVolume* pGammaDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetGammaDVID()));
	CXSeismicDataVolume* pRhoDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetRhoDVID()));
	CXSeismicDataVolume* pAziDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetAziSymDVID()));

	if (!pVpDV || !pVsDV || !pEpsDV || !pDeltaDV || !pGammaDV || !pRhoDV || !pAziDV)
		return;

	m_vecInputDV.push_back(pVpDV);
	m_vecInputDV.push_back(pVsDV);
	m_vecInputDV.push_back(pEpsDV);
	m_vecInputDV.push_back(pDeltaDV);
	m_vecInputDV.push_back(pGammaDV);
	m_vecInputDV.push_back(pRhoDV);
	m_vecInputDV.push_back(pAziDV);

	for (int i = 0; i < m_vecInputDV.size(); ++i)
	{
		LockRead(m_vecInputDV[i]);
	}

	// dimension info
	m_utmIn = m_vecInputDV[0]->GetUTM();
	m_nIIn = m_utmIn.GetNI();
	m_nJIn = m_utmIn.GetNJ();
	m_nKIn = m_vecInputDV[0]->GetSamplingQty();

	m_vecAzimuth = m_pPara->GetVecAzimuth();
	m_vecIncidence = m_pPara->GetVecIncidence();

	m_nAziNum = (int)m_vecAzimuth.size();
	m_nIncNum = (int)m_vecIncidence.size();
	m_nFold = m_nAziNum*m_nIncNum;
}

#pragma warning(disable : 4996)

bool CXThreadAnisotropyForwarding::_GetWaveletData()
{
	vector<QUuid> vecWaveletID = m_pPara->GetVecWaveletID();
	if (vecWaveletID.size() != m_nFold)
		return false;

	double dFactor = m_pPara->GetWaveletScalingFactor();
	
	for (int i = 0; i < vecWaveletID.size(); ++i)
	{
		if (IsStopped())
			return false;
		else
			this->EmitUpdateProgress(i, vecWaveletID.size());

		// wavelet
		CXWavelet* pWavelet = dynamic_cast<CXWavelet*>(::GetObjectByID(vecWaveletID[i]));
		if (!pWavelet)
			return false;

		unsigned int ndataLength;
		double *pData = pWavelet->CXObject::GetData(ndataLength);
		if (!pData)
			return false;

		if (i == 0)
			m_nWaveletSize = ndataLength;
		else
		{
			if (m_nWaveletSize != ndataLength)
				return false;
		}


		double* pWaveletData = new double[ndataLength];
		if (!pWaveletData)
			return false;

		//memcpy(pWaveletData, pData, sizeof(double)*ndataLength);
		std::transform(pData, pData + ndataLength, pWaveletData, [dFactor](float d) {return d*dFactor; });
		m_vecInputwaveletData.push_back(pWaveletData);

		// find the largest element
		m_vecWaveletPeakIndex.push_back(std::distance(pWaveletData, std::max_element(pWaveletData, pWaveletData+ ndataLength)));
	}

	return true;

}

bool CXThreadAnisotropyForwarding::_CreateBuffers()
{
	// W
	m_vecpW.resize(m_nFold, nullptr);
	for (int i = 0; i < m_nFold; ++i)
	{
		double* pW = nullptr;
		try
		{
			pW = new double[m_nKIn*m_nKIn];
		}
		catch (std::bad_alloc)
		{
			this->EmitMemoryNotEnough();
			return false;
		}
		m_vecpW[i] = pW;
	}

	// in buffs	
	for (int i = 0; i < m_vecInputDV.size(); ++i)
	{
		m_vecInput.push_back(new float[m_nKIn]);
	}

	// out buffs	
	for (int i = 0; i < m_nFold; ++i)
	{
		m_vecR.push_back(new double[m_nKOut]);
	}

	m_vecOutput.resize(m_nKOut*m_nFold);

	//interpolation
	m_vecX.resize(m_nKIn); 
	m_vecY.resize(m_nKIn);
	m_vecX2.resize(m_nKIn);
	m_vecY2.resize(m_nKIn);

	return true;

}

void CXThreadAnisotropyForwarding::_CalcW(int nK)
{
	for (int iWavelet = 0; iWavelet < m_nFold; ++iWavelet)
	{
		double *pW = m_vecpW[iWavelet];
		memset(pW, 0, sizeof(double)*nK*nK);
		int iPeakPosition = m_vecWaveletPeakIndex[iWavelet];

		// wavelet matrix, column-major
		for (int j = 0, iStart = iPeakPosition; j < nK; ++j, --iStart)
		{
			for (int i = qMax(0, iStart); i < m_nWaveletSize && i - iStart < nK; ++i)
			{
				pW[j*nK + i - iStart] = m_vecInputwaveletData[iWavelet][i];
			}
		}
	}
}

bool CXThreadAnisotropyForwarding::_GetReaders()
{
	for (int i = 0; i < m_vecInputDV.size(); ++i)
	{
		CXRegularDataReader<float>* pReader = new CXRegularDataReader<float>(m_vecInputDV[i]->GetTraceFileName(), m_vecInputDV[i]->GetInlineQty(),
			m_vecInputDV[i]->GetXlineQty(), m_vecInputDV[i]->GetSamplingQty());

		m_vecReader.push_back(pReader);

		if (!pReader->Open())
		{
			this->EmitGeneralErrorMsg("Cannot open the seismic data file.");
			return false;
		}
	}

	return true;
}


bool CXThreadAnisotropyForwarding::_CreateDV()
{
	if (m_vecInputDV.empty())
	{
		this->EmitGeneralErrorMsg("At least one of selected seismic data has been removed.");
		return false;
	}

	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	iInlineMin = m_pPara->GetMinInlineNum();
	iInlineMax = m_pPara->GetMaxInlineNum();
	iInlineInc = m_pPara->GetInlineInc();
	iXlineMin = m_pPara->GetMinXlineNum();
	iXlineMax = m_pPara->GetMaxXlineNum();
	iXlineInc = m_pPara->GetXlineInc();

	int nInlineNum = (iInlineMax - iInlineMin) / iInlineInc + 1;
	int nXlineNum = (iXlineMax - iXlineMin) / iXlineInc + 1;

	m_utmOut = m_utmIn;
	m_utmOut.Resize(iInlineMin, iXlineMin, nInlineNum, nXlineNum);

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	dSamplingStart = m_pPara->GetSamplingStart();
	dSamplingEnd = m_pPara->GetSamplingEnd();
	dSamplingRate = m_pPara->GetSamplingRate();

	m_pOutputDV = new CXSeismicDataVolume(m_utmOut, dSamplingStart, dSamplingEnd, dSamplingRate,
		"seismic", m_nFold, 0, 0, true);

	m_nIOut = m_utmOut.GetNI();
	m_nJOut = m_utmOut.GetNJ();
	m_nKOut = m_pOutputDV->GetSamplingQty();

	qint64 nSize = m_nIOut*m_nJOut;
	m_pInfoBuffer = new char[nSize*(10 + 4 * m_nFold)];

	if (IsStopped())
		return false;
	else
		return true;
}

void CXThreadAnisotropyForwarding::_FindValidRange(int nReaderNum)
{
	float fInvalid = g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	bool bConintue;

	m_kMin = 0;
	m_kMax = 0;

	// min
	for (int k = 0; k < m_nKIn; ++k)
	{
		bConintue = false;;
		for (int iReader = 0; iReader < nReaderNum; ++iReader)
		{
			if (qAbs(m_vecInput[iReader][k] - fInvalid) < fInvalidEPS)
			{
				bConintue = true;
				break;
			}
		}
		if (bConintue)
			continue;
		else
		{
			m_kMin = k;
			break;
		}
	}

	//max
	for (int k = m_nKIn - 1; k >= 0; --k)
	{
		bConintue = false;;
		for (int iReader = 0; iReader < nReaderNum; ++iReader)
		{
			if (qAbs(m_vecInput[iReader][k] - fInvalid) < fInvalidEPS)
			{
				bConintue = true;
				break;
			}
		}
		if (bConintue)
			continue;
		else
		{
			m_kMax = k;
			break;
		}
	}	
}

void CXThreadAnisotropyForwarding::_Interpolation(int nReaderNum)
{
	if (m_nK < 2)
		return;

	float fInvalid = (float) g_dInvalidData;
	float fEPSInv = ::GetEPSofInvalidData(fInvalid);

	for (int iReader = 0; iReader < nReaderNum; ++iReader)
	{
		int nKIn = 0;
		for (int k = m_kMin; k <= m_kMax; ++k)
		{
			m_vecX2[k - m_kMin] = k - m_kMin;

			if (qAbs(m_vecInput[iReader][k] - fInvalid) > fEPSInv)
			{
				m_vecX[nKIn] = k - m_kMin;
				m_vecY[nKIn] = m_vecInput[iReader][k];
				++nKIn;
			}
		}

		NXUtility::ReSample(nKIn, &m_vecX[0], &m_vecY[0], m_nK, &m_vecX2[0], &m_vecY2[0], g_dInvalidData, false);

		for (int k = m_kMin; k <= m_kMax; ++k)
		{
			m_vecInput[iReader][k] = m_vecY2[k - m_kMin];
		}
	}
}

void CXThreadAnisotropyForwarding::_Calculate()
{
	this->EmitResetProgressBar();
	this->EmitSetTaskName("Calculating");
	QCoreApplication::instance()->processEvents();

	float fInvalid = (float)g_dInvalidData;

	// writer
	CXAsynRegularWriter writer(QStringList() << m_pOutputDV->GetTraceFileName(), m_nIOut, m_nJOut, m_nKOut*m_nFold, m_nKOut*m_nFold);
	if (!writer.Init())
	{
		this->EmitGeneralErrorMsg("Cannot open the file to write.");
		return;
	}

	// range limit
	double dSamplingStartIn, dSamplingEndIn, dSamplingRateIn;
	m_vecInputDV[0]->GetSamplingRange(dSamplingStartIn, dSamplingEndIn, dSamplingRateIn);

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pOutputDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	int kkmin = static_cast<int>((dSamplingStart - dSamplingStartIn) / dSamplingRate + 0.01);
	int kkmax = static_cast<int>((dSamplingEnd - dSamplingStartIn) / dSamplingRate + 0.01);

	// coef
	double coef[12];
	int nReaderNum = (int)m_vecReader.size();
	vector<double> vecSeismic(m_nKOut);
	m_nK = -1;
	float* pOutputData = &m_vecOutput[0];
	std::vector<float*> vecData;
	vecData.push_back(pOutputData);

	bool bBreak = false;
	int iInline, iXline, ii, jj;
	for (int i = 0; i < m_nIOut; ++i)
	{
		if (bBreak)
			break;

		for (int j = 0; j < m_nJOut; ++j)
		{
			if (IsStopped())
			{
				bBreak = true;
				break;
			}
			else
			{
				this->EmitUpdateProgress(i*m_nJOut +j, m_nIOut*m_nJOut);
			}

			// read data
			m_utmOut.IJToLine(i, j, iInline, iXline);
			m_utmIn.LineToIJ(iInline, iXline, ii, jj);
			for (int iReader = 0; iReader < nReaderNum; ++iReader)
			{
				
				if (!m_vecReader[iReader]->ReadUVTrace(ii, jj, m_vecInput[iReader]))
				{
					this->EmitGeneralErrorMsg("Cannot read the seismic data from the disk.");
					return;
				}
			}

			// find valid range
			_FindValidRange(nReaderNum);
			m_kMin = qMax(m_kMin, kkmin);
			m_kMax = qMin(m_kMax, kkmax);

			if (m_nK != m_kMax - m_kMin + 1)
			{
				m_nK = m_kMax - m_kMin + 1;
				if (m_nK >= m_nWaveletSize)
					_CalcW(m_nK);
			}

			// interpolation
			//_Interpolation(nReaderNum);

			// calculate R			
			for (int k = m_kMin; k < m_kMax; ++k)
			{
				for (int iReader = 0; iReader < 6; ++iReader)
				{
					coef[iReader] = m_vecInput[iReader][k];
					coef[iReader+6] = m_vecInput[iReader][k+1];
				}

				for (int iAzi = 0; iAzi < m_nAziNum; ++iAzi)
				{
					for (int iInc = 0; iInc < m_nIncNum; ++iInc)
					{
						m_vecR[iAzi*m_nIncNum + iInc][k- m_kMin] = NXNumMethod::PP_coefficient2(coef, m_vecIncidence[iInc], m_vecAzimuth[iAzi] - m_vecInput[6][k]);
					}
				}			
			}
			// Last one
			for (int iFold = 0; iFold < m_nFold; ++iFold)
				m_vecR[iFold][m_kMax - m_kMin] = 0.;			

			// calc seismic
			if (m_nK < m_nWaveletSize)
			{
				for (int iFold = 0; iFold < m_nFold; ++iFold)
				{
					for (int k = 0; k < m_nKOut; ++k)
						pOutputData[iFold*m_nKOut+k] = fInvalid;
				}
			}
			else
			{
				for (int iFold = 0; iFold < m_nFold; ++iFold)
				{
					memset(&vecSeismic[0], 0, sizeof(double)*m_nK);
					cblas_dgemv(CblasColMajor, CblasNoTrans, m_nK, m_nK, 1., m_vecpW[iFold], m_nK, m_vecR[iFold], 1, 0, &vecSeismic[0], 1);

					for (int k = kkmin; k <= kkmax; ++k)
					{
						if (k<m_kMin || k>m_kMax)
						{
							pOutputData[iFold*m_nKOut + k-kkmin] = fInvalid;
						}
						else
						{
							pOutputData[iFold*m_nKOut + k-kkmin] = vecSeismic[k - m_kMin];
						}
					}				
				}
			}

			// write data
			writer.WaitWriteData();
			writer.WriteData(vecData, m_nKOut*m_nFold);			
		}
	}

	writer.WaitWriteData();
	writer.StopThread(); 

	if (!bBreak)
		_WriteInfoFile();

}

bool CXThreadAnisotropyForwarding::_WriteInfoFile()
{
	// set info buff
	int nSize = m_nIOut*m_nJOut;
	qint64 nBockSize = m_nKOut*m_nFold;
	qint64 offset;
	for (qint64 i = 0; i < nSize; ++i)
	{		
		char* pBuff = m_pInfoBuffer + i*(10 + 4 * m_nFold);

		// offset
		qint64* pOffset = (qint64*)pBuff;
		*pOffset = i*nBockSize * sizeof(float);

		// fold
		short* pFold = (short*)(pBuff + 8);
		*pFold = m_nFold;

		for (int iAzi = 0; iAzi < m_nAziNum; ++iAzi)
		{
			for (int iInc = 0; iInc < m_nIncNum; ++iInc)
			{
				short* pInc = (short*)(pBuff + 10 + 4 * (iAzi*m_nIncNum+iInc));
				short* pAzi = pInc + 1;

				*pInc = (short)m_vecIncidence[iInc];
				*pAzi = (short)m_vecAzimuth[iAzi];				
			}
		}
	}

	// write to file
	QString strInfoFileName = m_pOutputDV->GetTraceFileName();
	strInfoFileName.chop(4);
	strInfoFileName += ".inf";

	QFile qFile(strInfoFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return false;

	qFile.write(m_pInfoBuffer, nSize*(10 + 4 * m_nFold));
	qFile.close();
	return true;
}

void CXThreadAnisotropyForwarding::RunThread()
{
	mkl_set_num_threads(CXSystemInfo::GetCPUNum());

	if (m_vecInputDV.empty())
	{
		this->EmitGeneralErrorMsg("At least one of selected data volumes has been removed.");
		return;
	}

	this->EmitSetWindowName("Seismic Anisotropy Forwarding");
	this->EmitSetTaskName("Reading wavelet data");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	// Get wavelet data
	if (!_GetWaveletData())
	{
		this->EmitGeneralErrorMsg("There is no valid wavelet data.");
		return;
	}

	if (!_GetReaders())
		return;


	if (!_CreateDV())
		return;

	if (!_CreateBuffers())
		return;

	_Calculate();
}



