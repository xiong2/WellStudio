/********************************************************************************
** Form generated from reading UI file 'xdlgextracthorizonatt.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGEXTRACTHORIZONATT_H
#define UI_XDLGEXTRACTHORIZONATT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DlgExtractHorizonAtt
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_1;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QVBoxLayout *_2;
    QToolButton *m_pBtnAdd;
    QToolButton *m_pBtnRemove;
    QListWidget *m_pListDV;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *m_pCombMethod;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *m_pLineTopShift;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLineEdit *m_pLineBotShift;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgExtractHorizonAtt)
    {
        if (DlgExtractHorizonAtt->objectName().isEmpty())
            DlgExtractHorizonAtt->setObjectName(QString::fromUtf8("DlgExtractHorizonAtt"));
        DlgExtractHorizonAtt->resize(583, 455);
        gridLayout_3 = new QGridLayout(DlgExtractHorizonAtt);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_1 = new QLabel(DlgExtractHorizonAtt);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        horizontalLayout->addWidget(label_1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, -1, -1, 15);
        _2 = new QVBoxLayout();
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(-1, -1, -1, 0);
        m_pBtnAdd = new QToolButton(DlgExtractHorizonAtt);
        m_pBtnAdd->setObjectName(QString::fromUtf8("m_pBtnAdd"));
        m_pBtnAdd->setMaximumSize(QSize(16777215, 16777215));

        _2->addWidget(m_pBtnAdd);

        m_pBtnRemove = new QToolButton(DlgExtractHorizonAtt);
        m_pBtnRemove->setObjectName(QString::fromUtf8("m_pBtnRemove"));

        _2->addWidget(m_pBtnRemove);


        gridLayout_2->addLayout(_2, 0, 0, 1, 1);

        m_pListDV = new QListWidget(DlgExtractHorizonAtt);
        m_pListDV->setObjectName(QString::fromUtf8("m_pListDV"));

        gridLayout_2->addWidget(m_pListDV, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(DlgExtractHorizonAtt);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        m_pCombMethod = new QComboBox(groupBox);
        m_pCombMethod->addItem(QString());
        m_pCombMethod->addItem(QString());
        m_pCombMethod->setObjectName(QString::fromUtf8("m_pCombMethod"));
        m_pCombMethod->setMinimumSize(QSize(200, 0));

        gridLayout->addWidget(m_pCombMethod, 0, 2, 1, 4);

        horizontalSpacer_4 = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 6, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 1, 1, 1);

        m_pLineTopShift = new QLineEdit(groupBox);
        m_pLineTopShift->setObjectName(QString::fromUtf8("m_pLineTopShift"));
        m_pLineTopShift->setMinimumSize(QSize(60, 0));
        m_pLineTopShift->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(m_pLineTopShift, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 4, 1, 1);

        m_pLineBotShift = new QLineEdit(groupBox);
        m_pLineBotShift->setObjectName(QString::fromUtf8("m_pLineBotShift"));
        m_pLineBotShift->setMinimumSize(QSize(60, 0));
        m_pLineBotShift->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(m_pLineBotShift, 1, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 6, 1, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DlgExtractHorizonAtt);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 3, 0, 1, 1);


        retranslateUi(DlgExtractHorizonAtt);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgExtractHorizonAtt, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgExtractHorizonAtt, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgExtractHorizonAtt);
    } // setupUi

    void retranslateUi(QDialog *DlgExtractHorizonAtt)
    {
        DlgExtractHorizonAtt->setWindowTitle(QCoreApplication::translate("DlgExtractHorizonAtt", "Dialog", nullptr));
        label_1->setText(QCoreApplication::translate("DlgExtractHorizonAtt", "Select one or multiple data volumes to extract horizon attributes", nullptr));
        m_pBtnAdd->setText(QCoreApplication::translate("DlgExtractHorizonAtt", "...", nullptr));
        m_pBtnRemove->setText(QCoreApplication::translate("DlgExtractHorizonAtt", "...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgExtractHorizonAtt", "Extraction Parameters", nullptr));
        label->setText(QCoreApplication::translate("DlgExtractHorizonAtt", "Extraction Method: ", nullptr));
        m_pCombMethod->setItemText(0, QCoreApplication::translate("DlgExtractHorizonAtt", "Instantaneous", nullptr));
        m_pCombMethod->setItemText(1, QCoreApplication::translate("DlgExtractHorizonAtt", "Arithmetic Mean", nullptr));

        label_2->setText(QCoreApplication::translate("DlgExtractHorizonAtt", "Window Size:     ", nullptr));
        label_3->setText(QCoreApplication::translate("DlgExtractHorizonAtt", "Top shift", nullptr));
        label_4->setText(QCoreApplication::translate("DlgExtractHorizonAtt", "Bottom Shift", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgExtractHorizonAtt: public Ui_DlgExtractHorizonAtt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGEXTRACTHORIZONATT_H
