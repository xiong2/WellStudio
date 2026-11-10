/********************************************************************************
** Form generated from reading UI file 'xdlgpcalfiltering.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGPCALFILTERING_H
#define UI_XDLGPCALFILTERING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_DlgPCAFiltering
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    CXSliderComplex *m_pInlineWidget;
    CXSliderComplex *m_pXlineWidget;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QComboBox *m_pComboxDx;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *m_pComboxDy;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgPCAFiltering)
    {
        if (DlgPCAFiltering->objectName().isEmpty())
            DlgPCAFiltering->setObjectName(QString::fromUtf8("DlgPCAFiltering"));
        DlgPCAFiltering->resize(659, 285);
        gridLayout_3 = new QGridLayout(DlgPCAFiltering);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(DlgPCAFiltering);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 100));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pInlineWidget = new CXSliderComplex(groupBox);
        m_pInlineWidget->setObjectName(QString::fromUtf8("m_pInlineWidget"));
        m_pInlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pInlineWidget, 0, 0, 1, 1);

        m_pXlineWidget = new CXSliderComplex(groupBox);
        m_pXlineWidget->setObjectName(QString::fromUtf8("m_pXlineWidget"));
        m_pXlineWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pXlineWidget, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(DlgPCAFiltering);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        m_pComboxDx = new QComboBox(groupBox_2);
        m_pComboxDx->setObjectName(QString::fromUtf8("m_pComboxDx"));
        m_pComboxDx->setMinimumSize(QSize(90, 0));
        m_pComboxDx->setMaximumSize(QSize(90, 16777215));

        gridLayout_2->addWidget(m_pComboxDx, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(291, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 4, 1, 1);

        m_pComboxDy = new QComboBox(groupBox_2);
        m_pComboxDy->setObjectName(QString::fromUtf8("m_pComboxDy"));
        m_pComboxDy->setMinimumSize(QSize(90, 0));
        m_pComboxDy->setMaximumSize(QSize(90, 16777215));

        gridLayout_2->addWidget(m_pComboxDy, 0, 5, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 6, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(17, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DlgPCAFiltering);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 3, 0, 1, 1);


        retranslateUi(DlgPCAFiltering);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgPCAFiltering, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgPCAFiltering, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgPCAFiltering);
    } // setupUi

    void retranslateUi(QDialog *DlgPCAFiltering)
    {
        DlgPCAFiltering->setWindowTitle(QCoreApplication::translate("DlgPCAFiltering", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgPCAFiltering", "Output Range", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DlgPCAFiltering", "Filtering Parameters", nullptr));
        label->setText(QCoreApplication::translate("DlgPCAFiltering", "dx", nullptr));
        label_4->setText(QCoreApplication::translate("DlgPCAFiltering", "Traces", nullptr));
        label_2->setText(QCoreApplication::translate("DlgPCAFiltering", "dy", nullptr));
        label_3->setText(QCoreApplication::translate("DlgPCAFiltering", "Lines", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgPCAFiltering: public Ui_DlgPCAFiltering {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGPCALFILTERING_H
