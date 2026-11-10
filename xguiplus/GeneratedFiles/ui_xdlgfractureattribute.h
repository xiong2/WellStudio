/********************************************************************************
** Form generated from reading UI file 'xdlgfractureattribute.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGFRACTUREATTRIBUTE_H
#define UI_XDLGFRACTUREATTRIBUTE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
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
#include <QtWidgets/QToolButton>
#include <xslidercomplex.h>

QT_BEGIN_NAMESPACE

class Ui_DlgFractureAttribute
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    CXSliderComplex *m_pInlineWidget;
    CXSliderComplex *m_pXlineWidget;
    CXSliderComplex *m_pTimeWidget;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *m_pCmbCPUNumber;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QToolButton *m_pBtnSelectDV;
    QLineEdit *m_pLineEdtDV;
    QLabel *label_10;
    QLineEdit *m_pLineEdtMinimumFold;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DlgFractureAttribute)
    {
        if (DlgFractureAttribute->objectName().isEmpty())
            DlgFractureAttribute->setObjectName(QString::fromUtf8("DlgFractureAttribute"));
        DlgFractureAttribute->resize(717, 373);
        gridLayout_4 = new QGridLayout(DlgFractureAttribute);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(DlgFractureAttribute);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 170));
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

        m_pTimeWidget = new CXSliderComplex(groupBox);
        m_pTimeWidget->setObjectName(QString::fromUtf8("m_pTimeWidget"));
        m_pTimeWidget->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(m_pTimeWidget, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 2, 0, 1, 5);

        buttonBox = new QDialogButtonBox(DlgFractureAttribute);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_4->addWidget(buttonBox, 5, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(252, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 3, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 9, -1, 9);
        label = new QLabel(DlgFractureAttribute);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_pCmbCPUNumber = new QComboBox(DlgFractureAttribute);
        m_pCmbCPUNumber->setObjectName(QString::fromUtf8("m_pCmbCPUNumber"));
        m_pCmbCPUNumber->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_pCmbCPUNumber);


        gridLayout_4->addLayout(horizontalLayout, 3, 3, 1, 2);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 4, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_9 = new QLabel(DlgFractureAttribute);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_2->addWidget(label_9);

        m_pBtnSelectDV = new QToolButton(DlgFractureAttribute);
        m_pBtnSelectDV->setObjectName(QString::fromUtf8("m_pBtnSelectDV"));
        m_pBtnSelectDV->setMinimumSize(QSize(30, 0));
        m_pBtnSelectDV->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnSelectDV->setIcon(icon);

        horizontalLayout_2->addWidget(m_pBtnSelectDV);

        m_pLineEdtDV = new QLineEdit(DlgFractureAttribute);
        m_pLineEdtDV->setObjectName(QString::fromUtf8("m_pLineEdtDV"));
        m_pLineEdtDV->setReadOnly(true);

        horizontalLayout_2->addWidget(m_pLineEdtDV);


        gridLayout_4->addLayout(horizontalLayout_2, 0, 0, 1, 5);

        label_10 = new QLabel(DlgFractureAttribute);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 1, 0, 1, 1);

        m_pLineEdtMinimumFold = new QLineEdit(DlgFractureAttribute);
        m_pLineEdtMinimumFold->setObjectName(QString::fromUtf8("m_pLineEdtMinimumFold"));
        m_pLineEdtMinimumFold->setMinimumSize(QSize(100, 0));
        m_pLineEdtMinimumFold->setMaximumSize(QSize(80, 16777215));

        gridLayout_4->addWidget(m_pLineEdtMinimumFold, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(412, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 1, 2, 1, 2);

        label_10->raise();
        m_pLineEdtMinimumFold->raise();
        groupBox->raise();
        buttonBox->raise();

        retranslateUi(DlgFractureAttribute);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgFractureAttribute, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgFractureAttribute, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgFractureAttribute);
    } // setupUi

    void retranslateUi(QDialog *DlgFractureAttribute)
    {
        DlgFractureAttribute->setWindowTitle(QCoreApplication::translate("DlgFractureAttribute", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgFractureAttribute", "Output Range", nullptr));
        label->setText(QCoreApplication::translate("DlgFractureAttribute", "CPU Number for Computation", nullptr));
        label_9->setText(QCoreApplication::translate("DlgFractureAttribute", "Select Azimuthal VpVs Data Volume", nullptr));
        m_pBtnSelectDV->setText(QCoreApplication::translate("DlgFractureAttribute", "...", nullptr));
        label_10->setText(QCoreApplication::translate("DlgFractureAttribute", "Minimum fold", nullptr));
        m_pLineEdtMinimumFold->setText(QCoreApplication::translate("DlgFractureAttribute", "4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgFractureAttribute: public Ui_DlgFractureAttribute {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGFRACTUREATTRIBUTE_H
