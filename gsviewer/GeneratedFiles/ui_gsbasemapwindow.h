/********************************************************************************
** Form generated from reading UI file 'gsbasemapwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSBASEMAPWINDOW_H
#define UI_GSBASEMAPWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "gsbasemapview.h"
#include "xcolormapwidget.h"

QT_BEGIN_NAMESPACE

class Ui_CGSBasemapWindow
{
public:
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionZoom_Reset;
    QAction *actionNewSection;
    QAction *actionZoom_By_Rect;
    QAction *actionZoom_Undo;
    QAction *actionZoom_to_width;
    QAction *actionZoom_to_height;
    QAction *actionNewPDG;
    QAction *actionNewRoseDiagram;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    GSBasemapView *graphicsView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidgetColormap;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    CXColormapWidget *colormapWidget;

    void setupUi(QMainWindow *CGSBasemapWindow)
    {
        if (CGSBasemapWindow->objectName().isEmpty())
            CGSBasemapWindow->setObjectName(QString::fromUtf8("CGSBasemapWindow"));
        CGSBasemapWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/BasemapWindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        CGSBasemapWindow->setWindowIcon(icon);
        actionZoom_In = new QAction(CGSBasemapWindow);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/view_zoom_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon1);
        actionZoom_Out = new QAction(CGSBasemapWindow);
        actionZoom_Out->setObjectName(QString::fromUtf8("actionZoom_Out"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/view_zoom_out.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Out->setIcon(icon2);
        actionZoom_Reset = new QAction(CGSBasemapWindow);
        actionZoom_Reset->setObjectName(QString::fromUtf8("actionZoom_Reset"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/view_zoom_page.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Reset->setIcon(icon3);
        actionNewSection = new QAction(CGSBasemapWindow);
        actionNewSection->setObjectName(QString::fromUtf8("actionNewSection"));
        actionNewSection->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/SectionNew.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewSection->setIcon(icon4);
        actionNewSection->setVisible(false);
        actionZoom_By_Rect = new QAction(CGSBasemapWindow);
        actionZoom_By_Rect->setObjectName(QString::fromUtf8("actionZoom_By_Rect"));
        actionZoom_By_Rect->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/view_zoom_rect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_By_Rect->setIcon(icon5);
        actionZoom_Undo = new QAction(CGSBasemapWindow);
        actionZoom_Undo->setObjectName(QString::fromUtf8("actionZoom_Undo"));
        actionZoom_Undo->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/view_zoom_undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Undo->setIcon(icon6);
        actionZoom_to_width = new QAction(CGSBasemapWindow);
        actionZoom_to_width->setObjectName(QString::fromUtf8("actionZoom_to_width"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icon/view_zoom_width.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_to_width->setIcon(icon7);
        actionZoom_to_height = new QAction(CGSBasemapWindow);
        actionZoom_to_height->setObjectName(QString::fromUtf8("actionZoom_to_height"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icon/view_zoom_height.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_to_height->setIcon(icon8);
        actionNewPDG = new QAction(CGSBasemapWindow);
        actionNewPDG->setObjectName(QString::fromUtf8("actionNewPDG"));
        actionNewPDG->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Icon/PDGNew.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewPDG->setIcon(icon9);
        actionNewPDG->setVisible(false);
        actionNewRoseDiagram = new QAction(CGSBasemapWindow);
        actionNewRoseDiagram->setObjectName(QString::fromUtf8("actionNewRoseDiagram"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Icon/RoseDiagram.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewRoseDiagram->setIcon(icon10);
        actionNewRoseDiagram->setVisible(false);
        centralWidget = new QWidget(CGSBasemapWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new GSBasemapView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        CGSBasemapWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(CGSBasemapWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(16, 16));
        CGSBasemapWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CGSBasemapWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CGSBasemapWindow->setStatusBar(statusBar);
        dockWidgetColormap = new QDockWidget(CGSBasemapWindow);
        dockWidgetColormap->setObjectName(QString::fromUtf8("dockWidgetColormap"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        colormapWidget = new CXColormapWidget(dockWidgetContents);
        colormapWidget->setObjectName(QString::fromUtf8("colormapWidget"));
        colormapWidget->setMinimumSize(QSize(80, 0));

        gridLayout_2->addWidget(colormapWidget, 0, 0, 1, 1);

        dockWidgetColormap->setWidget(dockWidgetContents);
        CGSBasemapWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidgetColormap);

        mainToolBar->addAction(actionZoom_In);
        mainToolBar->addAction(actionZoom_Out);
        mainToolBar->addAction(actionZoom_to_width);
        mainToolBar->addAction(actionZoom_to_height);
        mainToolBar->addAction(actionZoom_By_Rect);
        mainToolBar->addAction(actionZoom_Undo);
        mainToolBar->addAction(actionZoom_Reset);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionNewSection);
        mainToolBar->addAction(actionNewPDG);
        mainToolBar->addAction(actionNewRoseDiagram);

        retranslateUi(CGSBasemapWindow);

        QMetaObject::connectSlotsByName(CGSBasemapWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CGSBasemapWindow)
    {
        actionZoom_In->setText(QCoreApplication::translate("CGSBasemapWindow", "Zoom In", nullptr));
        actionZoom_Out->setText(QCoreApplication::translate("CGSBasemapWindow", "Zoom Out", nullptr));
        actionZoom_Reset->setText(QCoreApplication::translate("CGSBasemapWindow", "Zoom Reset", nullptr));
        actionNewSection->setText(QCoreApplication::translate("CGSBasemapWindow", "New Section", nullptr));
#if QT_CONFIG(tooltip)
        actionNewSection->setToolTip(QCoreApplication::translate("CGSBasemapWindow", "Create a new section polyline", nullptr));
#endif // QT_CONFIG(tooltip)
        actionZoom_By_Rect->setText(QCoreApplication::translate("CGSBasemapWindow", "Zoom By Rect", nullptr));
        actionZoom_Undo->setText(QCoreApplication::translate("CGSBasemapWindow", "Zoom Undo", nullptr));
        actionZoom_to_width->setText(QCoreApplication::translate("CGSBasemapWindow", "Zoom to width", nullptr));
        actionZoom_to_height->setText(QCoreApplication::translate("CGSBasemapWindow", "Zoom to height", nullptr));
        actionNewPDG->setText(QCoreApplication::translate("CGSBasemapWindow", "New PDG", nullptr));
#if QT_CONFIG(tooltip)
        actionNewPDG->setToolTip(QCoreApplication::translate("CGSBasemapWindow", "Create a new PDG", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNewRoseDiagram->setText(QCoreApplication::translate("CGSBasemapWindow", "CreateRoseDiagram", nullptr));
#if QT_CONFIG(tooltip)
        actionNewRoseDiagram->setToolTip(QCoreApplication::translate("CGSBasemapWindow", "Create new Rose diagram", nullptr));
#endif // QT_CONFIG(tooltip)
        Q_UNUSED(CGSBasemapWindow);
    } // retranslateUi

};

namespace Ui {
    class CGSBasemapWindow: public Ui_CGSBasemapWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSBASEMAPWINDOW_H
