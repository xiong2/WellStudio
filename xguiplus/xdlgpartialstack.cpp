#include "xdlgpartialstack.h"
#include "xprocessfactory.h"
#include "xparameterspartialstack.h"
#include "xseismicdatavolume.h"
#include "xseismicirregularreader.h"
#include <QDebug>

BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgPartialStack)
EPartialStack
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgPartialStack)

CXDlgPartialStack::CXDlgPartialStack(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_pPara = dynamic_cast<CXParametersPartialStack *>(pPara);
	m_pOriDV = dynamic_cast<CXSeismicDataVolume *>(pParentObj);

	CXSeismicIrregularReader* pReader = m_pOriDV->GetIrregularReader();
	m_iStartOffset = pReader->GetMinOffset();
	m_iEndOffset = pReader->GetMaxOffset();
	m_iStartAzimuth = pReader->GetMinAzimuth();
	m_iEndAzimuth = pReader->GetMaxAzimuth();

	_initialize();
}

CXDlgPartialStack::~CXDlgPartialStack()
{
}

void CXDlgPartialStack::_initialize()
{
	//	DV name.
	ui.labelOriDVName->setText(m_pOriDV->GetObjectName());
	ui.lineEditOutputDV->setText(m_pOriDV->GetObjectName() + "(Partial Stacked)");

	//	Output range.
	const CXSeismicUTMTool& utm = m_pOriDV->GetUTM();
	ui.m_sliderInline->SetSliderName("Inline:");
	ui.m_sliderInline->SetRangeAndPrecision(utm.GetFirstInline(), utm.GetLastInline(), utm.GetInlineIncrement());
	ui.m_sliderXline->SetSliderName("Crossline:");
	ui.m_sliderXline->SetRangeAndPrecision(utm.GetFirstCrossline(), utm.GetLastCrossline(), utm.GetCrosslineIncrement());
	
	double dStartZ, dStopZ, dStep;
	m_pOriDV->GetSamplingRange(dStartZ, dStopZ, dStep);
	ui.m_sliderTime->SetSliderName("Time:");
	ui.m_sliderTime->SetRangeAndPrecision(dStartZ, dStopZ, dStep);

	int iSampleInv = (int)m_pOriDV->GetSampleInterval();
	ui.spinBoxSampleInterval->setRange(iSampleInv, 8 * iSampleInv);
	ui.spinBoxSampleInterval->setSingleStep(iSampleInv);
	ui.spinBoxSampleInterval->setValue(iSampleInv);

	//	Rolling widnow
	ui.spinBoxInlineRolling->setValue(m_pPara->GetRollingInlines());
	ui.spinBoxCrosslineRolling->setValue(m_pPara->GetRollingXlines());

	//	Common offset/azimuth gathers
	ui.labelOffsetBins->setText("The offset range from " + QString::number(m_iStartOffset) + " to " + QString::number(m_iEndOffset));
	ui.labelAzimuthRanges->setText("The azimuth range from " + QString::number(m_iStartAzimuth) + " to " + QString::number(m_iEndAzimuth));

	ui.spinBoxOffsetBinNumber->setValue(10);
	slotSetOffsetNumber(10);
	ui.spinBoxAzimuthRangeNumber->setValue(6);
	//ui.spinBoxAzimuthRangeCenter->setValue(m_pPara->GetFirstAzimuthCenter());
	//ui.checkBox->setChecked(m_pPara->GetBidirectionalAzimuth());
	slotSetAzimuthNumber(6);

	connect(ui.spinBoxOffsetBinNumber, SIGNAL(valueChanged(int)), this, SLOT(slotSetOffsetNumber(int)));
	connect(ui.spinBoxAzimuthRangeNumber, SIGNAL(valueChanged(int)), this, SLOT(slotSetAzimuthNumber(int)));
	//connect(ui.spinBoxAzimuthRangeCenter, SIGNAL(valueChanged(int)), this, SLOT(slotSetAzimuthLabel()));
	connect(ui.checkBox, SIGNAL(clicked()), this, SLOT(slotSetAzimuthLabel()));
	connect(ui.tableWidgetOffset, SIGNAL(cellChanged(int, int)), this, SLOT(slotSetItemValue(int, int)));
	connect(ui.tableWidgetAzimuth, SIGNAL(cellChanged(int, int)), this, SLOT(slotSetItemValue(int, int)));
	connect(ui.radioButtonStackAzimuth, SIGNAL(clicked()), this, SLOT(slotSetStackOption()));
	connect(ui.radioButtonStackOffset, SIGNAL(clicked()), this, SLOT(slotSetStackOption()));
	connect(ui.radioButtonStackBoth, SIGNAL(clicked()), this, SLOT(slotSetStackOption()));
}

void CXDlgPartialStack::slotSetOffsetNumber(int iNumOffsetBin)
{
	ui.tableWidgetOffset->blockSignals(true);
	ui.tableWidgetOffset->clearContents();
	ui.tableWidgetOffset->setRowCount(iNumOffsetBin);
	if (iNumOffsetBin <= 0)
		return;

	for (int i = 0; i < iNumOffsetBin; i++)
	{
		int iS = m_iStartOffset + i * (m_iEndOffset - m_iStartOffset) / iNumOffsetBin;
		ui.tableWidgetOffset->setItem(i, 0, new QTableWidgetItem(QString::number(iS)));
		//ui.tableWidgetOffset->setItem(i, 0, new QTableWidgetItem(QString::number(m_iStartOffset + i * (m_iEndOffset - m_iStartOffset) / iNumOffsetBin)));
		ui.tableWidgetOffset->setItem(i, 1, new QTableWidgetItem(QString::number(m_iStartOffset + (i + 1) * (m_iEndOffset - m_iStartOffset) / iNumOffsetBin)));
		ui.tableWidgetOffset->setItem(i, 2, new QTableWidgetItem(QString::number(m_iStartOffset + (int)((i + 0.5) * (m_iEndOffset - m_iStartOffset) / iNumOffsetBin))));
	}
	ui.tableWidgetOffset->blockSignals(false);
}

void CXDlgPartialStack::slotSetAzimuthNumber(int iNumAzimuth)
{
	ui.tableWidgetAzimuth->blockSignals(true);
	ui.tableWidgetAzimuth->clearContents();
	ui.tableWidgetAzimuth->setRowCount(iNumAzimuth);
	if (iNumAzimuth <= 0)
		return;

	for (int i = 0; i < iNumAzimuth; i++)
	{
		ui.tableWidgetAzimuth->setItem(i, 0, new QTableWidgetItem(QString::number(m_iStartAzimuth + i * (m_iEndAzimuth - m_iStartAzimuth) / iNumAzimuth)));
		ui.tableWidgetAzimuth->setItem(i, 1, new QTableWidgetItem(QString::number(m_iStartAzimuth + (i + 1) * (m_iEndAzimuth - m_iStartAzimuth) / iNumAzimuth)));
		ui.tableWidgetAzimuth->setItem(i, 2, new QTableWidgetItem(QString::number(m_iStartAzimuth + (int)((i + 0.5) * (m_iEndAzimuth - m_iStartAzimuth) / iNumAzimuth))));
	}
	ui.tableWidgetAzimuth->blockSignals(false);
}

void CXDlgPartialStack::slotSetStackOption()
{
	if (ui.radioButtonStackOffset->isChecked() == true)
	{
		ui.groupBoxOffset->setDisabled(false);
		ui.groupBoxAzimuth->setDisabled(true);
	}
	else if (ui.radioButtonStackAzimuth->isChecked() == true)
	{
		ui.groupBoxOffset->setDisabled(true);
		ui.groupBoxAzimuth->setDisabled(false);
	}
	else if (ui.radioButtonStackBoth->isChecked() == true)
	{
		ui.groupBoxOffset->setDisabled(false);
		ui.groupBoxAzimuth->setDisabled(false);
	}
}

void CXDlgPartialStack::slotSetItemValue(int iRow, int iColumn)
{
	int iS, iE;

	if (sender() == ui.tableWidgetOffset)
	{
		ui.tableWidgetOffset->blockSignals(true);
		iS = ui.tableWidgetOffset->item(iRow, 0)->text().toInt();
		iE = ui.tableWidgetOffset->item(iRow, 1)->text().toInt();
		ui.tableWidgetOffset->item(iRow, 2)->setText(QString::number((int)((iE + iS) / 2)));
		ui.tableWidgetOffset->blockSignals(false);
	}
	else if (sender() == ui.tableWidgetAzimuth)
	{
		ui.tableWidgetAzimuth->blockSignals(true);
		iS = ui.tableWidgetAzimuth->item(iRow, 0)->text().toInt();
		iE = ui.tableWidgetAzimuth->item(iRow, 1)->text().toInt();
		ui.tableWidgetAzimuth->item(iRow, 2)->setText(QString::number((int)((iE + iS) / 2)));
		ui.tableWidgetAzimuth->blockSignals(false);
	}
}

void CXDlgPartialStack::accept()
{
	//	Check the GUI and set the parameters.
	m_pPara->SetInputDVID(m_pOriDV->GetObjectID());
	m_pPara->SetOutputDVName(ui.lineEditOutputDV->text());
	m_pPara->SetStartInline(ui.m_sliderInline->GetMinValue());
	m_pPara->SetEndInline(ui.m_sliderInline->GetMaxValue());
	m_pPara->SetStartXline(ui.m_sliderXline->GetMinValue());
	m_pPara->SetEndXline(ui.m_sliderXline->GetMaxValue());
	m_pPara->SetStartZ(ui.m_sliderTime->GetMinValue());
	m_pPara->SetEndZ(ui.m_sliderTime->GetMaxValue());
	m_pPara->SetZInterval(ui.spinBoxSampleInterval->value());
	m_pPara->SetRollingInlines(ui.spinBoxInlineRolling->value());
	m_pPara->SetRollingXlines(ui.spinBoxCrosslineRolling->value());
	m_pPara->SetOffsetFirst(ui.radioButtonOffset->isChecked());

	if (ui.groupBoxOffset->isEnabled())
	{
		std::vector<int> vecOffset;
		int iRowCount = ui.tableWidgetOffset->rowCount();
		for (int i = 0; i < iRowCount; i++)
		{
			vecOffset.push_back(ui.tableWidgetOffset->item(i, 0)->text().toInt());
			vecOffset.push_back(ui.tableWidgetOffset->item(i, 1)->text().toInt());
			vecOffset.push_back(ui.tableWidgetOffset->item(i, 2)->text().toInt());
		}

		m_pPara->SetVectorOffsets(vecOffset);
	}
	if (ui.groupBoxAzimuth->isEnabled())
	{
		std::vector<int> vecAzimuth;
		int iRowCount = ui.tableWidgetAzimuth->rowCount();
		for (int i = 0; i < iRowCount; i++)
		{
			vecAzimuth.push_back(ui.tableWidgetAzimuth->item(i, 0)->text().toInt());
			vecAzimuth.push_back(ui.tableWidgetAzimuth->item(i, 1)->text().toInt());
			vecAzimuth.push_back(ui.tableWidgetAzimuth->item(i, 2)->text().toInt());
		}

		m_pPara->SetVectorAzimuth(vecAzimuth);
	}

	QDialog::accept();
}