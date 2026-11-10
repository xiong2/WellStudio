#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include "xfracturepatchfile.h"
#include "xfracturepatch.h"
#include "xglobal.h"

CXFracturePatchFile::CXFracturePatchFile(QString sFile) : CXASCIIFile(eFracturePatches, sFile)
{
}

bool CXFracturePatchFile::Import()
{
	QFileInfo qFI(m_sFile);
	QString sFrac = qFI.baseName();

	QFile qFile(m_sFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}
	QTextStream stream(&qFile);

	QString sLine;
	bool bReadData = false;
	int i, nProp, nNode = -1, nFrac = -1, iIDX = 0;
	QStringList sListProp, sListVal;
	double *pBuff = nullptr;
	while (!stream.atEnd())
	{
		sLine = stream.readLine().simplified();
		
		if (!bReadData)
		{
			if (sLine == "BEGIN FRACTURE")
			{
				bReadData = true;
			}
			else if (sLine.startsWith("No_Fractures ="))
			{
				sListVal = sLine.split("=");
				nFrac = sListVal[1].toInt();
			}
			else if (sLine.startsWith("No_Nodes ="))
			{
				sListVal = sLine.split("=");
				nNode = sListVal[1].toInt();
				if (nFrac != -1)
				{
					if (nFrac * 4 != nNode)
					{
						QMessageBox::warning(NULL, "Importing Fracture Patches", "This version only supports quad patches, non-quad patches will be abandoned!");
					}
				}
			}
			else if (sLine.startsWith("Prop"))
			{
				sListVal = sLine.split("=");
				int iSPos = sListVal[1].indexOf("\"");
				int iEPos = sListVal[1].lastIndexOf("\"");
				sListProp << sListVal[1].mid(iSPos + 1, iEPos - iSPos - 1);
			}
		}
		else
		{
			if (sLine == "END FRACTURE")
				break;

			if (pBuff == nullptr)
			{
				//if (nFrac * 4 != nNode || nFrac == 0)
				//{
				//	QMessageBox::warning(NULL, "Importing Fracture Patches", "This version only support quad patches!");
				//	qFile.close();
				//	return false;
				//}

				nProp = sListProp.size();
				pBuff = new double[(12 + nProp) * nFrac];
			}

			sListVal = sLine.split(" ");
			if (sListVal.size() != 4)
			{
				// Properties.
				if (sListVal.size() != nProp + 3)
				{
					QMessageBox::warning(NULL, "Importing Fracture Patches", "Properties amount error!");
					qFile.close();
					delete[]pBuff;
					return false;
				}

				int iNum = sListVal[1].toInt();
				if (iNum != 4)
				{
					//	Not a quad patch, we should abandoned it!
					for (i = 0; i < iNum + 1; i++)
					{
						sLine = stream.readLine();
					}
					continue;
				}

				for (i = 0; i < nProp; i++)
				{
					pBuff[iIDX] = sListVal[i + 3].toDouble();
					iIDX++;
				}
			}
			else
			{
				//	So far, ignore the normal.
				if (sLine.startsWith("0"))
					continue;

				pBuff[iIDX] = sListVal[1].toDouble();
				iIDX++;
				pBuff[iIDX] = sListVal[2].toDouble();
				iIDX++;
				pBuff[iIDX] = qAbs(sListVal[3].toDouble());
				iIDX++;
			}
		}
	}

	if (iIDX > (12 + nProp) * nFrac)
	{
		QMessageBox::warning(NULL, "Importing Fracture Patches", "Read wrong number data!");
		qFile.close();
		delete[]pBuff;
		return false;
	}

	//	Correct the patches amount.
	nFrac = iIDX / (12 + nProp);

	for (i = 0; i < nFrac; i++)
	{
		sortPoints(pBuff + i * (12 + nProp) + nProp);
	}

	CXObject* pFracFolder = ::GetRootObjectFolder(EXFracturePatchFolder);
	sFrac = pFracFolder->GetUnallocatedName(sFrac);
	CXFracturePatch *pFP = new CXFracturePatch(sFrac);
	pFP->ResetData(sListProp, pBuff, iIDX);
	pFracFolder->AddChild(pFP);
	::AddObjectEvent(pFP);
	
	qFile.close();

	return true;
}

void CXFracturePatchFile::sortPoints(double *pBuff)
{
	int i, j;
	double x[4], y[4], z[4], d[4];
	for (i = 0; i < 4; i++)
	{
		x[i] = pBuff[3 * i];
		y[i] = pBuff[3 * i + 1];
		z[i] = pBuff[3 * i + 2];
	}

	double cy = (y[0] + y[1] + y[2] + y[3]) / 4;
	double cz = (z[0] + z[1] + z[2] + z[3]) / 4;

	for (i = 0; i < 4; i++)
	{
		d[i] = atan2(y[i] - cy, z[i] - cz);
	}

	QVector<int> vecIDX;
	while (vecIDX.size() < 4)
	{
		double dMin = qMin(d[0], d[1]);
		dMin = qMin(dMin, d[2]);
		dMin = qMin(dMin, d[3]);

		for (i = 0; i < 4; i++)
		{
			if (dMin == d[i])
			{
				vecIDX.push_back(i);
				d[i] = 99999999;
				break;
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		pBuff[3 * i] = x[vecIDX[i]];
		pBuff[3 * i + 1] = y[vecIDX[i]];
		pBuff[3 * i + 2] = z[vecIDX[i]];
	}
}