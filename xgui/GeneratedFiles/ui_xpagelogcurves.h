/********************************************************************************
** Form generated from reading UI file 'xpagelogcurves.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGELOGCURVES_H
#define UI_XPAGELOGCURVES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_CXPagelogcurves
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QWizardPage *CXPagelogcurves)
    {
        if (CXPagelogcurves->objectName().isEmpty())
            CXPagelogcurves->setObjectName(QString::fromUtf8("CXPagelogcurves"));
        CXPagelogcurves->resize(400, 300);
        gridLayout_2 = new QGridLayout(CXPagelogcurves);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(CXPagelogcurves);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(CXPagelogcurves);

        QMetaObject::connectSlotsByName(CXPagelogcurves);
    } // setupUi

    void retranslateUi(QWizardPage *CXPagelogcurves)
    {
        CXPagelogcurves->setWindowTitle(QCoreApplication::translate("CXPagelogcurves", "CXPagelogcurves", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXPagelogcurves", "Log Curves", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPagelogcurves: public Ui_CXPagelogcurves {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGELOGCURVES_H
