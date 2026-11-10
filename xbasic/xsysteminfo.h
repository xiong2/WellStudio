#ifndef XSYSTEMINFO_H
#define XSYSTEMINFO_H

#include "xbasic_global.h"

/**
 * @class CXSystemInfo in the file "rlsysteminfo.h"
 * @brief The Class provides the methods to access system info
 * 
 * @author Yong Shu 
 * @date 5/27/2014
 * @see 
 * @bug	No Known bugs so far
 */

class XBASIC_EXPORT CXSystemInfo
{
public:
	/**
	 * @brief Get the number of multiple cores in the local computer
	 * @return Return the number
	 */
	static int GetCPUNum();

	/**
	 * @brief Get the size of free space in the specific disk partition which the directory belongs to(unit: bytes)
	 * @param[in]  strDirectoryPath: the directory path indicating which disk parition
	 * @return Return the size (bytes)
	 * @date 8/14/2009
	 */
    static qint64 GetFreeDiskSpace(const QString &strDirectoryPath);

	/**
	 * @brief Return the string of Space Size in terms of "XXX.YY GB" or "XXX MB"
	 * @param[in]  nFreeSpace: the size of free space (bytes)
	 * @return Return the string
	 */
	static QString GetSpaceSizeString(long long nFreeSpace);

	/**
	 * @brief Get the size of free memory in the system (unit: megabytes, 1000*1000)
	 * @return Return the size (MegaBytes)
	 */
	static int GetFreeMemory();

	/**
	* @brief Return the Size of LDM file
	* @param[in]  nx : dimension size of x direction (crossline)
	* @param[in]  ny : dimension size of y direction (inline)
	* @param[in]  nz : dimension size of z direction (time or depth)
	* @param[in]  nSampleSize : the size of each sample point in terms of bytes (example: float: 4, char: 1)
	* @param[in]  nTileSize : brick tile size
	* @return File size (bytes)
	* @see 
	*/
	static qint64 GetBrickFileSize(int nx, int ny, int nz, int nSampleSize, int nTileDim = 64);

    
    static int GetDPI (void);
};

#endif // RLSYSTEMINFO_H
