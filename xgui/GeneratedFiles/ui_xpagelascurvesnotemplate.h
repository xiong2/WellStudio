/********************************************************************************
** Form generated from reading UI file 'xpagelascurvesnotemplate.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGELASCURVESNOTEMPLATE_H
#define UI_XPAGELASCURVESNOTEMPLATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageLASCurvesNoTemplate
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QWidget *PageLASCurvesNoTemplate)
    {
        if (PageLASCurvesNoTemplate->objectName().isEmpty())
            PageLASCurvesNoTemplate->setObjectName(QString::fromUtf8("PageLASCurvesNoTemplate"));
        PageLASCurvesNoTemplate->resize(935, 649);
        gridLayout_3 = new QGridLayout(PageLASCurvesNoTemplate);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(PageLASCurvesNoTemplate);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 2);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(PageLASCurvesNoTemplate);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_2->addWidget(textEdit, 1, 0, 1, 3);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(PageLASCurvesNoTemplate);

        QMetaObject::connectSlotsByName(PageLASCurvesNoTemplate);
    } // setupUi

    void retranslateUi(QWidget *PageLASCurvesNoTemplate)
    {
        PageLASCurvesNoTemplate->setWindowTitle(QCoreApplication::translate("PageLASCurvesNoTemplate", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageLASCurvesNoTemplate", "Curves", nullptr));
        pushButton->setText(QCoreApplication::translate("PageLASCurvesNoTemplate", "Select All/Unselect All", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PageLASCurvesNoTemplate", "Load", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PageLASCurvesNoTemplate", "Curve Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PageLASCurvesNoTemplate", "Import Type", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PageLASCurvesNoTemplate", "Preview", nullptr));
        label->setText(QCoreApplication::translate("PageLASCurvesNoTemplate", "LAS File\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageLASCurvesNoTemplate: public Ui_PageLASCurvesNoTemplate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGELASCURVESNOTEMPLATE_H
