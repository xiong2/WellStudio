/********************************************************************************
** Form generated from reading UI file 'xpageloadsegydatastep2.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGELOADSEGYDATASTEP2_H
#define UI_XPAGELOADSEGYDATASTEP2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <xtableforascii.h>

QT_BEGIN_NAMESPACE

class Ui_loadsegystep2
{
public:
    QGridLayout *gridLayout_4;
    QLabel *labelAzimuth;
    QLineEdit *lineEditAzimuth;
    QLineEdit *lineEditOffset;
    QLabel *labelOffset;
    QCheckBox *checkBoxIrreOffset;
    QLineEdit *m_EdtCrossLine;
    QPushButton *m_PtnTreadCancel;
    QLabel *labelInline;
    QComboBox *comboBoxSEGYType;
    QFrame *line;
    QLabel *label_12;
    QProgressBar *m_PrbScanProbar;
    QLabel *label;
    QLineEdit *m_EdtInline;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QLineEdit *m_EdtStartLine;
    QLabel *label_10;
    QLineEdit *m_EdtEndLine;
    QLabel *label_9;
    QGroupBox *groupBoxAzimuth;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QRadioButton *radioButtonNorth;
    QRadioButton *radioButtonEast;
    QLabel *label_11;
    QRadioButton *radioButtonCW;
    QRadioButton *radioButtonCCW;
    QGroupBox *m_GrpTraceHeader;
    QGridLayout *gridLayout_3;
    QLabel *m_LblTraceTotal;
    QSlider *m_SldTrace;
    QSpinBox *m_SpxCurrTrace;
    QTabWidget *m_TabTrace;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QCheckBox *m_ChkAscIIFlip;
    CXTableForLoadSegy *m_TbAscIIView;
    QLabel *label_2;
    QRadioButton *m_RdoFormatIEEE;
    QRadioButton *m_RdoFormatIBM;
    QSpacerItem *horizontalSpacer;
    QGroupBox *m_GrpCoordnateFrom;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLineEdit *m_EdtFileDX;
    QLineEdit *m_EdtFileY;
    QLabel *labelDX;
    QCheckBox *m_ChkOverrideXYScale;
    QCheckBox *m_ChkWithoutZoneNumber;
    QRadioButton *m_RdoInput3Points;
    QLabel *labelDY;
    QLabel *labelDE;
    QLineEdit *m_EdtFileDY;
    QRadioButton *m_RdoScanSegyFile;
    QLabel *labelSE;
    QLabel *labelX;
    QComboBox *m_CmbXyUnit;
    QLineEdit *m_EdtFileDE;
    QLineEdit *m_EdtOverrideScaleValue;
    QLabel *labelY;
    QLineEdit *m_EdtFileX;
    QLineEdit *m_EdtFileSE;
    QLabel *labelFB;
    QLineEdit *m_EdtFileFB;
    QLabel *labelCrossline;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *loadsegystep2)
    {
        if (loadsegystep2->objectName().isEmpty())
            loadsegystep2->setObjectName(QString::fromUtf8("loadsegystep2"));
        loadsegystep2->resize(850, 596);
        gridLayout_4 = new QGridLayout(loadsegystep2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        labelAzimuth = new QLabel(loadsegystep2);
        labelAzimuth->setObjectName(QString::fromUtf8("labelAzimuth"));
        labelAzimuth->setMinimumSize(QSize(60, 0));

        gridLayout_4->addWidget(labelAzimuth, 4, 4, 1, 1);

        lineEditAzimuth = new QLineEdit(loadsegystep2);
        lineEditAzimuth->setObjectName(QString::fromUtf8("lineEditAzimuth"));
        lineEditAzimuth->setMinimumSize(QSize(70, 0));
        lineEditAzimuth->setMaximumSize(QSize(70, 16777215));

        gridLayout_4->addWidget(lineEditAzimuth, 4, 5, 1, 1);

        lineEditOffset = new QLineEdit(loadsegystep2);
        lineEditOffset->setObjectName(QString::fromUtf8("lineEditOffset"));
        lineEditOffset->setMinimumSize(QSize(70, 0));
        lineEditOffset->setMaximumSize(QSize(70, 16777215));

        gridLayout_4->addWidget(lineEditOffset, 4, 2, 1, 1);

        labelOffset = new QLabel(loadsegystep2);
        labelOffset->setObjectName(QString::fromUtf8("labelOffset"));
        labelOffset->setMinimumSize(QSize(60, 0));

        gridLayout_4->addWidget(labelOffset, 4, 1, 1, 1);

        checkBoxIrreOffset = new QCheckBox(loadsegystep2);
        checkBoxIrreOffset->setObjectName(QString::fromUtf8("checkBoxIrreOffset"));

        gridLayout_4->addWidget(checkBoxIrreOffset, 5, 4, 1, 2);

        m_EdtCrossLine = new QLineEdit(loadsegystep2);
        m_EdtCrossLine->setObjectName(QString::fromUtf8("m_EdtCrossLine"));
        m_EdtCrossLine->setMinimumSize(QSize(70, 0));
        m_EdtCrossLine->setMaximumSize(QSize(70, 16777215));

        gridLayout_4->addWidget(m_EdtCrossLine, 3, 5, 1, 1);

        m_PtnTreadCancel = new QPushButton(loadsegystep2);
        m_PtnTreadCancel->setObjectName(QString::fromUtf8("m_PtnTreadCancel"));

        gridLayout_4->addWidget(m_PtnTreadCancel, 10, 5, 1, 1);

        labelInline = new QLabel(loadsegystep2);
        labelInline->setObjectName(QString::fromUtf8("labelInline"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelInline->sizePolicy().hasHeightForWidth());
        labelInline->setSizePolicy(sizePolicy);
        labelInline->setMinimumSize(QSize(60, 0));
        labelInline->setLayoutDirection(Qt::RightToLeft);

        gridLayout_4->addWidget(labelInline, 3, 1, 1, 1);

        comboBoxSEGYType = new QComboBox(loadsegystep2);
        comboBoxSEGYType->addItem(QString());
        comboBoxSEGYType->addItem(QString());
        comboBoxSEGYType->addItem(QString());
        comboBoxSEGYType->addItem(QString());
        comboBoxSEGYType->setObjectName(QString::fromUtf8("comboBoxSEGYType"));

        gridLayout_4->addWidget(comboBoxSEGYType, 2, 3, 1, 3);

        line = new QFrame(loadsegystep2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setLineWidth(1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line, 1, 0, 1, 6);

        label_12 = new QLabel(loadsegystep2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_4->addWidget(label_12, 2, 1, 1, 2);

        m_PrbScanProbar = new QProgressBar(loadsegystep2);
        m_PrbScanProbar->setObjectName(QString::fromUtf8("m_PrbScanProbar"));
        m_PrbScanProbar->setValue(0);

        gridLayout_4->addWidget(m_PrbScanProbar, 10, 1, 1, 2);

        label = new QLabel(loadsegystep2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        m_EdtInline = new QLineEdit(loadsegystep2);
        m_EdtInline->setObjectName(QString::fromUtf8("m_EdtInline"));
        m_EdtInline->setMinimumSize(QSize(70, 0));
        m_EdtInline->setMaximumSize(QSize(70, 16777215));

        gridLayout_4->addWidget(m_EdtInline, 3, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 67, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 9, 3, 1, 1);

        groupBox = new QGroupBox(loadsegystep2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        m_EdtStartLine = new QLineEdit(groupBox);
        m_EdtStartLine->setObjectName(QString::fromUtf8("m_EdtStartLine"));
        m_EdtStartLine->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_6->addWidget(m_EdtStartLine, 0, 0, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setLayoutDirection(Qt::RightToLeft);

        gridLayout_6->addWidget(label_10, 0, 1, 1, 1);

        m_EdtEndLine = new QLineEdit(groupBox);
        m_EdtEndLine->setObjectName(QString::fromUtf8("m_EdtEndLine"));
        m_EdtEndLine->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_6->addWidget(m_EdtEndLine, 0, 2, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(25, 25));
        label_9->setMaximumSize(QSize(25, 25));

        gridLayout_6->addWidget(label_9, 0, 3, 1, 1);


        gridLayout_4->addWidget(groupBox, 7, 1, 1, 5);

        groupBoxAzimuth = new QGroupBox(loadsegystep2);
        groupBoxAzimuth->setObjectName(QString::fromUtf8("groupBoxAzimuth"));
        gridLayout = new QGridLayout(groupBoxAzimuth);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBoxAzimuth);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        radioButtonNorth = new QRadioButton(groupBoxAzimuth);
        buttonGroup = new QButtonGroup(loadsegystep2);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButtonNorth);
        radioButtonNorth->setObjectName(QString::fromUtf8("radioButtonNorth"));
        radioButtonNorth->setChecked(true);

        gridLayout->addWidget(radioButtonNorth, 0, 1, 1, 1);

        radioButtonEast = new QRadioButton(groupBoxAzimuth);
        buttonGroup->addButton(radioButtonEast);
        radioButtonEast->setObjectName(QString::fromUtf8("radioButtonEast"));
        radioButtonEast->setChecked(false);

        gridLayout->addWidget(radioButtonEast, 0, 2, 1, 1);

        label_11 = new QLabel(groupBoxAzimuth);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 1, 0, 1, 1);

        radioButtonCW = new QRadioButton(groupBoxAzimuth);
        radioButtonCW->setObjectName(QString::fromUtf8("radioButtonCW"));
        radioButtonCW->setChecked(true);

        gridLayout->addWidget(radioButtonCW, 1, 1, 1, 1);

        radioButtonCCW = new QRadioButton(groupBoxAzimuth);
        radioButtonCCW->setObjectName(QString::fromUtf8("radioButtonCCW"));
        radioButtonCCW->setChecked(false);

        gridLayout->addWidget(radioButtonCCW, 1, 2, 1, 1);


        gridLayout_4->addWidget(groupBoxAzimuth, 8, 1, 1, 5);

        m_GrpTraceHeader = new QGroupBox(loadsegystep2);
        m_GrpTraceHeader->setObjectName(QString::fromUtf8("m_GrpTraceHeader"));
        gridLayout_3 = new QGridLayout(m_GrpTraceHeader);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_LblTraceTotal = new QLabel(m_GrpTraceHeader);
        m_LblTraceTotal->setObjectName(QString::fromUtf8("m_LblTraceTotal"));

        gridLayout_3->addWidget(m_LblTraceTotal, 1, 0, 1, 1);

        m_SldTrace = new QSlider(m_GrpTraceHeader);
        m_SldTrace->setObjectName(QString::fromUtf8("m_SldTrace"));
        m_SldTrace->setOrientation(Qt::Horizontal);
        m_SldTrace->setTickPosition(QSlider::NoTicks);

        gridLayout_3->addWidget(m_SldTrace, 2, 0, 1, 1);

        m_SpxCurrTrace = new QSpinBox(m_GrpTraceHeader);
        m_SpxCurrTrace->setObjectName(QString::fromUtf8("m_SpxCurrTrace"));
        m_SpxCurrTrace->setMinimum(1);

        gridLayout_3->addWidget(m_SpxCurrTrace, 2, 1, 1, 1);

        m_TabTrace = new QTabWidget(m_GrpTraceHeader);
        m_TabTrace->setObjectName(QString::fromUtf8("m_TabTrace"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_ChkAscIIFlip = new QCheckBox(tab_2);
        m_ChkAscIIFlip->setObjectName(QString::fromUtf8("m_ChkAscIIFlip"));
        m_ChkAscIIFlip->setLayoutDirection(Qt::LeftToRight);

        gridLayout_5->addWidget(m_ChkAscIIFlip, 0, 0, 1, 2);

        m_TbAscIIView = new CXTableForLoadSegy(tab_2);
        if (m_TbAscIIView->columnCount() < 4)
            m_TbAscIIView->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_TbAscIIView->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_TbAscIIView->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_TbAscIIView->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        m_TbAscIIView->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        m_TbAscIIView->setObjectName(QString::fromUtf8("m_TbAscIIView"));
        m_TbAscIIView->horizontalHeader()->setStretchLastSection(true);

        gridLayout_5->addWidget(m_TbAscIIView, 2, 0, 1, 6);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_5->addWidget(label_2, 0, 2, 1, 1);

        m_RdoFormatIEEE = new QRadioButton(tab_2);
        m_RdoFormatIEEE->setObjectName(QString::fromUtf8("m_RdoFormatIEEE"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_RdoFormatIEEE->sizePolicy().hasHeightForWidth());
        m_RdoFormatIEEE->setSizePolicy(sizePolicy1);
        m_RdoFormatIEEE->setChecked(true);

        gridLayout_5->addWidget(m_RdoFormatIEEE, 0, 3, 1, 1);

        m_RdoFormatIBM = new QRadioButton(tab_2);
        m_RdoFormatIBM->setObjectName(QString::fromUtf8("m_RdoFormatIBM"));

        gridLayout_5->addWidget(m_RdoFormatIBM, 0, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 5, 1, 1);

        m_TabTrace->addTab(tab_2, QString());

        gridLayout_3->addWidget(m_TabTrace, 0, 0, 1, 3);


        gridLayout_4->addWidget(m_GrpTraceHeader, 2, 0, 8, 1);

        m_GrpCoordnateFrom = new QGroupBox(loadsegystep2);
        m_GrpCoordnateFrom->setObjectName(QString::fromUtf8("m_GrpCoordnateFrom"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_GrpCoordnateFrom->sizePolicy().hasHeightForWidth());
        m_GrpCoordnateFrom->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(m_GrpCoordnateFrom);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_8 = new QLabel(m_GrpCoordnateFrom);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(label_8, 8, 0, 1, 2);

        m_EdtFileDX = new QLineEdit(m_GrpCoordnateFrom);
        m_EdtFileDX->setObjectName(QString::fromUtf8("m_EdtFileDX"));
        m_EdtFileDX->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFileDX, 5, 1, 1, 1);

        m_EdtFileY = new QLineEdit(m_GrpCoordnateFrom);
        m_EdtFileY->setObjectName(QString::fromUtf8("m_EdtFileY"));
        m_EdtFileY->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFileY, 2, 3, 1, 1);

        labelDX = new QLabel(m_GrpCoordnateFrom);
        labelDX->setObjectName(QString::fromUtf8("labelDX"));
        sizePolicy.setHeightForWidth(labelDX->sizePolicy().hasHeightForWidth());
        labelDX->setSizePolicy(sizePolicy);
        labelDX->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(labelDX, 5, 0, 1, 1);

        m_ChkOverrideXYScale = new QCheckBox(m_GrpCoordnateFrom);
        m_ChkOverrideXYScale->setObjectName(QString::fromUtf8("m_ChkOverrideXYScale"));
        sizePolicy1.setHeightForWidth(m_ChkOverrideXYScale->sizePolicy().hasHeightForWidth());
        m_ChkOverrideXYScale->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_ChkOverrideXYScale, 9, 0, 1, 3);

        m_ChkWithoutZoneNumber = new QCheckBox(m_GrpCoordnateFrom);
        m_ChkWithoutZoneNumber->setObjectName(QString::fromUtf8("m_ChkWithoutZoneNumber"));
        m_ChkWithoutZoneNumber->setChecked(true);

        gridLayout_2->addWidget(m_ChkWithoutZoneNumber, 10, 0, 1, 3);

        m_RdoInput3Points = new QRadioButton(m_GrpCoordnateFrom);
        m_RdoInput3Points->setObjectName(QString::fromUtf8("m_RdoInput3Points"));
        sizePolicy1.setHeightForWidth(m_RdoInput3Points->sizePolicy().hasHeightForWidth());
        m_RdoInput3Points->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(m_RdoInput3Points, 0, 0, 1, 3);

        labelDY = new QLabel(m_GrpCoordnateFrom);
        labelDY->setObjectName(QString::fromUtf8("labelDY"));
        sizePolicy1.setHeightForWidth(labelDY->sizePolicy().hasHeightForWidth());
        labelDY->setSizePolicy(sizePolicy1);
        labelDY->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(labelDY, 5, 2, 1, 1);

        labelDE = new QLabel(m_GrpCoordnateFrom);
        labelDE->setObjectName(QString::fromUtf8("labelDE"));
        sizePolicy1.setHeightForWidth(labelDE->sizePolicy().hasHeightForWidth());
        labelDE->setSizePolicy(sizePolicy1);
        labelDE->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(labelDE, 6, 2, 1, 1);

        m_EdtFileDY = new QLineEdit(m_GrpCoordnateFrom);
        m_EdtFileDY->setObjectName(QString::fromUtf8("m_EdtFileDY"));
        m_EdtFileDY->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFileDY, 5, 3, 1, 1);

        m_RdoScanSegyFile = new QRadioButton(m_GrpCoordnateFrom);
        m_RdoScanSegyFile->setObjectName(QString::fromUtf8("m_RdoScanSegyFile"));
        sizePolicy1.setHeightForWidth(m_RdoScanSegyFile->sizePolicy().hasHeightForWidth());
        m_RdoScanSegyFile->setSizePolicy(sizePolicy1);
        m_RdoScanSegyFile->setChecked(true);

        gridLayout_2->addWidget(m_RdoScanSegyFile, 1, 0, 1, 3);

        labelSE = new QLabel(m_GrpCoordnateFrom);
        labelSE->setObjectName(QString::fromUtf8("labelSE"));
        sizePolicy.setHeightForWidth(labelSE->sizePolicy().hasHeightForWidth());
        labelSE->setSizePolicy(sizePolicy);
        labelSE->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(labelSE, 6, 0, 1, 1);

        labelX = new QLabel(m_GrpCoordnateFrom);
        labelX->setObjectName(QString::fromUtf8("labelX"));
        sizePolicy.setHeightForWidth(labelX->sizePolicy().hasHeightForWidth());
        labelX->setSizePolicy(sizePolicy);
        labelX->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(labelX, 2, 0, 1, 1);

        m_CmbXyUnit = new QComboBox(m_GrpCoordnateFrom);
        m_CmbXyUnit->addItem(QString());
        m_CmbXyUnit->addItem(QString());
        m_CmbXyUnit->setObjectName(QString::fromUtf8("m_CmbXyUnit"));

        gridLayout_2->addWidget(m_CmbXyUnit, 8, 3, 1, 1);

        m_EdtFileDE = new QLineEdit(m_GrpCoordnateFrom);
        m_EdtFileDE->setObjectName(QString::fromUtf8("m_EdtFileDE"));
        m_EdtFileDE->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFileDE, 6, 3, 1, 1);

        m_EdtOverrideScaleValue = new QLineEdit(m_GrpCoordnateFrom);
        m_EdtOverrideScaleValue->setObjectName(QString::fromUtf8("m_EdtOverrideScaleValue"));
        m_EdtOverrideScaleValue->setEnabled(false);
        m_EdtOverrideScaleValue->setMaximumSize(QSize(700, 16777215));

        gridLayout_2->addWidget(m_EdtOverrideScaleValue, 9, 3, 1, 2);

        labelY = new QLabel(m_GrpCoordnateFrom);
        labelY->setObjectName(QString::fromUtf8("labelY"));
        sizePolicy1.setHeightForWidth(labelY->sizePolicy().hasHeightForWidth());
        labelY->setSizePolicy(sizePolicy1);
        labelY->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(labelY, 2, 2, 1, 1);

        m_EdtFileX = new QLineEdit(m_GrpCoordnateFrom);
        m_EdtFileX->setObjectName(QString::fromUtf8("m_EdtFileX"));
        m_EdtFileX->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFileX, 2, 1, 1, 1);

        m_EdtFileSE = new QLineEdit(m_GrpCoordnateFrom);
        m_EdtFileSE->setObjectName(QString::fromUtf8("m_EdtFileSE"));
        m_EdtFileSE->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFileSE, 6, 1, 1, 1);

        labelFB = new QLabel(m_GrpCoordnateFrom);
        labelFB->setObjectName(QString::fromUtf8("labelFB"));
        sizePolicy.setHeightForWidth(labelFB->sizePolicy().hasHeightForWidth());
        labelFB->setSizePolicy(sizePolicy);
        labelFB->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(labelFB, 7, 0, 1, 1);

        m_EdtFileFB = new QLineEdit(m_GrpCoordnateFrom);
        m_EdtFileFB->setObjectName(QString::fromUtf8("m_EdtFileFB"));
        m_EdtFileFB->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFileFB, 7, 1, 1, 1);


        gridLayout_4->addWidget(m_GrpCoordnateFrom, 6, 1, 1, 5);

        labelCrossline = new QLabel(loadsegystep2);
        labelCrossline->setObjectName(QString::fromUtf8("labelCrossline"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelCrossline->sizePolicy().hasHeightForWidth());
        labelCrossline->setSizePolicy(sizePolicy3);
        labelCrossline->setLayoutDirection(Qt::RightToLeft);

        gridLayout_4->addWidget(labelCrossline, 3, 4, 1, 1);

        QWidget::setTabOrder(m_TabTrace, m_ChkAscIIFlip);
        QWidget::setTabOrder(m_ChkAscIIFlip, m_RdoFormatIEEE);
        QWidget::setTabOrder(m_RdoFormatIEEE, m_RdoFormatIBM);
        QWidget::setTabOrder(m_RdoFormatIBM, m_TbAscIIView);
        QWidget::setTabOrder(m_TbAscIIView, m_SldTrace);
        QWidget::setTabOrder(m_SldTrace, m_SpxCurrTrace);
        QWidget::setTabOrder(m_SpxCurrTrace, m_RdoInput3Points);
        QWidget::setTabOrder(m_RdoInput3Points, m_RdoScanSegyFile);
        QWidget::setTabOrder(m_RdoScanSegyFile, m_EdtInline);
        QWidget::setTabOrder(m_EdtInline, m_ChkOverrideXYScale);
        QWidget::setTabOrder(m_ChkOverrideXYScale, m_EdtOverrideScaleValue);

        retranslateUi(loadsegystep2);

        m_TabTrace->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(loadsegystep2);
    } // setupUi

    void retranslateUi(QWidget *loadsegystep2)
    {
        loadsegystep2->setWindowTitle(QCoreApplication::translate("loadsegystep2", "Form", nullptr));
        labelAzimuth->setText(QCoreApplication::translate("loadsegystep2", "Azimuth:", nullptr));
        labelOffset->setText(QCoreApplication::translate("loadsegystep2", "Offset:", nullptr));
        checkBoxIrreOffset->setText(QCoreApplication::translate("loadsegystep2", "Irregular Offsets", nullptr));
        m_PtnTreadCancel->setText(QCoreApplication::translate("loadsegystep2", "Abort", nullptr));
        labelInline->setText(QCoreApplication::translate("loadsegystep2", "Inline: ", nullptr));
        comboBoxSEGYType->setItemText(0, QCoreApplication::translate("loadsegystep2", "3-D Poststack Data Volume", nullptr));
        comboBoxSEGYType->setItemText(1, QCoreApplication::translate("loadsegystep2", "3-D Prestack Data Volume", nullptr));
        comboBoxSEGYType->setItemText(2, QCoreApplication::translate("loadsegystep2", "3-D Prestack Azimuth Data Volume", nullptr));
        comboBoxSEGYType->setItemText(3, QCoreApplication::translate("loadsegystep2", "Prestack Gather", nullptr));

        label_12->setText(QCoreApplication::translate("loadsegystep2", "Seismic File Type:", nullptr));
        label->setText(QCoreApplication::translate("loadsegystep2", "Step 2 of 4: Preview Trace Header", nullptr));
        groupBox->setTitle(QCoreApplication::translate("loadsegystep2", "Valid  Range of Inline/Xline Numbers", nullptr));
        label_10->setText(QCoreApplication::translate("loadsegystep2", "to", nullptr));
#if QT_CONFIG(tooltip)
        label_9->setToolTip(QCoreApplication::translate("loadsegystep2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Any trace with inline or xline number beyond the valid range will be regarded as dead trace. You can edit the value of the range to accommodate a specific SEG-Y file.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_9->setText(QCoreApplication::translate("loadsegystep2", "?", nullptr));
        groupBoxAzimuth->setTitle(QCoreApplication::translate("loadsegystep2", "Azimuth Setting", nullptr));
        label_4->setText(QCoreApplication::translate("loadsegystep2", "Starting corner:", nullptr));
        radioButtonNorth->setText(QCoreApplication::translate("loadsegystep2", "North", nullptr));
        radioButtonEast->setText(QCoreApplication::translate("loadsegystep2", "East", nullptr));
        label_11->setText(QCoreApplication::translate("loadsegystep2", "Rotation direction:", nullptr));
        radioButtonCW->setText(QCoreApplication::translate("loadsegystep2", "Clockwise", nullptr));
        radioButtonCCW->setText(QCoreApplication::translate("loadsegystep2", "Counterclockwise", nullptr));
        m_GrpTraceHeader->setTitle(QCoreApplication::translate("loadsegystep2", "Trace Header", nullptr));
        m_LblTraceTotal->setText(QCoreApplication::translate("loadsegystep2", "Current Trace (Total: 112875)", nullptr));
        m_ChkAscIIFlip->setText(QCoreApplication::translate("loadsegystep2", "Flip Bytes", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_TbAscIIView->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("loadsegystep2", "Bytes", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_TbAscIIView->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("loadsegystep2", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_TbAscIIView->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("loadsegystep2", "Format", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = m_TbAscIIView->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("loadsegystep2", "Value", nullptr));
        label_2->setText(QCoreApplication::translate("loadsegystep2", "Float Format:", nullptr));
        m_RdoFormatIEEE->setText(QCoreApplication::translate("loadsegystep2", "IEEE", nullptr));
        m_RdoFormatIBM->setText(QCoreApplication::translate("loadsegystep2", "IBM", nullptr));
        m_TabTrace->setTabText(m_TabTrace->indexOf(tab_2), QCoreApplication::translate("loadsegystep2", "ASCII", nullptr));
        m_GrpCoordnateFrom->setTitle(QCoreApplication::translate("loadsegystep2", "Coordinate from", nullptr));
        label_8->setText(QCoreApplication::translate("loadsegystep2", "X, Y Unit:", nullptr));
        labelDX->setText(QCoreApplication::translate("loadsegystep2", "Detector X:", nullptr));
        m_ChkOverrideXYScale->setText(QCoreApplication::translate("loadsegystep2", "Override X, Y Scale:   ", nullptr));
        m_ChkWithoutZoneNumber->setText(QCoreApplication::translate("loadsegystep2", "Without the zone number", nullptr));
        m_RdoInput3Points->setText(QCoreApplication::translate("loadsegystep2", "Input 3 Points", nullptr));
        labelDY->setText(QCoreApplication::translate("loadsegystep2", "Detector Y:", nullptr));
        labelDE->setText(QCoreApplication::translate("loadsegystep2", "Detector Elev:", nullptr));
        m_RdoScanSegyFile->setText(QCoreApplication::translate("loadsegystep2", "Scan SEG-Y File:", nullptr));
        labelSE->setText(QCoreApplication::translate("loadsegystep2", "Source Elev:", nullptr));
        labelX->setText(QCoreApplication::translate("loadsegystep2", "X:", nullptr));
        m_CmbXyUnit->setItemText(0, QCoreApplication::translate("loadsegystep2", "meter", nullptr));
        m_CmbXyUnit->setItemText(1, QCoreApplication::translate("loadsegystep2", "ft", nullptr));

        m_EdtOverrideScaleValue->setText(QString());
        labelY->setText(QCoreApplication::translate("loadsegystep2", "Y:", nullptr));
        labelFB->setText(QCoreApplication::translate("loadsegystep2", "First Break:", nullptr));
        labelCrossline->setText(QCoreApplication::translate("loadsegystep2", "Crossline:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loadsegystep2: public Ui_loadsegystep2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGELOADSEGYDATASTEP2_H
