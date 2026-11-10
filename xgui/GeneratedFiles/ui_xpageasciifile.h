/********************************************************************************
** Form generated from reading UI file 'xpageasciifile.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEASCIIFILE_H
#define UI_XPAGEASCIIFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageASCIIFileClass
{
public:
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QLabel *label;
    QLineEdit *lineEditFileName;
    QLabel *label_2;
    QLineEdit *lineEditLineNumber;
    QLabel *label_3;
    QLineEdit *lineEditInvalid;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *lineEditToLine;
    QLabel *label_4;
    QLineEdit *lineEditFromLine;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBoxComma;
    QCheckBox *checkBoxSemiColon;
    QCheckBox *checkBoxColon;
    QCheckBox *checkBoxTab;
    QCheckBox *checkBoxSpace;
    QCheckBox *checkBoxDOther;
    QLineEdit *lineEditDOther;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBoxDQ;
    QCheckBox *checkBoxSQ;
    QCheckBox *checkBoxQOther;
    QLineEdit *lineEditQOther;
    QCheckBox *checkBoxAllowBlank;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_7;
    QTableWidget *tableWidgetPreview;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QRadioButton *radioButtonLastUsed;
    QRadioButton *radioButtonAuto;
    QSpinBox *spinBoxNameLine;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_6;
    QLabel *label_8;
    QSpinBox *spinBoxPrivewNumber;
    QTableWidget *tableWidgetPreHeader;

    void setupUi(QWidget *PageASCIIFileClass)
    {
        if (PageASCIIFileClass->objectName().isEmpty())
            PageASCIIFileClass->setObjectName(QString::fromUtf8("PageASCIIFileClass"));
        PageASCIIFileClass->resize(933, 619);
        gridLayout_8 = new QGridLayout(PageASCIIFileClass);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        groupBox = new QGroupBox(PageASCIIFileClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        lineEditFileName = new QLineEdit(groupBox);
        lineEditFileName->setObjectName(QString::fromUtf8("lineEditFileName"));
        lineEditFileName->setReadOnly(true);

        gridLayout_5->addWidget(lineEditFileName, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_5->addWidget(label_2, 0, 2, 1, 1);

        lineEditLineNumber = new QLineEdit(groupBox);
        lineEditLineNumber->setObjectName(QString::fromUtf8("lineEditLineNumber"));
        lineEditLineNumber->setMaximumSize(QSize(80, 16777215));
        lineEditLineNumber->setReadOnly(true);

        gridLayout_5->addWidget(lineEditLineNumber, 0, 3, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_5->addWidget(label_3, 0, 4, 1, 1);

        lineEditInvalid = new QLineEdit(groupBox);
        lineEditInvalid->setObjectName(QString::fromUtf8("lineEditInvalid"));
        lineEditInvalid->setMaximumSize(QSize(80, 16777215));

        gridLayout_5->addWidget(lineEditInvalid, 0, 5, 1, 1);


        gridLayout_8->addWidget(groupBox, 0, 0, 1, 2);

        groupBox_2 = new QGroupBox(PageASCIIFileClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        lineEditToLine = new QLineEdit(groupBox_2);
        lineEditToLine->setObjectName(QString::fromUtf8("lineEditToLine"));

        gridLayout->addWidget(lineEditToLine, 0, 3, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        lineEditFromLine = new QLineEdit(groupBox_2);
        lineEditFromLine->setObjectName(QString::fromUtf8("lineEditFromLine"));

        gridLayout->addWidget(lineEditFromLine, 0, 1, 1, 1);


        gridLayout_8->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(PageASCIIFileClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBoxComma = new QCheckBox(groupBox_3);
        checkBoxComma->setObjectName(QString::fromUtf8("checkBoxComma"));

        gridLayout_2->addWidget(checkBoxComma, 0, 0, 1, 1);

        checkBoxSemiColon = new QCheckBox(groupBox_3);
        checkBoxSemiColon->setObjectName(QString::fromUtf8("checkBoxSemiColon"));

        gridLayout_2->addWidget(checkBoxSemiColon, 0, 1, 1, 1);

        checkBoxColon = new QCheckBox(groupBox_3);
        checkBoxColon->setObjectName(QString::fromUtf8("checkBoxColon"));

        gridLayout_2->addWidget(checkBoxColon, 0, 2, 1, 1);

        checkBoxTab = new QCheckBox(groupBox_3);
        checkBoxTab->setObjectName(QString::fromUtf8("checkBoxTab"));

        gridLayout_2->addWidget(checkBoxTab, 1, 0, 1, 1);

        checkBoxSpace = new QCheckBox(groupBox_3);
        checkBoxSpace->setObjectName(QString::fromUtf8("checkBoxSpace"));

        gridLayout_2->addWidget(checkBoxSpace, 1, 1, 1, 1);

        checkBoxDOther = new QCheckBox(groupBox_3);
        checkBoxDOther->setObjectName(QString::fromUtf8("checkBoxDOther"));

        gridLayout_2->addWidget(checkBoxDOther, 1, 2, 1, 1);

        lineEditDOther = new QLineEdit(groupBox_3);
        lineEditDOther->setObjectName(QString::fromUtf8("lineEditDOther"));

        gridLayout_2->addWidget(lineEditDOther, 1, 3, 1, 1);


        gridLayout_8->addWidget(groupBox_3, 2, 0, 1, 1);

        groupBox_4 = new QGroupBox(PageASCIIFileClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        checkBoxDQ = new QCheckBox(groupBox_4);
        checkBoxDQ->setObjectName(QString::fromUtf8("checkBoxDQ"));

        gridLayout_3->addWidget(checkBoxDQ, 0, 0, 1, 1);

        checkBoxSQ = new QCheckBox(groupBox_4);
        checkBoxSQ->setObjectName(QString::fromUtf8("checkBoxSQ"));

        gridLayout_3->addWidget(checkBoxSQ, 0, 1, 1, 1);

        checkBoxQOther = new QCheckBox(groupBox_4);
        checkBoxQOther->setObjectName(QString::fromUtf8("checkBoxQOther"));

        gridLayout_3->addWidget(checkBoxQOther, 0, 2, 1, 1);

        lineEditQOther = new QLineEdit(groupBox_4);
        lineEditQOther->setObjectName(QString::fromUtf8("lineEditQOther"));

        gridLayout_3->addWidget(lineEditQOther, 0, 3, 1, 1);

        checkBoxAllowBlank = new QCheckBox(groupBox_4);
        checkBoxAllowBlank->setObjectName(QString::fromUtf8("checkBoxAllowBlank"));

        gridLayout_3->addWidget(checkBoxAllowBlank, 1, 0, 1, 2);


        gridLayout_8->addWidget(groupBox_4, 2, 1, 1, 1);

        groupBox_5 = new QGroupBox(PageASCIIFileClass);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_7 = new QGridLayout(groupBox_5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        tableWidgetPreview = new QTableWidget(groupBox_5);
        tableWidgetPreview->setObjectName(QString::fromUtf8("tableWidgetPreview"));

        gridLayout_7->addWidget(tableWidgetPreview, 2, 0, 1, 2);

        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        radioButtonLastUsed = new QRadioButton(groupBox_6);
        radioButtonLastUsed->setObjectName(QString::fromUtf8("radioButtonLastUsed"));
        radioButtonLastUsed->setChecked(true);

        gridLayout_4->addWidget(radioButtonLastUsed, 0, 0, 1, 1);

        radioButtonAuto = new QRadioButton(groupBox_6);
        radioButtonAuto->setObjectName(QString::fromUtf8("radioButtonAuto"));
        radioButtonAuto->setChecked(false);

        gridLayout_4->addWidget(radioButtonAuto, 0, 1, 1, 1);

        spinBoxNameLine = new QSpinBox(groupBox_6);
        spinBoxNameLine->setObjectName(QString::fromUtf8("spinBoxNameLine"));
        spinBoxNameLine->setMinimum(1);
        spinBoxNameLine->setValue(1);

        gridLayout_4->addWidget(spinBoxNameLine, 0, 2, 1, 1);


        gridLayout_7->addWidget(groupBox_6, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(groupBox_5);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_6 = new QGridLayout(groupBox_7);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_8 = new QLabel(groupBox_7);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        spinBoxPrivewNumber = new QSpinBox(groupBox_7);
        spinBoxPrivewNumber->setObjectName(QString::fromUtf8("spinBoxPrivewNumber"));
        spinBoxPrivewNumber->setMinimum(1);
        spinBoxPrivewNumber->setValue(20);

        gridLayout_6->addWidget(spinBoxPrivewNumber, 0, 1, 1, 1);


        gridLayout_7->addWidget(groupBox_7, 0, 1, 1, 1);

        tableWidgetPreHeader = new QTableWidget(groupBox_5);
        tableWidgetPreHeader->setObjectName(QString::fromUtf8("tableWidgetPreHeader"));
        tableWidgetPreHeader->setMaximumSize(QSize(16777215, 60));
        tableWidgetPreHeader->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_7->addWidget(tableWidgetPreHeader, 1, 0, 1, 2);


        gridLayout_8->addWidget(groupBox_5, 3, 0, 1, 2);


        retranslateUi(PageASCIIFileClass);

        QMetaObject::connectSlotsByName(PageASCIIFileClass);
    } // setupUi

    void retranslateUi(QWidget *PageASCIIFileClass)
    {
        PageASCIIFileClass->setWindowTitle(QCoreApplication::translate("PageASCIIFileClass", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageASCIIFileClass", "File Properties", nullptr));
        label->setText(QCoreApplication::translate("PageASCIIFileClass", "File name:", nullptr));
        label_2->setText(QCoreApplication::translate("PageASCIIFileClass", "Numbers of lines:", nullptr));
        label_3->setText(QCoreApplication::translate("PageASCIIFileClass", "Invalid value:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PageASCIIFileClass", "Importing range", nullptr));
        label_5->setText(QCoreApplication::translate("PageASCIIFileClass", "To line:", nullptr));
        lineEditToLine->setText(QCoreApplication::translate("PageASCIIFileClass", "EOF", nullptr));
        label_4->setText(QCoreApplication::translate("PageASCIIFileClass", "From line:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("PageASCIIFileClass", "Delimiters", nullptr));
        checkBoxComma->setText(QCoreApplication::translate("PageASCIIFileClass", "Comma(,)", nullptr));
        checkBoxSemiColon->setText(QCoreApplication::translate("PageASCIIFileClass", "Semicolon(;)", nullptr));
        checkBoxColon->setText(QCoreApplication::translate("PageASCIIFileClass", "Colon(:)", nullptr));
        checkBoxTab->setText(QCoreApplication::translate("PageASCIIFileClass", "Tab", nullptr));
        checkBoxSpace->setText(QCoreApplication::translate("PageASCIIFileClass", "Space", nullptr));
        checkBoxDOther->setText(QCoreApplication::translate("PageASCIIFileClass", "Other:", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("PageASCIIFileClass", "Text qualifiers", nullptr));
        checkBoxDQ->setText(QCoreApplication::translate("PageASCIIFileClass", "Double quotes(\")", nullptr));
        checkBoxSQ->setText(QCoreApplication::translate("PageASCIIFileClass", "Single quotes(')", nullptr));
        checkBoxQOther->setText(QCoreApplication::translate("PageASCIIFileClass", "Other:", nullptr));
        checkBoxAllowBlank->setText(QCoreApplication::translate("PageASCIIFileClass", "Allow zero length", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("PageASCIIFileClass", "Columns Names", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("PageASCIIFileClass", "Col names from:", nullptr));
        radioButtonLastUsed->setText(QCoreApplication::translate("PageASCIIFileClass", "Last used", nullptr));
        radioButtonAuto->setText(QCoreApplication::translate("PageASCIIFileClass", "Automatic from line:", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("PageASCIIFileClass", "Preview", nullptr));
        label_8->setText(QCoreApplication::translate("PageASCIIFileClass", "Preview lines:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageASCIIFileClass: public Ui_PageASCIIFileClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEASCIIFILE_H
