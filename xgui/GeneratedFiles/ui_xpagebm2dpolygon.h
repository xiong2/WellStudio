/********************************************************************************
** Form generated from reading UI file 'xpagebm2dpolygon.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEBM2DPOLYGON_H
#define UI_XPAGEBM2DPOLYGON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"
#include "xsliderspinwidget.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageBM2DPolygon
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    CXButtonColorEdit *m_colorBtnLine;
    QLabel *label_6;
    QSpinBox *m_spinBoxLineWidth;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_7;
    CXButtonColorEdit *m_colorBtnPivot;
    QLabel *label_8;
    QSpinBox *m_spinBoxPivotSize;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *m_cbFill;
    CXButtonColorEdit *m_colorBtnFill;
    CXSliderSpinWidget *m_widgetAlpha;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPageBM2DPolygon)
    {
        if (CXPageBM2DPolygon->objectName().isEmpty())
            CXPageBM2DPolygon->setObjectName(QString::fromUtf8("CXPageBM2DPolygon"));
        CXPageBM2DPolygon->resize(400, 300);
        verticalLayout = new QVBoxLayout(CXPageBM2DPolygon);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXPageBM2DPolygon);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout->addWidget(label);

        line = new QFrame(CXPageBM2DPolygon);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        label_5 = new QLabel(CXPageBM2DPolygon);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_5);

        m_colorBtnLine = new CXButtonColorEdit(CXPageBM2DPolygon);
        m_colorBtnLine->setObjectName(QString::fromUtf8("m_colorBtnLine"));

        horizontalLayout_5->addWidget(m_colorBtnLine);

        label_6 = new QLabel(CXPageBM2DPolygon);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        m_spinBoxLineWidth = new QSpinBox(CXPageBM2DPolygon);
        m_spinBoxLineWidth->setObjectName(QString::fromUtf8("m_spinBoxLineWidth"));
        m_spinBoxLineWidth->setMinimum(1);

        horizontalLayout_5->addWidget(m_spinBoxLineWidth);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(CXPageBM2DPolygon);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout_2->addWidget(label_2);

        line_2 = new QFrame(CXPageBM2DPolygon);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_7 = new QLabel(CXPageBM2DPolygon);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(label_7);

        m_colorBtnPivot = new CXButtonColorEdit(CXPageBM2DPolygon);
        m_colorBtnPivot->setObjectName(QString::fromUtf8("m_colorBtnPivot"));

        horizontalLayout_6->addWidget(m_colorBtnPivot);

        label_8 = new QLabel(CXPageBM2DPolygon);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_6->addWidget(label_8);

        m_spinBoxPivotSize = new QSpinBox(CXPageBM2DPolygon);
        m_spinBoxPivotSize->setObjectName(QString::fromUtf8("m_spinBoxPivotSize"));
        m_spinBoxPivotSize->setMinimum(1);

        horizontalLayout_6->addWidget(m_spinBoxPivotSize);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(CXPageBM2DPolygon);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout_3->addWidget(label_3);

        line_3 = new QFrame(CXPageBM2DPolygon);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        m_cbFill = new QCheckBox(CXPageBM2DPolygon);
        m_cbFill->setObjectName(QString::fromUtf8("m_cbFill"));

        horizontalLayout_4->addWidget(m_cbFill);

        m_colorBtnFill = new CXButtonColorEdit(CXPageBM2DPolygon);
        m_colorBtnFill->setObjectName(QString::fromUtf8("m_colorBtnFill"));
        m_colorBtnFill->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_colorBtnFill->sizePolicy().hasHeightForWidth());
        m_colorBtnFill->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(m_colorBtnFill);

        m_widgetAlpha = new CXSliderSpinWidget(CXPageBM2DPolygon);
        m_widgetAlpha->setObjectName(QString::fromUtf8("m_widgetAlpha"));
        m_widgetAlpha->setEnabled(false);

        horizontalLayout_4->addWidget(m_widgetAlpha);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPageBM2DPolygon);
        QObject::connect(m_cbFill, SIGNAL(toggled(bool)), m_colorBtnFill, SLOT(setEnabled(bool)));
        QObject::connect(m_cbFill, SIGNAL(toggled(bool)), m_widgetAlpha, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(CXPageBM2DPolygon);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageBM2DPolygon)
    {
        CXPageBM2DPolygon->setWindowTitle(QCoreApplication::translate("CXPageBM2DPolygon", "CXPageBM2DPolygon", nullptr));
        label->setText(QCoreApplication::translate("CXPageBM2DPolygon", "Line", nullptr));
        label_5->setText(QCoreApplication::translate("CXPageBM2DPolygon", "Color:", nullptr));
        m_colorBtnLine->setText(QString());
        label_6->setText(QCoreApplication::translate("CXPageBM2DPolygon", "Line width:", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageBM2DPolygon", "Pivot", nullptr));
        label_7->setText(QCoreApplication::translate("CXPageBM2DPolygon", "Color:", nullptr));
        m_colorBtnPivot->setText(QString());
        label_8->setText(QCoreApplication::translate("CXPageBM2DPolygon", "Size", nullptr));
        label_3->setText(QCoreApplication::translate("CXPageBM2DPolygon", "Fill", nullptr));
        m_cbFill->setText(QCoreApplication::translate("CXPageBM2DPolygon", "Color:", nullptr));
        m_colorBtnFill->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXPageBM2DPolygon: public Ui_CXPageBM2DPolygon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEBM2DPOLYGON_H
