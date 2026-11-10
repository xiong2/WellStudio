/********************************************************************************
** Form generated from reading UI file 'xpagewellvis3d.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEWELLVIS3D_H
#define UI_XPAGEWELLVIS3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "xbuttoncoloredit.h"
#include "xlinecomponent.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageWellVis3D
{
public:
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_4;
    QLabel *m_WellSymbolSize;
    QSpacerItem *horizontalSpacer_7;
    CXButtonColorEdit *m_cbbSymbolColor;
    QCheckBox *m_cbSymbolVisible;
    QSpacerItem *horizontalSpacer;
    QLabel *m_WellSymbolColor;
    QComboBox *m_cbbSymbolRadius;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_WellHead;
    QFrame *line_3;
    QGridLayout *gridLayout;
    QLabel *m_PathColor;
    QLabel *m_PathSize;
    CXButtonColorEdit *m_cbbPathColor;
    CXLineWidthListCombBox *m_cbbPathSize;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *m_cbPathVisible;
    QHBoxLayout *horizontalLayout_5;
    QLabel *m_WellPath;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *m_WellName;
    QFrame *line;
    QGridLayout *gridLayout_name;
    CXButtonColorEdit *m_cbbNameColor;
    QLabel *m_nameColor;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *m_cbbNameFont;
    QLabel *m_nameFont;
    QComboBox *m_cbbNameSize;
    QLabel *m_nameSize;
    QCheckBox *m_cbNameVisible;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QComboBox *m_cbbNamePosition;

    void setupUi(QWidget *CXPageWellVis3D)
    {
        if (CXPageWellVis3D->objectName().isEmpty())
            CXPageWellVis3D->setObjectName(QString::fromUtf8("CXPageWellVis3D"));
        CXPageWellVis3D->resize(612, 361);
        gridLayout_5 = new QGridLayout(CXPageWellVis3D);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 7, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_WellSymbolSize = new QLabel(CXPageWellVis3D);
        m_WellSymbolSize->setObjectName(QString::fromUtf8("m_WellSymbolSize"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_WellSymbolSize->sizePolicy().hasHeightForWidth());
        m_WellSymbolSize->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_WellSymbolSize, 2, 3, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_7, 1, 0, 1, 1);

        m_cbbSymbolColor = new CXButtonColorEdit(CXPageWellVis3D);
        m_cbbSymbolColor->setObjectName(QString::fromUtf8("m_cbbSymbolColor"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_cbbSymbolColor->sizePolicy().hasHeightForWidth());
        m_cbbSymbolColor->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_cbbSymbolColor, 2, 2, 1, 1);

        m_cbSymbolVisible = new QCheckBox(CXPageWellVis3D);
        m_cbSymbolVisible->setObjectName(QString::fromUtf8("m_cbSymbolVisible"));

        gridLayout_4->addWidget(m_cbSymbolVisible, 1, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 2, 5, 1, 1);

        m_WellSymbolColor = new QLabel(CXPageWellVis3D);
        m_WellSymbolColor->setObjectName(QString::fromUtf8("m_WellSymbolColor"));
        sizePolicy.setHeightForWidth(m_WellSymbolColor->sizePolicy().hasHeightForWidth());
        m_WellSymbolColor->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(m_WellSymbolColor, 2, 1, 1, 1);

        m_cbbSymbolRadius = new QComboBox(CXPageWellVis3D);
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->addItem(QString());
        m_cbbSymbolRadius->setObjectName(QString::fromUtf8("m_cbbSymbolRadius"));
        sizePolicy1.setHeightForWidth(m_cbbSymbolRadius->sizePolicy().hasHeightForWidth());
        m_cbbSymbolRadius->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(m_cbbSymbolRadius, 2, 4, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 6, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_WellHead = new QLabel(CXPageWellVis3D);
        m_WellHead->setObjectName(QString::fromUtf8("m_WellHead"));
        sizePolicy.setHeightForWidth(m_WellHead->sizePolicy().hasHeightForWidth());
        m_WellHead->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(m_WellHead);

        line_3 = new QFrame(CXPageWellVis3D);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy2);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_3);


        gridLayout_5->addLayout(horizontalLayout_6, 5, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_PathColor = new QLabel(CXPageWellVis3D);
        m_PathColor->setObjectName(QString::fromUtf8("m_PathColor"));
        sizePolicy.setHeightForWidth(m_PathColor->sizePolicy().hasHeightForWidth());
        m_PathColor->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_PathColor, 1, 1, 1, 1);

        m_PathSize = new QLabel(CXPageWellVis3D);
        m_PathSize->setObjectName(QString::fromUtf8("m_PathSize"));
        sizePolicy.setHeightForWidth(m_PathSize->sizePolicy().hasHeightForWidth());
        m_PathSize->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_PathSize, 1, 3, 1, 1);

        m_cbbPathColor = new CXButtonColorEdit(CXPageWellVis3D);
        m_cbbPathColor->setObjectName(QString::fromUtf8("m_cbbPathColor"));

        gridLayout->addWidget(m_cbbPathColor, 1, 2, 1, 1);

        m_cbbPathSize = new CXLineWidthListCombBox(CXPageWellVis3D);
        m_cbbPathSize->setObjectName(QString::fromUtf8("m_cbbPathSize"));

        gridLayout->addWidget(m_cbbPathSize, 1, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 5, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        m_cbPathVisible = new QCheckBox(CXPageWellVis3D);
        m_cbPathVisible->setObjectName(QString::fromUtf8("m_cbPathVisible"));

        gridLayout->addWidget(m_cbPathVisible, 0, 1, 1, 2);


        gridLayout_5->addLayout(gridLayout, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_WellPath = new QLabel(CXPageWellVis3D);
        m_WellPath->setObjectName(QString::fromUtf8("m_WellPath"));
        sizePolicy.setHeightForWidth(m_WellPath->sizePolicy().hasHeightForWidth());
        m_WellPath->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(m_WellPath);

        line_2 = new QFrame(CXPageWellVis3D);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        sizePolicy2.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy2);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_2);


        gridLayout_5->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_WellName = new QLabel(CXPageWellVis3D);
        m_WellName->setObjectName(QString::fromUtf8("m_WellName"));
        sizePolicy.setHeightForWidth(m_WellName->sizePolicy().hasHeightForWidth());
        m_WellName->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(m_WellName);

        line = new QFrame(CXPageWellVis3D);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);


        gridLayout_5->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        gridLayout_name = new QGridLayout();
        gridLayout_name->setObjectName(QString::fromUtf8("gridLayout_name"));
        m_cbbNameColor = new CXButtonColorEdit(CXPageWellVis3D);
        m_cbbNameColor->setObjectName(QString::fromUtf8("m_cbbNameColor"));

        gridLayout_name->addWidget(m_cbbNameColor, 1, 2, 1, 1);

        m_nameColor = new QLabel(CXPageWellVis3D);
        m_nameColor->setObjectName(QString::fromUtf8("m_nameColor"));
        sizePolicy.setHeightForWidth(m_nameColor->sizePolicy().hasHeightForWidth());
        m_nameColor->setSizePolicy(sizePolicy);

        gridLayout_name->addWidget(m_nameColor, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_name->addItem(horizontalSpacer_3, 1, 9, 1, 1);

        m_cbbNameFont = new QComboBox(CXPageWellVis3D);
        m_cbbNameFont->addItem(QString());
        m_cbbNameFont->addItem(QString());
        m_cbbNameFont->addItem(QString());
        m_cbbNameFont->addItem(QString());
        m_cbbNameFont->addItem(QString());
        m_cbbNameFont->addItem(QString());
        m_cbbNameFont->setObjectName(QString::fromUtf8("m_cbbNameFont"));

        gridLayout_name->addWidget(m_cbbNameFont, 1, 6, 1, 1);

        m_nameFont = new QLabel(CXPageWellVis3D);
        m_nameFont->setObjectName(QString::fromUtf8("m_nameFont"));
        sizePolicy.setHeightForWidth(m_nameFont->sizePolicy().hasHeightForWidth());
        m_nameFont->setSizePolicy(sizePolicy);

        gridLayout_name->addWidget(m_nameFont, 1, 5, 1, 1);

        m_cbbNameSize = new QComboBox(CXPageWellVis3D);
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->addItem(QString());
        m_cbbNameSize->setObjectName(QString::fromUtf8("m_cbbNameSize"));

        gridLayout_name->addWidget(m_cbbNameSize, 1, 4, 1, 1);

        m_nameSize = new QLabel(CXPageWellVis3D);
        m_nameSize->setObjectName(QString::fromUtf8("m_nameSize"));
        sizePolicy.setHeightForWidth(m_nameSize->sizePolicy().hasHeightForWidth());
        m_nameSize->setSizePolicy(sizePolicy);

        gridLayout_name->addWidget(m_nameSize, 1, 3, 1, 1);

        m_cbNameVisible = new QCheckBox(CXPageWellVis3D);
        m_cbNameVisible->setObjectName(QString::fromUtf8("m_cbNameVisible"));

        gridLayout_name->addWidget(m_cbNameVisible, 0, 1, 1, 2);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_name->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        label = new QLabel(CXPageWellVis3D);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_name->addWidget(label, 1, 7, 1, 1);

        m_cbbNamePosition = new QComboBox(CXPageWellVis3D);
        m_cbbNamePosition->addItem(QString());
        m_cbbNamePosition->addItem(QString());
        m_cbbNamePosition->setObjectName(QString::fromUtf8("m_cbbNamePosition"));

        gridLayout_name->addWidget(m_cbbNamePosition, 1, 8, 1, 1);


        gridLayout_5->addLayout(gridLayout_name, 1, 0, 1, 1);


        retranslateUi(CXPageWellVis3D);

        QMetaObject::connectSlotsByName(CXPageWellVis3D);
    } // setupUi

    void retranslateUi(QWidget *CXPageWellVis3D)
    {
        CXPageWellVis3D->setWindowTitle(QCoreApplication::translate("CXPageWellVis3D", "Form", nullptr));
        m_WellSymbolSize->setText(QCoreApplication::translate("CXPageWellVis3D", "Radius", nullptr));
        m_cbSymbolVisible->setText(QCoreApplication::translate("CXPageWellVis3D", "Visible", nullptr));
        m_WellSymbolColor->setText(QCoreApplication::translate("CXPageWellVis3D", "Color:", nullptr));
        m_cbbSymbolRadius->setItemText(0, QCoreApplication::translate("CXPageWellVis3D", "1", nullptr));
        m_cbbSymbolRadius->setItemText(1, QCoreApplication::translate("CXPageWellVis3D", "2", nullptr));
        m_cbbSymbolRadius->setItemText(2, QCoreApplication::translate("CXPageWellVis3D", "3", nullptr));
        m_cbbSymbolRadius->setItemText(3, QCoreApplication::translate("CXPageWellVis3D", "4", nullptr));
        m_cbbSymbolRadius->setItemText(4, QCoreApplication::translate("CXPageWellVis3D", "5", nullptr));
        m_cbbSymbolRadius->setItemText(5, QCoreApplication::translate("CXPageWellVis3D", "6", nullptr));
        m_cbbSymbolRadius->setItemText(6, QCoreApplication::translate("CXPageWellVis3D", "7", nullptr));
        m_cbbSymbolRadius->setItemText(7, QCoreApplication::translate("CXPageWellVis3D", "8", nullptr));
        m_cbbSymbolRadius->setItemText(8, QCoreApplication::translate("CXPageWellVis3D", "9", nullptr));
        m_cbbSymbolRadius->setItemText(9, QCoreApplication::translate("CXPageWellVis3D", "10", nullptr));
        m_cbbSymbolRadius->setItemText(10, QCoreApplication::translate("CXPageWellVis3D", "13", nullptr));
        m_cbbSymbolRadius->setItemText(11, QCoreApplication::translate("CXPageWellVis3D", "15", nullptr));
        m_cbbSymbolRadius->setItemText(12, QCoreApplication::translate("CXPageWellVis3D", "20", nullptr));

        m_WellHead->setText(QCoreApplication::translate("CXPageWellVis3D", "Well Header Symbol", nullptr));
        m_PathColor->setText(QCoreApplication::translate("CXPageWellVis3D", "Color:", nullptr));
        m_PathSize->setText(QCoreApplication::translate("CXPageWellVis3D", "Size:", nullptr));
        m_cbPathVisible->setText(QCoreApplication::translate("CXPageWellVis3D", "Visible", nullptr));
        m_WellPath->setText(QCoreApplication::translate("CXPageWellVis3D", "Well Path", nullptr));
        m_WellName->setText(QCoreApplication::translate("CXPageWellVis3D", "Well Name", nullptr));
        m_nameColor->setText(QCoreApplication::translate("CXPageWellVis3D", "Color:", nullptr));
        m_cbbNameFont->setItemText(0, QCoreApplication::translate("CXPageWellVis3D", "arial", nullptr));
        m_cbbNameFont->setItemText(1, QCoreApplication::translate("CXPageWellVis3D", "dirtydoz", nullptr));
        m_cbbNameFont->setItemText(2, QCoreApplication::translate("CXPageWellVis3D", "fudd", nullptr));
        m_cbbNameFont->setItemText(3, QCoreApplication::translate("CXPageWellVis3D", "times", nullptr));
        m_cbbNameFont->setItemText(4, QCoreApplication::translate("CXPageWellVis3D", "Vera", nullptr));
        m_cbbNameFont->setItemText(5, QCoreApplication::translate("CXPageWellVis3D", "VeraMono", nullptr));

        m_nameFont->setText(QCoreApplication::translate("CXPageWellVis3D", "Font:", nullptr));
        m_cbbNameSize->setItemText(0, QCoreApplication::translate("CXPageWellVis3D", "1", nullptr));
        m_cbbNameSize->setItemText(1, QCoreApplication::translate("CXPageWellVis3D", "2", nullptr));
        m_cbbNameSize->setItemText(2, QCoreApplication::translate("CXPageWellVis3D", "3", nullptr));
        m_cbbNameSize->setItemText(3, QCoreApplication::translate("CXPageWellVis3D", "4", nullptr));
        m_cbbNameSize->setItemText(4, QCoreApplication::translate("CXPageWellVis3D", "5", nullptr));
        m_cbbNameSize->setItemText(5, QCoreApplication::translate("CXPageWellVis3D", "6", nullptr));
        m_cbbNameSize->setItemText(6, QCoreApplication::translate("CXPageWellVis3D", "7", nullptr));
        m_cbbNameSize->setItemText(7, QCoreApplication::translate("CXPageWellVis3D", "8", nullptr));
        m_cbbNameSize->setItemText(8, QCoreApplication::translate("CXPageWellVis3D", "9", nullptr));
        m_cbbNameSize->setItemText(9, QCoreApplication::translate("CXPageWellVis3D", "10", nullptr));
        m_cbbNameSize->setItemText(10, QCoreApplication::translate("CXPageWellVis3D", "13", nullptr));
        m_cbbNameSize->setItemText(11, QCoreApplication::translate("CXPageWellVis3D", "15", nullptr));
        m_cbbNameSize->setItemText(12, QCoreApplication::translate("CXPageWellVis3D", "20", nullptr));

        m_nameSize->setText(QCoreApplication::translate("CXPageWellVis3D", "Size:", nullptr));
        m_cbNameVisible->setText(QCoreApplication::translate("CXPageWellVis3D", "Visible", nullptr));
        label->setText(QCoreApplication::translate("CXPageWellVis3D", "Position", nullptr));
        m_cbbNamePosition->setItemText(0, QCoreApplication::translate("CXPageWellVis3D", "Top", nullptr));
        m_cbbNamePosition->setItemText(1, QCoreApplication::translate("CXPageWellVis3D", "Bottom", nullptr));

    } // retranslateUi

};

namespace Ui {
    class CXPageWellVis3D: public Ui_CXPageWellVis3D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEWELLVIS3D_H
