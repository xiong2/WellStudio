/********************************************************************************
** Form generated from reading UI file 'xdlgsegytraceheader.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGSEGYTRACEHEADER_H
#define UI_XDLGSEGYTRACEHEADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include "xtableforascii.h"

QT_BEGIN_NAMESPACE

class Ui_CXDlgSEGYTraceHeader
{
public:
    QGridLayout *gridLayout;
    CXTableForLoadSegy *tableWidget;
    QSpinBox *spinBox;
    QSlider *horizontalSlider;
    QLabel *label;
    QLineEdit *lineEditCDP;
    QLabel *label_2;
    QLineEdit *lineEditX;
    QLabel *label_3;
    QLineEdit *lineEditY;
    QCheckBox *checkBox;
    QLineEdit *lineEditScale;
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton;
    QLabel *labelTrace;

    void setupUi(QDialog *CXDlgSEGYTraceHeader)
    {
        if (CXDlgSEGYTraceHeader->objectName().isEmpty())
            CXDlgSEGYTraceHeader->setObjectName(QString::fromUtf8("CXDlgSEGYTraceHeader"));
        CXDlgSEGYTraceHeader->resize(446, 600);
        gridLayout = new QGridLayout(CXDlgSEGYTraceHeader);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new CXTableForLoadSegy(CXDlgSEGYTraceHeader);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 3);

        spinBox = new QSpinBox(CXDlgSEGYTraceHeader);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(60, 0));
        spinBox->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(spinBox, 2, 2, 2, 1);

        horizontalSlider = new QSlider(CXDlgSEGYTraceHeader);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 3, 0, 1, 2);

        label = new QLabel(CXDlgSEGYTraceHeader);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        lineEditCDP = new QLineEdit(CXDlgSEGYTraceHeader);
        lineEditCDP->setObjectName(QString::fromUtf8("lineEditCDP"));

        gridLayout->addWidget(lineEditCDP, 4, 1, 1, 2);

        label_2 = new QLabel(CXDlgSEGYTraceHeader);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        lineEditX = new QLineEdit(CXDlgSEGYTraceHeader);
        lineEditX->setObjectName(QString::fromUtf8("lineEditX"));

        gridLayout->addWidget(lineEditX, 5, 1, 1, 2);

        label_3 = new QLabel(CXDlgSEGYTraceHeader);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        lineEditY = new QLineEdit(CXDlgSEGYTraceHeader);
        lineEditY->setObjectName(QString::fromUtf8("lineEditY"));

        gridLayout->addWidget(lineEditY, 6, 1, 1, 2);

        checkBox = new QCheckBox(CXDlgSEGYTraceHeader);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 7, 0, 1, 1);

        lineEditScale = new QLineEdit(CXDlgSEGYTraceHeader);
        lineEditScale->setObjectName(QString::fromUtf8("lineEditScale"));
        lineEditScale->setEnabled(false);

        gridLayout->addWidget(lineEditScale, 7, 1, 1, 2);

        buttonBox = new QDialogButtonBox(CXDlgSEGYTraceHeader);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 8, 1, 1, 2);

        pushButton = new QPushButton(CXDlgSEGYTraceHeader);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 8, 0, 1, 1);

        labelTrace = new QLabel(CXDlgSEGYTraceHeader);
        labelTrace->setObjectName(QString::fromUtf8("labelTrace"));

        gridLayout->addWidget(labelTrace, 1, 0, 2, 2);


        retranslateUi(CXDlgSEGYTraceHeader);

        QMetaObject::connectSlotsByName(CXDlgSEGYTraceHeader);
    } // setupUi

    void retranslateUi(QDialog *CXDlgSEGYTraceHeader)
    {
        CXDlgSEGYTraceHeader->setWindowTitle(QCoreApplication::translate("CXDlgSEGYTraceHeader", "CXDlgSEGYTraceHeader", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "Bytes", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "Format", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "Value", nullptr));
        label->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "CDP Position:", nullptr));
        lineEditCDP->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "21", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "X Position:", nullptr));
        lineEditX->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "73", nullptr));
        label_3->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "Y Position:", nullptr));
        lineEditY->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "77", nullptr));
        checkBox->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "Override Scaling:", nullptr));
        lineEditScale->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "0.01", nullptr));
        pushButton->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "OK for All", nullptr));
        labelTrace->setText(QCoreApplication::translate("CXDlgSEGYTraceHeader", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgSEGYTraceHeader: public Ui_CXDlgSEGYTraceHeader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGSEGYTRACEHEADER_H
