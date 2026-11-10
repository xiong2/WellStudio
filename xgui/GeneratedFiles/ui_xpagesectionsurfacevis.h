/********************************************************************************
** Form generated from reading UI file 'xpagesectionsurfacevis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESECTIONSURFACEVIS_H
#define UI_XPAGESECTIONSURFACEVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_SurfaceVisPage
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QFrame *line;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    CXButtonColorEdit *m_pPtnLineColor;
    CXLineWidthListCombBox *m_pCmbLineSize;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QFrame *line_2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *m_EdtAnnSize;
    CXButtonColorEdit *m_pPtnAnnColor;
    QLabel *label_6;
    QCheckBox *m_pChkRightAnnVis;
    QCheckBox *m_pChkLeftAnnVis;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    CXButtonColorEdit *m_pPtnAnnBgr;
    QCheckBox *m_ChkBgr;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QFrame *line_3;
    QGridLayout *gridLayout_3;
    QLabel *label_10;
    QComboBox *m_pCbbPointSize;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(QWidget *SurfaceVisPage)
    {
        if (SurfaceVisPage->objectName().isEmpty())
            SurfaceVisPage->setObjectName(QString::fromUtf8("SurfaceVisPage"));
        SurfaceVisPage->resize(477, 297);
        verticalLayout = new QVBoxLayout(SurfaceVisPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(SurfaceVisPage);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_3);

        line = new QFrame(SurfaceVisPage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(SurfaceVisPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_2, 0, 3, 1, 1);

        m_pPtnLineColor = new CXButtonColorEdit(SurfaceVisPage);
        m_pPtnLineColor->setObjectName(QString::fromUtf8("m_pPtnLineColor"));

        gridLayout_2->addWidget(m_pPtnLineColor, 0, 2, 1, 1);

        m_pCmbLineSize = new CXLineWidthListCombBox(SurfaceVisPage);
        m_pCmbLineSize->setObjectName(QString::fromUtf8("m_pCmbLineSize"));

        gridLayout_2->addWidget(m_pCmbLineSize, 0, 4, 1, 1);

        label = new QLabel(SurfaceVisPage);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(SurfaceVisPage);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_4);

        line_2 = new QFrame(SurfaceVisPage);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(SurfaceVisPage);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_5, 2, 4, 2, 1);

        m_EdtAnnSize = new QLineEdit(SurfaceVisPage);
        m_EdtAnnSize->setObjectName(QString::fromUtf8("m_EdtAnnSize"));

        gridLayout->addWidget(m_EdtAnnSize, 3, 5, 1, 1);

        m_pPtnAnnColor = new CXButtonColorEdit(SurfaceVisPage);
        m_pPtnAnnColor->setObjectName(QString::fromUtf8("m_pPtnAnnColor"));

        gridLayout->addWidget(m_pPtnAnnColor, 2, 2, 2, 2);

        label_6 = new QLabel(SurfaceVisPage);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_6, 2, 1, 2, 1);

        m_pChkRightAnnVis = new QCheckBox(SurfaceVisPage);
        m_pChkRightAnnVis->setObjectName(QString::fromUtf8("m_pChkRightAnnVis"));

        gridLayout->addWidget(m_pChkRightAnnVis, 0, 3, 1, 2);

        m_pChkLeftAnnVis = new QCheckBox(SurfaceVisPage);
        m_pChkLeftAnnVis->setObjectName(QString::fromUtf8("m_pChkLeftAnnVis"));

        gridLayout->addWidget(m_pChkLeftAnnVis, 0, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 6, 1, 1);

        m_pPtnAnnBgr = new CXButtonColorEdit(SurfaceVisPage);
        m_pPtnAnnBgr->setObjectName(QString::fromUtf8("m_pPtnAnnBgr"));
        m_pPtnAnnBgr->setEnabled(false);

        gridLayout->addWidget(m_pPtnAnnBgr, 1, 5, 1, 1);

        m_ChkBgr = new QCheckBox(SurfaceVisPage);
        m_ChkBgr->setObjectName(QString::fromUtf8("m_ChkBgr"));

        gridLayout->addWidget(m_ChkBgr, 1, 1, 1, 4);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(SurfaceVisPage);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_7);

        line_3 = new QFrame(SurfaceVisPage);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_3);


        verticalLayout->addLayout(horizontalLayout_3);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_10 = new QLabel(SurfaceVisPage);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 0, 1, 1, 1);

        m_pCbbPointSize = new QComboBox(SurfaceVisPage);
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->addItem(QString());
        m_pCbbPointSize->setObjectName(QString::fromUtf8("m_pCbbPointSize"));

        gridLayout_3->addWidget(m_pCbbPointSize, 0, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_8 = new QLabel(SurfaceVisPage);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(20, 20));
        label_8->setMaximumSize(QSize(20, 20));

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(SurfaceVisPage);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(20, 20));
        label_9->setMaximumSize(QSize(20, 20));

        verticalLayout->addWidget(label_9);


        retranslateUi(SurfaceVisPage);
        QObject::connect(m_ChkBgr, SIGNAL(toggled(bool)), m_pPtnAnnBgr, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(SurfaceVisPage);
    } // setupUi

    void retranslateUi(QWidget *SurfaceVisPage)
    {
        SurfaceVisPage->setWindowTitle(QCoreApplication::translate("SurfaceVisPage", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("SurfaceVisPage", "Line", nullptr));
        label_2->setText(QCoreApplication::translate("SurfaceVisPage", "Size:", nullptr));
        m_pPtnLineColor->setText(QCoreApplication::translate("SurfaceVisPage", "PushButton", nullptr));
        label->setText(QCoreApplication::translate("SurfaceVisPage", "Color:", nullptr));
        label_4->setText(QCoreApplication::translate("SurfaceVisPage", "Annotation", nullptr));
        label_5->setText(QCoreApplication::translate("SurfaceVisPage", "Size:", nullptr));
        m_pPtnAnnColor->setText(QCoreApplication::translate("SurfaceVisPage", "PushButton", nullptr));
        label_6->setText(QCoreApplication::translate("SurfaceVisPage", "Color:", nullptr));
        m_pChkRightAnnVis->setText(QCoreApplication::translate("SurfaceVisPage", "Right", nullptr));
        m_pChkLeftAnnVis->setText(QCoreApplication::translate("SurfaceVisPage", "Left ", nullptr));
        m_pPtnAnnBgr->setText(QCoreApplication::translate("SurfaceVisPage", "PushButton", nullptr));
        m_ChkBgr->setText(QCoreApplication::translate("SurfaceVisPage", "Background color:", nullptr));
        label_7->setText(QCoreApplication::translate("SurfaceVisPage", "Intersection point", nullptr));
        label_10->setText(QCoreApplication::translate("SurfaceVisPage", "Size:", nullptr));
        m_pCbbPointSize->setItemText(0, QCoreApplication::translate("SurfaceVisPage", "1", nullptr));
        m_pCbbPointSize->setItemText(1, QCoreApplication::translate("SurfaceVisPage", "2", nullptr));
        m_pCbbPointSize->setItemText(2, QCoreApplication::translate("SurfaceVisPage", "3", nullptr));
        m_pCbbPointSize->setItemText(3, QCoreApplication::translate("SurfaceVisPage", "4", nullptr));
        m_pCbbPointSize->setItemText(4, QCoreApplication::translate("SurfaceVisPage", "5", nullptr));
        m_pCbbPointSize->setItemText(5, QCoreApplication::translate("SurfaceVisPage", "6", nullptr));
        m_pCbbPointSize->setItemText(6, QCoreApplication::translate("SurfaceVisPage", "7", nullptr));
        m_pCbbPointSize->setItemText(7, QCoreApplication::translate("SurfaceVisPage", "8", nullptr));
        m_pCbbPointSize->setItemText(8, QCoreApplication::translate("SurfaceVisPage", "9", nullptr));
        m_pCbbPointSize->setItemText(9, QCoreApplication::translate("SurfaceVisPage", "10", nullptr));
        m_pCbbPointSize->setItemText(10, QCoreApplication::translate("SurfaceVisPage", "11", nullptr));
        m_pCbbPointSize->setItemText(11, QCoreApplication::translate("SurfaceVisPage", "12", nullptr));
        m_pCbbPointSize->setItemText(12, QCoreApplication::translate("SurfaceVisPage", "13", nullptr));
        m_pCbbPointSize->setItemText(13, QCoreApplication::translate("SurfaceVisPage", "14", nullptr));
        m_pCbbPointSize->setItemText(14, QCoreApplication::translate("SurfaceVisPage", "15", nullptr));
        m_pCbbPointSize->setItemText(15, QCoreApplication::translate("SurfaceVisPage", "16", nullptr));

        label_8->setText(QString());
        label_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SurfaceVisPage: public Ui_SurfaceVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESECTIONSURFACEVIS_H
