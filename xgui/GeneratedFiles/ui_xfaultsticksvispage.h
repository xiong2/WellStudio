/********************************************************************************
** Form generated from reading UI file 'xfaultsticksvispage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XFAULTSTICKSVISPAGE_H
#define UI_XFAULTSTICKSVISPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_RLFaultSticksVisPage
{
public:
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *m_pChkVisiblePlane;
    QGridLayout *gridLayout_4;
    QLabel *m_pLabel3;
    CXButtonColorEdit *m_pColorEdtPlane;
    QSpacerItem *horizontalSpacer_6;
    QGridLayout *gridLayout;
    QLabel *m_pLabel6;
    QLineEdit *m_pLineEdtOpacity;
    QLabel *label;
    QSlider *m_pSlider;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_pLabelPoint;
    QFrame *line;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *m_pChkVisiblePoint;
    QHBoxLayout *horizontalLayout;
    QLabel *m_pLabel1;
    CXButtonColorEdit *m_pColorEdtPoint;
    QLabel *m_pLabel4;
    QComboBox *m_pCombPointSize;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_pLabelLine;
    QFrame *line_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *m_pChkVisibleLine;
    QLabel *m_pLabel2;
    CXButtonColorEdit *m_pColorEdtLine;
    QLabel *m_pLabel5;
    CXLineWidthListCombBox *m_pCombLineWidth;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_pLabelPlane;
    QFrame *line_3;

    void setupUi(QWidget *RLFaultSticksVisPage)
    {
        if (RLFaultSticksVisPage->objectName().isEmpty())
            RLFaultSticksVisPage->setObjectName(QString::fromUtf8("RLFaultSticksVisPage"));
        RLFaultSticksVisPage->setWindowModality(Qt::WindowModal);
        RLFaultSticksVisPage->resize(611, 392);
        gridLayout_6 = new QGridLayout(RLFaultSticksVisPage);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_7, 0, 0, 1, 1);

        m_pChkVisiblePlane = new QCheckBox(RLFaultSticksVisPage);
        m_pChkVisiblePlane->setObjectName(QString::fromUtf8("m_pChkVisiblePlane"));

        gridLayout_5->addWidget(m_pChkVisiblePlane, 0, 1, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_pLabel3 = new QLabel(RLFaultSticksVisPage);
        m_pLabel3->setObjectName(QString::fromUtf8("m_pLabel3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pLabel3->sizePolicy().hasHeightForWidth());
        m_pLabel3->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_pLabel3, 0, 0, 1, 1);

        m_pColorEdtPlane = new CXButtonColorEdit(RLFaultSticksVisPage);
        m_pColorEdtPlane->setObjectName(QString::fromUtf8("m_pColorEdtPlane"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pColorEdtPlane->sizePolicy().hasHeightForWidth());
        m_pColorEdtPlane->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_pColorEdtPlane, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_6, 1, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pLabel6 = new QLabel(RLFaultSticksVisPage);
        m_pLabel6->setObjectName(QString::fromUtf8("m_pLabel6"));
        sizePolicy.setHeightForWidth(m_pLabel6->sizePolicy().hasHeightForWidth());
        m_pLabel6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_pLabel6, 0, 0, 1, 1);

        m_pLineEdtOpacity = new QLineEdit(RLFaultSticksVisPage);
        m_pLineEdtOpacity->setObjectName(QString::fromUtf8("m_pLineEdtOpacity"));
        m_pLineEdtOpacity->setMaximumSize(QSize(87, 16777215));

        gridLayout->addWidget(m_pLineEdtOpacity, 0, 1, 1, 1);

        label = new QLabel(RLFaultSticksVisPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(30, 0));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        m_pSlider = new QSlider(RLFaultSticksVisPage);
        m_pSlider->setObjectName(QString::fromUtf8("m_pSlider"));
        m_pSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_pSlider, 0, 3, 1, 1);

        label_2 = new QLabel(RLFaultSticksVisPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(30, 0));

        gridLayout->addWidget(label_2, 0, 4, 1, 1);


        gridLayout_5->addLayout(gridLayout, 2, 1, 1, 2);


        gridLayout_6->addLayout(gridLayout_5, 5, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 6, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_pLabelPoint = new QLabel(RLFaultSticksVisPage);
        m_pLabelPoint->setObjectName(QString::fromUtf8("m_pLabelPoint"));
        sizePolicy.setHeightForWidth(m_pLabelPoint->sizePolicy().hasHeightForWidth());
        m_pLabelPoint->setSizePolicy(sizePolicy);
        m_pLabelPoint->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(m_pLabelPoint);

        line = new QFrame(RLFaultSticksVisPage);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);


        gridLayout_6->addLayout(horizontalLayout_4, 0, 0, 1, 2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        m_pChkVisiblePoint = new QCheckBox(RLFaultSticksVisPage);
        m_pChkVisiblePoint->setObjectName(QString::fromUtf8("m_pChkVisiblePoint"));

        gridLayout_2->addWidget(m_pChkVisiblePoint, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pLabel1 = new QLabel(RLFaultSticksVisPage);
        m_pLabel1->setObjectName(QString::fromUtf8("m_pLabel1"));
        sizePolicy.setHeightForWidth(m_pLabel1->sizePolicy().hasHeightForWidth());
        m_pLabel1->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_pLabel1);

        m_pColorEdtPoint = new CXButtonColorEdit(RLFaultSticksVisPage);
        m_pColorEdtPoint->setObjectName(QString::fromUtf8("m_pColorEdtPoint"));

        horizontalLayout->addWidget(m_pColorEdtPoint);

        m_pLabel4 = new QLabel(RLFaultSticksVisPage);
        m_pLabel4->setObjectName(QString::fromUtf8("m_pLabel4"));
        sizePolicy.setHeightForWidth(m_pLabel4->sizePolicy().hasHeightForWidth());
        m_pLabel4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_pLabel4);

        m_pCombPointSize = new QComboBox(RLFaultSticksVisPage);
        m_pCombPointSize->setObjectName(QString::fromUtf8("m_pCombPointSize"));

        horizontalLayout->addWidget(m_pCombPointSize);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout, 3, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_2, 1, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_pLabelLine = new QLabel(RLFaultSticksVisPage);
        m_pLabelLine->setObjectName(QString::fromUtf8("m_pLabelLine"));
        sizePolicy.setHeightForWidth(m_pLabelLine->sizePolicy().hasHeightForWidth());
        m_pLabelLine->setSizePolicy(sizePolicy);
        m_pLabelLine->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(m_pLabelLine);

        line_2 = new QFrame(RLFaultSticksVisPage);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        sizePolicy2.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy2);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_2);


        gridLayout_6->addLayout(horizontalLayout_5, 2, 0, 1, 2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        m_pChkVisibleLine = new QCheckBox(RLFaultSticksVisPage);
        m_pChkVisibleLine->setObjectName(QString::fromUtf8("m_pChkVisibleLine"));

        gridLayout_3->addWidget(m_pChkVisibleLine, 0, 1, 1, 5);

        m_pLabel2 = new QLabel(RLFaultSticksVisPage);
        m_pLabel2->setObjectName(QString::fromUtf8("m_pLabel2"));
        sizePolicy.setHeightForWidth(m_pLabel2->sizePolicy().hasHeightForWidth());
        m_pLabel2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_pLabel2, 1, 1, 1, 1);

        m_pColorEdtLine = new CXButtonColorEdit(RLFaultSticksVisPage);
        m_pColorEdtLine->setObjectName(QString::fromUtf8("m_pColorEdtLine"));

        gridLayout_3->addWidget(m_pColorEdtLine, 1, 2, 1, 1);

        m_pLabel5 = new QLabel(RLFaultSticksVisPage);
        m_pLabel5->setObjectName(QString::fromUtf8("m_pLabel5"));
        sizePolicy.setHeightForWidth(m_pLabel5->sizePolicy().hasHeightForWidth());
        m_pLabel5->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_pLabel5, 1, 3, 1, 1);

        m_pCombLineWidth = new CXLineWidthListCombBox(RLFaultSticksVisPage);
        m_pCombLineWidth->setObjectName(QString::fromUtf8("m_pCombLineWidth"));

        gridLayout_3->addWidget(m_pCombLineWidth, 1, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 5, 1, 1);


        gridLayout_6->addLayout(gridLayout_3, 3, 0, 1, 2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_pLabelPlane = new QLabel(RLFaultSticksVisPage);
        m_pLabelPlane->setObjectName(QString::fromUtf8("m_pLabelPlane"));
        sizePolicy.setHeightForWidth(m_pLabelPlane->sizePolicy().hasHeightForWidth());
        m_pLabelPlane->setSizePolicy(sizePolicy);
        m_pLabelPlane->setMinimumSize(QSize(0, 30));

        horizontalLayout_6->addWidget(m_pLabelPlane);

        line_3 = new QFrame(RLFaultSticksVisPage);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        sizePolicy2.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy2);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_3);


        gridLayout_6->addLayout(horizontalLayout_6, 4, 0, 1, 2);


        retranslateUi(RLFaultSticksVisPage);

        QMetaObject::connectSlotsByName(RLFaultSticksVisPage);
    } // setupUi

    void retranslateUi(QWidget *RLFaultSticksVisPage)
    {
        RLFaultSticksVisPage->setWindowTitle(QCoreApplication::translate("RLFaultSticksVisPage", "Form", nullptr));
        m_pChkVisiblePlane->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Visible", nullptr));
        m_pLabel3->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Color", nullptr));
        m_pLabel6->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Opacity", nullptr));
        label->setText(QCoreApplication::translate("RLFaultSticksVisPage", "0", nullptr));
        label_2->setText(QCoreApplication::translate("RLFaultSticksVisPage", "1.0", nullptr));
        m_pLabelPoint->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Point", nullptr));
        m_pChkVisiblePoint->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Visible", nullptr));
        m_pLabel1->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Color", nullptr));
        m_pLabel4->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Point Size", nullptr));
        m_pLabelLine->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Line", nullptr));
        m_pChkVisibleLine->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Visible", nullptr));
        m_pLabel2->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Color", nullptr));
        m_pLabel5->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Line Width", nullptr));
        m_pLabelPlane->setText(QCoreApplication::translate("RLFaultSticksVisPage", "Plane", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RLFaultSticksVisPage: public Ui_RLFaultSticksVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XFAULTSTICKSVISPAGE_H
