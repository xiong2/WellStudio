#pragma warning( push ,0 )
#include "xthreadfractureinversion.h"
#include "xparameter3terminversion.h"
#include "xseismicdatavolume.h"
#include "xasynregularwriter.h"
#include "xprestackasynreader.h"
#include <QCoreApplication>
#include <cassert>
#include <algorithm>
#include "xglobal.h"
#include "xproject.h"
#include "xutility.h"
#include <qtconcurrentmap.h>
#include <qfile.h>
#include "mkl.h"
#include "xavossinversion.h"
#include "x3dhorizon.h"
#include "xwavelet.h"
#include "xregulardatareader.h"
#include "xfunctiontemplate.h"

#pragma warning( pop )


CXThreadFractureInversion::CXThreadFractureInversion(CXParameter3TermInversion* pPara)
{
	m_pPara = pPara;
	m_pAziDV = nullptr;

	m_pTopHor = nullptr;
	m_pBotHor = nullptr;

	m_pOutputDV = nullptr;
	m_pInfoBuffer = nullptr;

	_Init();
}

CXThreadFractureInversion::~CXThreadFractureInversion()
{
	wait();

	if (m_pAziDV)		UnlockRead(m_pAziDV);
	if (m_pZpDV)		UnlockRead(m_pZpDV);
	if (m_pZsDV)		UnlockRead(m_pZsDV);
	if (m_pRhoDV)		UnlockRead(m_pRhoDV);
	if (m_pEpsilonDV)	UnlockRead(m_pEpsilonDV);
	if (m_pDeltaDV)		UnlockRead(m_pDeltaDV);
	if (m_pGammaDV)		UnlockRead(m_pGammaDV);
	if (m_pSymAziDV)	UnlockRead(m_pSymAziDV);

	if (m_pTopHor)		UnlockRead(m_pTopHor);
	if (m_pBotHor)		UnlockRead(m_pBotHor);

	if (m_pInfoBuffer) { delete[]m_pInfoBuffer; m_pInfoBuffer = nullptr; }

	// readers
	for (int i = 0; i < m_vecDVInfo.size(); ++i)
	{
		if (m_vecDVInfo[i].reader)	
			delete m_vecDVInfo[i].reader;
	}
	m_vecDVInfo.clear();

	// calculation
	qDeleteAll(m_vecCalculation);
	m_vecCalculation.clear();


	// DV
	if (IsStopped())
	{
		delete m_pOutputDV;
	}
}

void CXThreadFractureInversion::_Init()
{
	m_pAziDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetPrestackDVID()));

	m_pZpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZpID()));
	m_pZsDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZsID()));
	m_pRhoDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetRhoID()));
	m_pEpsilonDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetEpsilonID()));
	m_pDeltaDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetDeltaID()));
	m_pGammaDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetGammaID()));
	m_pSymAziDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetSymAziID()));

	if (m_pAziDV)		LockRead(m_pAziDV);
	if (m_pZpDV)		LockRead(m_pZpDV);
	if (m_pZsDV)		LockRead(m_pZsDV);
	if (m_pRhoDV)		LockRead(m_pRhoDV);
	if (m_pEpsilonDV)	LockRead(m_pEpsilonDV);
	if (m_pDeltaDV)		LockRead(m_pDeltaDV);
	if (m_pGammaDV)		LockRead(m_pGammaDV);
	if (m_pSymAziDV)	LockRead(m_pSymAziDV);


	// horizon
	m_bHorizon = m_pPara->GetUseHorizon();
	if (m_bHorizon)
	{
		m_pTopHor = dynamic_cast<CX3DHorizon*>(::GetObjectByID(m_pPara->GetTopHorizonID()));
		m_pBotHor = dynamic_cast<CX3DHorizon*>(::GetObjectByID(m_pPara->GetBotHorizonID()));

		if (m_pTopHor)		LockRead(m_pTopHor);
		if (m_pBotHor)		LockRead(m_pBotHor);
	}
}

bool CXThreadFractureInversion::_GetWaveletDataAndAziInfo()
{
	vector<float> vecAzi = m_pPara->GetVecAzimuth();
	vector<float> vecInc = m_pPara->GetVecAngleValue();
	vector<QUuid> vecWaveletID = m_pPara->GetVecWaveletID();
	if (vecAzi.empty() || vecAzi.size() != vecInc.size() || vecAzi.size() != vecWaveletID.size())
		return false;

	vector<float> vecData;
	m_nMaxAngleNum = 0;
	for (int i = 0; i < vecWaveletID.size(); ++i)
	{
		if (IsStopped())
			return false;
		else
			this->EmitUpdateProgress(i, vecWaveletID.size());

		// azimuth and offset
		if (i == 0 || vecAzi[i] != m_vecAziInfo.back().azimuth)
		{	
			sAziInfo s;
			s.azimuth = vecAzi[i];
			s.vecOffset.push_back(vecInc[i]);
			m_vecAziInfo.push_back(s);
		}
		else
		{
			m_vecAziInfo.back().vecOffset.push_back(vecInc[i]);
			m_nMaxAngleNum = qMax(m_nMaxAngleNum, (int)m_vecAziInfo.back().vecOffset.size());
		}

		// wavelet
		CXWavelet* pWavelet = dynamic_cast<CXWavelet*>(::GetObjectByID(vecWaveletID[i]));
		if (!pWavelet)
			return false;

		if (i == 0 || vecWaveletID[i] != vecWaveletID[i - 1])
		{
			unsigned int ndataLength;
			double *pData = pWavelet->CXObject::GetData(ndataLength);
			if (!pData)
				return false;

			vecData.resize(ndataLength);	
			std::transform(pData, pData + ndataLength, vecData.begin(), [](double d) {return static_cast<float>(d); });
		}
		m_vecAziInfo.back().vec2DWavelet.push_back(vecData);
		
	}

	return true;

}

void CXThreadFractureInversion::_GetHorizonData()
{
	if (!m_bHorizon)
	{
		m_dSamplingStart = m_pPara->GetSamplingStart();
		m_dSamplingEnd = m_pPara->GetSamplingEnd();
		m_dSamplingRate = m_pPara->GetSamplingRate();
	}
	else
	{
		double zmin = qMin(m_pTopHor->GetZMin(), m_pBotHor->GetZMin());
		double zmax = qMax(m_pTopHor->GetZMax(), m_pBotHor->GetZMax());

		double dSamplingStart, dSamplingEnd, dSamplingRate;
		m_pAziDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

		m_dSamplingRate = dSamplingRate;
		m_dSamplingStart = qMax(zmin, dSamplingStart);
		m_dSamplingStart = floor((m_dSamplingStart - dSamplingStart) / m_dSamplingRate)*m_dSamplingRate + dSamplingStart;
		m_dSamplingEnd = qMin(zmax, dSamplingEnd);
		m_dSamplingEnd = ceil((m_dSamplingEnd - dSamplingStart) / m_dSamplingRate)*m_dSamplingRate + dSamplingStart;

		m_utmTop = m_pTopHor->GetUTM();
		m_utmBot = m_pBotHor->GetUTM();

		m_vecTopHorData.resize(m_utmTop.GetNI()*m_utmTop.GetNJ());
		m_vecBotHorData.resize(m_utmBot.GetNI()*m_utmBot.GetNJ());

		memcpy(&m_vecTopHorData[0], m_pTopHor->GetData(), sizeof(float)*m_utmTop.GetNI()*m_utmTop.GetNJ());
		memcpy(&m_vecBotHorData[0], m_pBotHor->GetData(), sizeof(float)*m_utmBot.GetNI()*m_utmBot.GetNJ());
	}
}

bool CXThreadFractureInversion::_GetReaders()
{
	sDVInfo s;

	// prestack
	s.reader = nullptr;
	s.utm = m_pAziDV->GetUTM();
	m_pAziDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
	m_vecDVInfo.push_back(s);
	

	// zp
	s.reader = new CXRegularDataReader<float>(m_pZpDV->GetTraceFileName(), m_pZpDV->GetInlineQty(),
		m_pZpDV->GetXlineQty(), m_pZpDV->GetSamplingQty());

	s.utm = m_pZpDV->GetUTM();
	m_pZpDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
	m_vecDVInfo.push_back(s);
	if (!s.reader->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the P-impedance data file.");
		return false;
	}

	// zs
	s.reader = new CXRegularDataReader<float>(m_pZsDV->GetTraceFileName(), m_pZsDV->GetInlineQty(),
		m_pZsDV->GetXlineQty(), m_pZsDV->GetSamplingQty());

	s.utm = m_pZsDV->GetUTM();
	m_pZsDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
	m_vecDVInfo.push_back(s);
	if (!s.reader->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the S-impedance data file.");
		return false;
	}

	// Rho
	s.reader = new CXRegularDataReader<float>(m_pRhoDV->GetTraceFileName(), m_pRhoDV->GetInlineQty(),
		m_pRhoDV->GetXlineQty(), m_pRhoDV->GetSamplingQty());

	s.utm = m_pRhoDV->GetUTM();
	m_pRhoDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
	m_vecDVInfo.push_back(s);
	if (!s.reader->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the density data file.");
		return false;
	}

	// epsilon
	s.reader = new CXRegularDataReader<float>(m_pEpsilonDV->GetTraceFileName(), m_pEpsilonDV->GetInlineQty(),
		m_pEpsilonDV->GetXlineQty(), m_pEpsilonDV->GetSamplingQty());

	s.utm = m_pEpsilonDV->GetUTM();
	m_pEpsilonDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
	m_vecDVInfo.push_back(s);
	if (!s.reader->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the epsilon data file.");
		return false;
	}

	// delta
	s.reader = new CXRegularDataReader<float>(m_pDeltaDV->GetTraceFileName(), m_pDeltaDV->GetInlineQty(),
		m_pDeltaDV->GetXlineQty(), m_pDeltaDV->GetSamplingQty());

	s.utm = m_pDeltaDV->GetUTM();
	m_pDeltaDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
	m_vecDVInfo.push_back(s);
	if (!s.reader->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the delta data file.");
		return false;
	}

	// gamma
	s.reader = new CXRegularDataReader<float>(m_pGammaDV->GetTraceFileName(), m_pGammaDV->GetInlineQty(),
		m_pGammaDV->GetXlineQty(), m_pGammaDV->GetSamplingQty());

	s.utm = m_pGammaDV->GetUTM();
	m_pGammaDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
	m_vecDVInfo.push_back(s);
	if (!s.reader->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the gamma data file.");
		return false;
	}

	// symmetry azimuth
	s.reader = new CXRegularDataReader<float>(m_pSymAziDV->GetTraceFileName(), m_pSymAziDV->GetInlineQty(),
		m_pSymAziDV->GetXlineQty(), m_pSymAziDV->GetSamplingQty());

	s.utm = m_pSymAziDV->GetUTM();
	m_pSymAziDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
	m_vecDVInfo.push_back(s);
	if (!s.reader->Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the gamma data file.");
		return false;
	}

	// tell range
	if (m_vecDVInfo[0].samplingStart > m_vecDVInfo[1].samplingStart ||
		m_vecDVInfo[0].samplingEnd < m_vecDVInfo[1].samplingEnd)
	{
		this->EmitGeneralErrorMsg("The range of the seismic data is too small.");
		return false;
	}


	return true;
}


bool CXThreadFractureInversion::_CreateDV()
{
	if (!m_pAziDV)
	{
		this->EmitGeneralErrorMsg("There is no valid seismic data volume.");
		return false;
	}

	CXSeismicUTMTool utm = m_pAziDV->GetUTM();;


	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	double dSamplingStart, dSamplingEnd, dSamplingRate;

	iInlineMin = m_pPara->GetMinInlineNum();
	iInlineMax = m_pPara->GetMaxInlineNum();
	iInlineInc = m_pPara->GetInlineInc();
	iXlineMin = m_pPara->GetMinXlineNum();
	iXlineMax = m_pPara->GetMaxXlineNum();
	iXlineInc = m_pPara->GetXlineInc();

	dSamplingStart = m_pPara->GetSamplingStart();
	dSamplingEnd = m_pPara->GetSamplingEnd();
	dSamplingRate = m_pPara->GetSamplingRate();

	int nInlineNum = (iInlineMax - iInlineMin) / iInlineInc + 1;
	int nXlineNum = (iXlineMax - iXlineMin) / iXlineInc + 1;
	utm.Resize(iInlineMin, iXlineMin, nInlineNum, nXlineNum);	

	m_nMaxFold = m_pPara->GetVecAzimuth().size();
	m_pOutputDV = new CXSeismicDataVolume(utm, m_dSamplingStart, m_dSamplingEnd, m_dSamplingRate, 
											"VpVs", (int) m_vecAziInfo.size(), 0, 0, true);

	qint64 nSize = utm.GetNI()*utm.GetNJ();
	m_pInfoBuffer = new char[nSize*(10 + 4 * m_vecAziInfo.size())];
	
	if (IsStopped())
		return false;
	else
		return true;
}


void CXThreadFractureInversion::_GetNextIJLineNum(CXSeismicUTMTool& utm, int iInline, int iXline, int& iInlineNext, int& iXlineNext)
{
	int nI = utm.GetNI();
	int nJ = utm.GetNJ();
	int i, j, iNext, jNext;

	utm.LineToIJ(iInline, iXline, i, j);

	iNext = i;
	jNext = j + 1;
	if (jNext == nJ)
	{
		jNext = 0;
		++iNext;
	}
	if (iNext == nI)
	{
		iNext = -1;
		jNext = -1;
	}
	if (iNext == -1)
	{
		iInlineNext = -1;
		iXlineNext = -1;
	}
	else
	{
		utm.IJToLine(iNext, jNext, iInlineNext, iXlineNext);
	}
}

void CXThreadFractureInversion::_CalcMinMax(int nK, int& kMin, int& kMax)
{
	float fInvalid = g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

	for (int k = 0; k < nK; ++k)
	{
		bool bContinue = false;
		for (int iDV = 1; iDV < m_vecDVInfo.size(); ++iDV)
		{
			if (qAbs(m_vecDVInfo[iDV].vecTraceData[k] - fInvalid) < fInvalidEPS ||
				(iDV < 4 && m_vecDVInfo[iDV].vecTraceData[k] <= 0.f))
			{
				bContinue = true;
				break;
			}
		}

		if (bContinue)
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
		bool bContinue = false;
		for (int iDV = 1; iDV < m_vecDVInfo.size(); ++iDV)
		{
			if (qAbs(m_vecDVInfo[iDV].vecTraceData[k] - fInvalid) < fInvalidEPS || 
				(iDV < 4 && m_vecDVInfo[iDV].vecTraceData[k] <= 0.f))
			{
				bContinue = true;
				break;
			}
		}

		if (bContinue)
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

void CXThreadFractureInversion::_CalcHorizonKRange(int iInline, int iXline, double dImpedSamplingStart, int nKImped, int& kminnew, int& kmaxnew)
{
	if (!m_bHorizon)
	{
		kminnew = static_cast<int>((m_dSamplingStart - dImpedSamplingStart) / m_dSamplingRate + 0.01);
		kmaxnew = static_cast<int>((m_dSamplingEnd - dImpedSamplingStart) / m_dSamplingRate + 0.01);
	}
	else
	{
		float fInvalid = (float)::g_dInvalidData;

		// top
		int i, j;
		if (!m_utmTop.LineToIJ(iInline, iXline, i, j))
			kminnew = 0;
		else
		{
			float fTop = m_vecTopHorData[i*m_utmTop.GetNJ() + j];
			if (fTop == fInvalid)
				kminnew = 0;
			else
				kminnew = static_cast<int>((fTop - dImpedSamplingStart) / m_dSamplingRate + 0.01);
		}

		// bot
		if (!m_utmBot.LineToIJ(iInline, iXline, i, j))
			kmaxnew = nKImped - 1;
		else
		{
			float fBot = m_vecBotHorData[i*m_utmBot.GetNJ() + j];
			if (fBot == fInvalid)
				kmaxnew = nKImped - 1;
			else
				kmaxnew = static_cast<int>((fBot - dImpedSamplingStart) / m_dSamplingRate + 0.01);
		}

	}
}

void CXThreadFractureInversion::_ParseSeismicData(int iAzi, float* pGather, float* pOffAzi, int nFold, int nK, vector<float>& vecSeismic)
{
	int nAngleNum = m_vecAziInfo[iAzi].vecOffset.size();
	float fAzi, fAngle;
	int iIndex = 0;
	for (int i = 0; i < nAngleNum; ++i)
	{
		fAzi = m_vecAziInfo[iAzi].azimuth;
		fAngle = m_vecAziInfo[iAzi].vecOffset[i];

		for (int ii = 0; ii < nFold; ++ii)
		{
			if (fAzi == pOffAzi[2 * ii + 1] && fAngle == pOffAzi[2 * ii])
			{
				iIndex = ii;
				break;
			}
		}
		memcpy(&vecSeismic[0] + i*nK, pGather + iIndex*nK, sizeof(float)*nK);
	}
}

void CXThreadFractureInversion::_Calculate()
{
	this->EmitResetProgressBar();
	this->EmitSetTaskName("Calculating");
	QCoreApplication::instance()->processEvents();

	// target DV UTM
	CXSeismicUTMTool utm = m_pOutputDV->GetUTM();

	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	utm.GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);

	int nKSeismic = m_pAziDV->GetSamplingQty();
	int nKImped = m_pZpDV->GetSamplingQty();
	int nK = static_cast<int>((m_dSamplingEnd - m_dSamplingStart) / m_dSamplingRate + 0.01) + 1;

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pAziDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	double dPImedSamplingStart = m_vecDVInfo[1].samplingStart;
	int iOffset = static_cast<int>((dPImedSamplingStart - dSamplingStart) / m_dSamplingRate + 0.01);
	m_iWriterOffset = static_cast<int>((m_dSamplingStart - dPImedSamplingStart) / m_dSamplingRate + 0.01);

	vector<float> vecZp(nKImped), vecZs(nKImped), vecRho(nKImped), vecEpsilon(nKImped), vecDelta(nKImped), vecGamma(nKImped), vecSymAzi(nKImped);
	vector<float> vecSeismic(nKImped*m_nMaxAngleNum);

	// max folder for azimuth gather
	int nMaxAziGatherFold = m_pAziDV->GetMaxFold();
	vector<float> vecGather(nKSeismic*nKImped), vecOffAzi(2 * nMaxAziGatherFold);

	// reader
	CXPrestackAsynReader reader(m_pAziDV, 0, 0);
	if (!reader.Init(dPImedSamplingStart, nKImped))
	{
		this->EmitMemoryNotEnough();
		return;
	}

	// writer
	CXAsynRegularWriter writer(QStringList() << m_pOutputDV->GetTraceFileName(), m_pOutputDV->GetInlineQty(), m_pOutputDV->GetXlineQty(),
								  m_pOutputDV->GetSamplingQty()*m_vecAziInfo.size(), m_pOutputDV->GetSamplingQty()*m_vecAziInfo.size());
	if (!writer.Init())
	{
		this->EmitGeneralErrorMsg("Cannot open the file to write.");
		return;
	}

	// init
	int nThread = 1; // m_pPara->GetCPUNumber();
	bool bExportRCoef = m_pPara->GetExportReflectivity();
	bool bExportSeismic = m_pPara->GetExportSeismic();
	int iOutputType = m_pPara->GetOutputType();

	// lfm data trace buffer
	for (int i = 1; i < m_vecDVInfo.size(); ++i)
	{
		m_vecDVInfo[i].vecTraceData.resize(nKImped);
	}

	// method	
	for (int i = 0; i < m_vecAziInfo.size(); ++i)
	{
		CXAVOSSInversion* pCalculation = new CXAVOSSInversion;
		pCalculation->InitInversionPara(m_pPara);
		pCalculation->InitWaveletPara(m_vecAziInfo[i].vecOffset, m_vecAziInfo[i].vec2DWavelet[0].size(), m_vecAziInfo[i].vec2DWavelet);
		pCalculation->CreateBuffers(nKImped, bExportRCoef, bExportSeismic);
		m_vecCalculation.push_back(pCalculation);

		m_vecAziInfo[i].vecZp.resize(nKImped);
		m_vecAziInfo[i].vecZs.resize(nKImped);
		m_vecAziInfo[i].vecRho.resize(nKImped);
	}

	// buffers
	m_vecEpsilonR.resize(nKImped);
	m_vecDeltaR.resize(nKImped);
	m_vecGammaR.resize(nKImped);

	int iInlineNext, iXlineNext;
	int iCount = 0;
	bool bBreak = false;
	for (int i = iInlineMin; i <= iInlineMax; i += iInlineInc)
	{
		if (bBreak)
			break;

		for (int j = iXlineMin; j <= iXlineMax; j += iXlineInc)
		{
			if (IsStopped())
			{
				bBreak = true;
				break;;
			}
			else
			{
				this->EmitUpdateProgress(iCount, utm.GetNI()*utm.GetNJ());
			}

			_GetNextIJLineNum(utm, i, j, iInlineNext, iXlineNext);

			// reading prestack
			int nFold;
			reader.ReadData(i, j, &vecGather[0], &vecOffAzi[0], &nFold, iInlineNext, iXlineNext);
			reader.WaitReadData();

			// read
			// poststack
			//read data
			int iI, iJ;
			for (int iDV = 1; iDV < m_vecDVInfo.size(); ++iDV)
			{
				m_vecDVInfo[iDV].utm.LineToIJ(i, j, iI, iJ);
				if (!m_vecDVInfo[iDV].reader->ReadUVTrace(iI, iJ, &m_vecDVInfo[iDV].vecTraceData[0]))
				{
					bBreak = true;
					this->EmitGeneralErrorMsg("Cannot read data from the disk.");
					break;;
				}
			}


			int kMin(0), kMax(0);
			_CalcMinMax(nKImped, kMin, kMax);

			// Calculate Zp, Zs, Rho s.t azimuth			
			_CalcZpZsRhoWithAzi(kMin, kMax, nKImped);

			// Z constraints
			int kMinNew, kMaxNew;
			_CalcHorizonKRange(i, j, dPImedSamplingStart, nKImped, kMinNew, kMaxNew);

			for (int iAzi = 0; iAzi < m_vecAziInfo.size(); ++iAzi)
			{
				_ParseSeismicData(iAzi, &vecGather[0], &vecOffAzi[0], nFold, nKImped, vecSeismic);
				m_vecCalculation[iAzi]->SetDataBuffer(qMax(kMin, kMinNew), qMin(kMax, kMaxNew), &m_vecAziInfo[iAzi].vecZp[0], 
														&m_vecAziInfo[iAzi].vecZs[0], &m_vecAziInfo[iAzi].vecRho[0], &vecSeismic[0]);
				m_vecCalculation[iAzi]->Calculate();
			}	

			//write data			
			_WriterData(&writer, nK);

			// set buffer
			_Write2Buffer(iCount, i, j);
			++iCount;
		}
	}

	reader.StopThread();

	writer.WaitWriteData();
	writer.StopThread();

	if (!bBreak)
		_WriteInfoFile();
}

void CXThreadFractureInversion::_CalcZpZsRhoWithAzi(int kmin, int kmax, int nK)
{
	int nAzi = (int)m_vecAziInfo.size();
	// vp, vs
	//for (int k = kmin; k <= kmax; ++k)
	//{
	//	m_vecDVInfo[1].vecTraceData[k] /= (m_vecDVInfo[3].vecTraceData[k]*1000);
	//	m_vecDVInfo[2].vecTraceData[k] /= (m_vecDVInfo[3].vecTraceData[k]*1000);
	//}
	//
	// 
	double dmean;
	for (int k = kmin; k < kmax; ++k)
	{
		dmean = 0.5*(m_vecDVInfo[4].vecTraceData[k] + m_vecDVInfo[4].vecTraceData[k + 1]);
		m_vecEpsilonR[k] = (m_vecDVInfo[4].vecTraceData[k] + 1. - dmean) / (1. - dmean);

		dmean = 0.5*(m_vecDVInfo[5].vecTraceData[k] + m_vecDVInfo[5].vecTraceData[k + 1]);
		m_vecDeltaR[k] = (m_vecDVInfo[5].vecTraceData[k] + 1. - dmean)/(1. - dmean);

		dmean = 0.5*(m_vecDVInfo[6].vecTraceData[k] + m_vecDVInfo[6].vecTraceData[k + 1]);
		m_vecGammaR[k] = (m_vecDVInfo[6].vecTraceData[k] + 1. - dmean)/(1. - dmean);
	}

	//
	double dcos, dcos2, dcos4, dvsbar, dvpbar, dK;
	for (int iAzi = 0; iAzi < nAzi; ++iAzi)
	{
		for (int k = 0; k < nK; ++k)
		{
			if (k < kmin || k >= kmax)
			{
				m_vecAziInfo[iAzi].vecZp[k] = m_vecDVInfo[1].vecTraceData[k];
				m_vecAziInfo[iAzi].vecZs[k] = m_vecDVInfo[2].vecTraceData[k];
				m_vecAziInfo[iAzi].vecRho[k] = m_vecDVInfo[3].vecTraceData[k];
				continue;
			}

			dcos = cos((m_vecAziInfo[iAzi].azimuth - m_vecDVInfo[7].vecTraceData[k])*M_RAD);
			dcos2 = dcos*dcos;
			dcos4 = dcos2*dcos2;
			
			dvpbar = 0.5*(m_vecDVInfo[1].vecTraceData[k] / m_vecDVInfo[3].vecTraceData[k] + 
							m_vecDVInfo[1].vecTraceData[k + 1] / m_vecDVInfo[3].vecTraceData[k + 1]);
			dvsbar = 0.5*(m_vecDVInfo[2].vecTraceData[k] / m_vecDVInfo[3].vecTraceData[k] +
				m_vecDVInfo[2].vecTraceData[k + 1] / m_vecDVInfo[3].vecTraceData[k + 1]);
			dK = SQR(dvsbar/ dvpbar);

			m_vecAziInfo[iAzi].vecZp[k] = m_vecDVInfo[1].vecTraceData[k];
			m_vecAziInfo[iAzi].vecZs[k] = m_vecDVInfo[2].vecTraceData[k] * pow(sqrt(m_vecDeltaR[k])*m_vecGammaR[k], -dcos2)*
											pow(m_vecEpsilonR[k]/ m_vecDeltaR[k], (1.-4.*dK)/(8.*dK)*dcos4);
			m_vecAziInfo[iAzi].vecRho[k] = m_vecDVInfo[3].vecTraceData[k] * pow(m_vecDeltaR[k], -dcos2)*
											pow(m_vecEpsilonR[k] / m_vecDeltaR[k], -dcos4);
		}
	}
}

void CXThreadFractureInversion::_Write2Buffer(qint64 iCount, int iInlineNum, int iXlineNum)
{
	int nOutputFold = (int) m_vecAziInfo.size();
	char* pBuff = m_pInfoBuffer + iCount*(10 + 4 * nOutputFold);

	// offset
	qint64* pOffset = (qint64*)pBuff;
	*pOffset = iCount*nOutputFold*m_pOutputDV->GetSamplingQty() * sizeof(float);

	// fold
	short* pFold = (short*)(pBuff + 8);
	*pFold = (short)nOutputFold;

	// offset and azimuth
	for (int i = 0; i < nOutputFold; ++i)
	{
		short* pOff = (short*)(pBuff + 10 + 4 * i);
		short* pAzi = pOff + 1;

		*pOff = (short)0.;
		*pAzi = (short)m_vecAziInfo[i].azimuth;		
	}
}

bool CXThreadFractureInversion::_WriteInfoFile()
{
	QString strInfoFileName = m_pOutputDV->GetTraceInfoFileName();

	QFile qFile(strInfoFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return false;

	CXSeismicUTMTool utm = m_pOutputDV->GetUTM();
	qint64 nSize = utm.GetNI()*utm.GetNJ();

	qFile.write(m_pInfoBuffer, nSize*(10 + 4 * m_vecAziInfo.size()));
	qFile.close();
	return true;
}

bool CXThreadFractureInversion::_WriterData(CXAsynRegularWriter* pWriter, int nK)
{
	vector<float*> vecData;
	for (int iAzi = 0; iAzi < m_vecCalculation.size(); ++iAzi)
	{
		vector<float*> vec3Component;
		m_vecCalculation[iAzi]->GetThreeComponents(vec3Component);

		vecData.clear();
		float* pData = vec3Component[1] + m_iWriterOffset;
		//float* pData = vec3Component[7] + m_iWriterOffset;
		vecData.push_back(pData);
		pWriter->WaitWriteData();
		pWriter->WriteData(vecData, nK);
	}

	return true;
}

void CXThreadFractureInversion::RunThread()
{
	mkl_set_num_threads(m_pPara->GetCPUNumber());

	if (!m_pAziDV || !m_pZpDV || !m_pZsDV || !m_pRhoDV || !m_pEpsilonDV || !m_pDeltaDV || !m_pGammaDV || !m_pSymAziDV)
	{
		this->EmitGeneralErrorMsg("The selected data volumes has been deleted.");
		return;
	}

	if (m_bHorizon && (!m_pTopHor || !m_pBotHor))
	{
		this->EmitGeneralErrorMsg("One of selected horizons has been deleted.");
		return;
	}

	this->EmitSetWindowName("Seismic Anisotropy Inversion");
	this->EmitSetTaskName("Reading wavelet data");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	// for horizon constraints
	_GetHorizonData();

	// Get wavelet data
	if (!_GetWaveletDataAndAziInfo())
	{
		this->EmitGeneralErrorMsg("There is no valid wavelet data.");
		return;
	}

	if (!_GetReaders())
		return;


	if (!_CreateDV())
		return;

	_Calculate();
}



