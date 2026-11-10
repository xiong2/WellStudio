/********************************************************************************
** Form generated from reading UI file 'xdlgmergedv.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGMERGEDV_H
#define UI_XDLGMERGEDV_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_XDlgMergeDV
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonL;
    QPushButton *pushButtonR;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButtonD;
    QPushButton *pushButtonU;
    QTableWidget *tableWidget_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *XDlgMergeDV)
    {
        if (XDlgMergeDV->objectName().isEmpty())
            XDlgMergeDV->setObjectName(QString::fromUtf8("XDlgMergeDV"));
        XDlgMergeDV->setWindowModality(Qt::WindowModal);
        XDlgMergeDV->resize(649, 420);
        gridLayout_3 = new QGridLayout(XDlgMergeDV);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(XDlgMergeDV);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(XDlgMergeDV);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_3->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(XDlgMergeDV);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(XDlgMergeDV);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_3->addWidget(lineEdit, 1, 1, 1, 1);

        groupBox = new QGroupBox(XDlgMergeDV);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        pushButtonL = new QPushButton(groupBox);
        pushButtonL->setObjectName(QString::fromUtf8("pushButtonL"));
        pushButtonL->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18805.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonL->setIcon(icon);

        gridLayout->addWidget(pushButtonL, 1, 1, 1, 1);

        pushButtonR = new QPushButton(groupBox);
        pushButtonR->setObjectName(QString::fromUtf8("pushButtonR"));
        pushButtonR->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonR->setIcon(icon1);

        gridLayout->addWidget(pushButtonR, 0, 1, 1, 1);

        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->horizontalHeader()->setDefaultSectionSize(160);

        gridLayout->addWidget(tableWidget, 0, 0, 3, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 2);

        groupBox_2 = new QGroupBox(XDlgMergeDV);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);

        pushButtonD = new QPushButton(groupBox_2);
        pushButtonD->setObjectName(QString::fromUtf8("pushButtonD"));
        pushButtonD->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/Downwards.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonD->setIcon(icon2);

        gridLayout_2->addWidget(pushButtonD, 1, 1, 1, 1);

        pushButtonU = new QPushButton(groupBox_2);
        pushButtonU->setObjectName(QString::fromUtf8("pushButtonU"));
        pushButtonU->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/Upwards.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonU->setIcon(icon3);

        gridLayout_2->addWidget(pushButtonU, 0, 1, 1, 1);

        tableWidget_2 = new QTableWidget(groupBox_2);
        if (tableWidget_2->columnCount() < 2)
            tableWidget_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(160);

        gridLayout_2->addWidget(tableWidget_2, 0, 0, 3, 1);


        gridLayout_3->addWidget(groupBox_2, 2, 2, 1, 1);

        buttonBox = new QDialogButtonBox(XDlgMergeDV);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 3, 2, 1, 1);


        retranslateUi(XDlgMergeDV);
        QObject::connect(buttonBox, SIGNAL(accepted()), XDlgMergeDV, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), XDlgMergeDV, SLOT(reject()));

        QMetaObject::connectSlotsByName(XDlgMergeDV);
    } // setupUi

    void retranslateUi(QDialog *XDlgMergeDV)
    {
        XDlgMergeDV->setWindowTitle(QCoreApplication::translate("XDlgMergeDV", "\345\220\210\345\271\266\345\234\260\351\234\207\344\275\223", nullptr));
        label->setText(QCoreApplication::translate("XDlgMergeDV", "\345\237\272\347\241\200\346\225\260\346\215\256\344\275\223", nullptr));
        label_2->setText(QCoreApplication::translate("XDlgMergeDV", "\350\276\223\345\207\272\346\225\260\346\215\256\344\275\223", nullptr));
        groupBox->setTitle(QCoreApplication::translate("XDlgMergeDV", "\345\217\257\351\200\211\346\225\260\346\215\256\344\275\223", nullptr));
        pushButtonL->setText(QString());
        pushButtonR->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("XDlgMergeDV", "\346\225\260\346\215\256\344\275\223", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("XDlgMergeDV", "\351\200\211\344\270\255\347\232\204\346\225\260\346\215\256\344\275\223", nullptr));
        pushButtonD->setText(QString());
        pushButtonU->setText(QString());
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("XDlgMergeDV", "\346\225\260\346\215\256\344\275\223", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("XDlgMergeDV", "\346\235\203\351\207\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgMergeDV: public Ui_XDlgMergeDV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGMERGEDV_H
