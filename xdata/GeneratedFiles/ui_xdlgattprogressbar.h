/********************************************************************************
** Form generated from reading UI file 'xdlgattprogressbar.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGATTPROGRESSBAR_H
#define UI_XDLGATTPROGRESSBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXDlgAttProgressBar
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QSpacerItem *spacerItem;
    QLabel *m_pLabelName;
    QSpacerItem *spacerItem1;
    QProgressBar *m_pProgressBar;
    QHBoxLayout *hboxLayout;
    QLabel *p_mLabelTime;
    QLabel *m_pLabelElapsedTime;
    QSpacerItem *spacerItem2;
    QPushButton *m_pBtnCancel;

    void setupUi(QDialog *CXDlgAttProgressBar)
    {
        if (CXDlgAttProgressBar->objectName().isEmpty())
            CXDlgAttProgressBar->setObjectName(QString::fromUtf8("CXDlgAttProgressBar"));
        CXDlgAttProgressBar->resize(443, 121);
        gridLayout = new QGridLayout(CXDlgAttProgressBar);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        spacerItem = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);

        m_pLabelName = new QLabel(CXDlgAttProgressBar);
        m_pLabelName->setObjectName(QString::fromUtf8("m_pLabelName"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pLabelName->sizePolicy().hasHeightForWidth());
        m_pLabelName->setSizePolicy(sizePolicy);
        m_pLabelName->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(9);
        m_pLabelName->setFont(font);
        m_pLabelName->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(m_pLabelName);

        spacerItem1 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem1);


        vboxLayout->addLayout(vboxLayout1);

        m_pProgressBar = new QProgressBar(CXDlgAttProgressBar);
        m_pProgressBar->setObjectName(QString::fromUtf8("m_pProgressBar"));
        m_pProgressBar->setValue(24);
        m_pProgressBar->setAlignment(Qt::AlignHCenter);
        m_pProgressBar->setTextVisible(true);

        vboxLayout->addWidget(m_pProgressBar);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        p_mLabelTime = new QLabel(CXDlgAttProgressBar);
        p_mLabelTime->setObjectName(QString::fromUtf8("p_mLabelTime"));
        p_mLabelTime->setMinimumSize(QSize(120, 0));

        hboxLayout->addWidget(p_mLabelTime);

        m_pLabelElapsedTime = new QLabel(CXDlgAttProgressBar);
        m_pLabelElapsedTime->setObjectName(QString::fromUtf8("m_pLabelElapsedTime"));
        m_pLabelElapsedTime->setMinimumSize(QSize(100, 0));

        hboxLayout->addWidget(m_pLabelElapsedTime);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem2);

        m_pBtnCancel = new QPushButton(CXDlgAttProgressBar);
        m_pBtnCancel->setObjectName(QString::fromUtf8("m_pBtnCancel"));

        hboxLayout->addWidget(m_pBtnCancel);


        vboxLayout->addLayout(hboxLayout);


        gridLayout->addLayout(vboxLayout, 0, 0, 1, 1);


        retranslateUi(CXDlgAttProgressBar);

        QMetaObject::connectSlotsByName(CXDlgAttProgressBar);
    } // setupUi

    void retranslateUi(QDialog *CXDlgAttProgressBar)
    {
        CXDlgAttProgressBar->setWindowTitle(QCoreApplication::translate("CXDlgAttProgressBar", "Dialog", nullptr));
        m_pLabelName->setText(QCoreApplication::translate("CXDlgAttProgressBar", "TextLabel", nullptr));
        p_mLabelTime->setText(QCoreApplication::translate("CXDlgAttProgressBar", "Elapsed Time:", nullptr));
        m_pLabelElapsedTime->setText(QCoreApplication::translate("CXDlgAttProgressBar", "0", nullptr));
        m_pBtnCancel->setText(QCoreApplication::translate("CXDlgAttProgressBar", "Abort", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgAttProgressBar: public Ui_CXDlgAttProgressBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGATTPROGRESSBAR_H
