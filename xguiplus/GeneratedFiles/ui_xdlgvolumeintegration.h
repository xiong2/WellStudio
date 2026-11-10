/********************************************************************************
** Form generated from reading UI file 'xdlgvolumeintegration.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGVOLUMEINTEGRATION_H
#define UI_XDLGVOLUMEINTEGRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_XDlgVolumeIntegration
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    CXSliderComplex *m_pXlineWidget;
    CXSliderComplex *m_pInlineWidget;
    QLabel *label;
    QLineEdit *lineEdit;
    QSlider *horizontalSlider;
    QRadioButton *radioButtonHorizon;
    QComboBox *comboBox;
    QRadioButton *radioButtonDepth;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLineEdit *lineEditDV;

    void setupUi(QDialog *XDlgVolumeIntegration)
    {
        if (XDlgVolumeIntegration->objectName().isEmpty())
            XDlgVolumeIntegration->setObjectName(QString::fromUtf8("XDlgVolumeIntegration"));
        XDlgVolumeIntegration->resize(655, 261);
        gridLayout_2 = new QGridLayout(XDlgVolumeIntegration);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(XDlgVolumeIntegration);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pXlineWidget = new CXSliderComplex(groupBox);
        m_pXlineWidget->setObjectName(QString::fromUtf8("m_pXlineWidget"));
        m_pXlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pXlineWidget, 1, 0, 1, 6);

        m_pInlineWidget = new CXSliderComplex(groupBox);
        m_pInlineWidget->setObjectName(QString::fromUtf8("m_pInlineWidget"));
        m_pInlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pInlineWidget, 0, 0, 1, 6);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(lineEdit, 2, 4, 1, 1);

        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 2, 5, 1, 1);

        radioButtonHorizon = new QRadioButton(groupBox);
        radioButtonHorizon->setObjectName(QString::fromUtf8("radioButtonHorizon"));

        gridLayout->addWidget(radioButtonHorizon, 2, 1, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEnabled(false);
        comboBox->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(comboBox, 2, 2, 1, 1);

        radioButtonDepth = new QRadioButton(groupBox);
        radioButtonDepth->setObjectName(QString::fromUtf8("radioButtonDepth"));
        radioButtonDepth->setChecked(true);

        gridLayout->addWidget(radioButtonDepth, 2, 3, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 3);

        buttonBox = new QDialogButtonBox(XDlgVolumeIntegration);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 3, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 67, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        label_2 = new QLabel(XDlgVolumeIntegration);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEditDV = new QLineEdit(XDlgVolumeIntegration);
        lineEditDV->setObjectName(QString::fromUtf8("lineEditDV"));

        gridLayout_2->addWidget(lineEditDV, 0, 1, 1, 1);


        retranslateUi(XDlgVolumeIntegration);
        QObject::connect(buttonBox, SIGNAL(rejected()), XDlgVolumeIntegration, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), XDlgVolumeIntegration, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgVolumeIntegration);
    } // setupUi

    void retranslateUi(QDialog *XDlgVolumeIntegration)
    {
        XDlgVolumeIntegration->setWindowTitle(QCoreApplication::translate("XDlgVolumeIntegration", "XDlgVolumeIntegration", nullptr));
        groupBox->setTitle(QCoreApplication::translate("XDlgVolumeIntegration", "Output Range", nullptr));
        label->setText(QCoreApplication::translate("XDlgVolumeIntegration", "Bottom:", nullptr));
        radioButtonHorizon->setText(QCoreApplication::translate("XDlgVolumeIntegration", "By Horizon", nullptr));
        radioButtonDepth->setText(QCoreApplication::translate("XDlgVolumeIntegration", "By Depth", nullptr));
        label_2->setText(QCoreApplication::translate("XDlgVolumeIntegration", "Output volume:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgVolumeIntegration: public Ui_XDlgVolumeIntegration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGVOLUMEINTEGRATION_H
