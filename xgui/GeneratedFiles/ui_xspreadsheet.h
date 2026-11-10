/********************************************************************************
** Form generated from reading UI file 'xspreadsheet.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XSPREADSHEET_H
#define UI_XSPREADSHEET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_Spreadsheet
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButtonConfigure;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QTableView *tableView;

    void setupUi(QDialog *Spreadsheet)
    {
        if (Spreadsheet->objectName().isEmpty())
            Spreadsheet->setObjectName(QString::fromUtf8("Spreadsheet"));
        Spreadsheet->resize(716, 671);
        gridLayout = new QGridLayout(Spreadsheet);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButtonConfigure = new QToolButton(Spreadsheet);
        toolButtonConfigure->setObjectName(QString::fromUtf8("toolButtonConfigure"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonConfigure->setIcon(icon);

        horizontalLayout->addWidget(toolButtonConfigure);

        toolButton_2 = new QToolButton(Spreadsheet);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));

        horizontalLayout->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(Spreadsheet);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));

        horizontalLayout->addWidget(toolButton_3);

        toolButton_4 = new QToolButton(Spreadsheet);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout->addWidget(toolButton_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(Spreadsheet);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);


        gridLayout->addLayout(hboxLayout, 2, 0, 1, 1);

        tableView = new QTableView(Spreadsheet);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 1, 0, 1, 1);


        retranslateUi(Spreadsheet);
        QObject::connect(okButton, SIGNAL(clicked()), Spreadsheet, SLOT(accept()));

        QMetaObject::connectSlotsByName(Spreadsheet);
    } // setupUi

    void retranslateUi(QDialog *Spreadsheet)
    {
        Spreadsheet->setWindowTitle(QCoreApplication::translate("Spreadsheet", "Dialog", nullptr));
#if QT_CONFIG(tooltip)
        toolButtonConfigure->setToolTip(QCoreApplication::translate("Spreadsheet", "\351\205\215\347\275\256...", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButtonConfigure->setText(QCoreApplication::translate("Spreadsheet", "...", nullptr));
        toolButton_2->setText(QCoreApplication::translate("Spreadsheet", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("Spreadsheet", "...", nullptr));
        toolButton_4->setText(QCoreApplication::translate("Spreadsheet", "...", nullptr));
        okButton->setText(QCoreApplication::translate("Spreadsheet", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Spreadsheet: public Ui_Spreadsheet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XSPREADSHEET_H
