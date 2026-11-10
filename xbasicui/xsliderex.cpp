#include "xsliderex.h"

void CXSliderEx::Init(double dStart, double dEnd,double dStep,int nCount)
{
	setRange(0, nCount - 1);
	m_dStep  = dStart <= dEnd ? dStep : -dStep;
	m_dStart = dStart;
	m_dEnd   = dEnd;
}

double CXSliderEx::GetCurValue()
{
	return m_dStart + value() * m_dStep;
}

void CXSliderEx::SetValue(double dValue)
{
	dValue = qMax(dValue, qMin(m_dStart, m_dEnd));
	dValue = qMin(dValue, qMax(m_dStart, m_dEnd));
	setValue(qRound((dValue - m_dStart) / m_dStep));
}