/********************************************************************************
** Form generated from reading UI file 'gsbm3dhorizonvispage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSBM3DHORIZONVISPAGE_H
#define UI_GSBM3DHORIZONVISPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_GSBM3DHorizonVisPage
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_2;
    QLineEdit *lineEdit_LevelFirst;
    QLabel *label_9;
    QLineEdit *lineEdit_LevelLast;
    QLabel *label_10;
    QLineEdit *lineEdit_LevelNum;
    QSpacerItem *horizontalSpacer;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_3;
    CXButtonColorEdit *colorButton_CoarseLine;
    QLabel *label_4;
    QSpinBox *spinBox_CoarseWidth;
    QLabel *label_5;
    QSpinBox *spinBox_CoarseFreq;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_7;
    CXButtonColorEdit *colorButton_NormalLine;
    QLabel *label_11;
    QSpinBox *spinBox_NormalWidth;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_13;
    CXButtonColorEdit *colorButton_Annotation;
    QLabel *label_14;
    QFontComboBox *fontComboBox;
    QLabel *label_15;
    QSpinBox *spinBox_AnnotationFontSize;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(CXBasePropertyPage *GSBM3DHorizonVisPage)
    {
        if (GSBM3DHorizonVisPage->objectName().isEmpty())
            GSBM3DHorizonVisPage->setObjectName(QString::fromUtf8("GSBM3DHorizonVisPage"));
        GSBM3DHorizonVisPage->resize(631, 242);
        gridLayout = new QGridLayout(GSBM3DHorizonVisPage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(GSBM3DHorizonVisPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(true);
        groupBox->setCheckable(true);
        groupBox->setChecked(false);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_LevelFirst = new QLineEdit(groupBox);
        lineEdit_LevelFirst->setObjectName(QString::fromUtf8("lineEdit_LevelFirst"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_LevelFirst->sizePolicy().hasHeightForWidth());
        lineEdit_LevelFirst->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit_LevelFirst);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);

        lineEdit_LevelLast = new QLineEdit(groupBox);
        lineEdit_LevelLast->setObjectName(QString::fromUtf8("lineEdit_LevelLast"));
        sizePolicy.setHeightForWidth(lineEdit_LevelLast->sizePolicy().hasHeightForWidth());
        lineEdit_LevelLast->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit_LevelLast);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout->addWidget(label_10);

        lineEdit_LevelNum = new QLineEdit(groupBox);
        lineEdit_LevelNum->setObjectName(QString::fromUtf8("lineEdit_LevelNum"));
        sizePolicy.setHeightForWidth(lineEdit_LevelNum->sizePolicy().hasHeightForWidth());
        lineEdit_LevelNum->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit_LevelNum);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        colorButton_CoarseLine = new CXButtonColorEdit(groupBox);
        colorButton_CoarseLine->setObjectName(QString::fromUtf8("colorButton_CoarseLine"));

        horizontalLayout_2->addWidget(colorButton_CoarseLine);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        spinBox_CoarseWidth = new QSpinBox(groupBox);
        spinBox_CoarseWidth->setObjectName(QString::fromUtf8("spinBox_CoarseWidth"));

        horizontalLayout_2->addWidget(spinBox_CoarseWidth);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        spinBox_CoarseFreq = new QSpinBox(groupBox);
        spinBox_CoarseFreq->setObjectName(QString::fromUtf8("spinBox_CoarseFreq"));

        horizontalLayout_2->addWidget(spinBox_CoarseFreq);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);

        colorButton_NormalLine = new CXButtonColorEdit(groupBox);
        colorButton_NormalLine->setObjectName(QString::fromUtf8("colorButton_NormalLine"));

        horizontalLayout_3->addWidget(colorButton_NormalLine);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_3->addWidget(label_11);

        spinBox_NormalWidth = new QSpinBox(groupBox);
        spinBox_NormalWidth->setObjectName(QString::fromUtf8("spinBox_NormalWidth"));

        horizontalLayout_3->addWidget(spinBox_NormalWidth);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout->addWidget(label_12);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_4->addWidget(label_13);

        colorButton_Annotation = new CXButtonColorEdit(groupBox);
        colorButton_Annotation->setObjectName(QString::fromUtf8("colorButton_Annotation"));

        horizontalLayout_4->addWidget(colorButton_Annotation);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_4->addWidget(label_14);

        fontComboBox = new QFontComboBox(groupBox);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));

        horizontalLayout_4->addWidget(fontComboBox);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_4->addWidget(label_15);

        spinBox_AnnotationFontSize = new QSpinBox(groupBox);
        spinBox_AnnotationFontSize->setObjectName(QString::fromUtf8("spinBox_AnnotationFontSize"));

        horizontalLayout_4->addWidget(spinBox_AnnotationFontSize);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(GSBM3DHorizonVisPage);

        QMetaObject::connectSlotsByName(GSBM3DHorizonVisPage);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *GSBM3DHorizonVisPage)
    {
        GSBM3DHorizonVisPage->setWindowTitle(QCoreApplication::translate("GSBM3DHorizonVisPage", "GSPageBMVis3DHorizon", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GSBM3DHorizonVisPage", "Isoline", nullptr));
        label->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Level:", nullptr));
        label_2->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "First:", nullptr));
        label_9->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Last:", nullptr));
        label_10->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Number:", nullptr));
        label_8->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Coarse Line:", nullptr));
        label_3->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Color:", nullptr));
        colorButton_CoarseLine->setText(QString());
        label_4->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Width:", nullptr));
        label_5->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Frequency:", nullptr));
        label_6->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Normal Line:", nullptr));
        label_7->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Color:", nullptr));
        colorButton_NormalLine->setText(QString());
        label_11->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Width:", nullptr));
        label_12->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Annotation:", nullptr));
        label_13->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Color:", nullptr));
        colorButton_Annotation->setText(QString());
        label_14->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Font:", nullptr));
        label_15->setText(QCoreApplication::translate("GSBM3DHorizonVisPage", "Size:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSBM3DHorizonVisPage: public Ui_GSBM3DHorizonVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSBM3DHORIZONVISPAGE_H
