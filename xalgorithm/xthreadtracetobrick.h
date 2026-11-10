#ifndef XTHREADTRACETOBRICK_H
#define XTHREADTRACETOBRICK_H

#include <QFile>
#include <QStringList>
#include "xbasethread.h"
#include "xalgorithm_global.h"

class CXSeismicDataVolume;
class CXBrickOctree;

/**
* @class CXThreadTraceToBrick provided in the file "kethreadtracetobrick.h"
* @brief The Class provides a thread to do brick conversion
*
* @date 11/5/2015
* @bug	No Known bugs so far
*/
class XALGORITHM_EXPORT CXThreadTraceToBrick : public CXBaseThread
{
public:
	/// Constructor.
	CXThreadTraceToBrick(CXSeismicDataVolume* pDV);

	/// Destructor.	
	~CXThreadTraceToBrick();

protected:
	///@brief Reimplement the run 
	virtual void RunThread();

private:
	// Init parameter
	void _InitParameter();

	// Initialization
	bool _Initialization();
	// Tell if disk space is enough
	bool _HasEnoughDiskSpace();
	// Allocate disk space	
	bool _AllocateDiskSpace();

	// LDM converting
	bool _BrickConverting();
	bool _ConvertWithBlock(int nITileNum, int nPartialJTileNum);
	bool _ConvertOneBlock(int iTileMin, int iTileMax, int jTileMin, int jTileMax);
	inline void _TileIJKToPosition(int iTile, int jTile, int kTile, int& iMin, int& iMax, int& jMin, int& jMax, int& kMin, int& kMax);

	// Write the raw data and first level low-resolution tile data
	bool _WriteTiles(int iTileMin, int iTileMax, int jTileMin, int jTileMax, int kTileMin, int kTileMax);

	// Read one section data from the data volume
	bool _ReadSectionData(int iInlineIndex, int iXlineMinInd, int iXlineMaxInd, float* pBuffer);

	// Release the memory
	void _ReleaseMemory();

private:
	// The target data volume
	CXSeismicDataVolume* m_pDV;
	QStringList m_strListGTCTags;
	float m_fDataMin;
	float m_fDataMax;
	QFile m_qTraceFile;

	// Ouput LDM file
	QFile m_qFile;

	float m_fInvalid;
	float m_fInvalidEPS;
	bool m_bDiscrete;

private:	
	int m_nTraceSampleSize;
	int m_nBrickSampleSize;
	unsigned int m_nTraceFileHeadSize;

private:
	unsigned char* m_pMemMapData;

	CXBrickOctree* m_pOctree;

	void* m_pTmpBuffer;

	float* m_pSectionBuffer;
	bool* m_pWrittenMap;
	unsigned char* m_pOneTileData;
	unsigned char** m_2DTileData;

private:
	// Data dimension
	int m_nIDim;
	int m_nJDim;
	int m_nKDim;

	// Tile dimension
	int m_nITile;
	int m_nJTile;
	int m_nKTile;
	int m_nITileDim;
	int m_nJTileDim;
	int m_nKTileDim;
	// Tile size
	qint64 m_nOneTileSize;

	//Block Tile Num
	int m_nBlockTileNum;

private:
	//progress bar
	qint64 m_nTotalStep, m_iCurrent;
};

#endif // KETHREADTRACETOBRICK_H
