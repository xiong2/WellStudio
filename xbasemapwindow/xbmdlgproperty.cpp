#include "xbmdlgproperty.h"
#include "xwindowinfobasemap.h"
#include "xbasemapwindow.h"
#include "xbasemapscene.h"

CXBMDlgProperty::CXBMDlgProperty(QWidget *parent, CXWindowInfoBasemap* pWindowInfo)
	: QDialog(parent), m_pWindowInfo(pWindowInfo)
{
	m_ui.setupUi(this);

	setWindowTitle("Properties for" + parent->windowTitle());
	setAttribute(Qt::WA_DeleteOnClose);

	_InitUI();
	connect(m_ui.m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::pressed, this, &CXBMDlgProperty::slotApply);
	connect(m_ui.m_buttonBox, &QDialogButtonBox::accepted, this, &CXBMDlgProperty::slotApply);
}

CXBMDlgProperty::~CXBMDlgProperty()
{

}

void CXBMDlgProperty::slotApply()
{
	CXBaseMapWindow *pWindow = dynamic_cast<CXBaseMapWindow *>(parent());

	switch (m_ui.m_tab->currentIndex())
	{
	case 0: // Axis
		m_pWindowInfo->SetCoordVisible(m_ui.m_cbAxisVisible->isChecked());
		m_pWindowInfo->SetCoordColor(m_ui.m_colorBtnAxis->GetColor());
		m_pWindowInfo->SetCoordLineWidth(m_ui.m_spinBoxAxisLineWidth->value());
		m_pWindowInfo->SetCoordTickLength(m_ui.m_spinBoxAxisTickSize->value());

		m_pWindowInfo->SetCoordMarkFont(m_ui.m_cbbAxisMarkFont->currentText());
		m_pWindowInfo->SetCoordMarkSize(m_ui.m_spinBoxAxisMarkFontSize->value());

		m_pWindowInfo->SetCoordLabelVisible(m_ui.m_cbAxisLabelVisible->isChecked());
		m_pWindowInfo->SetCoordLabelFont(m_ui.m_cbbAxisLabelFont->currentText());
		m_pWindowInfo->SetCoordLabelSize(m_ui.m_spinBoxAxisLabelFontSize->value());
		m_pWindowInfo->SetCoordLabelX(m_ui.m_editAxisX->text());
		m_pWindowInfo->SetCoordLabelY(m_ui.m_editAxisY->text());

		m_pWindowInfo->SetCoordGridVisible(m_ui.m_cbAxisGridVisible->isChecked());
		m_pWindowInfo->SetCoordGridColor(m_ui.m_colorBtnAxisGrid->GetColor());
		m_pWindowInfo->SetCoordGridLineWidth(m_ui.m_spinBoxAxisGridLineWidth->value());

		pWindow->GetOSGScene()->UpdateCoordinateInfo();
		break;
	case 1: // Colorbar
		m_pWindowInfo->SetColorbarTitleVisible(m_ui.m_cbColorbarTitle->isChecked());
		m_pWindowInfo->SetColorbarTitleColor(m_ui.m_colorBtnColorbarTitle->GetColor());
		m_pWindowInfo->SetColorbarTitleSize(m_ui.m_spinBoxColorbarTitleFontSize->value());
		m_pWindowInfo->SetColorbarTitleFont(m_ui.m_cbbColorbarTitleFont->currentText());

		m_pWindowInfo->SetColorbarTickColor(m_ui.m_colorbtnColorbarTick->GetColor());
		m_pWindowInfo->SetColorbarTickSize(m_ui.m_spinBoxColorbarTickLength->value());
		
		m_pWindowInfo->SetColorbarMarkColor(m_ui.m_colorBtnColorbarMark->GetColor());
		m_pWindowInfo->SetColorbarMarkFont(m_ui.m_cbbColorbarMarkFont->currentText());
		m_pWindowInfo->SetColorbarMarkSize(m_ui.m_spinBoxColorbarMarkFontSize->value());

		m_pWindowInfo->SetColorbarPosition(m_ui.m_btnGroupColorbarPosition->checkedId());

		pWindow->GetOSGScene()->UpdateColorbarInfo();

		break;
	case 2: // Scalebar
		m_pWindowInfo->SetScalebarPosition(m_ui.m_btnGroupScalePosition->checkedId());
		m_pWindowInfo->SetScaleMarkColor(m_ui.m_colorBtnScaleMark->GetColor());
		m_pWindowInfo->SetScaleMarkSize(m_ui.m_spinBoxScaleMarkFontSize->value());
		m_pWindowInfo->SetScaleMarkFont(m_ui.m_cbbScaleMarkFont->currentText());
		m_pWindowInfo->SetScaleFrameColor(m_ui.m_colorBtnScaleFrame->GetColor());

		pWindow->GetOSGScene()->UpdateScaleInfo();
		break;
	case 3: // Compass
		m_pWindowInfo->SetCompassTopColor(m_ui.m_colorBtnCompassTop->GetColor());
		m_pWindowInfo->SetCompassBottomColor(m_ui.m_colorBtnCompassBottom->GetColor());
		m_pWindowInfo->SetCompassFrameColor(m_ui.m_colorBtnCompassFrame->GetColor());
		m_pWindowInfo->SetCompassPosition(m_ui.m_btnGroupCompassPosition->checkedId());

		pWindow->GetOSGScene()->UpdateCompassInfo();
		break;
	default:
		throw std::logic_error("no this tab!");
	}

	pWindow->update();
}

void CXBMDlgProperty::_InitUI()
{
	// Axis
	m_ui.m_cbAxisVisible->setChecked(m_pWindowInfo->GetCoordVisible());
	m_ui.m_colorBtnAxis->SetColor(m_pWindowInfo->GetCoordColor());
	m_ui.m_spinBoxAxisLineWidth->setValue(m_pWindowInfo->GetCoordLineWidth());
	m_ui.m_spinBoxAxisTickSize->setValue(m_pWindowInfo->GetCoordTickLength());

	m_ui.m_cbbAxisMarkFont->setCurrentText(m_pWindowInfo->GetCoordMarkFont());
	m_ui.m_spinBoxAxisMarkFontSize->setValue(m_pWindowInfo->GetCoordMarkSize());

	m_ui.m_cbAxisLabelVisible->setChecked(m_pWindowInfo->GetCoordLabelVisible());
	m_ui.m_cbbAxisLabelFont->setCurrentText(m_pWindowInfo->GetCoordLabelFont());
	m_ui.m_spinBoxAxisLabelFontSize->setValue(m_pWindowInfo->GetCoordLabelSize());
	m_ui.m_editAxisX->setText(m_pWindowInfo->GetCoordLabelX());
	m_ui.m_editAxisY->setText(m_pWindowInfo->GetCoordLabelY());

	m_ui.m_cbAxisGridVisible->setChecked(m_pWindowInfo->GetCoordGridVisible());
	m_ui.m_colorBtnAxisGrid->SetColor(m_pWindowInfo->GetCoordGridColor());
	m_ui.m_spinBoxAxisGridLineWidth->setValue(m_pWindowInfo->GetCoordGridLineWidth());

	// Colorbar
	m_ui.m_cbColorbarTitle->setChecked(m_pWindowInfo->GetColorbarTitleVisible());
	m_ui.m_colorBtnColorbarTitle->SetColor(m_pWindowInfo->GetColorbarTitleColor());
	m_ui.m_cbbColorbarTitleFont->setCurrentText(m_pWindowInfo->GetColorbarTitleFont());
	m_ui.m_spinBoxColorbarTitleFontSize->setValue(m_pWindowInfo->GetColorbarTitleSize());

	m_ui.m_colorbtnColorbarTick->SetColor(m_pWindowInfo->GetColorbarTickColor());
	m_ui.m_spinBoxColorbarTickLength->setValue(m_pWindowInfo->GetColorbarTickSize());

	m_ui.m_colorBtnColorbarMark->SetColor(m_pWindowInfo->GetColorbarMarkColor());
	m_ui.m_spinBoxColorbarMarkFontSize->setValue(m_pWindowInfo->GetColorbarMarkSize());
	m_ui.m_cbbColorbarMarkFont->setCurrentText(m_pWindowInfo->GetColorbarMarkFont());

	m_ui.m_btnGroupColorbarPosition->setId(m_ui.m_rbColorbarPosTopLeft, 0);
	m_ui.m_btnGroupColorbarPosition->setId(m_ui.m_rbColorbarPosBottomLeft, 1);
	m_ui.m_btnGroupColorbarPosition->setId(m_ui.m_rbColorbarPosBottomRight, 2);
	m_ui.m_btnGroupColorbarPosition->setId(m_ui.m_rbColorbarPosTopRight, 3);
	m_ui.m_btnGroupColorbarPosition->button(m_pWindowInfo->GetColorbarPosition())->setChecked(true);

	// Scale
	m_ui.m_btnGroupScalePosition->setId(m_ui.m_rbScalePosBottomLeft, 0);
	m_ui.m_btnGroupScalePosition->setId(m_ui.m_rbScalePosBottomRight, 1);
	m_ui.m_btnGroupScalePosition->setId(m_ui.m_rbScalePosTopRight, 2);
	m_ui.m_btnGroupScalePosition->setId(m_ui.m_rbScalePosTopLeft, 3);
	m_ui.m_btnGroupScalePosition->button(m_pWindowInfo->GetScalebarPosition())->setChecked(true);
	m_ui.m_colorBtnScaleMark->SetColor(m_pWindowInfo->GetScaleMarkColor());
	m_ui.m_spinBoxScaleMarkFontSize->setValue(m_pWindowInfo->GetScaleMarkSize());
	m_ui.m_cbbScaleMarkFont->setCurrentText(m_pWindowInfo->GetScaleMarkFont());
	m_ui.m_colorBtnScaleFrame->SetColor(m_pWindowInfo->GetScaleFrameColor());

	// Compass
	m_ui.m_colorBtnCompassTop->SetColor(m_pWindowInfo->GetCompassTopColor());
	m_ui.m_colorBtnCompassBottom->SetColor(m_pWindowInfo->GetCompassBottomColor());
	m_ui.m_colorBtnCompassFrame->SetColor(m_pWindowInfo->GetCompassFrameColor());
	m_ui.m_btnGroupCompassPosition->setId(m_ui.m_rbCompassPosBottomRight, 0);
	m_ui.m_btnGroupCompassPosition->setId(m_ui.m_rbCompassPosTopRight, 1);
	m_ui.m_btnGroupCompassPosition->setId(m_ui.m_rbCompassPosTopLeft, 2);
	m_ui.m_btnGroupCompassPosition->setId(m_ui.m_rbCompassPosBottomLeft, 3);
	m_ui.m_btnGroupCompassPosition->button(m_pWindowInfo->GetCompassPosition())->setChecked(true);
}