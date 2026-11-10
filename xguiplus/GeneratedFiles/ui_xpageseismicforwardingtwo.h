/********************************************************************************
** Form generated from reading UI file 'xpageseismicforwardingtwo.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGESEISMICFORWARDINGTWO_H
#define UI_XPAGESEISMICFORWARDINGTWO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageSeismicForwardingTwo
{
public:
    QGridLayout *gridLayout;
    QLabel *label_12;
    QFrame *line;
    QTableWidget *m_pTable;
    QLabel *label_11;
    QLineEdit *m_pLineEdtScalingFactor;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PageSeismicForwardingTwo)
    {
        if (PageSeismicForwardingTwo->objectName().isEmpty())
            PageSeismicForwardingTwo->setObjectName(QString::fromUtf8("PageSeismicForwardingTwo"));
        PageSeismicForwardingTwo->resize(741, 406);
        gridLayout = new QGridLayout(PageSeismicForwardingTwo);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_12 = new QLabel(PageSeismicForwardingTwo);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 0, 0, 1, 1);

        line = new QFrame(PageSeismicForwardingTwo);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 1, 1, 3);

        m_pTable = new QTableWidget(PageSeismicForwardingTwo);
        if (m_pTable->columnCount() < 3)
            m_pTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        m_pTable->setObjectName(QString::fromUtf8("m_pTable"));
        m_pTable->horizontalHeader()->setCascadingSectionResizes(true);
        m_pTable->horizontalHeader()->setMinimumSectionSize(50);
        m_pTable->horizontalHeader()->setDefaultSectionSize(200);
        m_pTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(m_pTable, 1, 0, 1, 4);

        label_11 = new QLabel(PageSeismicForwardingTwo);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 2, 0, 1, 2);

        m_pLineEdtScalingFactor = new QLineEdit(PageSeismicForwardingTwo);
        m_pLineEdtScalingFactor->setObjectName(QString::fromUtf8("m_pLineEdtScalingFactor"));
        m_pLineEdtScalingFactor->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(m_pLineEdtScalingFactor, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(426, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 3, 1, 1);


        retranslateUi(PageSeismicForwardingTwo);

        QMetaObject::connectSlotsByName(PageSeismicForwardingTwo);
    } // setupUi

    void retranslateUi(QWidget *PageSeismicForwardingTwo)
    {
        PageSeismicForwardingTwo->setWindowTitle(QCoreApplication::translate("PageSeismicForwardingTwo", "Form", nullptr));
        label_12->setText(QCoreApplication::translate("PageSeismicForwardingTwo", "Select Wavelets", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PageSeismicForwardingTwo", "Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PageSeismicForwardingTwo", "Incidence Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_pTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PageSeismicForwardingTwo", "Wavelet", nullptr));
        label_11->setText(QCoreApplication::translate("PageSeismicForwardingTwo", "Wavelet Scaling Factor", nullptr));
        m_pLineEdtScalingFactor->setText(QCoreApplication::translate("PageSeismicForwardingTwo", "10000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageSeismicForwardingTwo: public Ui_PageSeismicForwardingTwo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGESEISMICFORWARDINGTWO_H
