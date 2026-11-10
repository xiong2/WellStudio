/********************************************************************************
** Form generated from reading UI file 'xwellconditionvispage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XWELLCONDITIONVISPAGE_H
#define UI_XWELLCONDITIONVISPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXWellConditionVisPage
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_pLabelWellList;
    QFrame *line;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_pLabelLine;
    QFrame *line_3;
    QGridLayout *gridLayout_2;
    QPushButton *m_pBtDisSelectAll;
    QPushButton *m_pBtSelectAll;
    QSpacerItem *verticalSpacer_2;
    QListWidget *m_pListVisible;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_pLabelGeometry;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_pLabelGeoColor;
    CXButtonColorEdit *m_pColorEditGeo;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_3;
    QCheckBox *m_pChkVisible;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_pLabelLineColor;
    CXButtonColorEdit *m_pColorEditLine;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(CXBasePropertyPage *CXWellConditionVisPage)
    {
        if (CXWellConditionVisPage->objectName().isEmpty())
            CXWellConditionVisPage->setObjectName(QString::fromUtf8("CXWellConditionVisPage"));
        CXWellConditionVisPage->setWindowModality(Qt::WindowModal);
        CXWellConditionVisPage->resize(581, 473);
        gridLayout = new QGridLayout(CXWellConditionVisPage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pLabelWellList = new QLabel(CXWellConditionVisPage);
        m_pLabelWellList->setObjectName(QString::fromUtf8("m_pLabelWellList"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pLabelWellList->sizePolicy().hasHeightForWidth());
        m_pLabelWellList->setSizePolicy(sizePolicy);
        m_pLabelWellList->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(m_pLabelWellList);

        line = new QFrame(CXWellConditionVisPage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_pLabelLine = new QLabel(CXWellConditionVisPage);
        m_pLabelLine->setObjectName(QString::fromUtf8("m_pLabelLine"));
        sizePolicy.setHeightForWidth(m_pLabelLine->sizePolicy().hasHeightForWidth());
        m_pLabelLine->setSizePolicy(sizePolicy);
        m_pLabelLine->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(m_pLabelLine);

        line_3 = new QFrame(CXWellConditionVisPage);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_3);


        gridLayout->addLayout(horizontalLayout_4, 8, 0, 1, 2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pBtDisSelectAll = new QPushButton(CXWellConditionVisPage);
        m_pBtDisSelectAll->setObjectName(QString::fromUtf8("m_pBtDisSelectAll"));

        gridLayout_2->addWidget(m_pBtDisSelectAll, 2, 1, 1, 1);

        m_pBtSelectAll = new QPushButton(CXWellConditionVisPage);
        m_pBtSelectAll->setObjectName(QString::fromUtf8("m_pBtSelectAll"));

        gridLayout_2->addWidget(m_pBtSelectAll, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 1, 1, 1);

        m_pListVisible = new QListWidget(CXWellConditionVisPage);
        m_pListVisible->setObjectName(QString::fromUtf8("m_pListVisible"));

        gridLayout_2->addWidget(m_pListVisible, 0, 0, 3, 1);


        gridLayout->addLayout(gridLayout_2, 3, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_pLabelGeometry = new QLabel(CXWellConditionVisPage);
        m_pLabelGeometry->setObjectName(QString::fromUtf8("m_pLabelGeometry"));
        sizePolicy.setHeightForWidth(m_pLabelGeometry->sizePolicy().hasHeightForWidth());
        m_pLabelGeometry->setSizePolicy(sizePolicy);
        m_pLabelGeometry->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(m_pLabelGeometry);

        line_2 = new QFrame(CXWellConditionVisPage);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);


        gridLayout->addLayout(horizontalLayout_2, 5, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        m_pLabelGeoColor = new QLabel(CXWellConditionVisPage);
        m_pLabelGeoColor->setObjectName(QString::fromUtf8("m_pLabelGeoColor"));

        horizontalLayout_3->addWidget(m_pLabelGeoColor);

        m_pColorEditGeo = new CXButtonColorEdit(CXWellConditionVisPage);
        m_pColorEditGeo->setObjectName(QString::fromUtf8("m_pColorEditGeo"));

        horizontalLayout_3->addWidget(m_pColorEditGeo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_3, 7, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 15, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pChkVisible = new QCheckBox(CXWellConditionVisPage);
        m_pChkVisible->setObjectName(QString::fromUtf8("m_pChkVisible"));

        gridLayout_3->addWidget(m_pChkVisible, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_pLabelLineColor = new QLabel(CXWellConditionVisPage);
        m_pLabelLineColor->setObjectName(QString::fromUtf8("m_pLabelLineColor"));

        horizontalLayout_5->addWidget(m_pLabelLineColor);

        m_pColorEditLine = new CXButtonColorEdit(CXWellConditionVisPage);
        m_pColorEditLine->setObjectName(QString::fromUtf8("m_pColorEditLine"));

        horizontalLayout_5->addWidget(m_pColorEditLine);


        gridLayout_3->addLayout(horizontalLayout_5, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);


        gridLayout->addLayout(gridLayout_3, 10, 0, 1, 2);


        retranslateUi(CXWellConditionVisPage);

        QMetaObject::connectSlotsByName(CXWellConditionVisPage);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXWellConditionVisPage)
    {
        CXWellConditionVisPage->setWindowTitle(QCoreApplication::translate("CXWellConditionVisPage", "Form", nullptr));
        m_pLabelWellList->setText(QCoreApplication::translate("CXWellConditionVisPage", "Well Visible", nullptr));
        m_pLabelLine->setText(QCoreApplication::translate("CXWellConditionVisPage", "Grid Line", nullptr));
        m_pBtDisSelectAll->setText(QString());
        m_pBtSelectAll->setText(QString());
        m_pLabelGeometry->setText(QCoreApplication::translate("CXWellConditionVisPage", "Geometry", nullptr));
        m_pLabelGeoColor->setText(QCoreApplication::translate("CXWellConditionVisPage", "Color", nullptr));
        m_pColorEditGeo->setText(QString());
        m_pChkVisible->setText(QCoreApplication::translate("CXWellConditionVisPage", "Visible", nullptr));
        m_pLabelLineColor->setText(QCoreApplication::translate("CXWellConditionVisPage", "Color", nullptr));
        m_pColorEditLine->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXWellConditionVisPage: public Ui_CXWellConditionVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XWELLCONDITIONVISPAGE_H
