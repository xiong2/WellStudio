/********************************************************************************
** Form generated from reading UI file 'xdlg3dlightingsetting.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLG3DLIGHTINGSETTING_H
#define UI_XDLG3DLIGHTINGSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include "xbuttoncoloredit.h"

QT_BEGIN_NAMESPACE

class Ui_CXDlg3DLightingSetting
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QLineEdit *m_editX;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSlider *m_hsliderX;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QLineEdit *m_editY;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSlider *m_hsliderY;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QLineEdit *m_editZ;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSlider *m_hsliderZ;
    QLabel *label_7;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QRadioButton *m_radioLight1;
    CXButtonColorEdit *m_cbbColor1;
    QRadioButton *m_radioLight2;
    CXButtonColorEdit *m_cbbColor2;
    QRadioButton *m_radioLight3;
    CXButtonColorEdit *m_cbbColor3;
    QRadioButton *m_radioLight4;
    CXButtonColorEdit *m_cbbColor4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *m_ckbLight1;
    QCheckBox *m_ckbLight2;
    QCheckBox *m_ckbLight3;
    QCheckBox *m_ckbLight4;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSlider *m_vsliderAmbient;
    QLineEdit *m_editAmbient;
    QButtonGroup *m_groupStatus;
    QButtonGroup *m_groupLight;

    void setupUi(QDialog *CXDlg3DLightingSetting)
    {
        if (CXDlg3DLightingSetting->objectName().isEmpty())
            CXDlg3DLightingSetting->setObjectName(QString::fromUtf8("CXDlg3DLightingSetting"));
        CXDlg3DLightingSetting->resize(344, 347);
        gridLayout = new QGridLayout(CXDlg3DLightingSetting);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_3 = new QGroupBox(CXDlg3DLightingSetting);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(0, 0));
        groupBox_3->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_6->addWidget(label_8);

        m_editX = new QLineEdit(groupBox_3);
        m_editX->setObjectName(QString::fromUtf8("m_editX"));
        m_editX->setMinimumSize(QSize(200, 0));
        m_editX->setReadOnly(true);

        horizontalLayout_6->addWidget(m_editX);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        m_hsliderX = new QSlider(groupBox_3);
        m_hsliderX->setObjectName(QString::fromUtf8("m_hsliderX"));
        m_hsliderX->setMinimum(-1000);
        m_hsliderX->setMaximum(1000);
        m_hsliderX->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(m_hsliderX);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_5);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_7->addWidget(label_9);

        m_editY = new QLineEdit(groupBox_3);
        m_editY->setObjectName(QString::fromUtf8("m_editY"));
        m_editY->setMinimumSize(QSize(200, 0));
        m_editY->setReadOnly(true);

        horizontalLayout_7->addWidget(m_editY);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_3);

        m_hsliderY = new QSlider(groupBox_3);
        m_hsliderY->setObjectName(QString::fromUtf8("m_hsliderY"));
        m_hsliderY->setMinimum(-1000);
        m_hsliderY->setMaximum(1000);
        m_hsliderY->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(m_hsliderY);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_6);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_8->addWidget(label_10);

        m_editZ = new QLineEdit(groupBox_3);
        m_editZ->setObjectName(QString::fromUtf8("m_editZ"));
        m_editZ->setMinimumSize(QSize(200, 0));
        m_editZ->setReadOnly(true);

        horizontalLayout_8->addWidget(m_editZ);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_4);

        m_hsliderZ = new QSlider(groupBox_3);
        m_hsliderZ->setObjectName(QString::fromUtf8("m_hsliderZ"));
        m_hsliderZ->setMinimum(-1000);
        m_hsliderZ->setMaximum(1000);
        m_hsliderZ->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(m_hsliderZ);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_7);


        verticalLayout_2->addLayout(horizontalLayout_5);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox = new QGroupBox(CXDlg3DLightingSetting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setFlat(true);
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        m_radioLight1 = new QRadioButton(groupBox);
        m_groupLight = new QButtonGroup(CXDlg3DLightingSetting);
        m_groupLight->setObjectName(QString::fromUtf8("m_groupLight"));
        m_groupLight->addButton(m_radioLight1);
        m_radioLight1->setObjectName(QString::fromUtf8("m_radioLight1"));
        m_radioLight1->setChecked(true);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, m_radioLight1);

        m_cbbColor1 = new CXButtonColorEdit(groupBox);
        m_cbbColor1->setObjectName(QString::fromUtf8("m_cbbColor1"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_cbbColor1->sizePolicy().hasHeightForWidth());
        m_cbbColor1->setSizePolicy(sizePolicy2);
        m_cbbColor1->setMinimumSize(QSize(130, 0));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, m_cbbColor1);

        m_radioLight2 = new QRadioButton(groupBox);
        m_groupLight->addButton(m_radioLight2);
        m_radioLight2->setObjectName(QString::fromUtf8("m_radioLight2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, m_radioLight2);

        m_cbbColor2 = new CXButtonColorEdit(groupBox);
        m_cbbColor2->setObjectName(QString::fromUtf8("m_cbbColor2"));
        sizePolicy2.setHeightForWidth(m_cbbColor2->sizePolicy().hasHeightForWidth());
        m_cbbColor2->setSizePolicy(sizePolicy2);
        m_cbbColor2->setMinimumSize(QSize(130, 0));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, m_cbbColor2);

        m_radioLight3 = new QRadioButton(groupBox);
        m_groupLight->addButton(m_radioLight3);
        m_radioLight3->setObjectName(QString::fromUtf8("m_radioLight3"));
        m_radioLight3->setEnabled(false);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, m_radioLight3);

        m_cbbColor3 = new CXButtonColorEdit(groupBox);
        m_cbbColor3->setObjectName(QString::fromUtf8("m_cbbColor3"));
        sizePolicy2.setHeightForWidth(m_cbbColor3->sizePolicy().hasHeightForWidth());
        m_cbbColor3->setSizePolicy(sizePolicy2);
        m_cbbColor3->setMinimumSize(QSize(130, 0));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, m_cbbColor3);

        m_radioLight4 = new QRadioButton(groupBox);
        m_groupLight->addButton(m_radioLight4);
        m_radioLight4->setObjectName(QString::fromUtf8("m_radioLight4"));
        m_radioLight4->setEnabled(false);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, m_radioLight4);

        m_cbbColor4 = new CXButtonColorEdit(groupBox);
        m_cbbColor4->setObjectName(QString::fromUtf8("m_cbbColor4"));
        sizePolicy2.setHeightForWidth(m_cbbColor4->sizePolicy().hasHeightForWidth());
        m_cbbColor4->setSizePolicy(sizePolicy2);
        m_cbbColor4->setMinimumSize(QSize(130, 0));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, m_cbbColor4);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(CXDlg3DLightingSetting);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFlat(true);
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_ckbLight1 = new QCheckBox(groupBox_2);
        m_groupStatus = new QButtonGroup(CXDlg3DLightingSetting);
        m_groupStatus->setObjectName(QString::fromUtf8("m_groupStatus"));
        m_groupStatus->setExclusive(false);
        m_groupStatus->addButton(m_ckbLight1);
        m_ckbLight1->setObjectName(QString::fromUtf8("m_ckbLight1"));
        m_ckbLight1->setChecked(true);

        verticalLayout->addWidget(m_ckbLight1);

        m_ckbLight2 = new QCheckBox(groupBox_2);
        m_groupStatus->addButton(m_ckbLight2);
        m_ckbLight2->setObjectName(QString::fromUtf8("m_ckbLight2"));
        m_ckbLight2->setChecked(true);

        verticalLayout->addWidget(m_ckbLight2);

        m_ckbLight3 = new QCheckBox(groupBox_2);
        m_groupStatus->addButton(m_ckbLight3);
        m_ckbLight3->setObjectName(QString::fromUtf8("m_ckbLight3"));

        verticalLayout->addWidget(m_ckbLight3);

        m_ckbLight4 = new QCheckBox(groupBox_2);
        m_groupStatus->addButton(m_ckbLight4);
        m_ckbLight4->setObjectName(QString::fromUtf8("m_ckbLight4"));

        verticalLayout->addWidget(m_ckbLight4);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_4 = new QGroupBox(CXDlg3DLightingSetting);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFlat(true);
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_vsliderAmbient = new QSlider(groupBox_4);
        m_vsliderAmbient->setObjectName(QString::fromUtf8("m_vsliderAmbient"));
        m_vsliderAmbient->setMaximum(100);
        m_vsliderAmbient->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(m_vsliderAmbient);


        verticalLayout_3->addLayout(horizontalLayout_2);

        m_editAmbient = new QLineEdit(groupBox_4);
        m_editAmbient->setObjectName(QString::fromUtf8("m_editAmbient"));
        sizePolicy2.setHeightForWidth(m_editAmbient->sizePolicy().hasHeightForWidth());
        m_editAmbient->setSizePolicy(sizePolicy2);
        m_editAmbient->setMaximumSize(QSize(40, 16777215));
        m_editAmbient->setReadOnly(true);

        verticalLayout_3->addWidget(m_editAmbient);


        gridLayout->addWidget(groupBox_4, 1, 1, 1, 1);


        retranslateUi(CXDlg3DLightingSetting);
        QObject::connect(m_ckbLight1, SIGNAL(toggled(bool)), m_radioLight1, SLOT(setEnabled(bool)));
        QObject::connect(m_ckbLight2, SIGNAL(toggled(bool)), m_radioLight2, SLOT(setEnabled(bool)));
        QObject::connect(m_ckbLight3, SIGNAL(toggled(bool)), m_radioLight3, SLOT(setEnabled(bool)));
        QObject::connect(m_ckbLight4, SIGNAL(toggled(bool)), m_radioLight4, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(CXDlg3DLightingSetting);
    } // setupUi

    void retranslateUi(QDialog *CXDlg3DLightingSetting)
    {
        CXDlg3DLightingSetting->setWindowTitle(QCoreApplication::translate("CXDlg3DLightingSetting", "Light Settting", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CXDlg3DLightingSetting", "Light Position", nullptr));
        label_8->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "X = ", nullptr));
        label_2->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "-1.0", nullptr));
        label_5->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "1.0", nullptr));
        label_9->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Y = ", nullptr));
        label_3->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "-1.0", nullptr));
        label_6->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "1.0", nullptr));
        label_10->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Z = ", nullptr));
        label_4->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "-1.0", nullptr));
        label_7->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "1.0", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXDlg3DLightingSetting", "Current Editing Light", nullptr));
        m_radioLight1->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Light1", nullptr));
        m_radioLight2->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Light2", nullptr));
        m_radioLight3->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Light3", nullptr));
        m_radioLight4->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Light4", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXDlg3DLightingSetting", "Light Status", nullptr));
        m_ckbLight1->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Light1", nullptr));
        m_ckbLight2->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Light2", nullptr));
        m_ckbLight3->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Light3", nullptr));
        m_ckbLight4->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Light4", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("CXDlg3DLightingSetting", "Light Intensity", nullptr));
        label->setText(QCoreApplication::translate("CXDlg3DLightingSetting", "Ambient", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXDlg3DLightingSetting: public Ui_CXDlg3DLightingSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLG3DLIGHTINGSETTING_H
