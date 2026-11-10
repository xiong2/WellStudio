/********************************************************************************
** Form generated from reading UI file 'xdlgwelltie.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGWELLTIE_H
#define UI_XDLGWELLTIE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include <xslidercomplex.h>
#include "xframecorrelation.h"
#include "xframewtcorner.h"
#include "xscrollarea.h"

QT_BEGIN_NAMESPACE

class Ui_CXDlgWellTie
{
public:
    QGridLayout *gridLayout_3;
    QScrollBar *verticalScrollBar;
    QScrollBar *horizontalScrollBar;
    CXScrollArea *scrollAreaRight;
    QWidget *scrollAreaWidgetContents_4;
    CXFrameWTCorner *frameTL;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    CXFrameCorrelation *frame;
    CXSliderComplex *slideRangeWindow;
    QLabel *label_5;
    QSpinBox *spinBox;
    QPushButton *pushButtonApply;
    CXFrameWTCorner *frameTR;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QComboBox *comboBoxDV;
    QLineEdit *lineEditLength;
    QRadioButton *radioButtonTrace;
    QLabel *label_4;
    QLabel *label;
    QComboBox *comboBoxAC;
    QLabel *label_2;
    QLabel *labelWavelet;
    QLabel *label_3;
    QPushButton *pushButtonWavelet;
    QComboBox *comboBoxDEN;
    QRadioButton *radioButtonTree;
    QLineEdit *lineEditWavelet;
    QSpacerItem *verticalSpacer;
    CXScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    CXScrollArea *scrollAreaLeft;
    QWidget *scrollAreaWidgetContents_3;
    QScrollArea *scrollAreaTop;
    QWidget *scrollAreaWidgetContents;
    QLabel *labelMessage;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonUndo;
    QPushButton *pushButtonStr;
    QPushButton *pushButtonLast;
    QLabel *label_7;
    QComboBox *comboBoxSnap;
    QPushButton *pushButton;
    QPushButton *pushButtonCal;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonRedo;
    QPushButton *pushButtonAll;
    QPushButton *pushButtonLayout;
    QLineEdit *lineEdit;
    QLabel *label_6;

    void setupUi(QDialog *CXDlgWellTie)
    {
        if (CXDlgWellTie->objectName().isEmpty())
            CXDlgWellTie->setObjectName(QString::fromUtf8("CXDlgWellTie"));
        CXDlgWellTie->resize(1344, 796);
        gridLayout_3 = new QGridLayout(CXDlgWellTie);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalScrollBar = new QScrollBar(CXDlgWellTie);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setOrientation(Qt::Vertical);

        gridLayout_3->addWidget(verticalScrollBar, 1, 3, 6, 1);

        horizontalScrollBar = new QScrollBar(CXDlgWellTie);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(horizontalScrollBar, 8, 1, 1, 1);

        scrollAreaRight = new CXScrollArea(CXDlgWellTie);
        scrollAreaRight->setObjectName(QString::fromUtf8("scrollAreaRight"));
        scrollAreaRight->setMaximumSize(QSize(60, 16777215));
        scrollAreaRight->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaRight->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaRight->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 58, 643));
        scrollAreaRight->setWidget(scrollAreaWidgetContents_4);

        gridLayout_3->addWidget(scrollAreaRight, 1, 2, 6, 1);

        frameTL = new CXFrameWTCorner(CXDlgWellTie);
        frameTL->setObjectName(QString::fromUtf8("frameTL"));
        frameTL->setFrameShape(QFrame::StyledPanel);
        frameTL->setFrameShadow(QFrame::Raised);

        gridLayout_3->addWidget(frameTL, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(CXDlgWellTie);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        frame = new CXFrameCorrelation(groupBox_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 200));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(frame, 0, 0, 1, 3);

        slideRangeWindow = new CXSliderComplex(groupBox_2);
        slideRangeWindow->setObjectName(QString::fromUtf8("slideRangeWindow"));

        gridLayout_2->addWidget(slideRangeWindow, 1, 0, 1, 3);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        spinBox = new QSpinBox(groupBox_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(20);
        spinBox->setMaximum(500);
        spinBox->setSingleStep(10);
        spinBox->setValue(100);

        gridLayout_2->addWidget(spinBox, 2, 1, 1, 1);

        pushButtonApply = new QPushButton(groupBox_2);
        pushButtonApply->setObjectName(QString::fromUtf8("pushButtonApply"));
        pushButtonApply->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Flush.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonApply->setIcon(icon);

        gridLayout_2->addWidget(pushButtonApply, 2, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 3, 4, 1, 4);

        frameTR = new CXFrameWTCorner(CXDlgWellTie);
        frameTR->setObjectName(QString::fromUtf8("frameTR"));
        frameTR->setFrameShape(QFrame::StyledPanel);
        frameTR->setFrameShadow(QFrame::Raised);

        gridLayout_3->addWidget(frameTR, 0, 2, 1, 1);

        groupBox = new QGroupBox(CXDlgWellTie);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(400, 0));
        groupBox->setMaximumSize(QSize(600, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBoxDV = new QComboBox(groupBox);
        comboBoxDV->setObjectName(QString::fromUtf8("comboBoxDV"));

        gridLayout->addWidget(comboBoxDV, 0, 1, 1, 3);

        lineEditLength = new QLineEdit(groupBox);
        lineEditLength->setObjectName(QString::fromUtf8("lineEditLength"));
        lineEditLength->setEnabled(false);

        gridLayout->addWidget(lineEditLength, 6, 3, 1, 1);

        radioButtonTrace = new QRadioButton(groupBox);
        radioButtonTrace->setObjectName(QString::fromUtf8("radioButtonTrace"));
        radioButtonTrace->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(radioButtonTrace, 6, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        comboBoxAC = new QComboBox(groupBox);
        comboBoxAC->setObjectName(QString::fromUtf8("comboBoxAC"));

        gridLayout->addWidget(comboBoxAC, 1, 1, 1, 3);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        labelWavelet = new QLabel(groupBox);
        labelWavelet->setObjectName(QString::fromUtf8("labelWavelet"));
        labelWavelet->setEnabled(false);

        gridLayout->addWidget(labelWavelet, 6, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pushButtonWavelet = new QPushButton(groupBox);
        pushButtonWavelet->setObjectName(QString::fromUtf8("pushButtonWavelet"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonWavelet->setIcon(icon1);

        gridLayout->addWidget(pushButtonWavelet, 5, 2, 1, 1);

        comboBoxDEN = new QComboBox(groupBox);
        comboBoxDEN->setObjectName(QString::fromUtf8("comboBoxDEN"));

        gridLayout->addWidget(comboBoxDEN, 2, 1, 1, 3);

        radioButtonTree = new QRadioButton(groupBox);
        radioButtonTree->setObjectName(QString::fromUtf8("radioButtonTree"));
        radioButtonTree->setChecked(true);

        gridLayout->addWidget(radioButtonTree, 5, 0, 1, 1);

        lineEditWavelet = new QLineEdit(groupBox);
        lineEditWavelet->setObjectName(QString::fromUtf8("lineEditWavelet"));
        lineEditWavelet->setReadOnly(true);

        gridLayout->addWidget(lineEditWavelet, 5, 3, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 4, 3, 4);

        verticalSpacer = new QSpacerItem(20, 635, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 6, 6, 1, 1);

        scrollArea = new CXScrollArea(CXDlgWellTie);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 737, 643));
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_3->addWidget(scrollArea, 1, 1, 6, 1);

        scrollAreaLeft = new CXScrollArea(CXDlgWellTie);
        scrollAreaLeft->setObjectName(QString::fromUtf8("scrollAreaLeft"));
        scrollAreaLeft->setMaximumSize(QSize(60, 16777215));
        scrollAreaLeft->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaLeft->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 58, 643));
        scrollAreaLeft->setWidget(scrollAreaWidgetContents_3);

        gridLayout_3->addWidget(scrollAreaLeft, 1, 0, 6, 1);

        scrollAreaTop = new QScrollArea(CXDlgWellTie);
        scrollAreaTop->setObjectName(QString::fromUtf8("scrollAreaTop"));
        scrollAreaTop->setMaximumSize(QSize(16777215, 100));
        scrollAreaTop->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaTop->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaTop->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 737, 98));
        scrollAreaTop->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollAreaTop, 0, 1, 1, 1);

        labelMessage = new QLabel(CXDlgWellTie);
        labelMessage->setObjectName(QString::fromUtf8("labelMessage"));

        gridLayout_3->addWidget(labelMessage, 7, 4, 1, 4);

        groupBox_3 = new QGroupBox(CXDlgWellTie);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 150));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButtonSave = new QPushButton(groupBox_3);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setEnabled(false);
        pushButtonSave->setMinimumSize(QSize(100, 24));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonSave->setIcon(icon2);

        gridLayout_4->addWidget(pushButtonSave, 3, 3, 1, 1);

        pushButtonUndo = new QPushButton(groupBox_3);
        pushButtonUndo->setObjectName(QString::fromUtf8("pushButtonUndo"));
        pushButtonUndo->setEnabled(false);
        pushButtonUndo->setMinimumSize(QSize(80, 24));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/Undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonUndo->setIcon(icon3);

        gridLayout_4->addWidget(pushButtonUndo, 3, 0, 1, 1);

        pushButtonStr = new QPushButton(groupBox_3);
        pushButtonStr->setObjectName(QString::fromUtf8("pushButtonStr"));
        pushButtonStr->setEnabled(false);
        pushButtonStr->setMinimumSize(QSize(100, 24));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/WellTie.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonStr->setIcon(icon4);

        gridLayout_4->addWidget(pushButtonStr, 1, 0, 1, 1);

        pushButtonLast = new QPushButton(groupBox_3);
        pushButtonLast->setObjectName(QString::fromUtf8("pushButtonLast"));
        pushButtonLast->setEnabled(false);
        pushButtonLast->setMinimumSize(QSize(100, 24));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonLast->setIcon(icon5);

        gridLayout_4->addWidget(pushButtonLast, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);

        comboBoxSnap = new QComboBox(groupBox_3);
        comboBoxSnap->addItem(QString());
        comboBoxSnap->addItem(QString());
        comboBoxSnap->addItem(QString());
        comboBoxSnap->addItem(QString());
        comboBoxSnap->setObjectName(QString::fromUtf8("comboBoxSnap"));

        gridLayout_4->addWidget(comboBoxSnap, 1, 3, 1, 1);

        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(60, 24));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon6);

        gridLayout_4->addWidget(pushButton, 5, 3, 1, 1);

        pushButtonCal = new QPushButton(groupBox_3);
        pushButtonCal->setObjectName(QString::fromUtf8("pushButtonCal"));
        pushButtonCal->setMinimumSize(QSize(100, 0));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icon/Calculator.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCal->setIcon(icon7);

        gridLayout_4->addWidget(pushButtonCal, 5, 2, 1, 1);

        pushButtonReset = new QPushButton(groupBox_3);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        pushButtonReset->setEnabled(false);
        pushButtonReset->setMinimumSize(QSize(100, 0));
        pushButtonReset->setIcon(icon);

        gridLayout_4->addWidget(pushButtonReset, 5, 1, 1, 1);

        pushButtonRedo = new QPushButton(groupBox_3);
        pushButtonRedo->setObjectName(QString::fromUtf8("pushButtonRedo"));
        pushButtonRedo->setEnabled(false);
        pushButtonRedo->setMinimumSize(QSize(100, 24));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icon/Redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRedo->setIcon(icon8);

        gridLayout_4->addWidget(pushButtonRedo, 5, 0, 1, 1);

        pushButtonAll = new QPushButton(groupBox_3);
        pushButtonAll->setObjectName(QString::fromUtf8("pushButtonAll"));
        pushButtonAll->setEnabled(false);
        pushButtonAll->setMinimumSize(QSize(100, 24));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Icon/DisSelectAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAll->setIcon(icon9);

        gridLayout_4->addWidget(pushButtonAll, 3, 1, 1, 1);

        pushButtonLayout = new QPushButton(groupBox_3);
        pushButtonLayout->setObjectName(QString::fromUtf8("pushButtonLayout"));
        pushButtonLayout->setMinimumSize(QSize(100, 24));
        pushButtonLayout->setMaximumSize(QSize(100, 16777215));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Icon/Logview32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonLayout->setIcon(icon10);

        gridLayout_4->addWidget(pushButtonLayout, 3, 2, 1, 1);

        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_4->addWidget(lineEdit, 0, 1, 1, 2);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_6, 1, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 4, 4, 1, 4);


        retranslateUi(CXDlgWellTie);
        QObject::connect(pushButton, SIGNAL(clicked()), CXDlgWellTie, SLOT(accept()));

        QMetaObject::connectSlotsByName(CXDlgWellTie);
    } // setupUi

    void retranslateUi(QDialog *CXDlgWellTie)
    {
        CXDlgWellTie->setWindowTitle(QCoreApplication::translate("CXDlgWellTie", "CXDlgWellTie", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXDlgWellTie", "Correlation Analysis", nullptr));
        label_5->setText(QCoreApplication::translate("CXDlgWellTie", "Time shift window", nullptr));
        pushButtonApply->setText(QCoreApplication::translate("CXDlgWellTie", "Apply", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXDlgWellTie", "Synthetic Parameters", nullptr));
        lineEditLength->setText(QCoreApplication::translate("CXDlgWellTie", "51", nullptr));
        radioButtonTrace->setText(QCoreApplication::translate("CXDlgWellTie", "Extract from seismic trace nearby", nullptr));
        label_4->setText(QCoreApplication::translate("CXDlgWellTie", "Wavelet:", nullptr));
        label->setText(QCoreApplication::translate("CXDlgWellTie", "AC Curve:", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgWellTie", "3D Seismic Volume:", nullptr));
        labelWavelet->setText(QCoreApplication::translate("CXDlgWellTie", "wavelet length:", nullptr));
        label_3->setText(QCoreApplication::translate("CXDlgWellTie", "Density Curvey:", nullptr));
        pushButtonWavelet->setText(QString());
        radioButtonTree->setText(QCoreApplication::translate("CXDlgWellTie", "Select from Data Tree", nullptr));
        labelMessage->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("CXDlgWellTie", "Operations", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("CXDlgWellTie", "Save", nullptr));
        pushButtonUndo->setText(QCoreApplication::translate("CXDlgWellTie", "Undo Stretch", nullptr));
        pushButtonStr->setText(QCoreApplication::translate("CXDlgWellTie", "Stretch", nullptr));
        pushButtonLast->setText(QCoreApplication::translate("CXDlgWellTie", "Clear Last Pick", nullptr));
        label_7->setText(QCoreApplication::translate("CXDlgWellTie", "Output TD Name:", nullptr));
        comboBoxSnap->setItemText(0, QCoreApplication::translate("CXDlgWellTie", "Peak or Trough", nullptr));
        comboBoxSnap->setItemText(1, QCoreApplication::translate("CXDlgWellTie", "Peak", nullptr));
        comboBoxSnap->setItemText(2, QCoreApplication::translate("CXDlgWellTie", "Trough", nullptr));
        comboBoxSnap->setItemText(3, QCoreApplication::translate("CXDlgWellTie", "None", nullptr));

        pushButton->setText(QCoreApplication::translate("CXDlgWellTie", "Close", nullptr));
        pushButtonCal->setText(QCoreApplication::translate("CXDlgWellTie", "Calculate", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("CXDlgWellTie", "Reset", nullptr));
        pushButtonRedo->setText(QCoreApplication::translate("CXDlgWellTie", "Redo Stretch", nullptr));
        pushButtonAll->setText(QCoreApplication::translate("CXDlgWellTie", "Clear All Picks", nullptr));
        pushButtonLayout->setText(QCoreApplication::translate("CXDlgWellTie", "Layout", nullptr));
        label_6->setText(QCoreApplication::translate("CXDlgWellTie", "Snap to", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgWellTie: public Ui_CXDlgWellTie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGWELLTIE_H
