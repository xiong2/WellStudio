/********************************************************************************
** Form generated from reading UI file 'gsdlgrosediagram.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GSDLGROSEDIAGRAM_H
#define UI_GSDLGROSEDIAGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_gsdlgrosediagram
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonCircle;
    QRadioButton *radioButtonPolygon;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpinBox *spinBoxRadius;
    QLabel *label_2;
    QRadioButton *radioButtonClick;
    QRadioButton *radioButtonWell;
    QComboBox *comboBoxWells;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *gsdlgrosediagram)
    {
        if (gsdlgrosediagram->objectName().isEmpty())
            gsdlgrosediagram->setObjectName(QString::fromUtf8("gsdlgrosediagram"));
        gsdlgrosediagram->resize(361, 201);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gsdlgrosediagram->sizePolicy().hasHeightForWidth());
        gsdlgrosediagram->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(gsdlgrosediagram);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(gsdlgrosediagram);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        lineEdit = new QLineEdit(gsdlgrosediagram);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_3->addWidget(lineEdit, 0, 1, 1, 1);

        groupBox = new QGroupBox(gsdlgrosediagram);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButtonCircle = new QRadioButton(groupBox);
        buttonGroup = new QButtonGroup(gsdlgrosediagram);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButtonCircle);
        radioButtonCircle->setObjectName(QString::fromUtf8("radioButtonCircle"));
        radioButtonCircle->setChecked(true);

        gridLayout->addWidget(radioButtonCircle, 2, 0, 1, 1);

        radioButtonPolygon = new QRadioButton(groupBox);
        buttonGroup->addButton(radioButtonPolygon);
        radioButtonPolygon->setObjectName(QString::fromUtf8("radioButtonPolygon"));
        radioButtonPolygon->setToolTipDuration(5);

        gridLayout->addWidget(radioButtonPolygon, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/icons/HelpInfo.png")));

        gridLayout->addWidget(label_4, 2, 2, 1, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 2);

        spinBoxRadius = new QSpinBox(groupBox_2);
        spinBoxRadius->setObjectName(QString::fromUtf8("spinBoxRadius"));

        gridLayout_2->addWidget(spinBoxRadius, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        radioButtonClick = new QRadioButton(groupBox_2);
        radioButtonClick->setObjectName(QString::fromUtf8("radioButtonClick"));
        radioButtonClick->setChecked(true);

        gridLayout_2->addWidget(radioButtonClick, 1, 1, 1, 2);

        radioButtonWell = new QRadioButton(groupBox_2);
        radioButtonWell->setObjectName(QString::fromUtf8("radioButtonWell"));

        gridLayout_2->addWidget(radioButtonWell, 1, 3, 1, 1);

        comboBoxWells = new QComboBox(groupBox_2);
        comboBoxWells->setObjectName(QString::fromUtf8("comboBoxWells"));
        comboBoxWells->setEnabled(false);

        gridLayout_2->addWidget(comboBoxWells, 1, 4, 1, 1);


        gridLayout->addWidget(groupBox_2, 5, 0, 1, 3);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(gsdlgrosediagram);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_3->addWidget(buttonBox, 2, 0, 1, 2);


        retranslateUi(gsdlgrosediagram);
        QObject::connect(buttonBox, SIGNAL(accepted()), gsdlgrosediagram, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), gsdlgrosediagram, SLOT(reject()));

        QMetaObject::connectSlotsByName(gsdlgrosediagram);
    } // setupUi

    void retranslateUi(QDialog *gsdlgrosediagram)
    {
        gsdlgrosediagram->setWindowTitle(QCoreApplication::translate("gsdlgrosediagram", "gsdlgrosediagram", nullptr));
        label_3->setText(QCoreApplication::translate("gsdlgrosediagram", "Name:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("gsdlgrosediagram", "Range", nullptr));
#if QT_CONFIG(whatsthis)
        radioButtonCircle->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        radioButtonCircle->setText(QCoreApplication::translate("gsdlgrosediagram", "Define by circle", nullptr));
#if QT_CONFIG(tooltip)
        radioButtonPolygon->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        radioButtonPolygon->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        radioButtonPolygon->setText(QCoreApplication::translate("gsdlgrosediagram", "Define by polygon", nullptr));
#if QT_CONFIG(tooltip)
        label_4->setToolTip(QCoreApplication::translate("gsdlgrosediagram", "<html><head/><body><p>Click left mouse botton on the base map to define the polygon.  Press middle mouse botton to abort last node, and double click left button will finish the job.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("gsdlgrosediagram", "Circle Parameters", nullptr));
        label->setText(QCoreApplication::translate("gsdlgrosediagram", "Radius (m):", nullptr));
        label_2->setText(QCoreApplication::translate("gsdlgrosediagram", "Centre", nullptr));
        radioButtonClick->setText(QCoreApplication::translate("gsdlgrosediagram", "Click on map", nullptr));
        radioButtonWell->setText(QCoreApplication::translate("gsdlgrosediagram", "by Well", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gsdlgrosediagram: public Ui_gsdlgrosediagram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GSDLGROSEDIAGRAM_H
