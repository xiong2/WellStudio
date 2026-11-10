/********************************************************************************
** Form generated from reading UI file 'xdlgcreateseisworkarea.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGCREATESEISWORKAREA_H
#define UI_XDLGCREATESEISWORKAREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <xpageloadsegyutmview.h>

QT_BEGIN_NAMESPACE

class Ui_CreateSeisWorkArea
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLineEdit *m_pEdtSurveyName;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *m_EdtInlineSpace;
    QLabel *m_LblCrossSpaceUnit;
    QLineEdit *m_EdtCrosslineNumber;
    QLineEdit *m_EdtFirstCrossLine;
    QLabel *label_19;
    QLabel *m_LblInLineUnit;
    QLineEdit *m_EdtInlineNumber;
    QLabel *label_21;
    QLineEdit *m_EdtCrossSpace;
    QLineEdit *m_EdtFirstInline;
    QSpacerItem *verticalSpacer;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_6;
    QLineEdit *lineEditAngleP1;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_load;
    QPushButton *btn_save;
    CXPageLoadSegyUtmView *m_UtmToolView;
    QGroupBox *m_Grp3PointsCoordinates;
    QGridLayout *gridLayout;
    QLineEdit *m_EdtXPoint1;
    QLabel *label_11;
    QLineEdit *m_EdtCrossLinePoint1;
    QLineEdit *m_EdtInlinePoint1;
    QLabel *label_16;
    QLabel *label_4;
    QLineEdit *m_EdtYPoint1;
    QLabel *label_2;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_5;
    QLineEdit *m_EdtCrossLinePoint2;
    QLineEdit *m_EdtInLineInc;
    QLineEdit *m_EdtCrossLinePoint3;
    QLineEdit *m_EdtInlinePoint2;
    QPushButton *m_pBtnPreview;
    QLineEdit *m_EdtYPoint3;
    QLineEdit *m_EdtYPoint2;
    QLineEdit *m_pEdtCrossLineInc;
    QLineEdit *m_EdtInlinePoint3;
    QLineEdit *m_EdtXPoint3;
    QLineEdit *m_EdtXPoint2;
    QLabel *label_3;
    QLabel *label_17;

    void setupUi(QWidget *CreateSeisWorkArea)
    {
        if (CreateSeisWorkArea->objectName().isEmpty())
            CreateSeisWorkArea->setObjectName(QString::fromUtf8("CreateSeisWorkArea"));
        CreateSeisWorkArea->resize(915, 722);
        gridLayout_4 = new QGridLayout(CreateSeisWorkArea);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(CreateSeisWorkArea);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        m_pEdtSurveyName = new QLineEdit(groupBox);
        m_pEdtSurveyName->setObjectName(QString::fromUtf8("m_pEdtSurveyName"));

        gridLayout_3->addWidget(m_pEdtSurveyName, 0, 1, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 3);

        groupBox_2 = new QGroupBox(CreateSeisWorkArea);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_EdtInlineSpace = new QLineEdit(groupBox_2);
        m_EdtInlineSpace->setObjectName(QString::fromUtf8("m_EdtInlineSpace"));
        m_EdtInlineSpace->setEnabled(false);
        m_EdtInlineSpace->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtInlineSpace, 4, 1, 1, 1);

        m_LblCrossSpaceUnit = new QLabel(groupBox_2);
        m_LblCrossSpaceUnit->setObjectName(QString::fromUtf8("m_LblCrossSpaceUnit"));

        gridLayout_2->addWidget(m_LblCrossSpaceUnit, 5, 0, 1, 1);

        m_EdtCrosslineNumber = new QLineEdit(groupBox_2);
        m_EdtCrosslineNumber->setObjectName(QString::fromUtf8("m_EdtCrosslineNumber"));
        m_EdtCrosslineNumber->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtCrosslineNumber, 3, 1, 1, 1);

        m_EdtFirstCrossLine = new QLineEdit(groupBox_2);
        m_EdtFirstCrossLine->setObjectName(QString::fromUtf8("m_EdtFirstCrossLine"));
        m_EdtFirstCrossLine->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFirstCrossLine, 2, 1, 1, 1);

        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_2->addWidget(label_19, 2, 0, 1, 1);

        m_LblInLineUnit = new QLabel(groupBox_2);
        m_LblInLineUnit->setObjectName(QString::fromUtf8("m_LblInLineUnit"));

        gridLayout_2->addWidget(m_LblInLineUnit, 4, 0, 1, 1);

        m_EdtInlineNumber = new QLineEdit(groupBox_2);
        m_EdtInlineNumber->setObjectName(QString::fromUtf8("m_EdtInlineNumber"));
        m_EdtInlineNumber->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtInlineNumber, 1, 1, 1, 1);

        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 3, 0, 1, 1);

        m_EdtCrossSpace = new QLineEdit(groupBox_2);
        m_EdtCrossSpace->setObjectName(QString::fromUtf8("m_EdtCrossSpace"));
        m_EdtCrossSpace->setEnabled(false);
        m_EdtCrossSpace->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtCrossSpace, 5, 1, 1, 1);

        m_EdtFirstInline = new QLineEdit(groupBox_2);
        m_EdtFirstInline->setObjectName(QString::fromUtf8("m_EdtFirstInline"));
        m_EdtFirstInline->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFirstInline, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 7, 0, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 0, 0, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 6, 0, 1, 1);

        lineEditAngleP1 = new QLineEdit(groupBox_2);
        lineEditAngleP1->setObjectName(QString::fromUtf8("lineEditAngleP1"));
        lineEditAngleP1->setEnabled(false);
        lineEditAngleP1->setMaximumSize(QSize(70, 16777215));
        lineEditAngleP1->setReadOnly(false);

        gridLayout_2->addWidget(lineEditAngleP1, 6, 1, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 4, 0, 1, 1);

        groupBox_3 = new QGroupBox(CreateSeisWorkArea);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_load = new QPushButton(groupBox_3);
        btn_load->setObjectName(QString::fromUtf8("btn_load"));

        horizontalLayout->addWidget(btn_load);

        btn_save = new QPushButton(groupBox_3);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));

        horizontalLayout->addWidget(btn_save);


        gridLayout_4->addWidget(groupBox_3, 3, 0, 1, 1);

        m_UtmToolView = new CXPageLoadSegyUtmView(CreateSeisWorkArea);
        m_UtmToolView->setObjectName(QString::fromUtf8("m_UtmToolView"));
        m_UtmToolView->setFrameShape(QFrame::StyledPanel);
        m_UtmToolView->setFrameShadow(QFrame::Raised);

        gridLayout_4->addWidget(m_UtmToolView, 3, 1, 2, 2);

        m_Grp3PointsCoordinates = new QGroupBox(CreateSeisWorkArea);
        m_Grp3PointsCoordinates->setObjectName(QString::fromUtf8("m_Grp3PointsCoordinates"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_Grp3PointsCoordinates->sizePolicy().hasHeightForWidth());
        m_Grp3PointsCoordinates->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(m_Grp3PointsCoordinates);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_EdtXPoint1 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtXPoint1->setObjectName(QString::fromUtf8("m_EdtXPoint1"));

        gridLayout->addWidget(m_EdtXPoint1, 1, 4, 1, 1);

        label_11 = new QLabel(m_Grp3PointsCoordinates);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 0, 4, 1, 1);

        m_EdtCrossLinePoint1 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtCrossLinePoint1->setObjectName(QString::fromUtf8("m_EdtCrossLinePoint1"));

        gridLayout->addWidget(m_EdtCrossLinePoint1, 1, 3, 1, 1);

        m_EdtInlinePoint1 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtInlinePoint1->setObjectName(QString::fromUtf8("m_EdtInlinePoint1"));

        gridLayout->addWidget(m_EdtInlinePoint1, 1, 1, 1, 1);

        label_16 = new QLabel(m_Grp3PointsCoordinates);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_16, 4, 0, 1, 1);

        label_4 = new QLabel(m_Grp3PointsCoordinates);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        m_EdtYPoint1 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtYPoint1->setObjectName(QString::fromUtf8("m_EdtYPoint1"));

        gridLayout->addWidget(m_EdtYPoint1, 1, 5, 1, 1);

        label_2 = new QLabel(m_Grp3PointsCoordinates);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_10 = new QLabel(m_Grp3PointsCoordinates);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 0, 3, 1, 1);

        label_12 = new QLabel(m_Grp3PointsCoordinates);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 0, 5, 1, 1);

        label_5 = new QLabel(m_Grp3PointsCoordinates);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 1, 1, 1);

        m_EdtCrossLinePoint2 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtCrossLinePoint2->setObjectName(QString::fromUtf8("m_EdtCrossLinePoint2"));

        gridLayout->addWidget(m_EdtCrossLinePoint2, 2, 3, 1, 1);

        m_EdtInLineInc = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtInLineInc->setObjectName(QString::fromUtf8("m_EdtInLineInc"));
        m_EdtInLineInc->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(m_EdtInLineInc, 4, 1, 1, 1);

        m_EdtCrossLinePoint3 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtCrossLinePoint3->setObjectName(QString::fromUtf8("m_EdtCrossLinePoint3"));

        gridLayout->addWidget(m_EdtCrossLinePoint3, 3, 3, 1, 1);

        m_EdtInlinePoint2 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtInlinePoint2->setObjectName(QString::fromUtf8("m_EdtInlinePoint2"));

        gridLayout->addWidget(m_EdtInlinePoint2, 2, 1, 1, 1);

        m_pBtnPreview = new QPushButton(m_Grp3PointsCoordinates);
        m_pBtnPreview->setObjectName(QString::fromUtf8("m_pBtnPreview"));
        m_pBtnPreview->setEnabled(false);

        gridLayout->addWidget(m_pBtnPreview, 5, 5, 1, 1);

        m_EdtYPoint3 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtYPoint3->setObjectName(QString::fromUtf8("m_EdtYPoint3"));

        gridLayout->addWidget(m_EdtYPoint3, 3, 5, 1, 1);

        m_EdtYPoint2 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtYPoint2->setObjectName(QString::fromUtf8("m_EdtYPoint2"));

        gridLayout->addWidget(m_EdtYPoint2, 2, 5, 1, 1);

        m_pEdtCrossLineInc = new QLineEdit(m_Grp3PointsCoordinates);
        m_pEdtCrossLineInc->setObjectName(QString::fromUtf8("m_pEdtCrossLineInc"));
        m_pEdtCrossLineInc->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(m_pEdtCrossLineInc, 5, 1, 1, 1);

        m_EdtInlinePoint3 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtInlinePoint3->setObjectName(QString::fromUtf8("m_EdtInlinePoint3"));

        gridLayout->addWidget(m_EdtInlinePoint3, 3, 1, 1, 1);

        m_EdtXPoint3 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtXPoint3->setObjectName(QString::fromUtf8("m_EdtXPoint3"));

        gridLayout->addWidget(m_EdtXPoint3, 3, 4, 1, 1);

        m_EdtXPoint2 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtXPoint2->setObjectName(QString::fromUtf8("m_EdtXPoint2"));

        gridLayout->addWidget(m_EdtXPoint2, 2, 4, 1, 1);

        label_3 = new QLabel(m_Grp3PointsCoordinates);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_17 = new QLabel(m_Grp3PointsCoordinates);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_17, 5, 0, 1, 1);


        gridLayout_4->addWidget(m_Grp3PointsCoordinates, 2, 0, 1, 3);

        QWidget::setTabOrder(m_EdtInlinePoint1, m_EdtCrossLinePoint1);
        QWidget::setTabOrder(m_EdtCrossLinePoint1, m_EdtXPoint1);
        QWidget::setTabOrder(m_EdtXPoint1, m_EdtYPoint1);
        QWidget::setTabOrder(m_EdtYPoint1, m_EdtInlinePoint2);
        QWidget::setTabOrder(m_EdtInlinePoint2, m_EdtCrossLinePoint2);
        QWidget::setTabOrder(m_EdtCrossLinePoint2, m_EdtXPoint2);
        QWidget::setTabOrder(m_EdtXPoint2, m_EdtYPoint2);
        QWidget::setTabOrder(m_EdtYPoint2, m_EdtInlinePoint3);
        QWidget::setTabOrder(m_EdtInlinePoint3, m_EdtCrossLinePoint3);
        QWidget::setTabOrder(m_EdtCrossLinePoint3, m_EdtXPoint3);
        QWidget::setTabOrder(m_EdtXPoint3, m_EdtYPoint3);
        QWidget::setTabOrder(m_EdtYPoint3, m_EdtInLineInc);
        QWidget::setTabOrder(m_EdtInLineInc, m_pEdtCrossLineInc);
        QWidget::setTabOrder(m_pEdtCrossLineInc, m_EdtFirstInline);
        QWidget::setTabOrder(m_EdtFirstInline, m_EdtInlineNumber);
        QWidget::setTabOrder(m_EdtInlineNumber, m_EdtFirstCrossLine);
        QWidget::setTabOrder(m_EdtFirstCrossLine, m_EdtCrosslineNumber);
        QWidget::setTabOrder(m_EdtCrosslineNumber, m_EdtInlineSpace);
        QWidget::setTabOrder(m_EdtInlineSpace, m_EdtCrossSpace);
        QWidget::setTabOrder(m_EdtCrossSpace, m_pBtnPreview);

        retranslateUi(CreateSeisWorkArea);

        QMetaObject::connectSlotsByName(CreateSeisWorkArea);
    } // setupUi

    void retranslateUi(QWidget *CreateSeisWorkArea)
    {
        CreateSeisWorkArea->setWindowTitle(QCoreApplication::translate("CreateSeisWorkArea", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CreateSeisWorkArea", "General Information", nullptr));
        label->setText(QCoreApplication::translate("CreateSeisWorkArea", "Survey Name:", nullptr));
        m_pEdtSurveyName->setText(QCoreApplication::translate("CreateSeisWorkArea", "New Survey", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CreateSeisWorkArea", "Grid Information", nullptr));
        m_EdtInlineSpace->setText(QString());
        m_LblCrossSpaceUnit->setText(QCoreApplication::translate("CreateSeisWorkArea", "Crossline Space (m):", nullptr));
        m_EdtCrosslineNumber->setText(QString());
        m_EdtFirstCrossLine->setText(QString());
        label_19->setText(QCoreApplication::translate("CreateSeisWorkArea", "First Crossline:", nullptr));
        m_LblInLineUnit->setText(QCoreApplication::translate("CreateSeisWorkArea", "Inline Space (m):", nullptr));
        m_EdtInlineNumber->setText(QString());
        label_21->setText(QCoreApplication::translate("CreateSeisWorkArea", "Crossline Number:", nullptr));
        m_EdtCrossSpace->setText(QString());
        m_EdtFirstInline->setText(QString());
        label_13->setText(QCoreApplication::translate("CreateSeisWorkArea", "First Inline:", nullptr));
        label_15->setText(QCoreApplication::translate("CreateSeisWorkArea", "Inline Number:", nullptr));
        label_6->setText(QCoreApplication::translate("CreateSeisWorkArea", "Angle of P1(degree):", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CreateSeisWorkArea", "Coordinates parameters template", nullptr));
        btn_load->setText(QCoreApplication::translate("CreateSeisWorkArea", "Load...", nullptr));
        btn_save->setText(QCoreApplication::translate("CreateSeisWorkArea", "Save...", nullptr));
#if QT_CONFIG(tooltip)
        m_Grp3PointsCoordinates->setToolTip(QCoreApplication::translate("CreateSeisWorkArea", "You can edit coordinates of three corner points.", nullptr));
#endif // QT_CONFIG(tooltip)
        m_Grp3PointsCoordinates->setTitle(QCoreApplication::translate("CreateSeisWorkArea", "Three Points Coordinates", nullptr));
        m_EdtXPoint1->setText(QString());
        label_11->setText(QCoreApplication::translate("CreateSeisWorkArea", "X", nullptr));
        m_EdtCrossLinePoint1->setText(QString());
        m_EdtInlinePoint1->setText(QString());
        label_16->setText(QCoreApplication::translate("CreateSeisWorkArea", "Inline Inc:", nullptr));
        label_4->setText(QCoreApplication::translate("CreateSeisWorkArea", "Point 3: ", nullptr));
        m_EdtYPoint1->setText(QString());
        label_2->setText(QCoreApplication::translate("CreateSeisWorkArea", "Point 1: ", nullptr));
        label_10->setText(QCoreApplication::translate("CreateSeisWorkArea", "Crossline", nullptr));
        label_12->setText(QCoreApplication::translate("CreateSeisWorkArea", "Y", nullptr));
        label_5->setText(QCoreApplication::translate("CreateSeisWorkArea", "Inline", nullptr));
        m_EdtCrossLinePoint2->setText(QString());
        m_EdtInLineInc->setText(QString());
        m_EdtCrossLinePoint3->setText(QString());
        m_EdtInlinePoint2->setText(QString());
        m_pBtnPreview->setText(QCoreApplication::translate("CreateSeisWorkArea", "Preview", nullptr));
        m_EdtYPoint3->setText(QString());
        m_EdtYPoint2->setText(QString());
        m_pEdtCrossLineInc->setText(QString());
        m_EdtInlinePoint3->setText(QString());
        m_EdtXPoint3->setText(QString());
        m_EdtXPoint2->setText(QString());
        label_3->setText(QCoreApplication::translate("CreateSeisWorkArea", "Point 2: ", nullptr));
        label_17->setText(QCoreApplication::translate("CreateSeisWorkArea", "CrossLine Inc:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateSeisWorkArea: public Ui_CreateSeisWorkArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGCREATESEISWORKAREA_H
