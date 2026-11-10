/********************************************************************************
** Form generated from reading UI file 'xdlgimportwavelet.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGIMPORTWAVELET_H
#define UI_XDLGIMPORTWAVELET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDlgRLImportWavelet
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *m_pEdtFileName;
    QPushButton *m_pBtnSelect;
    QLabel *label_3;
    QLineEdit *m_pEdtName;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLineEdit *m_pEdtLineToSkip;
    QLabel *label_5;
    QLineEdit *m_pEdtSampleCount;
    QLabel *label_6;
    QLineEdit *m_pEdtStep;
    QLabel *label_7;
    QLineEdit *m_pEdtTimeZero;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pBtnImport;
    QPushButton *m_pBtnCancel;
    QTextBrowser *m_pTextBrowser;

    void setupUi(QWidget *CDlgRLImportWavelet)
    {
        if (CDlgRLImportWavelet->objectName().isEmpty())
            CDlgRLImportWavelet->setObjectName(QString::fromUtf8("CDlgRLImportWavelet"));
        CDlgRLImportWavelet->resize(975, 519);
        horizontalLayout_2 = new QHBoxLayout(CDlgRLImportWavelet);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(CDlgRLImportWavelet);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        m_pEdtFileName = new QLineEdit(groupBox_2);
        m_pEdtFileName->setObjectName(QString::fromUtf8("m_pEdtFileName"));
        m_pEdtFileName->setReadOnly(true);

        gridLayout_2->addWidget(m_pEdtFileName, 0, 1, 1, 1);

        m_pBtnSelect = new QPushButton(groupBox_2);
        m_pBtnSelect->setObjectName(QString::fromUtf8("m_pBtnSelect"));

        gridLayout_2->addWidget(m_pBtnSelect, 0, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        m_pEdtName = new QLineEdit(groupBox_2);
        m_pEdtName->setObjectName(QString::fromUtf8("m_pEdtName"));
        m_pEdtName->setEnabled(false);

        gridLayout_2->addWidget(m_pEdtName, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(CDlgRLImportWavelet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        m_pEdtLineToSkip = new QLineEdit(groupBox);
        m_pEdtLineToSkip->setObjectName(QString::fromUtf8("m_pEdtLineToSkip"));
        m_pEdtLineToSkip->setEnabled(false);

        gridLayout->addWidget(m_pEdtLineToSkip, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_pEdtSampleCount = new QLineEdit(groupBox);
        m_pEdtSampleCount->setObjectName(QString::fromUtf8("m_pEdtSampleCount"));
        m_pEdtSampleCount->setEnabled(false);

        gridLayout->addWidget(m_pEdtSampleCount, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        m_pEdtStep = new QLineEdit(groupBox);
        m_pEdtStep->setObjectName(QString::fromUtf8("m_pEdtStep"));
        m_pEdtStep->setEnabled(false);

        gridLayout->addWidget(m_pEdtStep, 2, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 2);

        m_pEdtTimeZero = new QLineEdit(groupBox);
        m_pEdtTimeZero->setObjectName(QString::fromUtf8("m_pEdtTimeZero"));
        m_pEdtTimeZero->setEnabled(false);

        gridLayout->addWidget(m_pEdtTimeZero, 4, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_pBtnImport = new QPushButton(CDlgRLImportWavelet);
        m_pBtnImport->setObjectName(QString::fromUtf8("m_pBtnImport"));
        m_pBtnImport->setEnabled(false);

        horizontalLayout->addWidget(m_pBtnImport);

        m_pBtnCancel = new QPushButton(CDlgRLImportWavelet);
        m_pBtnCancel->setObjectName(QString::fromUtf8("m_pBtnCancel"));

        horizontalLayout->addWidget(m_pBtnCancel);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        m_pTextBrowser = new QTextBrowser(CDlgRLImportWavelet);
        m_pTextBrowser->setObjectName(QString::fromUtf8("m_pTextBrowser"));

        horizontalLayout_2->addWidget(m_pTextBrowser);


        retranslateUi(CDlgRLImportWavelet);

        QMetaObject::connectSlotsByName(CDlgRLImportWavelet);
    } // setupUi

    void retranslateUi(QWidget *CDlgRLImportWavelet)
    {
        CDlgRLImportWavelet->setWindowTitle(QCoreApplication::translate("CDlgRLImportWavelet", "Import Wavelet", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CDlgRLImportWavelet", "File", nullptr));
        label->setText(QCoreApplication::translate("CDlgRLImportWavelet", "File:", nullptr));
        m_pBtnSelect->setText(QCoreApplication::translate("CDlgRLImportWavelet", "Select", nullptr));
        label_3->setText(QCoreApplication::translate("CDlgRLImportWavelet", "Name:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CDlgRLImportWavelet", "Parameters", nullptr));
        label_4->setText(QCoreApplication::translate("CDlgRLImportWavelet", "Lines to skip:", nullptr));
        m_pEdtLineToSkip->setText(QString());
        label_5->setText(QCoreApplication::translate("CDlgRLImportWavelet", "Number of samples:", nullptr));
        label_6->setText(QCoreApplication::translate("CDlgRLImportWavelet", "Sample rate(ms):", nullptr));
        m_pEdtStep->setText(QString());
        label_7->setText(QCoreApplication::translate("CDlgRLImportWavelet", "Time zero location (count from the first sample):)", nullptr));
        m_pBtnImport->setText(QCoreApplication::translate("CDlgRLImportWavelet", "Import", nullptr));
        m_pBtnCancel->setText(QCoreApplication::translate("CDlgRLImportWavelet", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CDlgRLImportWavelet: public Ui_CDlgRLImportWavelet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGIMPORTWAVELET_H
