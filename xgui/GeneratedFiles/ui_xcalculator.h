/********************************************************************************
** Form generated from reading UI file 'xcalculator.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XCALCULATOR_H
#define UI_XCALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgCalculator
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *m_EdtFunctionDisplay;
    QToolButton *m_TbnBrowse;
    QTreeWidget *m_VaribleTree;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QToolButton *m_TbnClearShowView;
    QToolButton *m_TbnCopy;
    QListWidget *m_LsResultShow;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *m_TbnDeg;
    QRadioButton *m_RdoRad;
    QRadioButton *m_RdoGrad;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *comboBox;
    QLabel *m_LblHelp;
    QGridLayout *gridLayout_2;
    QToolButton *m_Tbn7;
    QToolButton *m_Tbn8;
    QToolButton *m_Tbn9;
    QToolButton *m_TbnDivide;
    QToolButton *m_TbnLbracket;
    QToolButton *m_TbnRbracket;
    QToolButton *m_TbnClear;
    QToolButton *m_Tbn4;
    QToolButton *m_Tbn5;
    QToolButton *m_Tbn6;
    QToolButton *m_TbnMultiply;
    QToolButton *m_TbnLessthan;
    QToolButton *m_TbnLessAndEqual;
    QToolButton *m_TbnIf;
    QToolButton *m_Tbn1;
    QToolButton *m_Tbn2;
    QToolButton *m_Tbn3;
    QToolButton *m_TbnSubtract;
    QToolButton *m_TbnMorethan;
    QToolButton *m_TbnMoreAndEqual;
    QToolButton *m_TbnAnd;
    QToolButton *m_Tbn0;
    QToolButton *m_TbnU;
    QToolButton *m_TbnDot;
    QToolButton *m_TbnAddition;
    QToolButton *m_TbnCast;
    QToolButton *m_TbnEqual;
    QToolButton *m_TbnOr;
    QToolButton *m_TbnMin;
    QToolButton *m_TbnMax;
    QToolButton *m_TbnMean;
    QToolButton *m_TbnPi;
    QToolButton *m_TbnSin;
    QToolButton *m_TbnCos;
    QToolButton *m_TbnTan;
    QToolButton *m_TbnASin;
    QToolButton *m_TbnACos;
    QToolButton *m_TbnATan;
    QToolButton *m_TbnAcTan;
    QToolButton *m_TbnCTan;
    QToolButton *m_TbnRand;
    QToolButton *m_TbnRandn;
    QToolButton *m_TbnRound;
    QToolButton *m_TbnAbs;
    QToolButton *m_TbnExp;
    QToolButton *m_TbnPow;
    QToolButton *m_TbnSqrt;
    QToolButton *m_TbnInt;
    QToolButton *m_TbnLn;
    QToolButton *m_TbnLog;
    QToolButton *m_TbnStd;
    QToolButton *m_TbnNum;
    QToolButton *m_TbnEnter;
    QToolButton *m_TbnBackSpace;
    QToolButton *m_TbnSum;
    QLabel *label_3;

    void setupUi(QWidget *DlgCalculator)
    {
        if (DlgCalculator->objectName().isEmpty())
            DlgCalculator->setObjectName(QString::fromUtf8("DlgCalculator"));
        DlgCalculator->resize(838, 557);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DlgCalculator->sizePolicy().hasHeightForWidth());
        DlgCalculator->setSizePolicy(sizePolicy);
        DlgCalculator->setFocusPolicy(Qt::TabFocus);
        gridLayout_3 = new QGridLayout(DlgCalculator);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_EdtFunctionDisplay = new QLineEdit(DlgCalculator);
        m_EdtFunctionDisplay->setObjectName(QString::fromUtf8("m_EdtFunctionDisplay"));
        m_EdtFunctionDisplay->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(m_EdtFunctionDisplay);

        m_TbnBrowse = new QToolButton(DlgCalculator);
        m_TbnBrowse->setObjectName(QString::fromUtf8("m_TbnBrowse"));
        m_TbnBrowse->setEnabled(true);

        horizontalLayout_3->addWidget(m_TbnBrowse);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 2);

        m_VaribleTree = new QTreeWidget(DlgCalculator);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        m_VaribleTree->setHeaderItem(__qtreewidgetitem);
        m_VaribleTree->setObjectName(QString::fromUtf8("m_VaribleTree"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_VaribleTree->sizePolicy().hasHeightForWidth());
        m_VaribleTree->setSizePolicy(sizePolicy1);
        m_VaribleTree->setMinimumSize(QSize(200, 0));
        m_VaribleTree->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(m_VaribleTree, 1, 0, 1, 2);

        groupBox = new QGroupBox(DlgCalculator);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setFlat(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_TbnClearShowView = new QToolButton(groupBox);
        m_TbnClearShowView->setObjectName(QString::fromUtf8("m_TbnClearShowView"));

        gridLayout->addWidget(m_TbnClearShowView, 1, 0, 1, 1);

        m_TbnCopy = new QToolButton(groupBox);
        m_TbnCopy->setObjectName(QString::fromUtf8("m_TbnCopy"));

        gridLayout->addWidget(m_TbnCopy, 0, 0, 1, 1);

        m_LsResultShow = new QListWidget(groupBox);
        m_LsResultShow->setObjectName(QString::fromUtf8("m_LsResultShow"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_LsResultShow->sizePolicy().hasHeightForWidth());
        m_LsResultShow->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(m_LsResultShow, 0, 1, 2, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_2 = new QGroupBox(DlgCalculator);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(3, 3, 3, 3);
        m_TbnDeg = new QRadioButton(groupBox_2);
        m_TbnDeg->setObjectName(QString::fromUtf8("m_TbnDeg"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_TbnDeg->sizePolicy().hasHeightForWidth());
        m_TbnDeg->setSizePolicy(sizePolicy3);
        m_TbnDeg->setChecked(true);

        horizontalLayout_2->addWidget(m_TbnDeg);

        m_RdoRad = new QRadioButton(groupBox_2);
        m_RdoRad->setObjectName(QString::fromUtf8("m_RdoRad"));
        sizePolicy3.setHeightForWidth(m_RdoRad->sizePolicy().hasHeightForWidth());
        m_RdoRad->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(m_RdoRad);

        m_RdoGrad = new QRadioButton(groupBox_2);
        m_RdoGrad->setObjectName(QString::fromUtf8("m_RdoGrad"));
        sizePolicy3.setHeightForWidth(m_RdoGrad->sizePolicy().hasHeightForWidth());
        m_RdoGrad->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(m_RdoGrad);


        horizontalLayout_4->addWidget(groupBox_2);


        horizontalLayout_9->addLayout(horizontalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout_9, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(DlgCalculator);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        comboBox = new QComboBox(DlgCalculator);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        m_LblHelp = new QLabel(DlgCalculator);
        m_LblHelp->setObjectName(QString::fromUtf8("m_LblHelp"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(m_LblHelp->sizePolicy().hasHeightForWidth());
        m_LblHelp->setSizePolicy(sizePolicy4);
        m_LblHelp->setTextFormat(Qt::AutoText);
        m_LblHelp->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(m_LblHelp);


        gridLayout_3->addLayout(horizontalLayout, 3, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_Tbn7 = new QToolButton(DlgCalculator);
        m_Tbn7->setObjectName(QString::fromUtf8("m_Tbn7"));
        sizePolicy4.setHeightForWidth(m_Tbn7->sizePolicy().hasHeightForWidth());
        m_Tbn7->setSizePolicy(sizePolicy4);
        QPalette palette;
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(118, 116, 108, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn7->setPalette(palette);
        QFont font;
        font.setPointSize(9);
        m_Tbn7->setFont(font);

        gridLayout_2->addWidget(m_Tbn7, 2, 7, 1, 1);

        m_Tbn8 = new QToolButton(DlgCalculator);
        m_Tbn8->setObjectName(QString::fromUtf8("m_Tbn8"));
        sizePolicy4.setHeightForWidth(m_Tbn8->sizePolicy().hasHeightForWidth());
        m_Tbn8->setSizePolicy(sizePolicy4);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn8->setPalette(palette1);
        m_Tbn8->setFont(font);

        gridLayout_2->addWidget(m_Tbn8, 2, 8, 1, 1);

        m_Tbn9 = new QToolButton(DlgCalculator);
        m_Tbn9->setObjectName(QString::fromUtf8("m_Tbn9"));
        sizePolicy4.setHeightForWidth(m_Tbn9->sizePolicy().hasHeightForWidth());
        m_Tbn9->setSizePolicy(sizePolicy4);
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn9->setPalette(palette2);
        m_Tbn9->setFont(font);

        gridLayout_2->addWidget(m_Tbn9, 2, 9, 1, 1);

        m_TbnDivide = new QToolButton(DlgCalculator);
        m_TbnDivide->setObjectName(QString::fromUtf8("m_TbnDivide"));
        sizePolicy4.setHeightForWidth(m_TbnDivide->sizePolicy().hasHeightForWidth());
        m_TbnDivide->setSizePolicy(sizePolicy4);
        QPalette palette3;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnDivide->setPalette(palette3);
        m_TbnDivide->setFont(font);

        gridLayout_2->addWidget(m_TbnDivide, 2, 10, 1, 1);

        m_TbnLbracket = new QToolButton(DlgCalculator);
        m_TbnLbracket->setObjectName(QString::fromUtf8("m_TbnLbracket"));
        sizePolicy4.setHeightForWidth(m_TbnLbracket->sizePolicy().hasHeightForWidth());
        m_TbnLbracket->setSizePolicy(sizePolicy4);
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnLbracket->setPalette(palette4);
        m_TbnLbracket->setFont(font);

        gridLayout_2->addWidget(m_TbnLbracket, 2, 11, 1, 1);

        m_TbnRbracket = new QToolButton(DlgCalculator);
        m_TbnRbracket->setObjectName(QString::fromUtf8("m_TbnRbracket"));
        sizePolicy4.setHeightForWidth(m_TbnRbracket->sizePolicy().hasHeightForWidth());
        m_TbnRbracket->setSizePolicy(sizePolicy4);
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnRbracket->setPalette(palette5);
        m_TbnRbracket->setFont(font);

        gridLayout_2->addWidget(m_TbnRbracket, 2, 12, 1, 1);

        m_TbnClear = new QToolButton(DlgCalculator);
        m_TbnClear->setObjectName(QString::fromUtf8("m_TbnClear"));
        sizePolicy4.setHeightForWidth(m_TbnClear->sizePolicy().hasHeightForWidth());
        m_TbnClear->setSizePolicy(sizePolicy4);
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnClear->setPalette(palette6);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        m_TbnClear->setFont(font1);

        gridLayout_2->addWidget(m_TbnClear, 2, 13, 1, 1);

        m_Tbn4 = new QToolButton(DlgCalculator);
        m_Tbn4->setObjectName(QString::fromUtf8("m_Tbn4"));
        sizePolicy4.setHeightForWidth(m_Tbn4->sizePolicy().hasHeightForWidth());
        m_Tbn4->setSizePolicy(sizePolicy4);
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn4->setPalette(palette7);
        m_Tbn4->setFont(font);

        gridLayout_2->addWidget(m_Tbn4, 3, 7, 1, 1);

        m_Tbn5 = new QToolButton(DlgCalculator);
        m_Tbn5->setObjectName(QString::fromUtf8("m_Tbn5"));
        sizePolicy4.setHeightForWidth(m_Tbn5->sizePolicy().hasHeightForWidth());
        m_Tbn5->setSizePolicy(sizePolicy4);
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn5->setPalette(palette8);
        m_Tbn5->setFont(font);

        gridLayout_2->addWidget(m_Tbn5, 3, 8, 1, 1);

        m_Tbn6 = new QToolButton(DlgCalculator);
        m_Tbn6->setObjectName(QString::fromUtf8("m_Tbn6"));
        sizePolicy4.setHeightForWidth(m_Tbn6->sizePolicy().hasHeightForWidth());
        m_Tbn6->setSizePolicy(sizePolicy4);
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn6->setPalette(palette9);
        m_Tbn6->setFont(font);

        gridLayout_2->addWidget(m_Tbn6, 3, 9, 1, 1);

        m_TbnMultiply = new QToolButton(DlgCalculator);
        m_TbnMultiply->setObjectName(QString::fromUtf8("m_TbnMultiply"));
        sizePolicy4.setHeightForWidth(m_TbnMultiply->sizePolicy().hasHeightForWidth());
        m_TbnMultiply->setSizePolicy(sizePolicy4);
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnMultiply->setPalette(palette10);
        m_TbnMultiply->setFont(font);

        gridLayout_2->addWidget(m_TbnMultiply, 3, 10, 1, 1);

        m_TbnLessthan = new QToolButton(DlgCalculator);
        m_TbnLessthan->setObjectName(QString::fromUtf8("m_TbnLessthan"));
        sizePolicy4.setHeightForWidth(m_TbnLessthan->sizePolicy().hasHeightForWidth());
        m_TbnLessthan->setSizePolicy(sizePolicy4);
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnLessthan->setPalette(palette11);
        m_TbnLessthan->setFont(font);

        gridLayout_2->addWidget(m_TbnLessthan, 3, 11, 1, 1);

        m_TbnLessAndEqual = new QToolButton(DlgCalculator);
        m_TbnLessAndEqual->setObjectName(QString::fromUtf8("m_TbnLessAndEqual"));
        sizePolicy4.setHeightForWidth(m_TbnLessAndEqual->sizePolicy().hasHeightForWidth());
        m_TbnLessAndEqual->setSizePolicy(sizePolicy4);
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnLessAndEqual->setPalette(palette12);
        m_TbnLessAndEqual->setFont(font);

        gridLayout_2->addWidget(m_TbnLessAndEqual, 3, 12, 1, 1);

        m_TbnIf = new QToolButton(DlgCalculator);
        m_TbnIf->setObjectName(QString::fromUtf8("m_TbnIf"));
        sizePolicy4.setHeightForWidth(m_TbnIf->sizePolicy().hasHeightForWidth());
        m_TbnIf->setSizePolicy(sizePolicy4);
        QPalette palette13;
        QBrush brush3(QColor(0, 170, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette13.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette13.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette13.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnIf->setPalette(palette13);
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(true);
        font2.setWeight(75);
        m_TbnIf->setFont(font2);

        gridLayout_2->addWidget(m_TbnIf, 3, 13, 1, 1);

        m_Tbn1 = new QToolButton(DlgCalculator);
        m_Tbn1->setObjectName(QString::fromUtf8("m_Tbn1"));
        sizePolicy4.setHeightForWidth(m_Tbn1->sizePolicy().hasHeightForWidth());
        m_Tbn1->setSizePolicy(sizePolicy4);
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn1->setPalette(palette14);
        m_Tbn1->setFont(font);

        gridLayout_2->addWidget(m_Tbn1, 4, 7, 1, 1);

        m_Tbn2 = new QToolButton(DlgCalculator);
        m_Tbn2->setObjectName(QString::fromUtf8("m_Tbn2"));
        sizePolicy4.setHeightForWidth(m_Tbn2->sizePolicy().hasHeightForWidth());
        m_Tbn2->setSizePolicy(sizePolicy4);
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette15.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette15.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn2->setPalette(palette15);
        m_Tbn2->setFont(font);

        gridLayout_2->addWidget(m_Tbn2, 4, 8, 1, 1);

        m_Tbn3 = new QToolButton(DlgCalculator);
        m_Tbn3->setObjectName(QString::fromUtf8("m_Tbn3"));
        sizePolicy4.setHeightForWidth(m_Tbn3->sizePolicy().hasHeightForWidth());
        m_Tbn3->setSizePolicy(sizePolicy4);
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette16.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette16.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn3->setPalette(palette16);
        m_Tbn3->setFont(font);

        gridLayout_2->addWidget(m_Tbn3, 4, 9, 1, 1);

        m_TbnSubtract = new QToolButton(DlgCalculator);
        m_TbnSubtract->setObjectName(QString::fromUtf8("m_TbnSubtract"));
        sizePolicy4.setHeightForWidth(m_TbnSubtract->sizePolicy().hasHeightForWidth());
        m_TbnSubtract->setSizePolicy(sizePolicy4);
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette17.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette17.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnSubtract->setPalette(palette17);
        m_TbnSubtract->setFont(font);

        gridLayout_2->addWidget(m_TbnSubtract, 4, 10, 1, 1);

        m_TbnMorethan = new QToolButton(DlgCalculator);
        m_TbnMorethan->setObjectName(QString::fromUtf8("m_TbnMorethan"));
        sizePolicy4.setHeightForWidth(m_TbnMorethan->sizePolicy().hasHeightForWidth());
        m_TbnMorethan->setSizePolicy(sizePolicy4);
        QPalette palette18;
        palette18.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette18.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette18.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnMorethan->setPalette(palette18);
        m_TbnMorethan->setFont(font);

        gridLayout_2->addWidget(m_TbnMorethan, 4, 11, 1, 1);

        m_TbnMoreAndEqual = new QToolButton(DlgCalculator);
        m_TbnMoreAndEqual->setObjectName(QString::fromUtf8("m_TbnMoreAndEqual"));
        sizePolicy4.setHeightForWidth(m_TbnMoreAndEqual->sizePolicy().hasHeightForWidth());
        m_TbnMoreAndEqual->setSizePolicy(sizePolicy4);
        QPalette palette19;
        palette19.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette19.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnMoreAndEqual->setPalette(palette19);
        m_TbnMoreAndEqual->setFont(font);

        gridLayout_2->addWidget(m_TbnMoreAndEqual, 4, 12, 1, 1);

        m_TbnAnd = new QToolButton(DlgCalculator);
        m_TbnAnd->setObjectName(QString::fromUtf8("m_TbnAnd"));
        sizePolicy4.setHeightForWidth(m_TbnAnd->sizePolicy().hasHeightForWidth());
        m_TbnAnd->setSizePolicy(sizePolicy4);
        QPalette palette20;
        palette20.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette20.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette20.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnAnd->setPalette(palette20);
        m_TbnAnd->setFont(font2);

        gridLayout_2->addWidget(m_TbnAnd, 4, 13, 1, 1);

        m_Tbn0 = new QToolButton(DlgCalculator);
        m_Tbn0->setObjectName(QString::fromUtf8("m_Tbn0"));
        sizePolicy4.setHeightForWidth(m_Tbn0->sizePolicy().hasHeightForWidth());
        m_Tbn0->setSizePolicy(sizePolicy4);
        QPalette palette21;
        palette21.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette21.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette21.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_Tbn0->setPalette(palette21);
        m_Tbn0->setFont(font);

        gridLayout_2->addWidget(m_Tbn0, 5, 7, 1, 1);

        m_TbnU = new QToolButton(DlgCalculator);
        m_TbnU->setObjectName(QString::fromUtf8("m_TbnU"));
        sizePolicy4.setHeightForWidth(m_TbnU->sizePolicy().hasHeightForWidth());
        m_TbnU->setSizePolicy(sizePolicy4);
        QPalette palette22;
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette22.setBrush(QPalette::Active, QPalette::ButtonText, brush4);
        palette22.setBrush(QPalette::Inactive, QPalette::ButtonText, brush4);
        palette22.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnU->setPalette(palette22);
        m_TbnU->setFont(font);

        gridLayout_2->addWidget(m_TbnU, 5, 8, 1, 1);

        m_TbnDot = new QToolButton(DlgCalculator);
        m_TbnDot->setObjectName(QString::fromUtf8("m_TbnDot"));
        sizePolicy4.setHeightForWidth(m_TbnDot->sizePolicy().hasHeightForWidth());
        m_TbnDot->setSizePolicy(sizePolicy4);
        QPalette palette23;
        palette23.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette23.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette23.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnDot->setPalette(palette23);
        m_TbnDot->setFont(font);

        gridLayout_2->addWidget(m_TbnDot, 5, 9, 1, 1);

        m_TbnAddition = new QToolButton(DlgCalculator);
        m_TbnAddition->setObjectName(QString::fromUtf8("m_TbnAddition"));
        sizePolicy4.setHeightForWidth(m_TbnAddition->sizePolicy().hasHeightForWidth());
        m_TbnAddition->setSizePolicy(sizePolicy4);
        QPalette palette24;
        palette24.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette24.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette24.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnAddition->setPalette(palette24);
        m_TbnAddition->setFont(font);

        gridLayout_2->addWidget(m_TbnAddition, 5, 10, 1, 1);

        m_TbnCast = new QToolButton(DlgCalculator);
        m_TbnCast->setObjectName(QString::fromUtf8("m_TbnCast"));
        sizePolicy4.setHeightForWidth(m_TbnCast->sizePolicy().hasHeightForWidth());
        m_TbnCast->setSizePolicy(sizePolicy4);
        QPalette palette25;
        palette25.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette25.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette25.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnCast->setPalette(palette25);
        m_TbnCast->setFont(font);

        gridLayout_2->addWidget(m_TbnCast, 5, 11, 1, 1);

        m_TbnEqual = new QToolButton(DlgCalculator);
        m_TbnEqual->setObjectName(QString::fromUtf8("m_TbnEqual"));
        sizePolicy4.setHeightForWidth(m_TbnEqual->sizePolicy().hasHeightForWidth());
        m_TbnEqual->setSizePolicy(sizePolicy4);
        QPalette palette26;
        palette26.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette26.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette26.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnEqual->setPalette(palette26);
        m_TbnEqual->setFont(font);

        gridLayout_2->addWidget(m_TbnEqual, 5, 12, 1, 1);

        m_TbnOr = new QToolButton(DlgCalculator);
        m_TbnOr->setObjectName(QString::fromUtf8("m_TbnOr"));
        sizePolicy4.setHeightForWidth(m_TbnOr->sizePolicy().hasHeightForWidth());
        m_TbnOr->setSizePolicy(sizePolicy4);
        QPalette palette27;
        palette27.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        palette27.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        palette27.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnOr->setPalette(palette27);
        m_TbnOr->setFont(font2);

        gridLayout_2->addWidget(m_TbnOr, 5, 13, 1, 1);

        m_TbnMin = new QToolButton(DlgCalculator);
        m_TbnMin->setObjectName(QString::fromUtf8("m_TbnMin"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(m_TbnMin->sizePolicy().hasHeightForWidth());
        m_TbnMin->setSizePolicy(sizePolicy5);
        m_TbnMin->setMinimumSize(QSize(0, 27));
        QPalette palette28;
        QBrush brush5(QColor(170, 0, 255, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette28.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette28.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette28.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnMin->setPalette(palette28);
        m_TbnMin->setFont(font1);

        gridLayout_2->addWidget(m_TbnMin, 3, 4, 1, 1);

        m_TbnMax = new QToolButton(DlgCalculator);
        m_TbnMax->setObjectName(QString::fromUtf8("m_TbnMax"));
        sizePolicy5.setHeightForWidth(m_TbnMax->sizePolicy().hasHeightForWidth());
        m_TbnMax->setSizePolicy(sizePolicy5);
        m_TbnMax->setMinimumSize(QSize(0, 27));
        QPalette palette29;
        palette29.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette29.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette29.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnMax->setPalette(palette29);
        m_TbnMax->setFont(font1);

        gridLayout_2->addWidget(m_TbnMax, 4, 4, 1, 1);

        m_TbnMean = new QToolButton(DlgCalculator);
        m_TbnMean->setObjectName(QString::fromUtf8("m_TbnMean"));
        sizePolicy5.setHeightForWidth(m_TbnMean->sizePolicy().hasHeightForWidth());
        m_TbnMean->setSizePolicy(sizePolicy5);
        m_TbnMean->setMinimumSize(QSize(0, 27));
        QPalette palette30;
        palette30.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette30.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette30.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnMean->setPalette(palette30);
        m_TbnMean->setFont(font1);

        gridLayout_2->addWidget(m_TbnMean, 5, 4, 1, 1);

        m_TbnPi = new QToolButton(DlgCalculator);
        m_TbnPi->setObjectName(QString::fromUtf8("m_TbnPi"));
        sizePolicy5.setHeightForWidth(m_TbnPi->sizePolicy().hasHeightForWidth());
        m_TbnPi->setSizePolicy(sizePolicy5);
        m_TbnPi->setMinimumSize(QSize(0, 27));
        QPalette palette31;
        palette31.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette31.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette31.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnPi->setPalette(palette31);
        QFont font3;
        font3.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font3.setPointSize(9);
        font3.setBold(false);
        font3.setWeight(50);
        m_TbnPi->setFont(font3);

        gridLayout_2->addWidget(m_TbnPi, 1, 7, 1, 1);

        m_TbnSin = new QToolButton(DlgCalculator);
        m_TbnSin->setObjectName(QString::fromUtf8("m_TbnSin"));
        sizePolicy5.setHeightForWidth(m_TbnSin->sizePolicy().hasHeightForWidth());
        m_TbnSin->setSizePolicy(sizePolicy5);
        m_TbnSin->setMinimumSize(QSize(0, 27));
        QPalette palette32;
        palette32.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette32.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette32.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnSin->setPalette(palette32);
        m_TbnSin->setFont(font1);

        gridLayout_2->addWidget(m_TbnSin, 1, 0, 1, 1);

        m_TbnCos = new QToolButton(DlgCalculator);
        m_TbnCos->setObjectName(QString::fromUtf8("m_TbnCos"));
        sizePolicy5.setHeightForWidth(m_TbnCos->sizePolicy().hasHeightForWidth());
        m_TbnCos->setSizePolicy(sizePolicy5);
        m_TbnCos->setMinimumSize(QSize(0, 27));
        QPalette palette33;
        palette33.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette33.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette33.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnCos->setPalette(palette33);
        m_TbnCos->setFont(font1);

        gridLayout_2->addWidget(m_TbnCos, 2, 0, 1, 1);

        m_TbnTan = new QToolButton(DlgCalculator);
        m_TbnTan->setObjectName(QString::fromUtf8("m_TbnTan"));
        sizePolicy5.setHeightForWidth(m_TbnTan->sizePolicy().hasHeightForWidth());
        m_TbnTan->setSizePolicy(sizePolicy5);
        m_TbnTan->setMinimumSize(QSize(0, 27));
        QPalette palette34;
        palette34.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette34.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette34.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnTan->setPalette(palette34);
        m_TbnTan->setFont(font1);

        gridLayout_2->addWidget(m_TbnTan, 3, 0, 1, 1);

        m_TbnASin = new QToolButton(DlgCalculator);
        m_TbnASin->setObjectName(QString::fromUtf8("m_TbnASin"));
        sizePolicy5.setHeightForWidth(m_TbnASin->sizePolicy().hasHeightForWidth());
        m_TbnASin->setSizePolicy(sizePolicy5);
        m_TbnASin->setMinimumSize(QSize(0, 27));
        QPalette palette35;
        palette35.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette35.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette35.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnASin->setPalette(palette35);
        m_TbnASin->setFont(font1);

        gridLayout_2->addWidget(m_TbnASin, 1, 1, 1, 1);

        m_TbnACos = new QToolButton(DlgCalculator);
        m_TbnACos->setObjectName(QString::fromUtf8("m_TbnACos"));
        sizePolicy5.setHeightForWidth(m_TbnACos->sizePolicy().hasHeightForWidth());
        m_TbnACos->setSizePolicy(sizePolicy5);
        m_TbnACos->setMinimumSize(QSize(0, 27));
        QPalette palette36;
        palette36.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette36.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette36.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnACos->setPalette(palette36);
        m_TbnACos->setFont(font1);

        gridLayout_2->addWidget(m_TbnACos, 2, 1, 1, 1);

        m_TbnATan = new QToolButton(DlgCalculator);
        m_TbnATan->setObjectName(QString::fromUtf8("m_TbnATan"));
        sizePolicy5.setHeightForWidth(m_TbnATan->sizePolicy().hasHeightForWidth());
        m_TbnATan->setSizePolicy(sizePolicy5);
        m_TbnATan->setMinimumSize(QSize(0, 27));
        QPalette palette37;
        palette37.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette37.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette37.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnATan->setPalette(palette37);
        m_TbnATan->setFont(font1);

        gridLayout_2->addWidget(m_TbnATan, 3, 1, 1, 1);

        m_TbnAcTan = new QToolButton(DlgCalculator);
        m_TbnAcTan->setObjectName(QString::fromUtf8("m_TbnAcTan"));
        m_TbnAcTan->setMinimumSize(QSize(0, 27));
        QPalette palette38;
        palette38.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette38.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette38.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnAcTan->setPalette(palette38);
        m_TbnAcTan->setFont(font1);

        gridLayout_2->addWidget(m_TbnAcTan, 4, 1, 1, 1);

        m_TbnCTan = new QToolButton(DlgCalculator);
        m_TbnCTan->setObjectName(QString::fromUtf8("m_TbnCTan"));
        sizePolicy5.setHeightForWidth(m_TbnCTan->sizePolicy().hasHeightForWidth());
        m_TbnCTan->setSizePolicy(sizePolicy5);
        m_TbnCTan->setMinimumSize(QSize(0, 27));
        QPalette palette39;
        palette39.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette39.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette39.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnCTan->setPalette(palette39);
        m_TbnCTan->setFont(font1);

        gridLayout_2->addWidget(m_TbnCTan, 4, 0, 1, 1);

        m_TbnRand = new QToolButton(DlgCalculator);
        m_TbnRand->setObjectName(QString::fromUtf8("m_TbnRand"));
        sizePolicy5.setHeightForWidth(m_TbnRand->sizePolicy().hasHeightForWidth());
        m_TbnRand->setSizePolicy(sizePolicy5);
        m_TbnRand->setMinimumSize(QSize(0, 27));
        QPalette palette40;
        palette40.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette40.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette40.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnRand->setPalette(palette40);
        m_TbnRand->setFont(font1);

        gridLayout_2->addWidget(m_TbnRand, 5, 0, 1, 1);

        m_TbnRandn = new QToolButton(DlgCalculator);
        m_TbnRandn->setObjectName(QString::fromUtf8("m_TbnRandn"));
        sizePolicy5.setHeightForWidth(m_TbnRandn->sizePolicy().hasHeightForWidth());
        m_TbnRandn->setSizePolicy(sizePolicy5);
        m_TbnRandn->setMinimumSize(QSize(0, 27));
        QPalette palette41;
        palette41.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette41.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette41.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnRandn->setPalette(palette41);
        m_TbnRandn->setFont(font1);

        gridLayout_2->addWidget(m_TbnRandn, 5, 1, 1, 1);

        m_TbnRound = new QToolButton(DlgCalculator);
        m_TbnRound->setObjectName(QString::fromUtf8("m_TbnRound"));
        sizePolicy.setHeightForWidth(m_TbnRound->sizePolicy().hasHeightForWidth());
        m_TbnRound->setSizePolicy(sizePolicy);
        m_TbnRound->setMinimumSize(QSize(0, 0));
        QPalette palette42;
        palette42.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette42.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette42.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnRound->setPalette(palette42);
        m_TbnRound->setFont(font1);

        gridLayout_2->addWidget(m_TbnRound, 1, 2, 1, 1);

        m_TbnAbs = new QToolButton(DlgCalculator);
        m_TbnAbs->setObjectName(QString::fromUtf8("m_TbnAbs"));
        sizePolicy4.setHeightForWidth(m_TbnAbs->sizePolicy().hasHeightForWidth());
        m_TbnAbs->setSizePolicy(sizePolicy4);
        m_TbnAbs->setMinimumSize(QSize(0, 0));
        QPalette palette43;
        palette43.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette43.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette43.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnAbs->setPalette(palette43);
        m_TbnAbs->setFont(font1);

        gridLayout_2->addWidget(m_TbnAbs, 2, 2, 1, 1);

        m_TbnExp = new QToolButton(DlgCalculator);
        m_TbnExp->setObjectName(QString::fromUtf8("m_TbnExp"));
        sizePolicy4.setHeightForWidth(m_TbnExp->sizePolicy().hasHeightForWidth());
        m_TbnExp->setSizePolicy(sizePolicy4);
        QPalette palette44;
        palette44.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette44.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette44.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnExp->setPalette(palette44);
        m_TbnExp->setFont(font1);

        gridLayout_2->addWidget(m_TbnExp, 3, 2, 1, 1);

        m_TbnPow = new QToolButton(DlgCalculator);
        m_TbnPow->setObjectName(QString::fromUtf8("m_TbnPow"));
        sizePolicy4.setHeightForWidth(m_TbnPow->sizePolicy().hasHeightForWidth());
        m_TbnPow->setSizePolicy(sizePolicy4);
        m_TbnPow->setMinimumSize(QSize(0, 0));
        QPalette palette45;
        palette45.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette45.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette45.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnPow->setPalette(palette45);
        m_TbnPow->setFont(font1);

        gridLayout_2->addWidget(m_TbnPow, 4, 2, 1, 1);

        m_TbnSqrt = new QToolButton(DlgCalculator);
        m_TbnSqrt->setObjectName(QString::fromUtf8("m_TbnSqrt"));
        sizePolicy4.setHeightForWidth(m_TbnSqrt->sizePolicy().hasHeightForWidth());
        m_TbnSqrt->setSizePolicy(sizePolicy4);
        QPalette palette46;
        palette46.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette46.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette46.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnSqrt->setPalette(palette46);
        m_TbnSqrt->setFont(font1);

        gridLayout_2->addWidget(m_TbnSqrt, 5, 2, 1, 1);

        m_TbnInt = new QToolButton(DlgCalculator);
        m_TbnInt->setObjectName(QString::fromUtf8("m_TbnInt"));
        sizePolicy4.setHeightForWidth(m_TbnInt->sizePolicy().hasHeightForWidth());
        m_TbnInt->setSizePolicy(sizePolicy4);
        QPalette palette47;
        palette47.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette47.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette47.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnInt->setPalette(palette47);
        m_TbnInt->setFont(font1);

        gridLayout_2->addWidget(m_TbnInt, 1, 3, 1, 1);

        m_TbnLn = new QToolButton(DlgCalculator);
        m_TbnLn->setObjectName(QString::fromUtf8("m_TbnLn"));
        sizePolicy4.setHeightForWidth(m_TbnLn->sizePolicy().hasHeightForWidth());
        m_TbnLn->setSizePolicy(sizePolicy4);
        QPalette palette48;
        palette48.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette48.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette48.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnLn->setPalette(palette48);
        m_TbnLn->setFont(font1);

        gridLayout_2->addWidget(m_TbnLn, 2, 3, 1, 1);

        m_TbnLog = new QToolButton(DlgCalculator);
        m_TbnLog->setObjectName(QString::fromUtf8("m_TbnLog"));
        sizePolicy4.setHeightForWidth(m_TbnLog->sizePolicy().hasHeightForWidth());
        m_TbnLog->setSizePolicy(sizePolicy4);
        QPalette palette49;
        palette49.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette49.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette49.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnLog->setPalette(palette49);
        m_TbnLog->setFont(font1);

        gridLayout_2->addWidget(m_TbnLog, 3, 3, 1, 1);

        m_TbnStd = new QToolButton(DlgCalculator);
        m_TbnStd->setObjectName(QString::fromUtf8("m_TbnStd"));
        sizePolicy5.setHeightForWidth(m_TbnStd->sizePolicy().hasHeightForWidth());
        m_TbnStd->setSizePolicy(sizePolicy5);
        m_TbnStd->setMinimumSize(QSize(0, 27));
        QPalette palette50;
        palette50.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette50.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette50.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnStd->setPalette(palette50);
        m_TbnStd->setFont(font1);

        gridLayout_2->addWidget(m_TbnStd, 2, 4, 1, 1);

        m_TbnNum = new QToolButton(DlgCalculator);
        m_TbnNum->setObjectName(QString::fromUtf8("m_TbnNum"));
        sizePolicy5.setHeightForWidth(m_TbnNum->sizePolicy().hasHeightForWidth());
        m_TbnNum->setSizePolicy(sizePolicy5);
        m_TbnNum->setMinimumSize(QSize(0, 27));
        QPalette palette51;
        palette51.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette51.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette51.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnNum->setPalette(palette51);
        m_TbnNum->setFont(font1);

        gridLayout_2->addWidget(m_TbnNum, 5, 3, 1, 1);

        m_TbnEnter = new QToolButton(DlgCalculator);
        m_TbnEnter->setObjectName(QString::fromUtf8("m_TbnEnter"));
        sizePolicy4.setHeightForWidth(m_TbnEnter->sizePolicy().hasHeightForWidth());
        m_TbnEnter->setSizePolicy(sizePolicy4);
        QPalette palette52;
        palette52.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette52.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette52.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnEnter->setPalette(palette52);
        m_TbnEnter->setFont(font1);

        gridLayout_2->addWidget(m_TbnEnter, 1, 12, 1, 2);

        m_TbnBackSpace = new QToolButton(DlgCalculator);
        m_TbnBackSpace->setObjectName(QString::fromUtf8("m_TbnBackSpace"));
        sizePolicy4.setHeightForWidth(m_TbnBackSpace->sizePolicy().hasHeightForWidth());
        m_TbnBackSpace->setSizePolicy(sizePolicy4);
        QPalette palette53;
        palette53.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette53.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette53.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnBackSpace->setPalette(palette53);
        m_TbnBackSpace->setFont(font1);

        gridLayout_2->addWidget(m_TbnBackSpace, 1, 10, 1, 2);

        m_TbnSum = new QToolButton(DlgCalculator);
        m_TbnSum->setObjectName(QString::fromUtf8("m_TbnSum"));
        sizePolicy5.setHeightForWidth(m_TbnSum->sizePolicy().hasHeightForWidth());
        m_TbnSum->setSizePolicy(sizePolicy5);
        m_TbnSum->setMinimumSize(QSize(0, 27));
        QPalette palette54;
        palette54.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette54.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette54.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        m_TbnSum->setPalette(palette54);
        m_TbnSum->setFont(font1);

        gridLayout_2->addWidget(m_TbnSum, 4, 3, 1, 1);

        label_3 = new QLabel(DlgCalculator);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QPalette palette55;
        palette55.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette55.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette55.setBrush(QPalette::Active, QPalette::ButtonText, brush4);
        palette55.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette55.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette55.setBrush(QPalette::Inactive, QPalette::ButtonText, brush4);
        palette55.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette55.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette55.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        label_3->setPalette(palette55);
        label_3->setFont(font1);

        gridLayout_2->addWidget(label_3, 1, 4, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 4, 0, 1, 2);

        groupBox->raise();
        m_VaribleTree->raise();

        retranslateUi(DlgCalculator);

        QMetaObject::connectSlotsByName(DlgCalculator);
    } // setupUi

    void retranslateUi(QWidget *DlgCalculator)
    {
        DlgCalculator->setWindowTitle(QCoreApplication::translate("DlgCalculator", "Calculator", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnBrowse->setToolTip(QCoreApplication::translate("DlgCalculator", "Browse...", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnBrowse->setText(QCoreApplication::translate("DlgCalculator", "Load from File...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgCalculator", "History", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnClearShowView->setToolTip(QCoreApplication::translate("DlgCalculator", "Clear", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnClearShowView->setText(QCoreApplication::translate("DlgCalculator", "Clear", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnCopy->setToolTip(QCoreApplication::translate("DlgCalculator", "Copy", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnCopy->setText(QCoreApplication::translate("DlgCalculator", "Copy", nullptr));
        groupBox_2->setTitle(QString());
        m_TbnDeg->setText(QCoreApplication::translate("DlgCalculator", "Angle", nullptr));
        m_RdoRad->setText(QCoreApplication::translate("DlgCalculator", "Radian", nullptr));
        m_RdoGrad->setText(QCoreApplication::translate("DlgCalculator", "Grads", nullptr));
        label_4->setText(QCoreApplication::translate("DlgCalculator", "Template:", nullptr));
        m_LblHelp->setText(QCoreApplication::translate("DlgCalculator", "icon", nullptr));
        m_Tbn7->setText(QCoreApplication::translate("DlgCalculator", "7", nullptr));
        m_Tbn8->setText(QCoreApplication::translate("DlgCalculator", "8", nullptr));
        m_Tbn9->setText(QCoreApplication::translate("DlgCalculator", "9", nullptr));
        m_TbnDivide->setText(QCoreApplication::translate("DlgCalculator", "/", nullptr));
        m_TbnLbracket->setText(QCoreApplication::translate("DlgCalculator", "(", nullptr));
        m_TbnRbracket->setText(QCoreApplication::translate("DlgCalculator", ")", nullptr));
        m_TbnClear->setText(QCoreApplication::translate("DlgCalculator", "C", nullptr));
        m_Tbn4->setText(QCoreApplication::translate("DlgCalculator", "4", nullptr));
        m_Tbn5->setText(QCoreApplication::translate("DlgCalculator", "5", nullptr));
        m_Tbn6->setText(QCoreApplication::translate("DlgCalculator", "6", nullptr));
        m_TbnMultiply->setText(QCoreApplication::translate("DlgCalculator", "*", nullptr));
        m_TbnLessthan->setText(QCoreApplication::translate("DlgCalculator", "<", nullptr));
        m_TbnLessAndEqual->setText(QCoreApplication::translate("DlgCalculator", "<=", nullptr));
        m_TbnIf->setText(QCoreApplication::translate("DlgCalculator", "If", nullptr));
        m_Tbn1->setText(QCoreApplication::translate("DlgCalculator", "1", nullptr));
        m_Tbn2->setText(QCoreApplication::translate("DlgCalculator", "2", nullptr));
        m_Tbn3->setText(QCoreApplication::translate("DlgCalculator", "3", nullptr));
        m_TbnSubtract->setText(QCoreApplication::translate("DlgCalculator", "-", nullptr));
        m_TbnMorethan->setText(QCoreApplication::translate("DlgCalculator", ">", nullptr));
        m_TbnMoreAndEqual->setText(QCoreApplication::translate("DlgCalculator", ">=", nullptr));
        m_TbnAnd->setText(QCoreApplication::translate("DlgCalculator", "And", nullptr));
        m_Tbn0->setText(QCoreApplication::translate("DlgCalculator", "0", nullptr));
        m_TbnU->setText(QCoreApplication::translate("DlgCalculator", "Inv", nullptr));
        m_TbnDot->setText(QCoreApplication::translate("DlgCalculator", ".", nullptr));
        m_TbnAddition->setText(QCoreApplication::translate("DlgCalculator", "+", nullptr));
        m_TbnCast->setText(QCoreApplication::translate("DlgCalculator", "<>", nullptr));
        m_TbnEqual->setText(QCoreApplication::translate("DlgCalculator", "=", nullptr));
        m_TbnOr->setText(QCoreApplication::translate("DlgCalculator", "Or", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnMin->setToolTip(QCoreApplication::translate("DlgCalculator", "Min of Grid ", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnMin->setText(QCoreApplication::translate("DlgCalculator", "Min", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnMax->setToolTip(QCoreApplication::translate("DlgCalculator", "Max of Grid ", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnMax->setText(QCoreApplication::translate("DlgCalculator", "Max", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnMean->setToolTip(QCoreApplication::translate("DlgCalculator", "Average of Grid", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnMean->setText(QCoreApplication::translate("DlgCalculator", "Mean", nullptr));
        m_TbnPi->setText(QCoreApplication::translate("DlgCalculator", "Pi", nullptr));
        m_TbnSin->setText(QCoreApplication::translate("DlgCalculator", "Sin", nullptr));
        m_TbnCos->setText(QCoreApplication::translate("DlgCalculator", "Cos", nullptr));
        m_TbnTan->setText(QCoreApplication::translate("DlgCalculator", "Tan", nullptr));
        m_TbnASin->setText(QCoreApplication::translate("DlgCalculator", "Asin", nullptr));
        m_TbnACos->setText(QCoreApplication::translate("DlgCalculator", "Acos", nullptr));
        m_TbnATan->setText(QCoreApplication::translate("DlgCalculator", "Atan", nullptr));
        m_TbnAcTan->setText(QCoreApplication::translate("DlgCalculator", "Actan", nullptr));
        m_TbnCTan->setText(QCoreApplication::translate("DlgCalculator", "Ctan", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnRand->setToolTip(QCoreApplication::translate("DlgCalculator", "Rand Grid of Uniform Distribution between (0,1)", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnRand->setText(QCoreApplication::translate("DlgCalculator", "Rand", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnRandn->setToolTip(QCoreApplication::translate("DlgCalculator", "Rand Grid of Normal Distribution between (0,1)", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnRandn->setText(QCoreApplication::translate("DlgCalculator", "Randn", nullptr));
        m_TbnRound->setText(QCoreApplication::translate("DlgCalculator", "Round", nullptr));
        m_TbnAbs->setText(QCoreApplication::translate("DlgCalculator", "Abs", nullptr));
        m_TbnExp->setText(QCoreApplication::translate("DlgCalculator", "Exp", nullptr));
        m_TbnPow->setText(QCoreApplication::translate("DlgCalculator", "Pow", nullptr));
        m_TbnSqrt->setText(QCoreApplication::translate("DlgCalculator", "Sqrt", nullptr));
        m_TbnInt->setText(QCoreApplication::translate("DlgCalculator", "Int", nullptr));
        m_TbnLn->setText(QCoreApplication::translate("DlgCalculator", "Ln", nullptr));
        m_TbnLog->setText(QCoreApplication::translate("DlgCalculator", "Log", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnStd->setToolTip(QCoreApplication::translate("DlgCalculator", "Standard Deviation of Grid", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnStd->setText(QCoreApplication::translate("DlgCalculator", "Std", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnNum->setToolTip(QCoreApplication::translate("DlgCalculator", "Number of Cells", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnNum->setText(QCoreApplication::translate("DlgCalculator", "Num", nullptr));
        m_TbnEnter->setText(QCoreApplication::translate("DlgCalculator", "    Enter    ", nullptr));
        m_TbnBackSpace->setText(QCoreApplication::translate("DlgCalculator", "Backspace", nullptr));
#if QT_CONFIG(tooltip)
        m_TbnSum->setToolTip(QCoreApplication::translate("DlgCalculator", "Sum of Grid", nullptr));
#endif // QT_CONFIG(tooltip)
        m_TbnSum->setText(QCoreApplication::translate("DlgCalculator", "Sum", nullptr));
        label_3->setText(QCoreApplication::translate("DlgCalculator", "Statistic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgCalculator: public Ui_DlgCalculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XCALCULATOR_H
