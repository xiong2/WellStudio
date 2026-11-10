#include "xpagehistogram.h"
#include "xobject.h"
#include "xautogrid.h"

CXPageHistogram::CXPageHistogram(QWidget *parent, const CXHistogram& histogram)
	: QWidget(parent), m_histogram(histogram)
{
	m_ui.setupUi(this);
	_Init();
	_InitSlots();
}

CXPageHistogram::~CXPageHistogram()
{

}
void CXPageHistogram::_Init()
{
	m_ui.m_pCbbBinSize->setDisabled(true);

	double dDistance = m_histogram.m_dDataMax - m_histogram.m_dDataMin;
	for (double dSize : CXAutoGrid::AutoInterval(dDistance))
	{
		m_ui.m_pCbbBinSize->addItem(QString::number(dSize));
	}

	m_ui.m_pLblMin->setText(QString::number(m_histogram.m_dDataMin));
	m_ui.m_pLblMax->setText(QString::number(m_histogram.m_dDataMax));

	m_ui.m_pFrameHistogram->SetHistogram(m_histogram);
	m_ui.m_pFrameHistogram->slotSetNum(m_ui.m_pCbbBinNum->currentText());
}

void CXPageHistogram::_InitSlots()
{
	connect(m_ui.m_pCbbBinSize, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), m_ui.m_pFrameHistogram, &CXDrawHistogram::slotSetInterval);
	connect(m_ui.m_pCbbBinNum, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), m_ui.m_pFrameHistogram, &CXDrawHistogram::slotSetNum);
	connect(m_ui.m_pCbbAxisY, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), m_ui.m_pFrameHistogram, &CXDrawHistogram::slotYRepresentationChanged);
	connect(m_ui.m_pRdoBinSize, &QRadioButton::pressed, this, &CXPageHistogram::slotBinChanged);
	connect(m_ui.m_pRdoBinNum, &QRadioButton::pressed, this, &CXPageHistogram::slotBinChanged);
}

void CXPageHistogram::slotBinChanged()
{
	auto pRadioBtn = dynamic_cast<QRadioButton*>(sender());
	if (!pRadioBtn)
		return;

	if (pRadioBtn == m_ui.m_pRdoBinSize)
	{
		m_ui.m_pFrameHistogram->slotSetInterval(m_ui.m_pCbbBinSize->currentText());
	}
	else if (pRadioBtn == m_ui.m_pRdoBinNum)
	{
		m_ui.m_pFrameHistogram->slotSetNum(m_ui.m_pCbbBinNum->currentText());
	}
}