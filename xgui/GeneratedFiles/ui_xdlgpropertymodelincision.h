/********************************************************************************
** Form generated from reading UI file 'xdlgpropertymodelincision.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGPROPERTYMODELINCISION_H
#define UI_XDLGPROPERTYMODELINCISION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CXDlgPropertyModelIncision
{
public:
    QGridLayout *gridLayout;
    QLabel *m_pLabel;
    QComboBox *m_cbbRS;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *m_pBtnBox;

    void setupUi(QDialog *CXDlgPropertyModelIncision)
    {
        if (CXDlgPropertyModelIncision->objectName().isEmpty())
            CXDlgPropertyModelIncision->setObjectName(QString::fromUtf8("CXDlgPropertyModelIncision"));
        CXDlgPropertyModelIncision->resize(450, 300);
        gridLayout = new QGridLayout(CXDlgPropertyModelIncision);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pLabel = new QLabel(CXDlgPropertyModelIncision);
        m_pLabel->setObjectName(QString::fromUtf8("m_pLabel"));

        gridLayout->addWidget(m_pLabel, 0, 0, 1, 1);

        m_cbbRS = new QComboBox(CXDlgPropertyModelIncision);
        m_cbbRS->setObjectName(QString::fromUtf8("m_cbbRS"));

        gridLayout->addWidget(m_cbbRS, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        m_pBtnBox = new QDialogButtonBox(CXDlgPropertyModelIncision);
        m_pBtnBox->setObjectName(QString::fromUtf8("m_pBtnBox"));
        m_pBtnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(m_pBtnBox, 2, 1, 1, 1);


        retranslateUi(CXDlgPropertyModelIncision);

        QMetaObject::connectSlotsByName(CXDlgPropertyModelIncision);
    } // setupUi

    void retranslateUi(QDialog *CXDlgPropertyModelIncision)
    {
        CXDlgPropertyModelIncision->setWindowTitle(QCoreApplication::translate("CXDlgPropertyModelIncision", "Incision of property model", nullptr));
        m_pLabel->setText(QCoreApplication::translate("CXDlgPropertyModelIncision", "Select a random section:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgPropertyModelIncision: public Ui_CXDlgPropertyModelIncision {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGPROPERTYMODELINCISION_H
