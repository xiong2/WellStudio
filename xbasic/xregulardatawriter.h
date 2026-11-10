#ifndef XREGULARDATAWRITER_H
#define XREGULARDATAWRITER_H

#include <QFile>

/**
* @class CXRegularDataWriter in the file "rlregulardatawriter.h"
* @brief The class provides a class template to write 3-D regular data
* 
* @author Yong Shu 
* @date 4/22/2014
* @see 
*/

template<typename T>
class CXRegularDataWriter
{
public:
	///@brief Constructor and destructor. The data order: U -- V -- W (W changes fastest)
    CXRegularDataWriter(const QString& strFileName, int nU, int nV, int nW, unsigned int nHeadSize=0);
	~CXRegularDataWriter();

	///@brief Tell if the file can be open to read
	bool Open();

	//Read one segment of the file with specific data format. The buffer must be pre-allocated	
	bool Write (qint64 nOffset, qint64 nDataSize, T* pBuffer);

	///@brief Write a section along U direction
	bool WriteUSection(int iU, T* pData);

	///@brief Append data
	bool Append(qint64 nDataSize, T* pBuffer);

	///@brief Remove the file
	void Remove();

	///@brief Close the file
	void Close();

private:
	QFile *m_pFile;
	qint64 m_nU, m_nV, m_nW;
	unsigned int m_nFileHeadSize;
	qint64 m_nFileSize;
	bool m_bOpen;
};


// Constructor
template<typename T>
CXRegularDataWriter<T>::CXRegularDataWriter (const QString& strFileName, int nU, int nV, int nW, unsigned int nHeadSize)
:m_nU(nU), m_nV(nV), m_nW(nW), m_nFileHeadSize(nHeadSize),m_bOpen(false)
{
	m_pFile = new QFile(strFileName);
	m_nFileSize = m_nFileHeadSize + m_nU*m_nV*m_nW*sizeof(T);
}

// Destructor
template<typename T>
CXRegularDataWriter<T>::~CXRegularDataWriter()
{
	m_pFile->close();
}

// 	Tell if the file can be open to write
template<typename T>
bool CXRegularDataWriter<T>::Open()
{
	m_bOpen = m_pFile->open(QIODevice::WriteOnly);
	if (m_bOpen)
	{		
		m_pFile->resize(m_nFileSize);
	}
	return m_bOpen;
}

// 	Tell if the file can be open to write
template<typename T>
bool CXRegularDataWriter<T>::Append(qint64 nDataSize, T* pBuffer)
{

	qint64 nSize = nDataSize*sizeof(T);
	bool b = (nSize == m_pFile->write((char*)pBuffer, nDataSize*sizeof(T)));
	return b;
}

// Write one segment of the file with specific data format. The buffer must be pre-allocated
template<typename T>
bool CXRegularDataWriter<T>::Write (qint64 nOffset, qint64 nDataSize, T* pBuffer)
{
	// Size in terms of bytes
	nOffset *= sizeof(T);
	nDataSize *= sizeof(T);

	// Make sure to write data to valid area
	if (nOffset + nDataSize + m_nFileHeadSize > m_nFileSize)
		return false;

	m_pFile->seek(nOffset + m_nFileHeadSize);
	m_pFile->write((char*)pBuffer, nDataSize);

	return true;
}

// Read a section along U direction
template<typename T>
bool CXRegularDataWriter<T>::WriteUSection(int iU, T* pData)
{
	if (iU < 0 || iU >= m_nU || !pData)
		return false;

	qint64 nDataSize =  m_nV*m_nW;
	qint64 nOffset =  iU*nDataSize;

	if (!Write(nOffset, nDataSize, pData))
		return false;
	else	
		return true;
}

template<typename T>
void CXRegularDataWriter<T>::Remove()
{
	m_pFile->remove();
}

template<typename T>
void CXRegularDataWriter<T>::Close()
{
	m_pFile->close();
}

#endif // RLREGULARDATAWRITER_H
