/********************************************************************************
** Form generated from reading UI file 'xdlgsegydataformat.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGSEGYDATAFORMAT_H
#define UI_XDLGSEGYDATAFORMAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXDlgSEGYDataFormat
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditSampleNum;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_3;
    QCheckBox *checkBox;
    QLineEdit *lineEditInterval;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QRadioButton *radioButtonWiggle;
    QRadioButton *radioButtonHisto;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *labelTraceNum;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;

    void setupUi(QDialog *CXDlgSEGYDataFormat)
    {
        if (CXDlgSEGYDataFormat->objectName().isEmpty())
            CXDlgSEGYDataFormat->setObjectName(QString::fromUtf8("CXDlgSEGYDataFormat"));
        CXDlgSEGYDataFormat->resize(652, 434);
        gridLayout = new QGridLayout(CXDlgSEGYDataFormat);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(CXDlgSEGYDataFormat);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 3, 0, 1, 2);

        buttonBox = new QDialogButtonBox(CXDlgSEGYDataFormat);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 3, 1, 1);

        lineEditSampleNum = new QLineEdit(CXDlgSEGYDataFormat);
        lineEditSampleNum->setObjectName(QString::fromUtf8("lineEditSampleNum"));
        lineEditSampleNum->setEnabled(false);

        gridLayout->addWidget(lineEditSampleNum, 0, 3, 1, 1);

        label_2 = new QLabel(CXDlgSEGYDataFormat);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        comboBox = new QComboBox(CXDlgSEGYDataFormat);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label = new QLabel(CXDlgSEGYDataFormat);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(CXDlgSEGYDataFormat);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        checkBox = new QCheckBox(CXDlgSEGYDataFormat);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 1, 0, 1, 2);

        lineEditInterval = new QLineEdit(CXDlgSEGYDataFormat);
        lineEditInterval->setObjectName(QString::fromUtf8("lineEditInterval"));
        lineEditInterval->setEnabled(false);

        gridLayout->addWidget(lineEditInterval, 1, 3, 1, 1);

        groupBox = new QGroupBox(CXDlgSEGYDataFormat);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 200));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        radioButtonWiggle = new QRadioButton(groupBox);
        radioButtonWiggle->setObjectName(QString::fromUtf8("radioButtonWiggle"));
        radioButtonWiggle->setChecked(true);

        horizontalLayout_2->addWidget(radioButtonWiggle);

        radioButtonHisto = new QRadioButton(groupBox);
        radioButtonHisto->setObjectName(QString::fromUtf8("radioButtonHisto"));

        horizontalLayout_2->addWidget(radioButtonHisto);

        horizontalSpacer = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        labelTraceNum = new QLabel(groupBox);
        labelTraceNum->setObjectName(QString::fromUtf8("labelTraceNum"));

        horizontalLayout->addWidget(labelTraceNum);

        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addWidget(groupBox, 2, 0, 1, 4);


        retranslateUi(CXDlgSEGYDataFormat);

        QMetaObject::connectSlotsByName(CXDlgSEGYDataFormat);
    } // setupUi

    void retranslateUi(QDialog *CXDlgSEGYDataFormat)
    {
        CXDlgSEGYDataFormat->setWindowTitle(QCoreApplication::translate("CXDlgSEGYDataFormat", "CXDlgSEGYDataFormat", nullptr));
        pushButton->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "OK for All", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "Samples per Trace", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("CXDlgSEGYDataFormat", "4-byte IEEE float", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("CXDlgSEGYDataFormat", "4-byte IBM float", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("CXDlgSEGYDataFormat", "4-byte integer", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("CXDlgSEGYDataFormat", "2-byte integer", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("CXDlgSEGYDataFormat", "character", nullptr));

        label->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "Data Format", nullptr));
        label_3->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "Samples Interval", nullptr));
        checkBox->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "Flip Bytes", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXDlgSEGYDataFormat", "Trace Preview", nullptr));
        label_5->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "Display Model", nullptr));
        radioButtonWiggle->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "Wiggle", nullptr));
        radioButtonHisto->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "Histogram", nullptr));
        labelTraceNum->setText(QCoreApplication::translate("CXDlgSEGYDataFormat", "Total Traces: 1000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgSEGYDataFormat: public Ui_CXDlgSEGYDataFormat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGSEGYDATAFORMAT_H
