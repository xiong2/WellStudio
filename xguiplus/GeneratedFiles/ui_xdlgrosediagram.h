/********************************************************************************
** Form generated from reading UI file 'xdlgrosediagram.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGROSEDIAGRAM_H
#define UI_XDLGROSEDIAGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xbuttoncoloredit.h"
#include "xcanvasrosediagram.h"
#include "xcolormapcombo.h"

QT_BEGIN_NAMESPACE

class Ui_CXDlgRoseDiagram
{
public:
    QGridLayout *gridLayout;
    CXCanvasRoseDiagram *frame;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxRose;
    QCheckBox *checkBoxGrid;
    QCheckBox *checkBoxBins;
    QCheckBox *checkBoxHisto;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpinBox *spinBoxRose;
    QLabel *label_4;
    QLineEdit *lineEditStartAzi;
    QLabel *label_5;
    QLineEdit *lineEditEndAzi;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *spinBoxBins;
    QLabel *labelOffset;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonRefresh;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    CXButtonColorEdit *pushButtonRoseColor;
    QLabel *label_7;
    QSlider *horizontalSlider;
    QLineEdit *lineEditOpancity;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    CXButtonColorEdit *pushButtonGridColor;
    QLabel *label_8;
    CXColormapCombo *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *CXDlgRoseDiagram)
    {
        if (CXDlgRoseDiagram->objectName().isEmpty())
            CXDlgRoseDiagram->setObjectName(QString::fromUtf8("CXDlgRoseDiagram"));
        CXDlgRoseDiagram->resize(545, 727);
        gridLayout = new QGridLayout(CXDlgRoseDiagram);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new CXCanvasRoseDiagram(CXDlgRoseDiagram);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(320, 320));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame, 0, 0, 1, 3);

        groupBox = new QGroupBox(CXDlgRoseDiagram);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxRose = new QCheckBox(groupBox);
        checkBoxRose->setObjectName(QString::fromUtf8("checkBoxRose"));
        checkBoxRose->setMinimumSize(QSize(80, 0));
        checkBoxRose->setMaximumSize(QSize(80, 16777215));
        checkBoxRose->setChecked(true);

        horizontalLayout->addWidget(checkBoxRose);

        checkBoxGrid = new QCheckBox(groupBox);
        checkBoxGrid->setObjectName(QString::fromUtf8("checkBoxGrid"));
        checkBoxGrid->setMinimumSize(QSize(80, 0));
        checkBoxGrid->setMaximumSize(QSize(80, 16777215));
        checkBoxGrid->setChecked(true);

        horizontalLayout->addWidget(checkBoxGrid);

        checkBoxBins = new QCheckBox(groupBox);
        checkBoxBins->setObjectName(QString::fromUtf8("checkBoxBins"));
        checkBoxBins->setMinimumSize(QSize(80, 0));
        checkBoxBins->setMaximumSize(QSize(80, 16777215));
        checkBoxBins->setChecked(true);

        horizontalLayout->addWidget(checkBoxBins);

        checkBoxHisto = new QCheckBox(groupBox);
        checkBoxHisto->setObjectName(QString::fromUtf8("checkBoxHisto"));
        checkBoxHisto->setMinimumSize(QSize(80, 0));
        checkBoxHisto->setMaximumSize(QSize(80, 16777215));
        checkBoxHisto->setChecked(true);

        horizontalLayout->addWidget(checkBoxHisto);

        horizontalSpacer_2 = new QSpacerItem(73, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        spinBoxRose = new QSpinBox(groupBox);
        spinBoxRose->setObjectName(QString::fromUtf8("spinBoxRose"));
        spinBoxRose->setMaximumSize(QSize(40, 16777215));
        spinBoxRose->setMinimum(6);
        spinBoxRose->setMaximum(72);
        spinBoxRose->setSingleStep(2);
        spinBoxRose->setValue(36);

        horizontalLayout_2->addWidget(spinBoxRose);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEditStartAzi = new QLineEdit(groupBox);
        lineEditStartAzi->setObjectName(QString::fromUtf8("lineEditStartAzi"));
        lineEditStartAzi->setMinimumSize(QSize(40, 0));
        lineEditStartAzi->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(lineEditStartAzi);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lineEditEndAzi = new QLineEdit(groupBox);
        lineEditEndAzi->setObjectName(QString::fromUtf8("lineEditEndAzi"));
        lineEditEndAzi->setMinimumSize(QSize(40, 0));
        lineEditEndAzi->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(lineEditEndAzi);

        horizontalSpacer_3 = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        spinBoxBins = new QSpinBox(groupBox);
        spinBoxBins->setObjectName(QString::fromUtf8("spinBoxBins"));
        spinBoxBins->setMaximumSize(QSize(40, 16777215));
        spinBoxBins->setMinimum(5);
        spinBoxBins->setMaximum(40);
        spinBoxBins->setValue(20);

        horizontalLayout_3->addWidget(spinBoxBins);

        labelOffset = new QLabel(groupBox);
        labelOffset->setObjectName(QString::fromUtf8("labelOffset"));

        horizontalLayout_3->addWidget(labelOffset);

        horizontalSpacer_4 = new QSpacerItem(13, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        pushButtonRefresh = new QPushButton(groupBox);
        pushButtonRefresh->setObjectName(QString::fromUtf8("pushButtonRefresh"));

        horizontalLayout_3->addWidget(pushButtonRefresh);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addWidget(groupBox, 1, 0, 1, 3);

        groupBox_2 = new QGroupBox(CXDlgRoseDiagram);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(80, 0));
        label_6->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(label_6);

        pushButtonRoseColor = new CXButtonColorEdit(groupBox_2);
        pushButtonRoseColor->setObjectName(QString::fromUtf8("pushButtonRoseColor"));
        pushButtonRoseColor->setMinimumSize(QSize(75, 0));
        pushButtonRoseColor->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_4->addWidget(pushButtonRoseColor);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        horizontalSlider = new QSlider(groupBox_2);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setValue(153);
        horizontalSlider->setSliderPosition(153);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider);

        lineEditOpancity = new QLineEdit(groupBox_2);
        lineEditOpancity->setObjectName(QString::fromUtf8("lineEditOpancity"));
        lineEditOpancity->setMinimumSize(QSize(40, 0));
        lineEditOpancity->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(lineEditOpancity);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(80, 0));
        label_9->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_5->addWidget(label_9);

        pushButtonGridColor = new CXButtonColorEdit(groupBox_2);
        pushButtonGridColor->setObjectName(QString::fromUtf8("pushButtonGridColor"));
        pushButtonGridColor->setMinimumSize(QSize(75, 0));
        pushButtonGridColor->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_5->addWidget(pushButtonGridColor);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(label_8);

        comboBox = new CXColormapCombo(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_5->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout_5);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(437, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        pushButtonClose = new QPushButton(CXDlgRoseDiagram);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));

        gridLayout->addWidget(pushButtonClose, 3, 2, 1, 1);


        retranslateUi(CXDlgRoseDiagram);

        QMetaObject::connectSlotsByName(CXDlgRoseDiagram);
    } // setupUi

    void retranslateUi(QDialog *CXDlgRoseDiagram)
    {
        CXDlgRoseDiagram->setWindowTitle(QCoreApplication::translate("CXDlgRoseDiagram", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXDlgRoseDiagram", "Data Parameters", nullptr));
        checkBoxRose->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Rose", nullptr));
        checkBoxGrid->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Grid", nullptr));
        checkBoxBins->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Bins", nullptr));
        checkBoxHisto->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Histogram", nullptr));
        label_3->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Rose petal number:", nullptr));
        label_4->setText(QCoreApplication::translate("CXDlgRoseDiagram", "From: ", nullptr));
        lineEditStartAzi->setText(QCoreApplication::translate("CXDlgRoseDiagram", "-5", nullptr));
        label_5->setText(QCoreApplication::translate("CXDlgRoseDiagram", "To: ", nullptr));
        lineEditEndAzi->setText(QCoreApplication::translate("CXDlgRoseDiagram", "355", nullptr));
        label->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Offset bin number:", nullptr));
        labelOffset->setText(QCoreApplication::translate("CXDlgRoseDiagram", "From XXX to XXX m", nullptr));
        pushButtonRefresh->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Refresh", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXDlgRoseDiagram", "Visualization Parameters", nullptr));
        label_6->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Rose Color:", nullptr));
        pushButtonRoseColor->setText(QString());
        label_7->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Opacity:", nullptr));
        lineEditOpancity->setText(QCoreApplication::translate("CXDlgRoseDiagram", "0.6", nullptr));
        label_9->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Grid Color:", nullptr));
        pushButtonGridColor->setText(QString());
        label_8->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Bin's Colormap:", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("CXDlgRoseDiagram", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgRoseDiagram: public Ui_CXDlgRoseDiagram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGROSEDIAGRAM_H
