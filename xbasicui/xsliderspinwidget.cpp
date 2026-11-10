#include <QLabel>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include "xsliderspinwidget.h"
#include "xglobal.h"

/*=======================================================================================
class CXFilterEventSlider
=======================================================================================*/

void CXFilterEventSlider::mouseMoveEvent(QMouseEvent * event)
{
	QSlider::mouseMoveEvent(event);
	emit CurrentValueChanged(value());
}

void CXFilterEventSlider::mousePressEvent(QMouseEvent * event)
{
	QSlider::mousePressEvent(event);
}

void CXFilterEventSlider::mouseReleaseEvent(QMouseEvent * event)
{
	QSlider::mouseReleaseEvent(event);

	emit CurrentValueChanged(value());
	emit SliderReleased();
}

/*=======================================================================================
	class CXSliderSpinWidget
=======================================================================================*/

CXSliderSpinWidget::CXSliderSpinWidget(QWidget *parent) : QWidget(parent)
{
	m_pLblString = new QLabel(this);

	m_pSlider = new CXFilterEventSlider(this);
	m_pSlider->setMinimumWidth(200);
	m_pSlider->setOrientation(Qt::Horizontal);

	m_pSpin = new QDoubleSpinBox(this);
	m_pSpin->setMinimumWidth(60);

	QHBoxLayout* pLayout = new QHBoxLayout(this);
	pLayout->setMargin(0);
	pLayout->setSpacing(6);
	setLayout(pLayout);

	pLayout->addWidget(m_pLblString);
	pLayout->addWidget(m_pSlider, 2);
	pLayout->addWidget(m_pSpin);

	_BlockSignals(false);
}

void CXSliderSpinWidget::InitWidget(double dStart, double dEnd, double dStep, int nCount, int nDecimal)
{
	_BlockSignals(true) ;

	m_nDecimal = nDecimal ;

	m_pSlider->Init(dStart, dEnd, dStep, nCount) ;

	if(dStart > dEnd)
	{
		dStep = -dStep ;
	}

	double dTempStart, dTempEnd ;
	dTempStart = qMin(dStart, dEnd) ;
	dTempEnd = qMax(dStart, dEnd) ;

	m_pSpin->setRange(dTempStart, dTempEnd) ;
	m_pSpin->setSingleStep(dStep) ;

	_BlockSignals(false) ;
	connect(m_pSlider, SIGNAL(SliderReleased()), this, SIGNAL(SliderReleased())) ;
	connect(m_pSpin, SIGNAL(editingFinished()), this, SLOT(slotEditingFinished())) ;
}

void CXSliderSpinWidget::_BlockSignals(bool bBlock)
{
	if(bBlock)
	{
		disconnect(m_pSlider, SIGNAL(CurrentValueChanged(int)), this, SLOT(slotSliderValueChanged(int))) ;
		disconnect(m_pSpin, SIGNAL(valueChanged(double)), this, SLOT(slotSpinValueChanged(double))) ;
	}
	else
	{
		connect(m_pSlider, SIGNAL(CurrentValueChanged(int)), this, SLOT(slotSliderValueChanged(int))) ;
		connect(m_pSpin, SIGNAL(valueChanged(double)), this, SLOT(slotSpinValueChanged(double))) ;
	}
}

void CXSliderSpinWidget::slotEditingFinished()
{
	emit EditingFinished() ;
}

double CXSliderSpinWidget::GetValue()
{
	return m_pSpin->value() ;
}

void CXSliderSpinWidget::SetValue(double dValue)
{
	_BlockSignals(true) ;
	
	m_pSlider->SetValue(dValue) ;
	m_pSlider->repaint();
	_SetSpinBoxValue(dValue) ;

	_BlockSignals(false) ;
}

int CXSliderSpinWidget::GetCurrentIndex()
{
	return m_pSlider->value() ;
}

void CXSliderSpinWidget::SetCurrentIndex(int nIndex)
{
	m_pSlider->setValue(nIndex) ;

	_BlockSignals(true) ;

	_SetSpinBoxValue(m_pSlider->GetCurValue()) ;

	_BlockSignals(false) ;
}

int CXSliderSpinWidget::GetRangeMinValue()
{
	return m_pSlider->minimum() ;
}

int CXSliderSpinWidget::GetRangeMaxValue()
{
	return m_pSlider->maximum() ;
}

void CXSliderSpinWidget::SetLabelString(const QString & str)
{
	m_pLblString->setText(str) ;
}

void CXSliderSpinWidget::slotSliderValueChanged(int)
{
	_BlockSignals(true) ;

	double dValue = m_pSlider->GetCurValue() ;
	_SetSpinBoxValue(dValue) ;

	_BlockSignals(false) ;

	emit ValueChanged(dValue) ;
}

void CXSliderSpinWidget::_SetSpinBoxValue(double dValue)
{
	int nRealDecimal = 0 ;
	QString str = vtos(dValue, m_nDecimal, &nRealDecimal);
	m_pSpin->setDecimals(nRealDecimal) ;
	m_pSpin->setValue(str.toDouble()) ;
	m_pSpin->repaint();
}

void CXSliderSpinWidget::slotSpinValueChanged(double dValue)
{
	_BlockSignals(true) ;

	m_pSlider->SetValue(dValue) ;
	double dCorrectValue = m_pSlider->GetCurValue() ;
	_SetSpinBoxValue(dCorrectValue) ;

	_BlockSignals(false) ;

	emit ValueChanged(dCorrectValue) ;
	emit EditingFinished() ;
}

void CXSliderSpinWidget::SetEnabled(bool bEnabled)
{
	m_pSlider->setEnabled(bEnabled) ;
	m_pSpin->setEnabled(bEnabled) ;
}

void CXSliderSpinWidget::HideLabel(bool bHidden)
{
	m_pLblString->setHidden(bHidden) ;
}

void CXSliderSpinWidget::SetSpinSingleStep(double dStep)
{
	m_pSpin->setSingleStep(dStep) ;
}

/*=======================================================================================
		class CXRangeComponent
=======================================================================================*/

CXRangeComponent::CXRangeComponent(QWidget* parent, bool bEmitOnlyReleaseMouse, bool bStartEqualToEnd)
	: QWidget(parent), m_nLockedRangeValue(-1), m_bStartEqualToEnd(bStartEqualToEnd)
	, m_bEmitOnlyReleaseMouse(bEmitOnlyReleaseMouse)
{
	QGridLayout* pLayout = new QGridLayout(this);
	pLayout->setMargin(0);
	pLayout->setSpacing(6);
	setLayout(pLayout);

	m_pStartLabel = new QLabel(this);
	m_pStartWidget = new CXSliderSpinWidget(this);
	m_pStartWidget->HideLabel(true) ;

	m_pEndLabel = new QLabel(this);
	m_pEndWidget = new CXSliderSpinWidget(this);
	m_pEndWidget->HideLabel(true);

	pLayout->addWidget(m_pStartLabel, 0, 0);
	pLayout->addWidget(m_pStartWidget, 0, 1);
	pLayout->addWidget(m_pEndLabel, 1, 0);
	pLayout->addWidget(m_pEndWidget, 1, 1);
}

void CXRangeComponent::ResetRange()
{
	m_pStartWidget->SetCurrentIndex(m_pStartWidget->GetRangeMinValue());
	m_pEndWidget->SetCurrentIndex(m_pStartWidget->GetRangeMaxValue());

	emit ValueChanged(m_pStartWidget->GetValue(), m_pEndWidget->GetValue());
}

void CXRangeComponent::_BlockSignals(bool bBlock)
{
	if (bBlock)
	{
		disconnect(m_pStartWidget, SIGNAL(ValueChanged(double)), this, SLOT(slotStartValueChanged(double)));
		disconnect(m_pEndWidget, SIGNAL(ValueChanged(double)), this, SLOT(slotEndValueChanged(double)));

		disconnect(m_pStartWidget,SIGNAL(SliderReleased()), this,SLOT(slotValueChanged()));
		disconnect(m_pEndWidget,SIGNAL(SliderReleased()), this,SLOT(slotValueChanged()));
	}
	else
	{
		connect(m_pStartWidget, SIGNAL(ValueChanged(double)), this, SLOT(slotStartValueChanged(double)));
		connect(m_pEndWidget, SIGNAL(ValueChanged(double)), this, SLOT(slotEndValueChanged(double)));

		connect(m_pStartWidget,SIGNAL(SliderReleased()), this,SLOT(slotValueChanged()));
		connect(m_pEndWidget,SIGNAL(SliderReleased()), this,SLOT(slotValueChanged()));
	}
}

void CXRangeComponent::InitComponent(double dRangeStart, double dRangeEnd, double dStep, int nCount, double dStartValue, double dEndValue)
{
	int nDecimal = GetSeisUnitDecimalNumber(dStep);
	m_pStartWidget->InitWidget(dRangeStart, dRangeEnd, dStep, nCount, nDecimal);
	m_pEndWidget->InitWidget(dRangeStart, dRangeEnd, dStep, nCount, nDecimal);

	m_pStartWidget->SetValue(dStartValue) ;
	m_pEndWidget->SetValue(dEndValue) ;

	_BlockSignals(false) ;
}

void CXRangeComponent::SetComponentLabel(const QString & strStratLabel, const QString & strEndLabel)
{
	m_pStartLabel->setText(strStratLabel);
	m_pEndLabel->setText(strEndLabel);
}

void CXRangeComponent::SetLockRange(bool bLockRange)
{
	m_bLockRange = bLockRange;
	m_nLockedRangeValue = m_pEndWidget->GetCurrentIndex() - m_pStartWidget->GetCurrentIndex();
}

void CXRangeComponent::slotStartValueChanged(double)
{
	int nStartIndex = m_pStartWidget->GetCurrentIndex();
	int nEndIndex = m_pEndWidget->GetCurrentIndex();

	int nRangeMaxValue = m_pEndWidget->GetRangeMaxValue();

	_BlockSignals(true);

	if (m_bLockRange)
	{
		if (nStartIndex + m_nLockedRangeValue > nRangeMaxValue)
		{
			m_pEndWidget->SetCurrentIndex(nRangeMaxValue);
			m_pStartWidget->SetCurrentIndex(nRangeMaxValue - m_nLockedRangeValue);
		}
		else
		{
			m_pEndWidget->SetCurrentIndex(nStartIndex + m_nLockedRangeValue);
		}
	}
	else
	{
		if (m_bStartEqualToEnd)
		{
			if (nStartIndex > nEndIndex)
			{
				m_pStartWidget->SetCurrentIndex(nEndIndex);
				_BlockSignals(false);
				return ;
			}
		}
		else
		{
			if (nStartIndex >= nEndIndex)
			{
				m_pStartWidget->SetCurrentIndex(nEndIndex - 1);
				_BlockSignals(false) ;
				return ;
			}
		}

		if (nStartIndex >= nEndIndex)
		{
			m_pStartWidget->SetCurrentIndex(nEndIndex - m_bStartEqualToEnd ? 0 : 1);
		}
	}

	_BlockSignals(false);
}

void CXRangeComponent::slotEndValueChanged(double)
{
	int nStartIndex = m_pStartWidget->GetCurrentIndex();
	int nEndIndex = m_pEndWidget->GetCurrentIndex();
	int nRangeMinValue = m_pEndWidget->GetRangeMinValue();

	_BlockSignals(true);

	if (m_bLockRange)
	{
		if (nEndIndex - m_nLockedRangeValue < nRangeMinValue)
		{
			m_pStartWidget->SetCurrentIndex(nRangeMinValue) ;
			m_pEndWidget->SetCurrentIndex(nRangeMinValue + m_nLockedRangeValue) ;
		}
		else
		{
			m_pStartWidget->SetCurrentIndex(nEndIndex - m_nLockedRangeValue) ;
		}
	}
	else
	{
		if (m_bStartEqualToEnd)
		{
			if (nEndIndex < nStartIndex)
			{
				m_pEndWidget->SetCurrentIndex(nStartIndex) ;
				_BlockSignals(false) ;
				return ;
			}
		}
		else
		{
			if (nEndIndex <= nStartIndex)
			{
				m_pEndWidget->SetCurrentIndex(nStartIndex + 1) ;
				_BlockSignals(false) ;
				return ;
			}
		}

		if (nStartIndex >= nEndIndex)
		{
			m_pEndWidget->SetCurrentIndex(nStartIndex + m_bStartEqualToEnd ? 0 : 1);
		}
	}

	_BlockSignals(false) ;
}

void CXRangeComponent::slotValueChanged()
{
	if(m_bEmitOnlyReleaseMouse)
	{
		emit ValueChanged(m_pStartWidget->GetValue(), m_pEndWidget->GetValue());
	}
}