/********************************************************************************
** Form generated from reading UI file 'xpageloadsegydatastep4.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGELOADSEGYDATASTEP4_H
#define UI_XPAGELOADSEGYDATASTEP4_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loadsegydatastep4
{
public:
    QGridLayout *gridLayout_7;
    QLabel *label;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QComboBox *m_CmbExistSurvey;
    QRadioButton *m_RdoCreateNew;
    QLineEdit *m_EdtNewSureyName;
    QRadioButton *m_RdoSavetoExist;
    QCheckBox *checkBoxDataLine;
    QGroupBox *m_GrpDataVolume;
    QGridLayout *gridLayout_6;
    QLabel *label_2;
    QLineEdit *m_EdtVolumeName;
    QLabel *label_3;
    QComboBox *m_CmbSeismicAttribute;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_16;
    QLabel *label_21;
    QLineEdit *m_EdtOrgInlineStart;
    QLineEdit *m_EdtOrgInlineEnd;
    QLineEdit *m_EdtOrgInlineStep;
    QLineEdit *m_EdtOrgInlineNumber;
    QLabel *label_22;
    QLineEdit *m_EdtOrgCrossStart;
    QLineEdit *m_EdtOrgCrossEnd;
    QLineEdit *m_EdtOrgCrossStep;
    QLineEdit *m_EdtOrgCrossNumber;
    QLabel *label_24;
    QLineEdit *m_EdtOrgTimeStart;
    QLineEdit *m_EdtOrgTimeEnd;
    QLineEdit *m_EdtOrgTimeStep;
    QLineEdit *m_EdtOrgTimeNumber;
    QGroupBox *m_GrpImpotRange;
    QGridLayout *gridLayout_3;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_13;
    QLabel *label_17;
    QLabel *label_25;
    QLineEdit *m_EdtImpInlineStart;
    QLineEdit *m_EdtImpInlineEnd;
    QComboBox *m_EdtImpInlineStep;
    QLineEdit *m_EdtImpInlineNumber;
    QLabel *label_27;
    QLineEdit *m_EdtImpCrossStart;
    QLineEdit *m_EdtImpCrossEnd;
    QComboBox *m_EdtImpCrossStep;
    QLineEdit *m_EdtImpCrossNumber;
    QLabel *label_28;
    QLineEdit *m_EdtImpTimeStart;
    QLineEdit *m_EdtImpTimeEnd;
    QComboBox *m_EdtImpTimeStep;
    QLineEdit *m_EdtImpTimeNumber;
    QGroupBox *m_GrpDomain;
    QGridLayout *gridLayout_4;
    QRadioButton *m_RdoTime;
    QComboBox *m_CmbDomainUnit;
    QRadioButton *m_RdoDepth;
    QLabel *m_Lblunit;
    QSpacerItem *verticalSpacer_2;
    QFrame *line_2;
    QLineEdit *m_EdtStartTimeToValue;
    QCheckBox *m_ChkShiftStartTime;
    QGroupBox *m_GrpOutputOptions;
    QGridLayout *gridLayout_5;
    QCheckBox *m_ChkCreateSliceFile;
    QCheckBox *m_ChkCreateBrickFile;
    QLabel *label_8;
    QLabel *m_LblDiskSpaceAva;
    QLabel *label_9;
    QLabel *m_DiskSpaceRep;
    QSpacerItem *verticalSpacer;
    QToolButton *m_pHelpGTCVolume;
    QToolButton *m_pHelpGTCVolume_2;

    void setupUi(QWidget *loadsegydatastep4)
    {
        if (loadsegydatastep4->objectName().isEmpty())
            loadsegydatastep4->setObjectName(QString::fromUtf8("loadsegydatastep4"));
        loadsegydatastep4->resize(614, 585);
        gridLayout_7 = new QGridLayout(loadsegydatastep4);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label = new QLabel(loadsegydatastep4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_7->addWidget(label, 0, 0, 1, 2);

        groupBox = new QGroupBox(loadsegydatastep4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_CmbExistSurvey = new QComboBox(groupBox);
        m_CmbExistSurvey->setObjectName(QString::fromUtf8("m_CmbExistSurvey"));

        gridLayout->addWidget(m_CmbExistSurvey, 1, 1, 1, 1);

        m_RdoCreateNew = new QRadioButton(groupBox);
        m_RdoCreateNew->setObjectName(QString::fromUtf8("m_RdoCreateNew"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_RdoCreateNew->sizePolicy().hasHeightForWidth());
        m_RdoCreateNew->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_RdoCreateNew, 0, 0, 1, 1);

        m_EdtNewSureyName = new QLineEdit(groupBox);
        m_EdtNewSureyName->setObjectName(QString::fromUtf8("m_EdtNewSureyName"));

        gridLayout->addWidget(m_EdtNewSureyName, 0, 1, 1, 1);

        m_RdoSavetoExist = new QRadioButton(groupBox);
        m_RdoSavetoExist->setObjectName(QString::fromUtf8("m_RdoSavetoExist"));
        sizePolicy.setHeightForWidth(m_RdoSavetoExist->sizePolicy().hasHeightForWidth());
        m_RdoSavetoExist->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_RdoSavetoExist, 1, 0, 1, 1);

        checkBoxDataLine = new QCheckBox(groupBox);
        checkBoxDataLine->setObjectName(QString::fromUtf8("checkBoxDataLine"));
        checkBoxDataLine->setEnabled(false);

        gridLayout->addWidget(checkBoxDataLine, 2, 0, 1, 1);


        gridLayout_7->addWidget(groupBox, 3, 0, 2, 3);

        m_GrpDataVolume = new QGroupBox(loadsegydatastep4);
        m_GrpDataVolume->setObjectName(QString::fromUtf8("m_GrpDataVolume"));
        gridLayout_6 = new QGridLayout(m_GrpDataVolume);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_2 = new QLabel(m_GrpDataVolume);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setLayoutDirection(Qt::RightToLeft);

        gridLayout_6->addWidget(label_2, 0, 0, 1, 1);

        m_EdtVolumeName = new QLineEdit(m_GrpDataVolume);
        m_EdtVolumeName->setObjectName(QString::fromUtf8("m_EdtVolumeName"));

        gridLayout_6->addWidget(m_EdtVolumeName, 0, 1, 1, 1);

        label_3 = new QLabel(m_GrpDataVolume);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_6->addWidget(label_3, 1, 0, 1, 1);

        m_CmbSeismicAttribute = new QComboBox(m_GrpDataVolume);
        m_CmbSeismicAttribute->setObjectName(QString::fromUtf8("m_CmbSeismicAttribute"));

        gridLayout_6->addWidget(m_CmbSeismicAttribute, 1, 1, 1, 1);


        gridLayout_7->addWidget(m_GrpDataVolume, 5, 0, 1, 3);

        groupBox_2 = new QGroupBox(loadsegydatastep4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(label_10, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 0, 2, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 0, 3, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 0, 4, 1, 1);

        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 1, 0, 1, 1);

        m_EdtOrgInlineStart = new QLineEdit(groupBox_2);
        m_EdtOrgInlineStart->setObjectName(QString::fromUtf8("m_EdtOrgInlineStart"));
        m_EdtOrgInlineStart->setEnabled(true);
        m_EdtOrgInlineStart->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgInlineStart, 1, 1, 1, 1);

        m_EdtOrgInlineEnd = new QLineEdit(groupBox_2);
        m_EdtOrgInlineEnd->setObjectName(QString::fromUtf8("m_EdtOrgInlineEnd"));
        m_EdtOrgInlineEnd->setEnabled(true);
        m_EdtOrgInlineEnd->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgInlineEnd, 1, 2, 1, 1);

        m_EdtOrgInlineStep = new QLineEdit(groupBox_2);
        m_EdtOrgInlineStep->setObjectName(QString::fromUtf8("m_EdtOrgInlineStep"));
        m_EdtOrgInlineStep->setEnabled(true);
        m_EdtOrgInlineStep->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgInlineStep, 1, 3, 1, 1);

        m_EdtOrgInlineNumber = new QLineEdit(groupBox_2);
        m_EdtOrgInlineNumber->setObjectName(QString::fromUtf8("m_EdtOrgInlineNumber"));
        m_EdtOrgInlineNumber->setEnabled(true);
        m_EdtOrgInlineNumber->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgInlineNumber, 1, 4, 1, 1);

        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_2->addWidget(label_22, 2, 0, 1, 1);

        m_EdtOrgCrossStart = new QLineEdit(groupBox_2);
        m_EdtOrgCrossStart->setObjectName(QString::fromUtf8("m_EdtOrgCrossStart"));
        m_EdtOrgCrossStart->setEnabled(true);
        m_EdtOrgCrossStart->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgCrossStart, 2, 1, 1, 1);

        m_EdtOrgCrossEnd = new QLineEdit(groupBox_2);
        m_EdtOrgCrossEnd->setObjectName(QString::fromUtf8("m_EdtOrgCrossEnd"));
        m_EdtOrgCrossEnd->setEnabled(true);
        m_EdtOrgCrossEnd->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgCrossEnd, 2, 2, 1, 1);

        m_EdtOrgCrossStep = new QLineEdit(groupBox_2);
        m_EdtOrgCrossStep->setObjectName(QString::fromUtf8("m_EdtOrgCrossStep"));
        m_EdtOrgCrossStep->setEnabled(true);
        m_EdtOrgCrossStep->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgCrossStep, 2, 3, 1, 1);

        m_EdtOrgCrossNumber = new QLineEdit(groupBox_2);
        m_EdtOrgCrossNumber->setObjectName(QString::fromUtf8("m_EdtOrgCrossNumber"));
        m_EdtOrgCrossNumber->setEnabled(true);
        m_EdtOrgCrossNumber->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgCrossNumber, 2, 4, 1, 1);

        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_2->addWidget(label_24, 3, 0, 1, 1);

        m_EdtOrgTimeStart = new QLineEdit(groupBox_2);
        m_EdtOrgTimeStart->setObjectName(QString::fromUtf8("m_EdtOrgTimeStart"));
        m_EdtOrgTimeStart->setEnabled(true);
        m_EdtOrgTimeStart->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgTimeStart, 3, 1, 1, 1);

        m_EdtOrgTimeEnd = new QLineEdit(groupBox_2);
        m_EdtOrgTimeEnd->setObjectName(QString::fromUtf8("m_EdtOrgTimeEnd"));
        m_EdtOrgTimeEnd->setEnabled(true);
        m_EdtOrgTimeEnd->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgTimeEnd, 3, 2, 1, 1);

        m_EdtOrgTimeStep = new QLineEdit(groupBox_2);
        m_EdtOrgTimeStep->setObjectName(QString::fromUtf8("m_EdtOrgTimeStep"));
        m_EdtOrgTimeStep->setEnabled(true);
        m_EdtOrgTimeStep->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgTimeStep, 3, 3, 1, 1);

        m_EdtOrgTimeNumber = new QLineEdit(groupBox_2);
        m_EdtOrgTimeNumber->setObjectName(QString::fromUtf8("m_EdtOrgTimeNumber"));
        m_EdtOrgTimeNumber->setEnabled(true);
        m_EdtOrgTimeNumber->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtOrgTimeNumber, 3, 4, 1, 1);


        gridLayout_7->addWidget(groupBox_2, 6, 0, 3, 3);

        m_GrpImpotRange = new QGroupBox(loadsegydatastep4);
        m_GrpImpotRange->setObjectName(QString::fromUtf8("m_GrpImpotRange"));
        gridLayout_3 = new QGridLayout(m_GrpImpotRange);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_14 = new QLabel(m_GrpImpotRange);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy2.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_14, 0, 1, 1, 1);

        label_15 = new QLabel(m_GrpImpotRange);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 0, 2, 1, 1);

        label_13 = new QLabel(m_GrpImpotRange);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_3->addWidget(label_13, 0, 3, 1, 1);

        label_17 = new QLabel(m_GrpImpotRange);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_3->addWidget(label_17, 0, 4, 1, 1);

        label_25 = new QLabel(m_GrpImpotRange);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_3->addWidget(label_25, 1, 0, 1, 1);

        m_EdtImpInlineStart = new QLineEdit(m_GrpImpotRange);
        m_EdtImpInlineStart->setObjectName(QString::fromUtf8("m_EdtImpInlineStart"));

        gridLayout_3->addWidget(m_EdtImpInlineStart, 1, 1, 1, 1);

        m_EdtImpInlineEnd = new QLineEdit(m_GrpImpotRange);
        m_EdtImpInlineEnd->setObjectName(QString::fromUtf8("m_EdtImpInlineEnd"));

        gridLayout_3->addWidget(m_EdtImpInlineEnd, 1, 2, 1, 1);

        m_EdtImpInlineStep = new QComboBox(m_GrpImpotRange);
        m_EdtImpInlineStep->setObjectName(QString::fromUtf8("m_EdtImpInlineStep"));

        gridLayout_3->addWidget(m_EdtImpInlineStep, 1, 3, 1, 1);

        m_EdtImpInlineNumber = new QLineEdit(m_GrpImpotRange);
        m_EdtImpInlineNumber->setObjectName(QString::fromUtf8("m_EdtImpInlineNumber"));
        m_EdtImpInlineNumber->setReadOnly(true);

        gridLayout_3->addWidget(m_EdtImpInlineNumber, 1, 4, 1, 1);

        label_27 = new QLabel(m_GrpImpotRange);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_3->addWidget(label_27, 2, 0, 1, 1);

        m_EdtImpCrossStart = new QLineEdit(m_GrpImpotRange);
        m_EdtImpCrossStart->setObjectName(QString::fromUtf8("m_EdtImpCrossStart"));

        gridLayout_3->addWidget(m_EdtImpCrossStart, 2, 1, 1, 1);

        m_EdtImpCrossEnd = new QLineEdit(m_GrpImpotRange);
        m_EdtImpCrossEnd->setObjectName(QString::fromUtf8("m_EdtImpCrossEnd"));

        gridLayout_3->addWidget(m_EdtImpCrossEnd, 2, 2, 1, 1);

        m_EdtImpCrossStep = new QComboBox(m_GrpImpotRange);
        m_EdtImpCrossStep->setObjectName(QString::fromUtf8("m_EdtImpCrossStep"));

        gridLayout_3->addWidget(m_EdtImpCrossStep, 2, 3, 1, 1);

        m_EdtImpCrossNumber = new QLineEdit(m_GrpImpotRange);
        m_EdtImpCrossNumber->setObjectName(QString::fromUtf8("m_EdtImpCrossNumber"));
        m_EdtImpCrossNumber->setReadOnly(true);

        gridLayout_3->addWidget(m_EdtImpCrossNumber, 2, 4, 1, 1);

        label_28 = new QLabel(m_GrpImpotRange);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_3->addWidget(label_28, 3, 0, 1, 1);

        m_EdtImpTimeStart = new QLineEdit(m_GrpImpotRange);
        m_EdtImpTimeStart->setObjectName(QString::fromUtf8("m_EdtImpTimeStart"));

        gridLayout_3->addWidget(m_EdtImpTimeStart, 3, 1, 1, 1);

        m_EdtImpTimeEnd = new QLineEdit(m_GrpImpotRange);
        m_EdtImpTimeEnd->setObjectName(QString::fromUtf8("m_EdtImpTimeEnd"));

        gridLayout_3->addWidget(m_EdtImpTimeEnd, 3, 2, 1, 1);

        m_EdtImpTimeStep = new QComboBox(m_GrpImpotRange);
        m_EdtImpTimeStep->setObjectName(QString::fromUtf8("m_EdtImpTimeStep"));

        gridLayout_3->addWidget(m_EdtImpTimeStep, 3, 3, 1, 1);

        m_EdtImpTimeNumber = new QLineEdit(m_GrpImpotRange);
        m_EdtImpTimeNumber->setObjectName(QString::fromUtf8("m_EdtImpTimeNumber"));
        m_EdtImpTimeNumber->setReadOnly(true);

        gridLayout_3->addWidget(m_EdtImpTimeNumber, 3, 4, 1, 1);


        gridLayout_7->addWidget(m_GrpImpotRange, 9, 0, 1, 3);

        m_GrpDomain = new QGroupBox(loadsegydatastep4);
        m_GrpDomain->setObjectName(QString::fromUtf8("m_GrpDomain"));
        gridLayout_4 = new QGridLayout(m_GrpDomain);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_RdoTime = new QRadioButton(m_GrpDomain);
        m_RdoTime->setObjectName(QString::fromUtf8("m_RdoTime"));
        m_RdoTime->setEnabled(true);
        m_RdoTime->setChecked(true);

        gridLayout_4->addWidget(m_RdoTime, 0, 0, 1, 2);

        m_CmbDomainUnit = new QComboBox(m_GrpDomain);
        m_CmbDomainUnit->addItem(QString());
        m_CmbDomainUnit->setObjectName(QString::fromUtf8("m_CmbDomainUnit"));

        gridLayout_4->addWidget(m_CmbDomainUnit, 1, 1, 1, 3);

        m_RdoDepth = new QRadioButton(m_GrpDomain);
        m_RdoDepth->setObjectName(QString::fromUtf8("m_RdoDepth"));
        m_RdoDepth->setEnabled(true);

        gridLayout_4->addWidget(m_RdoDepth, 0, 2, 1, 2);

        m_Lblunit = new QLabel(m_GrpDomain);
        m_Lblunit->setObjectName(QString::fromUtf8("m_Lblunit"));

        gridLayout_4->addWidget(m_Lblunit, 1, 0, 1, 1);


        gridLayout_7->addWidget(m_GrpDomain, 3, 3, 2, 3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_2, 10, 2, 1, 1);

        line_2 = new QFrame(loadsegydatastep4);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_2, 1, 0, 1, 6);

        m_EdtStartTimeToValue = new QLineEdit(loadsegydatastep4);
        m_EdtStartTimeToValue->setObjectName(QString::fromUtf8("m_EdtStartTimeToValue"));
        m_EdtStartTimeToValue->setEnabled(false);

        gridLayout_7->addWidget(m_EdtStartTimeToValue, 5, 4, 1, 1);

        m_ChkShiftStartTime = new QCheckBox(loadsegydatastep4);
        m_ChkShiftStartTime->setObjectName(QString::fromUtf8("m_ChkShiftStartTime"));

        gridLayout_7->addWidget(m_ChkShiftStartTime, 5, 3, 1, 1);

        m_GrpOutputOptions = new QGroupBox(loadsegydatastep4);
        m_GrpOutputOptions->setObjectName(QString::fromUtf8("m_GrpOutputOptions"));
        gridLayout_5 = new QGridLayout(m_GrpOutputOptions);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_ChkCreateSliceFile = new QCheckBox(m_GrpOutputOptions);
        m_ChkCreateSliceFile->setObjectName(QString::fromUtf8("m_ChkCreateSliceFile"));
        m_ChkCreateSliceFile->setChecked(false);

        gridLayout_5->addWidget(m_ChkCreateSliceFile, 0, 0, 1, 1);

        m_ChkCreateBrickFile = new QCheckBox(m_GrpOutputOptions);
        m_ChkCreateBrickFile->setObjectName(QString::fromUtf8("m_ChkCreateBrickFile"));
        m_ChkCreateBrickFile->setChecked(false);

        gridLayout_5->addWidget(m_ChkCreateBrickFile, 1, 0, 1, 1);

        label_8 = new QLabel(m_GrpOutputOptions);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 2, 0, 1, 1);

        m_LblDiskSpaceAva = new QLabel(m_GrpOutputOptions);
        m_LblDiskSpaceAva->setObjectName(QString::fromUtf8("m_LblDiskSpaceAva"));

        gridLayout_5->addWidget(m_LblDiskSpaceAva, 2, 1, 1, 1);

        label_9 = new QLabel(m_GrpOutputOptions);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 3, 0, 1, 1);

        m_DiskSpaceRep = new QLabel(m_GrpOutputOptions);
        m_DiskSpaceRep->setObjectName(QString::fromUtf8("m_DiskSpaceRep"));

        gridLayout_5->addWidget(m_DiskSpaceRep, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 4, 0, 1, 1);

        m_pHelpGTCVolume = new QToolButton(m_GrpOutputOptions);
        m_pHelpGTCVolume->setObjectName(QString::fromUtf8("m_pHelpGTCVolume"));

        gridLayout_5->addWidget(m_pHelpGTCVolume, 1, 1, 1, 1);

        m_pHelpGTCVolume_2 = new QToolButton(m_GrpOutputOptions);
        m_pHelpGTCVolume_2->setObjectName(QString::fromUtf8("m_pHelpGTCVolume_2"));

        gridLayout_5->addWidget(m_pHelpGTCVolume_2, 0, 1, 1, 1);


        gridLayout_7->addWidget(m_GrpOutputOptions, 6, 3, 1, 2);


        retranslateUi(loadsegydatastep4);
        QObject::connect(m_RdoCreateNew, SIGNAL(toggled(bool)), m_EdtNewSureyName, SLOT(setEnabled(bool)));
        QObject::connect(m_RdoSavetoExist, SIGNAL(toggled(bool)), m_CmbExistSurvey, SLOT(setEnabled(bool)));
        QObject::connect(m_RdoSavetoExist, SIGNAL(toggled(bool)), checkBoxDataLine, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxDataLine, SIGNAL(toggled(bool)), m_ChkCreateBrickFile, SLOT(setDisabled(bool)));
        QObject::connect(checkBoxDataLine, SIGNAL(toggled(bool)), m_ChkCreateSliceFile, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(loadsegydatastep4);
    } // setupUi

    void retranslateUi(QWidget *loadsegydatastep4)
    {
        loadsegydatastep4->setWindowTitle(QCoreApplication::translate("loadsegydatastep4", "Form", nullptr));
        label->setText(QCoreApplication::translate("loadsegydatastep4", "Step 4 of 4: Output Parameters", nullptr));
        groupBox->setTitle(QCoreApplication::translate("loadsegydatastep4", "Survey", nullptr));
        m_RdoCreateNew->setText(QCoreApplication::translate("loadsegydatastep4", "Create New Survey", nullptr));
        m_RdoSavetoExist->setText(QCoreApplication::translate("loadsegydatastep4", "Save to Existing Survey", nullptr));
        checkBoxDataLine->setText(QCoreApplication::translate("loadsegydatastep4", "Import this one line as seismic data line.", nullptr));
        m_GrpDataVolume->setTitle(QCoreApplication::translate("loadsegydatastep4", "Data Volume", nullptr));
        label_2->setText(QCoreApplication::translate("loadsegydatastep4", "Name:", nullptr));
        m_EdtVolumeName->setText(QString());
        label_3->setText(QCoreApplication::translate("loadsegydatastep4", "Seismic Attribute:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("loadsegydatastep4", "Original Range", nullptr));
        label_10->setText(QCoreApplication::translate("loadsegydatastep4", "Start", nullptr));
        label_11->setText(QCoreApplication::translate("loadsegydatastep4", "End", nullptr));
        label_12->setText(QCoreApplication::translate("loadsegydatastep4", "Step", nullptr));
        label_16->setText(QCoreApplication::translate("loadsegydatastep4", "Number", nullptr));
        label_21->setText(QCoreApplication::translate("loadsegydatastep4", "Inline:", nullptr));
        m_EdtOrgInlineStart->setText(QString());
        m_EdtOrgInlineEnd->setText(QString());
        m_EdtOrgInlineStep->setText(QString());
        m_EdtOrgInlineNumber->setText(QString());
        label_22->setText(QCoreApplication::translate("loadsegydatastep4", "Crossline:", nullptr));
        m_EdtOrgCrossStart->setText(QString());
        m_EdtOrgCrossEnd->setText(QString());
        m_EdtOrgCrossStep->setText(QString());
        m_EdtOrgCrossNumber->setText(QString());
        label_24->setText(QCoreApplication::translate("loadsegydatastep4", "Time(ms):", nullptr));
        m_EdtOrgTimeStart->setText(QString());
        m_EdtOrgTimeEnd->setText(QString());
        m_EdtOrgTimeStep->setText(QString());
        m_EdtOrgTimeNumber->setText(QString());
        m_GrpImpotRange->setTitle(QCoreApplication::translate("loadsegydatastep4", "Import Range", nullptr));
        label_14->setText(QCoreApplication::translate("loadsegydatastep4", "Start", nullptr));
        label_15->setText(QCoreApplication::translate("loadsegydatastep4", "End", nullptr));
        label_13->setText(QCoreApplication::translate("loadsegydatastep4", "Step", nullptr));
        label_17->setText(QCoreApplication::translate("loadsegydatastep4", "Number", nullptr));
        label_25->setText(QCoreApplication::translate("loadsegydatastep4", "Inline:", nullptr));
        m_EdtImpInlineStart->setText(QString());
        m_EdtImpInlineEnd->setText(QString());
        m_EdtImpInlineNumber->setText(QString());
        label_27->setText(QCoreApplication::translate("loadsegydatastep4", "Crossline:", nullptr));
        m_EdtImpCrossStart->setText(QString());
        m_EdtImpCrossEnd->setText(QString());
        m_EdtImpCrossNumber->setText(QString());
        label_28->setText(QCoreApplication::translate("loadsegydatastep4", "Time(ms):", nullptr));
        m_EdtImpTimeStart->setText(QString());
        m_EdtImpTimeEnd->setText(QString());
        m_EdtImpTimeNumber->setText(QString());
        m_GrpDomain->setTitle(QCoreApplication::translate("loadsegydatastep4", "Domain Type", nullptr));
        m_RdoTime->setText(QCoreApplication::translate("loadsegydatastep4", "Time", nullptr));
        m_CmbDomainUnit->setItemText(0, QCoreApplication::translate("loadsegydatastep4", "ms", nullptr));

        m_RdoDepth->setText(QCoreApplication::translate("loadsegydatastep4", "Depth", nullptr));
        m_Lblunit->setText(QCoreApplication::translate("loadsegydatastep4", "Unit:", nullptr));
        m_EdtStartTimeToValue->setText(QString());
        m_ChkShiftStartTime->setText(QCoreApplication::translate("loadsegydatastep4", "Shift Start Time to (ms):", nullptr));
        m_GrpOutputOptions->setTitle(QCoreApplication::translate("loadsegydatastep4", "Output Options", nullptr));
        m_ChkCreateSliceFile->setText(QCoreApplication::translate("loadsegydatastep4", "Generate Slice File", nullptr));
        m_ChkCreateBrickFile->setText(QCoreApplication::translate("loadsegydatastep4", "Generate Brick File", nullptr));
        label_8->setText(QCoreApplication::translate("loadsegydatastep4", "Disk Space Available:", nullptr));
        m_LblDiskSpaceAva->setText(QCoreApplication::translate("loadsegydatastep4", "TextLabel", nullptr));
        label_9->setText(QCoreApplication::translate("loadsegydatastep4", "Disk Space Required:", nullptr));
        m_DiskSpaceRep->setText(QCoreApplication::translate("loadsegydatastep4", "TextLabel", nullptr));
#if QT_CONFIG(tooltip)
        m_pHelpGTCVolume->setToolTip(QCoreApplication::translate("loadsegydatastep4", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">If you choose not creating GTC volume file now, you can create the volume file through the right-button menu command in the data manager.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        m_pHelpGTCVolume->setText(QCoreApplication::translate("loadsegydatastep4", "?", nullptr));
#if QT_CONFIG(tooltip)
        m_pHelpGTCVolume_2->setToolTip(QCoreApplication::translate("loadsegydatastep4", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">A slice file is required to visualize time or depth slices on the base map and 3-D windows. If you choose not creating slice file now, you can create the slice file through a right-button menu command in the data manager or you will be asked to create one the first time you try to visualize the slice file on the base map or in 3-D windows.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        m_pHelpGTCVolume_2->setText(QCoreApplication::translate("loadsegydatastep4", "?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loadsegydatastep4: public Ui_loadsegydatastep4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGELOADSEGYDATASTEP4_H
