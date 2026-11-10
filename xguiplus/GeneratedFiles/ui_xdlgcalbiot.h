/********************************************************************************
** Form generated from reading UI file 'xdlgcalbiot.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGCALBIOT_H
#define UI_XDLGCALBIOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_XDlgCalBiot
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLineEdit *lineEditP;
    QLabel *label_5;
    QLineEdit *lineEditVp;
    QLabel *label_6;
    QLineEdit *lineEditVs;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QComboBox *comboBox;
    QLabel *label_8;
    QComboBox *comboBox_2;
    QLabel *label_9;
    QComboBox *comboBox_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLineEdit *lineEditDV;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *XDlgCalBiot)
    {
        if (XDlgCalBiot->objectName().isEmpty())
            XDlgCalBiot->setObjectName(QString::fromUtf8("XDlgCalBiot"));
        XDlgCalBiot->resize(475, 234);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        XDlgCalBiot->setFont(font);
        gridLayout_3 = new QGridLayout(XDlgCalBiot);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(XDlgCalBiot);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        lineEditP = new QLineEdit(groupBox);
        lineEditP->setObjectName(QString::fromUtf8("lineEditP"));

        gridLayout->addWidget(lineEditP, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        lineEditVp = new QLineEdit(groupBox);
        lineEditVp->setObjectName(QString::fromUtf8("lineEditVp"));

        gridLayout->addWidget(lineEditVp, 0, 3, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 4, 1, 1);

        lineEditVs = new QLineEdit(groupBox);
        lineEditVs->setObjectName(QString::fromUtf8("lineEditVs"));

        gridLayout->addWidget(lineEditVs, 0, 5, 1, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 3);

        groupBox_2 = new QGroupBox(XDlgCalBiot);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(20, 16777215));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_7->setFont(font1);

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(20, 16777215));
        label_8->setFont(font1);

        gridLayout_2->addWidget(label_8, 0, 2, 1, 1);

        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 0, 3, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMaximumSize(QSize(20, 16777215));
        QFont font2;
        font2.setPointSize(10);
        label_9->setFont(font2);

        gridLayout_2->addWidget(label_9, 0, 4, 1, 1);

        comboBox_3 = new QComboBox(groupBox_2);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout_2->addWidget(comboBox_3, 0, 5, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 3, 0, 1, 3);

        label_2 = new QLabel(XDlgCalBiot);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 57, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 4, 1, 1, 1);

        label = new QLabel(XDlgCalBiot);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font3;
        font3.setPointSize(12);
        label->setFont(font3);

        gridLayout_3->addWidget(label, 0, 0, 1, 2);

        lineEditDV = new QLineEdit(XDlgCalBiot);
        lineEditDV->setObjectName(QString::fromUtf8("lineEditDV"));

        gridLayout_3->addWidget(lineEditDV, 1, 1, 1, 2);

        buttonBox = new QDialogButtonBox(XDlgCalBiot);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 5, 2, 1, 1);


        retranslateUi(XDlgCalBiot);
        QObject::connect(buttonBox, SIGNAL(rejected()), XDlgCalBiot, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), XDlgCalBiot, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgCalBiot);
    } // setupUi

    void retranslateUi(QDialog *XDlgCalBiot)
    {
        XDlgCalBiot->setWindowTitle(QCoreApplication::translate("XDlgCalBiot", "XDlgCalBiot", nullptr));
        groupBox->setTitle(QCoreApplication::translate("XDlgCalBiot", "Matrix parameters", nullptr));
        label_4->setText(QCoreApplication::translate("XDlgCalBiot", "\317\201 (g/cc)", nullptr));
        lineEditP->setText(QCoreApplication::translate("XDlgCalBiot", "2.65", nullptr));
        label_5->setText(QCoreApplication::translate("XDlgCalBiot", "Vpm (m/s)", nullptr));
        lineEditVp->setText(QCoreApplication::translate("XDlgCalBiot", "5494.5", nullptr));
        label_6->setText(QCoreApplication::translate("XDlgCalBiot", "Vsm (m/s)", nullptr));
        lineEditVs->setText(QCoreApplication::translate("XDlgCalBiot", "3460.2", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("XDlgCalBiot", "Strata parameters", nullptr));
        label_7->setText(QCoreApplication::translate("XDlgCalBiot", "\317\201", nullptr));
        label_8->setText(QCoreApplication::translate("XDlgCalBiot", "Vp", nullptr));
        label_9->setText(QCoreApplication::translate("XDlgCalBiot", "Vs", nullptr));
        label_2->setText(QCoreApplication::translate("XDlgCalBiot", "Output volume(\316\261\357\274\211\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("XDlgCalBiot", "Calculate Biot Coefficient", nullptr));
        lineEditDV->setText(QCoreApplication::translate("XDlgCalBiot", "BiotDV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgCalBiot: public Ui_XDlgCalBiot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGCALBIOT_H
