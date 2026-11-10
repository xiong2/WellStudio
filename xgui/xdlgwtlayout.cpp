#include "xdlgwtlayout.h"
#include "xdlgwelltie.h"
#include "xframewelltie.h"

XDlgWTLayout::XDlgWTLayout(CXDlgWellTie *pDlg)
	: QDialog(pDlg)
{
	ui.setupUi(this);

	SLayout& sLayout = pDlg->GetSLayout();

	ui.checkBoxAC->setChecked(sLayout.m_iShowTracks & 0b1);
	ui.checkBoxDen->setChecked(sLayout.m_iShowTracks & 0b10);
	ui.checkBoxRC->setChecked(sLayout.m_iShowTracks & 0b100);
	ui.checkBoxDT->setChecked(sLayout.m_iShowTracks & 0b1000);
	ui.checkBoxDrift->setChecked(sLayout.m_iShowTracks & 0b10000);
	ui.spinBox->setValue(sLayout.m_iNumTraces);
	ui.comboBoxLeft->setCurrentIndex(sLayout.m_iLType);
	ui.comboBoxRight->setCurrentIndex(sLayout.m_iRType);
}

XDlgWTLayout::~XDlgWTLayout()
{
}

void XDlgWTLayout::accept()
{
	CXDlgWellTie *pDlg = (CXDlgWellTie *)parent();
	SLayout& sLayout = pDlg->GetSLayout();
	sLayout.m_iShowTracks = 0;
	if (ui.checkBoxAC->isChecked())
		sLayout.m_iShowTracks |= 0b1;
	if (ui.checkBoxDen->isChecked())
		sLayout.m_iShowTracks |= 0b10;
	if (ui.checkBoxRC->isChecked())
		sLayout.m_iShowTracks |= 0b100;
	if (ui.checkBoxDT->isChecked())
		sLayout.m_iShowTracks |= 0b1000;
	if (ui.checkBoxDrift->isChecked())
		sLayout.m_iShowTracks |= 0b10000;

	sLayout.m_iNumTraces = ui.spinBox->value();
	sLayout.m_iLType = ui.comboBoxLeft->currentIndex();
	sLayout.m_iRType = ui.comboBoxRight->currentIndex();

	pDlg->RefreshLayout();

	QDialog::accept();
}
