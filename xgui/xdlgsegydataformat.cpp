#include <QStackedLayout>
#include "xdlgsegydataformat.h"
#include "xpageloadsegyhistogram.h"
#include "xpageloadsegywiggle.h"
#include "xsegyloadparameters.h"

CXDlgSEGYDataFormat::CXDlgSEGYDataFormat(CXSEGYLoadParameters *pParameters, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_pParameters	= pParameters;
	m_bOKForAll		= false;
	m_pTraceData	= NULL;

	initialize();
	refreshPreview();

	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(acceptAll()));
}

CXDlgSEGYDataFormat::~CXDlgSEGYDataFormat()
{
	if (m_pTraceData)
		delete[]m_pTraceData;
}

void CXDlgSEGYDataFormat::initialize()
{
	int iNumSample = m_pParameters->GetSampleNumber();
	ui.lineEditSampleNum->setText(QString::number(iNumSample));
	ui.lineEditInterval->setText(QString::number(m_pParameters->GetSampleInterval()));
	ui.comboBox->setCurrentIndex(m_pParameters->GetDataType());
	ui.checkBox->setChecked(m_pParameters->DataNeedFlip());

	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSampleFormatChanged(int)));
	connect(ui.checkBox, SIGNAL(clicked()), this, SLOT(slotFlipData()));

	ui.labelTraceNum->setText("Total Traces: " + QString::number(m_pParameters->GetTraceNumber()));
	ui.horizontalSlider->setRange(1, m_pParameters->GetTraceNumber());
	ui.spinBox->setRange(1, m_pParameters->GetTraceNumber());

	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotTraceNumberChanged(int)));
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(slotTraceNumberChanged(int)));

	//	Trace preview.
	m_pTraceData = new float[iNumSample];
	CXPageLoadSegyWiggle *pWiggleWidget = new CXPageLoadSegyWiggle(NULL);
	CXPageLoadSegyHistogram *pHistogramFrame = new CXPageLoadSegyHistogram(NULL);
	QStackedLayout *pStackedLayout = new QStackedLayout(ui.frame);
	pStackedLayout->addWidget(pWiggleWidget);
	pStackedLayout->addWidget(pHistogramFrame);
	pHistogramFrame->SetTraceData(m_pTraceData, iNumSample);
	pWiggleWidget->SetTraceData(m_pTraceData, iNumSample);

	connect(ui.radioButtonHisto, SIGNAL(clicked()), this, SLOT(slotSelectDisplayMode()));
	connect(ui.radioButtonWiggle, SIGNAL(clicked()), this, SLOT(slotSelectDisplayMode()));
}

void CXDlgSEGYDataFormat::refreshPreview()
{
	int iTraceID = ui.spinBox->value();
	m_pParameters->GetOneTraceData(iTraceID, m_pTraceData);

	QStackedLayout *pStackedLayout = dynamic_cast<QStackedLayout *>(ui.frame->layout());
	CXPageLoadSegyHistogram *pPageHisto = dynamic_cast<CXPageLoadSegyHistogram*>(pStackedLayout->widget(1));
	CXPageLoadSegyWiggle *pPageWiggle = dynamic_cast<CXPageLoadSegyWiggle*>(pStackedLayout->widget(0));
	if (pPageHisto)
	{
		pPageHisto->SetTraceData(m_pTraceData, m_pParameters->GetSampleNumber());
	}
	if (pPageWiggle)
	{
		pPageWiggle->SetTraceData(m_pTraceData, m_pParameters->GetSampleNumber());
	}
}

void CXDlgSEGYDataFormat::slotTraceNumberChanged(int iValue)
{
	ui.horizontalSlider->blockSignals(true);
	ui.spinBox->blockSignals(true);

	ui.horizontalSlider->setValue(iValue);
	ui.spinBox->setValue(iValue);

	ui.horizontalSlider->blockSignals(false);
	ui.spinBox->blockSignals(false);

	refreshPreview();
}

void CXDlgSEGYDataFormat::slotSelectDisplayMode()
{
	QRadioButton * pRdo = dynamic_cast<QRadioButton*>(sender());
	QStackedLayout *pStackedLayout = dynamic_cast<QStackedLayout*>(ui.frame->layout());

	if (pRdo == ui.radioButtonWiggle)
	{
		pStackedLayout->setCurrentIndex(0);

	}
	else
	{
		pStackedLayout->setCurrentIndex(1);
	}
}

void CXDlgSEGYDataFormat::slotFlipData()
{
	m_pParameters->SetDataFlip(ui.checkBox->isChecked());
	refreshPreview();
}

void CXDlgSEGYDataFormat::slotSampleFormatChanged(int nFormateType)
{
	if (nFormateType == 1)
	{
		ui.checkBox->setChecked(true);
		ui.checkBox->setEnabled(false);
	}
	else if (nFormateType == 4)
	{
		ui.checkBox->setChecked(false);
		ui.checkBox->setEnabled(false);
	}
	else
	{
		ui.checkBox->setChecked(m_pParameters->DataNeedFlip());
		ui.checkBox->setEnabled(true);
	}

	m_pParameters->SetDataType(nFormateType);

	refreshPreview();
}

void CXDlgSEGYDataFormat::acceptAll()
{
	m_bOKForAll = true;

	accept();
}