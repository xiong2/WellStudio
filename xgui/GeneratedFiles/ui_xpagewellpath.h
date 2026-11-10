/********************************************************************************
** Form generated from reading UI file 'xpagewellpath.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEWELLPATH_H
#define UI_XPAGEWELLPATH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageWellPath
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonAzi;
    QRadioButton *radioButtonTVDDXDY;
    QRadioButton *radioButtonTVDXY;
    QRadioButton *radioButtonXYZ;
    QRadioButton *radioButtonDXDYDZ;
    QCheckBox *checkBox;
    QCheckBox *checkBoxSimplify;

    void setupUi(QWidget *PageWellPath)
    {
        if (PageWellPath->objectName().isEmpty())
            PageWellPath->setObjectName(QString::fromUtf8("PageWellPath"));
        PageWellPath->resize(637, 319);
        verticalLayout = new QVBoxLayout(PageWellPath);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(PageWellPath);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButtonAzi = new QRadioButton(groupBox);
        radioButtonAzi->setObjectName(QString::fromUtf8("radioButtonAzi"));

        gridLayout->addWidget(radioButtonAzi, 0, 0, 1, 1);

        radioButtonTVDDXDY = new QRadioButton(groupBox);
        radioButtonTVDDXDY->setObjectName(QString::fromUtf8("radioButtonTVDDXDY"));

        gridLayout->addWidget(radioButtonTVDDXDY, 1, 0, 1, 1);

        radioButtonTVDXY = new QRadioButton(groupBox);
        radioButtonTVDXY->setObjectName(QString::fromUtf8("radioButtonTVDXY"));

        gridLayout->addWidget(radioButtonTVDXY, 2, 0, 1, 1);

        radioButtonXYZ = new QRadioButton(groupBox);
        radioButtonXYZ->setObjectName(QString::fromUtf8("radioButtonXYZ"));

        gridLayout->addWidget(radioButtonXYZ, 3, 0, 1, 1);

        radioButtonDXDYDZ = new QRadioButton(groupBox);
        radioButtonDXDYDZ->setObjectName(QString::fromUtf8("radioButtonDXDYDZ"));

        gridLayout->addWidget(radioButtonDXDYDZ, 4, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        checkBox = new QCheckBox(PageWellPath);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        checkBoxSimplify = new QCheckBox(PageWellPath);
        checkBoxSimplify->setObjectName(QString::fromUtf8("checkBoxSimplify"));

        verticalLayout->addWidget(checkBoxSimplify);


        retranslateUi(PageWellPath);

        QMetaObject::connectSlotsByName(PageWellPath);
    } // setupUi

    void retranslateUi(QWidget *PageWellPath)
    {
        PageWellPath->setWindowTitle(QCoreApplication::translate("PageWellPath", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PageWellPath", "Select Dataset for Well Path", nullptr));
        radioButtonAzi->setText(QCoreApplication::translate("PageWellPath", "MD, Inclination, Azimuth", nullptr));
        radioButtonTVDDXDY->setText(QCoreApplication::translate("PageWellPath", "TVD, DX, DY", nullptr));
        radioButtonTVDXY->setText(QCoreApplication::translate("PageWellPath", "TVD, X, Y", nullptr));
        radioButtonXYZ->setText(QCoreApplication::translate("PageWellPath", "X, Y, Z", nullptr));
        radioButtonDXDYDZ->setText(QCoreApplication::translate("PageWellPath", "DX, DY, DZ", nullptr));
        checkBox->setText(QCoreApplication::translate("PageWellPath", "Negate Z", nullptr));
        checkBoxSimplify->setText(QCoreApplication::translate("PageWellPath", "Simplify the deviation data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageWellPath: public Ui_PageWellPath {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEWELLPATH_H
