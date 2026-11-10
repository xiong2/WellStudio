#include "xfaultsticksvispage.h"

#include <qmessagebox.h>
#include <cassert>

#include "xviewinfo3dfaultsticks.h"
#include "xviewinfo3dfracturepatches.h"
#include "xglobal.h"

CXFaultSticksVisPage::CXFaultSticksVisPage(QWidget *parent, CXViewInfoObject* pViewInfo)
	: CXBasePropertyPage(parent), m_pViewInfo(pViewInfo)
{
	m_ui.setupUi(this);

	_Init();
	_InitData();
}


CXFaultSticksVisPage::~CXFaultSticksVisPage()
{

}

void CXFaultSticksVisPage::_Init()
{
	CXViewInfo3DFaultSticks *pViewInfoFS = dynamic_cast<CXViewInfo3DFaultSticks *>(m_pViewInfo);
	CXViewInfo3DFracturePatches *pViewInfoFP = dynamic_cast<CXViewInfo3DFracturePatches *>(m_pViewInfo);

	// Point
	m_ui.m_pCombPointSize->clear();
	QStringList strListSize;
	for (int i=0; i<12; ++i)
		strListSize<<QString::number(i+1);
	m_ui.m_pCombPointSize->addItems(strListSize);

	//Opacity
	m_ui.m_pSlider->setRange(0, 1000);
	if (pViewInfoFS)
	{
		m_ui.m_pLineEdtOpacity->setText(QString::number(pViewInfoFS->GetOpacity(), 'f', 3));
		m_ui.m_pSlider->setValue(static_cast<int>(pViewInfoFS->GetOpacity()*1000));
	}
	else if(pViewInfoFP)
	{
		m_ui.m_pLineEdtOpacity->setText(QString::number(pViewInfoFP->GetOpacity(), 'f', 3));
		m_ui.m_pSlider->setValue(static_cast<int>(pViewInfoFP->GetOpacity() * 1000));
	}

	connect(m_ui.m_pSlider,	SIGNAL(valueChanged(int)),	this,	SLOT(slotSlider(int)));
	connect(m_ui.m_pLineEdtOpacity,SIGNAL(editingFinished()), this,	SLOT(slotChangeOpacity()));

}

void CXFaultSticksVisPage::_InitData()
{
	CXViewInfo3DFaultSticks *pViewInfoFS = dynamic_cast<CXViewInfo3DFaultSticks *>(m_pViewInfo);
	CXViewInfo3DFracturePatches *pViewInfoFP = dynamic_cast<CXViewInfo3DFracturePatches *>(m_pViewInfo);

	if (pViewInfoFS)
	{
		// Point
		m_ui.m_pChkVisiblePoint->setChecked(pViewInfoFS->GetDisplayPoint());
		m_ui.m_pColorEdtPoint->SetColor(pViewInfoFS->GetPointColor());
		m_ui.m_pCombPointSize->setCurrentIndex(pViewInfoFS->GetPointSize() - 1);

		// Line
		m_ui.m_pChkVisibleLine->setChecked(pViewInfoFS->GetDisplayLine());
		m_ui.m_pColorEdtLine->SetColor(pViewInfoFS->GetLineColor());
		m_ui.m_pCombLineWidth->SetLineWidth(pViewInfoFS->GetLineWidth());

		// Plane
		m_ui.m_pChkVisiblePlane->setChecked(pViewInfoFS->GetDisplayPlane());
		m_ui.m_pColorEdtPlane->SetColor(pViewInfoFS->GetPlaneColor());
	}
	else if (pViewInfoFP)
	{
		// Point
		m_ui.m_pChkVisiblePoint->setChecked(pViewInfoFP->GetDisplayPoint());
		m_ui.m_pColorEdtPoint->SetColor(pViewInfoFP->GetPointColor());
		m_ui.m_pCombPointSize->setCurrentIndex(pViewInfoFP->GetPointSize() - 1);

		// Line
		m_ui.m_pChkVisibleLine->setChecked(pViewInfoFP->GetDisplayLine());
		m_ui.m_pColorEdtLine->SetColor(pViewInfoFP->GetLineColor());
		m_ui.m_pCombLineWidth->SetLineWidth(pViewInfoFP->GetLineWidth());

		// Plane
		m_ui.m_pChkVisiblePlane->setChecked(pViewInfoFP->GetDisplayPlane());
		m_ui.m_pColorEdtPlane->SetColor(pViewInfoFP->GetPlaneColor());
	}
}

void CXFaultSticksVisPage::slotChangeOpacity()
{
	bool b;
	float fOpacity = m_ui.m_pLineEdtOpacity->text().toFloat(&b);
	if (!b || fOpacity < 0. || fOpacity > 1.)
	{
		QMessageBox::warning(0, ::g_strProductName, "Please enter a number between 0 and 1.");
		m_ui.m_pLineEdtOpacity->undo();
		m_ui.m_pLineEdtOpacity->setFocus();
	}

	m_ui.m_pSlider->setValue(static_cast<int>(fOpacity*1000));
}

void CXFaultSticksVisPage::slotSlider(int nValue)
{
	m_ui.m_pLineEdtOpacity->setText(QString::number(nValue/1000.f, 'f', 3));
}

void CXFaultSticksVisPage::Apply()
{
	CXViewInfo3DFaultSticks *pViewInfoFS = dynamic_cast<CXViewInfo3DFaultSticks *>(m_pViewInfo);
	CXViewInfo3DFracturePatches *pViewInfoFP = dynamic_cast<CXViewInfo3DFracturePatches *>(m_pViewInfo);

	if (pViewInfoFS)
	{
		// Point
		pViewInfoFS->SetDisplayPoint(m_ui.m_pChkVisiblePoint->isChecked());
		pViewInfoFS->SetPointColor(m_ui.m_pColorEdtPoint->GetColor());
		pViewInfoFS->SetPointSize(m_ui.m_pCombPointSize->currentText().toInt());

		// Line
		pViewInfoFS->SetDisplayLine(m_ui.m_pChkVisibleLine->isChecked());
		pViewInfoFS->SetLineColor(m_ui.m_pColorEdtLine->GetColor());
		pViewInfoFS->SetLineWidth(m_ui.m_pCombLineWidth->GetLineWidth());

		// Plane
		pViewInfoFS->SetDisplayPlane(m_ui.m_pChkVisiblePlane->isChecked());
		pViewInfoFS->SetPlaneColor(m_ui.m_pColorEdtPlane->GetColor());
		pViewInfoFS->SetOpacity(m_ui.m_pLineEdtOpacity->text().toFloat());
	}
	else if (pViewInfoFP)
	{
		// Point
		pViewInfoFP->SetDisplayPoint(m_ui.m_pChkVisiblePoint->isChecked());
		pViewInfoFP->SetPointColor(m_ui.m_pColorEdtPoint->GetColor());
		pViewInfoFP->SetPointSize(m_ui.m_pCombPointSize->currentText().toInt());

		// Line
		pViewInfoFP->SetDisplayLine(m_ui.m_pChkVisibleLine->isChecked());
		pViewInfoFP->SetLineColor(m_ui.m_pColorEdtLine->GetColor());
		pViewInfoFP->SetLineWidth(m_ui.m_pCombLineWidth->GetLineWidth());

		// Plane
		pViewInfoFP->SetDisplayPlane(m_ui.m_pChkVisiblePlane->isChecked());
		pViewInfoFP->SetPlaneColor(m_ui.m_pColorEdtPlane->GetColor());
		pViewInfoFP->SetOpacity(m_ui.m_pLineEdtOpacity->text().toFloat());
	}
}
