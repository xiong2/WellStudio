#include "xspinboxex.h"

void CXDoubleSpinBoxEx::Init(double dStart, double dEnd, double dStep, int nCount)
{
	setRange(0, nCount - 1);
	m_dStep = dStart <= dEnd ? dStep : -dStep;
	m_dStart = dStart;
	m_dEnd = dEnd;
}

double CXDoubleSpinBoxEx::GetCurValue() const
{
	return m_dStart + value() * m_dStep;
}

void CXDoubleSpinBoxEx::SetValue(double dValue)
{
	setValue((qBound(qMin(m_dStart, m_dEnd), dValue, qMax(m_dStart, m_dEnd)) - m_dStart) / m_dStep);
}

QString CXDoubleSpinBoxEx::textFromValue(double dValue) const
{
	return QString::number(m_dStart + dValue * m_dStep);
}

void CXSpinBoxEx::Init(int iStart, int iEnd, int iStep, int nCount)
{
	setRange(0, nCount - 1);
	m_iStep = iStart <= iEnd ? iStep : -iStep;
	m_iStart = iStart;
	m_iEnd = iEnd;
}

int CXSpinBoxEx::GetCurValue() const
{
	return m_iStart + value() * m_iStep;
}

void CXSpinBoxEx::SetValue(int value)
{
	setValue((qBound(qMin(m_iStart, m_iEnd), value, qMax(m_iStart, m_iEnd)) - m_iStart) / m_iStep);
}

QString CXSpinBoxEx::textFromValue(int value) const
{
	return QString::number(m_iStart + value * m_iStep);
}
