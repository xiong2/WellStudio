/********************************************************************************
** Form generated from reading UI file 'xdlgsegylineheader.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XDLGSEGYLINEHEADER_H
#define UI_XDLGSEGYLINEHEADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UILineHeader
{
public:
    QGridLayout *gridLayout;
    QCheckBox *m_ChkFlip;
    QTreeWidget *m_LineHeaderView;

    void setupUi(QWidget *UILineHeader)
    {
        if (UILineHeader->objectName().isEmpty())
            UILineHeader->setObjectName(QString::fromUtf8("UILineHeader"));
        UILineHeader->resize(726, 584);
        gridLayout = new QGridLayout(UILineHeader);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_ChkFlip = new QCheckBox(UILineHeader);
        m_ChkFlip->setObjectName(QString::fromUtf8("m_ChkFlip"));

        gridLayout->addWidget(m_ChkFlip, 1, 0, 1, 1);

        m_LineHeaderView = new QTreeWidget(UILineHeader);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        new QTreeWidgetItem(m_LineHeaderView);
        m_LineHeaderView->setObjectName(QString::fromUtf8("m_LineHeaderView"));
        m_LineHeaderView->setRootIsDecorated(false);
        m_LineHeaderView->setWordWrap(true);
        m_LineHeaderView->header()->setCascadingSectionResizes(false);

        gridLayout->addWidget(m_LineHeaderView, 0, 0, 1, 1);


        retranslateUi(UILineHeader);

        QMetaObject::connectSlotsByName(UILineHeader);
    } // setupUi

    void retranslateUi(QWidget *UILineHeader)
    {
        UILineHeader->setWindowTitle(QCoreApplication::translate("UILineHeader", "Form", nullptr));
        m_ChkFlip->setText(QCoreApplication::translate("UILineHeader", "Flip", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = m_LineHeaderView->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("UILineHeader", "Value", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("UILineHeader", "Description", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("UILineHeader", "Byte Numbers", nullptr));

        const bool __sortingEnabled = m_LineHeaderView->isSortingEnabled();
        m_LineHeaderView->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = m_LineHeaderView->topLevelItem(0);
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("UILineHeader", "Job identification number.", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("UILineHeader", "01-04", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = m_LineHeaderView->topLevelItem(1);
        ___qtreewidgetitem2->setText(1, QCoreApplication::translate("UILineHeader", "Line number.  For 3-D poststack data, this will typically contain the in-line number.", nullptr));
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("UILineHeader", "05-08", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = m_LineHeaderView->topLevelItem(2);
        ___qtreewidgetitem3->setText(1, QCoreApplication::translate("UILineHeader", "Reel number.", nullptr));
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("UILineHeader", "09-12", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = m_LineHeaderView->topLevelItem(3);
        ___qtreewidgetitem4->setText(1, QCoreApplication::translate("UILineHeader", "Number of data traces per ensemble.  Mandatory for prestack data.", nullptr));
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("UILineHeader", "13-14", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = m_LineHeaderView->topLevelItem(4);
        ___qtreewidgetitem5->setText(1, QCoreApplication::translate("UILineHeader", "Number of auxiliary traces per ensemble.  Mandatory for prestack data.", nullptr));
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("UILineHeader", "15-16", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = m_LineHeaderView->topLevelItem(5);
        ___qtreewidgetitem6->setText(1, QCoreApplication::translate("UILineHeader", "Sample interval in microseconds (\302\265s).  Mandatory for all data types.", nullptr));
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("UILineHeader", "17-18", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = m_LineHeaderView->topLevelItem(6);
        ___qtreewidgetitem7->setText(1, QCoreApplication::translate("UILineHeader", "Sample interval in microseconds  (\302\265s) of original field recording. ", nullptr));
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("UILineHeader", "19-20", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = m_LineHeaderView->topLevelItem(7);
        ___qtreewidgetitem8->setText(1, QCoreApplication::translate("UILineHeader", "Number of samples per data trace.  Mandatory for all types of data.", nullptr));
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("UILineHeader", "21-22", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = m_LineHeaderView->topLevelItem(8);
        ___qtreewidgetitem9->setText(1, QCoreApplication::translate("UILineHeader", "Number of samples per data trace for original field recording.", nullptr));
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("UILineHeader", "23-24", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = m_LineHeaderView->topLevelItem(9);
        ___qtreewidgetitem10->setText(1, QCoreApplication::translate("UILineHeader", "Data sample format code.  Mandatory for all data.", nullptr));
        ___qtreewidgetitem10->setText(0, QCoreApplication::translate("UILineHeader", "25-26", nullptr));
        QTreeWidgetItem *___qtreewidgetitem11 = m_LineHeaderView->topLevelItem(10);
        ___qtreewidgetitem11->setText(1, QCoreApplication::translate("UILineHeader", "Ensemble fold \342\200\224 The expected number of data traces per trace ensemble (e.g. the CMP fold).", nullptr));
        ___qtreewidgetitem11->setText(0, QCoreApplication::translate("UILineHeader", "27-28", nullptr));
        QTreeWidgetItem *___qtreewidgetitem12 = m_LineHeaderView->topLevelItem(11);
        ___qtreewidgetitem12->setText(1, QCoreApplication::translate("UILineHeader", "Trace sorting code.", nullptr));
        ___qtreewidgetitem12->setText(0, QCoreApplication::translate("UILineHeader", "29-30", nullptr));
        QTreeWidgetItem *___qtreewidgetitem13 = m_LineHeaderView->topLevelItem(12);
        ___qtreewidgetitem13->setText(1, QCoreApplication::translate("UILineHeader", "Vertical sum code.", nullptr));
        ___qtreewidgetitem13->setText(0, QCoreApplication::translate("UILineHeader", "31-32", nullptr));
        QTreeWidgetItem *___qtreewidgetitem14 = m_LineHeaderView->topLevelItem(13);
        ___qtreewidgetitem14->setText(1, QCoreApplication::translate("UILineHeader", "Sweep frequency at start (Hz).", nullptr));
        ___qtreewidgetitem14->setText(0, QCoreApplication::translate("UILineHeader", "33-34", nullptr));
        QTreeWidgetItem *___qtreewidgetitem15 = m_LineHeaderView->topLevelItem(14);
        ___qtreewidgetitem15->setText(1, QCoreApplication::translate("UILineHeader", "Sweep frequency at end (Hz).", nullptr));
        ___qtreewidgetitem15->setText(0, QCoreApplication::translate("UILineHeader", "35-36", nullptr));
        QTreeWidgetItem *___qtreewidgetitem16 = m_LineHeaderView->topLevelItem(15);
        ___qtreewidgetitem16->setText(1, QCoreApplication::translate("UILineHeader", "Sweep length (ms).", nullptr));
        ___qtreewidgetitem16->setText(0, QCoreApplication::translate("UILineHeader", "37-38", nullptr));
        QTreeWidgetItem *___qtreewidgetitem17 = m_LineHeaderView->topLevelItem(16);
        ___qtreewidgetitem17->setText(1, QCoreApplication::translate("UILineHeader", "Sweep type code.", nullptr));
        ___qtreewidgetitem17->setText(0, QCoreApplication::translate("UILineHeader", "39-40", nullptr));
        QTreeWidgetItem *___qtreewidgetitem18 = m_LineHeaderView->topLevelItem(17);
        ___qtreewidgetitem18->setText(1, QCoreApplication::translate("UILineHeader", "Trace number of sweep channel.", nullptr));
        ___qtreewidgetitem18->setText(0, QCoreApplication::translate("UILineHeader", "41-42", nullptr));
        QTreeWidgetItem *___qtreewidgetitem19 = m_LineHeaderView->topLevelItem(18);
        ___qtreewidgetitem19->setText(1, QCoreApplication::translate("UILineHeader", "Sweep trace taper length in milliseconds at start if tapered (the taper starts at zero time and is effective for this length).", nullptr));
        ___qtreewidgetitem19->setText(0, QCoreApplication::translate("UILineHeader", "43-44", nullptr));
        QTreeWidgetItem *___qtreewidgetitem20 = m_LineHeaderView->topLevelItem(19);
        ___qtreewidgetitem20->setText(1, QCoreApplication::translate("UILineHeader", "Sweep trace taper length in milliseconds at end (the ending taper starts at sweep length minus the taper length at end).", nullptr));
        ___qtreewidgetitem20->setText(0, QCoreApplication::translate("UILineHeader", "45-46", nullptr));
        QTreeWidgetItem *___qtreewidgetitem21 = m_LineHeaderView->topLevelItem(20);
        ___qtreewidgetitem21->setText(1, QCoreApplication::translate("UILineHeader", "Taper type.", nullptr));
        ___qtreewidgetitem21->setText(0, QCoreApplication::translate("UILineHeader", "47-48", nullptr));
        QTreeWidgetItem *___qtreewidgetitem22 = m_LineHeaderView->topLevelItem(21);
        ___qtreewidgetitem22->setText(1, QCoreApplication::translate("UILineHeader", "Correlated data traces.", nullptr));
        ___qtreewidgetitem22->setText(0, QCoreApplication::translate("UILineHeader", "49-50", nullptr));
        QTreeWidgetItem *___qtreewidgetitem23 = m_LineHeaderView->topLevelItem(22);
        ___qtreewidgetitem23->setText(1, QCoreApplication::translate("UILineHeader", "Binary gain recovered.", nullptr));
        ___qtreewidgetitem23->setText(0, QCoreApplication::translate("UILineHeader", "51-52", nullptr));
        QTreeWidgetItem *___qtreewidgetitem24 = m_LineHeaderView->topLevelItem(23);
        ___qtreewidgetitem24->setText(1, QCoreApplication::translate("UILineHeader", "Amplitude recovery method.", nullptr));
        ___qtreewidgetitem24->setText(0, QCoreApplication::translate("UILineHeader", "53-54", nullptr));
        QTreeWidgetItem *___qtreewidgetitem25 = m_LineHeaderView->topLevelItem(24);
        ___qtreewidgetitem25->setText(1, QCoreApplication::translate("UILineHeader", "Measurement system.", nullptr));
        ___qtreewidgetitem25->setText(0, QCoreApplication::translate("UILineHeader", "55-56", nullptr));
        QTreeWidgetItem *___qtreewidgetitem26 = m_LineHeaderView->topLevelItem(25);
        ___qtreewidgetitem26->setText(1, QCoreApplication::translate("UILineHeader", "Impulse signal polarity.", nullptr));
        ___qtreewidgetitem26->setText(0, QCoreApplication::translate("UILineHeader", "57-58", nullptr));
        QTreeWidgetItem *___qtreewidgetitem27 = m_LineHeaderView->topLevelItem(26);
        ___qtreewidgetitem27->setText(1, QCoreApplication::translate("UILineHeader", "Vibratory polarity code.", nullptr));
        ___qtreewidgetitem27->setText(0, QCoreApplication::translate("UILineHeader", "59-60", nullptr));
        QTreeWidgetItem *___qtreewidgetitem28 = m_LineHeaderView->topLevelItem(27);
        ___qtreewidgetitem28->setText(1, QCoreApplication::translate("UILineHeader", "Unassigned.", nullptr));
        ___qtreewidgetitem28->setText(0, QCoreApplication::translate("UILineHeader", "61-300", nullptr));
        QTreeWidgetItem *___qtreewidgetitem29 = m_LineHeaderView->topLevelItem(28);
        ___qtreewidgetitem29->setText(1, QCoreApplication::translate("UILineHeader", "SEG Y Format Revision Number. ", nullptr));
        ___qtreewidgetitem29->setText(0, QCoreApplication::translate("UILineHeader", "301-302", nullptr));
        QTreeWidgetItem *___qtreewidgetitem30 = m_LineHeaderView->topLevelItem(29);
        ___qtreewidgetitem30->setText(1, QCoreApplication::translate("UILineHeader", "Fixed length trace flag. ", nullptr));
        ___qtreewidgetitem30->setText(0, QCoreApplication::translate("UILineHeader", "303-304", nullptr));
        QTreeWidgetItem *___qtreewidgetitem31 = m_LineHeaderView->topLevelItem(30);
        ___qtreewidgetitem31->setText(1, QCoreApplication::translate("UILineHeader", "Number of 3200-byte, Extended Textual File Header records following the Binary Header. ", nullptr));
        ___qtreewidgetitem31->setText(0, QCoreApplication::translate("UILineHeader", "305-306", nullptr));
        QTreeWidgetItem *___qtreewidgetitem32 = m_LineHeaderView->topLevelItem(31);
        ___qtreewidgetitem32->setText(1, QCoreApplication::translate("UILineHeader", "Unassigned.", nullptr));
        ___qtreewidgetitem32->setText(0, QCoreApplication::translate("UILineHeader", "307-400", nullptr));
        m_LineHeaderView->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class UILineHeader: public Ui_UILineHeader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XDLGSEGYLINEHEADER_H
