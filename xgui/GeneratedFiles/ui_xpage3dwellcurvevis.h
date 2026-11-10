/********************************************************************************
** Form generated from reading UI file 'xpage3dwellcurvevis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGE3DWELLCURVEVIS_H
#define UI_XPAGE3DWELLCURVEVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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

class Ui_CXPage3DWellCurveVis
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *m_pGbxMode;
    QHBoxLayout *horizontalLayout;
    QRadioButton *m_pRadioBtnCylinder;
    QRadioButton *m_pRadioBtnFlat;
    QSpacerItem *horizontalSpacer;
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
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPage3DWellCurveVis)
    {
        if (CXPage3DWellCurveVis->objectName().isEmpty())
            CXPage3DWellCurveVis->setObjectName(QString::fromUtf8("CXPage3DWellCurveVis"));
        CXPage3DWellCurveVis->resize(334, 287);
        verticalLayout = new QVBoxLayout(CXPage3DWellCurveVis);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pGbxMode = new QGroupBox(CXPage3DWellCurveVis);
        m_pGbxMode->setObjectName(QString::fromUtf8("m_pGbxMode"));
        m_pGbxMode->setFlat(true);
        horizontalLayout = new QHBoxLayout(m_pGbxMode);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pRadioBtnCylinder = new QRadioButton(m_pGbxMode);
        m_pRadioBtnCylinder->setObjectName(QString::fromUtf8("m_pRadioBtnCylinder"));
        m_pRadioBtnCylinder->setChecked(true);

        horizontalLayout->addWidget(m_pRadioBtnCylinder);

        m_pRadioBtnFlat = new QRadioButton(m_pGbxMode);
        m_pRadioBtnFlat->setObjectName(QString::fromUtf8("m_pRadioBtnFlat"));

        horizontalLayout->addWidget(m_pRadioBtnFlat);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(m_pGbxMode);

        m_pGbxLine = new QGroupBox(CXPage3DWellCurveVis);
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

        gridLayout->addWidget(m_pEdtLineWidth, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);


        verticalLayout->addWidget(m_pGbxLine);

        m_pGbxFill = new QGroupBox(CXPage3DWellCurveVis);
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

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPage3DWellCurveVis);

        QMetaObject::connectSlotsByName(CXPage3DWellCurveVis);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPage3DWellCurveVis)
    {
        CXPage3DWellCurveVis->setWindowTitle(QCoreApplication::translate("CXPage3DWellCurveVis", "CXPage3DWellCurveVis", nullptr));
        m_pGbxMode->setTitle(QCoreApplication::translate("CXPage3DWellCurveVis", "Display Mode", nullptr));
        m_pRadioBtnCylinder->setText(QCoreApplication::translate("CXPage3DWellCurveVis", "Cylinder", nullptr));
        m_pRadioBtnFlat->setText(QCoreApplication::translate("CXPage3DWellCurveVis", "Flat", nullptr));
        m_pGbxLine->setTitle(QCoreApplication::translate("CXPage3DWellCurveVis", "Line", nullptr));
        m_pChkVisibleLine->setText(QCoreApplication::translate("CXPage3DWellCurveVis", "Visible", nullptr));
        m_pLblLineWidth->setText(QCoreApplication::translate("CXPage3DWellCurveVis", "Width: ", nullptr));
        m_pLblLineColor->setText(QCoreApplication::translate("CXPage3DWellCurveVis", "Color: ", nullptr));
        m_pClrBtnLine->setText(QString());
        m_pGbxFill->setTitle(QCoreApplication::translate("CXPage3DWellCurveVis", "Fill", nullptr));
        m_pClrBtnFill->setText(QString());
        m_pLblFillColor->setText(QCoreApplication::translate("CXPage3DWellCurveVis", "Color: ", nullptr));
        m_pChkVisibleFill->setText(QCoreApplication::translate("CXPage3DWellCurveVis", "Visible", nullptr));
        m_pLblFillWidth->setText(QCoreApplication::translate("CXPage3DWellCurveVis", "Width: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPage3DWellCurveVis: public Ui_CXPage3DWellCurveVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGE3DWELLCURVEVIS_H
