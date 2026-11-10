/********************************************************************************
** Form generated from reading UI file 'xhistogram.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XHISTOGRAM_H
#define UI_XHISTOGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <xdrawhistogram.h>

QT_BEGIN_NAMESPACE

class Ui_KEPageHistogram
{
public:
    QGridLayout *gridLayout;
    CXDrawHistogram *m_pFrameHistogram;
    QGroupBox *pGbxBin;
    QFormLayout *formLayout;
    QRadioButton *m_pRdoBinSize;
    QComboBox *m_pCbbBinSize;
    QRadioButton *m_pRdoBinNum;
    QComboBox *m_pCbbBinNum;
    QGroupBox *pGbxRange;
    QFormLayout *formLayout_2;
    QLabel *pLblMin;
    QLabel *m_pLblMin;
    QLabel *pLblMax;
    QLabel *m_pLblMax;
    QGroupBox *pGbxAxis;
    QFormLayout *formLayout_3;
    QLabel *lblAxisX;
    QComboBox *m_pCbbAxisX;
    QLabel *lblAxisY;
    QComboBox *m_pCbbAxisY;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *KEPageHistogram)
    {
        if (KEPageHistogram->objectName().isEmpty())
            KEPageHistogram->setObjectName(QString::fromUtf8("KEPageHistogram"));
        KEPageHistogram->resize(400, 113);
        gridLayout = new QGridLayout(KEPageHistogram);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pFrameHistogram = new CXDrawHistogram(KEPageHistogram);
        m_pFrameHistogram->setObjectName(QString::fromUtf8("m_pFrameHistogram"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pFrameHistogram->sizePolicy().hasHeightForWidth());
        m_pFrameHistogram->setSizePolicy(sizePolicy);
        m_pFrameHistogram->setFrameShape(QFrame::StyledPanel);
        m_pFrameHistogram->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(m_pFrameHistogram, 0, 0, 1, 4);

        pGbxBin = new QGroupBox(KEPageHistogram);
        pGbxBin->setObjectName(QString::fromUtf8("pGbxBin"));
        formLayout = new QFormLayout(pGbxBin);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        m_pRdoBinSize = new QRadioButton(pGbxBin);
        m_pRdoBinSize->setObjectName(QString::fromUtf8("m_pRdoBinSize"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pRdoBinSize->sizePolicy().hasHeightForWidth());
        m_pRdoBinSize->setSizePolicy(sizePolicy1);
        m_pRdoBinSize->setChecked(false);

        formLayout->setWidget(0, QFormLayout::LabelRole, m_pRdoBinSize);

        m_pCbbBinSize = new QComboBox(pGbxBin);
        m_pCbbBinSize->setObjectName(QString::fromUtf8("m_pCbbBinSize"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pCbbBinSize->sizePolicy().hasHeightForWidth());
        m_pCbbBinSize->setSizePolicy(sizePolicy2);

        formLayout->setWidget(0, QFormLayout::FieldRole, m_pCbbBinSize);

        m_pRdoBinNum = new QRadioButton(pGbxBin);
        m_pRdoBinNum->setObjectName(QString::fromUtf8("m_pRdoBinNum"));
        sizePolicy1.setHeightForWidth(m_pRdoBinNum->sizePolicy().hasHeightForWidth());
        m_pRdoBinNum->setSizePolicy(sizePolicy1);
        m_pRdoBinNum->setChecked(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, m_pRdoBinNum);

        m_pCbbBinNum = new QComboBox(pGbxBin);
        m_pCbbBinNum->addItem(QString());
        m_pCbbBinNum->addItem(QString());
        m_pCbbBinNum->addItem(QString());
        m_pCbbBinNum->addItem(QString());
        m_pCbbBinNum->addItem(QString());
        m_pCbbBinNum->addItem(QString());
        m_pCbbBinNum->addItem(QString());
        m_pCbbBinNum->addItem(QString());
        m_pCbbBinNum->setObjectName(QString::fromUtf8("m_pCbbBinNum"));
        sizePolicy2.setHeightForWidth(m_pCbbBinNum->sizePolicy().hasHeightForWidth());
        m_pCbbBinNum->setSizePolicy(sizePolicy2);

        formLayout->setWidget(1, QFormLayout::FieldRole, m_pCbbBinNum);


        gridLayout->addWidget(pGbxBin, 1, 0, 1, 1);

        pGbxRange = new QGroupBox(KEPageHistogram);
        pGbxRange->setObjectName(QString::fromUtf8("pGbxRange"));
        formLayout_2 = new QFormLayout(pGbxRange);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        pLblMin = new QLabel(pGbxRange);
        pLblMin->setObjectName(QString::fromUtf8("pLblMin"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, pLblMin);

        m_pLblMin = new QLabel(pGbxRange);
        m_pLblMin->setObjectName(QString::fromUtf8("m_pLblMin"));
        sizePolicy2.setHeightForWidth(m_pLblMin->sizePolicy().hasHeightForWidth());
        m_pLblMin->setSizePolicy(sizePolicy2);
        m_pLblMin->setFrameShape(QFrame::StyledPanel);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, m_pLblMin);

        pLblMax = new QLabel(pGbxRange);
        pLblMax->setObjectName(QString::fromUtf8("pLblMax"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, pLblMax);

        m_pLblMax = new QLabel(pGbxRange);
        m_pLblMax->setObjectName(QString::fromUtf8("m_pLblMax"));
        sizePolicy2.setHeightForWidth(m_pLblMax->sizePolicy().hasHeightForWidth());
        m_pLblMax->setSizePolicy(sizePolicy2);
        m_pLblMax->setFrameShape(QFrame::StyledPanel);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, m_pLblMax);


        gridLayout->addWidget(pGbxRange, 1, 1, 1, 1);

        pGbxAxis = new QGroupBox(KEPageHistogram);
        pGbxAxis->setObjectName(QString::fromUtf8("pGbxAxis"));
        formLayout_3 = new QFormLayout(pGbxAxis);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        lblAxisX = new QLabel(pGbxAxis);
        lblAxisX->setObjectName(QString::fromUtf8("lblAxisX"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lblAxisX->sizePolicy().hasHeightForWidth());
        lblAxisX->setSizePolicy(sizePolicy3);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, lblAxisX);

        m_pCbbAxisX = new QComboBox(pGbxAxis);
        m_pCbbAxisX->addItem(QString());
        m_pCbbAxisX->setObjectName(QString::fromUtf8("m_pCbbAxisX"));
        sizePolicy2.setHeightForWidth(m_pCbbAxisX->sizePolicy().hasHeightForWidth());
        m_pCbbAxisX->setSizePolicy(sizePolicy2);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, m_pCbbAxisX);

        lblAxisY = new QLabel(pGbxAxis);
        lblAxisY->setObjectName(QString::fromUtf8("lblAxisY"));
        sizePolicy3.setHeightForWidth(lblAxisY->sizePolicy().hasHeightForWidth());
        lblAxisY->setSizePolicy(sizePolicy3);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, lblAxisY);

        m_pCbbAxisY = new QComboBox(pGbxAxis);
        m_pCbbAxisY->addItem(QString());
        m_pCbbAxisY->addItem(QString());
        m_pCbbAxisY->setObjectName(QString::fromUtf8("m_pCbbAxisY"));
        sizePolicy2.setHeightForWidth(m_pCbbAxisY->sizePolicy().hasHeightForWidth());
        m_pCbbAxisY->setSizePolicy(sizePolicy2);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, m_pCbbAxisY);


        gridLayout->addWidget(pGbxAxis, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);


        retranslateUi(KEPageHistogram);
        QObject::connect(m_pRdoBinSize, SIGNAL(toggled(bool)), m_pCbbBinSize, SLOT(setEnabled(bool)));
        QObject::connect(m_pRdoBinNum, SIGNAL(toggled(bool)), m_pCbbBinNum, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(KEPageHistogram);
    } // setupUi

    void retranslateUi(QWidget *KEPageHistogram)
    {
        pGbxBin->setTitle(QCoreApplication::translate("KEPageHistogram", "Bin", nullptr));
        m_pRdoBinSize->setText(QCoreApplication::translate("KEPageHistogram", "Size", nullptr));
        m_pRdoBinNum->setText(QCoreApplication::translate("KEPageHistogram", "Number", nullptr));
        m_pCbbBinNum->setItemText(0, QCoreApplication::translate("KEPageHistogram", "256", nullptr));
        m_pCbbBinNum->setItemText(1, QCoreApplication::translate("KEPageHistogram", "128", nullptr));
        m_pCbbBinNum->setItemText(2, QCoreApplication::translate("KEPageHistogram", "64", nullptr));
        m_pCbbBinNum->setItemText(3, QCoreApplication::translate("KEPageHistogram", "32", nullptr));
        m_pCbbBinNum->setItemText(4, QCoreApplication::translate("KEPageHistogram", "16", nullptr));
        m_pCbbBinNum->setItemText(5, QCoreApplication::translate("KEPageHistogram", "8", nullptr));
        m_pCbbBinNum->setItemText(6, QCoreApplication::translate("KEPageHistogram", "4", nullptr));
        m_pCbbBinNum->setItemText(7, QCoreApplication::translate("KEPageHistogram", "2", nullptr));

        pGbxRange->setTitle(QCoreApplication::translate("KEPageHistogram", "Range", nullptr));
        pLblMin->setText(QCoreApplication::translate("KEPageHistogram", "Min", nullptr));
        m_pLblMin->setText(QString());
        pLblMax->setText(QCoreApplication::translate("KEPageHistogram", "Max", nullptr));
        m_pLblMax->setText(QString());
        pGbxAxis->setTitle(QCoreApplication::translate("KEPageHistogram", "Axis", nullptr));
        lblAxisX->setText(QCoreApplication::translate("KEPageHistogram", "X", nullptr));
        m_pCbbAxisX->setItemText(0, QCoreApplication::translate("KEPageHistogram", "Linear", nullptr));

        lblAxisY->setText(QCoreApplication::translate("KEPageHistogram", "Y", nullptr));
        m_pCbbAxisY->setItemText(0, QCoreApplication::translate("KEPageHistogram", "Percentage", nullptr));
        m_pCbbAxisY->setItemText(1, QCoreApplication::translate("KEPageHistogram", "Number", nullptr));

        Q_UNUSED(KEPageHistogram);
    } // retranslateUi

};

namespace Ui {
    class KEPageHistogram: public Ui_KEPageHistogram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XHISTOGRAM_H
