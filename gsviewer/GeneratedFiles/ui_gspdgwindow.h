/********************************************************************************
** Form generated from reading UI file 'gspdgwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSPDGWINDOW_H
#define UI_GSPDGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "gspdgview.h"

QT_BEGIN_NAMESPACE

class Ui_GSPDGWindow
{
public:
    QAction *actionZoom_In;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    GSPDGView *PDGView;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *GSPDGWindow)
    {
        if (GSPDGWindow->objectName().isEmpty())
            GSPDGWindow->setObjectName(QString::fromUtf8("GSPDGWindow"));
        GSPDGWindow->resize(1045, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/PDG.png"), QSize(), QIcon::Normal, QIcon::Off);
        GSPDGWindow->setWindowIcon(icon);
        actionZoom_In = new QAction(GSPDGWindow);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/ZoomIn.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon1);
        centralwidget = new QWidget(GSPDGWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        PDGView = new GSPDGView(centralwidget);
        PDGView->setObjectName(QString::fromUtf8("PDGView"));

        gridLayout->addWidget(PDGView, 0, 0, 1, 1);

        GSPDGWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(GSPDGWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GSPDGWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(GSPDGWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        GSPDGWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionZoom_In);

        retranslateUi(GSPDGWindow);

        QMetaObject::connectSlotsByName(GSPDGWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GSPDGWindow)
    {
        GSPDGWindow->setWindowTitle(QCoreApplication::translate("GSPDGWindow", "PDG Window", nullptr));
        actionZoom_In->setText(QCoreApplication::translate("GSPDGWindow", "Zoom In", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("GSPDGWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSPDGWindow: public Ui_GSPDGWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSPDGWINDOW_H
