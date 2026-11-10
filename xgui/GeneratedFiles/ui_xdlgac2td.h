/********************************************************************************
** Form generated from reading UI file 'xdlgac2td.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGAC2TD_H
#define UI_XDLGAC2TD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include "xframetdcurve.h"

QT_BEGIN_NAMESPACE

class Ui_CXDlgAC2TD
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditStart;
    QLabel *label_4;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QTableView *tableView;
    QLineEdit *lineEditEnd;
    QLabel *label_3;
    QPushButton *pushButton;
    CXFrameTDCurve *widget;

    void setupUi(QDialog *CXDlgAC2TD)
    {
        if (CXDlgAC2TD->objectName().isEmpty())
            CXDlgAC2TD->setObjectName(QString::fromUtf8("CXDlgAC2TD"));
        CXDlgAC2TD->resize(849, 532);
        gridLayout = new QGridLayout(CXDlgAC2TD);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(CXDlgAC2TD);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 5, 6, 1, 1);

        lineEditStart = new QLineEdit(CXDlgAC2TD);
        lineEditStart->setObjectName(QString::fromUtf8("lineEditStart"));

        gridLayout->addWidget(lineEditStart, 1, 1, 1, 1);

        label_4 = new QLabel(CXDlgAC2TD);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(16777215, 23));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        comboBox = new QComboBox(CXDlgAC2TD);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 4);

        label_2 = new QLabel(CXDlgAC2TD);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit = new QLineEdit(CXDlgAC2TD);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 2, 1, 1, 2);

        label = new QLabel(CXDlgAC2TD);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tableView = new QTableView(CXDlgAC2TD);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMinimumSize(QSize(400, 0));
        tableView->horizontalHeader()->setDefaultSectionSize(80);

        gridLayout->addWidget(tableView, 0, 6, 5, 1);

        lineEditEnd = new QLineEdit(CXDlgAC2TD);
        lineEditEnd->setObjectName(QString::fromUtf8("lineEditEnd"));

        gridLayout->addWidget(lineEditEnd, 1, 3, 1, 1);

        label_3 = new QLabel(CXDlgAC2TD);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(16777215, 23));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        pushButton = new QPushButton(CXDlgAC2TD);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 2, 3, 1, 1);

        widget = new CXFrameTDCurve(CXDlgAC2TD);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setAutoFillBackground(true);

        gridLayout->addWidget(widget, 3, 0, 2, 6);


        retranslateUi(CXDlgAC2TD);
        QObject::connect(buttonBox, SIGNAL(rejected()), CXDlgAC2TD, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), CXDlgAC2TD, SLOT(accept()));

        QMetaObject::connectSlotsByName(CXDlgAC2TD);
    } // setupUi

    void retranslateUi(QDialog *CXDlgAC2TD)
    {
        CXDlgAC2TD->setWindowTitle(QCoreApplication::translate("CXDlgAC2TD", "Calculate TD from AC curve", nullptr));
        lineEditStart->setText(QCoreApplication::translate("CXDlgAC2TD", "1", nullptr));
        label_4->setText(QCoreApplication::translate("CXDlgAC2TD", "to", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgAC2TD", "Compensate velocity (m/s):", nullptr));
        lineEdit->setText(QCoreApplication::translate("CXDlgAC2TD", "2000", nullptr));
        label->setText(QCoreApplication::translate("CXDlgAC2TD", "Input AC curve:", nullptr));
        label_3->setText(QCoreApplication::translate("CXDlgAC2TD", "Use samples from", nullptr));
        pushButton->setText(QCoreApplication::translate("CXDlgAC2TD", "Calculate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgAC2TD: public Ui_CXDlgAC2TD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGAC2TD_H
