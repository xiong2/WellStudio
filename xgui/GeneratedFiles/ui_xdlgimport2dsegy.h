/********************************************************************************
** Form generated from reading UI file 'xdlgimport2dsegy.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGIMPORT2DSEGY_H
#define UI_XDLGIMPORT2DSEGY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CXDlgImport2DSEGY
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEditSurvey;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QRadioButton *radioButtonTime;
    QRadioButton *radioButtonDepth;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QComboBox *comboBoxUnit;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QPushButton *pushButtonAddFiles;
    QPushButton *pushButtonRemvoeFiles;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CXDlgImport2DSEGY)
    {
        if (CXDlgImport2DSEGY->objectName().isEmpty())
            CXDlgImport2DSEGY->setObjectName(QString::fromUtf8("CXDlgImport2DSEGY"));
        CXDlgImport2DSEGY->resize(819, 420);
        gridLayout = new QGridLayout(CXDlgImport2DSEGY);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CXDlgImport2DSEGY);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditSurvey = new QLineEdit(CXDlgImport2DSEGY);
        lineEditSurvey->setObjectName(QString::fromUtf8("lineEditSurvey"));

        gridLayout->addWidget(lineEditSurvey, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(63, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label_2 = new QLabel(CXDlgImport2DSEGY);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        radioButtonTime = new QRadioButton(CXDlgImport2DSEGY);
        radioButtonTime->setObjectName(QString::fromUtf8("radioButtonTime"));
        radioButtonTime->setChecked(true);

        gridLayout->addWidget(radioButtonTime, 0, 4, 1, 1);

        radioButtonDepth = new QRadioButton(CXDlgImport2DSEGY);
        radioButtonDepth->setObjectName(QString::fromUtf8("radioButtonDepth"));

        gridLayout->addWidget(radioButtonDepth, 0, 5, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(63, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 6, 1, 1);

        label_3 = new QLabel(CXDlgImport2DSEGY);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 7, 1, 1);

        comboBoxUnit = new QComboBox(CXDlgImport2DSEGY);
        comboBoxUnit->addItem(QString());
        comboBoxUnit->addItem(QString());
        comboBoxUnit->setObjectName(QString::fromUtf8("comboBoxUnit"));

        gridLayout->addWidget(comboBoxUnit, 0, 8, 1, 1);

        horizontalSpacer = new QSpacerItem(138, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 9, 1, 1);

        tableWidget = new QTableWidget(CXDlgImport2DSEGY);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 10);

        pushButtonAddFiles = new QPushButton(CXDlgImport2DSEGY);
        pushButtonAddFiles->setObjectName(QString::fromUtf8("pushButtonAddFiles"));
        pushButtonAddFiles->setMinimumSize(QSize(100, 0));
        pushButtonAddFiles->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(pushButtonAddFiles, 2, 0, 1, 1);

        pushButtonRemvoeFiles = new QPushButton(CXDlgImport2DSEGY);
        pushButtonRemvoeFiles->setObjectName(QString::fromUtf8("pushButtonRemvoeFiles"));
        pushButtonRemvoeFiles->setEnabled(false);
        pushButtonRemvoeFiles->setMinimumSize(QSize(100, 0));
        pushButtonRemvoeFiles->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(pushButtonRemvoeFiles, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(CXDlgImport2DSEGY);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 6, 1, 4);


        retranslateUi(CXDlgImport2DSEGY);

        QMetaObject::connectSlotsByName(CXDlgImport2DSEGY);
    } // setupUi

    void retranslateUi(QDialog *CXDlgImport2DSEGY)
    {
        CXDlgImport2DSEGY->setWindowTitle(QCoreApplication::translate("CXDlgImport2DSEGY", "CXDlgImport2DSEGY", nullptr));
        label->setText(QCoreApplication::translate("CXDlgImport2DSEGY", "2D Survey:", nullptr));
        lineEditSurvey->setText(QCoreApplication::translate("CXDlgImport2DSEGY", "2D Survey", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgImport2DSEGY", "Domain:", nullptr));
        radioButtonTime->setText(QCoreApplication::translate("CXDlgImport2DSEGY", "Time", nullptr));
        radioButtonDepth->setText(QCoreApplication::translate("CXDlgImport2DSEGY", "Depth", nullptr));
        label_3->setText(QCoreApplication::translate("CXDlgImport2DSEGY", "Unit:", nullptr));
        comboBoxUnit->setItemText(0, QCoreApplication::translate("CXDlgImport2DSEGY", "ms", nullptr));
        comboBoxUnit->setItemText(1, QCoreApplication::translate("CXDlgImport2DSEGY", "s", nullptr));

        pushButtonAddFiles->setText(QCoreApplication::translate("CXDlgImport2DSEGY", "Add files...", nullptr));
        pushButtonRemvoeFiles->setText(QCoreApplication::translate("CXDlgImport2DSEGY", "Remove files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgImport2DSEGY: public Ui_CXDlgImport2DSEGY {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGIMPORT2DSEGY_H
