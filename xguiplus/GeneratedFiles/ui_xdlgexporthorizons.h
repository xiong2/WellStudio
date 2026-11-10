/********************************************************************************
** Form generated from reading UI file 'xdlgexporthorizons.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGEXPORTHORIZONS_H
#define UI_XDLGEXPORTHORIZONS_H

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

class Ui_CXDlgExportHorizons
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditDir;
    QPushButton *pushButtonBrowser;
    QGridLayout *gridLayout;
    QPushButton *pushButtonUnselectAll;
    QListWidget *listWidget;
    QPushButton *pushButtonSelectAll;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QCheckBox *checkBoxLine;
    QCheckBox *checkBoxXY;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxInv;
    QLineEdit *lineEditInv;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CXDlgExportHorizons)
    {
        if (CXDlgExportHorizons->objectName().isEmpty())
            CXDlgExportHorizons->setObjectName(QString::fromUtf8("CXDlgExportHorizons"));
        CXDlgExportHorizons->resize(450, 430);
        verticalLayout = new QVBoxLayout(CXDlgExportHorizons);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXDlgExportHorizons);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditDir = new QLineEdit(CXDlgExportHorizons);
        lineEditDir->setObjectName(QString::fromUtf8("lineEditDir"));

        horizontalLayout->addWidget(lineEditDir);

        pushButtonBrowser = new QPushButton(CXDlgExportHorizons);
        pushButtonBrowser->setObjectName(QString::fromUtf8("pushButtonBrowser"));
        pushButtonBrowser->setMinimumSize(QSize(30, 0));
        pushButtonBrowser->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(pushButtonBrowser);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonUnselectAll = new QPushButton(CXDlgExportHorizons);
        pushButtonUnselectAll->setObjectName(QString::fromUtf8("pushButtonUnselectAll"));
        pushButtonUnselectAll->setMinimumSize(QSize(30, 0));
        pushButtonUnselectAll->setMaximumSize(QSize(30, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/DisSelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonUnselectAll->setIcon(icon);

        gridLayout->addWidget(pushButtonUnselectAll, 2, 1, 1, 1);

        listWidget = new QListWidget(CXDlgExportHorizons);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 3, 1);

        pushButtonSelectAll = new QPushButton(CXDlgExportHorizons);
        pushButtonSelectAll->setObjectName(QString::fromUtf8("pushButtonSelectAll"));
        pushButtonSelectAll->setMinimumSize(QSize(30, 0));
        pushButtonSelectAll->setMaximumSize(QSize(30, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/SelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSelectAll->setIcon(icon1);

        gridLayout->addWidget(pushButtonSelectAll, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(CXDlgExportHorizons);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(140, 0));
        label_2->setMaximumSize(QSize(140, 16777215));

        horizontalLayout_2->addWidget(label_2);

        checkBoxLine = new QCheckBox(CXDlgExportHorizons);
        checkBoxLine->setObjectName(QString::fromUtf8("checkBoxLine"));
        checkBoxLine->setMinimumSize(QSize(130, 0));
        checkBoxLine->setMaximumSize(QSize(130, 16777215));
        checkBoxLine->setChecked(true);
        checkBoxLine->setTristate(false);

        horizontalLayout_2->addWidget(checkBoxLine);

        checkBoxXY = new QCheckBox(CXDlgExportHorizons);
        checkBoxXY->setObjectName(QString::fromUtf8("checkBoxXY"));
        checkBoxXY->setMinimumSize(QSize(130, 0));
        checkBoxXY->setMaximumSize(QSize(130, 16777215));
        checkBoxXY->setChecked(true);

        horizontalLayout_2->addWidget(checkBoxXY);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBoxInv = new QCheckBox(CXDlgExportHorizons);
        checkBoxInv->setObjectName(QString::fromUtf8("checkBoxInv"));
        checkBoxInv->setChecked(true);

        horizontalLayout_3->addWidget(checkBoxInv);

        lineEditInv = new QLineEdit(CXDlgExportHorizons);
        lineEditInv->setObjectName(QString::fromUtf8("lineEditInv"));

        horizontalLayout_3->addWidget(lineEditInv);


        verticalLayout->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(CXDlgExportHorizons);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CXDlgExportHorizons);

        QMetaObject::connectSlotsByName(CXDlgExportHorizons);
    } // setupUi

    void retranslateUi(QDialog *CXDlgExportHorizons)
    {
        CXDlgExportHorizons->setWindowTitle(QCoreApplication::translate("CXDlgExportHorizons", "CXDlgExportHorizons", nullptr));
        label->setText(QCoreApplication::translate("CXDlgExportHorizons", "Export Files Directory", nullptr));
        pushButtonBrowser->setText(QCoreApplication::translate("CXDlgExportHorizons", "...", nullptr));
        pushButtonUnselectAll->setText(QString());
        pushButtonSelectAll->setText(QString());
        label_2->setText(QCoreApplication::translate("CXDlgExportHorizons", "Export Columns Include", nullptr));
        checkBoxLine->setText(QCoreApplication::translate("CXDlgExportHorizons", "Inline, Crossline", nullptr));
        checkBoxXY->setText(QCoreApplication::translate("CXDlgExportHorizons", "X, Y Coordinate", nullptr));
        checkBoxInv->setText(QCoreApplication::translate("CXDlgExportHorizons", "Export Invalid Values as ", nullptr));
        lineEditInv->setText(QCoreApplication::translate("CXDlgExportHorizons", "-999.25", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgExportHorizons: public Ui_CXDlgExportHorizons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGEXPORTHORIZONS_H
