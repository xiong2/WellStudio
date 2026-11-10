/********************************************************************************
** Form generated from reading UI file 'xdlgavocssiadvanced.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGAVOCSSIADVANCED_H
#define UI_XDLGAVOCSSIADVANCED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgAVOCSSIAdvanced
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *m_pLabelRDistri;
    QLineEdit *m_pLineEdtDSigma;
    QLabel *m_pLabelRWeight_3;
    QLabel *m_pLabelRWeight_2;
    QLabel *m_pLabelRWeight;
    QSpacerItem *horizontalSpacer_5;
    QLabel *m_pLabelRDistri_2;
    QLineEdit *m_pLineEdtSSigma;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *m_pLineEdtSAlpha;
    QLineEdit *m_pLineEdtDAlpha;
    QLineEdit *m_pLineEdtPAlpha;
    QSpacerItem *horizontalSpacer_4;
    QLabel *m_pLabelRDistri_3;
    QLineEdit *m_pLineEdtPSigma;
    QLabel *label;
    QTableWidget *m_pTable;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgAVOCSSIAdvanced)
    {
        if (DlgAVOCSSIAdvanced->objectName().isEmpty())
            DlgAVOCSSIAdvanced->setObjectName(QString::fromUtf8("DlgAVOCSSIAdvanced"));
        DlgAVOCSSIAdvanced->resize(665, 401);
        gridLayout_2 = new QGridLayout(DlgAVOCSSIAdvanced);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(DlgAVOCSSIAdvanced);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 18);
        m_pLabelRDistri = new QLabel(groupBox);
        m_pLabelRDistri->setObjectName(QString::fromUtf8("m_pLabelRDistri"));
        m_pLabelRDistri->setMinimumSize(QSize(180, 0));

        gridLayout->addWidget(m_pLabelRDistri, 0, 0, 1, 1);

        m_pLineEdtDSigma = new QLineEdit(groupBox);
        m_pLineEdtDSigma->setObjectName(QString::fromUtf8("m_pLineEdtDSigma"));
        m_pLineEdtDSigma->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtDSigma, 2, 4, 1, 1);

        m_pLabelRWeight_3 = new QLabel(groupBox);
        m_pLabelRWeight_3->setObjectName(QString::fromUtf8("m_pLabelRWeight_3"));

        gridLayout->addWidget(m_pLabelRWeight_3, 2, 3, 1, 1);

        m_pLabelRWeight_2 = new QLabel(groupBox);
        m_pLabelRWeight_2->setObjectName(QString::fromUtf8("m_pLabelRWeight_2"));

        gridLayout->addWidget(m_pLabelRWeight_2, 1, 3, 1, 1);

        m_pLabelRWeight = new QLabel(groupBox);
        m_pLabelRWeight->setObjectName(QString::fromUtf8("m_pLabelRWeight"));
        m_pLabelRWeight->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(m_pLabelRWeight, 0, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(86, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 2, 1, 1);

        m_pLabelRDistri_2 = new QLabel(groupBox);
        m_pLabelRDistri_2->setObjectName(QString::fromUtf8("m_pLabelRDistri_2"));

        gridLayout->addWidget(m_pLabelRDistri_2, 1, 0, 1, 1);

        m_pLineEdtSSigma = new QLineEdit(groupBox);
        m_pLineEdtSSigma->setObjectName(QString::fromUtf8("m_pLineEdtSSigma"));
        m_pLineEdtSSigma->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtSSigma, 1, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(86, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 2, 2, 1, 1);

        m_pLineEdtSAlpha = new QLineEdit(groupBox);
        m_pLineEdtSAlpha->setObjectName(QString::fromUtf8("m_pLineEdtSAlpha"));
        m_pLineEdtSAlpha->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtSAlpha, 1, 1, 1, 1);

        m_pLineEdtDAlpha = new QLineEdit(groupBox);
        m_pLineEdtDAlpha->setObjectName(QString::fromUtf8("m_pLineEdtDAlpha"));
        m_pLineEdtDAlpha->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtDAlpha, 2, 1, 1, 1);

        m_pLineEdtPAlpha = new QLineEdit(groupBox);
        m_pLineEdtPAlpha->setObjectName(QString::fromUtf8("m_pLineEdtPAlpha"));
        m_pLineEdtPAlpha->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtPAlpha, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(86, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        m_pLabelRDistri_3 = new QLabel(groupBox);
        m_pLabelRDistri_3->setObjectName(QString::fromUtf8("m_pLabelRDistri_3"));

        gridLayout->addWidget(m_pLabelRDistri_3, 2, 0, 1, 1);

        m_pLineEdtPSigma = new QLineEdit(groupBox);
        m_pLineEdtPSigma->setObjectName(QString::fromUtf8("m_pLineEdtPSigma"));
        m_pLineEdtPSigma->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtPSigma, 0, 4, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 2);

        label = new QLabel(DlgAVOCSSIAdvanced);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        m_pTable = new QTableWidget(DlgAVOCSSIAdvanced);
        if (m_pTable->columnCount() < 3)
            m_pTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        m_pTable->setObjectName(QString::fromUtf8("m_pTable"));
        m_pTable->horizontalHeader()->setCascadingSectionResizes(false);
        m_pTable->horizontalHeader()->setMinimumSectionSize(100);
        m_pTable->horizontalHeader()->setDefaultSectionSize(180);
        m_pTable->horizontalHeader()->setStretchLastSection(true);
        m_pTable->verticalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(m_pTable, 2, 0, 1, 2);

        buttonBox = new QDialogButtonBox(DlgAVOCSSIAdvanced);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 3, 1, 1, 1);


        retranslateUi(DlgAVOCSSIAdvanced);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgAVOCSSIAdvanced, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgAVOCSSIAdvanced, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgAVOCSSIAdvanced);
    } // setupUi

    void retranslateUi(QDialog *DlgAVOCSSIAdvanced)
    {
        DlgAVOCSSIAdvanced->setWindowTitle(QCoreApplication::translate("DlgAVOCSSIAdvanced", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgAVOCSSIAdvanced", "Sparse Spike Parameters", nullptr));
        m_pLabelRDistri->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "P-Impedance Weight Factor", nullptr));
        m_pLineEdtDSigma->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "1", nullptr));
        m_pLabelRWeight_3->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "Density Distribution Factor", nullptr));
        m_pLabelRWeight_2->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "S-Impedance Distribution Factor", nullptr));
        m_pLabelRWeight->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "P-Impedance Distribution Factor", nullptr));
        m_pLabelRDistri_2->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "S-Impedance Weight Factor", nullptr));
        m_pLineEdtSSigma->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "1", nullptr));
        m_pLineEdtSAlpha->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "0.05", nullptr));
        m_pLineEdtDAlpha->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "0.05", nullptr));
        m_pLineEdtPAlpha->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "0.05", nullptr));
        m_pLabelRDistri_3->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "Density Weight Factor", nullptr));
        m_pLineEdtPSigma->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "1", nullptr));
        label->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "Parametes for each individual seismic data:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "Seismic Weight Factor", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_pTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DlgAVOCSSIAdvanced", "Wavelet Scale Factor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgAVOCSSIAdvanced: public Ui_DlgAVOCSSIAdvanced {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGAVOCSSIADVANCED_H
