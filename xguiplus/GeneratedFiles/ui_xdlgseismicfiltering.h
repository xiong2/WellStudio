/********************************************************************************
** Form generated from reading UI file 'xdlgseismicfiltering.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGSEISMICFILTERING_H
#define UI_XDLGSEISMICFILTERING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DlgSeismicFiltering
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *m_pRadioLowCut;
    QRadioButton *m_pRadioHighCut;
    QRadioButton *m_pRadioBandPass;
    QGroupBox *m_pGroupBoxFiltering;
    QGridLayout *gridLayout_3;
    QLabel *m_pLabelHighOver;
    QLabel *m_pLabelLowOver;
    QLineEdit *m_pLineEdtHighCut;
    QLineEdit *m_pLineEdtLowOverlap;
    QLineEdit *m_pLineEdtHighOverlap;
    QSpacerItem *horizontalSpacer_6;
    QLabel *m_pLabeHigh;
    QLabel *m_pLabelLow;
    QLineEdit *m_pLineEdtLowCut;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *m_pChkBoxInvalid;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgSeismicFiltering)
    {
        if (DlgSeismicFiltering->objectName().isEmpty())
            DlgSeismicFiltering->setObjectName(QString::fromUtf8("DlgSeismicFiltering"));
        DlgSeismicFiltering->resize(581, 295);
        gridLayout_2 = new QGridLayout(DlgSeismicFiltering);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(DlgSeismicFiltering);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pRadioLowCut = new QRadioButton(groupBox);
        m_pRadioLowCut->setObjectName(QString::fromUtf8("m_pRadioLowCut"));
        m_pRadioLowCut->setChecked(false);

        gridLayout->addWidget(m_pRadioLowCut, 0, 0, 1, 1);

        m_pRadioHighCut = new QRadioButton(groupBox);
        m_pRadioHighCut->setObjectName(QString::fromUtf8("m_pRadioHighCut"));

        gridLayout->addWidget(m_pRadioHighCut, 0, 1, 1, 1);

        m_pRadioBandPass = new QRadioButton(groupBox);
        m_pRadioBandPass->setObjectName(QString::fromUtf8("m_pRadioBandPass"));
        m_pRadioBandPass->setChecked(true);

        gridLayout->addWidget(m_pRadioBandPass, 0, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 2);

        m_pGroupBoxFiltering = new QGroupBox(DlgSeismicFiltering);
        m_pGroupBoxFiltering->setObjectName(QString::fromUtf8("m_pGroupBoxFiltering"));
        m_pGroupBoxFiltering->setCheckable(false);
        gridLayout_3 = new QGridLayout(m_pGroupBoxFiltering);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pLabelHighOver = new QLabel(m_pGroupBoxFiltering);
        m_pLabelHighOver->setObjectName(QString::fromUtf8("m_pLabelHighOver"));
        m_pLabelHighOver->setMinimumSize(QSize(140, 0));

        gridLayout_3->addWidget(m_pLabelHighOver, 1, 3, 1, 1);

        m_pLabelLowOver = new QLabel(m_pGroupBoxFiltering);
        m_pLabelLowOver->setObjectName(QString::fromUtf8("m_pLabelLowOver"));
        m_pLabelLowOver->setMinimumSize(QSize(140, 0));

        gridLayout_3->addWidget(m_pLabelLowOver, 0, 3, 1, 1);

        m_pLineEdtHighCut = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtHighCut->setObjectName(QString::fromUtf8("m_pLineEdtHighCut"));
        m_pLineEdtHighCut->setMinimumSize(QSize(60, 0));
        m_pLineEdtHighCut->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(m_pLineEdtHighCut, 1, 1, 1, 1);

        m_pLineEdtLowOverlap = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtLowOverlap->setObjectName(QString::fromUtf8("m_pLineEdtLowOverlap"));
        m_pLineEdtLowOverlap->setMinimumSize(QSize(60, 0));
        m_pLineEdtLowOverlap->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(m_pLineEdtLowOverlap, 0, 4, 1, 1);

        m_pLineEdtHighOverlap = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtHighOverlap->setObjectName(QString::fromUtf8("m_pLineEdtHighOverlap"));
        m_pLineEdtHighOverlap->setMinimumSize(QSize(60, 0));
        m_pLineEdtHighOverlap->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(m_pLineEdtHighOverlap, 1, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 1, 2, 1, 1);

        m_pLabeHigh = new QLabel(m_pGroupBoxFiltering);
        m_pLabeHigh->setObjectName(QString::fromUtf8("m_pLabeHigh"));
        m_pLabeHigh->setMinimumSize(QSize(120, 0));

        gridLayout_3->addWidget(m_pLabeHigh, 1, 0, 1, 1);

        m_pLabelLow = new QLabel(m_pGroupBoxFiltering);
        m_pLabelLow->setObjectName(QString::fromUtf8("m_pLabelLow"));
        m_pLabelLow->setMinimumSize(QSize(120, 0));

        gridLayout_3->addWidget(m_pLabelLow, 0, 0, 1, 1);

        m_pLineEdtLowCut = new QLineEdit(m_pGroupBoxFiltering);
        m_pLineEdtLowCut->setObjectName(QString::fromUtf8("m_pLineEdtLowCut"));
        m_pLineEdtLowCut->setMinimumSize(QSize(60, 0));
        m_pLineEdtLowCut->setMaximumSize(QSize(80, 16777215));

        gridLayout_3->addWidget(m_pLineEdtLowCut, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 2, 1, 1);


        gridLayout_2->addWidget(m_pGroupBoxFiltering, 1, 0, 1, 2);

        m_pChkBoxInvalid = new QCheckBox(DlgSeismicFiltering);
        m_pChkBoxInvalid->setObjectName(QString::fromUtf8("m_pChkBoxInvalid"));
        m_pChkBoxInvalid->setMinimumSize(QSize(200, 0));
        m_pChkBoxInvalid->setChecked(true);

        gridLayout_2->addWidget(m_pChkBoxInvalid, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(354, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 1, 1, 1);

        buttonBox = new QDialogButtonBox(DlgSeismicFiltering);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 4, 1, 1, 1);

        buttonBox->raise();
        groupBox->raise();
        m_pGroupBoxFiltering->raise();
        m_pChkBoxInvalid->raise();

        retranslateUi(DlgSeismicFiltering);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgSeismicFiltering, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgSeismicFiltering, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgSeismicFiltering);
    } // setupUi

    void retranslateUi(QDialog *DlgSeismicFiltering)
    {
        DlgSeismicFiltering->setWindowTitle(QCoreApplication::translate("DlgSeismicFiltering", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgSeismicFiltering", "Filtering Method", nullptr));
        m_pRadioLowCut->setText(QCoreApplication::translate("DlgSeismicFiltering", "Low Cut", nullptr));
        m_pRadioHighCut->setText(QCoreApplication::translate("DlgSeismicFiltering", "High Cut", nullptr));
        m_pRadioBandPass->setText(QCoreApplication::translate("DlgSeismicFiltering", "Band Pass", nullptr));
        m_pGroupBoxFiltering->setTitle(QCoreApplication::translate("DlgSeismicFiltering", "Filtering Parameters", nullptr));
        m_pLabelHighOver->setText(QCoreApplication::translate("DlgSeismicFiltering", "High Overlap Frequency", nullptr));
        m_pLabelLowOver->setText(QCoreApplication::translate("DlgSeismicFiltering", "Low Overlap Frequency         ", nullptr));
        m_pLineEdtHighCut->setText(QCoreApplication::translate("DlgSeismicFiltering", "60", nullptr));
        m_pLineEdtLowOverlap->setText(QCoreApplication::translate("DlgSeismicFiltering", "2", nullptr));
        m_pLineEdtHighOverlap->setText(QCoreApplication::translate("DlgSeismicFiltering", "5", nullptr));
        m_pLabeHigh->setText(QCoreApplication::translate("DlgSeismicFiltering", "High Cut Frequency    ", nullptr));
        m_pLabelLow->setText(QCoreApplication::translate("DlgSeismicFiltering", "Low Cut Frequency                ", nullptr));
        m_pLineEdtLowCut->setText(QCoreApplication::translate("DlgSeismicFiltering", "10", nullptr));
        m_pChkBoxInvalid->setText(QCoreApplication::translate("DlgSeismicFiltering", "Treat zero as invalid ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgSeismicFiltering: public Ui_DlgSeismicFiltering {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGSEISMICFILTERING_H
