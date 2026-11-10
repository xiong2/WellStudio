/********************************************************************************
** Form generated from reading UI file 'xdlglfinterpolation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGLFINTERPOLATION_H
#define UI_XDLGLFINTERPOLATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DlgLFMInterpolation
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labelkriging;
    QComboBox *m_pCombMethod;
    QSpacerItem *horizontalSpacer;
    QGroupBox *m_pGroupIDP;
    QGridLayout *gridLayout_3;
    QLineEdit *m_pSearchRadius;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *m_pPower;
    QLineEdit *m_pIDPMaximumSampleNumber;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_pLabelVariogram;
    QComboBox *m_pCombVariogram;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *m_pGroupKriging;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *m_pSill;
    QLabel *label_4;
    QLineEdit *m_pNugget;
    QLabel *label_5;
    QLineEdit *m_pMajorRange;
    QLabel *label_7;
    QLineEdit *m_pMinorRange;
    QLabel *label_6;
    QLineEdit *m_pAzimuth;
    QLabel *label_8;
    QLineEdit *m_pKMaximumSampleNumber;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgLFMInterpolation)
    {
        if (DlgLFMInterpolation->objectName().isEmpty())
            DlgLFMInterpolation->setObjectName(QString::fromUtf8("DlgLFMInterpolation"));
        DlgLFMInterpolation->resize(574, 300);
        gridLayout_2 = new QGridLayout(DlgLFMInterpolation);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labelkriging = new QLabel(DlgLFMInterpolation);
        m_labelkriging->setObjectName(QString::fromUtf8("m_labelkriging"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labelkriging->sizePolicy().hasHeightForWidth());
        m_labelkriging->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_labelkriging);

        m_pCombMethod = new QComboBox(DlgLFMInterpolation);
        m_pCombMethod->addItem(QString());
        m_pCombMethod->addItem(QString());
        m_pCombMethod->addItem(QString());
        m_pCombMethod->setObjectName(QString::fromUtf8("m_pCombMethod"));
        m_pCombMethod->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(m_pCombMethod);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        m_pGroupIDP = new QGroupBox(DlgLFMInterpolation);
        m_pGroupIDP->setObjectName(QString::fromUtf8("m_pGroupIDP"));
        gridLayout_3 = new QGridLayout(m_pGroupIDP);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pSearchRadius = new QLineEdit(m_pGroupIDP);
        m_pSearchRadius->setObjectName(QString::fromUtf8("m_pSearchRadius"));

        gridLayout_3->addWidget(m_pSearchRadius, 0, 1, 1, 1);

        label_9 = new QLabel(m_pGroupIDP);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1);

        label_11 = new QLabel(m_pGroupIDP);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 0, 2, 1, 1);

        label_10 = new QLabel(m_pGroupIDP);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 1, 0, 1, 1);

        m_pPower = new QLineEdit(m_pGroupIDP);
        m_pPower->setObjectName(QString::fromUtf8("m_pPower"));

        gridLayout_3->addWidget(m_pPower, 0, 3, 1, 1);

        m_pIDPMaximumSampleNumber = new QLineEdit(m_pGroupIDP);
        m_pIDPMaximumSampleNumber->setObjectName(QString::fromUtf8("m_pIDPMaximumSampleNumber"));

        gridLayout_3->addWidget(m_pIDPMaximumSampleNumber, 1, 1, 1, 1);

        label_9->raise();
        label_10->raise();
        label_11->raise();
        m_pSearchRadius->raise();
        m_pPower->raise();
        m_pIDPMaximumSampleNumber->raise();

        gridLayout_2->addWidget(m_pGroupIDP, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_pLabelVariogram = new QLabel(DlgLFMInterpolation);
        m_pLabelVariogram->setObjectName(QString::fromUtf8("m_pLabelVariogram"));

        horizontalLayout_2->addWidget(m_pLabelVariogram);

        m_pCombVariogram = new QComboBox(DlgLFMInterpolation);
        m_pCombVariogram->addItem(QString());
        m_pCombVariogram->addItem(QString());
        m_pCombVariogram->addItem(QString());
        m_pCombVariogram->setObjectName(QString::fromUtf8("m_pCombVariogram"));
        m_pCombVariogram->setMinimumSize(QSize(120, 0));

        horizontalLayout_2->addWidget(m_pCombVariogram);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        m_pGroupKriging = new QGroupBox(DlgLFMInterpolation);
        m_pGroupKriging->setObjectName(QString::fromUtf8("m_pGroupKriging"));
        gridLayout = new QGridLayout(m_pGroupKriging);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(m_pGroupKriging);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        m_pSill = new QLineEdit(m_pGroupKriging);
        m_pSill->setObjectName(QString::fromUtf8("m_pSill"));

        gridLayout->addWidget(m_pSill, 0, 1, 1, 1);

        label_4 = new QLabel(m_pGroupKriging);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        m_pNugget = new QLineEdit(m_pGroupKriging);
        m_pNugget->setObjectName(QString::fromUtf8("m_pNugget"));

        gridLayout->addWidget(m_pNugget, 0, 3, 1, 1);

        label_5 = new QLabel(m_pGroupKriging);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_pMajorRange = new QLineEdit(m_pGroupKriging);
        m_pMajorRange->setObjectName(QString::fromUtf8("m_pMajorRange"));

        gridLayout->addWidget(m_pMajorRange, 1, 1, 1, 1);

        label_7 = new QLabel(m_pGroupKriging);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 2, 1, 1);

        m_pMinorRange = new QLineEdit(m_pGroupKriging);
        m_pMinorRange->setObjectName(QString::fromUtf8("m_pMinorRange"));

        gridLayout->addWidget(m_pMinorRange, 1, 3, 1, 1);

        label_6 = new QLabel(m_pGroupKriging);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        m_pAzimuth = new QLineEdit(m_pGroupKriging);
        m_pAzimuth->setObjectName(QString::fromUtf8("m_pAzimuth"));

        gridLayout->addWidget(m_pAzimuth, 2, 1, 1, 1);

        label_8 = new QLabel(m_pGroupKriging);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 2, 2, 1, 1);

        m_pKMaximumSampleNumber = new QLineEdit(m_pGroupKriging);
        m_pKMaximumSampleNumber->setObjectName(QString::fromUtf8("m_pKMaximumSampleNumber"));

        gridLayout->addWidget(m_pKMaximumSampleNumber, 2, 3, 1, 1);


        gridLayout_2->addWidget(m_pGroupKriging, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DlgLFMInterpolation);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 5, 0, 1, 1);


        retranslateUi(DlgLFMInterpolation);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgLFMInterpolation, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgLFMInterpolation, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgLFMInterpolation);
    } // setupUi

    void retranslateUi(QDialog *DlgLFMInterpolation)
    {
        DlgLFMInterpolation->setWindowTitle(QCoreApplication::translate("DlgLFMInterpolation", "Dialog", nullptr));
        m_labelkriging->setText(QCoreApplication::translate("DlgLFMInterpolation", "Select One Interpolation Method     ", nullptr));
        m_pCombMethod->setItemText(0, QCoreApplication::translate("DlgLFMInterpolation", "Inverse Distance", nullptr));
        m_pCombMethod->setItemText(1, QCoreApplication::translate("DlgLFMInterpolation", "Global Kriging", nullptr));
        m_pCombMethod->setItemText(2, QCoreApplication::translate("DlgLFMInterpolation", "Ordinary Kriging", nullptr));

        m_pGroupIDP->setTitle(QString());
        label_9->setText(QCoreApplication::translate("DlgLFMInterpolation", "Search Radius", nullptr));
        label_11->setText(QCoreApplication::translate("DlgLFMInterpolation", "Power", nullptr));
        label_10->setText(QCoreApplication::translate("DlgLFMInterpolation", "Maximum Sample Number", nullptr));
        m_pLabelVariogram->setText(QCoreApplication::translate("DlgLFMInterpolation", "Variogram Type   ", nullptr));
        m_pCombVariogram->setItemText(0, QCoreApplication::translate("DlgLFMInterpolation", "Exponential", nullptr));
        m_pCombVariogram->setItemText(1, QCoreApplication::translate("DlgLFMInterpolation", "Gaussian", nullptr));
        m_pCombVariogram->setItemText(2, QCoreApplication::translate("DlgLFMInterpolation", "Spherical", nullptr));

        m_pGroupKriging->setTitle(QString());
        label_3->setText(QCoreApplication::translate("DlgLFMInterpolation", "Sill", nullptr));
        label_4->setText(QCoreApplication::translate("DlgLFMInterpolation", "Nugget", nullptr));
        label_5->setText(QCoreApplication::translate("DlgLFMInterpolation", "Major Range", nullptr));
        label_7->setText(QCoreApplication::translate("DlgLFMInterpolation", "Minor Range", nullptr));
        label_6->setText(QCoreApplication::translate("DlgLFMInterpolation", "Azimuth", nullptr));
        label_8->setText(QCoreApplication::translate("DlgLFMInterpolation", "Maximum Sample Number", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgLFMInterpolation: public Ui_DlgLFMInterpolation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGLFINTERPOLATION_H
