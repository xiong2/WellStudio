/********************************************************************************
** Form generated from reading UI file 'xpageprojectproperties.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEPROJECTPROPERTIES_H
#define UI_XPAGEPROJECTPROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include "xbasepropertypage.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageProjectProperties
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *m_bAuto;
    QSpinBox *m_nTime;
    QLabel *label;
    QPushButton *m_btnVacuumDB;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QCheckBox *m_checkBoxBold;
    QFontComboBox *m_fontComboBox;
    QLineEdit *m_editFontSize;
    QLabel *label_2;
    QCheckBox *m_checkBoxItalic;

    void setupUi(CXBasePropertyPage *CXPageProjectProperties)
    {
        if (CXPageProjectProperties->objectName().isEmpty())
            CXPageProjectProperties->setObjectName(QString::fromUtf8("CXPageProjectProperties"));
        CXPageProjectProperties->resize(400, 300);
        gridLayout_2 = new QGridLayout(CXPageProjectProperties);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(CXPageProjectProperties);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_bAuto = new QCheckBox(groupBox);
        m_bAuto->setObjectName(QString::fromUtf8("m_bAuto"));

        gridLayout->addWidget(m_bAuto, 0, 0, 1, 1);

        m_nTime = new QSpinBox(groupBox);
        m_nTime->setObjectName(QString::fromUtf8("m_nTime"));
        m_nTime->setMinimum(1);

        gridLayout->addWidget(m_nTime, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        m_btnVacuumDB = new QPushButton(groupBox);
        m_btnVacuumDB->setObjectName(QString::fromUtf8("m_btnVacuumDB"));

        gridLayout->addWidget(m_btnVacuumDB, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(CXPageProjectProperties);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_checkBoxBold = new QCheckBox(groupBox_2);
        m_checkBoxBold->setObjectName(QString::fromUtf8("m_checkBoxBold"));

        gridLayout_3->addWidget(m_checkBoxBold, 1, 0, 1, 1);

        m_fontComboBox = new QFontComboBox(groupBox_2);
        m_fontComboBox->setObjectName(QString::fromUtf8("m_fontComboBox"));

        gridLayout_3->addWidget(m_fontComboBox, 0, 0, 1, 1);

        m_editFontSize = new QLineEdit(groupBox_2);
        m_editFontSize->setObjectName(QString::fromUtf8("m_editFontSize"));

        gridLayout_3->addWidget(m_editFontSize, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        m_checkBoxItalic = new QCheckBox(groupBox_2);
        m_checkBoxItalic->setObjectName(QString::fromUtf8("m_checkBoxItalic"));

        gridLayout_3->addWidget(m_checkBoxItalic, 1, 1, 1, 2);


        gridLayout_2->addWidget(groupBox_2, 2, 0, 1, 1);


        retranslateUi(CXPageProjectProperties);

        QMetaObject::connectSlotsByName(CXPageProjectProperties);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageProjectProperties)
    {
        CXPageProjectProperties->setWindowTitle(QCoreApplication::translate("CXPageProjectProperties", "CXPageProjectProperties", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXPageProjectProperties", "Project Setting", nullptr));
        m_bAuto->setText(QCoreApplication::translate("CXPageProjectProperties", "Save automatically every", nullptr));
        label->setText(QCoreApplication::translate("CXPageProjectProperties", "minutes", nullptr));
        m_btnVacuumDB->setText(QCoreApplication::translate("CXPageProjectProperties", "Clean Project", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXPageProjectProperties", "Font", nullptr));
        m_checkBoxBold->setText(QCoreApplication::translate("CXPageProjectProperties", "Bold", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageProjectProperties", "Size:", nullptr));
        m_checkBoxItalic->setText(QCoreApplication::translate("CXPageProjectProperties", "Italic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageProjectProperties: public Ui_CXPageProjectProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEPROJECTPROPERTIES_H
