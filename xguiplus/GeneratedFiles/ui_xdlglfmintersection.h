/********************************************************************************
** Form generated from reading UI file 'xdlglfmintersection.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGLFMINTERSECTION_H
#define UI_XDLGLFMINTERSECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXDlgLFMIntersection
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *m_pBtbAddAll;
    QPushButton *m_pBtnRemoveAll;
    QDialogButtonBox *buttonBox;
    QListWidget *m_pListWidget;

    void setupUi(QDialog *CXDlgLFMIntersection)
    {
        if (CXDlgLFMIntersection->objectName().isEmpty())
            CXDlgLFMIntersection->setObjectName(QString::fromUtf8("CXDlgLFMIntersection"));
        CXDlgLFMIntersection->resize(642, 448);
        gridLayout = new QGridLayout(CXDlgLFMIntersection);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CXDlgLFMIntersection);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 320, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pBtbAddAll = new QPushButton(CXDlgLFMIntersection);
        m_pBtbAddAll->setObjectName(QString::fromUtf8("m_pBtbAddAll"));
        m_pBtbAddAll->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(m_pBtbAddAll);

        m_pBtnRemoveAll = new QPushButton(CXDlgLFMIntersection);
        m_pBtnRemoveAll->setObjectName(QString::fromUtf8("m_pBtnRemoveAll"));
        m_pBtnRemoveAll->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(m_pBtnRemoveAll);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(CXDlgLFMIntersection);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 1);

        m_pListWidget = new QListWidget(CXDlgLFMIntersection);
        m_pListWidget->setObjectName(QString::fromUtf8("m_pListWidget"));

        gridLayout->addWidget(m_pListWidget, 1, 0, 2, 1);


        retranslateUi(CXDlgLFMIntersection);
        QObject::connect(buttonBox, SIGNAL(accepted()), CXDlgLFMIntersection, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CXDlgLFMIntersection, SLOT(reject()));

        QMetaObject::connectSlotsByName(CXDlgLFMIntersection);
    } // setupUi

    void retranslateUi(QDialog *CXDlgLFMIntersection)
    {
        CXDlgLFMIntersection->setWindowTitle(QCoreApplication::translate("CXDlgLFMIntersection", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CXDlgLFMIntersection", "Please Select Wells with T-D Curve", nullptr));
        m_pBtbAddAll->setText(QString());
        m_pBtnRemoveAll->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXDlgLFMIntersection: public Ui_CXDlgLFMIntersection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGLFMINTERSECTION_H
