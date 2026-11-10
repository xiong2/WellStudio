/********************************************************************************
** Form generated from reading UI file 'xdlglfmtohorizon.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGLFMTOHORIZON_H
#define UI_XDLGLFMTOHORIZON_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CXDlgLFMToHorizon
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonSelectAll;
    QPushButton *pushButtonUnselectAll;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CXDlgLFMToHorizon)
    {
        if (CXDlgLFMToHorizon->objectName().isEmpty())
            CXDlgLFMToHorizon->setObjectName(QString::fromUtf8("CXDlgLFMToHorizon"));
        CXDlgLFMToHorizon->resize(377, 364);
        gridLayout = new QGridLayout(CXDlgLFMToHorizon);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget = new QListWidget(CXDlgLFMToHorizon);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 3, 2);

        verticalSpacer = new QSpacerItem(20, 228, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 2, 1, 1);

        pushButtonSelectAll = new QPushButton(CXDlgLFMToHorizon);
        pushButtonSelectAll->setObjectName(QString::fromUtf8("pushButtonSelectAll"));
        pushButtonSelectAll->setMaximumSize(QSize(60, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/SelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSelectAll->setIcon(icon);

        gridLayout->addWidget(pushButtonSelectAll, 1, 2, 1, 1);

        pushButtonUnselectAll = new QPushButton(CXDlgLFMToHorizon);
        pushButtonUnselectAll->setObjectName(QString::fromUtf8("pushButtonUnselectAll"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/DisSelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonUnselectAll->setIcon(icon1);

        gridLayout->addWidget(pushButtonUnselectAll, 2, 2, 1, 1);

        label = new QLabel(CXDlgLFMToHorizon);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        lineEdit = new QLineEdit(CXDlgLFMToHorizon);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 3, 1, 1, 2);

        buttonBox = new QDialogButtonBox(CXDlgLFMToHorizon);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 1, 1, 2);


        retranslateUi(CXDlgLFMToHorizon);

        QMetaObject::connectSlotsByName(CXDlgLFMToHorizon);
    } // setupUi

    void retranslateUi(QDialog *CXDlgLFMToHorizon)
    {
        CXDlgLFMToHorizon->setWindowTitle(QCoreApplication::translate("CXDlgLFMToHorizon", "CXDlgLFMToHorizon", nullptr));
        pushButtonSelectAll->setText(QString());
        pushButtonUnselectAll->setText(QString());
        label->setText(QCoreApplication::translate("CXDlgLFMToHorizon", "Output Horizons' Base Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgLFMToHorizon: public Ui_CXDlgLFMToHorizon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGLFMTOHORIZON_H
