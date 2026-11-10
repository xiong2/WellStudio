#include <qfileinfo.h>
#include <qmessagebox.h>
#include "xlaswisfile.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xwellpath.h"
#include "xwellnmr.h"
#include "xunit.h"
#include "xglobal.h"
#include "xdataconvertor.h"
#include "xdlisparser.h"
#include "xwaitcursor.h"
#include "xproject.h"

CXLasWisFile::CXLasWisFile(QString sFile, int iFileType)
{
	m_iFileType		= iFileType;
	m_sFileName		= sFile;
	m_sDelimiter	= " ";	//	Default is space.
	m_dInvalid		= ::g_dInvalidData;
	m_pWell			= NULL;
	m_dStart		= 99999.;
	m_dStop			= -99999.;
	m_dStep = 0.;
	m_pDLISParser	= NULL;
	m_bWrapped		= false;
}

CXLasWisFile::~CXLasWisFile()
{
	if(m_qFile.isOpen())
		m_qFile.close();

	if (!m_pDLISParser)
		delete m_pDLISParser;
}

QString CXLasWisFile::GetFileName(bool bNoPath)
{
	if(!bNoPath)
		return m_sFileName;

	QFileInfo qFI(m_sFileName);
	return qFI.fileName();
}

//	Parse the file to extract basic well informatoin.
bool CXLasWisFile::ParseFile()
{
	if (m_qFile.isOpen())
		m_qFile.close();

	m_qFile.setFileName(m_sFileName);
	if (!m_qFile.open(QIODevice::ReadOnly))
		return false;

	if (m_iFileType == 0)
		return parseLASFile();
	else if(m_iFileType == 1)
		return parseWISFile();
	else if (m_iFileType == 2)
		return parseXTFFile();
	else if (m_iFileType == 3)
		return parseDLISFile();

	return false;
}

bool CXLasWisFile::parseLASFile()
{
	QString sLine;
	m_qStream.setDevice(&m_qFile);
	while(!m_qStream.atEnd())
	{
		sLine = m_qStream.readLine();
		if(sLine == "" || sLine.startsWith("#"))
			continue;

		//	Version information.
		if(sLine.startsWith("~V", Qt::CaseInsensitive))
		{
			while(!m_qStream.atEnd())
			{
				sLine = m_qStream.readLine();
				if(sLine == "" || sLine.startsWith("#"))
					continue;

				sLine = sLine.trimmed();

				//	This means the begining of next section, just break.
				if(sLine.startsWith("~"))
					break;

				//	Wrapped?
				if (sLine.startsWith("WRAP", Qt::CaseInsensitive))
				{
					if (sLine.contains("YES", Qt::CaseInsensitive))
						m_bWrapped = true;
				}

				//	Delimiter.
				if(sLine.startsWith("DLM"))
				{
					if(sLine.contains("TAB"))
						m_sDelimiter = "\t";
					else if(sLine.contains("COMMA"))
						m_sDelimiter = ",";
				}
			}
		}

		//	Well Information.
		double dFileX = ::g_dInvalidData, dFileY = ::g_dInvalidData;
		if(sLine.startsWith("~W", Qt::CaseInsensitive))
		{
			//	Create the well now.
			if(m_pWell)
				delete m_pWell;
			m_pWell = new CXWell("New Well");

			while(!m_qStream.atEnd())
			{
				sLine = m_qStream.readLine();
				if(sLine == "" || sLine.startsWith("#"))
					continue;

				sLine = sLine.trimmed();

				//	This means the begining of next section, just break.
				if(sLine.startsWith("~"))
					break;

				if(sLine.startsWith("Comp", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("Company", getValue(sLine));
				}
				else if(sLine.startsWith("WELL", Qt::CaseInsensitive))
				{
					m_pWell->SetObjectName(getValue(sLine));
				}
				else if(sLine.startsWith("FLD", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("Field", getValue(sLine));
				}
				else if(sLine.startsWith("LOC", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("Location", getValue(sLine));
				}
				else if(sLine.startsWith("SRVC", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("Service", getValue(sLine));
				}
				else if(sLine.startsWith("CTRY", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("Country", getValue(sLine));
				}
				else if(sLine.startsWith("DATE", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("Date", getValue(sLine));
				}
				else if(sLine.startsWith("X", Qt::CaseInsensitive))
				{
					dFileX = getValue(sLine).toDouble();
				}
				else if(sLine.startsWith("Y", Qt::CaseInsensitive))
				{
					dFileY = getValue(sLine).toDouble();
				}
				else if(sLine.startsWith("KB", Qt::CaseInsensitive))
				{
					m_pWell->SetKB(getValue(sLine).toDouble());
				}
				else if(sLine.startsWith("API", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("API", getValue(sLine));
				}
				else if(sLine.startsWith("UWI", Qt::CaseInsensitive))
				{
					QString sUWI = getValue(sLine);
					
					//	Wipe out the delimiter.
					sUWI.remove("-");

					m_pWell->AddAttribute("UWI", sUWI);
				}	
				else if(sLine.startsWith("STAT", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("State", getValue(sLine));
				}
				else if(sLine.startsWith("CNTY", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("COUNTY", getValue(sLine));
				}
				else if(sLine.startsWith("PROV", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("Province", getValue(sLine));
				}
				else if(sLine.startsWith("LIC", Qt::CaseInsensitive))
				{
					m_pWell->AddAttribute("License", getValue(sLine));
				}
				else if(sLine.startsWith("STRT", Qt::CaseInsensitive)
					|| sLine.startsWith("START", Qt::CaseInsensitive))
				{
					m_dStart = getValue(sLine).toDouble();
					m_sDepthUnit = getUnit(sLine);
				}
				else if(sLine.startsWith("STOP", Qt::CaseInsensitive))
				{
					m_dStop = getValue(sLine).toDouble();
				}
				else if(sLine.startsWith("STEP", Qt::CaseInsensitive))
				{
					double fStep = getValue(sLine).toDouble();
					if (fStep != 0.)
					{
						m_dStep = fStep;
					}
				}
				else if(sLine.startsWith("NULL", Qt::CaseInsensitive))
				{
					m_dInvalid = getValue(sLine).toDouble();
				}
			}
		}

		//	If well still not exist, can not go on.
		if(!m_pWell)
			return false;

		if (m_dStep==0.
			|| m_dStart == 99999.
			|| m_dStop == -99999.)
		{
			return false;
		}

		//	Need correct the well range by its units.
		QString sPrjDUnit = "ft";
		if (::GetProject()->UsingMetricUnit())
			sPrjDUnit = "m";
		if (m_sDepthUnit != sPrjDUnit)
		{
			float fRatio = CXUnit::GetConvertRatio(m_sDepthUnit, sPrjDUnit);
			m_dStart *= fRatio;
			m_dStep *= fRatio;
			m_dStop *= fRatio;
			m_sDepthUnit = sPrjDUnit;
		}

		//	If the well does not contain coordinates, try to find then from attributes.
		double dWellX, dWellY;
		m_pWell->GetWellPosition(dWellX, dWellY);
		if(dWellX == ::g_dInvalidData || dWellY == ::g_dInvalidData)
		{
			if(dFileX == ::g_dInvalidData || dFileY == ::g_dInvalidData)
			{
				//	No X, Y given in LAS file, then try location.
				QString strLocation = m_pWell->GetAttribute("Location");

				if(!strLocation.isEmpty())
				{
					QStringList strListXY = strLocation.split(",");
					if(strListXY.size() != 2)
						strListXY = strLocation.split(" ");

					if(strListXY.size() == 2)
					{
						dFileX = strListXY[0].toDouble();
						dFileY = strListXY[1].toDouble();
					//	m_pWell->AddAttribute("X", QString::number(dFileX, 'f', 6));
					//	m_pWell->AddAttribute("Y", QString::number(dFileY, 'f', 6));
					}
				}
			}

			if(dFileX != ::g_dInvalidData && dFileY != ::g_dInvalidData)
			{
				//	Got X, Y, then reset coordinates of well path.
				unsigned int iNumber;
				CXWellPath *pWellPath = m_pWell->GetWellPath();
				double *pData = pWellPath->GetData(iNumber);

				iNumber /= 3;
				for(int i = 0; i < iNumber; i++)
				{
					pData[3 * i]		= dFileX;
					pData[3 * i + 1]	= dFileY;
				}
			}
		}

		//	Curve information.
		if(sLine.startsWith("~C", Qt::CaseInsensitive))
		{
			while(!m_qStream.atEnd())
			{
				sLine = m_qStream.readLine();
				if(sLine == "" || sLine.startsWith("#"))
					continue;

				//	This means the begining of next section, just break.
				if(sLine.startsWith("~"))
				{
					break;
				}

				m_sListCurves<<getName(sLine);
				m_sListUnits<<CXUnit::GetStandardName(getUnit(sLine));
			}
		}

		if(!sLine.startsWith("~A"))
			continue;
		else
			break;
	}
	m_pWell->ExpandWellRange(m_dStart, m_dStop, m_dStep);

	return true;
}

bool CXLasWisFile::parseWISFile()
{
	m_sListCurves.clear();
	m_sListUnits.clear();
	m_vecOffset.clear();

	char pChar[1024], pName[16], pUnit[8];
	short *pSh = (short *)pChar;
	int *pInt = (int *)pChar;
	float *pF = (float *)pChar;

	//	File ID.
	m_qFile.read(pChar, 10);
	QString sID = QString(pChar);
	if (!sID.startsWith("WIS 1.0"))
		return false;

	//	File header.
	m_qFile.read(pChar, 56);
	short iObjNum = pSh[2];
	short iBlockSize = pSh[3];
	int iOffset = pInt[2];

	//	Let's loop to parse each object.
	for (int i = 0; i < iObjNum; i++)
	{
		m_qFile.read(pChar, 72);
		
		//	So far only accept track objects.
		if (pSh[10] != 1)
			continue;

		//	Curve name.
		memcpy(pName, pChar, 16);
		QString sName = QString(pName);
		m_sListCurves << sName;

		//	Curve start offset.
		m_vecOffset << pInt[6];

		//	Curve unit.
		qint64 iPos = m_qFile.pos();
		m_qFile.seek(pInt[6]);
		m_qFile.read(pChar, 56);
		memcpy(pUnit, pChar, 8);
		QString sUnit = QString(pUnit);
		m_sListUnits << sUnit;

		if (pSh[27] == 1)
		{
			//	Read depth range.
			m_qFile.read(pChar, 56);
			float dStart = pF[8];
			if (dStart > 0 && dStart < 20000 && pInt[10] > 0 && pInt[10] < 200000)
			{
				m_dStep = pF[9];
				float dStop = dStart + pInt[10] * m_dStep;
				m_dStart = m_dStart < dStart ? m_dStart : dStart;
				m_dStop = m_dStop > dStop ? m_dStop : dStop;
			}
		}

		m_qFile.seek(iPos);
	}

	if (m_pWell)
		delete m_pWell;
	QFileInfo qFI(m_sFileName);
	m_pWell = new CXWell(qFI.baseName());
	m_pWell->ExpandWellRange(m_dStart, m_dStop, m_dStep);

	return true;
}

bool CXLasWisFile::parseXTFFile()
{
	int i, j;
	m_sListCurves.clear();
	m_sListUnits.clear();
	m_vecOffset.clear();

	char pChar[4096];
	short *pSh = (short *)pChar;
	int *pInt = (int *)pChar;
	float *pF = (float *)pChar;

	//	1st record.
	m_qFile.read(pChar, 4096);
	flip((unsigned char *)pChar, 516);
	int iNumCurves = pInt[249];
	m_dStart = pF[512];
	m_dStop = pF[513];
	m_dStep = pF[514];

	//	4th record, start of each curve.
	m_qFile.seek(3 * 4096);
	m_qFile.read(pChar, 4096);
	flip((unsigned char *)pChar, 512);

	int iHalfNum = qMin(256, iNumCurves);
	for (i = 0; i < iHalfNum; i++)
	{
		m_vecOffset << pInt[2 * i] - 1;
	}

	for (i = 256; i < iNumCurves; i++)
	{
		m_vecOffset << pInt[2 * (i - 256) + 1] - 1;
	}

	//	Now loop to read each curve's name and unit.
	for (i = 0; i < iNumCurves; i++)
	{
		m_qFile.seek(m_vecOffset[i] * 4096);
		QByteArray qBAName = m_qFile.read(8);
		m_sListCurves << QString(qBAName).simplified();
		QByteArray qBAUnit = m_qFile.read(8);
		m_sListUnits << QString(qBAUnit).simplified();
	}

	if (m_pWell)
		delete m_pWell;


	//	8th record, well name.
	char pWellName[80];
	m_qFile.seek(7 * 4096 + 8);
	QByteArray qBA = m_qFile.read(80);
	QString sWellName = QString(qBA);
	sWellName = sWellName.simplified();
	m_pWell = new CXWell(sWellName);
	m_pWell->ExpandWellRange(m_dStart, m_dStop, m_dStep);

	return true;
}

bool CXLasWisFile::parseDLISFile()
{
	CXWaitCursor waitCursor;

	if (m_pDLISParser)
		delete m_pDLISParser;

	m_pDLISParser = new CXDLISParser(m_sFileName);

	bool bSta = m_pDLISParser->Parse();
	
	if (!bSta)
		return false;

	if (m_pWell)
		delete m_pWell;
	m_pWell = new CXWell(m_pDLISParser->GetWellName());

	m_pDLISParser->PopulateCurvesAndUnits(m_sListCurves, m_sListUnits);
	m_pDLISParser->PopulateWellRange(m_dStart, m_dStop, m_dStep);
	m_pWell->ExpandWellRange(m_dStart, m_dStop, m_dStep);

	return true;
}

//	Load curves stored in the file.
bool CXLasWisFile::LoadCurves(QStringList& sListCurves, QList<CXObject *>& listObj)
{
	if (m_iFileType == 0)
		return loadLASCurves(sListCurves, listObj);
	else if (m_iFileType == 1)
		return loadWISCurves(sListCurves, listObj);
	else if (m_iFileType == 2)
		return loadXTFCurves(sListCurves, listObj);
	else if (m_iFileType == 3)
		return loadDLISCurves(sListCurves, listObj);

	return false;
}

bool CXLasWisFile::loadLASCurves(QStringList& sListCurves, QList<CXObject *>& listObj)
{
	if(!m_qFile.isOpen())
		return false;

	QString sLine;
	unsigned int i, iCount, iNumCurve = m_sListCurves.size();
	double fStep = m_pWell->GetWellStep();
	if(fStep == 0.)
	{
		QMessageBox::warning(NULL, "Importing LAS Files", "Can not load LAS file with variable sample step!");
		return false;
	}

	unsigned int iNumPoints = (m_dStop - m_dStart) / fStep + 1.9;

	if(iNumCurve == 0)
		return true;

	//	Prepare the curves' data.
	double** pData = new double *[iNumCurve];
	for(i = 0; i < iNumCurve; i++)
	{
		if(sListCurves.contains(m_sListCurves[i]))
			pData[i] = new double[iNumPoints];
		else
			pData[i] = NULL;
	}

	iCount = 0;
	QStringList sListValue;
	if (m_bWrapped)
	{
		while (!m_qStream.atEnd() && iCount < iNumPoints)
		{
			sLine = m_qStream.readLine();
			if (sLine == "" || sLine.startsWith("#"))
				continue;

			//	Meet other section, break;
			if (sLine.startsWith("~"))
				break;

			sListValue = sLine.split(m_sDelimiter);
			sListValue.removeAll("");
			while (sListValue.size() < iNumCurve)
			{
				sLine = m_qStream.readLine();
				if (sLine == "" || sLine.startsWith("#"))
					continue;

				//	Meet other section, break;
				if (sLine.startsWith("~"))
					break;

				QStringList sSLListValue = sLine.split(m_sDelimiter);
				sSLListValue.removeAll("");
				sListValue += sSLListValue;
			}

			for (i = 0; i < iNumCurve; i++)
			{
				if (pData[i] != NULL)
				{
					double fValue = sListValue[i].toDouble();
					if (fValue == m_dInvalid)
						pData[i][iCount] = ::g_dInvalidData;
					else
						pData[i][iCount] = fValue;
				}
			}

			iCount++;
		}
	}
	else
	{
		while(!m_qStream.atEnd() && iCount < iNumPoints)
		{
			sLine = m_qStream.readLine();
			if(sLine == "" || sLine.startsWith("#"))
				continue;

			//	Meet other section, break;
			if(sLine.startsWith("~"))
				break;
		
			sListValue = sLine.split(m_sDelimiter);
			sListValue.removeAll("");
			if(sListValue.size() != iNumCurve)
				continue;

			for(i = 0; i < iNumCurve; i++)
			{
				if(pData[i] != NULL)
				{
					double fValue = sListValue[i].toDouble();
					if(fValue == m_dInvalid)
						pData[i][iCount] = ::g_dInvalidData;
					else
						pData[i][iCount] = fValue;
				}
			}

			iCount++;
		}
	}

	//	Create the curves.
	for(i = 0; i <iNumCurve; i++)
	{
		if(pData[i] == NULL)
			continue;

		QString strNewName = m_sListCurves[i];
		strNewName = m_pWell->GetUnallocatedName(strNewName);
		if (sListCurves.contains(m_sListCurves[i]))
			sListCurves[sListCurves.indexOf(m_sListCurves[i])] = strNewName;


		CXWellCurve *pCurve = new CXWellCurve(strNewName);
		pCurve->ResetData(m_dStart, fStep, iCount, pData[i]);
		m_pWell->AddChild(pCurve);

		listObj.append(pCurve);
	}

	delete []pData;

	return true;
}

bool CXLasWisFile::loadWISCurves(QStringList& sListCurves, QList<CXObject *>& listObj)
{
	if (!m_qFile.isOpen())
		return false;

	float fInv = -9999.;	//	Is it a standard of WIS file?
	char pChar[1024];
	short *pSh = (short *)pChar;
	int *pInt = (int *)pChar;
	float *pF = (float *)pChar;

	float *pBuffer = NULL;
	int iBufferSize = 0;

	for (int i = 0; i < m_sListCurves.size(); i++)
	{
		//	Abort the curves not selected by user.
		if (!sListCurves.contains(m_sListCurves[i]))
			continue;

		m_qFile.seek(m_vecOffset[i]);
		m_qFile.read(pChar, 1024);

		int iNumSample = 0;
		int iDim = pSh[27];
		if (iDim == 1)
		{
			//	One dimension curve.
			iNumSample = pInt[24];
			if (iNumSample > iBufferSize)
			{
				if (iBufferSize > 0)
					delete pBuffer;

				iBufferSize = iNumSample;
				pBuffer = new float[iBufferSize];
			}

			m_qFile.read((char *)pBuffer, sizeof(float) * iNumSample);

			QString strNewName = m_sListCurves[i];
			//strNewName = m_pWell->GetUnallocatedName(strNewName);
			//if (sListCurves.contains(m_sListCurves[i]))
			//	sListCurves[sListCurves.indexOf(m_sListCurves[i])] = strNewName;

			double *pData = new double[iNumSample];
			for (int j = 0; j < iNumSample; j++)
			{
				if (pBuffer[j] == fInv)
					pData[j] = ::g_dInvalidData;
				else
					pData[j] = pBuffer[j];
			}

			CXWellCurve *pCurve = new CXWellCurve(strNewName);
			pCurve->ResetData(pF[22], pF[23], iNumSample, pData);
			m_pWell->AddChild(pCurve);

			listObj.append(pCurve);
		}
		else if (iDim == 2)
		{
			//	2D data.
			char pName[8];
			memcpy(pName, pChar + 56, 8);
			QString sName1 = QString(pName);
			float fStartDepth = pF[22];
			float fDepthInc = pF[23];
			int iSamNum1 = pInt[24];

			memcpy(pName, pChar + 112, 8);
			QString sName2 = QString(pName);
			float fStart2 = pF[36];
			float fInc2 = pF[37];
			int iSamNum2 = pInt[38];

			qint64 iTotalSize = iSamNum1 * iSamNum2;
			float *pTmpData = new float[iTotalSize];
			m_qFile.read((char *)pTmpData, sizeof(float) * iTotalSize);

			CXObject *pFolder = m_pWell->GetFolder(EXNMRFolder, true);
			CXWellNMR *pNMR = new CXWellNMR(fStartDepth, fDepthInc, iSamNum1, fStart2, fInc2, iSamNum2, m_sListCurves[i]);
			pFolder->AddChild(pNMR);

			int iIDX = 0, iIDX1, iIDX2;
			float *pData = pNMR->GetDataCache();
			for (iIDX1 = 0; iIDX1 < iSamNum1; iIDX1++)
			{
				for (iIDX2 = 0; iIDX2 < iSamNum2; iIDX2++)
				{
					if (pTmpData[iIDX] == -999.)
						pData[iIDX2] = ::g_dInvalidData;
					else
						pData[iIDX2] = pTmpData[iIDX];

					iIDX++;
				}

				pNMR->WriteTraceData(iIDX1);
			}

			pNMR->CloseFile();
			pNMR->SetModifiedFlag();
			::AddObjectEvent(pNMR);

			listObj.append(pNMR);

			delete[]pTmpData;
		}
	}

	if (pBuffer)
		delete[]pBuffer;

	return true;
}

bool CXLasWisFile::loadXTFCurves(QStringList& sListCurves, QList<CXObject *>& listObj)
{
	if (!m_qFile.isOpen())
		return false;

	float fInv = -9999.;	//	Is it a standard of WIS file?
	char pChar[4096];

	float *pBuffer = NULL;
	int iBufferSize = 0;

	for (int i = 0; i < m_sListCurves.size(); i++)
	{
		//	Abort the curves not selected by user.
		if (!sListCurves.contains(m_sListCurves[i]))
			continue;

		m_qFile.seek(m_vecOffset[i] * 4096);
		m_qFile.read(pChar, 4096);

		char *pChValue = pChar + 1024;
		flip((unsigned char *)pChValue, 3);

		float *pFDepth = (float *)pChValue;
		int iNumSample = (pFDepth[1] - pFDepth[0]) / pFDepth[2] + 1;

		if (iNumSample > iBufferSize)
		{
			if (iBufferSize > 0)
				delete pBuffer;

			iBufferSize = iNumSample;
			pBuffer = new float[iBufferSize];
		}

		m_qFile.read((char *)pBuffer, sizeof(float) * iNumSample);
		flip((unsigned char *)pBuffer, iNumSample);

		QString strNewName = m_sListCurves[i];
		strNewName = m_pWell->GetUnallocatedName(strNewName);
		if (sListCurves.contains(m_sListCurves[i]))
			sListCurves[sListCurves.indexOf(m_sListCurves[i])] = strNewName;

		double *pData = new double[iNumSample];
		for (int j = 0; j < iNumSample; j++)
		{
			if (pBuffer[j] == fInv)
				pData[j] = ::g_dInvalidData;
			else
				pData[j] = pBuffer[j];
		}

		CXWellCurve *pCurve = new CXWellCurve(strNewName);
		pCurve->ResetData(pFDepth[0], pFDepth[2], iNumSample, pData);
		m_pWell->AddChild(pCurve);

		listObj.append(pCurve);
	}

	if (pBuffer)
		delete[]pBuffer;

	return true;
}

bool CXLasWisFile::loadDLISCurves(QStringList& sListCurves, QList<CXObject *>& listObj)
{
	return m_pDLISParser->LoadCurves(m_pWell, sListCurves, listObj);
}

//	Get the name from the line, name before the first "."
QString CXLasWisFile::getName(QString sLine)
{
	QString str = "";
	int iIDX = sLine.indexOf(".");
	if(iIDX != -1)
	{
		str = sLine.left(iIDX);
		str = str.trimmed();
	}

	if(str == "")
		str = "Unknown";

	return str;
}

//	Get the value from the line, value between ".unit " and ":".
QString CXLasWisFile::getValue(QString sLine)
{
	QString sValue = "";

	sLine = sLine.simplified();
	int iPeriod = sLine.indexOf(".");
	int iIDX = sLine.indexOf(" ", iPeriod);
	int iColon = sLine.indexOf(":");

	if(iColon > iIDX)
		sValue = sLine.mid(iIDX + 1, iColon - iIDX -1);

	return sValue;
}

//	Get the unit from the line, unit just after the 1st ".".
QString CXLasWisFile::getUnit(QString sLine)
{
	QString sUnit = "";
	int iPeriod = sLine.indexOf(".");
	int iIDX = sLine.indexOf(" ", iPeriod);

	if(iIDX > iPeriod + 1)
		sUnit = sLine.mid(iPeriod + 1, iIDX - iPeriod - 1);

	return sUnit;
}