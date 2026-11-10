/********************************************************************************
** Form generated from reading UI file 'xpagewelltopformation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEWELLTOPFORMATION_H
#define UI_XPAGEWELLTOPFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageWellTopsVis3D
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QRadioButton *m_rdbSphere;
    QRadioButton *m_rdbDisk;
    QRadioButton *m_rdbCube;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_labelName;
    QSpinBox *m_dsbRadius;
    QLabel *label_2;
    CXButtonColorEdit *m_cbbColor;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QButtonGroup *m_btngroupMode;

    void setupUi(QWidget *CXPageWellTopsVis3D)
    {
        if (CXPageWellTopsVis3D->objectName().isEmpty())
            CXPageWellTopsVis3D->setObjectName(QString::fromUtf8("CXPageWellTopsVis3D"));
        CXPageWellTopsVis3D->resize(400, 300);
        verticalLayout = new QVBoxLayout(CXPageWellTopsVis3D);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXPageWellTopsVis3D);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        line = new QFrame(CXPageWellTopsVis3D);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_rdbSphere = new QRadioButton(CXPageWellTopsVis3D);
        m_btngroupMode = new QButtonGroup(CXPageWellTopsVis3D);
        m_btngroupMode->setObjectName(QString::fromUtf8("m_btngroupMode"));
        m_btngroupMode->addButton(m_rdbSphere);
        m_rdbSphere->setObjectName(QString::fromUtf8("m_rdbSphere"));

        horizontalLayout_2->addWidget(m_rdbSphere);

        m_rdbDisk = new QRadioButton(CXPageWellTopsVis3D);
        m_btngroupMode->addButton(m_rdbDisk);
        m_rdbDisk->setObjectName(QString::fromUtf8("m_rdbDisk"));

        horizontalLayout_2->addWidget(m_rdbDisk);

        m_rdbCube = new QRadioButton(CXPageWellTopsVis3D);
        m_btngroupMode->addButton(m_rdbCube);
        m_rdbCube->setObjectName(QString::fromUtf8("m_rdbCube"));

        horizontalLayout_2->addWidget(m_rdbCube);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(CXPageWellTopsVis3D);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        line_3 = new QFrame(CXPageWellTopsVis3D);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        sizePolicy1.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy1);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        m_labelName = new QLabel(CXPageWellTopsVis3D);
        m_labelName->setObjectName(QString::fromUtf8("m_labelName"));
        sizePolicy.setHeightForWidth(m_labelName->sizePolicy().hasHeightForWidth());
        m_labelName->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(m_labelName);

        m_dsbRadius = new QSpinBox(CXPageWellTopsVis3D);
        m_dsbRadius->setObjectName(QString::fromUtf8("m_dsbRadius"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_dsbRadius->sizePolicy().hasHeightForWidth());
        m_dsbRadius->setSizePolicy(sizePolicy2);
        m_dsbRadius->setMinimumSize(QSize(0, 0));
        m_dsbRadius->setMaximumSize(QSize(16777215, 16777215));
        m_dsbRadius->setBaseSize(QSize(0, 0));

        horizontalLayout_5->addWidget(m_dsbRadius);

        label_2 = new QLabel(CXPageWellTopsVis3D);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        m_cbbColor = new CXButtonColorEdit(CXPageWellTopsVis3D);
        m_cbbColor->setObjectName(QString::fromUtf8("m_cbbColor"));

        horizontalLayout_5->addWidget(m_cbbColor);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPageWellTopsVis3D);

        QMetaObject::connectSlotsByName(CXPageWellTopsVis3D);
    } // setupUi

    void retranslateUi(QWidget *CXPageWellTopsVis3D)
    {
        CXPageWellTopsVis3D->setWindowTitle(QCoreApplication::translate("CXPageWellTopsVis3D", "CXPageWellTopsVis3D", nullptr));
        label->setText(QCoreApplication::translate("CXPageWellTopsVis3D", "Display Mode", nullptr));
        m_rdbSphere->setText(QCoreApplication::translate("CXPageWellTopsVis3D", "Sphere", nullptr));
        m_rdbDisk->setText(QCoreApplication::translate("CXPageWellTopsVis3D", "Disk", nullptr));
        m_rdbCube->setText(QCoreApplication::translate("CXPageWellTopsVis3D", "Cube", nullptr));
        label_3->setText(QCoreApplication::translate("CXPageWellTopsVis3D", "Property", nullptr));
        m_labelName->setText(QCoreApplication::translate("CXPageWellTopsVis3D", "Radius", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageWellTopsVis3D", "Color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageWellTopsVis3D: public Ui_CXPageWellTopsVis3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEWELLTOPFORMATION_H
