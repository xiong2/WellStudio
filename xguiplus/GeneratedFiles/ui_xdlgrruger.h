/********************************************************************************
** Form generated from reading UI file 'xdlgrruger.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGRRUGER_H
#define UI_XDLGRRUGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXDlgRruger
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *m_pGroupPara;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *m_pBoxTable0;
    QGridLayout *gridLayout;
    QTableWidget *m_pTable0;
    QPushButton *m_pBtnMore;
    QGroupBox *m_pBoxTable1;
    QGridLayout *gridLayout_2;
    QTableWidget *m_pTable1;
    QGroupBox *m_pBoxTable2;
    QGridLayout *gridLayout_3;
    QTableWidget *m_pTable2;
    QPushButton *m_pBtnLess;
    QGroupBox *m_pGroupDisplay;
    QFormLayout *formLayout;
    QLabel *m_pLabelAzimuth;
    QTableWidget *m_pTableAzimuth;
    QLabel *m_pLabelIncident;
    QTableWidget *m_pTableIncident;
    QHBoxLayout *m_pLayoutStdBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pBtnRun;
    QPushButton *m_pBtnClose;

    void setupUi(QDialog *CXDlgRruger)
    {
        if (CXDlgRruger->objectName().isEmpty())
            CXDlgRruger->setObjectName(QString::fromUtf8("CXDlgRruger"));
        CXDlgRruger->resize(556, 760);
        verticalLayout = new QVBoxLayout(CXDlgRruger);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pGroupPara = new QGroupBox(CXDlgRruger);
        m_pGroupPara->setObjectName(QString::fromUtf8("m_pGroupPara"));
        m_pGroupPara->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(m_pGroupPara);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_pBoxTable0 = new QGroupBox(m_pGroupPara);
        m_pBoxTable0->setObjectName(QString::fromUtf8("m_pBoxTable0"));
        m_pBoxTable0->setCheckable(true);
        gridLayout = new QGridLayout(m_pBoxTable0);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pTable0 = new QTableWidget(m_pBoxTable0);
        if (m_pTable0->columnCount() < 6)
            m_pTable0->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pTable0->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pTable0->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        m_pTable0->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QFont font1;
        font1.setPointSize(12);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font1);
        m_pTable0->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font1);
        m_pTable0->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        m_pTable0->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (m_pTable0->rowCount() < 2)
            m_pTable0->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        m_pTable0->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        m_pTable0->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        m_pTable0->setItem(0, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        m_pTable0->setItem(0, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        m_pTable0->setItem(0, 2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        m_pTable0->setItem(0, 3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        m_pTable0->setItem(0, 4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        m_pTable0->setItem(0, 5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        m_pTable0->setItem(1, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        m_pTable0->setItem(1, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        m_pTable0->setItem(1, 2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        m_pTable0->setItem(1, 3, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        m_pTable0->setItem(1, 4, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        m_pTable0->setItem(1, 5, __qtablewidgetitem19);
        m_pTable0->setObjectName(QString::fromUtf8("m_pTable0"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pTable0->sizePolicy().hasHeightForWidth());
        m_pTable0->setSizePolicy(sizePolicy);
        m_pTable0->setMaximumSize(QSize(16777215, 120));
        m_pTable0->horizontalHeader()->setDefaultSectionSize(75);

        gridLayout->addWidget(m_pTable0, 0, 0, 1, 1);


        verticalLayout_2->addWidget(m_pBoxTable0);

        m_pBtnMore = new QPushButton(m_pGroupPara);
        m_pBtnMore->setObjectName(QString::fromUtf8("m_pBtnMore"));

        verticalLayout_2->addWidget(m_pBtnMore);

        m_pBoxTable1 = new QGroupBox(m_pGroupPara);
        m_pBoxTable1->setObjectName(QString::fromUtf8("m_pBoxTable1"));
        m_pBoxTable1->setCheckable(true);
        m_pBoxTable1->setChecked(false);
        gridLayout_2 = new QGridLayout(m_pBoxTable1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pTable1 = new QTableWidget(m_pBoxTable1);
        if (m_pTable1->columnCount() < 6)
            m_pTable1->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        m_pTable1->setHorizontalHeaderItem(0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        m_pTable1->setHorizontalHeaderItem(1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setFont(font1);
        m_pTable1->setHorizontalHeaderItem(2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setFont(font1);
        m_pTable1->setHorizontalHeaderItem(3, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        __qtablewidgetitem24->setFont(font1);
        m_pTable1->setHorizontalHeaderItem(4, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        m_pTable1->setHorizontalHeaderItem(5, __qtablewidgetitem25);
        if (m_pTable1->rowCount() < 2)
            m_pTable1->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        m_pTable1->setVerticalHeaderItem(0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        m_pTable1->setVerticalHeaderItem(1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        m_pTable1->setItem(0, 0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        m_pTable1->setItem(0, 1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        m_pTable1->setItem(0, 2, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        m_pTable1->setItem(0, 3, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        m_pTable1->setItem(0, 4, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        m_pTable1->setItem(0, 5, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        m_pTable1->setItem(1, 0, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        m_pTable1->setItem(1, 1, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        m_pTable1->setItem(1, 2, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        m_pTable1->setItem(1, 3, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        m_pTable1->setItem(1, 4, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        m_pTable1->setItem(1, 5, __qtablewidgetitem39);
        m_pTable1->setObjectName(QString::fromUtf8("m_pTable1"));
        sizePolicy.setHeightForWidth(m_pTable1->sizePolicy().hasHeightForWidth());
        m_pTable1->setSizePolicy(sizePolicy);
        m_pTable1->setMaximumSize(QSize(16777215, 120));
        m_pTable1->setShowGrid(true);
        m_pTable1->horizontalHeader()->setDefaultSectionSize(75);

        gridLayout_2->addWidget(m_pTable1, 0, 0, 1, 1);


        verticalLayout_2->addWidget(m_pBoxTable1);

        m_pBoxTable2 = new QGroupBox(m_pGroupPara);
        m_pBoxTable2->setObjectName(QString::fromUtf8("m_pBoxTable2"));
        m_pBoxTable2->setCheckable(true);
        m_pBoxTable2->setChecked(false);
        gridLayout_3 = new QGridLayout(m_pBoxTable2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        m_pTable2 = new QTableWidget(m_pBoxTable2);
        if (m_pTable2->columnCount() < 6)
            m_pTable2->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        m_pTable2->setHorizontalHeaderItem(0, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        m_pTable2->setHorizontalHeaderItem(1, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        __qtablewidgetitem42->setFont(font1);
        m_pTable2->setHorizontalHeaderItem(2, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        __qtablewidgetitem43->setFont(font1);
        m_pTable2->setHorizontalHeaderItem(3, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        __qtablewidgetitem44->setFont(font1);
        m_pTable2->setHorizontalHeaderItem(4, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        m_pTable2->setHorizontalHeaderItem(5, __qtablewidgetitem45);
        if (m_pTable2->rowCount() < 2)
            m_pTable2->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        m_pTable2->setVerticalHeaderItem(0, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        m_pTable2->setVerticalHeaderItem(1, __qtablewidgetitem47);
        m_pTable2->setObjectName(QString::fromUtf8("m_pTable2"));
        sizePolicy.setHeightForWidth(m_pTable2->sizePolicy().hasHeightForWidth());
        m_pTable2->setSizePolicy(sizePolicy);
        m_pTable2->setMaximumSize(QSize(16777215, 120));
        m_pTable2->horizontalHeader()->setDefaultSectionSize(75);

        gridLayout_3->addWidget(m_pTable2, 0, 0, 1, 1);


        verticalLayout_2->addWidget(m_pBoxTable2);

        m_pBtnLess = new QPushButton(m_pGroupPara);
        m_pBtnLess->setObjectName(QString::fromUtf8("m_pBtnLess"));

        verticalLayout_2->addWidget(m_pBtnLess);


        verticalLayout->addWidget(m_pGroupPara);

        m_pGroupDisplay = new QGroupBox(CXDlgRruger);
        m_pGroupDisplay->setObjectName(QString::fromUtf8("m_pGroupDisplay"));
        m_pGroupDisplay->setFlat(true);
        formLayout = new QFormLayout(m_pGroupDisplay);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        m_pLabelAzimuth = new QLabel(m_pGroupDisplay);
        m_pLabelAzimuth->setObjectName(QString::fromUtf8("m_pLabelAzimuth"));

        formLayout->setWidget(0, QFormLayout::LabelRole, m_pLabelAzimuth);

        m_pTableAzimuth = new QTableWidget(m_pGroupDisplay);
        if (m_pTableAzimuth->columnCount() < 3)
            m_pTableAzimuth->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        m_pTableAzimuth->setHorizontalHeaderItem(0, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        m_pTableAzimuth->setHorizontalHeaderItem(1, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        m_pTableAzimuth->setHorizontalHeaderItem(2, __qtablewidgetitem50);
        if (m_pTableAzimuth->rowCount() < 2)
            m_pTableAzimuth->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        m_pTableAzimuth->setVerticalHeaderItem(0, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        m_pTableAzimuth->setVerticalHeaderItem(1, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        m_pTableAzimuth->setItem(0, 0, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        m_pTableAzimuth->setItem(0, 1, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        m_pTableAzimuth->setItem(0, 2, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        m_pTableAzimuth->setItem(1, 0, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        m_pTableAzimuth->setItem(1, 1, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        __qtablewidgetitem58->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        m_pTableAzimuth->setItem(1, 2, __qtablewidgetitem58);
        m_pTableAzimuth->setObjectName(QString::fromUtf8("m_pTableAzimuth"));
        m_pTableAzimuth->setMaximumSize(QSize(16777215, 120));
        m_pTableAzimuth->horizontalHeader()->setDefaultSectionSize(60);

        formLayout->setWidget(1, QFormLayout::LabelRole, m_pTableAzimuth);

        m_pLabelIncident = new QLabel(m_pGroupDisplay);
        m_pLabelIncident->setObjectName(QString::fromUtf8("m_pLabelIncident"));

        formLayout->setWidget(0, QFormLayout::FieldRole, m_pLabelIncident);

        m_pTableIncident = new QTableWidget(m_pGroupDisplay);
        if (m_pTableIncident->columnCount() < 3)
            m_pTableIncident->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        m_pTableIncident->setHorizontalHeaderItem(0, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        m_pTableIncident->setHorizontalHeaderItem(1, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        m_pTableIncident->setHorizontalHeaderItem(2, __qtablewidgetitem61);
        if (m_pTableIncident->rowCount() < 2)
            m_pTableIncident->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        m_pTableIncident->setVerticalHeaderItem(0, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        m_pTableIncident->setVerticalHeaderItem(1, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        m_pTableIncident->setItem(0, 0, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        m_pTableIncident->setItem(0, 1, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        m_pTableIncident->setItem(0, 2, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        m_pTableIncident->setItem(1, 0, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        m_pTableIncident->setItem(1, 1, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        __qtablewidgetitem69->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        m_pTableIncident->setItem(1, 2, __qtablewidgetitem69);
        m_pTableIncident->setObjectName(QString::fromUtf8("m_pTableIncident"));
        m_pTableIncident->setMaximumSize(QSize(16777215, 120));
        m_pTableIncident->horizontalHeader()->setDefaultSectionSize(60);

        formLayout->setWidget(1, QFormLayout::FieldRole, m_pTableIncident);


        verticalLayout->addWidget(m_pGroupDisplay);

        m_pLayoutStdBtn = new QHBoxLayout();
        m_pLayoutStdBtn->setSpacing(6);
        m_pLayoutStdBtn->setObjectName(QString::fromUtf8("m_pLayoutStdBtn"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_pLayoutStdBtn->addItem(horizontalSpacer);

        m_pBtnRun = new QPushButton(CXDlgRruger);
        m_pBtnRun->setObjectName(QString::fromUtf8("m_pBtnRun"));

        m_pLayoutStdBtn->addWidget(m_pBtnRun);

        m_pBtnClose = new QPushButton(CXDlgRruger);
        m_pBtnClose->setObjectName(QString::fromUtf8("m_pBtnClose"));

        m_pLayoutStdBtn->addWidget(m_pBtnClose);


        verticalLayout->addLayout(m_pLayoutStdBtn);


        retranslateUi(CXDlgRruger);
        QObject::connect(m_pBtnMore, SIGNAL(clicked()), m_pBtnMore, SLOT(hide()));
        QObject::connect(m_pBtnMore, SIGNAL(clicked()), m_pBoxTable1, SLOT(show()));
        QObject::connect(m_pBtnMore, SIGNAL(clicked()), m_pBoxTable2, SLOT(show()));
        QObject::connect(m_pBtnMore, SIGNAL(clicked()), m_pBtnLess, SLOT(show()));
        QObject::connect(m_pBtnLess, SIGNAL(clicked()), m_pBtnLess, SLOT(hide()));
        QObject::connect(m_pBtnLess, SIGNAL(clicked()), m_pBoxTable1, SLOT(hide()));
        QObject::connect(m_pBtnLess, SIGNAL(clicked()), m_pBoxTable2, SLOT(hide()));
        QObject::connect(m_pBtnLess, SIGNAL(clicked()), m_pBtnMore, SLOT(show()));

        QMetaObject::connectSlotsByName(CXDlgRruger);
    } // setupUi

    void retranslateUi(QDialog *CXDlgRruger)
    {
        CXDlgRruger->setWindowTitle(QCoreApplication::translate("CXDlgRruger", "Anisotropic (HTI) PP Reflection Coefficient Forwarding (Base on Ruger approximation)", nullptr));
        m_pGroupPara->setTitle(QCoreApplication::translate("CXDlgRruger", "Parameter setting", nullptr));
        m_pBoxTable0->setTitle(QCoreApplication::translate("CXDlgRruger", "First data set", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTable0->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CXDlgRruger", "Vp-fast", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTable0->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CXDlgRruger", "Vs-fast", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = m_pTable0->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CXDlgRruger", "\316\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = m_pTable0->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CXDlgRruger", "\316\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = m_pTable0->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CXDlgRruger", "\316\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = m_pTable0->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("CXDlgRruger", "Density", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = m_pTable0->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("CXDlgRruger", "Up", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = m_pTable0->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("CXDlgRruger", "Down", nullptr));

        const bool __sortingEnabled = m_pTable0->isSortingEnabled();
        m_pTable0->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem8 = m_pTable0->item(0, 0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("CXDlgRruger", "4338", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = m_pTable0->item(0, 1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("CXDlgRruger", "2370", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = m_pTable0->item(0, 2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = m_pTable0->item(0, 3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = m_pTable0->item(0, 4);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = m_pTable0->item(0, 5);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("CXDlgRruger", "2424", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = m_pTable0->item(1, 0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("CXDlgRruger", "5716.546", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = m_pTable0->item(1, 1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("CXDlgRruger", "3143.055", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = m_pTable0->item(1, 2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("CXDlgRruger", "-0.2323", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = m_pTable0->item(1, 3);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("CXDlgRruger", "-0.1312", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = m_pTable0->item(1, 4);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("CXDlgRruger", "-0.2327", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = m_pTable0->item(1, 5);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("CXDlgRruger", "2614.65", nullptr));
        m_pTable0->setSortingEnabled(__sortingEnabled);

        m_pBtnMore->setText(QCoreApplication::translate("CXDlgRruger", "More...", nullptr));
        m_pBoxTable1->setTitle(QCoreApplication::translate("CXDlgRruger", "Second data set", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = m_pTable1->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("CXDlgRruger", "Vp-fast", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = m_pTable1->horizontalHeaderItem(1);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("CXDlgRruger", "Vs-fast", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = m_pTable1->horizontalHeaderItem(2);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("CXDlgRruger", "\316\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = m_pTable1->horizontalHeaderItem(3);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("CXDlgRruger", "\316\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = m_pTable1->horizontalHeaderItem(4);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("CXDlgRruger", "\316\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = m_pTable1->horizontalHeaderItem(5);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("CXDlgRruger", "Density", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = m_pTable1->verticalHeaderItem(0);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("CXDlgRruger", "Up", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = m_pTable1->verticalHeaderItem(1);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("CXDlgRruger", "Down", nullptr));

        const bool __sortingEnabled1 = m_pTable1->isSortingEnabled();
        m_pTable1->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem28 = m_pTable1->item(0, 0);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("CXDlgRruger", "4338", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = m_pTable1->item(0, 1);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("CXDlgRruger", "2370", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = m_pTable1->item(0, 2);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = m_pTable1->item(0, 3);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = m_pTable1->item(0, 4);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = m_pTable1->item(0, 5);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("CXDlgRruger", "2424", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = m_pTable1->item(1, 0);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("CXDlgRruger", "3740.215", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = m_pTable1->item(1, 1);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("CXDlgRruger", "2115.559", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = m_pTable1->item(1, 2);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("CXDlgRruger", "-0.2462", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = m_pTable1->item(1, 3);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("CXDlgRruger", "-0.1407", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = m_pTable1->item(1, 4);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("CXDlgRruger", "-0.2208", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = m_pTable1->item(1, 5);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("CXDlgRruger", "2177.90", nullptr));
        m_pTable1->setSortingEnabled(__sortingEnabled1);

        m_pBoxTable2->setTitle(QCoreApplication::translate("CXDlgRruger", "Third data set", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = m_pTable2->horizontalHeaderItem(0);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("CXDlgRruger", "Vp-fast", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = m_pTable2->horizontalHeaderItem(1);
        ___qtablewidgetitem41->setText(QCoreApplication::translate("CXDlgRruger", "Vs-fast", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = m_pTable2->horizontalHeaderItem(2);
        ___qtablewidgetitem42->setText(QCoreApplication::translate("CXDlgRruger", "\316\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = m_pTable2->horizontalHeaderItem(3);
        ___qtablewidgetitem43->setText(QCoreApplication::translate("CXDlgRruger", "\316\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = m_pTable2->horizontalHeaderItem(4);
        ___qtablewidgetitem44->setText(QCoreApplication::translate("CXDlgRruger", "\316\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = m_pTable2->horizontalHeaderItem(5);
        ___qtablewidgetitem45->setText(QCoreApplication::translate("CXDlgRruger", "Density", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = m_pTable2->verticalHeaderItem(0);
        ___qtablewidgetitem46->setText(QCoreApplication::translate("CXDlgRruger", "Up", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = m_pTable2->verticalHeaderItem(1);
        ___qtablewidgetitem47->setText(QCoreApplication::translate("CXDlgRruger", "Down", nullptr));
        m_pBtnLess->setText(QCoreApplication::translate("CXDlgRruger", "Less...", nullptr));
        m_pGroupDisplay->setTitle(QCoreApplication::translate("CXDlgRruger", "Display setting", nullptr));
        m_pLabelAzimuth->setText(QCoreApplication::translate("CXDlgRruger", "RC with azimuth in different incident", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = m_pTableAzimuth->horizontalHeaderItem(0);
        ___qtablewidgetitem48->setText(QCoreApplication::translate("CXDlgRruger", "Start", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = m_pTableAzimuth->horizontalHeaderItem(1);
        ___qtablewidgetitem49->setText(QCoreApplication::translate("CXDlgRruger", "End", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = m_pTableAzimuth->horizontalHeaderItem(2);
        ___qtablewidgetitem50->setText(QCoreApplication::translate("CXDlgRruger", "interval", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = m_pTableAzimuth->verticalHeaderItem(0);
        ___qtablewidgetitem51->setText(QCoreApplication::translate("CXDlgRruger", "Incident", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = m_pTableAzimuth->verticalHeaderItem(1);
        ___qtablewidgetitem52->setText(QCoreApplication::translate("CXDlgRruger", "Azimuth", nullptr));

        const bool __sortingEnabled2 = m_pTableAzimuth->isSortingEnabled();
        m_pTableAzimuth->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem53 = m_pTableAzimuth->item(0, 0);
        ___qtablewidgetitem53->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = m_pTableAzimuth->item(0, 1);
        ___qtablewidgetitem54->setText(QCoreApplication::translate("CXDlgRruger", "40", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = m_pTableAzimuth->item(0, 2);
        ___qtablewidgetitem55->setText(QCoreApplication::translate("CXDlgRruger", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = m_pTableAzimuth->item(1, 0);
        ___qtablewidgetitem56->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem57 = m_pTableAzimuth->item(1, 1);
        ___qtablewidgetitem57->setText(QCoreApplication::translate("CXDlgRruger", "350", nullptr));
        QTableWidgetItem *___qtablewidgetitem58 = m_pTableAzimuth->item(1, 2);
        ___qtablewidgetitem58->setText(QCoreApplication::translate("CXDlgRruger", "1", nullptr));
        m_pTableAzimuth->setSortingEnabled(__sortingEnabled2);

        m_pLabelIncident->setText(QCoreApplication::translate("CXDlgRruger", "RC with incident in different azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem59 = m_pTableIncident->horizontalHeaderItem(0);
        ___qtablewidgetitem59->setText(QCoreApplication::translate("CXDlgRruger", "Start", nullptr));
        QTableWidgetItem *___qtablewidgetitem60 = m_pTableIncident->horizontalHeaderItem(1);
        ___qtablewidgetitem60->setText(QCoreApplication::translate("CXDlgRruger", "End", nullptr));
        QTableWidgetItem *___qtablewidgetitem61 = m_pTableIncident->horizontalHeaderItem(2);
        ___qtablewidgetitem61->setText(QCoreApplication::translate("CXDlgRruger", "interval", nullptr));
        QTableWidgetItem *___qtablewidgetitem62 = m_pTableIncident->verticalHeaderItem(0);
        ___qtablewidgetitem62->setText(QCoreApplication::translate("CXDlgRruger", "Azimuth", nullptr));
        QTableWidgetItem *___qtablewidgetitem63 = m_pTableIncident->verticalHeaderItem(1);
        ___qtablewidgetitem63->setText(QCoreApplication::translate("CXDlgRruger", "Incident", nullptr));

        const bool __sortingEnabled3 = m_pTableIncident->isSortingEnabled();
        m_pTableIncident->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem64 = m_pTableIncident->item(0, 0);
        ___qtablewidgetitem64->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem65 = m_pTableIncident->item(0, 1);
        ___qtablewidgetitem65->setText(QCoreApplication::translate("CXDlgRruger", "350", nullptr));
        QTableWidgetItem *___qtablewidgetitem66 = m_pTableIncident->item(0, 2);
        ___qtablewidgetitem66->setText(QCoreApplication::translate("CXDlgRruger", "50", nullptr));
        QTableWidgetItem *___qtablewidgetitem67 = m_pTableIncident->item(1, 0);
        ___qtablewidgetitem67->setText(QCoreApplication::translate("CXDlgRruger", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem68 = m_pTableIncident->item(1, 1);
        ___qtablewidgetitem68->setText(QCoreApplication::translate("CXDlgRruger", "40", nullptr));
        QTableWidgetItem *___qtablewidgetitem69 = m_pTableIncident->item(1, 2);
        ___qtablewidgetitem69->setText(QCoreApplication::translate("CXDlgRruger", "1", nullptr));
        m_pTableIncident->setSortingEnabled(__sortingEnabled3);

        m_pBtnRun->setText(QCoreApplication::translate("CXDlgRruger", "Run", nullptr));
        m_pBtnClose->setText(QCoreApplication::translate("CXDlgRruger", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlgRruger: public Ui_CXDlgRruger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGRRUGER_H
