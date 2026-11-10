/********************************************************************************
** Form generated from reading UI file 'xpagegridmodelvis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEGRIDMODELVIS_H
#define UI_XPAGEGRIDMODELVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageGridModelVis
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QGridLayout *gridLayout_2;
    QCheckBox *m_pChkVisibleLine;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    CXButtonColorEdit *m_pColorEditLine;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    CXButtonColorEdit *m_pColorEditGeom;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QFrame *line_2;

    void setupUi(CXBasePropertyPage *CXPageGridModelVis)
    {
        if (CXPageGridModelVis->objectName().isEmpty())
            CXPageGridModelVis->setObjectName(QString::fromUtf8("CXPageGridModelVis"));
        CXPageGridModelVis->resize(400, 300);
        gridLayout = new QGridLayout(CXPageGridModelVis);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXPageGridModelVis);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(label);

        line = new QFrame(CXPageGridModelVis);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pChkVisibleLine = new QCheckBox(CXPageGridModelVis);
        m_pChkVisibleLine->setObjectName(QString::fromUtf8("m_pChkVisibleLine"));

        gridLayout_2->addWidget(m_pChkVisibleLine, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(CXPageGridModelVis);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        m_pColorEditLine = new CXButtonColorEdit(CXPageGridModelVis);
        m_pColorEditLine->setObjectName(QString::fromUtf8("m_pColorEditLine"));

        horizontalLayout_4->addWidget(m_pColorEditLine);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 3, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(CXPageGridModelVis);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        m_pColorEditGeom = new CXButtonColorEdit(CXPageGridModelVis);
        m_pColorEditGeom->setObjectName(QString::fromUtf8("m_pColorEditGeom"));

        horizontalLayout_2->addWidget(m_pColorEditGeom);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(CXPageGridModelVis);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(label_3);

        line_2 = new QFrame(CXPageGridModelVis);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_2);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 2);


        retranslateUi(CXPageGridModelVis);

        QMetaObject::connectSlotsByName(CXPageGridModelVis);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageGridModelVis)
    {
        CXPageGridModelVis->setWindowTitle(QCoreApplication::translate("CXPageGridModelVis", "CXPageGridModelVis", nullptr));
        label->setText(QCoreApplication::translate("CXPageGridModelVis", "Geometry", nullptr));
        m_pChkVisibleLine->setText(QCoreApplication::translate("CXPageGridModelVis", "Visible", nullptr));
        label_4->setText(QCoreApplication::translate("CXPageGridModelVis", "Color", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageGridModelVis", "Color", nullptr));
        label_3->setText(QCoreApplication::translate("CXPageGridModelVis", "Grid Line", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageGridModelVis: public Ui_CXPageGridModelVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEGRIDMODELVIS_H
