/********************************************************************************
** Form generated from reading UI file 'xpagefile3dsurface.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEFILE3DSURFACE_H
#define UI_XPAGEFILE3DSURFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RLPageFile3DSurface
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QFrame *line;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_10;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *m_pLineEditFileName;
    QComboBox *m_pComboDomain;
    QComboBox *m_pComboUTM;
    QLineEdit *m_pLineEdtHorizoName;
    QComboBox *m_pComboParent;
    QTableWidget *m_pTable;
    QCheckBox *m_pCheckNegateZ;
    QSpacerItem *verticalSpacer;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QFrame *line_2;
    QCheckBox *checkBoxZone;

    void setupUi(QWidget *RLPageFile3DSurface)
    {
        if (RLPageFile3DSurface->objectName().isEmpty())
            RLPageFile3DSurface->setObjectName(QString::fromUtf8("RLPageFile3DSurface"));
        RLPageFile3DSurface->resize(725, 444);
        gridLayout = new QGridLayout(RLPageFile3DSurface);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(RLPageFile3DSurface);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(85, 20));
        label_5->setMaximumSize(QSize(70, 16777215));
        QPalette palette;
        QBrush brush(QColor(0, 70, 213, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(118, 116, 108, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_5->setPalette(palette);

        horizontalLayout_2->addWidget(label_5);

        line = new QFrame(RLPageFile3DSurface);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        label_13 = new QLabel(RLPageFile3DSurface);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(10, 0));
        label_13->setMaximumSize(QSize(10, 16777215));

        gridLayout->addWidget(label_13, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(RLPageFile3DSurface);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(RLPageFile3DSurface);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_9 = new QLabel(RLPageFile3DSurface);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);

        label_8 = new QLabel(RLPageFile3DSurface);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        label_10 = new QLabel(RLPageFile3DSurface);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout->addWidget(label_10);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        m_pLineEditFileName = new QLineEdit(RLPageFile3DSurface);
        m_pLineEditFileName->setObjectName(QString::fromUtf8("m_pLineEditFileName"));

        verticalLayout_2->addWidget(m_pLineEditFileName);

        m_pComboDomain = new QComboBox(RLPageFile3DSurface);
        m_pComboDomain->addItem(QString());
        m_pComboDomain->addItem(QString());
        m_pComboDomain->addItem(QString());
        m_pComboDomain->setObjectName(QString::fromUtf8("m_pComboDomain"));

        verticalLayout_2->addWidget(m_pComboDomain);

        m_pComboUTM = new QComboBox(RLPageFile3DSurface);
        m_pComboUTM->addItem(QString());
        m_pComboUTM->setObjectName(QString::fromUtf8("m_pComboUTM"));

        verticalLayout_2->addWidget(m_pComboUTM);

        m_pLineEdtHorizoName = new QLineEdit(RLPageFile3DSurface);
        m_pLineEdtHorizoName->setObjectName(QString::fromUtf8("m_pLineEdtHorizoName"));

        verticalLayout_2->addWidget(m_pLineEdtHorizoName);

        m_pComboParent = new QComboBox(RLPageFile3DSurface);
        m_pComboParent->addItem(QString());
        m_pComboParent->setObjectName(QString::fromUtf8("m_pComboParent"));

        verticalLayout_2->addWidget(m_pComboParent);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 2, 2);

        m_pTable = new QTableWidget(RLPageFile3DSurface);
        m_pTable->setObjectName(QString::fromUtf8("m_pTable"));

        gridLayout->addWidget(m_pTable, 4, 0, 1, 2);

        m_pCheckNegateZ = new QCheckBox(RLPageFile3DSurface);
        m_pCheckNegateZ->setObjectName(QString::fromUtf8("m_pCheckNegateZ"));

        gridLayout->addWidget(m_pCheckNegateZ, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 0, 1, 1);

        label_15 = new QLabel(RLPageFile3DSurface);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(10, 0));
        label_15->setMaximumSize(QSize(10, 16777215));

        gridLayout->addWidget(label_15, 7, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_6 = new QLabel(RLPageFile3DSurface);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(60, 20));
        label_6->setMaximumSize(QSize(50, 16777215));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_6->setPalette(palette1);

        horizontalLayout_3->addWidget(label_6);

        line_2 = new QFrame(RLPageFile3DSurface);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_2);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 2);

        checkBoxZone = new QCheckBox(RLPageFile3DSurface);
        checkBoxZone->setObjectName(QString::fromUtf8("checkBoxZone"));
        checkBoxZone->setChecked(true);

        gridLayout->addWidget(checkBoxZone, 6, 0, 1, 1);

        label_13->raise();
        m_pTable->raise();
        label_15->raise();
        m_pCheckNegateZ->raise();
        checkBoxZone->raise();

        retranslateUi(RLPageFile3DSurface);

        QMetaObject::connectSlotsByName(RLPageFile3DSurface);
    } // setupUi

    void retranslateUi(QWidget *RLPageFile3DSurface)
    {
        RLPageFile3DSurface->setWindowTitle(QCoreApplication::translate("RLPageFile3DSurface", "Form", nullptr));
        label_5->setText(QCoreApplication::translate("RLPageFile3DSurface", "Data property", nullptr));
        label_13->setText(QString());
        label->setText(QCoreApplication::translate("RLPageFile3DSurface", "File name", nullptr));
        label_2->setText(QCoreApplication::translate("RLPageFile3DSurface", "Domain", nullptr));
        label_9->setText(QCoreApplication::translate("RLPageFile3DSurface", "3-D seismic survey   ", nullptr));
        label_8->setText(QCoreApplication::translate("RLPageFile3DSurface", "Horizon name", nullptr));
        label_10->setText(QCoreApplication::translate("RLPageFile3DSurface", "Parent", nullptr));
        m_pComboDomain->setItemText(0, QCoreApplication::translate("RLPageFile3DSurface", "NULL", nullptr));
        m_pComboDomain->setItemText(1, QCoreApplication::translate("RLPageFile3DSurface", "Time", nullptr));
        m_pComboDomain->setItemText(2, QCoreApplication::translate("RLPageFile3DSurface", "Depth", nullptr));

        m_pComboUTM->setItemText(0, QCoreApplication::translate("RLPageFile3DSurface", "NULL", nullptr));

        m_pComboParent->setItemText(0, QCoreApplication::translate("RLPageFile3DSurface", "NULL", nullptr));

        m_pCheckNegateZ->setText(QCoreApplication::translate("RLPageFile3DSurface", "Negate Z Values", nullptr));
        label_15->setText(QString());
        label_6->setText(QCoreApplication::translate("RLPageFile3DSurface", "Summary", nullptr));
        checkBoxZone->setText(QCoreApplication::translate("RLPageFile3DSurface", "Without the zone numbers", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RLPageFile3DSurface: public Ui_RLPageFile3DSurface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEFILE3DSURFACE_H
