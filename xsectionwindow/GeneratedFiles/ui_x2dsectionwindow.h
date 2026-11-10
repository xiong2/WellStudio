/********************************************************************************
** Form generated from reading UI file 'x2dsectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_X2DSECTIONWINDOW_H
#define UI_X2DSECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CX2DSectionWindow
{
public:
    QAction *m_actionProperties;
    QAction *m_actionZoomIn;
    QAction *m_actionZoomOut;
    QAction *m_actionViewAll;
    QAction *m_actionSynchronize;
    QAction *m_actionOrthoSections;
    QAction *m_actionFitToWindowWidth;
    QAction *m_actionFitToWindowHeight;
    QAction *m_actionIncreaseHorizonScale;
    QAction *m_actionDecreaseHorizonScale;
    QAction *m_actionIncreaseVerticalScale;
    QAction *m_actionDecreaseVerticalScale;
    QAction *m_actionIncreaseExcursion;
    QAction *m_actionDecreaseExcursion;
    QAction *m_actionVariableIntensity;
    QAction *m_actionWiggle;
    QAction *m_actionVariableAreaWiggle;
    QAction *m_actionFaultDigitizingTools;
    QAction *m_actionHorizonTrackingTools;
    QAction *m_action2ndLayerTools;
    QAction *actionRectZoom;
    QAction *actionRectZoomUndo;
    QAction *actionCancelZoomin;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *m_toolbarBasic;
    QToolBar *m_toolbarColormap;
    QToolBar *m_toolbarDisplayMode;
    QToolBar *m_toolbarDigitizingAndForeground;
    QToolBar *m_toolBarVolumes;

    void setupUi(QMainWindow *CX2DSectionWindow)
    {
        if (CX2DSectionWindow->objectName().isEmpty())
            CX2DSectionWindow->setObjectName(QString::fromUtf8("CX2DSectionWindow"));
        CX2DSectionWindow->resize(800, 600);
        CX2DSectionWindow->setIconSize(QSize(16, 16));
        m_actionProperties = new QAction(CX2DSectionWindow);
        m_actionProperties->setObjectName(QString::fromUtf8("m_actionProperties"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Properties.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionProperties->setIcon(icon);
        m_actionZoomIn = new QAction(CX2DSectionWindow);
        m_actionZoomIn->setObjectName(QString::fromUtf8("m_actionZoomIn"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/ZoomIn.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionZoomIn->setIcon(icon1);
        m_actionZoomOut = new QAction(CX2DSectionWindow);
        m_actionZoomOut->setObjectName(QString::fromUtf8("m_actionZoomOut"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/ZoomOut.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionZoomOut->setIcon(icon2);
        m_actionViewAll = new QAction(CX2DSectionWindow);
        m_actionViewAll->setObjectName(QString::fromUtf8("m_actionViewAll"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/ViewAll.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionViewAll->setIcon(icon3);
        m_actionSynchronize = new QAction(CX2DSectionWindow);
        m_actionSynchronize->setObjectName(QString::fromUtf8("m_actionSynchronize"));
        m_actionSynchronize->setCheckable(true);
        m_actionSynchronize->setChecked(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/Synchronize.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionSynchronize->setIcon(icon4);
        m_actionOrthoSections = new QAction(CX2DSectionWindow);
        m_actionOrthoSections->setObjectName(QString::fromUtf8("m_actionOrthoSections"));
        m_actionOrthoSections->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/OrthoSection.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_actionOrthoSections->setIcon(icon5);
        m_actionFitToWindowWidth = new QAction(CX2DSectionWindow);
        m_actionFitToWindowWidth->setObjectName(QString::fromUtf8("m_actionFitToWindowWidth"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/FitWidth.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionFitToWindowWidth->setIcon(icon6);
        m_actionFitToWindowHeight = new QAction(CX2DSectionWindow);
        m_actionFitToWindowHeight->setObjectName(QString::fromUtf8("m_actionFitToWindowHeight"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icon/FitHeight.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionFitToWindowHeight->setIcon(icon7);
        m_actionIncreaseHorizonScale = new QAction(CX2DSectionWindow);
        m_actionIncreaseHorizonScale->setObjectName(QString::fromUtf8("m_actionIncreaseHorizonScale"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icon/IncaseHorizon.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionIncreaseHorizonScale->setIcon(icon8);
        m_actionDecreaseHorizonScale = new QAction(CX2DSectionWindow);
        m_actionDecreaseHorizonScale->setObjectName(QString::fromUtf8("m_actionDecreaseHorizonScale"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Icon/DiscaseHorizon.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionDecreaseHorizonScale->setIcon(icon9);
        m_actionIncreaseVerticalScale = new QAction(CX2DSectionWindow);
        m_actionIncreaseVerticalScale->setObjectName(QString::fromUtf8("m_actionIncreaseVerticalScale"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Icon/IncaseVertical.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionIncreaseVerticalScale->setIcon(icon10);
        m_actionDecreaseVerticalScale = new QAction(CX2DSectionWindow);
        m_actionDecreaseVerticalScale->setObjectName(QString::fromUtf8("m_actionDecreaseVerticalScale"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Icon/DiscaseVertical.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionDecreaseVerticalScale->setIcon(icon11);
        m_actionIncreaseExcursion = new QAction(CX2DSectionWindow);
        m_actionIncreaseExcursion->setObjectName(QString::fromUtf8("m_actionIncreaseExcursion"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Icon/IncaseExcursion.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionIncreaseExcursion->setIcon(icon12);
        m_actionDecreaseExcursion = new QAction(CX2DSectionWindow);
        m_actionDecreaseExcursion->setObjectName(QString::fromUtf8("m_actionDecreaseExcursion"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Icon/DiscaseExcursion.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionDecreaseExcursion->setIcon(icon13);
        m_actionVariableIntensity = new QAction(CX2DSectionWindow);
        m_actionVariableIntensity->setObjectName(QString::fromUtf8("m_actionVariableIntensity"));
        m_actionVariableIntensity->setCheckable(true);
        m_actionVariableIntensity->setChecked(true);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Icon/VaribleIntensity.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionVariableIntensity->setIcon(icon14);
        m_actionWiggle = new QAction(CX2DSectionWindow);
        m_actionWiggle->setObjectName(QString::fromUtf8("m_actionWiggle"));
        m_actionWiggle->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Icon/Wiggle.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionWiggle->setIcon(icon15);
        m_actionVariableAreaWiggle = new QAction(CX2DSectionWindow);
        m_actionVariableAreaWiggle->setObjectName(QString::fromUtf8("m_actionVariableAreaWiggle"));
        m_actionVariableAreaWiggle->setCheckable(true);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Icon/WiggleArea.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionVariableAreaWiggle->setIcon(icon16);
        m_actionFaultDigitizingTools = new QAction(CX2DSectionWindow);
        m_actionFaultDigitizingTools->setObjectName(QString::fromUtf8("m_actionFaultDigitizingTools"));
        m_actionFaultDigitizingTools->setCheckable(true);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/Icon/Fault.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionFaultDigitizingTools->setIcon(icon17);
        m_actionHorizonTrackingTools = new QAction(CX2DSectionWindow);
        m_actionHorizonTrackingTools->setObjectName(QString::fromUtf8("m_actionHorizonTrackingTools"));
        m_actionHorizonTrackingTools->setCheckable(true);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/Icon/Horizon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon18.addFile(QString::fromUtf8(":/Icon/Horizon.png"), QSize(), QIcon::Normal, QIcon::On);
        m_actionHorizonTrackingTools->setIcon(icon18);
        m_action2ndLayerTools = new QAction(CX2DSectionWindow);
        m_action2ndLayerTools->setObjectName(QString::fromUtf8("m_action2ndLayerTools"));
        m_action2ndLayerTools->setCheckable(true);
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/Icon/SeismicDataVolume.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_action2ndLayerTools->setIcon(icon19);
        actionRectZoom = new QAction(CX2DSectionWindow);
        actionRectZoom->setObjectName(QString::fromUtf8("actionRectZoom"));
        actionRectZoom->setCheckable(true);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/Icon/RectZoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRectZoom->setIcon(icon20);
        actionRectZoomUndo = new QAction(CX2DSectionWindow);
        actionRectZoomUndo->setObjectName(QString::fromUtf8("actionRectZoomUndo"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/Icon/RectZoomUndo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRectZoomUndo->setIcon(icon21);
        actionCancelZoomin = new QAction(CX2DSectionWindow);
        actionCancelZoomin->setObjectName(QString::fromUtf8("actionCancelZoomin"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/Icon/RectZoomCancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCancelZoomin->setIcon(icon22);
        centralwidget = new QWidget(CX2DSectionWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        CX2DSectionWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CX2DSectionWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        CX2DSectionWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CX2DSectionWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CX2DSectionWindow->setStatusBar(statusbar);
        m_toolbarBasic = new QToolBar(CX2DSectionWindow);
        m_toolbarBasic->setObjectName(QString::fromUtf8("m_toolbarBasic"));
        CX2DSectionWindow->addToolBar(Qt::TopToolBarArea, m_toolbarBasic);
        m_toolbarColormap = new QToolBar(CX2DSectionWindow);
        m_toolbarColormap->setObjectName(QString::fromUtf8("m_toolbarColormap"));
        CX2DSectionWindow->addToolBar(Qt::BottomToolBarArea, m_toolbarColormap);
        m_toolbarDisplayMode = new QToolBar(CX2DSectionWindow);
        m_toolbarDisplayMode->setObjectName(QString::fromUtf8("m_toolbarDisplayMode"));
        CX2DSectionWindow->addToolBar(Qt::TopToolBarArea, m_toolbarDisplayMode);
        m_toolbarDigitizingAndForeground = new QToolBar(CX2DSectionWindow);
        m_toolbarDigitizingAndForeground->setObjectName(QString::fromUtf8("m_toolbarDigitizingAndForeground"));
        CX2DSectionWindow->addToolBar(Qt::BottomToolBarArea, m_toolbarDigitizingAndForeground);
        m_toolBarVolumes = new QToolBar(CX2DSectionWindow);
        m_toolBarVolumes->setObjectName(QString::fromUtf8("m_toolBarVolumes"));
        CX2DSectionWindow->addToolBar(Qt::TopToolBarArea, m_toolBarVolumes);

        m_toolbarBasic->addAction(m_actionProperties);
        m_toolbarBasic->addSeparator();
        m_toolbarBasic->addAction(m_actionViewAll);
        m_toolbarBasic->addAction(m_actionFitToWindowWidth);
        m_toolbarBasic->addAction(m_actionFitToWindowHeight);
        m_toolbarBasic->addSeparator();
        m_toolbarBasic->addAction(m_actionZoomIn);
        m_toolbarBasic->addAction(m_actionZoomOut);
        m_toolbarBasic->addAction(m_actionIncreaseHorizonScale);
        m_toolbarBasic->addAction(m_actionDecreaseHorizonScale);
        m_toolbarBasic->addAction(m_actionIncreaseVerticalScale);
        m_toolbarBasic->addAction(m_actionDecreaseVerticalScale);
        m_toolbarBasic->addSeparator();
        m_toolbarBasic->addAction(actionRectZoom);
        m_toolbarBasic->addAction(actionRectZoomUndo);
        m_toolbarBasic->addAction(actionCancelZoomin);
        m_toolbarBasic->addSeparator();
        m_toolbarBasic->addAction(m_actionIncreaseExcursion);
        m_toolbarBasic->addAction(m_actionDecreaseExcursion);
        m_toolbarDisplayMode->addAction(m_actionVariableIntensity);
        m_toolbarDisplayMode->addAction(m_actionWiggle);
        m_toolbarDisplayMode->addAction(m_actionVariableAreaWiggle);
        m_toolbarDigitizingAndForeground->addAction(m_actionHorizonTrackingTools);
        m_toolbarDigitizingAndForeground->addAction(m_actionFaultDigitizingTools);
        m_toolbarDigitizingAndForeground->addAction(m_action2ndLayerTools);
        m_toolbarDigitizingAndForeground->addAction(m_actionOrthoSections);

        retranslateUi(CX2DSectionWindow);

        QMetaObject::connectSlotsByName(CX2DSectionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CX2DSectionWindow)
    {
        m_actionProperties->setText(QCoreApplication::translate("CX2DSectionWindow", "Properties Window", nullptr));
        m_actionZoomIn->setText(QCoreApplication::translate("CX2DSectionWindow", "Zoom In", nullptr));
        m_actionZoomOut->setText(QCoreApplication::translate("CX2DSectionWindow", "Zoom Out", nullptr));
        m_actionViewAll->setText(QCoreApplication::translate("CX2DSectionWindow", "View All", nullptr));
        m_actionSynchronize->setText(QCoreApplication::translate("CX2DSectionWindow", "Synchronize", nullptr));
        m_actionOrthoSections->setText(QCoreApplication::translate("CX2DSectionWindow", "Show ortho sections", nullptr));
        m_actionFitToWindowWidth->setText(QCoreApplication::translate("CX2DSectionWindow", "Fit to Window Width", nullptr));
        m_actionFitToWindowHeight->setText(QCoreApplication::translate("CX2DSectionWindow", "Fit to Window Height", nullptr));
        m_actionIncreaseHorizonScale->setText(QCoreApplication::translate("CX2DSectionWindow", "Increase Horizon Scale", nullptr));
        m_actionDecreaseHorizonScale->setText(QCoreApplication::translate("CX2DSectionWindow", "Decrease Horizon Scale", nullptr));
        m_actionIncreaseVerticalScale->setText(QCoreApplication::translate("CX2DSectionWindow", "Increase Vertical Scale", nullptr));
        m_actionDecreaseVerticalScale->setText(QCoreApplication::translate("CX2DSectionWindow", "Decrease Vertical Scale", nullptr));
        m_actionIncreaseExcursion->setText(QCoreApplication::translate("CX2DSectionWindow", "Increase Excursion", nullptr));
        m_actionDecreaseExcursion->setText(QCoreApplication::translate("CX2DSectionWindow", "Decrease Excursion", nullptr));
        m_actionVariableIntensity->setText(QCoreApplication::translate("CX2DSectionWindow", "Variable Intensity", nullptr));
        m_actionWiggle->setText(QCoreApplication::translate("CX2DSectionWindow", "Wiggle", nullptr));
        m_actionVariableAreaWiggle->setText(QCoreApplication::translate("CX2DSectionWindow", "Variable Area + Wiggle", nullptr));
        m_actionFaultDigitizingTools->setText(QCoreApplication::translate("CX2DSectionWindow", "Fault Digitizing Tools", nullptr));
        m_actionHorizonTrackingTools->setText(QCoreApplication::translate("CX2DSectionWindow", "Horizon Tracking Tools", nullptr));
        m_action2ndLayerTools->setText(QCoreApplication::translate("CX2DSectionWindow", "2nd layer(Foreground) Tool", nullptr));
#if QT_CONFIG(tooltip)
        m_action2ndLayerTools->setToolTip(QCoreApplication::translate("CX2DSectionWindow", "2nd layer(Foreground) Tool", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRectZoom->setText(QCoreApplication::translate("CX2DSectionWindow", "RectZoom", nullptr));
#if QT_CONFIG(tooltip)
        actionRectZoom->setToolTip(QCoreApplication::translate("CX2DSectionWindow", "Zoom in to fit the given rectangle", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRectZoomUndo->setText(QCoreApplication::translate("CX2DSectionWindow", "RectZoomUndo", nullptr));
#if QT_CONFIG(tooltip)
        actionRectZoomUndo->setToolTip(QCoreApplication::translate("CX2DSectionWindow", "Undo last zoom in", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCancelZoomin->setText(QCoreApplication::translate("CX2DSectionWindow", "CancelZoomin", nullptr));
#if QT_CONFIG(tooltip)
        actionCancelZoomin->setToolTip(QCoreApplication::translate("CX2DSectionWindow", "Cancel all the zoom in", nullptr));
#endif // QT_CONFIG(tooltip)
        m_toolbarBasic->setWindowTitle(QCoreApplication::translate("CX2DSectionWindow", "Standard", nullptr));
        m_toolbarColormap->setWindowTitle(QCoreApplication::translate("CX2DSectionWindow", "Colormap", nullptr));
        m_toolbarDisplayMode->setWindowTitle(QCoreApplication::translate("CX2DSectionWindow", "Display mode and scale", nullptr));
        m_toolbarDigitizingAndForeground->setWindowTitle(QCoreApplication::translate("CX2DSectionWindow", "Digitizing and foreground tools", nullptr));
        m_toolBarVolumes->setWindowTitle(QCoreApplication::translate("CX2DSectionWindow", "Toolbar", nullptr));
        Q_UNUSED(CX2DSectionWindow);
    } // retranslateUi

};

namespace Ui {
    class CX2DSectionWindow: public Ui_CX2DSectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_X2DSECTIONWINDOW_H
