#pragma warning( push ,0 )
#include "xthreadfractureavo.h"
#include "xparameterfractureavo.h"
#include "xseismicdatavolume.h"
#include <QCoreApplication>
#include <QMultiMap>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "xproject.h"
#include "xutility.h"
#include "xavo3terminversion.h"
#include <QFile>
#include "xregulardatareader.h"
#include "xregulardatawriter.h"
#include "xsysteminfo.h"
#include <qtconcurrentmap.h>
#include "xprestackdatareaderbuff.h"

#include "mkl.h"

#pragma warning( pop )

CXThreadFractureAVO::CXThreadFractureAVO(CXParameterFractureAVO* pPara)
{
	m_pPara = pPara;
	m_pAziDV = nullptr;

	_Init();
}

CXThreadFractureAVO::~CXThreadFractureAVO()
{
	wait();

	for (int i = 0; i < m_vecInDV.size(); ++i)
	{
		UnlockRead(m_vecInDV[i]);
	}	

	if (m_pAziDV)
		UnlockRead(m_pAziDV);

	// writers
	qDeleteAll(m_vecWriter);
	m_vecWriter.clear();


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

void CXThreadFractureAVO::_Init()
{
	vector<QUuid> vecDVID = m_pPara->GetVecDVID();
	for (int i = 0; i < vecDVID.size(); ++i)
	{
		m_vecInDV.push_back(dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[i])));
	}
	for (int i = 0; i < m_vecInDV.size(); ++i)
	{
		LockRead(m_vecInDV[i]);
	}

	m_pAziDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetAzimuthDVID()));

	if (m_pAziDV)
		LockRead(m_pAziDV);
}


bool CXThreadFractureAVO::_GetReaders()
{	
	// post stack seismic data volume
	m_nMaxNK = 0;
	m_nMaxFold = 0;

	if (!m_vecInDV.empty())
	{
		for (int i = 0; i < m_vecInDV.size(); ++i)
		{
			m_nMaxNK = qMax(m_nMaxNK, m_vecInDV[i]->GetSamplingQty());
			m_nMaxFold = qMax(m_nMaxFold, (int)m_vecInDV[i]->GetMaxFold());
		}
		m_nMaxFold *= m_vecInDV.size();
	}
	else
	{
		m_nMaxNK = m_pAziDV->GetSamplingQty();
		m_nMaxFold = m_pAziDV->GetMaxFold();
	}

	return true;
}


bool CXThreadFractureAVO::_CreateDV()
{
	CXSeismicUTMTool utm;
	if (!m_vecInDV.empty())
	{
		utm = m_vecInDV[0]->GetUTM();
	}
	else if (m_pAziDV)
	{
		utm = m_pAziDV->GetUTM();
	}
	else
	{
		this->EmitGeneralErrorMsg("There is no valid seismic data volume.");
		return false;
	}

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
	int nK = static_cast<int>((dSamplingEnd - dSamplingStart) / dSamplingRate + 0.01) + 1;


	// two output DVs
	
	QStringList listDVName;
	listDVName << "Bani" << "Azimuth";

	for (int i = 0; i < listDVName.size(); ++i)
	{
		CXSeismicDataVolume* pNewDv = new CXSeismicDataVolume(utm, dSamplingStart, dSamplingEnd, dSamplingRate, listDVName[i]);
		m_vecOutputDV.push_back(pNewDv);
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
		return true;
}

void CXThreadFractureAVO::_CalcPostack()
{
	this->EmitSetTaskName("Calculating");
	QCoreApplication::instance()->processEvents();

	int nMinimumFold = m_pPara->GetMinimumFold();

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

	int nI = (iInlineMax - iInlineMin) / iInlineInc + 1;
	int nJ = (iXlineMax - iXlineMin) / iXlineInc + 1;
	qint64 nK = static_cast<int>((dSamplingEnd - dSamplingStart) / dSamplingRate + 0.01) + 1;

	int iHalfDI = qMax(0, m_pPara->GetDy() / 2 );
	int iHalfDJ = qMax(0, m_pPara->GetDx() / 2 );
	qint64 nMaxStackNum = (2 * iHalfDI + 1)*(2 * iHalfDJ + 1);

	vector<float> vecAzimuth = m_pPara->GetVecAzimuth();

	vector<float> vecBuffer(nMaxStackNum*nK*m_nMaxFold);
	vector<float> vecGatherBuff(m_nMaxNK*m_nMaxFold);
	QMultiMap<QPair<float, float>, int> mapPosition;
	QMap<QPair<float, float>, float*> mapBuff;
	QVector<float> vecOffsetAzi;

	float fInvalid = ::g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

	// reader buffer
	CXPrestackDataReaderBuff readerBuff;
	vector<CXSeismicDataVolume*> vecTmpDV;
	if (!m_vecInDV.empty())
		vecTmpDV = m_vecInDV;
	else
		vecTmpDV.push_back(m_pAziDV);

	readerBuff.Init(vecTmpDV, m_nMaxNK, m_nMaxFold / vecTmpDV.size());


	//output
	vector<float> vecOutBani(nK), vecOutAZi(nK);
	for (int i = 0; i < nI; ++i)
	{
		int iMin = qBound(0, i - iHalfDI, nI - 1);
		int iMax = qBound(0, i + iHalfDI, nI - 1);

		for (int j = 0; j < nJ; ++j)
		{
			if (IsStopped())
				return;
			else
			{
				this->EmitUpdateProgress(i*nJ+j, nI*nJ);
			}

			int jMin = qBound(0, j - iHalfDJ, nJ - 1);
			int jMax = qBound(0, j + iHalfDJ, nJ - 1);

			// stacking
			int iCount = 0;
			mapPosition.clear();

			// retrieve data
			for (int iI = iMin; iI <= iMax; ++iI)
			{
				for (int iJ = jMin; iJ <= jMax; ++iJ)
				{
					int iInlineNum = iInlineMin + iInlineInc*iI;
					int iXlineNum = iXlineMin + iXlineInc*iJ;

					
					double dSamplingStart1, dSamplingEnd1, dSamplingRate1;

					if (!m_vecInDV.empty())
					{
						for (int iDV = 0; iDV < m_vecInDV.size(); ++iDV)
						{
							vecOffsetAzi.clear();
							if ( //!m_vecInDV[iDV]->GetTraceDataAt(iInlineNum, iXlineNum, &vecGatherBuff[0], vecOffsetAzi))
								!readerBuff.Read(iDV, iInlineNum, iXlineNum, &vecGatherBuff[0], vecOffsetAzi))
							{
								this->EmitGeneralErrorMsg("Cannot read the seismic data from the disk.");
								return;
							}
							int nDVNK = m_vecInDV[iDV]->GetSamplingQty();
							m_vecInDV[iDV]->GetSamplingRange(dSamplingStart1, dSamplingEnd1, dSamplingRate1);

							int iTraceOffset = static_cast<int>((dSamplingStart - dSamplingStart1) / dSamplingRate + 0.01);
							int nTraceNum = vecOffsetAzi.size() / 2;
							for (int iTrace = 0; iTrace < nTraceNum; ++iTrace)
							{
								mapPosition.insert(qMakePair(vecAzimuth[iDV], vecOffsetAzi[2 * iTrace]), iCount);
								memcpy(&vecBuffer[0] + iCount*nK, &vecGatherBuff[0] + iTrace*nDVNK + iTraceOffset, sizeof(float)*nK);
								++iCount;
							}
						}
					}
					else // azimuth data volume
					{
						vecOffsetAzi.clear();
						if (//!m_pAziDV->GetTraceDataAt(iInlineNum, iXlineNum, &vecGatherBuff[0], vecOffsetAzi))
							!readerBuff.Read(0, iInlineNum, iXlineNum, &vecGatherBuff[0], vecOffsetAzi))
						{
							this->EmitGeneralErrorMsg("Cannot read the seismic data from the disk.");
							return;
						}

						int nDVNK = m_pAziDV->GetSamplingQty();
						m_pAziDV->GetSamplingRange(dSamplingStart1, dSamplingEnd1, dSamplingRate1);

						int iTraceOffset = static_cast<int>((dSamplingStart - dSamplingStart1) / dSamplingRate + 0.01);
						int nTraceNum = vecOffsetAzi.size() / 2;
						for (int iTrace = 0; iTrace < nTraceNum; ++iTrace)
						{
							mapPosition.insert(qMakePair(vecOffsetAzi[2 * iTrace + 1], vecOffsetAzi[2 * iTrace]), iCount);
							memcpy(&vecBuffer[0] + iCount*nK, &vecGatherBuff[0] + iTrace*nDVNK + iTraceOffset, sizeof(float)*nK);
							++iCount;
						}
					}
				}
			}

			// stacking
			QMultiMap<QPair<float, float>, int>::iterator it;
			mapBuff.clear();
			for (it = mapPosition.begin(); it != mapPosition.end(); ++it)
			{
				QList<int> listPos = mapPosition.values(it.key());		
				int nPosNum = listPos.size();
				 
				double dSum;				
				float fValue;
				int iTotalNum;
				qint64 iBufferIndex = listPos[0] * nK;
				for (int k = 0; k < nK; ++k)
				{
					dSum = 0;
					iTotalNum = 0;
					
					for (int iIndex = 0; iIndex < nPosNum; ++iIndex)
					{
						fValue = vecBuffer[listPos[iIndex] * nK + k];
						if (fValue == 0 ||qAbs(fValue - fInvalid) < fInvalidEPS)
							continue;

						dSum += fValue;
						++iTotalNum;
					}
					if (iTotalNum == 0)
						vecBuffer[iBufferIndex + k] = fInvalid;
					else
						vecBuffer[iBufferIndex + k] = static_cast<float>(dSum / iTotalNum);					
				}

				mapBuff.insert(it.key(), &vecBuffer[iBufferIndex]);
			}

			// calculating
			int mMaxSize = mapBuff.size();

			//  matrices
			vector<double> G(mMaxSize * 4), X(4), d(mMaxSize);


			QMap<QPair<float, float>, float*>::iterator it2;
			for (int k = 0; k < nK; ++k)
			{
				// determine m size
				int m = 0;
				for (it2 = mapBuff.begin(); it2 != mapBuff.end(); ++it2)
				{
					float* pData = it2.value();
					if (qAbs(pData[k] - fInvalid) > fInvalidEPS)
						++m;
				}

				if (m < nMinimumFold)
				{
					vecOutBani[k] = 0.f;
					vecOutAZi[k] = 0.f;
					continue;
				}

				// first column
				for (int ii = 0; ii < m; ++ii)
					G[ii] = 1.f;

				// set matrices
				int iMapIndex = 0;
				for (it2 = mapBuff.begin(); it2 != mapBuff.end(); ++it2)
				{
					float* pData = it2.value();
					if (qAbs(pData[k] - fInvalid) < fInvalidEPS)
						continue;

					d[iMapIndex] = pData[k];

					float fAzi = it2.key().first*M_RAD;
					float fInc = it2.key().second*M_RAD;
					float fsin2 = SQR(sin(fInc));
					G[m + iMapIndex] = fsin2;
					G[2 * m + iMapIndex] = -cos(2 * fAzi)*fsin2;
					G[3 * m + iMapIndex] = -sin(2 * fAzi)*fsin2;
					++iMapIndex;
				}

				// G*X = d
				LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m, 4, 1, &G[0], m, &d[0], m);

				// output
				vecOutBani[k] = sqrt(SQR(d[2]) + SQR(d[3]));
				float fOutAzi2 = atan2(d[2], d[3])*M_DEG;
				if (fOutAzi2 < 0.f)
					fOutAzi2 += 360.f;

				float fOutAzi = fOutAzi2 / 2.f;
				fOutAzi -= 90.f;
				if (fOutAzi < 0.f)
					fOutAzi += 360.f;

				vecOutAZi[k] = fOutAzi;
			}

			// write to the disk
			if (!m_vecWriter[0]->Append(nK, &vecOutBani[0]) ||
				!m_vecWriter[1]->Append(nK, &vecOutAZi[0]))
			{
				this->EmitGeneralErrorMsg("Cannot write the data to the disk.");
				return;
			}
		}
	}

}

void CXThreadFractureAVO::RunThread()
{
	mkl_set_num_threads(m_pPara->GetCPUNumber());	

	this->EmitSetWindowName("AVAz Analysis");	
	this->EmitSetTaskName("Calculating");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();


	if (!_GetReaders())
		return;


	if (!_CreateDV())
		return;

	_CalcPostack();
}



