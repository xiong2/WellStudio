#include <qdebug.h>
#include <QFile>
#include <qapplication.h>
#include <qmessagebox.h>
#include "xwelllogasciifile.h"
#include "xglobal.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xwellcurvealias.h"
#include "xtree.h"
#include "xtemplate.h"

bool CXWellLogASCIIFile::Import()
{
	//	The target object name is NULL, need not import.
	if (m_sObjName == "" || m_iDepthID == 999)
		return false;

	QApplication::setOverrideCursor(Qt::WaitCursor);

	//	Find the well first.
	CXObject *pWellFolder = ::GetRootObjectFolder(EXWellFolder);
	CXWell *pWell = (CXWell *)pWellFolder->GetChild(m_sObjName);

	//	Not found? create it!
	if (!pWell)
	{
		pWell = new CXWell(m_sObjName);

		//	Add the well to the project.
		pWellFolder->AddChild(pWell);
	}

	//	Prepare the file.
	QFile qFile(m_sFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QTextStream stream(&qFile);
	qint64 iCurrentLine = 1;

	//	Skip the file header.
	while (!stream.atEnd() && iCurrentLine < m_iImportFrom)
	{
		stream.readLine();
		iCurrentLine++;
	}

	//	Now prepare the data buff.
	qint64 iLength = m_iImportEnd - m_iImportFrom + 1;
	int i, j, iIDX = 0;
	int iNumCurves = m_fListUnitRatio.size();
	int iNumColumn = m_sListColumnChosen.size();
	double **pDataArray = new double*[iNumCurves];
	for (i = 0; i < iNumCurves; i++)
		pDataArray[i] = new double[iLength];

	//	Read the file contents.
	while (!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		QString sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if (sListValue.size() != iNumColumn)
			break;

		for (j = 0, i = 0; i < iNumColumn; i++)
		{
			if (m_sListColumnChosen[i] == "Do not import")
				continue;

			pDataArray[j][iIDX] = sListValue[i].toDouble();
			j++;
		}

		iIDX++;
	}

	//	Process the depth curve.
	iLength = iIDX;
	double dStart = pDataArray[m_iDepthID][0];
	double dEnd = pDataArray[m_iDepthID][iLength - 1];
	double dStep = pDataArray[m_iDepthID][1] - pDataArray[m_iDepthID][0];

	if (m_fListUnitRatio[m_iDepthID] != 1.)
	{
		dStart *= m_fListUnitRatio[m_iDepthID];
		dEnd *= m_fListUnitRatio[m_iDepthID];
		dStep *= m_fListUnitRatio[m_iDepthID];
	}

	//pWell->SetWellStep(dStep);
	pWell->ExpandWellRange(dStart, dEnd, dStep);

	delete[]pDataArray[m_iDepthID];

	//	Loop to process each curve.
	for (j = 0, i = 0; i < iNumColumn; i++)
	{
		if (m_sListColumnChosen[i] == "Do not import")
			continue;

		if (j != m_iDepthID)
		{
			if (m_fListUnitRatio[j] != 1.)
			{
				for (iIDX = 0; iIDX < iLength; iIDX++)
				{
					pDataArray[j][iIDX] *= m_fListUnitRatio[j];
				}
			}

			CXWellCurve *pCurve = new CXWellCurve(m_sListColumnChosen[i]);
			pCurve->ResetData(dStart, dStep, iLength, pDataArray[j]);
			CXObject *pAlias = CXWellCurveAlias::GetAlias(pCurve->GetObjectName());
			CXTemplate *pTemplate = CXTemplate::GetTemplate(m_sListTemplate[j]);
			pAlias->SetTemplateID(pTemplate->GetID());
			pCurve->SetAliasID(pAlias->GetObjectID());

			pWell->AddChild(pCurve);
		}

		j++;
	}

	::AddObjectEvent(pWell);

	delete[]pDataArray;

	QApplication::restoreOverrideCursor();

	return true;
}