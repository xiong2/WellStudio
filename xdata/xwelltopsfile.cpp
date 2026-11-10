#include <qdebug.h>
#include <QFile>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include "xglobal.h"
#include "xwelltopsfile.h"
#include "xwelltops.h"
#include "xtree.h"
#include "xproject.h"

QStringList CXWellTopsFile::GetAllFormationsInFile()
{
	QStringList sListAllFormation;
	int i;
	QFile qFile(m_sFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		return sListAllFormation;
	}

	QFileInfo qFI(m_sFile);

	QTextStream stream(&qFile);
	qint64 iCurrentLine = 1;

	//	Skip the file header.
	while (!stream.atEnd() && iCurrentLine < m_iImportFrom)
	{
		stream.readLine();
		iCurrentLine++;
	}

	int iFIDX = m_sListColumnChosen.indexOf("Formation");

	//	Read the file contents.
	while (!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
		QString sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if (sListValue.size() <= iFIDX)
			continue;

		QString strFormation = sListValue[iFIDX];
		if (!sListAllFormation.contains(strFormation))
			sListAllFormation << strFormation;
	}

	qFile.close();

	return sListAllFormation;
}

bool CXWellTopsFile::Import()
{
	int i;
	QFile qFile(m_sFile);
	if(!qFile.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QFileInfo qFI(m_sFile);

	//	Create the well tops.
	//CXWellTops *pWellTops = new CXWellTops(qFI.baseName());
	CXWellTops *pWellTops = dynamic_cast<CXWellTops*>(::GetRootObjectFolderOnly(EXWellTops));
	if (!pWellTops)
	{
		pWellTops = new CXWellTops();
		::GetProject()->AddChild(pWellTops);
	}

	//	Initialize well tops, note "Well" and "Formation" are default attributes.
//	QStringList sListAtt(m_sListAttributes);
//	sListAtt.removeAll("Well");
//	sListAtt.removeAll("Formation");
//	pWellTops->InitWellTops(sListAtt);

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
	int iNumAtt = m_sListAttributes.size(), iMaxIDX = 0;
	for(i = 0; i < iNumAtt; i++)
	{
		int iIDX = m_sListColumnChosen.indexOf(m_sListAttributes[i]);
		iListIDX<<iIDX;

		if (iIDX > iMaxIDX)
			iMaxIDX = iIDX;
	}

	//	Read the file contents.
	while(!stream.atEnd() && iCurrentLine <= m_iImportEnd)
	{
        QString sLine = stream.readLine();
		iCurrentLine++;

		QStringList sListValue = m_pDelimiter->GetSplittedString(sLine);
		if(sListValue.size() <= iMaxIDX)
			continue;

		vListValue.clear();
		QVector3D point3;
		QString strWell, strFormation;
		double md = ::g_dInvalidData;
		for(i = 0; i < iNumAtt; i++)
		{
			if (m_sListAttributes[i] == "Well")
			{
				strWell = sListValue[iListIDX[i]];
			}
			else if (m_sListAttributes[i] == "Formation")
			{
				strFormation = sListValue[iListIDX[i]];
			}
			else{
				double dValue = sListValue[iListIDX[i]].toDouble();
				if (m_fListUnitRatio[i] != 1.)
				{
					dValue *= m_fListUnitRatio[i];
				}

				if (m_sListAttributes[i] == "X")
				{
					point3.setX(dValue);
				}
				else if (m_sListAttributes[i] == "Y")
				{
					point3.setY(dValue);
				}
				else if (m_sListAttributes[i] == "Z")
				{
					point3.setZ(dValue);
				}
				else if (m_sListAttributes[i] == "Depth")
				{
					md = dValue;
				}
			}
		}

		//	Abort the formation not selected.
		if (!m_sListSelectedFormation.contains(strFormation))
			continue;

		pWellTops->AddOneRecord(strWell, strFormation, md);
		pWellTops->AddOneRecord(strWell, strFormation, point3);
		//	Add one record into the well tops.
	//	pWellTops->AddOneRecord(m_sListAttributes, vListValue);//lint
	}

	qFile.close();

	pWellTops->GenerateFormations();
	::AddObjectEvent(pWellTops);

	return true;
}

bool CXWellTopsFile::CheckSelectedColumns(QStringList& sListChosenColumn)
{
	if(!sListChosenColumn.contains("Well")
		|| !sListChosenColumn.contains("Formation")
		|| (!sListChosenColumn.contains("Depth") && !sListChosenColumn.contains("Z")))
	{
 		if(::UsingChinese())
			QMessageBox::warning(NULL, GetTr("加载井分层文件"), GetTr("Well、Formation、(Depth或者Z)必须被选中！"));
		else
			QMessageBox::warning(NULL, "Importing Well Tops Files", "At least Well, Formation,( Depth or Z )should be selected!");
		
		return false;
	}

	if (sListChosenColumn.contains("X")
		|| sListChosenColumn.contains("Y")
		|| sListChosenColumn.contains("Z"))
	{
		if (!sListChosenColumn.contains("X")
			|| !sListChosenColumn.contains("Y")
			|| !sListChosenColumn.contains("Z"))
		{
			if (::UsingChinese())
				QMessageBox::warning(NULL, GetTr("加载井分层文件"), GetTr("X、Y和Z必须同时被选中或不选中！"));
			else
				QMessageBox::warning(NULL, "Importing Well Tops Files", "X, Y and Z should be set up simultaneously, or do not set anyone!");

			return false;
		}
	}
	return true;
}