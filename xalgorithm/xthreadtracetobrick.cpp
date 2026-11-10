#pragma warning( push ,0 )
#include <QApplication>
#include <QMap>

#include "xthreadtracetobrick.h"
#include "xseismicdatavolume.h"
#include "xsysteminfo.h"
#include "xbrickoctree.h"
#include "xconcurrentparameter.h"
#include "xproject.h"
#include "xseismicutmtool.h"
#include <cmath>
#include <cassert>

#include "xutility.h"
#include "xglobal.h"

#pragma warning( pop )

bool ReadOneBlock(QFile& qFile, qint64 nOffset, int nDataSize, int nSampleSize, float* pData)
{
	unsigned char* pMemMapData = qFile.map(nOffset, nDataSize*nSampleSize);
	if (NULL == pMemMapData)
		return false;

	memcpy(pData, (float*)pMemMapData, nDataSize*nSampleSize);
	qFile.unmap(pMemMapData);
	return true;
}

void ConvertFloatToChar(float* pFloatBuff, unsigned char* pCharBuff, int nSize, float fMin, float fMax, float fInvalid, float fInvalidEPS, bool bDiscrete)
{
	if (fMin == fMax)
	{
		memset(pCharBuff, 0, sizeof(unsigned char)*nSize);
		return;
	}

	if (bDiscrete)
	{
		for (int i = 0; i<nSize; ++i)
		{
			if (qAbs(pFloatBuff[i] - fInvalid) < fInvalidEPS)
			{
				pCharBuff[i] = 255;
			}
			else
			{
				pCharBuff[i] = static_cast<unsigned char>(pFloatBuff[i]);
			}
		}
	}
	else
	{
		float fFactor = 254.0f / (fMax - fMin);
		for (int i = 0; i<nSize; ++i)
		{
			if (qAbs(pFloatBuff[i] - fInvalid) < fInvalidEPS)
			{
				pCharBuff[i] = 255;
			}
			else
			{
				if (pFloatBuff[i] >= fMax)
					pCharBuff[i] = 254;
				else if (pFloatBuff[i] <= fMin)
					pCharBuff[i] = 0;
				else
				{
					pCharBuff[i] = static_cast<char>((pFloatBuff[i] - fMin)*fFactor);
				}
			}
		}
	}
}

CXThreadTraceToBrick::CXThreadTraceToBrick(CXSeismicDataVolume* pDV)
	:m_pDV(pDV)
{
	m_pMemMapData = NULL;

	m_pOctree = NULL;

	m_pSectionBuffer = NULL;
	m_pWrittenMap = NULL;
	m_pOneTileData = NULL;

	m_2DTileData = NULL;

	if (NULL != m_pDV)
	{
		_InitParameter();

		QString strTraceFileName = m_pDV->GetTraceFileName();
		QString strBrickFileName = m_pDV->GetBrickFileName();
		m_qTraceFile.setFileName(strTraceFileName);
		m_qFile.setFileName(strBrickFileName);

		LockRead(m_pDV);
	}
}

CXThreadTraceToBrick::~CXThreadTraceToBrick()
{
	this->wait();

	UnlockRead(m_pDV);

	if (IsStopped())
	{
		m_qFile.close();
		QString strBrickFileName = m_qFile.fileName();
		QFile::remove(strBrickFileName);
	}

	_ReleaseMemory();
}

void CXThreadTraceToBrick::_InitParameter()
{
	// Invalid data
	m_fInvalid = ::g_dInvalidData;
	m_fInvalidEPS = ::GetEPSofInvalidData(m_fInvalid);
	m_bDiscrete = false;

	m_nIDim = m_pDV->GetInlineQty();
	m_nJDim = m_pDV->GetXlineQty();
	m_nKDim = m_pDV->GetSamplingQty();

	// Tile dimension
	m_nITileDim = m_nIDim > 64 ? 64 : m_nIDim;
	m_nJTileDim = 64;
	m_nKTileDim = 64;
	m_nBrickSampleSize = sizeof(char);
	m_nOneTileSize = m_nITileDim*m_nJTileDim*m_nKTileDim;

	// Get tile numers along each direction
	if (m_nIDim == m_nITileDim)
		m_nITile = 1;
	else
		m_nITile = (int)ceil(1.0*m_nIDim/m_nITileDim);

	m_nJTile = (int)ceil(1.0*m_nJDim / m_nJTileDim);
	m_nKTile = (int)ceil(1.0*m_nKDim / m_nKTileDim);

	// Max and min values
	// Get the data min and max according to percentage (in case signed char loses the resolution)
	double dMin, dMax;
	m_pDV->GetDataRange(dMin, dMax);
	m_fDataMin = (float)dMin;
	m_fDataMax = (float)dMax;
}

void CXThreadTraceToBrick::_ReleaseMemory()
{
	if (m_pMemMapData)
	{
		m_qTraceFile.unmap((unsigned char*)m_pMemMapData);
		m_pMemMapData = NULL;
		m_qTraceFile.close();
	}

	if (m_pOctree)			{ delete m_pOctree; m_pOctree = NULL; }

	if (m_pOneTileData)		{ delete[]m_pOneTileData; m_pOneTileData = NULL; }
	if (m_pSectionBuffer)	{ delete[]m_pSectionBuffer; m_pSectionBuffer = NULL; }
	if (m_pWrittenMap)		{ delete[]m_pWrittenMap; m_pWrittenMap = NULL; }

	if (m_2DTileData)		{ NXUtility::Free2DArray<unsigned char>(m_2DTileData, m_nBlockTileNum); m_2DTileData = NULL; }

}

bool CXThreadTraceToBrick::_Initialization()
{
	if (NULL == m_pDV)
	{
		EmitGeneralErrorMsg("The target seismic data volume has been deleted.");
		return false;
	}

	// Get the head size of the trace file
	m_nTraceFileHeadSize = 0;
	m_nTraceSampleSize = sizeof(float);

	// Open the trace file
	if (!m_qTraceFile.open(QIODevice::ReadOnly))
	{
		QString strErrorMsg = "Cannot open the trace file. Please make sure the file exists";
		EmitGeneralErrorMsg(strErrorMsg);
		return false;
	}

	// Tell if have enough disk space
	if (!_HasEnoughDiskSpace())
		return false;


	// Set memory map to speed up data reading
	m_pMemMapData = m_qTraceFile.map(m_nTraceFileHeadSize, m_nJDim*m_nKDim*m_nTraceSampleSize);

	// Set the octree
	m_pOctree = new CXBrickOctree(m_nITile, m_nJTile, m_nKTile);

	return true;
}

bool CXThreadTraceToBrick::_HasEnoughDiskSpace()
{
	// Get the available disk space
	qint64 nAvailable = CXSystemInfo::GetFreeDiskSpace(::GetProjectPath());
	qint64 nBrickSize = CXSystemInfo::GetBrickFileSize(m_nJDim, m_nIDim, m_nKDim, sizeof(char), 64);
	qint64 nAdditional = nBrickSize + 50 * 1000 * 1000 - nAvailable;

	if (nAdditional > 0)
	{
		QString strAdditionSpace = CXSystemInfo::GetSpaceSizeString(nAdditional);
		EmitDiskSpaceNotEnough(strAdditionSpace);
		return false;
	}
	else
	{
		return true;
	}
}

void CXThreadTraceToBrick::RunThread()
{
	// If stopped
	if (IsStopped())
		return;

	this->EmitResetProgressBar();

	// Initialization
	if (!_Initialization())
		return;

	// Set dialog title name and sub-task names
	QString strWindowName, strTaskName;
	strWindowName = "Converting Trace File to Brick File";
	strTaskName = "Waiting for another conversion process to finish...";
	this->EmitSetWindowName(strWindowName);
	this->EmitSetTaskName(strTaskName);
	qApp->processEvents();

	// Allow only one LDM converter thread running
	forever
	{
		if (CXConcurrentParameter::m_semaphoreSliceLDMConversion.tryAcquire(1, 500))
		break;
		else
		{
			if (IsStopped())
			{
				return;
			}
		}
	}

	strTaskName = "Allocating Disk Space (" + m_pDV->GetObjectName() + ")";
	this->EmitSetTaskName(strTaskName);
	this->EmitStartComputing();
	qApp->processEvents();

	// Allocate the disp space
	if (!_AllocateDiskSpace())
	{
		CXConcurrentParameter::m_semaphoreSliceLDMConversion.release();
		return;
	}

	// Converting	
	strTaskName = "Converting... (" + m_pDV->GetObjectName() + ")";
	this->EmitSetTaskName(strTaskName);
	this->EmitResetProgressBar();
	qApp->processEvents();

	if (!_BrickConverting())
	{
		CXConcurrentParameter::m_semaphoreSliceLDMConversion.release();
		return;
	}

	CXConcurrentParameter::m_semaphoreSliceLDMConversion.release();
	_ReleaseMemory();
}

bool CXThreadTraceToBrick::_AllocateDiskSpace()
{
	if (!m_qFile.open(QIODevice::ReadWrite))
	{
		QString strErrorMsg = "Unable to open a file to write!";
		EmitGeneralErrorMsg(strErrorMsg);
		return false;
	}

	m_pOneTileData = new unsigned char[m_nOneTileSize];
	memset(m_pOneTileData, 0, m_nOneTileSize*m_nBrickSampleSize);
	int nOriginalTileNum = m_pOctree->GetOriginalTileNum();

	for (int i = 0; i<nOriginalTileNum; ++i)
	{
		if (IsStopped())
			return false;
		else
		{
			this->EmitUpdateProgress(i, nOriginalTileNum);
		}

		m_qFile.write((char*)m_pOneTileData, m_nOneTileSize*m_nBrickSampleSize);
	}

	return true;
}

bool CXThreadTraceToBrick::_BrickConverting()
{
	int nTotalTileNum = m_pOctree->GetOriginalTileNum();

	//Alocating memory
	m_pWrittenMap = new bool[nTotalTileNum];
	for (int i = 0; i<nTotalTileNum; ++i)
		m_pWrittenMap[i] = false;

	try
	{
		m_pSectionBuffer = new float[m_nJDim*m_nKDim];
	}
	catch (std::bad_alloc)
	{
		EmitMemoryNotEnough();
		return false;
	}

	qint64 nMegaSize = 1000 * 1000;
	qint64 nFreeMemory = ((qint64)CXSystemInfo::GetFreeMemory())*nMegaSize;
	qint64 nMaxFreeMemory = qMin(nFreeMemory * 9 / 10, nFreeMemory - 150 * nMegaSize);

	int nITileNum = m_nITile == 1 ? 1 : 2;
	int nJTileNum = m_nJTile;
	if (nMaxFreeMemory < nITileNum*nJTileNum*m_nKTile*m_nOneTileSize*m_nBrickSampleSize)
	{
		if (nJTileNum <= 2)
		{
			EmitMemoryNotEnough();
			return false;
		}
		else
		{
			nJTileNum = 4;
			while (nMaxFreeMemory > nITileNum*nJTileNum*m_nKTile*m_nOneTileSize*m_nBrickSampleSize)
			{
				nJTileNum += 2;
			}
			nJTileNum -= 2;
		}
	}


	// Allocate memory to hold the tiles
	m_nBlockTileNum = nITileNum*nJTileNum*m_nKTile;
	m_2DTileData = NXUtility::New2DArray<unsigned char>(m_nBlockTileNum, (int)m_nOneTileSize);
	if (NULL == m_2DTileData)
	{
		EmitMemoryNotEnough();
		return false;
	}

	// Initialize the parameters for the progress bar
	m_iCurrent = 0;
	m_nTotalStep = m_pOctree->GetTotalTileNum() * 2 + m_nITile*m_nITileDim * 2;

	return _ConvertWithBlock(nITileNum, nJTileNum);
}

bool CXThreadTraceToBrick::_ConvertWithBlock(int nITileNum, int nJTileNum)
{
	int iTileMin, iTileMax, jTileMin, jTileMax;
	int nIBlockNum = (m_nITile - 1) / nITileNum + 1;
	int nJBlockNum = (m_nJTile - 1) / nJTileNum + 1;

	for (int iIBlock = 0; iIBlock<nIBlockNum; ++iIBlock)
	{
		iTileMin = iIBlock*nITileNum;
		iTileMax = (iIBlock + 1)*nITileNum - 1;
		if (iTileMax >= m_nITile)
			iTileMax = m_nITile - 1;

		for (int iJBlock = 0; iJBlock<nJBlockNum; ++iJBlock)
		{
			jTileMin = iJBlock*nJTileNum;
			jTileMax = (iJBlock + 1)*nJTileNum - 1;
			if (jTileMax >= m_nJTile)
				jTileMax = m_nJTile - 1;

			if (!_ConvertOneBlock(iTileMin, iTileMax, jTileMin, jTileMax))
				return false;
		}
	}

	return true;
}

bool CXThreadTraceToBrick::_ConvertOneBlock(int iTileMin, int iTileMax, int jTileMin, int jTileMax)
{
	// Compute the range of j for the given tile block (jjjMin, jjjMax)
	int iMin, iMax, jMin, jMax, kMin, kMax;
	int jjjMin, jjjMax, jjjDataMin, jjjDataMax;
	_TileIJKToPosition(iTileMin, jTileMin, 0, iMin, iMax, jjjMin, jMax, kMin, kMax);
	_TileIJKToPosition(iTileMax, jTileMax, 0, iMin, iMax, jMin, jjjMax, kMin, kMax);
	jjjDataMin = jjjMin;
	jjjDataMax = jjjMax >= m_nJDim ? m_nJDim - 1 : jjjMax;

	// Set the data for each tile
	int jIntersectMax, kIntersectMax;
	int iTileIndex;
	for (int iTile = iTileMin; iTile <= iTileMax; ++iTile)
	{
		_TileIJKToPosition(iTile, 0, 0, iMin, iMax, jMin, jMax, kMin, kMax);

		for (int i = iMin; i <= iMax; ++i)
		{
			//progress bar
			if (IsStopped())
				return false;
			else
			{
				m_iCurrent += 2;
				this->EmitUpdateProgress(m_iCurrent, m_nTotalStep);		
			}

			if (i < m_nIDim)
			{
				if (!_ReadSectionData(i, jjjMin, jjjDataMax, m_pSectionBuffer))
				{
					this->EmitGeneralErrorMsg("Cannot read the trace file.");
					return false;
				}
			}

			int iOffset = (i - iMin)*m_nJTileDim*m_nKTileDim;
			for (int jTile = jTileMin; jTile <= jTileMax; ++jTile)
			{
				for (int kTile = 0; kTile<m_nKTile; ++kTile)
				{
					if (IsStopped())
						return false;

					iTileIndex = (iTile - iTileMin)*(jTileMax - jTileMin + 1)*m_nKTile + (jTile - jTileMin)*m_nKTile + kTile;
					assert(iTileIndex >= 0 && iTileIndex < m_nBlockTileNum);
					unsigned char* pTileData = m_2DTileData[iTileIndex];

					// The position of the tile
					_TileIJKToPosition(iTile, jTile, kTile, iMin, iMax, jMin, jMax, kMin, kMax);

					// In case the part of the tile is out of the seismic data range
					jIntersectMax = jMax < jjjDataMax ? jMax : jjjDataMax;
					kIntersectMax = kMax < m_nKDim ? kMax : (m_nKDim - 1);
					int nLength = kIntersectMax - kMin + 1;

					// K direction
					for (int j = jMin; j <= jIntersectMax; ++j)
					{
						assert(iOffset + (j - jMin)*m_nKTileDim >= 0 && iOffset + (j - jMin)*m_nKTileDim < m_nOneTileSize);
						ConvertFloatToChar(m_pSectionBuffer + (j - jjjMin)*m_nKDim + kMin, pTileData + iOffset + (j - jMin)*m_nKTileDim, nLength, m_fDataMin, m_fDataMax, m_fInvalid, m_fInvalidEPS, m_bDiscrete);

						if (kIntersectMax < kMax)
						{
							assert(iOffset + (j - jMin)*m_nKTileDim + (kIntersectMax - kMin) >= 0 && iOffset + (j - jMin)*m_nKTileDim + (kIntersectMax - kMin) < m_nOneTileSize);
							unsigned char cValue = pTileData[iOffset + (j - jMin)*m_nKTileDim + (kIntersectMax - kMin)];
							for (int k = kIntersectMax + 1; k <= kMax; ++k)
							{
								assert(iOffset + (j - jMin)*m_nKTileDim + (k - kMin) >= 0 && iOffset + (j - jMin)*m_nKTileDim + (k - kMin) < m_nOneTileSize);
								pTileData[iOffset + (j - jMin)*m_nKTileDim + (k - kMin)] = cValue;
							}
						}
					}

					// J direction
					if (jIntersectMax < jMax)
					{
						assert(iOffset + (jIntersectMax - jMin)*m_nKTileDim >= 0 && iOffset + (jIntersectMax - jMin)*m_nKTileDim < m_nOneTileSize);
						unsigned char* pTileOffsetData = pTileData + iOffset + (jIntersectMax - jMin)*m_nKTileDim;
						for (int j = jIntersectMax + 1; j<jMax; ++j)
						{
							assert(iOffset + (j - jMin)*m_nKTileDim + m_nBrickSampleSize*m_nKTileDim >= 0 && iOffset + (j - jMin)*m_nKTileDim + m_nBrickSampleSize*m_nKTileDim < m_nOneTileSize);

							memcpy(pTileData + iOffset + (j - jMin)*m_nKTileDim, pTileOffsetData, m_nBrickSampleSize*m_nKTileDim);
						}
					}

				} //kTile
			}// jTile			
		}
	} //iTile

	// Write the raw data and first low-resolution tiles
	return _WriteTiles(iTileMin, iTileMax, jTileMin, jTileMax, 0, m_nKTile - 1);
}

bool CXThreadTraceToBrick::_WriteTiles(int iTileMin, int iTileMax, int jTileMin, int jTileMax, int kTileMin, int kTileMax)
{
	// Get the map from data IDs to block IDs
	QMap<int, int> mapDataIDToBlockID;
	int iBlockID = 0;
	int iDataID;
	qint64 iTileID;	
	for (int iTile = iTileMin; iTile <= iTileMax; ++iTile)
	{
		for (int jTile = jTileMin; jTile <= jTileMax; ++jTile)
		{
			for (int kTile = kTileMin; kTile <= kTileMax; ++kTile)
			{
				iTileID = m_pOctree->GetTileIDFromTileIJK(iTile, jTile, kTile);
				iDataID = m_pOctree->GetDataIDFromTileID(iTileID);
				mapDataIDToBlockID.insert(iDataID, iBlockID);

				iBlockID++;
			}
		}
	}


	// Write the raw tile data (highest resolution)
	int nLowResolutionTileNum = m_pOctree->GetTotalTileNum() - m_pOctree->GetOriginalTileNum();
	QMap<int, int>::const_iterator itor;
	qint64 offset;
	for (itor = mapDataIDToBlockID.begin(); itor != mapDataIDToBlockID.end(); ++itor)
	{
		iDataID = itor.key();
		iBlockID = itor.value();

		unsigned char* pTileData = m_2DTileData[iBlockID];
		offset = m_nOneTileSize*(iDataID - nLowResolutionTileNum)*m_nBrickSampleSize;
		m_qFile.seek(offset);

		//progress bar
		if (IsStopped())
			return false;
		else
		{
			m_iCurrent += 2;
			this->EmitUpdateProgress(m_iCurrent, m_nTotalStep);	
		}

		m_qFile.write((char*)pTileData, m_nBrickSampleSize*m_nOneTileSize);
		m_pWrittenMap[iDataID - nLowResolutionTileNum] = true;
	}


	return true;
}

bool CXThreadTraceToBrick::_ReadSectionData(int iInlineIndex, int iXlineMinInd, int iXlineMaxInd, float* pBuffer)
{
	qint64 nSectionSize = m_nJDim*m_nKDim*m_nTraceSampleSize;
	qint64 nOffset = m_nTraceFileHeadSize + nSectionSize*iInlineIndex + iXlineMinInd*m_nKDim*m_nTraceSampleSize;
	qint64 nDataSize = (iXlineMaxInd - iXlineMinInd + 1)*m_nKDim;

	return ReadOneBlock(m_qTraceFile, nOffset, nDataSize, m_nTraceSampleSize, pBuffer);
}

void CXThreadTraceToBrick::_TileIJKToPosition(int iTile, int jTile, int kTile, int& iMin, int& iMax, int& jMin, int& jMax, int& kMin, int& kMax)
{
	kMin = m_nKTileDim*kTile;
	kMax = m_nKTileDim*(kTile + 1) - 1;

	jMin = m_nJTileDim*jTile;
	jMax = m_nJTileDim*(jTile+1) - 1;

	iMin = m_nITileDim*iTile;
	iMax = m_nITileDim*(iTile + 1) - 1;
}


