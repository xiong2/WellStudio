/********************************************************************************
** Form generated from reading UI file 'xfaultsticksvispagesec.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XFAULTSTICKSVISPAGESEC_H
#define UI_XFAULTSTICKSVISPAGESEC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_RLFaultSticksVisPageSec
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QCheckBox *m_pChkTop;
    QCheckBox *m_pChkBottom;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_pLabelLine;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_pLabelPoint;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *m_pLabel6_2;
    QLabel *m_pLabel1;
    CXButtonColorEdit *m_pCmbStyleColor;
    QLabel *m_pLabel5;
    CXLineWidthListCombBox *m_pCmbSytleWidth;

    void setupUi(QWidget *RLFaultSticksVisPageSec)
    {
        if (RLFaultSticksVisPageSec->objectName().isEmpty())
            RLFaultSticksVisPageSec->setObjectName(QString::fromUtf8("RLFaultSticksVisPageSec"));
        RLFaultSticksVisPageSec->setWindowModality(Qt::WindowModal);
        RLFaultSticksVisPageSec->resize(443, 314);
        gridLayout_2 = new QGridLayout(RLFaultSticksVisPageSec);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(RLFaultSticksVisPageSec);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(20, 20));
        label->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(label);

        m_pChkTop = new QCheckBox(RLFaultSticksVisPageSec);
        m_pChkTop->setObjectName(QString::fromUtf8("m_pChkTop"));
        sizePolicy.setHeightForWidth(m_pChkTop->sizePolicy().hasHeightForWidth());
        m_pChkTop->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_pChkTop);

        m_pChkBottom = new QCheckBox(RLFaultSticksVisPageSec);
        m_pChkBottom->setObjectName(QString::fromUtf8("m_pChkBottom"));
        sizePolicy.setHeightForWidth(m_pChkBottom->sizePolicy().hasHeightForWidth());
        m_pChkBottom->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_pChkBottom);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_pLabelLine = new QLabel(RLFaultSticksVisPageSec);
        m_pLabelLine->setObjectName(QString::fromUtf8("m_pLabelLine"));
        sizePolicy.setHeightForWidth(m_pLabelLine->sizePolicy().hasHeightForWidth());
        m_pLabelLine->setSizePolicy(sizePolicy);
        m_pLabelLine->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(m_pLabelLine);

        line_2 = new QFrame(RLFaultSticksVisPageSec);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy1);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_2);


        gridLayout_2->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_pLabelPoint = new QLabel(RLFaultSticksVisPageSec);
        m_pLabelPoint->setObjectName(QString::fromUtf8("m_pLabelPoint"));
        sizePolicy.setHeightForWidth(m_pLabelPoint->sizePolicy().hasHeightForWidth());
        m_pLabelPoint->setSizePolicy(sizePolicy);
        m_pLabelPoint->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(m_pLabelPoint);

        line = new QFrame(RLFaultSticksVisPageSec);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pLabel6_2 = new QLabel(RLFaultSticksVisPageSec);
        m_pLabel6_2->setObjectName(QString::fromUtf8("m_pLabel6_2"));
        sizePolicy.setHeightForWidth(m_pLabel6_2->sizePolicy().hasHeightForWidth());
        m_pLabel6_2->setSizePolicy(sizePolicy);
        m_pLabel6_2->setMinimumSize(QSize(20, 20));
        m_pLabel6_2->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(m_pLabel6_2);

        m_pLabel1 = new QLabel(RLFaultSticksVisPageSec);
        m_pLabel1->setObjectName(QString::fromUtf8("m_pLabel1"));
        sizePolicy.setHeightForWidth(m_pLabel1->sizePolicy().hasHeightForWidth());
        m_pLabel1->setSizePolicy(sizePolicy);
        m_pLabel1->setLayoutDirection(Qt::LeftToRight);
        m_pLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(m_pLabel1);

        m_pCmbStyleColor = new CXButtonColorEdit(RLFaultSticksVisPageSec);
        m_pCmbStyleColor->setObjectName(QString::fromUtf8("m_pCmbStyleColor"));

        horizontalLayout->addWidget(m_pCmbStyleColor);

        m_pLabel5 = new QLabel(RLFaultSticksVisPageSec);
        m_pLabel5->setObjectName(QString::fromUtf8("m_pLabel5"));
        sizePolicy.setHeightForWidth(m_pLabel5->sizePolicy().hasHeightForWidth());
        m_pLabel5->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_pLabel5);

        m_pCmbSytleWidth = new CXLineWidthListCombBox(RLFaultSticksVisPageSec);
        m_pCmbSytleWidth->setObjectName(QString::fromUtf8("m_pCmbSytleWidth"));

        horizontalLayout->addWidget(m_pCmbSytleWidth);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(RLFaultSticksVisPageSec);

        QMetaObject::connectSlotsByName(RLFaultSticksVisPageSec);
    } // setupUi

    void retranslateUi(QWidget *RLFaultSticksVisPageSec)
    {
        RLFaultSticksVisPageSec->setWindowTitle(QCoreApplication::translate("RLFaultSticksVisPageSec", "Form", nullptr));
        label->setText(QString());
        m_pChkTop->setText(QCoreApplication::translate("RLFaultSticksVisPageSec", "Top", nullptr));
        m_pChkBottom->setText(QCoreApplication::translate("RLFaultSticksVisPageSec", "Bottom", nullptr));
        m_pLabelLine->setText(QCoreApplication::translate("RLFaultSticksVisPageSec", "Annotation", nullptr));
        m_pLabelPoint->setText(QCoreApplication::translate("RLFaultSticksVisPageSec", "Style", nullptr));
        m_pLabel6_2->setText(QString());
        m_pLabel1->setText(QCoreApplication::translate("RLFaultSticksVisPageSec", "Color:", nullptr));
        m_pLabel5->setText(QCoreApplication::translate("RLFaultSticksVisPageSec", "Width:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RLFaultSticksVisPageSec: public Ui_RLFaultSticksVisPageSec {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XFAULTSTICKSVISPAGESEC_H
