/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include <xmaintreewidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionOpen_Project;
    QAction *actionExit;
    QAction *actionSave_Project;
    QAction *actionNew_Project;
    QAction *actionHistogram_Window;
    QAction *actionTemplates;
    QAction *actionLog_View;
    QAction *actionCrossplot_view;
    QAction *actionHelp;
    QAction *actionImportWellHeader;
    QAction *actionImportWellPath;
    QAction *actionImportWellLas;
    QAction *actionImportWellTops;
    QAction *actionImportFaultStick;
    QAction *actionImportFaultPolygon;
    QAction *actionImportPoints;
    QAction *action3DWindow;
    QAction *actionImport3DSurface;
    QAction *actionImportSegy;
    QAction *actionSection_Window;
    QAction *actionBasemap_Window;
    QAction *actionCreateSeismicArea;
    QAction *actionImportReservoir;
    QAction *actionImportWellASCIILog;
    QAction *actionProject_Properties;
    QAction *actionSwitchWindowStyle;
    QAction *actionImportWellWis;
    QAction *actionImportWellXtf;
    QAction *actionFAQ;
    QAction *actionImportWellDlis;
    QAction *actionHorizon_Management;
    QAction *actionStress_Calculation;
    QAction *actionPDG_Window;
    QAction *actionGSBasemap_Window;
    QAction *actionGSSection_Window;
    QAction *actionRegional_Stress_Analysis;
    QAction *actionAdd_to_tool_bar;
    QAction *actionImportWellCheckShot;
    QAction *actionTMInversion;
    QAction *actionImportWavelet;
    QAction *actionTheoreticalWavelet;
    QAction *actionUpdateSEGY;
    QAction *actionImportFracturePatch;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuWindow;
    QMenu *menuImport;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuStress;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockDataTree;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    CXMainTreeWidget *treeWidgetData;
    QDockWidget *dockWindowTree;
    QWidget *dockWidgetContents_2;
    QGridLayout *gridLayout_3;
    QTreeWidget *treeWidgetWindow;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(1268, 882);
        actionOpen_Project = new QAction(MainWindowClass);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Folder(open)32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Project->setIcon(icon);
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionSave_Project = new QAction(MainWindowClass);
        actionSave_Project->setObjectName(QString::fromUtf8("actionSave_Project"));
        actionSave_Project->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/Save32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Project->setIcon(icon2);
        actionNew_Project = new QAction(MainWindowClass);
        actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/New32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Project->setIcon(icon3);
        actionHistogram_Window = new QAction(MainWindowClass);
        actionHistogram_Window->setObjectName(QString::fromUtf8("actionHistogram_Window"));
        actionHistogram_Window->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/Histogram32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHistogram_Window->setIcon(icon4);
        actionTemplates = new QAction(MainWindowClass);
        actionTemplates->setObjectName(QString::fromUtf8("actionTemplates"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/Setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTemplates->setIcon(icon5);
        actionLog_View = new QAction(MainWindowClass);
        actionLog_View->setObjectName(QString::fromUtf8("actionLog_View"));
        actionLog_View->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/Logview32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLog_View->setIcon(icon6);
        actionCrossplot_view = new QAction(MainWindowClass);
        actionCrossplot_view->setObjectName(QString::fromUtf8("actionCrossplot_view"));
        actionCrossplot_view->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icon/Crossplot32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCrossplot_view->setIcon(icon7);
        actionHelp = new QAction(MainWindowClass);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icon/Question4.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon8);
        actionImportWellHeader = new QAction(MainWindowClass);
        actionImportWellHeader->setObjectName(QString::fromUtf8("actionImportWellHeader"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Icon/WellFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportWellHeader->setIcon(icon9);
        actionImportWellPath = new QAction(MainWindowClass);
        actionImportWellPath->setObjectName(QString::fromUtf8("actionImportWellPath"));
        actionImportWellPath->setIcon(icon9);
        actionImportWellLas = new QAction(MainWindowClass);
        actionImportWellLas->setObjectName(QString::fromUtf8("actionImportWellLas"));
        actionImportWellLas->setIcon(icon9);
        actionImportWellTops = new QAction(MainWindowClass);
        actionImportWellTops->setObjectName(QString::fromUtf8("actionImportWellTops"));
        actionImportWellTops->setIcon(icon9);
        actionImportFaultStick = new QAction(MainWindowClass);
        actionImportFaultStick->setObjectName(QString::fromUtf8("actionImportFaultStick"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Icon/Fault.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportFaultStick->setIcon(icon10);
        actionImportFaultPolygon = new QAction(MainWindowClass);
        actionImportFaultPolygon->setObjectName(QString::fromUtf8("actionImportFaultPolygon"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Icon/FaultPolygon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportFaultPolygon->setIcon(icon11);
        actionImportPoints = new QAction(MainWindowClass);
        actionImportPoints->setObjectName(QString::fromUtf8("actionImportPoints"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Icon/Points.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportPoints->setIcon(icon12);
        action3DWindow = new QAction(MainWindowClass);
        action3DWindow->setObjectName(QString::fromUtf8("action3DWindow"));
        action3DWindow->setEnabled(false);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Icon/3DWindow32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action3DWindow->setIcon(icon13);
        actionImport3DSurface = new QAction(MainWindowClass);
        actionImport3DSurface->setObjectName(QString::fromUtf8("actionImport3DSurface"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Icon/Surface.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport3DSurface->setIcon(icon14);
        actionImportSegy = new QAction(MainWindowClass);
        actionImportSegy->setObjectName(QString::fromUtf8("actionImportSegy"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Icon/Seismic.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportSegy->setIcon(icon15);
        actionSection_Window = new QAction(MainWindowClass);
        actionSection_Window->setObjectName(QString::fromUtf8("actionSection_Window"));
        actionSection_Window->setEnabled(false);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Icon/SectionWindow32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSection_Window->setIcon(icon16);
        actionBasemap_Window = new QAction(MainWindowClass);
        actionBasemap_Window->setObjectName(QString::fromUtf8("actionBasemap_Window"));
        actionBasemap_Window->setEnabled(false);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/Icon/BasemapWindow32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBasemap_Window->setIcon(icon17);
        actionCreateSeismicArea = new QAction(MainWindowClass);
        actionCreateSeismicArea->setObjectName(QString::fromUtf8("actionCreateSeismicArea"));
        actionCreateSeismicArea->setIcon(icon15);
        actionImportReservoir = new QAction(MainWindowClass);
        actionImportReservoir->setObjectName(QString::fromUtf8("actionImportReservoir"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/Icon/ReservoirModel.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportReservoir->setIcon(icon18);
        actionImportWellASCIILog = new QAction(MainWindowClass);
        actionImportWellASCIILog->setObjectName(QString::fromUtf8("actionImportWellASCIILog"));
        actionImportWellASCIILog->setIcon(icon9);
        actionProject_Properties = new QAction(MainWindowClass);
        actionProject_Properties->setObjectName(QString::fromUtf8("actionProject_Properties"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/Icon/ProjectProperties.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProject_Properties->setIcon(icon19);
        actionSwitchWindowStyle = new QAction(MainWindowClass);
        actionSwitchWindowStyle->setObjectName(QString::fromUtf8("actionSwitchWindowStyle"));
        actionSwitchWindowStyle->setCheckable(true);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/Icon/TopLevel32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSwitchWindowStyle->setIcon(icon20);
        actionImportWellWis = new QAction(MainWindowClass);
        actionImportWellWis->setObjectName(QString::fromUtf8("actionImportWellWis"));
        actionImportWellWis->setIcon(icon9);
        actionImportWellXtf = new QAction(MainWindowClass);
        actionImportWellXtf->setObjectName(QString::fromUtf8("actionImportWellXtf"));
        actionImportWellXtf->setIcon(icon9);
        actionFAQ = new QAction(MainWindowClass);
        actionFAQ->setObjectName(QString::fromUtf8("actionFAQ"));
        actionFAQ->setEnabled(true);
        actionFAQ->setIcon(icon8);
        actionImportWellDlis = new QAction(MainWindowClass);
        actionImportWellDlis->setObjectName(QString::fromUtf8("actionImportWellDlis"));
        actionImportWellDlis->setIcon(icon9);
        actionHorizon_Management = new QAction(MainWindowClass);
        actionHorizon_Management->setObjectName(QString::fromUtf8("actionHorizon_Management"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/Icon/Horizon2.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHorizon_Management->setIcon(icon21);
        actionStress_Calculation = new QAction(MainWindowClass);
        actionStress_Calculation->setObjectName(QString::fromUtf8("actionStress_Calculation"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/Icon/Stress.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStress_Calculation->setIcon(icon22);
        actionPDG_Window = new QAction(MainWindowClass);
        actionPDG_Window->setObjectName(QString::fromUtf8("actionPDG_Window"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/Icon/PDG.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPDG_Window->setIcon(icon23);
        actionPDG_Window->setVisible(true);
        actionGSBasemap_Window = new QAction(MainWindowClass);
        actionGSBasemap_Window->setObjectName(QString::fromUtf8("actionGSBasemap_Window"));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/Icon/GSBasemapWindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGSBasemap_Window->setIcon(icon24);
        actionGSSection_Window = new QAction(MainWindowClass);
        actionGSSection_Window->setObjectName(QString::fromUtf8("actionGSSection_Window"));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/Icon/GSSectionWindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGSSection_Window->setIcon(icon25);
        actionRegional_Stress_Analysis = new QAction(MainWindowClass);
        actionRegional_Stress_Analysis->setObjectName(QString::fromUtf8("actionRegional_Stress_Analysis"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/Icon/Global.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRegional_Stress_Analysis->setIcon(icon26);
        actionAdd_to_tool_bar = new QAction(MainWindowClass);
        actionAdd_to_tool_bar->setObjectName(QString::fromUtf8("actionAdd_to_tool_bar"));
        actionAdd_to_tool_bar->setCheckable(true);
        actionImportWellCheckShot = new QAction(MainWindowClass);
        actionImportWellCheckShot->setObjectName(QString::fromUtf8("actionImportWellCheckShot"));
        actionImportWellCheckShot->setIcon(icon9);
        actionTMInversion = new QAction(MainWindowClass);
        actionTMInversion->setObjectName(QString::fromUtf8("actionTMInversion"));
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/Icon/Calculator.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTMInversion->setIcon(icon27);
        actionImportWavelet = new QAction(MainWindowClass);
        actionImportWavelet->setObjectName(QString::fromUtf8("actionImportWavelet"));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/Icon/WaveletFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportWavelet->setIcon(icon28);
        actionTheoreticalWavelet = new QAction(MainWindowClass);
        actionTheoreticalWavelet->setObjectName(QString::fromUtf8("actionTheoreticalWavelet"));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/Icon/Wavelet.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTheoreticalWavelet->setIcon(icon29);
        actionUpdateSEGY = new QAction(MainWindowClass);
        actionUpdateSEGY->setObjectName(QString::fromUtf8("actionUpdateSEGY"));
        actionUpdateSEGY->setIcon(icon15);
        actionImportFracturePatch = new QAction(MainWindowClass);
        actionImportFracturePatch->setObjectName(QString::fromUtf8("actionImportFracturePatch"));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/Icon/FracturePatch.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImportFracturePatch->setIcon(icon30);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1268, 21));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuImport = new QMenu(menuBar);
        menuImport->setObjectName(QString::fromUtf8("menuImport"));
        menu = new QMenu(menuImport);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setIcon(icon9);
        menu_2 = new QMenu(menuImport);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_2->setIcon(icon10);
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuStress = new QMenu(menuBar);
        menuStress->setObjectName(QString::fromUtf8("menuStress"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setAutoFillBackground(false);
        mainToolBar->setIconSize(QSize(32, 32));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);
        dockDataTree = new QDockWidget(MainWindowClass);
        dockDataTree->setObjectName(QString::fromUtf8("dockDataTree"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeWidgetData = new CXMainTreeWidget(dockWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetData->setHeaderItem(__qtreewidgetitem);
        treeWidgetData->setObjectName(QString::fromUtf8("treeWidgetData"));

        gridLayout_2->addWidget(treeWidgetData, 0, 0, 1, 1);

        dockDataTree->setWidget(dockWidgetContents);
        MainWindowClass->addDockWidget(Qt::LeftDockWidgetArea, dockDataTree);
        dockWindowTree = new QDockWidget(MainWindowClass);
        dockWindowTree->setObjectName(QString::fromUtf8("dockWindowTree"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        gridLayout_3 = new QGridLayout(dockWidgetContents_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        treeWidgetWindow = new QTreeWidget(dockWidgetContents_2);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        treeWidgetWindow->setHeaderItem(__qtreewidgetitem1);
        treeWidgetWindow->setObjectName(QString::fromUtf8("treeWidgetWindow"));

        gridLayout_3->addWidget(treeWidgetWindow, 0, 0, 1, 1);

        dockWindowTree->setWidget(dockWidgetContents_2);
        MainWindowClass->addDockWidget(Qt::LeftDockWidgetArea, dockWindowTree);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuImport->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuStress->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave_Project);
        menuFile->addAction(actionProject_Properties);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuWindow->addAction(actionLog_View);
        menuWindow->addAction(actionCrossplot_view);
        menuWindow->addAction(actionHistogram_Window);
        menuWindow->addAction(action3DWindow);
        menuWindow->addAction(actionSection_Window);
        menuWindow->addAction(actionBasemap_Window);
        menuImport->addAction(actionImportSegy);
        menuImport->addAction(actionCreateSeismicArea);
        menuImport->addAction(actionImport3DSurface);
        menuImport->addAction(menu_2->menuAction());
        menuImport->addAction(menu->menuAction());
        menuImport->addAction(actionImportWavelet);
        menuImport->addAction(actionImportPoints);
        menuImport->addAction(actionImportReservoir);
        menuImport->addAction(actionImportFracturePatch);
        menu->addAction(actionImportWellHeader);
        menu->addAction(actionImportWellPath);
        menu->addAction(actionImportWellLas);
        menu->addAction(actionImportWellWis);
        menu->addAction(actionImportWellXtf);
        menu->addAction(actionImportWellDlis);
        menu->addAction(actionImportWellASCIILog);
        menu->addAction(actionImportWellCheckShot);
        menu->addAction(actionImportWellTops);
        menu_2->addAction(actionImportFaultStick);
        menu_2->addAction(actionImportFaultPolygon);
        menuTools->addAction(actionTheoreticalWavelet);
        menuTools->addAction(actionTemplates);
        menuTools->addAction(actionUpdateSEGY);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionFAQ);
        menuStress->addAction(actionHorizon_Management);
        menuStress->addAction(actionStress_Calculation);
        menuStress->addAction(actionRegional_Stress_Analysis);
        menuStress->addSeparator();
        menuStress->addAction(actionGSBasemap_Window);
        menuStress->addAction(actionGSSection_Window);
        menuStress->addAction(actionPDG_Window);
        menuStress->addSeparator();
        menuStress->addAction(actionAdd_to_tool_bar);
        mainToolBar->addAction(actionNew_Project);
        mainToolBar->addAction(actionOpen_Project);
        mainToolBar->addAction(actionSave_Project);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSection_Window);
        mainToolBar->addAction(actionBasemap_Window);
        mainToolBar->addAction(action3DWindow);
        mainToolBar->addAction(actionLog_View);
        mainToolBar->addAction(actionCrossplot_view);
        mainToolBar->addAction(actionHistogram_Window);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSwitchWindowStyle);
        mainToolBar->addSeparator();

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QCoreApplication::translate("MainWindowClass", "XStudio", nullptr));
        actionOpen_Project->setText(QCoreApplication::translate("MainWindowClass", "Open...", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen_Project->setToolTip(QCoreApplication::translate("MainWindowClass", "\346\211\223\345\274\200\345\267\262\346\234\211\351\241\271\347\233\256", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen_Project->setShortcut(QCoreApplication::translate("MainWindowClass", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindowClass", "Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindowClass", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_Project->setText(QCoreApplication::translate("MainWindowClass", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_Project->setToolTip(QCoreApplication::translate("MainWindowClass", "\344\277\235\345\255\230\345\275\223\345\211\215\351\241\271\347\233\256", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_Project->setShortcut(QCoreApplication::translate("MainWindowClass", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew_Project->setText(QCoreApplication::translate("MainWindowClass", "Create...", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_Project->setShortcut(QCoreApplication::translate("MainWindowClass", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionHistogram_Window->setText(QCoreApplication::translate("MainWindowClass", "Histogram view...", nullptr));
#if QT_CONFIG(tooltip)
        actionHistogram_Window->setToolTip(QCoreApplication::translate("MainWindowClass", "\345\210\233\345\273\272\347\233\264\346\226\271\345\233\276\347\252\227\345\217\243", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTemplates->setText(QCoreApplication::translate("MainWindowClass", "Templates...", nullptr));
#if QT_CONFIG(shortcut)
        actionTemplates->setShortcut(QCoreApplication::translate("MainWindowClass", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLog_View->setText(QCoreApplication::translate("MainWindowClass", "Log View...", nullptr));
#if QT_CONFIG(tooltip)
        actionLog_View->setToolTip(QCoreApplication::translate("MainWindowClass", "\345\210\233\345\273\272\346\233\262\347\272\277\345\233\236\346\224\276\347\252\227\345\217\243", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCrossplot_view->setText(QCoreApplication::translate("MainWindowClass", "Crossplot view...", nullptr));
#if QT_CONFIG(tooltip)
        actionCrossplot_view->setToolTip(QCoreApplication::translate("MainWindowClass", "\345\210\233\345\273\272\344\272\244\344\274\232\345\233\276\347\252\227\345\217\243", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelp->setText(QCoreApplication::translate("MainWindowClass", "Help...", nullptr));
        actionImportWellHeader->setText(QCoreApplication::translate("MainWindowClass", "Import Wellhead...", nullptr));
        actionImportWellPath->setText(QCoreApplication::translate("MainWindowClass", "Import Path...", nullptr));
        actionImportWellLas->setText(QCoreApplication::translate("MainWindowClass", "Import Las...", nullptr));
        actionImportWellTops->setText(QCoreApplication::translate("MainWindowClass", "Import Tops...", nullptr));
        actionImportFaultStick->setText(QCoreApplication::translate("MainWindowClass", "Import FaultStick...", nullptr));
        actionImportFaultPolygon->setText(QCoreApplication::translate("MainWindowClass", "Import Fault Polygon...", nullptr));
        actionImportPoints->setText(QCoreApplication::translate("MainWindowClass", "Import Points...", nullptr));
        action3DWindow->setText(QCoreApplication::translate("MainWindowClass", "3DWindow...", nullptr));
#if QT_CONFIG(tooltip)
        action3DWindow->setToolTip(QCoreApplication::translate("MainWindowClass", "\345\210\233\345\273\2723DWindow", nullptr));
#endif // QT_CONFIG(tooltip)
        actionImport3DSurface->setText(QCoreApplication::translate("MainWindowClass", "Import 3D Horizon...", nullptr));
        actionImport3DSurface->setIconText(QCoreApplication::translate("MainWindowClass", "Import 3-D Horizon", nullptr));
#if QT_CONFIG(tooltip)
        actionImport3DSurface->setToolTip(QCoreApplication::translate("MainWindowClass", "Import 3-D Horizon", nullptr));
#endif // QT_CONFIG(tooltip)
        actionImportSegy->setText(QCoreApplication::translate("MainWindowClass", "Import Seismic...", nullptr));
        actionSection_Window->setText(QCoreApplication::translate("MainWindowClass", "Section Window...", nullptr));
#if QT_CONFIG(tooltip)
        actionSection_Window->setToolTip(QCoreApplication::translate("MainWindowClass", "Create 2D Section Window", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBasemap_Window->setText(QCoreApplication::translate("MainWindowClass", "Basemap Window...", nullptr));
#if QT_CONFIG(tooltip)
        actionBasemap_Window->setToolTip(QCoreApplication::translate("MainWindowClass", "New Base Map Window", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCreateSeismicArea->setText(QCoreApplication::translate("MainWindowClass", "Create Survey...", nullptr));
        actionImportReservoir->setText(QCoreApplication::translate("MainWindowClass", "Import Geomodel...", nullptr));
        actionImportWellASCIILog->setText(QCoreApplication::translate("MainWindowClass", "Import ASCII...", nullptr));
        actionProject_Properties->setText(QCoreApplication::translate("MainWindowClass", "Option...", nullptr));
        actionSwitchWindowStyle->setText(QCoreApplication::translate("MainWindowClass", "SwitchWindowStyle", nullptr));
#if QT_CONFIG(tooltip)
        actionSwitchWindowStyle->setToolTip(QCoreApplication::translate("MainWindowClass", "Switch Window Style", nullptr));
#endif // QT_CONFIG(tooltip)
        actionImportWellWis->setText(QCoreApplication::translate("MainWindowClass", "Import WIS...", nullptr));
        actionImportWellXtf->setText(QCoreApplication::translate("MainWindowClass", "Import XTF...", nullptr));
        actionFAQ->setText(QCoreApplication::translate("MainWindowClass", "About...", nullptr));
#if QT_CONFIG(tooltip)
        actionFAQ->setToolTip(QCoreApplication::translate("MainWindowClass", "About", nullptr));
#endif // QT_CONFIG(tooltip)
        actionImportWellDlis->setText(QCoreApplication::translate("MainWindowClass", "Import DLIS...", nullptr));
        actionHorizon_Management->setText(QCoreApplication::translate("MainWindowClass", "Horizon Management...", nullptr));
        actionStress_Calculation->setText(QCoreApplication::translate("MainWindowClass", "Stress Calculation...", nullptr));
        actionPDG_Window->setText(QCoreApplication::translate("MainWindowClass", "PDG Window...", nullptr));
        actionGSBasemap_Window->setText(QCoreApplication::translate("MainWindowClass", "GSBasemap Window...", nullptr));
        actionGSSection_Window->setText(QCoreApplication::translate("MainWindowClass", "GSSection Window...", nullptr));
        actionRegional_Stress_Analysis->setText(QCoreApplication::translate("MainWindowClass", "Regional Stress Analysis...", nullptr));
        actionAdd_to_tool_bar->setText(QCoreApplication::translate("MainWindowClass", "Show on Tool Bar", nullptr));
#if QT_CONFIG(tooltip)
        actionAdd_to_tool_bar->setToolTip(QCoreApplication::translate("MainWindowClass", "Show on tool bar", nullptr));
#endif // QT_CONFIG(tooltip)
        actionImportWellCheckShot->setText(QCoreApplication::translate("MainWindowClass", "Import Check Shot...", nullptr));
#if QT_CONFIG(tooltip)
        actionImportWellCheckShot->setToolTip(QCoreApplication::translate("MainWindowClass", "Import check shot data", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTMInversion->setText(QCoreApplication::translate("MainWindowClass", "TMInversion", nullptr));
        actionImportWavelet->setText(QCoreApplication::translate("MainWindowClass", "Import Wavelet...", nullptr));
#if QT_CONFIG(tooltip)
        actionImportWavelet->setToolTip(QCoreApplication::translate("MainWindowClass", "Import wavelet from file", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTheoreticalWavelet->setText(QCoreApplication::translate("MainWindowClass", "Theoretical Wavlet...", nullptr));
#if QT_CONFIG(tooltip)
        actionTheoreticalWavelet->setToolTip(QCoreApplication::translate("MainWindowClass", "Create theoretical wavelet", nullptr));
#endif // QT_CONFIG(tooltip)
        actionUpdateSEGY->setText(QCoreApplication::translate("MainWindowClass", "UpdateSEGY", nullptr));
        actionImportFracturePatch->setText(QCoreApplication::translate("MainWindowClass", "Import Fracture Patches...", nullptr));
#if QT_CONFIG(tooltip)
        actionImportFracturePatch->setToolTip(QCoreApplication::translate("MainWindowClass", "Import Fracture Patches", nullptr));
#endif // QT_CONFIG(tooltip)
        menuFile->setTitle(QCoreApplication::translate("MainWindowClass", "File", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("MainWindowClass", "View", nullptr));
        menuImport->setTitle(QCoreApplication::translate("MainWindowClass", "I/O", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindowClass", "Import Wells", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindowClass", "Import Fault", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindowClass", "Tools", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindowClass", "Help", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindowClass", "Window", nullptr));
        menuStress->setTitle(QCoreApplication::translate("MainWindowClass", "Stress", nullptr));
        mainToolBar->setWindowTitle(QCoreApplication::translate("MainWindowClass", "\345\267\245\345\205\267\346\240\217", nullptr));
        dockDataTree->setWindowTitle(QCoreApplication::translate("MainWindowClass", "Data", nullptr));
        dockWindowTree->setWindowTitle(QCoreApplication::translate("MainWindowClass", "Windows", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
