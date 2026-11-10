/********************************************************************************
** Form generated from reading UI file 'xpageformationvisonsec.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEFORMATIONVISONSEC_H
#define UI_XPAGEFORMATIONVISONSEC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_PageFormationVisOnSec
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    CXButtonColorEdit *m_pPtnSymbolColor;
    QLabel *label_9;
    QLineEdit *m_editSymbolHeight;
    QLabel *label_12;
    QLineEdit *m_editSymbolWidth;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    CXButtonColorEdit *m_pPtnFontColor;
    QLabel *label_5;
    QLineEdit *m_pEdtFontSize;
    QLabel *label_6;
    QFontComboBox *m_pFontName;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    CXButtonColorEdit *m_pPtnBackColor;
    QLabel *label_11;
    QSlider *m_pSldTrans;
    QLabel *m_pLblTransValue;
    QSpacerItem *verticalSpacer;
    QCheckBox *m_cbbAnnVisible;

    void setupUi(QWidget *PageFormationVisOnSec)
    {
        if (PageFormationVisOnSec->objectName().isEmpty())
            PageFormationVisOnSec->setObjectName(QString::fromUtf8("PageFormationVisOnSec"));
        PageFormationVisOnSec->resize(721, 219);
        gridLayout = new QGridLayout(PageFormationVisOnSec);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(PageFormationVisOnSec);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        line = new QFrame(PageFormationVisOnSec);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 13);

        label_7 = new QLabel(PageFormationVisOnSec);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(20, 20));

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(PageFormationVisOnSec);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        line_2 = new QFrame(PageFormationVisOnSec);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_2);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 13);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(PageFormationVisOnSec);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        m_pPtnSymbolColor = new CXButtonColorEdit(PageFormationVisOnSec);
        m_pPtnSymbolColor->setObjectName(QString::fromUtf8("m_pPtnSymbolColor"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pPtnSymbolColor->sizePolicy().hasHeightForWidth());
        m_pPtnSymbolColor->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(m_pPtnSymbolColor);

        label_9 = new QLabel(PageFormationVisOnSec);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_2->addWidget(label_9);

        m_editSymbolHeight = new QLineEdit(PageFormationVisOnSec);
        m_editSymbolHeight->setObjectName(QString::fromUtf8("m_editSymbolHeight"));

        horizontalLayout_2->addWidget(m_editSymbolHeight);

        label_12 = new QLabel(PageFormationVisOnSec);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_2->addWidget(label_12);

        m_editSymbolWidth = new QLineEdit(PageFormationVisOnSec);
        m_editSymbolWidth->setObjectName(QString::fromUtf8("m_editSymbolWidth"));

        horizontalLayout_2->addWidget(m_editSymbolWidth);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 12);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(PageFormationVisOnSec);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        m_pPtnFontColor = new CXButtonColorEdit(PageFormationVisOnSec);
        m_pPtnFontColor->setObjectName(QString::fromUtf8("m_pPtnFontColor"));
        sizePolicy1.setHeightForWidth(m_pPtnFontColor->sizePolicy().hasHeightForWidth());
        m_pPtnFontColor->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(m_pPtnFontColor);

        label_5 = new QLabel(PageFormationVisOnSec);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        m_pEdtFontSize = new QLineEdit(PageFormationVisOnSec);
        m_pEdtFontSize->setObjectName(QString::fromUtf8("m_pEdtFontSize"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pEdtFontSize->sizePolicy().hasHeightForWidth());
        m_pEdtFontSize->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(m_pEdtFontSize);

        label_6 = new QLabel(PageFormationVisOnSec);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        m_pFontName = new QFontComboBox(PageFormationVisOnSec);
        m_pFontName->setObjectName(QString::fromUtf8("m_pFontName"));

        horizontalLayout_4->addWidget(m_pFontName);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_4, 5, 1, 1, 12);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_10 = new QLabel(PageFormationVisOnSec);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_10);

        m_pPtnBackColor = new CXButtonColorEdit(PageFormationVisOnSec);
        m_pPtnBackColor->setObjectName(QString::fromUtf8("m_pPtnBackColor"));
        sizePolicy1.setHeightForWidth(m_pPtnBackColor->sizePolicy().hasHeightForWidth());
        m_pPtnBackColor->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(m_pPtnBackColor);

        label_11 = new QLabel(PageFormationVisOnSec);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_11);

        m_pSldTrans = new QSlider(PageFormationVisOnSec);
        m_pSldTrans->setObjectName(QString::fromUtf8("m_pSldTrans"));
        m_pSldTrans->setMaximum(100);
        m_pSldTrans->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(m_pSldTrans);

        m_pLblTransValue = new QLabel(PageFormationVisOnSec);
        m_pLblTransValue->setObjectName(QString::fromUtf8("m_pLblTransValue"));

        horizontalLayout_5->addWidget(m_pLblTransValue);


        gridLayout->addLayout(horizontalLayout_5, 6, 1, 1, 12);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 12, 1, 1);

        m_cbbAnnVisible = new QCheckBox(PageFormationVisOnSec);
        m_cbbAnnVisible->setObjectName(QString::fromUtf8("m_cbbAnnVisible"));

        gridLayout->addWidget(m_cbbAnnVisible, 4, 1, 1, 1);


        retranslateUi(PageFormationVisOnSec);

        QMetaObject::connectSlotsByName(PageFormationVisOnSec);
    } // setupUi

    void retranslateUi(QWidget *PageFormationVisOnSec)
    {
        PageFormationVisOnSec->setWindowTitle(QCoreApplication::translate("PageFormationVisOnSec", "Form", nullptr));
        label->setText(QCoreApplication::translate("PageFormationVisOnSec", "Symbol", nullptr));
        label_7->setText(QString());
        label_3->setText(QCoreApplication::translate("PageFormationVisOnSec", "Annotation", nullptr));
        label_2->setText(QCoreApplication::translate("PageFormationVisOnSec", "Color:", nullptr));
        m_pPtnSymbolColor->setText(QCoreApplication::translate("PageFormationVisOnSec", "PushButton", nullptr));
        label_9->setText(QCoreApplication::translate("PageFormationVisOnSec", "Height:", nullptr));
        label_12->setText(QCoreApplication::translate("PageFormationVisOnSec", "Width:", nullptr));
        label_4->setText(QCoreApplication::translate("PageFormationVisOnSec", "Color:", nullptr));
        m_pPtnFontColor->setText(QCoreApplication::translate("PageFormationVisOnSec", "PushButton", nullptr));
        label_5->setText(QCoreApplication::translate("PageFormationVisOnSec", "Size:", nullptr));
        label_6->setText(QCoreApplication::translate("PageFormationVisOnSec", "Font:", nullptr));
        label_10->setText(QCoreApplication::translate("PageFormationVisOnSec", "Background Color:", nullptr));
        m_pPtnBackColor->setText(QCoreApplication::translate("PageFormationVisOnSec", "PushButton", nullptr));
        label_11->setText(QCoreApplication::translate("PageFormationVisOnSec", "Transparency:", nullptr));
        m_pLblTransValue->setText(QCoreApplication::translate("PageFormationVisOnSec", "TextLabel", nullptr));
        m_cbbAnnVisible->setText(QCoreApplication::translate("PageFormationVisOnSec", "Visible", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageFormationVisOnSec: public Ui_PageFormationVisOnSec {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEFORMATIONVISONSEC_H
