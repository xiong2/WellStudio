/********************************************************************************
** Form generated from reading UI file 'gsdlginteractivecalculation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSDLGINTERACTIVECALCULATION_H
#define UI_GSDLGINTERACTIVECALCULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "gsbasemapview.h"

QT_BEGIN_NAMESPACE

class Ui_GSDlgInteractiveCalculation
{
public:
    QGridLayout *gridLayout;
    GSBasemapView *graphicsView;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBoxSmooth;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_8;
    QPushButton *pushButtonFit;
    QGroupBox *groupBoxRemoveOverlap;
    QGridLayout *gridLayout_4;
    QLabel *label_11;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBoxOverlap;
    QLineEdit *lineEditTrapWidth;
    QCheckBox *checkBoxLinesVisible;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_7;
    QPushButton *pushButtonSearch;
    QRadioButton *radioButtonGroup;
    QRadioButton *radioButtonDirection;
    QLabel *label_9;
    QCheckBox *checkBoxPointsVisible;
    QGroupBox *groupBoxTrap2;
    QGridLayout *gridLayout_2;
    QLabel *label_22;
    QSpinBox *spinBoxRadius2;
    QRadioButton *radioButtonAnti2;
    QRadioButton *radioButtonSyn2;
    QLineEdit *lineEditLT2;
    QSpinBox *spinBoxHeight2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_23;
    QDoubleSpinBox *doubleSpinBoxCT2;
    QGroupBox *groupBoxTrap3;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButtonSyn3;
    QSpinBox *spinBoxRadius3;
    QRadioButton *radioButtonAnti3;
    QSpinBox *spinBoxHeight3;
    QLabel *label_6;
    QLineEdit *lineEditLT3;
    QDoubleSpinBox *doubleSpinBoxCT3;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_5;
    QGroupBox *groupBoxTrap1;
    QGridLayout *gridLayout_13;
    QRadioButton *radioButtonAnti1;
    QRadioButton *radioButtonSyn1;
    QLabel *label;
    QSpinBox *spinBoxRadius1;
    QLabel *label_2;
    QSpinBox *spinBoxHeight1;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBoxCT1;
    QLineEdit *lineEditLT1;
    QLabel *label_8;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_9;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_5;
    QLabel *label_14;
    QSpinBox *spinBoxSRatio;
    QLabel *label_15;
    QSpinBox *spinBoxSRadius;
    QGroupBox *groupBoxStructureMerge;
    QGridLayout *gridLayout_6;
    QLabel *label_13;
    QLabel *label_12;
    QSpinBox *spinBoxMergeAngle;
    QDoubleSpinBox *doubleSpinBoxMergeOverlap;
    QPushButton *pushButtonCreate;
    QGroupBox *groupBoxFaults;
    QGridLayout *gridLayout_12;
    QLineEdit *lineEditFaultLength;
    QLabel *label_16;
    QPushButton *pushButtonFault;
    QCheckBox *checkBoxFaultVisible;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_11;
    QDoubleSpinBox *doubleSpinBoxCSS;
    QLabel *label_19;
    QLabel *label_18;
    QLabel *label_20;
    QLabel *label_17;
    QDoubleSpinBox *doubleSpinBoxSS;
    QDoubleSpinBox *doubleSpinBoxNorm;
    QDoubleSpinBox *doubleSpinBoxESS;
    QLabel *label_26;
    QSpinBox *spinBoxFLT;
    QPushButton *pushButtonAccept;
    QHBoxLayout *horizontalLayout;
    QLabel *label_21;
    QLineEdit *lineEditOutput;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonStress;
    QPushButton *pushButtonClear;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *GSDlgInteractiveCalculation)
    {
        if (GSDlgInteractiveCalculation->objectName().isEmpty())
            GSDlgInteractiveCalculation->setObjectName(QString::fromUtf8("GSDlgInteractiveCalculation"));
        GSDlgInteractiveCalculation->resize(1507, 856);
        gridLayout = new QGridLayout(GSDlgInteractiveCalculation);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new GSBasemapView(GSDlgInteractiveCalculation);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(400, 600));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        groupBox = new QGroupBox(GSDlgInteractiveCalculation);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer, 14, 0, 1, 1);

        checkBoxSmooth = new QCheckBox(groupBox);
        checkBoxSmooth->setObjectName(QString::fromUtf8("checkBoxSmooth"));
        checkBoxSmooth->setChecked(true);

        gridLayout_10->addWidget(checkBoxSmooth, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(200, 0));
        groupBox_3->setMaximumSize(QSize(200, 16777215));
        gridLayout_8 = new QGridLayout(groupBox_3);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        pushButtonFit = new QPushButton(groupBox_3);
        pushButtonFit->setObjectName(QString::fromUtf8("pushButtonFit"));

        gridLayout_8->addWidget(pushButtonFit, 4, 0, 1, 2);

        groupBoxRemoveOverlap = new QGroupBox(groupBox_3);
        groupBoxRemoveOverlap->setObjectName(QString::fromUtf8("groupBoxRemoveOverlap"));
        groupBoxRemoveOverlap->setCheckable(true);
        gridLayout_4 = new QGridLayout(groupBoxRemoveOverlap);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_11 = new QLabel(groupBoxRemoveOverlap);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_4->addWidget(label_11, 1, 0, 2, 1);

        label_10 = new QLabel(groupBoxRemoveOverlap);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 0, 0, 1, 1);

        doubleSpinBoxOverlap = new QDoubleSpinBox(groupBoxRemoveOverlap);
        doubleSpinBoxOverlap->setObjectName(QString::fromUtf8("doubleSpinBoxOverlap"));
        doubleSpinBoxOverlap->setDecimals(1);
        doubleSpinBoxOverlap->setMinimum(0.100000000000000);
        doubleSpinBoxOverlap->setMaximum(0.800000000000000);
        doubleSpinBoxOverlap->setSingleStep(0.100000000000000);
        doubleSpinBoxOverlap->setValue(0.300000000000000);

        gridLayout_4->addWidget(doubleSpinBoxOverlap, 1, 2, 1, 1);

        lineEditTrapWidth = new QLineEdit(groupBoxRemoveOverlap);
        lineEditTrapWidth->setObjectName(QString::fromUtf8("lineEditTrapWidth"));

        gridLayout_4->addWidget(lineEditTrapWidth, 0, 2, 1, 1);


        gridLayout_8->addWidget(groupBoxRemoveOverlap, 2, 0, 1, 2);

        checkBoxLinesVisible = new QCheckBox(groupBox_3);
        checkBoxLinesVisible->setObjectName(QString::fromUtf8("checkBoxLinesVisible"));
        checkBoxLinesVisible->setChecked(true);

        gridLayout_8->addWidget(checkBoxLinesVisible, 3, 0, 1, 2);


        gridLayout_10->addWidget(groupBox_3, 1, 2, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(200, 0));
        groupBox_2->setMaximumSize(QSize(200, 16777215));
        groupBox_2->setCheckable(false);
        gridLayout_7 = new QGridLayout(groupBox_2);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        pushButtonSearch = new QPushButton(groupBox_2);
        pushButtonSearch->setObjectName(QString::fromUtf8("pushButtonSearch"));

        gridLayout_7->addWidget(pushButtonSearch, 8, 0, 1, 3);

        radioButtonGroup = new QRadioButton(groupBox_2);
        buttonGroup = new QButtonGroup(GSDlgInteractiveCalculation);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButtonGroup);
        radioButtonGroup->setObjectName(QString::fromUtf8("radioButtonGroup"));
        radioButtonGroup->setChecked(true);

        gridLayout_7->addWidget(radioButtonGroup, 5, 2, 1, 1);

        radioButtonDirection = new QRadioButton(groupBox_2);
        buttonGroup->addButton(radioButtonDirection);
        radioButtonDirection->setObjectName(QString::fromUtf8("radioButtonDirection"));

        gridLayout_7->addWidget(radioButtonDirection, 5, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_7->addWidget(label_9, 5, 0, 1, 1);

        checkBoxPointsVisible = new QCheckBox(groupBox_2);
        checkBoxPointsVisible->setObjectName(QString::fromUtf8("checkBoxPointsVisible"));
        checkBoxPointsVisible->setChecked(true);

        gridLayout_7->addWidget(checkBoxPointsVisible, 4, 0, 1, 1);

        groupBoxTrap2 = new QGroupBox(groupBox_2);
        groupBoxTrap2->setObjectName(QString::fromUtf8("groupBoxTrap2"));
        groupBoxTrap2->setCheckable(true);
        groupBoxTrap2->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBoxTrap2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_22 = new QLabel(groupBoxTrap2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_2->addWidget(label_22, 5, 0, 1, 1);

        spinBoxRadius2 = new QSpinBox(groupBoxTrap2);
        spinBoxRadius2->setObjectName(QString::fromUtf8("spinBoxRadius2"));
        spinBoxRadius2->setMinimum(500);
        spinBoxRadius2->setMaximum(4000);
        spinBoxRadius2->setSingleStep(250);
        spinBoxRadius2->setValue(3000);

        gridLayout_2->addWidget(spinBoxRadius2, 1, 2, 1, 1);

        radioButtonAnti2 = new QRadioButton(groupBoxTrap2);
        radioButtonAnti2->setObjectName(QString::fromUtf8("radioButtonAnti2"));
        radioButtonAnti2->setChecked(true);

        gridLayout_2->addWidget(radioButtonAnti2, 0, 0, 1, 1);

        radioButtonSyn2 = new QRadioButton(groupBoxTrap2);
        radioButtonSyn2->setObjectName(QString::fromUtf8("radioButtonSyn2"));

        gridLayout_2->addWidget(radioButtonSyn2, 0, 1, 1, 2);

        lineEditLT2 = new QLineEdit(groupBoxTrap2);
        lineEditLT2->setObjectName(QString::fromUtf8("lineEditLT2"));

        gridLayout_2->addWidget(lineEditLT2, 7, 2, 1, 1);

        spinBoxHeight2 = new QSpinBox(groupBoxTrap2);
        spinBoxHeight2->setObjectName(QString::fromUtf8("spinBoxHeight2"));
        spinBoxHeight2->setMinimum(8);
        spinBoxHeight2->setMaximum(50);
        spinBoxHeight2->setValue(12);

        gridLayout_2->addWidget(spinBoxHeight2, 2, 2, 1, 1);

        label_3 = new QLabel(groupBoxTrap2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(groupBoxTrap2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        label_23 = new QLabel(groupBoxTrap2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_2->addWidget(label_23, 7, 0, 1, 1);

        doubleSpinBoxCT2 = new QDoubleSpinBox(groupBoxTrap2);
        doubleSpinBoxCT2->setObjectName(QString::fromUtf8("doubleSpinBoxCT2"));
        doubleSpinBoxCT2->setDecimals(1);
        doubleSpinBoxCT2->setMinimum(0.500000000000000);
        doubleSpinBoxCT2->setMaximum(0.900000000000000);
        doubleSpinBoxCT2->setSingleStep(0.100000000000000);
        doubleSpinBoxCT2->setValue(0.900000000000000);

        gridLayout_2->addWidget(doubleSpinBoxCT2, 5, 2, 1, 1);


        gridLayout_7->addWidget(groupBoxTrap2, 2, 0, 1, 3);

        groupBoxTrap3 = new QGroupBox(groupBox_2);
        groupBoxTrap3->setObjectName(QString::fromUtf8("groupBoxTrap3"));
        groupBoxTrap3->setCheckable(true);
        groupBoxTrap3->setChecked(false);
        gridLayout_3 = new QGridLayout(groupBoxTrap3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioButtonSyn3 = new QRadioButton(groupBoxTrap3);
        radioButtonSyn3->setObjectName(QString::fromUtf8("radioButtonSyn3"));

        gridLayout_3->addWidget(radioButtonSyn3, 0, 1, 1, 2);

        spinBoxRadius3 = new QSpinBox(groupBoxTrap3);
        spinBoxRadius3->setObjectName(QString::fromUtf8("spinBoxRadius3"));
        spinBoxRadius3->setMinimum(500);
        spinBoxRadius3->setMaximum(4000);
        spinBoxRadius3->setSingleStep(250);
        spinBoxRadius3->setValue(3000);

        gridLayout_3->addWidget(spinBoxRadius3, 1, 2, 3, 1);

        radioButtonAnti3 = new QRadioButton(groupBoxTrap3);
        radioButtonAnti3->setObjectName(QString::fromUtf8("radioButtonAnti3"));
        radioButtonAnti3->setChecked(true);

        gridLayout_3->addWidget(radioButtonAnti3, 0, 0, 1, 1);

        spinBoxHeight3 = new QSpinBox(groupBoxTrap3);
        spinBoxHeight3->setObjectName(QString::fromUtf8("spinBoxHeight3"));
        spinBoxHeight3->setMinimum(8);
        spinBoxHeight3->setMaximum(50);
        spinBoxHeight3->setValue(12);

        gridLayout_3->addWidget(spinBoxHeight3, 4, 2, 1, 1);

        label_6 = new QLabel(groupBoxTrap3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 4, 0, 1, 1);

        lineEditLT3 = new QLineEdit(groupBoxTrap3);
        lineEditLT3->setObjectName(QString::fromUtf8("lineEditLT3"));

        gridLayout_3->addWidget(lineEditLT3, 8, 2, 1, 1);

        doubleSpinBoxCT3 = new QDoubleSpinBox(groupBoxTrap3);
        doubleSpinBoxCT3->setObjectName(QString::fromUtf8("doubleSpinBoxCT3"));
        doubleSpinBoxCT3->setDecimals(1);
        doubleSpinBoxCT3->setMinimum(0.500000000000000);
        doubleSpinBoxCT3->setMaximum(0.900000000000000);
        doubleSpinBoxCT3->setSingleStep(0.100000000000000);
        doubleSpinBoxCT3->setValue(0.900000000000000);

        gridLayout_3->addWidget(doubleSpinBoxCT3, 5, 2, 1, 1);

        label_24 = new QLabel(groupBoxTrap3);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_3->addWidget(label_24, 5, 0, 1, 1);

        label_25 = new QLabel(groupBoxTrap3);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_3->addWidget(label_25, 8, 0, 1, 1);

        label_5 = new QLabel(groupBoxTrap3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 2, 0, 1, 1);


        gridLayout_7->addWidget(groupBoxTrap3, 3, 0, 1, 3);

        groupBoxTrap1 = new QGroupBox(groupBox_2);
        groupBoxTrap1->setObjectName(QString::fromUtf8("groupBoxTrap1"));
        groupBoxTrap1->setCheckable(true);
        gridLayout_13 = new QGridLayout(groupBoxTrap1);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        radioButtonAnti1 = new QRadioButton(groupBoxTrap1);
        radioButtonAnti1->setObjectName(QString::fromUtf8("radioButtonAnti1"));
        radioButtonAnti1->setChecked(true);

        gridLayout_13->addWidget(radioButtonAnti1, 0, 0, 1, 1);

        radioButtonSyn1 = new QRadioButton(groupBoxTrap1);
        radioButtonSyn1->setObjectName(QString::fromUtf8("radioButtonSyn1"));

        gridLayout_13->addWidget(radioButtonSyn1, 0, 1, 1, 1);

        label = new QLabel(groupBoxTrap1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_13->addWidget(label, 1, 0, 1, 1);

        spinBoxRadius1 = new QSpinBox(groupBoxTrap1);
        spinBoxRadius1->setObjectName(QString::fromUtf8("spinBoxRadius1"));
        spinBoxRadius1->setMinimum(500);
        spinBoxRadius1->setMaximum(4000);
        spinBoxRadius1->setSingleStep(250);
        spinBoxRadius1->setValue(3000);

        gridLayout_13->addWidget(spinBoxRadius1, 1, 1, 1, 1);

        label_2 = new QLabel(groupBoxTrap1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_13->addWidget(label_2, 2, 0, 1, 1);

        spinBoxHeight1 = new QSpinBox(groupBoxTrap1);
        spinBoxHeight1->setObjectName(QString::fromUtf8("spinBoxHeight1"));
        spinBoxHeight1->setMinimum(8);
        spinBoxHeight1->setMaximum(50);
        spinBoxHeight1->setValue(12);

        gridLayout_13->addWidget(spinBoxHeight1, 2, 1, 1, 1);

        label_7 = new QLabel(groupBoxTrap1);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_13->addWidget(label_7, 3, 0, 1, 1);

        doubleSpinBoxCT1 = new QDoubleSpinBox(groupBoxTrap1);
        doubleSpinBoxCT1->setObjectName(QString::fromUtf8("doubleSpinBoxCT1"));
        doubleSpinBoxCT1->setDecimals(1);
        doubleSpinBoxCT1->setMinimum(0.500000000000000);
        doubleSpinBoxCT1->setMaximum(0.900000000000000);
        doubleSpinBoxCT1->setSingleStep(0.100000000000000);
        doubleSpinBoxCT1->setValue(0.900000000000000);

        gridLayout_13->addWidget(doubleSpinBoxCT1, 3, 1, 1, 1);

        lineEditLT1 = new QLineEdit(groupBoxTrap1);
        lineEditLT1->setObjectName(QString::fromUtf8("lineEditLT1"));

        gridLayout_13->addWidget(lineEditLT1, 4, 1, 1, 1);

        label_8 = new QLabel(groupBoxTrap1);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_13->addWidget(label_8, 4, 0, 1, 1);


        gridLayout_7->addWidget(groupBoxTrap1, 0, 0, 1, 3);


        gridLayout_10->addWidget(groupBox_2, 1, 0, 4, 2);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(200, 16777215));
        gridLayout_9 = new QGridLayout(groupBox_4);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        groupBox_6 = new QGroupBox(groupBox_4);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_5 = new QGridLayout(groupBox_6);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_14 = new QLabel(groupBox_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_5->addWidget(label_14, 0, 0, 1, 1);

        spinBoxSRatio = new QSpinBox(groupBox_6);
        spinBoxSRatio->setObjectName(QString::fromUtf8("spinBoxSRatio"));
        spinBoxSRatio->setMinimum(1);
        spinBoxSRatio->setMaximum(20);
        spinBoxSRatio->setValue(5);

        gridLayout_5->addWidget(spinBoxSRatio, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_5->addWidget(label_15, 1, 0, 1, 1);

        spinBoxSRadius = new QSpinBox(groupBox_6);
        spinBoxSRadius->setObjectName(QString::fromUtf8("spinBoxSRadius"));
        spinBoxSRadius->setMaximumSize(QSize(45, 16777215));
        spinBoxSRadius->setMinimum(2000);
        spinBoxSRadius->setMaximum(6000);
        spinBoxSRadius->setSingleStep(500);
        spinBoxSRadius->setValue(4000);

        gridLayout_5->addWidget(spinBoxSRadius, 1, 1, 1, 1);


        gridLayout_9->addWidget(groupBox_6, 0, 0, 1, 1);

        groupBoxStructureMerge = new QGroupBox(groupBox_4);
        groupBoxStructureMerge->setObjectName(QString::fromUtf8("groupBoxStructureMerge"));
        groupBoxStructureMerge->setCheckable(true);
        gridLayout_6 = new QGridLayout(groupBoxStructureMerge);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_13 = new QLabel(groupBoxStructureMerge);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_6->addWidget(label_13, 1, 0, 1, 1);

        label_12 = new QLabel(groupBoxStructureMerge);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_6->addWidget(label_12, 0, 0, 1, 3);

        spinBoxMergeAngle = new QSpinBox(groupBoxStructureMerge);
        spinBoxMergeAngle->setObjectName(QString::fromUtf8("spinBoxMergeAngle"));
        spinBoxMergeAngle->setMaximum(90);
        spinBoxMergeAngle->setSingleStep(5);
        spinBoxMergeAngle->setValue(20);

        gridLayout_6->addWidget(spinBoxMergeAngle, 0, 3, 1, 1);

        doubleSpinBoxMergeOverlap = new QDoubleSpinBox(groupBoxStructureMerge);
        doubleSpinBoxMergeOverlap->setObjectName(QString::fromUtf8("doubleSpinBoxMergeOverlap"));
        doubleSpinBoxMergeOverlap->setDecimals(1);
        doubleSpinBoxMergeOverlap->setMinimum(0.100000000000000);
        doubleSpinBoxMergeOverlap->setMaximum(0.800000000000000);
        doubleSpinBoxMergeOverlap->setSingleStep(0.100000000000000);
        doubleSpinBoxMergeOverlap->setValue(0.500000000000000);

        gridLayout_6->addWidget(doubleSpinBoxMergeOverlap, 1, 3, 1, 1);


        gridLayout_9->addWidget(groupBoxStructureMerge, 1, 0, 1, 1);

        pushButtonCreate = new QPushButton(groupBox_4);
        pushButtonCreate->setObjectName(QString::fromUtf8("pushButtonCreate"));

        gridLayout_9->addWidget(pushButtonCreate, 2, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_4, 3, 2, 2, 1);

        groupBoxFaults = new QGroupBox(groupBox);
        groupBoxFaults->setObjectName(QString::fromUtf8("groupBoxFaults"));
        groupBoxFaults->setMinimumSize(QSize(200, 0));
        groupBoxFaults->setMaximumSize(QSize(200, 16777215));
        groupBoxFaults->setCheckable(true);
        gridLayout_12 = new QGridLayout(groupBoxFaults);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        lineEditFaultLength = new QLineEdit(groupBoxFaults);
        lineEditFaultLength->setObjectName(QString::fromUtf8("lineEditFaultLength"));

        gridLayout_12->addWidget(lineEditFaultLength, 1, 1, 1, 1);

        label_16 = new QLabel(groupBoxFaults);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_12->addWidget(label_16, 1, 0, 1, 1);

        pushButtonFault = new QPushButton(groupBoxFaults);
        pushButtonFault->setObjectName(QString::fromUtf8("pushButtonFault"));

        gridLayout_12->addWidget(pushButtonFault, 4, 0, 1, 2);

        checkBoxFaultVisible = new QCheckBox(groupBoxFaults);
        checkBoxFaultVisible->setObjectName(QString::fromUtf8("checkBoxFaultVisible"));
        checkBoxFaultVisible->setChecked(true);

        gridLayout_12->addWidget(checkBoxFaultVisible, 3, 0, 1, 2);

        groupBox_5 = new QGroupBox(groupBoxFaults);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setCheckable(true);
        gridLayout_11 = new QGridLayout(groupBox_5);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        doubleSpinBoxCSS = new QDoubleSpinBox(groupBox_5);
        doubleSpinBoxCSS->setObjectName(QString::fromUtf8("doubleSpinBoxCSS"));
        doubleSpinBoxCSS->setMinimum(0.500000000000000);
        doubleSpinBoxCSS->setMaximum(0.990000000000000);
        doubleSpinBoxCSS->setSingleStep(0.010000000000000);
        doubleSpinBoxCSS->setValue(0.800000000000000);

        gridLayout_11->addWidget(doubleSpinBoxCSS, 3, 1, 1, 1);

        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_11->addWidget(label_19, 2, 0, 1, 1);

        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_11->addWidget(label_18, 1, 0, 1, 1);

        label_20 = new QLabel(groupBox_5);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_11->addWidget(label_20, 3, 0, 1, 1);

        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_11->addWidget(label_17, 0, 0, 1, 1);

        doubleSpinBoxSS = new QDoubleSpinBox(groupBox_5);
        doubleSpinBoxSS->setObjectName(QString::fromUtf8("doubleSpinBoxSS"));
        doubleSpinBoxSS->setMinimum(0.300000000000000);
        doubleSpinBoxSS->setMaximum(0.800000000000000);
        doubleSpinBoxSS->setSingleStep(0.010000000000000);
        doubleSpinBoxSS->setValue(0.500000000000000);

        gridLayout_11->addWidget(doubleSpinBoxSS, 2, 1, 1, 1);

        doubleSpinBoxNorm = new QDoubleSpinBox(groupBox_5);
        doubleSpinBoxNorm->setObjectName(QString::fromUtf8("doubleSpinBoxNorm"));
        doubleSpinBoxNorm->setMaximum(0.300000000000000);
        doubleSpinBoxNorm->setSingleStep(0.010000000000000);
        doubleSpinBoxNorm->setValue(0.130000000000000);

        gridLayout_11->addWidget(doubleSpinBoxNorm, 0, 1, 1, 1);

        doubleSpinBoxESS = new QDoubleSpinBox(groupBox_5);
        doubleSpinBoxESS->setObjectName(QString::fromUtf8("doubleSpinBoxESS"));
        doubleSpinBoxESS->setMinimum(0.100000000000000);
        doubleSpinBoxESS->setMaximum(0.500000000000000);
        doubleSpinBoxESS->setSingleStep(0.010000000000000);
        doubleSpinBoxESS->setValue(0.290000000000000);

        gridLayout_11->addWidget(doubleSpinBoxESS, 1, 1, 1, 1);


        gridLayout_12->addWidget(groupBox_5, 2, 0, 1, 2);

        label_26 = new QLabel(groupBoxFaults);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_12->addWidget(label_26, 0, 0, 1, 1);

        spinBoxFLT = new QSpinBox(groupBoxFaults);
        spinBoxFLT->setObjectName(QString::fromUtf8("spinBoxFLT"));
        spinBoxFLT->setMinimum(200);
        spinBoxFLT->setMaximum(800);
        spinBoxFLT->setSingleStep(100);
        spinBoxFLT->setValue(600);

        gridLayout_12->addWidget(spinBoxFLT, 0, 1, 1, 1);


        gridLayout_10->addWidget(groupBoxFaults, 2, 2, 1, 1);

        pushButtonAccept = new QPushButton(groupBox);
        pushButtonAccept->setObjectName(QString::fromUtf8("pushButtonAccept"));
        pushButtonAccept->setMaximumSize(QSize(200, 16777215));

        gridLayout_10->addWidget(pushButtonAccept, 10, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy2);
        label_21->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(label_21);

        lineEditOutput = new QLineEdit(groupBox);
        lineEditOutput->setObjectName(QString::fromUtf8("lineEditOutput"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEditOutput->sizePolicy().hasHeightForWidth());
        lineEditOutput->setSizePolicy(sizePolicy3);
        lineEditOutput->setMinimumSize(QSize(300, 0));
        lineEditOutput->setMaximumSize(QSize(300, 16777215));
        lineEditOutput->setLayoutDirection(Qt::RightToLeft);
        lineEditOutput->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEditOutput);


        gridLayout_10->addLayout(horizontalLayout, 7, 0, 1, 3);

        pushButtonClose = new QPushButton(groupBox);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));

        gridLayout_10->addWidget(pushButtonClose, 10, 2, 1, 1);

        pushButtonStress = new QPushButton(groupBox);
        pushButtonStress->setObjectName(QString::fromUtf8("pushButtonStress"));

        gridLayout_10->addWidget(pushButtonStress, 9, 2, 1, 1);

        pushButtonClear = new QPushButton(groupBox);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));
        pushButtonClear->setMaximumSize(QSize(200, 16777215));

        gridLayout_10->addWidget(pushButtonClear, 9, 0, 1, 2);


        verticalLayout->addWidget(groupBox);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(GSDlgInteractiveCalculation);

        QMetaObject::connectSlotsByName(GSDlgInteractiveCalculation);
    } // setupUi

    void retranslateUi(QDialog *GSDlgInteractiveCalculation)
    {
        GSDlgInteractiveCalculation->setWindowTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "GSDlgInteractiveCalculation", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Calculate Parameters", nullptr));
        checkBoxSmooth->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Isopach Smooth", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Fit Trap Lines", nullptr));
        pushButtonFit->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Fit Lines", nullptr));
        groupBoxRemoveOverlap->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Remove Overlap Traps", nullptr));
        label_11->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Overlap Ratio", nullptr));
        label_10->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Trap Width(m)", nullptr));
        lineEditTrapWidth->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "2000", nullptr));
        checkBoxLinesVisible->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Visible", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Search Trap Points", nullptr));
        pushButtonSearch->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Search Points", nullptr));
        radioButtonGroup->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Group", nullptr));
        radioButtonDirection->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Direction", nullptr));
        label_9->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Color by:", nullptr));
        checkBoxPointsVisible->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Visible", nullptr));
        groupBoxTrap2->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Trap 2", nullptr));
        label_22->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Correlate", nullptr));
        radioButtonAnti2->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Anticline", nullptr));
        radioButtonSyn2->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Syncline", nullptr));
        lineEditLT2->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "5000", nullptr));
        label_3->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Search Radius", nullptr));
        label_4->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Trap Height", nullptr));
        label_23->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Min Length", nullptr));
        groupBoxTrap3->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Trap 3", nullptr));
        radioButtonSyn3->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Syncline", nullptr));
        radioButtonAnti3->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Anticline", nullptr));
        label_6->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Trap Height", nullptr));
        lineEditLT3->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "5000", nullptr));
        label_24->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Correlate", nullptr));
        label_25->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Min Length", nullptr));
        label_5->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Search Radius(m)", nullptr));
        groupBoxTrap1->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Trap 1", nullptr));
        radioButtonAnti1->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Anticline", nullptr));
        radioButtonSyn1->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Syncline", nullptr));
        label->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Search Radius", nullptr));
        label_2->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Trap Height", nullptr));
        label_7->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Correlate ", nullptr));
        lineEditLT1->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "5000", nullptr));
        label_8->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Min Length ", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Structure", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Trap Size", nullptr));
        label_14->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Length vs Width", nullptr));
        label_15->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Maximum Radius(m)", nullptr));
        groupBoxStructureMerge->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Structures Merge", nullptr));
        label_13->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Overlap Ratio", nullptr));
        label_12->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Intersection Angle", nullptr));
        pushButtonCreate->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Create Structures", nullptr));
        groupBoxFaults->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Faults", nullptr));
        lineEditFaultLength->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "4000", nullptr));
        label_16->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Min Fault Length(m)", nullptr));
        pushButtonFault->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Adjust Faults", nullptr));
        checkBoxFaultVisible->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Visible", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("GSDlgInteractiveCalculation", "Reverse Fraction", nullptr));
        label_19->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "SS Fault", nullptr));
        label_18->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "ESS Fault", nullptr));
        label_20->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "CSS Fault", nullptr));
        label_17->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Normal Fault", nullptr));
        label_26->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Linearity Tolerance", nullptr));
        pushButtonAccept->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Accept", nullptr));
        label_21->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Output Map", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Close", nullptr));
        pushButtonStress->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Calculate Stress", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("GSDlgInteractiveCalculation", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSDlgInteractiveCalculation: public Ui_GSDlgInteractiveCalculation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSDLGINTERACTIVECALCULATION_H
