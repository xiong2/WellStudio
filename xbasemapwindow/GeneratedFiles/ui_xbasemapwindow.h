/********************************************************************************
** Form generated from reading UI file 'xbasemapwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XBASEMAPWINDOW_H
#define UI_XBASEMAPWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rlbasemapmainwindow
{
public:
    QAction *m_actionViewAll;
    QAction *m_actionSelectMode;
    QAction *m_actionHome;
    QAction *m_actionSetHome;
    QAction *m_actionSynchronize;
    QAction *m_actionProperties;
    QAction *m_actionCoordinate;
    QAction *m_actionColorbar;
    QAction *m_actionScale;
    QAction *m_pActionPolygonNew;
    QAction *m_pActionRandomSectionNew;
    QAction *m_actionScreenshot;
    QAction *m_actionCompass;
    QAction *m_pActionRandomSection_Mode;
    QAction *m_pActionPolygon_Mode;
    QAction *m_pActionRandomSectionDelete;
    QAction *m_pActionPolygonDelete;
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QToolBar *toolBarTop;
    QToolBar *toolBarTrackingTools;
    QToolBar *toolBarVolume;
    QToolBar *m_pToolBarRandomSection;
    QToolBar *m_pToolBarPolygon;

    void setupUi(QMainWindow *rlbasemapmainwindow)
    {
        if (rlbasemapmainwindow->objectName().isEmpty())
            rlbasemapmainwindow->setObjectName(QString::fromUtf8("rlbasemapmainwindow"));
        rlbasemapmainwindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/BasemapWindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        rlbasemapmainwindow->setWindowIcon(icon);
        m_actionViewAll = new QAction(rlbasemapmainwindow);
        m_actionViewAll->setObjectName(QString::fromUtf8("m_actionViewAll"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/ViewAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionViewAll->setIcon(icon1);
        m_actionSelectMode = new QAction(rlbasemapmainwindow);
        m_actionSelectMode->setObjectName(QString::fromUtf8("m_actionSelectMode"));
        m_actionSelectMode->setCheckable(true);
        m_actionSelectMode->setChecked(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/Selection.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionSelectMode->setIcon(icon2);
        m_actionHome = new QAction(rlbasemapmainwindow);
        m_actionHome->setObjectName(QString::fromUtf8("m_actionHome"));
        m_actionHome->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/Home.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionHome->setIcon(icon3);
        m_actionSetHome = new QAction(rlbasemapmainwindow);
        m_actionSetHome->setObjectName(QString::fromUtf8("m_actionSetHome"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/SetHome.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionSetHome->setIcon(icon4);
        m_actionSynchronize = new QAction(rlbasemapmainwindow);
        m_actionSynchronize->setObjectName(QString::fromUtf8("m_actionSynchronize"));
        m_actionSynchronize->setCheckable(true);
        m_actionSynchronize->setChecked(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/Synchronize.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionSynchronize->setIcon(icon5);
        m_actionProperties = new QAction(rlbasemapmainwindow);
        m_actionProperties->setObjectName(QString::fromUtf8("m_actionProperties"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/Properties.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionProperties->setIcon(icon6);
        m_actionCoordinate = new QAction(rlbasemapmainwindow);
        m_actionCoordinate->setObjectName(QString::fromUtf8("m_actionCoordinate"));
        m_actionCoordinate->setCheckable(true);
        m_actionCoordinate->setChecked(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icon/Coordinates.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionCoordinate->setIcon(icon7);
        m_actionColorbar = new QAction(rlbasemapmainwindow);
        m_actionColorbar->setObjectName(QString::fromUtf8("m_actionColorbar"));
        m_actionColorbar->setCheckable(true);
        m_actionColorbar->setChecked(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icon/Colorbar.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionColorbar->setIcon(icon8);
        m_actionScale = new QAction(rlbasemapmainwindow);
        m_actionScale->setObjectName(QString::fromUtf8("m_actionScale"));
        m_actionScale->setCheckable(true);
        m_actionScale->setChecked(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Icon/Scale.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionScale->setIcon(icon9);
        m_pActionPolygonNew = new QAction(rlbasemapmainwindow);
        m_pActionPolygonNew->setObjectName(QString::fromUtf8("m_pActionPolygonNew"));
        m_pActionPolygonNew->setCheckable(true);
        m_pActionPolygonNew->setEnabled(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Icon/DigitizePolygonNew.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pActionPolygonNew->setIcon(icon10);
        m_pActionPolygonNew->setVisible(true);
        m_pActionRandomSectionNew = new QAction(rlbasemapmainwindow);
        m_pActionRandomSectionNew->setObjectName(QString::fromUtf8("m_pActionRandomSectionNew"));
        m_pActionRandomSectionNew->setCheckable(true);
        m_pActionRandomSectionNew->setEnabled(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Icon/RandomSectionNew.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pActionRandomSectionNew->setIcon(icon11);
        m_pActionRandomSectionNew->setVisible(true);
        m_actionScreenshot = new QAction(rlbasemapmainwindow);
        m_actionScreenshot->setObjectName(QString::fromUtf8("m_actionScreenshot"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Icon/Screenshot.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionScreenshot->setIcon(icon12);
        m_actionCompass = new QAction(rlbasemapmainwindow);
        m_actionCompass->setObjectName(QString::fromUtf8("m_actionCompass"));
        m_actionCompass->setCheckable(true);
        m_actionCompass->setChecked(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Icon/Compass.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionCompass->setIcon(icon13);
        m_pActionRandomSection_Mode = new QAction(rlbasemapmainwindow);
        m_pActionRandomSection_Mode->setObjectName(QString::fromUtf8("m_pActionRandomSection_Mode"));
        m_pActionRandomSection_Mode->setCheckable(true);
        m_pActionRandomSection_Mode->setEnabled(false);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Icon/RandomSectionCreate.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pActionRandomSection_Mode->setIcon(icon14);
        m_pActionPolygon_Mode = new QAction(rlbasemapmainwindow);
        m_pActionPolygon_Mode->setObjectName(QString::fromUtf8("m_pActionPolygon_Mode"));
        m_pActionPolygon_Mode->setCheckable(true);
        m_pActionPolygon_Mode->setEnabled(false);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Icon/DigitizePolygon.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pActionPolygon_Mode->setIcon(icon15);
        m_pActionRandomSectionDelete = new QAction(rlbasemapmainwindow);
        m_pActionRandomSectionDelete->setObjectName(QString::fromUtf8("m_pActionRandomSectionDelete"));
        m_pActionRandomSectionDelete->setEnabled(false);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Icon/RandomSectionDel.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pActionRandomSectionDelete->setIcon(icon16);
        m_pActionPolygonDelete = new QAction(rlbasemapmainwindow);
        m_pActionPolygonDelete->setObjectName(QString::fromUtf8("m_pActionPolygonDelete"));
        m_pActionPolygonDelete->setEnabled(false);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/Icon/DigitizePolygonDel.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pActionPolygonDelete->setIcon(icon17);
        centralwidget = new QWidget(rlbasemapmainwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        rlbasemapmainwindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(rlbasemapmainwindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        rlbasemapmainwindow->setStatusBar(statusbar);
        toolBarTop = new QToolBar(rlbasemapmainwindow);
        toolBarTop->setObjectName(QString::fromUtf8("toolBarTop"));
        toolBarTop->setIconSize(QSize(16, 16));
        rlbasemapmainwindow->addToolBar(Qt::TopToolBarArea, toolBarTop);
        toolBarTrackingTools = new QToolBar(rlbasemapmainwindow);
        toolBarTrackingTools->setObjectName(QString::fromUtf8("toolBarTrackingTools"));
        toolBarTrackingTools->setEnabled(true);
        toolBarTrackingTools->setIconSize(QSize(16, 16));
        rlbasemapmainwindow->addToolBar(Qt::BottomToolBarArea, toolBarTrackingTools);
        toolBarVolume = new QToolBar(rlbasemapmainwindow);
        toolBarVolume->setObjectName(QString::fromUtf8("toolBarVolume"));
        toolBarVolume->setIconSize(QSize(16, 16));
        rlbasemapmainwindow->addToolBar(Qt::BottomToolBarArea, toolBarVolume);
        m_pToolBarRandomSection = new QToolBar(rlbasemapmainwindow);
        m_pToolBarRandomSection->setObjectName(QString::fromUtf8("m_pToolBarRandomSection"));
        m_pToolBarRandomSection->setEnabled(false);
        m_pToolBarRandomSection->setIconSize(QSize(16, 16));
        rlbasemapmainwindow->addToolBar(Qt::BottomToolBarArea, m_pToolBarRandomSection);
        m_pToolBarPolygon = new QToolBar(rlbasemapmainwindow);
        m_pToolBarPolygon->setObjectName(QString::fromUtf8("m_pToolBarPolygon"));
        m_pToolBarPolygon->setEnabled(false);
        m_pToolBarPolygon->setIconSize(QSize(16, 16));
        rlbasemapmainwindow->addToolBar(Qt::BottomToolBarArea, m_pToolBarPolygon);

        toolBarTop->addAction(m_actionProperties);
        toolBarTop->addAction(m_actionScreenshot);
        toolBarTop->addAction(m_actionSelectMode);
        toolBarTop->addSeparator();
        toolBarTop->addAction(m_actionViewAll);
        toolBarTop->addAction(m_actionHome);
        toolBarTop->addAction(m_actionSetHome);
        toolBarTop->addSeparator();
        toolBarTop->addAction(m_actionCoordinate);
        toolBarTop->addAction(m_actionColorbar);
        toolBarTop->addAction(m_actionCompass);
        toolBarTop->addAction(m_actionScale);
        toolBarTop->addSeparator();
        toolBarTop->addAction(m_actionSynchronize);
        toolBarTop->addSeparator();
        toolBarTrackingTools->addAction(m_pActionPolygon_Mode);
        toolBarTrackingTools->addAction(m_pActionRandomSection_Mode);
        m_pToolBarRandomSection->addAction(m_pActionRandomSectionNew);
        m_pToolBarRandomSection->addAction(m_pActionRandomSectionDelete);
        m_pToolBarPolygon->addAction(m_pActionPolygonNew);
        m_pToolBarPolygon->addAction(m_pActionPolygonDelete);

        retranslateUi(rlbasemapmainwindow);
        QObject::connect(m_pActionPolygon_Mode, SIGNAL(triggered(bool)), m_pToolBarPolygon, SLOT(setVisible(bool)));
        QObject::connect(m_pActionRandomSection_Mode, SIGNAL(triggered(bool)), m_pToolBarRandomSection, SLOT(setVisible(bool)));
        QObject::connect(m_pActionPolygon_Mode, SIGNAL(triggered(bool)), m_pToolBarPolygon, SLOT(setEnabled(bool)));
        QObject::connect(m_pActionRandomSection_Mode, SIGNAL(triggered(bool)), m_pToolBarRandomSection, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(rlbasemapmainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *rlbasemapmainwindow)
    {
        rlbasemapmainwindow->setWindowTitle(QCoreApplication::translate("rlbasemapmainwindow", "Base Map Window", nullptr));
        m_actionViewAll->setText(QCoreApplication::translate("rlbasemapmainwindow", "View all", nullptr));
#if QT_CONFIG(tooltip)
        m_actionViewAll->setToolTip(QCoreApplication::translate("rlbasemapmainwindow", "View all", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        m_actionViewAll->setShortcut(QCoreApplication::translate("rlbasemapmainwindow", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        m_actionSelectMode->setText(QCoreApplication::translate("rlbasemapmainwindow", "Select mode", nullptr));
        m_actionHome->setText(QCoreApplication::translate("rlbasemapmainwindow", "Back to home", nullptr));
        m_actionSetHome->setText(QCoreApplication::translate("rlbasemapmainwindow", "Set home", nullptr));
        m_actionSynchronize->setText(QCoreApplication::translate("rlbasemapmainwindow", "Synchronize", nullptr));
        m_actionProperties->setText(QCoreApplication::translate("rlbasemapmainwindow", "Properties", nullptr));
        m_actionCoordinate->setText(QCoreApplication::translate("rlbasemapmainwindow", "Show/Hide coordinate", nullptr));
        m_actionColorbar->setText(QCoreApplication::translate("rlbasemapmainwindow", "Show Color bar", nullptr));
        m_actionScale->setText(QCoreApplication::translate("rlbasemapmainwindow", "Show/Hide scale", nullptr));
        m_pActionPolygonNew->setText(QCoreApplication::translate("rlbasemapmainwindow", "Polygon new", nullptr));
        m_pActionRandomSectionNew->setText(QCoreApplication::translate("rlbasemapmainwindow", "RandomSection new", nullptr));
        m_actionScreenshot->setText(QCoreApplication::translate("rlbasemapmainwindow", "Screenshot", nullptr));
#if QT_CONFIG(tooltip)
        m_actionScreenshot->setToolTip(QCoreApplication::translate("rlbasemapmainwindow", "Save Screenshot", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        m_actionScreenshot->setShortcut(QCoreApplication::translate("rlbasemapmainwindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        m_actionCompass->setText(QCoreApplication::translate("rlbasemapmainwindow", "Show/Hide compass", nullptr));
        m_pActionRandomSection_Mode->setText(QCoreApplication::translate("rlbasemapmainwindow", "RandomSection Mode", nullptr));
        m_pActionPolygon_Mode->setText(QCoreApplication::translate("rlbasemapmainwindow", "Polygon Mode", nullptr));
        m_pActionRandomSectionDelete->setText(QCoreApplication::translate("rlbasemapmainwindow", "Delete Random Section", nullptr));
        m_pActionPolygonDelete->setText(QCoreApplication::translate("rlbasemapmainwindow", "Delete Polygon", nullptr));
        toolBarTop->setWindowTitle(QCoreApplication::translate("rlbasemapmainwindow", "Toolbar", nullptr));
        toolBarTrackingTools->setWindowTitle(QCoreApplication::translate("rlbasemapmainwindow", "Tracking tools", nullptr));
        toolBarVolume->setWindowTitle(QCoreApplication::translate("rlbasemapmainwindow", "Seismic Tools", nullptr));
        m_pToolBarRandomSection->setWindowTitle(QCoreApplication::translate("rlbasemapmainwindow", "Random Section Tools", nullptr));
        m_pToolBarPolygon->setWindowTitle(QCoreApplication::translate("rlbasemapmainwindow", "Polygon Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class rlbasemapmainwindow: public Ui_rlbasemapmainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XBASEMAPWINDOW_H
