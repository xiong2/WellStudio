/********************************************************************************
** Form generated from reading UI file 'xparapageavoinversion.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPARAPAGEAVOINVERSION_H
#define UI_XPARAPAGEAVOINVERSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParaPageAvoInversion
{
public:
    QGridLayout *gridLayout_4;
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
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *m_pLineEdtZs;
    QLineEdit *m_pLineEdtRho;
    QLineEdit *m_pLineEdtZp;
    QTableWidget *m_pTable;

    void setupUi(QWidget *ParaPageAvoInversion)
    {
        if (ParaPageAvoInversion->objectName().isEmpty())
            ParaPageAvoInversion->setObjectName(QString::fromUtf8("ParaPageAvoInversion"));
        ParaPageAvoInversion->resize(794, 574);
        gridLayout_4 = new QGridLayout(ParaPageAvoInversion);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(ParaPageAvoInversion);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        m_pLineEdtTol = new QLineEdit(groupBox);
        m_pLineEdtTol->setObjectName(QString::fromUtf8("m_pLineEdtTol"));
        m_pLineEdtTol->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtTol->setReadOnly(true);

        gridLayout_2->addWidget(m_pLineEdtTol, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(232, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 4, 1, 1);

        m_pLineEdtMaxLoopNum = new QLineEdit(groupBox);
        m_pLineEdtMaxLoopNum->setObjectName(QString::fromUtf8("m_pLineEdtMaxLoopNum"));
        m_pLineEdtMaxLoopNum->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtMaxLoopNum->setReadOnly(true);

        gridLayout_2->addWidget(m_pLineEdtMaxLoopNum, 0, 5, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 0, 1, 2);

        m_pLineEdtLamda = new QLineEdit(groupBox);
        m_pLineEdtLamda->setObjectName(QString::fromUtf8("m_pLineEdtLamda"));
        m_pLineEdtLamda->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtLamda->setReadOnly(true);

        gridLayout_2->addWidget(m_pLineEdtLamda, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(226, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 4, 1, 1);

        m_pLineEdtBeta = new QLineEdit(groupBox);
        m_pLineEdtBeta->setObjectName(QString::fromUtf8("m_pLineEdtBeta"));
        m_pLineEdtBeta->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtBeta->setReadOnly(true);

        gridLayout_2->addWidget(m_pLineEdtBeta, 1, 5, 1, 1);

        m_pLabelRDistri = new QLabel(groupBox);
        m_pLabelRDistri->setObjectName(QString::fromUtf8("m_pLabelRDistri"));

        gridLayout_2->addWidget(m_pLabelRDistri, 2, 0, 1, 2);

        m_pLineEdtSigma = new QLineEdit(groupBox);
        m_pLineEdtSigma->setObjectName(QString::fromUtf8("m_pLineEdtSigma"));
        m_pLineEdtSigma->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtSigma->setReadOnly(true);

        gridLayout_2->addWidget(m_pLineEdtSigma, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(226, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 3, 1, 1);

        m_pLabelRWeight = new QLabel(groupBox);
        m_pLabelRWeight->setObjectName(QString::fromUtf8("m_pLabelRWeight"));

        gridLayout_2->addWidget(m_pLabelRWeight, 2, 4, 1, 1);

        m_pLineEdtAlpha = new QLineEdit(groupBox);
        m_pLineEdtAlpha->setObjectName(QString::fromUtf8("m_pLineEdtAlpha"));
        m_pLineEdtAlpha->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtAlpha->setReadOnly(true);

        gridLayout_2->addWidget(m_pLineEdtAlpha, 2, 5, 1, 1);

        m_pLineEdtGamma = new QLineEdit(groupBox);
        m_pLineEdtGamma->setObjectName(QString::fromUtf8("m_pLineEdtGamma"));
        m_pLineEdtGamma->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtGamma->setReadOnly(true);

        gridLayout_2->addWidget(m_pLineEdtGamma, 3, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(232, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 3, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        m_pGroupBoxFiltering = new QGroupBox(ParaPageAvoInversion);
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
        m_pLineEdtHighCut->setReadOnly(true);
        m_pLineEdtHighCut->setClearButtonEnabled(false);

        gridLayout_3->addWidget(m_pLineEdtHighCut, 1, 1, 1, 1);

        m_pLineEdtLowOverlap = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtLowOverlap->setObjectName(QString::fromUtf8("m_pLineEdtLowOverlap"));
        m_pLineEdtLowOverlap->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtLowOverlap->setReadOnly(true);
        m_pLineEdtLowOverlap->setClearButtonEnabled(false);

        gridLayout_3->addWidget(m_pLineEdtLowOverlap, 0, 4, 1, 1);

        m_pLineEdtLowCut = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtLowCut->setObjectName(QString::fromUtf8("m_pLineEdtLowCut"));
        m_pLineEdtLowCut->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtLowCut->setReadOnly(true);
        m_pLineEdtLowCut->setClearButtonEnabled(false);

        gridLayout_3->addWidget(m_pLineEdtLowCut, 0, 1, 1, 1);

        m_pLineEdtHighOverlap = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtHighOverlap->setObjectName(QString::fromUtf8("m_pLineEdtHighOverlap"));
        m_pLineEdtHighOverlap->setMaximumSize(QSize(80, 16777215));
        m_pLineEdtHighOverlap->setReadOnly(true);
        m_pLineEdtHighOverlap->setClearButtonEnabled(false);

        gridLayout_3->addWidget(m_pLineEdtHighOverlap, 1, 4, 1, 1);


        gridLayout_4->addWidget(m_pGroupBoxFiltering, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 15);
        label_2 = new QLabel(ParaPageAvoInversion);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(ParaPageAvoInversion);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(ParaPageAvoInversion);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_pLineEdtZs = new QLineEdit(ParaPageAvoInversion);
        m_pLineEdtZs->setObjectName(QString::fromUtf8("m_pLineEdtZs"));
        m_pLineEdtZs->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtZs, 1, 1, 1, 1);

        m_pLineEdtRho = new QLineEdit(ParaPageAvoInversion);
        m_pLineEdtRho->setObjectName(QString::fromUtf8("m_pLineEdtRho"));
        m_pLineEdtRho->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtRho, 2, 1, 1, 1);

        m_pLineEdtZp = new QLineEdit(ParaPageAvoInversion);
        m_pLineEdtZp->setObjectName(QString::fromUtf8("m_pLineEdtZp"));
        m_pLineEdtZp->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtZp, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout, 2, 0, 1, 1);

        m_pTable = new QTableWidget(ParaPageAvoInversion);
        if (m_pTable->columnCount() < 3)
            m_pTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        m_pTable->setObjectName(QString::fromUtf8("m_pTable"));
        m_pTable->setMinimumSize(QSize(0, 100));
        m_pTable->setMaximumSize(QSize(16777215, 16777215));
        m_pTable->horizontalHeader()->setDefaultSectionSize(150);
        m_pTable->horizontalHeader()->setStretchLastSection(true);
        m_pTable->verticalHeader()->setCascadingSectionResizes(false);

        gridLayout_4->addWidget(m_pTable, 3, 0, 1, 1);


        retranslateUi(ParaPageAvoInversion);

        QMetaObject::connectSlotsByName(ParaPageAvoInversion);
    } // setupUi

    void retranslateUi(QWidget *ParaPageAvoInversion)
    {
        ParaPageAvoInversion->setWindowTitle(QCoreApplication::translate("ParaPageAvoInversion", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ParaPageAvoInversion", "Inversion Parameters", nullptr));
        label_7->setText(QCoreApplication::translate("ParaPageAvoInversion", "Tolerance", nullptr));
        m_pLineEdtTol->setText(QCoreApplication::translate("ParaPageAvoInversion", "0.0001", nullptr));
        label_5->setText(QCoreApplication::translate("ParaPageAvoInversion", "Max. Iteration Number     ", nullptr));
        m_pLineEdtMaxLoopNum->setText(QCoreApplication::translate("ParaPageAvoInversion", "20", nullptr));
        label_10->setText(QCoreApplication::translate("ParaPageAvoInversion", "Seismic Weight Factor        ", nullptr));
        m_pLineEdtLamda->setText(QCoreApplication::translate("ParaPageAvoInversion", "1.0", nullptr));
        label_9->setText(QCoreApplication::translate("ParaPageAvoInversion", "Model Weight Factor", nullptr));
        m_pLineEdtBeta->setText(QCoreApplication::translate("ParaPageAvoInversion", "1", nullptr));
        m_pLabelRDistri->setText(QCoreApplication::translate("ParaPageAvoInversion", "R Distribution Factor", nullptr));
        m_pLineEdtSigma->setText(QCoreApplication::translate("ParaPageAvoInversion", "1.0", nullptr));
        m_pLabelRWeight->setText(QCoreApplication::translate("ParaPageAvoInversion", "R Weight Factor", nullptr));
        m_pLineEdtAlpha->setText(QCoreApplication::translate("ParaPageAvoInversion", "1", nullptr));
        m_pLineEdtGamma->setText(QCoreApplication::translate("ParaPageAvoInversion", "0.5", nullptr));
        label_4->setText(QCoreApplication::translate("ParaPageAvoInversion", "Gamma", nullptr));
        m_pGroupBoxFiltering->setTitle(QCoreApplication::translate("ParaPageAvoInversion", "Filtering Options", nullptr));
        label_16->setText(QCoreApplication::translate("ParaPageAvoInversion", "High Overlap Frequency", nullptr));
        label_15->setText(QCoreApplication::translate("ParaPageAvoInversion", "High Cut Frequency    ", nullptr));
        label_13->setText(QCoreApplication::translate("ParaPageAvoInversion", "Low Cut Frequency                ", nullptr));
        label_14->setText(QCoreApplication::translate("ParaPageAvoInversion", "Low Overlap Frequency         ", nullptr));
        m_pLineEdtHighCut->setText(QCoreApplication::translate("ParaPageAvoInversion", "60", nullptr));
        m_pLineEdtLowOverlap->setText(QCoreApplication::translate("ParaPageAvoInversion", "2", nullptr));
        m_pLineEdtLowCut->setText(QCoreApplication::translate("ParaPageAvoInversion", "5", nullptr));
        m_pLineEdtHighOverlap->setText(QCoreApplication::translate("ParaPageAvoInversion", "5", nullptr));
        label_2->setText(QCoreApplication::translate("ParaPageAvoInversion", "Select S-Impedance Data Volume", nullptr));
        label->setText(QCoreApplication::translate("ParaPageAvoInversion", "Select P-Impedance Data Volume", nullptr));
        label_3->setText(QCoreApplication::translate("ParaPageAvoInversion", "Select Density Data Volume", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ParaPageAvoInversion", "Seismic Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ParaPageAvoInversion", "Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_pTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ParaPageAvoInversion", "Wavelet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParaPageAvoInversion: public Ui_ParaPageAvoInversion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPARAPAGEAVOINVERSION_H
