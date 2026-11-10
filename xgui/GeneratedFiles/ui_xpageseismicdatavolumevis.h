/********************************************************************************
** Form generated from reading UI file 'xpageseismicdatavolumevis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESEISMICDATAVOLUMEVIS_H
#define UI_XPAGESEISMICDATAVOLUMEVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageSeismicDataVolumeVis
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    CXButtonColorEdit *m_color;
    QLabel *label_3;
    CXLineWidthListCombBox *m_cbbWidth;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPageSeismicDataVolumeVis)
    {
        if (CXPageSeismicDataVolumeVis->objectName().isEmpty())
            CXPageSeismicDataVolumeVis->setObjectName(QString::fromUtf8("CXPageSeismicDataVolumeVis"));
        CXPageSeismicDataVolumeVis->resize(400, 300);
        verticalLayout = new QVBoxLayout(CXPageSeismicDataVolumeVis);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXPageSeismicDataVolumeVis);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QString::fromUtf8("color: rgb(29, 32, 136);"));

        horizontalLayout->addWidget(label);

        line = new QFrame(CXPageSeismicDataVolumeVis);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(CXPageSeismicDataVolumeVis);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        m_color = new CXButtonColorEdit(CXPageSeismicDataVolumeVis);
        m_color->setObjectName(QString::fromUtf8("m_color"));

        horizontalLayout_2->addWidget(m_color);

        label_3 = new QLabel(CXPageSeismicDataVolumeVis);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        m_cbbWidth = new CXLineWidthListCombBox(CXPageSeismicDataVolumeVis);
        m_cbbWidth->setObjectName(QString::fromUtf8("m_cbbWidth"));

        horizontalLayout_2->addWidget(m_cbbWidth);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 227, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPageSeismicDataVolumeVis);

        QMetaObject::connectSlotsByName(CXPageSeismicDataVolumeVis);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageSeismicDataVolumeVis)
    {
        CXPageSeismicDataVolumeVis->setWindowTitle(QCoreApplication::translate("CXPageSeismicDataVolumeVis", "CXPageSeismicDataVolumeVis", nullptr));
        label->setText(QCoreApplication::translate("CXPageSeismicDataVolumeVis", "Frame", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageSeismicDataVolumeVis", "Color:", nullptr));
        m_color->setText(QString());
        label_3->setText(QCoreApplication::translate("CXPageSeismicDataVolumeVis", "Width:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageSeismicDataVolumeVis: public Ui_CXPageSeismicDataVolumeVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESEISMICDATAVOLUMEVIS_H
