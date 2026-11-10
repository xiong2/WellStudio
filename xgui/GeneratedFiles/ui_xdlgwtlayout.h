/********************************************************************************
** Form generated from reading UI file 'xdlgwtlayout.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGWTLAYOUT_H
#define UI_XDLGWTLAYOUT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_XDlgWTLayout
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *checkBoxAC;
    QCheckBox *checkBoxRC_4;
    QCheckBox *checkBoxDen;
    QCheckBox *checkBoxRC_5;
    QCheckBox *checkBoxRC;
    QCheckBox *checkBoxRC_6;
    QCheckBox *checkBoxDT;
    QCheckBox *checkBoxDrift;
    QLabel *label_3;
    QSpinBox *spinBox;
    QLabel *label;
    QComboBox *comboBoxLeft;
    QLabel *label_2;
    QComboBox *comboBoxRight;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *XDlgWTLayout)
    {
        if (XDlgWTLayout->objectName().isEmpty())
            XDlgWTLayout->setObjectName(QString::fromUtf8("XDlgWTLayout"));
        XDlgWTLayout->resize(261, 279);
        gridLayout_2 = new QGridLayout(XDlgWTLayout);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(XDlgWTLayout);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBoxAC = new QCheckBox(groupBox);
        checkBoxAC->setObjectName(QString::fromUtf8("checkBoxAC"));
        checkBoxAC->setChecked(true);

        gridLayout->addWidget(checkBoxAC, 0, 0, 1, 1);

        checkBoxRC_4 = new QCheckBox(groupBox);
        checkBoxRC_4->setObjectName(QString::fromUtf8("checkBoxRC_4"));
        checkBoxRC_4->setEnabled(false);
        checkBoxRC_4->setCheckable(true);
        checkBoxRC_4->setChecked(true);

        gridLayout->addWidget(checkBoxRC_4, 0, 1, 1, 1);

        checkBoxDen = new QCheckBox(groupBox);
        checkBoxDen->setObjectName(QString::fromUtf8("checkBoxDen"));
        checkBoxDen->setChecked(true);

        gridLayout->addWidget(checkBoxDen, 1, 0, 1, 1);

        checkBoxRC_5 = new QCheckBox(groupBox);
        checkBoxRC_5->setObjectName(QString::fromUtf8("checkBoxRC_5"));
        checkBoxRC_5->setEnabled(false);
        checkBoxRC_5->setChecked(true);

        gridLayout->addWidget(checkBoxRC_5, 1, 1, 1, 1);

        checkBoxRC = new QCheckBox(groupBox);
        checkBoxRC->setObjectName(QString::fromUtf8("checkBoxRC"));
        checkBoxRC->setChecked(true);

        gridLayout->addWidget(checkBoxRC, 2, 0, 1, 1);

        checkBoxRC_6 = new QCheckBox(groupBox);
        checkBoxRC_6->setObjectName(QString::fromUtf8("checkBoxRC_6"));
        checkBoxRC_6->setEnabled(false);
        checkBoxRC_6->setChecked(true);

        gridLayout->addWidget(checkBoxRC_6, 2, 1, 1, 1);

        checkBoxDT = new QCheckBox(groupBox);
        checkBoxDT->setObjectName(QString::fromUtf8("checkBoxDT"));
        checkBoxDT->setChecked(true);

        gridLayout->addWidget(checkBoxDT, 3, 0, 1, 1);

        checkBoxDrift = new QCheckBox(groupBox);
        checkBoxDrift->setObjectName(QString::fromUtf8("checkBoxDrift"));
        checkBoxDrift->setChecked(true);

        gridLayout->addWidget(checkBoxDrift, 4, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 3);

        label_3 = new QLabel(XDlgWTLayout);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 2);

        spinBox = new QSpinBox(XDlgWTLayout);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(5);
        spinBox->setMaximum(21);
        spinBox->setSingleStep(2);
        spinBox->setValue(9);

        gridLayout_2->addWidget(spinBox, 1, 2, 2, 1);

        label = new QLabel(XDlgWTLayout);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 3, 0, 1, 1);

        comboBoxLeft = new QComboBox(XDlgWTLayout);
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->addItem(QString());
        comboBoxLeft->setObjectName(QString::fromUtf8("comboBoxLeft"));

        gridLayout_2->addWidget(comboBoxLeft, 3, 2, 1, 1);

        label_2 = new QLabel(XDlgWTLayout);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 4, 0, 1, 1);

        comboBoxRight = new QComboBox(XDlgWTLayout);
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->addItem(QString());
        comboBoxRight->setObjectName(QString::fromUtf8("comboBoxRight"));

        gridLayout_2->addWidget(comboBoxRight, 4, 2, 1, 1);

        pushButton_2 = new QPushButton(XDlgWTLayout);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/OK.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon);

        gridLayout_2->addWidget(pushButton_2, 5, 1, 1, 1);

        pushButton = new QPushButton(XDlgWTLayout);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);

        gridLayout_2->addWidget(pushButton, 5, 2, 1, 1);


        retranslateUi(XDlgWTLayout);
        QObject::connect(pushButton_2, SIGNAL(clicked()), XDlgWTLayout, SLOT(accept()));
        QObject::connect(pushButton, SIGNAL(clicked()), XDlgWTLayout, SLOT(reject()));

        comboBoxRight->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(XDlgWTLayout);
    } // setupUi

    void retranslateUi(QDialog *XDlgWTLayout)
    {
        XDlgWTLayout->setWindowTitle(QCoreApplication::translate("XDlgWTLayout", "Well Tie Layout", nullptr));
        groupBox->setTitle(QCoreApplication::translate("XDlgWTLayout", "Display Track", nullptr));
        checkBoxAC->setText(QCoreApplication::translate("XDlgWTLayout", "AC Curve", nullptr));
        checkBoxRC_4->setText(QCoreApplication::translate("XDlgWTLayout", "Synthetic Seismo", nullptr));
        checkBoxDen->setText(QCoreApplication::translate("XDlgWTLayout", "Density Curve", nullptr));
        checkBoxRC_5->setText(QCoreApplication::translate("XDlgWTLayout", "Nearby Trace", nullptr));
        checkBoxRC->setText(QCoreApplication::translate("XDlgWTLayout", "RC Curve", nullptr));
        checkBoxRC_6->setText(QCoreApplication::translate("XDlgWTLayout", "Nearby Section", nullptr));
        checkBoxDT->setText(QCoreApplication::translate("XDlgWTLayout", "DT Curve", nullptr));
        checkBoxDrift->setText(QCoreApplication::translate("XDlgWTLayout", "Drift Curve", nullptr));
        label_3->setText(QCoreApplication::translate("XDlgWTLayout", "Nearby Section Trace Number", nullptr));
        label->setText(QCoreApplication::translate("XDlgWTLayout", "Left Annotation", nullptr));
        comboBoxLeft->setItemText(0, QCoreApplication::translate("XDlgWTLayout", "TWT", nullptr));
        comboBoxLeft->setItemText(1, QCoreApplication::translate("XDlgWTLayout", "MD", nullptr));
        comboBoxLeft->setItemText(2, QCoreApplication::translate("XDlgWTLayout", "TVD", nullptr));
        comboBoxLeft->setItemText(3, QCoreApplication::translate("XDlgWTLayout", "SSTVD", nullptr));

        label_2->setText(QCoreApplication::translate("XDlgWTLayout", "Right Annotation", nullptr));
        comboBoxRight->setItemText(0, QCoreApplication::translate("XDlgWTLayout", "TWT", nullptr));
        comboBoxRight->setItemText(1, QCoreApplication::translate("XDlgWTLayout", "MD", nullptr));
        comboBoxRight->setItemText(2, QCoreApplication::translate("XDlgWTLayout", "TVD", nullptr));
        comboBoxRight->setItemText(3, QCoreApplication::translate("XDlgWTLayout", "SSTVD", nullptr));

        pushButton_2->setText(QCoreApplication::translate("XDlgWTLayout", "OK", nullptr));
        pushButton->setText(QCoreApplication::translate("XDlgWTLayout", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgWTLayout: public Ui_XDlgWTLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGWTLAYOUT_H
