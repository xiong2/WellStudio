/********************************************************************************
** Form generated from reading UI file 'xpagebm3dsurvey.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEBM3DSURVEY_H
#define UI_XPAGEBM3DSURVEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageBM3DSurvey
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    CXButtonColorEdit *m_colorBtnBoundaryLine;
    QLabel *label_6;
    QSpinBox *m_spinBoxBoundaryLineWidth;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QFrame *line_2;
    QGridLayout *gridLayout;
    QCheckBox *m_cbSeismicLineVisible;
    QLabel *label_7;
    QSpinBox *m_spinBoxSeismicLineWidth;
    QLabel *label_8;
    CXButtonColorEdit *m_colorBtnSeismicLine;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QFrame *line_3;
    QGridLayout *gridLayout_2;
    QCheckBox *m_cbTracePointVisible;
    QComboBox *m_cbbTracePointSymbol;
    QLabel *label_9;
    CXButtonColorEdit *m_colorBtnTracePoint;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QFrame *line_4;
    QGridLayout *gridLayout_3;
    QLabel *label_12;
    CXButtonColorEdit *m_colorBtnTickMarks;
    QLabel *label_11;
    QCheckBox *m_cbTickMarksVisible;
    QLabel *label_15;
    QCheckBox *m_cbXlineOnBegin;
    QCheckBox *m_cbXlineOnEnd;
    QCheckBox *m_cbInlineOnEnd;
    QSpinBox *m_spinBoxFontSizeTickMarks;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *m_cbbFontTickMarks;
    QLabel *label_13;
    QCheckBox *m_cbInlineOnBegin;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_16;
    QFrame *line_5;
    QGridLayout *gridLayout_4;
    QSpinBox *m_spinBoxSurveyName;
    CXButtonColorEdit *m_colorBtnSurveyName;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *m_cbSurveyNameVisible;
    QLabel *label_17;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_10;
    QComboBox *m_cbbFontSurveyName;
    QLabel *label_19;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPageBM3DSurvey)
    {
        if (CXPageBM3DSurvey->objectName().isEmpty())
            CXPageBM3DSurvey->setObjectName(QString::fromUtf8("CXPageBM3DSurvey"));
        CXPageBM3DSurvey->resize(500, 451);
        verticalLayout = new QVBoxLayout(CXPageBM3DSurvey);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXPageBM3DSurvey);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout->addWidget(label);

        line = new QFrame(CXPageBM3DSurvey);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        label_5 = new QLabel(CXPageBM3DSurvey);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_5);

        m_colorBtnBoundaryLine = new CXButtonColorEdit(CXPageBM3DSurvey);
        m_colorBtnBoundaryLine->setObjectName(QString::fromUtf8("m_colorBtnBoundaryLine"));

        horizontalLayout_5->addWidget(m_colorBtnBoundaryLine);

        label_6 = new QLabel(CXPageBM3DSurvey);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        m_spinBoxBoundaryLineWidth = new QSpinBox(CXPageBM3DSurvey);
        m_spinBoxBoundaryLineWidth->setObjectName(QString::fromUtf8("m_spinBoxBoundaryLineWidth"));
        m_spinBoxBoundaryLineWidth->setMinimum(1);

        horizontalLayout_5->addWidget(m_spinBoxBoundaryLineWidth);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(CXPageBM3DSurvey);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout_2->addWidget(label_2);

        line_2 = new QFrame(CXPageBM3DSurvey);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_cbSeismicLineVisible = new QCheckBox(CXPageBM3DSurvey);
        m_cbSeismicLineVisible->setObjectName(QString::fromUtf8("m_cbSeismicLineVisible"));

        gridLayout->addWidget(m_cbSeismicLineVisible, 0, 1, 1, 2);

        label_7 = new QLabel(CXPageBM3DSurvey);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 3, 1, 1);

        m_spinBoxSeismicLineWidth = new QSpinBox(CXPageBM3DSurvey);
        m_spinBoxSeismicLineWidth->setObjectName(QString::fromUtf8("m_spinBoxSeismicLineWidth"));
        m_spinBoxSeismicLineWidth->setEnabled(false);
        m_spinBoxSeismicLineWidth->setMinimum(1);

        gridLayout->addWidget(m_spinBoxSeismicLineWidth, 1, 4, 1, 1);

        label_8 = new QLabel(CXPageBM3DSurvey);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_8, 1, 1, 1, 1);

        m_colorBtnSeismicLine = new CXButtonColorEdit(CXPageBM3DSurvey);
        m_colorBtnSeismicLine->setObjectName(QString::fromUtf8("m_colorBtnSeismicLine"));
        m_colorBtnSeismicLine->setEnabled(false);

        gridLayout->addWidget(m_colorBtnSeismicLine, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 5, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(CXPageBM3DSurvey);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout_3->addWidget(label_3);

        line_3 = new QFrame(CXPageBM3DSurvey);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_3);


        verticalLayout->addLayout(horizontalLayout_3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_cbTracePointVisible = new QCheckBox(CXPageBM3DSurvey);
        m_cbTracePointVisible->setObjectName(QString::fromUtf8("m_cbTracePointVisible"));

        gridLayout_2->addWidget(m_cbTracePointVisible, 0, 1, 1, 2);

        m_cbbTracePointSymbol = new QComboBox(CXPageBM3DSurvey);
        m_cbbTracePointSymbol->addItem(QString());
        m_cbbTracePointSymbol->addItem(QString());
        m_cbbTracePointSymbol->addItem(QString());
        m_cbbTracePointSymbol->setObjectName(QString::fromUtf8("m_cbbTracePointSymbol"));
        m_cbbTracePointSymbol->setEnabled(false);

        gridLayout_2->addWidget(m_cbbTracePointSymbol, 1, 4, 1, 1);

        label_9 = new QLabel(CXPageBM3DSurvey);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_9, 1, 1, 1, 1);

        m_colorBtnTracePoint = new CXButtonColorEdit(CXPageBM3DSurvey);
        m_colorBtnTracePoint->setObjectName(QString::fromUtf8("m_colorBtnTracePoint"));
        m_colorBtnTracePoint->setEnabled(false);

        gridLayout_2->addWidget(m_colorBtnTracePoint, 1, 2, 1, 1);

        label_10 = new QLabel(CXPageBM3DSurvey);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 1, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(CXPageBM3DSurvey);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout_4->addWidget(label_4);

        line_4 = new QFrame(CXPageBM3DSurvey);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_4);


        verticalLayout->addLayout(horizontalLayout_4);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_12 = new QLabel(CXPageBM3DSurvey);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 1, 3, 1, 1);

        m_colorBtnTickMarks = new CXButtonColorEdit(CXPageBM3DSurvey);
        m_colorBtnTickMarks->setObjectName(QString::fromUtf8("m_colorBtnTickMarks"));
        m_colorBtnTickMarks->setEnabled(false);

        gridLayout_3->addWidget(m_colorBtnTickMarks, 1, 2, 1, 1);

        label_11 = new QLabel(CXPageBM3DSurvey);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label_11, 1, 1, 1, 1);

        m_cbTickMarksVisible = new QCheckBox(CXPageBM3DSurvey);
        m_cbTickMarksVisible->setObjectName(QString::fromUtf8("m_cbTickMarksVisible"));

        gridLayout_3->addWidget(m_cbTickMarksVisible, 0, 1, 1, 2);

        label_15 = new QLabel(CXPageBM3DSurvey);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 3, 1, 1, 4);

        m_cbXlineOnBegin = new QCheckBox(CXPageBM3DSurvey);
        m_cbXlineOnBegin->setObjectName(QString::fromUtf8("m_cbXlineOnBegin"));
        m_cbXlineOnBegin->setEnabled(false);

        gridLayout_3->addWidget(m_cbXlineOnBegin, 3, 5, 1, 1);

        m_cbXlineOnEnd = new QCheckBox(CXPageBM3DSurvey);
        m_cbXlineOnEnd->setObjectName(QString::fromUtf8("m_cbXlineOnEnd"));
        m_cbXlineOnEnd->setEnabled(false);

        gridLayout_3->addWidget(m_cbXlineOnEnd, 3, 6, 1, 1);

        m_cbInlineOnEnd = new QCheckBox(CXPageBM3DSurvey);
        m_cbInlineOnEnd->setObjectName(QString::fromUtf8("m_cbInlineOnEnd"));
        m_cbInlineOnEnd->setEnabled(false);

        gridLayout_3->addWidget(m_cbInlineOnEnd, 2, 6, 1, 1);

        m_spinBoxFontSizeTickMarks = new QSpinBox(CXPageBM3DSurvey);
        m_spinBoxFontSizeTickMarks->setObjectName(QString::fromUtf8("m_spinBoxFontSizeTickMarks"));
        m_spinBoxFontSizeTickMarks->setEnabled(false);
        m_spinBoxFontSizeTickMarks->setMinimum(1);
        m_spinBoxFontSizeTickMarks->setMaximum(12);

        gridLayout_3->addWidget(m_spinBoxFontSizeTickMarks, 1, 6, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 0, 0, 1, 1);

        m_cbbFontTickMarks = new QComboBox(CXPageBM3DSurvey);
        m_cbbFontTickMarks->addItem(QString());
        m_cbbFontTickMarks->addItem(QString());
        m_cbbFontTickMarks->addItem(QString());
        m_cbbFontTickMarks->addItem(QString());
        m_cbbFontTickMarks->addItem(QString());
        m_cbbFontTickMarks->addItem(QString());
        m_cbbFontTickMarks->setObjectName(QString::fromUtf8("m_cbbFontTickMarks"));
        m_cbbFontTickMarks->setEnabled(false);

        gridLayout_3->addWidget(m_cbbFontTickMarks, 1, 4, 1, 1);

        label_13 = new QLabel(CXPageBM3DSurvey);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_3->addWidget(label_13, 1, 5, 1, 1);

        m_cbInlineOnBegin = new QCheckBox(CXPageBM3DSurvey);
        m_cbInlineOnBegin->setObjectName(QString::fromUtf8("m_cbInlineOnBegin"));
        m_cbInlineOnBegin->setEnabled(false);

        gridLayout_3->addWidget(m_cbInlineOnBegin, 2, 5, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 0, 7, 1, 1);

        label_14 = new QLabel(CXPageBM3DSurvey);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_3->addWidget(label_14, 2, 1, 1, 4);


        verticalLayout->addLayout(gridLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_16 = new QLabel(CXPageBM3DSurvey);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout_6->addWidget(label_16);

        line_5 = new QFrame(CXPageBM3DSurvey);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_5);


        verticalLayout->addLayout(horizontalLayout_6);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_spinBoxSurveyName = new QSpinBox(CXPageBM3DSurvey);
        m_spinBoxSurveyName->setObjectName(QString::fromUtf8("m_spinBoxSurveyName"));
        m_spinBoxSurveyName->setEnabled(false);
        m_spinBoxSurveyName->setMinimum(1);

        gridLayout_4->addWidget(m_spinBoxSurveyName, 1, 6, 1, 1);

        m_colorBtnSurveyName = new CXButtonColorEdit(CXPageBM3DSurvey);
        m_colorBtnSurveyName->setObjectName(QString::fromUtf8("m_colorBtnSurveyName"));
        m_colorBtnSurveyName->setEnabled(false);

        gridLayout_4->addWidget(m_colorBtnSurveyName, 1, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_9, 1, 7, 1, 1);

        m_cbSurveyNameVisible = new QCheckBox(CXPageBM3DSurvey);
        m_cbSurveyNameVisible->setObjectName(QString::fromUtf8("m_cbSurveyNameVisible"));

        gridLayout_4->addWidget(m_cbSurveyNameVisible, 0, 1, 1, 2);

        label_17 = new QLabel(CXPageBM3DSurvey);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_4->addWidget(label_17, 1, 5, 1, 1);

        label_18 = new QLabel(CXPageBM3DSurvey);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(label_18, 1, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_10, 0, 0, 1, 1);

        m_cbbFontSurveyName = new QComboBox(CXPageBM3DSurvey);
        m_cbbFontSurveyName->addItem(QString());
        m_cbbFontSurveyName->addItem(QString());
        m_cbbFontSurveyName->addItem(QString());
        m_cbbFontSurveyName->addItem(QString());
        m_cbbFontSurveyName->addItem(QString());
        m_cbbFontSurveyName->addItem(QString());
        m_cbbFontSurveyName->setObjectName(QString::fromUtf8("m_cbbFontSurveyName"));
        m_cbbFontSurveyName->setEnabled(false);

        gridLayout_4->addWidget(m_cbbFontSurveyName, 1, 4, 1, 1);

        label_19 = new QLabel(CXPageBM3DSurvey);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_4->addWidget(label_19, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPageBM3DSurvey);
        QObject::connect(m_cbSeismicLineVisible, SIGNAL(toggled(bool)), m_colorBtnSeismicLine, SLOT(setEnabled(bool)));
        QObject::connect(m_cbSeismicLineVisible, SIGNAL(toggled(bool)), m_spinBoxSeismicLineWidth, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTracePointVisible, SIGNAL(toggled(bool)), m_colorBtnTracePoint, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTracePointVisible, SIGNAL(toggled(bool)), m_cbbTracePointSymbol, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTickMarksVisible, SIGNAL(toggled(bool)), m_colorBtnTickMarks, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTickMarksVisible, SIGNAL(toggled(bool)), m_cbbFontTickMarks, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTickMarksVisible, SIGNAL(toggled(bool)), m_spinBoxFontSizeTickMarks, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTickMarksVisible, SIGNAL(toggled(bool)), m_cbInlineOnBegin, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTickMarksVisible, SIGNAL(toggled(bool)), m_cbXlineOnBegin, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTickMarksVisible, SIGNAL(toggled(bool)), m_cbInlineOnEnd, SLOT(setEnabled(bool)));
        QObject::connect(m_cbTickMarksVisible, SIGNAL(toggled(bool)), m_cbXlineOnEnd, SLOT(setEnabled(bool)));
        QObject::connect(m_cbSurveyNameVisible, SIGNAL(toggled(bool)), m_colorBtnSurveyName, SLOT(setEnabled(bool)));
        QObject::connect(m_cbSurveyNameVisible, SIGNAL(toggled(bool)), m_cbbFontSurveyName, SLOT(setEnabled(bool)));
        QObject::connect(m_cbSurveyNameVisible, SIGNAL(toggled(bool)), m_spinBoxSurveyName, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(CXPageBM3DSurvey);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageBM3DSurvey)
    {
        CXPageBM3DSurvey->setWindowTitle(QCoreApplication::translate("CXPageBM3DSurvey", "CXPageBM3DSurvey", nullptr));
        label->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Boundary line", nullptr));
        label_5->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Color:", nullptr));
        m_colorBtnBoundaryLine->setText(QString());
        label_6->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Line width:", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Seismic line", nullptr));
        m_cbSeismicLineVisible->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Visible", nullptr));
        label_7->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Line width:", nullptr));
        label_8->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Color:", nullptr));
        m_colorBtnSeismicLine->setText(QString());
        label_3->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Trace point", nullptr));
        m_cbTracePointVisible->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Visible", nullptr));
        m_cbbTracePointSymbol->setItemText(0, QCoreApplication::translate("CXPageBM3DSurvey", "\342\226\252", nullptr));
        m_cbbTracePointSymbol->setItemText(1, QCoreApplication::translate("CXPageBM3DSurvey", "+", nullptr));
        m_cbbTracePointSymbol->setItemText(2, QCoreApplication::translate("CXPageBM3DSurvey", "\303\227", nullptr));

        label_9->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Color:", nullptr));
        m_colorBtnTracePoint->setText(QString());
        label_10->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Symbol:", nullptr));
        label_4->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Tick marks", nullptr));
        label_12->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Font:", nullptr));
        m_colorBtnTickMarks->setText(QString());
        label_11->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Color:", nullptr));
        m_cbTickMarksVisible->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Visible", nullptr));
        label_15->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Display Crosslines annotation on:", nullptr));
        m_cbXlineOnBegin->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Begin", nullptr));
        m_cbXlineOnEnd->setText(QCoreApplication::translate("CXPageBM3DSurvey", "End", nullptr));
        m_cbInlineOnEnd->setText(QCoreApplication::translate("CXPageBM3DSurvey", "End", nullptr));
        m_cbbFontTickMarks->setItemText(0, QCoreApplication::translate("CXPageBM3DSurvey", "arial", nullptr));
        m_cbbFontTickMarks->setItemText(1, QCoreApplication::translate("CXPageBM3DSurvey", "dirtydoz", nullptr));
        m_cbbFontTickMarks->setItemText(2, QCoreApplication::translate("CXPageBM3DSurvey", "fudd", nullptr));
        m_cbbFontTickMarks->setItemText(3, QCoreApplication::translate("CXPageBM3DSurvey", "times", nullptr));
        m_cbbFontTickMarks->setItemText(4, QCoreApplication::translate("CXPageBM3DSurvey", "Vera", nullptr));
        m_cbbFontTickMarks->setItemText(5, QCoreApplication::translate("CXPageBM3DSurvey", "VeraMono", nullptr));

        label_13->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Font size:", nullptr));
        m_cbInlineOnBegin->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Begin", nullptr));
        label_14->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Display Inlines annotation on:", nullptr));
        label_16->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Survey Name", nullptr));
        m_colorBtnSurveyName->setText(QString());
        m_cbSurveyNameVisible->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Visible", nullptr));
        label_17->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Font size:", nullptr));
        label_18->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Color:", nullptr));
        m_cbbFontSurveyName->setItemText(0, QCoreApplication::translate("CXPageBM3DSurvey", "arial", nullptr));
        m_cbbFontSurveyName->setItemText(1, QCoreApplication::translate("CXPageBM3DSurvey", "dirtydoz", nullptr));
        m_cbbFontSurveyName->setItemText(2, QCoreApplication::translate("CXPageBM3DSurvey", "fudd", nullptr));
        m_cbbFontSurveyName->setItemText(3, QCoreApplication::translate("CXPageBM3DSurvey", "times", nullptr));
        m_cbbFontSurveyName->setItemText(4, QCoreApplication::translate("CXPageBM3DSurvey", "Vera", nullptr));
        m_cbbFontSurveyName->setItemText(5, QCoreApplication::translate("CXPageBM3DSurvey", "VeraMono", nullptr));

        label_19->setText(QCoreApplication::translate("CXPageBM3DSurvey", "Font:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageBM3DSurvey: public Ui_CXPageBM3DSurvey {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEBM3DSURVEY_H
