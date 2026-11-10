/********************************************************************************
** Form generated from reading UI file 'xshowtemplates.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XSHOWTEMPLATES_H
#define UI_XSHOWTEMPLATES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowTemplatesClass
{
public:
    QAction *actionSUS;
    QAction *actionExit;
    QAction *actionSave;
    QAction *actionReset;
    QAction *actionNew;
    QAction *actionDelete;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *m_pTabContinuous;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditName;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_13;
    QLineEdit *lineEditFullName;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_14;
    QLineEdit *lineEditType;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QLineEdit *lineEditUnitM;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_4;
    QLineEdit *lineEditUnitI;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEditDataMinM;
    QLabel *label_5;
    QLineEdit *lineEditDataMaxM;
    QSpacerItem *horizontalSpacer;
    QLabel *label_9;
    QLineEdit *lineEditDspMinM;
    QLabel *label_10;
    QLineEdit *lineEditDspMaxM;
    QLabel *label_6;
    QLineEdit *lineEditDataMinI;
    QLabel *label_7;
    QLineEdit *lineEditDataMaxI;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_12;
    QLineEdit *lineEditDspMinI;
    QLabel *label_11;
    QLineEdit *lineEditDspMaxI;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QLabel *label_15;
    QComboBox *comboBoxIcon;
    QLabel *label_8;
    QLineEdit *lineEditAlias;
    QWidget *m_pTabDiscrete;
    QGridLayout *gridLayout_5;
    QTableView *m_pTableViewDiscrete;
    QGridLayout *gridLayout_4;
    QLabel *label_20;
    QLineEdit *m_pEdtDiscreteFullName;
    QLineEdit *m_pEdtDiscreteMetricUnit;
    QLineEdit *m_pEdtDiscreteName;
    QLabel *label_17;
    QLabel *label_16;
    QLineEdit *m_pEdtDiscreteType;
    QLineEdit *m_pEdtDiscreteImperialUnit;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *m_pEdtDiscreteIcon;
    QLineEdit *m_pEdtDiscreteAlias;
    QGroupBox *gbxDiscreteProperties;
    QGridLayout *gridLayout_2;
    QPushButton *m_pBtnPropertyNew;
    QPushButton *m_pBtnPropertyDelete;
    QTableWidget *m_pTableProperties;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *ShowTemplatesClass)
    {
        if (ShowTemplatesClass->objectName().isEmpty())
            ShowTemplatesClass->setObjectName(QString::fromUtf8("ShowTemplatesClass"));
        ShowTemplatesClass->resize(1263, 677);
        actionSUS = new QAction(ShowTemplatesClass);
        actionSUS->setObjectName(QString::fromUtf8("actionSUS"));
        actionSUS->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Metric.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSUS->setIcon(icon);
        actionExit = new QAction(ShowTemplatesClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Exit24x24.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/Icon/Exit.png"), QSize(), QIcon::Normal, QIcon::On);
        actionExit->setIcon(icon1);
        actionSave = new QAction(ShowTemplatesClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/Save24x24.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/Icon/Save32.png"), QSize(), QIcon::Normal, QIcon::On);
        actionSave->setIcon(icon2);
        actionReset = new QAction(ShowTemplatesClass);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionReset->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/Reload24x24.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/Icon/Reset.png"), QSize(), QIcon::Normal, QIcon::On);
        actionReset->setIcon(icon3);
        actionNew = new QAction(ShowTemplatesClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/New24x24.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/Icon/New32.png"), QSize(), QIcon::Normal, QIcon::On);
        actionNew->setIcon(icon4);
        actionDelete = new QAction(ShowTemplatesClass);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/Delete24x24.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon5);
        centralWidget = new QWidget(ShowTemplatesClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        m_pTabContinuous = new QWidget();
        m_pTabContinuous->setObjectName(QString::fromUtf8("m_pTabContinuous"));
        verticalLayout = new QVBoxLayout(m_pTabContinuous);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new QTableView(m_pTabContinuous);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        groupBox = new QGroupBox(m_pTabContinuous);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEditName = new QLineEdit(groupBox);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditName->sizePolicy().hasHeightForWidth());
        lineEditName->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEditName);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_13);

        lineEditFullName = new QLineEdit(groupBox);
        lineEditFullName->setObjectName(QString::fromUtf8("lineEditFullName"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditFullName->sizePolicy().hasHeightForWidth());
        lineEditFullName->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(lineEditFullName);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_2->addWidget(label_14);

        lineEditType = new QLineEdit(groupBox);
        lineEditType->setObjectName(QString::fromUtf8("lineEditType"));
        sizePolicy.setHeightForWidth(lineEditType->sizePolicy().hasHeightForWidth());
        lineEditType->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEditType);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEditUnitM = new QLineEdit(groupBox);
        lineEditUnitM->setObjectName(QString::fromUtf8("lineEditUnitM"));
        sizePolicy.setHeightForWidth(lineEditUnitM->sizePolicy().hasHeightForWidth());
        lineEditUnitM->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEditUnitM);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEditUnitI = new QLineEdit(groupBox);
        lineEditUnitI->setObjectName(QString::fromUtf8("lineEditUnitI"));
        sizePolicy.setHeightForWidth(lineEditUnitI->sizePolicy().hasHeightForWidth());
        lineEditUnitI->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEditUnitI);


        verticalLayout_2->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lineEditDataMinM = new QLineEdit(groupBox);
        lineEditDataMinM->setObjectName(QString::fromUtf8("lineEditDataMinM"));

        gridLayout->addWidget(lineEditDataMinM, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        lineEditDataMaxM = new QLineEdit(groupBox);
        lineEditDataMaxM->setObjectName(QString::fromUtf8("lineEditDataMaxM"));

        gridLayout->addWidget(lineEditDataMaxM, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 0, 5, 1, 1);

        lineEditDspMinM = new QLineEdit(groupBox);
        lineEditDspMinM->setObjectName(QString::fromUtf8("lineEditDspMinM"));

        gridLayout->addWidget(lineEditDspMinM, 0, 6, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 0, 7, 1, 1);

        lineEditDspMaxM = new QLineEdit(groupBox);
        lineEditDspMaxM->setObjectName(QString::fromUtf8("lineEditDspMaxM"));

        gridLayout->addWidget(lineEditDspMaxM, 0, 8, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        lineEditDataMinI = new QLineEdit(groupBox);
        lineEditDataMinI->setObjectName(QString::fromUtf8("lineEditDataMinI"));

        gridLayout->addWidget(lineEditDataMinI, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 2, 1, 1);

        lineEditDataMaxI = new QLineEdit(groupBox);
        lineEditDataMaxI->setObjectName(QString::fromUtf8("lineEditDataMaxI"));

        gridLayout->addWidget(lineEditDataMaxI, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 1, 5, 1, 1);

        lineEditDspMinI = new QLineEdit(groupBox);
        lineEditDspMinI->setObjectName(QString::fromUtf8("lineEditDspMinI"));

        gridLayout->addWidget(lineEditDspMinI, 1, 6, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 1, 7, 1, 1);

        lineEditDspMaxI = new QLineEdit(groupBox);
        lineEditDspMaxI->setObjectName(QString::fromUtf8("lineEditDspMaxI"));

        gridLayout->addWidget(lineEditDspMaxI, 1, 8, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(checkBox);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout->addWidget(label_15);

        comboBoxIcon = new QComboBox(groupBox);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/T-AC.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon6, QString());
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icon/T-AZI.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon7, QString());
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icon/T-CAL.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon8, QString());
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Icon/T-DEPTH.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon9, QString());
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Icon/T-DIP.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon10, QString());
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Icon/T-EW.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon11, QString());
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Icon/T-FRA.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon12, QString());
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Icon/T-GEN.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon13, QString());
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Icon/T-GR.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon14, QString());
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Icon/T-LITH.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon15, QString());
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Icon/T-NPHI.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon16, QString());
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/Icon/T-PE.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon17, QString());
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/Icon/T-PERM.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon18, QString());
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/Icon/T-POR.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon19, QString());
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/Icon/T-POTA.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon20, QString());
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/Icon/T-RC.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon21, QString());
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/Icon/T-RHO.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon22, QString());
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/Icon/T-RT.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon23, QString());
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/Icon/T-SN.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon24, QString());
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/Icon/T-SP.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon25, QString());
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/Icon/T-SW.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon26, QString());
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/Icon/T-THOR.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon27, QString());
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/Icon/T-URAN.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxIcon->addItem(icon28, QString());
        comboBoxIcon->setObjectName(QString::fromUtf8("comboBoxIcon"));

        horizontalLayout->addWidget(comboBoxIcon);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout->addWidget(label_8);

        lineEditAlias = new QLineEdit(groupBox);
        lineEditAlias->setObjectName(QString::fromUtf8("lineEditAlias"));
        sizePolicy2.setHeightForWidth(lineEditAlias->sizePolicy().hasHeightForWidth());
        lineEditAlias->setSizePolicy(sizePolicy2);
        lineEditAlias->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEditAlias);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);

        tabWidget->addTab(m_pTabContinuous, QString());
        m_pTabDiscrete = new QWidget();
        m_pTabDiscrete->setObjectName(QString::fromUtf8("m_pTabDiscrete"));
        gridLayout_5 = new QGridLayout(m_pTabDiscrete);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        m_pTableViewDiscrete = new QTableView(m_pTabDiscrete);
        m_pTableViewDiscrete->setObjectName(QString::fromUtf8("m_pTableViewDiscrete"));

        gridLayout_5->addWidget(m_pTableViewDiscrete, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_20 = new QLabel(m_pTabDiscrete);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_4->addWidget(label_20, 0, 8, 1, 1);

        m_pEdtDiscreteFullName = new QLineEdit(m_pTabDiscrete);
        m_pEdtDiscreteFullName->setObjectName(QString::fromUtf8("m_pEdtDiscreteFullName"));

        gridLayout_4->addWidget(m_pEdtDiscreteFullName, 0, 3, 1, 1);

        m_pEdtDiscreteMetricUnit = new QLineEdit(m_pTabDiscrete);
        m_pEdtDiscreteMetricUnit->setObjectName(QString::fromUtf8("m_pEdtDiscreteMetricUnit"));

        gridLayout_4->addWidget(m_pEdtDiscreteMetricUnit, 0, 7, 1, 1);

        m_pEdtDiscreteName = new QLineEdit(m_pTabDiscrete);
        m_pEdtDiscreteName->setObjectName(QString::fromUtf8("m_pEdtDiscreteName"));

        gridLayout_4->addWidget(m_pEdtDiscreteName, 0, 1, 1, 1);

        label_17 = new QLabel(m_pTabDiscrete);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_4->addWidget(label_17, 0, 2, 1, 1);

        label_16 = new QLabel(m_pTabDiscrete);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_4->addWidget(label_16, 0, 0, 1, 1);

        m_pEdtDiscreteType = new QLineEdit(m_pTabDiscrete);
        m_pEdtDiscreteType->setObjectName(QString::fromUtf8("m_pEdtDiscreteType"));

        gridLayout_4->addWidget(m_pEdtDiscreteType, 0, 5, 1, 1);

        m_pEdtDiscreteImperialUnit = new QLineEdit(m_pTabDiscrete);
        m_pEdtDiscreteImperialUnit->setObjectName(QString::fromUtf8("m_pEdtDiscreteImperialUnit"));

        gridLayout_4->addWidget(m_pEdtDiscreteImperialUnit, 0, 9, 1, 1);

        label_18 = new QLabel(m_pTabDiscrete);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_4->addWidget(label_18, 0, 4, 1, 1);

        label_19 = new QLabel(m_pTabDiscrete);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_4->addWidget(label_19, 0, 6, 1, 1);

        label_21 = new QLabel(m_pTabDiscrete);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_4->addWidget(label_21, 1, 0, 1, 1);

        label_22 = new QLabel(m_pTabDiscrete);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_4->addWidget(label_22, 1, 2, 1, 1);

        m_pEdtDiscreteIcon = new QLineEdit(m_pTabDiscrete);
        m_pEdtDiscreteIcon->setObjectName(QString::fromUtf8("m_pEdtDiscreteIcon"));

        gridLayout_4->addWidget(m_pEdtDiscreteIcon, 1, 1, 1, 1);

        m_pEdtDiscreteAlias = new QLineEdit(m_pTabDiscrete);
        m_pEdtDiscreteAlias->setObjectName(QString::fromUtf8("m_pEdtDiscreteAlias"));

        gridLayout_4->addWidget(m_pEdtDiscreteAlias, 1, 3, 1, 7);


        gridLayout_5->addLayout(gridLayout_4, 1, 0, 1, 1);

        gbxDiscreteProperties = new QGroupBox(m_pTabDiscrete);
        gbxDiscreteProperties->setObjectName(QString::fromUtf8("gbxDiscreteProperties"));
        gridLayout_2 = new QGridLayout(gbxDiscreteProperties);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_pBtnPropertyNew = new QPushButton(gbxDiscreteProperties);
        m_pBtnPropertyNew->setObjectName(QString::fromUtf8("m_pBtnPropertyNew"));

        gridLayout_2->addWidget(m_pBtnPropertyNew, 1, 0, 1, 1);

        m_pBtnPropertyDelete = new QPushButton(gbxDiscreteProperties);
        m_pBtnPropertyDelete->setObjectName(QString::fromUtf8("m_pBtnPropertyDelete"));

        gridLayout_2->addWidget(m_pBtnPropertyDelete, 1, 1, 1, 1);

        m_pTableProperties = new QTableWidget(gbxDiscreteProperties);
        if (m_pTableProperties->columnCount() < 2)
            m_pTableProperties->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        m_pTableProperties->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        m_pTableProperties->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        m_pTableProperties->setObjectName(QString::fromUtf8("m_pTableProperties"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(m_pTableProperties->sizePolicy().hasHeightForWidth());
        m_pTableProperties->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(m_pTableProperties, 0, 0, 1, 2);


        gridLayout_5->addWidget(gbxDiscreteProperties, 0, 1, 2, 1);

        tabWidget->addTab(m_pTabDiscrete, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);

        ShowTemplatesClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ShowTemplatesClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ShowTemplatesClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        QWidget::setTabOrder(lineEditName, lineEditFullName);
        QWidget::setTabOrder(lineEditFullName, lineEditType);
        QWidget::setTabOrder(lineEditType, lineEditUnitM);
        QWidget::setTabOrder(lineEditUnitM, lineEditUnitI);
        QWidget::setTabOrder(lineEditUnitI, lineEditDataMinM);
        QWidget::setTabOrder(lineEditDataMinM, lineEditDataMaxM);
        QWidget::setTabOrder(lineEditDataMaxM, lineEditDspMinM);
        QWidget::setTabOrder(lineEditDspMinM, lineEditDspMaxM);
        QWidget::setTabOrder(lineEditDspMaxM, lineEditDataMinI);
        QWidget::setTabOrder(lineEditDataMinI, lineEditDataMaxI);
        QWidget::setTabOrder(lineEditDataMaxI, lineEditDspMinI);
        QWidget::setTabOrder(lineEditDspMinI, lineEditDspMaxI);
        QWidget::setTabOrder(lineEditDspMaxI, checkBox);
        QWidget::setTabOrder(checkBox, lineEditAlias);
        QWidget::setTabOrder(lineEditAlias, tableView);
        QWidget::setTabOrder(tableView, m_pEdtDiscreteName);
        QWidget::setTabOrder(m_pEdtDiscreteName, m_pEdtDiscreteFullName);
        QWidget::setTabOrder(m_pEdtDiscreteFullName, m_pEdtDiscreteType);
        QWidget::setTabOrder(m_pEdtDiscreteType, m_pEdtDiscreteMetricUnit);
        QWidget::setTabOrder(m_pEdtDiscreteMetricUnit, m_pEdtDiscreteImperialUnit);
        QWidget::setTabOrder(m_pEdtDiscreteImperialUnit, m_pEdtDiscreteIcon);
        QWidget::setTabOrder(m_pEdtDiscreteIcon, m_pEdtDiscreteAlias);
        QWidget::setTabOrder(m_pEdtDiscreteAlias, m_pBtnPropertyNew);
        QWidget::setTabOrder(m_pBtnPropertyNew, m_pBtnPropertyDelete);
        QWidget::setTabOrder(m_pBtnPropertyDelete, m_pTableProperties);
        QWidget::setTabOrder(m_pTableProperties, m_pTableViewDiscrete);
        QWidget::setTabOrder(m_pTableViewDiscrete, tabWidget);

        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionDelete);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionReset);
        mainToolBar->addAction(actionSUS);
        mainToolBar->addAction(actionExit);

        retranslateUi(ShowTemplatesClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ShowTemplatesClass);
    } // setupUi

    void retranslateUi(QMainWindow *ShowTemplatesClass)
    {
        ShowTemplatesClass->setWindowTitle(QCoreApplication::translate("ShowTemplatesClass", "ShowTemplates", nullptr));
        actionSUS->setText(QCoreApplication::translate("ShowTemplatesClass", "\345\210\207\346\215\242\345\215\225\344\275\215\347\263\273\347\273\237", nullptr));
#if QT_CONFIG(tooltip)
        actionSUS->setToolTip(QCoreApplication::translate("ShowTemplatesClass", "\345\234\250\345\205\254\345\210\266\345\222\214\350\213\261\345\210\266\345\215\225\344\275\215\347\263\273\347\273\237\351\227\264\345\210\207\346\215\242", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit->setText(QCoreApplication::translate("ShowTemplatesClass", "&Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("ShowTemplatesClass", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("ShowTemplatesClass", "Save", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("ShowTemplatesClass", "\344\277\235\345\255\230\346\250\241\347\211\210", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("ShowTemplatesClass", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionReset->setText(QCoreApplication::translate("ShowTemplatesClass", "Reload", nullptr));
#if QT_CONFIG(tooltip)
        actionReset->setToolTip(QCoreApplication::translate("ShowTemplatesClass", "\351\207\215\347\275\256\346\250\241\347\211\210", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionReset->setShortcut(QCoreApplication::translate("ShowTemplatesClass", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew->setText(QCoreApplication::translate("ShowTemplatesClass", "New", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("ShowTemplatesClass", "\345\210\233\345\273\272\346\226\260\346\250\241\347\211\210", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("ShowTemplatesClass", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete->setText(QCoreApplication::translate("ShowTemplatesClass", "Delete", nullptr));
#if QT_CONFIG(shortcut)
        actionDelete->setShortcut(QCoreApplication::translate("ShowTemplatesClass", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBox->setTitle(QCoreApplication::translate("ShowTemplatesClass", "Template", nullptr));
        label->setText(QCoreApplication::translate("ShowTemplatesClass", "Name", nullptr));
        label_13->setText(QCoreApplication::translate("ShowTemplatesClass", "Full Name", nullptr));
        label_14->setText(QCoreApplication::translate("ShowTemplatesClass", "Type", nullptr));
        label_3->setText(QCoreApplication::translate("ShowTemplatesClass", "Unit (Metric)", nullptr));
        label_4->setText(QCoreApplication::translate("ShowTemplatesClass", "Unit (Imperial)", nullptr));
        label_2->setText(QCoreApplication::translate("ShowTemplatesClass", "Data Range (Metric)", nullptr));
        label_5->setText(QCoreApplication::translate("ShowTemplatesClass", "To", nullptr));
        label_9->setText(QCoreApplication::translate("ShowTemplatesClass", "Display Range (Metric)", nullptr));
        label_10->setText(QCoreApplication::translate("ShowTemplatesClass", "To", nullptr));
        label_6->setText(QCoreApplication::translate("ShowTemplatesClass", "Data Range (Imperial)", nullptr));
        label_7->setText(QCoreApplication::translate("ShowTemplatesClass", "To", nullptr));
        label_12->setText(QCoreApplication::translate("ShowTemplatesClass", "Display Range (Imperial)", nullptr));
        label_11->setText(QCoreApplication::translate("ShowTemplatesClass", "To", nullptr));
        checkBox->setText(QCoreApplication::translate("ShowTemplatesClass", "Logarithmic Display", nullptr));
        label_15->setText(QCoreApplication::translate("ShowTemplatesClass", "Icon", nullptr));
        comboBoxIcon->setItemText(0, QCoreApplication::translate("ShowTemplatesClass", "T-AC.png", nullptr));
        comboBoxIcon->setItemText(1, QCoreApplication::translate("ShowTemplatesClass", "T-AZI.png", nullptr));
        comboBoxIcon->setItemText(2, QCoreApplication::translate("ShowTemplatesClass", "T-CAL.png", nullptr));
        comboBoxIcon->setItemText(3, QCoreApplication::translate("ShowTemplatesClass", "T-DEPTH.png", nullptr));
        comboBoxIcon->setItemText(4, QCoreApplication::translate("ShowTemplatesClass", "T-DIP.png", nullptr));
        comboBoxIcon->setItemText(5, QCoreApplication::translate("ShowTemplatesClass", "T-EW.png", nullptr));
        comboBoxIcon->setItemText(6, QCoreApplication::translate("ShowTemplatesClass", "T-FRA.png", nullptr));
        comboBoxIcon->setItemText(7, QCoreApplication::translate("ShowTemplatesClass", "T-GEN.png", nullptr));
        comboBoxIcon->setItemText(8, QCoreApplication::translate("ShowTemplatesClass", "T-GR.png", nullptr));
        comboBoxIcon->setItemText(9, QCoreApplication::translate("ShowTemplatesClass", "T-LITH.png", nullptr));
        comboBoxIcon->setItemText(10, QCoreApplication::translate("ShowTemplatesClass", "T-NPHI.png", nullptr));
        comboBoxIcon->setItemText(11, QCoreApplication::translate("ShowTemplatesClass", "T-PE.png", nullptr));
        comboBoxIcon->setItemText(12, QCoreApplication::translate("ShowTemplatesClass", "T-PERM.png", nullptr));
        comboBoxIcon->setItemText(13, QCoreApplication::translate("ShowTemplatesClass", "T-POR.png", nullptr));
        comboBoxIcon->setItemText(14, QCoreApplication::translate("ShowTemplatesClass", "T-POTA.png", nullptr));
        comboBoxIcon->setItemText(15, QCoreApplication::translate("ShowTemplatesClass", "T-RC.png", nullptr));
        comboBoxIcon->setItemText(16, QCoreApplication::translate("ShowTemplatesClass", "T-RHO.png", nullptr));
        comboBoxIcon->setItemText(17, QCoreApplication::translate("ShowTemplatesClass", "T-RT.png", nullptr));
        comboBoxIcon->setItemText(18, QCoreApplication::translate("ShowTemplatesClass", "T-SN.png", nullptr));
        comboBoxIcon->setItemText(19, QCoreApplication::translate("ShowTemplatesClass", "T-SP.png", nullptr));
        comboBoxIcon->setItemText(20, QCoreApplication::translate("ShowTemplatesClass", "T-SW.png", nullptr));
        comboBoxIcon->setItemText(21, QCoreApplication::translate("ShowTemplatesClass", "T-THOR.png", nullptr));
        comboBoxIcon->setItemText(22, QCoreApplication::translate("ShowTemplatesClass", "T-URAN.png", nullptr));

        label_8->setText(QCoreApplication::translate("ShowTemplatesClass", "Alias", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(m_pTabContinuous), QCoreApplication::translate("ShowTemplatesClass", "Continuous Template", nullptr));
        label_20->setText(QCoreApplication::translate("ShowTemplatesClass", "Unit(Imperial)", nullptr));
        label_17->setText(QCoreApplication::translate("ShowTemplatesClass", "Full Name", nullptr));
        label_16->setText(QCoreApplication::translate("ShowTemplatesClass", "Name", nullptr));
        label_18->setText(QCoreApplication::translate("ShowTemplatesClass", "Type", nullptr));
        label_19->setText(QCoreApplication::translate("ShowTemplatesClass", "Unit(Metric)", nullptr));
        label_21->setText(QCoreApplication::translate("ShowTemplatesClass", "Icon", nullptr));
        label_22->setText(QCoreApplication::translate("ShowTemplatesClass", "Alias", nullptr));
        gbxDiscreteProperties->setTitle(QCoreApplication::translate("ShowTemplatesClass", "Properties", nullptr));
        m_pBtnPropertyNew->setText(QCoreApplication::translate("ShowTemplatesClass", "New", nullptr));
        m_pBtnPropertyDelete->setText(QCoreApplication::translate("ShowTemplatesClass", "Delete", nullptr));
        QTableWidgetItem *___qtablewidgetitem = m_pTableProperties->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ShowTemplatesClass", "Properties", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = m_pTableProperties->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ShowTemplatesClass", "Colors", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(m_pTabDiscrete), QCoreApplication::translate("ShowTemplatesClass", "Discrete Template", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowTemplatesClass: public Ui_ShowTemplatesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XSHOWTEMPLATES_H
