/********************************************************************************
** Form generated from reading UI file 'xpage3termavoinversiontwo.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGE3TERMAVOINVERSIONTWO_H
#define UI_XPAGE3TERMAVOINVERSIONTWO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Page3TermAvoInversionTwo
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QLabel *label;
    QToolButton *m_pBtnSelectZp;
    QLineEdit *m_pLineEdtZp;
    QLabel *label_2;
    QToolButton *m_pBtnSelectZs;
    QLineEdit *m_pLineEdtZs;
    QLabel *label_3;
    QToolButton *m_pBtnSelectRho;
    QLineEdit *m_pLineEdtRho;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QLineEdit *m_pLineEdtTol;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QLineEdit *m_pLineEdtMaxLoopNum;
    QLabel *label_10;
    QLineEdit *m_pLineEdtLamda;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_9;
    QLineEdit *m_pLineEdtBeta;
    QLabel *m_pLabelRDistri;
    QLineEdit *m_pLineEdtSigma;
    QSpacerItem *horizontalSpacer_4;
    QLabel *m_pLabelRWeight;
    QLineEdit *m_pLineEdtAlpha;
    QLineEdit *m_pLineEdtGamma;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QToolButton *m_pBtnAdvanced;
    QGroupBox *m_pGroupBoxFiltering;
    QGridLayout *gridLayout_3;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_15;
    QLabel *label_13;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *m_pLineEdtHighCut;
    QLineEdit *m_pLineEdtLowOverlap;
    QLineEdit *m_pLineEdtLowCut;
    QLineEdit *m_pLineEdtHighOverlap;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Page3TermAvoInversionTwo)
    {
        if (Page3TermAvoInversionTwo->objectName().isEmpty())
            Page3TermAvoInversionTwo->setObjectName(QString::fromUtf8("Page3TermAvoInversionTwo"));
        Page3TermAvoInversionTwo->resize(798, 365);
        gridLayout_4 = new QGridLayout(Page3TermAvoInversionTwo);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 15);
        label = new QLabel(Page3TermAvoInversionTwo);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_pBtnSelectZp = new QToolButton(Page3TermAvoInversionTwo);
        m_pBtnSelectZp->setObjectName(QString::fromUtf8("m_pBtnSelectZp"));
        m_pBtnSelectZp->setMinimumSize(QSize(30, 0));
        m_pBtnSelectZp->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnSelectZp->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectZp, 0, 1, 1, 1);

        m_pLineEdtZp = new QLineEdit(Page3TermAvoInversionTwo);
        m_pLineEdtZp->setObjectName(QString::fromUtf8("m_pLineEdtZp"));
        m_pLineEdtZp->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtZp, 0, 2, 1, 1);

        label_2 = new QLabel(Page3TermAvoInversionTwo);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        m_pBtnSelectZs = new QToolButton(Page3TermAvoInversionTwo);
        m_pBtnSelectZs->setObjectName(QString::fromUtf8("m_pBtnSelectZs"));
        m_pBtnSelectZs->setMinimumSize(QSize(30, 0));
        m_pBtnSelectZs->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectZs->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectZs, 1, 1, 1, 1);

        m_pLineEdtZs = new QLineEdit(Page3TermAvoInversionTwo);
        m_pLineEdtZs->setObjectName(QString::fromUtf8("m_pLineEdtZs"));
        m_pLineEdtZs->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtZs, 1, 2, 1, 1);

        label_3 = new QLabel(Page3TermAvoInversionTwo);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_pBtnSelectRho = new QToolButton(Page3TermAvoInversionTwo);
        m_pBtnSelectRho->setObjectName(QString::fromUtf8("m_pBtnSelectRho"));
        m_pBtnSelectRho->setMinimumSize(QSize(30, 0));
        m_pBtnSelectRho->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectRho->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectRho, 2, 1, 1, 1);

        m_pLineEdtRho = new QLineEdit(Page3TermAvoInversionTwo);
        m_pLineEdtRho->setObjectName(QString::fromUtf8("m_pLineEdtRho"));
        m_pLineEdtRho->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtRho, 2, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);

        groupBox = new QGroupBox(Page3TermAvoInversionTwo);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        m_pLineEdtTol = new QLineEdit(groupBox);
        m_pLineEdtTol->setObjectName(QString::fromUtf8("m_pLineEdtTol"));
        m_pLineEdtTol->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtTol, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(232, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 4, 1, 1);

        m_pLineEdtMaxLoopNum = new QLineEdit(groupBox);
        m_pLineEdtMaxLoopNum->setObjectName(QString::fromUtf8("m_pLineEdtMaxLoopNum"));
        m_pLineEdtMaxLoopNum->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtMaxLoopNum, 0, 5, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 2);

        m_pLineEdtLamda = new QLineEdit(groupBox);
        m_pLineEdtLamda->setObjectName(QString::fromUtf8("m_pLineEdtLamda"));
        m_pLineEdtLamda->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtLamda, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(226, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 4, 1, 1);

        m_pLineEdtBeta = new QLineEdit(groupBox);
        m_pLineEdtBeta->setObjectName(QString::fromUtf8("m_pLineEdtBeta"));
        m_pLineEdtBeta->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtBeta, 1, 5, 1, 1);

        m_pLabelRDistri = new QLabel(groupBox);
        m_pLabelRDistri->setObjectName(QString::fromUtf8("m_pLabelRDistri"));

        gridLayout_2->addWidget(m_pLabelRDistri, 2, 0, 1, 2);

        m_pLineEdtSigma = new QLineEdit(groupBox);
        m_pLineEdtSigma->setObjectName(QString::fromUtf8("m_pLineEdtSigma"));
        m_pLineEdtSigma->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtSigma, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(226, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 3, 1, 1);

        m_pLabelRWeight = new QLabel(groupBox);
        m_pLabelRWeight->setObjectName(QString::fromUtf8("m_pLabelRWeight"));

        gridLayout_2->addWidget(m_pLabelRWeight, 2, 4, 1, 1);

        m_pLineEdtAlpha = new QLineEdit(groupBox);
        m_pLineEdtAlpha->setObjectName(QString::fromUtf8("m_pLineEdtAlpha"));
        m_pLineEdtAlpha->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtAlpha, 2, 5, 1, 1);

        m_pLineEdtGamma = new QLineEdit(groupBox);
        m_pLineEdtGamma->setObjectName(QString::fromUtf8("m_pLineEdtGamma"));
        m_pLineEdtGamma->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(m_pLineEdtGamma, 3, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(232, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 3, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        m_pBtnAdvanced = new QToolButton(groupBox);
        m_pBtnAdvanced->setObjectName(QString::fromUtf8("m_pBtnAdvanced"));

        gridLayout_2->addWidget(m_pBtnAdvanced, 3, 4, 1, 1);


        gridLayout_4->addWidget(groupBox, 1, 0, 1, 1);

        m_pGroupBoxFiltering = new QGroupBox(Page3TermAvoInversionTwo);
        m_pGroupBoxFiltering->setObjectName(QString::fromUtf8("m_pGroupBoxFiltering"));
        m_pGroupBoxFiltering->setCheckable(false);
        gridLayout_3 = new QGridLayout(m_pGroupBoxFiltering);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_16 = new QLabel(m_pGroupBoxFiltering);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(140, 0));

        gridLayout_3->addWidget(label_16, 1, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 1, 2, 1, 1);

        label_15 = new QLabel(m_pGroupBoxFiltering);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(120, 0));

        gridLayout_3->addWidget(label_15, 1, 0, 1, 1);

        label_13 = new QLabel(m_pGroupBoxFiltering);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(120, 0));

        gridLayout_3->addWidget(label_13, 0, 0, 1, 1);

        label_14 = new QLabel(m_pGroupBoxFiltering);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(140, 0));

        gridLayout_3->addWidget(label_14, 0, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        m_pLineEdtHighCut = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtHighCut->setObjectName(QString::fromUtf8("m_pLineEdtHighCut"));
        m_pLineEdtHighCut->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(m_pLineEdtHighCut, 1, 1, 1, 1);

        m_pLineEdtLowOverlap = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtLowOverlap->setObjectName(QString::fromUtf8("m_pLineEdtLowOverlap"));
        m_pLineEdtLowOverlap->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(m_pLineEdtLowOverlap, 0, 4, 1, 1);

        m_pLineEdtLowCut = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtLowCut->setObjectName(QString::fromUtf8("m_pLineEdtLowCut"));
        m_pLineEdtLowCut->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(m_pLineEdtLowCut, 0, 1, 1, 1);

        m_pLineEdtHighOverlap = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtHighOverlap->setObjectName(QString::fromUtf8("m_pLineEdtHighOverlap"));
        m_pLineEdtHighOverlap->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(m_pLineEdtHighOverlap, 1, 4, 1, 1);


        gridLayout_4->addWidget(m_pGroupBoxFiltering, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 117, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 3, 0, 1, 1);


        retranslateUi(Page3TermAvoInversionTwo);

        QMetaObject::connectSlotsByName(Page3TermAvoInversionTwo);
    } // setupUi

    void retranslateUi(QWidget *Page3TermAvoInversionTwo)
    {
        Page3TermAvoInversionTwo->setWindowTitle(QCoreApplication::translate("Page3TermAvoInversionTwo", "Form", nullptr));
        label->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Select P-Impedance Data Volume", nullptr));
        m_pBtnSelectZp->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "...", nullptr));
        label_2->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Select S-Impedance Data Volume", nullptr));
        m_pBtnSelectZs->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "...", nullptr));
        label_3->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Select Density Data Volume", nullptr));
        m_pBtnSelectRho->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "...", nullptr));
#if QT_CONFIG(whatsthis)
        groupBox->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        groupBox->setTitle(QCoreApplication::translate("Page3TermAvoInversionTwo", "Inversion Parameters", nullptr));
        label_7->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Tolerance", nullptr));
#if QT_CONFIG(tooltip)
        m_pLineEdtTol->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        m_pLineEdtTol->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        m_pLineEdtTol->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "0.0001", nullptr));
        label_5->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Max. Iteration Number     ", nullptr));
        m_pLineEdtMaxLoopNum->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "20", nullptr));
        label_10->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Seismic Weight Factor        ", nullptr));
#if QT_CONFIG(whatsthis)
        m_pLineEdtLamda->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        m_pLineEdtLamda->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "1.0", nullptr));
        label_9->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Model Weight Factor", nullptr));
        m_pLineEdtBeta->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "0", nullptr));
        m_pLabelRDistri->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "R Distribution Factor", nullptr));
        m_pLineEdtSigma->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "1.0", nullptr));
        m_pLabelRWeight->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "R Weight Factor", nullptr));
        m_pLineEdtAlpha->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "0.05", nullptr));
        m_pLineEdtGamma->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "0.5", nullptr));
        label_4->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Gamma", nullptr));
        m_pBtnAdvanced->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Advanced", nullptr));
        m_pGroupBoxFiltering->setTitle(QCoreApplication::translate("Page3TermAvoInversionTwo", "Filtering Options", nullptr));
        label_16->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "High Overlap Frequency", nullptr));
        label_15->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "High Cut Frequency    ", nullptr));
        label_13->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Low Cut Frequency                ", nullptr));
        label_14->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "Low Overlap Frequency         ", nullptr));
        m_pLineEdtHighCut->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "60", nullptr));
        m_pLineEdtLowOverlap->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "2", nullptr));
        m_pLineEdtLowCut->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "7", nullptr));
        m_pLineEdtHighOverlap->setText(QCoreApplication::translate("Page3TermAvoInversionTwo", "5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Page3TermAvoInversionTwo: public Ui_Page3TermAvoInversionTwo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGE3TERMAVOINVERSIONTWO_H
