#ifndef XREGULARDATAREADER_H
#define XREGULARDATAREADER_H

#include <QFile>

/**
* @class CXRegularDataReader in the file "rlregulardatareader.h"
* @brief The class provides a class template to read 3-D regular data
* 
* @author Yong Shu 
* @date 4/22/2014
* @see 
*/

template<typename T>
class  CXRegularDataReader
{
public:
	///@brief Constructor and destructor. The data order: U -- V -- S -- W (W changes fastest)
    CXRegularDataReader(const QString& strFileName, int nU, int nV, int nW, int nS = 1, unsigned int nHeadSize=0);
	~CXRegularDataReader();

	///@brief Tell if the file can be open to read
	bool Open();

	///@brief Read a section along U direction
	bool ReadUSection(int iU, T* pData);

	///@brief Read a section along V direction
	bool ReadVSection(int iV, T* pData);

	///@brief Read a section along W direction
	bool ReadWSection(int iW, T* pData);

	///@brief Read a trace given U and V indices
	bool ReadUVTrace(int iU, int iV, T* pData);

	///@brief Read a point
	bool ReadOnePoint(int iU, int iV, int iW, T& TValue);

	///@brief Read partial U section
	bool ReadPartialUSection(int iU, int iVMin, int iVMax, int iWMin, int iWMax, T* pData);

	///@brief Read partial V section
	bool ReadPartialVSection(int iV, int iUMin, int iUMax, int iWMin, int iWMax, T* pData);

private:
	//Read one segment of the file with specific data format. The buffer must be pre-allocated	
	bool _ReadDataBlock (qint64 nOffset, qint64 nDataSize, T* pBuffer);


private:
	QFile *m_pFile;	qint64 m_nU, m_nV, m_nW, m_nS;
	qint64 m_nFileHeadSize;
	qint64 m_nFileSize;
};


// Constructor
template<typename T>
CXRegularDataReader<T>::CXRegularDataReader (const QString& strFileName, int nU, int nV, int nW, int nS, unsigned int nHeadSize)
:m_nU(nU), m_nV(nV), m_nW(nW), m_nS(nS), m_nFileHeadSize(nHeadSize)
{
	m_pFile = new QFile(strFileName);
	m_nFileSize = m_nFileHeadSize + m_nU*m_nV*m_nW*m_nS*sizeof(T);
}

// Destructor
template<typename T>
CXRegularDataReader<T>::~CXRegularDataReader()
{
	m_pFile->close();
}

// 	Tell if the file can be open to read
template<typename T>
bool CXRegularDataReader<T>::Open()
{
	if (m_pFile->open(QIODevice::ReadOnly))
		return true;
	else
		return false;
}

// Read one segment of the file with specific data format. The buffer must be pre-allocated
template<typename T>
bool CXRegularDataReader<T>::_ReadDataBlock (qint64 nOffset, qint64 nDataSize, T* pBuffer)
{
	// Size in terms of bytes
	nOffset *= sizeof(T);
	nDataSize *= sizeof(T);

	// Make sure to map valid data
	if (nOffset + nDataSize + m_nFileHeadSize > m_nFileSize)
		return false;

	m_pFile->seek(nOffset + m_nFileHeadSize);
	if (m_pFile->read((char*)pBuffer, nDataSize) != nDataSize)
		return false;

	return true;
}

// Read a section along U direction
template<typename T>
bool CXRegularDataReader<T>::ReadUSection(int iU, T* pData)
{
	if (iU < 0 || iU >= m_nU || !pData)
		return false;

	qint64 nDataSize =  m_nV*m_nW*m_nS;
	qint64 nOffset =  iU*nDataSize;

	if (!_ReadDataBlock(nOffset, nDataSize, pData))
		return false;
	else	
		return true;
}

// Read a section along V direction
template<typename T>
bool CXRegularDataReader<T>::ReadVSection(int iV, T* pData)
{
	if (iV < 0 || iV >= m_nV || !pData)
		return false;

	//qint64 nDataSize =  m_nU*m_nW;

	// Read
	T* pTmpBuffer = pData;
	qint64 nOffset = iV*m_nW*m_nS;
	for (int iU=0; iU<m_nU; ++iU)
	{
		if (!_ReadDataBlock(nOffset, m_nS*m_nW, pTmpBuffer))
			return false;

		nOffset += m_nV*m_nS*m_nW;
		pTmpBuffer += m_nS*m_nW;
	}

	return true;
}

// Read a section along W direction
template<typename T>
bool CXRegularDataReader<T>::ReadWSection(int iW, T* pData)
{
	//	So far not work for prestack data.
	if (m_nS > 1)
		return false;

	if (iW < 0 || iW >= m_nW || !pData)
		return false;

	qint64 nDataSize =  m_nV*m_nW;
	qint64 nOffset = m_nFileHeadSize;

	// Read
	int index=0;
	for (int iU=0; iU<m_nU; ++iU)
	{
		unsigned char* pMapData = m_pFile->map(nOffset, nDataSize*sizeof(T));
		if (!pMapData )
			return false;

		T* pTmpData = (T*) pMapData;
		qint64 indexTmp = iW;
		for (int iV=0; iV<m_nV; ++iV)
		{
			pData[index++] = pTmpData[indexTmp];
			indexTmp += m_nW;
		}

		m_pFile->unmap(pMapData);
		nOffset += nDataSize*sizeof(T);
	}

	return true;
}

// Read a trace given U and V indices
template<typename T>
bool CXRegularDataReader<T>::ReadUVTrace(int iU, int iV, T* pData)
{
	if (iU < 0 || iU >= m_nU || iV < 0 || iV >= m_nV)
		return false;

	qint64 nOffset = iU*m_nV*m_nS*m_nW + iV*m_nS*m_nW;

	// Read
	if (!_ReadDataBlock(nOffset, m_nS*m_nW, pData))
		return false;
	else
		return true;
}


// Read a point
template<typename T>
bool CXRegularDataReader<T>::ReadOnePoint(int iU, int iV, int iW, T& TValue)
{
	qint64 nOffset = iU*m_nV*m_nW + iV*m_nW + iW;
	nOffset *= sizeof(T);
	nOffset += m_nFileHeadSize;

	if (nOffset < 0 || nOffset >= m_nFileSize)
		return false;
	else
	{	
		m_pFile->seek(nOffset);
		m_pFile->read((char*)&TValue, sizeof(T));
		return true;
	}
}

template<typename T>
bool CXRegularDataReader<T>::ReadPartialUSection(int iU, int iVMin, int iVMax, int iWMin, int iWMax, T* pData)
{
	if (iU    < 0  || iU    >= m_nU ||
		iVMin < 0  || iVMin >= m_nV ||
		iVMax < 0  || iVMax >= m_nV ||
		iWMin < 0  || iWMin >= m_nW ||
		iWMax < 0  || iWMax >= m_nW)
		return false;

	qint64 nOffset = m_nS*(iU*m_nV*m_nW + iVMin*m_nW);
	qint64 nDataSize = (iVMax - iVMin + 1)*m_nS*m_nW;

	if (iWMin == 0 && iWMax == m_nW-1)
	{
		return _ReadDataBlock(nOffset, nDataSize, pData);
	}
	else
	{		
		T* pTmp = new T [nDataSize];
		if (!_ReadDataBlock(nOffset, nDataSize, pTmp))
		{
			delete []pTmp;
			return false;
		}

		int nTraceLength = iWMax - iWMin + 1;
		for (int i=iVMin; i<=iVMax; ++i)
		{
			for (int j=iWMin; j<=iWMax; ++j)
			{
				for (int k = 0; k < m_nS; k++)
					pData[m_nS*(i - iVMin)*nTraceLength + k*nTraceLength + j - iWMin] = pTmp[(i - iVMin)*m_nW + j];
			}
		}
		delete []pTmp;
		return true;
	}
}

template<typename T>
bool CXRegularDataReader<T>::ReadPartialVSection(int iV, int iUMin, int iUMax, int iWMin, int iWMax, T* pData)
{
	if (iV    < 0  || iV    >= m_nV ||
		iUMin < 0  || iUMin >= m_nU ||
		iUMax < 0  || iUMax >= m_nU ||
		iWMin < 0  || iWMin >= m_nW ||
		iWMax < 0  || iWMax >= m_nW)
		return false;

	qint64 nOffset, nDataSize;
	nDataSize = iWMax - iWMin + 1;
	
	for (int i=iUMin; i<=iUMax; ++i)
	{
		for (int j = 0; j < m_nS; j++)
		{
			nOffset = i*m_nV*m_nS*m_nW + iV*m_nS*m_nW + j*m_nW + iWMin;

			if (!_ReadDataBlock(nOffset, nDataSize, pData + (m_nS*(i - iUMin) + j)*nDataSize))
			{
				return false;
			}
		}
	}

	return true;
}

#endif // RLREGULARDATAREADER_H
