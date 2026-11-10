/********************************************************************************
** Form generated from reading UI file 'xpageseismicforwardingthree.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESEISMICFORWARDINGTHREE_H
#define UI_XPAGESEISMICFORWARDINGTHREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_PageSeismicForwardingThree
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *m;
    QGridLayout *gridLayout;
    CXSliderComplex *m_pXlineWidget;
    CXSliderComplex *m_pTimeWidget;
    CXSliderComplex *m_pInlineWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_10;
    QLineEdit *m_pOutputName;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PageSeismicForwardingThree)
    {
        if (PageSeismicForwardingThree->objectName().isEmpty())
            PageSeismicForwardingThree->setObjectName(QString::fromUtf8("PageSeismicForwardingThree"));
        PageSeismicForwardingThree->resize(741, 406);
        gridLayout_2 = new QGridLayout(PageSeismicForwardingThree);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m = new QGroupBox(PageSeismicForwardingThree);
        m->setObjectName(QString::fromUtf8("m"));
        m->setMinimumSize(QSize(0, 180));
        gridLayout = new QGridLayout(m);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pXlineWidget = new CXSliderComplex(m);
        m_pXlineWidget->setObjectName(QString::fromUtf8("m_pXlineWidget"));
        m_pXlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pXlineWidget, 1, 0, 1, 1);

        m_pTimeWidget = new CXSliderComplex(m);
        m_pTimeWidget->setObjectName(QString::fromUtf8("m_pTimeWidget"));
        m_pTimeWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pTimeWidget, 2, 0, 1, 1);

        m_pInlineWidget = new CXSliderComplex(m);
        m_pInlineWidget->setObjectName(QString::fromUtf8("m_pInlineWidget"));
        m_pInlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pInlineWidget, 0, 0, 1, 1);


        gridLayout_2->addWidget(m, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_10 = new QLabel(PageSeismicForwardingThree);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(230, 0));

        horizontalLayout->addWidget(label_10);

        m_pOutputName = new QLineEdit(PageSeismicForwardingThree);
        m_pOutputName->setObjectName(QString::fromUtf8("m_pOutputName"));
        m_pOutputName->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(m_pOutputName);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 168, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);


        retranslateUi(PageSeismicForwardingThree);

        QMetaObject::connectSlotsByName(PageSeismicForwardingThree);
    } // setupUi

    void retranslateUi(QWidget *PageSeismicForwardingThree)
    {
        PageSeismicForwardingThree->setWindowTitle(QCoreApplication::translate("PageSeismicForwardingThree", "Form", nullptr));
        m->setTitle(QCoreApplication::translate("PageSeismicForwardingThree", "Output Range", nullptr));
        label_10->setText(QCoreApplication::translate("PageSeismicForwardingThree", "Name of Output Seismic Data Volume", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageSeismicForwardingThree: public Ui_PageSeismicForwardingThree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESEISMICFORWARDINGTHREE_H
