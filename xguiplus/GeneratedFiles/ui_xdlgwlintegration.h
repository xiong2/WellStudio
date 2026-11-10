/********************************************************************************
** Form generated from reading UI file 'xdlgwlintegration.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGWLINTEGRATION_H
#define UI_XDLGWLINTEGRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_XDlgWLIntegration
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *lineEditCurve;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditP0;
    QLabel *label_4;
    QLineEdit *lineEditA;
    QLabel *label_5;
    QLineEdit *lineEditB;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *XDlgWLIntegration)
    {
        if (XDlgWLIntegration->objectName().isEmpty())
            XDlgWLIntegration->setObjectName(QString::fromUtf8("XDlgWLIntegration"));
        XDlgWLIntegration->resize(224, 200);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(XDlgWLIntegration->sizePolicy().hasHeightForWidth());
        XDlgWLIntegration->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(XDlgWLIntegration);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(XDlgWLIntegration);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEditCurve = new QLineEdit(XDlgWLIntegration);
        lineEditCurve->setObjectName(QString::fromUtf8("lineEditCurve"));

        gridLayout_2->addWidget(lineEditCurve, 0, 1, 1, 1);

        groupBox = new QGroupBox(XDlgWLIntegration);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        lineEditP0 = new QLineEdit(groupBox);
        lineEditP0->setObjectName(QString::fromUtf8("lineEditP0"));

        gridLayout->addWidget(lineEditP0, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lineEditA = new QLineEdit(groupBox);
        lineEditA->setObjectName(QString::fromUtf8("lineEditA"));

        gridLayout->addWidget(lineEditA, 2, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        lineEditB = new QLineEdit(groupBox);
        lineEditB->setObjectName(QString::fromUtf8("lineEditB"));

        gridLayout->addWidget(lineEditB, 3, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(XDlgWLIntegration);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(XDlgWLIntegration);
        QObject::connect(buttonBox, SIGNAL(rejected()), XDlgWLIntegration, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), XDlgWLIntegration, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgWLIntegration);
    } // setupUi

    void retranslateUi(QDialog *XDlgWLIntegration)
    {
        XDlgWLIntegration->setWindowTitle(QCoreApplication::translate("XDlgWLIntegration", "XDlgWLIntegration", nullptr));
        label->setText(QCoreApplication::translate("XDlgWLIntegration", "Output Curve:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("XDlgWLIntegration", "Amoco Method", nullptr));
        label_2->setText(QCoreApplication::translate("XDlgWLIntegration", "P = P0 + A * Depth ** B", nullptr));
        label_3->setText(QCoreApplication::translate("XDlgWLIntegration", "P0 (g/cc)", nullptr));
        lineEditP0->setText(QCoreApplication::translate("XDlgWLIntegration", "1.95", nullptr));
        label_4->setText(QCoreApplication::translate("XDlgWLIntegration", "A", nullptr));
        lineEditA->setText(QCoreApplication::translate("XDlgWLIntegration", "0.55", nullptr));
        label_5->setText(QCoreApplication::translate("XDlgWLIntegration", "B", nullptr));
        lineEditB->setText(QCoreApplication::translate("XDlgWLIntegration", "0.045", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgWLIntegration: public Ui_XDlgWLIntegration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGWLINTEGRATION_H
