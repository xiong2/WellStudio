/********************************************************************************
** Form generated from reading UI file 'xpageseismicforwardingone.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESEISMICFORWARDINGONE_H
#define UI_XPAGESEISMICFORWARDINGONE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageSeismicForwardingOne
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QToolButton *m_pBtnSelectVp;
    QLineEdit *m_pLineEdtVp;
    QLabel *label_2;
    QToolButton *m_pBtnSelectVs;
    QLineEdit *m_pLineEdtVs;
    QLabel *label_3;
    QToolButton *m_pBtnSelectRho;
    QLineEdit *m_pLineEdtRho;
    QLabel *label_4;
    QToolButton *m_pBtnSelectEpsilon;
    QLineEdit *m_pLineEdtEpsilon;
    QLabel *label_6;
    QToolButton *m_pBtnSelectDelta;
    QLineEdit *m_pLineEdtDelta;
    QLabel *label_5;
    QToolButton *m_pBtnSelectGamma;
    QLineEdit *m_pLineEdtGamma;
    QLabel *label_7;
    QToolButton *m_pBtnSelectAzimuth;
    QLineEdit *m_pLineEdtAzimuth;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *m_pLineEdtEnterAzi;
    QLabel *label_9;
    QLabel *label_8;
    QLineEdit *m_pLineEdtEnterIncidence;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pPushBtnLoadPara;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PageSeismicForwardingOne)
    {
        if (PageSeismicForwardingOne->objectName().isEmpty())
            PageSeismicForwardingOne->setObjectName(QString::fromUtf8("PageSeismicForwardingOne"));
        PageSeismicForwardingOne->resize(791, 435);
        gridLayout_3 = new QGridLayout(PageSeismicForwardingOne);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(PageSeismicForwardingOne);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_pBtnSelectVp = new QToolButton(groupBox);
        m_pBtnSelectVp->setObjectName(QString::fromUtf8("m_pBtnSelectVp"));
        m_pBtnSelectVp->setMinimumSize(QSize(30, 0));
        m_pBtnSelectVp->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnSelectVp->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectVp, 0, 1, 1, 1);

        m_pLineEdtVp = new QLineEdit(groupBox);
        m_pLineEdtVp->setObjectName(QString::fromUtf8("m_pLineEdtVp"));
        m_pLineEdtVp->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtVp, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        m_pBtnSelectVs = new QToolButton(groupBox);
        m_pBtnSelectVs->setObjectName(QString::fromUtf8("m_pBtnSelectVs"));
        m_pBtnSelectVs->setMinimumSize(QSize(30, 0));
        m_pBtnSelectVs->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectVs->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectVs, 1, 1, 1, 1);

        m_pLineEdtVs = new QLineEdit(groupBox);
        m_pLineEdtVs->setObjectName(QString::fromUtf8("m_pLineEdtVs"));
        m_pLineEdtVs->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtVs, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_pBtnSelectRho = new QToolButton(groupBox);
        m_pBtnSelectRho->setObjectName(QString::fromUtf8("m_pBtnSelectRho"));
        m_pBtnSelectRho->setMinimumSize(QSize(30, 0));
        m_pBtnSelectRho->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectRho->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectRho, 2, 1, 1, 1);

        m_pLineEdtRho = new QLineEdit(groupBox);
        m_pLineEdtRho->setObjectName(QString::fromUtf8("m_pLineEdtRho"));
        m_pLineEdtRho->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtRho, 2, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        m_pBtnSelectEpsilon = new QToolButton(groupBox);
        m_pBtnSelectEpsilon->setObjectName(QString::fromUtf8("m_pBtnSelectEpsilon"));
        m_pBtnSelectEpsilon->setMinimumSize(QSize(30, 0));
        m_pBtnSelectEpsilon->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectEpsilon->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectEpsilon, 3, 1, 1, 1);

        m_pLineEdtEpsilon = new QLineEdit(groupBox);
        m_pLineEdtEpsilon->setObjectName(QString::fromUtf8("m_pLineEdtEpsilon"));
        m_pLineEdtEpsilon->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtEpsilon, 3, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        m_pBtnSelectDelta = new QToolButton(groupBox);
        m_pBtnSelectDelta->setObjectName(QString::fromUtf8("m_pBtnSelectDelta"));
        m_pBtnSelectDelta->setMinimumSize(QSize(30, 0));
        m_pBtnSelectDelta->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectDelta->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectDelta, 4, 1, 1, 1);

        m_pLineEdtDelta = new QLineEdit(groupBox);
        m_pLineEdtDelta->setObjectName(QString::fromUtf8("m_pLineEdtDelta"));
        m_pLineEdtDelta->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtDelta, 4, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        m_pBtnSelectGamma = new QToolButton(groupBox);
        m_pBtnSelectGamma->setObjectName(QString::fromUtf8("m_pBtnSelectGamma"));
        m_pBtnSelectGamma->setMinimumSize(QSize(30, 0));
        m_pBtnSelectGamma->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectGamma->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectGamma, 5, 1, 1, 1);

        m_pLineEdtGamma = new QLineEdit(groupBox);
        m_pLineEdtGamma->setObjectName(QString::fromUtf8("m_pLineEdtGamma"));
        m_pLineEdtGamma->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtGamma, 5, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        m_pBtnSelectAzimuth = new QToolButton(groupBox);
        m_pBtnSelectAzimuth->setObjectName(QString::fromUtf8("m_pBtnSelectAzimuth"));
        m_pBtnSelectAzimuth->setMinimumSize(QSize(30, 0));
        m_pBtnSelectAzimuth->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectAzimuth->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectAzimuth, 6, 1, 1, 1);

        m_pLineEdtAzimuth = new QLineEdit(groupBox);
        m_pLineEdtAzimuth->setObjectName(QString::fromUtf8("m_pLineEdtAzimuth"));
        m_pLineEdtAzimuth->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtAzimuth, 6, 2, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 2);

        groupBox_2 = new QGroupBox(PageSeismicForwardingOne);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 100));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pLineEdtEnterAzi = new QLineEdit(groupBox_2);
        m_pLineEdtEnterAzi->setObjectName(QString::fromUtf8("m_pLineEdtEnterAzi"));

        gridLayout_2->addWidget(m_pLineEdtEnterAzi, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        m_pLineEdtEnterIncidence = new QLineEdit(groupBox_2);
        m_pLineEdtEnterIncidence->setObjectName(QString::fromUtf8("m_pLineEdtEnterIncidence"));

        gridLayout_2->addWidget(m_pLineEdtEnterIncidence, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(664, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 2, 0, 1, 1);

        m_pPushBtnLoadPara = new QPushButton(PageSeismicForwardingOne);
        m_pPushBtnLoadPara->setObjectName(QString::fromUtf8("m_pPushBtnLoadPara"));
        m_pPushBtnLoadPara->setMinimumSize(QSize(100, 0));

        gridLayout_3->addWidget(m_pPushBtnLoadPara, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 47, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 0, 1, 1);


        retranslateUi(PageSeismicForwardingOne);

        QMetaObject::connectSlotsByName(PageSeismicForwardingOne);
    } // setupUi

    void retranslateUi(QWidget *PageSeismicForwardingOne)
    {
        PageSeismicForwardingOne->setWindowTitle(QCoreApplication::translate("PageSeismicForwardingOne", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageSeismicForwardingOne", "Select Seismic Data Volumes", nullptr));
        label->setText(QCoreApplication::translate("PageSeismicForwardingOne", "Select P-wave Velocity", nullptr));
        m_pBtnSelectVp->setText(QCoreApplication::translate("PageSeismicForwardingOne", "...", nullptr));
        label_2->setText(QCoreApplication::translate("PageSeismicForwardingOne", "Select S-wave Velocity", nullptr));
        m_pBtnSelectVs->setText(QCoreApplication::translate("PageSeismicForwardingOne", "...", nullptr));
        label_3->setText(QCoreApplication::translate("PageSeismicForwardingOne", "<html><head/><body><p>Select <span style=\" font-family:'Calibri,sans-serif'; font-size:11pt;\">\317\201</span></p></body></html>", nullptr));
        m_pBtnSelectRho->setText(QCoreApplication::translate("PageSeismicForwardingOne", "...", nullptr));
        label_4->setText(QCoreApplication::translate("PageSeismicForwardingOne", "<html><head/><body><p>Select <span style=\" font-size:11pt;\">\311\233</span> Thomsen parameter</p></body></html>", nullptr));
        m_pBtnSelectEpsilon->setText(QCoreApplication::translate("PageSeismicForwardingOne", "...", nullptr));
        label_6->setText(QCoreApplication::translate("PageSeismicForwardingOne", "<html><head/><body><p>Select <span style=\" font-size:10pt;\">\316\264</span> Thomsen parameter</p></body></html>", nullptr));
        m_pBtnSelectDelta->setText(QCoreApplication::translate("PageSeismicForwardingOne", "...", nullptr));
        label_5->setText(QCoreApplication::translate("PageSeismicForwardingOne", "<html><head/><body><p>Select <span style=\" font-size:10pt;\">\316\263</span> Thomsen parameter</p></body></html>", nullptr));
        m_pBtnSelectGamma->setText(QCoreApplication::translate("PageSeismicForwardingOne", "...", nullptr));
        label_7->setText(QCoreApplication::translate("PageSeismicForwardingOne", "<html><head/><body><p>Select Azimuth of Symmetry Axis </p></body></html>", nullptr));
        m_pBtnSelectAzimuth->setText(QCoreApplication::translate("PageSeismicForwardingOne", "...", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PageSeismicForwardingOne", "Azimuth, Incidence Angles and Wavelet", nullptr));
        m_pLineEdtEnterAzi->setText(QCoreApplication::translate("PageSeismicForwardingOne", "0, 20, 40, 60, 80, 100, 120, 140, 160", nullptr));
        label_9->setText(QCoreApplication::translate("PageSeismicForwardingOne", "Enter Incidence Angles (deg)", nullptr));
        label_8->setText(QCoreApplication::translate("PageSeismicForwardingOne", "Enter Azimuth Angles (deg)", nullptr));
        m_pLineEdtEnterIncidence->setText(QCoreApplication::translate("PageSeismicForwardingOne", "0, 5, 10, 20, 30, 40", nullptr));
#if QT_CONFIG(tooltip)
        m_pPushBtnLoadPara->setToolTip(QCoreApplication::translate("PageSeismicForwardingOne", "Please select an item on the tree to copy its parameter here.", nullptr));
#endif // QT_CONFIG(tooltip)
        m_pPushBtnLoadPara->setText(QCoreApplication::translate("PageSeismicForwardingOne", "Load Parameter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageSeismicForwardingOne: public Ui_PageSeismicForwardingOne {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESEISMICFORWARDINGONE_H
