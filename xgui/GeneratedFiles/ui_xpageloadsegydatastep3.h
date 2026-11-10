/********************************************************************************
** Form generated from reading UI file 'xpageloadsegydatastep3.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGELOADSEGYDATASTEP3_H
#define UI_XPAGELOADSEGYDATASTEP3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
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

class Ui_LoadSegyDataRange
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label;
    QFrame *line;
    QGroupBox *m_Grp3PointsCoordinates;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_2;
    QLineEdit *m_EdtInlinePoint1;
    QLineEdit *m_EdtCrossLinePoint1;
    QLineEdit *m_EdtXPoint1;
    QLineEdit *m_EdtYPoint1;
    QLabel *label_3;
    QLineEdit *m_EdtInlinePoint2;
    QLineEdit *m_EdtCrossLinePoint2;
    QLineEdit *m_EdtXPoint2;
    QLineEdit *m_EdtYPoint2;
    QLabel *label_4;
    QLineEdit *m_EdtInlinePoint3;
    QLineEdit *m_EdtCrossLinePoint3;
    QLineEdit *m_EdtXPoint3;
    QLineEdit *m_EdtYPoint3;
    QLabel *m_LblPoint4;
    QLineEdit *m_EdtInlinePoint4;
    QLineEdit *m_EdtCrossLinePoint4;
    QLineEdit *m_EdtXPoint4;
    QLineEdit *m_EdtYPoint4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *m_EdtFirstInline;
    QLabel *label_13;
    QLineEdit *m_EdtInlineIncrement;
    QLabel *label_15;
    QLineEdit *lineEditStartOffset;
    QLineEdit *m_EdtInlineNumber;
    QLabel *label_19;
    QLineEdit *m_EdtFirstCrossLine;
    QLabel *label_20;
    QLineEdit *m_EdtCrossLineIncrement;
    QLabel *labelMinAzim;
    QLineEdit *m_EdtInlineSpace;
    QLabel *m_LblCrossSpaceUnit;
    QLineEdit *m_EdtCrossSpace;
    QLabel *label_14;
    QSpacerItem *verticalSpacer;
    QLabel *labelStartOffset;
    QLabel *labelOffsetInc;
    QLabel *labelOffsetNumber;
    QLineEdit *lineEditOffsetInc;
    QLineEdit *lineEditOffsetNumber;
    QLabel *m_LblInLineUnit;
    QLineEdit *m_EdtCrosslineNumber;
    QLabel *label_21;
    QLineEdit *lineEditMaxAzim;
    QLabel *labelMaxAzim;
    QLineEdit *lineEditMinAzim;
    QLabel *labelMaxFold;
    QLineEdit *lineEditMaxFold;
    CXPageLoadSegyUtmView *m_UtmToolView;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_BtnLoad;
    QLabel *label_6;
    QLabel *m_LblFilePath;

    void setupUi(QWidget *LoadSegyDataRange)
    {
        if (LoadSegyDataRange->objectName().isEmpty())
            LoadSegyDataRange->setObjectName(QString::fromUtf8("LoadSegyDataRange"));
        LoadSegyDataRange->resize(787, 650);
        gridLayout_3 = new QGridLayout(LoadSegyDataRange);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(LoadSegyDataRange);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        line = new QFrame(LoadSegyDataRange);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 1, 0, 1, 2);

        m_Grp3PointsCoordinates = new QGroupBox(LoadSegyDataRange);
        m_Grp3PointsCoordinates->setObjectName(QString::fromUtf8("m_Grp3PointsCoordinates"));
        sizePolicy.setHeightForWidth(m_Grp3PointsCoordinates->sizePolicy().hasHeightForWidth());
        m_Grp3PointsCoordinates->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(m_Grp3PointsCoordinates);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(m_Grp3PointsCoordinates);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 1, 1, 1);

        label_10 = new QLabel(m_Grp3PointsCoordinates);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 0, 2, 1, 1);

        label_11 = new QLabel(m_Grp3PointsCoordinates);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 0, 3, 1, 1);

        label_12 = new QLabel(m_Grp3PointsCoordinates);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 0, 4, 1, 1);

        label_2 = new QLabel(m_Grp3PointsCoordinates);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        m_EdtInlinePoint1 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtInlinePoint1->setObjectName(QString::fromUtf8("m_EdtInlinePoint1"));

        gridLayout->addWidget(m_EdtInlinePoint1, 1, 1, 1, 1);

        m_EdtCrossLinePoint1 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtCrossLinePoint1->setObjectName(QString::fromUtf8("m_EdtCrossLinePoint1"));

        gridLayout->addWidget(m_EdtCrossLinePoint1, 1, 2, 1, 1);

        m_EdtXPoint1 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtXPoint1->setObjectName(QString::fromUtf8("m_EdtXPoint1"));

        gridLayout->addWidget(m_EdtXPoint1, 1, 3, 1, 1);

        m_EdtYPoint1 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtYPoint1->setObjectName(QString::fromUtf8("m_EdtYPoint1"));

        gridLayout->addWidget(m_EdtYPoint1, 1, 4, 1, 1);

        label_3 = new QLabel(m_Grp3PointsCoordinates);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_EdtInlinePoint2 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtInlinePoint2->setObjectName(QString::fromUtf8("m_EdtInlinePoint2"));

        gridLayout->addWidget(m_EdtInlinePoint2, 2, 1, 1, 1);

        m_EdtCrossLinePoint2 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtCrossLinePoint2->setObjectName(QString::fromUtf8("m_EdtCrossLinePoint2"));

        gridLayout->addWidget(m_EdtCrossLinePoint2, 2, 2, 1, 1);

        m_EdtXPoint2 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtXPoint2->setObjectName(QString::fromUtf8("m_EdtXPoint2"));

        gridLayout->addWidget(m_EdtXPoint2, 2, 3, 1, 1);

        m_EdtYPoint2 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtYPoint2->setObjectName(QString::fromUtf8("m_EdtYPoint2"));

        gridLayout->addWidget(m_EdtYPoint2, 2, 4, 1, 1);

        label_4 = new QLabel(m_Grp3PointsCoordinates);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        m_EdtInlinePoint3 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtInlinePoint3->setObjectName(QString::fromUtf8("m_EdtInlinePoint3"));

        gridLayout->addWidget(m_EdtInlinePoint3, 3, 1, 1, 1);

        m_EdtCrossLinePoint3 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtCrossLinePoint3->setObjectName(QString::fromUtf8("m_EdtCrossLinePoint3"));

        gridLayout->addWidget(m_EdtCrossLinePoint3, 3, 2, 1, 1);

        m_EdtXPoint3 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtXPoint3->setObjectName(QString::fromUtf8("m_EdtXPoint3"));

        gridLayout->addWidget(m_EdtXPoint3, 3, 3, 1, 1);

        m_EdtYPoint3 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtYPoint3->setObjectName(QString::fromUtf8("m_EdtYPoint3"));

        gridLayout->addWidget(m_EdtYPoint3, 3, 4, 1, 1);

        m_LblPoint4 = new QLabel(m_Grp3PointsCoordinates);
        m_LblPoint4->setObjectName(QString::fromUtf8("m_LblPoint4"));

        gridLayout->addWidget(m_LblPoint4, 4, 0, 1, 1);

        m_EdtInlinePoint4 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtInlinePoint4->setObjectName(QString::fromUtf8("m_EdtInlinePoint4"));
        m_EdtInlinePoint4->setReadOnly(true);

        gridLayout->addWidget(m_EdtInlinePoint4, 4, 1, 1, 1);

        m_EdtCrossLinePoint4 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtCrossLinePoint4->setObjectName(QString::fromUtf8("m_EdtCrossLinePoint4"));
        m_EdtCrossLinePoint4->setReadOnly(true);

        gridLayout->addWidget(m_EdtCrossLinePoint4, 4, 2, 1, 1);

        m_EdtXPoint4 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtXPoint4->setObjectName(QString::fromUtf8("m_EdtXPoint4"));

        gridLayout->addWidget(m_EdtXPoint4, 4, 3, 1, 1);

        m_EdtYPoint4 = new QLineEdit(m_Grp3PointsCoordinates);
        m_EdtYPoint4->setObjectName(QString::fromUtf8("m_EdtYPoint4"));

        gridLayout->addWidget(m_EdtYPoint4, 4, 4, 1, 1);


        gridLayout_3->addWidget(m_Grp3PointsCoordinates, 2, 0, 1, 2);

        groupBox_2 = new QGroupBox(LoadSegyDataRange);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_EdtFirstInline = new QLineEdit(groupBox_2);
        m_EdtFirstInline->setObjectName(QString::fromUtf8("m_EdtFirstInline"));
        m_EdtFirstInline->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFirstInline, 0, 1, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 0, 0, 1, 1);

        m_EdtInlineIncrement = new QLineEdit(groupBox_2);
        m_EdtInlineIncrement->setObjectName(QString::fromUtf8("m_EdtInlineIncrement"));
        m_EdtInlineIncrement->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtInlineIncrement, 1, 1, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 2, 0, 1, 1);

        lineEditStartOffset = new QLineEdit(groupBox_2);
        lineEditStartOffset->setObjectName(QString::fromUtf8("lineEditStartOffset"));
        lineEditStartOffset->setMaximumSize(QSize(70, 16777215));
        lineEditStartOffset->setReadOnly(true);

        gridLayout_2->addWidget(lineEditStartOffset, 8, 1, 1, 1);

        m_EdtInlineNumber = new QLineEdit(groupBox_2);
        m_EdtInlineNumber->setObjectName(QString::fromUtf8("m_EdtInlineNumber"));
        m_EdtInlineNumber->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtInlineNumber, 2, 1, 1, 1);

        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_2->addWidget(label_19, 3, 0, 1, 1);

        m_EdtFirstCrossLine = new QLineEdit(groupBox_2);
        m_EdtFirstCrossLine->setObjectName(QString::fromUtf8("m_EdtFirstCrossLine"));
        m_EdtFirstCrossLine->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtFirstCrossLine, 3, 1, 1, 1);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_2->addWidget(label_20, 4, 0, 1, 1);

        m_EdtCrossLineIncrement = new QLineEdit(groupBox_2);
        m_EdtCrossLineIncrement->setObjectName(QString::fromUtf8("m_EdtCrossLineIncrement"));
        m_EdtCrossLineIncrement->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtCrossLineIncrement, 4, 1, 1, 1);

        labelMinAzim = new QLabel(groupBox_2);
        labelMinAzim->setObjectName(QString::fromUtf8("labelMinAzim"));

        gridLayout_2->addWidget(labelMinAzim, 11, 0, 1, 1);

        m_EdtInlineSpace = new QLineEdit(groupBox_2);
        m_EdtInlineSpace->setObjectName(QString::fromUtf8("m_EdtInlineSpace"));
        m_EdtInlineSpace->setEnabled(true);
        m_EdtInlineSpace->setMaximumSize(QSize(70, 16777215));
        m_EdtInlineSpace->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtInlineSpace, 6, 1, 1, 1);

        m_LblCrossSpaceUnit = new QLabel(groupBox_2);
        m_LblCrossSpaceUnit->setObjectName(QString::fromUtf8("m_LblCrossSpaceUnit"));

        gridLayout_2->addWidget(m_LblCrossSpaceUnit, 7, 0, 1, 1);

        m_EdtCrossSpace = new QLineEdit(groupBox_2);
        m_EdtCrossSpace->setObjectName(QString::fromUtf8("m_EdtCrossSpace"));
        m_EdtCrossSpace->setEnabled(true);
        m_EdtCrossSpace->setMaximumSize(QSize(70, 16777215));
        m_EdtCrossSpace->setReadOnly(true);

        gridLayout_2->addWidget(m_EdtCrossSpace, 7, 1, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 15, 0, 1, 1);

        labelStartOffset = new QLabel(groupBox_2);
        labelStartOffset->setObjectName(QString::fromUtf8("labelStartOffset"));

        gridLayout_2->addWidget(labelStartOffset, 8, 0, 1, 1);

        labelOffsetInc = new QLabel(groupBox_2);
        labelOffsetInc->setObjectName(QString::fromUtf8("labelOffsetInc"));

        gridLayout_2->addWidget(labelOffsetInc, 9, 0, 1, 1);

        labelOffsetNumber = new QLabel(groupBox_2);
        labelOffsetNumber->setObjectName(QString::fromUtf8("labelOffsetNumber"));

        gridLayout_2->addWidget(labelOffsetNumber, 10, 0, 1, 1);

        lineEditOffsetInc = new QLineEdit(groupBox_2);
        lineEditOffsetInc->setObjectName(QString::fromUtf8("lineEditOffsetInc"));
        lineEditOffsetInc->setMaximumSize(QSize(70, 16777215));
        lineEditOffsetInc->setReadOnly(true);

        gridLayout_2->addWidget(lineEditOffsetInc, 9, 1, 1, 1);

        lineEditOffsetNumber = new QLineEdit(groupBox_2);
        lineEditOffsetNumber->setObjectName(QString::fromUtf8("lineEditOffsetNumber"));
        lineEditOffsetNumber->setMaximumSize(QSize(70, 16777215));
        lineEditOffsetNumber->setReadOnly(true);

        gridLayout_2->addWidget(lineEditOffsetNumber, 10, 1, 1, 1);

        m_LblInLineUnit = new QLabel(groupBox_2);
        m_LblInLineUnit->setObjectName(QString::fromUtf8("m_LblInLineUnit"));

        gridLayout_2->addWidget(m_LblInLineUnit, 6, 0, 1, 1);

        m_EdtCrosslineNumber = new QLineEdit(groupBox_2);
        m_EdtCrosslineNumber->setObjectName(QString::fromUtf8("m_EdtCrosslineNumber"));
        m_EdtCrosslineNumber->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(m_EdtCrosslineNumber, 5, 1, 1, 1);

        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 5, 0, 1, 1);

        lineEditMaxAzim = new QLineEdit(groupBox_2);
        lineEditMaxAzim->setObjectName(QString::fromUtf8("lineEditMaxAzim"));
        lineEditMaxAzim->setMaximumSize(QSize(70, 16777215));
        lineEditMaxAzim->setReadOnly(true);

        gridLayout_2->addWidget(lineEditMaxAzim, 12, 1, 1, 1);

        labelMaxAzim = new QLabel(groupBox_2);
        labelMaxAzim->setObjectName(QString::fromUtf8("labelMaxAzim"));

        gridLayout_2->addWidget(labelMaxAzim, 12, 0, 1, 1);

        lineEditMinAzim = new QLineEdit(groupBox_2);
        lineEditMinAzim->setObjectName(QString::fromUtf8("lineEditMinAzim"));
        lineEditMinAzim->setMaximumSize(QSize(70, 16777215));
        lineEditMinAzim->setReadOnly(true);

        gridLayout_2->addWidget(lineEditMinAzim, 11, 1, 1, 1);

        labelMaxFold = new QLabel(groupBox_2);
        labelMaxFold->setObjectName(QString::fromUtf8("labelMaxFold"));

        gridLayout_2->addWidget(labelMaxFold, 13, 0, 1, 1);

        lineEditMaxFold = new QLineEdit(groupBox_2);
        lineEditMaxFold->setObjectName(QString::fromUtf8("lineEditMaxFold"));
        lineEditMaxFold->setMaximumSize(QSize(70, 16777215));
        lineEditMaxFold->setReadOnly(true);

        gridLayout_2->addWidget(lineEditMaxFold, 13, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 3, 0, 1, 1);

        m_UtmToolView = new CXPageLoadSegyUtmView(LoadSegyDataRange);
        m_UtmToolView->setObjectName(QString::fromUtf8("m_UtmToolView"));
        m_UtmToolView->setFrameShape(QFrame::StyledPanel);
        m_UtmToolView->setFrameShadow(QFrame::Raised);

        gridLayout_3->addWidget(m_UtmToolView, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_BtnLoad = new QPushButton(LoadSegyDataRange);
        m_BtnLoad->setObjectName(QString::fromUtf8("m_BtnLoad"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_BtnLoad->sizePolicy().hasHeightForWidth());
        m_BtnLoad->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(m_BtnLoad);

        label_6 = new QLabel(LoadSegyDataRange);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(label_6);

        m_LblFilePath = new QLabel(LoadSegyDataRange);
        m_LblFilePath->setObjectName(QString::fromUtf8("m_LblFilePath"));
        sizePolicy.setHeightForWidth(m_LblFilePath->sizePolicy().hasHeightForWidth());
        m_LblFilePath->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_LblFilePath);


        gridLayout_3->addLayout(horizontalLayout, 4, 0, 1, 2);


        retranslateUi(LoadSegyDataRange);

        QMetaObject::connectSlotsByName(LoadSegyDataRange);
    } // setupUi

    void retranslateUi(QWidget *LoadSegyDataRange)
    {
        LoadSegyDataRange->setWindowTitle(QCoreApplication::translate("LoadSegyDataRange", "Form", nullptr));
        label->setText(QCoreApplication::translate("LoadSegyDataRange", "Step 3 of 4: Data Range", nullptr));
#if QT_CONFIG(tooltip)
        m_Grp3PointsCoordinates->setToolTip(QCoreApplication::translate("LoadSegyDataRange", "You can edit coordinates of three corner points.", nullptr));
#endif // QT_CONFIG(tooltip)
        m_Grp3PointsCoordinates->setTitle(QCoreApplication::translate("LoadSegyDataRange", "Three Points Coordinates", nullptr));
        label_5->setText(QCoreApplication::translate("LoadSegyDataRange", "Inline", nullptr));
        label_10->setText(QCoreApplication::translate("LoadSegyDataRange", "Crossline", nullptr));
        label_11->setText(QCoreApplication::translate("LoadSegyDataRange", "X", nullptr));
        label_12->setText(QCoreApplication::translate("LoadSegyDataRange", "Y", nullptr));
        label_2->setText(QCoreApplication::translate("LoadSegyDataRange", "Point 1: ", nullptr));
        m_EdtInlinePoint1->setText(QString());
        m_EdtCrossLinePoint1->setText(QString());
        m_EdtXPoint1->setText(QString());
        m_EdtYPoint1->setText(QString());
        label_3->setText(QCoreApplication::translate("LoadSegyDataRange", "Point 2: ", nullptr));
        m_EdtInlinePoint2->setText(QString());
        m_EdtCrossLinePoint2->setText(QString());
        m_EdtXPoint2->setText(QString());
        m_EdtYPoint2->setText(QString());
        label_4->setText(QCoreApplication::translate("LoadSegyDataRange", "Point 3: ", nullptr));
        m_EdtInlinePoint3->setText(QString());
        m_EdtCrossLinePoint3->setText(QString());
        m_EdtXPoint3->setText(QString());
        m_EdtYPoint3->setText(QString());
        m_LblPoint4->setText(QCoreApplication::translate("LoadSegyDataRange", "Point 4:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("LoadSegyDataRange", "Grid Information", nullptr));
        m_EdtFirstInline->setText(QString());
        label_13->setText(QCoreApplication::translate("LoadSegyDataRange", "First Inline:", nullptr));
        m_EdtInlineIncrement->setText(QString());
        label_15->setText(QCoreApplication::translate("LoadSegyDataRange", "Inline Number:", nullptr));
        m_EdtInlineNumber->setText(QString());
        label_19->setText(QCoreApplication::translate("LoadSegyDataRange", "First Crossline:", nullptr));
        m_EdtFirstCrossLine->setText(QString());
        label_20->setText(QCoreApplication::translate("LoadSegyDataRange", "Crossline Increment:", nullptr));
        m_EdtCrossLineIncrement->setText(QString());
        labelMinAzim->setText(QCoreApplication::translate("LoadSegyDataRange", "Minimum Azimuth", nullptr));
        m_EdtInlineSpace->setText(QString());
        m_LblCrossSpaceUnit->setText(QCoreApplication::translate("LoadSegyDataRange", "Crossline Space (m):", nullptr));
        m_EdtCrossSpace->setText(QString());
        label_14->setText(QCoreApplication::translate("LoadSegyDataRange", "Inline Increment:", nullptr));
        labelStartOffset->setText(QCoreApplication::translate("LoadSegyDataRange", "Nearest Offset (m):", nullptr));
        labelOffsetInc->setText(QCoreApplication::translate("LoadSegyDataRange", "Offset Interval (m):", nullptr));
        labelOffsetNumber->setText(QCoreApplication::translate("LoadSegyDataRange", "Offset Number:", nullptr));
        m_LblInLineUnit->setText(QCoreApplication::translate("LoadSegyDataRange", "Inline Space (m):", nullptr));
        m_EdtCrosslineNumber->setText(QString());
        label_21->setText(QCoreApplication::translate("LoadSegyDataRange", "Crossline Number:", nullptr));
        labelMaxAzim->setText(QCoreApplication::translate("LoadSegyDataRange", "Maximum Azimuth", nullptr));
        labelMaxFold->setText(QCoreApplication::translate("LoadSegyDataRange", "Maximum Fold", nullptr));
        m_BtnLoad->setText(QCoreApplication::translate("LoadSegyDataRange", "Load...", nullptr));
        label_6->setText(QCoreApplication::translate("LoadSegyDataRange", "?", nullptr));
        m_LblFilePath->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoadSegyDataRange: public Ui_LoadSegyDataRange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGELOADSEGYDATASTEP3_H
