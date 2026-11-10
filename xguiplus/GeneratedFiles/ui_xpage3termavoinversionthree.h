/********************************************************************************
** Form generated from reading UI file 'xpage3termavoinversionthree.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGE3TERMAVOINVERSIONTHREE_H
#define UI_XPAGE3TERMAVOINVERSIONTHREE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_Page3TermAvoInversionThree
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *m;
    QGridLayout *gridLayout;
    CXSliderComplex *m_pInlineWidget;
    CXSliderComplex *m_pXlineWidget;
    CXSliderComplex *m_pTimeWidget;
    QCheckBox *m_pCheckBoxHorizon;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_pLabelTop;
    QPushButton *m_pBtnTop;
    QLineEdit *m_pLineEdtTopHorizon;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_pLabelBot;
    QPushButton *m_pBtnBot;
    QLineEdit *m_pLineEdtBotHorizon;
    QGroupBox *m_pGroupBoxInversion;
    QGridLayout *gridLayout_2;
    QRadioButton *m_pRadioZpZsRho;
    QRadioButton *m_pRadioZpVpVsRho;
    QRadioButton *m_pRadioVpVsRho;
    QCheckBox *m_pRadioReflectivity;
    QCheckBox *m_pRadioSeismic;
    QGroupBox *m_pGroupBoxPrior;
    QGridLayout *gridLayout_3;
    QCheckBox *m_pCheckBoxPrior;
    QRadioButton *m_pRadioAki;
    QRadioButton *m_pRadioZoeppritz;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *m_pCmbCPUNumber;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Page3TermAvoInversionThree)
    {
        if (Page3TermAvoInversionThree->objectName().isEmpty())
            Page3TermAvoInversionThree->setObjectName(QString::fromUtf8("Page3TermAvoInversionThree"));
        Page3TermAvoInversionThree->resize(667, 416);
        gridLayout_4 = new QGridLayout(Page3TermAvoInversionThree);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m = new QGroupBox(Page3TermAvoInversionThree);
        m->setObjectName(QString::fromUtf8("m"));
        m->setMinimumSize(QSize(0, 180));
        gridLayout = new QGridLayout(m);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pInlineWidget = new CXSliderComplex(m);
        m_pInlineWidget->setObjectName(QString::fromUtf8("m_pInlineWidget"));
        m_pInlineWidget->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(m_pInlineWidget, 0, 0, 1, 1);

        m_pXlineWidget = new CXSliderComplex(m);
        m_pXlineWidget->setObjectName(QString::fromUtf8("m_pXlineWidget"));
        m_pXlineWidget->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(m_pXlineWidget, 1, 0, 1, 1);

        m_pTimeWidget = new CXSliderComplex(m);
        m_pTimeWidget->setObjectName(QString::fromUtf8("m_pTimeWidget"));
        m_pTimeWidget->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(m_pTimeWidget, 2, 0, 1, 1);

        m_pCheckBoxHorizon = new QCheckBox(m);
        m_pCheckBoxHorizon->setObjectName(QString::fromUtf8("m_pCheckBoxHorizon"));

        gridLayout->addWidget(m_pCheckBoxHorizon, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_pLabelTop = new QLabel(m);
        m_pLabelTop->setObjectName(QString::fromUtf8("m_pLabelTop"));

        horizontalLayout_2->addWidget(m_pLabelTop);

        m_pBtnTop = new QPushButton(m);
        m_pBtnTop->setObjectName(QString::fromUtf8("m_pBtnTop"));
        m_pBtnTop->setMaximumSize(QSize(30, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnTop->setIcon(icon);

        horizontalLayout_2->addWidget(m_pBtnTop);

        m_pLineEdtTopHorizon = new QLineEdit(m);
        m_pLineEdtTopHorizon->setObjectName(QString::fromUtf8("m_pLineEdtTopHorizon"));
        m_pLineEdtTopHorizon->setMinimumSize(QSize(200, 0));
        m_pLineEdtTopHorizon->setReadOnly(true);

        horizontalLayout_2->addWidget(m_pLineEdtTopHorizon);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_pLabelBot = new QLabel(m);
        m_pLabelBot->setObjectName(QString::fromUtf8("m_pLabelBot"));

        horizontalLayout_2->addWidget(m_pLabelBot);

        m_pBtnBot = new QPushButton(m);
        m_pBtnBot->setObjectName(QString::fromUtf8("m_pBtnBot"));
        m_pBtnBot->setMinimumSize(QSize(0, 20));
        m_pBtnBot->setMaximumSize(QSize(30, 16777215));
        m_pBtnBot->setIcon(icon);

        horizontalLayout_2->addWidget(m_pBtnBot);

        m_pLineEdtBotHorizon = new QLineEdit(m);
        m_pLineEdtBotHorizon->setObjectName(QString::fromUtf8("m_pLineEdtBotHorizon"));
        m_pLineEdtBotHorizon->setMinimumSize(QSize(200, 0));
        m_pLineEdtBotHorizon->setReadOnly(true);

        horizontalLayout_2->addWidget(m_pLineEdtBotHorizon);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 1);


        gridLayout_4->addWidget(m, 0, 0, 1, 2);

        m_pGroupBoxInversion = new QGroupBox(Page3TermAvoInversionThree);
        m_pGroupBoxInversion->setObjectName(QString::fromUtf8("m_pGroupBoxInversion"));
        m_pGroupBoxInversion->setCheckable(true);
        gridLayout_2 = new QGridLayout(m_pGroupBoxInversion);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pRadioZpZsRho = new QRadioButton(m_pGroupBoxInversion);
        m_pRadioZpZsRho->setObjectName(QString::fromUtf8("m_pRadioZpZsRho"));

        gridLayout_2->addWidget(m_pRadioZpZsRho, 0, 0, 1, 1);

        m_pRadioZpVpVsRho = new QRadioButton(m_pGroupBoxInversion);
        m_pRadioZpVpVsRho->setObjectName(QString::fromUtf8("m_pRadioZpVpVsRho"));
        m_pRadioZpVpVsRho->setChecked(true);

        gridLayout_2->addWidget(m_pRadioZpVpVsRho, 0, 1, 1, 1);

        m_pRadioVpVsRho = new QRadioButton(m_pGroupBoxInversion);
        m_pRadioVpVsRho->setObjectName(QString::fromUtf8("m_pRadioVpVsRho"));

        gridLayout_2->addWidget(m_pRadioVpVsRho, 0, 2, 1, 1);

        m_pRadioReflectivity = new QCheckBox(m_pGroupBoxInversion);
        m_pRadioReflectivity->setObjectName(QString::fromUtf8("m_pRadioReflectivity"));

        gridLayout_2->addWidget(m_pRadioReflectivity, 1, 1, 1, 1);

        m_pRadioSeismic = new QCheckBox(m_pGroupBoxInversion);
        m_pRadioSeismic->setObjectName(QString::fromUtf8("m_pRadioSeismic"));

        gridLayout_2->addWidget(m_pRadioSeismic, 1, 2, 1, 1);


        gridLayout_4->addWidget(m_pGroupBoxInversion, 1, 0, 1, 2);

        m_pGroupBoxPrior = new QGroupBox(Page3TermAvoInversionThree);
        m_pGroupBoxPrior->setObjectName(QString::fromUtf8("m_pGroupBoxPrior"));
        m_pGroupBoxPrior->setCheckable(true);
        m_pGroupBoxPrior->setChecked(false);
        gridLayout_3 = new QGridLayout(m_pGroupBoxPrior);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pCheckBoxPrior = new QCheckBox(m_pGroupBoxPrior);
        m_pCheckBoxPrior->setObjectName(QString::fromUtf8("m_pCheckBoxPrior"));
        m_pCheckBoxPrior->setEnabled(false);
        m_pCheckBoxPrior->setCheckable(true);
        m_pCheckBoxPrior->setChecked(true);
        m_pCheckBoxPrior->setAutoRepeat(false);

        gridLayout_3->addWidget(m_pCheckBoxPrior, 0, 0, 1, 1);

        m_pRadioAki = new QRadioButton(m_pGroupBoxPrior);
        m_pRadioAki->setObjectName(QString::fromUtf8("m_pRadioAki"));
        m_pRadioAki->setChecked(true);

        gridLayout_3->addWidget(m_pRadioAki, 0, 1, 1, 1);

        m_pRadioZoeppritz = new QRadioButton(m_pGroupBoxPrior);
        m_pRadioZoeppritz->setObjectName(QString::fromUtf8("m_pRadioZoeppritz"));

        gridLayout_3->addWidget(m_pRadioZoeppritz, 0, 2, 1, 1);


        gridLayout_4->addWidget(m_pGroupBoxPrior, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(348, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 9, -1, 9);
        label = new QLabel(Page3TermAvoInversionThree);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_pCmbCPUNumber = new QComboBox(Page3TermAvoInversionThree);
        m_pCmbCPUNumber->setObjectName(QString::fromUtf8("m_pCmbCPUNumber"));
        m_pCmbCPUNumber->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_pCmbCPUNumber);


        gridLayout_4->addLayout(horizontalLayout, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 224, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 1, 1, 1);


        retranslateUi(Page3TermAvoInversionThree);

        QMetaObject::connectSlotsByName(Page3TermAvoInversionThree);
    } // setupUi

    void retranslateUi(QWidget *Page3TermAvoInversionThree)
    {
        Page3TermAvoInversionThree->setWindowTitle(QCoreApplication::translate("Page3TermAvoInversionThree", "Form", nullptr));
        m->setTitle(QCoreApplication::translate("Page3TermAvoInversionThree", "Output Range", nullptr));
        m_pCheckBoxHorizon->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Horizon Constraints", nullptr));
        m_pLabelTop->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Top", nullptr));
        m_pBtnTop->setText(QString());
        m_pLabelBot->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Bottom", nullptr));
        m_pBtnBot->setText(QString());
        m_pGroupBoxInversion->setTitle(QCoreApplication::translate("Page3TermAvoInversionThree", "Inversion Output Options", nullptr));
        m_pRadioZpZsRho->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Zp-Zs-\317\201", nullptr));
        m_pRadioZpVpVsRho->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Zp-VpVs-\317\201", nullptr));
        m_pRadioVpVsRho->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Vp-Vs-\317\201", nullptr));
        m_pRadioReflectivity->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Reflectivities", nullptr));
        m_pRadioSeismic->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Simulated Seismic Data", nullptr));
        m_pGroupBoxPrior->setTitle(QCoreApplication::translate("Page3TermAvoInversionThree", "Prior Output Options", nullptr));
        m_pCheckBoxPrior->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Prior Synthetics", nullptr));
        m_pRadioAki->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Aki && Richards", nullptr));
        m_pRadioZoeppritz->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "Zoeppritz", nullptr));
        label->setText(QCoreApplication::translate("Page3TermAvoInversionThree", "CPU Number for Computation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Page3TermAvoInversionThree: public Ui_Page3TermAvoInversionThree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGE3TERMAVOINVERSIONTHREE_H
