/********************************************************************************
** Form generated from reading UI file 'xpagetimeslicevis.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGETIMESLICEVIS_H
#define UI_XPAGETIMESLICEVIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"
#include "xcolorbutton.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageTimeSliceVis
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *m_pStackedWidget;
    QWidget *m_pPageSection;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_section_linecolor;
    CXColorButton *m_pClrBtnSectionLineColor;
    QLabel *lbl_section_linewidth;
    CXLineWidthListCombBox *m_pCbbSectionLineWidth;
    QLabel *lbl_section_linetype;
    CXLineTypeListCombBox *m_pCbbSectionLineType;
    QSpacerItem *verticalSpacer_2;
    QWidget *m_pPageBM;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *gbxBMMode;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *m_pRdoBMSeismic;
    QRadioButton *m_pRdoBMFrac;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *gbxBMFrame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbl_bm_framecolor;
    CXButtonColorEdit *m_pClrBtnBMFrameColor;
    QLabel *lbl_bm_framewidth;
    CXLineWidthListCombBox *m_pCbbBMFrameWidth;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *m_pGbxBMFrac;
    QGridLayout *gridLayout_2;
    QCheckBox *m_pChkBMSeismic;
    QLabel *lbl_bm_frac_min_percent;
    QLabel *lbl_bm_frac_dy_trace;
    QComboBox *m_pCbbBMFracDen;
    QLineEdit *m_pEdtBMFracMax;
    QLineEdit *m_pEdtBMFracWidth;
    QLabel *lbl_bm_frac_scale;
    QLineEdit *m_pEdtBMFracMin;
    QLabel *lbl_bm_frac_color;
    QLabel *lbl_bm_frac_width;
    QLineEdit *m_pEdtBMFracDY;
    QLineEdit *m_pEdtBMFracScale;
    QLabel *lbl_bm_frac_dx;
    QLabel *lbl_bm_frac_azi;
    QComboBox *m_pCbbBMFracAzi;
    QLabel *lbl_bm_frac_max;
    QLabel *lbl_bm_frac_dx_trace;
    QLabel *lbl_bm_frac_dy;
    QLabel *lbl_bm_frac_max_percent;
    QLabel *lbl_bm_frac_min;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_10;
    CXButtonColorEdit *m_pClrBtnBMFracColor;
    QLabel *lbl_bm_frac_den;
    QLineEdit *m_pEdtBMFracDX;
    QSpacerItem *verticalSpacer_3;
    QWidget *m_pPage3D;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *gbx3DMode;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *m_pRdo3DSeismic;
    QRadioButton *m_pRdo3DFrac;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *m_pGbx3DFrac;
    QGridLayout *gridLayout;
    QLineEdit *m_pEdt3DFracDY;
    QLabel *lbl_3d_frac_dx;
    QLabel *lbl_3d_frac_dy_trace;
    QLineEdit *m_pEdt3DFracDX;
    QLabel *lbl_3d_frac_dx_trace;
    QLabel *lbl_3d_frac_dy;
    QSpacerItem *horizontalSpacer_9;
    QLabel *lbl_3d_frac_azi;
    QLabel *lbl_3d_frac_den;
    QComboBox *m_pCbb3DFracAzi;
    QComboBox *m_pCbb3DFracDen;
    QCheckBox *m_pChk3DFracSeismic;
    QLabel *lbl_3d_frac_scale;
    QLabel *lbl_3d_frac_min;
    QLabel *lbl_3d_frac_min_percent;
    QLineEdit *m_pEdt3DFracScale;
    QSpacerItem *horizontalSpacer_8;
    QLabel *lbl_3d_frac_max;
    QLabel *lbl_3d_frac_max_percent;
    QLabel *lbl_3d_frac_color;
    CXButtonColorEdit *m_pClrBtn3DFracColor;
    QLineEdit *m_pEdt3DFracMax;
    QLineEdit *m_pEdt3DFracMin;
    QLabel *m_pLbl3DFracHeight;
    QLineEdit *m_pEdt3DFracHeight;
    QSpacerItem *verticalSpacer;

    void setupUi(CXBasePropertyPage *CXPageTimeSliceVis)
    {
        if (CXPageTimeSliceVis->objectName().isEmpty())
            CXPageTimeSliceVis->setObjectName(QString::fromUtf8("CXPageTimeSliceVis"));
        CXPageTimeSliceVis->resize(597, 412);
        verticalLayout = new QVBoxLayout(CXPageTimeSliceVis);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pStackedWidget = new QStackedWidget(CXPageTimeSliceVis);
        m_pStackedWidget->setObjectName(QString::fromUtf8("m_pStackedWidget"));
        m_pPageSection = new QWidget();
        m_pPageSection->setObjectName(QString::fromUtf8("m_pPageSection"));
        verticalLayout_3 = new QVBoxLayout(m_pPageSection);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lbl_section_linecolor = new QLabel(m_pPageSection);
        lbl_section_linecolor->setObjectName(QString::fromUtf8("lbl_section_linecolor"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbl_section_linecolor->sizePolicy().hasHeightForWidth());
        lbl_section_linecolor->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lbl_section_linecolor);

        m_pClrBtnSectionLineColor = new CXColorButton(m_pPageSection);
        m_pClrBtnSectionLineColor->setObjectName(QString::fromUtf8("m_pClrBtnSectionLineColor"));

        horizontalLayout_3->addWidget(m_pClrBtnSectionLineColor);

        lbl_section_linewidth = new QLabel(m_pPageSection);
        lbl_section_linewidth->setObjectName(QString::fromUtf8("lbl_section_linewidth"));
        sizePolicy.setHeightForWidth(lbl_section_linewidth->sizePolicy().hasHeightForWidth());
        lbl_section_linewidth->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lbl_section_linewidth);

        m_pCbbSectionLineWidth = new CXLineWidthListCombBox(m_pPageSection);
        m_pCbbSectionLineWidth->setObjectName(QString::fromUtf8("m_pCbbSectionLineWidth"));

        horizontalLayout_3->addWidget(m_pCbbSectionLineWidth);

        lbl_section_linetype = new QLabel(m_pPageSection);
        lbl_section_linetype->setObjectName(QString::fromUtf8("lbl_section_linetype"));
        sizePolicy.setHeightForWidth(lbl_section_linetype->sizePolicy().hasHeightForWidth());
        lbl_section_linetype->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lbl_section_linetype);

        m_pCbbSectionLineType = new CXLineTypeListCombBox(m_pPageSection);
        m_pCbbSectionLineType->setObjectName(QString::fromUtf8("m_pCbbSectionLineType"));

        horizontalLayout_3->addWidget(m_pCbbSectionLineType);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        m_pStackedWidget->addWidget(m_pPageSection);
        m_pPageBM = new QWidget();
        m_pPageBM->setObjectName(QString::fromUtf8("m_pPageBM"));
        verticalLayout_4 = new QVBoxLayout(m_pPageBM);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gbxBMMode = new QGroupBox(m_pPageBM);
        gbxBMMode->setObjectName(QString::fromUtf8("gbxBMMode"));
        gbxBMMode->setFlat(true);
        horizontalLayout_5 = new QHBoxLayout(gbxBMMode);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_pRdoBMSeismic = new QRadioButton(gbxBMMode);
        m_pRdoBMSeismic->setObjectName(QString::fromUtf8("m_pRdoBMSeismic"));
        m_pRdoBMSeismic->setChecked(true);

        horizontalLayout_5->addWidget(m_pRdoBMSeismic);

        m_pRdoBMFrac = new QRadioButton(gbxBMMode);
        m_pRdoBMFrac->setObjectName(QString::fromUtf8("m_pRdoBMFrac"));

        horizontalLayout_5->addWidget(m_pRdoBMFrac);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_4->addWidget(gbxBMMode);

        gbxBMFrame = new QGroupBox(m_pPageBM);
        gbxBMFrame->setObjectName(QString::fromUtf8("gbxBMFrame"));
        gbxBMFrame->setFlat(true);
        horizontalLayout_4 = new QHBoxLayout(gbxBMFrame);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lbl_bm_framecolor = new QLabel(gbxBMFrame);
        lbl_bm_framecolor->setObjectName(QString::fromUtf8("lbl_bm_framecolor"));

        horizontalLayout_4->addWidget(lbl_bm_framecolor);

        m_pClrBtnBMFrameColor = new CXButtonColorEdit(gbxBMFrame);
        m_pClrBtnBMFrameColor->setObjectName(QString::fromUtf8("m_pClrBtnBMFrameColor"));

        horizontalLayout_4->addWidget(m_pClrBtnBMFrameColor);

        lbl_bm_framewidth = new QLabel(gbxBMFrame);
        lbl_bm_framewidth->setObjectName(QString::fromUtf8("lbl_bm_framewidth"));

        horizontalLayout_4->addWidget(lbl_bm_framewidth);

        m_pCbbBMFrameWidth = new CXLineWidthListCombBox(gbxBMFrame);
        m_pCbbBMFrameWidth->setObjectName(QString::fromUtf8("m_pCbbBMFrameWidth"));

        horizontalLayout_4->addWidget(m_pCbbBMFrameWidth);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addWidget(gbxBMFrame);

        m_pGbxBMFrac = new QGroupBox(m_pPageBM);
        m_pGbxBMFrac->setObjectName(QString::fromUtf8("m_pGbxBMFrac"));
        m_pGbxBMFrac->setFlat(true);
        gridLayout_2 = new QGridLayout(m_pGbxBMFrac);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pChkBMSeismic = new QCheckBox(m_pGbxBMFrac);
        m_pChkBMSeismic->setObjectName(QString::fromUtf8("m_pChkBMSeismic"));
        m_pChkBMSeismic->setChecked(true);

        gridLayout_2->addWidget(m_pChkBMSeismic, 0, 0, 1, 2);

        lbl_bm_frac_min_percent = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_min_percent->setObjectName(QString::fromUtf8("lbl_bm_frac_min_percent"));

        gridLayout_2->addWidget(lbl_bm_frac_min_percent, 4, 7, 1, 1);

        lbl_bm_frac_dy_trace = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_dy_trace->setObjectName(QString::fromUtf8("lbl_bm_frac_dy_trace"));

        gridLayout_2->addWidget(lbl_bm_frac_dy_trace, 6, 2, 1, 1);

        m_pCbbBMFracDen = new QComboBox(m_pGbxBMFrac);
        m_pCbbBMFracDen->setObjectName(QString::fromUtf8("m_pCbbBMFracDen"));

        gridLayout_2->addWidget(m_pCbbBMFracDen, 3, 1, 1, 1);

        m_pEdtBMFracMax = new QLineEdit(m_pGbxBMFrac);
        m_pEdtBMFracMax->setObjectName(QString::fromUtf8("m_pEdtBMFracMax"));

        gridLayout_2->addWidget(m_pEdtBMFracMax, 6, 5, 1, 1);

        m_pEdtBMFracWidth = new QLineEdit(m_pGbxBMFrac);
        m_pEdtBMFracWidth->setObjectName(QString::fromUtf8("m_pEdtBMFracWidth"));

        gridLayout_2->addWidget(m_pEdtBMFracWidth, 7, 5, 1, 1);

        lbl_bm_frac_scale = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_scale->setObjectName(QString::fromUtf8("lbl_bm_frac_scale"));

        gridLayout_2->addWidget(lbl_bm_frac_scale, 7, 0, 1, 1);

        m_pEdtBMFracMin = new QLineEdit(m_pGbxBMFrac);
        m_pEdtBMFracMin->setObjectName(QString::fromUtf8("m_pEdtBMFracMin"));

        gridLayout_2->addWidget(m_pEdtBMFracMin, 4, 5, 1, 1);

        lbl_bm_frac_color = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_color->setObjectName(QString::fromUtf8("lbl_bm_frac_color"));

        gridLayout_2->addWidget(lbl_bm_frac_color, 1, 0, 1, 1);

        lbl_bm_frac_width = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_width->setObjectName(QString::fromUtf8("lbl_bm_frac_width"));

        gridLayout_2->addWidget(lbl_bm_frac_width, 7, 4, 1, 1);

        m_pEdtBMFracDY = new QLineEdit(m_pGbxBMFrac);
        m_pEdtBMFracDY->setObjectName(QString::fromUtf8("m_pEdtBMFracDY"));

        gridLayout_2->addWidget(m_pEdtBMFracDY, 6, 1, 1, 1);

        m_pEdtBMFracScale = new QLineEdit(m_pGbxBMFrac);
        m_pEdtBMFracScale->setObjectName(QString::fromUtf8("m_pEdtBMFracScale"));

        gridLayout_2->addWidget(m_pEdtBMFracScale, 7, 1, 1, 1);

        lbl_bm_frac_dx = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_dx->setObjectName(QString::fromUtf8("lbl_bm_frac_dx"));

        gridLayout_2->addWidget(lbl_bm_frac_dx, 4, 0, 1, 1);

        lbl_bm_frac_azi = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_azi->setObjectName(QString::fromUtf8("lbl_bm_frac_azi"));

        gridLayout_2->addWidget(lbl_bm_frac_azi, 2, 0, 1, 1);

        m_pCbbBMFracAzi = new QComboBox(m_pGbxBMFrac);
        m_pCbbBMFracAzi->setObjectName(QString::fromUtf8("m_pCbbBMFracAzi"));

        gridLayout_2->addWidget(m_pCbbBMFracAzi, 2, 1, 1, 1);

        lbl_bm_frac_max = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_max->setObjectName(QString::fromUtf8("lbl_bm_frac_max"));

        gridLayout_2->addWidget(lbl_bm_frac_max, 6, 4, 1, 1);

        lbl_bm_frac_dx_trace = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_dx_trace->setObjectName(QString::fromUtf8("lbl_bm_frac_dx_trace"));

        gridLayout_2->addWidget(lbl_bm_frac_dx_trace, 4, 2, 1, 1);

        lbl_bm_frac_dy = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_dy->setObjectName(QString::fromUtf8("lbl_bm_frac_dy"));

        gridLayout_2->addWidget(lbl_bm_frac_dy, 6, 0, 1, 1);

        lbl_bm_frac_max_percent = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_max_percent->setObjectName(QString::fromUtf8("lbl_bm_frac_max_percent"));

        gridLayout_2->addWidget(lbl_bm_frac_max_percent, 6, 7, 1, 1);

        lbl_bm_frac_min = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_min->setObjectName(QString::fromUtf8("lbl_bm_frac_min"));

        gridLayout_2->addWidget(lbl_bm_frac_min, 4, 4, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 4, 8, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 4, 3, 1, 1);

        m_pClrBtnBMFracColor = new CXButtonColorEdit(m_pGbxBMFrac);
        m_pClrBtnBMFracColor->setObjectName(QString::fromUtf8("m_pClrBtnBMFracColor"));

        gridLayout_2->addWidget(m_pClrBtnBMFracColor, 1, 1, 1, 1);

        lbl_bm_frac_den = new QLabel(m_pGbxBMFrac);
        lbl_bm_frac_den->setObjectName(QString::fromUtf8("lbl_bm_frac_den"));

        gridLayout_2->addWidget(lbl_bm_frac_den, 3, 0, 1, 1);

        m_pEdtBMFracDX = new QLineEdit(m_pGbxBMFrac);
        m_pEdtBMFracDX->setObjectName(QString::fromUtf8("m_pEdtBMFracDX"));

        gridLayout_2->addWidget(m_pEdtBMFracDX, 4, 1, 1, 1);


        verticalLayout_4->addWidget(m_pGbxBMFrac);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        m_pStackedWidget->addWidget(m_pPageBM);
        m_pPage3D = new QWidget();
        m_pPage3D->setObjectName(QString::fromUtf8("m_pPage3D"));
        verticalLayout_2 = new QVBoxLayout(m_pPage3D);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gbx3DMode = new QGroupBox(m_pPage3D);
        gbx3DMode->setObjectName(QString::fromUtf8("gbx3DMode"));
        gbx3DMode->setFlat(true);
        horizontalLayout_2 = new QHBoxLayout(gbx3DMode);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_pRdo3DSeismic = new QRadioButton(gbx3DMode);
        m_pRdo3DSeismic->setObjectName(QString::fromUtf8("m_pRdo3DSeismic"));
        m_pRdo3DSeismic->setChecked(true);

        horizontalLayout_2->addWidget(m_pRdo3DSeismic);

        m_pRdo3DFrac = new QRadioButton(gbx3DMode);
        m_pRdo3DFrac->setObjectName(QString::fromUtf8("m_pRdo3DFrac"));

        horizontalLayout_2->addWidget(m_pRdo3DFrac);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(gbx3DMode);

        m_pGbx3DFrac = new QGroupBox(m_pPage3D);
        m_pGbx3DFrac->setObjectName(QString::fromUtf8("m_pGbx3DFrac"));
        m_pGbx3DFrac->setFlat(true);
        gridLayout = new QGridLayout(m_pGbx3DFrac);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pEdt3DFracDY = new QLineEdit(m_pGbx3DFrac);
        m_pEdt3DFracDY->setObjectName(QString::fromUtf8("m_pEdt3DFracDY"));

        gridLayout->addWidget(m_pEdt3DFracDY, 6, 1, 1, 1);

        lbl_3d_frac_dx = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_dx->setObjectName(QString::fromUtf8("lbl_3d_frac_dx"));

        gridLayout->addWidget(lbl_3d_frac_dx, 4, 0, 1, 1);

        lbl_3d_frac_dy_trace = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_dy_trace->setObjectName(QString::fromUtf8("lbl_3d_frac_dy_trace"));

        gridLayout->addWidget(lbl_3d_frac_dy_trace, 6, 2, 1, 1);

        m_pEdt3DFracDX = new QLineEdit(m_pGbx3DFrac);
        m_pEdt3DFracDX->setObjectName(QString::fromUtf8("m_pEdt3DFracDX"));

        gridLayout->addWidget(m_pEdt3DFracDX, 4, 1, 1, 1);

        lbl_3d_frac_dx_trace = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_dx_trace->setObjectName(QString::fromUtf8("lbl_3d_frac_dx_trace"));

        gridLayout->addWidget(lbl_3d_frac_dx_trace, 4, 2, 1, 1);

        lbl_3d_frac_dy = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_dy->setObjectName(QString::fromUtf8("lbl_3d_frac_dy"));

        gridLayout->addWidget(lbl_3d_frac_dy, 6, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 4, 3, 1, 1);

        lbl_3d_frac_azi = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_azi->setObjectName(QString::fromUtf8("lbl_3d_frac_azi"));

        gridLayout->addWidget(lbl_3d_frac_azi, 2, 0, 1, 1);

        lbl_3d_frac_den = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_den->setObjectName(QString::fromUtf8("lbl_3d_frac_den"));

        gridLayout->addWidget(lbl_3d_frac_den, 3, 0, 1, 1);

        m_pCbb3DFracAzi = new QComboBox(m_pGbx3DFrac);
        m_pCbb3DFracAzi->setObjectName(QString::fromUtf8("m_pCbb3DFracAzi"));

        gridLayout->addWidget(m_pCbb3DFracAzi, 2, 1, 1, 1);

        m_pCbb3DFracDen = new QComboBox(m_pGbx3DFrac);
        m_pCbb3DFracDen->setObjectName(QString::fromUtf8("m_pCbb3DFracDen"));

        gridLayout->addWidget(m_pCbb3DFracDen, 3, 1, 1, 1);

        m_pChk3DFracSeismic = new QCheckBox(m_pGbx3DFrac);
        m_pChk3DFracSeismic->setObjectName(QString::fromUtf8("m_pChk3DFracSeismic"));
        m_pChk3DFracSeismic->setChecked(true);

        gridLayout->addWidget(m_pChk3DFracSeismic, 0, 0, 1, 2);

        lbl_3d_frac_scale = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_scale->setObjectName(QString::fromUtf8("lbl_3d_frac_scale"));

        gridLayout->addWidget(lbl_3d_frac_scale, 7, 0, 1, 1);

        lbl_3d_frac_min = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_min->setObjectName(QString::fromUtf8("lbl_3d_frac_min"));

        gridLayout->addWidget(lbl_3d_frac_min, 4, 4, 1, 1);

        lbl_3d_frac_min_percent = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_min_percent->setObjectName(QString::fromUtf8("lbl_3d_frac_min_percent"));

        gridLayout->addWidget(lbl_3d_frac_min_percent, 4, 7, 1, 1);

        m_pEdt3DFracScale = new QLineEdit(m_pGbx3DFrac);
        m_pEdt3DFracScale->setObjectName(QString::fromUtf8("m_pEdt3DFracScale"));

        gridLayout->addWidget(m_pEdt3DFracScale, 7, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 4, 8, 1, 1);

        lbl_3d_frac_max = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_max->setObjectName(QString::fromUtf8("lbl_3d_frac_max"));

        gridLayout->addWidget(lbl_3d_frac_max, 6, 4, 1, 1);

        lbl_3d_frac_max_percent = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_max_percent->setObjectName(QString::fromUtf8("lbl_3d_frac_max_percent"));

        gridLayout->addWidget(lbl_3d_frac_max_percent, 6, 7, 1, 1);

        lbl_3d_frac_color = new QLabel(m_pGbx3DFrac);
        lbl_3d_frac_color->setObjectName(QString::fromUtf8("lbl_3d_frac_color"));

        gridLayout->addWidget(lbl_3d_frac_color, 1, 0, 1, 1);

        m_pClrBtn3DFracColor = new CXButtonColorEdit(m_pGbx3DFrac);
        m_pClrBtn3DFracColor->setObjectName(QString::fromUtf8("m_pClrBtn3DFracColor"));

        gridLayout->addWidget(m_pClrBtn3DFracColor, 1, 1, 1, 1);

        m_pEdt3DFracMax = new QLineEdit(m_pGbx3DFrac);
        m_pEdt3DFracMax->setObjectName(QString::fromUtf8("m_pEdt3DFracMax"));

        gridLayout->addWidget(m_pEdt3DFracMax, 6, 5, 1, 1);

        m_pEdt3DFracMin = new QLineEdit(m_pGbx3DFrac);
        m_pEdt3DFracMin->setObjectName(QString::fromUtf8("m_pEdt3DFracMin"));

        gridLayout->addWidget(m_pEdt3DFracMin, 4, 5, 1, 1);

        m_pLbl3DFracHeight = new QLabel(m_pGbx3DFrac);
        m_pLbl3DFracHeight->setObjectName(QString::fromUtf8("m_pLbl3DFracHeight"));

        gridLayout->addWidget(m_pLbl3DFracHeight, 7, 4, 1, 1);

        m_pEdt3DFracHeight = new QLineEdit(m_pGbx3DFrac);
        m_pEdt3DFracHeight->setObjectName(QString::fromUtf8("m_pEdt3DFracHeight"));

        gridLayout->addWidget(m_pEdt3DFracHeight, 7, 5, 1, 1);


        verticalLayout_2->addWidget(m_pGbx3DFrac);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        m_pStackedWidget->addWidget(m_pPage3D);

        verticalLayout->addWidget(m_pStackedWidget);


        retranslateUi(CXPageTimeSliceVis);
        QObject::connect(m_pRdo3DFrac, SIGNAL(toggled(bool)), m_pGbx3DFrac, SLOT(setVisible(bool)));
        QObject::connect(m_pRdoBMFrac, SIGNAL(toggled(bool)), m_pGbxBMFrac, SLOT(setVisible(bool)));

        m_pStackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CXPageTimeSliceVis);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageTimeSliceVis)
    {
        CXPageTimeSliceVis->setWindowTitle(QCoreApplication::translate("CXPageTimeSliceVis", "CXPageTimeSliceVisBM", nullptr));
        lbl_section_linecolor->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Color:", nullptr));
        m_pClrBtnSectionLineColor->setText(QString());
        lbl_section_linewidth->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Width:", nullptr));
        lbl_section_linetype->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Style:", nullptr));
        gbxBMMode->setTitle(QCoreApplication::translate("CXPageTimeSliceVis", "Display Mode", nullptr));
        m_pRdoBMSeismic->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Seismic", nullptr));
        m_pRdoBMFrac->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Fracture", nullptr));
        gbxBMFrame->setTitle(QCoreApplication::translate("CXPageTimeSliceVis", "Frame", nullptr));
        lbl_bm_framecolor->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Color:", nullptr));
        m_pClrBtnBMFrameColor->setText(QString());
        lbl_bm_framewidth->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Width:", nullptr));
        m_pGbxBMFrac->setTitle(QCoreApplication::translate("CXPageTimeSliceVis", "Fracture", nullptr));
        m_pChkBMSeismic->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Seismic Display", nullptr));
        lbl_bm_frac_min_percent->setText(QCoreApplication::translate("CXPageTimeSliceVis", "%", nullptr));
        lbl_bm_frac_dy_trace->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Trace", nullptr));
        lbl_bm_frac_scale->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Scale:", nullptr));
        m_pEdtBMFracMin->setText(QString());
        lbl_bm_frac_color->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Color:", nullptr));
        lbl_bm_frac_width->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Width:", nullptr));
        m_pEdtBMFracDY->setText(QString());
        m_pEdtBMFracScale->setText(QString());
        lbl_bm_frac_dx->setText(QCoreApplication::translate("CXPageTimeSliceVis", "DX:", nullptr));
        lbl_bm_frac_azi->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Azimuth:", nullptr));
        lbl_bm_frac_max->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Max-threshold:", nullptr));
        lbl_bm_frac_dx_trace->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Trace", nullptr));
        lbl_bm_frac_dy->setText(QCoreApplication::translate("CXPageTimeSliceVis", "DY:", nullptr));
        lbl_bm_frac_max_percent->setText(QCoreApplication::translate("CXPageTimeSliceVis", "%", nullptr));
        lbl_bm_frac_min->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Min-threshold:", nullptr));
        m_pClrBtnBMFracColor->setText(QString());
        lbl_bm_frac_den->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Density:", nullptr));
        m_pEdtBMFracDX->setText(QString());
        gbx3DMode->setTitle(QCoreApplication::translate("CXPageTimeSliceVis", "Display Mode", nullptr));
        m_pRdo3DSeismic->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Seismic", nullptr));
        m_pRdo3DFrac->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Fracture", nullptr));
        m_pGbx3DFrac->setTitle(QCoreApplication::translate("CXPageTimeSliceVis", "Fracture", nullptr));
        m_pEdt3DFracDY->setText(QString());
        lbl_3d_frac_dx->setText(QCoreApplication::translate("CXPageTimeSliceVis", "DX:", nullptr));
        lbl_3d_frac_dy_trace->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Trace", nullptr));
        m_pEdt3DFracDX->setText(QString());
        lbl_3d_frac_dx_trace->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Trace", nullptr));
        lbl_3d_frac_dy->setText(QCoreApplication::translate("CXPageTimeSliceVis", "DY:", nullptr));
        lbl_3d_frac_azi->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Azimuth:", nullptr));
        lbl_3d_frac_den->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Density:", nullptr));
        m_pChk3DFracSeismic->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Seismic Display", nullptr));
        lbl_3d_frac_scale->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Scale:", nullptr));
        lbl_3d_frac_min->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Min-threshold:", nullptr));
        lbl_3d_frac_min_percent->setText(QCoreApplication::translate("CXPageTimeSliceVis", "%", nullptr));
        m_pEdt3DFracScale->setText(QString());
        lbl_3d_frac_max->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Max-threshold:", nullptr));
        lbl_3d_frac_max_percent->setText(QCoreApplication::translate("CXPageTimeSliceVis", "%", nullptr));
        lbl_3d_frac_color->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Color:", nullptr));
        m_pClrBtn3DFracColor->setText(QString());
        m_pEdt3DFracMin->setText(QString());
        m_pLbl3DFracHeight->setText(QCoreApplication::translate("CXPageTimeSliceVis", "Height:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageTimeSliceVis: public Ui_CXPageTimeSliceVis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGETIMESLICEVIS_H
