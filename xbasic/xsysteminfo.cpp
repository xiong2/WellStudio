#include "xsysteminfo.h"

#include <cmath>
#include <QThread>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QDesktopWidget>

#ifdef WIN32
    #include <windows.h>
#else
	#include <sys/sysinfo.h>
	#include <sys/vfs.h>
	#include <unistd.h>
#endif

// From "..\..\..\toolkit\OpenGL\glew-1.5.6-win64\include\GL\glew.h"
#ifndef GL_SHADING_LANGUAGE_VERSION
    #define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#endif

int CXSystemInfo::GetCPUNum()
{
	int nCPU = QThread::idealThreadCount();
	if (nCPU <1)
		nCPU = 1;
	return nCPU;
}

qint64 CXSystemInfo::GetFreeDiskSpace(const QString &strDirectoryPath)
{
	long long nFreeSpace;
#ifdef WIN32
    ULARGE_INTEGER x1,x2,x3;
	::SetCurrentDirectoryA(strDirectoryPath.toLatin1().data());
    ::GetDiskFreeSpaceEx(NULL,&x1,&x2,&x3);
    nFreeSpace = x3.QuadPart;
#else
    struct statfs aa;	
    statfs((char *)strDirectoryPath.toLatin1().data(),&aa);
    nFreeSpace = aa.f_bfree*aa.f_bsize;
#endif

    return nFreeSpace;
}

QString CXSystemInfo::GetSpaceSizeString(long long nFreeSpace)
{
	QString str;
	long long GBytes, MBytes;
	double dGBytes;
	GBytes = nFreeSpace/(1024*1024*1024);

	if (GBytes>0)
	{
		dGBytes = ((double) nFreeSpace)/(1024*1024*1024);
		str = QString::number(dGBytes,'f', 2) + " GB";
	}
	else
	{
		MBytes = nFreeSpace/(1024*1024);
		if (MBytes == 0)
			MBytes = 1;
		str = QString::number(MBytes) + " MB";
	}

	return str;
}

int CXSystemInfo::GetFreeMemory()
{
#ifdef WIN32
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullAvailPhys/(1000*1000);
#else

#endif
}

qint64 CXSystemInfo::GetBrickFileSize(int nx, int ny, int nz, int nSampleSize, int nTileDim)
{
	if (nx<1 || ny <1 || nz< 1 || nTileDim <1)
		return 0;

	qint64 nTileSize = nTileDim*nTileDim*nTileDim*nSampleSize;

	qint64 xTileNum, yTileNum, zTileNum;
	if (nx < nTileDim)
		xTileNum = 1;
	else
		xTileNum = (int) ceil (nx*1.0/nTileDim);

	if (ny < nTileDim)
		yTileNum = 1;
	else
		yTileNum = (int) ceil (ny*1.0/nTileDim);

	if (nz < nTileDim)
		zTileNum = 1;
	else
		zTileNum = (int) ceil (nz*1.0/nTileDim);

	qint64 nFileSize;

	if (yTileNum == 1)
		nFileSize = (xTileNum*yTileNum*zTileNum)*(nTileSize/nTileDim*ny);
	else
		nFileSize = (xTileNum*yTileNum*zTileNum)*nTileSize;

	return nFileSize;
}


int CXSystemInfo::GetDPI (void)
{
    QDesktopWidget desk;
    //int height = desk.height ();
    //int width = desk.width ();
    //int heightMM = desk.heightMM ();
    //int widthMM = desk.widthMM ();
    int logicalDpiX = desk.logicalDpiX ();
    //int logicalDpiY = desk.logicalDpiY ();
    //int physicalDpiX = desk.physicalDpiX ();
    //int physicalDpiY = desk.physicalDpiY ();

    return logicalDpiX;
}
