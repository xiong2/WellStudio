/********************************************************************************
** Form generated from reading UI file 'xdlglfmupscaling.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGLFMUPSCALING_H
#define UI_XDLGLFMUPSCALING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_DlgLFMUpscaling
{
public:
    QGridLayout *gridLayout_2;
    QLabel *label;
    QListWidget *m_pListWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *m_pRadioAri;
    QRadioButton *m_pRadioGeo;
    QRadioButton *m_pRadioMedian;
    QRadioButton *m_pRadioRMS;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DlgLFMUpscaling)
    {
        if (DlgLFMUpscaling->objectName().isEmpty())
            DlgLFMUpscaling->setObjectName(QString::fromUtf8("DlgLFMUpscaling"));
        DlgLFMUpscaling->resize(545, 448);
        gridLayout_2 = new QGridLayout(DlgLFMUpscaling);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(DlgLFMUpscaling);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        m_pListWidget = new QListWidget(DlgLFMUpscaling);
        m_pListWidget->setObjectName(QString::fromUtf8("m_pListWidget"));

        gridLayout_2->addWidget(m_pListWidget, 1, 0, 1, 2);

        groupBox = new QGroupBox(DlgLFMUpscaling);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pRadioAri = new QRadioButton(groupBox);
        m_pRadioAri->setObjectName(QString::fromUtf8("m_pRadioAri"));
        m_pRadioAri->setChecked(true);

        gridLayout->addWidget(m_pRadioAri, 0, 0, 1, 1);

        m_pRadioGeo = new QRadioButton(groupBox);
        m_pRadioGeo->setObjectName(QString::fromUtf8("m_pRadioGeo"));

        gridLayout->addWidget(m_pRadioGeo, 0, 1, 1, 1);

        m_pRadioMedian = new QRadioButton(groupBox);
        m_pRadioMedian->setObjectName(QString::fromUtf8("m_pRadioMedian"));

        gridLayout->addWidget(m_pRadioMedian, 0, 3, 1, 1);

        m_pRadioRMS = new QRadioButton(groupBox);
        m_pRadioRMS->setObjectName(QString::fromUtf8("m_pRadioRMS"));

        gridLayout->addWidget(m_pRadioRMS, 0, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 2);

        buttonBox = new QDialogButtonBox(DlgLFMUpscaling);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 3, 1, 1, 1);

        label->raise();
        buttonBox->raise();
        m_pListWidget->raise();
        groupBox->raise();
        m_pRadioRMS->raise();

        retranslateUi(DlgLFMUpscaling);
        QObject::connect(buttonBox, SIGNAL(accepted()), DlgLFMUpscaling, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DlgLFMUpscaling, SLOT(reject()));

        QMetaObject::connectSlotsByName(DlgLFMUpscaling);
    } // setupUi

    void retranslateUi(QDialog *DlgLFMUpscaling)
    {
        DlgLFMUpscaling->setWindowTitle(QCoreApplication::translate("DlgLFMUpscaling", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DlgLFMUpscaling", "Please Select Well Curves", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DlgLFMUpscaling", "Average Method", nullptr));
        m_pRadioAri->setText(QCoreApplication::translate("DlgLFMUpscaling", "Arithmetic Mean", nullptr));
        m_pRadioGeo->setText(QCoreApplication::translate("DlgLFMUpscaling", "Geometric Mean", nullptr));
        m_pRadioMedian->setText(QCoreApplication::translate("DlgLFMUpscaling", "Median", nullptr));
        m_pRadioRMS->setText(QCoreApplication::translate("DlgLFMUpscaling", "RMS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DlgLFMUpscaling: public Ui_DlgLFMUpscaling {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGLFMUPSCALING_H
