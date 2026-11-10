/********************************************************************************
** Form generated from reading UI file 'xpagecssinversiontwo.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGECSSINVERSIONTWO_H
#define UI_XPAGECSSINVERSIONTWO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_PageCSSInversionTwo
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox;
    QCheckBox *m_pRadioReflectivity;
    QCheckBox *m_pRadioSeismic;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *m_pCmbCPUNumber;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    CXSliderComplex *m_pInlineWidget;
    CXSliderComplex *m_pXlineWidget;

    void setupUi(QWidget *PageCSSInversionTwo)
    {
        if (PageCSSInversionTwo->objectName().isEmpty())
            PageCSSInversionTwo->setObjectName(QString::fromUtf8("PageCSSInversionTwo"));
        PageCSSInversionTwo->resize(619, 310);
        gridLayout_3 = new QGridLayout(PageCSSInversionTwo);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_2 = new QGroupBox(PageCSSInversionTwo);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);
        checkBox->setChecked(true);

        gridLayout_2->addWidget(checkBox, 0, 0, 1, 1);

        m_pRadioReflectivity = new QCheckBox(groupBox_2);
        m_pRadioReflectivity->setObjectName(QString::fromUtf8("m_pRadioReflectivity"));

        gridLayout_2->addWidget(m_pRadioReflectivity, 0, 1, 1, 1);

        m_pRadioSeismic = new QCheckBox(groupBox_2);
        m_pRadioSeismic->setObjectName(QString::fromUtf8("m_pRadioSeismic"));

        gridLayout_2->addWidget(m_pRadioSeismic, 0, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(348, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 9, -1, 9);
        label = new QLabel(PageCSSInversionTwo);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_pCmbCPUNumber = new QComboBox(PageCSSInversionTwo);
        m_pCmbCPUNumber->setObjectName(QString::fromUtf8("m_pCmbCPUNumber"));
        m_pCmbCPUNumber->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_pCmbCPUNumber);


        gridLayout_3->addLayout(horizontalLayout, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 224, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 1, 1, 1);

        groupBox = new QGroupBox(PageCSSInversionTwo);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 100));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pInlineWidget = new CXSliderComplex(groupBox);
        m_pInlineWidget->setObjectName(QString::fromUtf8("m_pInlineWidget"));
        m_pInlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pInlineWidget, 0, 0, 1, 1);

        m_pXlineWidget = new CXSliderComplex(groupBox);
        m_pXlineWidget->setObjectName(QString::fromUtf8("m_pXlineWidget"));
        m_pXlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pXlineWidget, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 2);


        retranslateUi(PageCSSInversionTwo);

        QMetaObject::connectSlotsByName(PageCSSInversionTwo);
    } // setupUi

    void retranslateUi(QWidget *PageCSSInversionTwo)
    {
        PageCSSInversionTwo->setWindowTitle(QCoreApplication::translate("PageCSSInversionTwo", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PageCSSInversionTwo", "Output Options", nullptr));
        checkBox->setText(QCoreApplication::translate("PageCSSInversionTwo", "P-Impedance", nullptr));
        m_pRadioReflectivity->setText(QCoreApplication::translate("PageCSSInversionTwo", "Reflectivity", nullptr));
        m_pRadioSeismic->setText(QCoreApplication::translate("PageCSSInversionTwo", "Simulated Seismic Data", nullptr));
        label->setText(QCoreApplication::translate("PageCSSInversionTwo", "CPU Number for Computation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageCSSInversionTwo", "Output Range", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageCSSInversionTwo: public Ui_PageCSSInversionTwo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGECSSINVERSIONTWO_H
