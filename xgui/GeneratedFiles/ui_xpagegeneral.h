/********************************************************************************
** Form generated from reading UI file 'xpagegeneral.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEGENERAL_H
#define UI_XPAGEGENERAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageGeneral
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *m_EdtName;
    QSpacerItem *horizontalSpacer;
    QLabel *m_EdtType;
    QLineEdit *lineEditType;
    QLabel *m_pLabelDatum;
    QLineEdit *m_pLineEdtDatum;
    QLabel *m_pLabelRepVel;
    QLineEdit *m_pLineEdtRepVel;
    QLabel *label_XOffset;
    QLineEdit *lineEdit_XOffset;
    QLineEdit *lineEdit_YOffset;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QTableWidget *m_GeneralInfo;
    QTableWidget *tableWidget;
    CXButtonColorEdit *comboBoxColor;
    QLineEdit *m_pLineEdtKB;
    QLabel *m_pLabelKB;
    QLabel *label_2;
    QLabel *label_YOffset;

    void setupUi(QWidget *CXPageGeneral)
    {
        if (CXPageGeneral->objectName().isEmpty())
            CXPageGeneral->setObjectName(QString::fromUtf8("CXPageGeneral"));
        CXPageGeneral->resize(548, 443);
        gridLayout = new QGridLayout(CXPageGeneral);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CXPageGeneral);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_EdtName = new QLineEdit(CXPageGeneral);
        m_EdtName->setObjectName(QString::fromUtf8("m_EdtName"));

        gridLayout->addWidget(m_EdtName, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(92, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        m_EdtType = new QLabel(CXPageGeneral);
        m_EdtType->setObjectName(QString::fromUtf8("m_EdtType"));

        gridLayout->addWidget(m_EdtType, 1, 0, 1, 1);

        lineEditType = new QLineEdit(CXPageGeneral);
        lineEditType->setObjectName(QString::fromUtf8("lineEditType"));

        gridLayout->addWidget(lineEditType, 1, 1, 1, 1);

        m_pLabelDatum = new QLabel(CXPageGeneral);
        m_pLabelDatum->setObjectName(QString::fromUtf8("m_pLabelDatum"));

        gridLayout->addWidget(m_pLabelDatum, 2, 0, 1, 1);

        m_pLineEdtDatum = new QLineEdit(CXPageGeneral);
        m_pLineEdtDatum->setObjectName(QString::fromUtf8("m_pLineEdtDatum"));

        gridLayout->addWidget(m_pLineEdtDatum, 2, 1, 1, 1);

        m_pLabelRepVel = new QLabel(CXPageGeneral);
        m_pLabelRepVel->setObjectName(QString::fromUtf8("m_pLabelRepVel"));
        m_pLabelRepVel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(m_pLabelRepVel, 2, 3, 1, 2);

        m_pLineEdtRepVel = new QLineEdit(CXPageGeneral);
        m_pLineEdtRepVel->setObjectName(QString::fromUtf8("m_pLineEdtRepVel"));

        gridLayout->addWidget(m_pLineEdtRepVel, 2, 5, 1, 1);

        label_XOffset = new QLabel(CXPageGeneral);
        label_XOffset->setObjectName(QString::fromUtf8("label_XOffset"));

        gridLayout->addWidget(label_XOffset, 3, 0, 1, 1);

        lineEdit_XOffset = new QLineEdit(CXPageGeneral);
        lineEdit_XOffset->setObjectName(QString::fromUtf8("lineEdit_XOffset"));

        gridLayout->addWidget(lineEdit_XOffset, 3, 1, 1, 1);

        lineEdit_YOffset = new QLineEdit(CXPageGeneral);
        lineEdit_YOffset->setObjectName(QString::fromUtf8("lineEdit_YOffset"));

        gridLayout->addWidget(lineEdit_YOffset, 3, 5, 1, 1);

        groupBox = new QGroupBox(CXPageGeneral);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(true);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_GeneralInfo = new QTableWidget(groupBox);
        if (m_GeneralInfo->columnCount() < 3)
            m_GeneralInfo->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_GeneralInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_GeneralInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_GeneralInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (m_GeneralInfo->rowCount() < 3)
            m_GeneralInfo->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        m_GeneralInfo->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        m_GeneralInfo->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        m_GeneralInfo->setVerticalHeaderItem(2, __qtablewidgetitem5);
        m_GeneralInfo->setObjectName(QString::fromUtf8("m_GeneralInfo"));
        m_GeneralInfo->setMinimumSize(QSize(0, 110));
        m_GeneralInfo->setMaximumSize(QSize(16777215, 102));
        m_GeneralInfo->setShowGrid(false);
        m_GeneralInfo->horizontalHeader()->setDefaultSectionSize(120);
        m_GeneralInfo->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(m_GeneralInfo);

        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setShowGrid(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(240);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidget);


        gridLayout->addWidget(groupBox, 4, 0, 1, 6);

        comboBoxColor = new CXButtonColorEdit(CXPageGeneral);
        comboBoxColor->setObjectName(QString::fromUtf8("comboBoxColor"));
        comboBoxColor->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(comboBoxColor, 0, 5, 1, 1);

        m_pLineEdtKB = new QLineEdit(CXPageGeneral);
        m_pLineEdtKB->setObjectName(QString::fromUtf8("m_pLineEdtKB"));

        gridLayout->addWidget(m_pLineEdtKB, 1, 5, 1, 1);

        m_pLabelKB = new QLabel(CXPageGeneral);
        m_pLabelKB->setObjectName(QString::fromUtf8("m_pLabelKB"));
        m_pLabelKB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(m_pLabelKB, 1, 3, 1, 2);

        label_2 = new QLabel(CXPageGeneral);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 0, 3, 1, 2);

        label_YOffset = new QLabel(CXPageGeneral);
        label_YOffset->setObjectName(QString::fromUtf8("label_YOffset"));
        label_YOffset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_YOffset, 3, 3, 1, 2);


        retranslateUi(CXPageGeneral);

        QMetaObject::connectSlotsByName(CXPageGeneral);
    } // setupUi

    void retranslateUi(QWidget *CXPageGeneral)
    {
        CXPageGeneral->setWindowTitle(QCoreApplication::translate("CXPageGeneral", "Form", nullptr));
        label->setText(QCoreApplication::translate("CXPageGeneral", "Name", nullptr));
        m_EdtType->setText(QCoreApplication::translate("CXPageGeneral", "Type", nullptr));
        m_pLabelDatum->setText(QCoreApplication::translate("CXPageGeneral", "Datum", nullptr));
        m_pLineEdtDatum->setText(QCoreApplication::translate("CXPageGeneral", "0", nullptr));
        m_pLabelRepVel->setText(QCoreApplication::translate("CXPageGeneral", "Replacement Velocity ", nullptr));
        m_pLineEdtRepVel->setText(QCoreApplication::translate("CXPageGeneral", "2000", nullptr));
        label_XOffset->setText(QCoreApplication::translate("CXPageGeneral", "X Offset", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXPageGeneral", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_GeneralInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CXPageGeneral", "Minimum", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_GeneralInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CXPageGeneral", "Maximum", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_GeneralInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CXPageGeneral", "Delta", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = m_GeneralInfo->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CXPageGeneral", "X (m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = m_GeneralInfo->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CXPageGeneral", "Y (m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = m_GeneralInfo->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("CXPageGeneral", "Z (m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("CXPageGeneral", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("CXPageGeneral", "Value", nullptr));
        m_pLineEdtKB->setText(QCoreApplication::translate("CXPageGeneral", "0", nullptr));
        m_pLabelKB->setText(QCoreApplication::translate("CXPageGeneral", "KB ", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageGeneral", "Color ", nullptr));
        label_YOffset->setText(QCoreApplication::translate("CXPageGeneral", "Y Offset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageGeneral: public Ui_CXPageGeneral {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEGENERAL_H
