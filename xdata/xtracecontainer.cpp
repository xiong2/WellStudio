#include "xtracecontainer.h"
#include "xseismicdatavolume.h"
#include "xglobal.h"

CXTraceContainer::CXTraceContainer(int iTimeStep, int nZ, std::vector<int> vecOffset, std::vector<int> vecAzi, bool bOffsetFirst, QString sDataFile, QString sTIFile)
	: m_iTimeStep(iTimeStep), m_nZ(nZ), m_bOffsetFirst(bOffsetFirst), m_vecOffset(vecOffset), m_vecAzi(vecAzi)
{
	m_qFileData.setFileName(sDataFile);
	m_qFileData.open(QIODevice::WriteOnly);

	m_qFileTI.setFileName(sTIFile);
	m_qFileTI.open(QIODevice::WriteOnly);

	int iNumTrace = m_vecOffset.size() * m_vecAzi.size() / 9;
	m_pVector = new QVector<SKEOneTrace>[iNumTrace];
	m_pTIBuffer = new SKETraceInfo[iNumTrace];
	m_pDataBuffer = new float[m_nZ / m_iTimeStep];

	int i, j, iCount = 0;
	if (bOffsetFirst)
	{
		for (i = 0; i < m_vecOffset.size(); i += 3)
		{
			for (j = 0; j < m_vecAzi.size(); j += 3)
			{
				m_pTIBuffer[iCount].m_iOffset = m_vecOffset[i + 2];
				m_pTIBuffer[iCount].m_iAzimuth = m_vecAzi[j + 2];
				iCount++;
			}
		}
	}
	else
	{
		for (j = 0; j < m_vecAzi.size(); j += 3)
		{
			for (i = 0; i < m_vecOffset.size(); i += 3)
			{
				m_pTIBuffer[iCount].m_iOffset = m_vecOffset[i + 2];
				m_pTIBuffer[iCount].m_iAzimuth = m_vecAzi[j + 2];
				iCount++;
			}
		}
	}
}

CXTraceContainer::~CXTraceContainer()
{
	delete[]m_pVector;
	delete[]m_pTIBuffer;
	delete[]m_pDataBuffer;

	m_qFileData.close();
	m_qFileTI.close();
}

bool CXTraceContainer::AddOneTrace(SKEOneTrace oneTrace)
{
	int i, j, iCount = 0;
	for (i = 0; i < m_vecOffset.size(); i += 3)
	{
		if (oneTrace.m_pTraceInfo->m_iOffset < m_vecOffset[i] || oneTrace.m_pTraceInfo->m_iOffset > m_vecOffset[i + 1])
		{
			iCount += (m_vecAzi.size() / 3);
			continue;
		}

		for (j = 0; j < m_vecAzi.size(); j += 3)
		{
			if (oneTrace.m_pTraceInfo->m_iAzimuth >= m_vecAzi[j] && oneTrace.m_pTraceInfo->m_iAzimuth <= m_vecAzi[j + 1])
			{
				m_pVector[iCount].append(oneTrace);
			}

			iCount++;
		}
	}

	return true;
}

void CXTraceContainer::StackOneCDP()
{
	int i, j, k, iTCount = 0, iCount, iLen = m_nZ / m_iTimeStep;
	int iNumTrace = m_vecOffset.size() * m_vecAzi.size() / 9;
	char *pIBuffer = new char[10 + 4 * iNumTrace];
	memset(pIBuffer, 0, 10 + 4 * iNumTrace);
	qint64 *pLong = (qint64 *)pIBuffer;
	short *pSh = (short *)pIBuffer;

	pLong[0] = m_qFileData.pos();
	for (i = 0; i < iNumTrace; i++)
	{
		if (m_pVector[i].isEmpty())
			continue;

		pSh[5 + 2 * iTCount] = m_pTIBuffer[i].m_iOffset;
		pSh[5 + 2 * iTCount + 1] = m_pTIBuffer[i].m_iAzimuth;
		iTCount++;

		for (k = 0; k < iLen; k ++)
		{
			iCount = 0;
			float fSum = 0.;
			m_pDataBuffer[k] = 0.;

			for (j = 0; j < m_pVector[i].size(); j++)
			{
				if (m_pVector[i][j].m_pData[k * m_iTimeStep] != 0. && m_pVector[i][j].m_pData[k * m_iTimeStep] != ::g_dInvalidData)
				{
					fSum += m_pVector[i][j].m_pData[k * m_iTimeStep];
					iCount++;
				}
			}

			if (iCount > 0)
				m_pDataBuffer[k] = fSum / iCount;
		}

		//	Write one trace to the files.
		m_qFileData.write((char *)m_pDataBuffer, sizeof(float) * iLen);

		//	Clear the buff.
		m_pVector[i].clear();
	}

	pSh[4] = iTCount;
	m_qFileTI.write(pIBuffer, 10 + 4 * iNumTrace);
		
	delete[]pIBuffer;
}