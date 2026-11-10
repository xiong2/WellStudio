/********************************************************************************
** Form generated from reading UI file 'xlicense.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XLICENSE_H
#define UI_XLICENSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXLicenseClass
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *edit_Username;
    QLabel *label_2;
    QLineEdit *edit_PC;
    QLabel *label_3;
    QLineEdit *edit_MAC;
    QLabel *label_4;
    QDateEdit *dateEdit_Start;
    QLabel *label_5;
    QDateEdit *dateEdit_End;
    QCheckBox *chkb_NoLimits;
    QGroupBox *groupBoxApp;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_Local;
    QPushButton *btn_Test;
    QPushButton *btn_Generate;
    QPushButton *btn_GenerateOld;
    QPushButton *btn_Exit;

    void setupUi(QDialog *CXLicenseClass)
    {
        if (CXLicenseClass->objectName().isEmpty())
            CXLicenseClass->setObjectName(QString::fromUtf8("CXLicenseClass"));
        CXLicenseClass->resize(294, 186);
        gridLayout = new QGridLayout(CXLicenseClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(CXLicenseClass);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        edit_Username = new QLineEdit(CXLicenseClass);
        edit_Username->setObjectName(QString::fromUtf8("edit_Username"));

        formLayout->setWidget(0, QFormLayout::FieldRole, edit_Username);

        label_2 = new QLabel(CXLicenseClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        edit_PC = new QLineEdit(CXLicenseClass);
        edit_PC->setObjectName(QString::fromUtf8("edit_PC"));

        formLayout->setWidget(1, QFormLayout::FieldRole, edit_PC);

        label_3 = new QLabel(CXLicenseClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        edit_MAC = new QLineEdit(CXLicenseClass);
        edit_MAC->setObjectName(QString::fromUtf8("edit_MAC"));

        formLayout->setWidget(2, QFormLayout::FieldRole, edit_MAC);

        label_4 = new QLabel(CXLicenseClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        dateEdit_Start = new QDateEdit(CXLicenseClass);
        dateEdit_Start->setObjectName(QString::fromUtf8("dateEdit_Start"));

        formLayout->setWidget(3, QFormLayout::FieldRole, dateEdit_Start);

        label_5 = new QLabel(CXLicenseClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        dateEdit_End = new QDateEdit(CXLicenseClass);
        dateEdit_End->setObjectName(QString::fromUtf8("dateEdit_End"));

        formLayout->setWidget(4, QFormLayout::FieldRole, dateEdit_End);

        chkb_NoLimits = new QCheckBox(CXLicenseClass);
        chkb_NoLimits->setObjectName(QString::fromUtf8("chkb_NoLimits"));

        formLayout->setWidget(5, QFormLayout::FieldRole, chkb_NoLimits);


        gridLayout->addLayout(formLayout, 1, 0, 1, 1);

        groupBoxApp = new QGroupBox(CXLicenseClass);
        groupBoxApp->setObjectName(QString::fromUtf8("groupBoxApp"));

        gridLayout->addWidget(groupBoxApp, 0, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btn_Local = new QPushButton(CXLicenseClass);
        btn_Local->setObjectName(QString::fromUtf8("btn_Local"));

        verticalLayout->addWidget(btn_Local);

        btn_Test = new QPushButton(CXLicenseClass);
        btn_Test->setObjectName(QString::fromUtf8("btn_Test"));

        verticalLayout->addWidget(btn_Test);

        btn_Generate = new QPushButton(CXLicenseClass);
        btn_Generate->setObjectName(QString::fromUtf8("btn_Generate"));

        verticalLayout->addWidget(btn_Generate);

        btn_GenerateOld = new QPushButton(CXLicenseClass);
        btn_GenerateOld->setObjectName(QString::fromUtf8("btn_GenerateOld"));

        verticalLayout->addWidget(btn_GenerateOld);

        btn_Exit = new QPushButton(CXLicenseClass);
        btn_Exit->setObjectName(QString::fromUtf8("btn_Exit"));

        verticalLayout->addWidget(btn_Exit);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);


        retranslateUi(CXLicenseClass);
        QObject::connect(btn_Exit, SIGNAL(pressed()), CXLicenseClass, SLOT(reject()));
        QObject::connect(chkb_NoLimits, SIGNAL(toggled(bool)), edit_MAC, SLOT(setDisabled(bool)));
        QObject::connect(chkb_NoLimits, SIGNAL(toggled(bool)), edit_PC, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(CXLicenseClass);
    } // setupUi

    void retranslateUi(QDialog *CXLicenseClass)
    {
        CXLicenseClass->setWindowTitle(QCoreApplication::translate("CXLicenseClass", "License Generator", nullptr));
        label->setText(QCoreApplication::translate("CXLicenseClass", "Username:", nullptr));
        label_2->setText(QCoreApplication::translate("CXLicenseClass", "PC name:", nullptr));
        label_3->setText(QCoreApplication::translate("CXLicenseClass", "MAC:", nullptr));
        edit_MAC->setInputMask(QCoreApplication::translate("CXLicenseClass", "HH:HH:HH:HH:HH:HH", nullptr));
        label_4->setText(QCoreApplication::translate("CXLicenseClass", "From:", nullptr));
        label_5->setText(QCoreApplication::translate("CXLicenseClass", "To:", nullptr));
        chkb_NoLimits->setText(QCoreApplication::translate("CXLicenseClass", "No Limits", nullptr));
        groupBoxApp->setTitle(QCoreApplication::translate("CXLicenseClass", "Apps", nullptr));
        btn_Local->setText(QCoreApplication::translate("CXLicenseClass", "Local", nullptr));
        btn_Test->setText(QCoreApplication::translate("CXLicenseClass", "Test", nullptr));
        btn_Generate->setText(QCoreApplication::translate("CXLicenseClass", "Generate", nullptr));
        btn_GenerateOld->setText(QCoreApplication::translate("CXLicenseClass", "GenerateOld", nullptr));
        btn_Exit->setText(QCoreApplication::translate("CXLicenseClass", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXLicenseClass: public Ui_CXLicenseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XLICENSE_H
