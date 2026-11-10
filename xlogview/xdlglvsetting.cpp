#include <qlineedit.h>
#include "xdlglvsetting.h"
#include "xlvscene.h"
#include "xlvitemwell.h"
#include "xlvitemcurve.h"
#include "xlvitemwelltops.h"
#include "xglobal.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xwelltops.h"
#include "xlogview.h"
#include "xviewinfolpcurve.h"
#include "xviewinfolpwell.h"
#include "xviewinfolpwelltops.h"
#include "xlvwindowinfo.h"

#include "xbuttoncoloredit.h"
#include "xtypecombo.h"
#include "xlinestylecombo.h"
#include "xlinecomponent.h"
#include "xslidercomplex.h"

XDlgLVSetting::XDlgLVSetting(CXLVScene *pScene, QWidget *parent)
	: QDialog(parent), m_pScene(pScene)
{
	ui.setupUi(this);
	m_pWindow = (CXLogView *)parent;

	initUI();
}

XDlgLVSetting::~XDlgLVSetting()
{
}

void XDlgLVSetting::initUI()
{
	int i;
	connect(ui.buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(apply()));

	CXLVWindowInfo *pWInfo = (CXLVWindowInfo *)m_pScene->GetWindowViewInfo();
	ui.spinBoxHInv->setValue(pWInfo->m_iHIntv);
	ui.spinBoxLTWidth->setValue(pWInfo->m_dTrackWidth);
	ui.checkBoxUDepth->setChecked(pWInfo->m_bUniqueDepth);
	ui.checkBoxShowBin->setChecked(pWInfo->m_bShowBinGrid);

	QVector<qreal> vecCan;
	vecCan << 0.5 << 1. << 2. << 3.;
	qreal dVScale = pWInfo->m_dVScale;
	ui.comboBox->setCurrentIndex(vecCan.indexOf(dVScale));
	
	QStringList sListCurve;
	QList<QUuid>listCID;
	QVector<CXLVItemWell *>& vecWItem = m_pScene->GetAllWellItems();

	//	Wells group
	QList<CXWell *> listWell;
	foreach(CXLVItemWell* pWItem, vecWItem)
	{
		CXWell *pWell = dynamic_cast<CXWell *>(::GetObjectByID(pWItem->GetObjectID()));
		if (pWell)
			listWell << pWell;
	}

	if (listWell.isEmpty())
		return;

	ui.tableWidgetWells->setRowCount(listWell.size());
	ui.tableWidgetWells->setColumnCount(1);
	for (i = 0; i < listWell.size(); i++)
	{
		double dStart, dStop;
		listWell[i]->GetDepthRange(dStart, dStop);

		CXViewInfoLPWell *pVInfo = (CXViewInfoLPWell *)m_pWindow->GetObjectViewInfo(listWell[i]->GetObjectID());

		CXSliderComplex *pRange = new CXSliderComplex();
		pRange->SetSliderName(listWell[i]->GetObjectName());
		pRange->SetRangeAndPrecision(dStart, dStop, 0.1);
		pRange->SetMinPosition(pVInfo->GetStartDepth());
		pRange->SetMaxPosition(pVInfo->GetEndDepth());
		ui.tableWidgetWells->setCellWidget(i, 0, pRange);
	}

	//	Curves group
	foreach(CXLVItemWell* pWItem, vecWItem)
	{
		QList<QGraphicsItem *> listGItem = pWItem->childItems();
		foreach(QGraphicsItem *pGItem, listGItem)
		{
			CXLVItemCurve *pCItem = dynamic_cast<CXLVItemCurve *>(pGItem);
			if (!pCItem)
				continue;

			CXObject *pObj = ::GetObjectByID(pCItem->GetObjectID());
			sListCurve << pObj->GetParent()->GetObjectName() + " - " + pObj->GetObjectName();
			listCID << pObj->GetObjectID();
		}
	}

	if (sListCurve.isEmpty())
		return;

	ui.tableWidgetLogs->setRowCount(sListCurve.size());
	for (i = 0; i < sListCurve.size(); i++)
	{
		CXViewInfoLPCurve *pVInfo = (CXViewInfoLPCurve *)m_pWindow->GetObjectViewInfo(listCID[i]);

		//	Name.
		QTableWidgetItem *pItem = new QTableWidgetItem(sListCurve[i]);
		pItem->setData(Qt::UserRole, QVariant(listCID[i]));
		ui.tableWidgetLogs->setItem(i, 0, pItem);

		//	Left 
		QLineEdit* pLEdit = new QLineEdit(QString::number(pVInfo->GetDisplayDataMin()));
		pLEdit->setValidator(new QDoubleValidator);
		ui.tableWidgetLogs->setCellWidget(i, 1, pLEdit);

		//	Right 
		QLineEdit* pREdit = new QLineEdit(QString::number(pVInfo->GetDisplayDataMax()));
		pREdit->setValidator(new QDoubleValidator);
		ui.tableWidgetLogs->setCellWidget(i, 2, pREdit);

		//	Line Color
		CXButtonColorEdit *pColorButton = new CXButtonColorEdit;
		pColorButton->SetColor(pVInfo->GetColor());
		ui.tableWidgetLogs->setCellWidget(i, 3, pColorButton);

		//	Line Width
		CXLineWidthListCombBox *pLineWidthCom = new CXLineWidthListCombBox;
		pLineWidthCom->SetLineWidth(pVInfo->GetLineWidth());
		ui.tableWidgetLogs->setCellWidget(i, 4, pLineWidthCom);

		//	Line Style
		CXLineStyleCombo *pLineStyleCom = new CXLineStyleCombo;
		pLineStyleCom->SetLineType((Qt::PenStyle)(pVInfo->GetLineStyle()));
		ui.tableWidgetLogs->setCellWidget(i, 5, pLineStyleCom);

		//	Fill from
		QLineEdit* pFFEdit = new QLineEdit(QString::number(pVInfo->GetFillFrom()));
		pFFEdit->setValidator(new QDoubleValidator);
		ui.tableWidgetLogs->setCellWidget(i, 6, pFFEdit);

		//	FF Color
		pColorButton = new CXButtonColorEdit;
		pColorButton->SetColor(pVInfo->GetFFColor());
		ui.tableWidgetLogs->setCellWidget(i, 7, pColorButton);

		//	FF Pattern
		CXTypeCombo *pFFTypeCB = new CXTypeCombo(ePatternType);
		pFFTypeCB->SetSelectedType(pVInfo->GetFFPattern());
		ui.tableWidgetLogs->setCellWidget(i, 8, pFFTypeCB);

		//	Fill to
		QLineEdit* pFTEdit = new QLineEdit(QString::number(pVInfo->GetFillTo()));
		pFFEdit->setValidator(new QDoubleValidator);
		ui.tableWidgetLogs->setCellWidget(i, 9, pFTEdit);

		//	FT Color
		pColorButton = new CXButtonColorEdit;
		pColorButton->SetColor(pVInfo->GetFTColor());
		ui.tableWidgetLogs->setCellWidget(i, 10, pColorButton);

		//	FT Pattern
		CXTypeCombo *pFTTypeCB = new CXTypeCombo(ePatternType);
		pFTTypeCB->SetSelectedType(pVInfo->GetFFPattern());
		ui.tableWidgetLogs->setCellWidget(i, 11, pFTTypeCB);
	}

	//	Well tops group.
	CXLVItemWellTops *pTopItem = m_pScene->GetWellTopsItem();
	if (!pTopItem)
	{
		ui.groupBox_2->setVisible(false);
	}
	else
	{
		CXViewInfoLPWellTops *pVInfo = (CXViewInfoLPWellTops *)m_pWindow->GetObjectViewInfo(pTopItem->GetObjectID());
		ui.checkBoxConnect->setChecked(pVInfo->GetConnect());
		ui.checkBoxLeft->setChecked(pVInfo->GetShowNameOnLeft());
		ui.checkBoxRight->setChecked(pVInfo->GetShowNameOnRight());
		ui.comboBoxLW->SetLineWidth(pVInfo->GetLineWidth());
		ui.comboBoxLS->SetLineType((Qt::PenStyle)pVInfo->GetLineStyle());
	}
}

void XDlgLVSetting::accept()
{
	apply();

	QDialog::accept();
}

void XDlgLVSetting::apply()
{
	int i;
	CXLVWindowInfo *pWInfo = (CXLVWindowInfo *)m_pScene->GetWindowViewInfo();

	pWInfo->m_iHIntv = ui.spinBoxHInv->value();
	pWInfo->m_dTrackWidth = ui.spinBoxLTWidth->value();
	pWInfo->m_bShowBinGrid = ui.checkBoxShowBin->isChecked();
	pWInfo->m_bUniqueDepth = ui.checkBoxUDepth->isChecked();

	QVector<qreal> vecCan;
	vecCan << 0.5 << 1. << 2. << 3.;
	pWInfo->m_dVScale = vecCan[ui.comboBox->currentIndex()];

	QList<CXViewInfoLPWell *> listWVInfo;
	QVector<CXLVItemWell *>& vecWItem = m_pScene->GetAllWellItems();
	foreach(CXLVItemWell* pWItem, vecWItem)
	{
		CXWell *pWell = dynamic_cast<CXWell *>(::GetObjectByID(pWItem->GetObjectID()));
		CXViewInfoLPWell *pVInfo = (CXViewInfoLPWell *)m_pWindow->GetObjectViewInfo(pWell->GetObjectID());
		listWVInfo << pVInfo;
	}

	double dMin = 9999999., dMax = -9999999.;
	for (i = 0; i < ui.tableWidgetWells->rowCount(); i++)
	{
		CXSliderComplex *pRange = (CXSliderComplex *)ui.tableWidgetWells->cellWidget(i, 0);
		listWVInfo[i]->SetStartDepth(pRange->GetMinValue());
		listWVInfo[i]->SetEndDepth(pRange->GetMaxValue());

		dMin = qMin(dMin, pRange->GetMinValue());
		dMax = qMax(dMax, pRange->GetMaxValue());
	}

	pWInfo->m_dSDepth = dMin;
	pWInfo->m_dEDepth = dMax;

	for (i = 0; i < ui.tableWidgetLogs->rowCount(); i++)
	{
		QUuid curveID = ui.tableWidgetLogs->item(i, 0)->data(Qt::UserRole).toUuid();
		CXViewInfoLPCurve *pVInfo = (CXViewInfoLPCurve *)m_pWindow->GetObjectViewInfo(curveID);

		QLineEdit *pLEdit = (QLineEdit *)ui.tableWidgetLogs->cellWidget(i, 1);
		pVInfo->SetDisplayDataMin(pLEdit->text().toDouble());
		pLEdit = (QLineEdit *)ui.tableWidgetLogs->cellWidget(i, 2);
		pVInfo->SetDisplayDataMax(pLEdit->text().toDouble());

		CXButtonColorEdit *pColorButton = (CXButtonColorEdit *)ui.tableWidgetLogs->cellWidget(i, 3);
		pVInfo->SetColor(pColorButton->GetColor());

		CXLineWidthListCombBox *pLineWidthCom = (CXLineWidthListCombBox *)ui.tableWidgetLogs->cellWidget(i, 4);
		pVInfo->SetLineWidth(pLineWidthCom->GetLineWidth());

		CXLineStyleCombo *pLineStyleCom = (CXLineStyleCombo *)ui.tableWidgetLogs->cellWidget(i, 5);
		pVInfo->SetLineStyle(pLineStyleCom->GetLineType());

		pLEdit = (QLineEdit *)ui.tableWidgetLogs->cellWidget(i, 6);
		pVInfo->SetFillFrom(pLEdit->text().toDouble());
		pColorButton = (CXButtonColorEdit *)ui.tableWidgetLogs->cellWidget(i, 7);
		pVInfo->SetFFColor(pColorButton->GetColor());
		CXTypeCombo *pTypeCB = (CXTypeCombo *)ui.tableWidgetLogs->cellWidget(i, 8);
		pVInfo->SetFFPattern(pTypeCB->GetSelectedType());

		pLEdit = (QLineEdit *)ui.tableWidgetLogs->cellWidget(i, 9);
		pVInfo->SetFillTo(pLEdit->text().toDouble());
		pColorButton = (CXButtonColorEdit *)ui.tableWidgetLogs->cellWidget(i, 10);
		pVInfo->SetFTColor(pColorButton->GetColor());
		pTypeCB = (CXTypeCombo *)ui.tableWidgetLogs->cellWidget(i, 11);
		pVInfo->SetFTPattern(pTypeCB->GetSelectedType());
	}

	CXLVItemWellTops *pTopItem = m_pScene->GetWellTopsItem();
	if (pTopItem)
	{
		CXViewInfoLPWellTops *pVInfo = (CXViewInfoLPWellTops *)m_pWindow->GetObjectViewInfo(pTopItem->GetObjectID());
		pVInfo->SetConnect(ui.checkBoxConnect->isChecked());
		pVInfo->SetShowNameOnLeft(ui.checkBoxLeft->isChecked());
		pVInfo->SetShowNameOnRight(ui.checkBoxRight->isChecked());
		pVInfo->SetLineWidth(ui.comboBoxLW->GetLineWidth());
		pVInfo->SetLineStyle(ui.comboBoxLS->GetLineType());
	}

	m_pScene->update();
}