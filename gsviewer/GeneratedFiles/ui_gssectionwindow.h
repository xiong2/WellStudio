/********************************************************************************
** Form generated from reading UI file 'gssectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSSECTIONWINDOW_H
#define UI_GSSECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "gssectionview.h"

QT_BEGIN_NAMESPACE

class Ui_GSSectionWindow
{
public:
    QAction *actionZoom_In;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    GSSectionView *sectionView;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *GSSectionWindow)
    {
        if (GSSectionWindow->objectName().isEmpty())
            GSSectionWindow->setObjectName(QString::fromUtf8("GSSectionWindow"));
        GSSectionWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/SectionWindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        GSSectionWindow->setWindowIcon(icon);
        actionZoom_In = new QAction(GSSectionWindow);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/view_zoom_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon1);
        centralwidget = new QWidget(GSSectionWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sectionView = new GSSectionView(centralwidget);
        sectionView->setObjectName(QString::fromUtf8("sectionView"));

        gridLayout->addWidget(sectionView, 0, 0, 1, 1);

        GSSectionWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(GSSectionWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GSSectionWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(GSSectionWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        GSSectionWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionZoom_In);

        retranslateUi(GSSectionWindow);

        QMetaObject::connectSlotsByName(GSSectionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GSSectionWindow)
    {
        GSSectionWindow->setWindowTitle(QCoreApplication::translate("GSSectionWindow", "Section Window", nullptr));
        actionZoom_In->setText(QCoreApplication::translate("GSSectionWindow", "Zoom In", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("GSSectionWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSSectionWindow: public Ui_GSSectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSSECTIONWINDOW_H
