/********************************************************************************
** Form generated from reading UI file 'xdialogproperties.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDIALOGPROPERTIES_H
#define UI_XDIALOGPROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_RLDialogProperties
{
public:
    QGridLayout *gridLayout;
    QTabWidget *m_TabWidget;
    QPushButton *m_pPushBtnApply2All;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *m_pDlgButtonBox;

    void setupUi(QDialog *RLDialogProperties)
    {
        if (RLDialogProperties->objectName().isEmpty())
            RLDialogProperties->setObjectName(QString::fromUtf8("RLDialogProperties"));
        RLDialogProperties->resize(605, 494);
        gridLayout = new QGridLayout(RLDialogProperties);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_TabWidget = new QTabWidget(RLDialogProperties);
        m_TabWidget->setObjectName(QString::fromUtf8("m_TabWidget"));

        gridLayout->addWidget(m_TabWidget, 0, 0, 1, 3);

        m_pPushBtnApply2All = new QPushButton(RLDialogProperties);
        m_pPushBtnApply2All->setObjectName(QString::fromUtf8("m_pPushBtnApply2All"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pPushBtnApply2All->sizePolicy().hasHeightForWidth());
        m_pPushBtnApply2All->setSizePolicy(sizePolicy);
        m_pPushBtnApply2All->setMaximumSize(QSize(40, 16777215));
        m_pPushBtnApply2All->setCheckable(true);

        gridLayout->addWidget(m_pPushBtnApply2All, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(233, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        m_pDlgButtonBox = new QDialogButtonBox(RLDialogProperties);
        m_pDlgButtonBox->setObjectName(QString::fromUtf8("m_pDlgButtonBox"));
        m_pDlgButtonBox->setOrientation(Qt::Horizontal);
        m_pDlgButtonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(m_pDlgButtonBox, 1, 2, 1, 1);


        retranslateUi(RLDialogProperties);
        QObject::connect(m_pDlgButtonBox, SIGNAL(accepted()), RLDialogProperties, SLOT(accept()));
        QObject::connect(m_pDlgButtonBox, SIGNAL(rejected()), RLDialogProperties, SLOT(reject()));

        m_TabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(RLDialogProperties);
    } // setupUi

    void retranslateUi(QDialog *RLDialogProperties)
    {
        RLDialogProperties->setWindowTitle(QCoreApplication::translate("RLDialogProperties", "Dialog", nullptr));
        m_pPushBtnApply2All->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RLDialogProperties: public Ui_RLDialogProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDIALOGPROPERTIES_H
