#pragma warning( push ,0 )
#include "xthreadavossinversion.h"
#include "xparameter3terminversion.h"
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
#include "xavo3terminversion.h"
#include <QFile>
#include "xregulardatareader.h"
#include "xregulardatawriter.h"
#include "xsysteminfo.h"
#include <qtconcurrentmap.h>

#include "xavossinversion.h"
#include "mkl.h"
#include "xwavelet.h"
#include "x3dhorizon.h"

#pragma warning( pop )

// in order to use qtconcurrent
void CalculateAVOInversion(CXAVOSSInversion* pCalculation)
{
	pCalculation->Calculate();
}


CXThreadAVOSSInversion::CXThreadAVOSSInversion(CXParameter3TermInversion* pPara)
{
	m_pPara = pPara;

	m_pTopHor = nullptr;
	m_pBotHor = nullptr;

	_Init();	
}

CXThreadAVOSSInversion::~CXThreadAVOSSInversion()
{
	wait();

	// unlock object
	if (m_pPrestackDV)	UnlockRead(m_pPrestackDV);
	if (m_pZpDV)		UnlockRead(m_pZpDV);
	if (m_pZsDV)		UnlockRead(m_pZsDV);
	if (m_pRhoDV)		UnlockRead(m_pRhoDV);

	if (m_pTopHor)		UnlockRead(m_pTopHor);
	if (m_pBotHor)		UnlockRead(m_pBotHor);

	for (int i = 0; i < m_vecPSDV.size(); ++i)
	{
		UnlockRead(m_vecPSDV[i]);
	}

	// readers
	for (int i = 0; i < m_vecDVInfo.size(); ++i)
	{
		delete m_vecDVInfo[i].reader;
	}
	m_vecDVInfo.clear();

	//dv readers
	qDeleteAll(m_vecPSDVReader);
	m_vecPSDVReader.clear();

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

void CXThreadAVOSSInversion::_Init()
{
	m_pPrestackDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetPrestackDVID()));

	vector<QUuid> vecDVID = m_pPara->GetVecDVID();
	for (int i = 0; i < vecDVID.size(); ++i)
	{
		m_vecPSDV.push_back(dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[i])));
	}
	for (int i = 0; i < m_vecPSDV.size(); ++i)
	{
		LockRead(m_vecPSDV[i]);
	}

	m_pZpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZpID()));
	m_pZsDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZsID()));
	m_pRhoDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetRhoID()));


	if (m_pPrestackDV)	LockRead(m_pPrestackDV);
	if (m_pZpDV)		LockRead(m_pZpDV);
	if (m_pZsDV)		LockRead(m_pZsDV);
	if (m_pRhoDV)		LockRead(m_pRhoDV);

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

bool CXThreadAVOSSInversion::_GetWaveletData()
{
	QStringList listFileName = m_pPara->GetListWaveletFileName();
	std::vector<QUuid> vecWaveletObjID = m_pPara->GetVecWaveletID();

	m_nAngleNum = listFileName.size();	
	for (int i = 0; i < listFileName.size(); ++i)
	{
		vector<float> vecData;

		if (IsStopped())
			return false;
		else
			this->EmitUpdateProgress(i, m_nAngleNum + 2);
				
		if (QFile::exists(listFileName[i]))
		{
			QFile qFile(listFileName[i]);
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
					vecData.push_back(fValue);
				}
			}
		}
		else
		{
			CXWavelet* pWavelet = dynamic_cast<CXWavelet*>(::GetObjectByID(vecWaveletObjID[i]));
			if (pWavelet)
			{
				unsigned int ndataLength;
				double *pData = pWavelet->CXObject::GetData(ndataLength);
				vecData.resize(ndataLength);				
				if (pData)
				{
					for (int ii = 0; ii < ndataLength; ++ii)
						vecData[ii] = (float)pData[ii];
				}
			}
		}
		m_nWaveletSize = (int)vecData.size();
		m_vec2DWavelet.push_back(vecData);

		if (vecData.empty())
		{
			this->EmitGeneralErrorMsg("Cannot read the wavelet data.");
			return false;
		}
	}

	m_vecAngle = m_pPara->GetVecAngleValue();
	m_vecAngleIndex = m_pPara->GetVecAngleIndex();

	if (IsStopped())
		return false;
	else
		this->EmitUpdateProgress(m_nAngleNum, m_nAngleNum + 2);

	return true;
}



bool CXThreadAVOSSInversion::_GetReaders()
{
	sDVInfo s;

	// prestack
	if (m_pPrestackDV)
	{
		s.reader = new CXRegularDataReader<float>(m_pPrestackDV->GetTraceFileName(), m_pPrestackDV->GetInlineQty(),
			m_pPrestackDV->GetXlineQty(), m_pPrestackDV->GetSamplingQty(), m_pPrestackDV->GetMaxFold());

		s.utm = m_pPrestackDV->GetUTM();
		m_pPrestackDV->GetSamplingRange(s.samplingStart, s.samplingEnd, s.samplingRate);
		m_vecDVInfo.push_back(s);
		if (!s.reader->Open())
		{
			this->EmitGeneralErrorMsg("Cannot open the prestack data file.");
			return false;
		}

		double dMin, dMax;
		m_pPrestackDV->GetDataRange(dMin, dMax);
		for (int i = 0; i < m_nAngleNum; ++i)
			m_vecMaxValue.push_back(dMax);
	}

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

	// tell range
	if (m_pPrestackDV)
	{
		if (m_vecDVInfo[0].samplingStart > m_vecDVInfo[1].samplingStart ||
			m_vecDVInfo[0].samplingEnd < m_vecDVInfo[1].samplingEnd)
		{
			this->EmitGeneralErrorMsg("The range of the seismic data is too small.");
			return false;
		}
	}
	else
	{
		double dSamplingstart, dSamplingEnd, dStep;
		m_vecPSDV[0]->GetSamplingRange(dSamplingstart, dSamplingEnd, dStep);

		if (dSamplingstart > m_vecDVInfo[1].samplingStart ||
			dSamplingEnd < m_vecDVInfo[1].samplingEnd)
		{
			this->EmitGeneralErrorMsg("The range of the seismic data is too small.");
			return false;
		}
	}

	// post stack seismic data volume
	for (int i = 0; i < m_vecPSDV.size(); ++i)
	{
		int nI = m_vecPSDV[i]->GetInlineQty();
		int nJ = m_vecPSDV[i]->GetXlineQty();
		int nK = m_vecPSDV[i]->GetSamplingQty();
		m_utmPSDV = m_vecPSDV[i]->GetUTM();

		CXRegularDataReader<float>* pReader = new CXRegularDataReader<float>(m_vecPSDV[i]->GetTraceFileName(), nI, nJ, nK);
		m_vecPSDVReader.push_back(pReader);
		if (!pReader->Open())
		{
			this->EmitGeneralErrorMsg("Cannot open the seismic data volume to read data.");
			return false;
		}

		// max value
		double dMin, dMax;
		m_vecPSDV[i]->GetDataRange(dMin, dMax);
		m_vecMaxValue.push_back(dMax);
	}


	if (IsStopped())
		return false;
	else
		this->EmitUpdateProgress(m_nAngleNum + 1, m_nAngleNum + 2);

	return true;
}




bool CXThreadAVOSSInversion::_CreateDV()
{
	CXSeismicUTMTool utm;
	if (m_pPrestackDV)
		utm = m_pPrestackDV->GetUTM();
	else
		utm = m_vecPSDV[0]->GetUTM();

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

	//double dSamplingStart, dSamplingEnd, dSamplingRate;
	//m_pZpDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	// three output
	//const QChar rho(0x03C1);
	if (m_pPara->GetOutputInversion())
	{
		QStringList listDVName;
		int iOutputType = m_pPara->GetOutputType();
		if (iOutputType == CXParameter3TermInversion::eZpZsRho)
		{
			listDVName << "Zp" << "Zs" << "Density" << "Zp bp" << "Zs bp" << "Density bp" << "Zp merged" << "Zs merged" << "Density merged";
		}
		else if (iOutputType == CXParameter3TermInversion::eZpVpVsRho)
		{
			listDVName << "Zp" << "VpVs" << "Density" << "Zp bp" << "VpVs bp" << "Density bp" << "Zp merged" << "VpVs merged" << "Density merged";
		}
		else
		{
			listDVName << "Vp" << "Vs" << "Density" << "Vp bp" << "Vs bp" << "Density bp" << "Vp merged" << "Vs merged" << "Density merged";
		}

		for (int i = 0; i < 9; ++i)
		{
			CXSeismicDataVolume* pNewDv = new CXSeismicDataVolume(utm, m_dSamplingStart, m_dSamplingEnd, m_dSamplingRate, listDVName[i]);
			m_vecOutputDV.push_back(pNewDv);
		}

		// reflectivity
		if (m_pPara->GetExportReflectivity())
		{
			for (int i = 0; i < m_vecAngle.size(); ++i)
			{
				QString strName = QString("R ") + QString::number(m_vecAngle[i], 'f', 1);
				CXSeismicDataVolume* pDV = new CXSeismicDataVolume(utm, m_dSamplingStart, m_dSamplingEnd, m_dSamplingRate, strName);
				m_vecOutputDV.push_back(pDV);
			}
		}

		// seismic
		if (m_pPara->GetExportSeismic())
		{
			for (int i = 0; i < m_vecAngle.size(); ++i)
			{
				QString strName = QString("Seismic ") + QString::number(m_vecAngle[i], 'f', 1);
				CXSeismicDataVolume* pDV = new CXSeismicDataVolume(utm, m_dSamplingStart, m_dSamplingEnd, m_dSamplingRate, strName);
				m_vecOutputDV.push_back(pDV);
			}
		}
	}

	if (m_pPara->GetOutputPrior())
	{
		for (int i = 0; i < m_vecAngle.size(); ++i)
		{
			QString strName = QString("synthetic ") + QString::number(m_vecAngle[i], 'f', 1);
			CXSeismicDataVolume* pDV = new CXSeismicDataVolume(utm, m_dSamplingStart, m_dSamplingEnd, m_dSamplingRate, strName);
			m_vecOutputDV.push_back(pDV);
		}
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
		this->EmitUpdateProgress(m_nAngleNum + 2, m_nAngleNum + 2);

	return true;
}

void CXThreadAVOSSInversion::_CalcMinMax(vector<float>& vecZp, vector<float>& vecZs, vector<float>& vecRho, int nK, int& kMin, int& kMax)
{
	float fInvalid = g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

	for (int k = 0; k < nK; ++k)
	{
		if (qAbs(vecZp[k] - fInvalid) < fInvalidEPS || vecZp[k] <= 0.f ||
			qAbs(vecZs[k] - fInvalid) < fInvalidEPS || vecZs[k] <= 0.f ||
			qAbs(vecRho[k] - fInvalid) < fInvalidEPS || vecRho[k] <= 0.f)
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
		if (qAbs(vecZp[k] - fInvalid) < fInvalidEPS || vecZp[k] <= 0.f ||
			qAbs(vecZs[k] - fInvalid) < fInvalidEPS || vecZs[k] <= 0.f ||
			qAbs(vecRho[k] - fInvalid) < fInvalidEPS || vecRho[k] <= 0.f)
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

void CXThreadAVOSSInversion::_RearrangeSeismicData(vector<float>& vecPreTrace, vector<float>& vecSeismic, int nKSeismic, int nKImped, int iKOffset)
{
	if (m_pPrestackDV)
	{
		for (int i = 0; i < m_vecAngleIndex.size(); ++i)
		{
			memcpy(&vecSeismic[i*nKImped], &vecPreTrace[m_vecAngleIndex[i] * nKSeismic + iKOffset], sizeof(float)*nKImped);
		}
	}
	else
	{
		for (int i = 0; i < m_nAngleNum; ++i)
		{
			memcpy(&vecSeismic[i*nKImped], &vecPreTrace[i * nKSeismic + iKOffset], sizeof(float)*nKImped);
		}
	}
}

void CXThreadAVOSSInversion::_CalcPrestack()
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

	int nKSeismic = m_pPrestackDV->GetSamplingQty();
	int nOffsetNum = m_pPrestackDV->GetMaxFold();
	int nKImped = m_pZpDV->GetSamplingQty();
	int nK = static_cast<int>((m_dSamplingEnd - m_dSamplingStart) / m_dSamplingRate + 0.01) + 1;

	double dPImedSamplingStart = m_vecDVInfo[1].samplingStart;
	int iOffset = static_cast<int>((dPImedSamplingStart - m_vecDVInfo[0].samplingStart) / m_vecDVInfo[0].samplingRate + 0.01);
	m_iWriterOffset = static_cast<int>((m_dSamplingStart - dPImedSamplingStart) / m_dSamplingRate + 0.01);	

	vector<float> vecPreTrace(nKSeismic*nOffsetNum), vecZp(nKImped), vecZs(nKImped), vecRho(nKImped);
	vector<float> vecSeismic(nKImped*m_nAngleNum);

	// init
	int nThread = 1;// m_pPara->GetCPUNumber();
	bool bExportRCoef = m_pPara->GetExportReflectivity();
	bool bExportSeismic = m_pPara->GetExportSeismic();

	//CXSystemInfo::GetCPUNum();	
	for (int i = 0; i < nThread; ++i)
	{
		CXAVOSSInversion* pCalculation = new CXAVOSSInversion;
		pCalculation->InitInversionPara(m_pPara);
		pCalculation->InitWaveletPara(m_vecAngle, m_nWaveletSize, m_vec2DWavelet);
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
			// prestack
			int iI, iJ;
			int kMin(0), kMax(0);

			m_vecDVInfo[0].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[0].reader->ReadUVTrace(iI, iJ, &vecPreTrace[0]);

			// zp
			m_vecDVInfo[1].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[1].reader->ReadUVTrace(iI, iJ, &vecZp[0]);

			//zs
			m_vecDVInfo[2].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[2].reader->ReadUVTrace(iI, iJ, &vecZs[0]);

			//rho
			m_vecDVInfo[3].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[3].reader->ReadUVTrace(iI, iJ, &vecRho[0]);


			_CalcMinMax(vecZp, vecZs, vecRho, nKImped, kMin, kMax);
			_RearrangeSeismicData(vecPreTrace, vecSeismic, nKSeismic, nKImped, iOffset);

			// Z constraints
			int kMinNew, kMaxNew;
			_CalcHorizonKRange(i, j, dPImedSamplingStart, nKImped, kMinNew, kMaxNew);


			m_vecCalculation[nCurrentThread]->SetDataBuffer(qMax(kMin, kMinNew), qMin(kMax, kMaxNew), &vecZp[0], &vecZs[0], &vecRho[0], &vecSeismic[0]);


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

			QList<CXAVOSSInversion*> listCalculation;
			for (int iCalc = 0; iCalc < nCurrentThread; ++iCalc)
				listCalculation.append(m_vecCalculation[iCalc]);

			// calculate			
			QtConcurrent::blockingMap<QList<CXAVOSSInversion*> >(listCalculation, CalculateAVOInversion);

			//write data
			if (!_WriterData(listCalculation, nK, bExportRCoef, bExportSeismic))
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

void CXThreadAVOSSInversion::_CalcPostack()
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

	int nKSeismic = m_vecPSDV[0]->GetSamplingQty();
	int nKImped = m_pZpDV->GetSamplingQty();
	int nK = static_cast<int>((m_dSamplingEnd - m_dSamplingStart) / m_dSamplingRate + 0.01) + 1;

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_vecPSDV[0]->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	double dPImedSamplingStart = m_vecDVInfo[1].samplingStart;
	int iOffset = static_cast<int>((dPImedSamplingStart - dSamplingStart) / m_dSamplingRate + 0.01);
	m_iWriterOffset = static_cast<int>((m_dSamplingStart - dPImedSamplingStart) / m_dSamplingRate + 0.01);

	vector<float> vecPreTrace(nKSeismic*m_nAngleNum), vecZp(nKImped), vecZs(nKImped), vecRho(nKImped);
	vector<float> vecSeismic(nKImped*m_nAngleNum);

	// init
	int nThread = 1; // m_pPara->GetCPUNumber();
	bool bExportRCoef = m_pPara->GetExportReflectivity();
	bool bExportSeismic = m_pPara->GetExportSeismic();
	int iOutputType = m_pPara->GetOutputType();

	//CXSystemInfo::GetCPUNum();	
	for (int i = 0; i < nThread; ++i)
	{
		CXAVOSSInversion* pCalculation = new CXAVOSSInversion;
		pCalculation->InitInversionPara(m_pPara);
		pCalculation->InitWaveletPara(m_vecAngle, m_nWaveletSize, m_vec2DWavelet);
		pCalculation->CreateBuffers(nKImped, bExportRCoef, bExportSeismic);
		m_vecCalculation.push_back(pCalculation);
	}

	int nCurrentThread = 0;
	vector<int> vecOffset;
	for (int i = iInlineMin; i <= iInlineMax; i += iInlineInc)
	{
		for (int j = iXlineMin; j <= iXlineMax; j += iXlineInc)
		{
			if (IsStopped())
				return;

			// read
			// poststack
			int iI, iJ;
			m_utmPSDV.LineToIJ(i, j, iI, iJ);
			for (int iDV = 0; iDV < m_vecPSDVReader.size(); ++iDV)
			{
				m_vecPSDVReader[iDV]->ReadUVTrace(iI, iJ, &vecPreTrace[iDV*nKSeismic]);
			}

			// zp
			m_vecDVInfo[0].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[0].reader->ReadUVTrace(iI, iJ, &vecZp[0]);

			//zs
			m_vecDVInfo[1].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[1].reader->ReadUVTrace(iI, iJ, &vecZs[0]);

			//rho
			m_vecDVInfo[2].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[2].reader->ReadUVTrace(iI, iJ, &vecRho[0]);


			int kMin(0), kMax(0);
			_CalcMinMax(vecZp, vecZs, vecRho, nKImped, kMin, kMax);
			_RearrangeSeismicData(vecPreTrace, vecSeismic, nKSeismic, nKImped, iOffset);

			// Z constraints
			int kMinNew, kMaxNew;
			_CalcHorizonKRange(i, j, dPImedSamplingStart, nKImped, kMinNew, kMaxNew);

			m_vecCalculation[nCurrentThread]->SetDataBuffer(qMax(kMin, kMinNew), qMin(kMax, kMaxNew), &vecZp[0], &vecZs[0], &vecRho[0], &vecSeismic[0]);


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

			QList<CXAVOSSInversion*> listCalculation;
			for (int iCalc = 0; iCalc < nCurrentThread; ++iCalc)
				listCalculation.append(m_vecCalculation[iCalc]);

			// calculate			
			QtConcurrent::blockingMap<QList<CXAVOSSInversion*> >(listCalculation, CalculateAVOInversion);

			//write data
			if (!_WriterData(listCalculation, nK, bExportRCoef, bExportSeismic))
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

void CXThreadAVOSSInversion::_CalcHorizonKRange(int iInline, int iXline, double dImpedSamplingStart, int nKImped, int& kminnew, int& kmaxnew)
{
	//kminnew = 0;
	//kmaxnew = nKImped - 1;

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
			kmaxnew = nKImped-1;
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


void CXThreadAVOSSInversion::_CalcPostack2()
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

	int nKSeismic = m_vecPSDV[0]->GetSamplingQty();
	int nKImped = m_pZpDV->GetSamplingQty();

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_vecPSDV[0]->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	int iOffset = static_cast<int>((m_vecDVInfo[1].samplingStart - dSamplingStart) / dSamplingRate + 0.01);	

	vector<float> vecPreTrace(nKSeismic*m_nAngleNum), vecZp(nKImped), vecZs(nKImped), vecRho(nKImped);
	vector<float> vecSeismic(nKImped*m_nAngleNum);

	// init
	int nThread = 1; // m_pPara->GetCPUNumber();
	bool bExportRCoef = m_pPara->GetExportReflectivity();
	bool bExportSeismic = m_pPara->GetExportSeismic();
	int iOutputType = m_pPara->GetOutputType();

	CXAVOSSInversion* pCalculation = new CXAVOSSInversion;
	pCalculation->InitInversionPara(m_pPara);
	pCalculation->InitWaveletPara(m_vecAngle, m_nWaveletSize, m_vec2DWavelet);
	pCalculation->CreateBuffers(nKImped, bExportRCoef, bExportSeismic);

	QList<CXAVOSSInversion*> listCalculation;
	listCalculation.append(pCalculation);


	int nCurrentThread = 0;
	for (int i = iInlineMin; i <= iInlineMax; i += iInlineInc)
	{
		for (int j = iXlineMin; j <= iXlineMax; j += iXlineInc)
		{
			if (IsStopped())
				return;

			// read
			// poststack
			int iI, iJ;
			m_utmPSDV.LineToIJ(i, j, iI, iJ);
			for (int iDV = 0; iDV < m_vecPSDVReader.size(); ++iDV)
			{
				m_vecPSDVReader[iDV]->ReadUVTrace(iI, iJ, &vecPreTrace[iDV*nKSeismic]);
			}

			// zp
			m_vecDVInfo[0].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[0].reader->ReadUVTrace(iI, iJ, &vecZp[0]);

			//zs
			m_vecDVInfo[1].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[1].reader->ReadUVTrace(iI, iJ, &vecZs[0]);

			//rho
			m_vecDVInfo[2].utm.LineToIJ(i, j, iI, iJ);
			m_vecDVInfo[2].reader->ReadUVTrace(iI, iJ, &vecRho[0]);


			int kMin(0), kMax(0);
			_CalcMinMax(vecZp, vecZs, vecRho, nKImped, kMin, kMax);
			_RearrangeSeismicData(vecPreTrace, vecSeismic, nKSeismic, nKImped, iOffset);

			pCalculation->SetDataBuffer(kMin, kMax, &vecZp[0], &vecZs[0], &vecRho[0], &vecSeismic[0]);		

			if (IsStopped())
				return;
			else
			{
				int ii, jj;
				utm.LineToIJ(i, j, ii, jj);
				this->EmitUpdateProgress(ii*utm.GetNJ() + jj, utm.GetNI()*utm.GetNJ());
			}
			
			pCalculation->Calculate();
			
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

bool CXThreadAVOSSInversion::_WriterData(QList<CXAVOSSInversion*>& listCalc, int nZ, bool bExportR, bool bExportSeismic)
{
	float fInvalid = (float)::g_dInvalidData;
	int iDVIndex = 0;
	for (int iTrace = 0; iTrace < listCalc.size(); ++iTrace)
	{
		int iOffset = m_iWriterOffset;
		// three components
		iDVIndex = 0;
		if (m_pPara->GetOutputInversion())
		{
			vector<float*> vec3Component;
			listCalc[iTrace]->GetThreeComponents(vec3Component);

			for (int i = 0; i < 9; ++i)
			{
				if (!m_vecWriter[i]->Append(nZ, vec3Component[i]+ iOffset))
					return false;
			}

			iDVIndex = 9;
			if (bExportR)
			{
				float** pRCoef = listCalc[iTrace]->GetRCoef();
				assert(pRCoef);
				for (int iAngle = 0; iAngle < m_vecAngle.size(); ++iAngle)
				{
					if (!m_vecWriter[iDVIndex + iAngle]->Append(nZ, pRCoef[iAngle] + iOffset))
						return false;
				}

				iDVIndex += m_vecAngle.size();
			}

			if (bExportSeismic)
			{
				float** pSeismic = listCalc[iTrace]->GetSeismic();
				assert(pSeismic);

				for (int iAngle = 0; iAngle < m_vecAngle.size(); ++iAngle)
				{
					if (!m_vecWriter[iDVIndex + iAngle]->Append(nZ, pSeismic[iAngle] + iOffset))
						return false;
				}

				iDVIndex += m_vecAngle.size();
			}
		}

		if (m_pPara->GetOutputPrior())
		{
			float** p2DPrior = listCalc[iTrace]->GetPriorSeismic();
			assert(p2DPrior);

			for (int iAngle = 0; iAngle < m_vecAngle.size(); ++iAngle)
			{
				if (!m_vecWriter[iDVIndex + iAngle]->Append(nZ, p2DPrior[iAngle] + iOffset))
					return false;
			}
		}

	}

	return true;
}


void CXThreadAVOSSInversion::_GetHorizonData()
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
		m_vecPSDV[0]->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

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

void CXThreadAVOSSInversion::RunThread()
{	
	mkl_set_num_threads(m_pPara->GetCPUNumber());

	if (!m_pZpDV || !m_pZsDV || !m_pRhoDV)
	{
		this->EmitGeneralErrorMsg("One of selected data volumes has been deleted.");
		return;
	}

	if (!m_pPrestackDV)
	{
		if (m_vecPSDV.empty() || m_vecPSDV.size() != m_pPara->GetVecAngleValue().size())
		{
			this->EmitGeneralErrorMsg("One of selected seismic data volumes has been deleted.");
			return;
		}
	}

	if (m_bHorizon && (!m_pTopHor || !m_pBotHor))
	{
		this->EmitGeneralErrorMsg("One of selected horizons has been deleted.");
		return;
	}

	if (m_pPara->GetObjectType() == EAVOSSInversion)
		this->EmitSetWindowName("Prestack AVO Sparse Spike Inversion");
	else
		this->EmitSetWindowName("Prestack AVO Inversion");

	this->EmitSetTaskName("Reading wavelet data");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	// for horizon constraints
	_GetHorizonData();

	// Get wavelet data
	if (!_GetWaveletData())
		return;

	if (!_GetReaders())
		return;


	if (!_CreateDV())
		return;

	if (m_pPrestackDV)
		_CalcPrestack();
	else
		_CalcPostack();
	
}



