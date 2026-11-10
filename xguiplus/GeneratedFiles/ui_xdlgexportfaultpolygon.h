/********************************************************************************
** Form generated from reading UI file 'xdlgexportfaultpolygon.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGEXPORTFAULTPOLYGON_H
#define UI_XDLGEXPORTFAULTPOLYGON_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXDlgExportFaultPolygon
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEditPath;
    QPushButton *btnSelectPath;
    QGridLayout *gridLayout;
    QListWidget *listFaultPolygon;
    QSpacerItem *verticalSpacer;
    QPushButton *btnSelectAll;
    QPushButton *btnUnselectAll;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QCheckBox *chkTab;
    QCheckBox *chkSpace;
    QCheckBox *chkComma;
    QSpacerItem *horizontalSpacer;
    QCheckBox *chkExportName;
    QDialogButtonBox *btnBox;

    void setupUi(QDialog *CXDlgExportFaultPolygon)
    {
        if (CXDlgExportFaultPolygon->objectName().isEmpty())
            CXDlgExportFaultPolygon->setObjectName(QString::fromUtf8("CXDlgExportFaultPolygon"));
        CXDlgExportFaultPolygon->resize(398, 296);
        verticalLayout = new QVBoxLayout(CXDlgExportFaultPolygon);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(CXDlgExportFaultPolygon);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEditPath = new QLineEdit(CXDlgExportFaultPolygon);
        lineEditPath->setObjectName(QString::fromUtf8("lineEditPath"));

        horizontalLayout->addWidget(lineEditPath);

        btnSelectPath = new QPushButton(CXDlgExportFaultPolygon);
        btnSelectPath->setObjectName(QString::fromUtf8("btnSelectPath"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnSelectPath->sizePolicy().hasHeightForWidth());
        btnSelectPath->setSizePolicy(sizePolicy);
        btnSelectPath->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(btnSelectPath);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listFaultPolygon = new QListWidget(CXDlgExportFaultPolygon);
        listFaultPolygon->setObjectName(QString::fromUtf8("listFaultPolygon"));

        gridLayout->addWidget(listFaultPolygon, 0, 0, 3, 1);

        verticalSpacer = new QSpacerItem(17, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        btnSelectAll = new QPushButton(CXDlgExportFaultPolygon);
        btnSelectAll->setObjectName(QString::fromUtf8("btnSelectAll"));
        sizePolicy.setHeightForWidth(btnSelectAll->sizePolicy().hasHeightForWidth());
        btnSelectAll->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/SelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSelectAll->setIcon(icon);

        gridLayout->addWidget(btnSelectAll, 1, 1, 1, 1);

        btnUnselectAll = new QPushButton(CXDlgExportFaultPolygon);
        btnUnselectAll->setObjectName(QString::fromUtf8("btnUnselectAll"));
        sizePolicy.setHeightForWidth(btnUnselectAll->sizePolicy().hasHeightForWidth());
        btnUnselectAll->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/DisSelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnUnselectAll->setIcon(icon1);

        gridLayout->addWidget(btnUnselectAll, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(CXDlgExportFaultPolygon);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        chkTab = new QCheckBox(CXDlgExportFaultPolygon);
        chkTab->setObjectName(QString::fromUtf8("chkTab"));
        chkTab->setChecked(true);

        horizontalLayout_2->addWidget(chkTab);

        chkSpace = new QCheckBox(CXDlgExportFaultPolygon);
        chkSpace->setObjectName(QString::fromUtf8("chkSpace"));

        horizontalLayout_2->addWidget(chkSpace);

        chkComma = new QCheckBox(CXDlgExportFaultPolygon);
        chkComma->setObjectName(QString::fromUtf8("chkComma"));
        chkComma->setChecked(true);

        horizontalLayout_2->addWidget(chkComma);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        chkExportName = new QCheckBox(CXDlgExportFaultPolygon);
        chkExportName->setObjectName(QString::fromUtf8("chkExportName"));

        verticalLayout->addWidget(chkExportName);

        btnBox = new QDialogButtonBox(CXDlgExportFaultPolygon);
        btnBox->setObjectName(QString::fromUtf8("btnBox"));
        btnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(btnBox);


        retranslateUi(CXDlgExportFaultPolygon);
        QObject::connect(btnBox, SIGNAL(accepted()), CXDlgExportFaultPolygon, SLOT(accept()));
        QObject::connect(btnBox, SIGNAL(rejected()), CXDlgExportFaultPolygon, SLOT(reject()));

        QMetaObject::connectSlotsByName(CXDlgExportFaultPolygon);
    } // setupUi

    void retranslateUi(QDialog *CXDlgExportFaultPolygon)
    {
        CXDlgExportFaultPolygon->setWindowTitle(QCoreApplication::translate("CXDlgExportFaultPolygon", "Export fault polygons", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgExportFaultPolygon", "Export File", nullptr));
        btnSelectPath->setText(QCoreApplication::translate("CXDlgExportFaultPolygon", "...", nullptr));
        btnSelectAll->setText(QString());
        btnUnselectAll->setText(QString());
        label->setText(QCoreApplication::translate("CXDlgExportFaultPolygon", "Delimiters", nullptr));
        chkTab->setText(QCoreApplication::translate("CXDlgExportFaultPolygon", "Tab", nullptr));
        chkSpace->setText(QCoreApplication::translate("CXDlgExportFaultPolygon", "Space", nullptr));
        chkComma->setText(QCoreApplication::translate("CXDlgExportFaultPolygon", "Comma(,)", nullptr));
        chkExportName->setText(QCoreApplication::translate("CXDlgExportFaultPolygon", "Export fault polygon name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgExportFaultPolygon: public Ui_CXDlgExportFaultPolygon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGEXPORTFAULTPOLYGON_H
