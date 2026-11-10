/********************************************************************************
** Form generated from reading UI file 'xpagegsinversion1.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEGSINVERSION1_H
#define UI_XPAGEGSINVERSION1_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWizardPage>
#include "xslidercomplex.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageGSInversion1
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidgetSM;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidgetWells;
    QLabel *label_2;
    QComboBox *comboBoxDiscrete;
    QLabel *label_3;
    QComboBox *comboBoxContinuous;
    QLabel *labelContinuousLog1;
    QComboBox *comboBoxContinuousLog1;
    QLabel *labelContinuousLog2;
    QComboBox *comboBoxContinuousLog2;
    QLabel *labelContinuousLog3;
    QComboBox *comboBoxContinuousLog3;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QLabel *labelNumBins;
    QSpinBox *spinBox;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *pushButtonQCSection;
    QLabel *label;
    QLineEdit *lineEditQCSection;
    CXSliderComplex *inlineRange;
    CXSliderComplex *crosslineRange;

    void setupUi(QWizardPage *CXPageGSInversion1)
    {
        if (CXPageGSInversion1->objectName().isEmpty())
            CXPageGSInversion1->setObjectName(QString::fromUtf8("CXPageGSInversion1"));
        CXPageGSInversion1->resize(894, 447);
        gridLayout_3 = new QGridLayout(CXPageGSInversion1);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(CXPageGSInversion1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidgetSM = new QTableWidget(groupBox);
        if (tableWidgetSM->columnCount() < 3)
            tableWidgetSM->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetSM->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetSM->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetSM->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetSM->setObjectName(QString::fromUtf8("tableWidgetSM"));

        horizontalLayout->addWidget(tableWidgetSM);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(CXPageGSInversion1);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidgetWells = new QTableWidget(groupBox_3);
        if (tableWidgetWells->columnCount() < 2)
            tableWidgetWells->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tableWidgetWells->setObjectName(QString::fromUtf8("tableWidgetWells"));

        gridLayout_2->addWidget(tableWidgetWells, 0, 0, 8, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 2);

        comboBoxDiscrete = new QComboBox(groupBox_3);
        comboBoxDiscrete->setObjectName(QString::fromUtf8("comboBoxDiscrete"));

        gridLayout_2->addWidget(comboBoxDiscrete, 0, 3, 1, 2);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 1, 1, 2);

        comboBoxContinuous = new QComboBox(groupBox_3);
        comboBoxContinuous->addItem(QString());
        comboBoxContinuous->addItem(QString());
        comboBoxContinuous->addItem(QString());
        comboBoxContinuous->setObjectName(QString::fromUtf8("comboBoxContinuous"));

        gridLayout_2->addWidget(comboBoxContinuous, 1, 3, 1, 2);

        labelContinuousLog1 = new QLabel(groupBox_3);
        labelContinuousLog1->setObjectName(QString::fromUtf8("labelContinuousLog1"));

        gridLayout_2->addWidget(labelContinuousLog1, 2, 1, 1, 1);

        comboBoxContinuousLog1 = new QComboBox(groupBox_3);
        comboBoxContinuousLog1->setObjectName(QString::fromUtf8("comboBoxContinuousLog1"));

        gridLayout_2->addWidget(comboBoxContinuousLog1, 2, 3, 1, 2);

        labelContinuousLog2 = new QLabel(groupBox_3);
        labelContinuousLog2->setObjectName(QString::fromUtf8("labelContinuousLog2"));

        gridLayout_2->addWidget(labelContinuousLog2, 3, 1, 1, 1);

        comboBoxContinuousLog2 = new QComboBox(groupBox_3);
        comboBoxContinuousLog2->setObjectName(QString::fromUtf8("comboBoxContinuousLog2"));

        gridLayout_2->addWidget(comboBoxContinuousLog2, 3, 3, 1, 2);

        labelContinuousLog3 = new QLabel(groupBox_3);
        labelContinuousLog3->setObjectName(QString::fromUtf8("labelContinuousLog3"));

        gridLayout_2->addWidget(labelContinuousLog3, 4, 1, 1, 1);

        comboBoxContinuousLog3 = new QComboBox(groupBox_3);
        comboBoxContinuousLog3->setObjectName(QString::fromUtf8("comboBoxContinuousLog3"));

        gridLayout_2->addWidget(comboBoxContinuousLog3, 4, 3, 1, 2);

        checkBox = new QCheckBox(groupBox_3);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setChecked(true);

        gridLayout_2->addWidget(checkBox, 5, 1, 1, 3);

        comboBox = new QComboBox(groupBox_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 5, 4, 1, 1);

        labelNumBins = new QLabel(groupBox_3);
        labelNumBins->setObjectName(QString::fromUtf8("labelNumBins"));
        labelNumBins->setEnabled(false);

        gridLayout_2->addWidget(labelNumBins, 6, 1, 1, 2);

        spinBox = new QSpinBox(groupBox_3);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setEnabled(false);
        spinBox->setMinimum(10);
        spinBox->setMaximum(50);
        spinBox->setValue(25);

        gridLayout_2->addWidget(spinBox, 6, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 211, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 7, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 0, 1, 2, 1);

        groupBox_2 = new QGroupBox(CXPageGSInversion1);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonQCSection = new QPushButton(groupBox_2);
        pushButtonQCSection->setObjectName(QString::fromUtf8("pushButtonQCSection"));
        pushButtonQCSection->setMinimumSize(QSize(40, 0));
        pushButtonQCSection->setMaximumSize(QSize(40, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonQCSection->setIcon(icon);

        gridLayout->addWidget(pushButtonQCSection, 2, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        lineEditQCSection = new QLineEdit(groupBox_2);
        lineEditQCSection->setObjectName(QString::fromUtf8("lineEditQCSection"));

        gridLayout->addWidget(lineEditQCSection, 2, 2, 1, 1);

        inlineRange = new CXSliderComplex(groupBox_2);
        inlineRange->setObjectName(QString::fromUtf8("inlineRange"));

        gridLayout->addWidget(inlineRange, 0, 0, 1, 4);

        crosslineRange = new CXSliderComplex(groupBox_2);
        crosslineRange->setObjectName(QString::fromUtf8("crosslineRange"));

        gridLayout->addWidget(crosslineRange, 1, 0, 1, 4);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(CXPageGSInversion1);

        QMetaObject::connectSlotsByName(CXPageGSInversion1);
    } // setupUi

    void retranslateUi(QWizardPage *CXPageGSInversion1)
    {
        CXPageGSInversion1->setWindowTitle(QCoreApplication::translate("CXPageGSInversion1", "CXPageGSInversion1", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXPageGSInversion1", "Structure Model Setting", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetSM->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CXPageGSInversion1", "Use", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetSM->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CXPageGSInversion1", "Zone", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetSM->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CXPageGSInversion1", "Reservoir", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CXPageGSInversion1", "Wells & Logs", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetWells->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CXPageGSInversion1", "Use", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetWells->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CXPageGSInversion1", "Well", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageGSInversion1", "Discrete Propoerty", nullptr));
        label_3->setText(QCoreApplication::translate("CXPageGSInversion1", "Continuous Propoerty", nullptr));
        comboBoxContinuous->setItemText(0, QCoreApplication::translate("CXPageGSInversion1", "Zp, Vp/Vs, Rho", nullptr));
        comboBoxContinuous->setItemText(1, QCoreApplication::translate("CXPageGSInversion1", "Vp, Vs, Rho", nullptr));
        comboBoxContinuous->setItemText(2, QCoreApplication::translate("CXPageGSInversion1", "Zp, Zs, Rho", nullptr));

        labelContinuousLog1->setText(QCoreApplication::translate("CXPageGSInversion1", "ZP", nullptr));
        labelContinuousLog2->setText(QCoreApplication::translate("CXPageGSInversion1", "VP/VS", nullptr));
        labelContinuousLog3->setText(QCoreApplication::translate("CXPageGSInversion1", "Rho", nullptr));
        checkBox->setText(QCoreApplication::translate("CXPageGSInversion1", "Fit prior pdfs of shape", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("CXPageGSInversion1", "Normal", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("CXPageGSInversion1", "Log normal", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("CXPageGSInversion1", "Binned", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("CXPageGSInversion1", "Uniform", nullptr));

        labelNumBins->setText(QCoreApplication::translate("CXPageGSInversion1", "Number of bins", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXPageGSInversion1", "Output", nullptr));
        pushButtonQCSection->setText(QString());
        label->setText(QCoreApplication::translate("CXPageGSInversion1", "QC Section:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageGSInversion1: public Ui_CXPageGSInversion1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEGSINVERSION1_H
