/********************************************************************************
** Form generated from reading UI file 'xsliderwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XSLIDERWIDGET_H
#define UI_XSLIDERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include <xslider.h>

QT_BEGIN_NAMESPACE

class Ui_WidgetSliderComplex
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *m_pSliderName;
    QLineEdit *m_pLineEdtMin;
    CXSlider *m_pSlider;
    QLineEdit *m_pLineEdtMax;

    void setupUi(QWidget *WidgetSliderComplex)
    {
        if (WidgetSliderComplex->objectName().isEmpty())
            WidgetSliderComplex->setObjectName(QString::fromUtf8("WidgetSliderComplex"));
        WidgetSliderComplex->resize(539, 32);
        gridLayout_2 = new QGridLayout(WidgetSliderComplex);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, -1);
        m_pSliderName = new QLabel(WidgetSliderComplex);
        m_pSliderName->setObjectName(QString::fromUtf8("m_pSliderName"));
        m_pSliderName->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(m_pSliderName, 0, 0, 1, 1);

        m_pLineEdtMin = new QLineEdit(WidgetSliderComplex);
        m_pLineEdtMin->setObjectName(QString::fromUtf8("m_pLineEdtMin"));
        m_pLineEdtMin->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(m_pLineEdtMin, 0, 1, 1, 1);

        m_pSlider = new CXSlider(WidgetSliderComplex);
        m_pSlider->setObjectName(QString::fromUtf8("m_pSlider"));
        m_pSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_pSlider, 0, 2, 1, 1);

        m_pLineEdtMax = new QLineEdit(WidgetSliderComplex);
        m_pLineEdtMax->setObjectName(QString::fromUtf8("m_pLineEdtMax"));
        m_pLineEdtMax->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(m_pLineEdtMax, 0, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(WidgetSliderComplex);

        QMetaObject::connectSlotsByName(WidgetSliderComplex);
    } // setupUi

    void retranslateUi(QWidget *WidgetSliderComplex)
    {
        WidgetSliderComplex->setWindowTitle(QCoreApplication::translate("WidgetSliderComplex", "Form", nullptr));
        m_pSliderName->setText(QCoreApplication::translate("WidgetSliderComplex", "Crossline Start", nullptr));
        m_pLineEdtMin->setText(QCoreApplication::translate("WidgetSliderComplex", "8888.8888", nullptr));
        m_pLineEdtMax->setText(QCoreApplication::translate("WidgetSliderComplex", "8888.8888", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetSliderComplex: public Ui_WidgetSliderComplex {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XSLIDERWIDGET_H
