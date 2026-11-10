/********************************************************************************
** Form generated from reading UI file 'xpageimportformation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEIMPORTFORMATION_H
#define UI_XPAGEIMPORTFORMATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_CXPageImportFormation
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButtonSelectAll;
    QTableWidget *tableWidget;
    QPushButton *pushButtonUnselectAll;

    void setupUi(QWizardPage *CXPageImportFormation)
    {
        if (CXPageImportFormation->objectName().isEmpty())
            CXPageImportFormation->setObjectName(QString::fromUtf8("CXPageImportFormation"));
        CXPageImportFormation->resize(486, 399);
        gridLayout = new QGridLayout(CXPageImportFormation);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonSelectAll = new QPushButton(CXPageImportFormation);
        pushButtonSelectAll->setObjectName(QString::fromUtf8("pushButtonSelectAll"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/SelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSelectAll->setIcon(icon);

        gridLayout->addWidget(pushButtonSelectAll, 0, 1, 1, 1);

        tableWidget = new QTableWidget(CXPageImportFormation);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 3, 1);

        pushButtonUnselectAll = new QPushButton(CXPageImportFormation);
        pushButtonUnselectAll->setObjectName(QString::fromUtf8("pushButtonUnselectAll"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/DisSelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonUnselectAll->setIcon(icon1);

        gridLayout->addWidget(pushButtonUnselectAll, 1, 1, 1, 1);


        retranslateUi(CXPageImportFormation);

        QMetaObject::connectSlotsByName(CXPageImportFormation);
    } // setupUi

    void retranslateUi(QWizardPage *CXPageImportFormation)
    {
        CXPageImportFormation->setWindowTitle(QCoreApplication::translate("CXPageImportFormation", "CXPageImportFormation", nullptr));
        pushButtonSelectAll->setText(QString());
        pushButtonUnselectAll->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXPageImportFormation: public Ui_CXPageImportFormation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEIMPORTFORMATION_H
