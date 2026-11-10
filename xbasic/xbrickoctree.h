#ifndef XBRICKOCTREE_H
#define XBRICKOCTREE_H

#include "xbasic_global.h"
#include <QtGlobal>
#include <vector>

/**
* @class CXBrickOctree in the file "xsbrickoctree.h"
* @brief The class provides interface to access octree. The tile ID is strictly coresponding to the entire octree index.
*
* @date 11/5/2015
* @see
*/
class XBASIC_EXPORT CXBrickOctree
{
public:
	///@brief Constructor and destructor
	CXBrickOctree(int nITile, int nJTile, int nKTile);
	~CXBrickOctree();

	///@brief Get tile position in the real cube from the tile ID. 
	///@brief Return false if there is no valid data coresponding to the tile ID.
	bool GetTileIJKFromTileID(qint64 iTileID, int& iTile, int& jTile, int& kTile);

	///@brief Get the tile ID from the tile position in the real cube
	qint64 GetTileIDFromTileIJK(int iTile, int jTile, int kTile);

	///@brief Get the data ID in the file from the tile ID
	///@brief return -1 if there is data ID
	int GetDataIDFromTileID(qint64 iTileID);

	///@brief Get the tile ID from the data ID
	qint64 GetTileIDFromDataID(int iDataID);

	///@brief Get daughter tile IDs, return the number of valid tile IDs
	int GetDaughterTileIDFromTileID(qint64 iParentTileID, qint64 daughterTileID[8]);

	///@brief Get daughter data IDs, return the number of valid data IDs
	int GetDaughterDataIDFromDataID(int iParentDataID, int daughterDataID[8]);

	///@brief Get the parent tile ID
	qint64 GetParentTileID(qint64 iTileID);

	///@brief Get the parent Data ID
	int GetParentDataID(int iDataID);

	///@brief Get the number of the total tile IDs that have the data IDs
	int GetTotalTileNum() { return m_nNumTotalTileAtAllLevel; }

	///@brief Get the array of accumulated tile numbers
	void GetVecAccumulatedTileNum(std::vector<qint64>& vecAccumulatedTileNum);

	///@brief Get the array of tile numbers
	void GetVecTileNum(std::vector<qint64>& vecTileNum);

	///@brief Get the number of original data tiles
	int GetOriginalTileNum();


private:
	// Initialization
	void _Init();
	// Calculate the relationship between data IDs and tile IDs
	void _CalculateDataIDs();

private:
	// The ascending ordered tile IDs which have the valid data IDs in the file
	qint64* m_pTileID;

	// The number of the total tile IDs that have the valid data IDs
	int m_nNumTotalTileAtAllLevel;

	// An array of numbers of tile IDs at the each level
	std::vector<qint64> m_vecTileNumAtLevel;

	// Real cube dimension
	int m_nITile;
	int m_nJTile;
	int m_nKTile;

	// The minimum cube dimension (the power of 2) that contains the real cube
	int m_nDimTile;

	// The level number (from 0 to m_nLevel)
	int m_nLevel;

	// The number of total low-resolution tiles in the cube with each dimension of m_nDimTile
	qint64 m_nLowTileNum;
};
#endif // KEBRICKOCTREE_H
