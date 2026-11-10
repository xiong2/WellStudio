/********************************************************************************
** Form generated from reading UI file 'xdlgpyviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGPYVIEWER_H
#define UI_XDLGPYVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "xframepyviewer.h"

QT_BEGIN_NAMESPACE

class Ui_XDlgPyViewer
{
public:
    QVBoxLayout *verticalLayout;
    XFramePyViewer *frameBro;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpinBox *spinBoxBStart;
    QLabel *label_4;
    QSpinBox *spinBoxBEnd;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonBO;
    QPushButton *pushButtonBW;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonFW;
    QPushButton *pushButtonFO;
    QLabel *label_6;
    QSlider *horizontalSlider;
    QLabel *label_7;
    QFrame *line;
    XFramePyViewer *frameStack;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QPushButton *pushButtonOK;

    void setupUi(QDialog *XDlgPyViewer)
    {
        if (XDlgPyViewer->objectName().isEmpty())
            XDlgPyViewer->setObjectName(QString::fromUtf8("XDlgPyViewer"));
        XDlgPyViewer->resize(546, 566);
        verticalLayout = new QVBoxLayout(XDlgPyViewer);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frameBro = new XFramePyViewer(XDlgPyViewer);
        frameBro->setObjectName(QString::fromUtf8("frameBro"));
        frameBro->setFrameShape(QFrame::StyledPanel);
        frameBro->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frameBro);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(XDlgPyViewer);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        spinBoxBStart = new QSpinBox(XDlgPyViewer);
        spinBoxBStart->setObjectName(QString::fromUtf8("spinBoxBStart"));
        spinBoxBStart->setMaximum(360);

        horizontalLayout_2->addWidget(spinBoxBStart);

        label_4 = new QLabel(XDlgPyViewer);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        spinBoxBEnd = new QSpinBox(XDlgPyViewer);
        spinBoxBEnd->setObjectName(QString::fromUtf8("spinBoxBEnd"));
        spinBoxBEnd->setMaximum(360);
        spinBoxBEnd->setValue(360);

        horizontalLayout_2->addWidget(spinBoxBEnd);

        label_5 = new QLabel(XDlgPyViewer);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lineEdit = new QLineEdit(XDlgPyViewer);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSpacer_5 = new QSpacerItem(175, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonBO = new QPushButton(XDlgPyViewer);
        pushButtonBO->setObjectName(QString::fromUtf8("pushButtonBO"));
        pushButtonBO->setMaximumSize(QSize(24, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/PlayPageUp.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonBO->setIcon(icon);

        horizontalLayout->addWidget(pushButtonBO);

        pushButtonBW = new QPushButton(XDlgPyViewer);
        pushButtonBW->setObjectName(QString::fromUtf8("pushButtonBW"));
        pushButtonBW->setMaximumSize(QSize(24, 24));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/PlayBackward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonBW->setIcon(icon1);

        horizontalLayout->addWidget(pushButtonBW);

        pushButtonStop = new QPushButton(XDlgPyViewer);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setMaximumSize(QSize(24, 24));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/PlayPause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonStop->setIcon(icon2);

        horizontalLayout->addWidget(pushButtonStop);

        pushButtonFW = new QPushButton(XDlgPyViewer);
        pushButtonFW->setObjectName(QString::fromUtf8("pushButtonFW"));
        pushButtonFW->setMaximumSize(QSize(24, 24));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icon/PlayForward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonFW->setIcon(icon3);

        horizontalLayout->addWidget(pushButtonFW);

        pushButtonFO = new QPushButton(XDlgPyViewer);
        pushButtonFO->setObjectName(QString::fromUtf8("pushButtonFO"));
        pushButtonFO->setMaximumSize(QSize(24, 24));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icon/PlayPageDown.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonFO->setIcon(icon4);

        horizontalLayout->addWidget(pushButtonFO);

        label_6 = new QLabel(XDlgPyViewer);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        horizontalSlider = new QSlider(XDlgPyViewer);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(5);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setValue(10);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        label_7 = new QLabel(XDlgPyViewer);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(XDlgPyViewer);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        frameStack = new XFramePyViewer(XDlgPyViewer);
        frameStack->setObjectName(QString::fromUtf8("frameStack"));
        frameStack->setFrameShape(QFrame::StyledPanel);
        frameStack->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frameStack);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label = new QLabel(XDlgPyViewer);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_6);

        pushButtonOK = new QPushButton(XDlgPyViewer);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setMinimumSize(QSize(240, 0));
        pushButtonOK->setMaximumSize(QSize(240, 16777215));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icon/OK.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonOK->setIcon(icon5);

        verticalLayout->addWidget(pushButtonOK);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(4, 1);

        retranslateUi(XDlgPyViewer);
        QObject::connect(pushButtonOK, SIGNAL(clicked()), XDlgPyViewer, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgPyViewer);
    } // setupUi

    void retranslateUi(QDialog *XDlgPyViewer)
    {
        XDlgPyViewer->setWindowTitle(QCoreApplication::translate("XDlgPyViewer", "\346\273\244\346\263\242\346\226\271\345\267\256\345\210\206\346\236\220", nullptr));
        label_3->setText(QCoreApplication::translate("XDlgPyViewer", "\346\265\217\350\247\210\350\207\252", nullptr));
        label_4->setText(QCoreApplication::translate("XDlgPyViewer", "\350\207\263", nullptr));
        label_5->setText(QCoreApplication::translate("XDlgPyViewer", "\345\275\223\345\211\215\344\270\272", nullptr));
        lineEdit->setText(QCoreApplication::translate("XDlgPyViewer", "90", nullptr));
        pushButtonBO->setText(QString());
        pushButtonBW->setText(QString());
        pushButtonStop->setText(QString());
        pushButtonFW->setText(QString());
        pushButtonFO->setText(QString());
        label_6->setText(QCoreApplication::translate("XDlgPyViewer", "\345\277\253", nullptr));
        label_7->setText(QCoreApplication::translate("XDlgPyViewer", "\346\205\242", nullptr));
        label->setText(QCoreApplication::translate("XDlgPyViewer", "TextLabel", nullptr));
        pushButtonOK->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class XDlgPyViewer: public Ui_XDlgPyViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGPYVIEWER_H
