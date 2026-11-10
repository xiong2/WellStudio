/********************************************************************************
** Form generated from reading UI file 'xpagesection3dhorizonvis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESECTION3DHORIZONVIS_H
#define UI_XPAGESECTION3DHORIZONVIS_H

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
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageSection3DHorizonVis
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QFrame *line;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    CXButtonColorEdit *m_colorLine;
    QLabel *label_2;
    QLabel *label;
    CXLineWidthListCombBox *m_cbbLineWidth;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QFrame *line_2;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    CXButtonColorEdit *m_colorAnn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *m_cbAnnLeft;
    QCheckBox *m_cbAnnBkg;
    QLabel *label_5;
    CXButtonColorEdit *m_colorAnnBkg;
    QLineEdit *m_editAnnSize;
    QCheckBox *m_cbAnnRight;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QFrame *line_3;
    QGridLayout *gridLayout_3;
    QComboBox *m_cbbPointSize;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(CXBasePropertyPage *CXPageSection3DHorizonVis)
    {
        if (CXPageSection3DHorizonVis->objectName().isEmpty())
            CXPageSection3DHorizonVis->setObjectName(QString::fromUtf8("CXPageSection3DHorizonVis"));
        CXPageSection3DHorizonVis->resize(400, 300);
        verticalLayout = new QVBoxLayout(CXPageSection3DHorizonVis);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(CXPageSection3DHorizonVis);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout->addWidget(label_3);

        line = new QFrame(CXPageSection3DHorizonVis);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(112, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 5, 1, 1);

        m_colorLine = new CXButtonColorEdit(CXPageSection3DHorizonVis);
        m_colorLine->setObjectName(QString::fromUtf8("m_colorLine"));

        gridLayout->addWidget(m_colorLine, 0, 2, 1, 1);

        label_2 = new QLabel(CXPageSection3DHorizonVis);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        label = new QLabel(CXPageSection3DHorizonVis);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        m_cbbLineWidth = new CXLineWidthListCombBox(CXPageSection3DHorizonVis);
        m_cbbLineWidth->setObjectName(QString::fromUtf8("m_cbbLineWidth"));

        gridLayout->addWidget(m_cbbLineWidth, 0, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(CXPageSection3DHorizonVis);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout_2->addWidget(label_4);

        line_2 = new QFrame(CXPageSection3DHorizonVis);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(CXPageSection3DHorizonVis);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_6, 2, 1, 1, 1);

        m_colorAnn = new CXButtonColorEdit(CXPageSection3DHorizonVis);
        m_colorAnn->setObjectName(QString::fromUtf8("m_colorAnn"));

        gridLayout_2->addWidget(m_colorAnn, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 6, 1, 1);

        m_cbAnnLeft = new QCheckBox(CXPageSection3DHorizonVis);
        m_cbAnnLeft->setObjectName(QString::fromUtf8("m_cbAnnLeft"));

        gridLayout_2->addWidget(m_cbAnnLeft, 0, 1, 1, 2);

        m_cbAnnBkg = new QCheckBox(CXPageSection3DHorizonVis);
        m_cbAnnBkg->setObjectName(QString::fromUtf8("m_cbAnnBkg"));

        gridLayout_2->addWidget(m_cbAnnBkg, 1, 1, 1, 3);

        label_5 = new QLabel(CXPageSection3DHorizonVis);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_5, 2, 3, 1, 1);

        m_colorAnnBkg = new CXButtonColorEdit(CXPageSection3DHorizonVis);
        m_colorAnnBkg->setObjectName(QString::fromUtf8("m_colorAnnBkg"));
        m_colorAnnBkg->setEnabled(false);

        gridLayout_2->addWidget(m_colorAnnBkg, 1, 4, 1, 1);

        m_editAnnSize = new QLineEdit(CXPageSection3DHorizonVis);
        m_editAnnSize->setObjectName(QString::fromUtf8("m_editAnnSize"));

        gridLayout_2->addWidget(m_editAnnSize, 2, 4, 1, 1);

        m_cbAnnRight = new QCheckBox(CXPageSection3DHorizonVis);
        m_cbAnnRight->setObjectName(QString::fromUtf8("m_cbAnnRight"));

        gridLayout_2->addWidget(m_cbAnnRight, 0, 4, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(CXPageSection3DHorizonVis);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout_3->addWidget(label_7);

        line_3 = new QFrame(CXPageSection3DHorizonVis);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_3);


        verticalLayout->addLayout(horizontalLayout_3);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_cbbPointSize = new QComboBox(CXPageSection3DHorizonVis);
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->addItem(QString());
        m_cbbPointSize->setObjectName(QString::fromUtf8("m_cbbPointSize"));

        gridLayout_3->addWidget(m_cbbPointSize, 0, 2, 1, 1);

        label_10 = new QLabel(CXPageSection3DHorizonVis);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        verticalSpacer = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_8 = new QLabel(CXPageSection3DHorizonVis);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(20, 20));
        label_8->setMaximumSize(QSize(20, 20));

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(CXPageSection3DHorizonVis);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(20, 20));
        label_9->setMaximumSize(QSize(20, 20));

        verticalLayout->addWidget(label_9);


        retranslateUi(CXPageSection3DHorizonVis);
        QObject::connect(m_cbAnnBkg, SIGNAL(toggled(bool)), m_colorAnnBkg, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(CXPageSection3DHorizonVis);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageSection3DHorizonVis)
    {
        CXPageSection3DHorizonVis->setWindowTitle(QCoreApplication::translate("CXPageSection3DHorizonVis", "CXPageSection3DHorizonVis", nullptr));
        label_3->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Line", nullptr));
        m_colorLine->setText(QString());
        label_2->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Size:", nullptr));
        label->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Color:", nullptr));
        label_4->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Annotation", nullptr));
        label_6->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Color:", nullptr));
        m_colorAnn->setText(QString());
        m_cbAnnLeft->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Left ", nullptr));
        m_cbAnnBkg->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Background color:", nullptr));
        label_5->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Size:", nullptr));
        m_colorAnnBkg->setText(QString());
        m_cbAnnRight->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Right", nullptr));
        label_7->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Intersection point", nullptr));
        m_cbbPointSize->setItemText(0, QCoreApplication::translate("CXPageSection3DHorizonVis", "1", nullptr));
        m_cbbPointSize->setItemText(1, QCoreApplication::translate("CXPageSection3DHorizonVis", "2", nullptr));
        m_cbbPointSize->setItemText(2, QCoreApplication::translate("CXPageSection3DHorizonVis", "3", nullptr));
        m_cbbPointSize->setItemText(3, QCoreApplication::translate("CXPageSection3DHorizonVis", "4", nullptr));
        m_cbbPointSize->setItemText(4, QCoreApplication::translate("CXPageSection3DHorizonVis", "5", nullptr));
        m_cbbPointSize->setItemText(5, QCoreApplication::translate("CXPageSection3DHorizonVis", "6", nullptr));
        m_cbbPointSize->setItemText(6, QCoreApplication::translate("CXPageSection3DHorizonVis", "7", nullptr));
        m_cbbPointSize->setItemText(7, QCoreApplication::translate("CXPageSection3DHorizonVis", "8", nullptr));
        m_cbbPointSize->setItemText(8, QCoreApplication::translate("CXPageSection3DHorizonVis", "9", nullptr));
        m_cbbPointSize->setItemText(9, QCoreApplication::translate("CXPageSection3DHorizonVis", "10", nullptr));
        m_cbbPointSize->setItemText(10, QCoreApplication::translate("CXPageSection3DHorizonVis", "11", nullptr));
        m_cbbPointSize->setItemText(11, QCoreApplication::translate("CXPageSection3DHorizonVis", "12", nullptr));
        m_cbbPointSize->setItemText(12, QCoreApplication::translate("CXPageSection3DHorizonVis", "13", nullptr));
        m_cbbPointSize->setItemText(13, QCoreApplication::translate("CXPageSection3DHorizonVis", "14", nullptr));
        m_cbbPointSize->setItemText(14, QCoreApplication::translate("CXPageSection3DHorizonVis", "15", nullptr));
        m_cbbPointSize->setItemText(15, QCoreApplication::translate("CXPageSection3DHorizonVis", "16", nullptr));

        label_10->setText(QCoreApplication::translate("CXPageSection3DHorizonVis", "Size:", nullptr));
        label_8->setText(QString());
        label_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXPageSection3DHorizonVis: public Ui_CXPageSection3DHorizonVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESECTION3DHORIZONVIS_H
