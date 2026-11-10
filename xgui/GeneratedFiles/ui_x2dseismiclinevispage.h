/********************************************************************************
** Form generated from reading UI file 'x2dseismiclinevispage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_X2DSEISMICLINEVISPAGE_H
#define UI_X2DSEISMICLINEVISPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <xbuttoncoloredit.h>
#include <xlinecomponent.h>

QT_BEGIN_NAMESPACE

class Ui_CX2DSeismicLineVisPage
{
public:
    QGridLayout *gridLayout;
    QLabel *label_empty;
    QCheckBox *m_checkBoxTop;
    QCheckBox *m_checkBoxBottom;
    QLabel *label_color;
    QLabel *label_name_size;
    QComboBox *m_cbbNameSize;
    QLabel *label_name_font;
    QLabel *label_line_empty;
    QLabel *label_line_color;
    QLabel *label_line_width;
    CXLineWidthListCombBox *m_cbbLineWidth;
    QHBoxLayout *horizontalLayout_name;
    QLabel *label_name;
    QFrame *line;
    QHBoxLayout *horizontalLayout_line;
    QLabel *label_line;
    QFrame *line_2;
    QSpacerItem *verticalSpacer;
    QFontComboBox *m_fontComboBox;
    CXButtonColorEdit *m_btnLineColor;
    CXButtonColorEdit *m_btnNameColor;

    void setupUi(QWidget *CX2DSeismicLineVisPage)
    {
        if (CX2DSeismicLineVisPage->objectName().isEmpty())
            CX2DSeismicLineVisPage->setObjectName(QString::fromUtf8("CX2DSeismicLineVisPage"));
        CX2DSeismicLineVisPage->resize(532, 300);
        gridLayout = new QGridLayout(CX2DSeismicLineVisPage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_empty = new QLabel(CX2DSeismicLineVisPage);
        label_empty->setObjectName(QString::fromUtf8("label_empty"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_empty->sizePolicy().hasHeightForWidth());
        label_empty->setSizePolicy(sizePolicy);
        label_empty->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(label_empty, 1, 0, 1, 1);

        m_checkBoxTop = new QCheckBox(CX2DSeismicLineVisPage);
        m_checkBoxTop->setObjectName(QString::fromUtf8("m_checkBoxTop"));

        gridLayout->addWidget(m_checkBoxTop, 1, 1, 1, 1);

        m_checkBoxBottom = new QCheckBox(CX2DSeismicLineVisPage);
        m_checkBoxBottom->setObjectName(QString::fromUtf8("m_checkBoxBottom"));

        gridLayout->addWidget(m_checkBoxBottom, 1, 2, 1, 1);

        label_color = new QLabel(CX2DSeismicLineVisPage);
        label_color->setObjectName(QString::fromUtf8("label_color"));
        sizePolicy.setHeightForWidth(label_color->sizePolicy().hasHeightForWidth());
        label_color->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_color, 3, 1, 1, 1);

        label_name_size = new QLabel(CX2DSeismicLineVisPage);
        label_name_size->setObjectName(QString::fromUtf8("label_name_size"));
        sizePolicy.setHeightForWidth(label_name_size->sizePolicy().hasHeightForWidth());
        label_name_size->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_name_size, 3, 3, 1, 1);

        m_cbbNameSize = new QComboBox(CX2DSeismicLineVisPage);
        m_cbbNameSize->setObjectName(QString::fromUtf8("m_cbbNameSize"));

        gridLayout->addWidget(m_cbbNameSize, 3, 4, 1, 1);

        label_name_font = new QLabel(CX2DSeismicLineVisPage);
        label_name_font->setObjectName(QString::fromUtf8("label_name_font"));
        sizePolicy.setHeightForWidth(label_name_font->sizePolicy().hasHeightForWidth());
        label_name_font->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_name_font, 3, 5, 1, 1);

        label_line_empty = new QLabel(CX2DSeismicLineVisPage);
        label_line_empty->setObjectName(QString::fromUtf8("label_line_empty"));
        sizePolicy.setHeightForWidth(label_line_empty->sizePolicy().hasHeightForWidth());
        label_line_empty->setSizePolicy(sizePolicy);
        label_line_empty->setMinimumSize(QSize(20, 0));

        gridLayout->addWidget(label_line_empty, 5, 0, 1, 1);

        label_line_color = new QLabel(CX2DSeismicLineVisPage);
        label_line_color->setObjectName(QString::fromUtf8("label_line_color"));
        sizePolicy.setHeightForWidth(label_line_color->sizePolicy().hasHeightForWidth());
        label_line_color->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_line_color, 5, 1, 1, 1);

        label_line_width = new QLabel(CX2DSeismicLineVisPage);
        label_line_width->setObjectName(QString::fromUtf8("label_line_width"));
        sizePolicy.setHeightForWidth(label_line_width->sizePolicy().hasHeightForWidth());
        label_line_width->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_line_width, 5, 3, 1, 1);

        m_cbbLineWidth = new CXLineWidthListCombBox(CX2DSeismicLineVisPage);
        m_cbbLineWidth->setObjectName(QString::fromUtf8("m_cbbLineWidth"));

        gridLayout->addWidget(m_cbbLineWidth, 5, 4, 1, 1);

        horizontalLayout_name = new QHBoxLayout();
        horizontalLayout_name->setSpacing(6);
        horizontalLayout_name->setObjectName(QString::fromUtf8("horizontalLayout_name"));
        label_name = new QLabel(CX2DSeismicLineVisPage);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        sizePolicy.setHeightForWidth(label_name->sizePolicy().hasHeightForWidth());
        label_name->setSizePolicy(sizePolicy);

        horizontalLayout_name->addWidget(label_name);

        line = new QFrame(CX2DSeismicLineVisPage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_name->addWidget(line);


        gridLayout->addLayout(horizontalLayout_name, 0, 0, 1, 7);

        horizontalLayout_line = new QHBoxLayout();
        horizontalLayout_line->setSpacing(6);
        horizontalLayout_line->setObjectName(QString::fromUtf8("horizontalLayout_line"));
        label_line = new QLabel(CX2DSeismicLineVisPage);
        label_line->setObjectName(QString::fromUtf8("label_line"));
        sizePolicy.setHeightForWidth(label_line->sizePolicy().hasHeightForWidth());
        label_line->setSizePolicy(sizePolicy);

        horizontalLayout_line->addWidget(label_line);

        line_2 = new QFrame(CX2DSeismicLineVisPage);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_line->addWidget(line_2);


        gridLayout->addLayout(horizontalLayout_line, 4, 0, 1, 7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 6, 1, 1);

        m_fontComboBox = new QFontComboBox(CX2DSeismicLineVisPage);
        m_fontComboBox->setObjectName(QString::fromUtf8("m_fontComboBox"));
        m_fontComboBox->setCurrentIndex(24);

        gridLayout->addWidget(m_fontComboBox, 3, 6, 1, 1);

        m_btnLineColor = new CXButtonColorEdit(CX2DSeismicLineVisPage);
        m_btnLineColor->setObjectName(QString::fromUtf8("m_btnLineColor"));

        gridLayout->addWidget(m_btnLineColor, 5, 2, 1, 1);

        m_btnNameColor = new CXButtonColorEdit(CX2DSeismicLineVisPage);
        m_btnNameColor->setObjectName(QString::fromUtf8("m_btnNameColor"));

        gridLayout->addWidget(m_btnNameColor, 3, 2, 1, 1);


        retranslateUi(CX2DSeismicLineVisPage);

        QMetaObject::connectSlotsByName(CX2DSeismicLineVisPage);
    } // setupUi

    void retranslateUi(QWidget *CX2DSeismicLineVisPage)
    {
        label_empty->setText(QString());
        m_checkBoxTop->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Top", nullptr));
        m_checkBoxBottom->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Bottom", nullptr));
        label_color->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Color:", nullptr));
        label_name_size->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Size:", nullptr));
        label_name_font->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Font:", nullptr));
        label_line_empty->setText(QString());
        label_line_color->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Color:", nullptr));
        label_line_width->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Size:", nullptr));
        label_name->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Name", nullptr));
        label_line->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Line", nullptr));
        m_fontComboBox->setCurrentText(QCoreApplication::translate("CX2DSeismicLineVisPage", "Arial", nullptr));
        m_btnLineColor->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "PushButton", nullptr));
        m_btnNameColor->setText(QCoreApplication::translate("CX2DSeismicLineVisPage", "PushButton", nullptr));
        Q_UNUSED(CX2DSeismicLineVisPage);
    } // retranslateUi

};

namespace Ui {
    class CX2DSeismicLineVisPage: public Ui_CX2DSeismicLineVisPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_X2DSEISMICLINEVISPAGE_H
