/********************************************************************************
** Form generated from reading UI file 'xdlgpyramid.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGPYRAMID_H
#define UI_XDLGPYRAMID_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <xslidercomplex.h>
#include "xviewpyramid.h"

QT_BEGIN_NAMESPACE

class Ui_XDlgPyramid
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QRadioButton *radioButtonI;
    QRadioButton *radioButtonX;
    QRadioButton *radioButtonT;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *lineEditSection;
    QSlider *horizontalSliderSection;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEditTo;
    QLineEdit *lineEditStep;
    QLineEdit *lineEditDegree;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label_9;
    QLineEdit *lineEditFrom;
    QSlider *horizontalSliderDegree;
    QGroupBox *groupBoxStack;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_4;
    QLabel *label_6;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    CXSliderComplex *slideRangeInline;
    CXSliderComplex *slideRangeXline;
    CXSliderComplex *slideRangeTimeSlice;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QCheckBox *checkBox;
    QLineEdit *lineEditOutside;
    XViewPyramid *graphicsView;

    void setupUi(QDialog *XDlgPyramid)
    {
        if (XDlgPyramid->objectName().isEmpty())
            XDlgPyramid->setObjectName(QString::fromUtf8("XDlgPyramid"));
        XDlgPyramid->resize(1286, 880);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(XDlgPyramid->sizePolicy().hasHeightForWidth());
        XDlgPyramid->setSizePolicy(sizePolicy);
        XDlgPyramid->setMinimumSize(QSize(1286, 880));
        XDlgPyramid->setMaximumSize(QSize(1286, 880));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icon/Pyramid.png"), QSize(), QIcon::Normal, QIcon::Off);
        XDlgPyramid->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(XDlgPyramid);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(XDlgPyramid);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(320, 0));
        groupBox->setMaximumSize(QSize(400, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        radioButtonI = new QRadioButton(groupBox);
        radioButtonI->setObjectName(QString::fromUtf8("radioButtonI"));
        radioButtonI->setToolTipDuration(-2);
        radioButtonI->setChecked(true);

        horizontalLayout_2->addWidget(radioButtonI);

        radioButtonX = new QRadioButton(groupBox);
        radioButtonX->setObjectName(QString::fromUtf8("radioButtonX"));

        horizontalLayout_2->addWidget(radioButtonX);

        radioButtonT = new QRadioButton(groupBox);
        radioButtonT->setObjectName(QString::fromUtf8("radioButtonT"));

        horizontalLayout_2->addWidget(radioButtonT);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineEditSection = new QLineEdit(groupBox);
        lineEditSection->setObjectName(QString::fromUtf8("lineEditSection"));
        lineEditSection->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(lineEditSection);

        horizontalSliderSection = new QSlider(groupBox);
        horizontalSliderSection->setObjectName(QString::fromUtf8("horizontalSliderSection"));
        horizontalSliderSection->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSliderSection);


        verticalLayout_2->addLayout(horizontalLayout_3);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setCheckable(true);
        groupBox_4->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 6, 1, 1);

        lineEditTo = new QLineEdit(groupBox_4);
        lineEditTo->setObjectName(QString::fromUtf8("lineEditTo"));
        lineEditTo->setMaximumSize(QSize(40, 16777215));

        gridLayout_2->addWidget(lineEditTo, 0, 3, 1, 1);

        lineEditStep = new QLineEdit(groupBox_4);
        lineEditStep->setObjectName(QString::fromUtf8("lineEditStep"));
        lineEditStep->setMaximumSize(QSize(40, 16777215));

        gridLayout_2->addWidget(lineEditStep, 0, 5, 1, 1);

        lineEditDegree = new QLineEdit(groupBox_4);
        lineEditDegree->setObjectName(QString::fromUtf8("lineEditDegree"));
        lineEditDegree->setMaximumSize(QSize(40, 16777215));

        gridLayout_2->addWidget(lineEditDegree, 1, 1, 1, 1);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 0, 4, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        lineEditFrom = new QLineEdit(groupBox_4);
        lineEditFrom->setObjectName(QString::fromUtf8("lineEditFrom"));
        lineEditFrom->setMaximumSize(QSize(40, 16777215));

        gridLayout_2->addWidget(lineEditFrom, 0, 1, 1, 1);

        horizontalSliderDegree = new QSlider(groupBox_4);
        horizontalSliderDegree->setObjectName(QString::fromUtf8("horizontalSliderDegree"));
        horizontalSliderDegree->setMaximum(360);
        horizontalSliderDegree->setSingleStep(5);
        horizontalSliderDegree->setValue(90);
        horizontalSliderDegree->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSliderDegree, 1, 2, 1, 6);


        verticalLayout_2->addWidget(groupBox_4);


        gridLayout_3->addWidget(groupBox, 0, 2, 1, 1);

        groupBoxStack = new QGroupBox(XDlgPyramid);
        groupBoxStack->setObjectName(QString::fromUtf8("groupBoxStack"));
        groupBoxStack->setMaximumSize(QSize(400, 16777215));
        groupBoxStack->setCheckable(false);
        groupBoxStack->setChecked(false);
        horizontalLayout_4 = new QHBoxLayout(groupBoxStack);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_4 = new QPushButton(groupBoxStack);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icon/Rectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon1);
        pushButton_4->setCheckable(true);

        horizontalLayout_4->addWidget(pushButton_4);

        label_6 = new QLabel(groupBoxStack);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_6);

        lineEdit_3 = new QLineEdit(groupBoxStack);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(40, 16777215));
        lineEdit_3->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit_3);

        pushButton_3 = new QPushButton(groupBoxStack);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icon/OK.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon2);

        horizontalLayout_4->addWidget(pushButton_3);


        gridLayout_3->addWidget(groupBoxStack, 1, 2, 1, 1);

        groupBox_2 = new QGroupBox(XDlgPyramid);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(400, 16777215));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        slideRangeInline = new CXSliderComplex(groupBox_3);
        slideRangeInline->setObjectName(QString::fromUtf8("slideRangeInline"));

        verticalLayout->addWidget(slideRangeInline);

        slideRangeXline = new CXSliderComplex(groupBox_3);
        slideRangeXline->setObjectName(QString::fromUtf8("slideRangeXline"));

        verticalLayout->addWidget(slideRangeXline);

        slideRangeTimeSlice = new CXSliderComplex(groupBox_3);
        slideRangeTimeSlice->setObjectName(QString::fromUtf8("slideRangeTimeSlice"));

        verticalLayout->addWidget(slideRangeTimeSlice);


        gridLayout->addWidget(groupBox_3, 4, 0, 1, 3);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 2, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 2, 1, 1);

        comboBox = new QComboBox(groupBox_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEnabled(false);

        gridLayout->addWidget(comboBox, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 401, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 6, 0, 1, 3);

        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 3, 0, 1, 2);

        lineEditOutside = new QLineEdit(groupBox_2);
        lineEditOutside->setObjectName(QString::fromUtf8("lineEditOutside"));
        lineEditOutside->setEnabled(false);

        gridLayout->addWidget(lineEditOutside, 3, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 2, 2, 1, 1);

        graphicsView = new XViewPyramid(XDlgPyramid);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(graphicsView, 0, 1, 3, 1);


        retranslateUi(XDlgPyramid);
        QObject::connect(pushButton_2, SIGNAL(clicked()), XDlgPyramid, SLOT(reject()));
        QObject::connect(pushButton, SIGNAL(clicked()), XDlgPyramid, SLOT(accept()));

        QMetaObject::connectSlotsByName(XDlgPyramid);
    } // setupUi

    void retranslateUi(QDialog *XDlgPyramid)
    {
        XDlgPyramid->setWindowTitle(QCoreApplication::translate("XDlgPyramid", "\351\207\221\345\255\227\345\241\224\346\273\244\346\263\242\345\257\271\350\257\235\346\241\206", nullptr));
        groupBox->setTitle(QCoreApplication::translate("XDlgPyramid", "\351\242\204\350\247\210\346\216\247\345\210\266", nullptr));
        label_4->setText(QCoreApplication::translate("XDlgPyramid", "\345\244\204\347\220\206\346\226\271\345\220\221", nullptr));
        radioButtonI->setText(QCoreApplication::translate("XDlgPyramid", "\344\270\273\346\265\213\347\272\277", nullptr));
        radioButtonX->setText(QCoreApplication::translate("XDlgPyramid", "\350\201\224\347\273\234\346\265\213\347\272\277", nullptr));
        radioButtonT->setText(QCoreApplication::translate("XDlgPyramid", "\346\227\266\351\227\264\345\210\207\347\211\207", nullptr));
        label_5->setText(QCoreApplication::translate("XDlgPyramid", "\351\242\204\350\247\210\345\211\226\351\235\242", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("XDlgPyramid", "\346\273\244\346\263\242\345\244\204\347\220\206", nullptr));
        label_8->setText(QCoreApplication::translate("XDlgPyramid", "\350\207\263", nullptr));
        lineEditTo->setText(QCoreApplication::translate("XDlgPyramid", "360", nullptr));
        lineEditStep->setText(QCoreApplication::translate("XDlgPyramid", "1", nullptr));
        lineEditDegree->setText(QCoreApplication::translate("XDlgPyramid", "90", nullptr));
        label_10->setText(QCoreApplication::translate("XDlgPyramid", "\346\255\245\351\225\277", nullptr));
        label_7->setText(QCoreApplication::translate("XDlgPyramid", "\344\273\216", nullptr));
        label_9->setText(QCoreApplication::translate("XDlgPyramid", "l\346\273\244\346\263\242\350\247\222\345\272\246", nullptr));
        lineEditFrom->setText(QCoreApplication::translate("XDlgPyramid", "0", nullptr));
        groupBoxStack->setTitle(QCoreApplication::translate("XDlgPyramid", "\347\233\256\346\240\207\345\214\272\345\237\237\351\200\211\346\213\251", nullptr));
        pushButton_4->setText(QCoreApplication::translate("XDlgPyramid", "\345\214\272\345\237\237\351\200\211\346\213\251", nullptr));
        label_6->setText(QCoreApplication::translate("XDlgPyramid", "\345\273\272\350\256\256\346\273\244\346\263\242\350\247\222\345\272\246", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("XDlgPyramid", "90", nullptr));
        pushButton_3->setText(QCoreApplication::translate("XDlgPyramid", "\345\272\224\347\224\250\350\257\245\350\247\222\345\272\246", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("XDlgPyramid", "\350\276\223\345\207\272\346\216\247\345\210\266", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("XDlgPyramid", "\346\225\260\346\215\256\350\214\203\345\233\264", nullptr));
        label->setText(QCoreApplication::translate("XDlgPyramid", "\350\276\223\345\207\272\345\234\260\351\234\207\344\275\223", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("XDlgPyramid", "90", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("XDlgPyramid", "\344\270\216\351\242\204\350\247\210\346\226\271\345\220\221\347\233\270\345\220\214", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("XDlgPyramid", "\344\270\273\346\265\213\347\272\277", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("XDlgPyramid", "\350\201\224\347\273\234\346\265\213\347\272\277", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("XDlgPyramid", "\346\227\266\351\227\264\345\210\207\347\211\207", nullptr));

#if QT_CONFIG(tooltip)
        comboBox->setToolTip(QCoreApplication::translate("XDlgPyramid", "\351\200\211\346\213\251\347\233\256\346\240\207\345\214\272\345\237\237", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("XDlgPyramid", "\345\244\204\347\220\206\350\247\222\345\272\246", nullptr));
        label_2->setText(QCoreApplication::translate("XDlgPyramid", "\345\244\204\347\220\206\346\226\271\345\220\221", nullptr));
        pushButton->setText(QCoreApplication::translate("XDlgPyramid", "\350\256\241\347\256\227", nullptr));
        pushButton_2->setText(QCoreApplication::translate("XDlgPyramid", "\345\205\263\351\227\255", nullptr));
        checkBox->setText(QCoreApplication::translate("XDlgPyramid", "\345\214\272\345\237\237\345\244\226\345\272\224\347\224\250\344\270\215\345\220\214\350\247\222\345\272\246\346\273\244\346\263\242\357\274\232", nullptr));
        lineEditOutside->setPlaceholderText(QCoreApplication::translate("XDlgPyramid", "180", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XDlgPyramid: public Ui_XDlgPyramid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGPYRAMID_H
