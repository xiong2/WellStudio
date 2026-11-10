#include <qmessagebox.h>
#include <qdebug.h>
#include <qfileinfo.h>
#include <QFile>
#include <qtextstream.h>
#include "xfaultsticksfile.h"
#include "xglobal.h"
#include "xproject.h"
#include "xfaultsticks.h"
#include "x2dpolygon.h"
#include "xtree.h"
#include "xgeneralfolder.h"
#include "x3dsurvey.h"
#include "xseismicutmtool.h"

bool CXFaultSticksFile::CheckSelectedColumns(QStringList& sListChosenColumn)
{
	int iCount = 0;
	if (sListChosenColumn.contains("X"))
		iCount++;
	if (sListChosenColumn.contains("Y"))
		iCount++;
	if (sListChosenColumn.contains("Z"))
		iCount++;
	if (sListChosenColumn.contains("Line ID"))
		iCount++;
	if (m_eFileType == eFaultPolygonASCII && iCount < 3)
	{
		QMessageBox::warning(NULL, "Importing Fault Polygon", "X, Y, Line ID should be selected!");
		return false;
	}
	else if(iCount < 4)
	{
		QMessageBox::warning(NULL, "Importing Fault Polygon", "X, Y, Z, Line ID should be selected!");
		return false;
	}

	return true;
}


bool CXFaultSticksFile::Import()
{
	if(m_eFileType == eFaultPolygonASCII)
		return importFaultPolygons();
	else
		return importFaultSticks();
}

bool CXFaultSticksFile::importFaultSticks()
{
	int i;
	short iIDX[4] = {-1, -1, -1, -1}, iMaxIDX = -1;
	iIDX[0] = m_sListColumnChosen.indexOf("X");
	iIDX[1] = m_sListColumnChosen.indexOf("Y");
	iIDX[2] = m_sListColumnChosen.indexOf("Z");
	iIDX[3] = m_sListColumnChosen.indexOf("Line ID");

	if(iIDX[0] == -1 || iIDX[1] == -1 || iIDX[2] == -1 || iIDX[3] == -1)
	{
		qDebug()<<"Something error!";
		return false;
	}

	if(iIDX[0] > iMaxIDX)
		iMaxIDX = iIDX[0];
	if(iIDX[1] > iMaxIDX)
		iMaxIDX = iIDX[1];
	if(iIDX[2] > iMaxIDX)
		iMaxIDX = iIDX[2];
	if(iIDX[3] > iMaxIDX)
		iMaxIDX = iIDX[3];

	//	Prepare the file.
	QFile qFile(m_sFile);
	if(!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	//	The target object name is NULL, need create one.
	CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(::GetObjectByID(m_surveyID));
	if (!pSurvey)
		return false;

	CXFaultSticks *pFSticks = NULL;
	CXGeneralFolder *pFaultFolder = (CXGeneralFolder *)(pSurvey->GetFolder(EXFaultFolder));
	if(m_sObjName != "")
	{
		//	Find the object by name.
		pFSticks = (CXFaultSticks *)pFaultFolder->GetChild(m_sObjName);
	}

	if(!pFSticks)
	{
		//	Object not exist, create one.  First get the object name from the file.
		QFileInfo qFI(m_sFile);
		m_sObjName = pFaultFolder->GetUnallocatedName(qFI.baseName());
		pFSticks = new CXFaultSticks(m_sObjName, m_surveyID);

		pFaultFolder->AddChild(pFSticks);
		::AddObjectEvent(pFSticks);
	}
	
	QList<CXFaultStick *>& listSticks = pFSticks->GetAllSticks();

	QTextStream stream(&qFile);
	qint64 iCurrentLine = 1;
	QString sLine;

	//	Skip the file header.
	while(!stream.atEnd() && iCurrentLine < m_iImportFrom)
	{
		sLine = stream.readLine();
		iCurrentLine++;
	}

	//	Data buffer.
	double *pDataBuff = new double[1024 * 256 * 3];
	unsigned int iOffset = 0;

	//	Read the file contents.
	int iLineID = -999;
	while(!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if(sListValue.size() <= iMaxIDX)
			continue;

		if(iLineID == -999)
			iLineID = sListValue[iIDX[3]].toInt();
		else if(iLineID != sListValue[iIDX[3]].toInt())
		{
			if(iOffset >= 6)
			{
				//	Only accpet stick more than 1 point.
				double *pData = new double[iOffset];
				memcpy(pData, pDataBuff, sizeof(double) * iOffset);

				CXFaultStick *pStick = new CXFaultStick;
				pStick->ResetData(pData, iOffset / 3);
				checkStickType(pStick);
				listSticks.append(pStick);
			}

			//	Reset the vector.
			iOffset = 0;
			iLineID = sListValue[iIDX[3]].toInt();
		}

		for(i = 0; i < 3; i++)
		{
			double dValue = sListValue[iIDX[i]].toDouble();
			if(m_fListUnitRatio[i] != 1.)
			{
				dValue *= m_fListUnitRatio[i];
			}
			
			pDataBuff[iOffset] = dValue;
			iOffset++;
		}
	}

	//	The last stick should be added here.
	if(iOffset >= 6)
	{
		//	Only accpet stick more than 1 point.
		double *pData = new double[iOffset];
		memcpy(pData, pDataBuff, sizeof(double) * iOffset);

		CXFaultStick *pStick = new CXFaultStick;
		pStick->ResetData(pData, iOffset / 3);
		checkStickType(pStick);
		listSticks.append(pStick);
	}
		
	//	Need re-calculate the dimension.
	pFSticks->SetNeedCalcDimension();

	//	Free the buff and close the file.
	delete []pDataBuff;
	qFile.close();

	return true;
}

bool CXFaultSticksFile::importFaultPolygons()
{
	int i;
	short iIDX[3] = {-1, -1, -1}, iMaxIDX = -1;
	iIDX[0] = m_sListColumnChosen.indexOf("X");
	iIDX[1] = m_sListColumnChosen.indexOf("Y");
	iIDX[2] = m_sListColumnChosen.indexOf("Line ID");

	if(iIDX[0] == -1 || iIDX[1] == -1 || iIDX[2] == -1)
	{
		qDebug()<<"Something error!";
		return false;
	}

	if(iIDX[0] > iMaxIDX)
		iMaxIDX = iIDX[0];
	if(iIDX[1] > iMaxIDX)
		iMaxIDX = iIDX[1];
	if(iIDX[2] > iMaxIDX)
		iMaxIDX = iIDX[2];

	//	Prepare the file.
	QFile qFile(m_sFile);
	if(!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	CXGeneralFolder *pFaultFolder = (CXGeneralFolder *)::GetRootObjectFolder(EXFaultPolygonFolder);

		//	Get the polygons' base name.
	QFileInfo qFI(m_sFile);
	QString strBaseName = qFI.baseName();
	
	QTextStream stream(&qFile);
	qint64 iCurrentLine = 1;
	QString sLine;

	//	Skip the file header.
	while(!stream.atEnd() && iCurrentLine < m_iImportFrom)
	{
		sLine = stream.readLine();
		iCurrentLine++;
	}

	//	Data buffer.
	double *pDataBuff = new double[1024 * 2];
	unsigned short iOffset = 0;

	//	Read the file contents.
	QString sLineID = "";
	int iLineID = -999;
	while(!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if(sListValue.size() <= iMaxIDX)
			continue;

		if(sLineID.isEmpty())
			sLineID = sListValue[iIDX[2]];
		else if(sLineID != sListValue[iIDX[2]])
		{
			if(iOffset >= 6)
			{
				//	Only accpet polygon more than 2 point.
				double *pData = new double[iOffset];
				memcpy(pData, pDataBuff, sizeof(double) * iOffset);

				CX2DPolygon *pPolygon = new CX2DPolygon(pFaultFolder->GetUnallocatedName(strBaseName), EXFaultPolygon);
				pPolygon->ResetData(pData, iOffset);

				pFaultFolder->AddChild(pPolygon);
				::AddObjectEvent(pPolygon);
			}

			//	Reset the vector.
			iOffset = 0;
			sLineID = sListValue[iIDX[2]];
		}

		for(i = 0; i < 2; i++)
		{
			double dValue = sListValue[iIDX[i]].toDouble();
			if(m_fListUnitRatio[i] != 1.)
			{
				dValue *= m_fListUnitRatio[i];
			}
			
			pDataBuff[iOffset] = dValue;
			iOffset++;
		}
	}

	//	The last stick should be added here.
	if(iOffset >= 6)
	{
		//	Only accpet polygon more than 2 points.
		double *pData = new double[iOffset];
		memcpy(pData, pDataBuff, sizeof(double) * iOffset);

		CX2DPolygon *pPolygon = new CX2DPolygon(pFaultFolder->GetUnallocatedName(strBaseName), EXFaultPolygon);
		pPolygon->ResetData(pData, iOffset);

		pFaultFolder->AddChild(pPolygon);
		::AddObjectEvent(pPolygon);
	}

	//	Free the buff and close the file.
	delete []pDataBuff;
	qFile.close();

	return true;
}

void CXFaultSticksFile::checkStickType(CXFaultStick *pFS)
{
	CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(::GetObjectByID(m_surveyID));
	if (!pSurvey)
		return;

	CXSeismicUTMTool UTM = pSurvey->GetUTM();
	pFS->CheckStickType(&UTM);
}