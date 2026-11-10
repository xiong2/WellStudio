/********************************************************************************
** Form generated from reading UI file 'xpagewellcondition.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEWELLCONDITION_H
#define UI_XPAGEWELLCONDITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXPageWellCondition
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *m_pLabelUnCalcWells;
    QListWidget *m_pListUnCalc;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *m_pBtnCalcSelectAll;
    QPushButton *m_pBtnCalcClear;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *m_pBtnUnCalcSelectAll;
    QPushButton *m_pBtnUnCalcClear;
    QVBoxLayout *verticalLayout_3;
    QLabel *m_pLabelCalcWells;
    QListWidget *m_pListCalc;
    QDialogButtonBox *m_pBtnGroupOkCancel;

    void setupUi(QDialog *CXPageWellCondition)
    {
        if (CXPageWellCondition->objectName().isEmpty())
            CXPageWellCondition->setObjectName(QString::fromUtf8("CXPageWellCondition"));
        CXPageWellCondition->resize(800, 600);
        gridLayout = new QGridLayout(CXPageWellCondition);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        m_pLabelUnCalcWells = new QLabel(CXPageWellCondition);
        m_pLabelUnCalcWells->setObjectName(QString::fromUtf8("m_pLabelUnCalcWells"));

        verticalLayout_4->addWidget(m_pLabelUnCalcWells);

        m_pListUnCalc = new QListWidget(CXPageWellCondition);
        m_pListUnCalc->setObjectName(QString::fromUtf8("m_pListUnCalc"));

        verticalLayout_4->addWidget(m_pListUnCalc);


        gridLayout->addLayout(verticalLayout_4, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        m_pBtnCalcSelectAll = new QPushButton(CXPageWellCondition);
        m_pBtnCalcSelectAll->setObjectName(QString::fromUtf8("m_pBtnCalcSelectAll"));

        verticalLayout->addWidget(m_pBtnCalcSelectAll);

        m_pBtnCalcClear = new QPushButton(CXPageWellCondition);
        m_pBtnCalcClear->setObjectName(QString::fromUtf8("m_pBtnCalcClear"));

        verticalLayout->addWidget(m_pBtnCalcClear);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 2, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        m_pBtnUnCalcSelectAll = new QPushButton(CXPageWellCondition);
        m_pBtnUnCalcSelectAll->setObjectName(QString::fromUtf8("m_pBtnUnCalcSelectAll"));

        verticalLayout_2->addWidget(m_pBtnUnCalcSelectAll);

        m_pBtnUnCalcClear = new QPushButton(CXPageWellCondition);
        m_pBtnUnCalcClear->setObjectName(QString::fromUtf8("m_pBtnUnCalcClear"));

        verticalLayout_2->addWidget(m_pBtnUnCalcClear);


        gridLayout->addLayout(verticalLayout_2, 1, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        m_pLabelCalcWells = new QLabel(CXPageWellCondition);
        m_pLabelCalcWells->setObjectName(QString::fromUtf8("m_pLabelCalcWells"));

        verticalLayout_3->addWidget(m_pLabelCalcWells);

        m_pListCalc = new QListWidget(CXPageWellCondition);
        m_pListCalc->setObjectName(QString::fromUtf8("m_pListCalc"));

        verticalLayout_3->addWidget(m_pListCalc);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        m_pBtnGroupOkCancel = new QDialogButtonBox(CXPageWellCondition);
        m_pBtnGroupOkCancel->setObjectName(QString::fromUtf8("m_pBtnGroupOkCancel"));
        m_pBtnGroupOkCancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(m_pBtnGroupOkCancel, 4, 0, 1, 2);


        retranslateUi(CXPageWellCondition);

        QMetaObject::connectSlotsByName(CXPageWellCondition);
    } // setupUi

    void retranslateUi(QDialog *CXPageWellCondition)
    {
        CXPageWellCondition->setWindowTitle(QCoreApplication::translate("CXPageWellCondition", "Select Wells", nullptr));
        m_pLabelUnCalcWells->setText(QCoreApplication::translate("CXPageWellCondition", "Wells (not calculated yet)", nullptr));
        m_pBtnCalcSelectAll->setText(QString());
        m_pBtnCalcClear->setText(QString());
        m_pBtnUnCalcSelectAll->setText(QString());
        m_pBtnUnCalcClear->setText(QString());
        m_pLabelCalcWells->setText(QCoreApplication::translate("CXPageWellCondition", "Wells (already calculated)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageWellCondition: public Ui_CXPageWellCondition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEWELLCONDITION_H
