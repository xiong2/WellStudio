/********************************************************************************
** Form generated from reading UI file 'xdlgabout.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGABOUT_H
#define UI_XDLGABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_XDlgAbout
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *XDlgAbout)
    {
        if (XDlgAbout->objectName().isEmpty())
            XDlgAbout->setObjectName(QString::fromUtf8("XDlgAbout"));
        XDlgAbout->resize(878, 357);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(XDlgAbout->sizePolicy().hasHeightForWidth());
        XDlgAbout->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/X.png"), QSize(), QIcon::Normal, QIcon::Off);
        XDlgAbout->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(XDlgAbout);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(XDlgAbout);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(860, 310));
        label->setMaximumSize(QSize(860, 310));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Icon/About.png")));

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(XDlgAbout);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(XDlgAbout);
        QObject::connect(pushButton, SIGNAL(clicked()), XDlgAbout, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgAbout);
    } // setupUi

    void retranslateUi(QDialog *XDlgAbout)
    {
        XDlgAbout->setWindowTitle(QCoreApplication::translate("XDlgAbout", "About...", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("XDlgAbout", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgAbout: public Ui_XDlgAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGABOUT_H
