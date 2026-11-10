#pragma warning( push ,0 )
#include <cmath>
#include <QFile>
#include <cassert>
#include "xbrickreader.h"
#include "xutility.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xbrickoctree.h"
#include "xseismicdatavolume.h"
#include "xfunctiontemplate.h"
#pragma warning( pop )

CXBrickReader::CXBrickReader(CXSeismicDataVolume* pDV)
{
	assert(pDV);

	m_bOpen = false;
	m_pOctree = NULL;

	m_nSampleSize = 1;
	m_nMaxTileNum = 256;

	if (pDV)
	{
		_Init(pDV);
	}
	if (m_bOpen)
	{
		_CalcTileNum();
		m_pOctree = new CXBrickOctree(m_nITileNum, m_nJTileNum, m_nKTileNum);
	}
}

CXBrickReader::~CXBrickReader()
{
	if (m_pOctree)
		delete m_pOctree;

	QMap<qint64, unsigned char*>::const_iterator itor;
	for (itor = m_mapTileIDToData.begin(); itor != m_mapTileIDToData.end(); ++itor)
	{
		void* pData = itor.value();
		if (pData)
			delete[]pData;
	}
	m_mapTileIDToData.clear();

	m_vector.clear();
}

void CXBrickReader::_Init(CXSeismicDataVolume* pDV)
{
	QString strFileBrickFile = pDV->GetBrickFileName();
	if (!QFile::exists(strFileBrickFile))
		return;

	m_nIDim = pDV->GetInlineQty();
	m_nJDim = pDV->GetXlineQty();
	m_nKDim = pDV->GetSamplingQty();

	// tile dimension
	m_nKTileDim = m_nJTileDim = m_nITileDim = 64;
	if (m_nIDim < m_nJTileDim)
	{
		m_nITileDim = m_nIDim;
	}

	//open file
	m_qFile.setFileName(strFileBrickFile);
	m_bOpen = m_qFile.open(QIODevice::ReadOnly);
}

void CXBrickReader::_CalcTileNum()
{
	// Get tile numers along each direction
	m_nKTileNum = (int)ceil(1.0*m_nKDim / m_nKTileDim);
	m_nJTileNum = (int)ceil(1.0*m_nJDim / m_nJTileDim);
	if (m_nIDim == m_nITileDim)
		m_nITileNum = 1;
	else
		m_nITileNum = (int)ceil(1.0*m_nIDim / m_nITileDim);

	m_nTileSize = m_nKTileDim*m_nJTileDim*m_nITileDim;
}

unsigned char CXBrickReader::ReadData(int iTimeInd, int iInlineInd, int iXlineInd)
{
	if (!m_bOpen)
		return 255;

	if (!_IsLineInRange(iInlineInd, iXlineInd, iTimeInd))
		return 255;

	int iI, iJ, iK;
	iI = iInlineInd;
	iJ = iXlineInd;
	iK = iTimeInd;

	int iTile, jTile, kTile;
	_LineIndexToTileIJK(iI, iJ, iK, iTile, jTile, kTile);
	qint64 iTileID = m_pOctree->GetTileIDFromTileIJK(iTile, jTile, kTile);

	if (!m_mapTileIDToData.contains(iTileID))
	{
		if (!_ReadOneTile(iTileID))
			return 255;
	}

	QMap<qint64, unsigned char*>::iterator itor = m_mapTileIDToData.find(iTileID);
	if (itor == m_mapTileIDToData.end())
		return 255;
	else
	{
		unsigned char* pTileData = itor.value();
		int iMin, iMax, jMin, jMax, kMin, kMax;
		_TileIJKToPosition(iTile, jTile, kTile, iMin, iMax, jMin, jMax, kMin, kMax);

		int nOffset = (iI - iMin)*m_nJTileDim*m_nKTileDim + (iJ - jMin)*m_nKTileDim + (iK - kMin);
		return pTileData[nOffset];
	}
}

bool CXBrickReader::ReadData(int iXLineInd, int iInlineInd, int iTimeMinInd, int iTimeMaxInd, unsigned char *pBuff)
{
	if (!m_bOpen)
		return false;

	if (!_IsLineInRange(iInlineInd, iXLineInd, iTimeMinInd) ||
		!_IsLineInRange(iInlineInd, iXLineInd, iTimeMaxInd))
		return false;

	int iI = iInlineInd;
	int iJ = iXLineInd;
	int kTraceMin = iTimeMinInd;
	int kTraceMax = iTimeMaxInd;
	int iK = kTraceMin;
	while (iK <= kTraceMax)
	{
		int iTile, jTile, kTile;
		_LineIndexToTileIJK(iI, iJ, iK, iTile, jTile, kTile);
		qint64 iTileID = m_pOctree->GetTileIDFromTileIJK(iTile, jTile, kTile);

		if (!m_mapTileIDToData.contains(iTileID))
		{
			if (!_ReadOneTile(iTileID))
				return false;
		}

		QMap<qint64, unsigned char*>::iterator itor = m_mapTileIDToData.find(iTileID);
		if (itor == m_mapTileIDToData.end())
			return false;
		else
		{
			unsigned char* pTileData = itor.value();
			int iMin, iMax, jMin, jMax, kMin, kMax;
			_TileIJKToPosition(iTile, jTile, kTile, iMin, iMax, jMin, jMax, kMin, kMax);

			int length = qMin((kMax - iK + 1), (kTraceMax - iK + 1));
			int nOffset = (iI - iMin)*m_nJTileDim*m_nKTileDim + (iJ - jMin)*m_nKTileDim + (iK - kMin);

			
			for (int iii = 0; iii < length; ++iii)
			{
				pBuff[iK - kTraceMin + iii] = *(pTileData + nOffset + iii);
			}			

			iK += length;
		}
	}

	return true;
}

bool CXBrickReader::_ReadOneTile(qint64 iTileID)
{
	if (!m_bOpen)
		return false;

	// Tell if need allocate the new memory
	unsigned char* pData = NULL;
	if (m_mapTileIDToData.size() < m_nMaxTileNum)
	{
		try
		{
			pData = new unsigned char[m_nTileSize];
		}
		catch (std::bad_alloc)
		{
			return false;
		}
	}
	else
	{
		pData = m_mapTileIDToData.value(m_vector.front());
		m_mapTileIDToData.remove(m_vector.front());
		m_vector.pop_front();
	}

	// Read data
	int iDataID = m_pOctree->GetDataIDFromTileID(iTileID);
	int nLowResTileNum = m_pOctree->GetTotalTileNum() - m_pOctree->GetOriginalTileNum();

	qint64 nOffset = m_nTileSize*(iDataID - nLowResTileNum)*m_nSampleSize;
	unsigned char* pMapData = m_qFile.map(nOffset, m_nTileSize*m_nSampleSize);
	memcpy((unsigned char*)pData, pMapData, m_nTileSize*m_nSampleSize);
	m_qFile.unmap(pMapData);

	m_mapTileIDToData.insert(iTileID, pData);
	m_vector.push_back(iTileID);

	return true;
}

bool CXBrickReader::_IsLineInRange(int iInlineInd, int iXlineInd, int iTimeInd)
{
	return (IsBound(iInlineInd, 0, m_nIDim - 1) &&
			IsBound(iXlineInd, 0, m_nJDim - 1) &&
			IsBound(iTimeInd, 0, m_nKDim - 1));
}

void CXBrickReader::_TileIJKToPosition(int iTile, int jTile, int kTile, int& iMin, int& iMax, int& jMin, int& jMax, int& kMin, int& kMax)
{
	kMin = m_nKTileDim*kTile;
	kMax = m_nKTileDim*(kTile + 1) - 1;

	jMin = m_nJTileDim*jTile;
	jMax = m_nJTileDim*(jTile + 1) - 1;

	iMin = m_nITileDim*iTile;
	iMax = m_nITileDim*(iTile + 1) - 1;
}

void CXBrickReader::_LineIndexToTileIJK(int iI, int iJ, int iK, int& iTile, int& jTile, int& kTile)
{
	kTile = iK / m_nKTileDim;
	jTile = iJ / m_nJTileDim;
	iTile = iI / m_nITileDim;
}