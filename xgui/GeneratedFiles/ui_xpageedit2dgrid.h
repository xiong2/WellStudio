/********************************************************************************
** Form generated from reading UI file 'xpageedit2dgrid.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEEDIT2DGRID_H
#define UI_XPAGEEDIT2DGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CXPageEdit2DGrid
{
public:
    QLabel *label_3;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *line;
    QVBoxLayout *verticalLayout_5;
    QPushButton *m_pbtZoomOut;
    QPushButton *m_pbtZoomIn;
    QPushButton *m_pbtReset;
    QPushButton *m_pbt3DSurve;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_5;
    QDoubleSpinBox *m_dspbMinX;
    QDoubleSpinBox *m_dspbNIIterval;
    QSpinBox *m_spbNI;
    QLabel *label_4;
    QDoubleSpinBox *m_dspbMinY;
    QDoubleSpinBox *m_dspbNJIterval;
    QSpinBox *m_spbNJ;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QSlider *m_hsliRotationAngle;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_11;
    QDoubleSpinBox *m_dspbRotationAngle;
    QCheckBox *m_chbAutoAdjust;
    QGraphicsView *view;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *CXPageEdit2DGrid)
    {
        if (CXPageEdit2DGrid->objectName().isEmpty())
            CXPageEdit2DGrid->setObjectName(QString::fromUtf8("CXPageEdit2DGrid"));
        CXPageEdit2DGrid->resize(558, 558);
        label_3 = new QLabel(CXPageEdit2DGrid);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(11, 33, 16, 16));
        gridLayout_2 = new QGridLayout(CXPageEdit2DGrid);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CXPageEdit2DGrid);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(0, 70, 213, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label->setPalette(palette);

        horizontalLayout->addWidget(label);

        line = new QFrame(CXPageEdit2DGrid);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        m_pbtZoomOut = new QPushButton(CXPageEdit2DGrid);
        m_pbtZoomOut->setObjectName(QString::fromUtf8("m_pbtZoomOut"));

        verticalLayout_5->addWidget(m_pbtZoomOut);

        m_pbtZoomIn = new QPushButton(CXPageEdit2DGrid);
        m_pbtZoomIn->setObjectName(QString::fromUtf8("m_pbtZoomIn"));

        verticalLayout_5->addWidget(m_pbtZoomIn);

        m_pbtReset = new QPushButton(CXPageEdit2DGrid);
        m_pbtReset->setObjectName(QString::fromUtf8("m_pbtReset"));

        verticalLayout_5->addWidget(m_pbtReset);

        m_pbt3DSurve = new QPushButton(CXPageEdit2DGrid);
        m_pbt3DSurve->setObjectName(QString::fromUtf8("m_pbt3DSurve"));

        verticalLayout_5->addWidget(m_pbt3DSurve);


        gridLayout_2->addLayout(verticalLayout_5, 0, 1, 3, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(CXPageEdit2DGrid);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        label_7 = new QLabel(CXPageEdit2DGrid);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_7, 0, 2, 1, 1);

        label_6 = new QLabel(CXPageEdit2DGrid);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_6, 0, 3, 1, 1);

        label_5 = new QLabel(CXPageEdit2DGrid);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_dspbMinX = new QDoubleSpinBox(CXPageEdit2DGrid);
        m_dspbMinX->setObjectName(QString::fromUtf8("m_dspbMinX"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_dspbMinX->sizePolicy().hasHeightForWidth());
        m_dspbMinX->setSizePolicy(sizePolicy2);
        m_dspbMinX->setMinimum(100000.000000000000000);
        m_dspbMinX->setMaximum(999999.000000000000000);
        m_dspbMinX->setValue(100000.000000000000000);

        gridLayout->addWidget(m_dspbMinX, 1, 1, 1, 1);

        m_dspbNIIterval = new QDoubleSpinBox(CXPageEdit2DGrid);
        m_dspbNIIterval->setObjectName(QString::fromUtf8("m_dspbNIIterval"));
        sizePolicy2.setHeightForWidth(m_dspbNIIterval->sizePolicy().hasHeightForWidth());
        m_dspbNIIterval->setSizePolicy(sizePolicy2);
        m_dspbNIIterval->setKeyboardTracking(true);
        m_dspbNIIterval->setMinimum(0.000000000000000);
        m_dspbNIIterval->setMaximum(333333.000000000000000);
        m_dspbNIIterval->setSingleStep(1.000000000000000);
        m_dspbNIIterval->setValue(0.000000000000000);

        gridLayout->addWidget(m_dspbNIIterval, 1, 2, 1, 1);

        m_spbNI = new QSpinBox(CXPageEdit2DGrid);
        m_spbNI->setObjectName(QString::fromUtf8("m_spbNI"));
        sizePolicy2.setHeightForWidth(m_spbNI->sizePolicy().hasHeightForWidth());
        m_spbNI->setSizePolicy(sizePolicy2);
        m_spbNI->setKeyboardTracking(true);
        m_spbNI->setMinimum(3);
        m_spbNI->setMaximum(10000);

        gridLayout->addWidget(m_spbNI, 1, 3, 1, 1);

        label_4 = new QLabel(CXPageEdit2DGrid);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 2, 2);

        m_dspbMinY = new QDoubleSpinBox(CXPageEdit2DGrid);
        m_dspbMinY->setObjectName(QString::fromUtf8("m_dspbMinY"));
        sizePolicy2.setHeightForWidth(m_dspbMinY->sizePolicy().hasHeightForWidth());
        m_dspbMinY->setSizePolicy(sizePolicy2);
        m_dspbMinY->setMinimum(1000000.000000000000000);
        m_dspbMinY->setMaximum(9999999.000000000000000);

        gridLayout->addWidget(m_dspbMinY, 3, 1, 1, 1);

        m_dspbNJIterval = new QDoubleSpinBox(CXPageEdit2DGrid);
        m_dspbNJIterval->setObjectName(QString::fromUtf8("m_dspbNJIterval"));
        sizePolicy2.setHeightForWidth(m_dspbNJIterval->sizePolicy().hasHeightForWidth());
        m_dspbNJIterval->setSizePolicy(sizePolicy2);
        m_dspbNJIterval->setKeyboardTracking(true);
        m_dspbNJIterval->setMaximum(3333333.000000000000000);
        m_dspbNJIterval->setSingleStep(1.000000000000000);

        gridLayout->addWidget(m_dspbNJIterval, 3, 2, 1, 1);

        m_spbNJ = new QSpinBox(CXPageEdit2DGrid);
        m_spbNJ->setObjectName(QString::fromUtf8("m_spbNJ"));
        sizePolicy2.setHeightForWidth(m_spbNJ->sizePolicy().hasHeightForWidth());
        m_spbNJ->setSizePolicy(sizePolicy2);
        m_spbNJ->setKeyboardTracking(true);
        m_spbNJ->setMinimum(3);
        m_spbNJ->setMaximum(10000);

        gridLayout->addWidget(m_spbNJ, 3, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        label_12 = new QLabel(CXPageEdit2DGrid);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_8 = new QLabel(CXPageEdit2DGrid);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_8->setPalette(palette1);

        horizontalLayout_3->addWidget(label_8);

        line_2 = new QFrame(CXPageEdit2DGrid);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_2);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_9 = new QLabel(CXPageEdit2DGrid);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        m_hsliRotationAngle = new QSlider(CXPageEdit2DGrid);
        m_hsliRotationAngle->setObjectName(QString::fromUtf8("m_hsliRotationAngle"));
        m_hsliRotationAngle->setMouseTracking(false);
        m_hsliRotationAngle->setAutoFillBackground(false);
        m_hsliRotationAngle->setMaximum(360);
        m_hsliRotationAngle->setValue(0);
        m_hsliRotationAngle->setOrientation(Qt::Horizontal);
        m_hsliRotationAngle->setInvertedAppearance(false);
        m_hsliRotationAngle->setInvertedControls(false);
        m_hsliRotationAngle->setTickPosition(QSlider::TicksBelow);
        m_hsliRotationAngle->setTickInterval(1000);

        horizontalLayout_4->addWidget(m_hsliRotationAngle);

        label_10 = new QLabel(CXPageEdit2DGrid);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);


        gridLayout_2->addLayout(horizontalLayout_4, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_11 = new QLabel(CXPageEdit2DGrid);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_5->addWidget(label_11);

        m_dspbRotationAngle = new QDoubleSpinBox(CXPageEdit2DGrid);
        m_dspbRotationAngle->setObjectName(QString::fromUtf8("m_dspbRotationAngle"));
        sizePolicy2.setHeightForWidth(m_dspbRotationAngle->sizePolicy().hasHeightForWidth());
        m_dspbRotationAngle->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(m_dspbRotationAngle);


        gridLayout_2->addLayout(horizontalLayout_5, 5, 0, 1, 1);

        m_chbAutoAdjust = new QCheckBox(CXPageEdit2DGrid);
        m_chbAutoAdjust->setObjectName(QString::fromUtf8("m_chbAutoAdjust"));

        gridLayout_2->addWidget(m_chbAutoAdjust, 5, 1, 1, 1);

        view = new QGraphicsView(CXPageEdit2DGrid);
        view->setObjectName(QString::fromUtf8("view"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(view->sizePolicy().hasHeightForWidth());
        view->setSizePolicy(sizePolicy3);
        view->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(view, 6, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout_2->addItem(verticalSpacer, 7, 1, 1, 1);


        retranslateUi(CXPageEdit2DGrid);

        QMetaObject::connectSlotsByName(CXPageEdit2DGrid);
    } // setupUi

    void retranslateUi(QWidget *CXPageEdit2DGrid)
    {
        CXPageEdit2DGrid->setWindowTitle(QCoreApplication::translate("CXPageEdit2DGrid", "Edit Surface Geometry - Step 2 of 3", nullptr));
        label_3->setText(QString());
        label->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Grid Information", nullptr));
        m_pbtZoomOut->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Shrink", nullptr));
        m_pbtZoomIn->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Magnify", nullptr));
        m_pbtReset->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Reset", nullptr));
        m_pbt3DSurve->setText(QCoreApplication::translate("CXPageEdit2DGrid", "3-D Surve", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Minimum Coordinates", nullptr));
        label_7->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Spacing", nullptr));
        label_6->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Grid Number", nullptr));
        label_5->setText(QCoreApplication::translate("CXPageEdit2DGrid", "X", nullptr));
        label_4->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Y", nullptr));
        label_12->setText(QString());
        label_8->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Preview", nullptr));
        label_9->setText(QCoreApplication::translate("CXPageEdit2DGrid", "0", nullptr));
        label_10->setText(QCoreApplication::translate("CXPageEdit2DGrid", "360", nullptr));
        label_11->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Rotation Angle", nullptr));
        m_chbAutoAdjust->setText(QCoreApplication::translate("CXPageEdit2DGrid", "Auto Adjust", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageEdit2DGrid: public Ui_CXPageEdit2DGrid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEEDIT2DGRID_H
