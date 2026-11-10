/********************************************************************************
** Form generated from reading UI file 'xpage3termavoinversionone.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGE3TERMAVOINVERSIONONE_H
#define UI_XPAGE3TERMAVOINVERSIONONE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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

class Ui_Page3TermAvoInversionOne
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QToolButton *m_pBtnSelectDV;
    QLineEdit *m_pLineEdtDV;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QComboBox *m_pCmbPosition;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *m_pLineEdtAngle;
    QLineEdit *m_pLineEdtWavelet;
    QToolButton *m_pBtnSelectWavelet;
    QComboBox *m_pCombDataSource;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pBtnAdd;
    QLabel *label_5;
    QPushButton *m_pBtnBrowse;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QTableWidget *m_pTable;

    void setupUi(QWidget *Page3TermAvoInversionOne)
    {
        if (Page3TermAvoInversionOne->objectName().isEmpty())
            Page3TermAvoInversionOne->setObjectName(QString::fromUtf8("Page3TermAvoInversionOne"));
        Page3TermAvoInversionOne->resize(622, 408);
        gridLayout_2 = new QGridLayout(Page3TermAvoInversionOne);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 9, -1, 13);
        label = new QLabel(Page3TermAvoInversionOne);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        m_pBtnSelectDV = new QToolButton(Page3TermAvoInversionOne);
        m_pBtnSelectDV->setObjectName(QString::fromUtf8("m_pBtnSelectDV"));
        m_pBtnSelectDV->setMinimumSize(QSize(30, 0));
        m_pBtnSelectDV->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnSelectDV->setIcon(icon);

        horizontalLayout->addWidget(m_pBtnSelectDV);

        m_pLineEdtDV = new QLineEdit(Page3TermAvoInversionOne);
        m_pLineEdtDV->setObjectName(QString::fromUtf8("m_pLineEdtDV"));
        m_pLineEdtDV->setReadOnly(true);

        horizontalLayout->addWidget(m_pLineEdtDV);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        groupBox = new QGroupBox(Page3TermAvoInversionOne);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 9, -1, 9);
        m_pCmbPosition = new QComboBox(groupBox);
        m_pCmbPosition->addItem(QString());
        m_pCmbPosition->addItem(QString());
        m_pCmbPosition->addItem(QString());
        m_pCmbPosition->setObjectName(QString::fromUtf8("m_pCmbPosition"));
        m_pCmbPosition->setMinimumSize(QSize(60, 0));

        gridLayout->addWidget(m_pCmbPosition, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 8, 1, 1);

        m_pLineEdtAngle = new QLineEdit(groupBox);
        m_pLineEdtAngle->setObjectName(QString::fromUtf8("m_pLineEdtAngle"));
        m_pLineEdtAngle->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtAngle, 0, 4, 1, 1);

        m_pLineEdtWavelet = new QLineEdit(groupBox);
        m_pLineEdtWavelet->setObjectName(QString::fromUtf8("m_pLineEdtWavelet"));
        m_pLineEdtWavelet->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtWavelet, 1, 5, 1, 4);

        m_pBtnSelectWavelet = new QToolButton(groupBox);
        m_pBtnSelectWavelet->setObjectName(QString::fromUtf8("m_pBtnSelectWavelet"));
        m_pBtnSelectWavelet->setEnabled(true);
        m_pBtnSelectWavelet->setMaximumSize(QSize(30, 16777215));
        m_pBtnSelectWavelet->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectWavelet, 1, 3, 1, 1);

        m_pCombDataSource = new QComboBox(groupBox);
        m_pCombDataSource->addItem(QString());
        m_pCombDataSource->addItem(QString());
        m_pCombDataSource->setObjectName(QString::fromUtf8("m_pCombDataSource"));

        gridLayout->addWidget(m_pCombDataSource, 1, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 6, 1, 1);

        m_pBtnAdd = new QPushButton(groupBox);
        m_pBtnAdd->setObjectName(QString::fromUtf8("m_pBtnAdd"));
        m_pBtnAdd->setMaximumSize(QSize(60, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnAdd->setIcon(icon1);

        gridLayout->addWidget(m_pBtnAdd, 0, 7, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        m_pBtnBrowse = new QPushButton(groupBox);
        m_pBtnBrowse->setObjectName(QString::fromUtf8("m_pBtnBrowse"));

        gridLayout->addWidget(m_pBtnBrowse, 1, 4, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 9, -1, -1);
        label_6 = new QLabel(Page3TermAvoInversionOne);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(label_6);

        line = new QFrame(Page3TermAvoInversionOne);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 29, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 0, 1, 1);

        m_pTable = new QTableWidget(Page3TermAvoInversionOne);
        if (m_pTable->columnCount() < 3)
            m_pTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        m_pTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        m_pTable->setObjectName(QString::fromUtf8("m_pTable"));
        m_pTable->setMinimumSize(QSize(0, 100));
        m_pTable->setMaximumSize(QSize(16777215, 16777215));
        m_pTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout_2->addWidget(m_pTable, 3, 0, 1, 1);


        retranslateUi(Page3TermAvoInversionOne);

        QMetaObject::connectSlotsByName(Page3TermAvoInversionOne);
    } // setupUi

    void retranslateUi(QWidget *Page3TermAvoInversionOne)
    {
        Page3TermAvoInversionOne->setWindowTitle(QCoreApplication::translate("Page3TermAvoInversionOne", "Form", nullptr));
        label->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Select Seismic Data", nullptr));
        m_pBtnSelectDV->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Page3TermAvoInversionOne", "Add One Angle Dataset", nullptr));
        m_pCmbPosition->setItemText(0, QCoreApplication::translate("Page3TermAvoInversionOne", "1", nullptr));
        m_pCmbPosition->setItemText(1, QCoreApplication::translate("Page3TermAvoInversionOne", "2", nullptr));
        m_pCmbPosition->setItemText(2, QCoreApplication::translate("Page3TermAvoInversionOne", "3", nullptr));

        label_3->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Angle ", nullptr));
        label_2->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Angle Position", nullptr));
        m_pLineEdtAngle->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "0", nullptr));
        m_pBtnSelectWavelet->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "...", nullptr));
        m_pCombDataSource->setItemText(0, QCoreApplication::translate("Page3TermAvoInversionOne", "Data File", nullptr));
        m_pCombDataSource->setItemText(1, QCoreApplication::translate("Page3TermAvoInversionOne", "From Project", nullptr));

        label_4->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "deg.", nullptr));
        m_pBtnAdd->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Add", nullptr));
        label_5->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Wavelet Source", nullptr));
        m_pBtnBrowse->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Browse", nullptr));
        label_6->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Selected Datasets", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_pTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Page3TermAvoInversionOne", "Wavelet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Page3TermAvoInversionOne: public Ui_Page3TermAvoInversionOne {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGE3TERMAVOINVERSIONONE_H
