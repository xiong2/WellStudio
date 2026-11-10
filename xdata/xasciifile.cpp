#include <qdebug.h>
#include <QFile>
#include <qtextstream.h>
#include "xasciifile.h"
#include "xglobal.h"

CXASCIIFile::CXASCIIFile(EImportFileType eFileType, QString sFile)
{
	m_eFileType				= eFileType;
	m_dInvalid				= ::g_dInvalidData;
	m_pDelimiter			= new CXDelimiter();
	
	m_iImportFrom			= 1;
	m_iNameLine				= 1;
	m_iPreviewLineNumber	= 50;
	m_iImportEnd			= 0;
	m_bEOF					= true;
	if(sFile != "")
		SetFile(sFile);
}

CXASCIIFile::~CXASCIIFile()
{
	if(m_pDelimiter)
		delete m_pDelimiter;
}

bool CXASCIIFile::SetFile(QString sFile, QString sObjName)
{
	m_sFile			= sFile;
	if(!sObjName.isEmpty())
		m_sObjName		= sObjName;
	m_iLineNumber	= GetASCIIFileLineNumber(sFile);
	
	if(m_bEOF || m_iImportEnd	== 0 || m_iImportEnd > m_iLineNumber)
		m_iImportEnd = m_iLineNumber;

	if(m_iLineNumber == 0)
	{
		m_iImportFrom			= 0;
		m_iNameLine				= 0;
		m_iPreviewLineNumber	= 0;

		return false;
	}
	else
	{
		if(m_iImportFrom > m_iLineNumber)
			m_iImportFrom = m_iLineNumber;
		if(m_iNameLine > m_iLineNumber)
			m_iNameLine = m_iLineNumber;
		if(m_iPreviewLineNumber > m_iLineNumber)
			m_iPreviewLineNumber = m_iLineNumber;

		return true;
	}
}

qint64 CXASCIIFile::GetASCIIFileLineNumber(QString sFile)
{
	QFile file(sFile);
	if(!file.open(QIODevice::ReadOnly))
	{
		return 0;
	}
	qint64 nTotalSize = file.size ();
	qint64 nOffset = 0;
	qint64 nBuffSize = 1000000;
	uchar ucLine = '\n';
	qint64 maxLine = MAXLINENUMBER;
	int iLineQty=0;
	bool bLastLine = false;
	while (nOffset < nTotalSize)
	{
		if ((nOffset+nBuffSize) > nTotalSize)
			nBuffSize = nTotalSize-nOffset;
		uchar *readData = file.map (nOffset, nBuffSize);
		if (NULL == readData)
			break;
		for (int i = 0; i < nBuffSize; i++)
		{
			if (readData[i] == ucLine)
				iLineQty ++;
		}
		if (iLineQty > maxLine)
			break;

		if (readData[nBuffSize-1] != ucLine || readData[nBuffSize-2] != ucLine)
			bLastLine = true;

		nOffset += nBuffSize;
		file.unmap (readData);
	}
	file.close();

	if (bLastLine == true)
		iLineQty ++;

	return iLineQty;
}

QStringList CXASCIIFile::GuessColumnName()
{
	QStringList strList;

	QFile qFile(m_sFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		return strList;
	}

	unsigned int iCount = 0;
	QString sLine;
	QTextStream stream(&qFile);
	while (!stream.atEnd())
	{
		sLine = stream.readLine();
		iCount++;

		if (iCount >= m_iNameLine)
			break;
	}

	if (iCount != m_iNameLine)
		return strList;

	QStringList strResList = m_pDelimiter->GetSplittedString(sLine);
	if (strResList.size() == 0)
		return strList;

	//	Not implement yet.
	if (m_sListColumnCandidates.size() == 0)
	{
		//	No candidates, we directly use the given line content.
		//m_sListColumnCandidates = strResList;
		return strResList;
	}
	else
	{
		return strList;
	}
}