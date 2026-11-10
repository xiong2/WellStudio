/********************************************************************************
** Form generated from reading UI file 'xpageselectwelltopsformation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESELECTWELLTOPSFORMATION_H
#define UI_XPAGESELECTWELLTOPSFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_CXPageSelectWellTopsFormation
{
public:
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *m_lwgtFormation;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *m_pbSelectAll;
    QPushButton *m_pbUnSelectAll;

    void setupUi(QWizardPage *CXPageSelectWellTopsFormation)
    {
        if (CXPageSelectWellTopsFormation->objectName().isEmpty())
            CXPageSelectWellTopsFormation->setObjectName(QString::fromUtf8("CXPageSelectWellTopsFormation"));
        CXPageSelectWellTopsFormation->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CXPageSelectWellTopsFormation->sizePolicy().hasHeightForWidth());
        CXPageSelectWellTopsFormation->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(CXPageSelectWellTopsFormation);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_lwgtFormation = new QListWidget(CXPageSelectWellTopsFormation);
        m_lwgtFormation->setObjectName(QString::fromUtf8("m_lwgtFormation"));

        horizontalLayout_3->addWidget(m_lwgtFormation);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        m_pbSelectAll = new QPushButton(CXPageSelectWellTopsFormation);
        m_pbSelectAll->setObjectName(QString::fromUtf8("m_pbSelectAll"));

        verticalLayout_2->addWidget(m_pbSelectAll);

        m_pbUnSelectAll = new QPushButton(CXPageSelectWellTopsFormation);
        m_pbUnSelectAll->setObjectName(QString::fromUtf8("m_pbUnSelectAll"));

        verticalLayout_2->addWidget(m_pbUnSelectAll);


        horizontalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout->addLayout(horizontalLayout_3);


        retranslateUi(CXPageSelectWellTopsFormation);

        QMetaObject::connectSlotsByName(CXPageSelectWellTopsFormation);
    } // setupUi

    void retranslateUi(QWizardPage *CXPageSelectWellTopsFormation)
    {
        CXPageSelectWellTopsFormation->setWindowTitle(QCoreApplication::translate("CXPageSelectWellTopsFormation", "CXPageWellTops", nullptr));
        m_pbSelectAll->setText(QCoreApplication::translate("CXPageSelectWellTopsFormation", "Select All", nullptr));
        m_pbUnSelectAll->setText(QCoreApplication::translate("CXPageSelectWellTopsFormation", "Deselect All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageSelectWellTopsFormation: public Ui_CXPageSelectWellTopsFormation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESELECTWELLTOPSFORMATION_H
