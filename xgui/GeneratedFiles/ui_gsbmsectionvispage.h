/********************************************************************************
** Form generated from reading UI file 'gsbmsectionvispage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSBMSECTIONVISPAGE_H
#define UI_GSBMSECTIONVISPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"

QT_BEGIN_NAMESPACE

class Ui_GSBMSectionVisPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox_Width;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_TurningPoints;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spinBox_Radius;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *GSBMSectionVisPage)
    {
        if (GSBMSectionVisPage->objectName().isEmpty())
            GSBMSectionVisPage->setObjectName(QString::fromUtf8("GSBMSectionVisPage"));
        GSBMSectionVisPage->resize(141, 176);
        verticalLayout_2 = new QVBoxLayout(GSBMSectionVisPage);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(GSBMSectionVisPage);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBox_Width = new QSpinBox(GSBMSectionVisPage);
        spinBox_Width->setObjectName(QString::fromUtf8("spinBox_Width"));
        spinBox_Width->setMaximum(20);
        spinBox_Width->setValue(1);

        horizontalLayout->addWidget(spinBox_Width);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox_TurningPoints = new QGroupBox(GSBMSectionVisPage);
        groupBox_TurningPoints->setObjectName(QString::fromUtf8("groupBox_TurningPoints"));
        groupBox_TurningPoints->setCheckable(true);
        verticalLayout = new QVBoxLayout(groupBox_TurningPoints);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox_TurningPoints);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spinBox_Radius = new QSpinBox(groupBox_TurningPoints);
        spinBox_Radius->setObjectName(QString::fromUtf8("spinBox_Radius"));
        spinBox_Radius->setMinimum(1);

        horizontalLayout_2->addWidget(spinBox_Radius);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(groupBox_TurningPoints);

        verticalSpacer = new QSpacerItem(20, 69, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(GSBMSectionVisPage);

        QMetaObject::connectSlotsByName(GSBMSectionVisPage);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *GSBMSectionVisPage)
    {
        GSBMSectionVisPage->setWindowTitle(QCoreApplication::translate("GSBMSectionVisPage", "GSBMSectionVisPage", nullptr));
        label->setText(QCoreApplication::translate("GSBMSectionVisPage", "Width:", nullptr));
        groupBox_TurningPoints->setTitle(QCoreApplication::translate("GSBMSectionVisPage", "Turning Points", nullptr));
        label_2->setText(QCoreApplication::translate("GSBMSectionVisPage", "Radius:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSBMSectionVisPage: public Ui_GSBMSectionVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSBMSECTIONVISPAGE_H
