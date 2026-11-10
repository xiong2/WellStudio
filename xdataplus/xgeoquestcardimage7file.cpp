#include <qfile.h>
#include <qtextstream.h>
#include <qvector.h>
#include <qmessagebox.h>
#include <set>
#include "xgeoquestcardimage7file.h"
#include "x3dsurvey.h"
#include "xseismicutmtool.h"
#include "x3dhorizon.h"
#include "xfaultsticks.h"
#include "xproject.h"
#include "xglobal.h"
#include "xtree.h"
#include "xgeneralfolder.h"
#include "xwaitcursor.h"

CXGeoQuestCardImage7File::CXGeoQuestCardImage7File(QString sFile, bool bHorizon)
	:CXASCIIFile(eGeoquestCardImage7, sFile)
{
	m_bHorizon = bHorizon;
}

bool CXGeoQuestCardImage7File::Import()
{
	if (m_bHorizon)
		return importHorizon();
	else
		return importFault();
}

bool CXGeoQuestCardImage7File::importFault()
{
	QFile qFile(m_sFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}
	QTextStream stream(&qFile);
	QString sLine, sSubLine, sSurveyName = "", sFaultName = "";
	double *pBuff = new double[1024 * 3];
	int iOffset = 0, iELineID = -999, iNLineID;

	QList<CXFaultStick *> *pListSticks = NULL;
	CX3DSurvey *pSurvey = NULL;
	CXFaultSticks *pFSticks = NULL;
	CXGeneralFolder *pFaultFolder = NULL;

	CXWaitCursor *pWaitCursor = new CXWaitCursor;
	while (!stream.atEnd())
	{
		sLine = stream.readLine();

		//	Skip comment lines.
		if (sLine.startsWith("SNAPPING", Qt::CaseInsensitive))
			continue;

		if (sLine.startsWith("PROFILE", Qt::CaseInsensitive))
		{
			//	The begining of a new horizon.
			sFaultName = sLine.mid(8, 16).simplified();
		}
		else if (sLine.startsWith("EOD ", Qt::CaseInsensitive))
		{
			if (!pFSticks)
				continue;

			//	Process the last stick.
			if (iOffset > 3)
			{
				//	Only accpet stick more than 1 point.
				double *pData = new double[iOffset];
				memcpy(pData, pBuff, sizeof(double) * iOffset);

				CXFaultStick *pStick = new CXFaultStick;
				pStick->ResetData(pData, iOffset / 3);
				pListSticks->append(pStick);
			}

			iELineID = -999;
			iOffset = 0;
			pListSticks = NULL;

			pFSticks->SetNeedCalcDimension();
			pFaultFolder->AddChild(pFSticks);
			::AddObjectEvent(pFSticks);
			pFSticks = nullptr;
		}
		else if (sLine.length() > 90)
		{
			//	Data line.
			if (!pListSticks)
			{
				sSurveyName = sLine.mid(96).simplified();

				if (!pSurvey)
				{
					pSurvey = dynamic_cast<CX3DSurvey *>(::GetProject()->GetChild(sSurveyName, EX3DSurvey));
					if (!pSurvey)
					{
						QMessageBox::warning(NULL, "Importing Fault Sticks", "The destinate survey does not exist!");
						qFile.close();
						return false;
					}
				}
					
				pFaultFolder = (CXGeneralFolder *)(pSurvey->GetFolder(EXFaultFolder));
				pFSticks = new CXFaultSticks(sFaultName, pSurvey->GetObjectID());
				pListSticks = &pFSticks->GetAllSticks();
			}

			iNLineID = sLine.mid(32, 3).toInt();
			if (iNLineID != iELineID)
			{
				if (iOffset > 3)
				{
					//	Only accpet stick more than 1 point.
					double *pData = new double[iOffset];
					memcpy(pData, pBuff, sizeof(double) * iOffset);

					CXFaultStick *pStick = new CXFaultStick;
					pStick->ResetData(pData, iOffset / 3);
					pListSticks->append(pStick);
				}

				iELineID = iNLineID;
				iOffset = 0;
			}

			pBuff[iOffset] = sLine.mid(0, 16).toDouble();
			iOffset++;
			pBuff[iOffset] = sLine.mid(16, 16).toDouble();
			iOffset++;
			pBuff[iOffset] = sLine.mid(35, 12).toDouble();
			iOffset++;
		}
	}

	delete pWaitCursor;

	return true;
}

bool CXGeoQuestCardImage7File::importHorizon()
{
	CXSeismicUTMTool totalUTM;
	QList<CX3DHorizon *> listHorizon;
	
	QFile qFile(m_sFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}
	QTextStream stream(&qFile);
	QString sLine, sSubLine, sSurveyName = "", sHorizonName = "";
	QStringList strList;
	QVector<float> vecData;	//	Stored z, line, cdp.
	double dX, dY, dZ, dT, dL;
	int iInline, iXline, iInline1, iXline1, iInline2 = -1, iXline2, iInline3, iXline3;
	double x1, y1, x2, y2, x3, y3;
	std::set<int> setLine;
	std::set<int> setTrace;

	CXWaitCursor *pWaitCursor = new CXWaitCursor;
	while (!stream.atEnd())
	{
		sLine = stream.readLine();

		//	Skip comment lines.
		if (sLine.startsWith("SNAPPING", Qt::CaseInsensitive))
			continue;

		if (sLine.startsWith("PROFILE", Qt::CaseInsensitive))
		{
			//	The begining of a new horizon.
			sHorizonName = sLine.mid(8, 16).simplified();
			vecData.clear();
			setLine.clear();
			setTrace.clear();
		}
		else if (sLine.startsWith("EOD ", Qt::CaseInsensitive))
		{
			//	End of o horizon.
			if (vecData.isEmpty() || setLine.size() < 2 || setTrace.size() < 2)
				continue;

			//	Find out the line step.
			int i, j, k, iLStep = 999, iTStep = 999;
			for (auto iter = setLine.begin(); std::next(iter) != setLine.end(); ++iter)
			{
				if (iLStep > *std::next(iter) - *iter)
					iLStep = *std::next(iter) - *iter;
			}
			int iNumLine = (*setLine.rbegin() - *setLine.begin()) / iLStep + 1;
			for (auto iter = setTrace.begin(); std::next(iter) != setTrace.end(); ++iter)
			{
				if (iTStep > *std::next(iter) - *iter)
					iTStep = *std::next(iter) - *iter;
			}
			int iNumTrace = (*setTrace.rbegin() - *setTrace.begin()) / iTStep + 1;

			//	Create the utm.
			CXSeismicUTMTool utm;
			utm.InitSize(*setLine.begin(), iNumLine, iLStep, *setTrace.begin(), iNumTrace, iTStep);
			utm.InitCoordinates(iInline1, iXline1, x1, y1, iInline2, iXline2, x2, y2, iInline3, iXline3, x3, y3);

			//	Compatible to the survey?
			if (totalUTM.GetNI() == 0)
			{
				totalUTM = CXSeismicUTMTool(utm);
			}
			else
			{
				if (!totalUTM.MergeUTM(utm))
				{
					//	Not compatible!
					QMessageBox::warning(NULL, "Import Horizons", sHorizonName + " not compatible with others!");
					continue;
				}
			}

			//	Create the horizon and populate its data.
			CX3DHorizon *pHorizon = new CX3DHorizon(QUuid(), utm, sHorizonName);
			float *pData = pHorizon->GetData();
			for (k = 0; k < vecData.size(); k += 3)
			{
				iInline = vecData[k + 1];
				iXline = vecData[k + 2];
				utm.LineToIJ(iInline, iXline, i, j);
				pData[i * iNumTrace + j] = vecData[k];
			}
			pHorizon->SetModifiedFlag();
			listHorizon << pHorizon;
		}
		else if(sLine.length() > 90)
		{
			//	Data line.
			dX = sLine.mid(0, 16).toDouble();
			dY = sLine.mid(16, 16).toDouble();
			dZ = sLine.mid(32, 15).toFloat();
			dT = sLine.mid(47, 10).toFloat();
			sSubLine = sLine.mid(90).simplified();
			strList = sSubLine.split(" ");
			dL = strList[0].toFloat();
			
			if (sSurveyName.isEmpty() && strList.size() > 1)
				sSurveyName = strList[1];

			iInline = (int)dL;
			iXline = (int)dT;

			if (vecData.isEmpty())
			{
				//	The 1st point.
				iInline1 = iInline;
				iXline1 = iXline;
				x1 = dX;
				y1 = dY;
			}
			else if (iInline2 == iInline || iInline2 == -1)
			{
				//	The 2nd point, should be the last trace on the 1st line.
				iInline2 = iInline;
				iXline2 = iXline;
				x2 = dX;
				y2 = dY;
			}
			else
			{
				//	The 3rd point, should be the last trace on the last line.
				iInline3 = iInline;
				iXline3 = iXline;
				x3 = dX;
				y3 = dY;
			}

			vecData << dZ << dL << dT;
			setTrace.insert(iXline);
			setLine.insert(iInline);
		}
	}

	qFile.close();

	if (!listHorizon.isEmpty())
	{
		CX3DSurvey *pSurvey = new CX3DSurvey(totalUTM, sSurveyName);
		::GetProject()->AddChild(pSurvey);
		CXGeneralFolder *pHFolder = dynamic_cast<CXGeneralFolder *>(pSurvey->GetFolder(EXHorizonFolder));

		foreach(CX3DHorizon *pHorizon, listHorizon)
		{
			pHorizon->SetSurveyID(pSurvey->GetObjectID());
			sHorizonName = pHFolder->GetUnallocatedName(pHorizon->GetObjectName());
			pHorizon->SetObjectName(sHorizonName);
			pHFolder->AddChild(pHorizon);
		}

		::AddObjectEvent(pSurvey);
	}

	delete pWaitCursor;

	return true;
}