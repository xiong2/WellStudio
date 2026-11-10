#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qmap.h>
#include "xwell.h"
#include "xasciifile.h"
#include "xlaswisfile.h"
#include "xwellheaderfile.h"
#include "xwellpathfile.h"
#include "xwellcheckshotfile.h"
#include "xwelltopsfile.h"
#include "xwelllogasciifile.h"
#include "xmicroseismicfile.h"
#include "xpointsfile.h"
#include "xfaultsticksfile.h"
#include "xdataimporter.h"
#include "xpageasciifile.h"
#include "xpagematchwells.h"
#include "xpagelascurves.h"
#include "xpagelascurvesnotemplate.h"
#include "xpagelogcurves.h"
#include "xpageattributes.h"
#include "xpagewellpath.h"
#include "xpageimportformation.h"
#include "xfile3dsurface.h"
#include "xpagefile3dsurface.h"
#include "xwaitcursor.h"
#include "xpageloadsegy.h"
#include "xsegyimporter.h"
#include "xdlgimport2dsegy.h"
#include "xdlgimportreservoir.h"
#include "xproject.h"
#include <QtCore/QSettings>
#include "xconsole.h"
#include "xgeoquestcardimage7file.h"
#include "xfracturepatchfile.h"

QMap<QString, int> gMapNameFilterToType;

bool CXDataImporter::ImportData(EImportFileType eType, CXObject *pObj)
{
	QString sTitle, sFilter;
	QStringList strListFilter;
	gMapNameFilterToType.clear();

	//	There must have a survey before importing fault sticks!
	//if (eType == eFaultSticksASCII)
	//{
	//	if (::GetProject()->GetChildren(EX3DSurvey).isEmpty())
	//	{
	//		QMessageBox::warning(NULL, "Importing Fault Files", "Fault should belong to one survey, so please create or import a survey first!");
	//		return false;
	//	}
	//}

	switch(eType)
	{
	case eWellHeaderASCII:
		sTitle = "Import Well Header ASCII Files";
		sFilter = "ASCII File (*)";
		break;
	case eWellPathASCII:
		sTitle = "Import Well Path ASCII Files";
		sFilter = "ASCII File (*)";
		break;
	case eWellLAS:
	case eWellLAS_NoTemplate:
		sTitle = "Import Well LAS Files";
		sFilter = "LAS File (*.las)";
		break;
	case eWellWIS:
		sTitle = "Import Well WIS Files";
		sFilter = "WIS File (*.wis)";
		break;
	case eWellXTF:
		sTitle = "Import Well XTF Files";
		sFilter = "XTF File (*.xtf)";
		break;
	case eWellDLIS:
		sTitle = "Import Well DLIS Files";
		sFilter = "DLIS File (*.dlis)";
		break;
	case eWellASCIILog:
		sTitle = "Import Well ASCII Files";
		sFilter = "ASCII File (*)";
		break;
	case eWellCheckShot:
		sTitle = "Import Check Shot Files";
		sFilter = "Check Short File (*)";
		break;
	case eWellTopsASCII:
		sTitle = "Import Well Tops Files";
		sFilter = "Tops ASCII File (*)";
		break;
	case eFracturePatches:
		sTitle = "Imort Fracture Patch file";
		sFilter = "FAB File(*.fab)";
		break;
	case eMicroSeismicASCII:
		sTitle = "Import Micro Seismic File";
		sFilter = "ASCII File (*)";
		break;
	case e3DPointsASCII:
		sTitle = "Import Points ASCII Files";
		sFilter = "Points ASCII File (*)";
		break;
	case eFaultPolygonASCII:
		sTitle = "Import Fault Polygon ASCII Files";
		gMapNameFilterToType.insert("Fault Polygon[ASCII](*)", eFaultPolygonASCII);
		strListFilter = QStringList(gMapNameFilterToType.keys());
		break;
	case eFaultSticksASCII:
		{
			gMapNameFilterToType.insert("Fault Sticks[ASCII](*)", eFaultSticksASCII);
			gMapNameFilterToType.insert("GeoQuest Card Image 7(*)", eGeoquestCardImage7);
			strListFilter = QStringList(gMapNameFilterToType.keys());

			sTitle = "Import Fault Sticks ASCII Files";
		}
		break;
	case eZMapASCII:
		{
			gMapNameFilterToType.insert("Zmap+ Grid[ASCII](*)", eZMapASCII);
			gMapNameFilterToType.insert("3-D Horizon Picks[ASCII](*)", e3DHorizonPicks);
			gMapNameFilterToType.insert("GeoQuest Card Image 7(*)", eGeoquestCardImage7);
			strListFilter = QStringList(gMapNameFilterToType.keys());

			sTitle = "Import 3-D Surface Files";
		}

		break;
	case e3DSEGY:
		{
			strListFilter << "3-D or Prestack SEGY (*.segy *.sgy)"
				<< "2-D Poststack SEGY (*.segy *.sgy)";
			gMapNameFilterToType.insert(strListFilter[0], e3DSEGY);
			gMapNameFilterToType.insert(strListFilter[1], e2DSEGY);

			sTitle = "Import SEG-Y files";
		}
		break;
	case e2DSEGY:
	{
		strListFilter << "2-D SEGY (*.segy *.sgy)";
		gMapNameFilterToType.insert(strListFilter[0], e2DSEGY);

		sTitle = "Import SEG-Y files";
	}
	break;
	case eReservoir:
		sTitle = "Import Reservoir file";
		sFilter = "*.grdecl";
		break;
	}

	QFileDialog dialog(NULL, sTitle);
	dialog.setFileMode(QFileDialog::ExistingFiles);
	if (strListFilter.empty())
		dialog.setNameFilter(sFilter);
	else
		dialog.setNameFilters(strListFilter);

	QSettings settings("XStudio", "RecentDataDir");
	QString recentDataDir = settings.value("lastPath").toString();
	if (!recentDataDir.isEmpty()) dialog.setDirectory(recentDataDir);

	QStringList sListFiles;
	QString strSelectedFilter;
	if(dialog.exec())
	{
		QDir currentDir = dialog.directory();
		settings.setValue("lastPath", currentDir.absolutePath());
		sListFiles = dialog.selectedFiles();
		strSelectedFilter = dialog.selectedNameFilter();
	}

	//	No file selected.
	if(sListFiles.size() == 0)
		return false;

	bool bRes = false;
	switch(eType)
	{
	case eWellHeaderASCII:
		bRes = importWellASCIIHeaderFiles(sListFiles);
		break;
	case eWellPathASCII:
		bRes = importWellASCIIPathFiles(sListFiles);
		break;
	case eWellLAS:
		bRes = importWellLasDlisFiles(sListFiles, true);
		break;
	case eWellWIS:
		bRes = importWellWISFiles(sListFiles);
		break;
	case eWellXTF:
		bRes = importWellXTFFiles(sListFiles);
		break;
	case eWellDLIS:
		bRes = importWellLasDlisFiles(sListFiles, false);
		break;
	case eWellLAS_NoTemplate:
		bRes = importWellLasDlisFiles(sListFiles, true, true);
		break;
	case eWellASCIILog:
		bRes = importWellASCIILogFiles(sListFiles);
		break;
	case eWellCheckShot:
		bRes = importWellCheckShotFiles(sListFiles);
		break;
	case eWellTopsASCII:
		bRes = importWellASCIITopsFiles(sListFiles);
		break;
	case eMicroSeismicASCII:
		bRes = importMicroSeismicFiles(sListFiles, pObj);
		break;
	case eFracturePatches:
		bRes = importFABFile(sListFiles);
		break;
	case e3DPointsASCII:
		bRes = importPointsASCIIFiles(sListFiles);
		break;
	case eFaultPolygonASCII:
		bRes = importFaultSticksASCIIFiles(strSelectedFilter, sListFiles);
		break;
	case eFaultSticksASCII:
		bRes = importFaultSticksASCIIFiles(strSelectedFilter, sListFiles);
		break;

	case eZMapASCII:
		bRes = import3DSurfaceFiles(strSelectedFilter, sListFiles);
		break;
	case  e3DSEGY:
		bRes = importSegyFile(strSelectedFilter, sListFiles);
		break;
	case  e2DSEGY:
		bRes = importSegyFile(strSelectedFilter, sListFiles);
		break;
	case  eReservoir:
		bRes = importReservoirFile(sListFiles);
		break;
	default:
		break;
	}

	return bRes;
}

bool CXDataImporter::importWellASCIIHeaderFiles(QStringList sListFiles)
{
	CXASCIIFile *pAFile = new CXWellHeaderFile(sListFiles[0]);

	QWizard wizard;
	wizard.setWindowTitle("Import ASCII Well Header File");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	CXPageASCIIFile *pFilePage = new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageAttributes *pAttPage = new CXPageAttributes(pAFile);
	wizard.addPage(pAttPage);
	wizard.resize(1000, 600);

	//	Populate the candidates of each column for well header files.
	QStringList& sListCandidates = pAFile->GetColumnCandidates();
	sListCandidates<<"Do not import"<<"Well"<<"X Coordinate"<<"Y Coordinate"<<"KB"<<"Total Depth"<<"Type";

	if(wizard.exec() == QDialog::Accepted)
	{
		for(int i = 0; i < sListFiles.size(); i++)
		{
			pAFile->SetFile(sListFiles.at(i));
			pAFile->Import();
		}
	}

	delete pAFile;
	return true;
}

bool CXDataImporter::importWellASCIIPathFiles(QStringList sListFiles)
{
	int i;
	CXASCIIFile *pAFile = new CXWellPathFile(sListFiles[0]);
	QStringList sListWellInfo;
	QStringList sListMatchedWells;

	for(i = 0; i < sListFiles.size(); i++)
	{
		QFileInfo qFI(sListFiles.at(i));
		sListWellInfo << qFI.baseName() << qFI.baseName() << "" << "" << "";
		sListMatchedWells<<"";
	}

	QWizard wizard;
	wizard.setWindowTitle("Import ASCII Well Path File");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	CXPageMatchWells *pPageMatchWells	= new CXPageMatchWells(sListWellInfo, sListMatchedWells);
	wizard.addPage(pPageMatchWells);
	CXPageASCIIFile *pFilePage			= new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageWellPath *pPathPage			= new CXPageWellPath(pAFile);
	wizard.addPage(pPathPage);
	CXPageAttributes *pAttPage			= new CXPageAttributes(pAFile);
	wizard.addPage(pAttPage);
	wizard.resize(800, 600);

	//	Populate the candidates of each column for well header files.
	QStringList& sListCandidates = pAFile->GetColumnCandidates();
	sListCandidates<<"Do not import"<<"X"<<"Y"<<"Z"<<"TVD"<<"MD"<<"DX"<<"DY"<<"DZ"<<"Azimuth"<<"Inclination";

	if(wizard.exec() == QDialog::Accepted)
	{
		for(i = 0; i < sListFiles.size(); i++)
		{
			pAFile->SetFile(sListFiles.at(i), sListMatchedWells[i]);
			pAFile->Import();
		}
	}

	delete pAFile;
	return true;
}

bool CXDataImporter::importWellLasDlisFiles(QStringList sListFiles, bool bLAS, bool bNoTemplate)
{
	QList<CXLasWisFile *> listLASFile;
	QStringList sListWellInfo;
	QStringList sListMatchedWells;

	int iFileType = 0;
	if (!bLAS)
		iFileType = 3;

	for(int i = 0; i < sListFiles.size(); i++)
	{
		CXLasWisFile *pLASFile = new CXLasWisFile(sListFiles.at(i), iFileType);

		if(pLASFile->ParseFile())
		{
			listLASFile.append(pLASFile);

			QFileInfo qFI(sListFiles.at(i));
			CXWell *pWell = pLASFile->GetWell();
			double dWellX, dWellY;
			pWell->GetWellPosition(dWellX, dWellY);
			if (dWellX == ::g_dInvalidData || dWellY == ::g_dInvalidData)
			{
				sListWellInfo << qFI.baseName() << pWell->GetObjectName()
					<< pWell->GetAttribute("UWI")
					<< "" << "";
			}
			else
			{
				sListWellInfo << qFI.baseName() << pWell->GetObjectName()
					<< pWell->GetAttribute("UWI")
					<< QString::number(dWellX, 'f', 6) << QString::number(dWellY, 'f', 6);
			}
			sListMatchedWells<<"";
		}
		else
		{
			if(bLAS)
				QMessageBox::warning(NULL, "Importing LAS Files", sListFiles.at(i) + " is not a valid LAS file!");
			else
				QMessageBox::warning(NULL, "Importing DLIS Files", sListFiles.at(i) + " is not a valid DLIS file!");

			delete pLASFile;
		}
	}

	if(listLASFile.size() == 0)
		return false;

	if (bNoTemplate==false)
	{
		CXPageMatchWells *pPageMatchWells = new CXPageMatchWells(sListWellInfo, sListMatchedWells);
		CXPageLASCurves *pPageLASCurves = new CXPageLASCurves(listLASFile, sListMatchedWells, bLAS);
		QWizard wizard;
		if(bLAS)
			wizard.setWindowTitle("Import LAS Files");
		else
			wizard.setWindowTitle("Import DLIS Files");
		wizard.setWizardStyle(QWizard::ClassicStyle);
		wizard.addPage(pPageMatchWells);
		wizard.addPage(pPageLASCurves);
		wizard.resize(800, 600);
		wizard.exec();
	}
	else{
		CXPageMatchWells *pPageMatchWells = new CXPageMatchWells(sListWellInfo, sListMatchedWells);
		CXPageLASCurvesNoTemplate *pPageLASCurves = new CXPageLASCurvesNoTemplate(listLASFile, sListMatchedWells);
		QWizard wizard;
		wizard.setWindowTitle("Import LAS Files");
		wizard.setWizardStyle(QWizard::ClassicStyle);
		wizard.addPage(pPageMatchWells);
		wizard.addPage(pPageLASCurves);
		wizard.resize(800, 600);
		wizard.exec();
	}

	// release the las file.
	qDeleteAll(listLASFile);

	return true;
}

bool CXDataImporter::importWellWISFiles(QStringList sListFiles)
{
	QList<CXLasWisFile *> listWISFile;
	QStringList sListWellInfo;
	QStringList sListMatchedWells;

	for (int i = 0; i < sListFiles.size(); i++)
	{
		CXLasWisFile *pWISFile = new CXLasWisFile(sListFiles.at(i), 1);

		if (pWISFile->ParseFile())
		{
			listWISFile.append(pWISFile);

			QFileInfo qFI(sListFiles.at(i));
			CXWell *pWell = pWISFile->GetWell();
			double dWellX, dWellY;
			sListWellInfo << qFI.baseName() << pWell->GetObjectName()
				<< pWell->GetAttribute("UWI")
				<< "" << "";
			sListMatchedWells << "";
		}
	}

	CXPageMatchWells *pPageMatchWells = new CXPageMatchWells(sListWellInfo, sListMatchedWells);
	CXPageLASCurves *pPageLASCurves = new CXPageLASCurves(listWISFile, sListMatchedWells, false);
	QWizard wizard;
	wizard.setWindowTitle("Import WIS Files");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	wizard.addPage(pPageMatchWells);
	wizard.addPage(pPageLASCurves);
	wizard.resize(800, 600);
	wizard.exec();

	return true;
}

bool CXDataImporter::importWellXTFFiles(QStringList sListFiles)
{
	QList<CXLasWisFile *> listWISFile;
	QStringList sListWellInfo;
	QStringList sListMatchedWells;

	for (int i = 0; i < sListFiles.size(); i++)
	{
		CXLasWisFile *pWISFile = new CXLasWisFile(sListFiles.at(i), 2);

		if (pWISFile->ParseFile())
		{
			listWISFile.append(pWISFile);

			QFileInfo qFI(sListFiles.at(i));
			CXWell *pWell = pWISFile->GetWell();
			double dWellX, dWellY;
			sListWellInfo << qFI.baseName() << pWell->GetObjectName()
				<< pWell->GetAttribute("UWI")
				<< "" << "";
			sListMatchedWells << "";
		}
	}

	CXPageMatchWells *pPageMatchWells = new CXPageMatchWells(sListWellInfo, sListMatchedWells);
	CXPageLASCurves *pPageLASCurves = new CXPageLASCurves(listWISFile, sListMatchedWells, false);
	QWizard wizard;
	wizard.setWindowTitle("Import WIS Files");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	wizard.addPage(pPageMatchWells);
	wizard.addPage(pPageLASCurves);
	wizard.resize(800, 600);
	wizard.exec();

	return true;
}

bool CXDataImporter::importWellASCIILogFiles(QStringList sListFiles)
{
	int i;
	CXWellLogASCIIFile *pAFile = new CXWellLogASCIIFile(sListFiles[0]);

	QStringList sListWellInfo;
	QStringList sListMatchedWells;

	for (i = 0; i < sListFiles.size(); i++)
	{
		QFileInfo qFI(sListFiles.at(i));
		sListWellInfo << qFI.baseName() << "" << "" << "" << "";
		sListMatchedWells << "";
	}

	QWizard wizard;
	wizard.setWindowTitle("Import ASCII Log Files");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	CXPageMatchWells *pPageMatchWells = new CXPageMatchWells(sListWellInfo, sListMatchedWells);
	wizard.addPage(pPageMatchWells);
	CXPageASCIIFile *pFilePage = new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageLogCurves *pPageLogCurves = new CXPageLogCurves(pAFile);
	wizard.addPage(pPageLogCurves);
	wizard.resize(800, 600);

	if (wizard.exec() == QDialog::Accepted)
	{
		for (i = 0; i < sListFiles.size(); i++)
		{
			pAFile->SetFile(sListFiles.at(i), sListMatchedWells[i]);
			pAFile->Import();
		}
	}

	delete pAFile;

	return true;
}

bool CXDataImporter::importWellCheckShotFiles(QStringList sListFiles)
{
	CXASCIIFile *pAFile = new CXWellCheckShotFile(sListFiles[0]);
	QStringList sListWellInfo;
	QStringList sListMatchedWells;

	for (int i = 0; i < sListFiles.size(); i++)
	{
		QFileInfo qFI(sListFiles.at(i));
		sListWellInfo << qFI.baseName() << qFI.baseName() << "" << "" << "";
		sListMatchedWells << "";
	}

	QWizard wizard;
	wizard.setWindowTitle("Import Well Check Shot File");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	CXPageMatchWells *pPageMatchWells = new CXPageMatchWells(sListWellInfo, sListMatchedWells);
	wizard.addPage(pPageMatchWells);
	CXPageASCIIFile *pFilePage = new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageAttributes *pAttPage = new CXPageAttributes(pAFile);
	wizard.addPage(pAttPage);
	wizard.resize(1000, 600);

	//	Populate the candidates of each column for well header files.
	QStringList& sListCandidates = pAFile->GetColumnCandidates();
	sListCandidates << "Do not import" << "TVD" << "TVDSS" << "MD" << "TWT";

	if (wizard.exec() == QDialog::Accepted)
	{
		for (int i = 0; i < sListFiles.size(); i++)
		{
			pAFile->SetFile(sListFiles.at(i), sListMatchedWells[i]);
			pAFile->Import();
		}
	}

	delete pAFile;
	return true;
}

bool CXDataImporter::importWellASCIITopsFiles(QStringList sListFiles)
{
	int i;
	CXASCIIFile *pAFile = new CXWellTopsFile(sListFiles[0]);

	QWizard wizard;
	wizard.setWindowTitle("Import ASCII Well Tops File");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	CXPageASCIIFile *pFilePage = new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageImportFormation *pFormationPage = new CXPageImportFormation(pAFile);
	wizard.addPage(pFormationPage);
	CXPageAttributes *pAttPage = new CXPageAttributes(pAFile);
	wizard.addPage(pAttPage);
	wizard.resize(1000, 600);

	//	Populate the candidates of each column for tops files.
	QStringList& sListCandidates = pAFile->GetColumnCandidates();
	sListCandidates<<"Do not import"<<"Well"<<"Formation"<<"Depth"<<"X"<<"Y"<<"Z";

	if(wizard.exec() == QDialog::Accepted)
	{
		for(i = 0; i < sListFiles.size(); i++)
		{
			pAFile->SetFile(sListFiles.at(i));
			pAFile->Import();
		}
	}

	delete pAFile;
	return true;
}

bool CXDataImporter::importMicroSeismicFiles(QStringList sListFiles, CXObject *pObj)
{
	if(!pObj)
		return false;

	int i;
	CXASCIIFile *pAFile = new CXMicroSeismicFile(sListFiles[0]);

	QWizard wizard;
	wizard.setWindowTitle("Import ASCII Micro Seismic File");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	CXPageASCIIFile *pFilePage = new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageAttributes *pAttPage = new CXPageAttributes(pAFile);
	wizard.addPage(pAttPage);
	wizard.resize(1000, 600);

	//	Populate the candidates of each column for tops files.
	QStringList& sListCandidates = pAFile->GetColumnCandidates();
	sListCandidates<<"Do not import"<<"Stage"<<"Date"<<"Time"<<"X"<<"Y"<<"Z"<<"DX"<<"DY"<<"DZ"<<"Magnitude"<<"Energy"<<"Confidence";

	if(wizard.exec() == QDialog::Accepted)
	{
		for(i = 0; i < sListFiles.size(); i++)
		{
			pAFile->SetFile(sListFiles.at(i), pObj->GetObjectName());
			pAFile->Import();
		}
	}

	delete pAFile;
	return true;
}

bool CXDataImporter::importPointsASCIIFiles(QStringList sListFiles)
{
	int i;
	CXASCIIFile *pAFile = new CXPointsFile(sListFiles[0]);

	QWizard wizard;
	wizard.setWindowTitle("Import ASCII Points File");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	CXPageASCIIFile *pFilePage			= new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageAttributes *pAttPage			= new CXPageAttributes(pAFile);
	wizard.addPage(pAttPage);
	wizard.resize(800, 600);

	//	Populate the candidates of each column for well header files.
	QStringList& sListCandidates = pAFile->GetColumnCandidates();
	sListCandidates<<"Do not import"<<"X"<<"Y"<<"Z";

	if(wizard.exec() == QDialog::Accepted)
	{
		for(i = 0; i < sListFiles.size(); i++)
		{
			pAFile->SetFile(sListFiles.at(i));
			pAFile->Import();
		}
	}

	delete pAFile;
	return true;
}

bool CXDataImporter::importFaultSticksASCIIFiles(const QString& strNameFilter, const QStringList&  sListFiles)
{
	EImportFileType eFileType = static_cast<EImportFileType>(gMapNameFilterToType.value(strNameFilter));
	if (eFileType == eGeoquestCardImage7)
	{
		CXGeoQuestCardImage7File file(sListFiles.at(0), false);
		return file.Import();
	}

	int i;
	CXASCIIFile *pAFile = new CXFaultSticksFile(sListFiles[0], eFileType);

	QWizard wizard;
	wizard.setWizardStyle(QWizard::ClassicStyle);
	if(eFileType == eFaultSticksASCII)
		wizard.setWindowTitle("Import ASCII Fault Sticks File");
	else 
		wizard.setWindowTitle("Import ASCII Fault Polygon File");

	CXPageASCIIFile *pFilePage			= new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageFile3DSurface *pPageOne = new CXPageFile3DSurface(pAFile);
	wizard.addPage(pPageOne);
	CXPageAttributes *pAttPage = new CXPageAttributes(pAFile);
	wizard.addPage(pAttPage);
	wizard.resize(800, 600);

	//	Populate the candidates of each column for well header files.
	QStringList& sListCandidates = pAFile->GetColumnCandidates();
	if(eFileType == eFaultSticksASCII)
		sListCandidates<<"Do not import"<<"X"<<"Y"<<"Z"<<"Line ID";
	else
		sListCandidates<<"Do not import"<<"X"<<"Y"<<"Line ID";

	if(wizard.exec() == QDialog::Accepted)
	{
		for(i = 0; i < sListFiles.size(); i++)
		{
			QFileInfo qFI(sListFiles.at(i));
			pAFile->SetFile(sListFiles.at(i), qFI.baseName());
			pAFile->Import();
		}
	}

	delete pAFile;
	return true;
}

bool CXDataImporter::import3DSurfaceFiles(const QString& strNameFilter, const QStringList&  sListFiles)
{	
	EImportFileType eFileType = static_cast<EImportFileType>(gMapNameFilterToType.value(strNameFilter));	
	if (eFileType == eGeoquestCardImage7)
	{
		CXGeoQuestCardImage7File file(sListFiles.at(0));
		return file.Import();
	}

	CXFile3DSurface surfaceFile(eFileType, sListFiles.at(0));

	QWizard wizard;	
	wizard.setWindowTitle("Import 3-D Surface Files");
	wizard.setWizardStyle(QWizard::ClassicStyle);

	if (eFileType == e3DHorizonPicks)
	{
		CXPageASCIIFile *pFilePage			= new CXPageASCIIFile(&surfaceFile);
		wizard.addPage(pFilePage);
	}

	CXPageFile3DSurface *pPageOne	= new CXPageFile3DSurface(&surfaceFile);
	wizard.addPage(pPageOne);
	CXPageAttributes *pPageTwo	= new CXPageAttributes(&surfaceFile);
	wizard.addPage(pPageTwo);
	wizard.resize(800, 600);

	//	Populate the candidates of each column for well header files.
	QStringList& sListCandidates = surfaceFile.GetColumnCandidates();
	sListCandidates<<"Do not import"<<"Inline"<<"Xline"<<"X"<<"Y"<<"Z";

	//	Populate the candidates of each column for well header file
	if(wizard.exec() == QDialog::Accepted)
	{
		CXWaitCursor waitCursor;
		if (!surfaceFile.Import())
			return false;

		for (int i=1; i<sListFiles.size(); ++i)
		{
			if (!surfaceFile.SetAdditionalFile(sListFiles.at(i)))
				return false;

			if (!surfaceFile.Import())
				return false;
		}
	}
	
	return true;
}

bool CXDataImporter::importSegyFile(const QString& strNameFilter, const QStringList&  sListFiles)
{
	EImportFileType eFileType = static_cast<EImportFileType>(gMapNameFilterToType.value(strNameFilter));

	if (eFileType == e3DSEGY)
		return improt3DSegyFile(sListFiles);
	else if (eFileType == e2DSEGY)
		return improt2DPostStackSegyFile(sListFiles);
	
	return false;
}

bool CXDataImporter::improt2DPostStackSegyFile(QStringList  sListFiles)
{
	CXDlgImport2DSEGY dlgImporter(sListFiles);

	if (dlgImporter.exec() == QDialog::Accepted)
	{
		QList<CXSEGYLoadParameters*> listPara = dlgImporter.GetParameters();

		CXSEGYImporter::Import2DSEGY(listPara, dlgImporter.Get2DSurveyName());
	}

	return true;
}

bool CXDataImporter::improt3DSegyFile(QStringList  sListFiles)
{
	QWizard wizard(::GetConsole()->GetMainWindowWidget());
	wizard.setWindowTitle("Import 3D SEG-Y Files");
	wizard.setWizardStyle(QWizard::ModernStyle);

	QWizardPage *pPage = new CXPageLoadSegyStep1(&wizard, sListFiles);
	wizard.addPage(pPage);
	pPage =  new CXPageLoadSegyStep2(&wizard);
	wizard.addPage(pPage);
	pPage =  new CXPageLoadSegyStep3(&wizard);
	wizard.addPage(pPage);
	pPage =  new CXPageLoadSegyStep4(&wizard);
	wizard.addPage(pPage);	
	wizard.setMinimumSize(800,680);
	//wizard.setWindowModality(Qt::NonModal);
	wizard.show();

	//	Populate the candidates of each column for well header file*/
	if(wizard.exec() == QDialog::Accepted)
	{
		CXPageLoadSegyStep1 *pPage = (CXPageLoadSegyStep1 *) wizard.page(0);
		CXSEGYLoadParameters *pLoadParameters =  pPage->GetDataParameters();

		CXSEGYImporter::ImportSEGY(pLoadParameters);
	}

	return true;
}

bool CXDataImporter::importReservoirFile(QStringList  sListFiles)
{
	CXDlgImportReservoir dlgImporter(sListFiles[0]);

	dlgImporter.exec();

	return true;
}

bool CXDataImporter::importFABFile(QStringList sListFiles)
{
	CXWaitCursor waitCursor;
	foreach(QString sFile, sListFiles)
	{
		CXFracturePatchFile file(sFile);
		if (!file.Import())
			return false;
	}

	return true;
}