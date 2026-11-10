#include <qdebug.h>
#include <QFile>
#include <qfileinfo.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include "xglobal.h"
#include "xmicroseismicfile.h"
#include "xmicroseismicdata.h"
#include "xtree.h"
#include "xwell.h"

bool CXMicroSeismicFile::Import()
{
	int i;

	//	Find the well information first.
	CXObject *pWellFolder = ::GetRootObjectFolder(EXWellFolder);
	CXWell *pWell = (CXWell *)pWellFolder->GetChild(m_sObjName);
	if(!pWell)
		return false;
	
	QFile qFile(m_sFile);
	if(!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QFileInfo qFI(m_sFile);

	//	Create the micro seismic object.
	CXMicroSeismicData *pMS = new CXMicroSeismicData(qFI.baseName());

	//	Initialize micro seismic object, we use x, y, z rather than dx, dy, dz.
	QStringList sListAtt(m_sListAttributes);
	//bool bDelta = false;
	if(sListAtt.contains("DX"))
	{
		//bDelta = true;
		sListAtt.replaceInStrings("DX", "X");
		sListAtt.replaceInStrings("DY", "Y");
		sListAtt.replaceInStrings("DZ", "Z");
	}

	pMS->InitTables(sListAtt);
	QTextStream stream(&qFile);
	qint64 iCurrentLine = 1;

	//	Skip the file header.
	while(!stream.atEnd() && iCurrentLine < m_iImportFrom)
	{
		stream.readLine();
		iCurrentLine++;
	}

	QList<QVariant> vListValue;
	QList<int> iListIDX;
	int iNumAtt = m_sListAttributes.size();
	for(i = 0; i < iNumAtt; i++)
	{
		int iIDX = m_sListColumnChosen.indexOf(m_sListAttributes[i]);
		iListIDX<<iIDX;
	}

	//	Read the file contents.
	while(!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		QString sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if(sListValue.size() != m_sListColumnChosen.size())
			continue;

		vListValue.clear();
		for(i = 0; i < iNumAtt; i++)
		{
			if(m_fListUnitRatio[i] != 1.)
			{
				double dValue = sListValue[iListIDX[i]].toDouble();
				dValue *= m_fListUnitRatio[i];
				vListValue<<dValue;
			}
			else
				vListValue<<sListValue[iListIDX[i]];
		}

		//	Add one record into the well tops.
		pMS->AddOneRecord(m_sListAttributes, vListValue);
	}

	qFile.close();

	pWell->AddChild(pMS);
	::AddObjectEvent(pMS);

	return true;
}

bool CXMicroSeismicFile::CheckSelectedColumns(QStringList& sListChosenColumn)
{
	if((!sListChosenColumn.contains("X") || !sListChosenColumn.contains("Y") || !sListChosenColumn.contains("Z"))
		&& (!sListChosenColumn.contains("DX") || !sListChosenColumn.contains("DY") || !sListChosenColumn.contains("DZ"))) 
	{
 		if(::UsingChinese())
			QMessageBox::warning(NULL, GetTr("加载微地震文件"), GetTr("X, Y, Z或者DX, DY, DZ必须被选中！"));
		else
			QMessageBox::warning(NULL, "Importing Micro Seismic Files", "Either X, Y, Z or DX, DY, DZ should be selected!");
		
		return false;
	}

	return true;
}