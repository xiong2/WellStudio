#include <QtWidgets/QMessageBox>
#include "ximport3dsurfacemanager.h"

#include <cassert>

#include <QFile>
#include <qfileinfo.h>
#include <qtextstream.h>

#include "xglobal.h"
#include "xmathmacro.h"
#include "xutmtool.h"
#include "x3dhorizon.h"
#include "xseismicutmtool.h"
#include "xprogressbar.h"

CXImportSurfacePara::CXImportSurfacePara()
{
	m_fInvalidData = ::g_dInvalidData;

	m_nInlineIndex = -1;
	m_nCrosslineIndex = -1;
	m_nXIndex = -1;
	m_nYIndex = -1;
	m_nIIndex = -1;
	m_nJIndex = -1;

	m_nHorizonType = -1;

	m_iFirstLineNum = 0;
	m_iLastLineNum = INT_MAX;
}

CXImportSurfacePara::~CXImportSurfacePara()
{
	ClearDataBuffer();
}

void CXImportSurfacePara::CalculateLineIncrement()
{
	double fEPS4Invalid = GetEPSofInvalidData(m_fInvalidData);

	//line-number Space
	bool bFoundInlineSpace = false;
	bool bFoundXlineSpace = false;
	int iInlineInc = 1000000, iXlineInc = 1000000, iTmp;
	int nRowCount = m_vecInline.size();
	int i = 1;
	while (i < 10000 && i < nRowCount)
	{
		if (bFoundInlineSpace && bFoundXlineSpace)
			break;

		if (!bFoundInlineSpace &&
			qAbs((double)m_vecInline[i] - m_fInvalidData) > fEPS4Invalid &&
			qAbs((double)m_vecInline[i - 1] - m_fInvalidData) > fEPS4Invalid)
		{
			if (m_vecInline[i] != m_vecInline[i - 1])
			{
				iTmp = qAbs(m_vecInline[i] - m_vecInline[i - 1]);
				if (iTmp != iInlineInc)
				{
					//	To find the greatest common divisor.
					int iDiv = 1;
					int iMin = qMin(iTmp, iInlineInc);
					for (int j = 2; j <= iMin; j++)
					{
						if (iTmp % j == 0 && iInlineInc % j == 0)
							iDiv = j;
					}
					iInlineInc = iDiv;
				}

				if (iInlineInc == 1)
					bFoundInlineSpace = true;
			}
		}

		if (!bFoundXlineSpace &&
			qAbs((double)m_vecXline[i] - m_fInvalidData) > fEPS4Invalid &&
			qAbs((double)m_vecXline[i - 1] - m_fInvalidData) > fEPS4Invalid)
		{
			if (m_vecXline[i] != m_vecXline[i - 1])
			{
				iTmp = qAbs(m_vecXline[i] - m_vecXline[i - 1]);
				if (iTmp != iXlineInc)
				{
					//	To find the greatest common divisor.
					int iDiv = 1;
					int iMin = qMin(iTmp, iXlineInc);
					for (int j = 2; j <= iMin; j++)
					{
						if (iTmp % j == 0 && iXlineInc % j == 0)
							iDiv = j;
					}
					iXlineInc = iDiv;
				}

				if (iXlineInc == 1)
					bFoundXlineSpace = true;
			}
		}

		++i;
	}

	m_nInlineInc = iInlineInc;
	m_nXlineInc = iXlineInc;
}

bool CXImportSurfacePara::ParseOneLineData(const QStringList& strList, float* pZ, double fInvalidEPS)
{
	bool bOK, bContinue;
	int nInline = 0, nXline = 0;
	int iI, iJ;
	double dX = 0, dY = 0;

	// Inline number
	if (m_nInlineIndex > -1)
	{
		nInline = (int)strList[m_nInlineIndex].toFloat(&bOK);
		if (!bOK)
			return false;
	}

	// Xline number
	if (m_nCrosslineIndex > -1)
	{
		nXline = (int)strList[m_nCrosslineIndex].toFloat(&bOK);
		if (!bOK)
			return false;
	}

	// I
	if (m_nIIndex > -1)
	{
		iI = (int)strList[m_nIIndex].toInt(&bOK);
		if (!bOK)
			return false;
	}

	// J
	if (m_nJIndex > -1)
	{
		iJ = (int)strList[m_nJIndex].toInt(&bOK);
		if (!bOK)
			return false;
	}

	// X coordinate
	if (m_nXIndex > -1)
	{
		dX = strList[m_nXIndex].toDouble(&bOK);
		if (!bOK)
			return false;

	}
	// Y coordinate
	if (m_nYIndex > -1)
	{
		dY = strList[m_nYIndex].toDouble(&bOK);
		if (!bOK)
			return false;
	}

	// Must have Z
	bContinue = false;
	for (int i = 0; i < m_nHorizonCount; i++)
	{
		if (strList[m_vecDataIndex[i]] == "")
		{
			pZ[i] = m_fInvalidData;
		}
		else
		{
			pZ[i] = strList[m_vecDataIndex[i]].toFloat(&bOK);
			if (!bOK)
			{
				bContinue = true;
				break;
			}
		}
	}
	if (bContinue)
		return false;


	// Get the min and max
	// Inline
	if (m_nInlineIndex > -1 && qAbs((double)nInline - m_fInvalidData) > fInvalidEPS)
	{
		if (m_nInlineMin > nInline)
			m_nInlineMin = nInline;
		if (m_nInlineMax < nInline)
			m_nInlineMax = nInline;
	}
	// Xline
	if (m_nCrosslineIndex > -1 && qAbs((double)nXline - m_fInvalidData) > fInvalidEPS)
	{
		if (m_nXlineMin > nXline)
			m_nXlineMin = nXline;
		if (m_nXlineMax < nXline)
			m_nXlineMax = nXline;
	}
	// X
	if (m_nXIndex > -1 && qAbs(dX - m_fInvalidData) > fInvalidEPS)
	{
		if (m_dXMin > dX)
			m_dXMin = dX;
		if (m_dXMax < dX)
			m_dXMax = dX;
	}
	else
	{
		dX = ::g_dInvalidData;
		m_dXMin = 0.0;
		m_dXMax = 0.0;
	}
	// Y
	if (m_nYIndex > -1 && qAbs(dY - m_fInvalidData) > fInvalidEPS)
	{
		if (m_dYMin > dY)
			m_dYMin = dY;
		if (m_dYMax < dY)
			m_dYMax = dY;
	}
	else
	{
		dY = ::g_dInvalidData;
		m_dYMin = 0.0;
		m_dYMax = 0.0;
	}

	// Must have Z
	double dZ;
	for (int i = 0; i < m_nHorizonCount; ++i)
	{
		dZ = pZ[i];
		if (qAbs(dZ - m_fInvalidData) > fInvalidEPS)
		{
			if (m_vecZMin[i] > dZ)
				m_vecZMin[i] = dZ;
			if (m_vecZMax[i] < dZ)
				m_vecZMax[i] = dZ;
		}
		else
		{
			pZ[i] = ::g_dInvalidData;
		}
	}

	// Get the data
	if (m_nInlineIndex > -1)
		m_vecInline.push_back(nInline);
	if (m_nCrosslineIndex > -1)
		m_vecXline.push_back(nXline);
	if (m_nXIndex > -1)
		m_vecX.push_back(dX);
	if (m_nYIndex > -1)
		m_vecY.push_back(dY);
	if (m_nIIndex > -1)
		m_vecI.push_back(iI);
	if (m_nJIndex > -1)
		m_vecJ.push_back(iJ);

	// set data
	for (int i = 0; i < m_nHorizonCount; ++i)
	{
		m_vecVecZ[i].push_back(pZ[i]);
	}

	return true;
}

void CXImportSurfacePara::ResetMinMaxValues()
{
	m_nInlineMin = 999999;
	m_nInlineMax = -999999;
	m_nInlineInc = 0;
	m_nXlineMin = 999999;
	m_nXlineMax = -999999;
	m_nXlineInc = 0;

	m_dXMin = M_FLT_MAX;
	m_dXMax = M_FLT_NEGATIVEMAX;
	m_dYMin = M_FLT_MAX;
	m_dYMax = M_FLT_NEGATIVEMAX;

	m_vecZMin.clear();
	m_vecZMax.clear();

	for (int i = 0; i < m_nHorizonCount; ++i)
	{
		m_vecZMin.push_back(M_FLT_MAX);
		m_vecZMax.push_back(M_FLT_NEGATIVEMAX);
	}
}

void CXImportSurfacePara::ClearDataBuffer()
{
	m_vecInline.clear();
	m_vecXline.clear();
	m_vecI.clear();
	m_vecJ.clear();
	m_vecX.clear();
	m_vecY.clear();
	for (int i = 0; i < m_vecVecZ.size(); ++i)
		m_vecVecZ.at(i).clear();
	m_vecVecZ.clear();
}


CXImport3DSurfaceManager::CXImport3DSurfaceManager(const QString& strFileName, EImportFileType eFileType)
	:m_sFileName(strFileName), m_eFileType(eFileType)
{
	m_nHeadSize = 0;
}

CXImport3DSurfaceManager::~CXImport3DSurfaceManager()
{
}

bool CXImport3DSurfaceManager::_VerifyHorizonPicks(const CXDelimiter& delimiter, const QStringList& listColumnNames, int iFirstLineNum, int iLastLineNum, double fInvalid)
{
	m_Delimiter = delimiter;

	//	Make sure the file exists and can be read.
	QFile qFile(m_sFileName);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(0, ::g_strProductName, "Unable to open file: " + m_sFileName);
		return false;
	}
	qFile.close();

	// Set invalid data
	m_ImPara.m_fInvalidData = fInvalid;
	m_ImPara.m_iFirstLineNum = iFirstLineNum;
	m_ImPara.m_iLastLineNum = iLastLineNum;

	if (m_ImPara.m_iFirstLineNum > m_ImPara.m_iLastLineNum)
	{
		QMessageBox::warning(0, g_strProductName, "The selected line range is wrong!");
		return false;
	}

	// Set index
	int i = 0;
	QString sColName;

	int nColX = -1, nColY = -1, nInline = -1, nXline = -1;
	std::vector<int> vecZIndex;

	for (i = 0; i < listColumnNames.size(); ++i)
	{
		sColName = listColumnNames[i];
		sColName.trimmed();
		if (sColName.toLower() == "x")
			nColX = i;
		else if (sColName.toLower() == "y")
			nColY = i;
		else if (sColName.toLower() == "inline")
			nInline = i;
		else if (sColName.toLower() == "xline")
			nXline = i;
		else if (sColName.toLower() == "z")
			vecZIndex.push_back(i);
	}

	//	No Z value?  Just return.
	if (vecZIndex.empty())
	{
		QMessageBox::warning(0, g_strProductName, "At least one Z coordinate has to be selected!");
		return false;
	}

	//	No X/Y?
	if (nColX == -1)
		nColY = -1;
	else if (nColY == -1)
		nColX = -1;

	//	No Inline/Crossline?
	if (nInline == -1)
		nXline = -1;
	else if (nXline == -1)
		nInline = -1;

	//	No X, Y, Inline, Crossline, then return false;
	if (nColX == -1 && nInline == -1)
	{
		QMessageBox::warning(0, "Warning", "No enough coordinates are selected!");
		return false;
	}

	//	Remember each horizon's Z column index.
	m_ImPara.m_nHorizonCount = (int)vecZIndex.size();
	m_ImPara.m_nInlineIndex = nInline;
	m_ImPara.m_nCrosslineIndex = nXline;
	m_ImPara.m_nXIndex = nColX;
	m_ImPara.m_nYIndex = nColY;

	m_ImPara.m_vecDataIndex.clear();
	m_ImPara.m_nHorizonType = -1;

	for (int index = 0; index < vecZIndex.size(); ++index)
		m_ImPara.m_vecDataIndex.push_back(vecZIndex.at(index));

	//Name
	QFile file(m_sFileName);
	QFileInfo FileInfo(file);
	QString strName = FileInfo.baseName();
	m_strListHorizonName.clear();


	// All Z's or all attributes
	if (!vecZIndex.empty())
		m_ImPara.m_nHorizonType = 0;
	else
		m_ImPara.m_nHorizonType = 1;

	for (int j = 0; j < m_ImPara.m_nHorizonCount; ++j)
	{
		QString strOneName;
		if (j == 0)
			strOneName = strName;
		else
			strOneName = strName + " " + QString::number(j + 1);
		m_strListHorizonName.append(strOneName);
	}

	return true;
}


bool CXImport3DSurfaceManager::_VerifyZMapGridASCII()
{
	//	Make sure the file exists and can be read.
	QFile qFile(m_sFileName);
	if (!qFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(0, g_strProductName, "Unable to open file: " + m_sFileName);
		return false;
	}

	// Horizon number
	m_ImPara.m_nHorizonCount = 1;

	// Horizon name
	QFileInfo fileInfo(m_sFileName);
	m_strListHorizonName.clear();
	m_strListHorizonName.append(fileInfo.baseName());

	// Parse head structure
	int nRow = 0;
	QString strLine;
	QStringList strListLine;
	bool bOK;
	bool bHeadStart = false, bInvalid = false, bIJMinMax = false, bHeadEnd = false;
	while (!qFile.atEnd() && nRow < 200)
	{
		if (bHeadEnd)
			break;

		strLine = qFile.readLine();
		++nRow;
		strLine = strLine.simplified();
		if (strLine.isEmpty())
			continue;

		strListLine = strLine.split(",", QString::SkipEmptyParts);

		if (!bHeadStart)				 // horizon count
		{
			if (!strLine.contains("@", Qt::CaseInsensitive))
				continue;

			bHeadStart = true;
		}
		else if (!bInvalid)	   // horizon names
		{
			if (strListLine.size() < 4)
				continue;

			double fInvalidData = strListLine.at(1).toDouble(&bOK);
			if (!bOK)
				continue;

			m_ImPara.m_fInvalidData = fInvalidData;
			bInvalid = true;
		}
		else if (!bIJMinMax)
		{
			if (strListLine.size() < 6)
				continue;

			m_ImPara.m_nI = strListLine.at(0).toInt();
			m_ImPara.m_nJ = strListLine.at(1).toInt();
			m_ImPara.m_dXMin = strListLine.at(2).toDouble();
			m_ImPara.m_dXMax = strListLine.at(3).toDouble();
			m_ImPara.m_dYMin = strListLine.at(4).toDouble();
			m_ImPara.m_dYMax = strListLine.at(5).toDouble();

			if (m_ImPara.m_nI == 0 || m_ImPara.m_nJ == 0)
				continue;

			bIJMinMax = true;
		}
		else if (!bHeadEnd)
		{
			if (!strLine.contains("@", Qt::CaseInsensitive))
				continue;

			m_nHeadSize = qFile.pos();
			bHeadEnd = true;
		}
	}

	if (qFile.atEnd() || nRow >= 200)
	{
		qFile.close();
		QMessageBox::warning(0, g_strProductName, "The file format is not ZMap Grid (ASCII)!");
		return false;
	}
	qFile.close();

	return true;
}

bool CXImport3DSurfaceManager::_ImportGeneralSurfaceData()
{
	QFile qFile(m_sFileName);
	if (!qFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(0, g_strProductName, "Unable to import data from file:" + m_sFileName);
		return false;
	}

	float* pData;
	int nSize = m_ImPara.m_nI*m_ImPara.m_nJ;
	try { pData = new float[nSize]; }
	catch (...)
	{
		QMessageBox::warning(0, "Warning", "The memory is not enough!");
		return false;
	}

	qFile.seek(m_nHeadSize);


	// Get the file size and file name
	QFileInfo fileInfo(m_sFileName);
	QString strHorizonFileName = fileInfo.baseName();
	QString strLabelFileName = QString("Importing File: ") + strHorizonFileName;

	// progress bar
	CXProgressBar progress("Import Horizon", strLabelFileName, fileInfo.size());

	// Initialization
	m_ImPara.ClearDataBuffer();
	m_ImPara.m_vecVecZ.resize(m_ImPara.m_nHorizonCount);
	m_bAbort = false;

	// Invalid data
	double fInvalidData = m_ImPara.m_fInvalidData;
	double fInvalidEPS = ::GetEPSofInvalidData(fInvalidData);
	double dZMin = M_FLT_MAX;
	double dZMax = M_FLT_NEGATIVEMAX;

	// Read data
	QStringList strList;
	QString strLine;
	int index = 0, count;
	float fValue;
	bool bOK, bError = false;
	while (!qFile.atEnd() && index < nSize)
	{
		if (bError)
			break;

		//   Cancel 
		if (progress.IsAborted())
		{
			delete[]pData;
			return false;
		}
		else
		{
			progress.SetValue(qFile.pos());
		}

		strLine = qFile.readLine();
		strLine = strLine.simplified();
		strList = strLine.split(" ", QString::SkipEmptyParts);

		if (strList.isEmpty())
			continue;

		count = strList.size();
		for (int i = 0; i < count; ++i)
		{
			fValue = strList.at(i).toFloat(&bOK);
			if (bOK)
			{
				if (index == nSize)
				{
					bError = true;
					break;
				}

				if (qAbs(fValue - fInvalidData) > fInvalidEPS)
				{
					if (fValue > dZMax)
						dZMax = fValue;
					if (fValue < dZMin)
						dZMin = fValue;

					pData[index++] = fValue;
				}
				else
				{
					pData[index++] = ::g_dInvalidData;
				}
			}
		}
	}

	qFile.close();

	if (index != nSize)
	{
		delete[]pData;
		QMessageBox::warning(0, g_strProductName, QString("The file ") + strHorizonFileName + " is corrupt!");
		return false;
	}

	m_ImPara.m_vecZMin.clear();
	m_ImPara.m_vecZMax.clear();
	m_ImPara.m_vecZMin.push_back(dZMin);
	m_ImPara.m_vecZMax.push_back(dZMax);

	m_ImPara.m_vecVecZ.resize(1);
	m_ImPara.m_vecVecZ.at(0).resize(nSize);

	int nI = m_ImPara.m_nI;
	int nJ = m_ImPara.m_nJ;
	float* pVecData = &m_ImPara.m_vecVecZ[0][0];
	if (m_eFileType == eZMapASCII)
	{
		int idx = 0;
		for (int i = 0; i < nI; ++i)
		{
			for (int j = 0; j < nJ; ++j)
			{
				pVecData[idx++] = pData[j*nI + (nI - i - 1)];
			}
		}
	}
	else
	{
		memcpy(pVecData, pData, sizeof(float)*nI*nJ);
	}

	delete[]pData;
	return true;
}

bool CXImport3DSurfaceManager::_ImportGeneralColumnHorizonData()
{
	QFile qFile(m_sFileName);
	if (!qFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(0, "Warning", "Unable to import data from file:" + m_sFileName);
		return false;
	}

	// Get the file size and file name
	QFileInfo fileInfo(m_sFileName);
	qint64 nFileSize = fileInfo.size();
	QString strLabelFileName = QString("Importing File: ") + fileInfo.baseName();

	// progress bar
	CXProgressBar progress("Import Horizon", strLabelFileName, nFileSize);

	// The maximum column index user selected.
	int nMaxColIndex = qMax(qMax(m_ImPara.m_nInlineIndex, m_ImPara.m_nCrosslineIndex),
							qMax(m_ImPara.m_nXIndex, m_ImPara.m_nYIndex));
	for (int i = 0; i < m_ImPara.m_nHorizonCount; ++i)
		nMaxColIndex = qMax(nMaxColIndex, m_ImPara.m_vecDataIndex[i]);
	double fInvalidEPS = ::GetEPSofInvalidData((float)m_ImPara.m_fInvalidData);

	// Initialization
	m_ImPara.ResetMinMaxValues();
	m_ImPara.ClearDataBuffer();
	m_ImPara.m_vecVecZ.resize(m_ImPara.m_nHorizonCount);
	std::vector<float> pZ;
	pZ.resize(m_ImPara.m_nHorizonCount);
	m_bAbort = false;

	QStringList strList;
	QString strLine;
	int nValidRow = 0;
	int nRow = 0;
	qint64 nStart = 0, nEnd;
	bool bAllowEmptyEntry = m_Delimiter.IsAllowBlankItem();
	QTextStream stream(&qFile);
	//while (!qFile.atEnd() && nRow <= m_ImPara.m_iLastLineNum)
	while (!stream.atEnd() && nRow <= m_ImPara.m_iLastLineNum)
	{
		//   Cancel 
		if (progress.IsAborted())
		{
			return false;
		}
		nRow++;

		//progress
		progress.SetValue(qFile.pos());

		strLine = stream.readLine();
		if (nRow < m_ImPara.m_iFirstLineNum)
			continue;

		// Reserve some memory space
		if (nValidRow == 1)
			nStart = qFile.pos();
		else if (nValidRow == 2)
		{
			nEnd = qFile.pos();
			//int nRows = (int)(nFileSize / (nEnd - nStart));
			int nRows = m_ImPara.m_iLastLineNum - m_ImPara.m_iFirstLineNum + 1;
			m_ImPara.m_vecInline.reserve(nRows);
			m_ImPara.m_vecXline.reserve(nRows);
			m_ImPara.m_vecX.reserve(nRows);
			m_ImPara.m_vecY.reserve(nRows);
			for (int i = 0; i < m_ImPara.m_nHorizonCount; ++i)
				m_ImPara.m_vecVecZ.at(i).reserve(nRows);
		}

		//strLine = qFile.readLine();
		strLine = strLine.simplified();

		if (bAllowEmptyEntry)
			strList = m_Delimiter.GetSplittedString(strLine);
		else
			strList = strLine.split(" ", QString::SkipEmptyParts);

		if (strList.size() <= nMaxColIndex)
		{
			strList = m_Delimiter.GetSplittedString(strLine);
		}

		if (strList.size() <= nMaxColIndex)
		{
			continue;
		}

		if (!m_ImPara.ParseOneLineData(strList, &pZ[0], fInvalidEPS))
			continue;

		nValidRow++;
	}

	progress.setValue(nFileSize);

	qFile.close();

	if (nValidRow <= 0)
	{
		m_ImPara.ClearDataBuffer();
		QMessageBox::warning(0, ::g_strProductName, "Unable to import from file:" + m_sFileName);
		return false;
	}

	// Calculate both inline and crossline increments
	m_ImPara.CalculateLineIncrement();

	return true;
}


bool CXImport3DSurfaceManager::VerifyFileFormat(const CXDelimiter& delimiter, const QStringList& listColumnNames, int iFirstLineNum, int iLastLineNum, double fInvalid)
{
	if (m_eFileType == eZMapASCII)
		return _VerifyZMapGridASCII();
	else if (m_eFileType == e3DHorizonPicks)
		return _VerifyHorizonPicks(delimiter, listColumnNames, iFirstLineNum, iLastLineNum, fInvalid);

	else
		return false;
}

bool CXImport3DSurfaceManager::ImportData()
{
	if (m_eFileType == eZMapASCII)
		return _ImportGeneralSurfaceData();
	else if (m_eFileType == e3DHorizonPicks)
		return _ImportGeneralColumnHorizonData();
	else
		return false;
}

void CXImport3DSurfaceManager::CopyPara(CXImport3DSurfaceManager* pOther)
{
	if (!pOther)
		return;

	m_eFileType = pOther->m_eFileType;

	m_ImPara.m_nInlineIndex = pOther->m_ImPara.m_nInlineIndex;
	m_ImPara.m_nCrosslineIndex = pOther->m_ImPara.m_nCrosslineIndex;
	m_ImPara.m_nXIndex = pOther->m_ImPara.m_nXIndex;
	m_ImPara.m_nYIndex = pOther->m_ImPara.m_nYIndex;
	m_ImPara.m_vecDataIndex = pOther->m_ImPara.m_vecDataIndex;
	m_ImPara.m_fInvalidData = pOther->m_ImPara.m_fInvalidData;
	m_ImPara.m_nHorizonCount = pOther->m_ImPara.m_nHorizonCount;
	m_ImPara.m_nInlineIndex = pOther->m_ImPara.m_nInlineIndex;
	m_ImPara.m_nIIndex = pOther->m_ImPara.m_nIIndex;
	m_ImPara.m_nJIndex = pOther->m_ImPara.m_nJIndex;
	m_ImPara.m_nHorizonType = pOther->m_ImPara.m_nHorizonType;
	m_ImPara.m_iFirstLineNum = pOther->m_ImPara.m_iFirstLineNum;
	m_ImPara.m_iLastLineNum = pOther->m_ImPara.m_iLastLineNum;
}

void CXImport3DSurfaceManager::GetXYZMinMax(int index, double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	dXMin = m_ImPara.m_dXMin;
	dXMax = m_ImPara.m_dXMax;
	dYMin = m_ImPara.m_dYMin;
	dYMax = m_ImPara.m_dYMax;

	if (m_ImPara.m_vecZMin.size() > index && m_ImPara.m_vecZMax.size() > index)
	{
		dZMin = m_ImPara.m_vecZMin.at(index);
		dZMax = m_ImPara.m_vecZMax.at(index);
	}
	else
	{
		dZMin = -1.0;
		dZMax = -1.0;
	}
}

void CXImport3DSurfaceManager::WipeStripNumber()
{
	if (m_ImPara.m_dXMax < 10000000)
		return;

	int iBase = (int)m_ImPara.m_dXMax / 1000000;
	iBase *= 1000000;
	m_ImPara.m_dXMax -= iBase;
	m_ImPara.m_dXMin -= iBase;

	if (!m_ImPara.m_vecX.empty())
	{
		int nSize = m_ImPara.m_vecX.size();
		for (int i = 0; i < nSize; ++i)
		{
			m_ImPara.m_vecX[i] -= iBase;
		}
	}
}

bool CXImport3DSurfaceManager::GetRegularUTMTool(CXUTMTool* pUTM, bool bWithoutZone)
{
	if (!pUTM->InitSize(m_ImPara.m_nI, m_ImPara.m_nJ))
		return false;

	if (!pUTM->InitCoordinates(0, 0, m_ImPara.m_dXMin, m_ImPara.m_dYMin,
		0, m_ImPara.m_nJ - 1, m_ImPara.m_dXMax, m_ImPara.m_dYMin,
		m_ImPara.m_nI - 1, 0, m_ImPara.m_dXMin, m_ImPara.m_dYMax))
		return false;

	if (bWithoutZone)
		pUTM->RemoveXStrip();

	return true;
}

void CXImport3DSurfaceManager::SetHorizonName(int index, const QString& strName)
{
	if (index < 0 || index >= m_strListHorizonName.size())
		return;

	m_strListHorizonName[index] = strName;
}

void CXImport3DSurfaceManager::SetUnitConversionRatios(float fXRatio, float fYRatio, float fZRatio)
{
	double dInvalid = g_dInvalidData;
	double dInvalidEPS = ::GetEPSofInvalidData(dInvalid);
	int nSize = m_ImPara.m_vecX.size();
	for (int i = 0; i < nSize; ++i)
	{
		if (qAbs(m_ImPara.m_vecX[i] - dInvalid) < dInvalidEPS)
			continue;

		m_ImPara.m_vecX[i] *= fXRatio;
	}

	nSize = m_ImPara.m_vecY.size();
	for (int i = 0; i < nSize; ++i)
	{
		if (qAbs(m_ImPara.m_vecY[i] - dInvalid) < dInvalidEPS)
			continue;

		m_ImPara.m_vecY[i] *= fYRatio;
	}

	m_ImPara.m_dXMin *= fXRatio;
	m_ImPara.m_dXMax *= fXRatio;
	m_ImPara.m_dYMin *= fYRatio;
	m_ImPara.m_dYMax *= fYRatio;

	// Z
	float fInvalid = ::g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	int nHorizonNum = m_ImPara.m_vecVecZ.size();
	for (int i = 0; i < nHorizonNum; ++i)
	{
		nSize = m_ImPara.m_vecVecZ[i].size();
		for (int j = 0; j < nSize; ++j)
		{
			if (qAbs(m_ImPara.m_vecVecZ[i][j] - fInvalid) < fInvalidEPS)
				continue;

			m_ImPara.m_vecVecZ[i][j] *= fZRatio;
		}
	}

	nHorizonNum = m_ImPara.m_vecZMin.size();
	for (int i = 0; i < nHorizonNum; ++i)
	{
		m_ImPara.m_vecZMin[i] *= fZRatio;
		m_ImPara.m_vecZMax[i] *= fZRatio;
	}
}


bool CXImport3DSurfaceManager::GuessUTMTool(CXUTMTool* pUTM, bool bWithoutZone)
{
	if (!pUTM)
		return false;

	CXSeismicUTMTool* pSeismicUTM = dynamic_cast<CXSeismicUTMTool*>(pUTM);

	// Tell if data is valid
	const int COUNTNUM = 5;

	bool bLine = (m_ImPara.m_vecInline.size() > COUNTNUM && m_ImPara.m_vecXline.size() > COUNTNUM);
	bool bIJ = (m_ImPara.m_vecI.size() > COUNTNUM && m_ImPara.m_vecJ.size() > COUNTNUM);
	bool bXY = (m_ImPara.m_vecX.size() > COUNTNUM || m_ImPara.m_vecY.size() > COUNTNUM);

	if (!bXY)
		return false;
	if (pSeismicUTM)
	{
		if (!bLine)
			return false;
	}
	else
	{
		if (!bIJ)
			return false;
	}

	// Set size
	if (pSeismicUTM)     // Seismic UTM tool
	{
		int nNumInline = qAbs((m_ImPara.m_nInlineMax - m_ImPara.m_nInlineMin) / m_ImPara.m_nInlineInc) + 1;
		int nNumXline = qAbs((m_ImPara.m_nXlineMax - m_ImPara.m_nXlineMin) / m_ImPara.m_nXlineInc) + 1;
		pSeismicUTM->InitSize(m_ImPara.m_nInlineMin, nNumInline, m_ImPara.m_nInlineInc,
							  m_ImPara.m_nXlineMin, nNumXline, m_ImPara.m_nXlineInc);
	}
	else	    // UTM tool
	{
		pUTM->InitSize(m_ImPara.m_nI, m_ImPara.m_nJ);
	}

	double fInvalidData = m_ImPara.m_fInvalidData;
	double fEPSInvalid = ::GetEPSofInvalidData((float)fInvalidData);
	int nRowCount = m_ImPara.m_vecX.size();

	int inline1 = 0, inline2 = 0, inline3 = 0, xline1 = 0, xline2 = 0, xline3 = 0;	 // inline/xline or I/J
	double x1, x2, x3, y1, y2, y3;
	int row1, row2, row3;

	std::vector<double> fX0, fY0, fDIX, fDIY, fDJX, fDJY;
	fX0.resize(COUNTNUM);
	fY0.resize(COUNTNUM);
	fDIX.resize(COUNTNUM);
	fDIY.resize(COUNTNUM);
	fDJX.resize(COUNTNUM);
	fDJY.resize(COUNTNUM);

	double fXX0, fYY0, fDIXX, fDIYY, fDJXX, fDJYY;
	int count, nCycle;
	count = 0;
	nCycle = 0;
	while (count < COUNTNUM && nCycle < 10000)
	{
		// random choose three points to figure out geometry      
		row1 = static_cast<int>(1.0f*rand() / RAND_MAX*(nRowCount - 1));
		row2 = static_cast<int>(1.0f*rand() / RAND_MAX*(nRowCount - 1));
		row3 = static_cast<int>(1.0f*rand() / RAND_MAX*(nRowCount - 1));

		if (bLine)
		{
			inline1 = m_ImPara.m_vecInline[row1];
			inline2 = m_ImPara.m_vecInline[row2];
			inline3 = m_ImPara.m_vecInline[row3];
			xline1 = m_ImPara.m_vecXline[row1];
			xline2 = m_ImPara.m_vecXline[row2];
			xline3 = m_ImPara.m_vecXline[row3];
		}
		else if (bIJ)
		{
			inline1 = m_ImPara.m_vecI[row1];
			inline2 = m_ImPara.m_vecI[row2];
			inline3 = m_ImPara.m_vecI[row3];
			xline1 = m_ImPara.m_vecJ[row1];
			xline2 = m_ImPara.m_vecJ[row2];
			xline3 = m_ImPara.m_vecJ[row3];
		}

		x1 = m_ImPara.m_vecX[row1];
		x2 = m_ImPara.m_vecX[row2];
		x3 = m_ImPara.m_vecX[row3];
		y1 = m_ImPara.m_vecY[row1];
		y2 = m_ImPara.m_vecY[row2];
		y3 = m_ImPara.m_vecY[row3];

		if (qAbs((double)inline1 - fInvalidData) < fEPSInvalid ||
			qAbs((double)inline2 - fInvalidData) < fEPSInvalid ||
			qAbs((double)inline3 - fInvalidData) < fEPSInvalid ||
			qAbs((double)xline1 - fInvalidData) < fEPSInvalid ||
			qAbs((double)xline2 - fInvalidData) < fEPSInvalid ||
			qAbs((double)xline3 - fInvalidData) < fEPSInvalid ||
			qAbs(x1 - fInvalidData) < fEPSInvalid ||
			qAbs(x2 - fInvalidData) < fEPSInvalid ||
			qAbs(x3 - fInvalidData) < fEPSInvalid ||
			qAbs(y1 - fInvalidData) < fEPSInvalid ||
			qAbs(y2 - fInvalidData) < fEPSInvalid ||
			qAbs(y3 - fInvalidData) < fEPSInvalid)
			continue;

		nCycle++;

		if (!pUTM->InitCoordinates(inline1, xline1, x1, y1, inline2, xline2, x2, y2, inline3, xline3, x3, y3))
			continue;

		pUTM->IJToXY(0, 0, fXX0, fYY0);
		pUTM->IJToXY(1, 0, fDIXX, fDIYY);
		pUTM->IJToXY(0, 1, fDJXX, fDJYY);

		fX0[count] = fXX0;
		fY0[count] = fYY0;
		fDIX[count] = fDIXX - fXX0;
		fDIY[count] = fDIYY - fYY0;
		fDJX[count] = fDJXX - fXX0;
		fDJY[count] = fDJYY - fYY0;
		count++;
	}

	if (nCycle >= 10000)
		return false;

	fXX0 = fYY0 = fDIXX = fDIYY = fDJXX = fDJYY = 0.0;

	for (int i = 0; i < count; ++i)
	{
		fXX0 += fX0[i];
		fYY0 += fY0[i];
		fDIXX += fDIX[i];
		fDIYY += fDIY[i];
		fDJXX += fDJX[i];
		fDJYY += fDJY[i];
	}

	fXX0 /= count;
	fYY0 /= count;
	fDIXX /= count;
	fDIYY /= count;
	fDJXX /= count;
	fDJYY /= count;

	pUTM->CXUTMTool::InitCoordinates(0, 0, fXX0, fYY0, 1, 0, fXX0 + fDIXX, fYY0 + fDIYY, 0, 1, fXX0 + fDJXX, fYY0 + fDJYY);

	if (bWithoutZone)
		pUTM->RemoveXStrip();

	return true;
}

void CXImport3DSurfaceManager::ConvertColumnDataToSurface(CX3DSurface* pSurface, CXUTMTool* pDataUTM, int index, int nType)
{
	int nI_Surf = pSurface->GetUTM().GetNI();
	int nJ_Surf = pSurface->GetUTM().GetNJ();
	int nI_Data = pDataUTM->GetNI();
	int nJ_Data = pDataUTM->GetNJ();
	float* pSurfaceData = pSurface->GetData();
	CXUTMTool* SurfaceUTM = &(pSurface->GetUTM());
	assert(pSurfaceData);
	assert(pDataUTM);

	CXSeismicUTMTool* pDataSeismicUTM = dynamic_cast<CXSeismicUTMTool*>(pDataUTM);

	if (index < 0 || index >= m_ImPara.m_vecVecZ.size())
		return;
	float* pImportData = &m_ImPara.m_vecVecZ[index][0];
	float fInvalidData = ::g_dInvalidData;

	DataFormat eType = (DataFormat)nType;

	if (eType == e_H_Line)			// Horizon, have inline/xline, Surface UTM is same as data UTM
	{
		CXSeismicUTMTool* SurfaceSeismicUTM = dynamic_cast<CXSeismicUTMTool*>(SurfaceUTM);

		int* pInline = &m_ImPara.m_vecInline[0];
		int* pXline = &m_ImPara.m_vecXline[0];
		int iInlineNum, iXlineNum, iI, iJ;
		int nRowCount = m_ImPara.m_vecInline.size();

		for (int i = 0; i < nRowCount; ++i)
		{
			iInlineNum = pInline[i];
			iXlineNum = pXline[i];

			if (!SurfaceSeismicUTM->LineToIJ(iInlineNum, iXlineNum, iI, iJ))
				continue;

			pSurfaceData[iI*nJ_Surf + iJ] = pImportData[i];
		}
	}
	else if (eType == e_H_Line_XY) // Horizon, have line/xline, X/Y
	{
		// Set import data
		CXSeismicUTMTool* SurfaceSeismicUTM = dynamic_cast<CXSeismicUTMTool*>(SurfaceUTM);

		int nDataSize = nI_Data*nJ_Data;
		float* pData = new float[nDataSize];
		for (int i = 0; i < nDataSize; ++i)
			pData[i] = fInvalidData;

		int* pInline = &m_ImPara.m_vecInline[0];
		int* pXline = &m_ImPara.m_vecXline[0];
		int iInlineNum, iXlineNum, iI, iJ;
		int nRowCount = m_ImPara.m_vecInline.size();

		for (int i = 0; i < nRowCount; ++i)
		{
			iInlineNum = pInline[i];
			iXlineNum = pXline[i];

			if (!SurfaceSeismicUTM->LineToIJ(iInlineNum, iXlineNum, iI, iJ))
				continue;

			if (iI >= nI_Data || iJ >= nJ_Data)
				continue;

			pData[iI*nJ_Data + iJ] = pImportData[i];
		}

		// Set surface data
		double dX, dY;
		for (int i = 0; i < nI_Surf; ++i)
		{
			for (int j = 0; j < nJ_Surf; ++j)
			{
				SurfaceUTM->IJToXY(i, j, dX, dY);
				if (!pDataSeismicUTM->XYToIJ(dX, dY, iI, iJ))
					continue;

				pSurfaceData[i*nJ_Surf + j] = pData[iI*nJ_Data + iJ];
			}
		}

		delete[]pData;
	}
	else if (eType == e_H_IJ_XY) // Horizon, have I/J, X/Y
	{
		// Set import data
		int nDataSize = nI_Data*nJ_Data;
		float* pData = new float[nDataSize];
		for (int i = 0; i < nDataSize; ++i)
			pData[i] = fInvalidData;

		double* pX = &m_ImPara.m_vecX[0];
		double* pY = &m_ImPara.m_vecY[0];
		double dX, dY;
		int iI, iJ;
		int nRowCount = m_ImPara.m_vecX.size();
		for (int i = 0; i < nRowCount; ++i)
		{
			dX = pX[i];
			dY = pY[i];

			if (!pDataUTM->XYToIJ(dX, dY, iI, iJ))
				continue;

			pData[iI*nJ_Data + iJ] = pImportData[i];
		}

		// Set surface data		
		for (int i = 0; i < nI_Surf; ++i)
		{
			for (int j = 0; j < nJ_Surf; ++j)
			{
				SurfaceUTM->IJToXY(i, j, dX, dY);
				if (!pDataUTM->XYToIJ(dX, dY, iI, iJ))
					continue;

				pSurfaceData[i*nJ_Surf + j] = pData[iI*nJ_Data + iJ];
			}
		}

		delete[]pData;
	}
	else if (eType == e_H_XY) // Horizon, have X/Y	
	{
		// Set surface data
		double* pX = &m_ImPara.m_vecX[0];
		double* pY = &m_ImPara.m_vecY[0];
		double dX, dY;
		int iI, iJ;
		int nRowCount = m_ImPara.m_vecX.size();
		for (int i = 0; i < nRowCount; ++i)
		{
			dX = pX[i];
			dY = pY[i];

			if (!SurfaceUTM->XYToIJ(dX, dY, iI, iJ))
				continue;

			pSurfaceData[iI*nJ_Surf + iJ] = pImportData[i];
		}
	}
	else if (eType == e_H)  // Horizon, only have data
	{
		// Set surface data
		double dX, dY;
		int iI, iJ;
		for (int i = 0; i < nI_Surf; ++i)
		{
			for (int j = 0; j < nJ_Surf; ++j)
			{
				SurfaceUTM->IJToXY(i, j, dX, dY);
				if (!pDataUTM->XYToIJ(dX, dY, iI, iJ))
					continue;

				pSurfaceData[i*nJ_Surf + j] = pImportData[iI*nJ_Data + iJ];
			}
		}
	}
	else if (eType == e_S_Line_XY) // Surface, have inline/crossline, X/Y
	{
		// Set Surface data
		assert(pDataSeismicUTM);

		int* pInline = &m_ImPara.m_vecInline[0];
		int* pXline = &m_ImPara.m_vecXline[0];
		int iInlineNum, iXlineNum, iI, iJ;
		int nRowCount = m_ImPara.m_vecInline.size();

		for (int i = 0; i < nRowCount; ++i)
		{
			iInlineNum = pInline[i];
			iXlineNum = pXline[i];

			if (!pDataSeismicUTM->LineToIJ(iInlineNum, iXlineNum, iI, iJ))
				continue;

			pSurfaceData[iI*nJ_Surf + iJ] = pImportData[i];
		}
	}
	else if (eType == e_S_IJ_XY) // Surface, have I/J, X/Y
	{
		// Set Surface data
		int* pI = &m_ImPara.m_vecI[0];
		int* pJ = &m_ImPara.m_vecJ[0];
		int iI, iJ;
		int nRowCount = m_ImPara.m_vecX.size();
		for (int i = 0; i < nRowCount; ++i)
		{
			iI = pI[i];
			iJ = pJ[i];

			if (iI < 0 || iI >= nI_Surf || iJ < 0 || iJ >= nJ_Surf)
				continue;

			pSurfaceData[iI*nJ_Surf + iJ] = pImportData[i];
		}
	}
	else if (eType == e_S)	// Surface, only have data
	{
		memcpy(pSurfaceData, pImportData, sizeof(float)*nI_Surf *nJ_Surf);
	}

}

void CXImport3DSurfaceManager::GetDataFlag(bool& bInline, bool& bXline, bool& bX, bool& bY, bool& bI, bool& bJ)
{
	bInline = !m_ImPara.m_vecInline.empty();
	bXline = !m_ImPara.m_vecXline.empty();
	bX = !m_ImPara.m_vecX.empty();
	bY = !m_ImPara.m_vecY.empty();
	bI = !m_ImPara.m_vecI.empty();
	bJ = !m_ImPara.m_vecJ.empty();
}

void CXImport3DSurfaceManager::GetLineRange(int& iInlineMin, int& iInlineMax, int& iInlineInc, int& iXlineMin, int& iXlineMax, int& iXlineInc)
{
	iInlineMin = m_ImPara.m_nInlineMin;
	iInlineMax = m_ImPara.m_nInlineMax;
	iInlineInc = m_ImPara.m_nInlineInc;
	iXlineMin = m_ImPara.m_nXlineMin;
	iXlineMax = m_ImPara.m_nXlineMax;
	iXlineInc = m_ImPara.m_nXlineInc;
}


