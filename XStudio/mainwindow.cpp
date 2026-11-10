#include "mainwindow.h"

#include <QApplication>
#include <QMdiSubWindow>
#include <QAction>
#include <QDesktopWidget>
#include <QInputDialog>
#include <QDesktopServices>
#include <QMessageBox>

#include "xglobal.h"
#include "xconsole.h"
#include "xshowtemplates.h"
#include "xdataimporter.h"
#include "xproject.h"
#include "xtree.h"
#include "xwindow.h"
#include "xwindowtree.h"
#include "xcreateseisworkarea.h"
#include "xwindowmanager.h"
#include "xdlgprojectproperties.h"
#include "xprocessengine.h"

#include "gsdlghorizonmanagement.h"
#include "gsdlgstresscalculation.h"
#include "gsdlgrsa.h"

#include "xdlgimportwavelet.h"
#include "xdlgtheowavelet.h"
#include "xdlgabout.h"

#include "xdlgupdatesgy.h"

#include "xseismicutmtool.h"
#include <qfile.h>
#include <qtextstream.h>

CMainWindow::CMainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(::g_strProductName);
	setWindowIcon(QIcon(::GetIconPath() + "X.png"));

	ui.setupUi(this);

	_Init();
	// File
	connect(ui.actionNew_Project, &QAction::triggered, this, &CMainWindow::slotNewProject);
	connect(ui.actionOpen_Project, &QAction::triggered, this, &CMainWindow::slotOpenProject);
	connect(ui.actionSave_Project, &QAction::triggered, this, &CMainWindow::slotSaveProject);
	connect(ui.actionProject_Properties, &QAction::triggered, this, &CMainWindow::slotProjectProperties);
    connect(ui.actionExit, &QAction::triggered, this, &CMainWindow::close);
	// I/O
	connect(ui.actionImportWellHeader, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportWellPath, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportWellLas, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportWellWis, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportWellXtf, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportWellDlis, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportWellASCIILog, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportWellCheckShot, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportWellTops, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportPoints, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportFaultPolygon, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportFaultStick, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImport3DSurface, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportSegy, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionImportReservoir, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);
	connect(ui.actionCreateSeismicArea, &QAction::triggered, this, &CMainWindow::slotCreateSeismicWorkArea);
	connect(ui.actionImportWavelet, &QAction::triggered, this, &CMainWindow::slotImportWavelet);
	connect(ui.actionImportFracturePatch, &QAction::triggered, this, &CMainWindow::slotImportFromFiles);

	// View
	connect(ui.actionLog_View, &QAction::triggered, this, &CMainWindow::slotCreateView);
	connect(ui.actionCrossplot_view, &QAction::triggered, this, &CMainWindow::slotCreateView);
	connect(ui.actionHistogram_Window, &QAction::triggered, this, &CMainWindow::slotCreateView);
	connect(ui.action3DWindow, &QAction::triggered, this, &CMainWindow::slotCreateView);
	connect(ui.actionBasemap_Window,&QAction::triggered,this,&CMainWindow::slotCreateView);
	connect(ui.actionSection_Window, &QAction::triggered, this, &CMainWindow::slotCreateView);
	
	// Tools
	connect(ui.actionTheoreticalWavelet, &QAction::triggered, this, &CMainWindow::slotTool);
	connect(ui.actionTemplates, &QAction::triggered, this, &CMainWindow::slotTool);
	connect(ui.actionUpdateSEGY, &QAction::triggered, this, &CMainWindow::slotTool);

	// GSM
	connect(ui.actionHorizon_Management, &QAction::triggered, this, &CMainWindow::slotGSM);
	connect(ui.actionStress_Calculation, &QAction::triggered, this, &CMainWindow::slotGSM);
	connect(ui.actionRegional_Stress_Analysis, &QAction::triggered, this, &CMainWindow::slotGSM);
	connect(ui.actionPDG_Window, &QAction::triggered, this, &CMainWindow::slotGSMWindow);
	connect(ui.actionGSBasemap_Window, &QAction::triggered, this, &CMainWindow::slotGSMWindow);
	connect(ui.actionGSSection_Window, &QAction::triggered, this, &CMainWindow::slotGSMWindow);
	connect(ui.actionAdd_to_tool_bar, &QAction::triggered, this, &CMainWindow::slotGSM);

	// Help
	connect(ui.actionHelp, &QAction::triggered, this, &CMainWindow::slotHelp);
	connect(ui.actionFAQ, &QAction::triggered, this, &CMainWindow::slotFAQ);

	connect(ui.actionSwitchWindowStyle, &QAction::triggered, this, &CMainWindow::slotSwitchWindowStyle);
	connect(dynamic_cast<QMdiArea*>(centralWidget()), &QMdiArea::subWindowActivated, this, &CMainWindow::slotActiveView);
	
	EnableActions(false);
}

CMainWindow::~CMainWindow()
{
	CXConsole* pConsole = ::GetConsole();
	delete pConsole;
}

void CMainWindow::_Init()
{
	//	Get recent projects from setting.
	QSettings settings("XStudio", "WindowStyle");
	QString sWStyle = settings.value("style").toString();

	QMdiArea *mdiArea = new QMdiArea;
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(mdiArea);

	if (sWStyle == "MDI" || sWStyle.isEmpty())
	{
		settings.setValue("style", "MDI");
	}
	else
	{
		delete mdiArea;
		ui.actionSwitchWindowStyle->setChecked(true);
	}

	CXTree::Instance().SetMainWindowTree(ui.treeWidgetData);
	CXWindowTree::Instance().SetWindowTree(ui.treeWidgetWindow);

	ui.actionLog_View->setData(eLogViewWindow);
	ui.actionCrossplot_view->setData(eCrossplotWindow);
	ui.actionHistogram_Window->setData(eHistogramWindow);
	ui.action3DWindow->setData(e3DWindow);
	ui.actionSection_Window->setData(eSectionWindow);
	ui.actionBasemap_Window->setData(e3DBaseMap);
	
	ui.actionPDG_Window->setData(eGSPDGWindow);
	ui.actionGSBasemap_Window->setData(eGSBaseMap);
	ui.actionGSSection_Window->setData(eGSSectionWindow);

	ui.menuView->addAction(ui.dockDataTree->toggleViewAction());
	ui.menuView->addAction(ui.dockWindowTree->toggleViewAction());

	int i;
	for(i = 0; i < MAX_RECENTPROJECTS; i++)
	{
		m_pRecentProjects[i] = new QAction(this);
		m_pRecentProjects[i]->setVisible(false);
		connect(m_pRecentProjects[i], &QAction::triggered, this, &CMainWindow::slotOpenProject);
	
		ui.menuFile->insertAction(ui.actionExit, m_pRecentProjects[i]);
	}

	m_pSeperator = ui.menuFile->insertSeparator(ui.actionExit);
	m_pSeperator->setVisible(false);

	updateRecentProjectsMenu();

	//qDebug() << "The screen size is " << QApplication::desktop()->geometry();
}

void CMainWindow::updateRecentProjectsMenu()
{
	//	Get recent projects from setting.
	QSettings settings("XStudio", "RecentProjects");
	QStringList sListProjects = settings.value("Recent").toStringList();

	int i, iNumRecents = qMin(sListProjects.size(), static_cast<int>(MAX_RECENTPROJECTS));
	m_pSeperator->setVisible(iNumRecents > 0);

	for(i = 0; i < iNumRecents; i++)
	{
		QString sText = QString("&%1 %2").arg(i + 1).arg(sListProjects[i]);
		m_pRecentProjects[i]->setText(sText);
		m_pRecentProjects[i]->setData(sListProjects[i]);
		m_pRecentProjects[i]->setVisible(true);
	}

	for(; i < MAX_RECENTPROJECTS; i++)
		m_pRecentProjects[i]->setVisible(false);
}

void CMainWindow::EnableActions(bool bEnable)
{
	ui.actionSave_Project->setEnabled(bEnable);
	ui.actionProject_Properties->setEnabled(bEnable);

	ui.actionImportWellHeader->setEnabled(bEnable);
	ui.actionImportWellPath->setEnabled(bEnable);
	ui.actionImportWellLas->setEnabled(bEnable);
	ui.actionImportWellWis->setEnabled(bEnable);
	ui.actionImportWellXtf->setEnabled(bEnable);
	ui.actionImportWellASCIILog->setEnabled(bEnable);
	ui.actionImportWellCheckShot->setEnabled(bEnable);
	ui.actionImportWellTops->setEnabled(bEnable);
	ui.actionImportPoints->setEnabled(bEnable);
	ui.actionImportFaultPolygon->setEnabled(bEnable);
	ui.actionImportFaultStick->setEnabled(bEnable);
	ui.actionImport3DSurface->setEnabled(bEnable);
	ui.actionImportSegy->setEnabled(bEnable);
	ui.actionImportReservoir->setEnabled(bEnable);
	ui.actionImportWavelet->setEnabled(bEnable);
	ui.actionImportFracturePatch->setEnabled(bEnable);
	ui.actionCreateSeismicArea->setEnabled(bEnable);

	ui.actionLog_View->setEnabled(bEnable);
	ui.actionCrossplot_view->setEnabled(bEnable);
	ui.actionHistogram_Window->setEnabled(bEnable);
	ui.action3DWindow->setEnabled(bEnable);
	ui.actionBasemap_Window->setEnabled(bEnable);
	ui.actionSection_Window->setEnabled(bEnable);
	
	ui.actionTheoreticalWavelet->setEnabled(bEnable);
	ui.actionTemplates->setEnabled(bEnable);

	ui.actionHorizon_Management->setEnabled(bEnable);
	ui.actionStress_Calculation->setEnabled(bEnable);
	ui.actionRegional_Stress_Analysis->setEnabled(bEnable);
	ui.actionGSBasemap_Window->setEnabled(bEnable);
	ui.actionGSSection_Window->setEnabled(bEnable);
	ui.actionPDG_Window->setEnabled(bEnable);
}

void CMainWindow::slotSwitchWindowStyle()
{
	CXConsole *pConsole = ::GetConsole();
	pConsole->GetWindowManager()->CloseAllWindows();

	QMdiArea *pMDI = dynamic_cast<QMdiArea *>(centralWidget());
	if (pMDI)
	{
		delete pMDI;

		int mainHeight = QApplication::desktop()->height() * 0.93;
		move(0, 0);
		resize(400, mainHeight);

		QSettings settings("XStudio", "WindowStyle");
		settings.setValue("style", "TopLevel");
	}
	else
	{
		pMDI = new QMdiArea(this);
		pMDI->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		pMDI->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		setCentralWidget(pMDI);
		connect(pMDI, &QMdiArea::subWindowActivated, this, &CMainWindow::slotActiveView);

		int mainWidth = QApplication::desktop()->width();
		if (mainWidth > 2400)
			mainWidth /= 2;
		mainWidth *= 0.93;
		int mainHeight = QApplication::desktop()->height() * 0.93;
		move(0, 0);
		resize(mainWidth, mainHeight);

		QSettings settings("XStudio", "WindowStyle");
		settings.setValue("style", "MDI");
	}
}

bool CMainWindow::IsMDI()
{
	QMdiArea *pMDI = dynamic_cast<QMdiArea *>(centralWidget());
	if (pMDI)
		return true;
	else
		return false;
}

void CMainWindow::slotImportFromFiles()
{
	CXDataImporter importer;
	if(	ui.actionImportWellHeader == sender())
	{
		importer.ImportData(eWellHeaderASCII);
	}
	else if(ui.actionImportFaultPolygon == sender())
	{
		importer.ImportData(eFaultPolygonASCII);
	}
	else if(ui.actionImportFaultStick == sender())
	{
		importer.ImportData(eFaultSticksASCII);
	}
	else if(ui.actionImportPoints == sender())
	{
		importer.ImportData(e3DPointsASCII);
	}
	else if (ui.actionImportWellLas == sender())
	{
		importer.ImportData(eWellLAS);
	}
	else if (ui.actionImportWellWis == sender())
	{
		importer.ImportData(eWellWIS);
	}
	else if (ui.actionImportWellXtf == sender())
	{
		importer.ImportData(eWellXTF);
	}
	else if (ui.actionImportWellDlis == sender())
	{
		importer.ImportData(eWellDLIS);
	}
	else if (ui.actionImportWellASCIILog == sender())
	{
		importer.ImportData(eWellASCIILog);
	}
	else if (ui.actionImportWellPath == sender())
	{
		importer.ImportData(eWellPathASCII);
	}
	else if (ui.actionImportWellCheckShot == sender())
	{
		importer.ImportData(eWellCheckShot);
	}
	else if (ui.actionImportWellTops == sender())
	{
		importer.ImportData(eWellTopsASCII);
	}
	else if (ui.actionImport3DSurface == sender())
	{
		importer.ImportData(eZMapASCII);
	}
	else if (ui.actionImportSegy == sender())
	{
		importer.ImportData(e3DSEGY);
	}
	else if (ui.actionImportReservoir == sender())
	{
		importer.ImportData(eReservoir);
	}
	else if (ui.actionImportFracturePatch == sender())
	{
		importer.ImportData(eFracturePatches);
	}
}

void CMainWindow::slotImportWavelet()
{
	CXDlgImportWavelet* pDlg = new CXDlgImportWavelet(nullptr);
	pDlg->show();
}

void CMainWindow::slotCreateView()
{
	QAction *pAction = qobject_cast<QAction *>(sender());
	int iType = qvariant_cast<int>(pAction->data());
	EXWindowType eWindowType = static_cast<EXWindowType>(iType);

	CXConsole *pConsole = ::GetConsole();
	CXWindow *pWindow = pConsole->CreateNewWindow(eWindowType);

	if (!pWindow)
		return;

	QMdiArea *pMDI = dynamic_cast<QMdiArea *>(centralWidget());
	if (pMDI)
	{
		QMdiSubWindow *pSubWindow = pMDI->addSubWindow(pWindow);
		pSubWindow->show();
		pMDI->viewport()->update();
	}
	else
		pWindow->show();

	pWindow->InitOpenGL();
}

void CMainWindow::slotTool()
{
	if (sender() == ui.actionTemplates)
	{
		CXShowTemplates *pST = new CXShowTemplates(this);
		pST->show();
	}
	else if (sender() == ui.actionTheoreticalWavelet)
	{
		XDlgTheoWavelet *pTW = new XDlgTheoWavelet(this);
		pTW->show();
	}
	else if (sender() == ui.actionUpdateSEGY)
	{
		XDlgUpdateSGY *pUS = new XDlgUpdateSGY(this);
		pUS->show();
	}
}

void CMainWindow::slotGSM()
{
	if (sender() == ui.actionHorizon_Management)
	{
		GSDlgHorizonManagement dlg;
		dlg.exec();
	}
	else if (sender() == ui.actionStress_Calculation)
	{
		GSDlgStressCalculation dlg;
		dlg.exec();
	}
	else if (sender() == ui.actionRegional_Stress_Analysis)
	{
		GSDlgRSA dlg;
		dlg.exec();
	}
	else if (sender() == ui.actionAdd_to_tool_bar)
	{
		if (ui.actionAdd_to_tool_bar->isChecked())
		{
			ui.mainToolBar->addAction(ui.actionHorizon_Management);
			ui.mainToolBar->addAction(ui.actionStress_Calculation);
			ui.mainToolBar->addAction(ui.actionRegional_Stress_Analysis);
			ui.mainToolBar->addAction(ui.actionGSBasemap_Window);
			ui.mainToolBar->addAction(ui.actionGSSection_Window);
			ui.mainToolBar->addAction(ui.actionPDG_Window);
		}
		else
		{
			ui.mainToolBar->removeAction(ui.actionHorizon_Management);
			ui.mainToolBar->removeAction(ui.actionStress_Calculation);
			ui.mainToolBar->removeAction(ui.actionRegional_Stress_Analysis);
			ui.mainToolBar->removeAction(ui.actionGSBasemap_Window);
			ui.mainToolBar->removeAction(ui.actionGSSection_Window);
			ui.mainToolBar->removeAction(ui.actionPDG_Window);
		}
	}
}

void CMainWindow::slotGSMWindow()
{
	QAction *pAction = qobject_cast<QAction *>(sender());
	int iType = qvariant_cast<int>(pAction->data());
	EXWindowType eWindowType = static_cast<EXWindowType>(iType);

	CXConsole *pConsole = ::GetConsole();
	CXWindow *pWindow = pConsole->CreateNewWindow(eWindowType);

	if (!pWindow)
		return;

	QMdiArea *pMDI = dynamic_cast<QMdiArea *>(centralWidget());
	if (pMDI)
	{
		QMdiSubWindow *pSubWindow = pMDI->addSubWindow(pWindow);
		pSubWindow->show();
		pMDI->viewport()->update();
	}
	else
		pWindow->show();

	//pWindow->InitOpenGL();	
}

void CMainWindow::slotHelp()
{
	//QDesktopServices::openUrl(QUrl("https://github.com/preend/XStudio", QUrl::TolerantMode));
	QDesktopServices::openUrl(QUrl("GeoVizPRO-UserGuide.pdf"));
}

void CMainWindow::slotFAQ()
{
	XDlgAbout dlg(this);
	dlg.exec();
#if 0
	CXSeismicUTMTool utm;
	utm.InitSize(1985, 1246, 1, 640, 1476, 1);
	utm.InitCoordinates(1985, 640, 625112., 5105203,
		1985, 2115, 639065., 5100399.,
		3230, 2115, 643117., 5112171.);

	QFile qInFile("d:/testdata/well.csv");
	qInFile.open(QIODevice::ReadOnly);
	QTextStream inStream(&qInFile);
	QFile qOutFile("d:/tmp/well.csv");
	qOutFile.open(QIODevice::WriteOnly);
	QTextStream outStream(&qOutFile);
	double x, y;
	//while (!inStream.atEnd())
	//{
	//	QString sLine = inStream.readLine();
	//	QStringList sListValue = sLine.simplified().split(" ");

	//	int iLine = (int)(sListValue[2].toDouble());
	//	int iCdp = (int)(sListValue[3].toDouble());
	//	utm.LineToXY(iLine, iCdp, x, y);
	//	QString sX = QString::number(x, 'f', 2);
	//	QString sY = QString::number(y, 'f', 2);

	//	sLine.replace(10, sX.length(), sX);
	//	sLine.replace(25, sY.length(), sY);

	//	outStream << sLine << endl;
	//}
	QString sLine = inStream.readLine();
	while (!inStream.atEnd())
	{
		QString sLine = inStream.readLine();
		QStringList sListValue = sLine.simplified().split(",");
		if (sListValue.size() != 4)
			continue;

		x = sListValue[1].toDouble();
		y = sListValue[2].toDouble();
		int line, cdp;
		utm.XYToLine(x, y, line, cdp);

		outStream << sLine << "," << QString::number(line) << "," << QString::number(cdp) << endl;
	}

	qInFile.close();
	qOutFile.close();
#endif
}

void CMainWindow::slotActiveView(QMdiSubWindow *pSubWindow)
{
	CXWindow *pWindow = NULL;
	if (pSubWindow)
	{
		pWindow = dynamic_cast<CXWindow *>(pSubWindow->widget());
	}

	CXConsole *pConsole = ::GetConsole();
	pConsole->SetActiveWindow(pWindow);
}

void CMainWindow::slotNewProject()
{
	CXConsole *pConsole = ::GetConsole();

	CXProject *pProject = pConsole->NewProject();

	if(pProject)
	{
		setWindowTitle(::g_strProductName + ": " + pProject->GetObjectName());
		EnableActions();
	}
}

void CMainWindow::slotSaveProject()
{
	::GetConsole()->SaveProject();

	::SetProjectDirty(false);
		
	addRecentProject(::GetProject()->GetProjectPath() + ::GetProject()->GetObjectName() + ".rdb");
}

void CMainWindow::slotProjectProperties()
{
	CXDlgProjectProperties* pProjectPropertiesDlg = new CXDlgProjectProperties(this);
	pProjectPropertiesDlg->exec();
}

void CMainWindow::slotOpenProject()
{
	CXConsole *pConsole = ::GetConsole();

	//	Close current project first, if there's one already opened.
	if(!pConsole->CloseCurrentProject())
		return;

	QString strProject = "";
	QAction *pAction = qobject_cast<QAction *>(sender());
	if(pAction)
	{
		strProject = pAction->data().toString();
	}

	CXProject *pProject = pConsole->OpenProject(strProject);
	if(pProject)
	{
		setWindowTitle(::g_strProductName + ": " + pProject->GetObjectName());
		EnableActions();
		::SetProjectDirty(false);

		addRecentProject(strProject);
	}
	else
	{
		refreshRecentProject();
	}
}

void CMainWindow::addRecentProject(QString strProject)
{
	strProject = QDir::toNativeSeparators(strProject);

	//	Get recent projects from setting.
	QSettings settings("XStudio", "RecentProjects");
	QStringList sListProjects = settings.value("Recent").toStringList();

	//	Remove the project if exist.
	sListProjects.removeAll(strProject);

	//	Add it to the beginning and save to the setting.
	sListProjects.prepend(strProject);
	settings.setValue("Recent", sListProjects);

	refreshRecentProject();

	//	Update the GUI.
	updateRecentProjectsMenu();
}

void CMainWindow::refreshRecentProject()
{
	//	Get recent projects from setting.
	QSettings settings("XStudio", "RecentProjects");
	QStringList sListProjects = settings.value("Recent").toStringList();
	QStringList sListExistPrjs;

	foreach(QString sPrj, sListProjects)
	{
		if (QFile::exists(sPrj))
			sListExistPrjs << sPrj;
	}

	settings.setValue("Recent", sListExistPrjs);
	updateRecentProjectsMenu();
}

// inversion
void CMainWindow::slotAVOInversion()
{
	CXProcessEngine process(nullptr, EAVOInversion);
	process.Calculate(false);
}
void CMainWindow::slotCSSI()
{
	CXProcessEngine process(nullptr, ECSSInversion);
	process.Calculate(false);
}
void CMainWindow::slotAVOCSSI()
{
	CXProcessEngine process(nullptr, EAVOSSInversion);
	process.Calculate(false);
}

void CMainWindow::slotCreateSeismicWorkArea()
{
	CXCreateSeisWorkArea *pDlg = new CXCreateSeisWorkArea(this);
	pDlg->show();
}