/********************************************************************************
** Form generated from reading UI file 'xdlgupdatesgy.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGUPDATESGY_H
#define UI_XDLGUPDATESGY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_XDlgUpdateSGY
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit_2;

    void setupUi(QDialog *XDlgUpdateSGY)
    {
        if (XDlgUpdateSGY->objectName().isEmpty())
            XDlgUpdateSGY->setObjectName(QString::fromUtf8("XDlgUpdateSGY"));
        XDlgUpdateSGY->resize(495, 100);
        gridLayout = new QGridLayout(XDlgUpdateSGY);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(XDlgUpdateSGY);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 3, 1, 1);

        lineEdit = new QLineEdit(XDlgUpdateSGY);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setReadOnly(true);

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        label_2 = new QLabel(XDlgUpdateSGY);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(XDlgUpdateSGY);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(XDlgUpdateSGY);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 2, 1, 2);

        lineEdit_2 = new QLineEdit(XDlgUpdateSGY);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 2, 1, 1);


        retranslateUi(XDlgUpdateSGY);
        QObject::connect(buttonBox, SIGNAL(rejected()), XDlgUpdateSGY, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), XDlgUpdateSGY, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgUpdateSGY);
    } // setupUi

    void retranslateUi(QDialog *XDlgUpdateSGY)
    {
        XDlgUpdateSGY->setWindowTitle(QCoreApplication::translate("XDlgUpdateSGY", "Update all SEGY files", nullptr));
        pushButton->setText(QCoreApplication::translate("XDlgUpdateSGY", "...", nullptr));
        label_2->setText(QCoreApplication::translate("XDlgUpdateSGY", "Start ID:", nullptr));
        label->setText(QCoreApplication::translate("XDlgUpdateSGY", "Select the directory:", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("XDlgUpdateSGY", "10007", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgUpdateSGY: public Ui_XDlgUpdateSGY {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGUPDATESGY_H
