#include "xpagetimeslicevis.h"
#include "xviewinfotimeslice.h"
#include "xobject.h"
#include "xglobal.h"

CXPageTimeSliceVis::CXPageTimeSliceVis(QWidget *parent, CXViewInfoObject* pViewInfo, CXObject* pObj, EXWindowType typeWin)
	: CXBasePropertyPage(parent), m_pObj(pObj), m_typeWin(typeWin)
{
	m_ui.setupUi(this);
	m_pViewInfo = dynamic_cast<CXViewInfoTimeSlice*>(pViewInfo);

	_Init();
}

CXPageTimeSliceVis::~CXPageTimeSliceVis()
{
}

void CXPageTimeSliceVis::Apply()
{
	switch (m_typeWin)
	{
	case e2DSection:
	{
		_ApplyForSectionWindow();
		break;
	}
	case e3DBaseMap:
	{
		_ApplyForBaseMapWindow();
		break;
	}
	case e3DWindow:
	{
		_ApplyFor3DWindow();
		break;
	}
	}
}

void CXPageTimeSliceVis::SetObjectColorBuddyButton(CXButtonColorEdit * pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_pClrBtnSectionLineColor, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_pClrBtnBMFrameColor, &CXButtonColorEdit::slotObjectColorChanged);
}

void CXPageTimeSliceVis::_Init()
{
	switch (m_typeWin)
	{
	case e2DSection:
	{
		m_ui.m_pStackedWidget->setCurrentIndex(0);
		_InitForSectionWindow();
		break;
	}
	case e3DBaseMap:
	{
		m_ui.m_pStackedWidget->setCurrentIndex(1);
		_InitForBaseMapWindow();
		break;
	}
	case e3DWindow:
	{
		m_ui.m_pStackedWidget->setCurrentIndex(2);
		_InitFor3DWindow();
		break;
	}
	}
}

void CXPageTimeSliceVis::_InitForSectionWindow()
{
	m_ui.m_pClrBtnSectionLineColor->SetColor(m_pViewInfo->GetLineColor());
	m_ui.m_pCbbSectionLineType->SetLineType(Qt::PenStyle(m_pViewInfo->GetLineStyle()));
	m_ui.m_pCbbSectionLineWidth->SetLineWidth(m_pViewInfo->GetLineSize());
}

void CXPageTimeSliceVis::_InitForBaseMapWindow()
{
	m_ui.m_pGbxBMFrac->setVisible(false);

	m_ui.m_pRdoBMFrac->setChecked(m_pViewInfo->GetDisplayMode());
	m_ui.m_pClrBtnBMFrameColor->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui.m_pClrBtnBMFrameColor->SetColor(m_pViewInfo->GetBMLineUseObjectColor(), m_pViewInfo->GetBMLineColor());
	m_ui.m_pCbbBMFrameWidth->SetLineWidth(m_pViewInfo->GetBMLineWidth());
	m_ui.m_pChkBMSeismic->setChecked(m_pViewInfo->GetSeismicDisplay());
	m_ui.m_pClrBtnBMFracColor->SetColor(m_pViewInfo->GetFracColor());
	m_ui.m_pEdtBMFracDX->setText(QString::number(m_pViewInfo->GetFracDX()));
	m_ui.m_pEdtBMFracDY->setText(QString::number(m_pViewInfo->GetFracDY()));
	m_ui.m_pEdtBMFracScale->setText(QString::number(m_pViewInfo->GetFracScale()));
	m_ui.m_pEdtBMFracMin->setText(QString::number(m_pViewInfo->GetFracMinThreshold() * 100));
	m_ui.m_pEdtBMFracMax->setText(QString::number(m_pViewInfo->GetFracMaxThreshold() * 100));
	m_ui.m_pEdtBMFracWidth->setText(QString::number(m_pViewInfo->GetFracWidth()));

	_InitAttributeList(m_ui.m_pCbbBMFracAzi, m_ui.m_pCbbBMFracDen);

	int iFracAzimuth = m_ui.m_pCbbBMFracAzi->findData(m_pViewInfo->GetFracAzimuth());
	if (iFracAzimuth != -1)
	{
		m_ui.m_pCbbBMFracAzi->setCurrentIndex(iFracAzimuth);
	}

	int iFracDensity = m_ui.m_pCbbBMFracDen->findData(m_pViewInfo->GetFracDensity());
	if (iFracDensity != -1)
	{
		m_ui.m_pCbbBMFracDen->setCurrentIndex(iFracDensity);
	}
}

void CXPageTimeSliceVis::_InitFor3DWindow()
{
	m_ui.m_pGbx3DFrac->setVisible(false);

	m_ui.m_pRdo3DFrac->setChecked(m_pViewInfo->GetDisplayMode());
	m_ui.m_pChk3DFracSeismic->setChecked(m_pViewInfo->GetSeismicDisplay());
	m_ui.m_pClrBtn3DFracColor->SetColor(m_pViewInfo->GetFracColor());
	m_ui.m_pEdt3DFracDX->setText(QString::number(m_pViewInfo->GetFracDX()));
	m_ui.m_pEdt3DFracDY->setText(QString::number(m_pViewInfo->GetFracDY()));
	m_ui.m_pEdt3DFracScale->setText(QString::number(m_pViewInfo->GetFracScale()));
	m_ui.m_pEdt3DFracMin->setText(QString::number(m_pViewInfo->GetFracMinThreshold() * 100));
	m_ui.m_pEdt3DFracMax->setText(QString::number(m_pViewInfo->GetFracMaxThreshold() * 100));
	m_ui.m_pEdt3DFracHeight->setText(QString::number(m_pViewInfo->GetFracHeight()));

	_InitAttributeList(m_ui.m_pCbb3DFracAzi, m_ui.m_pCbb3DFracDen);

	int iFracAzimuth = m_ui.m_pCbb3DFracAzi->findData(m_pViewInfo->GetFracAzimuth());
	if (iFracAzimuth != -1)
	{
		m_ui.m_pCbb3DFracAzi->setCurrentIndex(iFracAzimuth);
	}

	int iFracDensity = m_ui.m_pCbb3DFracDen->findData(m_pViewInfo->GetFracDensity());
	if (iFracDensity != -1)
	{
		m_ui.m_pCbb3DFracDen->setCurrentIndex(iFracDensity);
	}
}

void CXPageTimeSliceVis::_InitAttributeList(QComboBox* pCbbAzi, QComboBox* pCbbDen)
{
	pCbbAzi->clear();
	pCbbDen->clear();

	for (CXObject* pObj : m_pObj->GetAncient(EX3DSurvey)->GetChildren(EXSeismicDataVolume, true))
	{
		double dMin, dMax;
		pObj->GetDataRange(dMin, dMax);

		if (0.0 <= dMin && dMax <= 360.0 || -180.0 <= dMin && dMax <= 180.0)
		{
			pCbbAzi->addItem(QIcon(::GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID());
		}

		pCbbDen->addItem(QIcon(::GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID());
	}

	pCbbAzi->setCurrentIndex(pCbbAzi->findData(m_pViewInfo->GetFracAzimuth()));
	pCbbDen->setCurrentIndex(pCbbDen->findData(m_pViewInfo->GetFracDensity()));
}

void CXPageTimeSliceVis::_ApplyForSectionWindow()
{
	m_pViewInfo->SetLineColor(m_ui.m_pClrBtnSectionLineColor->GetColor());
	m_pViewInfo->SetLineStyle(m_ui.m_pCbbSectionLineType->currentIndex() + 1);
	m_pViewInfo->SetLineSize(m_ui.m_pCbbSectionLineWidth->GetLineWidth());
}

void CXPageTimeSliceVis::_ApplyForBaseMapWindow()
{
	m_pViewInfo->SetDisplayMode(m_ui.m_pRdoBMFrac->isChecked());
	m_pViewInfo->SetBMLineColor(m_ui.m_pClrBtnBMFrameColor->GetColor());
	m_pViewInfo->SetBMLineUseObjectColor(m_ui.m_pClrBtnBMFrameColor->ColorType());
	m_pViewInfo->SetBMLineWidth(m_ui.m_pCbbBMFrameWidth->GetLineWidth());
	m_pViewInfo->SetSeismicDisplay(m_ui.m_pChkBMSeismic->isChecked());
	m_pViewInfo->SetFracColor(m_ui.m_pClrBtnBMFracColor->GetColor());
	m_pViewInfo->SetFracAzimuth(m_ui.m_pCbbBMFracAzi->currentData().toUuid());
	m_pViewInfo->SetFracDensity(m_ui.m_pCbbBMFracDen->currentData().toUuid());
	m_pViewInfo->SetFracDX(m_ui.m_pEdtBMFracDX->text().toInt());
	m_pViewInfo->SetFracDY(m_ui.m_pEdtBMFracDY->text().toInt());
	m_pViewInfo->SetFracScale(m_ui.m_pEdtBMFracScale->text().toFloat());
	m_pViewInfo->SetFracMinThreshold(m_ui.m_pEdtBMFracMin->text().toInt() / 100.f);
	m_pViewInfo->SetFracMaxThreshold(m_ui.m_pEdtBMFracMax->text().toInt() / 100.f);
	m_pViewInfo->SetFracWidth(m_ui.m_pEdtBMFracWidth->text().toInt());
}

void CXPageTimeSliceVis::_ApplyFor3DWindow()
{
	m_pViewInfo->SetDisplayMode(m_ui.m_pRdo3DFrac->isChecked());
	m_pViewInfo->SetSeismicDisplay(m_ui.m_pChk3DFracSeismic->isChecked());
	m_pViewInfo->SetFracColor(m_ui.m_pClrBtn3DFracColor->GetColor());
	m_pViewInfo->SetFracAzimuth(m_ui.m_pCbb3DFracAzi->currentData().toUuid());
	m_pViewInfo->SetFracDensity(m_ui.m_pCbb3DFracDen->currentData().toUuid());
	m_pViewInfo->SetFracDX(m_ui.m_pEdt3DFracDX->text().toInt());
	m_pViewInfo->SetFracDY(m_ui.m_pEdt3DFracDY->text().toInt());
	m_pViewInfo->SetFracScale(m_ui.m_pEdt3DFracScale->text().toFloat());
	m_pViewInfo->SetFracMinThreshold(m_ui.m_pEdt3DFracMin->text().toInt() / 100.f);
	m_pViewInfo->SetFracMaxThreshold(m_ui.m_pEdt3DFracMax->text().toInt() / 100.f);
	m_pViewInfo->SetFracHeight(m_ui.m_pEdt3DFracHeight->text().toInt());
}