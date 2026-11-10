/********************************************************************************
** Form generated from reading UI file 'xpage3termavoinversiononeext.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGE3TERMAVOINVERSIONONEEXT_H
#define UI_XPAGE3TERMAVOINVERSIONONEEXT_H

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

class Ui_Page3TermAvoInversionOneExt
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *m_pPushBtnLoadPara;
    QSpacerItem *horizontalSpacer_5;
    QTableWidget *m_pTable;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QFrame *line;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QToolButton *m_pBtnSelectDV;
    QLineEdit *m_pLineEdtDV;
    QLabel *label_5;
    QComboBox *m_pCombDataSource;
    QToolButton *m_pBtnSelectWavelet;
    QPushButton *m_pBtnBrowse;
    QLineEdit *m_pLineEdtWavelet;
    QLabel *label_3;
    QLineEdit *m_pLineEdtAngle;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *m_pBtnAdd;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Page3TermAvoInversionOneExt)
    {
        if (Page3TermAvoInversionOneExt->objectName().isEmpty())
            Page3TermAvoInversionOneExt->setObjectName(QString::fromUtf8("Page3TermAvoInversionOneExt"));
        Page3TermAvoInversionOneExt->resize(646, 392);
        gridLayout_2 = new QGridLayout(Page3TermAvoInversionOneExt);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pPushBtnLoadPara = new QPushButton(Page3TermAvoInversionOneExt);
        m_pPushBtnLoadPara->setObjectName(QString::fromUtf8("m_pPushBtnLoadPara"));
        m_pPushBtnLoadPara->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(m_pPushBtnLoadPara, 3, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(519, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        m_pTable = new QTableWidget(Page3TermAvoInversionOneExt);
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
        m_pTable->horizontalHeader()->setDefaultSectionSize(150);
        m_pTable->horizontalHeader()->setStretchLastSection(true);
        m_pTable->verticalHeader()->setCascadingSectionResizes(false);

        gridLayout_2->addWidget(m_pTable, 2, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 9, -1, -1);
        label_6 = new QLabel(Page3TermAvoInversionOneExt);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(label_6);

        line = new QFrame(Page3TermAvoInversionOneExt);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        groupBox = new QGroupBox(Page3TermAvoInversionOneExt);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 3);

        m_pBtnSelectDV = new QToolButton(groupBox);
        m_pBtnSelectDV->setObjectName(QString::fromUtf8("m_pBtnSelectDV"));
        m_pBtnSelectDV->setMinimumSize(QSize(30, 0));
        m_pBtnSelectDV->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/18804.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnSelectDV->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectDV, 0, 3, 1, 1);

        m_pLineEdtDV = new QLineEdit(groupBox);
        m_pLineEdtDV->setObjectName(QString::fromUtf8("m_pLineEdtDV"));
        m_pLineEdtDV->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtDV, 0, 4, 1, 8);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 2);

        m_pCombDataSource = new QComboBox(groupBox);
        m_pCombDataSource->addItem(QString());
        m_pCombDataSource->addItem(QString());
        m_pCombDataSource->setObjectName(QString::fromUtf8("m_pCombDataSource"));

        gridLayout->addWidget(m_pCombDataSource, 1, 2, 1, 3);

        m_pBtnSelectWavelet = new QToolButton(groupBox);
        m_pBtnSelectWavelet->setObjectName(QString::fromUtf8("m_pBtnSelectWavelet"));
        m_pBtnSelectWavelet->setEnabled(false);
        m_pBtnSelectWavelet->setMaximumSize(QSize(30, 16777215));
        m_pBtnSelectWavelet->setIcon(icon);

        gridLayout->addWidget(m_pBtnSelectWavelet, 1, 5, 1, 1);

        m_pBtnBrowse = new QPushButton(groupBox);
        m_pBtnBrowse->setObjectName(QString::fromUtf8("m_pBtnBrowse"));

        gridLayout->addWidget(m_pBtnBrowse, 1, 6, 1, 2);

        m_pLineEdtWavelet = new QLineEdit(groupBox);
        m_pLineEdtWavelet->setObjectName(QString::fromUtf8("m_pLineEdtWavelet"));
        m_pLineEdtWavelet->setReadOnly(true);

        gridLayout->addWidget(m_pLineEdtWavelet, 1, 8, 1, 4);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_pLineEdtAngle = new QLineEdit(groupBox);
        m_pLineEdtAngle->setObjectName(QString::fromUtf8("m_pLineEdtAngle"));
        m_pLineEdtAngle->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(m_pLineEdtAngle, 2, 1, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 5, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 7, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(96, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 9, 1, 1);

        m_pBtnAdd = new QPushButton(groupBox);
        m_pBtnAdd->setObjectName(QString::fromUtf8("m_pBtnAdd"));
        m_pBtnAdd->setMaximumSize(QSize(60, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_pBtnAdd->setIcon(icon1);

        gridLayout->addWidget(m_pBtnAdd, 2, 10, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 11, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 2);


        retranslateUi(Page3TermAvoInversionOneExt);

        QMetaObject::connectSlotsByName(Page3TermAvoInversionOneExt);
    } // setupUi

    void retranslateUi(QWidget *Page3TermAvoInversionOneExt)
    {
        Page3TermAvoInversionOneExt->setWindowTitle(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Form", nullptr));
#if QT_CONFIG(tooltip)
        m_pPushBtnLoadPara->setToolTip(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Please select an item on the tree to copy its parameter here.", nullptr));
#endif // QT_CONFIG(tooltip)
        m_pPushBtnLoadPara->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Load Parameter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Seismic Data", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Angle", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_pTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Wavelet", nullptr));
        label_6->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Selected Datasets", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Add One Angle Dataset", nullptr));
        label->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Select Seismic Data", nullptr));
        m_pBtnSelectDV->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "...", nullptr));
        label_5->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Wavelet Source", nullptr));
        m_pCombDataSource->setItemText(0, QCoreApplication::translate("Page3TermAvoInversionOneExt", "Data File", nullptr));
        m_pCombDataSource->setItemText(1, QCoreApplication::translate("Page3TermAvoInversionOneExt", "From Project", nullptr));

        m_pBtnSelectWavelet->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "...", nullptr));
        m_pBtnBrowse->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Browse", nullptr));
        label_3->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Angle ", nullptr));
        m_pLineEdtAngle->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "0", nullptr));
        label_4->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "deg.", nullptr));
        m_pBtnAdd->setText(QCoreApplication::translate("Page3TermAvoInversionOneExt", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Page3TermAvoInversionOneExt: public Ui_Page3TermAvoInversionOneExt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGE3TERMAVOINVERSIONONEEXT_H
