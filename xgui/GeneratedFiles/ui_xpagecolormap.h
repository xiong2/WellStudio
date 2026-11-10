/********************************************************************************
** Form generated from reading UI file 'xpagecolormap.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGECOLORMAP_H
#define UI_XPAGECOLORMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include "xbasepropertypage.h"
#include "xbuttoncoloredit.h"
#include "xcolormapcombo.h"
#include "xcolormapeditor.h"

QT_BEGIN_NAMESPACE

class Ui_CXPageColormap
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *m_rbTransparent;
    QRadioButton *m_rbSpecified;
    CXButtonColorEdit *m_btColor;
    QLabel *m_labelMin;
    QLabel *m_labelMax;
    QFrame *line;
    QGroupBox *grpTemplate;
    QGridLayout *gridLayout_2;
    CXColormapCombo *m_cbbTemplate;
    QPushButton *m_btRetrieve;
    QPushButton *m_btSaveAs;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QCheckBox *m_cbRealtime;
    QCheckBox *m_cbFreeDrawing;
    QPushButton *m_btReset;
    QPushButton *m_btFlip;
    CXColormapEditor *colormapEditor;
    QGroupBox *grpDataRange;
    QGridLayout *gridLayout_3;
    QLabel *label_min;
    QLabel *label_max;
    QLineEdit *m_edMin;
    QLineEdit *m_edMax;
    QPushButton *m_btDefault;
    QRadioButton *m_rbManual;
    QRadioButton *m_rbAutomatic;
    QCheckBox *m_cbZeroIsInvalid;
    QLabel *m_labelMessage;

    void setupUi(CXBasePropertyPage *CXPageColormap)
    {
        if (CXPageColormap->objectName().isEmpty())
            CXPageColormap->setObjectName(QString::fromUtf8("CXPageColormap"));
        CXPageColormap->resize(722, 440);
        gridLayout = new QGridLayout(CXPageColormap);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_2 = new QGroupBox(CXPageColormap);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_rbTransparent = new QRadioButton(groupBox_2);
        m_rbTransparent->setObjectName(QString::fromUtf8("m_rbTransparent"));
        m_rbTransparent->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(m_rbTransparent);

        m_rbSpecified = new QRadioButton(groupBox_2);
        m_rbSpecified->setObjectName(QString::fromUtf8("m_rbSpecified"));
        m_rbSpecified->setFocusPolicy(Qt::NoFocus);
        m_rbSpecified->setChecked(true);

        verticalLayout->addWidget(m_rbSpecified);

        m_btColor = new CXButtonColorEdit(groupBox_2);
        m_btColor->setObjectName(QString::fromUtf8("m_btColor"));
        m_btColor->setFocusPolicy(Qt::ClickFocus);
        m_btColor->setFlat(false);

        verticalLayout->addWidget(m_btColor);


        gridLayout->addWidget(groupBox_2, 5, 3, 1, 1);

        m_labelMin = new QLabel(CXPageColormap);
        m_labelMin->setObjectName(QString::fromUtf8("m_labelMin"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_labelMin->sizePolicy().hasHeightForWidth());
        m_labelMin->setSizePolicy(sizePolicy);

        gridLayout->addWidget(m_labelMin, 0, 0, 1, 2);

        m_labelMax = new QLabel(CXPageColormap);
        m_labelMax->setObjectName(QString::fromUtf8("m_labelMax"));
        sizePolicy.setHeightForWidth(m_labelMax->sizePolicy().hasHeightForWidth());
        m_labelMax->setSizePolicy(sizePolicy);
        m_labelMax->setLayoutDirection(Qt::LeftToRight);
        m_labelMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(m_labelMax, 0, 2, 1, 2);

        line = new QFrame(CXPageColormap);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 4);

        grpTemplate = new QGroupBox(CXPageColormap);
        grpTemplate->setObjectName(QString::fromUtf8("grpTemplate"));
        gridLayout_2 = new QGridLayout(grpTemplate);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        m_cbbTemplate = new CXColormapCombo(grpTemplate);
        m_cbbTemplate->setObjectName(QString::fromUtf8("m_cbbTemplate"));

        gridLayout_2->addWidget(m_cbbTemplate, 0, 0, 1, 2);

        m_btRetrieve = new QPushButton(grpTemplate);
        m_btRetrieve->setObjectName(QString::fromUtf8("m_btRetrieve"));
        m_btRetrieve->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(m_btRetrieve, 1, 0, 1, 1);

        m_btSaveAs = new QPushButton(grpTemplate);
        m_btSaveAs->setObjectName(QString::fromUtf8("m_btSaveAs"));
        m_btSaveAs->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(m_btSaveAs, 1, 1, 1, 1);


        gridLayout->addWidget(grpTemplate, 5, 0, 1, 1);

        groupBox = new QGroupBox(CXPageColormap);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        m_cbRealtime = new QCheckBox(groupBox);
        m_cbRealtime->setObjectName(QString::fromUtf8("m_cbRealtime"));
        m_cbRealtime->setEnabled(true);
        m_cbRealtime->setFocusPolicy(Qt::NoFocus);
        m_cbRealtime->setChecked(false);

        gridLayout_4->addWidget(m_cbRealtime, 3, 0, 1, 1);

        m_cbFreeDrawing = new QCheckBox(groupBox);
        m_cbFreeDrawing->setObjectName(QString::fromUtf8("m_cbFreeDrawing"));
        m_cbFreeDrawing->setFocusPolicy(Qt::NoFocus);

        gridLayout_4->addWidget(m_cbFreeDrawing, 3, 1, 1, 1);

        m_btReset = new QPushButton(groupBox);
        m_btReset->setObjectName(QString::fromUtf8("m_btReset"));
        m_btReset->setFocusPolicy(Qt::NoFocus);

        gridLayout_4->addWidget(m_btReset, 1, 0, 1, 2);

        m_btFlip = new QPushButton(groupBox);
        m_btFlip->setObjectName(QString::fromUtf8("m_btFlip"));
        m_btFlip->setFocusPolicy(Qt::NoFocus);

        gridLayout_4->addWidget(m_btFlip, 0, 0, 1, 2);


        gridLayout->addWidget(groupBox, 5, 2, 1, 1);

        colormapEditor = new CXColormapEditor(CXPageColormap);
        colormapEditor->setObjectName(QString::fromUtf8("colormapEditor"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(colormapEditor->sizePolicy().hasHeightForWidth());
        colormapEditor->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(colormapEditor, 2, 0, 2, 4);

        grpDataRange = new QGroupBox(CXPageColormap);
        grpDataRange->setObjectName(QString::fromUtf8("grpDataRange"));
        sizePolicy.setHeightForWidth(grpDataRange->sizePolicy().hasHeightForWidth());
        grpDataRange->setSizePolicy(sizePolicy);
        grpDataRange->setMinimumSize(QSize(0, 55));
        gridLayout_3 = new QGridLayout(grpDataRange);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_min = new QLabel(grpDataRange);
        label_min->setObjectName(QString::fromUtf8("label_min"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_min->sizePolicy().hasHeightForWidth());
        label_min->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_min, 2, 0, 1, 1);

        label_max = new QLabel(grpDataRange);
        label_max->setObjectName(QString::fromUtf8("label_max"));
        sizePolicy2.setHeightForWidth(label_max->sizePolicy().hasHeightForWidth());
        label_max->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_max, 3, 0, 1, 1);

        m_edMin = new QLineEdit(grpDataRange);
        m_edMin->setObjectName(QString::fromUtf8("m_edMin"));
        m_edMin->setEnabled(false);
        sizePolicy.setHeightForWidth(m_edMin->sizePolicy().hasHeightForWidth());
        m_edMin->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_edMin, 2, 1, 1, 2);

        m_edMax = new QLineEdit(grpDataRange);
        m_edMax->setObjectName(QString::fromUtf8("m_edMax"));
        m_edMax->setEnabled(false);
        sizePolicy.setHeightForWidth(m_edMax->sizePolicy().hasHeightForWidth());
        m_edMax->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_edMax, 3, 1, 1, 2);

        m_btDefault = new QPushButton(grpDataRange);
        m_btDefault->setObjectName(QString::fromUtf8("m_btDefault"));
        m_btDefault->setEnabled(false);
        m_btDefault->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(m_btDefault, 4, 3, 1, 1);

        m_rbManual = new QRadioButton(grpDataRange);
        m_rbManual->setObjectName(QString::fromUtf8("m_rbManual"));
        m_rbManual->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(m_rbManual, 3, 3, 1, 1);

        m_rbAutomatic = new QRadioButton(grpDataRange);
        m_rbAutomatic->setObjectName(QString::fromUtf8("m_rbAutomatic"));
        m_rbAutomatic->setFocusPolicy(Qt::NoFocus);
        m_rbAutomatic->setChecked(true);

        gridLayout_3->addWidget(m_rbAutomatic, 2, 3, 1, 1);

        m_cbZeroIsInvalid = new QCheckBox(grpDataRange);
        m_cbZeroIsInvalid->setObjectName(QString::fromUtf8("m_cbZeroIsInvalid"));
        m_cbZeroIsInvalid->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(m_cbZeroIsInvalid, 4, 0, 1, 3);


        gridLayout->addWidget(grpDataRange, 5, 1, 1, 1);

        m_labelMessage = new QLabel(CXPageColormap);
        m_labelMessage->setObjectName(QString::fromUtf8("m_labelMessage"));
        sizePolicy.setHeightForWidth(m_labelMessage->sizePolicy().hasHeightForWidth());
        m_labelMessage->setSizePolicy(sizePolicy);
        m_labelMessage->setFrameShape(QFrame::Panel);
        m_labelMessage->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(m_labelMessage, 6, 0, 1, 4);

        QWidget::setTabOrder(m_edMin, m_edMax);
        QWidget::setTabOrder(m_edMax, m_btColor);
        QWidget::setTabOrder(m_btColor, m_cbbTemplate);
        QWidget::setTabOrder(m_cbbTemplate, m_btRetrieve);
        QWidget::setTabOrder(m_btRetrieve, m_btSaveAs);
        QWidget::setTabOrder(m_btSaveAs, m_cbRealtime);
        QWidget::setTabOrder(m_cbRealtime, m_cbFreeDrawing);
        QWidget::setTabOrder(m_cbFreeDrawing, m_btReset);
        QWidget::setTabOrder(m_btReset, m_btFlip);
        QWidget::setTabOrder(m_btFlip, m_rbTransparent);
        QWidget::setTabOrder(m_rbTransparent, m_rbSpecified);
        QWidget::setTabOrder(m_rbSpecified, m_btDefault);
        QWidget::setTabOrder(m_btDefault, m_rbManual);
        QWidget::setTabOrder(m_rbManual, m_rbAutomatic);
        QWidget::setTabOrder(m_rbAutomatic, m_cbZeroIsInvalid);

        retranslateUi(CXPageColormap);
        QObject::connect(m_edMin, SIGNAL(textChanged(QString)), m_labelMin, SLOT(setText(QString)));
        QObject::connect(m_edMax, SIGNAL(textChanged(QString)), m_labelMax, SLOT(setText(QString)));
        QObject::connect(m_rbManual, SIGNAL(toggled(bool)), m_btDefault, SLOT(setEnabled(bool)));
        QObject::connect(m_rbSpecified, SIGNAL(toggled(bool)), m_btColor, SLOT(setEnabled(bool)));
        QObject::connect(m_rbManual, SIGNAL(toggled(bool)), m_edMax, SLOT(setEnabled(bool)));
        QObject::connect(m_rbManual, SIGNAL(toggled(bool)), m_edMin, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(CXPageColormap);
    } // setupUi

    void retranslateUi(CXBasePropertyPage *CXPageColormap)
    {
        CXPageColormap->setWindowTitle(QCoreApplication::translate("CXPageColormap", "CXPageColormap", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CXPageColormap", "Invalid Value", nullptr));
        m_rbTransparent->setText(QCoreApplication::translate("CXPageColormap", "Transparent", nullptr));
        m_rbSpecified->setText(QCoreApplication::translate("CXPageColormap", "Specified", nullptr));
        m_btColor->setText(QString());
        m_labelMin->setText(QString());
        m_labelMax->setText(QString());
        grpTemplate->setTitle(QCoreApplication::translate("CXPageColormap", "Color Map Template", nullptr));
        m_btRetrieve->setText(QCoreApplication::translate("CXPageColormap", "Retrieve...", nullptr));
        m_btSaveAs->setText(QCoreApplication::translate("CXPageColormap", "Save as...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CXPageColormap", "Operating", nullptr));
        m_cbRealtime->setText(QCoreApplication::translate("CXPageColormap", "Auto-Apply", nullptr));
        m_cbFreeDrawing->setText(QCoreApplication::translate("CXPageColormap", "Free drawing", nullptr));
        m_btReset->setText(QCoreApplication::translate("CXPageColormap", "Reset to Default", nullptr));
        m_btFlip->setText(QCoreApplication::translate("CXPageColormap", "Flip Colors", nullptr));
        grpDataRange->setTitle(QCoreApplication::translate("CXPageColormap", "Data Range", nullptr));
        label_min->setText(QCoreApplication::translate("CXPageColormap", "Min:", nullptr));
        label_max->setText(QCoreApplication::translate("CXPageColormap", "Max:", nullptr));
        m_btDefault->setText(QCoreApplication::translate("CXPageColormap", "Default", nullptr));
        m_rbManual->setText(QCoreApplication::translate("CXPageColormap", "Manual", nullptr));
        m_rbAutomatic->setText(QCoreApplication::translate("CXPageColormap", "Automatic", nullptr));
        m_cbZeroIsInvalid->setText(QCoreApplication::translate("CXPageColormap", "Zero is invalid value", nullptr));
        m_labelMessage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CXPageColormap: public Ui_CXPageColormap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGECOLORMAP_H
