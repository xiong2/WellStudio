/********************************************************************************
** Form generated from reading UI file 'xdlgexportsegy.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGEXPORTSEGY_H
#define UI_XDLGEXPORTSEGY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <xsliderlineedit.h>

QT_BEGIN_NAMESPACE

class Ui_CXDlgExportSEGY
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tabRange;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_26;
    QSpinBox *spinBox;
    CXRangeFrame *m_rangeFrame;
    QSpacerItem *verticalSpacer;
    QWidget *tabFormat;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditSEGYFile;
    QPushButton *pushButton;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLineEdit *lineEditHeaderSEGY;
    QPushButton *pushButtonHeaderSEGY;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QComboBox *comboBoxTraceData;
    QLabel *label_5;
    QCheckBox *checkBoxFlipTD;
    QComboBox *comboBoxCoord;
    QLabel *label_3;
    QCheckBox *checkBoxFlipLH;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QCheckBox *checkBoxNanValue;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *CXDlgExportSEGY)
    {
        if (CXDlgExportSEGY->objectName().isEmpty())
            CXDlgExportSEGY->setObjectName(QString::fromUtf8("CXDlgExportSEGY"));
        CXDlgExportSEGY->resize(565, 441);
        gridLayout = new QGridLayout(CXDlgExportSEGY);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(CXDlgExportSEGY);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        tabWidget = new QTabWidget(CXDlgExportSEGY);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabRange = new QWidget();
        tabRange->setObjectName(QString::fromUtf8("tabRange"));
        verticalLayout_2 = new QVBoxLayout(tabRange);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_2 = new QGroupBox(tabRange);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_2->addWidget(label_26, 1, 0, 1, 1);

        spinBox = new QSpinBox(groupBox_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        gridLayout_2->addWidget(spinBox, 1, 1, 1, 1);

        m_rangeFrame = new CXRangeFrame(groupBox_2);
        m_rangeFrame->setObjectName(QString::fromUtf8("m_rangeFrame"));
        m_rangeFrame->setMinimumSize(QSize(0, 40));
        m_rangeFrame->setFrameShape(QFrame::StyledPanel);
        m_rangeFrame->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(m_rangeFrame, 0, 0, 1, 2);


        verticalLayout_2->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tabRange, QString());
        tabFormat = new QWidget();
        tabFormat->setObjectName(QString::fromUtf8("tabFormat"));
        gridLayout_5 = new QGridLayout(tabFormat);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(tabFormat);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditSEGYFile = new QLineEdit(groupBox);
        lineEditSEGYFile->setObjectName(QString::fromUtf8("lineEditSEGYFile"));

        horizontalLayout->addWidget(lineEditSEGYFile);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(tabFormat);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioButton = new QRadioButton(groupBox_3);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        gridLayout_3->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(groupBox_3);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        gridLayout_3->addWidget(radioButton_2, 1, 0, 1, 1);

        lineEditHeaderSEGY = new QLineEdit(groupBox_3);
        lineEditHeaderSEGY->setObjectName(QString::fromUtf8("lineEditHeaderSEGY"));

        gridLayout_3->addWidget(lineEditHeaderSEGY, 1, 1, 1, 1);

        pushButtonHeaderSEGY = new QPushButton(groupBox_3);
        pushButtonHeaderSEGY->setObjectName(QString::fromUtf8("pushButtonHeaderSEGY"));

        gridLayout_3->addWidget(pushButtonHeaderSEGY, 1, 2, 1, 1);

        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(120, 16777215));

        gridLayout_3->addWidget(pushButton_3, 2, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_4 = new QGroupBox(tabFormat);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        comboBoxTraceData = new QComboBox(groupBox_4);
        comboBoxTraceData->addItem(QString());
        comboBoxTraceData->addItem(QString());
        comboBoxTraceData->addItem(QString());
        comboBoxTraceData->addItem(QString());
        comboBoxTraceData->addItem(QString());
        comboBoxTraceData->setObjectName(QString::fromUtf8("comboBoxTraceData"));
        comboBoxTraceData->setMinimumSize(QSize(130, 0));
        comboBoxTraceData->setMaximumSize(QSize(130, 16777215));

        gridLayout_4->addWidget(comboBoxTraceData, 1, 1, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 1, 0, 1, 1);

        checkBoxFlipTD = new QCheckBox(groupBox_4);
        checkBoxFlipTD->setObjectName(QString::fromUtf8("checkBoxFlipTD"));
        checkBoxFlipTD->setChecked(true);

        gridLayout_4->addWidget(checkBoxFlipTD, 1, 2, 1, 1);

        comboBoxCoord = new QComboBox(groupBox_4);
        comboBoxCoord->addItem(QString());
        comboBoxCoord->addItem(QString());
        comboBoxCoord->setObjectName(QString::fromUtf8("comboBoxCoord"));
        comboBoxCoord->setMinimumSize(QSize(130, 0));
        comboBoxCoord->setMaximumSize(QSize(130, 16777215));

        gridLayout_4->addWidget(comboBoxCoord, 2, 1, 1, 1);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 0, 0, 1, 1);

        checkBoxFlipLH = new QCheckBox(groupBox_4);
        checkBoxFlipLH->setObjectName(QString::fromUtf8("checkBoxFlipLH"));
        checkBoxFlipLH->setChecked(true);

        gridLayout_4->addWidget(checkBoxFlipLH, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 2, 0, 1, 1);

        checkBoxNanValue = new QCheckBox(groupBox_4);
        checkBoxNanValue->setObjectName(QString::fromUtf8("checkBoxNanValue"));
        checkBoxNanValue->setChecked(true);

        gridLayout_4->addWidget(checkBoxNanValue, 3, 0, 1, 2);


        gridLayout_5->addWidget(groupBox_4, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_2, 3, 0, 1, 1);

        tabWidget->addTab(tabFormat, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);


        retranslateUi(CXDlgExportSEGY);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CXDlgExportSEGY);
    } // setupUi

    void retranslateUi(QDialog *CXDlgExportSEGY)
    {
        CXDlgExportSEGY->setWindowTitle(QCoreApplication::translate("CXDlgExportSEGY", "CXDlgExportSEGY", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXDlgExportSEGY", "Output Range", nullptr));
        label_26->setText(QCoreApplication::translate("CXDlgExportSEGY", "Sample Interval:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabRange), QCoreApplication::translate("CXDlgExportSEGY", "Data Range", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXDlgExportSEGY", "Output File", nullptr));
        label->setText(QCoreApplication::translate("CXDlgExportSEGY", "SEGY File Name:", nullptr));
        pushButton->setText(QCoreApplication::translate("CXDlgExportSEGY", "...", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CXDlgExportSEGY", "SEGY Header Info", nullptr));
        radioButton->setText(QCoreApplication::translate("CXDlgExportSEGY", "Calculate from Data", nullptr));
        radioButton_2->setText(QCoreApplication::translate("CXDlgExportSEGY", "Copy from Specified SEGY File:", nullptr));
        pushButtonHeaderSEGY->setText(QCoreApplication::translate("CXDlgExportSEGY", "...", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CXDlgExportSEGY", "EBCDIC Header...", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("CXDlgExportSEGY", "Data Format", nullptr));
        comboBoxTraceData->setItemText(0, QCoreApplication::translate("CXDlgExportSEGY", "32-bit IEEE Float", nullptr));
        comboBoxTraceData->setItemText(1, QCoreApplication::translate("CXDlgExportSEGY", "32-bit IBM Float", nullptr));
        comboBoxTraceData->setItemText(2, QCoreApplication::translate("CXDlgExportSEGY", "32-bit Integer", nullptr));
        comboBoxTraceData->setItemText(3, QCoreApplication::translate("CXDlgExportSEGY", "16-bit Integer", nullptr));
        comboBoxTraceData->setItemText(4, QCoreApplication::translate("CXDlgExportSEGY", "8-bit Integer", nullptr));

        label_5->setText(QCoreApplication::translate("CXDlgExportSEGY", "Trace Data", nullptr));
        checkBoxFlipTD->setText(QCoreApplication::translate("CXDlgExportSEGY", "Flip Bytes", nullptr));
        comboBoxCoord->setItemText(0, QCoreApplication::translate("CXDlgExportSEGY", "Integer", nullptr));
        comboBoxCoord->setItemText(1, QCoreApplication::translate("CXDlgExportSEGY", "Float", nullptr));

        label_3->setText(QCoreApplication::translate("CXDlgExportSEGY", "Line Header:", nullptr));
        checkBoxFlipLH->setText(QCoreApplication::translate("CXDlgExportSEGY", "Flip Bytes", nullptr));
        label_7->setText(QCoreApplication::translate("CXDlgExportSEGY", "Coordinate:", nullptr));
        checkBoxNanValue->setText(QCoreApplication::translate("CXDlgExportSEGY", "Export invalid values as zero", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabFormat), QCoreApplication::translate("CXDlgExportSEGY", "Data Format", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgExportSEGY: public Ui_CXDlgExportSEGY {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGEXPORTSEGY_H
