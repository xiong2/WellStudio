/********************************************************************************
** Form generated from reading UI file 'xdlgkriginginterpolation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGKRIGINGINTERPOLATION_H
#define UI_XDLGKRIGINGINTERPOLATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXKrigingInterpolationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_labelkriging;
    QComboBox *m_cbKriging;
    QSpacerItem *horizontalSpacer;
    QGroupBox *m_gbIDP;
    QGridLayout *gridLayout_3;
    QLineEdit *m_leSearchRadius;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *m_lePower;
    QLineEdit *m_leIDPMaximumSampleNumber;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_lFunction;
    QComboBox *m_cbbType;
    QSpacerItem *horizontalSpacer_2;
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
    QGroupBox *m_gbTrendFunction;
    QGridLayout *gridLayout_2;
    QLabel *m_labela;
    QLineEdit *m_lineEditAvalue;
    QLabel *m_labelx;
    QLineEdit *m_lineEditxValue;
    QLabel *m_labely;
    QLineEdit *m_lineEditYvalue;
    QLabel *m_labelz;
    QLineEdit *m_lineEditzValue;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CXKrigingInterpolationDialog)
    {
        if (CXKrigingInterpolationDialog->objectName().isEmpty())
            CXKrigingInterpolationDialog->setObjectName(QString::fromUtf8("CXKrigingInterpolationDialog"));
        CXKrigingInterpolationDialog->resize(485, 335);
        verticalLayout = new QVBoxLayout(CXKrigingInterpolationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_labelkriging = new QLabel(CXKrigingInterpolationDialog);
        m_labelkriging->setObjectName(QString::fromUtf8("m_labelkriging"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labelkriging->sizePolicy().hasHeightForWidth());
        m_labelkriging->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_labelkriging);

        m_cbKriging = new QComboBox(CXKrigingInterpolationDialog);
        m_cbKriging->setObjectName(QString::fromUtf8("m_cbKriging"));

        horizontalLayout->addWidget(m_cbKriging);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        m_gbIDP = new QGroupBox(CXKrigingInterpolationDialog);
        m_gbIDP->setObjectName(QString::fromUtf8("m_gbIDP"));
        gridLayout_3 = new QGridLayout(m_gbIDP);
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

        verticalLayout->addWidget(m_gbIDP);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_lFunction = new QLabel(CXKrigingInterpolationDialog);
        m_lFunction->setObjectName(QString::fromUtf8("m_lFunction"));

        horizontalLayout_2->addWidget(m_lFunction);

        m_cbbType = new QComboBox(CXKrigingInterpolationDialog);
        m_cbbType->setObjectName(QString::fromUtf8("m_cbbType"));

        horizontalLayout_2->addWidget(m_cbbType);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        m_gbKriging = new QGroupBox(CXKrigingInterpolationDialog);
        m_gbKriging->setObjectName(QString::fromUtf8("m_gbKriging"));
        gridLayout = new QGridLayout(m_gbKriging);
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


        verticalLayout->addWidget(m_gbKriging);

        m_gbTrendFunction = new QGroupBox(CXKrigingInterpolationDialog);
        m_gbTrendFunction->setObjectName(QString::fromUtf8("m_gbTrendFunction"));
        gridLayout_2 = new QGridLayout(m_gbTrendFunction);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_labela = new QLabel(m_gbTrendFunction);
        m_labela->setObjectName(QString::fromUtf8("m_labela"));

        gridLayout_2->addWidget(m_labela, 0, 0, 1, 1);

        m_lineEditAvalue = new QLineEdit(m_gbTrendFunction);
        m_lineEditAvalue->setObjectName(QString::fromUtf8("m_lineEditAvalue"));

        gridLayout_2->addWidget(m_lineEditAvalue, 0, 1, 1, 1);

        m_labelx = new QLabel(m_gbTrendFunction);
        m_labelx->setObjectName(QString::fromUtf8("m_labelx"));

        gridLayout_2->addWidget(m_labelx, 0, 2, 1, 1);

        m_lineEditxValue = new QLineEdit(m_gbTrendFunction);
        m_lineEditxValue->setObjectName(QString::fromUtf8("m_lineEditxValue"));

        gridLayout_2->addWidget(m_lineEditxValue, 0, 3, 1, 1);

        m_labely = new QLabel(m_gbTrendFunction);
        m_labely->setObjectName(QString::fromUtf8("m_labely"));

        gridLayout_2->addWidget(m_labely, 0, 4, 1, 1);

        m_lineEditYvalue = new QLineEdit(m_gbTrendFunction);
        m_lineEditYvalue->setObjectName(QString::fromUtf8("m_lineEditYvalue"));

        gridLayout_2->addWidget(m_lineEditYvalue, 0, 5, 1, 1);

        m_labelz = new QLabel(m_gbTrendFunction);
        m_labelz->setObjectName(QString::fromUtf8("m_labelz"));

        gridLayout_2->addWidget(m_labelz, 0, 6, 1, 1);

        m_lineEditzValue = new QLineEdit(m_gbTrendFunction);
        m_lineEditzValue->setObjectName(QString::fromUtf8("m_lineEditzValue"));

        gridLayout_2->addWidget(m_lineEditzValue, 0, 7, 1, 1);


        verticalLayout->addWidget(m_gbTrendFunction);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXKrigingInterpolationDialog);

        QMetaObject::connectSlotsByName(CXKrigingInterpolationDialog);
    } // setupUi

    void retranslateUi(QDialog *CXKrigingInterpolationDialog)
    {
        CXKrigingInterpolationDialog->setWindowTitle(QCoreApplication::translate("CXKrigingInterpolationDialog", "Dialog", nullptr));
        m_labelkriging->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Kriging Method", nullptr));
        m_gbIDP->setTitle(QString());
        label_9->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Search Radius", nullptr));
        label_11->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Power", nullptr));
        label_10->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Maximum Sample Number", nullptr));
        m_lFunction->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Variogram", nullptr));
        m_gbKriging->setTitle(QString());
        label_4->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Nugget", nullptr));
        label_8->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Maximum Sample Number", nullptr));
        label_7->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Minor Range", nullptr));
        label_3->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Sill", nullptr));
        label_6->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Azimuth", nullptr));
        label_5->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "Major Range", nullptr));
        m_gbTrendFunction->setTitle(QCoreApplication::translate("CXKrigingInterpolationDialog", "Trend Function", nullptr));
        m_labela->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "a:", nullptr));
        m_labelx->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "x:", nullptr));
        m_labely->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "y:", nullptr));
        m_labelz->setText(QCoreApplication::translate("CXKrigingInterpolationDialog", "z:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXKrigingInterpolationDialog: public Ui_CXKrigingInterpolationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGKRIGINGINTERPOLATION_H
