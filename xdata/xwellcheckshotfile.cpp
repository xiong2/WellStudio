#include <qmessagebox.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>
#include "xwellcheckshotfile.h"
#include "xglobal.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xwelltd.h"

bool CXWellCheckShotFile::CheckSelectedColumns(QStringList& sListChosenColumn)
{
	if (!sListChosenColumn.contains("TWT"))
	{
		QMessageBox::warning(NULL, "Importing Check Shot Files", "TWT should be selected!");
		return false;
	}

	int iNumDep = 0;
	if (sListChosenColumn.contains("MD"))
		iNumDep++;
	if (sListChosenColumn.contains("TVD"))
		iNumDep++;
	if (sListChosenColumn.contains("TVDSS"))
		iNumDep++;
	if (iNumDep != 1)
	{
		QMessageBox::warning(NULL, "Importing Check Shot Files", "One and only one from MD, TVD and TVDSS should be selected!");
		return false;
	}

	return true;
}

bool CXWellCheckShotFile::Import()
{
	//	Find the well first.
	CXObject *pWellFolder = ::GetRootObjectFolder(EXWellFolder);
	CXWell *pWell = (CXWell *)pWellFolder->GetChild(m_sObjName);

	//	Not found? create it!
	if (!pWell)
	{
		QMessageBox::critical(NULL, "Importing Well TD", "The object well " + m_sObjName + " does not exist yet!");
		return false;
	}
	CXWellPath *pWPath = pWell->GetWellPath();
	double dKB = pWell->GetKB();

	int iDType = 0;	//	0 MD, 1 TVD, 2 TVDSS.
	int iIDXT = m_sListColumnChosen.indexOf("TWT");
	int iIDXD = m_sListColumnChosen.indexOf("MD");
	if (iIDXD == -1)
	{
		iDType = 1;
		iIDXD = m_sListColumnChosen.indexOf("TVD");
		if (iIDXD == -1)
		{
			iIDXD = m_sListColumnChosen.indexOf("TVDSS");
			iDType = 2;
		}
	}

	int iIDXMax = qMax(iIDXT, iIDXD);

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

	//	Data buffer.
	QVector<double> vecTData, vecDData;
	vecTData.reserve(1024);
	vecDData.reserve(1024);

	//	Read the file contents.
	while (!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		QString sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if (sListValue.size() <= iIDXMax)
			continue;

		double dValue = sListValue[iIDXT].toDouble();
		if (dValue == m_dInvalid)
			dValue = g_dInvalidData;
		else if (m_fListUnitRatio[0] != 1.)
			dValue *= m_fListUnitRatio[0];
		vecTData << dValue;

		dValue = sListValue[iIDXD].toDouble();
		if (dValue == m_dInvalid)
			dValue = g_dInvalidData;
		else if (m_fListUnitRatio[1] != 1.)
			dValue *= m_fListUnitRatio[1];

		if(iDType == 1)
			dValue -= dKB;
		else if(iDType == 0)
			dValue = pWPath->Md2Tvd(dValue);
		vecDData << dValue;
	}

	int iSize = vecDData.size();
	double *pBuff = new double[2 * iSize];
	memcpy(pBuff, vecDData.data(), sizeof(double) * iSize);
	memcpy(pBuff + iSize, vecTData.data(), sizeof(double) * iSize);

	CXWellTD *pTD = new CXWellTD;

	QString sName = pWell->GetUnallocatedName("TD");
	pTD->SetObjectName(sName);
	QFileInfo qFI(m_sFile);
	pTD->SetIconName("From checkshot file: " + qFI.fileName());
	pTD->ResetData(pBuff, 2 * iSize);
	pWell->AddChild(pTD);
	pWell->SetActivatedTDName(sName);

	qFile.close();

	return true;
}