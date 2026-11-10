/********************************************************************************
** Form generated from reading UI file 'xdlgremovefootprint.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGREMOVEFOOTPRINT_H
#define UI_XDLGREMOVEFOOTPRINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <qchartview.h>
#include <xsvgwidget.h>

QT_BEGIN_NAMESPACE

class Ui_DlgRemoveFootprint
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *m_pSliderSlice;
    QLineEdit *m_pLineEdtSliceZ;
    QLabel *m_pLabelZUnit;
    CXSvgWidget *m_pSvgWidget;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *m_pCombWavelet;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QComboBox *m_pCombDirection;
    QLabel *label_5;
    QComboBox *m_pCombLevel;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;
    QComboBox *m_pCombWindow;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSlider *m_pSliderThreshold;
    QDoubleSpinBox *m_pSpinThreshold;
    QChartView *graphicsView;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *m_pButtonOne;
    QPushButton *m_pButtonAll;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgRemoveFootprint)
    {
        if (DlgRemoveFootprint->objectName().isEmpty())
            DlgRemoveFootprint->setObjectName(QString::fromUtf8("DlgRemoveFootprint"));
        DlgRemoveFootprint->resize(1103, 765);
        gridLayout_3 = new QGridLayout(DlgRemoveFootprint);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DlgRemoveFootprint);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_pSliderSlice = new QSlider(DlgRemoveFootprint);
        m_pSliderSlice->setObjectName(QString::fromUtf8("m_pSliderSlice"));
        m_pSliderSlice->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(m_pSliderSlice);

        m_pLineEdtSliceZ = new QLineEdit(DlgRemoveFootprint);
        m_pLineEdtSliceZ->setObjectName(QString::fromUtf8("m_pLineEdtSliceZ"));

        horizontalLayout->addWidget(m_pLineEdtSliceZ);

        m_pLabelZUnit = new QLabel(DlgRemoveFootprint);
        m_pLabelZUnit->setObjectName(QString::fromUtf8("m_pLabelZUnit"));

        horizontalLayout->addWidget(m_pLabelZUnit);

        horizontalLayout->setStretch(1, 1);

        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        m_pSvgWidget = new CXSvgWidget(DlgRemoveFootprint);
        m_pSvgWidget->setObjectName(QString::fromUtf8("m_pSvgWidget"));
        m_pSvgWidget->setMinimumSize(QSize(0, 500));

        gridLayout_3->addWidget(m_pSvgWidget, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox = new QGroupBox(DlgRemoveFootprint);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        m_pCombWavelet = new QComboBox(groupBox);
        m_pCombWavelet->addItem(QString());
        m_pCombWavelet->addItem(QString());
        m_pCombWavelet->addItem(QString());
        m_pCombWavelet->setObjectName(QString::fromUtf8("m_pCombWavelet"));

        gridLayout->addWidget(m_pCombWavelet, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        m_pCombDirection = new QComboBox(groupBox);
        m_pCombDirection->addItem(QString());
        m_pCombDirection->addItem(QString());
        m_pCombDirection->addItem(QString());
        m_pCombDirection->setObjectName(QString::fromUtf8("m_pCombDirection"));

        gridLayout->addWidget(m_pCombDirection, 0, 4, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_pCombLevel = new QComboBox(groupBox);
        m_pCombLevel->addItem(QString());
        m_pCombLevel->addItem(QString());
        m_pCombLevel->addItem(QString());
        m_pCombLevel->addItem(QString());
        m_pCombLevel->setObjectName(QString::fromUtf8("m_pCombLevel"));

        gridLayout->addWidget(m_pCombLevel, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 3, 1, 1);

        m_pCombWindow = new QComboBox(groupBox);
        m_pCombWindow->addItem(QString());
        m_pCombWindow->addItem(QString());
        m_pCombWindow->addItem(QString());
        m_pCombWindow->setObjectName(QString::fromUtf8("m_pCombWindow"));

        gridLayout->addWidget(m_pCombWindow, 1, 4, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 2);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnStretch(4, 2);
        gridLayout->setColumnMinimumWidth(1, 1);
        gridLayout->setColumnMinimumWidth(4, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        m_pSliderThreshold = new QSlider(groupBox);
        m_pSliderThreshold->setObjectName(QString::fromUtf8("m_pSliderThreshold"));
        m_pSliderThreshold->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(m_pSliderThreshold);

        m_pSpinThreshold = new QDoubleSpinBox(groupBox);
        m_pSpinThreshold->setObjectName(QString::fromUtf8("m_pSpinThreshold"));
        m_pSpinThreshold->setMinimumSize(QSize(60, 0));

        horizontalLayout_3->addWidget(m_pSpinThreshold);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox);

        graphicsView = new QChartView(DlgRemoveFootprint);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(0, 180));

        horizontalLayout_2->addWidget(graphicsView);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 3);

        gridLayout_3->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_pButtonOne = new QPushButton(DlgRemoveFootprint);
        m_pButtonOne->setObjectName(QString::fromUtf8("m_pButtonOne"));

        horizontalLayout_4->addWidget(m_pButtonOne);

        m_pButtonAll = new QPushButton(DlgRemoveFootprint);
        m_pButtonAll->setObjectName(QString::fromUtf8("m_pButtonAll"));

        horizontalLayout_4->addWidget(m_pButtonAll);

        buttonBox = new QDialogButtonBox(DlgRemoveFootprint);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);

        horizontalLayout_4->addWidget(buttonBox);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5->setStretch(0, 1);

        gridLayout_3->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        gridLayout_3->setRowStretch(1, 1);

        retranslateUi(DlgRemoveFootprint);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgRemoveFootprint, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgRemoveFootprint, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgRemoveFootprint);
    } // setupUi

    void retranslateUi(QDialog *DlgRemoveFootprint)
    {
        DlgRemoveFootprint->setWindowTitle(QCoreApplication::translate("DlgRemoveFootprint", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DlgRemoveFootprint", "Seismic Slice", nullptr));
        m_pLabelZUnit->setText(QCoreApplication::translate("DlgRemoveFootprint", "ms", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgRemoveFootprint", "Parameters", nullptr));
        label_2->setText(QCoreApplication::translate("DlgRemoveFootprint", "Wavelet", nullptr));
        m_pCombWavelet->setItemText(0, QCoreApplication::translate("DlgRemoveFootprint", "sym4", nullptr));
        m_pCombWavelet->setItemText(1, QCoreApplication::translate("DlgRemoveFootprint", "db8", nullptr));
        m_pCombWavelet->setItemText(2, QCoreApplication::translate("DlgRemoveFootprint", "coif2", nullptr));

        label_3->setText(QCoreApplication::translate("DlgRemoveFootprint", "Direction", nullptr));
        m_pCombDirection->setItemText(0, QCoreApplication::translate("DlgRemoveFootprint", "Horizontal", nullptr));
        m_pCombDirection->setItemText(1, QCoreApplication::translate("DlgRemoveFootprint", "Vertical", nullptr));
        m_pCombDirection->setItemText(2, QCoreApplication::translate("DlgRemoveFootprint", "Both", nullptr));

        label_5->setText(QCoreApplication::translate("DlgRemoveFootprint", "Level", nullptr));
        m_pCombLevel->setItemText(0, QCoreApplication::translate("DlgRemoveFootprint", "3", nullptr));
        m_pCombLevel->setItemText(1, QCoreApplication::translate("DlgRemoveFootprint", "4", nullptr));
        m_pCombLevel->setItemText(2, QCoreApplication::translate("DlgRemoveFootprint", "5", nullptr));
        m_pCombLevel->setItemText(3, QCoreApplication::translate("DlgRemoveFootprint", "6", nullptr));

        label_6->setText(QCoreApplication::translate("DlgRemoveFootprint", "Window", nullptr));
        m_pCombWindow->setItemText(0, QCoreApplication::translate("DlgRemoveFootprint", "3", nullptr));
        m_pCombWindow->setItemText(1, QCoreApplication::translate("DlgRemoveFootprint", "5", nullptr));
        m_pCombWindow->setItemText(2, QCoreApplication::translate("DlgRemoveFootprint", "7", nullptr));

        label_4->setText(QCoreApplication::translate("DlgRemoveFootprint", "Threshold", nullptr));
        m_pButtonOne->setText(QCoreApplication::translate("DlgRemoveFootprint", "Computer One", nullptr));
        m_pButtonAll->setText(QCoreApplication::translate("DlgRemoveFootprint", "Computer All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgRemoveFootprint: public Ui_DlgRemoveFootprint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGREMOVEFOOTPRINT_H
