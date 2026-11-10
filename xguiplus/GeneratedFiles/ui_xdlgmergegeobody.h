/********************************************************************************
** Form generated from reading UI file 'xdlgmergegeobody.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGMERGEGEOBODY_H
#define UI_XDLGMERGEGEOBODY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CXDlgMergeGeobody
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *CXDlgMergeGeobody)
    {
        if (CXDlgMergeGeobody->objectName().isEmpty())
            CXDlgMergeGeobody->setObjectName(QString::fromUtf8("CXDlgMergeGeobody"));
        CXDlgMergeGeobody->resize(650, 780);
        gridLayout = new QGridLayout(CXDlgMergeGeobody);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CXDlgMergeGeobody);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(CXDlgMergeGeobody);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        tableWidget = new QTableWidget(CXDlgMergeGeobody);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(CXDlgMergeGeobody);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);


        retranslateUi(CXDlgMergeGeobody);

        QMetaObject::connectSlotsByName(CXDlgMergeGeobody);
    } // setupUi

    void retranslateUi(QWidget *CXDlgMergeGeobody)
    {
        CXDlgMergeGeobody->setWindowTitle(QCoreApplication::translate("CXDlgMergeGeobody", "CXDlgMergeGeobody", nullptr));
        label->setText(QCoreApplication::translate("CXDlgMergeGeobody", "Output Geobody", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgMergeGeobody: public Ui_CXDlgMergeGeobody {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGMERGEGEOBODY_H
