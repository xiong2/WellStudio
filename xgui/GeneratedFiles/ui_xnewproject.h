/********************************************************************************
** Form generated from reading UI file 'xnewproject.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XNEWPROJECT_H
#define UI_XNEWPROJECT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_NewProject
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEditName;
    QLabel *label_2;
    QRadioButton *radioButtonM;
    QRadioButton *radioButtonI;
    QLabel *label_3;
    QLineEdit *lineEditDirectory;
    QPushButton *pushButtonBrowse;
    QLabel *label_4;
    QTextEdit *textEditComments;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *NewProject)
    {
        if (NewProject->objectName().isEmpty())
            NewProject->setObjectName(QString::fromUtf8("NewProject"));
        NewProject->setWindowModality(Qt::ApplicationModal);
        NewProject->resize(400, 300);
        gridLayout = new QGridLayout(NewProject);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(NewProject);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditName = new QLineEdit(NewProject);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 0, 1, 1, 3);

        label_2 = new QLabel(NewProject);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        radioButtonM = new QRadioButton(NewProject);
        radioButtonM->setObjectName(QString::fromUtf8("radioButtonM"));
        radioButtonM->setMaximumSize(QSize(80, 16777215));
        radioButtonM->setChecked(true);

        gridLayout->addWidget(radioButtonM, 1, 1, 1, 1);

        radioButtonI = new QRadioButton(NewProject);
        radioButtonI->setObjectName(QString::fromUtf8("radioButtonI"));

        gridLayout->addWidget(radioButtonI, 1, 2, 1, 1);

        label_3 = new QLabel(NewProject);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEditDirectory = new QLineEdit(NewProject);
        lineEditDirectory->setObjectName(QString::fromUtf8("lineEditDirectory"));

        gridLayout->addWidget(lineEditDirectory, 2, 1, 1, 2);

        pushButtonBrowse = new QPushButton(NewProject);
        pushButtonBrowse->setObjectName(QString::fromUtf8("pushButtonBrowse"));
        pushButtonBrowse->setMaximumSize(QSize(80, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Folder(open).png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonBrowse->setIcon(icon);

        gridLayout->addWidget(pushButtonBrowse, 2, 3, 1, 1);

        label_4 = new QLabel(NewProject);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        textEditComments = new QTextEdit(NewProject);
        textEditComments->setObjectName(QString::fromUtf8("textEditComments"));

        gridLayout->addWidget(textEditComments, 4, 0, 1, 4);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(NewProject);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setFocusPolicy(Qt::StrongFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/OK.png"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon1);

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(NewProject);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon2);

        hboxLayout->addWidget(cancelButton);


        gridLayout->addLayout(hboxLayout, 5, 0, 1, 4);


        retranslateUi(NewProject);
        QObject::connect(okButton, SIGNAL(clicked()), NewProject, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), NewProject, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewProject);
    } // setupUi

    void retranslateUi(QDialog *NewProject)
    {
        NewProject->setWindowTitle(QCoreApplication::translate("NewProject", "New project", nullptr));
        label->setText(QCoreApplication::translate("NewProject", "Project name:", nullptr));
        lineEditName->setText(QCoreApplication::translate("NewProject", "Project", nullptr));
        label_2->setText(QCoreApplication::translate("NewProject", "Units:", nullptr));
        radioButtonM->setText(QCoreApplication::translate("NewProject", "metric", nullptr));
        radioButtonI->setText(QCoreApplication::translate("NewProject", "imperial", nullptr));
        label_3->setText(QCoreApplication::translate("NewProject", "Project location:", nullptr));
        pushButtonBrowse->setText(QCoreApplication::translate("NewProject", "...", nullptr));
        label_4->setText(QCoreApplication::translate("NewProject", "Remarks:", nullptr));
        okButton->setText(QCoreApplication::translate("NewProject", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("NewProject", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewProject: public Ui_NewProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XNEWPROJECT_H
