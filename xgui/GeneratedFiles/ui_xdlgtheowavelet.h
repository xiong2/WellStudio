/********************************************************************************
** Form generated from reading UI file 'xdlgtheowavelet.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGTHEOWAVELET_H
#define UI_XDLGTHEOWAVELET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "xpagediagram.h"

QT_BEGIN_NAMESPACE

class Ui_XDlgTheoWavelet
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditName;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_5;
    QLineEdit *lineEditSTime;
    QLabel *label_4;
    QLineEdit *lineEditLength;
    QLabel *label_3;
    QLineEdit *lineEditInterval;
    QLabel *labelP1;
    QLineEdit *lineEditP1;
    QLabel *labelP2;
    QLineEdit *lineEditP2;
    QLabel *labelP3;
    QLineEdit *lineEditP3;
    QLabel *labelP4;
    QLineEdit *lineEditP4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    CXPageDiagram *frame;
    QPushButton *pushButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *XDlgTheoWavelet)
    {
        if (XDlgTheoWavelet->objectName().isEmpty())
            XDlgTheoWavelet->setObjectName(QString::fromUtf8("XDlgTheoWavelet"));
        XDlgTheoWavelet->resize(636, 645);
        gridLayout_2 = new QGridLayout(XDlgTheoWavelet);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(XDlgTheoWavelet);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEditName = new QLineEdit(XDlgTheoWavelet);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setMinimumSize(QSize(100, 0));
        lineEditName->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEditName, 0, 1, 1, 1);

        label = new QLabel(XDlgTheoWavelet);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 2, 1, 1);

        comboBox = new QComboBox(XDlgTheoWavelet);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(comboBox, 0, 4, 1, 1);

        label_5 = new QLabel(XDlgTheoWavelet);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        lineEditSTime = new QLineEdit(XDlgTheoWavelet);
        lineEditSTime->setObjectName(QString::fromUtf8("lineEditSTime"));
        lineEditSTime->setMinimumSize(QSize(100, 0));
        lineEditSTime->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEditSTime, 1, 1, 1, 1);

        label_4 = new QLabel(XDlgTheoWavelet);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 2, 1, 1);

        lineEditLength = new QLineEdit(XDlgTheoWavelet);
        lineEditLength->setObjectName(QString::fromUtf8("lineEditLength"));
        lineEditLength->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEditLength, 1, 4, 1, 1);

        label_3 = new QLabel(XDlgTheoWavelet);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(210, 0));
        label_3->setMaximumSize(QSize(210, 16777215));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        lineEditInterval = new QLineEdit(XDlgTheoWavelet);
        lineEditInterval->setObjectName(QString::fromUtf8("lineEditInterval"));
        lineEditInterval->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEditInterval, 2, 1, 1, 1);

        labelP1 = new QLabel(XDlgTheoWavelet);
        labelP1->setObjectName(QString::fromUtf8("labelP1"));
        labelP1->setMinimumSize(QSize(210, 0));
        labelP1->setMaximumSize(QSize(210, 16777215));

        gridLayout_2->addWidget(labelP1, 3, 0, 1, 1);

        lineEditP1 = new QLineEdit(XDlgTheoWavelet);
        lineEditP1->setObjectName(QString::fromUtf8("lineEditP1"));
        lineEditP1->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEditP1, 3, 1, 1, 1);

        labelP2 = new QLabel(XDlgTheoWavelet);
        labelP2->setObjectName(QString::fromUtf8("labelP2"));
        labelP2->setMinimumSize(QSize(210, 0));
        labelP2->setMaximumSize(QSize(210, 16777215));

        gridLayout_2->addWidget(labelP2, 3, 2, 1, 2);

        lineEditP2 = new QLineEdit(XDlgTheoWavelet);
        lineEditP2->setObjectName(QString::fromUtf8("lineEditP2"));
        lineEditP2->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEditP2, 3, 4, 1, 1);

        labelP3 = new QLabel(XDlgTheoWavelet);
        labelP3->setObjectName(QString::fromUtf8("labelP3"));
        labelP3->setMinimumSize(QSize(200, 0));
        labelP3->setMaximumSize(QSize(200, 16777215));

        gridLayout_2->addWidget(labelP3, 4, 0, 1, 1);

        lineEditP3 = new QLineEdit(XDlgTheoWavelet);
        lineEditP3->setObjectName(QString::fromUtf8("lineEditP3"));
        lineEditP3->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEditP3, 4, 1, 1, 1);

        labelP4 = new QLabel(XDlgTheoWavelet);
        labelP4->setObjectName(QString::fromUtf8("labelP4"));
        labelP4->setMinimumSize(QSize(200, 0));
        labelP4->setMaximumSize(QSize(200, 16777215));

        gridLayout_2->addWidget(labelP4, 4, 2, 1, 2);

        lineEditP4 = new QLineEdit(XDlgTheoWavelet);
        lineEditP4->setObjectName(QString::fromUtf8("lineEditP4"));
        lineEditP4->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(lineEditP4, 4, 4, 1, 1);

        groupBox = new QGroupBox(XDlgTheoWavelet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new CXPageDiagram(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 5, 0, 1, 5);

        pushButton = new QPushButton(XDlgTheoWavelet);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 6, 0, 1, 1);

        buttonBox = new QDialogButtonBox(XDlgTheoWavelet);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 6, 3, 1, 2);


        retranslateUi(XDlgTheoWavelet);
        QObject::connect(buttonBox, SIGNAL(accepted()), XDlgTheoWavelet, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), XDlgTheoWavelet, SLOT(reject()));

        QMetaObject::connectSlotsByName(XDlgTheoWavelet);
    } // setupUi

    void retranslateUi(QDialog *XDlgTheoWavelet)
    {
        XDlgTheoWavelet->setWindowTitle(QCoreApplication::translate("XDlgTheoWavelet", "Theoretical Wavelet", nullptr));
        label_2->setText(QCoreApplication::translate("XDlgTheoWavelet", "Output wavelet", nullptr));
        label->setText(QCoreApplication::translate("XDlgTheoWavelet", "Wavlet Type:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("XDlgTheoWavelet", "Ricker", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("XDlgTheoWavelet", "Ormsby", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("XDlgTheoWavelet", "Klauder", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("XDlgTheoWavelet", "Minimum Phase", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("XDlgTheoWavelet", "Wide-band Ricker (Yu's)", nullptr));

        label_5->setText(QCoreApplication::translate("XDlgTheoWavelet", "Start Time (ms)", nullptr));
        lineEditSTime->setText(QCoreApplication::translate("XDlgTheoWavelet", "-200", nullptr));
        label_4->setText(QCoreApplication::translate("XDlgTheoWavelet", "Wavelet Length (ms)", nullptr));
        lineEditLength->setText(QCoreApplication::translate("XDlgTheoWavelet", "401", nullptr));
        label_3->setText(QCoreApplication::translate("XDlgTheoWavelet", "Sample Interval (ms)", nullptr));
        lineEditInterval->setText(QCoreApplication::translate("XDlgTheoWavelet", "1", nullptr));
        labelP1->setText(QCoreApplication::translate("XDlgTheoWavelet", "Low-cut Frequency (Hz)", nullptr));
        labelP2->setText(QCoreApplication::translate("XDlgTheoWavelet", "Low-pass Frequency (Hz)", nullptr));
        labelP3->setText(QCoreApplication::translate("XDlgTheoWavelet", "Lower Limit Dominant Frequency (Hz)", nullptr));
        labelP4->setText(QCoreApplication::translate("XDlgTheoWavelet", "Lower Limit Dominant Frequency (Hz)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("XDlgTheoWavelet", "Preview", nullptr));
        pushButton->setText(QCoreApplication::translate("XDlgTheoWavelet", "Preview", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgTheoWavelet: public Ui_XDlgTheoWavelet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGTHEOWAVELET_H
