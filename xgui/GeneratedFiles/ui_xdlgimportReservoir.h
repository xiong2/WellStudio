/********************************************************************************
** Form generated from reading UI file 'xdlgimportReservoir.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGIMPORTRESERVOIR_H
#define UI_XDLGIMPORTRESERVOIR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ImportReservoir
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLineEdit *lineEditName;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *labelNI;
    QLineEdit *lineEditNI;
    QLabel *labelNJ;
    QLineEdit *lineEditNJ;
    QLabel *labelNK;
    QLineEdit *lineEditNK;
    QLabel *labelTotalCells;
    QLineEdit *lineEditTotalCells;
    QLabel *labelValidCells;
    QLineEdit *lineEditValidCells;
    QLabel *labelValidPercentage;
    QLineEdit *lineEditValidPercentage;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonGlobalCoord;
    QRadioButton *radioButtonLocalCoord;
    QLabel *label;
    QLineEdit *lineEditOriX;
    QLabel *label_2;
    QLineEdit *lineEditOriY;
    QLabel *label_3;
    QLineEdit *lineEditOriZ;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QLineEdit *lineEditPrjXUnit;
    QLabel *label_5;
    QLineEdit *lineEditPrjZUnit;
    QLabel *label_6;
    QComboBox *comboBox;
    QLabel *label_7;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetDimension;
    QCheckBox *checkBox;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QLabel *label_9;
    QLineEdit *lineEditInvalid;
    QPushButton *pushButtonSelectAll;
    QPushButton *pushButtonDeselectAll;
    QTableWidget *tableWidgetProperties;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonScan;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportReservoir)
    {
        if (ImportReservoir->objectName().isEmpty())
            ImportReservoir->setObjectName(QString::fromUtf8("ImportReservoir"));
        ImportReservoir->resize(852, 815);
        verticalLayout_3 = new QVBoxLayout(ImportReservoir);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_8 = new QLabel(ImportReservoir);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_2->addWidget(label_8);

        lineEditName = new QLineEdit(ImportReservoir);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        horizontalLayout_2->addWidget(lineEditName);


        verticalLayout_2->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(ImportReservoir);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelNI = new QLabel(groupBox);
        labelNI->setObjectName(QString::fromUtf8("labelNI"));

        gridLayout->addWidget(labelNI, 0, 0, 1, 1);

        lineEditNI = new QLineEdit(groupBox);
        lineEditNI->setObjectName(QString::fromUtf8("lineEditNI"));
        lineEditNI->setReadOnly(true);

        gridLayout->addWidget(lineEditNI, 0, 1, 1, 1);

        labelNJ = new QLabel(groupBox);
        labelNJ->setObjectName(QString::fromUtf8("labelNJ"));

        gridLayout->addWidget(labelNJ, 0, 2, 1, 1);

        lineEditNJ = new QLineEdit(groupBox);
        lineEditNJ->setObjectName(QString::fromUtf8("lineEditNJ"));

        gridLayout->addWidget(lineEditNJ, 0, 3, 1, 1);

        labelNK = new QLabel(groupBox);
        labelNK->setObjectName(QString::fromUtf8("labelNK"));

        gridLayout->addWidget(labelNK, 0, 4, 1, 1);

        lineEditNK = new QLineEdit(groupBox);
        lineEditNK->setObjectName(QString::fromUtf8("lineEditNK"));

        gridLayout->addWidget(lineEditNK, 0, 5, 1, 1);

        labelTotalCells = new QLabel(groupBox);
        labelTotalCells->setObjectName(QString::fromUtf8("labelTotalCells"));

        gridLayout->addWidget(labelTotalCells, 1, 0, 1, 1);

        lineEditTotalCells = new QLineEdit(groupBox);
        lineEditTotalCells->setObjectName(QString::fromUtf8("lineEditTotalCells"));

        gridLayout->addWidget(lineEditTotalCells, 1, 1, 1, 1);

        labelValidCells = new QLabel(groupBox);
        labelValidCells->setObjectName(QString::fromUtf8("labelValidCells"));

        gridLayout->addWidget(labelValidCells, 1, 2, 1, 1);

        lineEditValidCells = new QLineEdit(groupBox);
        lineEditValidCells->setObjectName(QString::fromUtf8("lineEditValidCells"));

        gridLayout->addWidget(lineEditValidCells, 1, 3, 1, 1);

        labelValidPercentage = new QLabel(groupBox);
        labelValidPercentage->setObjectName(QString::fromUtf8("labelValidPercentage"));

        gridLayout->addWidget(labelValidPercentage, 1, 4, 1, 1);

        lineEditValidPercentage = new QLineEdit(groupBox);
        lineEditValidPercentage->setObjectName(QString::fromUtf8("lineEditValidPercentage"));

        gridLayout->addWidget(lineEditValidPercentage, 1, 5, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(ImportReservoir);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButtonGlobalCoord = new QRadioButton(groupBox_2);
        radioButtonGlobalCoord->setObjectName(QString::fromUtf8("radioButtonGlobalCoord"));
        radioButtonGlobalCoord->setChecked(true);

        gridLayout_2->addWidget(radioButtonGlobalCoord, 0, 0, 1, 2);

        radioButtonLocalCoord = new QRadioButton(groupBox_2);
        radioButtonLocalCoord->setObjectName(QString::fromUtf8("radioButtonLocalCoord"));

        gridLayout_2->addWidget(radioButtonLocalCoord, 0, 2, 1, 2);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(false);

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        lineEditOriX = new QLineEdit(groupBox_2);
        lineEditOriX->setObjectName(QString::fromUtf8("lineEditOriX"));
        lineEditOriX->setEnabled(false);

        gridLayout_2->addWidget(lineEditOriX, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(false);

        gridLayout_2->addWidget(label_2, 1, 2, 1, 1);

        lineEditOriY = new QLineEdit(groupBox_2);
        lineEditOriY->setObjectName(QString::fromUtf8("lineEditOriY"));
        lineEditOriY->setEnabled(false);

        gridLayout_2->addWidget(lineEditOriY, 1, 3, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(false);

        gridLayout_2->addWidget(label_3, 1, 4, 1, 1);

        lineEditOriZ = new QLineEdit(groupBox_2);
        lineEditOriZ->setObjectName(QString::fromUtf8("lineEditOriZ"));
        lineEditOriZ->setEnabled(false);

        gridLayout_2->addWidget(lineEditOriZ, 1, 5, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(ImportReservoir);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        lineEditPrjXUnit = new QLineEdit(groupBox_3);
        lineEditPrjXUnit->setObjectName(QString::fromUtf8("lineEditPrjXUnit"));
        lineEditPrjXUnit->setReadOnly(true);

        gridLayout_3->addWidget(lineEditPrjXUnit, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 2, 1, 1);

        lineEditPrjZUnit = new QLineEdit(groupBox_3);
        lineEditPrjZUnit->setObjectName(QString::fromUtf8("lineEditPrjZUnit"));
        lineEditPrjZUnit->setReadOnly(true);

        gridLayout_3->addWidget(lineEditPrjZUnit, 0, 3, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        comboBox = new QComboBox(groupBox_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_3->addWidget(comboBox, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 1, 2, 1, 1);

        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout_3->addWidget(comboBox_2, 1, 3, 1, 1);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(ImportReservoir);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidgetDimension = new QTableWidget(groupBox_4);
        tableWidgetDimension->setObjectName(QString::fromUtf8("tableWidgetDimension"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetDimension->sizePolicy().hasHeightForWidth());
        tableWidgetDimension->setSizePolicy(sizePolicy);
        tableWidgetDimension->setMaximumSize(QSize(16777215, 120));

        verticalLayout->addWidget(tableWidgetDimension);

        checkBox = new QCheckBox(groupBox_4);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);


        verticalLayout_2->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(ImportReservoir);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_4->addWidget(label_9, 1, 0, 1, 1);

        lineEditInvalid = new QLineEdit(groupBox_5);
        lineEditInvalid->setObjectName(QString::fromUtf8("lineEditInvalid"));

        gridLayout_4->addWidget(lineEditInvalid, 1, 1, 1, 1);

        pushButtonSelectAll = new QPushButton(groupBox_5);
        pushButtonSelectAll->setObjectName(QString::fromUtf8("pushButtonSelectAll"));

        gridLayout_4->addWidget(pushButtonSelectAll, 1, 2, 1, 1);

        pushButtonDeselectAll = new QPushButton(groupBox_5);
        pushButtonDeselectAll->setObjectName(QString::fromUtf8("pushButtonDeselectAll"));

        gridLayout_4->addWidget(pushButtonDeselectAll, 1, 3, 1, 1);

        tableWidgetProperties = new QTableWidget(groupBox_5);
        tableWidgetProperties->setObjectName(QString::fromUtf8("tableWidgetProperties"));

        gridLayout_4->addWidget(tableWidgetProperties, 0, 0, 1, 4);


        verticalLayout_2->addWidget(groupBox_5);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonScan = new QPushButton(ImportReservoir);
        pushButtonScan->setObjectName(QString::fromUtf8("pushButtonScan"));

        horizontalLayout->addWidget(pushButtonScan);

        buttonBox = new QDialogButtonBox(ImportReservoir);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(ImportReservoir);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportReservoir, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportReservoir, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportReservoir);
    } // setupUi

    void retranslateUi(QDialog *ImportReservoir)
    {
        ImportReservoir->setWindowTitle(QCoreApplication::translate("ImportReservoir", "Dialog", nullptr));
        label_8->setText(QCoreApplication::translate("ImportReservoir", "Model Name", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ImportReservoir", "Grid Infomation", nullptr));
        labelNI->setText(QCoreApplication::translate("ImportReservoir", "Cell num along I direction", nullptr));
        labelNJ->setText(QCoreApplication::translate("ImportReservoir", "Cell num along J direction", nullptr));
        labelNK->setText(QCoreApplication::translate("ImportReservoir", "Cell num along K direction", nullptr));
        labelTotalCells->setText(QCoreApplication::translate("ImportReservoir", "Total cell number", nullptr));
        labelValidCells->setText(QCoreApplication::translate("ImportReservoir", "Valid cell number", nullptr));
        labelValidPercentage->setText(QCoreApplication::translate("ImportReservoir", "Valid cell percentage (%)", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ImportReservoir", "Coordinate System", nullptr));
        radioButtonGlobalCoord->setText(QCoreApplication::translate("ImportReservoir", "Global", nullptr));
        radioButtonLocalCoord->setText(QCoreApplication::translate("ImportReservoir", "Local", nullptr));
        label->setText(QCoreApplication::translate("ImportReservoir", "X (origin)", nullptr));
        lineEditOriX->setText(QCoreApplication::translate("ImportReservoir", "0", nullptr));
        label_2->setText(QCoreApplication::translate("ImportReservoir", "Y (origin)", nullptr));
        lineEditOriY->setText(QCoreApplication::translate("ImportReservoir", "0", nullptr));
        label_3->setText(QCoreApplication::translate("ImportReservoir", "Z (origin)", nullptr));
        lineEditOriZ->setText(QCoreApplication::translate("ImportReservoir", "0", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("ImportReservoir", "Coordinate Units", nullptr));
        label_4->setText(QCoreApplication::translate("ImportReservoir", "Horizontal length unit (Project)", nullptr));
        label_5->setText(QCoreApplication::translate("ImportReservoir", "Vertical length unit (Project)", nullptr));
        label_6->setText(QCoreApplication::translate("ImportReservoir", "Horizontal length unit (Input)", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ImportReservoir", "m", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ImportReservoir", "cm", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("ImportReservoir", "mm", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("ImportReservoir", "ft", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("ImportReservoir", "inch", nullptr));

        label_7->setText(QCoreApplication::translate("ImportReservoir", "Vertical length unit (Input)", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("ImportReservoir", "m", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("ImportReservoir", "cm", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("ImportReservoir", "mm", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("ImportReservoir", "ft", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("ImportReservoir", "inch", nullptr));

        groupBox_4->setTitle(QCoreApplication::translate("ImportReservoir", "Model Range", nullptr));
        checkBox->setText(QCoreApplication::translate("ImportReservoir", "Negate Z", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("ImportReservoir", "Select Reservoir Properties", nullptr));
        label_9->setText(QCoreApplication::translate("ImportReservoir", "Invalid Value", nullptr));
        lineEditInvalid->setText(QCoreApplication::translate("ImportReservoir", "-9999", nullptr));
        pushButtonSelectAll->setText(QCoreApplication::translate("ImportReservoir", "Select All", nullptr));
        pushButtonDeselectAll->setText(QCoreApplication::translate("ImportReservoir", "Deselect All", nullptr));
        pushButtonScan->setText(QCoreApplication::translate("ImportReservoir", "Scan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportReservoir: public Ui_ImportReservoir {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGIMPORTRESERVOIR_H
