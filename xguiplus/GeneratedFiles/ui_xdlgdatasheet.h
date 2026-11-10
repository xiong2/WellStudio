/********************************************************************************
** Form generated from reading UI file 'xdlgdatasheet.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGDATASHEET_H
#define UI_XDLGDATASHEET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_CXDlgDataSheet
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButtonInsert;
    QToolButton *toolButtonAppend;
    QToolButton *toolButtonRemove;
    QToolButton *toolButtonRL;
    QToolButton *toolButtonFlush;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QTableView *tableView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CXDlgDataSheet)
    {
        if (CXDlgDataSheet->objectName().isEmpty())
            CXDlgDataSheet->setObjectName(QString::fromUtf8("CXDlgDataSheet"));
        CXDlgDataSheet->resize(744, 677);
        gridLayout = new QGridLayout(CXDlgDataSheet);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButtonInsert = new QToolButton(CXDlgDataSheet);
        toolButtonInsert->setObjectName(QString::fromUtf8("toolButtonInsert"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/RowInsert.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonInsert->setIcon(icon);

        horizontalLayout_2->addWidget(toolButtonInsert);

        toolButtonAppend = new QToolButton(CXDlgDataSheet);
        toolButtonAppend->setObjectName(QString::fromUtf8("toolButtonAppend"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/RowAppend.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonAppend->setIcon(icon1);

        horizontalLayout_2->addWidget(toolButtonAppend);

        toolButtonRemove = new QToolButton(CXDlgDataSheet);
        toolButtonRemove->setObjectName(QString::fromUtf8("toolButtonRemove"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/RowRemove.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRemove->setIcon(icon2);

        horizontalLayout_2->addWidget(toolButtonRemove);

        toolButtonRL = new QToolButton(CXDlgDataSheet);
        toolButtonRL->setObjectName(QString::fromUtf8("toolButtonRL"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/RowRemoveLast.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonRL->setIcon(icon3);

        horizontalLayout_2->addWidget(toolButtonRL);

        toolButtonFlush = new QToolButton(CXDlgDataSheet);
        toolButtonFlush->setObjectName(QString::fromUtf8("toolButtonFlush"));
        toolButtonFlush->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/Flush.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonFlush->setIcon(icon4);

        horizontalLayout_2->addWidget(toolButtonFlush);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(CXDlgDataSheet);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Icon/HelpInfo.png")));

        horizontalLayout_2->addWidget(label);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        tableView = new QTableView(CXDlgDataSheet);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(CXDlgDataSheet);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Save);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(CXDlgDataSheet);
        QObject::connect(buttonBox, SIGNAL(accepted()), CXDlgDataSheet, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CXDlgDataSheet, SLOT(reject()));

        QMetaObject::connectSlotsByName(CXDlgDataSheet);
    } // setupUi

    void retranslateUi(QDialog *CXDlgDataSheet)
    {
        CXDlgDataSheet->setWindowTitle(QCoreApplication::translate("CXDlgDataSheet", "CXDlgDataSheet", nullptr));
        toolButtonInsert->setText(QCoreApplication::translate("CXDlgDataSheet", "...", nullptr));
        toolButtonAppend->setText(QCoreApplication::translate("CXDlgDataSheet", "...", nullptr));
        toolButtonRemove->setText(QCoreApplication::translate("CXDlgDataSheet", "...", nullptr));
        toolButtonRL->setText(QCoreApplication::translate("CXDlgDataSheet", "...", nullptr));
        toolButtonFlush->setText(QCoreApplication::translate("CXDlgDataSheet", "...", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXDlgDataSheet: public Ui_CXDlgDataSheet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGDATASHEET_H
