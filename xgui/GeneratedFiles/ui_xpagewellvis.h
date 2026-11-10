/********************************************************************************
** Form generated from reading UI file 'xpagewellvis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEWELLVIS_H
#define UI_XPAGEWELLVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageWellVis
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    CXButtonColorEdit *m_cbbNameColor;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *m_cbNameVisible;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QFrame *line_2;
    QGridLayout *gridLayout_3;
    CXButtonColorEdit *m_cbbPathColor;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_5;
    CXLineWidthListCombBox *m_cbbPathWidth;
    QCheckBox *m_cbPathVisible;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *CXPageWellVis)
    {
        if (CXPageWellVis->objectName().isEmpty())
            CXPageWellVis->setObjectName(QString::fromUtf8("CXPageWellVis"));
        CXPageWellVis->resize(400, 300);
        verticalLayout = new QVBoxLayout(CXPageWellVis);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXPageWellVis);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        line = new QFrame(CXPageWellVis);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        label_2 = new QLabel(CXPageWellVis);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 1, 1, 1);

        m_cbbNameColor = new CXButtonColorEdit(CXPageWellVis);
        m_cbbNameColor->setObjectName(QString::fromUtf8("m_cbbNameColor"));

        gridLayout_2->addWidget(m_cbbNameColor, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        m_cbNameVisible = new QCheckBox(CXPageWellVis);
        m_cbNameVisible->setObjectName(QString::fromUtf8("m_cbNameVisible"));

        gridLayout_2->addWidget(m_cbNameVisible, 1, 1, 1, 2);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(CXPageWellVis);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_3);

        line_2 = new QFrame(CXPageWellVis);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_cbbPathColor = new CXButtonColorEdit(CXPageWellVis);
        m_cbbPathColor->setObjectName(QString::fromUtf8("m_cbbPathColor"));

        gridLayout_3->addWidget(m_cbbPathColor, 2, 2, 1, 1);

        label_4 = new QLabel(CXPageWellVis);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 2, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        label_5 = new QLabel(CXPageWellVis);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 2, 3, 1, 1);

        m_cbbPathWidth = new CXLineWidthListCombBox(CXPageWellVis);
        m_cbbPathWidth->setObjectName(QString::fromUtf8("m_cbbPathWidth"));

        gridLayout_3->addWidget(m_cbbPathWidth, 2, 4, 1, 1);

        m_cbPathVisible = new QCheckBox(CXPageWellVis);
        m_cbPathVisible->setObjectName(QString::fromUtf8("m_cbPathVisible"));

        gridLayout_3->addWidget(m_cbPathVisible, 1, 1, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 2, 5, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPageWellVis);

        QMetaObject::connectSlotsByName(CXPageWellVis);
    } // setupUi

    void retranslateUi(QWidget *CXPageWellVis)
    {
        CXPageWellVis->setWindowTitle(QCoreApplication::translate("CXPageWellVis", "CXPageWellVis", nullptr));
        label->setText(QCoreApplication::translate("CXPageWellVis", "Well Name", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageWellVis", "Color:", nullptr));
        m_cbNameVisible->setText(QCoreApplication::translate("CXPageWellVis", "Visible", nullptr));
        label_3->setText(QCoreApplication::translate("CXPageWellVis", "Well Path", nullptr));
        label_4->setText(QCoreApplication::translate("CXPageWellVis", "Color:", nullptr));
        label_5->setText(QCoreApplication::translate("CXPageWellVis", "Size:", nullptr));
        m_cbPathVisible->setText(QCoreApplication::translate("CXPageWellVis", "Visible", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageWellVis: public Ui_CXPageWellVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEWELLVIS_H
