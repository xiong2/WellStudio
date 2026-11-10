#ifndef __CXSORTONDISK_H__
#define __CXSORTONDISK_H__

#include "xutility.h"
#include <QFile>
#include <QFileInfo>
#include <limits>
#include <algorithm>
#include "xsysteminfo.h"


template<typename T>
class CXSortOnDisk
{
public:
	CXSortOnDisk(const QString& strFileName);
	~CXSortOnDisk();

	bool Sort();

private:
	bool _BlockSort();
	bool _Merge();

	bool _CreateBuffers();
	void _ReleaseBuffers();
	bool _InitReaderAndWriter();
	bool _ReadBlock(qint64 iBlock);
	bool _WriteBlock();


private:
	QString m_strRawFileName;
	QString m_strNewFileName;
	QFile m_qRawFile;
	QFile m_qNewFile;

private:
	T** m_p2DReadBuffer;
	T*  m_pWriteBuffer;

	qint64* m_pReadIndex;
	qint64* m_pReadBufferCount;
	qint64* m_pReadOffset;
	bool*   m_pReadBlockFinished;

private:
	qint64 m_nFileSize;
	qint64 m_nSortBlockSize;
	qint64 m_nBlockNum;

	qint64 m_nReadBufferSize;
	qint64 m_nWriteBufferSize;

	qint64 m_nWriteBufferCount;
	qint64 m_nTotalWriteCount;
};


template<typename T>
CXSortOnDisk<T>::CXSortOnDisk(const QString &strFileName)
	:m_strRawFileName(strFileName)
{
	m_strNewFileName = m_strRawFileName + ".tmp";
	m_qRawFile.setFileName(m_strRawFileName);
	m_qNewFile.setFileName(m_strNewFileName);

	QFileInfo fileInfo(m_strRawFileName);
	m_nFileSize = fileInfo.size() / sizeof(T);

	m_nSortBlockSize = 60 * 1000 * 1000;
	m_nReadBufferSize = 2 * 1000 * 1000;
	m_nWriteBufferSize = 10 * 1000 * 1000;

	m_nBlockNum = m_nFileSize / m_nSortBlockSize + 1;

	// Init buffers
	m_p2DReadBuffer = NULL;
	m_pWriteBuffer = NULL;

	m_pReadIndex = NULL;
	m_pReadBufferCount = NULL;
	m_pReadOffset = NULL;
	m_pReadBlockFinished = NULL;
}

template<typename T>
CXSortOnDisk<T>::~CXSortOnDisk()
{
	_ReleaseBuffers();
}

template<typename T>
bool CXSortOnDisk<T>::_BlockSort()
{
	if (m_nBlockNum < 1)
		return false;

	if (CXSystemInfo::GetFreeDiskSpace(m_strRawFileName) < m_nFileSize*sizeof(T))
		return false;

	if (!m_qRawFile.open(QIODevice::ReadWrite))
		return false;

	T* pBlockBuffer = NULL;
	try
	{
		pBlockBuffer = new T[m_nSortBlockSize];
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	for (qint64 i = 0; i<m_nBlockNum; ++i)
	{
		qint64 iOffset = i*m_nSortBlockSize*sizeof(T);
		qint64 nDataSize = m_nSortBlockSize;
		if (i == m_nBlockNum - 1)
		{
			nDataSize = m_nFileSize - i*m_nSortBlockSize;
		}

		// Read
		m_qRawFile.seek(iOffset);
		m_qRawFile.read((char*)pBlockBuffer, sizeof(T)*nDataSize);

		//sort
		std::sort(pBlockBuffer, pBlockBuffer + nDataSize);

		// write
		m_qRawFile.seek(iOffset);
		m_qRawFile.write((char*)pBlockBuffer, sizeof(T)*nDataSize);
	}

	delete[]pBlockBuffer;
	m_qRawFile.close();

	return true;
}

template<typename T>
bool CXSortOnDisk<T>::_CreateBuffers()
{
	try
	{
		m_p2DReadBuffer = NXUtility::New2DArray<T>(m_nBlockNum, m_nReadBufferSize);
		m_pWriteBuffer = new T[m_nWriteBufferSize];

		m_pReadIndex = new qint64[m_nBlockNum];
		m_pReadBufferCount = new qint64[m_nBlockNum];
		m_pReadOffset = new qint64[m_nBlockNum];
		m_pReadBlockFinished = new bool[m_nBlockNum];
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	for (qint64 iBlock = 0; iBlock<m_nBlockNum; ++iBlock)
	{
		m_pReadOffset[iBlock] = iBlock*m_nSortBlockSize;
		m_pReadBlockFinished[iBlock] = false;
	}

	return true;
}

template<typename T>
void CXSortOnDisk<T>::_ReleaseBuffers()
{
	if (m_p2DReadBuffer)		{ NXUtility::Free2DArray<T>(m_p2DReadBuffer, m_nBlockNum); m_p2DReadBuffer = NULL; }
	if (m_pWriteBuffer)			{ delete[]m_pWriteBuffer; m_pWriteBuffer = NULL; }

	if (m_pReadIndex)			{ delete[]m_pReadIndex; m_pReadIndex = NULL; }
	if (m_pReadBufferCount)		{ delete[]m_pReadBufferCount; m_pReadBufferCount = NULL; }
	if (m_pReadOffset)			{ delete[]m_pReadOffset; m_pReadOffset = NULL; }
	if (m_pReadBlockFinished)	{ delete[]m_pReadBlockFinished; m_pReadBlockFinished = NULL; }
}

template<typename T>
bool CXSortOnDisk<T>::_InitReaderAndWriter()
{
	if (!m_qNewFile.open(QIODevice::WriteOnly))
		return false;

	if (!m_qRawFile.open(QIODevice::ReadOnly))
		return false;

	return true;
}


template<typename T>
bool CXSortOnDisk<T>::_WriteBlock()
{
	m_qNewFile.write((char*)m_pWriteBuffer, sizeof(T)*m_nWriteBufferCount);
	m_nTotalWriteCount += m_nWriteBufferCount;
	m_nWriteBufferCount = 0;
	return true;
}

template<typename T>
bool CXSortOnDisk<T>::_ReadBlock(qint64 iBlock)
{
	if (m_pReadBlockFinished[iBlock])
		return true;

	qint64 iEndOffset = 0;

	if (iBlock < m_nBlockNum - 1)
	{
		iEndOffset = (iBlock + 1)*m_nSortBlockSize;
	}
	else
	{
		iEndOffset = m_nFileSize;
	}

	if (m_pReadOffset[iBlock] + m_nReadBufferSize <= iEndOffset)
	{
		m_qRawFile.seek(sizeof(T)*m_pReadOffset[iBlock]);
		m_qRawFile.read((char*)m_p2DReadBuffer[iBlock], sizeof(T)*m_nReadBufferSize);
		m_pReadOffset[iBlock] += m_nReadBufferSize;
		m_pReadBufferCount[iBlock] = m_nReadBufferSize;
		m_pReadIndex[iBlock] = 0;
	}
	else
	{
		m_qRawFile.seek(sizeof(T)*m_pReadOffset[iBlock]);
		qint64 nDataSize = iEndOffset - m_pReadOffset[iBlock];
		m_qRawFile.read((char*)m_p2DReadBuffer[iBlock], sizeof(T)*nDataSize);
		m_pReadOffset[iBlock] = iEndOffset;
		m_pReadBufferCount[iBlock] = nDataSize;
		m_pReadIndex[iBlock] = 0;
	}

	if (m_pReadOffset[iBlock] == iEndOffset)
	{
		m_pReadBlockFinished[iBlock] = true;
	}

	return true;
}

template<typename T>
bool CXSortOnDisk<T>::_Merge()
{
	m_nTotalWriteCount = 0;
	m_nWriteBufferCount = 0;

	for (qint64 iBlock = 0; iBlock<m_nBlockNum; ++iBlock)
	{
		m_pReadIndex[iBlock] = 0;
		_ReadBlock(iBlock);
	}

	T TMax = std::numeric_limits<T>::max();
	qint64 iIndex, iFinalIndex, iFinalBlock(0);
	T tValue;

	while (m_nTotalWriteCount < m_nFileSize)
	{
		tValue = TMax;
		iFinalIndex = -1;
		for (qint64 iBlock = 0; iBlock<m_nBlockNum; ++iBlock)
		{
			if (m_pReadBlockFinished[iBlock] &&
				m_pReadIndex[iBlock] == m_pReadBufferCount[iBlock])
				continue;

			iIndex = m_pReadIndex[iBlock];

			if (m_p2DReadBuffer[iBlock][iIndex] < tValue)
			{
				tValue = m_p2DReadBuffer[iBlock][iIndex];
				iFinalBlock = iBlock;
				iFinalIndex = iIndex;
			}
		}

		if (iFinalIndex == -1)
		{
			_WriteBlock();
			break;
		}

		m_pReadIndex[iFinalBlock]++;
		if (m_pReadIndex[iFinalBlock] == m_pReadBufferCount[iFinalBlock])
			_ReadBlock(iFinalBlock);

		// write
		m_pWriteBuffer[m_nWriteBufferCount++] = tValue;
		if (m_nWriteBufferCount == m_nWriteBufferSize)
			_WriteBlock();
	}

	return true;

}

template<typename T>
bool CXSortOnDisk<T>::Sort()
{
	if (!_BlockSort())
		return false;

	if (m_nBlockNum == 1)
		return true;

	if (!_CreateBuffers())
		return false;

	if (!_InitReaderAndWriter())
		return false;

	if (!_Merge())
		return false;

	_ReleaseBuffers();

	m_qRawFile.close();
	m_qNewFile.close();

	QFile::remove(m_strRawFileName);
	QFile::rename(m_strNewFileName, m_strRawFileName);

	return true;
}

#endif