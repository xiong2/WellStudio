/********************************************************************************
** Form generated from reading UI file 'xwidget3dsurface.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XWIDGET3DSURFACE_H
#define UI_XWIDGET3DSURFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <xcolormapwidget.h>

QT_BEGIN_NAMESPACE

class Ui_Widget3DSurface
{
public:
    QGridLayout *gridLayout;
    QScrollArea *m_pScrollArea;
    QWidget *scrollAreaWidgetContents;
    CXColormapWidget *m_pColormapWidget;

    void setupUi(QWidget *Widget3DSurface)
    {
        if (Widget3DSurface->objectName().isEmpty())
            Widget3DSurface->setObjectName(QString::fromUtf8("Widget3DSurface"));
        Widget3DSurface->resize(589, 518);
        gridLayout = new QGridLayout(Widget3DSurface);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pScrollArea = new QScrollArea(Widget3DSurface);
        m_pScrollArea->setObjectName(QString::fromUtf8("m_pScrollArea"));
        m_pScrollArea->setFrameShadow(QFrame::Raised);
        m_pScrollArea->setLineWidth(0);
        m_pScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 483, 498));
        m_pScrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(m_pScrollArea, 0, 0, 1, 1);

        m_pColormapWidget = new CXColormapWidget(Widget3DSurface);
        m_pColormapWidget->setObjectName(QString::fromUtf8("m_pColormapWidget"));
        m_pColormapWidget->setMinimumSize(QSize(80, 0));
        m_pColormapWidget->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pColormapWidget, 0, 1, 1, 1);


        retranslateUi(Widget3DSurface);

        QMetaObject::connectSlotsByName(Widget3DSurface);
    } // setupUi

    void retranslateUi(QWidget *Widget3DSurface)
    {
        Widget3DSurface->setWindowTitle(QCoreApplication::translate("Widget3DSurface", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget3DSurface: public Ui_Widget3DSurface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XWIDGET3DSURFACE_H
