/********************************************************************************
** Form generated from reading UI file 'xpagesurfacevisualization.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESURFACEVISUALIZATION_H
#define UI_XPAGESURFACEVISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"
#include "xcolormapcombo.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_CXSurfVisualizationPage
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *m_pDisplayModeGroupBox;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *m_DispModPointradioBtn;
    QRadioButton *m_DispModSurfaceradioBtn;
    QRadioButton *m_DispModFracradioBtn;
    QSpacerItem *horizontalSpacer;
    QGroupBox *m_pFracGroupBox;
    QGridLayout *gridLayout;
    QLineEdit *m_editFracDy;
    QLabel *label;
    QLabel *label_4;
    QLineEdit *m_editFracDx;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_8;
    QComboBox *m_pCbbFracAzimuth;
    QLabel *label_5;
    QLineEdit *m_editFracScale;
    QLabel *label_7;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *m_editFracMinThreshold;
    QLineEdit *m_editFracMaxThreshold;
    QLineEdit *m_editFracWidth;
    QLabel *label_13;
    CXButtonColorEdit *m_pFracColorBtn;
    QLabel *m_pLblFracHeight;
    QLineEdit *m_editFracHeight;
    QLabel *m_lblFracOffset;
    QLineEdit *m_editFracOffset;
    QLabel *label_9;
    QComboBox *m_pCbbFracDensity;
    QGroupBox *m_pPointGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_color;
    CXButtonColorEdit *m_pPointColorBtn;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_14;
    QSpinBox *spinBox_pointSize;
    QGroupBox *m_pFillGroupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_fillcolor;
    CXButtonColorEdit *m_pFillColorBtn;
    QSpacerItem *horizontalSpacer_5;
    QWidget *m_pWgtFill;
    QGridLayout *gridLayout1;
    QTableWidget *m_pFillColorTable;
    QPushButton *m_pBtnFillNum;
    QLabel *label_36;
    QLabel *label_colorbar;
    CXColormapCombo *m_pCombFillColorBar;
    QLabel *label_minlevel;
    QLineEdit *m_pEdtMinLevel;
    QPushButton *m_pBtnFillAdd;
    QLabel *label_maxlevel;
    QLineEdit *m_pEdtMaxLevel;
    QPushButton *m_pBtnFillDel;
    QLabel *label_inc_2;
    QLineEdit *m_pEdtFillInc;
    QCheckBox *m_pReverseColorMap;
    QGroupBox *m_pContourGroupBox;
    QGridLayout *gridLayout_contour;
    QCheckBox *m_pContourVisible;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_attri;
    QComboBox *m_pComboBoxAttr;
    QLabel *label_start;
    QLineEdit *m_pEdtContourStart;
    QLabel *label_end;
    QLineEdit *m_pEdtContourEnd;
    QLabel *label_inc;
    QLineEdit *m_pEdtContourInc;
    QSpacerItem *horizontalSpacer_7;
    QLabel *m_pChkMajorLine;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_colormajorlines;
    CXButtonColorEdit *m_pMajorLineColorBtn;
    QLabel *label_majlinsize;
    CXLineWidthListCombBox *m_pCombContourMajorSize;
    QLabel *label_majlintype;
    CXLineTypeListCombBox *m_pCombContourMajorType;
    QLabel *label_majlininterva;
    QSpinBox *m_pSpinContourInterval;
    QLabel *label_majminorline;
    QLabel *m_pChkMinorLine;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_colorminorlines;
    CXButtonColorEdit *m_pMinorLineColorBtn;
    QLabel *label_minlinsize;
    CXLineWidthListCombBox *m_pCombContourMinorSize;
    QLabel *label_minlinetype;
    CXLineTypeListCombBox *m_pCombContourMinorType;
    QSpacerItem *verticalSpacer;
    QButtonGroup *m_pModeButtonGroup;

    void setupUi(QWidget *CXSurfVisualizationPage)
    {
        if (CXSurfVisualizationPage->objectName().isEmpty())
            CXSurfVisualizationPage->setObjectName(QString::fromUtf8("CXSurfVisualizationPage"));
        CXSurfVisualizationPage->resize(664, 821);
        verticalLayout_3 = new QVBoxLayout(CXSurfVisualizationPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_pDisplayModeGroupBox = new QGroupBox(CXSurfVisualizationPage);
        m_pDisplayModeGroupBox->setObjectName(QString::fromUtf8("m_pDisplayModeGroupBox"));
        m_pDisplayModeGroupBox->setFlat(true);
        horizontalLayout_6 = new QHBoxLayout(m_pDisplayModeGroupBox);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_DispModPointradioBtn = new QRadioButton(m_pDisplayModeGroupBox);
        m_pModeButtonGroup = new QButtonGroup(CXSurfVisualizationPage);
        m_pModeButtonGroup->setObjectName(QString::fromUtf8("m_pModeButtonGroup"));
        m_pModeButtonGroup->addButton(m_DispModPointradioBtn);
        m_DispModPointradioBtn->setObjectName(QString::fromUtf8("m_DispModPointradioBtn"));

        horizontalLayout_6->addWidget(m_DispModPointradioBtn);

        m_DispModSurfaceradioBtn = new QRadioButton(m_pDisplayModeGroupBox);
        m_pModeButtonGroup->addButton(m_DispModSurfaceradioBtn);
        m_DispModSurfaceradioBtn->setObjectName(QString::fromUtf8("m_DispModSurfaceradioBtn"));
        m_DispModSurfaceradioBtn->setChecked(true);

        horizontalLayout_6->addWidget(m_DispModSurfaceradioBtn);

        m_DispModFracradioBtn = new QRadioButton(m_pDisplayModeGroupBox);
        m_pModeButtonGroup->addButton(m_DispModFracradioBtn);
        m_DispModFracradioBtn->setObjectName(QString::fromUtf8("m_DispModFracradioBtn"));

        horizontalLayout_6->addWidget(m_DispModFracradioBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(m_pDisplayModeGroupBox);

        m_pFracGroupBox = new QGroupBox(CXSurfVisualizationPage);
        m_pFracGroupBox->setObjectName(QString::fromUtf8("m_pFracGroupBox"));
        m_pFracGroupBox->setFlat(true);
        gridLayout = new QGridLayout(m_pFracGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_editFracDy = new QLineEdit(m_pFracGroupBox);
        m_editFracDy->setObjectName(QString::fromUtf8("m_editFracDy"));

        gridLayout->addWidget(m_editFracDy, 6, 1, 1, 1);

        label = new QLabel(m_pFracGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        label_4 = new QLabel(m_pFracGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 6, 2, 1, 1);

        m_editFracDx = new QLineEdit(m_pFracGroupBox);
        m_editFracDx->setObjectName(QString::fromUtf8("m_editFracDx"));

        gridLayout->addWidget(m_editFracDx, 4, 1, 1, 1);

        label_2 = new QLabel(m_pFracGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 2, 1, 1);

        label_3 = new QLabel(m_pFracGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 4, 3, 1, 1);

        label_8 = new QLabel(m_pFracGroupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        m_pCbbFracAzimuth = new QComboBox(m_pFracGroupBox);
        m_pCbbFracAzimuth->setObjectName(QString::fromUtf8("m_pCbbFracAzimuth"));

        gridLayout->addWidget(m_pCbbFracAzimuth, 2, 1, 1, 1);

        label_5 = new QLabel(m_pFracGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 7, 0, 1, 1);

        m_editFracScale = new QLineEdit(m_pFracGroupBox);
        m_editFracScale->setObjectName(QString::fromUtf8("m_editFracScale"));

        gridLayout->addWidget(m_editFracScale, 7, 1, 1, 1);

        label_7 = new QLabel(m_pFracGroupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 9, 1, 1);

        label_6 = new QLabel(m_pFracGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 4, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 4, 10, 1, 1);

        label_10 = new QLabel(m_pFracGroupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 6, 4, 1, 1);

        label_11 = new QLabel(m_pFracGroupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 6, 9, 1, 1);

        label_12 = new QLabel(m_pFracGroupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 7, 4, 1, 1);

        m_editFracMinThreshold = new QLineEdit(m_pFracGroupBox);
        m_editFracMinThreshold->setObjectName(QString::fromUtf8("m_editFracMinThreshold"));

        gridLayout->addWidget(m_editFracMinThreshold, 4, 5, 1, 1);

        m_editFracMaxThreshold = new QLineEdit(m_pFracGroupBox);
        m_editFracMaxThreshold->setObjectName(QString::fromUtf8("m_editFracMaxThreshold"));

        gridLayout->addWidget(m_editFracMaxThreshold, 6, 5, 1, 1);

        m_editFracWidth = new QLineEdit(m_pFracGroupBox);
        m_editFracWidth->setObjectName(QString::fromUtf8("m_editFracWidth"));

        gridLayout->addWidget(m_editFracWidth, 7, 5, 1, 1);

        label_13 = new QLabel(m_pFracGroupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 0, 0, 1, 1);

        m_pFracColorBtn = new CXButtonColorEdit(m_pFracGroupBox);
        m_pFracColorBtn->setObjectName(QString::fromUtf8("m_pFracColorBtn"));

        gridLayout->addWidget(m_pFracColorBtn, 0, 1, 1, 1);

        m_pLblFracHeight = new QLabel(m_pFracGroupBox);
        m_pLblFracHeight->setObjectName(QString::fromUtf8("m_pLblFracHeight"));

        gridLayout->addWidget(m_pLblFracHeight, 8, 0, 1, 1);

        m_editFracHeight = new QLineEdit(m_pFracGroupBox);
        m_editFracHeight->setObjectName(QString::fromUtf8("m_editFracHeight"));

        gridLayout->addWidget(m_editFracHeight, 8, 1, 1, 1);

        m_lblFracOffset = new QLabel(m_pFracGroupBox);
        m_lblFracOffset->setObjectName(QString::fromUtf8("m_lblFracOffset"));

        gridLayout->addWidget(m_lblFracOffset, 8, 4, 1, 1);

        m_editFracOffset = new QLineEdit(m_pFracGroupBox);
        m_editFracOffset->setObjectName(QString::fromUtf8("m_editFracOffset"));

        gridLayout->addWidget(m_editFracOffset, 8, 5, 1, 1);

        label_9 = new QLabel(m_pFracGroupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        m_pCbbFracDensity = new QComboBox(m_pFracGroupBox);
        m_pCbbFracDensity->setObjectName(QString::fromUtf8("m_pCbbFracDensity"));

        gridLayout->addWidget(m_pCbbFracDensity, 1, 1, 1, 1);


        verticalLayout_3->addWidget(m_pFracGroupBox);

        m_pPointGroupBox = new QGroupBox(CXSurfVisualizationPage);
        m_pPointGroupBox->setObjectName(QString::fromUtf8("m_pPointGroupBox"));
        m_pPointGroupBox->setFlat(true);
        gridLayout_2 = new QGridLayout(m_pPointGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_color = new QLabel(m_pPointGroupBox);
        label_color->setObjectName(QString::fromUtf8("label_color"));
        label_color->setMaximumSize(QSize(16777215, 16777215));
        label_color->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_color, 0, 0, 1, 1);

        m_pPointColorBtn = new CXButtonColorEdit(m_pPointGroupBox);
        m_pPointColorBtn->setObjectName(QString::fromUtf8("m_pPointColorBtn"));
        m_pPointColorBtn->setMinimumSize(QSize(80, 0));

        gridLayout_2->addWidget(m_pPointColorBtn, 0, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 3, 2, 1);

        label_14 = new QLabel(m_pPointGroupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 1, 0, 1, 1);

        spinBox_pointSize = new QSpinBox(m_pPointGroupBox);
        spinBox_pointSize->setObjectName(QString::fromUtf8("spinBox_pointSize"));

        gridLayout_2->addWidget(spinBox_pointSize, 1, 1, 1, 2);


        verticalLayout_3->addWidget(m_pPointGroupBox);

        m_pFillGroupBox = new QGroupBox(CXSurfVisualizationPage);
        m_pFillGroupBox->setObjectName(QString::fromUtf8("m_pFillGroupBox"));
        m_pFillGroupBox->setFlat(true);
        verticalLayout_4 = new QVBoxLayout(m_pFillGroupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_fillcolor = new QLabel(m_pFillGroupBox);
        label_fillcolor->setObjectName(QString::fromUtf8("label_fillcolor"));

        horizontalLayout_3->addWidget(label_fillcolor);

        m_pFillColorBtn = new CXButtonColorEdit(m_pFillGroupBox);
        m_pFillColorBtn->setObjectName(QString::fromUtf8("m_pFillColorBtn"));

        horizontalLayout_3->addWidget(m_pFillColorBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_3);

        m_pWgtFill = new QWidget(m_pFillGroupBox);
        m_pWgtFill->setObjectName(QString::fromUtf8("m_pWgtFill"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pWgtFill->sizePolicy().hasHeightForWidth());
        m_pWgtFill->setSizePolicy(sizePolicy);
        m_pWgtFill->setMinimumSize(QSize(0, 0));
        m_pWgtFill->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setUnderline(false);
        m_pWgtFill->setFont(font);
        m_pWgtFill->setAutoFillBackground(false);
        gridLayout1 = new QGridLayout(m_pWgtFill);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        m_pFillColorTable = new QTableWidget(m_pWgtFill);
        if (m_pFillColorTable->columnCount() < 3)
            m_pFillColorTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pFillColorTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pFillColorTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_pFillColorTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (m_pFillColorTable->rowCount() < 5)
            m_pFillColorTable->setRowCount(5);
        m_pFillColorTable->setObjectName(QString::fromUtf8("m_pFillColorTable"));
        m_pFillColorTable->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
        m_pFillColorTable->setRowCount(5);
        m_pFillColorTable->setColumnCount(3);

        gridLayout1->addWidget(m_pFillColorTable, 0, 0, 5, 1);

        m_pBtnFillNum = new QPushButton(m_pWgtFill);
        m_pBtnFillNum->setObjectName(QString::fromUtf8("m_pBtnFillNum"));
        m_pBtnFillNum->setMinimumSize(QSize(0, 18));
        m_pBtnFillNum->setMaximumSize(QSize(40, 20));

        gridLayout1->addWidget(m_pBtnFillNum, 0, 1, 1, 1);

        label_36 = new QLabel(m_pWgtFill);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setMinimumSize(QSize(5, 0));

        gridLayout1->addWidget(label_36, 0, 2, 4, 1);

        label_colorbar = new QLabel(m_pWgtFill);
        label_colorbar->setObjectName(QString::fromUtf8("label_colorbar"));

        gridLayout1->addWidget(label_colorbar, 0, 3, 1, 1);

        m_pCombFillColorBar = new CXColormapCombo(m_pWgtFill);
        m_pCombFillColorBar->setObjectName(QString::fromUtf8("m_pCombFillColorBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pCombFillColorBar->sizePolicy().hasHeightForWidth());
        m_pCombFillColorBar->setSizePolicy(sizePolicy1);
        m_pCombFillColorBar->setMinimumSize(QSize(0, 0));
        m_pCombFillColorBar->setMaximumSize(QSize(100, 16777215));

        gridLayout1->addWidget(m_pCombFillColorBar, 0, 4, 1, 1);

        label_minlevel = new QLabel(m_pWgtFill);
        label_minlevel->setObjectName(QString::fromUtf8("label_minlevel"));

        gridLayout1->addWidget(label_minlevel, 2, 3, 1, 1);

        m_pEdtMinLevel = new QLineEdit(m_pWgtFill);
        m_pEdtMinLevel->setObjectName(QString::fromUtf8("m_pEdtMinLevel"));
        m_pEdtMinLevel->setMinimumSize(QSize(0, 0));
        m_pEdtMinLevel->setMaximumSize(QSize(100, 16777215));

        gridLayout1->addWidget(m_pEdtMinLevel, 2, 4, 1, 1);

        m_pBtnFillAdd = new QPushButton(m_pWgtFill);
        m_pBtnFillAdd->setObjectName(QString::fromUtf8("m_pBtnFillAdd"));
        m_pBtnFillAdd->setMinimumSize(QSize(0, 18));
        m_pBtnFillAdd->setMaximumSize(QSize(40, 20));

        gridLayout1->addWidget(m_pBtnFillAdd, 3, 1, 1, 1);

        label_maxlevel = new QLabel(m_pWgtFill);
        label_maxlevel->setObjectName(QString::fromUtf8("label_maxlevel"));

        gridLayout1->addWidget(label_maxlevel, 3, 3, 1, 1);

        m_pEdtMaxLevel = new QLineEdit(m_pWgtFill);
        m_pEdtMaxLevel->setObjectName(QString::fromUtf8("m_pEdtMaxLevel"));
        m_pEdtMaxLevel->setMinimumSize(QSize(0, 0));
        m_pEdtMaxLevel->setMaximumSize(QSize(100, 16777215));

        gridLayout1->addWidget(m_pEdtMaxLevel, 3, 4, 1, 1);

        m_pBtnFillDel = new QPushButton(m_pWgtFill);
        m_pBtnFillDel->setObjectName(QString::fromUtf8("m_pBtnFillDel"));
        m_pBtnFillDel->setMinimumSize(QSize(0, 18));
        m_pBtnFillDel->setMaximumSize(QSize(40, 20));

        gridLayout1->addWidget(m_pBtnFillDel, 4, 1, 1, 1);

        label_inc_2 = new QLabel(m_pWgtFill);
        label_inc_2->setObjectName(QString::fromUtf8("label_inc_2"));

        gridLayout1->addWidget(label_inc_2, 4, 3, 1, 1);

        m_pEdtFillInc = new QLineEdit(m_pWgtFill);
        m_pEdtFillInc->setObjectName(QString::fromUtf8("m_pEdtFillInc"));
        m_pEdtFillInc->setMinimumSize(QSize(0, 0));
        m_pEdtFillInc->setMaximumSize(QSize(100, 16777215));

        gridLayout1->addWidget(m_pEdtFillInc, 4, 4, 1, 1);

        m_pReverseColorMap = new QCheckBox(m_pWgtFill);
        m_pReverseColorMap->setObjectName(QString::fromUtf8("m_pReverseColorMap"));

        gridLayout1->addWidget(m_pReverseColorMap, 1, 3, 1, 2);


        verticalLayout_4->addWidget(m_pWgtFill);


        verticalLayout_3->addWidget(m_pFillGroupBox);

        m_pContourGroupBox = new QGroupBox(CXSurfVisualizationPage);
        m_pContourGroupBox->setObjectName(QString::fromUtf8("m_pContourGroupBox"));
        m_pContourGroupBox->setFlat(true);
        gridLayout_contour = new QGridLayout(m_pContourGroupBox);
        gridLayout_contour->setObjectName(QString::fromUtf8("gridLayout_contour"));
        m_pContourVisible = new QCheckBox(m_pContourGroupBox);
        m_pContourVisible->setObjectName(QString::fromUtf8("m_pContourVisible"));

        gridLayout_contour->addWidget(m_pContourVisible, 0, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_contour->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        label_attri = new QLabel(m_pContourGroupBox);
        label_attri->setObjectName(QString::fromUtf8("label_attri"));

        gridLayout_contour->addWidget(label_attri, 1, 1, 1, 1);

        m_pComboBoxAttr = new QComboBox(m_pContourGroupBox);
        m_pComboBoxAttr->setObjectName(QString::fromUtf8("m_pComboBoxAttr"));
        m_pComboBoxAttr->setEnabled(false);

        gridLayout_contour->addWidget(m_pComboBoxAttr, 1, 2, 1, 1);

        label_start = new QLabel(m_pContourGroupBox);
        label_start->setObjectName(QString::fromUtf8("label_start"));

        gridLayout_contour->addWidget(label_start, 2, 1, 1, 1);

        m_pEdtContourStart = new QLineEdit(m_pContourGroupBox);
        m_pEdtContourStart->setObjectName(QString::fromUtf8("m_pEdtContourStart"));
        m_pEdtContourStart->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pEdtContourStart->sizePolicy().hasHeightForWidth());
        m_pEdtContourStart->setSizePolicy(sizePolicy2);

        gridLayout_contour->addWidget(m_pEdtContourStart, 2, 2, 1, 1);

        label_end = new QLabel(m_pContourGroupBox);
        label_end->setObjectName(QString::fromUtf8("label_end"));

        gridLayout_contour->addWidget(label_end, 2, 3, 1, 1);

        m_pEdtContourEnd = new QLineEdit(m_pContourGroupBox);
        m_pEdtContourEnd->setObjectName(QString::fromUtf8("m_pEdtContourEnd"));
        m_pEdtContourEnd->setEnabled(false);
        sizePolicy2.setHeightForWidth(m_pEdtContourEnd->sizePolicy().hasHeightForWidth());
        m_pEdtContourEnd->setSizePolicy(sizePolicy2);

        gridLayout_contour->addWidget(m_pEdtContourEnd, 2, 4, 1, 1);

        label_inc = new QLabel(m_pContourGroupBox);
        label_inc->setObjectName(QString::fromUtf8("label_inc"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_inc->sizePolicy().hasHeightForWidth());
        label_inc->setSizePolicy(sizePolicy3);

        gridLayout_contour->addWidget(label_inc, 2, 5, 1, 1);

        m_pEdtContourInc = new QLineEdit(m_pContourGroupBox);
        m_pEdtContourInc->setObjectName(QString::fromUtf8("m_pEdtContourInc"));
        m_pEdtContourInc->setEnabled(false);
        sizePolicy2.setHeightForWidth(m_pEdtContourInc->sizePolicy().hasHeightForWidth());
        m_pEdtContourInc->setSizePolicy(sizePolicy2);

        gridLayout_contour->addWidget(m_pEdtContourInc, 2, 6, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_contour->addItem(horizontalSpacer_7, 2, 7, 1, 1);

        m_pChkMajorLine = new QLabel(m_pContourGroupBox);
        m_pChkMajorLine->setObjectName(QString::fromUtf8("m_pChkMajorLine"));

        gridLayout_contour->addWidget(m_pChkMajorLine, 3, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_contour->addItem(horizontalSpacer_4, 4, 0, 1, 1);

        label_colormajorlines = new QLabel(m_pContourGroupBox);
        label_colormajorlines->setObjectName(QString::fromUtf8("label_colormajorlines"));

        gridLayout_contour->addWidget(label_colormajorlines, 4, 1, 1, 1);

        m_pMajorLineColorBtn = new CXButtonColorEdit(m_pContourGroupBox);
        m_pMajorLineColorBtn->setObjectName(QString::fromUtf8("m_pMajorLineColorBtn"));
        m_pMajorLineColorBtn->setEnabled(false);

        gridLayout_contour->addWidget(m_pMajorLineColorBtn, 4, 2, 1, 1);

        label_majlinsize = new QLabel(m_pContourGroupBox);
        label_majlinsize->setObjectName(QString::fromUtf8("label_majlinsize"));

        gridLayout_contour->addWidget(label_majlinsize, 4, 3, 1, 1);

        m_pCombContourMajorSize = new CXLineWidthListCombBox(m_pContourGroupBox);
        m_pCombContourMajorSize->setObjectName(QString::fromUtf8("m_pCombContourMajorSize"));
        m_pCombContourMajorSize->setEnabled(false);
        sizePolicy2.setHeightForWidth(m_pCombContourMajorSize->sizePolicy().hasHeightForWidth());
        m_pCombContourMajorSize->setSizePolicy(sizePolicy2);

        gridLayout_contour->addWidget(m_pCombContourMajorSize, 4, 4, 1, 1);

        label_majlintype = new QLabel(m_pContourGroupBox);
        label_majlintype->setObjectName(QString::fromUtf8("label_majlintype"));
        sizePolicy3.setHeightForWidth(label_majlintype->sizePolicy().hasHeightForWidth());
        label_majlintype->setSizePolicy(sizePolicy3);

        gridLayout_contour->addWidget(label_majlintype, 4, 5, 1, 1);

        m_pCombContourMajorType = new CXLineTypeListCombBox(m_pContourGroupBox);
        m_pCombContourMajorType->setObjectName(QString::fromUtf8("m_pCombContourMajorType"));
        m_pCombContourMajorType->setEnabled(false);
        sizePolicy2.setHeightForWidth(m_pCombContourMajorType->sizePolicy().hasHeightForWidth());
        m_pCombContourMajorType->setSizePolicy(sizePolicy2);

        gridLayout_contour->addWidget(m_pCombContourMajorType, 4, 6, 1, 1);

        label_majlininterva = new QLabel(m_pContourGroupBox);
        label_majlininterva->setObjectName(QString::fromUtf8("label_majlininterva"));

        gridLayout_contour->addWidget(label_majlininterva, 5, 1, 1, 1);

        m_pSpinContourInterval = new QSpinBox(m_pContourGroupBox);
        m_pSpinContourInterval->setObjectName(QString::fromUtf8("m_pSpinContourInterval"));
        m_pSpinContourInterval->setEnabled(false);
        sizePolicy2.setHeightForWidth(m_pSpinContourInterval->sizePolicy().hasHeightForWidth());
        m_pSpinContourInterval->setSizePolicy(sizePolicy2);
        m_pSpinContourInterval->setMinimum(1);

        gridLayout_contour->addWidget(m_pSpinContourInterval, 5, 2, 1, 1);

        label_majminorline = new QLabel(m_pContourGroupBox);
        label_majminorline->setObjectName(QString::fromUtf8("label_majminorline"));

        gridLayout_contour->addWidget(label_majminorline, 5, 3, 1, 1);

        m_pChkMinorLine = new QLabel(m_pContourGroupBox);
        m_pChkMinorLine->setObjectName(QString::fromUtf8("m_pChkMinorLine"));

        gridLayout_contour->addWidget(m_pChkMinorLine, 6, 0, 1, 2);

        horizontalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_contour->addItem(horizontalSpacer_11, 7, 0, 1, 1);

        label_colorminorlines = new QLabel(m_pContourGroupBox);
        label_colorminorlines->setObjectName(QString::fromUtf8("label_colorminorlines"));

        gridLayout_contour->addWidget(label_colorminorlines, 7, 1, 1, 1);

        m_pMinorLineColorBtn = new CXButtonColorEdit(m_pContourGroupBox);
        m_pMinorLineColorBtn->setObjectName(QString::fromUtf8("m_pMinorLineColorBtn"));
        m_pMinorLineColorBtn->setEnabled(false);

        gridLayout_contour->addWidget(m_pMinorLineColorBtn, 7, 2, 1, 1);

        label_minlinsize = new QLabel(m_pContourGroupBox);
        label_minlinsize->setObjectName(QString::fromUtf8("label_minlinsize"));

        gridLayout_contour->addWidget(label_minlinsize, 7, 3, 1, 1);

        m_pCombContourMinorSize = new CXLineWidthListCombBox(m_pContourGroupBox);
        m_pCombContourMinorSize->setObjectName(QString::fromUtf8("m_pCombContourMinorSize"));
        m_pCombContourMinorSize->setEnabled(false);
        sizePolicy2.setHeightForWidth(m_pCombContourMinorSize->sizePolicy().hasHeightForWidth());
        m_pCombContourMinorSize->setSizePolicy(sizePolicy2);

        gridLayout_contour->addWidget(m_pCombContourMinorSize, 7, 4, 1, 1);

        label_minlinetype = new QLabel(m_pContourGroupBox);
        label_minlinetype->setObjectName(QString::fromUtf8("label_minlinetype"));
        sizePolicy3.setHeightForWidth(label_minlinetype->sizePolicy().hasHeightForWidth());
        label_minlinetype->setSizePolicy(sizePolicy3);

        gridLayout_contour->addWidget(label_minlinetype, 7, 5, 1, 1);

        m_pCombContourMinorType = new CXLineTypeListCombBox(m_pContourGroupBox);
        m_pCombContourMinorType->setObjectName(QString::fromUtf8("m_pCombContourMinorType"));
        m_pCombContourMinorType->setEnabled(false);
        sizePolicy2.setHeightForWidth(m_pCombContourMinorType->sizePolicy().hasHeightForWidth());
        m_pCombContourMinorType->setSizePolicy(sizePolicy2);

        gridLayout_contour->addWidget(m_pCombContourMinorType, 7, 6, 1, 1);


        verticalLayout_3->addWidget(m_pContourGroupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        m_pContourGroupBox->raise();
        m_pFillGroupBox->raise();
        m_pDisplayModeGroupBox->raise();
        m_pPointGroupBox->raise();
        m_pFracGroupBox->raise();

        retranslateUi(CXSurfVisualizationPage);
        QObject::connect(m_DispModPointradioBtn, SIGNAL(toggled(bool)), m_pPointGroupBox, SLOT(setVisible(bool)));
        QObject::connect(m_pContourVisible, SIGNAL(toggled(bool)), m_pMajorLineColorBtn, SLOT(setEnabled(bool)));
        QObject::connect(m_pContourVisible, SIGNAL(toggled(bool)), m_pCombContourMajorSize, SLOT(setEnabled(bool)));
        QObject::connect(m_pContourVisible, SIGNAL(toggled(bool)), m_pCombContourMajorType, SLOT(setEnabled(bool)));
        QObject::connect(m_pContourVisible, SIGNAL(toggled(bool)), m_pSpinContourInterval, SLOT(setEnabled(bool)));
        QObject::connect(m_pContourVisible, SIGNAL(toggled(bool)), m_pMinorLineColorBtn, SLOT(setEnabled(bool)));
        QObject::connect(m_pContourVisible, SIGNAL(toggled(bool)), m_pCombContourMinorSize, SLOT(setEnabled(bool)));
        QObject::connect(m_pContourVisible, SIGNAL(toggled(bool)), m_pCombContourMinorType, SLOT(setEnabled(bool)));
        QObject::connect(m_DispModSurfaceradioBtn, SIGNAL(toggled(bool)), m_pFillGroupBox, SLOT(setVisible(bool)));
        QObject::connect(m_DispModSurfaceradioBtn, SIGNAL(toggled(bool)), m_pContourGroupBox, SLOT(setVisible(bool)));
        QObject::connect(m_DispModFracradioBtn, SIGNAL(toggled(bool)), m_pFracGroupBox, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(CXSurfVisualizationPage);
    } // setupUi

    void retranslateUi(QWidget *CXSurfVisualizationPage)
    {
        CXSurfVisualizationPage->setWindowTitle(QCoreApplication::translate("CXSurfVisualizationPage", "Form", nullptr));
        m_pDisplayModeGroupBox->setTitle(QCoreApplication::translate("CXSurfVisualizationPage", "Display Mode", nullptr));
        m_DispModPointradioBtn->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Point", nullptr));
        m_DispModSurfaceradioBtn->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Surface", nullptr));
        m_DispModFracradioBtn->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Fracture", nullptr));
        m_pFracGroupBox->setTitle(QCoreApplication::translate("CXSurfVisualizationPage", "Fracture", nullptr));
        m_editFracDy->setText(QString());
        label->setText(QCoreApplication::translate("CXSurfVisualizationPage", "DX:", nullptr));
        label_4->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Trace", nullptr));
        m_editFracDx->setText(QString());
        label_2->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Trace", nullptr));
        label_3->setText(QCoreApplication::translate("CXSurfVisualizationPage", "DY:", nullptr));
        label_8->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Azimuth:", nullptr));
        label_5->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Scale:", nullptr));
        m_editFracScale->setText(QString());
        label_7->setText(QCoreApplication::translate("CXSurfVisualizationPage", "%", nullptr));
        label_6->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Min-threshold:", nullptr));
        label_10->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Max-threshold:", nullptr));
        label_11->setText(QCoreApplication::translate("CXSurfVisualizationPage", "%", nullptr));
        label_12->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Width:", nullptr));
        m_editFracMinThreshold->setText(QString());
        label_13->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Color:", nullptr));
        m_pLblFracHeight->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Height:", nullptr));
        m_lblFracOffset->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Offset:", nullptr));
        label_9->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Density:", nullptr));
        m_pPointGroupBox->setTitle(QCoreApplication::translate("CXSurfVisualizationPage", "Point", nullptr));
        label_color->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Color:", nullptr));
        label_14->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Size:", nullptr));
        m_pFillGroupBox->setTitle(QCoreApplication::translate("CXSurfVisualizationPage", "Fill", nullptr));
        label_fillcolor->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Color:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pFillColorTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Start", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pFillColorTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CXSurfVisualizationPage", "End", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_pFillColorTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Fill Color", nullptr));
        m_pBtnFillNum->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Num.", nullptr));
        label_36->setText(QString());
        label_colorbar->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Color Map:", nullptr));
        label_minlevel->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Min level:", nullptr));
        m_pBtnFillAdd->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Add", nullptr));
        label_maxlevel->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Max level:", nullptr));
        m_pBtnFillDel->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Del.", nullptr));
        label_inc_2->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Inc:", nullptr));
        m_pReverseColorMap->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Reverse", nullptr));
        m_pContourGroupBox->setTitle(QCoreApplication::translate("CXSurfVisualizationPage", "Contour", nullptr));
        m_pContourVisible->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Visible:", nullptr));
        label_attri->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Attribute:", nullptr));
        label_start->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Start:", nullptr));
        label_end->setText(QCoreApplication::translate("CXSurfVisualizationPage", "End:", nullptr));
        label_inc->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Inc:", nullptr));
        m_pChkMajorLine->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Major lines:", nullptr));
        label_colormajorlines->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Color:", nullptr));
        label_majlinsize->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Size:", nullptr));
        label_majlintype->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Type:", nullptr));
        label_majlininterva->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Interval:", nullptr));
        label_majminorline->setText(QCoreApplication::translate("CXSurfVisualizationPage", "minor lines", nullptr));
        m_pChkMinorLine->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Minor lines:", nullptr));
        label_colorminorlines->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Color:", nullptr));
        label_minlinsize->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Size:", nullptr));
        label_minlinetype->setText(QCoreApplication::translate("CXSurfVisualizationPage", "Type:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXSurfVisualizationPage: public Ui_CXSurfVisualizationPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESURFACEVISUALIZATION_H
