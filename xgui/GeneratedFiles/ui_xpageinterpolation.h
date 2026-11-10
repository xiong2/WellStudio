/********************************************************************************
** Form generated from reading UI file 'xpageinterpolation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEINTERPOLATION_H
#define UI_XPAGEINTERPOLATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_CXPageInterpolation
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *m_gbKriging;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_8;
    QLineEdit *m_leSill;
    QLineEdit *m_leKMaximumSampleNumber;
    QLabel *label_7;
    QLineEdit *m_leMinorRange;
    QLabel *label_3;
    QLabel *label_6;
    QLineEdit *m_leNugget;
    QLineEdit *m_leMajorRange;
    QLabel *label_5;
    QLineEdit *m_leAzimuth;
    QLabel *label;
    QComboBox *m_cbbMethod;
    QLabel *m_lFunction;
    QComboBox *m_cbbType;
    QGroupBox *m_gbIDP;
    QGridLayout *gridLayout_3;
    QLineEdit *m_leSearchRadius;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *m_lePower;
    QLineEdit *m_leIDPMaximumSampleNumber;

    void setupUi(QWizardPage *CXPageInterpolation)
    {
        if (CXPageInterpolation->objectName().isEmpty())
            CXPageInterpolation->setObjectName(QString::fromUtf8("CXPageInterpolation"));
        CXPageInterpolation->resize(514, 234);
        gridLayout_2 = new QGridLayout(CXPageInterpolation);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_gbKriging = new QGroupBox(CXPageInterpolation);
        m_gbKriging->setObjectName(QString::fromUtf8("m_gbKriging"));
        gridLayout = new QGridLayout(m_gbKriging);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(m_gbKriging);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        label_8 = new QLabel(m_gbKriging);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 2, 2, 1, 1);

        m_leSill = new QLineEdit(m_gbKriging);
        m_leSill->setObjectName(QString::fromUtf8("m_leSill"));

        gridLayout->addWidget(m_leSill, 0, 1, 1, 1);

        m_leKMaximumSampleNumber = new QLineEdit(m_gbKriging);
        m_leKMaximumSampleNumber->setObjectName(QString::fromUtf8("m_leKMaximumSampleNumber"));

        gridLayout->addWidget(m_leKMaximumSampleNumber, 2, 3, 1, 1);

        label_7 = new QLabel(m_gbKriging);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 2, 1, 1);

        m_leMinorRange = new QLineEdit(m_gbKriging);
        m_leMinorRange->setObjectName(QString::fromUtf8("m_leMinorRange"));

        gridLayout->addWidget(m_leMinorRange, 1, 3, 1, 1);

        label_3 = new QLabel(m_gbKriging);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_6 = new QLabel(m_gbKriging);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        m_leNugget = new QLineEdit(m_gbKriging);
        m_leNugget->setObjectName(QString::fromUtf8("m_leNugget"));

        gridLayout->addWidget(m_leNugget, 0, 3, 1, 1);

        m_leMajorRange = new QLineEdit(m_gbKriging);
        m_leMajorRange->setObjectName(QString::fromUtf8("m_leMajorRange"));

        gridLayout->addWidget(m_leMajorRange, 1, 1, 1, 1);

        label_5 = new QLabel(m_gbKriging);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_leAzimuth = new QLineEdit(m_gbKriging);
        m_leAzimuth->setObjectName(QString::fromUtf8("m_leAzimuth"));

        gridLayout->addWidget(m_leAzimuth, 2, 1, 1, 1);


        gridLayout_2->addWidget(m_gbKriging, 6, 0, 1, 3);

        label = new QLabel(CXPageInterpolation);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        m_cbbMethod = new QComboBox(CXPageInterpolation);
        m_cbbMethod->setObjectName(QString::fromUtf8("m_cbbMethod"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_cbbMethod->sizePolicy().hasHeightForWidth());
        m_cbbMethod->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(m_cbbMethod, 0, 2, 1, 1);

        m_lFunction = new QLabel(CXPageInterpolation);
        m_lFunction->setObjectName(QString::fromUtf8("m_lFunction"));

        gridLayout_2->addWidget(m_lFunction, 5, 0, 1, 1);

        m_cbbType = new QComboBox(CXPageInterpolation);
        m_cbbType->setObjectName(QString::fromUtf8("m_cbbType"));

        gridLayout_2->addWidget(m_cbbType, 5, 1, 1, 1);

        m_gbIDP = new QGroupBox(CXPageInterpolation);
        m_gbIDP->setObjectName(QString::fromUtf8("m_gbIDP"));
        gridLayout_3 = new QGridLayout(m_gbIDP);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_leSearchRadius = new QLineEdit(m_gbIDP);
        m_leSearchRadius->setObjectName(QString::fromUtf8("m_leSearchRadius"));

        gridLayout_3->addWidget(m_leSearchRadius, 0, 1, 1, 1);

        label_9 = new QLabel(m_gbIDP);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1);

        label_11 = new QLabel(m_gbIDP);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 0, 2, 1, 1);

        label_10 = new QLabel(m_gbIDP);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 1, 0, 1, 1);

        m_lePower = new QLineEdit(m_gbIDP);
        m_lePower->setObjectName(QString::fromUtf8("m_lePower"));

        gridLayout_3->addWidget(m_lePower, 0, 3, 1, 1);

        m_leIDPMaximumSampleNumber = new QLineEdit(m_gbIDP);
        m_leIDPMaximumSampleNumber->setObjectName(QString::fromUtf8("m_leIDPMaximumSampleNumber"));

        gridLayout_3->addWidget(m_leIDPMaximumSampleNumber, 1, 1, 1, 1);

        label_9->raise();
        label_10->raise();
        label_11->raise();
        m_leSearchRadius->raise();
        m_lePower->raise();
        m_leIDPMaximumSampleNumber->raise();

        gridLayout_2->addWidget(m_gbIDP, 3, 0, 2, 3);


        retranslateUi(CXPageInterpolation);

        QMetaObject::connectSlotsByName(CXPageInterpolation);
    } // setupUi

    void retranslateUi(QWizardPage *CXPageInterpolation)
    {
        CXPageInterpolation->setWindowTitle(QCoreApplication::translate("CXPageInterpolation", "CXPageInterpolation", nullptr));
        m_gbKriging->setTitle(QString());
        label_4->setText(QCoreApplication::translate("CXPageInterpolation", "Nugget", nullptr));
        label_8->setText(QCoreApplication::translate("CXPageInterpolation", "Maximum Sample Number", nullptr));
        label_7->setText(QCoreApplication::translate("CXPageInterpolation", "Minor Range", nullptr));
        label_3->setText(QCoreApplication::translate("CXPageInterpolation", "Sill", nullptr));
        label_6->setText(QCoreApplication::translate("CXPageInterpolation", "Azimuth", nullptr));
        label_5->setText(QCoreApplication::translate("CXPageInterpolation", "Major Range", nullptr));
        label->setText(QCoreApplication::translate("CXPageInterpolation", "Select an interpolation:", nullptr));
        m_lFunction->setText(QCoreApplication::translate("CXPageInterpolation", "Variogram function:", nullptr));
        m_gbIDP->setTitle(QString());
        label_9->setText(QCoreApplication::translate("CXPageInterpolation", "Search Radius", nullptr));
        label_11->setText(QCoreApplication::translate("CXPageInterpolation", "Power", nullptr));
        label_10->setText(QCoreApplication::translate("CXPageInterpolation", "Maximum Sample Number", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageInterpolation: public Ui_CXPageInterpolation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEINTERPOLATION_H
