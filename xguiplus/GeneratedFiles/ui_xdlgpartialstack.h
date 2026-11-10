/********************************************************************************
** Form generated from reading UI file 'xdlgpartialstack.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGPARTIALSTACK_H
#define UI_XDLGPARTIALSTACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include "xslidercomplex.h"

QT_BEGIN_NAMESPACE

class Ui_CXDlgPartialStack
{
public:
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *labelOriDVName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditOutputDV;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBoxSampleInterval;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_3;
    CXSliderComplex *m_sliderInline;
    CXSliderComplex *m_sliderXline;
    CXSliderComplex *m_sliderTime;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    QSpinBox *spinBoxInlineRolling;
    QLabel *label_9;
    QSpinBox *spinBoxCrosslineRolling;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioButtonAzimuth;
    QRadioButton *radioButtonOffset;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButtonStackOffset;
    QRadioButton *radioButtonStackAzimuth;
    QRadioButton *radioButtonStackBoth;
    QGroupBox *groupBoxOffset;
    QGridLayout *gridLayout;
    QLabel *labelOffsetBins;
    QLabel *label_10;
    QSpinBox *spinBoxOffsetBinNumber;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidgetOffset;
    QGroupBox *groupBoxAzimuth;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidgetAzimuth;
    QCheckBox *checkBox;
    QSpinBox *spinBoxAzimuthRangeNumber;
    QLabel *label_11;
    QLabel *labelAzimuthRanges;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *CXDlgPartialStack)
    {
        if (CXDlgPartialStack->objectName().isEmpty())
            CXDlgPartialStack->setObjectName(QString::fromUtf8("CXDlgPartialStack"));
        CXDlgPartialStack->resize(807, 780);
        gridLayout_5 = new QGridLayout(CXDlgPartialStack);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(CXDlgPartialStack);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        labelOriDVName = new QLabel(CXDlgPartialStack);
        labelOriDVName->setObjectName(QString::fromUtf8("labelOriDVName"));

        horizontalLayout_3->addWidget(labelOriDVName);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(CXDlgPartialStack);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEditOutputDV = new QLineEdit(CXDlgPartialStack);
        lineEditOutputDV->setObjectName(QString::fromUtf8("lineEditOutputDV"));

        horizontalLayout_2->addWidget(lineEditOutputDV);


        gridLayout_5->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(CXDlgPartialStack);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinBoxSampleInterval = new QSpinBox(groupBox);
        spinBoxSampleInterval->setObjectName(QString::fromUtf8("spinBoxSampleInterval"));
        spinBoxSampleInterval->setMinimum(1);
        spinBoxSampleInterval->setMaximum(32);

        gridLayout_2->addWidget(spinBoxSampleInterval, 3, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 3, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(224, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 3, 2, 1, 1);

        m_sliderInline = new CXSliderComplex(groupBox);
        m_sliderInline->setObjectName(QString::fromUtf8("m_sliderInline"));

        gridLayout_2->addWidget(m_sliderInline, 0, 0, 1, 3);

        m_sliderXline = new CXSliderComplex(groupBox);
        m_sliderXline->setObjectName(QString::fromUtf8("m_sliderXline"));

        gridLayout_2->addWidget(m_sliderXline, 1, 0, 1, 3);

        m_sliderTime = new CXSliderComplex(groupBox);
        m_sliderTime->setObjectName(QString::fromUtf8("m_sliderTime"));

        gridLayout_2->addWidget(m_sliderTime, 2, 0, 1, 3);


        gridLayout_5->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(CXDlgPartialStack);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout->addWidget(label_8);

        spinBoxInlineRolling = new QSpinBox(groupBox_2);
        spinBoxInlineRolling->setObjectName(QString::fromUtf8("spinBoxInlineRolling"));
        spinBoxInlineRolling->setMinimum(1);
        spinBoxInlineRolling->setMaximum(9);
        spinBoxInlineRolling->setSingleStep(2);

        horizontalLayout->addWidget(spinBoxInlineRolling);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);

        spinBoxCrosslineRolling = new QSpinBox(groupBox_2);
        spinBoxCrosslineRolling->setObjectName(QString::fromUtf8("spinBoxCrosslineRolling"));
        spinBoxCrosslineRolling->setMinimum(1);
        spinBoxCrosslineRolling->setMaximum(9);
        spinBoxCrosslineRolling->setSingleStep(2);

        horizontalLayout->addWidget(spinBoxCrosslineRolling);


        gridLayout_5->addWidget(groupBox_2, 3, 0, 1, 1);

        groupBox_3 = new QGroupBox(CXDlgPartialStack);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        radioButtonAzimuth = new QRadioButton(groupBox_4);
        buttonGroup = new QButtonGroup(CXDlgPartialStack);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButtonAzimuth);
        radioButtonAzimuth->setObjectName(QString::fromUtf8("radioButtonAzimuth"));

        horizontalLayout_5->addWidget(radioButtonAzimuth);

        radioButtonOffset = new QRadioButton(groupBox_4);
        buttonGroup->addButton(radioButtonOffset);
        radioButtonOffset->setObjectName(QString::fromUtf8("radioButtonOffset"));
        radioButtonOffset->setChecked(true);

        horizontalLayout_5->addWidget(radioButtonOffset);


        gridLayout_4->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioButtonStackOffset = new QRadioButton(groupBox_5);
        radioButtonStackOffset->setObjectName(QString::fromUtf8("radioButtonStackOffset"));

        horizontalLayout_4->addWidget(radioButtonStackOffset);

        radioButtonStackAzimuth = new QRadioButton(groupBox_5);
        radioButtonStackAzimuth->setObjectName(QString::fromUtf8("radioButtonStackAzimuth"));

        horizontalLayout_4->addWidget(radioButtonStackAzimuth);

        radioButtonStackBoth = new QRadioButton(groupBox_5);
        radioButtonStackBoth->setObjectName(QString::fromUtf8("radioButtonStackBoth"));
        radioButtonStackBoth->setChecked(true);

        horizontalLayout_4->addWidget(radioButtonStackBoth);


        gridLayout_4->addWidget(groupBox_5, 0, 1, 1, 1);

        groupBoxOffset = new QGroupBox(groupBox_3);
        groupBoxOffset->setObjectName(QString::fromUtf8("groupBoxOffset"));
        gridLayout = new QGridLayout(groupBoxOffset);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelOffsetBins = new QLabel(groupBoxOffset);
        labelOffsetBins->setObjectName(QString::fromUtf8("labelOffsetBins"));

        gridLayout->addWidget(labelOffsetBins, 0, 0, 1, 3);

        label_10 = new QLabel(groupBoxOffset);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        spinBoxOffsetBinNumber = new QSpinBox(groupBoxOffset);
        spinBoxOffsetBinNumber->setObjectName(QString::fromUtf8("spinBoxOffsetBinNumber"));
        spinBoxOffsetBinNumber->setMinimum(1);
        spinBoxOffsetBinNumber->setMaximum(1000);
        spinBoxOffsetBinNumber->setValue(10);

        gridLayout->addWidget(spinBoxOffsetBinNumber, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(185, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        tableWidgetOffset = new QTableWidget(groupBoxOffset);
        if (tableWidgetOffset->columnCount() < 3)
            tableWidgetOffset->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetOffset->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetOffset->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetOffset->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidgetOffset->rowCount() < 10)
            tableWidgetOffset->setRowCount(10);
        tableWidgetOffset->setObjectName(QString::fromUtf8("tableWidgetOffset"));
        tableWidgetOffset->setRowCount(10);

        gridLayout->addWidget(tableWidgetOffset, 2, 0, 1, 3);


        gridLayout_4->addWidget(groupBoxOffset, 1, 0, 1, 1);

        groupBoxAzimuth = new QGroupBox(groupBox_3);
        groupBoxAzimuth->setObjectName(QString::fromUtf8("groupBoxAzimuth"));
        gridLayout_3 = new QGridLayout(groupBoxAzimuth);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableWidgetAzimuth = new QTableWidget(groupBoxAzimuth);
        if (tableWidgetAzimuth->columnCount() < 3)
            tableWidgetAzimuth->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetAzimuth->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetAzimuth->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetAzimuth->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        if (tableWidgetAzimuth->rowCount() < 6)
            tableWidgetAzimuth->setRowCount(6);
        tableWidgetAzimuth->setObjectName(QString::fromUtf8("tableWidgetAzimuth"));
        tableWidgetAzimuth->setRowCount(6);

        gridLayout_3->addWidget(tableWidgetAzimuth, 2, 0, 1, 3);

        checkBox = new QCheckBox(groupBoxAzimuth);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout_3->addWidget(checkBox, 1, 2, 1, 1);

        spinBoxAzimuthRangeNumber = new QSpinBox(groupBoxAzimuth);
        spinBoxAzimuthRangeNumber->setObjectName(QString::fromUtf8("spinBoxAzimuthRangeNumber"));
        spinBoxAzimuthRangeNumber->setMinimum(1);
        spinBoxAzimuthRangeNumber->setMaximum(36);
        spinBoxAzimuthRangeNumber->setValue(6);

        gridLayout_3->addWidget(spinBoxAzimuthRangeNumber, 1, 1, 1, 1);

        label_11 = new QLabel(groupBoxAzimuth);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 1, 0, 1, 1);

        labelAzimuthRanges = new QLabel(groupBoxAzimuth);
        labelAzimuthRanges->setObjectName(QString::fromUtf8("labelAzimuthRanges"));

        gridLayout_3->addWidget(labelAzimuthRanges, 0, 0, 1, 3);


        gridLayout_4->addWidget(groupBoxAzimuth, 1, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(CXDlgPartialStack);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_5->addWidget(buttonBox, 5, 0, 1, 1);


        retranslateUi(CXDlgPartialStack);
        QObject::connect(buttonBox, SIGNAL(rejected()), CXDlgPartialStack, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), CXDlgPartialStack, SLOT(accept()));

        QMetaObject::connectSlotsByName(CXDlgPartialStack);
    } // setupUi

    void retranslateUi(QDialog *CXDlgPartialStack)
    {
        CXDlgPartialStack->setWindowTitle(QCoreApplication::translate("CXDlgPartialStack", "CXDlgPartialStack", nullptr));
        label->setText(QCoreApplication::translate("CXDlgPartialStack", "Input volume:", nullptr));
        labelOriDVName->setText(QCoreApplication::translate("CXDlgPartialStack", "XXX", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgPartialStack", "Output volume:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXDlgPartialStack", "Output range", nullptr));
        label_7->setText(QCoreApplication::translate("CXDlgPartialStack", "Sample Interval:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXDlgPartialStack", "Rolling window", nullptr));
        label_8->setText(QCoreApplication::translate("CXDlgPartialStack", "Inlines", nullptr));
        label_9->setText(QCoreApplication::translate("CXDlgPartialStack", "Crosslines", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CXDlgPartialStack", "Common offset/azimuth gathers", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("CXDlgPartialStack", "Sort by", nullptr));
        radioButtonAzimuth->setText(QCoreApplication::translate("CXDlgPartialStack", "Azimuth and Offset", nullptr));
        radioButtonOffset->setText(QCoreApplication::translate("CXDlgPartialStack", "Offset and Azimuth", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("CXDlgPartialStack", "Stack by", nullptr));
        radioButtonStackOffset->setText(QCoreApplication::translate("CXDlgPartialStack", "Offset", nullptr));
        radioButtonStackAzimuth->setText(QCoreApplication::translate("CXDlgPartialStack", "Azimuth", nullptr));
        radioButtonStackBoth->setText(QCoreApplication::translate("CXDlgPartialStack", "Both", nullptr));
        groupBoxOffset->setTitle(QCoreApplication::translate("CXDlgPartialStack", "Offsets", nullptr));
        labelOffsetBins->setText(QCoreApplication::translate("CXDlgPartialStack", "The offset range from", nullptr));
        label_10->setText(QCoreApplication::translate("CXDlgPartialStack", "Number of offset bins:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetOffset->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CXDlgPartialStack", "Start Offset", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetOffset->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CXDlgPartialStack", "End Offset", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetOffset->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CXDlgPartialStack", "Output Offset", nullptr));
        groupBoxAzimuth->setTitle(QCoreApplication::translate("CXDlgPartialStack", "Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetAzimuth->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CXDlgPartialStack", "Start Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetAzimuth->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CXDlgPartialStack", "End Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetAzimuth->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("CXDlgPartialStack", "Output Azimuth", nullptr));
        checkBox->setText(QCoreApplication::translate("CXDlgPartialStack", "Bidirectional azimuth", nullptr));
        label_11->setText(QCoreApplication::translate("CXDlgPartialStack", "Number of azimuth ranges:", nullptr));
        labelAzimuthRanges->setText(QCoreApplication::translate("CXDlgPartialStack", "The azimuth range from ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgPartialStack: public Ui_CXDlgPartialStack {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGPARTIALSTACK_H
