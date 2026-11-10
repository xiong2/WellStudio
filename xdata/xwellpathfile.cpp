#include <qdebug.h>
#include <QFile>
#include <qmessagebox.h>
#include <cmath>
#include "xwellpathfile.h"
#include "xglobal.h"
#include "xwellpath.h"
#include "xwelltd.h"
#include "xwell.h"
#include "xtree.h"
#include "xgraphicsapi.h"

bool CXWellPathFile::Import()
{
	//	The target object name is NULL, need not import.
	if(m_sObjName == "")
		return false;

	//	Find the well first.
	CXObject *pWellFolder = ::GetRootObjectFolder(EXWellFolder);
	CXWell *pWell = (CXWell *)pWellFolder->GetChild(m_sObjName);

	//	Not found? create it!
	if(!pWell)
	{
		//	Not all import mode support create new well auto.
		if(m_iImportMode == 0 || m_iImportMode == 1 || m_iImportMode == 4)
		{
			QMessageBox::critical(NULL, "Importing Well Path", "While using azimuth, inclination, delta x or delta y data,\n the well header information should be imported first!");
			return false;
		}

		pWell = new CXWell(m_sObjName);

		//	Add the well to the project.
		pWellFolder->AddChild(pWell);
		::AddObjectEvent(pWell);
	}

	//	Get data column position.
	short iIDX[3] = {-1, -1, -1}, iMaxIDX = -1;
	if(m_iImportMode == 0)
	{
		iIDX[0] = m_sListColumnChosen.indexOf("MD");
		iIDX[1] = m_sListColumnChosen.indexOf("Azimuth");
		iIDX[2] = m_sListColumnChosen.indexOf("Inclination");
	}
	else if (m_iImportMode == 1)
	{
		iIDX[0] = m_sListColumnChosen.indexOf("DX");
		iIDX[1] = m_sListColumnChosen.indexOf("DY");
		iIDX[2] = m_sListColumnChosen.indexOf("TVD");
	}
	else if (m_iImportMode == 2)
	{
		iIDX[0] = m_sListColumnChosen.indexOf("X");
		iIDX[1] = m_sListColumnChosen.indexOf("Y");
		iIDX[2] = m_sListColumnChosen.indexOf("TVD");
	}
	else if (m_iImportMode == 3)
	{
		iIDX[0] = m_sListColumnChosen.indexOf("X");
		iIDX[1] = m_sListColumnChosen.indexOf("Y");
		iIDX[2] = m_sListColumnChosen.indexOf("Z");
	}
	else if (m_iImportMode == 4)
	{
		iIDX[0] = m_sListColumnChosen.indexOf("DX");
		iIDX[1] = m_sListColumnChosen.indexOf("DY");
		iIDX[2] = m_sListColumnChosen.indexOf("DZ");
	}
	else
	{
		QMessageBox::critical(NULL, "Importing Well Path", "Something error about the selected columns!");
		return false;
	}

	if(m_bNegateZ && m_fListUnitRatio[2] > 0.)
		m_fListUnitRatio[2] *= (-1);	
	qDebug()<<"Z ratio is "<<m_fListUnitRatio[2];

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
	while(!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		QString sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if(sListValue.size() <= iMaxIDX)
			continue;

		for(int i = 0; i < 3; i++)
		{
			double dValue = sListValue[iIDX[i]].toDouble();
			if(m_fListUnitRatio[i] != 1.)
			{
				dValue *= m_fListUnitRatio[i];
			}

			vecData.push_back(dValue);
		}
	}

	qFile.close();

	if(vecData.size() < 3)
		return true;

	//	Populate well path data.
	CXWellPath *pWellPath = pWell->GetWellPath();

	unsigned int i, j, iNumber;
	double dKB = pWell->GetKB();
	double *pOldData	= pWellPath->GetData(iNumber);		//	Some import mode need the 1st point of the well path.
	if(m_iImportMode == 0)
	{
		//	Using MD, Azi, Inc, get the last total MD value first.
		iNumber = vecData.size();
		double *pNewData = new double[iNumber + 3];
		double *pNewMD = new double[iNumber / 3 + 1];

		//	The 1st point copy from old data directly.
		memcpy(pNewData, pOldData, 3 * sizeof(double));
		pNewMD[0] = 0.;

		double dCurMD = 0, dCurAzi = 0., dCurInc = 0., dLength, dDeltaH;
		for(i = 0, j = 3; i < iNumber; i += 3)
		{
			vecData[i + 1] *= M_RAD;
			vecData[i + 2] *= M_RAD;

			if(dCurAzi == vecData[i + 1] && dCurInc == vecData[i + 2])
			{
				//	If azimuth and inclination not change, this point could be abort.
				continue;
			}

			dLength = vecData[i] - dCurMD;
			dDeltaH = sin(dCurInc) * dLength;
			pNewData[j]		= pNewData[j - 3] + sin(dCurAzi) * dDeltaH;
			pNewData[j + 1] = pNewData[j - 2] + cos(dCurAzi) * dDeltaH;
			pNewData[j + 2] = pNewData[j - 1] + cos(dCurInc) * dLength;
			pNewMD[j / 3] = vecData[i];

			dCurMD = vecData[i];
			dCurAzi = vecData[i + 1];
			dCurInc = vecData[i + 2];

			j += 3;
		}

		pWellPath->ResetData(pNewData, j, pNewMD);
	}
	else if(m_iImportMode == 1 || m_iImportMode == 4)
	{
		//	Using DX, DY, TVD or DX, DY, DZ
		unsigned int iNumber = vecData.size();
		double *pData = new double[iNumber + 3];

		memcpy(pData, pOldData, 3 * sizeof(double));

		for(i = 0; i < iNumber; i += 3)
		{
			pData[i + 3] = vecData[i] + pData[0];
			pData[i + 4] = vecData[i + 1] + pData[1];

			if (m_iImportMode == 1)
				pData[i + 5] = vecData[i + 2] - dKB;
			else
				pData[i + 5] = vecData[i + 2] + pData[2];
		}

		pWellPath->ResetData(pData, iNumber + 3);
	}
	else if(m_iImportMode == 2 || m_iImportMode == 3)
	{
		//	Using X, Y, TVD or X, Y, Z.
		unsigned int iNumber = vecData.size();
		double *pData = new double[iNumber];
		memcpy(pData, vecData.data(), sizeof(double) * iNumber);

		if (m_iImportMode == 2)
		{
			//	Uses KB to correct TVD to Z.
			for (i = 2; i < iNumber; i += 3)
				pData[i] -= dKB;
		}

		pWellPath->ResetData(pData, iNumber);
	}

	if (m_bSimplifyData)
	{
		unsigned int iNum;
		double *pData = pWellPath->GetData(iNum);

		int iSize = iNum / 3;
		double *pX = new double[iSize];
		double *pY = new double[iSize];
		double *pZ = new double[iSize];
		for (int i = 0; i < iSize; i++)
		{
			pX[i] = pData[3 * i];
			pY[i] = pData[3 * i + 1];
			pZ[i] = pData[3 * i + 2];
		}

		std::vector<int> vecIDX;
		CXGraphicsAPI::SegmentSimplification(pX, pY, pZ, iSize, vecIDX);

		int iNSize = vecIDX.size();
		double *pNData = new double[3 * iNSize];
		for (i = 0; i < iNSize; i++)
		{
			pNData[3 * i] = pX[vecIDX[i]];
			pNData[3 * i + 1] = pY[vecIDX[i]];
			pNData[3 * i + 2] = pZ[vecIDX[i]];
		}

		pWellPath->ResetData(pNData, 3 * iNSize);

		delete[]pX;
		delete[]pY;
		delete[]pZ;
	}

	return true;
}

void CXWellPathFile::SetImportMode(unsigned int iImportMode)
{
	if(iImportMode > 4)
		iImportMode = 0;

	m_iImportMode = iImportMode;
}