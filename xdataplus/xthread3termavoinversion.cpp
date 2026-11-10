#pragma warning( push ,0 )
#include "xthread3termavoinversion.h"
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

//test
#include "xdataconvertor.h"
#include "x2dseismicline.h"
#include "xseismicdataline.h"
#include "xavoinversion.h"
#include "mkl.h"

#pragma warning( pop )

// in order to use qtconcurrent
void CalculateAVOInversion(CXAVOInversion* pCalculation)
{
	pCalculation->Calculate();
}


CXThread3TermAVOInversion::CXThread3TermAVOInversion(CXParameter3TermInversion* pPara)
{
	m_pPara = pPara;

	_Init();

	m_bTest = false;

	m_p2DLine = NULL;
}

CXThread3TermAVOInversion::~CXThread3TermAVOInversion()
{
	wait();

	// unlock object
	if (m_pPrestackDV)	UnlockRead(m_pPrestackDV);
	if (m_pZpDV)		UnlockRead(m_pZpDV);
	if (m_pZsDV)		UnlockRead(m_pZsDV);
	if (m_pRhoDV)		UnlockRead(m_pRhoDV);

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

		if (m_p2DLine)
		{
			delete m_p2DLine;
			m_p2DLine = NULL;
		}
	}
}

void CXThread3TermAVOInversion::_Init()
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

}

bool CXThread3TermAVOInversion::_GetWaveletData()
{
	QStringList listFileName = m_pPara->GetListWaveletFileName();

	m_nAngleNum = listFileName.size();
	for (int i = 0; i < listFileName.size(); ++i)
	{
		if (IsStopped())
			return false;
		else
			this->EmitUpdateProgress(i, m_nAngleNum + 2);

		vector<float> vecData;
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
		m_nWaveletSize = (int)vecData.size();
		m_vec2DWavelet.push_back(vecData);
	}

	m_vecAngle = m_pPara->GetVecAngleValue();
	m_vecAngleIndex = m_pPara->GetVecAngleIndex();

	if (IsStopped())
		return false;
	else
		this->EmitUpdateProgress(m_nAngleNum, m_nAngleNum + 2);

	return true;
}

bool CXThread3TermAVOInversion::_GetWaveletData_Test()
{
	QStringList listFileName;
		
	listFileName.append("F:/work/Code/examples/w12.dat");
	listFileName.append("F:/work/Code/examples/w36.dat");
	listFileName.append("F:/work/Code/examples/w43.dat");

	m_nAngleNum = listFileName.size();
	for (int i = 0; i < listFileName.size(); ++i)
	{
		if (IsStopped())
			return false;
		else
			this->EmitUpdateProgress(i, m_nAngleNum + 2);

		vector<float> vecData;
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
		m_nWaveletSize = (int)vecData.size();
		m_vec2DWavelet.push_back(vecData);
	}
	
	m_vecAngle.push_back(12.);
	m_vecAngle.push_back(36.);
	m_vecAngle.push_back(43.);

	if (IsStopped())
		return false;
	else
		this->EmitUpdateProgress(m_nAngleNum, m_nAngleNum + 2);

	return true;
}

bool CXThread3TermAVOInversion::_GetReaders()
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
		this->EmitUpdateProgress(m_nAngleNum+1, m_nAngleNum + 2);

	return true;
}


bool CXThread3TermAVOInversion::_Create2DDVAndReaders()
{
	//	Now create the imported line.
	m_p2DLine = new CX2DSeismicLine("2DLine");
	int nLength = 71;

	double* pX = new double [nLength];
	double* pY = new double[nLength];
	unsigned int* pCDP = new unsigned int[nLength];
	for (int i = 0; i < nLength; ++i)
	{
		pX[i] = i * 20;
		pY[i] = i * 20;
		pCDP[i] = 1;
	}
	m_p2DLine->PopulateData(nLength, pCDP, pX, pY);

	//	Then the seismic section	
	CXSeismicDataLine *pZp = new CXSeismicDataLine(m_p2DLine, 1, 301, 1, "Zp");
	CXRegularDataWriter<float>* pWriter = new CXRegularDataWriter<float>(pZp->GetDataFileName(), 1, nLength, 301);
	m_p2DLine->AddChild(pZp);
	m_vecWriter.push_back(pWriter);
	pWriter->Open();

	CXSeismicDataLine *pZs = new CXSeismicDataLine(m_p2DLine, 1, 301, 1, "Zs");
	pWriter = new CXRegularDataWriter<float>(pZs->GetDataFileName(), 1, nLength, 301);
	m_p2DLine->AddChild(pZs);
	m_vecWriter.push_back(pWriter);
	pWriter->Open();

	CXSeismicDataLine *pRho = new CXSeismicDataLine(m_p2DLine, 1, 301, 1, "Rho");
	pWriter = new CXRegularDataWriter<float>(pRho->GetDataFileName(), 1, nLength, 301);
	m_p2DLine->AddChild(pRho);
	m_vecWriter.push_back(pWriter);
	pWriter->Open();

	if (IsStopped())
		return false;
	else
		this->EmitUpdateProgress(m_nAngleNum + 2, m_nAngleNum + 2);

	return true;
}

bool CXThread3TermAVOInversion::_CreateDV()
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

	double dSamplingStart, dSamplingEnd, dSamplingRate;
	m_pZpDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	// three output
	const QChar rho(0x03C1);
	QStringList listDVName;
	int iOutputType = m_pPara->GetOutputType();
	if (iOutputType == CXParameter3TermInversion::eZpZsRho)
	{
		listDVName << "Zp" << "Zs" << rho;
	}
	else if (iOutputType == CXParameter3TermInversion::eZpVpVsRho)
	{
		listDVName << "Zp" << "VpVs" << rho;
	}
	else
	{
		listDVName << "Vp" << "Vs" << rho;
	}

	CXSeismicDataVolume* pNewZpDv = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, listDVName[0]);
	CXSeismicDataVolume* pNewZSDv = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, listDVName[1]);
	CXSeismicDataVolume* pNewDDv = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, listDVName[2]);

	m_vecOutputDV.push_back(pNewZpDv);
	m_vecOutputDV.push_back(pNewZSDv);
	m_vecOutputDV.push_back(pNewDDv);

	// reflectivity
	if (m_pPara->GetExportReflectivity())
	{
		for (int i = 0; i < m_vecAngle.size(); ++i)
		{
			QString strName = QString("R ") + QString::number(m_vecAngle[i], 'f', 1);
			CXSeismicDataVolume* pDV = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, strName);
			m_vecOutputDV.push_back(pDV);
		}
	}

	// seismic
	if (m_pPara->GetExportSeismic())
	{
		for (int i = 0; i < m_vecAngle.size(); ++i)
		{
			QString strName = QString("Seismic ") + QString::number(m_vecAngle[i], 'f', 1);
			CXSeismicDataVolume* pDV = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, strName);
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

void CXThread3TermAVOInversion::_CalcMinMax(vector<float>& vecZp, vector<float>& vecZs, vector<float>& vecRho, int nK, int& kMin, int& kMax)
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

	for (int k = nK-1; k >=0; --k)
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

void CXThread3TermAVOInversion::_RearrangeSeismicData(vector<float>& vecPreTrace, vector<float>& vecSeismic, int nKSeismic, int nK, int iKOffset)
{
	if (m_pPrestackDV)
	{
		for (int i = 0; i < m_vecAngleIndex.size(); ++i)
		{
			memcpy(&vecSeismic[i*nK], &vecPreTrace[m_vecAngleIndex[i] * nKSeismic + iKOffset], sizeof(float)*nK);
		}
	}
	else
	{
		for (int i = 0; i < m_nAngleNum; ++i)
		{
			memcpy(&vecSeismic[i*nK], &vecPreTrace[i * nKSeismic + iKOffset], sizeof(float)*nK);
		}
	}
}

void CXThread3TermAVOInversion::_CalcPrestack()
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
	int iOffset = static_cast<int>((m_vecDVInfo[1].samplingStart - m_vecDVInfo[0].samplingStart) / m_vecDVInfo[0].samplingRate + 0.01);

	vector<float> vecPreTrace(nKSeismic*nOffsetNum), vecZp(nKImped), vecZs(nKImped), vecRho(nKImped);
	vector<float> vecSeismic(nKImped*m_nAngleNum);

	// init
	int nThread = 1; // m_pPara->GetCPUNumber();
	bool bExportRCoef = m_pPara->GetExportReflectivity();
	bool bExportSeismic = m_pPara->GetExportSeismic();	
	int iOutputType = m_pPara->GetOutputType();

	//CXSystemInfo::GetCPUNum();	
	for (int i = 0; i < nThread; ++i)
	{
		CXAVOInversion* pCalculation = new CXAVOInversion;
		pCalculation->InitInversionPara(m_pPara->GetLambda(), m_pPara->GetGamma(), m_pPara->GetMaxLoopNum(), m_pPara->GetTolerance());
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


			m_vecCalculation[nCurrentThread]->SetDataBuffer(kMin, kMax, &vecZp[0], &vecZs[0], &vecRho[0], &vecSeismic[0], m_vecMaxValue);


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

			QList<CXAVOInversion*> listCalculation;
			for (int iCalc = 0; iCalc < nCurrentThread; ++iCalc)
				listCalculation.append(m_vecCalculation[iCalc]);

			// calculate			
			QtConcurrent::blockingMap<QList<CXAVOInversion*> >(listCalculation, CalculateAVOInversion);

			//write data
			if (!_WriterData(listCalculation, vecZp, nKImped, iOutputType, bExportRCoef, bExportSeismic))
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

void CXThread3TermAVOInversion::_CalcPostack()
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

	//CXSystemInfo::GetCPUNum();	
	for (int i = 0; i < nThread; ++i)
	{
		CXAVOInversion* pCalculation = new CXAVOInversion;
		pCalculation->InitInversionPara(m_pPara->GetLambda(), m_pPara->GetGamma(), m_pPara->GetMaxLoopNum(), m_pPara->GetTolerance());
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


			m_vecCalculation[nCurrentThread]->SetDataBuffer(kMin, kMax, &vecZp[0], &vecZs[0], &vecRho[0], &vecSeismic[0], m_vecMaxValue);


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

			QList<CXAVOInversion*> listCalculation;
			for (int iCalc = 0; iCalc < nCurrentThread; ++iCalc)
				listCalculation.append(m_vecCalculation[iCalc]);

			// calculate			
			QtConcurrent::blockingMap<QList<CXAVOInversion*> >(listCalculation, CalculateAVOInversion);

			//write data
			if (!_WriterData(listCalculation, vecZp, nKImped, iOutputType, bExportRCoef, bExportSeismic))
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

bool CXThread3TermAVOInversion::_WriteThreeComponents(float* pZp, float* pZs, float* pRho, vector<float>& vecBuffer, int nZ, int iOutputType)
{
	float fInvalid = (float)::g_dInvalidData;

	if (iOutputType == CXParameter3TermInversion::eZpZsRho)
	{
		if (!m_vecWriter[0]->Append(nZ, pZp) ||
			!m_vecWriter[1]->Append(nZ, pZs) ||
			!m_vecWriter[2]->Append(nZ, pRho))
			return false;
	}
	else if (iOutputType == CXParameter3TermInversion::eZpVpVsRho)
	{
		for (int i = 0; i < nZ; ++i)
		{
			if (pZp[i] == fInvalid || pZs[i] == fInvalid || pZs[i] == 0.f)
				vecBuffer[i] = fInvalid;
			else
				vecBuffer[i] = pZp[i] / pZs[i];
		}
		if (!m_vecWriter[0]->Append(nZ, pZp) ||
			!m_vecWriter[1]->Append(nZ, &vecBuffer[0]) ||
			!m_vecWriter[2]->Append(nZ, pRho))
			return false;
	}
	else
	{
		// vp
		for (int i = 0; i < nZ; ++i)
		{
			if (pZp[i] == fInvalid || pRho[i] == fInvalid || pRho[i] == 0.f)
				vecBuffer[i] = fInvalid;
			else
				vecBuffer[i] = pZp[i] / (1000*pRho[i]);
		}
		if (!m_vecWriter[0]->Append(nZ, &vecBuffer[0]))
			return false;

		// Vs
		for (int i = 0; i < nZ; ++i)
		{
			if (pZs[i] == fInvalid || pRho[i] == fInvalid || pRho[i] == 0.f)
				vecBuffer[i] = fInvalid;
			else
				vecBuffer[i] = pZs[i] / (1000*pRho[i]);
		}
		if (!m_vecWriter[1]->Append(nZ, &vecBuffer[0]))
			return false;

		if (!m_vecWriter[2]->Append(nZ, pRho))
			return false;
	}

	return true;
}

bool CXThread3TermAVOInversion::_WriterData(QList<CXAVOInversion*>& listCalc, vector<float>& vecBuffer, int nZ, int iOutputType, bool bExportR, bool bExportSeismic)
{
	float fInvalid = (float)::g_dInvalidData;
	int iDVIndex = 0;
	for (int iTrace = 0; iTrace < listCalc.size(); ++iTrace)
	{
		// three components
		float* pZpData = listCalc[iTrace]->GetZP();
		float* pZsData = listCalc[iTrace]->GetZS();
		float* pDData = listCalc[iTrace]->GetZD();

		if (!_WriteThreeComponents(pZpData, pZsData, pDData, vecBuffer, nZ, iOutputType))
			return false;

		iDVIndex = 3;
		if (bExportR)
		{
			float** pRCoef = listCalc[iTrace]->GetRCoef();
			assert(pRCoef);
			for (int iAngle = 0; iAngle < m_vecAngle.size(); ++iAngle)
			{
				if (!m_vecWriter[iDVIndex + iAngle]->Append(nZ, pRCoef[iAngle]))
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
				if (!m_vecWriter[iDVIndex + iAngle]->Append(nZ, pSeismic[iAngle]))
					return false;
			}
		}

	}

	return true;
}

void CXThread3TermAVOInversion::_Calc_Test()
{
	this->EmitResetProgressBar();
	this->EmitSetTaskName("Calculating");
	QCoreApplication::instance()->processEvents();

	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;

	iInlineMin = 0;
	iInlineMax = 70;
	iInlineInc = 1;

	iXlineMin = iXlineMax = iXlineInc = 1;

	int nKSeismic = 301;
	int nOffsetNum = 3;
	int nKImped = 301;
	int iOffset = 0;

	vector<float> vecPreTrace(nKSeismic*nOffsetNum), vecZp(nKImped), vecZs(nKImped), vecRho(nKImped);
	vector<float> vecSeismic(nKImped*m_nAngleNum);

	// init
	int nThread = 1;// CXSystemInfo::GetCPUNum();
		//CXSystemInfo::GetCPUNum();	
	for (int i = 0; i < nThread; ++i)
	{
		CXAVOInversion* pCalculation = new CXAVOInversion;
		pCalculation->InitInversionPara(m_pPara->GetLambda(), m_pPara->GetGamma(), m_pPara->GetMaxLoopNum(), m_pPara->GetTolerance());
		pCalculation->InitWaveletPara(m_vecAngle, m_nWaveletSize, m_vec2DWavelet);		
		pCalculation->CreateBuffers(nKImped, false, false);
		m_vecCalculation.push_back(pCalculation);
	}

	for (int i = 0; i < m_nAngleNum; ++i)
		m_vecMaxValue.push_back(1.);
	
	int nCurrentThread = 0;
	for (int i = iInlineMin; i <= iInlineMax; i += iInlineInc)
	{
		if (IsStopped())
			return;

		// read
		// prestack
		int iI, iJ;
		int kMin(0), kMax(0);

		_ReadTestCode(vecSeismic, vecZp, vecZs, vecRho, i);
		_CalcMinMax(vecZp, vecZs, vecRho, nKImped, kMin, kMax);	

		m_vecCalculation[nCurrentThread]->SetDataBuffer(kMin, kMax, &vecZp[0], &vecZs[0], &vecRho[0], &vecSeismic[0], m_vecMaxValue);

		++nCurrentThread;

		if (nCurrentThread < nThread && i != iInlineMax)
			continue;

		if (IsStopped())
			return;
		else
		{
			this->EmitUpdateProgress(i, iInlineMax);
		}

		QList<CXAVOInversion*> listCalculation;
		for (int iCalc = 0; iCalc < nCurrentThread; ++iCalc)
			listCalculation.append(m_vecCalculation[iCalc]);

		// calculate			
		QtConcurrent::blockingMap<QList<CXAVOInversion*> >(listCalculation, CalculateAVOInversion);

		// write
		for (int iCalc = 0; iCalc < listCalculation.size(); ++iCalc)
		{
			float* pZpData = listCalculation[iCalc]->GetZP();
			float* pZsData = listCalculation[iCalc]->GetZS();
			float* pDData = listCalculation[iCalc]->GetZD();

			if (!m_vecWriter[0]->Append(nKImped, pZpData) ||
				!m_vecWriter[1]->Append(nKImped, pZsData) ||
				!m_vecWriter[2]->Append(nKImped, pDData))
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

void CXThread3TermAVOInversion::_ReadTestCode(vector<float>& vecSeismic, vector<float>& vecZp, vector<float>& vecZs, vector<float>& vecRho, int index)
{
	QString strSeis = "F:/work/Code/examples/V.sgy";
	QString strZp = "F:/work/Code/examples/Zp0.sgy";
	QString strZs = "F:/work/Code/examples/Zs0.sgy";
	QString strRho = "F:/work/Code/examples/Dn0.sgy";

	// read seismic
	int nLength = vecZp.size();
	vector<float> vecTrace(nLength), vecData(nLength);
	QFile qFile;
	qFile.setFileName(strSeis);
	bool b = qFile.open(QIODevice::ReadOnly);
	int iOffset = 3 * index*(240 + nLength*sizeof(float));
	qFile.seek(3600 + iOffset + 240);
	qFile.read((char*)&vecTrace[0], sizeof(float)*nLength);
	_ConvertData((char*)&vecTrace[0], &vecData[0], nLength);
	for (int i = 0; i < nLength; ++i)
		vecSeismic[i] = vecData[i];

	qFile.seek(3600 + iOffset+ (240 + nLength*sizeof(float)) * 1 + 240);
	qFile.read((char*)&vecTrace[0], sizeof(float)*nLength);
	_ConvertData((char*)&vecTrace[0], &vecData[0], nLength);
	for (int i = 0; i < nLength; ++i)
		vecSeismic[i + nLength] = vecData[i];

	qFile.seek(3600 + iOffset+ (240 + nLength*sizeof(float)) * 2 + 240);
	qFile.read((char*)&vecTrace[0], sizeof(float)*nLength);
	_ConvertData((char*)&vecTrace[0], &vecData[0], nLength);
	for (int i = 0; i < nLength; ++i)
		vecSeismic[i + 2*nLength] = vecData[i];

	// read zp
	iOffset = index*(240 + nLength*sizeof(float));
	qFile.close();
	qFile.setFileName(strZp);
	qFile.open(QIODevice::ReadOnly);
	qFile.seek(3600 + iOffset+240);
	qFile.read((char*)&vecTrace[0], sizeof(float)*nLength);
	_ConvertData((char*)&vecTrace[0], &vecData[0], nLength);
	for (int i = 0; i < nLength; ++i)
		vecZp[i ] = vecData[i];

	// read zs
	qFile.close();
	qFile.setFileName(strZs);
	qFile.open(QIODevice::ReadOnly);
	qFile.seek(3600 + iOffset+240);
	qFile.read((char*)&vecTrace[0], sizeof(float)*nLength);
	_ConvertData((char*)&vecTrace[0], &vecData[0], nLength);
	for (int i = 0; i < nLength; ++i)
		vecZs[i] = vecData[i];

	// read rho
	qFile.close();
	qFile.setFileName(strRho);
	qFile.open(QIODevice::ReadOnly);
	qFile.seek(3600 + iOffset+240);
	qFile.read((char*)&vecTrace[0], sizeof(float)*nLength);
	_ConvertData((char*)&vecTrace[0], &vecData[0], nLength);
	for (int i = 0; i < nLength; ++i)
		vecRho[i] = vecData[i];

}

void CXThread3TermAVOInversion::_ConvertData(char* pChar, float* fData, int nDataLength)
{
	vector<float> vecData(nDataLength);
	char c;

	for (int i = 0; i < nDataLength; ++i)
	{
		c = pChar[4 * i];
		pChar[4 * i] = pChar[4 * i + 3];
		pChar[4 * i + 3] = c;
		c = pChar[4 * i + 1];
		pChar[4 * i + 1] = pChar[4 * i + 2];
		pChar[4 * i + 2] = c;

		vecData[i] = *((float *)(pChar + 4 * i));
	}

	IBMToIEEE((int *)&vecData[0], (int *)fData, nDataLength);

}

void CXThread3TermAVOInversion::RunThread()
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

	this->EmitSetWindowName("Three-term AVO Inversion");
	this->EmitSetTaskName("Reading wavelet data");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	if (m_bTest)
	{
		if (!_GetWaveletData_Test())
			return;

		if (!_Create2DDVAndReaders())
			return;

		_Calc_Test();
	}
	else
	{
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
}



