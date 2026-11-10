/********************************************************************************
** Form generated from reading UI file 'xpage3dpoints.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGE3DPOINTS_H
#define UI_XPAGE3DPOINTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXPage3DPoints
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    CXButtonColorEdit *pushButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPage3DPoints)
    {
        if (CXPage3DPoints->objectName().isEmpty())
            CXPage3DPoints->setObjectName(QString::fromUtf8("CXPage3DPoints"));
        CXPage3DPoints->resize(197, 89);
        verticalLayout = new QVBoxLayout(CXPage3DPoints);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXPage3DPoints);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(CXPage3DPoints);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);

        horizontalLayout->addWidget(spinBox);

        label_2 = new QLabel(CXPage3DPoints);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        pushButton = new CXButtonColorEdit(CXPage3DPoints);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPage3DPoints);

        QMetaObject::connectSlotsByName(CXPage3DPoints);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPage3DPoints)
    {
        CXPage3DPoints->setWindowTitle(QCoreApplication::translate("CXPage3DPoints", "CXPage3DPoints", nullptr));
        label->setText(QCoreApplication::translate("CXPage3DPoints", "Size", nullptr));
        label_2->setText(QCoreApplication::translate("CXPage3DPoints", "Color", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXPage3DPoints: public Ui_CXPage3DPoints {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGE3DPOINTS_H
