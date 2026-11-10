#ifndef XBRICKREADER_H
#define XBRICKREADER_H

#include <QString>
#include <QMap>
#include <QVector>
#include "xdata_global.h"
#include <QFile>

class QFile;
class CXBrickOctree;
class CXSeismicDataVolume;

/**
* @class CXBrickReader in the file "kebrickreader.h"
* @brief The class implements the methods to reader brick file
*
* @author Yong Shu
* @date 11/6/2015
* @see
*/
class XDATA_EXPORT CXBrickReader
{
public:
	CXBrickReader(CXSeismicDataVolume* pDV);
	virtual ~CXBrickReader();

	///@brief Tell if the file manager is ready
	bool IsOpen() { return m_bOpen; }

	///@brief Read part of a trace. Should allocate enough space for pBuff by the user. The data range is between [0,254]
	///@brief The value 255 represents invalid data.
	bool ReadData(int iXLineInd, int iInlineInd, int iTimeMinInd, int iTimeMaxInd, unsigned char *pBuff);

	///@brief Read one point by index. The data range is between [0,254]
	///@brief The value 255 represents invalid data.
	unsigned char ReadData(int iTimeInd, int iInlineInd, int iXlineInd);

private:
	// Init
	void _Init(CXSeismicDataVolume* pDV);

	// Calculate the number of the tiles
	void _CalcTileNum();
	// Read one tile data
	bool _ReadOneTile(qint64 iTileID);
	// Tell if line index is valid
	bool _IsLineInRange(int iInlineInd, int iXlineInd, int iTimeInd);

	inline void _LineIndexToTileIJK(int iI, int iJ, int iK, int& iTile, int& jTile, int& kTile);
	inline void _TileIJKToPosition(int iTile, int jTile, int kTile, int& iMin, int& iMax, int& jMin, int& jMax, int& kMin, int& kMax);


private:
	QVector<qint64> m_vector;
	QMap<qint64, unsigned char*> m_mapTileIDToData;

	int m_nMaxTileNum;

	QFile m_qFile;

	qint64 m_nTileSize;

	CXBrickOctree* m_pOctree;

	bool m_bOpen;
private:
	// Data dimension
	int m_nIDim;
	int m_nJDim;
	int m_nKDim;

	// Tile dimension
	int m_nITileNum;
	int m_nJTileNum;
	int m_nKTileNum;
	int m_nITileDim;
	int m_nJTileDim;
	int m_nKTileDim;

	// Sample size in terms of bytes
	int m_nSampleSize;
};

#endif // KEBRICKREADER_H
