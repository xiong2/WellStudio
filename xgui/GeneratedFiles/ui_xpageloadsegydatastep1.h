/********************************************************************************
** Form generated from reading UI file 'xpageloadsegydatastep1.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGELOADSEGYDATASTEP1_H
#define UI_XPAGELOADSEGYDATASTEP1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loadsegystep1
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *line;
    QListWidget *m_LstFilePath;
    QPushButton *m_PtnVolumeHeader;
    QPushButton *m_PtnLineHeader;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QGroupBox *m_GrpPreview;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *m_GrpDisplayMode;
    QGridLayout *gridLayout_3;
    QRadioButton *m_RdoWiggle;
    QRadioButton *m_RdoHistogram;
    QLabel *label_4;
    QSlider *m_SldTraceTick;
    QSpinBox *m_EdtCurTraceValue;
    QCheckBox *m_ChkFlipBytes;
    QLabel *label_3;
    QComboBox *m_CmbSampleFormat;
    QLineEdit *m_EdtSampleInterval;
    QLabel *label_5;
    QLineEdit *m_EdtSampleNumber;
    QLabel *label_6;
    QFrame *m_FramePreview;

    void setupUi(QWidget *loadsegystep1)
    {
        if (loadsegystep1->objectName().isEmpty())
            loadsegystep1->setObjectName(QString::fromUtf8("loadsegystep1"));
        loadsegystep1->resize(934, 725);
        gridLayout = new QGridLayout(loadsegystep1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(loadsegystep1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        line = new QFrame(loadsegystep1);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 3);

        m_LstFilePath = new QListWidget(loadsegystep1);
        m_LstFilePath->setObjectName(QString::fromUtf8("m_LstFilePath"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_LstFilePath->sizePolicy().hasHeightForWidth());
        m_LstFilePath->setSizePolicy(sizePolicy);
        m_LstFilePath->setMinimumSize(QSize(60, 0));
        m_LstFilePath->setMaximumSize(QSize(16777215, 60));
        m_LstFilePath->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_LstFilePath->setProperty("showDropIndicator", QVariant(false));
        m_LstFilePath->setSelectionMode(QAbstractItemView::ExtendedSelection);

        gridLayout->addWidget(m_LstFilePath, 4, 0, 2, 1);

        m_PtnVolumeHeader = new QPushButton(loadsegystep1);
        m_PtnVolumeHeader->setObjectName(QString::fromUtf8("m_PtnVolumeHeader"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_PtnVolumeHeader->sizePolicy().hasHeightForWidth());
        m_PtnVolumeHeader->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_PtnVolumeHeader, 4, 2, 1, 1);

        m_PtnLineHeader = new QPushButton(loadsegystep1);
        m_PtnLineHeader->setObjectName(QString::fromUtf8("m_PtnLineHeader"));
        sizePolicy1.setHeightForWidth(m_PtnLineHeader->sizePolicy().hasHeightForWidth());
        m_PtnLineHeader->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(m_PtnLineHeader, 5, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(loadsegystep1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 3);

        m_GrpPreview = new QGroupBox(loadsegystep1);
        m_GrpPreview->setObjectName(QString::fromUtf8("m_GrpPreview"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_GrpPreview->sizePolicy().hasHeightForWidth());
        m_GrpPreview->setSizePolicy(sizePolicy3);
        gridLayout_5 = new QGridLayout(m_GrpPreview);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_GrpDisplayMode = new QGroupBox(m_GrpPreview);
        m_GrpDisplayMode->setObjectName(QString::fromUtf8("m_GrpDisplayMode"));
        sizePolicy1.setHeightForWidth(m_GrpDisplayMode->sizePolicy().hasHeightForWidth());
        m_GrpDisplayMode->setSizePolicy(sizePolicy1);
        gridLayout_3 = new QGridLayout(m_GrpDisplayMode);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        m_RdoWiggle = new QRadioButton(m_GrpDisplayMode);
        m_RdoWiggle->setObjectName(QString::fromUtf8("m_RdoWiggle"));
        m_RdoWiggle->setChecked(true);

        gridLayout_3->addWidget(m_RdoWiggle, 0, 0, 1, 1);

        m_RdoHistogram = new QRadioButton(m_GrpDisplayMode);
        m_RdoHistogram->setObjectName(QString::fromUtf8("m_RdoHistogram"));

        gridLayout_3->addWidget(m_RdoHistogram, 0, 1, 1, 1);


        horizontalLayout_3->addWidget(m_GrpDisplayMode);

        label_4 = new QLabel(m_GrpPreview);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_4);

        m_SldTraceTick = new QSlider(m_GrpPreview);
        m_SldTraceTick->setObjectName(QString::fromUtf8("m_SldTraceTick"));
        m_SldTraceTick->setOrientation(Qt::Horizontal);
        m_SldTraceTick->setTickPosition(QSlider::NoTicks);

        horizontalLayout_3->addWidget(m_SldTraceTick);

        m_EdtCurTraceValue = new QSpinBox(m_GrpPreview);
        m_EdtCurTraceValue->setObjectName(QString::fromUtf8("m_EdtCurTraceValue"));
        m_EdtCurTraceValue->setMinimumSize(QSize(70, 0));
        m_EdtCurTraceValue->setMaximumSize(QSize(70, 16777215));
        m_EdtCurTraceValue->setMinimum(1);

        horizontalLayout_3->addWidget(m_EdtCurTraceValue);


        gridLayout_5->addLayout(horizontalLayout_3, 9, 0, 1, 4);

        m_ChkFlipBytes = new QCheckBox(m_GrpPreview);
        m_ChkFlipBytes->setObjectName(QString::fromUtf8("m_ChkFlipBytes"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(m_ChkFlipBytes->sizePolicy().hasHeightForWidth());
        m_ChkFlipBytes->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(m_ChkFlipBytes, 1, 2, 1, 1);

        label_3 = new QLabel(m_GrpPreview);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setLayoutDirection(Qt::RightToLeft);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_5->addWidget(label_3, 1, 0, 1, 1);

        m_CmbSampleFormat = new QComboBox(m_GrpPreview);
        m_CmbSampleFormat->addItem(QString());
        m_CmbSampleFormat->addItem(QString());
        m_CmbSampleFormat->addItem(QString());
        m_CmbSampleFormat->addItem(QString());
        m_CmbSampleFormat->addItem(QString());
        m_CmbSampleFormat->setObjectName(QString::fromUtf8("m_CmbSampleFormat"));

        gridLayout_5->addWidget(m_CmbSampleFormat, 1, 1, 1, 1);

        m_EdtSampleInterval = new QLineEdit(m_GrpPreview);
        m_EdtSampleInterval->setObjectName(QString::fromUtf8("m_EdtSampleInterval"));

        gridLayout_5->addWidget(m_EdtSampleInterval, 2, 3, 1, 1);

        label_5 = new QLabel(m_GrpPreview);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_5, 2, 2, 1, 1);

        m_EdtSampleNumber = new QLineEdit(m_GrpPreview);
        m_EdtSampleNumber->setObjectName(QString::fromUtf8("m_EdtSampleNumber"));
        m_EdtSampleNumber->setReadOnly(true);

        gridLayout_5->addWidget(m_EdtSampleNumber, 2, 1, 1, 1);

        label_6 = new QLabel(m_GrpPreview);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(label_6, 2, 0, 1, 1);

        m_FramePreview = new QFrame(m_GrpPreview);
        m_FramePreview->setObjectName(QString::fromUtf8("m_FramePreview"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(1);
        sizePolicy5.setHeightForWidth(m_FramePreview->sizePolicy().hasHeightForWidth());
        m_FramePreview->setSizePolicy(sizePolicy5);
        m_FramePreview->setMinimumSize(QSize(0, 0));
        m_FramePreview->setFrameShape(QFrame::StyledPanel);
        m_FramePreview->setFrameShadow(QFrame::Raised);

        gridLayout_5->addWidget(m_FramePreview, 7, 0, 1, 4);

        m_FramePreview->raise();
        m_ChkFlipBytes->raise();
        label_3->raise();
        m_CmbSampleFormat->raise();
        m_EdtSampleNumber->raise();
        label_6->raise();
        label_5->raise();
        m_EdtSampleInterval->raise();

        gridLayout->addWidget(m_GrpPreview, 6, 0, 1, 3);


        retranslateUi(loadsegystep1);

        QMetaObject::connectSlotsByName(loadsegystep1);
    } // setupUi

    void retranslateUi(QWidget *loadsegystep1)
    {
        loadsegystep1->setWindowTitle(QCoreApplication::translate("loadsegystep1", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("loadsegystep1", "Step 1 of 4: Data Type", nullptr));
        m_PtnVolumeHeader->setText(QCoreApplication::translate("loadsegystep1", "Volume Header...", nullptr));
        m_PtnLineHeader->setText(QCoreApplication::translate("loadsegystep1", "Line Header...", nullptr));
        label_2->setText(QCoreApplication::translate("loadsegystep1", "Input Files:", nullptr));
        m_GrpPreview->setTitle(QCoreApplication::translate("loadsegystep1", "Preview", nullptr));
        m_GrpDisplayMode->setTitle(QCoreApplication::translate("loadsegystep1", "Display Mode:", nullptr));
#if QT_CONFIG(accessibility)
        m_RdoWiggle->setAccessibleName(QCoreApplication::translate("loadsegystep1", "Wiggle", nullptr));
#endif // QT_CONFIG(accessibility)
        m_RdoWiggle->setText(QCoreApplication::translate("loadsegystep1", "Wiggle", nullptr));
#if QT_CONFIG(accessibility)
        m_RdoHistogram->setAccessibleName(QCoreApplication::translate("loadsegystep1", "Histogram", nullptr));
#endif // QT_CONFIG(accessibility)
        m_RdoHistogram->setText(QCoreApplication::translate("loadsegystep1", "Histogram", nullptr));
        label_4->setText(QCoreApplication::translate("loadsegystep1", "Current Trace (Total: )", nullptr));
#if QT_CONFIG(accessibility)
        m_ChkFlipBytes->setAccessibleName(QCoreApplication::translate("loadsegystep1", "Flip", nullptr));
#endif // QT_CONFIG(accessibility)
        m_ChkFlipBytes->setText(QCoreApplication::translate("loadsegystep1", "Flip Bytes", nullptr));
        label_3->setText(QCoreApplication::translate("loadsegystep1", "Sample Format:", nullptr));
        m_CmbSampleFormat->setItemText(0, QCoreApplication::translate("loadsegystep1", "32-bit IEEE Float", nullptr));
        m_CmbSampleFormat->setItemText(1, QCoreApplication::translate("loadsegystep1", "32-bit IBM Float", nullptr));
        m_CmbSampleFormat->setItemText(2, QCoreApplication::translate("loadsegystep1", "32-bit Integer", nullptr));
        m_CmbSampleFormat->setItemText(3, QCoreApplication::translate("loadsegystep1", "16-bit Integer", nullptr));
        m_CmbSampleFormat->setItemText(4, QCoreApplication::translate("loadsegystep1", "8-bit Integer", nullptr));

        label_5->setText(QCoreApplication::translate("loadsegystep1", "Sample Interval:", nullptr));
        label_6->setText(QCoreApplication::translate("loadsegystep1", "Sample Number:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loadsegystep1: public Ui_loadsegystep1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGELOADSEGYDATASTEP1_H
