/********************************************************************************
** Form generated from reading UI file 'xsubgridsetting.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XSUBGRIDSETTING_H
#define UI_XSUBGRIDSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CXSubGridSetting
{
public:
    QGridLayout *gridLayout;
    QSlider *m_hSliderMinJ;
    QSpinBox *m_spinBoxMinI;
    QLabel *label_2;
    QLabel *label_6;
    QSlider *m_hSliderMaxJ;
    QSpinBox *m_spinBoxMinJ;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_3;
    QSlider *m_hSliderMaxI;
    QSpinBox *m_spinBoxMaxI;
    QSpinBox *m_spinBoxMaxJ;
    QSpinBox *m_spinBoxMaxK;
    QSpinBox *m_spinBoxMinK;
    QSlider *m_hSliderMinI;
    QSlider *m_hSliderMinK;
    QSlider *m_hSliderMaxK;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btReset;
    QPushButton *m_btClose;

    void setupUi(QDialog *CXSubGridSetting)
    {
        if (CXSubGridSetting->objectName().isEmpty())
            CXSubGridSetting->setObjectName(QString::fromUtf8("CXSubGridSetting"));
        CXSubGridSetting->resize(400, 300);
        gridLayout = new QGridLayout(CXSubGridSetting);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_hSliderMinJ = new QSlider(CXSubGridSetting);
        m_hSliderMinJ->setObjectName(QString::fromUtf8("m_hSliderMinJ"));
        m_hSliderMinJ->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_hSliderMinJ, 3, 1, 1, 1);

        m_spinBoxMinI = new QSpinBox(CXSubGridSetting);
        m_spinBoxMinI->setObjectName(QString::fromUtf8("m_spinBoxMinI"));

        gridLayout->addWidget(m_spinBoxMinI, 1, 3, 1, 1);

        label_2 = new QLabel(CXSubGridSetting);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_6 = new QLabel(CXSubGridSetting);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        m_hSliderMaxJ = new QSlider(CXSubGridSetting);
        m_hSliderMaxJ->setObjectName(QString::fromUtf8("m_hSliderMaxJ"));
        m_hSliderMaxJ->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_hSliderMaxJ, 4, 1, 1, 1);

        m_spinBoxMinJ = new QSpinBox(CXSubGridSetting);
        m_spinBoxMinJ->setObjectName(QString::fromUtf8("m_spinBoxMinJ"));

        gridLayout->addWidget(m_spinBoxMinJ, 3, 3, 1, 1);

        label_4 = new QLabel(CXSubGridSetting);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_5 = new QLabel(CXSubGridSetting);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label = new QLabel(CXSubGridSetting);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(CXSubGridSetting);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        m_hSliderMaxI = new QSlider(CXSubGridSetting);
        m_hSliderMaxI->setObjectName(QString::fromUtf8("m_hSliderMaxI"));
        m_hSliderMaxI->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_hSliderMaxI, 2, 1, 1, 1);

        m_spinBoxMaxI = new QSpinBox(CXSubGridSetting);
        m_spinBoxMaxI->setObjectName(QString::fromUtf8("m_spinBoxMaxI"));

        gridLayout->addWidget(m_spinBoxMaxI, 2, 3, 1, 1);

        m_spinBoxMaxJ = new QSpinBox(CXSubGridSetting);
        m_spinBoxMaxJ->setObjectName(QString::fromUtf8("m_spinBoxMaxJ"));

        gridLayout->addWidget(m_spinBoxMaxJ, 4, 3, 1, 1);

        m_spinBoxMaxK = new QSpinBox(CXSubGridSetting);
        m_spinBoxMaxK->setObjectName(QString::fromUtf8("m_spinBoxMaxK"));

        gridLayout->addWidget(m_spinBoxMaxK, 6, 3, 1, 1);

        m_spinBoxMinK = new QSpinBox(CXSubGridSetting);
        m_spinBoxMinK->setObjectName(QString::fromUtf8("m_spinBoxMinK"));

        gridLayout->addWidget(m_spinBoxMinK, 5, 3, 1, 1);

        m_hSliderMinI = new QSlider(CXSubGridSetting);
        m_hSliderMinI->setObjectName(QString::fromUtf8("m_hSliderMinI"));
        m_hSliderMinI->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_hSliderMinI, 1, 1, 1, 1);

        m_hSliderMinK = new QSlider(CXSubGridSetting);
        m_hSliderMinK->setObjectName(QString::fromUtf8("m_hSliderMinK"));
        m_hSliderMinK->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_hSliderMinK, 5, 1, 1, 1);

        m_hSliderMaxK = new QSlider(CXSubGridSetting);
        m_hSliderMaxK->setObjectName(QString::fromUtf8("m_hSliderMaxK"));
        m_hSliderMaxK->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(m_hSliderMaxK, 6, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btReset = new QPushButton(CXSubGridSetting);
        m_btReset->setObjectName(QString::fromUtf8("m_btReset"));

        horizontalLayout->addWidget(m_btReset);

        m_btClose = new QPushButton(CXSubGridSetting);
        m_btClose->setObjectName(QString::fromUtf8("m_btClose"));

        horizontalLayout->addWidget(m_btClose);


        gridLayout->addLayout(horizontalLayout, 8, 0, 1, 4);


        retranslateUi(CXSubGridSetting);
        QObject::connect(m_hSliderMinI, SIGNAL(valueChanged(int)), m_spinBoxMinI, SLOT(setValue(int)));
        QObject::connect(m_hSliderMaxI, SIGNAL(valueChanged(int)), m_spinBoxMaxI, SLOT(setValue(int)));
        QObject::connect(m_hSliderMinJ, SIGNAL(valueChanged(int)), m_spinBoxMinJ, SLOT(setValue(int)));
        QObject::connect(m_hSliderMaxJ, SIGNAL(valueChanged(int)), m_spinBoxMaxJ, SLOT(setValue(int)));
        QObject::connect(m_hSliderMinK, SIGNAL(valueChanged(int)), m_spinBoxMinK, SLOT(setValue(int)));
        QObject::connect(m_hSliderMaxK, SIGNAL(valueChanged(int)), m_spinBoxMaxK, SLOT(setValue(int)));
        QObject::connect(m_spinBoxMinI, SIGNAL(valueChanged(int)), m_hSliderMinI, SLOT(setValue(int)));
        QObject::connect(m_spinBoxMaxI, SIGNAL(valueChanged(int)), m_hSliderMaxI, SLOT(setValue(int)));
        QObject::connect(m_spinBoxMinJ, SIGNAL(valueChanged(int)), m_hSliderMinJ, SLOT(setValue(int)));
        QObject::connect(m_spinBoxMaxJ, SIGNAL(valueChanged(int)), m_hSliderMaxJ, SLOT(setValue(int)));
        QObject::connect(m_spinBoxMinK, SIGNAL(valueChanged(int)), m_hSliderMinK, SLOT(setValue(int)));
        QObject::connect(m_spinBoxMaxK, SIGNAL(valueChanged(int)), m_hSliderMaxK, SLOT(setValue(int)));
        QObject::connect(m_btClose, SIGNAL(clicked()), CXSubGridSetting, SLOT(accept()));

        QMetaObject::connectSlotsByName(CXSubGridSetting);
    } // setupUi

    void retranslateUi(QDialog *CXSubGridSetting)
    {
        CXSubGridSetting->setWindowTitle(QCoreApplication::translate("CXSubGridSetting", "Geometry", nullptr));
        label_2->setText(QCoreApplication::translate("CXSubGridSetting", "Maximum I:", nullptr));
        label_6->setText(QCoreApplication::translate("CXSubGridSetting", "Maximum K:", nullptr));
        label_4->setText(QCoreApplication::translate("CXSubGridSetting", "Maximum J:", nullptr));
        label_5->setText(QCoreApplication::translate("CXSubGridSetting", "Minimum K:", nullptr));
        label->setText(QCoreApplication::translate("CXSubGridSetting", "Minimum I:", nullptr));
        label_3->setText(QCoreApplication::translate("CXSubGridSetting", "Minimum J:", nullptr));
        m_btReset->setText(QCoreApplication::translate("CXSubGridSetting", "Reset", nullptr));
        m_btClose->setText(QCoreApplication::translate("CXSubGridSetting", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXSubGridSetting: public Ui_CXSubGridSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XSUBGRIDSETTING_H
