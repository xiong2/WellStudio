/********************************************************************************
** Form generated from reading UI file 'gsdlghorizonmanagement.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSDLGHORIZONMANAGEMENT_H
#define UI_GSDLGHORIZONMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GSDlgHorizonManagement
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBoxSeaBed;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QGroupBox *groupBox_UseFaults;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *lineEdit_FaultTolerance;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_UseThickForFaultType;
    QLabel *label_5;
    QLineEdit *lineEdit_ThickTolerance;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GSDlgHorizonManagement)
    {
        if (GSDlgHorizonManagement->objectName().isEmpty())
            GSDlgHorizonManagement->setObjectName(QString::fromUtf8("GSDlgHorizonManagement"));
        GSDlgHorizonManagement->resize(903, 436);
        verticalLayout_2 = new QVBoxLayout(GSDlgHorizonManagement);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(GSDlgHorizonManagement);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(110, 16777215));

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(GSDlgHorizonManagement);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(200, 0));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        checkBoxSeaBed = new QCheckBox(GSDlgHorizonManagement);
        checkBoxSeaBed->setObjectName(QString::fromUtf8("checkBoxSeaBed"));

        horizontalLayout->addWidget(checkBoxSeaBed);


        verticalLayout_2->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(GSDlgHorizonManagement);
        if (tableWidget->columnCount() < 10)
            tableWidget->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->verticalHeader()->setDefaultSectionSize(33);

        verticalLayout_2->addWidget(tableWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(GSDlgHorizonManagement);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(280, 0));
        label->setMaximumSize(QSize(280, 16777215));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(GSDlgHorizonManagement);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton = new QPushButton(GSDlgHorizonManagement);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        groupBox_UseFaults = new QGroupBox(GSDlgHorizonManagement);
        groupBox_UseFaults->setObjectName(QString::fromUtf8("groupBox_UseFaults"));
        groupBox_UseFaults->setCheckable(true);
        verticalLayout = new QVBoxLayout(groupBox_UseFaults);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupBox_UseFaults);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        lineEdit_FaultTolerance = new QLineEdit(groupBox_UseFaults);
        lineEdit_FaultTolerance->setObjectName(QString::fromUtf8("lineEdit_FaultTolerance"));

        horizontalLayout_5->addWidget(lineEdit_FaultTolerance);

        label_4 = new QLabel(groupBox_UseFaults);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBox_UseThickForFaultType = new QCheckBox(groupBox_UseFaults);
        checkBox_UseThickForFaultType->setObjectName(QString::fromUtf8("checkBox_UseThickForFaultType"));
        checkBox_UseThickForFaultType->setChecked(true);

        horizontalLayout_4->addWidget(checkBox_UseThickForFaultType);

        label_5 = new QLabel(groupBox_UseFaults);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        lineEdit_ThickTolerance = new QLineEdit(groupBox_UseFaults);
        lineEdit_ThickTolerance->setObjectName(QString::fromUtf8("lineEdit_ThickTolerance"));
        lineEdit_ThickTolerance->setEnabled(true);

        horizontalLayout_4->addWidget(lineEdit_ThickTolerance);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(groupBox_UseFaults);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(379, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(GSDlgHorizonManagement);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(GSDlgHorizonManagement);
        QObject::connect(buttonBox, SIGNAL(accepted()), GSDlgHorizonManagement, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GSDlgHorizonManagement, SLOT(reject()));
        QObject::connect(checkBox_UseThickForFaultType, SIGNAL(toggled(bool)), lineEdit_ThickTolerance, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(GSDlgHorizonManagement);
    } // setupUi

    void retranslateUi(QDialog *GSDlgHorizonManagement)
    {
        GSDlgHorizonManagement->setWindowTitle(QCoreApplication::translate("GSDlgHorizonManagement", "Horizon Management", nullptr));
        label_2->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Select Survey:", nullptr));
        checkBoxSeaBed->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Create Isopach for sea bed", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Using", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Horizon", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Compression", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Base Stress Direction", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Interval Velocity", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("GSDlgHorizonManagement", "For Pore Pressure", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Pore Pressure", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Hydrostatic Gradient", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Lithostatic Gradient", nullptr));
        label->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Import pulse and interval velocity from file:", nullptr));
        pushButton->setText(QCoreApplication::translate("GSDlgHorizonManagement", "...", nullptr));
        groupBox_UseFaults->setTitle(QCoreApplication::translate("GSDlgHorizonManagement", "Use Faults", nullptr));
        label_3->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Fault data tolerance:                                                        ", nullptr));
        label_4->setText(QCoreApplication::translate("GSDlgHorizonManagement", "m", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_UseThickForFaultType->setToolTip(QCoreApplication::translate("GSDlgHorizonManagement", "Determine fault type from thickness", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_UseThickForFaultType->setText(QCoreApplication::translate("GSDlgHorizonManagement", "Use thick for fault type(ISO)", nullptr));
        label_5->setText(QCoreApplication::translate("GSDlgHorizonManagement", "thick data tolerance: ", nullptr));
        lineEdit_ThickTolerance->setText(QCoreApplication::translate("GSDlgHorizonManagement", "5.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSDlgHorizonManagement: public Ui_GSDlgHorizonManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSDLGHORIZONMANAGEMENT_H
