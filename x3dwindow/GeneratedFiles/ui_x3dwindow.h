/********************************************************************************
** Form generated from reading UI file 'x3dwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_X3DWINDOW_H
#define UI_X3DWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_X3DWindow
{
public:
    QAction *actionSelect_Mode;
    QAction *actionView_All;
    QAction *actionHome;
    QAction *actionSet_Home;
    QAction *actionXY_Plane_View;
    QAction *actionXZ_Plane_View;
    QAction *actionYZ_Plane_View;
    QAction *actionShow_Hide_Coordinates;
    QAction *actionShow_Hide_Coordinates_Grid;
    QAction *actionPerspective_Orthogonal_View_Mode;
    QAction *actionCompass;
    QAction *actionSynchronize;
    QAction *actionColorbar;
    QAction *actionLight_Setting;
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *bottomToolBar;

    void setupUi(QMainWindow *X3DWindow)
    {
        if (X3DWindow->objectName().isEmpty())
            X3DWindow->setObjectName(QString::fromUtf8("X3DWindow"));
        X3DWindow->resize(906, 625);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/3dwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        X3DWindow->setWindowIcon(icon);
        actionSelect_Mode = new QAction(X3DWindow);
        actionSelect_Mode->setObjectName(QString::fromUtf8("actionSelect_Mode"));
        actionSelect_Mode->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Selection.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect_Mode->setIcon(icon1);
        actionView_All = new QAction(X3DWindow);
        actionView_All->setObjectName(QString::fromUtf8("actionView_All"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/ViewAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionView_All->setIcon(icon2);
        actionHome = new QAction(X3DWindow);
        actionHome->setObjectName(QString::fromUtf8("actionHome"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/Home.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHome->setIcon(icon3);
        actionSet_Home = new QAction(X3DWindow);
        actionSet_Home->setObjectName(QString::fromUtf8("actionSet_Home"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/SetHome.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_Home->setIcon(icon4);
        actionXY_Plane_View = new QAction(X3DWindow);
        actionXY_Plane_View->setObjectName(QString::fromUtf8("actionXY_Plane_View"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/XYPlane.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionXY_Plane_View->setIcon(icon5);
        actionXZ_Plane_View = new QAction(X3DWindow);
        actionXZ_Plane_View->setObjectName(QString::fromUtf8("actionXZ_Plane_View"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/XZPlane.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionXZ_Plane_View->setIcon(icon6);
        actionYZ_Plane_View = new QAction(X3DWindow);
        actionYZ_Plane_View->setObjectName(QString::fromUtf8("actionYZ_Plane_View"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icon/YZPlane.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionYZ_Plane_View->setIcon(icon7);
        actionShow_Hide_Coordinates = new QAction(X3DWindow);
        actionShow_Hide_Coordinates->setObjectName(QString::fromUtf8("actionShow_Hide_Coordinates"));
        actionShow_Hide_Coordinates->setCheckable(true);
        actionShow_Hide_Coordinates->setChecked(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icon/Axes.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_Hide_Coordinates->setIcon(icon8);
        actionShow_Hide_Coordinates_Grid = new QAction(X3DWindow);
        actionShow_Hide_Coordinates_Grid->setObjectName(QString::fromUtf8("actionShow_Hide_Coordinates_Grid"));
        actionShow_Hide_Coordinates_Grid->setCheckable(true);
        actionShow_Hide_Coordinates_Grid->setChecked(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Icon/AxesGrids.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_Hide_Coordinates_Grid->setIcon(icon9);
        actionPerspective_Orthogonal_View_Mode = new QAction(X3DWindow);
        actionPerspective_Orthogonal_View_Mode->setObjectName(QString::fromUtf8("actionPerspective_Orthogonal_View_Mode"));
        actionPerspective_Orthogonal_View_Mode->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Icon/Perspective.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon10.addFile(QString::fromUtf8(":/Icon/Ortho.png"), QSize(), QIcon::Normal, QIcon::On);
        actionPerspective_Orthogonal_View_Mode->setIcon(icon10);
        actionCompass = new QAction(X3DWindow);
        actionCompass->setObjectName(QString::fromUtf8("actionCompass"));
        actionCompass->setCheckable(true);
        actionCompass->setChecked(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Icon/Compass.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCompass->setIcon(icon11);
        actionSynchronize = new QAction(X3DWindow);
        actionSynchronize->setObjectName(QString::fromUtf8("actionSynchronize"));
        actionSynchronize->setCheckable(true);
        actionSynchronize->setChecked(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Icon/Synchronize.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSynchronize->setIcon(icon12);
        actionColorbar = new QAction(X3DWindow);
        actionColorbar->setObjectName(QString::fromUtf8("actionColorbar"));
        actionColorbar->setCheckable(true);
        actionColorbar->setChecked(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Icon/Colorbar.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionColorbar->setIcon(icon13);
        actionLight_Setting = new QAction(X3DWindow);
        actionLight_Setting->setObjectName(QString::fromUtf8("actionLight_Setting"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Icon/lights.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLight_Setting->setIcon(icon14);
        centralWidget = new QWidget(X3DWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        X3DWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(X3DWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(16, 16));
        X3DWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(X3DWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        X3DWindow->setStatusBar(statusBar);
        bottomToolBar = new QToolBar(X3DWindow);
        bottomToolBar->setObjectName(QString::fromUtf8("bottomToolBar"));
        X3DWindow->addToolBar(Qt::BottomToolBarArea, bottomToolBar);

        mainToolBar->addAction(actionSelect_Mode);
        mainToolBar->addAction(actionSynchronize);
        mainToolBar->addAction(actionHome);
        mainToolBar->addAction(actionSet_Home);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionView_All);
        mainToolBar->addAction(actionXY_Plane_View);
        mainToolBar->addAction(actionXZ_Plane_View);
        mainToolBar->addAction(actionYZ_Plane_View);
        mainToolBar->addAction(actionPerspective_Orthogonal_View_Mode);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionShow_Hide_Coordinates);
        mainToolBar->addAction(actionShow_Hide_Coordinates_Grid);
        mainToolBar->addAction(actionCompass);
        mainToolBar->addAction(actionColorbar);
        mainToolBar->addAction(actionLight_Setting);

        retranslateUi(X3DWindow);

        QMetaObject::connectSlotsByName(X3DWindow);
    } // setupUi

    void retranslateUi(QMainWindow *X3DWindow)
    {
        X3DWindow->setWindowTitle(QCoreApplication::translate("X3DWindow", "3-D Window", nullptr));
        actionSelect_Mode->setText(QCoreApplication::translate("X3DWindow", "Select Mode", nullptr));
        actionView_All->setText(QCoreApplication::translate("X3DWindow", "View All", nullptr));
        actionHome->setText(QCoreApplication::translate("X3DWindow", "Home", nullptr));
        actionSet_Home->setText(QCoreApplication::translate("X3DWindow", "Set Home", nullptr));
        actionXY_Plane_View->setText(QCoreApplication::translate("X3DWindow", "XY Plane View", nullptr));
        actionXZ_Plane_View->setText(QCoreApplication::translate("X3DWindow", "XZ Plane View", nullptr));
        actionYZ_Plane_View->setText(QCoreApplication::translate("X3DWindow", "YZ Plane View", nullptr));
        actionShow_Hide_Coordinates->setText(QCoreApplication::translate("X3DWindow", "Show/Hide Coordinates", nullptr));
        actionShow_Hide_Coordinates_Grid->setText(QCoreApplication::translate("X3DWindow", "Show/Hide Coordinates Grid", nullptr));
        actionPerspective_Orthogonal_View_Mode->setText(QCoreApplication::translate("X3DWindow", "Perspective/Orthogonal View Mode", nullptr));
        actionCompass->setText(QCoreApplication::translate("X3DWindow", "Compass", nullptr));
        actionSynchronize->setText(QCoreApplication::translate("X3DWindow", "Synchronize", nullptr));
        actionColorbar->setText(QCoreApplication::translate("X3DWindow", "Colorbar", nullptr));
        actionLight_Setting->setText(QCoreApplication::translate("X3DWindow", "Light Setting", nullptr));
        bottomToolBar->setWindowTitle(QCoreApplication::translate("X3DWindow", "Toolbar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class X3DWindow: public Ui_X3DWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_X3DWINDOW_H
