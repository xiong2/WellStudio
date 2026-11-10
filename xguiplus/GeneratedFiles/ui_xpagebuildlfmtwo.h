/********************************************************************************
** Form generated from reading UI file 'xpagebuildlfmtwo.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEBUILDLFMTWO_H
#define UI_XPAGEBUILDLFMTWO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_PageBuildLowFrequencyModelTwo
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    CXSliderComplex *m_pInlineWidget;
    CXSliderComplex *m_pXlineWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QToolButton *m_BtnAddPolygon;
    QLineEdit *m_pLinePolygon;
    QToolButton *m_pBtnRemovePolygon;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PageBuildLowFrequencyModelTwo)
    {
        if (PageBuildLowFrequencyModelTwo->objectName().isEmpty())
            PageBuildLowFrequencyModelTwo->setObjectName(QString::fromUtf8("PageBuildLowFrequencyModelTwo"));
        PageBuildLowFrequencyModelTwo->resize(622, 278);
        gridLayout_2 = new QGridLayout(PageBuildLowFrequencyModelTwo);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(PageBuildLowFrequencyModelTwo);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pInlineWidget = new CXSliderComplex(groupBox);
        m_pInlineWidget->setObjectName(QString::fromUtf8("m_pInlineWidget"));
        m_pInlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pInlineWidget, 0, 0, 1, 1);

        m_pXlineWidget = new CXSliderComplex(groupBox);
        m_pXlineWidget->setObjectName(QString::fromUtf8("m_pXlineWidget"));
        m_pXlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pXlineWidget, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(PageBuildLowFrequencyModelTwo);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_5);

        m_BtnAddPolygon = new QToolButton(PageBuildLowFrequencyModelTwo);
        m_BtnAddPolygon->setObjectName(QString::fromUtf8("m_BtnAddPolygon"));

        horizontalLayout->addWidget(m_BtnAddPolygon);

        m_pLinePolygon = new QLineEdit(PageBuildLowFrequencyModelTwo);
        m_pLinePolygon->setObjectName(QString::fromUtf8("m_pLinePolygon"));
        m_pLinePolygon->setReadOnly(true);

        horizontalLayout->addWidget(m_pLinePolygon);

        m_pBtnRemovePolygon = new QToolButton(PageBuildLowFrequencyModelTwo);
        m_pBtnRemovePolygon->setObjectName(QString::fromUtf8("m_pBtnRemovePolygon"));

        horizontalLayout->addWidget(m_pBtnRemovePolygon);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 145, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        m_pLinePolygon->raise();
        m_pBtnRemovePolygon->raise();
        label_5->raise();
        m_BtnAddPolygon->raise();
        groupBox->raise();
        m_pLinePolygon->raise();

        retranslateUi(PageBuildLowFrequencyModelTwo);

        QMetaObject::connectSlotsByName(PageBuildLowFrequencyModelTwo);
    } // setupUi

    void retranslateUi(QWidget *PageBuildLowFrequencyModelTwo)
    {
        PageBuildLowFrequencyModelTwo->setWindowTitle(QCoreApplication::translate("PageBuildLowFrequencyModelTwo", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageBuildLowFrequencyModelTwo", "Ranges of Inline and Crossline ", nullptr));
        label_5->setText(QCoreApplication::translate("PageBuildLowFrequencyModelTwo", "Select Polygon", nullptr));
        m_BtnAddPolygon->setText(QCoreApplication::translate("PageBuildLowFrequencyModelTwo", "...", nullptr));
        m_pBtnRemovePolygon->setText(QCoreApplication::translate("PageBuildLowFrequencyModelTwo", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageBuildLowFrequencyModelTwo: public Ui_PageBuildLowFrequencyModelTwo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEBUILDLFMTWO_H
