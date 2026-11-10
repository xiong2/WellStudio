/********************************************************************************
** Form generated from reading UI file 'xpagemakefaultsticksbysurveyfrompoints.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPAGEMAKEFAULTSTICKSBYSURVEYFROMPOINTS_H
#define UI_XPAGEMAKEFAULTSTICKSBYSURVEYFROMPOINTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CXPageMakeFaultSticksBySurveyFromPoints
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox_survey;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *spinBox_firstInline;
    QLabel *label_3;
    QSpinBox *spinBox_lastInline;
    QLabel *label_4;
    QSpinBox *spinBox_inlineStep;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_alsoCrossline;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *lineEdit_output;
    QPushButton *pushButton_generate;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CXPageMakeFaultSticksBySurveyFromPoints)
    {
        if (CXPageMakeFaultSticksBySurveyFromPoints->objectName().isEmpty())
            CXPageMakeFaultSticksBySurveyFromPoints->setObjectName(QString::fromUtf8("CXPageMakeFaultSticksBySurveyFromPoints"));
        CXPageMakeFaultSticksBySurveyFromPoints->resize(338, 199);
        verticalLayout = new QVBoxLayout(CXPageMakeFaultSticksBySurveyFromPoints);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(CXPageMakeFaultSticksBySurveyFromPoints);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        comboBox_survey = new QComboBox(CXPageMakeFaultSticksBySurveyFromPoints);
        comboBox_survey->setObjectName(QString::fromUtf8("comboBox_survey"));

        horizontalLayout_2->addWidget(comboBox_survey);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(CXPageMakeFaultSticksBySurveyFromPoints);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBox_firstInline = new QSpinBox(CXPageMakeFaultSticksBySurveyFromPoints);
        spinBox_firstInline->setObjectName(QString::fromUtf8("spinBox_firstInline"));
        spinBox_firstInline->setMaximum(99999);

        horizontalLayout->addWidget(spinBox_firstInline);

        label_3 = new QLabel(CXPageMakeFaultSticksBySurveyFromPoints);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBox_lastInline = new QSpinBox(CXPageMakeFaultSticksBySurveyFromPoints);
        spinBox_lastInline->setObjectName(QString::fromUtf8("spinBox_lastInline"));
        spinBox_lastInline->setMaximum(99999);

        horizontalLayout->addWidget(spinBox_lastInline);

        label_4 = new QLabel(CXPageMakeFaultSticksBySurveyFromPoints);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        spinBox_inlineStep = new QSpinBox(CXPageMakeFaultSticksBySurveyFromPoints);
        spinBox_inlineStep->setObjectName(QString::fromUtf8("spinBox_inlineStep"));

        horizontalLayout->addWidget(spinBox_inlineStep);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        checkBox_alsoCrossline = new QCheckBox(CXPageMakeFaultSticksBySurveyFromPoints);
        checkBox_alsoCrossline->setObjectName(QString::fromUtf8("checkBox_alsoCrossline"));

        horizontalLayout_4->addWidget(checkBox_alsoCrossline);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(CXPageMakeFaultSticksBySurveyFromPoints);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineEdit_output = new QLineEdit(CXPageMakeFaultSticksBySurveyFromPoints);
        lineEdit_output->setObjectName(QString::fromUtf8("lineEdit_output"));

        horizontalLayout_3->addWidget(lineEdit_output);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButton_generate = new QPushButton(CXPageMakeFaultSticksBySurveyFromPoints);
        pushButton_generate->setObjectName(QString::fromUtf8("pushButton_generate"));

        verticalLayout->addWidget(pushButton_generate);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(CXPageMakeFaultSticksBySurveyFromPoints);

        QMetaObject::connectSlotsByName(CXPageMakeFaultSticksBySurveyFromPoints);
    } // setupUi

    void retranslateUi(QDialog *CXPageMakeFaultSticksBySurveyFromPoints)
    {
        CXPageMakeFaultSticksBySurveyFromPoints->setWindowTitle(QCoreApplication::translate("CXPageMakeFaultSticksBySurveyFromPoints", "Make Fault Sticks according to survey", nullptr));
        label->setText(QCoreApplication::translate("CXPageMakeFaultSticksBySurveyFromPoints", "3-D Seismic survey", nullptr));
        label_2->setText(QCoreApplication::translate("CXPageMakeFaultSticksBySurveyFromPoints", "Inline from", nullptr));
        label_3->setText(QCoreApplication::translate("CXPageMakeFaultSticksBySurveyFromPoints", "to", nullptr));
        label_4->setText(QCoreApplication::translate("CXPageMakeFaultSticksBySurveyFromPoints", "that each step is", nullptr));
        checkBox_alsoCrossline->setText(QCoreApplication::translate("CXPageMakeFaultSticksBySurveyFromPoints", "Same step to Crossline", nullptr));
        label_5->setText(QCoreApplication::translate("CXPageMakeFaultSticksBySurveyFromPoints", "Output file name", nullptr));
        pushButton_generate->setText(QCoreApplication::translate("CXPageMakeFaultSticksBySurveyFromPoints", "Generate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CXPageMakeFaultSticksBySurveyFromPoints: public Ui_CXPageMakeFaultSticksBySurveyFromPoints {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPAGEMAKEFAULTSTICKSBYSURVEYFROMPOINTS_H
