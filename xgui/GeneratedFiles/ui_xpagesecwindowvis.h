/********************************************************************************
** Form generated from reading UI file 'xpagesecwindowvis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESECWINDOWVIS_H
#define UI_XPAGESECWINDOWVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_PageSectionWindowVis
{
public:
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_26;
    QCheckBox *m_pChkShowMajorLine;
    QSpinBox *m_pSpbVerMargin;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_11;
    QLabel *label_31;
    QRadioButton *m_pRdoVerAuto;
    QLineEdit *m_pEdtVerInc;
    QLabel *label_32;
    QLabel *label_33;
    QLineEdit *m_pEdtVerIncOfMinor;
    QRadioButton *m_pRdoVerManual;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_3;
    CXButtonColorEdit *m_pVerAnnColor;
    QLabel *label_4;
    QSpinBox *m_pSpbVerAnnSize;
    QFontComboBox *m_pVerAnnFont;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QLabel *label_6;
    CXButtonColorEdit *m_pHorAnnColor;
    QLabel *label_7;
    QSpinBox *m_pSpbHorSize;
    QLabel *label_8;
    QFontComboBox *m_pHorFont;
    QLabel *label_25;
    QSpinBox *m_pSpinHorMargin;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QLabel *label_9;
    QRadioButton *m_pRdoHorAuto;
    QLineEdit *m_pEdtHorInc;
    QLabel *label_11;
    QLabel *label_29;
    QLineEdit *m_pEdtIncOfMinor;
    QLabel *label_30;
    QRadioButton *m_pRdoHorManual;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QComboBox *m_pCmbContent;
    QListWidget *m_pLstHorAnn;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_28;
    QLabel *label_22;
    QLineEdit *lm_pEdtSearchRadius;
    QLabel *label_23;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QFrame *line_2;
    QGridLayout *gridLayout_8;
    QLineEdit *m_pEdtTraceStep;
    QLabel *label_20;
    QLabel *label_17;
    QLineEdit *m_pEdtCliping;
    QLabel *label_16;
    QLineEdit *m_pEdtExcursion;
    QLabel *label_15;
    QLabel *label_12;
    QLineEdit *m_pEdtVerScale;
    QLabel *label_27;
    QLineEdit *m_pEdtScale;
    QLabel *label_19;
    QLabel *label_13;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_18;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_21;
    QFrame *line_3;

    void setupUi(QWidget *PageSectionWindowVis)
    {
        if (PageSectionWindowVis->objectName().isEmpty())
            PageSectionWindowVis->setObjectName(QString::fromUtf8("PageSectionWindowVis"));
        PageSectionWindowVis->resize(684, 491);
        gridLayout_6 = new QGridLayout(PageSectionWindowVis);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox_2 = new QGroupBox(PageSectionWindowVis);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_26, 3, 0, 1, 1);

        m_pChkShowMajorLine = new QCheckBox(groupBox_2);
        m_pChkShowMajorLine->setObjectName(QString::fromUtf8("m_pChkShowMajorLine"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pChkShowMajorLine->sizePolicy().hasHeightForWidth());
        m_pChkShowMajorLine->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(m_pChkShowMajorLine, 0, 0, 1, 1);

        m_pSpbVerMargin = new QSpinBox(groupBox_2);
        m_pSpbVerMargin->setObjectName(QString::fromUtf8("m_pSpbVerMargin"));

        gridLayout_2->addWidget(m_pSpbVerMargin, 3, 1, 1, 1);

        groupBox_8 = new QGroupBox(groupBox_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy3);
        gridLayout_11 = new QGridLayout(groupBox_8);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_31 = new QLabel(groupBox_8);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        sizePolicy.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy);
        label_31->setLayoutDirection(Qt::RightToLeft);
        label_31->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_11->addWidget(label_31, 1, 0, 1, 1);

        m_pRdoVerAuto = new QRadioButton(groupBox_8);
        m_pRdoVerAuto->setObjectName(QString::fromUtf8("m_pRdoVerAuto"));
        m_pRdoVerAuto->setChecked(true);

        gridLayout_11->addWidget(m_pRdoVerAuto, 0, 0, 1, 1);

        m_pEdtVerInc = new QLineEdit(groupBox_8);
        m_pEdtVerInc->setObjectName(QString::fromUtf8("m_pEdtVerInc"));
        m_pEdtVerInc->setEnabled(false);

        gridLayout_11->addWidget(m_pEdtVerInc, 1, 1, 1, 1);

        label_32 = new QLabel(groupBox_8);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        sizePolicy1.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy1);

        gridLayout_11->addWidget(label_32, 2, 0, 1, 1);

        label_33 = new QLabel(groupBox_8);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_11->addWidget(label_33, 1, 2, 1, 1);

        m_pEdtVerIncOfMinor = new QLineEdit(groupBox_8);
        m_pEdtVerIncOfMinor->setObjectName(QString::fromUtf8("m_pEdtVerIncOfMinor"));
        m_pEdtVerIncOfMinor->setEnabled(false);

        gridLayout_11->addWidget(m_pEdtVerIncOfMinor, 2, 1, 1, 1);

        m_pRdoVerManual = new QRadioButton(groupBox_8);
        m_pRdoVerManual->setObjectName(QString::fromUtf8("m_pRdoVerManual"));

        gridLayout_11->addWidget(m_pRdoVerManual, 0, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_8, 2, 0, 1, 2);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        m_pVerAnnColor = new CXButtonColorEdit(groupBox_3);
        m_pVerAnnColor->setObjectName(QString::fromUtf8("m_pVerAnnColor"));
        sizePolicy2.setHeightForWidth(m_pVerAnnColor->sizePolicy().hasHeightForWidth());
        m_pVerAnnColor->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(m_pVerAnnColor, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        m_pSpbVerAnnSize = new QSpinBox(groupBox_3);
        m_pSpbVerAnnSize->setObjectName(QString::fromUtf8("m_pSpbVerAnnSize"));

        gridLayout->addWidget(m_pSpbVerAnnSize, 0, 3, 1, 1);

        m_pVerAnnFont = new QFontComboBox(groupBox_3);
        m_pVerAnnFont->setObjectName(QString::fromUtf8("m_pVerAnnFont"));

        gridLayout->addWidget(m_pVerAnnFont, 1, 1, 1, 3);


        gridLayout_2->addWidget(groupBox_3, 1, 0, 1, 2);


        gridLayout_6->addWidget(groupBox_2, 1, 1, 1, 1);

        groupBox = new QGroupBox(PageSectionWindowVis);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(1);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(3, 3, 3, 3);
        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy3.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy3);
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        m_pHorAnnColor = new CXButtonColorEdit(groupBox_5);
        m_pHorAnnColor->setObjectName(QString::fromUtf8("m_pHorAnnColor"));
        sizePolicy2.setHeightForWidth(m_pHorAnnColor->sizePolicy().hasHeightForWidth());
        m_pHorAnnColor->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(m_pHorAnnColor, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(label_7, 0, 2, 1, 1);

        m_pSpbHorSize = new QSpinBox(groupBox_5);
        m_pSpbHorSize->setObjectName(QString::fromUtf8("m_pSpbHorSize"));

        gridLayout_4->addWidget(m_pSpbHorSize, 0, 3, 1, 1);

        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 1, 0, 1, 1);

        m_pHorFont = new QFontComboBox(groupBox_5);
        m_pHorFont->setObjectName(QString::fromUtf8("m_pHorFont"));

        gridLayout_4->addWidget(m_pHorFont, 1, 1, 1, 3);


        gridLayout_5->addWidget(groupBox_5, 0, 1, 1, 2);

        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy1.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_25, 2, 1, 1, 1);

        m_pSpinHorMargin = new QSpinBox(groupBox);
        m_pSpinHorMargin->setObjectName(QString::fromUtf8("m_pSpinHorMargin"));

        gridLayout_5->addWidget(m_pSpinHorMargin, 2, 2, 1, 1);

        groupBox_6 = new QGroupBox(groupBox);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        sizePolicy3.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy3);
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_9 = new QLabel(groupBox_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setLayoutDirection(Qt::LeftToRight);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_9, 1, 0, 1, 1);

        m_pRdoHorAuto = new QRadioButton(groupBox_6);
        m_pRdoHorAuto->setObjectName(QString::fromUtf8("m_pRdoHorAuto"));
        m_pRdoHorAuto->setChecked(true);

        gridLayout_7->addWidget(m_pRdoHorAuto, 0, 0, 1, 1);

        m_pEdtHorInc = new QLineEdit(groupBox_6);
        m_pEdtHorInc->setObjectName(QString::fromUtf8("m_pEdtHorInc"));
        m_pEdtHorInc->setEnabled(false);

        gridLayout_7->addWidget(m_pEdtHorInc, 1, 1, 1, 1);

        label_11 = new QLabel(groupBox_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(label_11, 2, 0, 1, 1);

        label_29 = new QLabel(groupBox_6);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_7->addWidget(label_29, 1, 2, 1, 1);

        m_pEdtIncOfMinor = new QLineEdit(groupBox_6);
        m_pEdtIncOfMinor->setObjectName(QString::fromUtf8("m_pEdtIncOfMinor"));
        m_pEdtIncOfMinor->setEnabled(false);

        gridLayout_7->addWidget(m_pEdtIncOfMinor, 2, 1, 1, 1);

        label_30 = new QLabel(groupBox_6);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_7->addWidget(label_30, 2, 2, 1, 1);

        m_pRdoHorManual = new QRadioButton(groupBox_6);
        m_pRdoHorManual->setObjectName(QString::fromUtf8("m_pRdoHorManual"));

        gridLayout_7->addWidget(m_pRdoHorManual, 0, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_6, 1, 1, 1, 2);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pCmbContent = new QComboBox(groupBox_4);
        m_pCmbContent->setObjectName(QString::fromUtf8("m_pCmbContent"));

        gridLayout_3->addWidget(m_pCmbContent, 0, 0, 1, 1);

        m_pLstHorAnn = new QListWidget(groupBox_4);
        m_pLstHorAnn->setObjectName(QString::fromUtf8("m_pLstHorAnn"));

        gridLayout_3->addWidget(m_pLstHorAnn, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 0, 0, 5, 1);


        gridLayout_6->addWidget(groupBox, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 8, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(PageSectionWindowVis);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        line = new QFrame(PageSectionWindowVis);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 2);

        buttonBox = new QDialogButtonBox(PageSectionWindowVis);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        sizePolicy3.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy3);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_6->addWidget(buttonBox, 10, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_28 = new QLabel(PageSectionWindowVis);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setMinimumSize(QSize(20, 0));
        label_28->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_4->addWidget(label_28);

        label_22 = new QLabel(PageSectionWindowVis);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy1.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_22);

        lm_pEdtSearchRadius = new QLineEdit(PageSectionWindowVis);
        lm_pEdtSearchRadius->setObjectName(QString::fromUtf8("lm_pEdtSearchRadius"));
        sizePolicy2.setHeightForWidth(lm_pEdtSearchRadius->sizePolicy().hasHeightForWidth());
        lm_pEdtSearchRadius->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(lm_pEdtSearchRadius);

        label_23 = new QLabel(PageSectionWindowVis);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy1.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_23);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout_6->addLayout(horizontalLayout_4, 7, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_2, 10, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(PageSectionWindowVis);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        line_2 = new QFrame(PageSectionWindowVis);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);


        gridLayout_6->addLayout(horizontalLayout_2, 2, 0, 1, 2);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        m_pEdtTraceStep = new QLineEdit(PageSectionWindowVis);
        m_pEdtTraceStep->setObjectName(QString::fromUtf8("m_pEdtTraceStep"));

        gridLayout_8->addWidget(m_pEdtTraceStep, 2, 2, 1, 1);

        label_20 = new QLabel(PageSectionWindowVis);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_20, 2, 1, 1, 1);

        label_17 = new QLabel(PageSectionWindowVis);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy1.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_17, 1, 9, 1, 1);

        m_pEdtCliping = new QLineEdit(PageSectionWindowVis);
        m_pEdtCliping->setObjectName(QString::fromUtf8("m_pEdtCliping"));

        gridLayout_8->addWidget(m_pEdtCliping, 1, 7, 1, 2);

        label_16 = new QLabel(PageSectionWindowVis);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy1.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_16, 1, 3, 1, 2);

        m_pEdtExcursion = new QLineEdit(PageSectionWindowVis);
        m_pEdtExcursion->setObjectName(QString::fromUtf8("m_pEdtExcursion"));

        gridLayout_8->addWidget(m_pEdtExcursion, 1, 2, 1, 1);

        label_15 = new QLabel(PageSectionWindowVis);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy1);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_15, 1, 1, 1, 1);

        label_12 = new QLabel(PageSectionWindowVis);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_8->addWidget(label_12, 0, 9, 1, 1);

        m_pEdtVerScale = new QLineEdit(PageSectionWindowVis);
        m_pEdtVerScale->setObjectName(QString::fromUtf8("m_pEdtVerScale"));

        gridLayout_8->addWidget(m_pEdtVerScale, 0, 7, 1, 2);

        label_27 = new QLabel(PageSectionWindowVis);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setMinimumSize(QSize(20, 0));
        label_27->setMaximumSize(QSize(20, 16777215));

        gridLayout_8->addWidget(label_27, 0, 0, 1, 1);

        m_pEdtScale = new QLineEdit(PageSectionWindowVis);
        m_pEdtScale->setObjectName(QString::fromUtf8("m_pEdtScale"));

        gridLayout_8->addWidget(m_pEdtScale, 0, 2, 1, 1);

        label_19 = new QLabel(PageSectionWindowVis);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_19, 2, 3, 1, 2);

        label_13 = new QLabel(PageSectionWindowVis);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_13, 0, 1, 1, 1);

        label_10 = new QLabel(PageSectionWindowVis);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_8->addWidget(label_10, 0, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_3, 0, 10, 1, 1);

        label_18 = new QLabel(PageSectionWindowVis);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_18, 1, 5, 1, 1);

        label_14 = new QLabel(PageSectionWindowVis);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(label_14, 0, 4, 1, 2);


        gridLayout_6->addLayout(gridLayout_8, 3, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_21 = new QLabel(PageSectionWindowVis);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy1.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_21);

        line_3 = new QFrame(PageSectionWindowVis);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_3);


        gridLayout_6->addLayout(horizontalLayout_3, 4, 0, 1, 2);


        retranslateUi(PageSectionWindowVis);
        QObject::connect(m_pRdoHorAuto, SIGNAL(toggled(bool)), m_pEdtHorInc, SLOT(setDisabled(bool)));
        QObject::connect(m_pRdoHorAuto, SIGNAL(toggled(bool)), m_pEdtIncOfMinor, SLOT(setDisabled(bool)));
        QObject::connect(m_pRdoHorManual, SIGNAL(toggled(bool)), m_pEdtHorInc, SLOT(setEnabled(bool)));
        QObject::connect(m_pRdoHorManual, SIGNAL(toggled(bool)), m_pEdtIncOfMinor, SLOT(setEnabled(bool)));
        QObject::connect(m_pRdoVerAuto, SIGNAL(toggled(bool)), m_pEdtVerInc, SLOT(setDisabled(bool)));
        QObject::connect(m_pRdoVerAuto, SIGNAL(toggled(bool)), m_pEdtVerIncOfMinor, SLOT(setDisabled(bool)));
        QObject::connect(m_pRdoVerManual, SIGNAL(toggled(bool)), m_pEdtVerInc, SLOT(setEnabled(bool)));
        QObject::connect(m_pRdoVerManual, SIGNAL(toggled(bool)), m_pEdtVerIncOfMinor, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(PageSectionWindowVis);
    } // setupUi

    void retranslateUi(QWidget *PageSectionWindowVis)
    {
        PageSectionWindowVis->setWindowTitle(QCoreApplication::translate("PageSectionWindowVis", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PageSectionWindowVis", "Vertical", nullptr));
        label_26->setText(QCoreApplication::translate("PageSectionWindowVis", "Vertical Axis Margin:", nullptr));
        m_pChkShowMajorLine->setText(QCoreApplication::translate("PageSectionWindowVis", "Show Major Line", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("PageSectionWindowVis", "Tick", nullptr));
        label_31->setText(QCoreApplication::translate("PageSectionWindowVis", "X Inc:", nullptr));
        m_pRdoVerAuto->setText(QCoreApplication::translate("PageSectionWindowVis", "Automatic", nullptr));
        label_32->setText(QCoreApplication::translate("PageSectionWindowVis", "Inc. of minor tick:", nullptr));
        label_33->setText(QCoreApplication::translate("PageSectionWindowVis", "unit", nullptr));
        m_pRdoVerManual->setText(QCoreApplication::translate("PageSectionWindowVis", "Manual", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("PageSectionWindowVis", "Annotation", nullptr));
        label_5->setText(QCoreApplication::translate("PageSectionWindowVis", "Font:", nullptr));
        label_3->setText(QCoreApplication::translate("PageSectionWindowVis", "Color:", nullptr));
        m_pVerAnnColor->setText(QCoreApplication::translate("PageSectionWindowVis", "Color", nullptr));
        label_4->setText(QCoreApplication::translate("PageSectionWindowVis", "Size:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageSectionWindowVis", "Horizon", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("PageSectionWindowVis", "Annotation", nullptr));
        label_6->setText(QCoreApplication::translate("PageSectionWindowVis", "Color:", nullptr));
        m_pHorAnnColor->setText(QCoreApplication::translate("PageSectionWindowVis", "Color", nullptr));
        label_7->setText(QCoreApplication::translate("PageSectionWindowVis", "Size:", nullptr));
        label_8->setText(QCoreApplication::translate("PageSectionWindowVis", "Font:", nullptr));
        label_25->setText(QCoreApplication::translate("PageSectionWindowVis", "Horizontal Axis Margin:", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("PageSectionWindowVis", "Tick", nullptr));
        label_9->setText(QCoreApplication::translate("PageSectionWindowVis", "Inc:", nullptr));
        m_pRdoHorAuto->setText(QCoreApplication::translate("PageSectionWindowVis", "Automatic", nullptr));
        label_11->setText(QCoreApplication::translate("PageSectionWindowVis", "Inc. of minor tick:", nullptr));
        label_29->setText(QCoreApplication::translate("PageSectionWindowVis", "Traces", nullptr));
        label_30->setText(QCoreApplication::translate("PageSectionWindowVis", "Traces", nullptr));
        m_pRdoHorManual->setText(QCoreApplication::translate("PageSectionWindowVis", "Manual", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("PageSectionWindowVis", "Content", nullptr));
        label->setText(QCoreApplication::translate("PageSectionWindowVis", "Axis", nullptr));
        label_28->setText(QString());
        label_22->setText(QCoreApplication::translate("PageSectionWindowVis", "Searching Radius:", nullptr));
        label_23->setText(QCoreApplication::translate("PageSectionWindowVis", "m", nullptr));
        label_2->setText(QCoreApplication::translate("PageSectionWindowVis", "Scale", nullptr));
        label_20->setText(QCoreApplication::translate("PageSectionWindowVis", " Trace step:", nullptr));
        label_17->setText(QCoreApplication::translate("PageSectionWindowVis", "Traces", nullptr));
        label_16->setText(QCoreApplication::translate("PageSectionWindowVis", "Traces", nullptr));
        label_15->setText(QCoreApplication::translate("PageSectionWindowVis", "  Excursion:", nullptr));
        label_12->setText(QCoreApplication::translate("PageSectionWindowVis", "ms/cm", nullptr));
        label_27->setText(QString());
        label_19->setText(QCoreApplication::translate("PageSectionWindowVis", "Traces", nullptr));
        label_13->setText(QCoreApplication::translate("PageSectionWindowVis", "Trace Scale:", nullptr));
        label_10->setText(QCoreApplication::translate("PageSectionWindowVis", "Traces/cm", nullptr));
        label_18->setText(QCoreApplication::translate("PageSectionWindowVis", "Cliping:", nullptr));
        label_14->setText(QCoreApplication::translate("PageSectionWindowVis", "    Time/Depth scale:", nullptr));
        label_21->setText(QCoreApplication::translate("PageSectionWindowVis", "Others", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageSectionWindowVis: public Ui_PageSectionWindowVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESECWINDOWVIS_H
