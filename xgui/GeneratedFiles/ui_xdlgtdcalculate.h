/********************************************************************************
** Form generated from reading UI file 'xdlgtdcalculate.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGTDCALCULATE_H
#define UI_XDLGTDCALCULATE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXDlgTDCalculate
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxNew;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QPushButton *pushButtonImport;
    QLabel *label_2;
    QPushButton *pushButtonCal;
    QGroupBox *groupBoxExist;
    QGridLayout *gridLayout;
    QPushButton *pushButtonAct;
    QPushButton *pushButtonDel;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBoxAct;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;

    void setupUi(QDialog *CXDlgTDCalculate)
    {
        if (CXDlgTDCalculate->objectName().isEmpty())
            CXDlgTDCalculate->setObjectName(QString::fromUtf8("CXDlgTDCalculate"));
        CXDlgTDCalculate->resize(690, 485);
        horizontalLayout_2 = new QHBoxLayout(CXDlgTDCalculate);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxNew = new QGroupBox(CXDlgTDCalculate);
        groupBoxNew->setObjectName(QString::fromUtf8("groupBoxNew"));
        gridLayout_2 = new QGridLayout(groupBoxNew);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBoxNew);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        pushButtonImport = new QPushButton(groupBoxNew);
        pushButtonImport->setObjectName(QString::fromUtf8("pushButtonImport"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/WellFile.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonImport->setIcon(icon);

        gridLayout_2->addWidget(pushButtonImport, 0, 1, 1, 1);

        label_2 = new QLabel(groupBoxNew);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        pushButtonCal = new QPushButton(groupBoxNew);
        pushButtonCal->setObjectName(QString::fromUtf8("pushButtonCal"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/T-AC.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonCal->setIcon(icon1);

        gridLayout_2->addWidget(pushButtonCal, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBoxNew);

        groupBoxExist = new QGroupBox(CXDlgTDCalculate);
        groupBoxExist->setObjectName(QString::fromUtf8("groupBoxExist"));
        gridLayout = new QGridLayout(groupBoxExist);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonAct = new QPushButton(groupBoxExist);
        pushButtonAct->setObjectName(QString::fromUtf8("pushButtonAct"));
        pushButtonAct->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/OK.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonAct->setIcon(icon2);

        gridLayout->addWidget(pushButtonAct, 1, 0, 1, 1);

        pushButtonDel = new QPushButton(groupBoxExist);
        pushButtonDel->setObjectName(QString::fromUtf8("pushButtonDel"));
        pushButtonDel->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/Delete.png"), QSize(), QIcon::Disabled, QIcon::On);
        pushButtonDel->setIcon(icon3);

        gridLayout->addWidget(pushButtonDel, 1, 1, 1, 1);

        tableWidget = new QTableWidget(groupBoxExist);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setWordWrap(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(60);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 2);


        verticalLayout->addWidget(groupBoxExist);

        buttonBox = new QDialogButtonBox(CXDlgTDCalculate);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        horizontalLayout_2->addLayout(verticalLayout);

        groupBoxAct = new QGroupBox(CXDlgTDCalculate);
        groupBoxAct->setObjectName(QString::fromUtf8("groupBoxAct"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxAct->sizePolicy().hasHeightForWidth());
        groupBoxAct->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(groupBoxAct);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableView = new QTableView(groupBoxAct);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout->addWidget(tableView);


        horizontalLayout_2->addWidget(groupBoxAct);


        retranslateUi(CXDlgTDCalculate);
        QObject::connect(buttonBox, SIGNAL(rejected()), CXDlgTDCalculate, SLOT(reject()));

        QMetaObject::connectSlotsByName(CXDlgTDCalculate);
    } // setupUi

    void retranslateUi(QDialog *CXDlgTDCalculate)
    {
        CXDlgTDCalculate->setWindowTitle(QCoreApplication::translate("CXDlgTDCalculate", "T-D Calculator", nullptr));
        groupBoxNew->setTitle(QCoreApplication::translate("CXDlgTDCalculate", "Create new T-D Curves", nullptr));
        label->setText(QCoreApplication::translate("CXDlgTDCalculate", "By importing Checkshot file:", nullptr));
        pushButtonImport->setText(QCoreApplication::translate("CXDlgTDCalculate", "...", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgTDCalculate", "By calculated from AC curve:", nullptr));
        pushButtonCal->setText(QCoreApplication::translate("CXDlgTDCalculate", "...", nullptr));
        groupBoxExist->setTitle(QCoreApplication::translate("CXDlgTDCalculate", "Exist T-D Curves", nullptr));
        pushButtonAct->setText(QCoreApplication::translate("CXDlgTDCalculate", "Set as activated", nullptr));
        pushButtonDel->setText(QCoreApplication::translate("CXDlgTDCalculate", "Delete", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CXDlgTDCalculate", "TD", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CXDlgTDCalculate", "Comments", nullptr));
        groupBoxAct->setTitle(QCoreApplication::translate("CXDlgTDCalculate", "Activated T-D Curve", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgTDCalculate: public Ui_CXDlgTDCalculate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGTDCALCULATE_H
