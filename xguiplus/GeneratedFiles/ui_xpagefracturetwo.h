/********************************************************************************
** Form generated from reading UI file 'xpagefracturetwo.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEFRACTURETWO_H
#define UI_XPAGEFRACTURETWO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_PageFractureTwo
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QLineEdit *m_pLineEdtDy;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QLineEdit *m_pLineEdtDx;
    QLabel *label_4;
    QLabel *label_2;
    QComboBox *m_pCombMethod;
    QLabel *label_8;
    QLineEdit *m_pLineEdtMinimumFold;
    QSpacerItem *horizontalSpacer_3;
    QLabel *m_pLabelIncidence;
    QLabel *label_3;
    QComboBox *m_pCombBoxIncidence;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    CXSliderComplex *m_pInlineWidget;
    CXSliderComplex *m_pXlineWidget;
    CXSliderComplex *m_pTimeWidget;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *m_pCmbCPUNumber;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PageFractureTwo)
    {
        if (PageFractureTwo->objectName().isEmpty())
            PageFractureTwo->setObjectName(QString::fromUtf8("PageFractureTwo"));
        PageFractureTwo->resize(631, 362);
        gridLayout_3 = new QGridLayout(PageFractureTwo);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_2 = new QGroupBox(PageFractureTwo);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 2, 8, 1, 1);

        m_pLineEdtDy = new QLineEdit(groupBox_2);
        m_pLineEdtDy->setObjectName(QString::fromUtf8("m_pLineEdtDy"));
        m_pLineEdtDy->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtDy, 2, 7, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 6, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 4, 1, 2);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 3, 1, 1);

        m_pLineEdtDx = new QLineEdit(groupBox_2);
        m_pLineEdtDx->setObjectName(QString::fromUtf8("m_pLineEdtDx"));
        m_pLineEdtDx->setMinimumSize(QSize(0, 0));
        m_pLineEdtDx->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtDx, 2, 2, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        m_pCombMethod = new QComboBox(groupBox_2);
        m_pCombMethod->addItem(QString());
        m_pCombMethod->addItem(QString());
        m_pCombMethod->setObjectName(QString::fromUtf8("m_pCombMethod"));

        gridLayout_2->addWidget(m_pCombMethod, 0, 1, 1, 5);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        m_pLineEdtMinimumFold = new QLineEdit(groupBox_2);
        m_pLineEdtMinimumFold->setObjectName(QString::fromUtf8("m_pLineEdtMinimumFold"));
        m_pLineEdtMinimumFold->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtMinimumFold, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(94, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 3, 1, 2);

        m_pLabelIncidence = new QLabel(groupBox_2);
        m_pLabelIncidence->setObjectName(QString::fromUtf8("m_pLabelIncidence"));

        gridLayout_2->addWidget(m_pLabelIncidence, 1, 5, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        m_pCombBoxIncidence = new QComboBox(groupBox_2);
        m_pCombBoxIncidence->setObjectName(QString::fromUtf8("m_pCombBoxIncidence"));

        gridLayout_2->addWidget(m_pCombBoxIncidence, 1, 7, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 2);

        groupBox = new QGroupBox(PageFractureTwo);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 130));
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

        m_pTimeWidget = new CXSliderComplex(groupBox);
        m_pTimeWidget->setObjectName(QString::fromUtf8("m_pTimeWidget"));
        m_pTimeWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pTimeWidget, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(348, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 9, -1, 9);
        label = new QLabel(PageFractureTwo);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_pCmbCPUNumber = new QComboBox(PageFractureTwo);
        m_pCmbCPUNumber->setObjectName(QString::fromUtf8("m_pCmbCPUNumber"));
        m_pCmbCPUNumber->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_pCmbCPUNumber);


        gridLayout_3->addLayout(horizontalLayout, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 48, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 0, 1, 1);

        groupBox->raise();
        groupBox_2->raise();

        retranslateUi(PageFractureTwo);

        QMetaObject::connectSlotsByName(PageFractureTwo);
    } // setupUi

    void retranslateUi(QWidget *PageFractureTwo)
    {
        PageFractureTwo->setWindowTitle(QCoreApplication::translate("PageFractureTwo", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PageFractureTwo", "Calculation Parameters", nullptr));
        label_7->setText(QCoreApplication::translate("PageFractureTwo", "lines", nullptr));
        label_6->setText(QCoreApplication::translate("PageFractureTwo", "Dy", nullptr));
        label_5->setText(QCoreApplication::translate("PageFractureTwo", "traces", nullptr));
        label_4->setText(QCoreApplication::translate("PageFractureTwo", "Dx", nullptr));
        label_2->setText(QCoreApplication::translate("PageFractureTwo", "Calculation Method  ", nullptr));
        m_pCombMethod->setItemText(0, QCoreApplication::translate("PageFractureTwo", "Ruger's  Equation", nullptr));
        m_pCombMethod->setItemText(1, QCoreApplication::translate("PageFractureTwo", "Azimuthal Fourier Coefficients", nullptr));

        label_8->setText(QCoreApplication::translate("PageFractureTwo", "Minimum fold", nullptr));
        m_pLabelIncidence->setText(QCoreApplication::translate("PageFractureTwo", "Angle of Incidence (deg)", nullptr));
        label_3->setText(QCoreApplication::translate("PageFractureTwo", "Window Size", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageFractureTwo", "Output Range", nullptr));
        label->setText(QCoreApplication::translate("PageFractureTwo", "CPU Number for Computation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageFractureTwo: public Ui_PageFractureTwo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEFRACTURETWO_H
