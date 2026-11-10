/********************************************************************************
** Form generated from reading UI file 'xdlggatherwin.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGGATHERWIN_H
#define UI_XDLGGATHERWIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include "xaxeswidget.h"
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_XDlgGatherWin
{
public:
    QGridLayout *gridLayout;
    XAxesWidget *AxesWidget;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QSlider *horizontalSlider;
    QPushButton *pushButtonShow;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonW;
    QPushButton *pushButtonVA;
    QPushButton *pushButtonVD;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonHUp;
    QPushButton *pushButtonHDown;
    QPushButton *pushButtonVUp;
    QPushButton *pushButtonVDown;
    QPushButton *pushButtonIE;
    QPushButton *pushButtonDE;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox;
    CXButtonColorEdit *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *XDlgGatherWin)
    {
        if (XDlgGatherWin->objectName().isEmpty())
            XDlgGatherWin->setObjectName(QString::fromUtf8("XDlgGatherWin"));
        XDlgGatherWin->resize(1100, 891);
        gridLayout = new QGridLayout(XDlgGatherWin);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        AxesWidget = new XAxesWidget(XDlgGatherWin);
        AxesWidget->setObjectName(QString::fromUtf8("AxesWidget"));

        gridLayout->addWidget(AxesWidget, 0, 0, 1, 6);

        groupBox = new QGroupBox(XDlgGatherWin);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(60, 0));
        lineEdit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        pushButtonShow = new QPushButton(groupBox);
        pushButtonShow->setObjectName(QString::fromUtf8("pushButtonShow"));

        horizontalLayout_2->addWidget(pushButtonShow);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(XDlgGatherWin);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonW = new QPushButton(groupBox_2);
        pushButtonW->setObjectName(QString::fromUtf8("pushButtonW"));
        pushButtonW->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Wiggle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonW->setIcon(icon);
        pushButtonW->setCheckable(true);
        pushButtonW->setChecked(true);

        horizontalLayout_3->addWidget(pushButtonW);

        pushButtonVA = new QPushButton(groupBox_2);
        pushButtonVA->setObjectName(QString::fromUtf8("pushButtonVA"));
        pushButtonVA->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/WiggleArea.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonVA->setIcon(icon1);
        pushButtonVA->setCheckable(true);
        pushButtonVA->setChecked(true);

        horizontalLayout_3->addWidget(pushButtonVA);

        pushButtonVD = new QPushButton(groupBox_2);
        pushButtonVD->setObjectName(QString::fromUtf8("pushButtonVD"));
        pushButtonVD->setMaximumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/VaribleIntensity.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonVD->setIcon(icon2);
        pushButtonVD->setCheckable(true);

        horizontalLayout_3->addWidget(pushButtonVD);


        gridLayout->addWidget(groupBox_2, 1, 1, 1, 1);

        groupBox_3 = new QGroupBox(XDlgGatherWin);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonHUp = new QPushButton(groupBox_3);
        pushButtonHUp->setObjectName(QString::fromUtf8("pushButtonHUp"));
        pushButtonHUp->setMaximumSize(QSize(30, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/IncaseHorizon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonHUp->setIcon(icon3);
        pushButtonHUp->setCheckable(false);
        pushButtonHUp->setChecked(false);

        horizontalLayout->addWidget(pushButtonHUp);

        pushButtonHDown = new QPushButton(groupBox_3);
        pushButtonHDown->setObjectName(QString::fromUtf8("pushButtonHDown"));
        pushButtonHDown->setMaximumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/DiscaseHorizon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonHDown->setIcon(icon4);
        pushButtonHDown->setCheckable(false);
        pushButtonHDown->setChecked(false);

        horizontalLayout->addWidget(pushButtonHDown);

        pushButtonVUp = new QPushButton(groupBox_3);
        pushButtonVUp->setObjectName(QString::fromUtf8("pushButtonVUp"));
        pushButtonVUp->setMaximumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/IncaseVertical.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonVUp->setIcon(icon5);
        pushButtonVUp->setCheckable(false);
        pushButtonVUp->setChecked(false);

        horizontalLayout->addWidget(pushButtonVUp);

        pushButtonVDown = new QPushButton(groupBox_3);
        pushButtonVDown->setObjectName(QString::fromUtf8("pushButtonVDown"));
        pushButtonVDown->setMaximumSize(QSize(30, 30));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icon/DiscaseVertical.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonVDown->setIcon(icon6);
        pushButtonVDown->setCheckable(false);
        pushButtonVDown->setChecked(false);

        horizontalLayout->addWidget(pushButtonVDown);

        pushButtonIE = new QPushButton(groupBox_3);
        pushButtonIE->setObjectName(QString::fromUtf8("pushButtonIE"));
        pushButtonIE->setMaximumSize(QSize(30, 30));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icon/IncaseExcursion.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonIE->setIcon(icon7);
        pushButtonIE->setCheckable(false);
        pushButtonIE->setChecked(false);

        horizontalLayout->addWidget(pushButtonIE);

        pushButtonDE = new QPushButton(groupBox_3);
        pushButtonDE->setObjectName(QString::fromUtf8("pushButtonDE"));
        pushButtonDE->setMaximumSize(QSize(30, 30));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icon/DiscaseExcursion.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonDE->setIcon(icon8);
        pushButtonDE->setCheckable(false);
        pushButtonDE->setChecked(false);

        horizontalLayout->addWidget(pushButtonDE);


        gridLayout->addWidget(groupBox_3, 1, 2, 1, 1);

        groupBox_4 = new QGroupBox(XDlgGatherWin);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setEnabled(true);
        horizontalLayout_4 = new QHBoxLayout(groupBox_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBox = new QCheckBox(groupBox_4);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);

        horizontalLayout_4->addWidget(checkBox);

        comboBox = new CXButtonColorEdit(groupBox_4);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEnabled(false);

        horizontalLayout_4->addWidget(comboBox);


        gridLayout->addWidget(groupBox_4, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(186, 54, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 1, 1);

        pushButton = new QPushButton(XDlgGatherWin);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 5, 1, 1);


        retranslateUi(XDlgGatherWin);
        QObject::connect(pushButton, SIGNAL(clicked()), XDlgGatherWin, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgGatherWin);
    } // setupUi

    void retranslateUi(QDialog *XDlgGatherWin)
    {
        XDlgGatherWin->setWindowTitle(QCoreApplication::translate("XDlgGatherWin", "Gather Viewer", nullptr));
        groupBox->setTitle(QCoreApplication::translate("XDlgGatherWin", "Gather", nullptr));
        label->setText(QCoreApplication::translate("XDlgGatherWin", "Shot Index", nullptr));
        pushButtonShow->setText(QCoreApplication::translate("XDlgGatherWin", "Show", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("XDlgGatherWin", "Display Mode", nullptr));
        pushButtonW->setText(QString());
        pushButtonVA->setText(QString());
        pushButtonVD->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("XDlgGatherWin", "Display Scale", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonHUp->setToolTip(QCoreApplication::translate("XDlgGatherWin", "Increase horizontal scale", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonHUp->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonHDown->setToolTip(QCoreApplication::translate("XDlgGatherWin", "Decrease horizontal scale", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonHDown->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonVUp->setToolTip(QCoreApplication::translate("XDlgGatherWin", "Increase vertical scale", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonVUp->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonVDown->setToolTip(QCoreApplication::translate("XDlgGatherWin", "Decrease vertical scale", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonVDown->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonIE->setToolTip(QCoreApplication::translate("XDlgGatherWin", "Increase excursion", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonIE->setText(QString());
#if QT_CONFIG(tooltip)
        pushButtonDE->setToolTip(QCoreApplication::translate("XDlgGatherWin", "Decrease excursion", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonDE->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("XDlgGatherWin", "First Break", nullptr));
        checkBox->setText(QCoreApplication::translate("XDlgGatherWin", "Show", nullptr));
        pushButton->setText(QCoreApplication::translate("XDlgGatherWin", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgGatherWin: public Ui_XDlgGatherWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGGATHERWIN_H
