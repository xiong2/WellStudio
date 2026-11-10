/********************************************************************************
** Form generated from reading UI file 'gsbmrosediagramvispage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSBMROSEDIAGRAMVISPAGE_H
#define UI_GSBMROSEDIAGRAMVISPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_GSBMRoseDiagramVisPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBoxSize;
    QLabel *label_8;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QSpinBox *spinBoxPNumber;
    QLabel *label_3;
    QSlider *horizontalSliderPO;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    CXButtonColorEdit *pushButtonLColor;
    QLabel *label_2;
    CXButtonColorEdit *pushButtonPColor;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBoxRange;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    CXButtonColorEdit *pushButtonRColor;
    QLabel *label_10;
    QSlider *horizontalSliderRO;
    QLabel *label_11;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *GSBMRoseDiagramVisPage)
    {
        if (GSBMRoseDiagramVisPage->objectName().isEmpty())
            GSBMRoseDiagramVisPage->setObjectName(QString::fromUtf8("GSBMRoseDiagramVisPage"));
        GSBMRoseDiagramVisPage->resize(392, 211);
        verticalLayout_2 = new QVBoxLayout(GSBMRoseDiagramVisPage);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(GSBMRoseDiagramVisPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBoxSize = new QSpinBox(groupBox);
        spinBoxSize->setObjectName(QString::fromUtf8("spinBoxSize"));
        spinBoxSize->setMinimum(1);
        spinBoxSize->setMaximum(5);
        spinBoxSize->setValue(5);

        gridLayout->addWidget(spinBoxSize, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        spinBoxPNumber = new QSpinBox(groupBox);
        spinBoxPNumber->setObjectName(QString::fromUtf8("spinBoxPNumber"));
        spinBoxPNumber->setMinimum(4);
        spinBoxPNumber->setMaximum(64);
        spinBoxPNumber->setSingleStep(4);
        spinBoxPNumber->setValue(32);

        horizontalLayout->addWidget(spinBoxPNumber);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSliderPO = new QSlider(groupBox);
        horizontalSliderPO->setObjectName(QString::fromUtf8("horizontalSliderPO"));
        horizontalSliderPO->setMaximum(255);
        horizontalSliderPO->setValue(255);
        horizontalSliderPO->setSliderPosition(255);
        horizontalSliderPO->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSliderPO);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        pushButtonLColor = new CXButtonColorEdit(groupBox);
        pushButtonLColor->setObjectName(QString::fromUtf8("pushButtonLColor"));
        pushButtonLColor->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(pushButtonLColor);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        pushButtonPColor = new CXButtonColorEdit(groupBox);
        pushButtonPColor->setObjectName(QString::fromUtf8("pushButtonPColor"));
        pushButtonPColor->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(pushButtonPColor);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 4);


        verticalLayout_2->addWidget(groupBox);

        groupBoxRange = new QGroupBox(GSBMRoseDiagramVisPage);
        groupBoxRange->setObjectName(QString::fromUtf8("groupBoxRange"));
        groupBoxRange->setCheckable(true);
        verticalLayout = new QVBoxLayout(groupBoxRange);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(groupBoxRange);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_3->addWidget(label_9);

        pushButtonRColor = new CXButtonColorEdit(groupBoxRange);
        pushButtonRColor->setObjectName(QString::fromUtf8("pushButtonRColor"));
        pushButtonRColor->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(pushButtonRColor);

        label_10 = new QLabel(groupBoxRange);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_3->addWidget(label_10);

        horizontalSliderRO = new QSlider(groupBoxRange);
        horizontalSliderRO->setObjectName(QString::fromUtf8("horizontalSliderRO"));
        horizontalSliderRO->setMaximum(255);
        horizontalSliderRO->setSliderPosition(100);
        horizontalSliderRO->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSliderRO);

        label_11 = new QLabel(groupBoxRange);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_3->addWidget(label_11);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(groupBoxRange);

        verticalSpacer = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        groupBoxRange->raise();
        groupBox->raise();
        label_10->raise();

        retranslateUi(GSBMRoseDiagramVisPage);

        comboBox->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(GSBMRoseDiagramVisPage);
    } // setupUi

    void retranslateUi(QWidget *GSBMRoseDiagramVisPage)
    {
        GSBMRoseDiagramVisPage->setWindowTitle(QCoreApplication::translate("GSBMRoseDiagramVisPage", "GSBMRoseDiagramVisPage", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Rose diagram", nullptr));
        label->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Size:", nullptr));
        label_8->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Position:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Top Left", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Top", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Top Right", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Left", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Centre", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Right", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Bottom Left", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Bottom", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("GSBMRoseDiagramVisPage", "Bottom Right", nullptr));

        label_5->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Petal Number:", nullptr));
        label_3->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Opacity:0", nullptr));
        label_4->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "1", nullptr));
        label_6->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Line Color: ", nullptr));
        pushButtonLColor->setText(QString());
        label_2->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Petal Color:", nullptr));
        pushButtonPColor->setText(QString());
        groupBoxRange->setTitle(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Range", nullptr));
        label_9->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Range Color:", nullptr));
        pushButtonRColor->setText(QString());
        label_10->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "Opacity:0", nullptr));
        label_11->setText(QCoreApplication::translate("GSBMRoseDiagramVisPage", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSBMRoseDiagramVisPage: public Ui_GSBMRoseDiagramVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSBMROSEDIAGRAMVISPAGE_H
