/********************************************************************************
** Form generated from reading UI file 'gsbmstressmapvispage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSBMSTRESSMAPVISPAGE_H
#define UI_GSBMSTRESSMAPVISPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_GSBMStressMapVisPage
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBoxStrressLine;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    CXButtonColorEdit *colorButton_StressLine;
    QLabel *label_16;
    QSpinBox *spinBoxLength;
    QLabel *label_2;
    QSpinBox *spinBox_StressLineWidth;
    QLabel *label_9;
    QSpinBox *spinBox_StressLineStep;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBoxFaultPolygon;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_14;
    CXButtonColorEdit *colorButtonFPL;
    QLabel *label_15;
    QSpinBox *spinBoxFPLineWidth;
    QLabel *label_17;
    CXButtonColorEdit *colorButtonFPF;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBoxStructure;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    CXButtonColorEdit *colorButton_CapsuleLineColor;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLabel *label_11;
    QSlider *horizontalSlider_Opacity;
    QLabel *label_12;
    QGroupBox *groupBoxAnticline;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    CXButtonColorEdit *colorButton_AnticlineColor;
    QLabel *label_5;
    QSpinBox *spinBox_AnticlineWidth;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *spinBox_AnticlineMarkerSize;
    QLabel *label_7;
    QSpinBox *spinBox_AnticlineArrowSize;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBoxStressStates;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QLabel *label_13;
    QCheckBox *checkBoxTL;
    QSlider *horizontalSlider_StatesOpacity;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *GSBMStressMapVisPage)
    {
        if (GSBMStressMapVisPage->objectName().isEmpty())
            GSBMStressMapVisPage->setObjectName(QString::fromUtf8("GSBMStressMapVisPage"));
        GSBMStressMapVisPage->resize(435, 440);
        verticalLayout_4 = new QVBoxLayout(GSBMStressMapVisPage);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBoxStrressLine = new QGroupBox(GSBMStressMapVisPage);
        groupBoxStrressLine->setObjectName(QString::fromUtf8("groupBoxStrressLine"));
        groupBoxStrressLine->setFlat(true);
        verticalLayout = new QVBoxLayout(groupBoxStrressLine);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBoxStrressLine);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        colorButton_StressLine = new CXButtonColorEdit(groupBoxStrressLine);
        colorButton_StressLine->setObjectName(QString::fromUtf8("colorButton_StressLine"));

        horizontalLayout->addWidget(colorButton_StressLine);

        label_16 = new QLabel(groupBoxStrressLine);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout->addWidget(label_16);

        spinBoxLength = new QSpinBox(groupBoxStrressLine);
        spinBoxLength->setObjectName(QString::fromUtf8("spinBoxLength"));
        spinBoxLength->setMinimum(1);
        spinBoxLength->setMaximum(10);
        spinBoxLength->setValue(4);

        horizontalLayout->addWidget(spinBoxLength);

        label_2 = new QLabel(groupBoxStrressLine);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBox_StressLineWidth = new QSpinBox(groupBoxStrressLine);
        spinBox_StressLineWidth->setObjectName(QString::fromUtf8("spinBox_StressLineWidth"));

        horizontalLayout->addWidget(spinBox_StressLineWidth);

        label_9 = new QLabel(groupBoxStrressLine);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);

        spinBox_StressLineStep = new QSpinBox(groupBoxStrressLine);
        spinBox_StressLineStep->setObjectName(QString::fromUtf8("spinBox_StressLineStep"));

        horizontalLayout->addWidget(spinBox_StressLineStep);

        checkBox = new QCheckBox(groupBoxStrressLine);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBoxStrressLine);

        groupBoxFaultPolygon = new QGroupBox(GSBMStressMapVisPage);
        groupBoxFaultPolygon->setObjectName(QString::fromUtf8("groupBoxFaultPolygon"));
        groupBoxFaultPolygon->setFlat(true);
        groupBoxFaultPolygon->setCheckable(true);
        horizontalLayout_8 = new QHBoxLayout(groupBoxFaultPolygon);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_14 = new QLabel(groupBoxFaultPolygon);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_7->addWidget(label_14);

        colorButtonFPL = new CXButtonColorEdit(groupBoxFaultPolygon);
        colorButtonFPL->setObjectName(QString::fromUtf8("colorButtonFPL"));

        horizontalLayout_7->addWidget(colorButtonFPL);

        label_15 = new QLabel(groupBoxFaultPolygon);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_7->addWidget(label_15);

        spinBoxFPLineWidth = new QSpinBox(groupBoxFaultPolygon);
        spinBoxFPLineWidth->setObjectName(QString::fromUtf8("spinBoxFPLineWidth"));

        horizontalLayout_7->addWidget(spinBoxFPLineWidth);

        label_17 = new QLabel(groupBoxFaultPolygon);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_7->addWidget(label_17);

        colorButtonFPF = new CXButtonColorEdit(groupBoxFaultPolygon);
        colorButtonFPF->setObjectName(QString::fromUtf8("colorButtonFPF"));

        horizontalLayout_7->addWidget(colorButtonFPF);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        horizontalLayout_8->addLayout(horizontalLayout_7);


        verticalLayout_4->addWidget(groupBoxFaultPolygon);

        groupBoxStructure = new QGroupBox(GSBMStressMapVisPage);
        groupBoxStructure->setObjectName(QString::fromUtf8("groupBoxStructure"));
        groupBoxStructure->setFlat(true);
        groupBoxStructure->setCheckable(true);
        verticalLayout_2 = new QVBoxLayout(groupBoxStructure);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(groupBoxStructure);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        colorButton_CapsuleLineColor = new CXButtonColorEdit(groupBoxStructure);
        colorButton_CapsuleLineColor->setObjectName(QString::fromUtf8("colorButton_CapsuleLineColor"));

        horizontalLayout_2->addWidget(colorButton_CapsuleLineColor);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_10 = new QLabel(groupBoxStructure);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);

        label_11 = new QLabel(groupBoxStructure);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_4->addWidget(label_11);

        horizontalSlider_Opacity = new QSlider(groupBoxStructure);
        horizontalSlider_Opacity->setObjectName(QString::fromUtf8("horizontalSlider_Opacity"));
        horizontalSlider_Opacity->setMaximum(10);
        horizontalSlider_Opacity->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider_Opacity);

        label_12 = new QLabel(groupBoxStructure);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_4->addWidget(label_12);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_4->addWidget(groupBoxStructure);

        groupBoxAnticline = new QGroupBox(GSBMStressMapVisPage);
        groupBoxAnticline->setObjectName(QString::fromUtf8("groupBoxAnticline"));
        groupBoxAnticline->setFlat(true);
        groupBoxAnticline->setCheckable(true);
        verticalLayout_3 = new QVBoxLayout(groupBoxAnticline);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(groupBoxAnticline);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        colorButton_AnticlineColor = new CXButtonColorEdit(groupBoxAnticline);
        colorButton_AnticlineColor->setObjectName(QString::fromUtf8("colorButton_AnticlineColor"));

        horizontalLayout_3->addWidget(colorButton_AnticlineColor);

        label_5 = new QLabel(groupBoxAnticline);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        spinBox_AnticlineWidth = new QSpinBox(groupBoxAnticline);
        spinBox_AnticlineWidth->setObjectName(QString::fromUtf8("spinBox_AnticlineWidth"));

        horizontalLayout_3->addWidget(spinBox_AnticlineWidth);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupBoxAnticline);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        spinBox_AnticlineMarkerSize = new QSpinBox(groupBoxAnticline);
        spinBox_AnticlineMarkerSize->setObjectName(QString::fromUtf8("spinBox_AnticlineMarkerSize"));

        horizontalLayout_5->addWidget(spinBox_AnticlineMarkerSize);

        label_7 = new QLabel(groupBoxAnticline);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        spinBox_AnticlineArrowSize = new QSpinBox(groupBoxAnticline);
        spinBox_AnticlineArrowSize->setObjectName(QString::fromUtf8("spinBox_AnticlineArrowSize"));

        horizontalLayout_5->addWidget(spinBox_AnticlineArrowSize);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_4->addWidget(groupBoxAnticline);

        groupBoxStressStates = new QGroupBox(GSBMStressMapVisPage);
        groupBoxStressStates->setObjectName(QString::fromUtf8("groupBoxStressStates"));
        groupBoxStressStates->setFlat(true);
        groupBoxStressStates->setCheckable(true);
        groupBoxStressStates->setChecked(false);
        gridLayout = new QGridLayout(groupBoxStressStates);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_8 = new QLabel(groupBoxStressStates);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 1, 1, 1, 1);

        label_13 = new QLabel(groupBoxStressStates);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 1, 5, 1, 1);

        checkBoxTL = new QCheckBox(groupBoxStressStates);
        checkBoxTL->setObjectName(QString::fromUtf8("checkBoxTL"));

        gridLayout->addWidget(checkBoxTL, 0, 1, 1, 3);

        horizontalSlider_StatesOpacity = new QSlider(groupBoxStressStates);
        horizontalSlider_StatesOpacity->setObjectName(QString::fromUtf8("horizontalSlider_StatesOpacity"));
        horizontalSlider_StatesOpacity->setMaximum(10);
        horizontalSlider_StatesOpacity->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_StatesOpacity, 1, 2, 1, 1);


        verticalLayout_4->addWidget(groupBoxStressStates);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        retranslateUi(GSBMStressMapVisPage);

        QMetaObject::connectSlotsByName(GSBMStressMapVisPage);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *GSBMStressMapVisPage)
    {
        GSBMStressMapVisPage->setWindowTitle(QCoreApplication::translate("GSBMStressMapVisPage", "GSPageBMVisStressMap", nullptr));
        groupBoxStrressLine->setTitle(QCoreApplication::translate("GSBMStressMapVisPage", "Stress Line", nullptr));
        label->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Color:", nullptr));
        colorButton_StressLine->setText(QString());
        label_16->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Length:", nullptr));
        label_2->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Width:", nullptr));
        label_9->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Step:", nullptr));
        checkBox->setText(QCoreApplication::translate("GSBMStressMapVisPage", "All", nullptr));
        groupBoxFaultPolygon->setTitle(QCoreApplication::translate("GSBMStressMapVisPage", "Fault Polygon", nullptr));
        label_14->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Line Color:", nullptr));
        colorButtonFPL->setText(QString());
        label_15->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Width:", nullptr));
        label_17->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Fill Color:", nullptr));
        colorButtonFPF->setText(QString());
        groupBoxStructure->setTitle(QCoreApplication::translate("GSBMStressMapVisPage", "Structure", nullptr));
        label_6->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Line Color:", nullptr));
        colorButton_CapsuleLineColor->setText(QString());
        label_10->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Opacity:", nullptr));
        label_11->setText(QCoreApplication::translate("GSBMStressMapVisPage", "0", nullptr));
        label_12->setText(QCoreApplication::translate("GSBMStressMapVisPage", "1.0", nullptr));
        groupBoxAnticline->setTitle(QCoreApplication::translate("GSBMStressMapVisPage", "Anticline", nullptr));
        label_4->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Color:", nullptr));
        colorButton_AnticlineColor->setText(QString());
        label_5->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Width:", nullptr));
        label_3->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Marker Size:", nullptr));
        label_7->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Stress Arrow Size:", nullptr));
        groupBoxStressStates->setTitle(QCoreApplication::translate("GSBMStressMapVisPage", "Stress states", nullptr));
        label_8->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Opacity: 0", nullptr));
        label_13->setText(QCoreApplication::translate("GSBMStressMapVisPage", "1.0", nullptr));
        checkBoxTL->setText(QCoreApplication::translate("GSBMStressMapVisPage", "Show as traffic light stop-go colour scheme", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSBMStressMapVisPage: public Ui_GSBMStressMapVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSBMSTRESSMAPVISPAGE_H
