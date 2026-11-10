#include "xdlgrosediagram.h"
#include "xseismicdatavolume.h"
#include "xseismicirregularreader.h"
#include <qmessagebox.h>

CXDlgRoseDiagram::CXDlgRoseDiagram(CXObject *pObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_pDV = dynamic_cast<CXSeismicDataVolume *>(pObj);

	if(m_pDV)
		_InitUI();
}

CXDlgRoseDiagram::~CXDlgRoseDiagram()
{

}

void CXDlgRoseDiagram::_InitUI()
{
	ui.pushButtonRoseColor->SetColor(QColor(210, 127, 111));
	ui.pushButtonGridColor->SetColor(QColor("green"));
	ui.comboBox->SetCurrentText("greyscale");

	ui.frame->m_pReader = m_pDV->GetIrregularReader();
	ui.frame->m_iNumGather = m_pDV->GetUTM().GetNI() * m_pDV->GetUTM().GetNJ();
	unsigned short iMinOffset = ui.frame->m_pReader->GetMinOffset();
	unsigned short iMaxOffset = ui.frame->m_pReader->GetMaxOffset();
	ui.labelOffset->setText("from " + QString::number(iMinOffset) + "m to " + QString::number(iMaxOffset) + "m");

	connect(ui.pushButtonRefresh, SIGNAL(clicked()), this, SLOT(slotRefreshData()));
	connect(ui.pushButtonClose, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.checkBoxRose, SIGNAL(clicked()), this, SLOT(slotRefreshVisPara()));
	connect(ui.checkBoxGrid, SIGNAL(clicked()), this, SLOT(slotRefreshVisPara()));
	connect(ui.checkBoxBins, SIGNAL(clicked()), this, SLOT(slotRefreshVisPara()));
	connect(ui.checkBoxHisto, SIGNAL(clicked()), this, SLOT(slotRefreshVisPara()));
	connect(ui.pushButtonGridColor, &CXButtonColorEdit::ColorSelected, this, &CXDlgRoseDiagram::slotRefreshVisPara);
	connect(ui.pushButtonRoseColor, &CXButtonColorEdit::ColorSelected, this, &CXDlgRoseDiagram::slotRefreshVisPara);
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotOpanChanged()));
	connect(ui.lineEditOpancity, SIGNAL(editingFinished()), this, SLOT(slotOpanChanged()));
	connect(ui.comboBox, SIGNAL(currentTextChanged(const QString &text)), this, SLOT(slotRefreshVisPara()));
	connect(ui.comboBox, &CXColormapCombo::currentTextChanged, this, &CXDlgRoseDiagram::slotRefreshVisPara);
}

void CXDlgRoseDiagram::slotRefreshData()
{
	int iStartRose = ui.lineEditStartAzi->text().toInt();
	int iEndRose = ui.lineEditEndAzi->text().toInt();
	if (iStartRose < -360 || iEndRose > 360 || iStartRose >= iEndRose)
	{
		QMessageBox::warning(NULL, "Error Parameters", 
			"Rose angles wrong!\nBoth should be integer within -360 to 360,\nAnd \"From\" should less than \"To\".");
		return;
	}

	ui.frame->Refresh(ui.spinBoxRose->value(), iStartRose, iEndRose, ui.spinBoxBins->value());
}

void CXDlgRoseDiagram::slotRefreshVisPara()
{
	ui.frame->m_bBins = ui.checkBoxBins->isChecked();
	ui.frame->m_bGrid = ui.checkBoxGrid->isChecked();
	ui.frame->m_bRose = ui.checkBoxRose->isChecked();
	ui.frame->m_bHisto = ui.checkBoxHisto->isChecked();

	ui.frame->m_strColormap = ui.comboBox->currentText();
	ui.frame->m_roseColor = ui.pushButtonRoseColor->GetColor();
	ui.frame->m_roseColor.setAlpha(ui.horizontalSlider->value());
	ui.frame->m_gridColor = ui.pushButtonGridColor->GetColor();

	ui.frame->update();
}

void CXDlgRoseDiagram::slotOpanChanged()
{
	int iValue;
	if (sender() == ui.horizontalSlider)
	{
		iValue = ui.horizontalSlider->value();
		ui.lineEditOpancity->blockSignals(true);
		ui.lineEditOpancity->setText(QString::number(iValue / 255., 'g', 2));
		ui.lineEditOpancity->blockSignals(false);
	}
	else
	{
		iValue = (int)(ui.lineEditOpancity->text().toFloat() * 255);
		iValue = iValue > 255 ? 255 : iValue;
		iValue = iValue < 0 ? 0 : iValue;

		ui.horizontalSlider->blockSignals(true);
		ui.horizontalSlider->setValue(iValue);
		ui.horizontalSlider->blockSignals(false);
	}

	ui.frame->m_roseColor.setAlpha(iValue);

	ui.frame->update();
}
