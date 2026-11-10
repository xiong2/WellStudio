#pragma warning( push ,0 )
#include <cstring>
#include "xbrickoctree.h"
#pragma warning( pop )


CXBrickOctree::CXBrickOctree(int nITile, int nJTile, int nKTile)
{
	m_nITile = nITile;
	m_nJTile = nJTile;
	m_nKTile = nKTile;

	m_pTileID = NULL;

	_Init();

	_CalculateDataIDs();
}

CXBrickOctree::~CXBrickOctree()
{
	if (m_pTileID)
		delete[]m_pTileID;
	m_pTileID = NULL;
}

void CXBrickOctree::_Init()
{
	int nDim = qMax(qMax(m_nITile, m_nJTile), m_nKTile);

	m_nDimTile = 1;
	m_nLevel = 0;
	while (m_nDimTile < nDim)
	{
		m_nDimTile <<= 1;
		m_nLevel++;
	}

	m_nLowTileNum = 1;
	m_nLowTileNum <<= (3 * m_nLevel);
	m_nLowTileNum = (m_nLowTileNum - 1) / (8 - 1);
}

bool CXBrickOctree::GetTileIJKFromTileID(qint64 iTileID, int& iTile, int& jTile, int& kTile)
{
	if (iTileID < m_nLowTileNum)
	{
		iTile = -1;
		jTile = -1;
		kTile = -1;
		return false;
	}
	else
	{
		iTile = 0;
		jTile = 0;
		kTile = 0;
	}

	qint64 iParentTileID;
	int offset;
	int nTime = 1;
	for (int iLevel = m_nLevel; iLevel > 0; --iLevel)
	{
		iParentTileID = (iTileID - 1) >> 3;
		offset = iTileID - (iParentTileID << 3) - 1;

		if (4 & offset)
			iTile += nTime;
		if (2 & offset)
			jTile += nTime;
		if (1 & offset)
			kTile += nTime;

		nTime <<= 1;
		iTileID = iParentTileID;
	}

	return true;
}

qint64 CXBrickOctree::GetTileIDFromTileIJK(int iTile, int jTile, int kTile)
{
	int offset;
	qint64 iTileID;
	int nTime = 1 << (m_nLevel - 1);
	iTileID = 0;
	for (int iLevel = 1; iLevel <= m_nLevel; ++iLevel)
	{
		offset = 0;
		if (iTile - nTime >= 0)
		{
			offset += 4;
			iTile -= nTime;
		}

		if (jTile - nTime >= 0)
		{
			offset += 2;
			jTile -= nTime;
		}

		if (kTile - nTime >= 0)
		{
			offset += 1;
			kTile -= nTime;
		}

		nTime >>= 1;
		iTileID = (iTileID << 3) + 1 + offset;
	}

	return iTileID;
}

void CXBrickOctree::_CalculateDataIDs()
{
	std::vector<qint64*> vecVecTileID;
	std::vector<int> vecTileNumAtLevel;
	int numBlocks = m_nITile*m_nJTile*m_nKTile;

	qint64* pTmp = new qint64[numBlocks];
	// First loop at the level (m_nLevel)

	qint64 iTileID;
	int iBlockID;
	int index = 0;
	for (int iTile = 0; iTile<m_nITile; ++iTile)
	{
		for (int jTile = 0; jTile<m_nJTile; ++jTile)
		{
			for (int kTile = 0; kTile<m_nKTile; ++kTile)
			{
				iTileID = GetTileIDFromTileIJK(iTile, jTile, kTile);
				pTmp[index++] = iTileID;
			}
		}
	}

	std::sort(pTmp, pTmp + index);
	vecVecTileID.push_back(pTmp);
	vecTileNumAtLevel.push_back(index);

	// The rest levels
	for (int iLevel = m_nLevel - 1; iLevel >= 0; --iLevel)
	{
		int nDaughterTileNum = vecTileNumAtLevel.back();
		qint64* pDaughterTmp = vecVecTileID.back();
		qint64* pParentTmp = new qint64[nDaughterTileNum];

		index = 0;
		qint64 iParentID;
		for (int i = 0; i<nDaughterTileNum; ++i)
		{
			iParentID = (pDaughterTmp[i] - 1) >> 3;

			if (index == 0 || pParentTmp[index - 1] != iParentID)
				pParentTmp[index++] = iParentID;
		}

		std::sort(pParentTmp, pParentTmp + index);
		vecVecTileID.push_back(pParentTmp);
		vecTileNumAtLevel.push_back(index);
	}

	// Put together
	int nTotalTiles = 0;
	for (int i = 0; i<vecTileNumAtLevel.size(); ++i)
		nTotalTiles += vecTileNumAtLevel.at(i);

	m_pTileID = new qint64[nTotalTiles];

	m_nNumTotalTileAtAllLevel = 0;
	for (int i = vecTileNumAtLevel.size() - 1; i >= 0; --i)
	{
		qint64* pData = vecVecTileID.at(i);
		int nTileNum = vecTileNumAtLevel.at(i);

		memcpy(m_pTileID + m_nNumTotalTileAtAllLevel, pData, sizeof(qint64)*nTileNum);
		m_nNumTotalTileAtAllLevel += nTileNum;
	}

	m_vecTileNumAtLevel.resize(m_nLevel + 1);
	for (int i = 0; i<m_nLevel + 1; ++i)
		m_vecTileNumAtLevel[i] = vecTileNumAtLevel[m_nLevel - i];


	for (int i = 0; i<vecVecTileID.size(); ++i)
	{
		qint64* pData = vecVecTileID.at(i);
		delete[]pData;
	}
	vecVecTileID.clear();
}

int CXBrickOctree::GetOriginalTileNum()
{
	return (int) m_vecTileNumAtLevel[m_nLevel];
}


int CXBrickOctree::GetDataIDFromTileID(qint64 iTileID)
{
	int iLow = 0;
	int iHigh = m_nNumTotalTileAtAllLevel - 1;
	int iMiddle;
	qint64 iMiddleTileID;

	if (iTileID < m_pTileID[iLow] || iTileID > m_pTileID[iHigh])
		return -1;

	while (iLow != iHigh)
	{
		iMiddle = (iLow + iHigh) / 2;
		iMiddleTileID = m_pTileID[iMiddle];

		if (iMiddleTileID < iTileID)
		{
			iLow = iMiddle + 1;
		}
		else if (iMiddleTileID == iTileID)
		{
			iLow = iMiddle;
			break;
		}
		else if (iMiddleTileID > iTileID)
		{
			iHigh = iMiddle;
		}
	}

	if (m_pTileID[iLow] == iTileID)
		return iLow;
	else
		return -1;
}

qint64 CXBrickOctree::GetTileIDFromDataID(int iDataID)
{
	if (iDataID < 0 || iDataID >= m_nNumTotalTileAtAllLevel)
		return -1;

	else
		return m_pTileID[iDataID];
}

int CXBrickOctree::GetDaughterTileIDFromTileID(qint64 iParentTileID, qint64 daughterTileID[8])
{
	for (int i = 0; i<8; ++i)
		daughterTileID[i] = -1;

	// If the parent tile lies in the deepest level or there is no coresponding data ID
	if (iParentTileID >= m_nLowTileNum || GetDataIDFromTileID(iParentTileID) == -1)
	{
		return 0;
	}
	else
	{
		int nNum = 0;
		for (int i = 1; i <= 8; ++i)
		{
			qint64 iDaughtTileID = (iParentTileID << 3) + i;
			if (GetDataIDFromTileID(iDaughtTileID) != -1)
			{
				daughterTileID[i - 1] = iDaughtTileID;
				nNum++;
			}
			else
				daughterTileID[i - 1] = -1;
		}

		return nNum;
	}
}

qint64 CXBrickOctree::GetParentTileID(qint64 iTileID)
{
	if (iTileID <= 0)
		return -1;
	else
	{
		return (iTileID - 1) >> 3;
	}
}

int CXBrickOctree::GetParentDataID(int iDataID)
{
	qint64 iTileID = GetTileIDFromDataID(iDataID);
	if (iTileID == -1)
		return -1;
	else
	{
		qint64 iParentTileID = GetParentTileID(iTileID);
		if (iParentTileID == -1)
			return -1;
		else
			return GetDataIDFromTileID(iParentTileID);
	}
}

void CXBrickOctree::GetVecAccumulatedTileNum(std::vector<qint64>& vecAccumulatedTileNum)
{
	vecAccumulatedTileNum.resize(m_vecTileNumAtLevel.size());
	std::copy(m_vecTileNumAtLevel.begin(), m_vecTileNumAtLevel.end(), vecAccumulatedTileNum.begin());

	for (int i = 0; i<m_vecTileNumAtLevel.size(); ++i)
	{
		if (i>0)
			vecAccumulatedTileNum.at(i) += vecAccumulatedTileNum.at(i - 1);
	}
}

void CXBrickOctree::GetVecTileNum(std::vector<qint64>& vecTileNum)
{
	vecTileNum.resize(m_vecTileNumAtLevel.size());

	std::copy(m_vecTileNumAtLevel.begin(), m_vecTileNumAtLevel.end(), vecTileNum.begin());
}

int CXBrickOctree::GetDaughterDataIDFromDataID(int iParentDataID, int daughterDataID[8])
{
	qint64 iParentTileID = this->GetTileIDFromDataID(iParentDataID);

	qint64 daughterTileID[8];
	GetDaughterTileIDFromTileID(iParentTileID, daughterTileID);

	int nNum = 0;
	for (int i = 0; i<8; ++i)
	{
		if (daughterTileID[i] == -1)
			daughterDataID[i] = -1;
		else
		{
			daughterDataID[i] = this->GetDataIDFromTileID(daughterTileID[i]);
			nNum++;
		}
	}

	return nNum;
}


