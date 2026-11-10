/********************************************************************************
** Form generated from reading UI file 'xspreadsheetconf.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XSPREADSHEETCONF_H
#define UI_XSPREADSHEETCONF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SpreadsheetConf
{
public:
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEditStart;
    QLabel *labelStop;
    QLineEdit *lineEditStop;
    QSpinBox *spinBox;
    QLabel *label_3;
    QLabel *labelStart;
    QPushButton *pushButton;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *SpreadsheetConf)
    {
        if (SpreadsheetConf->objectName().isEmpty())
            SpreadsheetConf->setObjectName(QString::fromUtf8("SpreadsheetConf"));
        SpreadsheetConf->resize(394, 466);
        gridLayout_2 = new QGridLayout(SpreadsheetConf);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidget = new QTableWidget(SpreadsheetConf);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 1);

        groupBox = new QGroupBox(SpreadsheetConf);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditStart = new QLineEdit(groupBox);
        lineEditStart->setObjectName(QString::fromUtf8("lineEditStart"));

        gridLayout->addWidget(lineEditStart, 0, 1, 1, 1);

        labelStop = new QLabel(groupBox);
        labelStop->setObjectName(QString::fromUtf8("labelStop"));

        gridLayout->addWidget(labelStop, 0, 2, 1, 1);

        lineEditStop = new QLineEdit(groupBox);
        lineEditStop->setObjectName(QString::fromUtf8("lineEditStop"));

        gridLayout->addWidget(lineEditStop, 0, 3, 1, 1);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(10);

        gridLayout->addWidget(spinBox, 0, 5, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 4, 1, 1);

        labelStart = new QLabel(groupBox);
        labelStart->setObjectName(QString::fromUtf8("labelStart"));

        gridLayout->addWidget(labelStart, 0, 0, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 5, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(SpreadsheetConf);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(SpreadsheetConf);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout_2->addLayout(hboxLayout, 2, 0, 1, 1);


        retranslateUi(SpreadsheetConf);
        QObject::connect(okButton, SIGNAL(clicked()), SpreadsheetConf, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), SpreadsheetConf, SLOT(reject()));

        QMetaObject::connectSlotsByName(SpreadsheetConf);
    } // setupUi

    void retranslateUi(QDialog *SpreadsheetConf)
    {
        SpreadsheetConf->setWindowTitle(QCoreApplication::translate("SpreadsheetConf", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SpreadsheetConf", "Display Range", nullptr));
        labelStop->setText(QCoreApplication::translate("SpreadsheetConf", "End", nullptr));
        spinBox->setSuffix(QString());
        label_3->setText(QCoreApplication::translate("SpreadsheetConf", "Step", nullptr));
        labelStart->setText(QCoreApplication::translate("SpreadsheetConf", "Start", nullptr));
        pushButton->setText(QCoreApplication::translate("SpreadsheetConf", "Reset", nullptr));
        okButton->setText(QCoreApplication::translate("SpreadsheetConf", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("SpreadsheetConf", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpreadsheetConf: public Ui_SpreadsheetConf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XSPREADSHEETCONF_H
