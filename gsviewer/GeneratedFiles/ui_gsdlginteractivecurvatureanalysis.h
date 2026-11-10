/********************************************************************************
** Form generated from reading UI file 'gsdlginteractivecurvatureanalysis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSDLGINTERACTIVECURVATUREANALYSIS_H
#define UI_GSDLGINTERACTIVECURVATUREANALYSIS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include "gsbasemapview.h"

QT_BEGIN_NAMESPACE

class Ui_GSDlgInteractiveCurvatureAnalysis
{
public:
    QGridLayout *gridLayout_5;
    GSBasemapView *graphicsView;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonOri;
    QRadioButton *radioButtonMPC;
    QRadioButton *radioButtonMNC;
    QLineEdit *lineEditMNC;
    QRadioButton *radioButtonAzi;
    QRadioButton *radioButtonBlender;
    QLineEdit *lineEditMPC;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *spinBoxDX;
    QLabel *label_3;
    QSpinBox *spinBoxDY;
    QPushButton *pushButtonCal;
    QLabel *label;
    QCheckBox *checkBox;
    QLineEdit *lineEditThreshold;
    QPushButton *pushButtonBlender;
    QGroupBox *groupBoxFaults;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonFaultAll;
    QDoubleSpinBox *spinBoxThrow;
    QLabel *label_8;
    QLabel *label_4;
    QLabel *label_6;
    QSpinBox *spinBoxLWR;
    QPushButton *pushButtonFaultNone;
    QSpinBox *spinBoxLinearity;
    QSpinBox *spinBoxFLen;
    QLabel *label_5;
    QLabel *label_7;
    QComboBox *comboBoxStatus;
    QCheckBox *checkBoxMerge;
    QTableWidget *tableWidget;
    QCheckBox *checkBoxShowFName;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonCalStress;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonFS;
    QGroupBox *groupBoxWells;
    QGridLayout *gridLayout_6;
    QTableWidget *tableWidgetWells;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *GSDlgInteractiveCurvatureAnalysis)
    {
        if (GSDlgInteractiveCurvatureAnalysis->objectName().isEmpty())
            GSDlgInteractiveCurvatureAnalysis->setObjectName(QString::fromUtf8("GSDlgInteractiveCurvatureAnalysis"));
        GSDlgInteractiveCurvatureAnalysis->resize(1618, 883);
        gridLayout_5 = new QGridLayout(GSDlgInteractiveCurvatureAnalysis);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        graphicsView = new GSBasemapView(GSDlgInteractiveCurvatureAnalysis);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(400, 600));

        gridLayout_5->addWidget(graphicsView, 0, 0, 2, 1);

        groupBox = new QGroupBox(GSDlgInteractiveCurvatureAnalysis);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(600, 0));
        groupBox->setMaximumSize(QSize(600, 16777215));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(300, 0));
        groupBox_2->setMaximumSize(QSize(300, 16777215));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButtonOri = new QRadioButton(groupBox_2);
        radioButtonOri->setObjectName(QString::fromUtf8("radioButtonOri"));
        radioButtonOri->setChecked(true);

        gridLayout->addWidget(radioButtonOri, 0, 0, 1, 1);

        radioButtonMPC = new QRadioButton(groupBox_2);
        radioButtonMPC->setObjectName(QString::fromUtf8("radioButtonMPC"));
        radioButtonMPC->setEnabled(false);

        gridLayout->addWidget(radioButtonMPC, 1, 0, 1, 2);

        radioButtonMNC = new QRadioButton(groupBox_2);
        radioButtonMNC->setObjectName(QString::fromUtf8("radioButtonMNC"));
        radioButtonMNC->setEnabled(false);

        gridLayout->addWidget(radioButtonMNC, 2, 0, 1, 2);

        lineEditMNC = new QLineEdit(groupBox_2);
        lineEditMNC->setObjectName(QString::fromUtf8("lineEditMNC"));
        lineEditMNC->setMaximumSize(QSize(80, 16777215));
        lineEditMNC->setReadOnly(true);

        gridLayout->addWidget(lineEditMNC, 2, 2, 1, 1);

        radioButtonAzi = new QRadioButton(groupBox_2);
        radioButtonAzi->setObjectName(QString::fromUtf8("radioButtonAzi"));
        radioButtonAzi->setEnabled(false);

        gridLayout->addWidget(radioButtonAzi, 3, 0, 1, 1);

        radioButtonBlender = new QRadioButton(groupBox_2);
        radioButtonBlender->setObjectName(QString::fromUtf8("radioButtonBlender"));
        radioButtonBlender->setEnabled(false);

        gridLayout->addWidget(radioButtonBlender, 4, 0, 1, 1);

        lineEditMPC = new QLineEdit(groupBox_2);
        lineEditMPC->setObjectName(QString::fromUtf8("lineEditMPC"));
        lineEditMPC->setMinimumSize(QSize(80, 0));
        lineEditMPC->setMaximumSize(QSize(80, 16777215));
        lineEditMPC->setReadOnly(true);

        gridLayout->addWidget(lineEditMPC, 1, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 3, 3, 1);

        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(260, 16777215));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        spinBoxDX = new QSpinBox(groupBox_3);
        spinBoxDX->setObjectName(QString::fromUtf8("spinBoxDX"));
        spinBoxDX->setMinimum(3);
        spinBoxDX->setMaximum(21);
        spinBoxDX->setSingleStep(2);

        horizontalLayout_3->addWidget(spinBoxDX);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        spinBoxDY = new QSpinBox(groupBox_3);
        spinBoxDY->setObjectName(QString::fromUtf8("spinBoxDY"));
        spinBoxDY->setMinimum(3);
        spinBoxDY->setMaximum(21);
        spinBoxDY->setSingleStep(2);

        horizontalLayout_3->addWidget(spinBoxDY);

        pushButtonCal = new QPushButton(groupBox_3);
        pushButtonCal->setObjectName(QString::fromUtf8("pushButtonCal"));

        horizontalLayout_3->addWidget(pushButtonCal);


        gridLayout_3->addWidget(groupBox_3, 0, 0, 1, 3);

        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 1, 0, 1, 1);

        checkBox = new QCheckBox(groupBox_4);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);

        gridLayout_3->addWidget(checkBox, 2, 0, 1, 2);

        lineEditThreshold = new QLineEdit(groupBox_4);
        lineEditThreshold->setObjectName(QString::fromUtf8("lineEditThreshold"));
        lineEditThreshold->setMinimumSize(QSize(80, 0));

        gridLayout_3->addWidget(lineEditThreshold, 1, 1, 1, 2);

        pushButtonBlender = new QPushButton(groupBox_4);
        pushButtonBlender->setObjectName(QString::fromUtf8("pushButtonBlender"));
        pushButtonBlender->setEnabled(false);

        gridLayout_3->addWidget(pushButtonBlender, 2, 2, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 0, 1, 1, 4);

        groupBoxFaults = new QGroupBox(groupBox);
        groupBoxFaults->setObjectName(QString::fromUtf8("groupBoxFaults"));
        groupBoxFaults->setCheckable(true);
        groupBoxFaults->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBoxFaults);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButtonFaultAll = new QPushButton(groupBoxFaults);
        pushButtonFaultAll->setObjectName(QString::fromUtf8("pushButtonFaultAll"));
        pushButtonFaultAll->setMaximumSize(QSize(40, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/SelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonFaultAll->setIcon(icon);

        gridLayout_2->addWidget(pushButtonFaultAll, 1, 0, 1, 1);

        spinBoxThrow = new QDoubleSpinBox(groupBoxFaults);
        spinBoxThrow->setObjectName(QString::fromUtf8("spinBoxThrow"));
        spinBoxThrow->setDecimals(1);
        spinBoxThrow->setMinimum(0.500000000000000);
        spinBoxThrow->setMaximum(5.000000000000000);
        spinBoxThrow->setSingleStep(0.500000000000000);
        spinBoxThrow->setValue(1.000000000000000);

        gridLayout_2->addWidget(spinBoxThrow, 1, 3, 1, 1);

        label_8 = new QLabel(groupBoxFaults);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 1, 2, 1, 1);

        label_4 = new QLabel(groupBoxFaults);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_4, 1, 4, 1, 1);

        label_6 = new QLabel(groupBoxFaults);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 4, 2, 1, 1);

        spinBoxLWR = new QSpinBox(groupBoxFaults);
        spinBoxLWR->setObjectName(QString::fromUtf8("spinBoxLWR"));
        spinBoxLWR->setMinimum(2);
        spinBoxLWR->setMaximum(20);
        spinBoxLWR->setValue(10);

        gridLayout_2->addWidget(spinBoxLWR, 4, 5, 1, 1);

        pushButtonFaultNone = new QPushButton(groupBoxFaults);
        pushButtonFaultNone->setObjectName(QString::fromUtf8("pushButtonFaultNone"));
        pushButtonFaultNone->setMaximumSize(QSize(40, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/DisSelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonFaultNone->setIcon(icon1);

        gridLayout_2->addWidget(pushButtonFaultNone, 4, 0, 1, 1);

        spinBoxLinearity = new QSpinBox(groupBoxFaults);
        spinBoxLinearity->setObjectName(QString::fromUtf8("spinBoxLinearity"));
        spinBoxLinearity->setMinimum(2);
        spinBoxLinearity->setMaximum(16);
        spinBoxLinearity->setValue(6);

        gridLayout_2->addWidget(spinBoxLinearity, 1, 5, 1, 1);

        spinBoxFLen = new QSpinBox(groupBoxFaults);
        spinBoxFLen->setObjectName(QString::fromUtf8("spinBoxFLen"));
        spinBoxFLen->setMinimum(0);
        spinBoxFLen->setMaximum(8000);
        spinBoxFLen->setSingleStep(500);
        spinBoxFLen->setValue(2000);

        gridLayout_2->addWidget(spinBoxFLen, 4, 3, 1, 1);

        label_5 = new QLabel(groupBoxFaults);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 4, 4, 1, 1);

        label_7 = new QLabel(groupBoxFaults);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_7, 1, 6, 1, 1);

        comboBoxStatus = new QComboBox(groupBoxFaults);
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->setObjectName(QString::fromUtf8("comboBoxStatus"));

        gridLayout_2->addWidget(comboBoxStatus, 1, 7, 1, 1);

        checkBoxMerge = new QCheckBox(groupBoxFaults);
        checkBoxMerge->setObjectName(QString::fromUtf8("checkBoxMerge"));
        checkBoxMerge->setChecked(true);

        gridLayout_2->addWidget(checkBoxMerge, 1, 9, 1, 1);

        tableWidget = new QTableWidget(groupBoxFaults);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setColumnCount(7);
        tableWidget->verticalHeader()->setDefaultSectionSize(33);

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 10);

        checkBoxShowFName = new QCheckBox(groupBoxFaults);
        checkBoxShowFName->setObjectName(QString::fromUtf8("checkBoxShowFName"));
        checkBoxShowFName->setChecked(true);

        gridLayout_2->addWidget(checkBoxShowFName, 4, 9, 1, 1);


        gridLayout_4->addWidget(groupBoxFaults, 1, 1, 1, 4);

        pushButtonClear = new QPushButton(groupBox);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));

        gridLayout_4->addWidget(pushButtonClear, 3, 2, 1, 1);

        pushButtonCalStress = new QPushButton(groupBox);
        pushButtonCalStress->setObjectName(QString::fromUtf8("pushButtonCalStress"));

        gridLayout_4->addWidget(pushButtonCalStress, 3, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 1, 1, 4);

        pushButtonFS = new QPushButton(groupBox);
        pushButtonFS->setObjectName(QString::fromUtf8("pushButtonFS"));

        gridLayout_4->addWidget(pushButtonFS, 3, 3, 1, 1);

        groupBoxWells = new QGroupBox(groupBox);
        groupBoxWells->setObjectName(QString::fromUtf8("groupBoxWells"));
        groupBoxWells->setMinimumSize(QSize(0, 160));
        groupBoxWells->setCheckable(true);
        groupBoxWells->setChecked(false);
        gridLayout_6 = new QGridLayout(groupBoxWells);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        tableWidgetWells = new QTableWidget(groupBoxWells);
        if (tableWidgetWells->columnCount() < 13)
            tableWidgetWells->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(7, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(8, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(9, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(10, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(11, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidgetWells->setHorizontalHeaderItem(12, __qtablewidgetitem19);
        tableWidgetWells->setObjectName(QString::fromUtf8("tableWidgetWells"));
        tableWidgetWells->verticalHeader()->setDefaultSectionSize(33);

        gridLayout_6->addWidget(tableWidgetWells, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBoxWells, 2, 1, 1, 4);


        gridLayout_5->addWidget(groupBox, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_2 = new QPushButton(GSDlgInteractiveCurvatureAnalysis);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(GSDlgInteractiveCurvatureAnalysis);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);


        gridLayout_5->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        groupBox->raise();
        graphicsView->raise();

        retranslateUi(GSDlgInteractiveCurvatureAnalysis);
        QObject::connect(pushButton_3, SIGNAL(clicked()), GSDlgInteractiveCurvatureAnalysis, SLOT(reject()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), GSDlgInteractiveCurvatureAnalysis, SLOT(accept()));

        QMetaObject::connectSlotsByName(GSDlgInteractiveCurvatureAnalysis);
    } // setupUi

    void retranslateUi(QDialog *GSDlgInteractiveCurvatureAnalysis)
    {
        GSDlgInteractiveCurvatureAnalysis->setWindowTitle(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "GSDlgInteractiveCurvatureAnalysis", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Calculate Parameters", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Curvature", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Result Maps", nullptr));
        radioButtonOri->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Original Surface", nullptr));
        radioButtonMPC->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Most Positive Curvature", nullptr));
        radioButtonMNC->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Most Negative Curvature", nullptr));
        radioButtonAzi->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Dip-Azimuth", nullptr));
        radioButtonBlender->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Blendering", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Window Size", nullptr));
        label_2->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "DX", nullptr));
        label_3->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "DY", nullptr));
        pushButtonCal->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Calculate", nullptr));
        label->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Threshold", nullptr));
        checkBox->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Show Sticks", nullptr));
        pushButtonBlender->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Re-Blendering", nullptr));
        groupBoxFaults->setTitle(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Faults", nullptr));
        pushButtonFaultAll->setText(QString());
        label_8->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Minimum Throw", nullptr));
        label_4->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Linearity", nullptr));
        label_6->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Minimum Length", nullptr));
        pushButtonFaultNone->setText(QString());
        label_5->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "L/W Ratio", nullptr));
        label_7->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Lowest status", nullptr));
        comboBoxStatus->setItemText(0, QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Normal", nullptr));
        comboBoxStatus->setItemText(1, QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Loading", nullptr));
        comboBoxStatus->setItemText(2, QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Uplift", nullptr));
        comboBoxStatus->setItemText(3, QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "ESS", nullptr));
        comboBoxStatus->setItemText(4, QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "SS", nullptr));
        comboBoxStatus->setItemText(5, QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "CSS", nullptr));
        comboBoxStatus->setItemText(6, QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Reverse", nullptr));

        checkBoxMerge->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Structure Merge", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Active", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Fault", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Length (m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Av Dip", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Throw (m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Reverse (%)", nullptr));
        checkBoxShowFName->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Show Name", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Clear", nullptr));
        pushButtonCalStress->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Calculate Stress", nullptr));
        pushButtonFS->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Create Structures", nullptr));
        groupBoxWells->setTitle(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Wells", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetWells->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Active", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetWells->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Well", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetWells->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Length (m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetWells->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetWells->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "L/W Ratio", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetWells->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetWells->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidgetWells->horizontalHeaderItem(7);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Depth (m)", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidgetWells->horizontalHeaderItem(8);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "SH Azi", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidgetWells->horizontalHeaderItem(9);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "SH Mag", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidgetWells->horizontalHeaderItem(10);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Sh Mag", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidgetWells->horizontalHeaderItem(11);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "SV Mag", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidgetWells->horizontalHeaderItem(12);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Pp", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "OK", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GSDlgInteractiveCurvatureAnalysis", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSDlgInteractiveCurvatureAnalysis: public Ui_GSDlgInteractiveCurvatureAnalysis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSDLGINTERACTIVECURVATUREANALYSIS_H
