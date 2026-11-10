/********************************************************************************
** Form generated from reading UI file 'xpagebuildlfmone.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEBUILDLFMONE_H
#define UI_XPAGEBUILDLFMONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageBuildLowFrequencyModel
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_1;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *vboxLayout;
    QToolButton *m_pBtnAdd;
    QToolButton *m_pBtnRemove;
    QListWidget *m_pListHorizon;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *m_pLineEdtLFMName;

    void setupUi(QWidget *PageBuildLowFrequencyModel)
    {
        if (PageBuildLowFrequencyModel->objectName().isEmpty())
            PageBuildLowFrequencyModel->setObjectName(QString::fromUtf8("PageBuildLowFrequencyModel"));
        PageBuildLowFrequencyModel->resize(490, 383);
        gridLayout = new QGridLayout(PageBuildLowFrequencyModel);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_1 = new QLabel(PageBuildLowFrequencyModel);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        horizontalLayout->addWidget(label_1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        m_pBtnAdd = new QToolButton(PageBuildLowFrequencyModel);
        m_pBtnAdd->setObjectName(QString::fromUtf8("m_pBtnAdd"));
        m_pBtnAdd->setMaximumSize(QSize(16777215, 16777215));

        vboxLayout->addWidget(m_pBtnAdd);

        m_pBtnRemove = new QToolButton(PageBuildLowFrequencyModel);
        m_pBtnRemove->setObjectName(QString::fromUtf8("m_pBtnRemove"));

        vboxLayout->addWidget(m_pBtnRemove);


        gridLayout->addLayout(vboxLayout, 1, 0, 1, 1);

        m_pListHorizon = new QListWidget(PageBuildLowFrequencyModel);
        m_pListHorizon->setObjectName(QString::fromUtf8("m_pListHorizon"));

        gridLayout->addWidget(m_pListHorizon, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(PageBuildLowFrequencyModel);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        m_pLineEdtLFMName = new QLineEdit(PageBuildLowFrequencyModel);
        m_pLineEdtLFMName->setObjectName(QString::fromUtf8("m_pLineEdtLFMName"));

        horizontalLayout_2->addWidget(m_pLineEdtLFMName);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 2);


        retranslateUi(PageBuildLowFrequencyModel);

        QMetaObject::connectSlotsByName(PageBuildLowFrequencyModel);
    } // setupUi

    void retranslateUi(QWidget *PageBuildLowFrequencyModel)
    {
        PageBuildLowFrequencyModel->setWindowTitle(QCoreApplication::translate("PageBuildLowFrequencyModel", "Form", nullptr));
        label_1->setText(QCoreApplication::translate("PageBuildLowFrequencyModel", "Select one or multiple 3-D horizons to build a low frequency model", nullptr));
        m_pBtnAdd->setText(QCoreApplication::translate("PageBuildLowFrequencyModel", "...", nullptr));
        m_pBtnRemove->setText(QCoreApplication::translate("PageBuildLowFrequencyModel", "...", nullptr));
        label_3->setText(QCoreApplication::translate("PageBuildLowFrequencyModel", "Name of low frequency model  ", nullptr));
        m_pLineEdtLFMName->setText(QCoreApplication::translate("PageBuildLowFrequencyModel", "LFM-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageBuildLowFrequencyModel: public Ui_PageBuildLowFrequencyModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEBUILDLFMONE_H
