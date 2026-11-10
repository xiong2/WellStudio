/********************************************************************************
** Form generated from reading UI file 'xpagesectionseismicsection.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESECTIONSEISMICSECTION_H
#define UI_XPAGESECTIONSEISMICSECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <xslidercomplex.h>
#include "xbasepropertypage.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageSectionSeismicSection
{
public:
    QVBoxLayout *verticalLayout;
    CXSliderComplex *m_sliderSectionRange;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPageSectionSeismicSection)
    {
        if (CXPageSectionSeismicSection->objectName().isEmpty())
            CXPageSectionSeismicSection->setObjectName(QString::fromUtf8("CXPageSectionSeismicSection"));
        CXPageSectionSeismicSection->resize(400, 300);
        verticalLayout = new QVBoxLayout(CXPageSectionSeismicSection);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_sliderSectionRange = new CXSliderComplex(CXPageSectionSeismicSection);
        m_sliderSectionRange->setObjectName(QString::fromUtf8("m_sliderSectionRange"));

        verticalLayout->addWidget(m_sliderSectionRange);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPageSectionSeismicSection);

        QMetaObject::connectSlotsByName(CXPageSectionSeismicSection);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageSectionSeismicSection)
    {
        CXPageSectionSeismicSection->setWindowTitle(QCoreApplication::translate("CXPageSectionSeismicSection", "CXPageSectionSeismicSection", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageSectionSeismicSection: public Ui_CXPageSectionSeismicSection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESECTIONSEISMICSECTION_H
