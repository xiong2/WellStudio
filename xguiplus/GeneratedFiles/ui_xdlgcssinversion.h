/********************************************************************************
** Form generated from reading UI file 'xdlgcssinversion.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGCSSINVERSION_H
#define UI_XDLGCSSINVERSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DlgCSSInversion
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QLineEdit *m_pLineEdtTol;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_6;
    QLineEdit *m_pLineEdtMaxLoopNum;
    QLabel *label_10;
    QLineEdit *m_pLineEdtBeta;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLabel *label_7;
    QLineEdit *m_pLineEdtSigma;
    QSpacerItem *horizontalSpacer;
    QLabel *label_9;
    QLineEdit *m_pLineEdtMu;
    QLabel *label_11;
    QLineEdit *m_pLineEdtWaveletFactor;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *m_pLineEdtAlpha;
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
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgCSSInversion)
    {
        if (DlgCSSInversion->objectName().isEmpty())
            DlgCSSInversion->setObjectName(QString::fromUtf8("DlgCSSInversion"));
        DlgCSSInversion->resize(703, 305);
        gridLayout_2 = new QGridLayout(DlgCSSInversion);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        groupBox = new QGroupBox(DlgCSSInversion);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        m_pLineEdtTol = new QLineEdit(groupBox);
        m_pLineEdtTol->setObjectName(QString::fromUtf8("m_pLineEdtTol"));
        m_pLineEdtTol->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtTol, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(232, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(130, 0));

        gridLayout->addWidget(label_6, 0, 3, 1, 1);

        m_pLineEdtMaxLoopNum = new QLineEdit(groupBox);
        m_pLineEdtMaxLoopNum->setObjectName(QString::fromUtf8("m_pLineEdtMaxLoopNum"));
        m_pLineEdtMaxLoopNum->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtMaxLoopNum, 0, 4, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(130, 0));

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        m_pLineEdtBeta = new QLineEdit(groupBox);
        m_pLineEdtBeta->setObjectName(QString::fromUtf8("m_pLineEdtBeta"));
        m_pLineEdtBeta->setMinimumSize(QSize(80, 0));
        m_pLineEdtBeta->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtBeta, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(177, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(label_4, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(130, 0));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        m_pLineEdtSigma = new QLineEdit(groupBox);
        m_pLineEdtSigma->setObjectName(QString::fromUtf8("m_pLineEdtSigma"));
        m_pLineEdtSigma->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtSigma, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(232, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(label_9, 2, 3, 1, 1);

        m_pLineEdtMu = new QLineEdit(groupBox);
        m_pLineEdtMu->setObjectName(QString::fromUtf8("m_pLineEdtMu"));
        m_pLineEdtMu->setMinimumSize(QSize(80, 0));
        m_pLineEdtMu->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtMu, 2, 4, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(90, 0));

        gridLayout->addWidget(label_11, 3, 0, 1, 1);

        m_pLineEdtWaveletFactor = new QLineEdit(groupBox);
        m_pLineEdtWaveletFactor->setObjectName(QString::fromUtf8("m_pLineEdtWaveletFactor"));
        m_pLineEdtWaveletFactor->setMinimumSize(QSize(80, 0));
        m_pLineEdtWaveletFactor->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtWaveletFactor, 3, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(395, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 2, 1, 2);

        m_pLineEdtAlpha = new QLineEdit(groupBox);
        m_pLineEdtAlpha->setObjectName(QString::fromUtf8("m_pLineEdtAlpha"));
        m_pLineEdtAlpha->setMinimumSize(QSize(80, 0));
        m_pLineEdtAlpha->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtAlpha, 1, 4, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        m_pGroupBoxFiltering = new QGroupBox(DlgCSSInversion);
        m_pGroupBoxFiltering->setObjectName(QString::fromUtf8("m_pGroupBoxFiltering"));
        m_pGroupBoxFiltering->setCheckable(false);
        gridLayout_3 = new QGridLayout(m_pGroupBoxFiltering);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_16 = new QLabel(m_pGroupBoxFiltering);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(140, 0));

        gridLayout_3->addWidget(label_16, 1, 3, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(247, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

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

        horizontalSpacer_5 = new QSpacerItem(247, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

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


        gridLayout_2->addWidget(m_pGroupBoxFiltering, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DlgCSSInversion);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 3, 0, 1, 1);


        retranslateUi(DlgCSSInversion);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgCSSInversion, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgCSSInversion, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgCSSInversion);
    } // setupUi

    void retranslateUi(QDialog *DlgCSSInversion)
    {
        DlgCSSInversion->setWindowTitle(QCoreApplication::translate("DlgCSSInversion", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgCSSInversion", "Inversion Parameters", nullptr));
        label_8->setText(QCoreApplication::translate("DlgCSSInversion", "Tolerance", nullptr));
        m_pLineEdtTol->setText(QCoreApplication::translate("DlgCSSInversion", "0.00001", nullptr));
        label_6->setText(QCoreApplication::translate("DlgCSSInversion", "Max. Iteration Number           ", nullptr));
        m_pLineEdtMaxLoopNum->setText(QCoreApplication::translate("DlgCSSInversion", "20", nullptr));
#if QT_CONFIG(tooltip)
        label_10->setToolTip(QCoreApplication::translate("DlgCSSInversion", "Seismic factor", nullptr));
#endif // QT_CONFIG(tooltip)
        label_10->setText(QCoreApplication::translate("DlgCSSInversion", "Seismic Weight Factor           ", nullptr));
        m_pLineEdtBeta->setText(QCoreApplication::translate("DlgCSSInversion", "1.0", nullptr));
#if QT_CONFIG(tooltip)
        label_4->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("DlgCSSInversion", "Model Weight Factor", nullptr));
#if QT_CONFIG(tooltip)
        label_7->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_7->setText(QCoreApplication::translate("DlgCSSInversion", "R Distribution Factor   ", nullptr));
        m_pLineEdtSigma->setText(QCoreApplication::translate("DlgCSSInversion", "1.0", nullptr));
#if QT_CONFIG(tooltip)
        label_9->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_9->setText(QCoreApplication::translate("DlgCSSInversion", "R Weight Factor", nullptr));
        m_pLineEdtMu->setText(QCoreApplication::translate("DlgCSSInversion", "2", nullptr));
        label_11->setText(QCoreApplication::translate("DlgCSSInversion", "Wavelet Factor", nullptr));
        m_pLineEdtWaveletFactor->setText(QCoreApplication::translate("DlgCSSInversion", "1.0", nullptr));
        m_pLineEdtAlpha->setText(QCoreApplication::translate("DlgCSSInversion", "0.1", nullptr));
        m_pGroupBoxFiltering->setTitle(QCoreApplication::translate("DlgCSSInversion", "Filtering Options", nullptr));
        label_16->setText(QCoreApplication::translate("DlgCSSInversion", "High Overlap Frequency", nullptr));
        label_15->setText(QCoreApplication::translate("DlgCSSInversion", "High Cut Frequency", nullptr));
        label_13->setText(QCoreApplication::translate("DlgCSSInversion", "Low Cut Frequency         ", nullptr));
        label_14->setText(QCoreApplication::translate("DlgCSSInversion", "Low Overlap Frequency      ", nullptr));
        m_pLineEdtHighCut->setText(QCoreApplication::translate("DlgCSSInversion", "60", nullptr));
        m_pLineEdtLowOverlap->setText(QCoreApplication::translate("DlgCSSInversion", "2", nullptr));
        m_pLineEdtLowCut->setText(QCoreApplication::translate("DlgCSSInversion", "7", nullptr));
        m_pLineEdtHighOverlap->setText(QCoreApplication::translate("DlgCSSInversion", "5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgCSSInversion: public Ui_DlgCSSInversion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGCSSINVERSION_H
