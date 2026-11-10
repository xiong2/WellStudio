/********************************************************************************
** Form generated from reading UI file 'xpagewellconditionupscale.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEWELLCONDITIONUPSCALE_H
#define UI_XPAGEWELLCONDITIONUPSCALE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXPageWellConditionUpscale
{
public:
    QGridLayout *gridLayout;
    QLabel *m_pLabelLogAlias;
    QListWidget *m_pListLogAlias;
    QHBoxLayout *horizontalLayout;
    QLabel *m_pLabelFunction;
    QComboBox *m_pCbbFunctions;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *m_pBtnSelectAll;
    QPushButton *m_pBtnDisSelectAll;
    QHBoxLayout *horizontalLayout_2;
    QDialogButtonBox *m_pBtnGroupOkCancel;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CXPageWellConditionUpscale)
    {
        if (CXPageWellConditionUpscale->objectName().isEmpty())
            CXPageWellConditionUpscale->setObjectName(QString::fromUtf8("CXPageWellConditionUpscale"));
        CXPageWellConditionUpscale->resize(400, 300);
        gridLayout = new QGridLayout(CXPageWellConditionUpscale);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pLabelLogAlias = new QLabel(CXPageWellConditionUpscale);
        m_pLabelLogAlias->setObjectName(QString::fromUtf8("m_pLabelLogAlias"));

        gridLayout->addWidget(m_pLabelLogAlias, 0, 0, 1, 1);

        m_pListLogAlias = new QListWidget(CXPageWellConditionUpscale);
        m_pListLogAlias->setObjectName(QString::fromUtf8("m_pListLogAlias"));

        gridLayout->addWidget(m_pListLogAlias, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pLabelFunction = new QLabel(CXPageWellConditionUpscale);
        m_pLabelFunction->setObjectName(QString::fromUtf8("m_pLabelFunction"));

        horizontalLayout->addWidget(m_pLabelFunction);

        m_pCbbFunctions = new QComboBox(CXPageWellConditionUpscale);
        m_pCbbFunctions->setObjectName(QString::fromUtf8("m_pCbbFunctions"));

        horizontalLayout->addWidget(m_pCbbFunctions);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        m_pBtnSelectAll = new QPushButton(CXPageWellConditionUpscale);
        m_pBtnSelectAll->setObjectName(QString::fromUtf8("m_pBtnSelectAll"));

        verticalLayout->addWidget(m_pBtnSelectAll);

        m_pBtnDisSelectAll = new QPushButton(CXPageWellConditionUpscale);
        m_pBtnDisSelectAll->setObjectName(QString::fromUtf8("m_pBtnDisSelectAll"));

        verticalLayout->addWidget(m_pBtnDisSelectAll);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_pBtnGroupOkCancel = new QDialogButtonBox(CXPageWellConditionUpscale);
        m_pBtnGroupOkCancel->setObjectName(QString::fromUtf8("m_pBtnGroupOkCancel"));
        m_pBtnGroupOkCancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(m_pBtnGroupOkCancel);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);


        retranslateUi(CXPageWellConditionUpscale);

        QMetaObject::connectSlotsByName(CXPageWellConditionUpscale);
    } // setupUi

    void retranslateUi(QDialog *CXPageWellConditionUpscale)
    {
        CXPageWellConditionUpscale->setWindowTitle(QCoreApplication::translate("CXPageWellConditionUpscale", "Select log alias", nullptr));
        m_pLabelLogAlias->setText(QCoreApplication::translate("CXPageWellConditionUpscale", "Log alias:", nullptr));
        m_pLabelFunction->setText(QCoreApplication::translate("CXPageWellConditionUpscale", "Upscale function:", nullptr));
        m_pBtnSelectAll->setText(QString());
        m_pBtnDisSelectAll->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXPageWellConditionUpscale: public Ui_CXPageWellConditionUpscale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEWELLCONDITIONUPSCALE_H
