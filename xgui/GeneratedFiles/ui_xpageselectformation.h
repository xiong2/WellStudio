/********************************************************************************
** Form generated from reading UI file 'xpageselectformation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESELECTFORMATION_H
#define UI_XPAGESELECTFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_CXPageSelectFormation
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *m_lwgtFormation;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *m_pbSelectAll;
    QPushButton *m_pbUnSelectAll;

    void setupUi(QWizardPage *CXPageSelectFormation)
    {
        if (CXPageSelectFormation->objectName().isEmpty())
            CXPageSelectFormation->setObjectName(QString::fromUtf8("CXPageSelectFormation"));
        CXPageSelectFormation->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CXPageSelectFormation->sizePolicy().hasHeightForWidth());
        CXPageSelectFormation->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(CXPageSelectFormation);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_lwgtFormation = new QListWidget(CXPageSelectFormation);
        m_lwgtFormation->setObjectName(QString::fromUtf8("m_lwgtFormation"));

        horizontalLayout->addWidget(m_lwgtFormation);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        m_pbSelectAll = new QPushButton(CXPageSelectFormation);
        m_pbSelectAll->setObjectName(QString::fromUtf8("m_pbSelectAll"));

        verticalLayout_2->addWidget(m_pbSelectAll);

        m_pbUnSelectAll = new QPushButton(CXPageSelectFormation);
        m_pbUnSelectAll->setObjectName(QString::fromUtf8("m_pbUnSelectAll"));

        verticalLayout_2->addWidget(m_pbUnSelectAll);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(CXPageSelectFormation);

        QMetaObject::connectSlotsByName(CXPageSelectFormation);
    } // setupUi

    void retranslateUi(QWizardPage *CXPageSelectFormation)
    {
        CXPageSelectFormation->setWindowTitle(QCoreApplication::translate("CXPageSelectFormation", "Select Formation", nullptr));
        m_pbSelectAll->setText(QCoreApplication::translate("CXPageSelectFormation", "Select All", nullptr));
        m_pbUnSelectAll->setText(QCoreApplication::translate("CXPageSelectFormation", "Deselect All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageSelectFormation: public Ui_CXPageSelectFormation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESELECTFORMATION_H
