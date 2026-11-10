/********************************************************************************
** Form generated from reading UI file 'xdlgnewobject.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGNEWOBJECT_H
#define UI_XDLGNEWOBJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXDlgNewObject
{
public:
    QGridLayout *gridLayout;
    QLabel *label_name;
    QLineEdit *lineEdit;
    QLabel *label_color;
    CXButtonColorEdit *pushButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CXDlgNewObject)
    {
        if (CXDlgNewObject->objectName().isEmpty())
            CXDlgNewObject->setObjectName(QString::fromUtf8("CXDlgNewObject"));
        CXDlgNewObject->resize(378, 128);
        gridLayout = new QGridLayout(CXDlgNewObject);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_name = new QLabel(CXDlgNewObject);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        gridLayout->addWidget(label_name, 0, 0, 1, 1);

        lineEdit = new QLineEdit(CXDlgNewObject);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_color = new QLabel(CXDlgNewObject);
        label_color->setObjectName(QString::fromUtf8("label_color"));

        gridLayout->addWidget(label_color, 1, 0, 1, 1);

        pushButton = new CXButtonColorEdit(CXDlgNewObject);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 52, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);


        retranslateUi(CXDlgNewObject);

        QMetaObject::connectSlotsByName(CXDlgNewObject);
    } // setupUi

    void retranslateUi(QDialog *CXDlgNewObject)
    {
        CXDlgNewObject->setWindowTitle(QCoreApplication::translate("CXDlgNewObject", "CXDlgNewObject", nullptr));
        label_name->setText(QCoreApplication::translate("CXDlgNewObject", "Object Name:", nullptr));
        label_color->setText(QCoreApplication::translate("CXDlgNewObject", "Object Color:", nullptr));
        pushButton->setText(QCoreApplication::translate("CXDlgNewObject", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgNewObject: public Ui_CXDlgNewObject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGNEWOBJECT_H
