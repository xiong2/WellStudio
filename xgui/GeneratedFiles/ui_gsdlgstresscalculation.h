/********************************************************************************
** Form generated from reading UI file 'gsdlgstresscalculation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSDLGSTRESSCALCULATION_H
#define UI_GSDLGSTRESSCALCULATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
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

QT_BEGIN_NAMESPACE

class Ui_GSDlgStressCalculation
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBoxSurvey;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonSAll;
    QPushButton *pushButtonDAll;
    QGroupBox *groupBox_2;
    QCheckBox *checkBoxFaults;
    QGroupBox *groupBoxShape1;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBoxRadius;
    QLineEdit *lineEditLength;
    QLabel *labelHeight;
    QRadioButton *radioButtonAnti;
    QLabel *labelLength;
    QDoubleSpinBox *doubleSpinBox;
    QRadioButton *radioButtonSyn;
    QLabel *labelCorre;
    QCheckBox *checkBoxAuto;
    QLabel *labelRadius;
    QSpinBox *spinBoxHeight;
    QGroupBox *groupBoxShape2;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *doubleSpinBox_2;
    QCheckBox *checkBoxAuto_2;
    QLabel *labelRadius_2;
    QLineEdit *lineEditLength_2;
    QLabel *labelCorre_2;
    QRadioButton *radioButtonAnti_2;
    QLabel *labelLength_2;
    QSpinBox *spinBoxHeight_2;
    QLabel *labelHeight_2;
    QSpinBox *spinBoxRadius_2;
    QRadioButton *radioButtonSyn_2;
    QGroupBox *groupBoxShape3;
    QGridLayout *gridLayout_4;
    QSpinBox *spinBoxRadius_3;
    QLabel *labelHeight_3;
    QLineEdit *lineEditLength_3;
    QRadioButton *radioButtonAnti_3;
    QLabel *labelLength_3;
    QDoubleSpinBox *doubleSpinBox_3;
    QLabel *labelRadius_3;
    QRadioButton *radioButtonSyn_3;
    QCheckBox *checkBoxAuto_3;
    QLabel *labelCorre_3;
    QSpinBox *spinBoxHeight_3;
    QGroupBox *groupBoxMerge;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxOverlap;
    QLabel *label_3;
    QSpinBox *spinBoxAngle;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GSDlgStressCalculation)
    {
        if (GSDlgStressCalculation->objectName().isEmpty())
            GSDlgStressCalculation->setObjectName(QString::fromUtf8("GSDlgStressCalculation"));
        GSDlgStressCalculation->resize(846, 667);
        gridLayout_5 = new QGridLayout(GSDlgStressCalculation);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(GSDlgStressCalculation);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(32, 32));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxSurvey = new QComboBox(groupBox);
        comboBoxSurvey->setObjectName(QString::fromUtf8("comboBoxSurvey"));
        comboBoxSurvey->setMinimumSize(QSize(160, 0));
        comboBoxSurvey->setMaximumSize(QSize(160, 16777215));

        gridLayout->addWidget(comboBoxSurvey, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(511, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->horizontalHeader()->setDefaultSectionSize(200);
        tableWidget->verticalHeader()->setMinimumSectionSize(40);
        tableWidget->verticalHeader()->setDefaultSectionSize(40);

        gridLayout->addWidget(tableWidget, 1, 0, 3, 3);

        verticalSpacer = new QSpacerItem(20, 144, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 3, 1, 1);

        pushButtonSAll = new QPushButton(groupBox);
        pushButtonSAll->setObjectName(QString::fromUtf8("pushButtonSAll"));
        pushButtonSAll->setMinimumSize(QSize(32, 32));
        pushButtonSAll->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/SelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSAll->setIcon(icon);

        gridLayout->addWidget(pushButtonSAll, 2, 3, 1, 1);

        pushButtonDAll = new QPushButton(groupBox);
        pushButtonDAll->setObjectName(QString::fromUtf8("pushButtonDAll"));
        pushButtonDAll->setMinimumSize(QSize(32, 32));
        pushButtonDAll->setMaximumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/DisSelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonDAll->setIcon(icon1);

        gridLayout->addWidget(pushButtonDAll, 3, 3, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(GSDlgStressCalculation);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 260));
        groupBox_2->setMaximumSize(QSize(16777215, 260));
        checkBoxFaults = new QCheckBox(groupBox_2);
        checkBoxFaults->setObjectName(QString::fromUtf8("checkBoxFaults"));
        checkBoxFaults->setGeometry(QRect(10, 20, 101, 16));
        checkBoxFaults->setChecked(true);
        groupBoxShape1 = new QGroupBox(groupBox_2);
        groupBoxShape1->setObjectName(QString::fromUtf8("groupBoxShape1"));
        groupBoxShape1->setGeometry(QRect(10, 50, 251, 201));
        groupBoxShape1->setCheckable(true);
        gridLayout_2 = new QGridLayout(groupBoxShape1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinBoxRadius = new QSpinBox(groupBoxShape1);
        spinBoxRadius->setObjectName(QString::fromUtf8("spinBoxRadius"));
        spinBoxRadius->setEnabled(false);
        spinBoxRadius->setMinimum(500);
        spinBoxRadius->setMaximum(4000);
        spinBoxRadius->setSingleStep(500);
        spinBoxRadius->setValue(3000);

        gridLayout_2->addWidget(spinBoxRadius, 8, 2, 1, 1);

        lineEditLength = new QLineEdit(groupBoxShape1);
        lineEditLength->setObjectName(QString::fromUtf8("lineEditLength"));
        lineEditLength->setMaximumSize(QSize(60, 16777215));

        gridLayout_2->addWidget(lineEditLength, 5, 2, 1, 1);

        labelHeight = new QLabel(groupBoxShape1);
        labelHeight->setObjectName(QString::fromUtf8("labelHeight"));
        labelHeight->setEnabled(false);

        gridLayout_2->addWidget(labelHeight, 7, 0, 1, 2);

        radioButtonAnti = new QRadioButton(groupBoxShape1);
        radioButtonAnti->setObjectName(QString::fromUtf8("radioButtonAnti"));
        radioButtonAnti->setChecked(true);

        gridLayout_2->addWidget(radioButtonAnti, 0, 0, 1, 1);

        labelLength = new QLabel(groupBoxShape1);
        labelLength->setObjectName(QString::fromUtf8("labelLength"));

        gridLayout_2->addWidget(labelLength, 5, 0, 1, 2);

        doubleSpinBox = new QDoubleSpinBox(groupBoxShape1);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMaximumSize(QSize(60, 16777215));
        doubleSpinBox->setDecimals(1);
        doubleSpinBox->setMinimum(0.500000000000000);
        doubleSpinBox->setMaximum(0.900000000000000);
        doubleSpinBox->setSingleStep(0.100000000000000);
        doubleSpinBox->setValue(0.900000000000000);

        gridLayout_2->addWidget(doubleSpinBox, 4, 2, 1, 1);

        radioButtonSyn = new QRadioButton(groupBoxShape1);
        radioButtonSyn->setObjectName(QString::fromUtf8("radioButtonSyn"));

        gridLayout_2->addWidget(radioButtonSyn, 0, 1, 1, 1);

        labelCorre = new QLabel(groupBoxShape1);
        labelCorre->setObjectName(QString::fromUtf8("labelCorre"));

        gridLayout_2->addWidget(labelCorre, 4, 0, 1, 1);

        checkBoxAuto = new QCheckBox(groupBoxShape1);
        checkBoxAuto->setObjectName(QString::fromUtf8("checkBoxAuto"));
        checkBoxAuto->setChecked(true);

        gridLayout_2->addWidget(checkBoxAuto, 11, 0, 1, 2);

        labelRadius = new QLabel(groupBoxShape1);
        labelRadius->setObjectName(QString::fromUtf8("labelRadius"));
        labelRadius->setEnabled(false);

        gridLayout_2->addWidget(labelRadius, 8, 0, 1, 2);

        spinBoxHeight = new QSpinBox(groupBoxShape1);
        spinBoxHeight->setObjectName(QString::fromUtf8("spinBoxHeight"));
        spinBoxHeight->setEnabled(false);
        spinBoxHeight->setMinimum(8);
        spinBoxHeight->setMaximum(50);
        spinBoxHeight->setValue(12);

        gridLayout_2->addWidget(spinBoxHeight, 7, 2, 1, 1);

        groupBoxShape2 = new QGroupBox(groupBox_2);
        groupBoxShape2->setObjectName(QString::fromUtf8("groupBoxShape2"));
        groupBoxShape2->setGeometry(QRect(270, 50, 251, 201));
        groupBoxShape2->setCheckable(true);
        groupBoxShape2->setChecked(true);
        gridLayout_3 = new QGridLayout(groupBoxShape2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        doubleSpinBox_2 = new QDoubleSpinBox(groupBoxShape2);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setEnabled(true);
        doubleSpinBox_2->setMaximumSize(QSize(60, 16777215));
        doubleSpinBox_2->setDecimals(1);
        doubleSpinBox_2->setMinimum(0.500000000000000);
        doubleSpinBox_2->setMaximum(0.900000000000000);
        doubleSpinBox_2->setSingleStep(0.100000000000000);
        doubleSpinBox_2->setValue(0.900000000000000);

        gridLayout_3->addWidget(doubleSpinBox_2, 4, 2, 1, 1);

        checkBoxAuto_2 = new QCheckBox(groupBoxShape2);
        checkBoxAuto_2->setObjectName(QString::fromUtf8("checkBoxAuto_2"));
        checkBoxAuto_2->setEnabled(true);
        checkBoxAuto_2->setChecked(true);

        gridLayout_3->addWidget(checkBoxAuto_2, 11, 0, 1, 2);

        labelRadius_2 = new QLabel(groupBoxShape2);
        labelRadius_2->setObjectName(QString::fromUtf8("labelRadius_2"));
        labelRadius_2->setEnabled(false);

        gridLayout_3->addWidget(labelRadius_2, 8, 0, 1, 2);

        lineEditLength_2 = new QLineEdit(groupBoxShape2);
        lineEditLength_2->setObjectName(QString::fromUtf8("lineEditLength_2"));
        lineEditLength_2->setEnabled(true);
        lineEditLength_2->setMaximumSize(QSize(60, 16777215));

        gridLayout_3->addWidget(lineEditLength_2, 5, 2, 1, 1);

        labelCorre_2 = new QLabel(groupBoxShape2);
        labelCorre_2->setObjectName(QString::fromUtf8("labelCorre_2"));
        labelCorre_2->setEnabled(true);

        gridLayout_3->addWidget(labelCorre_2, 4, 0, 1, 1);

        radioButtonAnti_2 = new QRadioButton(groupBoxShape2);
        radioButtonAnti_2->setObjectName(QString::fromUtf8("radioButtonAnti_2"));
        radioButtonAnti_2->setEnabled(true);
        radioButtonAnti_2->setChecked(true);

        gridLayout_3->addWidget(radioButtonAnti_2, 0, 0, 1, 1);

        labelLength_2 = new QLabel(groupBoxShape2);
        labelLength_2->setObjectName(QString::fromUtf8("labelLength_2"));
        labelLength_2->setEnabled(true);

        gridLayout_3->addWidget(labelLength_2, 5, 0, 1, 2);

        spinBoxHeight_2 = new QSpinBox(groupBoxShape2);
        spinBoxHeight_2->setObjectName(QString::fromUtf8("spinBoxHeight_2"));
        spinBoxHeight_2->setEnabled(false);
        spinBoxHeight_2->setMinimum(8);
        spinBoxHeight_2->setMaximum(50);
        spinBoxHeight_2->setValue(12);

        gridLayout_3->addWidget(spinBoxHeight_2, 7, 2, 1, 1);

        labelHeight_2 = new QLabel(groupBoxShape2);
        labelHeight_2->setObjectName(QString::fromUtf8("labelHeight_2"));
        labelHeight_2->setEnabled(false);

        gridLayout_3->addWidget(labelHeight_2, 7, 0, 1, 2);

        spinBoxRadius_2 = new QSpinBox(groupBoxShape2);
        spinBoxRadius_2->setObjectName(QString::fromUtf8("spinBoxRadius_2"));
        spinBoxRadius_2->setEnabled(false);
        spinBoxRadius_2->setMinimum(500);
        spinBoxRadius_2->setMaximum(4000);
        spinBoxRadius_2->setSingleStep(500);
        spinBoxRadius_2->setValue(3000);

        gridLayout_3->addWidget(spinBoxRadius_2, 8, 2, 1, 1);

        radioButtonSyn_2 = new QRadioButton(groupBoxShape2);
        radioButtonSyn_2->setObjectName(QString::fromUtf8("radioButtonSyn_2"));
        radioButtonSyn_2->setEnabled(true);

        gridLayout_3->addWidget(radioButtonSyn_2, 0, 1, 1, 1);

        groupBoxShape3 = new QGroupBox(groupBox_2);
        groupBoxShape3->setObjectName(QString::fromUtf8("groupBoxShape3"));
        groupBoxShape3->setGeometry(QRect(550, 50, 251, 201));
        groupBoxShape3->setCheckable(true);
        groupBoxShape3->setChecked(true);
        gridLayout_4 = new QGridLayout(groupBoxShape3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        spinBoxRadius_3 = new QSpinBox(groupBoxShape3);
        spinBoxRadius_3->setObjectName(QString::fromUtf8("spinBoxRadius_3"));
        spinBoxRadius_3->setEnabled(false);
        spinBoxRadius_3->setMinimum(500);
        spinBoxRadius_3->setMaximum(4000);
        spinBoxRadius_3->setSingleStep(500);
        spinBoxRadius_3->setValue(3000);

        gridLayout_4->addWidget(spinBoxRadius_3, 8, 2, 1, 1);

        labelHeight_3 = new QLabel(groupBoxShape3);
        labelHeight_3->setObjectName(QString::fromUtf8("labelHeight_3"));
        labelHeight_3->setEnabled(false);

        gridLayout_4->addWidget(labelHeight_3, 7, 0, 1, 2);

        lineEditLength_3 = new QLineEdit(groupBoxShape3);
        lineEditLength_3->setObjectName(QString::fromUtf8("lineEditLength_3"));
        lineEditLength_3->setEnabled(true);
        lineEditLength_3->setMaximumSize(QSize(60, 16777215));

        gridLayout_4->addWidget(lineEditLength_3, 5, 2, 1, 1);

        radioButtonAnti_3 = new QRadioButton(groupBoxShape3);
        radioButtonAnti_3->setObjectName(QString::fromUtf8("radioButtonAnti_3"));
        radioButtonAnti_3->setEnabled(true);
        radioButtonAnti_3->setChecked(true);

        gridLayout_4->addWidget(radioButtonAnti_3, 0, 0, 1, 1);

        labelLength_3 = new QLabel(groupBoxShape3);
        labelLength_3->setObjectName(QString::fromUtf8("labelLength_3"));
        labelLength_3->setEnabled(true);

        gridLayout_4->addWidget(labelLength_3, 5, 0, 1, 2);

        doubleSpinBox_3 = new QDoubleSpinBox(groupBoxShape3);
        doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));
        doubleSpinBox_3->setEnabled(true);
        doubleSpinBox_3->setMaximumSize(QSize(60, 16777215));
        doubleSpinBox_3->setDecimals(1);
        doubleSpinBox_3->setMinimum(0.500000000000000);
        doubleSpinBox_3->setMaximum(0.900000000000000);
        doubleSpinBox_3->setSingleStep(0.100000000000000);
        doubleSpinBox_3->setValue(0.900000000000000);

        gridLayout_4->addWidget(doubleSpinBox_3, 4, 2, 1, 1);

        labelRadius_3 = new QLabel(groupBoxShape3);
        labelRadius_3->setObjectName(QString::fromUtf8("labelRadius_3"));
        labelRadius_3->setEnabled(false);

        gridLayout_4->addWidget(labelRadius_3, 8, 0, 1, 2);

        radioButtonSyn_3 = new QRadioButton(groupBoxShape3);
        radioButtonSyn_3->setObjectName(QString::fromUtf8("radioButtonSyn_3"));
        radioButtonSyn_3->setEnabled(true);

        gridLayout_4->addWidget(radioButtonSyn_3, 0, 1, 1, 1);

        checkBoxAuto_3 = new QCheckBox(groupBoxShape3);
        checkBoxAuto_3->setObjectName(QString::fromUtf8("checkBoxAuto_3"));
        checkBoxAuto_3->setEnabled(true);
        checkBoxAuto_3->setChecked(true);

        gridLayout_4->addWidget(checkBoxAuto_3, 11, 0, 1, 2);

        labelCorre_3 = new QLabel(groupBoxShape3);
        labelCorre_3->setObjectName(QString::fromUtf8("labelCorre_3"));
        labelCorre_3->setEnabled(true);

        gridLayout_4->addWidget(labelCorre_3, 4, 0, 1, 1);

        spinBoxHeight_3 = new QSpinBox(groupBoxShape3);
        spinBoxHeight_3->setObjectName(QString::fromUtf8("spinBoxHeight_3"));
        spinBoxHeight_3->setEnabled(false);
        spinBoxHeight_3->setMinimum(8);
        spinBoxHeight_3->setMaximum(50);
        spinBoxHeight_3->setValue(12);

        gridLayout_4->addWidget(spinBoxHeight_3, 7, 2, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBoxMerge = new QGroupBox(GSDlgStressCalculation);
        groupBoxMerge->setObjectName(QString::fromUtf8("groupBoxMerge"));
        groupBoxMerge->setCheckable(true);
        horizontalLayout = new QHBoxLayout(groupBoxMerge);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBoxMerge);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        doubleSpinBoxOverlap = new QDoubleSpinBox(groupBoxMerge);
        doubleSpinBoxOverlap->setObjectName(QString::fromUtf8("doubleSpinBoxOverlap"));
        doubleSpinBoxOverlap->setDecimals(1);
        doubleSpinBoxOverlap->setMinimum(0.100000000000000);
        doubleSpinBoxOverlap->setMaximum(0.900000000000000);
        doubleSpinBoxOverlap->setSingleStep(0.100000000000000);
        doubleSpinBoxOverlap->setValue(0.500000000000000);

        horizontalLayout->addWidget(doubleSpinBoxOverlap);

        label_3 = new QLabel(groupBoxMerge);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBoxAngle = new QSpinBox(groupBoxMerge);
        spinBoxAngle->setObjectName(QString::fromUtf8("spinBoxAngle"));
        spinBoxAngle->setMinimum(1);
        spinBoxAngle->setMaximum(45);
        spinBoxAngle->setValue(20);

        horizontalLayout->addWidget(spinBoxAngle);

        horizontalSpacer_2 = new QSpacerItem(425, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_5->addWidget(groupBoxMerge, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(GSDlgStressCalculation);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_5->addWidget(buttonBox, 3, 0, 1, 1);


        retranslateUi(GSDlgStressCalculation);
        QObject::connect(buttonBox, SIGNAL(accepted()), GSDlgStressCalculation, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GSDlgStressCalculation, SLOT(reject()));

        QMetaObject::connectSlotsByName(GSDlgStressCalculation);
    } // setupUi

    void retranslateUi(QDialog *GSDlgStressCalculation)
    {
        GSDlgStressCalculation->setWindowTitle(QCoreApplication::translate("GSDlgStressCalculation", "GSDlgStressCalculation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GSDlgStressCalculation", "Isopach Maps", nullptr));
        label->setText(QCoreApplication::translate("GSDlgStressCalculation", "Select Survey:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GSDlgStressCalculation", "Calculate", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GSDlgStressCalculation", "Isopach Map", nullptr));
        pushButtonSAll->setText(QString());
        pushButtonDAll->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("GSDlgStressCalculation", "Calculation Options", nullptr));
        checkBoxFaults->setText(QCoreApplication::translate("GSDlgStressCalculation", "Use Faults", nullptr));
        groupBoxShape1->setTitle(QCoreApplication::translate("GSDlgStressCalculation", "Trap 1", nullptr));
        lineEditLength->setText(QCoreApplication::translate("GSDlgStressCalculation", "5000", nullptr));
        labelHeight->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Structure Height(m)", nullptr));
        radioButtonAnti->setText(QCoreApplication::translate("GSDlgStressCalculation", "Anticline", nullptr));
        labelLength->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Structure Length(m)", nullptr));
        radioButtonSyn->setText(QCoreApplication::translate("GSDlgStressCalculation", "Syncline", nullptr));
        labelCorre->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Correlation \357\274\2100-1\357\274\211\357\274\211", nullptr));
        checkBoxAuto->setText(QCoreApplication::translate("GSDlgStressCalculation", "Auto select", nullptr));
        labelRadius->setText(QCoreApplication::translate("GSDlgStressCalculation", "Maximum Search Radius(m)", nullptr));
        groupBoxShape2->setTitle(QCoreApplication::translate("GSDlgStressCalculation", "Trap 2", nullptr));
        checkBoxAuto_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "Auto select", nullptr));
        labelRadius_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "Maximum Search Radius(m)", nullptr));
        lineEditLength_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "5000", nullptr));
        labelCorre_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Correlation \357\274\2100-1\357\274\211\357\274\211", nullptr));
        radioButtonAnti_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "Anticline", nullptr));
        labelLength_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Structure Length(m)", nullptr));
        labelHeight_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Structure Height(m)", nullptr));
        radioButtonSyn_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "Syncline", nullptr));
        groupBoxShape3->setTitle(QCoreApplication::translate("GSDlgStressCalculation", "Trap 3", nullptr));
        labelHeight_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Structure Height(m)", nullptr));
        lineEditLength_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "5000", nullptr));
        radioButtonAnti_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "Anticline", nullptr));
        labelLength_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Structure Length(m)", nullptr));
        labelRadius_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "Maximum Search Radius(m)", nullptr));
        radioButtonSyn_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "Syncline", nullptr));
        checkBoxAuto_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "Auto select", nullptr));
        labelCorre_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "Minimum Correlation \357\274\2100-1\357\274\211\357\274\211", nullptr));
        groupBoxMerge->setTitle(QCoreApplication::translate("GSDlgStressCalculation", "Structure Merge", nullptr));
        label_2->setText(QCoreApplication::translate("GSDlgStressCalculation", "Overlap Threshold", nullptr));
        label_3->setText(QCoreApplication::translate("GSDlgStressCalculation", "Intersection Angle Threshold", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSDlgStressCalculation: public Ui_GSDlgStressCalculation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSDLGSTRESSCALCULATION_H
