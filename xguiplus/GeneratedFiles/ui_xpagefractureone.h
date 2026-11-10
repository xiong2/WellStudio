/********************************************************************************
** Form generated from reading UI file 'xpagefractureone.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEFRACTUREONE_H
#define UI_XPAGEFRACTUREONE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageFractureOne
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QToolButton *m_pBtnSelectDV;
    QLineEdit *m_pLineEdtDV;
    QLabel *label_3;
    QLineEdit *m_pLineEdtAzi;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pBtnAdd;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QFrame *line;
    QTableWidget *m_pTable;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PageFractureOne)
    {
        if (PageFractureOne->objectName().isEmpty())
            PageFractureOne->setObjectName(QString::fromUtf8("PageFractureOne"));
        PageFractureOne->resize(622, 368);
        gridLayout_2 = new QGridLayout(PageFractureOne);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(PageFractureOne);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        m_pBtnSelectDV = new QToolButton(groupBox);
        m_pBtnSelectDV->setObjectName(QString::fromUtf8("m_pBtnSelectDV"));
        m_pBtnSelectDV->setMinimumSize(QSize(30, 0));
        m_pBtnSelectDV->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnSelectDV->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectDV, 0, 2, 1, 1);

        m_pLineEdtDV = new QLineEdit(groupBox);
        m_pLineEdtDV->setObjectName(QString::fromUtf8("m_pLineEdtDV"));
        m_pLineEdtDV->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtDV, 0, 3, 1, 3);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        m_pLineEdtAzi = new QLineEdit(groupBox);
        m_pLineEdtAzi->setObjectName(QString::fromUtf8("m_pLineEdtAzi"));
        m_pLineEdtAzi->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtAzi, 1, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(329, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 1, 1);

        m_pBtnAdd = new QPushButton(groupBox);
        m_pBtnAdd->setObjectName(QString::fromUtf8("m_pBtnAdd"));
        m_pBtnAdd->setMaximumSize(QSize(60, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnAdd->setIcon(icon1);

        gridLayout->addWidget(m_pBtnAdd, 1, 5, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 9, -1, -1);
        label_6 = new QLabel(PageFractureOne);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(label_6);

        line = new QFrame(PageFractureOne);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        m_pTable = new QTableWidget(PageFractureOne);
        if (m_pTable->columnCount() < 2)
            m_pTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        m_pTable->setObjectName(QString::fromUtf8("m_pTable"));
        m_pTable->setMinimumSize(QSize(0, 100));
        m_pTable->setMaximumSize(QSize(16777215, 16777215));
        m_pTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout_2->addWidget(m_pTable, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 29, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);


        retranslateUi(PageFractureOne);

        QMetaObject::connectSlotsByName(PageFractureOne);
    } // setupUi

    void retranslateUi(QWidget *PageFractureOne)
    {
        PageFractureOne->setWindowTitle(QCoreApplication::translate("PageFractureOne", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageFractureOne", "Add One Angle Dataset", nullptr));
        label->setText(QCoreApplication::translate("PageFractureOne", "Select Seismic Data", nullptr));
        m_pBtnSelectDV->setText(QCoreApplication::translate("PageFractureOne", "...", nullptr));
        label_3->setText(QCoreApplication::translate("PageFractureOne", "Azimuth", nullptr));
        m_pLineEdtAzi->setText(QCoreApplication::translate("PageFractureOne", "0", nullptr));
        label_4->setText(QCoreApplication::translate("PageFractureOne", "deg.", nullptr));
        m_pBtnAdd->setText(QCoreApplication::translate("PageFractureOne", "Add", nullptr));
        label_6->setText(QCoreApplication::translate("PageFractureOne", "Selected Datasets", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PageFractureOne", "Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PageFractureOne", "Seismic Data Volume", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageFractureOne: public Ui_PageFractureOne {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEFRACTUREONE_H
