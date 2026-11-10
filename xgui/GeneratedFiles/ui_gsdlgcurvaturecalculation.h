/********************************************************************************
** Form generated from reading UI file 'gsdlgcurvaturecalculation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSDLGCURVATURECALCULATION_H
#define UI_GSDLGCURVATURECALCULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_GSDlgCurvatureCalculation
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBoxDX;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpinBox *spinBoxDY;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GSDlgCurvatureCalculation)
    {
        if (GSDlgCurvatureCalculation->objectName().isEmpty())
            GSDlgCurvatureCalculation->setObjectName(QString::fromUtf8("GSDlgCurvatureCalculation"));
        GSDlgCurvatureCalculation->resize(510, 532);
        gridLayout_2 = new QGridLayout(GSDlgCurvatureCalculation);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(GSDlgCurvatureCalculation);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        if (tableWidget->rowCount() < 2)
            tableWidget->setRowCount(2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setRowCount(2);
        tableWidget->setColumnCount(4);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(40);
        tableWidget->verticalHeader()->setDefaultSectionSize(40);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(GSDlgCurvatureCalculation);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBoxDX = new QSpinBox(groupBox_2);
        spinBoxDX->setObjectName(QString::fromUtf8("spinBoxDX"));
        spinBoxDX->setMinimum(3);
        spinBoxDX->setMaximum(21);
        spinBoxDX->setSingleStep(2);

        horizontalLayout->addWidget(spinBoxDX);

        horizontalSpacer = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBoxDY = new QSpinBox(groupBox_2);
        spinBoxDY->setObjectName(QString::fromUtf8("spinBoxDY"));
        spinBoxDY->setMinimum(3);
        spinBoxDY->setMaximum(21);
        spinBoxDY->setSingleStep(2);

        horizontalLayout->addWidget(spinBoxDY);

        horizontalSpacer_2 = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(GSDlgCurvatureCalculation);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(GSDlgCurvatureCalculation);
        QObject::connect(buttonBox, SIGNAL(accepted()), GSDlgCurvatureCalculation, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GSDlgCurvatureCalculation, SLOT(close()));

        QMetaObject::connectSlotsByName(GSDlgCurvatureCalculation);
    } // setupUi

    void retranslateUi(QDialog *GSDlgCurvatureCalculation)
    {
        GSDlgCurvatureCalculation->setWindowTitle(QCoreApplication::translate("GSDlgCurvatureCalculation", "GSDlgCurvatureCalculation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GSDlgCurvatureCalculation", "Select Attributes", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("GSDlgCurvatureCalculation", "Window Size", nullptr));
        label->setText(QCoreApplication::translate("GSDlgCurvatureCalculation", "dx", nullptr));
        label_2->setText(QCoreApplication::translate("GSDlgCurvatureCalculation", "dy", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSDlgCurvatureCalculation: public Ui_GSDlgCurvatureCalculation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSDLGCURVATURECALCULATION_H
