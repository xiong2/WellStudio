/********************************************************************************
** Form generated from reading UI file 'xpagesectionwellcurvevis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESECTIONWELLCURVEVIS_H
#define UI_XPAGESECTIONWELLCURVEVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageSectionWellCurveVis
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *m_pGbxMode;
    QHBoxLayout *horizontalLayout;
    QRadioButton *m_pRadioBtnCurve;
    QRadioButton *m_pRadioBtnVI;
    QSpacerItem *horizontalSpacer;
    QGroupBox *m_pGbxVI;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_pLblVIWidth;
    QLineEdit *m_pEdtVIWidth;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *m_pGbxLine;
    QGridLayout *gridLayout;
    QCheckBox *m_pChkVisibleLine;
    QLabel *m_pLblLineWidth;
    QLabel *m_pLblLineColor;
    CXButtonColorEdit *m_pClrBtnLine;
    QLineEdit *m_pEdtLineWidth;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *m_pGbxFill;
    QGridLayout *gridLayout_2;
    CXButtonColorEdit *m_pClrBtnFill;
    QLabel *m_pLblFillColor;
    QLineEdit *m_pEdtFillWidth;
    QCheckBox *m_pChkVisibleFill;
    QLabel *m_pLblFillWidth;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *m_pGbxFilter;
    QGridLayout *gridLayout_5;
    QComboBox *m_pCbbFilterType;
    QLabel *m_pLblFilterType;
    QGroupBox *m_pGbxHighValues;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *m_pDsbxHighFreq;
    QLabel *m_pLblHighFreq;
    QLabel *m_pLblHighOverlap;
    QDoubleSpinBox *m_pDsbxHighOverlap;
    QGroupBox *m_pGbxLowValues;
    QGridLayout *gridLayout_4;
    QLabel *m_pLblLowFreq;
    QDoubleSpinBox *m_pDsbxLowFreq;
    QLabel *m_pLblLowOverlap;
    QDoubleSpinBox *m_pDsbxLowOverlap;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPageSectionWellCurveVis)
    {
        if (CXPageSectionWellCurveVis->objectName().isEmpty())
            CXPageSectionWellCurveVis->setObjectName(QString::fromUtf8("CXPageSectionWellCurveVis"));
        CXPageSectionWellCurveVis->resize(446, 490);
        verticalLayout = new QVBoxLayout(CXPageSectionWellCurveVis);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pGbxMode = new QGroupBox(CXPageSectionWellCurveVis);
        m_pGbxMode->setObjectName(QString::fromUtf8("m_pGbxMode"));
        m_pGbxMode->setFlat(true);
        horizontalLayout = new QHBoxLayout(m_pGbxMode);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pRadioBtnCurve = new QRadioButton(m_pGbxMode);
        m_pRadioBtnCurve->setObjectName(QString::fromUtf8("m_pRadioBtnCurve"));
        m_pRadioBtnCurve->setChecked(true);

        horizontalLayout->addWidget(m_pRadioBtnCurve);

        m_pRadioBtnVI = new QRadioButton(m_pGbxMode);
        m_pRadioBtnVI->setObjectName(QString::fromUtf8("m_pRadioBtnVI"));

        horizontalLayout->addWidget(m_pRadioBtnVI);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(m_pGbxMode);

        m_pGbxVI = new QGroupBox(CXPageSectionWellCurveVis);
        m_pGbxVI->setObjectName(QString::fromUtf8("m_pGbxVI"));
        horizontalLayout_2 = new QHBoxLayout(m_pGbxVI);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_pLblVIWidth = new QLabel(m_pGbxVI);
        m_pLblVIWidth->setObjectName(QString::fromUtf8("m_pLblVIWidth"));

        horizontalLayout_2->addWidget(m_pLblVIWidth);

        m_pEdtVIWidth = new QLineEdit(m_pGbxVI);
        m_pEdtVIWidth->setObjectName(QString::fromUtf8("m_pEdtVIWidth"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pEdtVIWidth->sizePolicy().hasHeightForWidth());
        m_pEdtVIWidth->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_pEdtVIWidth);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        m_pLblVIWidth->raise();
        m_pEdtVIWidth->raise();

        verticalLayout->addWidget(m_pGbxVI);

        m_pGbxLine = new QGroupBox(CXPageSectionWellCurveVis);
        m_pGbxLine->setObjectName(QString::fromUtf8("m_pGbxLine"));
        m_pGbxLine->setFlat(true);
        gridLayout = new QGridLayout(m_pGbxLine);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pChkVisibleLine = new QCheckBox(m_pGbxLine);
        m_pChkVisibleLine->setObjectName(QString::fromUtf8("m_pChkVisibleLine"));
        m_pChkVisibleLine->setChecked(true);

        gridLayout->addWidget(m_pChkVisibleLine, 0, 0, 1, 2);

        m_pLblLineWidth = new QLabel(m_pGbxLine);
        m_pLblLineWidth->setObjectName(QString::fromUtf8("m_pLblLineWidth"));

        gridLayout->addWidget(m_pLblLineWidth, 1, 0, 1, 1);

        m_pLblLineColor = new QLabel(m_pGbxLine);
        m_pLblLineColor->setObjectName(QString::fromUtf8("m_pLblLineColor"));

        gridLayout->addWidget(m_pLblLineColor, 1, 2, 1, 1);

        m_pClrBtnLine = new CXButtonColorEdit(m_pGbxLine);
        m_pClrBtnLine->setObjectName(QString::fromUtf8("m_pClrBtnLine"));

        gridLayout->addWidget(m_pClrBtnLine, 1, 3, 1, 1);

        m_pEdtLineWidth = new QLineEdit(m_pGbxLine);
        m_pEdtLineWidth->setObjectName(QString::fromUtf8("m_pEdtLineWidth"));
        sizePolicy.setHeightForWidth(m_pEdtLineWidth->sizePolicy().hasHeightForWidth());
        m_pEdtLineWidth->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_pEdtLineWidth, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);


        verticalLayout->addWidget(m_pGbxLine);

        m_pGbxFill = new QGroupBox(CXPageSectionWellCurveVis);
        m_pGbxFill->setObjectName(QString::fromUtf8("m_pGbxFill"));
        m_pGbxFill->setFlat(true);
        gridLayout_2 = new QGridLayout(m_pGbxFill);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pClrBtnFill = new CXButtonColorEdit(m_pGbxFill);
        m_pClrBtnFill->setObjectName(QString::fromUtf8("m_pClrBtnFill"));

        gridLayout_2->addWidget(m_pClrBtnFill, 1, 3, 1, 1);

        m_pLblFillColor = new QLabel(m_pGbxFill);
        m_pLblFillColor->setObjectName(QString::fromUtf8("m_pLblFillColor"));

        gridLayout_2->addWidget(m_pLblFillColor, 1, 2, 1, 1);

        m_pEdtFillWidth = new QLineEdit(m_pGbxFill);
        m_pEdtFillWidth->setObjectName(QString::fromUtf8("m_pEdtFillWidth"));
        sizePolicy.setHeightForWidth(m_pEdtFillWidth->sizePolicy().hasHeightForWidth());
        m_pEdtFillWidth->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_pEdtFillWidth, 1, 1, 1, 1);

        m_pChkVisibleFill = new QCheckBox(m_pGbxFill);
        m_pChkVisibleFill->setObjectName(QString::fromUtf8("m_pChkVisibleFill"));

        gridLayout_2->addWidget(m_pChkVisibleFill, 0, 0, 1, 2);

        m_pLblFillWidth = new QLabel(m_pGbxFill);
        m_pLblFillWidth->setObjectName(QString::fromUtf8("m_pLblFillWidth"));

        gridLayout_2->addWidget(m_pLblFillWidth, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 4, 1, 1);


        verticalLayout->addWidget(m_pGbxFill);

        m_pGbxFilter = new QGroupBox(CXPageSectionWellCurveVis);
        m_pGbxFilter->setObjectName(QString::fromUtf8("m_pGbxFilter"));
        m_pGbxFilter->setFlat(true);
        gridLayout_5 = new QGridLayout(m_pGbxFilter);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_pCbbFilterType = new QComboBox(m_pGbxFilter);
        m_pCbbFilterType->addItem(QString());
        m_pCbbFilterType->addItem(QString());
        m_pCbbFilterType->addItem(QString());
        m_pCbbFilterType->addItem(QString());
        m_pCbbFilterType->setObjectName(QString::fromUtf8("m_pCbbFilterType"));

        gridLayout_5->addWidget(m_pCbbFilterType, 0, 1, 1, 1);

        m_pLblFilterType = new QLabel(m_pGbxFilter);
        m_pLblFilterType->setObjectName(QString::fromUtf8("m_pLblFilterType"));

        gridLayout_5->addWidget(m_pLblFilterType, 0, 0, 1, 1);

        m_pGbxHighValues = new QGroupBox(m_pGbxFilter);
        m_pGbxHighValues->setObjectName(QString::fromUtf8("m_pGbxHighValues"));
        gridLayout_3 = new QGridLayout(m_pGbxHighValues);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pDsbxHighFreq = new QDoubleSpinBox(m_pGbxHighValues);
        m_pDsbxHighFreq->setObjectName(QString::fromUtf8("m_pDsbxHighFreq"));
        m_pDsbxHighFreq->setMaximum(9999999999.989999771118164);

        gridLayout_3->addWidget(m_pDsbxHighFreq, 0, 1, 1, 1);

        m_pLblHighFreq = new QLabel(m_pGbxHighValues);
        m_pLblHighFreq->setObjectName(QString::fromUtf8("m_pLblHighFreq"));

        gridLayout_3->addWidget(m_pLblHighFreq, 0, 0, 1, 1);

        m_pLblHighOverlap = new QLabel(m_pGbxHighValues);
        m_pLblHighOverlap->setObjectName(QString::fromUtf8("m_pLblHighOverlap"));

        gridLayout_3->addWidget(m_pLblHighOverlap, 1, 0, 1, 1);

        m_pDsbxHighOverlap = new QDoubleSpinBox(m_pGbxHighValues);
        m_pDsbxHighOverlap->setObjectName(QString::fromUtf8("m_pDsbxHighOverlap"));
        m_pDsbxHighOverlap->setMaximum(9999999999.989999771118164);

        gridLayout_3->addWidget(m_pDsbxHighOverlap, 1, 1, 1, 1);


        gridLayout_5->addWidget(m_pGbxHighValues, 1, 2, 1, 1);

        m_pGbxLowValues = new QGroupBox(m_pGbxFilter);
        m_pGbxLowValues->setObjectName(QString::fromUtf8("m_pGbxLowValues"));
        gridLayout_4 = new QGridLayout(m_pGbxLowValues);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_pLblLowFreq = new QLabel(m_pGbxLowValues);
        m_pLblLowFreq->setObjectName(QString::fromUtf8("m_pLblLowFreq"));

        gridLayout_4->addWidget(m_pLblLowFreq, 0, 0, 1, 1);

        m_pDsbxLowFreq = new QDoubleSpinBox(m_pGbxLowValues);
        m_pDsbxLowFreq->setObjectName(QString::fromUtf8("m_pDsbxLowFreq"));
        m_pDsbxLowFreq->setMaximum(9999999999.989999771118164);

        gridLayout_4->addWidget(m_pDsbxLowFreq, 0, 1, 1, 1);

        m_pLblLowOverlap = new QLabel(m_pGbxLowValues);
        m_pLblLowOverlap->setObjectName(QString::fromUtf8("m_pLblLowOverlap"));

        gridLayout_4->addWidget(m_pLblLowOverlap, 1, 0, 1, 1);

        m_pDsbxLowOverlap = new QDoubleSpinBox(m_pGbxLowValues);
        m_pDsbxLowOverlap->setObjectName(QString::fromUtf8("m_pDsbxLowOverlap"));
        m_pDsbxLowOverlap->setMaximum(9999999999.989999771118164);

        gridLayout_4->addWidget(m_pDsbxLowOverlap, 1, 1, 1, 1);


        gridLayout_5->addWidget(m_pGbxLowValues, 1, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 1, 3, 1, 1);


        verticalLayout->addWidget(m_pGbxFilter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPageSectionWellCurveVis);
        QObject::connect(m_pRadioBtnVI, SIGNAL(toggled(bool)), m_pGbxVI, SLOT(setVisible(bool)));
        QObject::connect(m_pRadioBtnVI, SIGNAL(toggled(bool)), m_pGbxLine, SLOT(setHidden(bool)));
        QObject::connect(m_pRadioBtnVI, SIGNAL(toggled(bool)), m_pGbxFill, SLOT(setHidden(bool)));

        QMetaObject::connectSlotsByName(CXPageSectionWellCurveVis);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageSectionWellCurveVis)
    {
        CXPageSectionWellCurveVis->setWindowTitle(QCoreApplication::translate("CXPageSectionWellCurveVis", "CXPageSectionWellCurveVis", nullptr));
        m_pGbxMode->setTitle(QCoreApplication::translate("CXPageSectionWellCurveVis", "Display Mode", nullptr));
        m_pRadioBtnCurve->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Curve", nullptr));
        m_pRadioBtnVI->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Variable Indensity", nullptr));
        m_pGbxVI->setTitle(QCoreApplication::translate("CXPageSectionWellCurveVis", "VI", nullptr));
        m_pLblVIWidth->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Width:", nullptr));
        m_pGbxLine->setTitle(QCoreApplication::translate("CXPageSectionWellCurveVis", "Line", nullptr));
        m_pChkVisibleLine->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Visible", nullptr));
        m_pLblLineWidth->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Width: ", nullptr));
        m_pLblLineColor->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Color: ", nullptr));
        m_pClrBtnLine->setText(QString());
        m_pGbxFill->setTitle(QCoreApplication::translate("CXPageSectionWellCurveVis", "Fill", nullptr));
        m_pClrBtnFill->setText(QString());
        m_pLblFillColor->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Color: ", nullptr));
        m_pChkVisibleFill->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Visible", nullptr));
        m_pLblFillWidth->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Width: ", nullptr));
        m_pGbxFilter->setTitle(QCoreApplication::translate("CXPageSectionWellCurveVis", "Filter", nullptr));
        m_pCbbFilterType->setItemText(0, QCoreApplication::translate("CXPageSectionWellCurveVis", "No filtering", nullptr));
        m_pCbbFilterType->setItemText(1, QCoreApplication::translate("CXPageSectionWellCurveVis", "Low pass filter", nullptr));
        m_pCbbFilterType->setItemText(2, QCoreApplication::translate("CXPageSectionWellCurveVis", "Band pass filter", nullptr));
        m_pCbbFilterType->setItemText(3, QCoreApplication::translate("CXPageSectionWellCurveVis", "High pass filter", nullptr));

        m_pLblFilterType->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Filter type", nullptr));
        m_pGbxHighValues->setTitle(QCoreApplication::translate("CXPageSectionWellCurveVis", "High pass parameter", nullptr));
        m_pLblHighFreq->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Frequency", nullptr));
        m_pLblHighOverlap->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Overlap", nullptr));
        m_pGbxLowValues->setTitle(QCoreApplication::translate("CXPageSectionWellCurveVis", "Low pass parameter", nullptr));
        m_pLblLowFreq->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Frequency", nullptr));
        m_pLblLowOverlap->setText(QCoreApplication::translate("CXPageSectionWellCurveVis", "Overlap", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageSectionWellCurveVis: public Ui_CXPageSectionWellCurveVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESECTIONWELLCURVEVIS_H
