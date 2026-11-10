#include <qmessagebox.h>
#include "xpagewellpath.h"
#include "xasciifile.h"
#include "xwellpathfile.h"

CXPageWellPath::CXPageWellPath(CXASCIIFile *pASCIIFile, QWidget *pParent): QWizardPage(pParent)
{
	ui.setupUi(this);
	m_pASCIIFile	= pASCIIFile;
}

void CXPageWellPath::initializePage()
{
	QStringList& sListAttributes = m_pASCIIFile->GetAttributes();

	//	Uses the selected columns to determine which radio box could be checked.
	bool bSet = false;
	if(sListAttributes.contains("MD") && sListAttributes.contains("Inclination") && sListAttributes.contains("Azimuth"))
	{
		ui.radioButtonAzi->setEnabled(true);
		ui.radioButtonAzi->setChecked(true);
		bSet = true;
	}
	else
		ui.radioButtonAzi->setEnabled(false);

	if(sListAttributes.contains("TVD") && sListAttributes.contains("DX") && sListAttributes.contains("DY"))
	{
		ui.radioButtonTVDDXDY->setEnabled(true);

		if(!bSet)
		{
			ui.radioButtonTVDDXDY->setChecked(true);
			bSet = true;
		}
	}
	else
		ui.radioButtonTVDDXDY->setEnabled(false);

	if(sListAttributes.contains("TVD") && sListAttributes.contains("X") && sListAttributes.contains("Y"))
	{
		ui.radioButtonTVDXY->setEnabled(true);

		if(!bSet)
		{
			ui.radioButtonTVDXY->setChecked(true);
			bSet = true;
		}
	}
	else
		ui.radioButtonTVDXY->setEnabled(false);

	if(sListAttributes.contains("X") && sListAttributes.contains("Y") && sListAttributes.contains("Z"))
	{
		ui.radioButtonXYZ->setEnabled(true);

		if(!bSet)
		{
			ui.radioButtonXYZ->setChecked(true);
			bSet = true;
		}
	}
	else
		ui.radioButtonXYZ->setEnabled(false);

	if(sListAttributes.contains("DX") && sListAttributes.contains("DY") && sListAttributes.contains("DZ"))
	{
		ui.radioButtonDXDYDZ->setEnabled(true);

		if(!bSet)
		{
			ui.radioButtonDXDYDZ->setChecked(true);
			bSet = true;
		}
	}
	else
		ui.radioButtonDXDYDZ->setEnabled(false);
}

bool CXPageWellPath::validatePage()
{
	unsigned int iImportMode = 9;
	if(ui.radioButtonAzi->isChecked())
		iImportMode = 0;
	else if(ui.radioButtonTVDDXDY->isChecked())
		iImportMode = 1;
	else if(ui.radioButtonTVDXY->isChecked())
		iImportMode = 2;
	else if(ui.radioButtonXYZ->isChecked())
		iImportMode = 3;
	else if(ui.radioButtonDXDYDZ->isChecked())
		iImportMode = 4;

	if(iImportMode == 9)
	{
		QMessageBox::warning(NULL, "Import Well Path", "No enough data columns selected!");
		return false;
	}

	CXWellPathFile *pWellPathFile = dynamic_cast<CXWellPathFile *>(m_pASCIIFile);
	pWellPathFile->SetImportMode(iImportMode);
	pWellPathFile->SetNegateZ(ui.checkBox->isChecked());
	pWellPathFile->SetSimplify(ui.checkBoxSimplify->isChecked());

	return true;
}