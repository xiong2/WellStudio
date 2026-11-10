/********************************************************************************
** Form generated from reading UI file 'gsdlgrsa.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSDLGRSA_H
#define UI_GSDLGRSA_H

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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include "gsbasemapview.h"

QT_BEGIN_NAMESPACE

class Ui_GSDlgRSA
{
public:
    QGridLayout *gridLayout;
    GSBasemapView *graphicsView;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidget;
    QSpinBox *spinBoxSSource;
    QListWidget *listWidget;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonRemove;
    QLabel *label_4;
    QPushButton *pushButtonAll;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBoxSurvey;
    QComboBox *comboBoxStage;
    QLabel *label;
    QSpinBox *spinBoxStage;

    void setupUi(QDialog *GSDlgRSA)
    {
        if (GSDlgRSA->objectName().isEmpty())
            GSDlgRSA->setObjectName(QString::fromUtf8("GSDlgRSA"));
        GSDlgRSA->resize(1319, 885);
        gridLayout = new QGridLayout(GSDlgRSA);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new GSBasemapView(GSDlgRSA);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(400, 600));

        gridLayout->addWidget(graphicsView, 0, 0, 2, 1);

        groupBox = new QGroupBox(GSDlgRSA);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(400, 0));
        groupBox->setMaximumSize(QSize(400, 16777215));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout_3->addWidget(tableWidget, 1, 0, 1, 3);

        spinBoxSSource = new QSpinBox(groupBox_2);
        spinBoxSSource->setObjectName(QString::fromUtf8("spinBoxSSource"));
        spinBoxSSource->setMinimum(0);
        spinBoxSSource->setMaximum(6);

        gridLayout_3->addWidget(spinBoxSSource, 0, 2, 1, 1);

        listWidget = new QListWidget(groupBox_2);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_3->addWidget(listWidget, 5, 0, 1, 3);

        pushButtonAdd = new QPushButton(groupBox_2);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAdd->setIcon(icon);

        gridLayout_3->addWidget(pushButtonAdd, 4, 1, 1, 1);

        pushButtonRemove = new QPushButton(groupBox_2);
        pushButtonRemove->setObjectName(QString::fromUtf8("pushButtonRemove"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemove->setIcon(icon1);

        gridLayout_3->addWidget(pushButtonRemove, 4, 2, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 2);

        pushButtonAll = new QPushButton(groupBox_2);
        pushButtonAll->setObjectName(QString::fromUtf8("pushButtonAll"));

        gridLayout_3->addWidget(pushButtonAll, 6, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(groupBox_2);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        gridLayout_3->addWidget(buttonBox, 7, 2, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 3, 0, 1, 3);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        comboBoxSurvey = new QComboBox(groupBox);
        comboBoxSurvey->setObjectName(QString::fromUtf8("comboBoxSurvey"));

        gridLayout_2->addWidget(comboBoxSurvey, 0, 1, 1, 2);

        comboBoxStage = new QComboBox(groupBox);
        comboBoxStage->addItem(QString());
        comboBoxStage->setObjectName(QString::fromUtf8("comboBoxStage"));

        gridLayout_2->addWidget(comboBoxStage, 2, 1, 1, 2);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        spinBoxStage = new QSpinBox(groupBox);
        spinBoxStage->setObjectName(QString::fromUtf8("spinBoxStage"));
        spinBoxStage->setMinimum(0);
        spinBoxStage->setMaximum(10);
        spinBoxStage->setValue(0);

        gridLayout_2->addWidget(spinBoxStage, 1, 1, 1, 2);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);


        retranslateUi(GSDlgRSA);
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), GSDlgRSA, SLOT(reject()));

        QMetaObject::connectSlotsByName(GSDlgRSA);
    } // setupUi

    void retranslateUi(QDialog *GSDlgRSA)
    {
        GSDlgRSA->setWindowTitle(QCoreApplication::translate("GSDlgRSA", "GSDlgRSA", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GSDlgRSA", "Parameters", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("GSDlgRSA", "Current geologic stage", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GSDlgRSA", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GSDlgRSA", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GSDlgRSA", "Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GSDlgRSA", "Distance (m)", nullptr));
        pushButtonAdd->setText(QString());
        pushButtonRemove->setText(QString());
        label_4->setText(QCoreApplication::translate("GSDlgRSA", "Number of regional stress source:", nullptr));
        pushButtonAll->setText(QCoreApplication::translate("GSDlgRSA", "Apply to all stages", nullptr));
        label_5->setText(QCoreApplication::translate("GSDlgRSA", "Horizons belong to current stage:", nullptr));
        label_2->setText(QCoreApplication::translate("GSDlgRSA", "Number of geologic stages:", nullptr));
        label_3->setText(QCoreApplication::translate("GSDlgRSA", "Current geologic stages:", nullptr));
        comboBoxStage->setItemText(0, QCoreApplication::translate("GSDlgRSA", "stage 1", nullptr));

        label->setText(QCoreApplication::translate("GSDlgRSA", "Survey:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSDlgRSA: public Ui_GSDlgRSA {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSDLGRSA_H
