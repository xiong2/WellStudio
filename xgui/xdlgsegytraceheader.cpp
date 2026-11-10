#include "xdlgsegytraceheader.h"
#include "xsegyloadparameters.h"
#include "xsegytraceheader.h"

CXDlgSEGYTraceHeader::CXDlgSEGYTraceHeader(CXSEGYLoadParameters *pParameters, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pParameters	= pParameters;
	m_pTraceHeader	= NULL;
	m_bOKForAll		= false;

	if (m_pParameters)
		initialize();

	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(acceptAll()));
}

CXDlgSEGYTraceHeader::~CXDlgSEGYTraceHeader()
{

}

void CXDlgSEGYTraceHeader::initialize()
{
	//	Current trace.
	int iNumTrace = m_pParameters->GetTraceNumber();
	ui.labelTrace->setText("Current trace: 1 (1 of " + QString::number(iNumTrace) + " traces)");
	ui.horizontalSlider->setValue(1);
	ui.horizontalSlider->setRange(1, iNumTrace);
	ui.spinBox->setValue(1);
	ui.spinBox->setRange(1, iNumTrace);

	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotTraceNumberChanged(int)));
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(slotTraceNumberChanged(int)));

	//	Populate the tab.
	m_pTraceHeader = m_pParameters->GetOneTraceHeader(1);
	ui.tableWidget->SetData(m_pTraceHeader);
	ui.tableWidget->SetParentWidget(this);

	ui.lineEditCDP->setText(QString::number(m_pParameters->GetCrosslinePosition()));
	ui.lineEditX->setText(QString::number(m_pParameters->GetXPosition()));
	ui.lineEditY->setText(QString::number(m_pParameters->GetYPosition()));
}

void CXDlgSEGYTraceHeader::slotTraceNumberChanged(int iValue)
{
	ui.horizontalSlider->blockSignals(true);
	ui.spinBox->blockSignals(true);

	ui.labelTrace->setText("Current trace: " + QString::number(iValue) + " (" + QString::number(iValue) + " of " + QString::number(m_pParameters->GetTraceNumber()) + " traces)");
	m_pTraceHeader = m_pParameters->GetOneTraceHeader(iValue);
	ui.horizontalSlider->setValue(iValue);
	ui.spinBox->setValue(iValue);

	ui.horizontalSlider->blockSignals(false);
	ui.spinBox->blockSignals(false);
	ui.tableWidget->UpdateTableValue();
}

void CXDlgSEGYTraceHeader::accept()
{
	m_pParameters->SetCrosslinePosition(ui.lineEditCDP->text().toUShort());
	m_pParameters->SetXPosition(ui.lineEditX->text().toUShort());
	m_pParameters->SetYPosition(ui.lineEditY->text().toUShort());

	QDialog::accept();
}

void CXDlgSEGYTraceHeader::acceptAll()
{
	m_bOKForAll = true;

	accept();
}