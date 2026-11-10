/********************************************************************************
** Form generated from reading UI file 'xexportlas.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XEXPORTLAS_H
#define UI_XEXPORTLAS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
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
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ExportLAS
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonBrowse;
    QLabel *label_3;
    QLineEdit *lineEditDirectory;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *pushButtonAll;
    QPushButton *pushButtonNone;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ExportLAS)
    {
        if (ExportLAS->objectName().isEmpty())
            ExportLAS->setObjectName(QString::fromUtf8("ExportLAS"));
        ExportLAS->setWindowModality(Qt::ApplicationModal);
        ExportLAS->resize(307, 399);
        gridLayout_2 = new QGridLayout(ExportLAS);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButtonBrowse = new QPushButton(ExportLAS);
        pushButtonBrowse->setObjectName(QString::fromUtf8("pushButtonBrowse"));
        pushButtonBrowse->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(pushButtonBrowse, 0, 2, 1, 1);

        label_3 = new QLabel(ExportLAS);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        lineEditDirectory = new QLineEdit(ExportLAS);
        lineEditDirectory->setObjectName(QString::fromUtf8("lineEditDirectory"));

        gridLayout_2->addWidget(lineEditDirectory, 0, 1, 1, 1);

        groupBox = new QGroupBox(ExportLAS);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 2);

        pushButtonAll = new QPushButton(groupBox);
        pushButtonAll->setObjectName(QString::fromUtf8("pushButtonAll"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/SelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAll->setIcon(icon);

        gridLayout->addWidget(pushButtonAll, 1, 0, 1, 1);

        pushButtonNone = new QPushButton(groupBox);
        pushButtonNone->setObjectName(QString::fromUtf8("pushButtonNone"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/DisSelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonNone->setIcon(icon1);

        gridLayout->addWidget(pushButtonNone, 1, 1, 1, 1);

        pushButtonAll->raise();
        pushButtonNone->raise();
        tableWidget->raise();

        gridLayout_2->addWidget(groupBox, 1, 0, 1, 3);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(ExportLAS);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(ExportLAS);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout_2->addLayout(hboxLayout, 2, 0, 1, 3);

        label_3->raise();
        lineEditDirectory->raise();
        pushButtonBrowse->raise();
        groupBox->raise();

        retranslateUi(ExportLAS);
        QObject::connect(okButton, SIGNAL(clicked()), ExportLAS, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), ExportLAS, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExportLAS);
    } // setupUi

    void retranslateUi(QDialog *ExportLAS)
    {
        ExportLAS->setWindowTitle(QCoreApplication::translate("ExportLAS", "Dialog", nullptr));
        pushButtonBrowse->setText(QCoreApplication::translate("ExportLAS", "Browse...", nullptr));
        label_3->setText(QCoreApplication::translate("ExportLAS", "File\357\274\232", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ExportLAS", "Curves", nullptr));
        pushButtonAll->setText(QString());
        pushButtonNone->setText(QString());
        okButton->setText(QCoreApplication::translate("ExportLAS", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("ExportLAS", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExportLAS: public Ui_ExportLAS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XEXPORTLAS_H
