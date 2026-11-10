/********************************************************************************
** Form generated from reading UI file 'xdlgprojectproperties.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGPROJECTPROPERTIES_H
#define UI_XDLGPROJECTPROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXDlgProjectProperties
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *m_tabWidget;
    QDialogButtonBox *m_buttonBox;

    void setupUi(QDialog *CXDlgProjectProperties)
    {
        if (CXDlgProjectProperties->objectName().isEmpty())
            CXDlgProjectProperties->setObjectName(QString::fromUtf8("CXDlgProjectProperties"));
        CXDlgProjectProperties->resize(400, 300);
        verticalLayout = new QVBoxLayout(CXDlgProjectProperties);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_tabWidget = new QTabWidget(CXDlgProjectProperties);
        m_tabWidget->setObjectName(QString::fromUtf8("m_tabWidget"));

        verticalLayout->addWidget(m_tabWidget);

        m_buttonBox = new QDialogButtonBox(CXDlgProjectProperties);
        m_buttonBox->setObjectName(QString::fromUtf8("m_buttonBox"));
        m_buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        m_buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(m_buttonBox);


        retranslateUi(CXDlgProjectProperties);

        QMetaObject::connectSlotsByName(CXDlgProjectProperties);
    } // setupUi

    void retranslateUi(QDialog *CXDlgProjectProperties)
    {
        CXDlgProjectProperties->setWindowTitle(QCoreApplication::translate("CXDlgProjectProperties", "CXDlgProjectProperties", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgProjectProperties: public Ui_CXDlgProjectProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGPROJECTPROPERTIES_H
