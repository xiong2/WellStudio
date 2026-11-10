#include <qdebug.h>
#include <qfileinfo.h>
#include <QFile>
#include <qtextstream.h>
#include "xpointsfile.h"
#include "xglobal.h"
#include "xproject.h"
#include "x3dpoints.h"
#include "xtree.h"
#include "xgeneralfolder.h"

bool CXPointsFile::Import()
{
	int i;

	short iIDX[3] = {-1, -1, -1}, iMaxIDX = -1;
	iIDX[0] = m_sListColumnChosen.indexOf("X");
	iIDX[1] = m_sListColumnChosen.indexOf("Y");
	iIDX[2] = m_sListColumnChosen.indexOf("Z");

	if(iIDX[0] == -1 || iIDX[1] == -1)
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

	//	The target object name is NULL, need create one.
	CX3DPoints *pPoints = NULL;
	CXGeneralFolder *pPointsFolder = (CXGeneralFolder *)::GetRootObjectFolder(EXPointsFolder);
	if(m_sObjName != "")
	{
		//	Find the object by name.
		pPoints = (CX3DPoints *)pPointsFolder->GetChild(m_sObjName);
	}

	if(!pPoints)
	{
		//	Object not exist, create one.  First get the object name from the file.
		QFileInfo qFI(m_sFile);
		pPoints = new CX3DPoints(qFI.baseName());

		pPointsFolder->AddChild(pPoints);
		::AddObjectEvent(pPoints);
	}

	QTextStream stream(&qFile);
	qint64 iCurrentLine = 1;

	//	Skip the file header.
	while(!stream.atEnd() && iCurrentLine < m_iImportFrom)
	{
		stream.readLine();
		iCurrentLine++;
	}

	//	Data buffer.
	QVector<double> vecData;
	vecData.reserve(1024 * 3);

	//	Read the file contents.
	double dValues[3];
	while(!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		QString sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if(sListValue.size() <= iMaxIDX)
			continue;

		bool bSu = true;
		for(i = 0; i < 2; i++)
		{
			dValues[i] = sListValue[iIDX[i]].toDouble();
			if (dValues[i] == m_dInvalid)
			{
				bSu = false;
				break;
			}
			if(m_fListUnitRatio[i] != 1.)
			{
				dValues[i] *= m_fListUnitRatio[i];
			}
		}

		if (!bSu)
			continue;

		if(iIDX[2] != -1)
		{
			//	Has Z value.
			dValues[2] = sListValue[iIDX[i]].toDouble();
			if (dValues[2] == m_dInvalid)
			{
				continue;
			}

			if(m_fListUnitRatio[i] != 1.)
			{
				dValues[2] *= m_fListUnitRatio[i];
			}
		}
		else
		{
			//	No Z value, give an invalid value.
			dValues[2] = g_dInvalidData;
		}

		for (i = 0; i < 3; i++)
			vecData << dValues[i];
	}

	unsigned int iNumber = vecData.size();
	double *pData = new double[iNumber];
	memcpy(pData, vecData.data(), sizeof(double) * iNumber);

	pPoints->ResetData(pData, iNumber);

	qFile.close();
	
	return true;
}