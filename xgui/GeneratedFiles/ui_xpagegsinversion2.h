/********************************************************************************
** Form generated from reading UI file 'xpagegsinversion2.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEGSINVERSION2_H
#define UI_XPAGEGSINVERSION2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_CXPageGSInversion2
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *tableWidgetZone;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QWidget *histoCanvas;
    QTableWidget *tableWidgetCategory;
    QWidget *page_2;

    void setupUi(QWizardPage *CXPageGSInversion2)
    {
        if (CXPageGSInversion2->objectName().isEmpty())
            CXPageGSInversion2->setObjectName(QString::fromUtf8("CXPageGSInversion2"));
        CXPageGSInversion2->resize(897, 447);
        gridLayout_3 = new QGridLayout(CXPageGSInversion2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(CXPageGSInversion2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidgetZone = new QTableWidget(groupBox);
        if (tableWidgetZone->columnCount() < 8)
            tableWidgetZone->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetZone->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetZone->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetZone->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetZone->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetZone->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetZone->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetZone->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetZone->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidgetZone->setObjectName(QString::fromUtf8("tableWidgetZone"));

        gridLayout->addWidget(tableWidgetZone, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(CXPageGSInversion2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        stackedWidget = new QStackedWidget(groupBox_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        histoCanvas = new QWidget(page);
        histoCanvas->setObjectName(QString::fromUtf8("histoCanvas"));
        histoCanvas->setAutoFillBackground(true);

        gridLayout_2->addWidget(histoCanvas, 0, 0, 1, 1);

        tableWidgetCategory = new QTableWidget(page);
        if (tableWidgetCategory->columnCount() < 2)
            tableWidgetCategory->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetCategory->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetCategory->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        tableWidgetCategory->setObjectName(QString::fromUtf8("tableWidgetCategory"));
        tableWidgetCategory->setMinimumSize(QSize(240, 0));
        tableWidgetCategory->setMaximumSize(QSize(240, 16777215));

        gridLayout_2->addWidget(tableWidgetCategory, 0, 1, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(CXPageGSInversion2);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CXPageGSInversion2);
    } // setupUi

    void retranslateUi(QWizardPage *CXPageGSInversion2)
    {
        CXPageGSInversion2->setWindowTitle(QCoreApplication::translate("CXPageGSInversion2", "CXPageGSInversion2", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXPageGSInversion2", "Geostatistical Parameters", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetZone->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CXPageGSInversion2", "Zone", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetZone->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CXPageGSInversion2", "Discrete Properties", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetZone->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CXPageGSInversion2", "Continuous Properties", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetZone->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CXPageGSInversion2", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetZone->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CXPageGSInversion2", "Pdf/Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetZone->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("CXPageGSInversion2", "Model Variogram", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetZone->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("CXPageGSInversion2", "Sample Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetZone->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("CXPageGSInversion2", "Well Conditioning", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXPageGSInversion2", "Geostatistical Parameters Modification", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetCategory->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("CXPageGSInversion2", "Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetCategory->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("CXPageGSInversion2", "Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageGSInversion2: public Ui_CXPageGSInversion2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEGSINVERSION2_H
