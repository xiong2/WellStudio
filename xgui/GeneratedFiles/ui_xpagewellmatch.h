/********************************************************************************
** Form generated from reading UI file 'xpagewellmatch.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEWELLMATCH_H
#define UI_XPAGEWELLMATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageMatchWells
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *pushButtonSelectAll;

    void setupUi(QWidget *PageMatchWells)
    {
        if (PageMatchWells->objectName().isEmpty())
            PageMatchWells->setObjectName(QString::fromUtf8("PageMatchWells"));
        PageMatchWells->resize(650, 320);
        gridLayout_2 = new QGridLayout(PageMatchWells);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(PageMatchWells);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        pushButtonSelectAll = new QPushButton(groupBox);
        pushButtonSelectAll->setObjectName(QString::fromUtf8("pushButtonSelectAll"));
        pushButtonSelectAll->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(pushButtonSelectAll, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(PageMatchWells);

        QMetaObject::connectSlotsByName(PageMatchWells);
    } // setupUi

    void retranslateUi(QWidget *PageMatchWells)
    {
        PageMatchWells->setWindowTitle(QCoreApplication::translate("PageMatchWells", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageMatchWells", "Select Wells", nullptr));
        pushButtonSelectAll->setText(QCoreApplication::translate("PageMatchWells", "Select All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageMatchWells: public Ui_PageMatchWells {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEWELLMATCH_H
