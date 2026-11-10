/********************************************************************************
** Form generated from reading UI file 'xpageprestackgathervis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEPRESTACKGATHERVIS_H
#define UI_XPAGEPRESTACKGATHERVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"
#include "xsliderspinwidget.h"
#include "xtypecombo.h"

QT_BEGIN_NAMESPACE

class Ui_CXPagePreStackGatherVis
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioBtn_ViewAll;
    QRadioButton *radioBtn_Specified;
    CXSliderSpinWidget *widget_SliderSpin;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    CXTypeCombo *comboBox_SourceShape;
    QLabel *label_2;
    QSpinBox *spinBox_SourceSize;
    QLabel *label_3;
    CXButtonColorEdit *btn_SourceColor;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    CXTypeCombo *comboBox_DetectShape;
    QLabel *label_5;
    QSpinBox *spinBox_DetectSize;
    QLabel *label_6;
    CXButtonColorEdit *btn_DetectColor;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPagePreStackGatherVis)
    {
        if (CXPagePreStackGatherVis->objectName().isEmpty())
            CXPagePreStackGatherVis->setObjectName(QString::fromUtf8("CXPagePreStackGatherVis"));
        CXPagePreStackGatherVis->resize(326, 263);
        verticalLayout = new QVBoxLayout(CXPagePreStackGatherVis);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(CXPagePreStackGatherVis);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(true);
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        radioBtn_ViewAll = new QRadioButton(groupBox);
        radioBtn_ViewAll->setObjectName(QString::fromUtf8("radioBtn_ViewAll"));
        radioBtn_ViewAll->setChecked(true);

        horizontalLayout_3->addWidget(radioBtn_ViewAll);

        radioBtn_Specified = new QRadioButton(groupBox);
        radioBtn_Specified->setObjectName(QString::fromUtf8("radioBtn_Specified"));

        horizontalLayout_3->addWidget(radioBtn_Specified);

        widget_SliderSpin = new CXSliderSpinWidget(groupBox);
        widget_SliderSpin->setObjectName(QString::fromUtf8("widget_SliderSpin"));
        widget_SliderSpin->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_SliderSpin->sizePolicy().hasHeightForWidth());
        widget_SliderSpin->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(widget_SliderSpin);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(CXPagePreStackGatherVis);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFlat(true);
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBox_SourceShape = new CXTypeCombo(groupBox_2);
        comboBox_SourceShape->setObjectName(QString::fromUtf8("comboBox_SourceShape"));

        horizontalLayout->addWidget(comboBox_SourceShape);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBox_SourceSize = new QSpinBox(groupBox_2);
        spinBox_SourceSize->setObjectName(QString::fromUtf8("spinBox_SourceSize"));
        spinBox_SourceSize->setMinimum(1);

        horizontalLayout->addWidget(spinBox_SourceSize);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        btn_SourceColor = new CXButtonColorEdit(groupBox_2);
        btn_SourceColor->setObjectName(QString::fromUtf8("btn_SourceColor"));

        horizontalLayout->addWidget(btn_SourceColor);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(CXPagePreStackGatherVis);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFlat(true);
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        comboBox_DetectShape = new CXTypeCombo(groupBox_3);
        comboBox_DetectShape->setObjectName(QString::fromUtf8("comboBox_DetectShape"));

        horizontalLayout_2->addWidget(comboBox_DetectShape);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        spinBox_DetectSize = new QSpinBox(groupBox_3);
        spinBox_DetectSize->setObjectName(QString::fromUtf8("spinBox_DetectSize"));
        spinBox_DetectSize->setMinimum(1);

        horizontalLayout_2->addWidget(spinBox_DetectSize);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        btn_DetectColor = new CXButtonColorEdit(groupBox_3);
        btn_DetectColor->setObjectName(QString::fromUtf8("btn_DetectColor"));

        horizontalLayout_2->addWidget(btn_DetectColor);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPagePreStackGatherVis);
        QObject::connect(radioBtn_Specified, SIGNAL(toggled(bool)), widget_SliderSpin, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(CXPagePreStackGatherVis);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPagePreStackGatherVis)
    {
        CXPagePreStackGatherVis->setWindowTitle(QCoreApplication::translate("CXPagePreStackGatherVis", "CXPagePreStackGatherVis", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXPagePreStackGatherVis", "Range", nullptr));
        radioBtn_ViewAll->setText(QCoreApplication::translate("CXPagePreStackGatherVis", "View All", nullptr));
        radioBtn_Specified->setText(QCoreApplication::translate("CXPagePreStackGatherVis", "Specified", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXPagePreStackGatherVis", "Source Points", nullptr));
        label->setText(QCoreApplication::translate("CXPagePreStackGatherVis", "Shape", nullptr));
        label_2->setText(QCoreApplication::translate("CXPagePreStackGatherVis", "Size", nullptr));
        label_3->setText(QCoreApplication::translate("CXPagePreStackGatherVis", "Color", nullptr));
        btn_SourceColor->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("CXPagePreStackGatherVis", "Detect Points", nullptr));
        label_4->setText(QCoreApplication::translate("CXPagePreStackGatherVis", "Shape", nullptr));
        label_5->setText(QCoreApplication::translate("CXPagePreStackGatherVis", "Size", nullptr));
        label_6->setText(QCoreApplication::translate("CXPagePreStackGatherVis", "Color", nullptr));
        btn_DetectColor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXPagePreStackGatherVis: public Ui_CXPagePreStackGatherVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEPRESTACKGATHERVIS_H
