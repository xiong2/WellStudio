/********************************************************************************
** Form generated from reading UI file 'xpagelascurves.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGELASCURVES_H
#define UI_XPAGELASCURVES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageLASCurves
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QWidget *PageLASCurves)
    {
        if (PageLASCurves->objectName().isEmpty())
            PageLASCurves->setObjectName(QString::fromUtf8("PageLASCurves"));
        PageLASCurves->resize(576, 404);
        gridLayout_3 = new QGridLayout(PageLASCurves);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(PageLASCurves);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(PageLASCurves);
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


        retranslateUi(PageLASCurves);

        QMetaObject::connectSlotsByName(PageLASCurves);
    } // setupUi

    void retranslateUi(QWidget *PageLASCurves)
    {
        PageLASCurves->setWindowTitle(QCoreApplication::translate("PageLASCurves", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageLASCurves", "Curves", nullptr));
        pushButton->setText(QCoreApplication::translate("PageLASCurves", "Select All", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PageLASCurves", "Preview", nullptr));
        label->setText(QCoreApplication::translate("PageLASCurves", "LAS file\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageLASCurves: public Ui_PageLASCurves {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGELASCURVES_H
