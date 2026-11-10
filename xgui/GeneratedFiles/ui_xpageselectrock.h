/********************************************************************************
** Form generated from reading UI file 'xpageselectrock.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESELECTROCK_H
#define UI_XPAGESELECTROCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_CXPageSelectRock
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWizardPage *CXPageSelectRock)
    {
        if (CXPageSelectRock->objectName().isEmpty())
            CXPageSelectRock->setObjectName(QString::fromUtf8("CXPageSelectRock"));
        CXPageSelectRock->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CXPageSelectRock->sizePolicy().hasHeightForWidth());
        CXPageSelectRock->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(CXPageSelectRock);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget = new QTableWidget(CXPageSelectRock);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout->addWidget(tableWidget);


        retranslateUi(CXPageSelectRock);

        QMetaObject::connectSlotsByName(CXPageSelectRock);
    } // setupUi

    void retranslateUi(QWizardPage *CXPageSelectRock)
    {
        CXPageSelectRock->setWindowTitle(QCoreApplication::translate("CXPageSelectRock", "CXPageSelectRock", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageSelectRock: public Ui_CXPageSelectRock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESELECTROCK_H
