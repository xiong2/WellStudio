/********************************************************************************
** Form generated from reading UI file 'xpagebuildlfmthree.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEBUILDLFMTHREE_H
#define UI_XPAGEBUILDLFMTHREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageBuildLowFrequencyModelThree
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QLineEdit *m_pLineEdtTop;
    QLabel *m_pLabelTopShiftUnit;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QLineEdit *m_pLineEdtBottom;
    QLabel *m_pLabelBottomShiftUnit;

    void setupUi(QWidget *PageBuildLowFrequencyModelThree)
    {
        if (PageBuildLowFrequencyModelThree->objectName().isEmpty())
            PageBuildLowFrequencyModelThree->setObjectName(QString::fromUtf8("PageBuildLowFrequencyModelThree"));
        PageBuildLowFrequencyModelThree->resize(576, 374);
        gridLayout = new QGridLayout(PageBuildLowFrequencyModelThree);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_10 = new QLabel(PageBuildLowFrequencyModelThree);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout->addWidget(label_10);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 4);

        tableWidget = new QTableWidget(PageBuildLowFrequencyModelThree);
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

        gridLayout->addWidget(tableWidget, 1, 0, 1, 7);

        label_2 = new QLabel(PageBuildLowFrequencyModelThree);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        m_pLineEdtTop = new QLineEdit(PageBuildLowFrequencyModelThree);
        m_pLineEdtTop->setObjectName(QString::fromUtf8("m_pLineEdtTop"));
        m_pLineEdtTop->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(m_pLineEdtTop, 2, 1, 1, 1);

        m_pLabelTopShiftUnit = new QLabel(PageBuildLowFrequencyModelThree);
        m_pLabelTopShiftUnit->setObjectName(QString::fromUtf8("m_pLabelTopShiftUnit"));

        gridLayout->addWidget(m_pLabelTopShiftUnit, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(169, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        label_4 = new QLabel(PageBuildLowFrequencyModelThree);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 4, 1, 1);

        m_pLineEdtBottom = new QLineEdit(PageBuildLowFrequencyModelThree);
        m_pLineEdtBottom->setObjectName(QString::fromUtf8("m_pLineEdtBottom"));
        m_pLineEdtBottom->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(m_pLineEdtBottom, 2, 5, 1, 1);

        m_pLabelBottomShiftUnit = new QLabel(PageBuildLowFrequencyModelThree);
        m_pLabelBottomShiftUnit->setObjectName(QString::fromUtf8("m_pLabelBottomShiftUnit"));

        gridLayout->addWidget(m_pLabelBottomShiftUnit, 2, 6, 1, 1);


        retranslateUi(PageBuildLowFrequencyModelThree);

        QMetaObject::connectSlotsByName(PageBuildLowFrequencyModelThree);
    } // setupUi

    void retranslateUi(QWidget *PageBuildLowFrequencyModelThree)
    {
        PageBuildLowFrequencyModelThree->setWindowTitle(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "Form", nullptr));
        label_10->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "Please select a contact type", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "Zone", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "Contact Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "No. Slice", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "Thickness", nullptr));
        label_2->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "Top Shift", nullptr));
        m_pLabelTopShiftUnit->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "ms", nullptr));
        label_4->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "Bottom Shift", nullptr));
        m_pLabelBottomShiftUnit->setText(QCoreApplication::translate("PageBuildLowFrequencyModelThree", "ms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageBuildLowFrequencyModelThree: public Ui_PageBuildLowFrequencyModelThree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEBUILDLFMTHREE_H
