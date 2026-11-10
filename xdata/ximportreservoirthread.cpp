#include <QFile>
#include <qtextstream.h>
#include "ximportreservoirthread.h"
#include "xeclipseobject.h"
#include "xgridmodel.h"
#include "xpropertymodel.h"
#include "xgridcell.h"
#include "xglobal.h"

#define EPS 0.01

CXImportReservoirThread::CXImportReservoirThread(QString sFileName)
{
	m_sFileName		= sFileName;
	m_pEObj			= NULL;
	m_pGridModel	= NULL;
}

CXImportReservoirThread::~CXImportReservoirThread()
{
	if(m_pEObj)
		delete m_pEObj;

	if(m_pGridModel)
		delete m_pGridModel;

	foreach(CXPropertyModel *pProp, m_listProps)
	{
		delete pProp;
	}
}

void CXImportReservoirThread::RunThread()
{
	//	Open the file first.
	QFile qFile(m_sFileName);
	if(!qFile.open(QIODevice::ReadOnly))
	{
		EmitGeneralErrorMsg("Unable to open the reservoir file!");
		return;
	}

	// Set the names for progress dialog
	QString strWindowName = "Scanning the reservoir file"; 
	EmitSetWindowName(strWindowName);

	QTextStream stream(&qFile);
	QString sFileString;
	int nI = 0, nJ = 0, nK = 0, nReservoir = 0;
	char ch;

	//	Read the dimentions info first.
	while (!stream.atEnd()) 
	{
		sFileString = stream.readLine();			                     
		if (sFileString == "" || sFileString.left(2) == "--") 
			continue;

		sFileString = sFileString.simplified();
		if(sFileString.startsWith("SPECGRID", Qt::CaseInsensitive))
		{
			while (!stream.atEnd())
			{	
				sFileString = stream.readLine();				
				if (sFileString == "") 
					continue;

				sFileString = sFileString.simplified();
				sscanf(sFileString.toLatin1().constData (), "%d %d %d %d %c", &nJ, &nI, &nK, &nReservoir, &ch);
				break;
			}

			break;
		}
	}

	if(m_pEObj)
	{
		delete m_pEObj;
		m_pEObj = NULL;
	}

	if(m_pGridModel)
	{
		delete m_pGridModel;
		m_pGridModel = NULL;
	}

	if(nI * nJ * nK > 0)
	{
		m_pEObj = new CXEclipseObject(nI, nJ, nK);
		m_pGridModel = new CXGridModel(nI, nJ, nK);
	}
	else
	{
		EmitGeneralErrorMsg("The dimension of the grid is wrong!");
		qFile.close();
		return;
	}

	bool bSuccessful = true;
	bool bModelReady = false;
	while (!stream.atEnd()) 
	{
		sFileString = stream.readLine();			                     
		if (sFileString == "" || sFileString.startsWith("--")) 
			continue;
		
		if (sFileString.indexOf("--") != -1)
			sFileString.truncate(sFileString.indexOf("--"));

		sFileString = sFileString.simplified();
		if(sFileString.compare("COORD", Qt::CaseInsensitive) == 0)
		{
			if(!_readPCoord(stream))
			{
				bSuccessful = false;
				break;
			}
		}
		else if(sFileString.compare("ZCORN", Qt::CaseInsensitive) == 0)
		{
			if(!_readZCoord(stream))
			{
				bSuccessful = false;
				break;
			}
		}
		else if(sFileString.compare("ACTNUM", Qt::CaseInsensitive) == 0)
		{
			if(!_readActCell(stream))
			{
				bSuccessful = false;
				break;
			}

			if(!_calcCellCoord())
			{
				bSuccessful = false;
				break;
			}

			bModelReady = true;
		}
		else if(bModelReady)
		{
			_readProperty(sFileString, stream);
		}
	}

	if(!bSuccessful)
	{
		delete m_pEObj;
		m_pEObj = NULL;

		delete m_pGridModel;
		m_pGridModel = NULL;

		return;
	}
}

bool CXImportReservoirThread::_readPCoord(QTextStream& stream)
{
	QString sFileString;
	unsigned int iIDX = 0, iPillarIDX = 0;
	float fVal[6];

	while (!stream.atEnd()) 
	{
		sFileString = stream.readLine();			                     
		if (sFileString == "" || sFileString.startsWith("--"))
			continue;
		if (sFileString == "/") 
			break;	

		sFileString = sFileString.simplified();
		QStringList listXYZ = sFileString.split(" ");
		foreach( QString strXYZ, listXYZ  )
		{
			if (strXYZ == "/")
				break;

			if (strXYZ.contains("*"))
			{
				QStringList listVal = strXYZ.split("*");
				if (listVal.size() != 2)
				{
					EmitGeneralErrorMsg("Can not parse string as " + strXYZ + "!");
					return false;
				}

				int iNum = listVal[0].toInt();
				float fV = listVal[1].toFloat();
				for (int i = 0; i < iNum; i++)
				{
					fVal[iIDX] = fV;
					iIDX++;

					if (iIDX == 6)
					{
						fVal[3] -= fVal[0];
						fVal[4] -= fVal[1];
						fVal[5] -= fVal[2];

						memcpy(m_pEObj->m_pPillars[iPillarIDX].m_pPoints, fVal, sizeof(float) * 6);
						iPillarIDX++;
						iIDX = 0;
					}
				}

				continue;
			}

			fVal[iIDX] = strXYZ.toFloat();
			iIDX++;

			if(iIDX == 6)
			{
				fVal[3] -= fVal[0];
				fVal[4] -= fVal[1];
				fVal[5] -= fVal[2];

				memcpy(m_pEObj->m_pPillars[iPillarIDX].m_pPoints, fVal, sizeof(float) * 6);
				iPillarIDX++;
				iIDX = 0;
			}
		}

		if (sFileString.endsWith("/"))
			break;
	}

	if(iPillarIDX != (m_pEObj->m_nI + 1) * (m_pEObj->m_nJ + 1))
	{
		EmitGeneralErrorMsg("The number of pillars is wrong!");
		return false;
	}

	return true;
}

bool CXImportReservoirThread::_readZCoord(QTextStream& stream)
{
	QString sFileString;
	unsigned int iIDX = 0;
	QString strTaskName = "Reading the Z coordinates";
	EmitSetTaskName(strTaskName);
	EmitStartComputing();

	unsigned int nOldPercentage = 0, nPercentage;
	while (!stream.atEnd()) 
	{
		sFileString = stream.readLine();
		if (sFileString == "" || sFileString.startsWith("--"))
			continue;
		if (sFileString == "/")
			break;

		sFileString = sFileString.simplified();
		QStringList listXYZ = sFileString.split(" ");
		foreach( QString strXYZ, listXYZ  )
		{
			if (strXYZ == "/")
				break;

			if (strXYZ.contains("*"))
			{
				QStringList listVal = strXYZ.split("*");
				if (listVal.size() != 2)
				{
					EmitGeneralErrorMsg("Can not parse string as " + strXYZ + "!");
					return false;
				}

				int iNum = listVal[0].toInt();
				float fV = listVal[1].toFloat();
				for (int i = 0; i < iNum; i++)
				{
					m_pEObj->m_pZCoord[iIDX] = fV;
					iIDX++;
				}

				continue;
			}
				
			m_pEObj->m_pZCoord[iIDX] = strXYZ.toFloat();
			iIDX++;
		}
				
		nPercentage = iIDX * 13 / m_pEObj->m_nTotalCells;
		if(nPercentage > nOldPercentage)
		{
			EmitUpdateProgress(iIDX, m_pEObj->m_nTotalCells * 8);
			nOldPercentage = nPercentage;
		}

		if (sFileString.endsWith("/"))
			break;
	}

	if(iIDX != m_pEObj->m_nTotalCells * 8)
	{
		EmitGeneralErrorMsg("The number of Z coordinates is wrong!");
		return false;
	}

	return true;
}

bool CXImportReservoirThread::_readActCell(QTextStream& stream)
{
	QString sFileString;
	unsigned int iIDX = 0;

	while (!stream.atEnd()) 
	{
		sFileString = stream.readLine();
		if (sFileString == "" || sFileString.startsWith("--"))
			continue;
		if (sFileString == "/")
			break;

		sFileString = sFileString.simplified();
		QStringList listXYZ = sFileString.split(" ");
		foreach( QString strXYZ, listXYZ)
		{
			if (strXYZ == "/")
				break;

			if (strXYZ.contains("*"))
			{
				QStringList listVal = strXYZ.split("*");
				if (listVal.size() != 2)
				{
					EmitGeneralErrorMsg("Can not parse string as " + strXYZ + "!");
					return false;
				}

				int iNum = listVal[0].toInt();
				int iV = listVal[1].toInt();
				for (int i = 0; i < iNum; i++)
				{
					m_pEObj->m_arrayBit[iIDX] = iV;
					iIDX++;
				}

				continue;
			}

			m_pEObj->m_arrayBit[iIDX] = strXYZ.toInt();
			iIDX++;
		}

		if (sFileString.endsWith("/"))
			break;
	}

	if(iIDX != m_pEObj->m_nTotalCells)
	{
		EmitGeneralErrorMsg("The number of active cells is wrong!");
		return false;
	}

	return true;
}

bool CXImportReservoirThread::_calcCellCoord()
{
	QList<CXGridCell *>& listCells = m_pGridModel->GetAllCells();

	unsigned int i, j, k, m, iIDX = 0;
	SPillar sPillar[4];
	float z[8], fDZ;
	double dCoord[24];

	QString strTaskName = "Calculating cell coordinates";
	EmitSetTaskName(strTaskName);
	EmitResetProgressBar();

	unsigned int nOldPercentage = 0, nPercentage;
	double dXMin = 9999999999., dXMax = -9999999999., dYMin = 9999999999., dYMax = -9999999999., dZMin = 9999999999., dZMax = -9999999999.;
	
	for(k = 0; k < m_pEObj->m_nK; k++)
	{
		for(i = 0; i < m_pEObj->m_nI; i++)
		{
			for(j = 0; j < m_pEObj->m_nJ; j++, iIDX++)
			{
				nPercentage = iIDX * 100 / m_pEObj->m_nTotalCells;
				if(nPercentage > nOldPercentage)
				{
					EmitUpdateProgress(iIDX, m_pEObj->m_nTotalCells);
					nOldPercentage = nPercentage;
				}

				if(!m_pEObj->m_arrayBit[iIDX])
					continue;

				//	Get it's four pillars.
				memcpy(sPillar[0].m_pPoints, m_pEObj->m_pPillars[i * (m_pEObj->m_nJ + 1) + j].m_pPoints, sizeof(float) * 6);
				memcpy(sPillar[1].m_pPoints, m_pEObj->m_pPillars[i * (m_pEObj->m_nJ + 1) + j + 1].m_pPoints, sizeof(float) * 6);
				memcpy(sPillar[2].m_pPoints, m_pEObj->m_pPillars[(i + 1) * (m_pEObj->m_nJ + 1) + j + 1].m_pPoints, sizeof(float) * 6);
				memcpy(sPillar[3].m_pPoints, m_pEObj->m_pPillars[(i + 1) * (m_pEObj->m_nJ + 1) + j].m_pPoints, sizeof(float) * 6);

				//	Delta Z should not be 0.
				if(qAbs(sPillar[0].m_pPoints[5]) < EPS || qAbs(sPillar[1].m_pPoints[5]) < EPS 
					|| qAbs(sPillar[2].m_pPoints[5]) < EPS || qAbs(sPillar[3].m_pPoints[5]) < EPS)
				{
					//	Abort this cell.
					m_pEObj->m_arrayBit[iIDX] = false;
					continue;
				}

				//	Get the 8 corners' Z values.
				z[0] = m_pEObj->m_pZCoord[8 * m_pEObj->m_nI * m_pEObj->m_nJ * k + 4 * m_pEObj->m_nJ * i + 2 * j];
				z[1] = m_pEObj->m_pZCoord[8 * m_pEObj->m_nI * m_pEObj->m_nJ * k + 4 * m_pEObj->m_nJ * i + 2 * j + 1];
				z[2] = m_pEObj->m_pZCoord[8 * m_pEObj->m_nI * m_pEObj->m_nJ * k + 2 * m_pEObj->m_nJ * (2 * i + 1) + 2 * j + 1];
				z[3] = m_pEObj->m_pZCoord[8 * m_pEObj->m_nI * m_pEObj->m_nJ * k + 2 * m_pEObj->m_nJ * (2 * i + 1) + 2 * j];
				z[4] = m_pEObj->m_pZCoord[8 * m_pEObj->m_nI * m_pEObj->m_nJ * k + 4 * m_pEObj->m_nI * m_pEObj->m_nJ + 4 * m_pEObj->m_nJ * i + 2 * j];
				z[5] = m_pEObj->m_pZCoord[8 * m_pEObj->m_nI * m_pEObj->m_nJ * k + 4 * m_pEObj->m_nI * m_pEObj->m_nJ + 4 * m_pEObj->m_nJ * i + 2 * j + 1];
				z[6] = m_pEObj->m_pZCoord[8 * m_pEObj->m_nI * m_pEObj->m_nJ * k + 4 * m_pEObj->m_nI * m_pEObj->m_nJ + 2 * m_pEObj->m_nJ * (2 * i + 1) + 2 * j + 1];
				z[7] = m_pEObj->m_pZCoord[8 * m_pEObj->m_nI * m_pEObj->m_nJ * k + 4 * m_pEObj->m_nI * m_pEObj->m_nJ + 2 * m_pEObj->m_nJ * (2 * i + 1) + 2 * j];

				fDZ = 0.;
				for(m = 0; m < 4; m++)
				{
					fDZ += (z[m + 4] - z[m]);

					//	X, Y, Z of the top corner.
					dCoord[m * 3]		= sPillar[m].m_pPoints[0] + sPillar[m].m_pPoints[3] * (z[m] - sPillar[m].m_pPoints[2]) / sPillar[m].m_pPoints[5];
					dCoord[m * 3 + 1]	= sPillar[m].m_pPoints[1] + sPillar[m].m_pPoints[4] * (z[m] - sPillar[m].m_pPoints[2]) / sPillar[m].m_pPoints[5];
					dCoord[m * 3 + 2]	= z[m];

					//	X, Y, Z of the bottom corner.
					dCoord[m * 3 + 12]	= sPillar[m].m_pPoints[0] + sPillar[m].m_pPoints[3] * (z[m + 4] - sPillar[m].m_pPoints[2]) / sPillar[m].m_pPoints[5];
					dCoord[m * 3 + 13]	= sPillar[m].m_pPoints[1] + sPillar[m].m_pPoints[4] * (z[m + 4] - sPillar[m].m_pPoints[2]) / sPillar[m].m_pPoints[5];
					dCoord[m * 3 + 14]	= z[m + 4];
				}

				//	Thickness error!
				if(qAbs(fDZ) < EPS)
				{
					m_pEObj->m_arrayBit[iIDX] = false;
					continue;
				}

				for(m = 0; m < 8; m++)
				{
					if(dXMin > dCoord[3 * m])
						dXMin = dCoord[3 * m];
					if(dXMax < dCoord[3 * m])
						dXMax = dCoord[3 * m];

					if(dYMin > dCoord[3 * m + 1])
						dYMin = dCoord[3 * m + 1];
					if(dYMax < dCoord[3 * m + 1])
						dYMax = dCoord[3 * m + 1];

					if(dZMin > dCoord[3 * m + 2])
						dZMin = dCoord[3 * m + 2];
					if(dZMax < dCoord[3 * m + 2])
						dZMax = dCoord[3 * m + 2];
				}

				CXGridCell *pCell = new CXGridCell(i, j, k);
				memcpy(pCell->GetVertex(), dCoord, sizeof(double) * 24);
				listCells<<pCell;
			}
		}
	}

	if(listCells.count() > 1)
	{
		m_pGridModel->SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	}

	return true;
}

bool CXImportReservoirThread::_readProperty(QString sPropName, QTextStream& stream)
{
	QString sFileString;
	unsigned int iIDXTotal = 0, iIDXValid = 0, iSize = m_pGridModel->GetValidCellNumber();
	double *pBuff = new double[iSize];

	QString strTaskName = "Reading property: " + sPropName;
	EmitSetTaskName(strTaskName);
	EmitResetProgressBar();
	unsigned int nOldPercentage = 0, nPercentage;

	while (!stream.atEnd()) 
	{
		if(sFileString.endsWith("/"))
			break;
		sFileString = stream.readLine();			                     
		if (sFileString == "" || sFileString.left(2) == "--") 
			continue;
		if (sFileString == "/") 
			break;	

		nPercentage = iIDXTotal * 100 / m_pEObj->m_nTotalCells;
		if(nPercentage > nOldPercentage)
		{
			EmitUpdateProgress(iIDXTotal, m_pEObj->m_nTotalCells);
			nOldPercentage = nPercentage;
		}

		sFileString = sFileString.simplified();
		QStringList listVal = sFileString.split(" ");
		foreach( QString strVal, listVal)
		{
			if (strVal == "/")
				break;

			if (strVal.contains("*"))
			{
				QStringList listV = strVal.split("*");
				if (listV.size() != 2)
				{
					EmitGeneralErrorMsg("Can not parse string as " + strVal + "!");
					return false;
				}

				int iNum = listV[0].toInt();
				float fV = listV[1].toFloat();
				for (int i = 0; i < iNum; i++)
				{
					if (m_pEObj->m_arrayBit[iIDXTotal])
					{
						if (iIDXValid >= iSize)
						{
							//	Something wrong!
							EmitGeneralErrorMsg("Someting wrong about the number of valid cells!");
							delete[]pBuff;
							return false;
						}

						if (qAbs(strVal.toDouble() - m_dInvalid) < EPS)
							pBuff[iIDXValid] = ::g_dInvalidData;
						else
							pBuff[iIDXValid] = strVal.toDouble();
						iIDXValid++;
					}

					iIDXTotal++;
				}

				continue;
			}

			if(m_pEObj->m_arrayBit[iIDXTotal])
			{
				if(iIDXValid >= iSize)
				{
					//	Something wrong!
					EmitGeneralErrorMsg("Someting wrong about the number of valid cells!");
					delete []pBuff;
					return false;
				}

				if(qAbs(strVal.toDouble() - m_dInvalid) < EPS)
					pBuff[iIDXValid] = ::g_dInvalidData;
				else
					pBuff[iIDXValid] = strVal.toDouble();
				iIDXValid++;
			}
				
			iIDXTotal++;
		}
	}

	if(iIDXValid != iSize)
	{
		//EmitGeneralErrorMsg("The number of active cells is wrong!");
		delete []pBuff;
		return false;
	}

	CXPropertyModel *pPropModel = new CXPropertyModel(sPropName);
	pPropModel->ResetData(iSize, pBuff);

	m_listProps<<pPropModel;

	return true;
}