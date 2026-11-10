#include <QFile>
#include <qvector.h>
#include "xseismicirregularreader.h"
#include "xseismicutmtool.h"
#include "xseismicdatavolume.h"
#include "xseismicsection.h"
#include "xeventconsole.h"

CXSeismicIrregularReader::CXSeismicIrregularReader(unsigned short iMaxFold, CXSeismicUTMTool *pUTM, QString sFileName, int iGatherNum)
{
	m_iMaxFold = iMaxFold;
	m_bAzimuth = false;
	m_pUTM = pUTM;
	m_sFileName = sFileName;
	m_pBuff = NULL;

	if (m_pUTM)
		m_iGatherNum = m_pUTM->GetNI() * m_pUTM->GetNJ();
	else
		m_iGatherNum = iGatherNum;

	//	Is it an azimuth volume?
	QFile qFile(m_sFileName);
	qint64 iFileSize = qFile.size();

	if (iFileSize >= m_iGatherNum * (10 + 4 * m_iMaxFold))
		m_bAzimuth = true;

	m_iMaxOffset = 0;
}

CXSeismicIrregularReader::~CXSeismicIrregularReader()
{
	if (m_pBuff)
		delete[]m_pBuff;
}

bool CXSeismicIrregularReader::SaveToFile()
{
	if (!m_pBuff)
		return false;

	QFile qFile(m_sFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return false;
	qint64 iGatherSize = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	qint64 iTotalSize = iGatherSize * m_iGatherNum;
	if (qFile.write(m_pBuff, iTotalSize) != iTotalSize)
		return false;

	qFile.close();

	return true;
}

unsigned short CXSeismicIrregularReader::GetMinOffset()
{
	if (m_iMaxOffset == 0)
	{
		//	It means not populated yet, populate it now.
		GetBuffer();
	}

	return m_iMinOffset;
}

short CXSeismicIrregularReader::GetMinAzimuth()
{
	if (m_iMaxOffset == 0)
	{
		//	It means not populated yet, populate it now.
		GetBuffer();
	}

	return m_iMinAzi;
}

short CXSeismicIrregularReader::GetMaxAzimuth()
{
	if (m_iMaxOffset == 0)
	{
		//	It means not populated yet, populate it now.
		GetBuffer();
	}

	return m_iMaxAzi;
}

unsigned short CXSeismicIrregularReader::GetMaxOffset()
{
	if (m_iMaxOffset == 0)
	{
		//	It means not populated yet, populate it now.
		GetBuffer();
	}

	return m_iMaxOffset;
}

char* CXSeismicIrregularReader::GetBuffer()
{
	if (m_pBuff)
		return m_pBuff;

	qint64 i, j, iGatherSize = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	qint64 iGatherNum = m_iGatherNum;
	m_pBuff = new char[iGatherNum * iGatherSize];
	memset(m_pBuff, 0, iGatherNum * iGatherSize);

	QFile qFile(m_sFileName);
	if (qFile.open(QIODevice::ReadOnly))
	{
		qFile.read(m_pBuff, iGatherNum * iGatherSize);
		qFile.close();
	}

	//	Statistics.
	m_iMaxOffset = 0;
	m_iMinOffset = 65530;
	if (m_bAzimuth)
	{
		m_iMaxAzi = -360;
		m_iMinAzi = 360;
		for (i = 0; i < iGatherNum; i++)
		{
			short *pSh = (short *)(m_pBuff + i * iGatherSize);
			if (pSh[4] == 0)
				continue;

			for (j = 0; j < pSh[4]; j++)
			{
				m_iMaxOffset = m_iMaxOffset > pSh[5 + j * 2] ? m_iMaxOffset : pSh[5 + j * 2];
				m_iMinOffset = m_iMinOffset < pSh[5 + j * 2] ? m_iMinOffset : pSh[5 + j * 2];
				m_iMaxAzi = m_iMaxAzi > pSh[5 + j * 2 + 1] ? m_iMaxAzi : pSh[5 + j * 2 + 1];
				m_iMinAzi = m_iMinAzi < pSh[5 + j * 2 + 1] ? m_iMinAzi : pSh[5 + j * 2 + 1];
			}
		}
	}
	else
	{
		for (i = 0; i < iGatherNum; i++)
		{
			short *pSh = (short *)(m_pBuff + i * iGatherSize);
			for (j = 0; j < pSh[4]; j++)
			{
				m_iMaxOffset = m_iMaxOffset > pSh[5 + j] ? m_iMaxOffset : pSh[5 + j];
				m_iMinOffset = m_iMinOffset < pSh[5 + j] ? m_iMinOffset : pSh[5 + j];
			}
		}
	}

	return m_pBuff;
}

int CXSeismicIrregularReader::GetXlineTraceQty(int iInline)
{
	if (iInline <= 0 || !m_pUTM)
		return 0;

	int ii, jj;
	m_pUTM->LineToIJ(iInline, 1, ii, jj);
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	char *pBuff = GetBuffer();
	pBuff += (ii * m_pUTM->GetNJ() * iLength);

	int i, iQty = 0;
	for (i = 0; i < m_pUTM->GetNJ(); i++)
	{
		short *pSh = (short *)pBuff;
		iQty += pSh[4];
		pBuff += iLength;
	}

	return iQty;
}

int CXSeismicIrregularReader::GetInlineTraceQty(int iXline)
{
	if (iXline <= 0 || !m_pUTM)
		return 0;

	int ii, jj;
	m_pUTM->LineToIJ(1, iXline, ii, jj);
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;;
	char *pBuff = GetBuffer();
	pBuff += (jj * iLength);

	int i, iQty = 0;
	for (i = 0; i < m_pUTM->GetNI(); i++)
	{
		short *pSh = (short *)pBuff;
		iQty += pSh[4];
		pBuff += (iLength * m_pUTM->GetNJ());
	}

	return iQty;
}

void CXSeismicIrregularReader::GetFoldMap(unsigned short *pFoldMap)
{
	char *pBuff = GetBuffer();
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;

	for (int i = 0; i < m_iGatherNum; i++)
	{
		short *pSh = (short *)pBuff;
		pFoldMap[i] = pSh[4];
		pBuff += iLength;
	}
}

int CXSeismicIrregularReader::GetSectionTraceQty(CXSeismicSection *pSection)
{
	int iQty = 0, i, i1, i2, j, j1, j2;
	if (!pSection)
		return iQty;

	int iSTrace, iETrace;
	pSection->GetSectionRange(iSTrace, iETrace);
	if (pSection->GetSectionType() == eInlineSection)
	{
		if (iSTrace == -1 || iETrace == -1)
		{
			iSTrace = m_pUTM->GetFirstCrossline();
			iETrace = m_pUTM->GetLastCrossline();

			pSection->SetSectionRange(iSTrace, iETrace);
		}

		bool bChanged = false;
		if (iSTrace < m_pUTM->GetFirstCrossline())
		{
			iSTrace = m_pUTM->GetFirstCrossline();
			bChanged = true;
		}

		if (iETrace > m_pUTM->GetLastCrossline())
		{
			iETrace = m_pUTM->GetLastCrossline();
			bChanged = true;
		}

		if (bChanged)
		{
			pSection->SetSectionRange(iSTrace, iETrace);

			CXProcessEvent processEvent;
			pSection->AddEvent(EDataChanged);
		}

		m_pUTM->LineToIJ(pSection->GetSectionNumber(), iSTrace, i, j1);
		m_pUTM->LineToIJ(pSection->GetSectionNumber(), iETrace, i, j2);

		qint64 iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;;
		qint64 iOffset = iLength * (i * m_pUTM->GetNJ() + j1);
		char *pBuff = GetBuffer();
		pBuff += iOffset;

		for (j = j1; j <= j2; j++)
		{
			short *pSh = (short *)pBuff;
			iQty += pSh[4];
			pBuff += iLength;
		}
	}
	else if (pSection->GetSectionType() == eCrosslineSection)
	{
		if (iSTrace == -1 || iETrace == -1)
		{
			iSTrace = m_pUTM->GetFirstInline();
			iETrace = m_pUTM->GetLastInline();

			pSection->SetSectionRange(iSTrace, iETrace);
		}

		bool bChanged = false;
		if (iSTrace < m_pUTM->GetFirstInline())
		{
			iSTrace = m_pUTM->GetFirstInline();
			bChanged = true;
		}

		if (iETrace > m_pUTM->GetLastInline())
		{
			iETrace = m_pUTM->GetLastInline();
			bChanged = true;
		}

		if (bChanged)
		{
			pSection->SetSectionRange(iSTrace, iETrace);

			CXProcessEvent processEvent;
			pSection->AddEvent(EDataChanged);
		}

		m_pUTM->LineToIJ(iSTrace, pSection->GetSectionNumber(), i1, j);
		m_pUTM->LineToIJ(iETrace, pSection->GetSectionNumber(), i2, j);

		int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;;
		char *pBuff = GetBuffer();
		pBuff += ((i1 * m_pUTM->GetNI() + j) * iLength);

		for (i = i1; i <= i2; i++)
		{
			short *pSh = (short *)pBuff;
			iQty += pSh[4];
			pBuff += (iLength * m_pUTM->GetNJ());
		}
	}

	return iQty;
}

int CXSeismicIrregularReader::GetRandomSectionTraceQty(vector<int>& vecInline, vector<int>& vecXline)
{
	if (!m_pUTM)
		return 0;

	int i, iSize = vecInline.size(), iQty = 0;
	int ii, jj;
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;;
	for (i = 0; i < iSize; i++)
	{
		if (m_pUTM->LineToIJ(vecInline[i], vecXline[i], ii, jj))
		{
			char *pBuff = GetBuffer();
			pBuff = pBuff + ((ii * m_pUTM->GetNJ() + jj) * iLength);
			short *pSh = (short *)pBuff;
			iQty += pSh[4];
		}
	}

	return iQty;
}

bool CXSeismicIrregularReader::ReadInline(CXSeismicObject *pDV, int iInline, float* pDataBuffer, SKETraceInfo* pTraceInfo)
{
	//	Get the trace file name.
	QFile qTraceFile(pDV->GetTraceFileName());
	if (!qTraceFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	int iSampleQty = pDV->GetSamplingQty();

	int ii, jj, iXline = 1;
	m_pUTM->LineToIJ(iInline, iXline, ii, jj);
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	char *pInfoBuff = GetBuffer();
	pInfoBuff += (ii * m_pUTM->GetNJ() * iLength);
	qint64 iPos = *(qint64 *)pInfoBuff;

	int iTraceQty = GetXlineTraceQty(iInline);

	qTraceFile.seek(iPos);
	qTraceFile.read((char *)pDataBuffer, iTraceQty * iSampleQty * 4);

	qTraceFile.close();

	int i, j, iQty = 0, iIDX = 0;
	double dX, dY;
	for (j = 0; j < m_pUTM->GetNJ(); j++)
	{
		m_pUTM->IJToLine(ii, j, iInline, iXline);
		m_pUTM->IJToXY(ii, j, dX, dY);

		short *pSh = (short *)pInfoBuff;
		iQty = pSh[4];

		for (i = 0; i < iQty; i++)
		{
			pTraceInfo[iIDX].m_iLine = iInline;
			pTraceInfo[iIDX].m_iCDP = iXline;
			pTraceInfo[iIDX].m_dX = dX;
			pTraceInfo[iIDX].m_dY = dY;
			pTraceInfo[iIDX].m_iOffset = pSh[5 + i * (1 + m_bAzimuth)];
			pTraceInfo[iIDX].m_iAzimuth = m_bAzimuth ? pSh[5 + i * 2 + 1] : 0;

			iIDX++;
		}

		pInfoBuff += iLength;
	}

	return true;
}

bool CXSeismicIrregularReader::ReadInline(CXSeismicObject *pDV, int iInline, int iXlineMinNum, int iXlineMaxNum, double dStart, double dEnd, float* pDataBuffer, SKETraceInfo* pTraceInfo)
{
	//	Get the trace file name.
	QString sTFile = pDV->GetTraceFileName();
	QFile qTraceFile(pDV->GetTraceFileName());
	if (!qTraceFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	double dSZ, dEZ, dStep;
	int iSampleQty = pDV->GetSamplingQty();
	pDV->GetSamplingRange(dSZ, dEZ, dStep);
	int iSampleOffset = (dStart - dSZ) / dStep;
	int iSampleNum = (dEnd - dStart) / dStep + 1;

	int ii, jj, iXline = iXlineMinNum;
	int iXlineInc = m_pUTM->GetCrosslineIncrement();
	m_pUTM->LineToIJ(iInline, iXline, ii, jj);
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	char *pInfoBuff = GetBuffer();
	pInfoBuff += ((ii * m_pUTM->GetNJ() + jj) * iLength);
	qint64 iPos = *(qint64 *)pInfoBuff;
	float *pBuffer = new float[iSampleQty * m_iMaxFold];
	int iMaxTraceQty = ((iXlineMaxNum - iXlineMinNum) / iXlineInc + 1) * m_iMaxFold;

	qTraceFile.seek(iPos);

	int i, j, iQty = 0, iIDX = 0;
	double dX, dY;
	for (iXline = iXlineMinNum; iXline <= iXlineMaxNum; iXline += iXlineInc)
	{
		m_pUTM->LineToXY(iInline, iXline, dX, dY);

		short *pSh = (short *)pInfoBuff;
		iQty = pSh[4];
		qint64 iRes = qTraceFile.read((char *)pBuffer, iQty * iSampleQty * 4);

		for (i = 0; i < iQty; i++)
		{
			pTraceInfo[iIDX].m_iLine = iInline;
			pTraceInfo[iIDX].m_iCDP = iXline;
			pTraceInfo[iIDX].m_dX = dX;
			pTraceInfo[iIDX].m_dY = dY;
			pTraceInfo[iIDX].m_iOffset = pSh[5 + i * (1 + m_bAzimuth)];
			pTraceInfo[iIDX].m_iAzimuth = m_bAzimuth ? pSh[5 + i * 2 + 1] : 0;

			memcpy(pDataBuffer, pBuffer + i * iSampleQty + iSampleOffset, iSampleNum * sizeof(float));

			pDataBuffer += iSampleNum;
			iIDX++;
		}

		pInfoBuff += iLength;
	}

	qTraceFile.close();
	delete[]pBuffer;
	return true;
}

bool CXSeismicIrregularReader::ReadXline(CXSeismicObject *pDV, int iXline, float* pDataBuffer, SKETraceInfo* pTraceInfo)
{
	//	Get the trace file name.
	QFile qTraceFile(pDV->GetTraceFileName());
	if (!qTraceFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	int iSampleQty = pDV->GetSamplingQty();

	int iInline = 1, ii, jj;
	m_pUTM->LineToIJ(iInline, iXline, ii, jj);
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	char *pInfoBuff = GetBuffer();
	pInfoBuff += (jj * iLength);

	int i, j, iQty = 0, iIDX = 0;
	double dX, dY;
	qint64 iPos = 0;
	for (i = 0; i < m_pUTM->GetNI(); i++)
	{
		m_pUTM->IJToLine(i, jj, iInline, iXline);
		m_pUTM->IJToXY(i, jj, dX, dY);

		short *pSh = (short *)pInfoBuff;
		iQty = pSh[4];
		iPos = *(qint64 *)pInfoBuff;

		qTraceFile.seek(iPos);
		qTraceFile.read((char *)pDataBuffer, iQty * iSampleQty * 4);

		for (j = 0; j < iQty; j++)
		{
			pTraceInfo[iIDX].m_iLine = iInline;
			pTraceInfo[iIDX].m_iCDP = iXline;
			pTraceInfo[iIDX].m_dX = dX;
			pTraceInfo[iIDX].m_dY = dY;
			pTraceInfo[iIDX].m_iOffset = pSh[5 + j * (1 + m_bAzimuth)];
			pTraceInfo[iIDX].m_iAzimuth = m_bAzimuth ? pSh[5 + j * 2 + 1] : 0;

			iIDX++;
		}

		pInfoBuff += (iLength * m_pUTM->GetNJ());
		pDataBuffer += (iQty * iSampleQty);
	}

	qTraceFile.close();
	return true;
}

bool CXSeismicIrregularReader::ReadXline(CXSeismicObject *pDV, int iXline, int iInlineMinNum, int iInlineMaxNum, double dStart, double dEnd, float* pDataBuffer, SKETraceInfo* pTraceInfo)
{
	//	Get the trace file name.
	QFile qTraceFile(pDV->GetTraceFileName());
	if (!qTraceFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	double dSZ, dEZ, dStep;
	int iSampleQty = pDV->GetSamplingQty();
	pDV->GetSamplingRange(dSZ, dEZ, dStep);
	int iSampleOffset = (dStart - dSZ) / dStep;
	int iSampleNum = (dEnd - dStart) / dStep + 1;

	int ii, jj, iInline = iInlineMinNum;
	int iInlineInc = m_pUTM->GetInlineIncrement();
	m_pUTM->LineToIJ(iInline, iXline, ii, jj);
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	char *pInfoBuff = GetBuffer();
	pInfoBuff += ((ii * m_pUTM->GetNJ() + jj) * iLength);
	qint64 iPos = *(qint64 *)pInfoBuff;
	float *pBuffer = new float[iSampleQty * m_iMaxFold];
	int iMaxTraceQty = ((iInlineMaxNum - iInlineMinNum) / iInlineInc + 1) * m_iMaxFold;

	qTraceFile.seek(iPos);

	int i, j, iQty = 0, iIDX = 0;
	double dX, dY;
	for (iInline = iInlineMinNum; iInline <= iInlineMaxNum; iInline += iInlineInc)
	{
		m_pUTM->LineToXY(iInline, iXline, dX, dY);

		short *pSh = (short *)pInfoBuff;
		iQty = pSh[4];
		qTraceFile.read((char *)pBuffer, iQty * iSampleQty * 4);

		for (i = 0; i < iQty; i++)
		{
			pTraceInfo[iIDX].m_iLine = iInline;
			pTraceInfo[iIDX].m_iCDP = iXline;
			pTraceInfo[iIDX].m_dX = dX;
			pTraceInfo[iIDX].m_dY = dY;
			pTraceInfo[iIDX].m_iOffset = pSh[5 + i * (1 + m_bAzimuth)];
			pTraceInfo[iIDX].m_iAzimuth = m_bAzimuth ? pSh[5 + i * 2 + 1] : 0;

			memcpy(pDataBuffer, pBuffer + i * iSampleQty + iSampleOffset, iSampleNum * sizeof(float));

			pDataBuffer += iSampleNum;
			iIDX++;
		}

		pInfoBuff += (iLength * m_pUTM->GetNJ());
	}

	qTraceFile.close();
	delete[]pBuffer;
	return true;
}

bool CXSeismicIrregularReader::ReadRandomSection(CXSeismicObject *pDV, vector<int>& vecInline, vector<int>& vecXline, float* pDataBuffer, SKETraceInfo* pTraceInfo)
{
	//	Get the trace file name.
	QFile qTraceFile(pDV->GetTraceFileName());
	if (!qTraceFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	int iSampleQty = pDV->GetSamplingQty();

	qint64 iPos;
	int ii, jj;
	int i, j, iSize = vecInline.size(), iQty = 0, iIDX = 0;
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	double dX, dY;

	for (i = 0; i < iSize; i++)
	{
		if (m_pUTM->LineToIJ(vecInline[i], vecXline[i], ii, jj))
		{
			m_pUTM->LineToXY(vecInline[i], vecXline[i], dX, dY);
			char *pInfoBuff = GetBuffer();
			pInfoBuff = pInfoBuff + ((ii * m_pUTM->GetNJ() + jj) * iLength);
			iPos = *(qint64 *)pInfoBuff;
			short *pSh = (short *)pInfoBuff;
			iQty = pSh[4];

			qTraceFile.seek(iPos);
			qTraceFile.read((char *)pDataBuffer, iQty * iSampleQty * 4);

			pDataBuffer += (iQty * iSampleQty);

			for (j = 0; j < iQty; j++)
			{
				pTraceInfo[iIDX].m_iLine = vecInline[i];
				pTraceInfo[iIDX].m_iCDP = vecXline[i];
				pTraceInfo[iIDX].m_dX = dX;
				pTraceInfo[iIDX].m_dY = dY;
				pTraceInfo[iIDX].m_iOffset = pSh[5 + j * (1 + m_bAzimuth)];
				pTraceInfo[iIDX].m_iAzimuth = m_bAzimuth ? pSh[5 + j * 2 + 1] : 0;

				iIDX++;
			}
		}
	}
			
	return true;
}

///@brief	Get the trace number of the specified CDP.
int CXSeismicIrregularReader::GetTraceNumberAt(int iInline, int iXline)
{
	int ii, jj;
	if (!m_pUTM->LineToIJ(iInline, iXline, ii, jj))
		return 0;

	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	char *pBuff = GetBuffer();
	pBuff += ((ii * m_pUTM->GetNJ() + jj) * iLength);
	short *pSh = (short *)pBuff;

	return pSh[4];
}

///@brief	Get the trace data and offset/azimuth info of the specified CDP.
///			The space of pData should be pre-allocated and mananged by the caller.
bool CXSeismicIrregularReader::GetTraceDataAt(CXSeismicDataVolume *pDV, int iInline, int iXline, float *pData, QVector<float>& vecOffsetAziPair)
{
	//	Get the trace file name.
	QFile qTraceFile(pDV->GetTraceFileName());
	if (!qTraceFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	int iSampleQty = pDV->GetSamplingQty();

	int ii, jj;
	m_pUTM->LineToIJ(iInline, iXline, ii, jj);
	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	char *pInfoBuff = GetBuffer();
	pInfoBuff += ((ii * m_pUTM->GetNJ() + jj) * iLength);
	qint64 iPos = *(qint64 *)pInfoBuff;

	short *pSh = (short *)pInfoBuff;
	int iTraceQty = pSh[4];

	qTraceFile.seek(iPos);
	qTraceFile.read((char *)pData, iTraceQty * iSampleQty * 4);

	qTraceFile.close();

	for (int i = 0; i < iTraceQty; i++)
	{
		vecOffsetAziPair << pSh[5 + i * (1 + m_bAzimuth)];
		vecOffsetAziPair << (m_bAzimuth ? pSh[5 + i * 2 + 1] : 0.);
	}

	return true;
}

void CXSeismicIrregularReader::GetOffset(int iInline, int iXline, vector<int>& vecOffset)
{
	int ii, jj;
	if (!m_pUTM->LineToIJ(iInline, iXline, ii, jj))
		return;

	int iLength = 10 + 2 * (1 + m_bAzimuth) * m_iMaxFold;
	char *pInfoBuff = GetBuffer();
	pInfoBuff += ((ii * m_pUTM->GetNJ() + jj) * iLength);
	qint64 iPos = *(qint64 *)pInfoBuff;

	short *pSh = (short *)pInfoBuff;
	int iTraceQty = pSh[4];

	for (int i = 0; i < iTraceQty; i++)
	{
		vecOffset.push_back(pSh[5 + i * (1 + m_bAzimuth)]);
	}
}

bool CXSeismicIrregularReader::ContainsAzimuthOnly()
{
	GetBuffer();

	return (m_iMinOffset == m_iMaxOffset && m_iMinAzi != m_iMaxAzi);
}