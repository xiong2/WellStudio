/********************************************************************************
** Form generated from reading UI file 'xdlgfracgridintr.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGFRACGRIDINTR_H
#define UI_XDLGFRACGRIDINTR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_CXDlgFracGridIntr
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QComboBox *comboBoxProp;
    QComboBox *comboBoxGrid;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CXDlgFracGridIntr)
    {
        if (CXDlgFracGridIntr->objectName().isEmpty())
            CXDlgFracGridIntr->setObjectName(QString::fromUtf8("CXDlgFracGridIntr"));
        CXDlgFracGridIntr->resize(215, 127);
        gridLayout = new QGridLayout(CXDlgFracGridIntr);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(CXDlgFracGridIntr);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(CXDlgFracGridIntr);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBoxProp = new QComboBox(CXDlgFracGridIntr);
        comboBoxProp->setObjectName(QString::fromUtf8("comboBoxProp"));

        gridLayout->addWidget(comboBoxProp, 1, 1, 1, 1);

        comboBoxGrid = new QComboBox(CXDlgFracGridIntr);
        comboBoxGrid->setObjectName(QString::fromUtf8("comboBoxGrid"));

        gridLayout->addWidget(comboBoxGrid, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(CXDlgFracGridIntr);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(CXDlgFracGridIntr);
        QObject::connect(buttonBox, SIGNAL(accepted()), CXDlgFracGridIntr, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CXDlgFracGridIntr, SLOT(reject()));

        QMetaObject::connectSlotsByName(CXDlgFracGridIntr);
    } // setupUi

    void retranslateUi(QDialog *CXDlgFracGridIntr)
    {
        CXDlgFracGridIntr->setWindowTitle(QCoreApplication::translate("CXDlgFracGridIntr", "Fracture-Grid Intersect", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlgFracGridIntr", "Select Property", nullptr));
        label->setText(QCoreApplication::translate("CXDlgFracGridIntr", "Select Grid", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgFracGridIntr: public Ui_CXDlgFracGridIntr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGFRACGRIDINTR_H
