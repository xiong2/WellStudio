/********************************************************************************
** Form generated from reading UI file 'xpagfractureinversionone.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGFRACTUREINVERSIONONE_H
#define UI_XPAGFRACTUREINVERSIONONE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageFractureInversion
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QToolButton *m_pBtnSelectEpsilon;
    QLineEdit *m_pLineEdtEpsilon;
    QLabel *label_2;
    QToolButton *m_pBtnSelectDelta;
    QLineEdit *m_pLineEdtDelta;
    QLabel *label_3;
    QToolButton *m_pBtnSelectGamma;
    QLineEdit *m_pLineEdtGamma;
    QLabel *label_7;
    QToolButton *m_pBtnSelectAzimuth;
    QLineEdit *m_pLineEdtAzimuth;
    QLabel *label_6;
    QTableWidget *m_pTable;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *m_pPushBtnLoadPara;

    void setupUi(QWidget *PageFractureInversion)
    {
        if (PageFractureInversion->objectName().isEmpty())
            PageFractureInversion->setObjectName(QString::fromUtf8("PageFractureInversion"));
        PageFractureInversion->resize(740, 511);
        gridLayout_2 = new QGridLayout(PageFractureInversion);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(PageFractureInversion);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_pBtnSelectEpsilon = new QToolButton(PageFractureInversion);
        m_pBtnSelectEpsilon->setObjectName(QString::fromUtf8("m_pBtnSelectEpsilon"));
        m_pBtnSelectEpsilon->setMinimumSize(QSize(30, 0));
        m_pBtnSelectEpsilon->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnSelectEpsilon->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectEpsilon, 0, 1, 1, 1);

        m_pLineEdtEpsilon = new QLineEdit(PageFractureInversion);
        m_pLineEdtEpsilon->setObjectName(QString::fromUtf8("m_pLineEdtEpsilon"));
        m_pLineEdtEpsilon->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtEpsilon, 0, 2, 1, 1);

        label_2 = new QLabel(PageFractureInversion);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        m_pBtnSelectDelta = new QToolButton(PageFractureInversion);
        m_pBtnSelectDelta->setObjectName(QString::fromUtf8("m_pBtnSelectDelta"));
        m_pBtnSelectDelta->setMinimumSize(QSize(30, 0));
        m_pBtnSelectDelta->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectDelta->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectDelta, 1, 1, 1, 1);

        m_pLineEdtDelta = new QLineEdit(PageFractureInversion);
        m_pLineEdtDelta->setObjectName(QString::fromUtf8("m_pLineEdtDelta"));
        m_pLineEdtDelta->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtDelta, 1, 2, 1, 1);

        label_3 = new QLabel(PageFractureInversion);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_pBtnSelectGamma = new QToolButton(PageFractureInversion);
        m_pBtnSelectGamma->setObjectName(QString::fromUtf8("m_pBtnSelectGamma"));
        m_pBtnSelectGamma->setMinimumSize(QSize(30, 0));
        m_pBtnSelectGamma->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectGamma->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectGamma, 2, 1, 1, 1);

        m_pLineEdtGamma = new QLineEdit(PageFractureInversion);
        m_pLineEdtGamma->setObjectName(QString::fromUtf8("m_pLineEdtGamma"));
        m_pLineEdtGamma->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtGamma, 2, 2, 1, 1);

        label_7 = new QLabel(PageFractureInversion);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        m_pBtnSelectAzimuth = new QToolButton(PageFractureInversion);
        m_pBtnSelectAzimuth->setObjectName(QString::fromUtf8("m_pBtnSelectAzimuth"));
        m_pBtnSelectAzimuth->setMinimumSize(QSize(30, 0));
        m_pBtnSelectAzimuth->setMaximumSize(QSize(16777215, 16777215));
        m_pBtnSelectAzimuth->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectAzimuth, 3, 1, 1, 1);

        m_pLineEdtAzimuth = new QLineEdit(PageFractureInversion);
        m_pLineEdtAzimuth->setObjectName(QString::fromUtf8("m_pLineEdtAzimuth"));
        m_pLineEdtAzimuth->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtAzimuth, 3, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 2);

        label_6 = new QLabel(PageFractureInversion);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(130, 16777215));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        m_pTable = new QTableWidget(PageFractureInversion);
        if (m_pTable->columnCount() < 3)
            m_pTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        m_pTable->setObjectName(QString::fromUtf8("m_pTable"));
        m_pTable->setMinimumSize(QSize(0, 300));
        m_pTable->setMaximumSize(QSize(16777215, 16777215));
        m_pTable->horizontalHeader()->setDefaultSectionSize(150);
        m_pTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout_2->addWidget(m_pTable, 2, 0, 1, 2);

        horizontalSpacer_5 = new QSpacerItem(531, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        m_pPushBtnLoadPara = new QPushButton(PageFractureInversion);
        m_pPushBtnLoadPara->setObjectName(QString::fromUtf8("m_pPushBtnLoadPara"));
        m_pPushBtnLoadPara->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(m_pPushBtnLoadPara, 3, 1, 1, 1);


        retranslateUi(PageFractureInversion);

        QMetaObject::connectSlotsByName(PageFractureInversion);
    } // setupUi

    void retranslateUi(QWidget *PageFractureInversion)
    {
        PageFractureInversion->setWindowTitle(QCoreApplication::translate("PageFractureInversion", "Form", nullptr));
        label->setText(QCoreApplication::translate("PageFractureInversion", "Select \311\233 Thomsen parameter", nullptr));
        m_pBtnSelectEpsilon->setText(QCoreApplication::translate("PageFractureInversion", "...", nullptr));
        label_2->setText(QCoreApplication::translate("PageFractureInversion", "Select \316\264 Thomsen parameter", nullptr));
        m_pBtnSelectDelta->setText(QCoreApplication::translate("PageFractureInversion", "...", nullptr));
        label_3->setText(QCoreApplication::translate("PageFractureInversion", "Select \316\263 Thomsen parameter", nullptr));
        m_pBtnSelectGamma->setText(QCoreApplication::translate("PageFractureInversion", "...", nullptr));
        label_7->setText(QCoreApplication::translate("PageFractureInversion", "<html><head/><body><p>Select Azimuth of Symmetry Axis </p></body></html>", nullptr));
        m_pBtnSelectAzimuth->setText(QCoreApplication::translate("PageFractureInversion", "...", nullptr));
        label_6->setText(QCoreApplication::translate("PageFractureInversion", "Select Wavelet Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PageFractureInversion", "Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PageFractureInversion", "Incidence Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_pTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PageFractureInversion", "Wavelet", nullptr));
#if QT_CONFIG(tooltip)
        m_pPushBtnLoadPara->setToolTip(QCoreApplication::translate("PageFractureInversion", "Please select an item on the tree to copy its parameter here.", nullptr));
#endif // QT_CONFIG(tooltip)
        m_pPushBtnLoadPara->setText(QCoreApplication::translate("PageFractureInversion", "Load Parameter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageFractureInversion: public Ui_PageFractureInversion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGFRACTUREINVERSIONONE_H
