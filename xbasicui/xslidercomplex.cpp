#include "xslidercomplex.h"
#include "xglobal.h"
#include <QMessageBox>

CXSliderComplex::CXSliderComplex(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	m_ui.m_pSlider->setHandleMovementMode(CXSlider::NoOverlapping);

	connect(m_ui.m_pLineEdtMin, SIGNAL(editingFinished()), this, SLOT(slotChangeMin()));
	connect(m_ui.m_pLineEdtMax, SIGNAL(editingFinished()), this, SLOT(slotChangeMax()));

	connect(m_ui.m_pSlider, SIGNAL(minValueChanged(int)), this, SLOT(slotMinValueChanged(int)));
	connect(m_ui.m_pSlider, SIGNAL(maxValueChanged(int)), this, SLOT(slotMaxValueChanged(int)));

    connect(m_ui.m_pSlider, SIGNAL(sliderReleased()), this, SIGNAL(SliderReleased()));
}

CXSliderComplex::~CXSliderComplex()
{

}

void CXSliderComplex::SetSliderName(const QString& strName)
{
	m_ui.m_pSliderName->setText(strName);
}

void CXSliderComplex::SetRangeAndPrecision(double dMin, double dMax, double dStep, int nPrecision)
{
	m_nPrecision = nPrecision;

	m_dDataMin = dMin;
	m_dDataMax = dMax;
	m_dStep = dStep;

	m_nTotalNum = static_cast<int>((dMax - dMin) / dStep + 0.01) + 1;

	// set range
	m_ui.m_pSlider->setRange(0, m_nTotalNum - 1);
	m_ui.m_pSlider->SetRange(0, m_nTotalNum-1);
	//m_ui.m_pSlider->setMinValue(1);
	//m_ui.m_pSlider->setMaxValue(m_nTotalNum);

	m_ui.m_pLineEdtMin->setText(QString::number(m_dDataMin, 'f', m_nPrecision));
	m_ui.m_pLineEdtMax->setText(QString::number(m_dDataMax, 'f', m_nPrecision));
}

void CXSliderComplex::slotChangeMin()
{
	bool b;
	double dValue = m_ui.m_pLineEdtMin->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, ::g_strProductName, "Please enter a valid number.");
		m_ui.m_pLineEdtMin->undo();
		m_ui.m_pLineEdtMin->setFocus();
	}
	if (dValue > GetMaxValue())
	{
		QMessageBox::warning(0, ::g_strProductName, "The minimum value cannot be greater than the maximum value.");
		m_ui.m_pLineEdtMin->undo();
		m_ui.m_pLineEdtMin->setFocus();
		return;
	}

	int index = static_cast<int>((dValue - m_dDataMin) / m_dStep + 0.01);
	index = qBound(0, index, m_nTotalNum-1);

	dValue = m_dDataMin + index*m_dStep;
	m_ui.m_pLineEdtMin->setText(QString::number(dValue, 'f', m_nPrecision));

	m_ui.m_pSlider->setMinValue(index);
}

void CXSliderComplex::slotChangeMax()
{
	bool b;
	double dValue = m_ui.m_pLineEdtMax->text().toDouble(&b);
	if (!b)
	{
		QMessageBox::warning(0, ::g_strProductName, "Please enter a valid number.");
		m_ui.m_pLineEdtMax->undo();
		m_ui.m_pLineEdtMax->setFocus();
	}
	if (dValue < GetMinValue())
	{
		QMessageBox::warning(0, ::g_strProductName, "The maximum value cannot be less than the minimum value.");
		m_ui.m_pLineEdtMax->undo();
		m_ui.m_pLineEdtMax->setFocus();
		return;
	}

	int index = static_cast<int>((dValue - m_dDataMin) / m_dStep + 0.01);
	index = qBound(0, index, m_nTotalNum-1);

	dValue = m_dDataMin + index*m_dStep;
	m_ui.m_pLineEdtMax->setText(QString::number(dValue, 'f', m_nPrecision));

	m_ui.m_pSlider->setMaxValue(index);
}

void CXSliderComplex::slotMinValueChanged(int nMinValue)
{
	double dValue = m_dDataMin + nMinValue*m_dStep;
	m_ui.m_pLineEdtMin->setText(QString::number(dValue, 'f', m_nPrecision));
}

void CXSliderComplex::slotMaxValueChanged(int nMaxValue)
{
	double dValue = m_dDataMin + nMaxValue*m_dStep;
	m_ui.m_pLineEdtMax->setText(QString::number(dValue, 'f', m_nPrecision));
}

double CXSliderComplex::GetMinValue()
{
	return m_ui.m_pSlider->minValue()*m_dStep + m_dDataMin;
}

double CXSliderComplex::GetMaxValue()
{
	return m_ui.m_pSlider->maxValue()*m_dStep + m_dDataMin;
}

void CXSliderComplex::SetMinPosition(double dMin)
{
	m_ui.m_pSlider->setMinPosition(qRound((dMin - m_dDataMin) / m_dStep));
}

void CXSliderComplex::SetMaxPosition(double dMax)
{
	m_ui.m_pSlider->setMaxPosition(qRound((dMax - m_dDataMin) / m_dStep));
}

void CXSliderComplex::SetNameVisible(bool bVisible)
{
	m_ui.m_pSliderName->setVisible(bVisible);
}
