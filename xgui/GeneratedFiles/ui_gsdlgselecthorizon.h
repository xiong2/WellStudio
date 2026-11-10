/********************************************************************************
** Form generated from reading UI file 'gsdlgselecthorizon.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSDLGSELECTHORIZON_H
#define UI_GSDLGSELECTHORIZON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_GSDlgSelectHorizon
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GSDlgSelectHorizon)
    {
        if (GSDlgSelectHorizon->objectName().isEmpty())
            GSDlgSelectHorizon->setObjectName(QString::fromUtf8("GSDlgSelectHorizon"));
        GSDlgSelectHorizon->resize(338, 341);
        gridLayout = new QGridLayout(GSDlgSelectHorizon);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(GSDlgSelectHorizon);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(GSDlgSelectHorizon);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/HelpInfo.png")));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        listWidget = new QListWidget(GSDlgSelectHorizon);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(GSDlgSelectHorizon);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(GSDlgSelectHorizon);
        QObject::connect(buttonBox, SIGNAL(rejected()), GSDlgSelectHorizon, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), GSDlgSelectHorizon, SLOT(accept()));

        QMetaObject::connectSlotsByName(GSDlgSelectHorizon);
    } // setupUi

    void retranslateUi(QDialog *GSDlgSelectHorizon)
    {
        GSDlgSelectHorizon->setWindowTitle(QCoreApplication::translate("GSDlgSelectHorizon", "GSDlgSelectHorizon", nullptr));
        label->setText(QCoreApplication::translate("GSDlgSelectHorizon", "Select horizons belong to current geologic stage", nullptr));
#if QT_CONFIG(tooltip)
        label_2->setToolTip(QCoreApplication::translate("GSDlgSelectHorizon", "<html><head/><body><p>Here list all horizons of current survey.  Select horizons already belong to other geologic stage will automatically wipe them out from that stage.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QString());
#if QT_CONFIG(tooltip)
        buttonBox->setToolTip(QCoreApplication::translate("GSDlgSelectHorizon", "<html><head/><body><p>Here list all horizons belong to current survey.  Select horizons already belongs to other geologic stage will automatically wipe them out from that stage.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class GSDlgSelectHorizon: public Ui_GSDlgSelectHorizon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSDLGSELECTHORIZON_H
