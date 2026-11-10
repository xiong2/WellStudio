/********************************************************************************
** Form generated from reading UI file 'xpagelfmgeometryvis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGELFMGEOMETRYVIS_H
#define UI_XPAGELFMGEOMETRYVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <xbasepropertypage.h>
#include <xbuttoncoloredit.h>
#include <xlinecomponent.h>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_CXPageLFMGeometryVis
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *gbxDisplayRange;
    QVBoxLayout *verticalLayout_2;
    CXSliderComplex *m_pSliderInline;
    CXSliderComplex *m_pSliderCrossline;
    QGroupBox *gbxGridLine;
    QGridLayout *gridLayout_2;
    QLabel *lblColor;
    CXButtonColorEdit *m_pClrBtnLine;
    QCheckBox *m_pChkTopAndBottomLine;
    QLabel *lblSize;
    CXLineWidthListCombBox *m_pCmbLineSize;
    QCheckBox *m_pChkHorizontalSlice;
    QLabel *lblVerticalLineSpacing;
    QCheckBox *m_pChkVerticalSlice;
    QComboBox *m_pCmbVerticalLineSpacing;
    QSpacerItem *horizontalSpacer;
    QGroupBox *gbxZoneSetting;
    QGridLayout *gridLayout;
    QTableWidget *m_pTableZone;

    void setupUi(CXBasePropertyPage *CXPageLFMGeometryVis)
    {
        if (CXPageLFMGeometryVis->objectName().isEmpty())
            CXPageLFMGeometryVis->setObjectName(QString::fromUtf8("CXPageLFMGeometryVis"));
        CXPageLFMGeometryVis->resize(444, 439);
        verticalLayout = new QVBoxLayout(CXPageLFMGeometryVis);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gbxDisplayRange = new QGroupBox(CXPageLFMGeometryVis);
        gbxDisplayRange->setObjectName(QString::fromUtf8("gbxDisplayRange"));
        gbxDisplayRange->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(gbxDisplayRange);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_pSliderInline = new CXSliderComplex(gbxDisplayRange);
        m_pSliderInline->setObjectName(QString::fromUtf8("m_pSliderInline"));

        verticalLayout_2->addWidget(m_pSliderInline);

        m_pSliderCrossline = new CXSliderComplex(gbxDisplayRange);
        m_pSliderCrossline->setObjectName(QString::fromUtf8("m_pSliderCrossline"));

        verticalLayout_2->addWidget(m_pSliderCrossline);


        verticalLayout->addWidget(gbxDisplayRange);

        gbxGridLine = new QGroupBox(CXPageLFMGeometryVis);
        gbxGridLine->setObjectName(QString::fromUtf8("gbxGridLine"));
        gbxGridLine->setFlat(true);
        gridLayout_2 = new QGridLayout(gbxGridLine);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lblColor = new QLabel(gbxGridLine);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblColor->sizePolicy().hasHeightForWidth());
        lblColor->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(lblColor, 1, 0, 1, 1);

        m_pClrBtnLine = new CXButtonColorEdit(gbxGridLine);
        m_pClrBtnLine->setObjectName(QString::fromUtf8("m_pClrBtnLine"));

        gridLayout_2->addWidget(m_pClrBtnLine, 1, 1, 1, 1);

        m_pChkTopAndBottomLine = new QCheckBox(gbxGridLine);
        m_pChkTopAndBottomLine->setObjectName(QString::fromUtf8("m_pChkTopAndBottomLine"));

        gridLayout_2->addWidget(m_pChkTopAndBottomLine, 0, 0, 1, 2);

        lblSize = new QLabel(gbxGridLine);
        lblSize->setObjectName(QString::fromUtf8("lblSize"));
        sizePolicy.setHeightForWidth(lblSize->sizePolicy().hasHeightForWidth());
        lblSize->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(lblSize, 1, 2, 1, 1);

        m_pCmbLineSize = new CXLineWidthListCombBox(gbxGridLine);
        m_pCmbLineSize->setObjectName(QString::fromUtf8("m_pCmbLineSize"));

        gridLayout_2->addWidget(m_pCmbLineSize, 1, 3, 1, 1);

        m_pChkHorizontalSlice = new QCheckBox(gbxGridLine);
        m_pChkHorizontalSlice->setObjectName(QString::fromUtf8("m_pChkHorizontalSlice"));

        gridLayout_2->addWidget(m_pChkHorizontalSlice, 0, 2, 1, 2);

        lblVerticalLineSpacing = new QLabel(gbxGridLine);
        lblVerticalLineSpacing->setObjectName(QString::fromUtf8("lblVerticalLineSpacing"));

        gridLayout_2->addWidget(lblVerticalLineSpacing, 1, 4, 1, 1);

        m_pChkVerticalSlice = new QCheckBox(gbxGridLine);
        m_pChkVerticalSlice->setObjectName(QString::fromUtf8("m_pChkVerticalSlice"));

        gridLayout_2->addWidget(m_pChkVerticalSlice, 0, 4, 1, 2);

        m_pCmbVerticalLineSpacing = new QComboBox(gbxGridLine);
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->addItem(QString());
        m_pCmbVerticalLineSpacing->setObjectName(QString::fromUtf8("m_pCmbVerticalLineSpacing"));

        gridLayout_2->addWidget(m_pCmbVerticalLineSpacing, 1, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 6, 1, 1);


        verticalLayout->addWidget(gbxGridLine);

        gbxZoneSetting = new QGroupBox(CXPageLFMGeometryVis);
        gbxZoneSetting->setObjectName(QString::fromUtf8("gbxZoneSetting"));
        gbxZoneSetting->setFlat(true);
        gridLayout = new QGridLayout(gbxZoneSetting);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pTableZone = new QTableWidget(gbxZoneSetting);
        m_pTableZone->setObjectName(QString::fromUtf8("m_pTableZone"));

        gridLayout->addWidget(m_pTableZone, 0, 0, 1, 1);


        verticalLayout->addWidget(gbxZoneSetting);


        retranslateUi(CXPageLFMGeometryVis);

        QMetaObject::connectSlotsByName(CXPageLFMGeometryVis);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageLFMGeometryVis)
    {
        CXPageLFMGeometryVis->setWindowTitle(QCoreApplication::translate("CXPageLFMGeometryVis", "CXPage3DLFMGeometryVis", nullptr));
        gbxDisplayRange->setTitle(QCoreApplication::translate("CXPageLFMGeometryVis", "Display Range", nullptr));
        gbxGridLine->setTitle(QCoreApplication::translate("CXPageLFMGeometryVis", "Grid Line", nullptr));
        lblColor->setText(QCoreApplication::translate("CXPageLFMGeometryVis", "Color:", nullptr));
        m_pClrBtnLine->setText(QString());
        m_pChkTopAndBottomLine->setText(QCoreApplication::translate("CXPageLFMGeometryVis", "Top and Bottom Line", nullptr));
        lblSize->setText(QCoreApplication::translate("CXPageLFMGeometryVis", "Size:", nullptr));
        m_pChkHorizontalSlice->setText(QCoreApplication::translate("CXPageLFMGeometryVis", "Horizontal Slice", nullptr));
        lblVerticalLineSpacing->setText(QCoreApplication::translate("CXPageLFMGeometryVis", "Vertical Line Spacing:", nullptr));
        m_pChkVerticalSlice->setText(QCoreApplication::translate("CXPageLFMGeometryVis", "Vertical Slice", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(0, QCoreApplication::translate("CXPageLFMGeometryVis", "1", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(1, QCoreApplication::translate("CXPageLFMGeometryVis", "2", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(2, QCoreApplication::translate("CXPageLFMGeometryVis", "3", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(3, QCoreApplication::translate("CXPageLFMGeometryVis", "4", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(4, QCoreApplication::translate("CXPageLFMGeometryVis", "5", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(5, QCoreApplication::translate("CXPageLFMGeometryVis", "6", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(6, QCoreApplication::translate("CXPageLFMGeometryVis", "7", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(7, QCoreApplication::translate("CXPageLFMGeometryVis", "8", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(8, QCoreApplication::translate("CXPageLFMGeometryVis", "9", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(9, QCoreApplication::translate("CXPageLFMGeometryVis", "10", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(10, QCoreApplication::translate("CXPageLFMGeometryVis", "20", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(11, QCoreApplication::translate("CXPageLFMGeometryVis", "30", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(12, QCoreApplication::translate("CXPageLFMGeometryVis", "50", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(13, QCoreApplication::translate("CXPageLFMGeometryVis", "80", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(14, QCoreApplication::translate("CXPageLFMGeometryVis", "100", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(15, QCoreApplication::translate("CXPageLFMGeometryVis", "120", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(16, QCoreApplication::translate("CXPageLFMGeometryVis", "150", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(17, QCoreApplication::translate("CXPageLFMGeometryVis", "200", nullptr));
        m_pCmbVerticalLineSpacing->setItemText(18, QCoreApplication::translate("CXPageLFMGeometryVis", "300", nullptr));

        gbxZoneSetting->setTitle(QCoreApplication::translate("CXPageLFMGeometryVis", "Zone Setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageLFMGeometryVis: public Ui_CXPageLFMGeometryVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGELFMGEOMETRYVIS_H
