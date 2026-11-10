/********************************************************************************
** Form generated from reading UI file 'xdlgdetectgeobody.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGDETECTGEOBODY_H
#define UI_XDLGDETECTGEOBODY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <xcolormapviewer.h>
#include <xsliderlineedit.h>

QT_BEGIN_NAMESPACE

class Ui_DlgDetectGeobody
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *lineEditGeobodyName;
    QLabel *label_2;
    QLineEdit *lineEditDVName;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    CXRangeFrame *m_lineRangeFrame;
    QPushButton *pushButtonRemovePolygon;
    QLineEdit *lineEditPolygon;
    QPushButton *pushButtonAddPolygon;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxInterval;
    QPushButton *pushButtonAddInterval;
    QLineEdit *lineEditInterval;
    QPushButton *pushButtonRemoveInterval;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButtonTopTWT;
    QLineEdit *lineEditTopTWT;
    QLabel *label_23;
    QSlider *sliderTopTWT;
    QLabel *label_22;
    QRadioButton *radioButtonTopHorizon;
    QPushButton *pushButtonAddTopHorizon;
    QLineEdit *lineEditTopHorizon;
    QPushButton *pushButtonRemoveTopHorizon;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButtonBottomTWT;
    QLineEdit *lineEditBottomTWT;
    QLabel *label_24;
    QSlider *sliderBottomTWT;
    QLabel *label_25;
    QRadioButton *radioButtonBottomHorizon;
    QPushButton *pushButtonAddBottomHorizon;
    QLineEdit *lineEditBottomHorizon;
    QPushButton *pushButtonRemoveBottomHorizon;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_26;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEditLowThreshold;
    QLabel *label_27;
    QLineEdit *lineEditHighThreshold;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_28;
    QLineEdit *lineEditMinimumSize;
    QLabel *label_29;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioButtonFaceConnect;
    QRadioButton *radioButtonCornerConnect;
    QCheckBox *checkBoxSeperate;
    CXColormapViewer *colormapEditor;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgDetectGeobody)
    {
        if (DlgDetectGeobody->objectName().isEmpty())
            DlgDetectGeobody->setObjectName(QString::fromUtf8("DlgDetectGeobody"));
        DlgDetectGeobody->resize(943, 624);
        verticalLayout_2 = new QVBoxLayout(DlgDetectGeobody);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(DlgDetectGeobody);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        lineEditGeobodyName = new QLineEdit(DlgDetectGeobody);
        lineEditGeobodyName->setObjectName(QString::fromUtf8("lineEditGeobodyName"));

        horizontalLayout_4->addWidget(lineEditGeobodyName);

        label_2 = new QLabel(DlgDetectGeobody);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineEditDVName = new QLineEdit(DlgDetectGeobody);
        lineEditDVName->setObjectName(QString::fromUtf8("lineEditDVName"));
        lineEditDVName->setEnabled(false);

        horizontalLayout_4->addWidget(lineEditDVName);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox = new QGroupBox(DlgDetectGeobody);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_lineRangeFrame = new CXRangeFrame(groupBox);
        m_lineRangeFrame->setObjectName(QString::fromUtf8("m_lineRangeFrame"));
        m_lineRangeFrame->setFrameShape(QFrame::StyledPanel);
        m_lineRangeFrame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(m_lineRangeFrame, 1, 0, 1, 5);

        pushButtonRemovePolygon = new QPushButton(groupBox);
        pushButtonRemovePolygon->setObjectName(QString::fromUtf8("pushButtonRemovePolygon"));
        pushButtonRemovePolygon->setMinimumSize(QSize(30, 0));
        pushButtonRemovePolygon->setMaximumSize(QSize(30, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRemovePolygon->setIcon(icon);

        gridLayout->addWidget(pushButtonRemovePolygon, 0, 4, 1, 1);

        lineEditPolygon = new QLineEdit(groupBox);
        lineEditPolygon->setObjectName(QString::fromUtf8("lineEditPolygon"));

        gridLayout->addWidget(lineEditPolygon, 0, 2, 1, 2);

        pushButtonAddPolygon = new QPushButton(groupBox);
        pushButtonAddPolygon->setObjectName(QString::fromUtf8("pushButtonAddPolygon"));
        pushButtonAddPolygon->setMinimumSize(QSize(30, 0));
        pushButtonAddPolygon->setMaximumSize(QSize(30, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddPolygon->setIcon(icon1);

        gridLayout->addWidget(pushButtonAddPolygon, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DlgDetectGeobody);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxInterval = new QCheckBox(groupBox_2);
        checkBoxInterval->setObjectName(QString::fromUtf8("checkBoxInterval"));

        horizontalLayout->addWidget(checkBoxInterval);

        pushButtonAddInterval = new QPushButton(groupBox_2);
        pushButtonAddInterval->setObjectName(QString::fromUtf8("pushButtonAddInterval"));
        pushButtonAddInterval->setEnabled(false);
        pushButtonAddInterval->setMinimumSize(QSize(30, 0));
        pushButtonAddInterval->setMaximumSize(QSize(30, 16777215));
        pushButtonAddInterval->setIcon(icon1);

        horizontalLayout->addWidget(pushButtonAddInterval);

        lineEditInterval = new QLineEdit(groupBox_2);
        lineEditInterval->setObjectName(QString::fromUtf8("lineEditInterval"));
        lineEditInterval->setEnabled(false);

        horizontalLayout->addWidget(lineEditInterval);

        pushButtonRemoveInterval = new QPushButton(groupBox_2);
        pushButtonRemoveInterval->setObjectName(QString::fromUtf8("pushButtonRemoveInterval"));
        pushButtonRemoveInterval->setEnabled(false);
        pushButtonRemoveInterval->setMinimumSize(QSize(30, 0));
        pushButtonRemoveInterval->setMaximumSize(QSize(30, 16777215));
        pushButtonRemoveInterval->setIcon(icon);

        horizontalLayout->addWidget(pushButtonRemoveInterval);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButtonTopTWT = new QRadioButton(groupBox_3);
        radioButtonTopTWT->setObjectName(QString::fromUtf8("radioButtonTopTWT"));
        radioButtonTopTWT->setChecked(true);

        gridLayout_2->addWidget(radioButtonTopTWT, 0, 0, 1, 1);

        lineEditTopTWT = new QLineEdit(groupBox_3);
        lineEditTopTWT->setObjectName(QString::fromUtf8("lineEditTopTWT"));
        lineEditTopTWT->setMinimumSize(QSize(40, 0));
        lineEditTopTWT->setMaximumSize(QSize(40, 16777215));

        gridLayout_2->addWidget(lineEditTopTWT, 0, 1, 1, 2);

        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_2->addWidget(label_23, 0, 3, 1, 1);

        sliderTopTWT = new QSlider(groupBox_3);
        sliderTopTWT->setObjectName(QString::fromUtf8("sliderTopTWT"));
        sliderTopTWT->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(sliderTopTWT, 0, 4, 1, 1);

        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_2->addWidget(label_22, 0, 5, 1, 1);

        radioButtonTopHorizon = new QRadioButton(groupBox_3);
        radioButtonTopHorizon->setObjectName(QString::fromUtf8("radioButtonTopHorizon"));

        gridLayout_2->addWidget(radioButtonTopHorizon, 1, 0, 1, 1);

        pushButtonAddTopHorizon = new QPushButton(groupBox_3);
        pushButtonAddTopHorizon->setObjectName(QString::fromUtf8("pushButtonAddTopHorizon"));
        pushButtonAddTopHorizon->setEnabled(false);
        pushButtonAddTopHorizon->setMinimumSize(QSize(30, 0));
        pushButtonAddTopHorizon->setMaximumSize(QSize(30, 16777215));
        pushButtonAddTopHorizon->setIcon(icon1);

        gridLayout_2->addWidget(pushButtonAddTopHorizon, 1, 1, 1, 1);

        lineEditTopHorizon = new QLineEdit(groupBox_3);
        lineEditTopHorizon->setObjectName(QString::fromUtf8("lineEditTopHorizon"));
        lineEditTopHorizon->setEnabled(false);

        gridLayout_2->addWidget(lineEditTopHorizon, 1, 2, 1, 3);

        pushButtonRemoveTopHorizon = new QPushButton(groupBox_3);
        pushButtonRemoveTopHorizon->setObjectName(QString::fromUtf8("pushButtonRemoveTopHorizon"));
        pushButtonRemoveTopHorizon->setEnabled(false);
        pushButtonRemoveTopHorizon->setMinimumSize(QSize(30, 0));
        pushButtonRemoveTopHorizon->setMaximumSize(QSize(30, 16777215));
        pushButtonRemoveTopHorizon->setIcon(icon);

        gridLayout_2->addWidget(pushButtonRemoveTopHorizon, 1, 5, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioButtonBottomTWT = new QRadioButton(groupBox_4);
        radioButtonBottomTWT->setObjectName(QString::fromUtf8("radioButtonBottomTWT"));
        radioButtonBottomTWT->setChecked(true);

        gridLayout_3->addWidget(radioButtonBottomTWT, 0, 0, 1, 1);

        lineEditBottomTWT = new QLineEdit(groupBox_4);
        lineEditBottomTWT->setObjectName(QString::fromUtf8("lineEditBottomTWT"));
        lineEditBottomTWT->setMinimumSize(QSize(40, 0));
        lineEditBottomTWT->setMaximumSize(QSize(40, 16777215));

        gridLayout_3->addWidget(lineEditBottomTWT, 0, 1, 1, 2);

        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_3->addWidget(label_24, 0, 3, 1, 1);

        sliderBottomTWT = new QSlider(groupBox_4);
        sliderBottomTWT->setObjectName(QString::fromUtf8("sliderBottomTWT"));
        sliderBottomTWT->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(sliderBottomTWT, 0, 4, 1, 1);

        label_25 = new QLabel(groupBox_4);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_3->addWidget(label_25, 0, 5, 1, 1);

        radioButtonBottomHorizon = new QRadioButton(groupBox_4);
        radioButtonBottomHorizon->setObjectName(QString::fromUtf8("radioButtonBottomHorizon"));

        gridLayout_3->addWidget(radioButtonBottomHorizon, 1, 0, 1, 1);

        pushButtonAddBottomHorizon = new QPushButton(groupBox_4);
        pushButtonAddBottomHorizon->setObjectName(QString::fromUtf8("pushButtonAddBottomHorizon"));
        pushButtonAddBottomHorizon->setEnabled(false);
        pushButtonAddBottomHorizon->setMinimumSize(QSize(30, 0));
        pushButtonAddBottomHorizon->setMaximumSize(QSize(30, 16777215));
        pushButtonAddBottomHorizon->setIcon(icon1);

        gridLayout_3->addWidget(pushButtonAddBottomHorizon, 1, 1, 1, 1);

        lineEditBottomHorizon = new QLineEdit(groupBox_4);
        lineEditBottomHorizon->setObjectName(QString::fromUtf8("lineEditBottomHorizon"));
        lineEditBottomHorizon->setEnabled(false);

        gridLayout_3->addWidget(lineEditBottomHorizon, 1, 2, 1, 3);

        pushButtonRemoveBottomHorizon = new QPushButton(groupBox_4);
        pushButtonRemoveBottomHorizon->setObjectName(QString::fromUtf8("pushButtonRemoveBottomHorizon"));
        pushButtonRemoveBottomHorizon->setEnabled(false);
        pushButtonRemoveBottomHorizon->setMinimumSize(QSize(30, 0));
        pushButtonRemoveBottomHorizon->setMaximumSize(QSize(30, 16777215));
        pushButtonRemoveBottomHorizon->setIcon(icon);

        gridLayout_3->addWidget(pushButtonRemoveBottomHorizon, 1, 5, 1, 1);


        verticalLayout->addWidget(groupBox_4);


        horizontalLayout_2->addWidget(groupBox_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        groupBox_5 = new QGroupBox(DlgDetectGeobody);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(320, 0));
        groupBox_5->setMaximumSize(QSize(320, 16777215));
        verticalLayout_3 = new QVBoxLayout(groupBox_5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_26 = new QLabel(groupBox_5);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        verticalLayout_3->addWidget(label_26);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEditLowThreshold = new QLineEdit(groupBox_5);
        lineEditLowThreshold->setObjectName(QString::fromUtf8("lineEditLowThreshold"));
        lineEditLowThreshold->setMinimumSize(QSize(100, 0));
        lineEditLowThreshold->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(lineEditLowThreshold);

        label_27 = new QLabel(groupBox_5);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout_3->addWidget(label_27);

        lineEditHighThreshold = new QLineEdit(groupBox_5);
        lineEditHighThreshold->setObjectName(QString::fromUtf8("lineEditHighThreshold"));
        lineEditHighThreshold->setMinimumSize(QSize(100, 0));
        lineEditHighThreshold->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(lineEditHighThreshold);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_28 = new QLabel(groupBox_5);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout_6->addWidget(label_28);

        lineEditMinimumSize = new QLineEdit(groupBox_5);
        lineEditMinimumSize->setObjectName(QString::fromUtf8("lineEditMinimumSize"));
        lineEditMinimumSize->setMinimumSize(QSize(40, 0));
        lineEditMinimumSize->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_6->addWidget(lineEditMinimumSize);


        verticalLayout_3->addLayout(horizontalLayout_6);

        label_29 = new QLabel(groupBox_5);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        verticalLayout_3->addWidget(label_29);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        radioButtonFaceConnect = new QRadioButton(groupBox_5);
        radioButtonFaceConnect->setObjectName(QString::fromUtf8("radioButtonFaceConnect"));

        horizontalLayout_5->addWidget(radioButtonFaceConnect);

        radioButtonCornerConnect = new QRadioButton(groupBox_5);
        radioButtonCornerConnect->setObjectName(QString::fromUtf8("radioButtonCornerConnect"));
        radioButtonCornerConnect->setChecked(true);

        horizontalLayout_5->addWidget(radioButtonCornerConnect);


        verticalLayout_3->addLayout(horizontalLayout_5);

        checkBoxSeperate = new QCheckBox(groupBox_5);
        checkBoxSeperate->setObjectName(QString::fromUtf8("checkBoxSeperate"));
        checkBoxSeperate->setChecked(true);

        verticalLayout_3->addWidget(checkBoxSeperate);


        horizontalLayout_7->addWidget(groupBox_5);

        colormapEditor = new CXColormapViewer(DlgDetectGeobody);
        colormapEditor->setObjectName(QString::fromUtf8("colormapEditor"));

        horizontalLayout_7->addWidget(colormapEditor);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(DlgDetectGeobody);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(DlgDetectGeobody);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgDetectGeobody, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgDetectGeobody, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgDetectGeobody);
    } // setupUi

    void retranslateUi(QDialog *DlgDetectGeobody)
    {
        DlgDetectGeobody->setWindowTitle(QCoreApplication::translate("DlgDetectGeobody", "Geobody Detection", nullptr));
        label->setText(QCoreApplication::translate("DlgDetectGeobody", "Geobody Name:", nullptr));
        label_2->setText(QCoreApplication::translate("DlgDetectGeobody", "Seismic Data Volume:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgDetectGeobody", "Range of Plane", nullptr));
        pushButtonRemovePolygon->setText(QString());
        pushButtonAddPolygon->setText(QString());
        label_3->setText(QCoreApplication::translate("DlgDetectGeobody", "Boundary Polygon:", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DlgDetectGeobody", "Range of Z", nullptr));
        checkBoxInterval->setText(QCoreApplication::translate("DlgDetectGeobody", "By Interval", nullptr));
        pushButtonAddInterval->setText(QString());
        pushButtonRemoveInterval->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("DlgDetectGeobody", "Top", nullptr));
        radioButtonTopTWT->setText(QCoreApplication::translate("DlgDetectGeobody", "By TWT(ms)", nullptr));
        label_23->setText(QCoreApplication::translate("DlgDetectGeobody", "1000", nullptr));
        label_22->setText(QCoreApplication::translate("DlgDetectGeobody", "2000", nullptr));
        radioButtonTopHorizon->setText(QCoreApplication::translate("DlgDetectGeobody", "By Horizon", nullptr));
        pushButtonAddTopHorizon->setText(QString());
        pushButtonRemoveTopHorizon->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("DlgDetectGeobody", "Bottom", nullptr));
        radioButtonBottomTWT->setText(QCoreApplication::translate("DlgDetectGeobody", "By TWT(ms)", nullptr));
        label_24->setText(QCoreApplication::translate("DlgDetectGeobody", "1000", nullptr));
        label_25->setText(QCoreApplication::translate("DlgDetectGeobody", "2000", nullptr));
        radioButtonBottomHorizon->setText(QCoreApplication::translate("DlgDetectGeobody", "By Horizon", nullptr));
        pushButtonAddBottomHorizon->setText(QString());
        pushButtonRemoveBottomHorizon->setText(QString());
        groupBox_5->setTitle(QCoreApplication::translate("DlgDetectGeobody", "Detection Parameters", nullptr));
        label_26->setText(QCoreApplication::translate("DlgDetectGeobody", "Detection threshold:", nullptr));
        label_27->setText(QCoreApplication::translate("DlgDetectGeobody", "<= Geobody  <= ", nullptr));
        label_28->setText(QCoreApplication::translate("DlgDetectGeobody", "Minimum Geobody Size (Cell Number):", nullptr));
        lineEditMinimumSize->setText(QCoreApplication::translate("DlgDetectGeobody", "100", nullptr));
        label_29->setText(QCoreApplication::translate("DlgDetectGeobody", "Connectivity:", nullptr));
        radioButtonFaceConnect->setText(QCoreApplication::translate("DlgDetectGeobody", "Face", nullptr));
        radioButtonCornerConnect->setText(QCoreApplication::translate("DlgDetectGeobody", "Corner", nullptr));
        checkBoxSeperate->setText(QCoreApplication::translate("DlgDetectGeobody", "Merge into a big geobody", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgDetectGeobody: public Ui_DlgDetectGeobody {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGDETECTGEOBODY_H
