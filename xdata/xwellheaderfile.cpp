#include <qdebug.h>
#include <QFile>
#include <qtextstream.h>
#include <qmessagebox.h>
#include "xwellheaderfile.h"
#include "xglobal.h"
#include "xtree.h"
#include "xproject.h"
#include "xgeneralfolder.h"
#include "xwell.h"
#include "xwellpath.h"

bool CXWellHeaderFile::Import()
{
	double dX, dY = g_dInvalidData, dKB, dTD = g_dInvalidData;

	int iXPos = m_sListAttributes.indexOf("X Coordinate");
	int iYPos = m_sListAttributes.indexOf("Y Coordinate");
	int iKBPos = m_sListAttributes.indexOf("KB");
	int iTDPos = m_sListAttributes.indexOf("Total Depth");
	int iTypePos = m_sListAttributes.indexOf("Type");

	int iMaxID = qMax(qMax(qMax(qMax(iXPos, iYPos), iKBPos), iTDPos), iTypePos);

	// Find the well folder.
	CXGeneralFolder *pWellFolder = (CXGeneralFolder *)::GetRootObjectFolder(EXWellFolder);

	QFile qFile(m_sFile);
	if(!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QTextStream stream(&qFile);
	qint64 iCurrentLine = 1;
	QString strWellName;

	//	Skip the file header.
	while(!stream.atEnd() && iCurrentLine < m_iImportFrom)
	{
		stream.readLine();
		iCurrentLine++;
	}

	//	Read the file contents.
	while(!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		QString sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if (sListValue.size() <= iMaxID)
			continue;

		//	Well position.
		dKB = 0;
		dX = dY = dTD = g_dInvalidData;
		if (iXPos != -1)
			dX = sListValue[m_sListColumnChosen.indexOf("X Coordinate")].toDouble() * m_fListUnitRatio[iXPos];
		if(iYPos != -1)
			dY = sListValue[m_sListColumnChosen.indexOf("Y Coordinate")].toDouble() * m_fListUnitRatio[iYPos];
		if(iKBPos != -1)
			dKB = sListValue[m_sListColumnChosen.indexOf("KB")].toDouble() * m_fListUnitRatio[iKBPos];
		if(iTDPos != -1)
			dTD = sListValue[m_sListColumnChosen.indexOf("Total Depth")].toDouble() * m_fListUnitRatio[iTDPos];

		//	Get the well name.
		strWellName = sListValue[m_sListColumnChosen.indexOf("Well")];

		//	Does it exist?
		CXWell *pWell = (CXWell *)pWellFolder->GetChild(strWellName);
		if(!pWell)
		{
			//	Well does not exist, create it!
			pWell = new CXWell(strWellName, dX, dY);

			//	Add the well to the project.
			pWellFolder->AddChild(pWell);
			::AddObjectEvent(pWell);

			if(dKB != 0 || dTD != g_dInvalidData)
			{
				//	Reset the well position.
				unsigned int iNumber;
				CXWellPath *pWellPath = pWell->GetWellPath();
				double *pData = pWellPath->GetData(iNumber);

				pData[2] -= dKB;
				if(dTD != g_dInvalidData)
					pData[5] = dTD - dKB;
				else
					pData[5] -= dKB;
			}
		}
		else
		{
			if(dX != g_dInvalidData && dY != g_dInvalidData)
			{
				//	Reset the well position.
				unsigned int iNumber;
				CXWellPath *pWellPath = pWell->GetWellPath();
				double *pData = pWellPath->GetData(iNumber);

				//	Only while well path just contains 2 points (top & bottom) we can reset well position.
				if(iNumber == 6)
				{
					if(pData[0] == pData[3] && pData[1] == pData[4])
					{
						//	Top and bottom has the same coordinate, so should be moved the same time.
						pData[0] = pData[3] = dX;
						pData[1] = pData[4] = dY;
					}
					else
					{
						//	Only move the top.
						pData[0] = dX;
						pData[1] = dY;
					}

					if(dKB != 0 || dTD != g_dInvalidData)
					{
						pData[2] -= dKB;
						if(dTD != g_dInvalidData)
							pData[5] = dTD - dKB;
						else
							pData[5] -= dKB;
					}
				}
			}
		}

		if (dKB != 0)
			pWell->SetKB(dKB);

		if(iTypePos != -1)
			pWell->AddAttribute("Type", sListValue[m_sListColumnChosen.indexOf("Type")]);
	}

	qFile.close();

	return true;
}

bool CXWellHeaderFile::CheckSelectedColumns(QStringList& sListChosenColumn)
{
	if(!sListChosenColumn.contains("Well"))
	{
 		if(::UsingChinese())
			QMessageBox::warning(NULL, GetTr("加载井头文件"), GetTr("Well必须被选中！"));
		else
			QMessageBox::warning(NULL, "Importing Well Header Files", "At least Well should be selected!");

		return false;
	}

	return true;
}