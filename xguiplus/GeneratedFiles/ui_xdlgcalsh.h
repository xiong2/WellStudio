/********************************************************************************
** Form generated from reading UI file 'xdlgcalsh.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGCALSH_H
#define UI_XDLGCALSH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_XDlgCalSH
{
public:
    QGridLayout *gridLayout;
    QComboBox *comboBoxNiu;
    QComboBox *comboBoxSv;
    QComboBox *comboBoxPp;
    QComboBox *comboBoxBiot;
    QLineEdit *lineEditSHDV;
    QLineEdit *lineEditSh;
    QLabel *label_5;
    QLabel *label_11;
    QLabel *label_3;
    QLabel *label_9;
    QLabel *label;
    QComboBox *comboBoxE;
    QLabel *label_8;
    QLabel *label_4;
    QLabel *label_10;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditShDV;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEditSH;
    QLabel *label_7;

    void setupUi(QDialog *XDlgCalSH)
    {
        if (XDlgCalSH->objectName().isEmpty())
            XDlgCalSH->setObjectName(QString::fromUtf8("XDlgCalSH"));
        XDlgCalSH->resize(578, 220);
        gridLayout = new QGridLayout(XDlgCalSH);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBoxNiu = new QComboBox(XDlgCalSH);
        comboBoxNiu->setObjectName(QString::fromUtf8("comboBoxNiu"));
        comboBoxNiu->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(comboBoxNiu, 4, 3, 1, 1);

        comboBoxSv = new QComboBox(XDlgCalSH);
        comboBoxSv->setObjectName(QString::fromUtf8("comboBoxSv"));
        comboBoxSv->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(comboBoxSv, 5, 3, 1, 1);

        comboBoxPp = new QComboBox(XDlgCalSH);
        comboBoxPp->setObjectName(QString::fromUtf8("comboBoxPp"));
        comboBoxPp->setMinimumSize(QSize(120, 0));
        comboBoxPp->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(comboBoxPp, 5, 1, 1, 1);

        comboBoxBiot = new QComboBox(XDlgCalSH);
        comboBoxBiot->setObjectName(QString::fromUtf8("comboBoxBiot"));
        comboBoxBiot->setMinimumSize(QSize(120, 0));
        comboBoxBiot->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(comboBoxBiot, 4, 1, 1, 1);

        lineEditSHDV = new QLineEdit(XDlgCalSH);
        lineEditSHDV->setObjectName(QString::fromUtf8("lineEditSHDV"));

        gridLayout->addWidget(lineEditSHDV, 1, 2, 1, 2);

        lineEditSh = new QLineEdit(XDlgCalSH);
        lineEditSh->setObjectName(QString::fromUtf8("lineEditSh"));

        gridLayout->addWidget(lineEditSh, 3, 3, 1, 1);

        label_5 = new QLabel(XDlgCalSH);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(20, 16777215));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_11 = new QLabel(XDlgCalSH);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_11->setFont(font1);

        gridLayout->addWidget(label_11, 2, 0, 1, 2);

        label_3 = new QLabel(XDlgCalSH);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(20, 16777215));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_9 = new QLabel(XDlgCalSH);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(20, 0));
        label_9->setMaximumSize(QSize(20, 16777215));
        label_9->setFont(font);

        gridLayout->addWidget(label_9, 5, 2, 1, 1);

        label = new QLabel(XDlgCalSH);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);

        gridLayout->addWidget(label, 0, 0, 1, 4);

        comboBoxE = new QComboBox(XDlgCalSH);
        comboBoxE->setObjectName(QString::fromUtf8("comboBoxE"));
        comboBoxE->setMinimumSize(QSize(170, 0));
        comboBoxE->setMaximumSize(QSize(170, 16777215));

        gridLayout->addWidget(comboBoxE, 4, 5, 1, 1);

        label_8 = new QLabel(XDlgCalSH);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(20, 16777215));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 5, 0, 1, 1);

        label_4 = new QLabel(XDlgCalSH);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(20, 16777215));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 3, 2, 1, 1);

        label_10 = new QLabel(XDlgCalSH);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font1);

        gridLayout->addWidget(label_10, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(XDlgCalSH);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 4, 1, 2);

        lineEditShDV = new QLineEdit(XDlgCalSH);
        lineEditShDV->setObjectName(QString::fromUtf8("lineEditShDV"));

        gridLayout->addWidget(lineEditShDV, 2, 2, 1, 2);

        label_6 = new QLabel(XDlgCalSH);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(20, 16777215));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 4, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 2, 1, 1);

        lineEditSH = new QLineEdit(XDlgCalSH);
        lineEditSH->setObjectName(QString::fromUtf8("lineEditSH"));

        gridLayout->addWidget(lineEditSH, 3, 1, 1, 1);

        label_7 = new QLabel(XDlgCalSH);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(20, 16777215));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 4, 4, 1, 1);


        retranslateUi(XDlgCalSH);
        QObject::connect(buttonBox, SIGNAL(rejected()), XDlgCalSH, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), XDlgCalSH, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgCalSH);
    } // setupUi

    void retranslateUi(QDialog *XDlgCalSH)
    {
        XDlgCalSH->setWindowTitle(QCoreApplication::translate("XDlgCalSH", "XDlgCalSH", nullptr));
        lineEditSHDV->setText(QCoreApplication::translate("XDlgCalSH", "SHDV", nullptr));
        lineEditSh->setText(QCoreApplication::translate("XDlgCalSH", "0.02", nullptr));
        label_5->setText(QCoreApplication::translate("XDlgCalSH", "\316\261", nullptr));
        label_11->setText(QCoreApplication::translate("XDlgCalSH", "Output \317\203h volume", nullptr));
        label_3->setText(QCoreApplication::translate("XDlgCalSH", "\316\276H", nullptr));
        label_9->setText(QCoreApplication::translate("XDlgCalSH", "\317\203v", nullptr));
        label->setText(QCoreApplication::translate("XDlgCalSH", "Calculate Horizontal Stresses", nullptr));
        label_8->setText(QCoreApplication::translate("XDlgCalSH", "Pp", nullptr));
        label_4->setText(QCoreApplication::translate("XDlgCalSH", "\316\276h", nullptr));
        label_10->setText(QCoreApplication::translate("XDlgCalSH", "Output \317\203H volume", nullptr));
        lineEditShDV->setText(QCoreApplication::translate("XDlgCalSH", "ShDV", nullptr));
        label_6->setText(QCoreApplication::translate("XDlgCalSH", "\316\274", nullptr));
        lineEditSH->setText(QCoreApplication::translate("XDlgCalSH", "0.03", nullptr));
        label_7->setText(QCoreApplication::translate("XDlgCalSH", "E", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgCalSH: public Ui_XDlgCalSH {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGCALSH_H
