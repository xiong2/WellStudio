/********************************************************************************
** Form generated from reading UI file 'gssecsectionvispage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSSECSECTIONVISPAGE_H
#define UI_GSSECSECTIONVISPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include "xbasepropertypage.h"

QT_BEGIN_NAMESPACE

class Ui_GSSecSectionVisPage
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QRadioButton *radioButtonS;
    QRadioButton *radioButtonH;
    QLabel *label_2;
    QCheckBox *checkBoxLH;
    QCheckBox *checkBoxRH;
    QLabel *label_3;
    QCheckBox *checkBoxLP;
    QCheckBox *checkBoxRP;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *GSSecSectionVisPage)
    {
        if (GSSecSectionVisPage->objectName().isEmpty())
            GSSecSectionVisPage->setObjectName(QString::fromUtf8("GSSecSectionVisPage"));
        GSSecSectionVisPage->resize(302, 201);
        gridLayout = new QGridLayout(GSSecSectionVisPage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(GSSecSectionVisPage);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        radioButtonS = new QRadioButton(GSSecSectionVisPage);
        radioButtonS->setObjectName(QString::fromUtf8("radioButtonS"));

        gridLayout->addWidget(radioButtonS, 0, 1, 1, 1);

        radioButtonH = new QRadioButton(GSSecSectionVisPage);
        radioButtonH->setObjectName(QString::fromUtf8("radioButtonH"));
        radioButtonH->setChecked(true);

        gridLayout->addWidget(radioButtonH, 0, 2, 1, 1);

        label_2 = new QLabel(GSSecSectionVisPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        checkBoxLH = new QCheckBox(GSSecSectionVisPage);
        checkBoxLH->setObjectName(QString::fromUtf8("checkBoxLH"));

        gridLayout->addWidget(checkBoxLH, 1, 1, 2, 1);

        checkBoxRH = new QCheckBox(GSSecSectionVisPage);
        checkBoxRH->setObjectName(QString::fromUtf8("checkBoxRH"));

        gridLayout->addWidget(checkBoxRH, 1, 2, 1, 1);

        label_3 = new QLabel(GSSecSectionVisPage);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 2, 1);

        checkBoxLP = new QCheckBox(GSSecSectionVisPage);
        checkBoxLP->setObjectName(QString::fromUtf8("checkBoxLP"));

        gridLayout->addWidget(checkBoxLP, 3, 1, 1, 1);

        checkBoxRP = new QCheckBox(GSSecSectionVisPage);
        checkBoxRP->setObjectName(QString::fromUtf8("checkBoxRP"));

        gridLayout->addWidget(checkBoxRP, 3, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 69, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);


        retranslateUi(GSSecSectionVisPage);

        QMetaObject::connectSlotsByName(GSSecSectionVisPage);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *GSSecSectionVisPage)
    {
        GSSecSectionVisPage->setWindowTitle(QCoreApplication::translate("GSSecSectionVisPage", "GSBMSectionVisPage", nullptr));
        label->setText(QCoreApplication::translate("GSSecSectionVisPage", "Filled by :", nullptr));
        radioButtonS->setText(QCoreApplication::translate("GSSecSectionVisPage", "Stress Maps", nullptr));
        radioButtonH->setText(QCoreApplication::translate("GSSecSectionVisPage", "Horizons", nullptr));
        label_2->setText(QCoreApplication::translate("GSSecSectionVisPage", "Horizon Name:", nullptr));
        checkBoxLH->setText(QCoreApplication::translate("GSSecSectionVisPage", "Left end", nullptr));
        checkBoxRH->setText(QCoreApplication::translate("GSSecSectionVisPage", "Right  end", nullptr));
        label_3->setText(QCoreApplication::translate("GSSecSectionVisPage", "Compression Pulse:", nullptr));
        checkBoxLP->setText(QCoreApplication::translate("GSSecSectionVisPage", "Left end", nullptr));
        checkBoxRP->setText(QCoreApplication::translate("GSSecSectionVisPage", "Right end", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GSSecSectionVisPage: public Ui_GSSecSectionVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSSECSECTIONVISPAGE_H
