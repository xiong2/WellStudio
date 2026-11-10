/********************************************************************************
** Form generated from reading UI file 'xdlgattachprofile.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGATTACHPROFILE_H
#define UI_XDLGATTACHPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AttachProfile
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *labelCanvas;
    QLabel *label_2;
    QLineEdit *lineEditEndTime;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditFile;
    QPushButton *pushButtonBrowser;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLineEdit *lineEditStartTrace;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLineEdit *lineEditLineNumber;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_5;
    QLineEdit *lineEditEndTrace;
    QLineEdit *lineEditStartTime;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *AttachProfile)
    {
        if (AttachProfile->objectName().isEmpty())
            AttachProfile->setObjectName(QString::fromUtf8("AttachProfile"));
        AttachProfile->resize(880, 728);
        gridLayout = new QGridLayout(AttachProfile);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(AttachProfile);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(AttachProfile);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        labelCanvas = new QLabel(AttachProfile);
        labelCanvas->setObjectName(QString::fromUtf8("labelCanvas"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelCanvas->sizePolicy().hasHeightForWidth());
        labelCanvas->setSizePolicy(sizePolicy);
        labelCanvas->setMinimumSize(QSize(540, 0));
        labelCanvas->setMaximumSize(QSize(16777215, 16777215));
        labelCanvas->setFrameShape(QFrame::StyledPanel);
        labelCanvas->setScaledContents(true);
        labelCanvas->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelCanvas, 2, 1, 5, 1);

        label_2 = new QLabel(AttachProfile);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEditEndTime = new QLineEdit(AttachProfile);
        lineEditEndTime->setObjectName(QString::fromUtf8("lineEditEndTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditEndTime->sizePolicy().hasHeightForWidth());
        lineEditEndTime->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditEndTime, 6, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditFile = new QLineEdit(AttachProfile);
        lineEditFile->setObjectName(QString::fromUtf8("lineEditFile"));

        horizontalLayout->addWidget(lineEditFile);

        pushButtonBrowser = new QPushButton(AttachProfile);
        pushButtonBrowser->setObjectName(QString::fromUtf8("pushButtonBrowser"));

        horizontalLayout->addWidget(pushButtonBrowser);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_4 = new QLabel(AttachProfile);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEditStartTrace = new QLineEdit(AttachProfile);
        lineEditStartTrace->setObjectName(QString::fromUtf8("lineEditStartTrace"));

        horizontalLayout_2->addWidget(lineEditStartTrace);

        horizontalSpacer = new QSpacerItem(158, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_6 = new QLabel(AttachProfile);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        lineEditLineNumber = new QLineEdit(AttachProfile);
        lineEditLineNumber->setObjectName(QString::fromUtf8("lineEditLineNumber"));

        horizontalLayout_2->addWidget(lineEditLineNumber);

        horizontalSpacer_2 = new QSpacerItem(178, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_5 = new QLabel(AttachProfile);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lineEditEndTrace = new QLineEdit(AttachProfile);
        lineEditEndTrace->setObjectName(QString::fromUtf8("lineEditEndTrace"));

        horizontalLayout_2->addWidget(lineEditEndTrace);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 2);

        lineEditStartTime = new QLineEdit(AttachProfile);
        lineEditStartTime->setObjectName(QString::fromUtf8("lineEditStartTime"));
        sizePolicy1.setHeightForWidth(lineEditStartTime->sizePolicy().hasHeightForWidth());
        lineEditStartTime->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditStartTime, 3, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(AttachProfile);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(AttachProfile);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 7, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 268, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);

        label_2->raise();
        lineEditStartTime->raise();
        label_3->raise();
        lineEditEndTime->raise();
        label->raise();
        labelCanvas->raise();

        retranslateUi(AttachProfile);
        QObject::connect(okButton, SIGNAL(clicked()), AttachProfile, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), AttachProfile, SLOT(reject()));

        QMetaObject::connectSlotsByName(AttachProfile);
    } // setupUi

    void retranslateUi(QDialog *AttachProfile)
    {
        AttachProfile->setWindowTitle(QCoreApplication::translate("AttachProfile", "Attach Profile", nullptr));
        label->setText(QCoreApplication::translate("AttachProfile", "Attach profile image:", nullptr));
        label_3->setText(QCoreApplication::translate("AttachProfile", "End time", nullptr));
        labelCanvas->setText(QString());
        label_2->setText(QCoreApplication::translate("AttachProfile", "Start time", nullptr));
        pushButtonBrowser->setText(QCoreApplication::translate("AttachProfile", "Browse...", nullptr));
        label_4->setText(QCoreApplication::translate("AttachProfile", "First trace:", nullptr));
        label_6->setText(QCoreApplication::translate("AttachProfile", "Line:", nullptr));
        label_5->setText(QCoreApplication::translate("AttachProfile", "Last trace:", nullptr));
        okButton->setText(QCoreApplication::translate("AttachProfile", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("AttachProfile", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AttachProfile: public Ui_AttachProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGATTACHPROFILE_H
