#include "x2daxishelper.h"
#include <QFontMetricsF>
#include "xmathmacro.h"
#include <qlist.h>

CX2DAxisHelper::CX2DAxisHelper(double dDataStart, double dDataEnd, double dStep, bool bVertical, const vector<int>& vecKeyIndex)
	:m_dDataStart(dDataStart), m_dDataEnd(dDataEnd), m_dDataStep(dStep), m_bVertical(bVertical)
{
	m_nPoint = static_cast<int>((dDataEnd - dDataStart) / dStep + 0.01) + 1;
	m_vecKeyIndex = QVector<int>::fromStdVector(vecKeyIndex);

	m_pLinearMap = NULL;

	m_dLeft = std::numeric_limits<double>::max();
	m_dTop = std::numeric_limits<double>::max();
}

CX2DAxisHelper::~CX2DAxisHelper()
{
	if (m_pLinearMap)
	{
		delete m_pLinearMap;
	}
}

bool CX2DAxisHelper::IsKeyPoint(int index)
{
	return m_vecKeyIndex.contains(index);
}

void CX2DAxisHelper::SetFontandRect(const QFont& font, const QRectF& rect, double dLeft, double dTop, const vector<double>& vecValue)
{
	// do not need change
	if (m_font == font &&
		m_dLeft == dLeft &&
		m_dTop == dTop &&
		m_rect.width() == rect.width())
	{
		if (m_rect != rect)
		{
			if (m_pLinearMap)
				delete m_pLinearMap;

			m_rect = rect;

			if (m_bVertical)
			{
				m_pLinearMap = new CXLinearMap<double>(m_dDataStart, m_dDataEnd, m_rect.top() + m_dTop, m_rect.bottom() + m_dTop);
			}
			else
			{
				m_pLinearMap = new CXLinearMap<double>(m_dDataStart, m_dDataEnd, m_rect.left() + m_dLeft, m_rect.right() + m_dLeft);
			}
		}

		return;
	}

	if (m_pLinearMap)
		delete m_pLinearMap;

	m_font = font;
	m_rect = rect;
	m_dLeft = dLeft;
	m_dTop = dTop;
	m_vecValue = vecValue;

	if (m_bVertical)
	{
		m_pLinearMap = new CXLinearMap<double>(m_dDataStart, m_dDataEnd, m_rect.top() + m_dTop, m_rect.bottom() + m_dTop);
	}
	else
	{
		m_pLinearMap = new CXLinearMap<double>(m_dDataStart, m_dDataEnd, m_rect.left() + m_dLeft, m_rect.right() + m_dLeft);
	}

	_CalcTicks();
	_AddConstraint();
	
}

double CX2DAxisHelper::GetPositionFromData(double dData)
{
	return m_pLinearMap->GetYFromX(dData);
}

double CX2DAxisHelper::GetDataFromPositon(double dPosition)
{
	return m_pLinearMap->GetXFromY(dPosition);
}

bool CX2DAxisHelper::IsMainTick(double dValue)
{
	if (m_vecOut.empty())
	{
		double dTmp = dValue / m_dMainTickStep;
		int nTmp = static_cast<int>(dTmp + M_FEPS);
		if (qAbs(dTmp - (double)nTmp) < M_FEPS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		int index = static_cast<int>((dValue - m_dDataStart) / m_dDataStep + 0.01);
		if (index < 0 || index > m_nPoint - 1)
			return false;
		else
			return m_vecOut[index] == 2;
	}
}

bool CX2DAxisHelper::IsMinorTick(double dValue)
{
	if (m_vecOut.empty())
	{
		double dTmp = dValue / (m_dMainTickStep / (m_nMinorTickNum + 1));
		int nTmp = static_cast<int>(dTmp + M_FEPS * 10);
		if (qAbs(dTmp - (double)nTmp) < M_FEPS * 10)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		int index = static_cast<int>((dValue - m_dDataStart) / m_dDataStep + 0.01);
		if (index < 0 || index > m_nPoint - 1)
			return false;
		else
			return m_vecOut[index] == 1;

	}
}

bool CX2DAxisHelper::_IsMainTick(double dValue)
{
	double dTmp = dValue / m_dMainTickStep;
	int nTmp = static_cast<int>(dTmp + M_FEPS);
	if (qAbs(dTmp - (double)nTmp) < M_FEPS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CX2DAxisHelper::_IsMinorTick(double dValue)
{
	double dTmp = dValue / (m_dMainTickStep / (m_nMinorTickNum + 1));
	int nTmp = static_cast<int>(dTmp + M_FEPS * 10);
	if (qAbs(dTmp - (double)nTmp) < M_FEPS * 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CX2DAxisHelper::_AddConstraint()
{
	if (m_vecKeyIndex.empty())
		return;
	
	// set each point status
	m_vecOut.resize(m_nPoint);
	for (int i = 0; i < m_nPoint; ++i)
	{
		double dValue = m_dDataStart + i * m_dDataStep;
		if (_IsMainTick(dValue))
			m_vecOut[i] = 2;
		else if (_IsMinorTick(dValue))
			m_vecOut[i] = 1;
		else
			m_vecOut[i] = 0;
	}

	// modify key point status, key point -> main tick
	int iPos, iLeft, iRight;
	for (int i = 0; i < m_vecKeyIndex.size(); ++i)
	{
		iPos = m_vecKeyIndex[i];
		if (m_vecOut[iPos] == 2)
			
			continue;

		else if (m_vecOut[iPos] == 1)
		{
			// tell wether either next left main tick or right main tick lies on the key point or not
			iLeft = iPos - 1;
			while (iLeft >= 0 && m_vecOut[iLeft] != 2)
				--iLeft;

			if (iLeft >= 0)
			{
				if (m_vecKeyIndex.contains(iLeft))
					continue;
				else // normal main tick：iLeft
				{
					iRight = iPos + 1;
					while (iRight <= m_nPoint - 1 && m_vecOut[iRight] != 2)
						++iRight;

					if (iRight <= m_nPoint - 1)
					{
						if (m_vecKeyIndex.contains(iRight))
							;
						else
						{
							m_vecOut[iPos] = 2;
							m_vecOut[iLeft] = 1;
							m_vecOut[iRight] = 1;
						}
					}
					else // iRight == -1, no main tick at the right
					{
						//continue;
					}
				}
			}
			else // iLeft == -1
			{
				iRight = iPos + 1;
				while (iRight <= m_nPoint - 1 && m_vecOut[iRight] != 2)
					++iRight;

				if (iRight <= m_nPoint - 1)
				{
					if (m_vecKeyIndex.contains(iRight))
						;
					else
					{
						m_vecOut[iPos] = 2;
						m_vecOut[iRight] = 1;
					}
				}
				else // iRight == -1, no main tick at the right
				{
					//continue;
				}
			}
		}
		else // (m_vecOut[iPos] == 0)
		{
			// tell wether either next left main tick or right main tick lies on the key point or not
			iLeft = iPos - 1;
			while (iLeft >= 0 && m_vecOut[iLeft] != 2)
				--iLeft;

			if (iLeft >= 0)
			{
				if (m_vecKeyIndex.contains(iLeft))
					;
				else // normal main tick：iLeft
				{
					iRight = iPos + 1;
					while (iRight <= m_nPoint - 1 && m_vecOut[iRight] != 2)
						++iRight;

					if (iRight <= m_nPoint - 1)
					{
						if (m_vecKeyIndex.contains(iRight))
							;
						else
						{
							m_vecOut[iPos] = 2;
							m_vecOut[iLeft] = 1;
							m_vecOut[iRight] = 1;
						}
					}
					else // iRight == -1, no main tick at the right
					{
						m_vecOut[iPos] = 2;
						m_vecOut[iLeft] = 1;
					}
				}
			}
			else // iLeft == -1
			{
				iRight = iPos + 1;
				while (iRight <= m_nPoint - 1 && m_vecOut[iRight] != 2)
					++iRight;

				if (iRight <= m_nPoint - 1)
				{
					if (m_vecKeyIndex.contains(iRight))
						;
					else
					{
						m_vecOut[iPos] = 2;
						m_vecOut[iRight] = 1;
					}
				}
				else // iRight == -1, no main tick at the right
				{
					//continue;
				}
			}

		}
	}
}


int CX2DAxisHelper::_GetValidDecimalNum(double dData)
{
	if (static_cast<int>(dData)*1. == dData)
		return 0;

	int nPrecision = 0;
	QString str = QString::number(dData + M_FEPS, 'f');

	for (int i = str.size() - 1; i >= 0; --i)
	{
		if (str.at(i) == '0')
			continue;

		if (str.at(i) == '.')
			break;

		++nPrecision;
	}
	return nPrecision;
}

void CX2DAxisHelper::_CalcTicks()
{
	m_nPrecision = 0;
	for (auto dValue : m_vecValue)
	{
		m_nPrecision = qMax(m_nPrecision, _GetValidDecimalNum(dValue));
	}

	double dMaxTextSize = 0;
	QFontMetricsF fontMetrics(m_font);
	for (auto dValue : m_vecValue)
	{
		QString str = QString::number(dValue, 'f', m_nPrecision);

		if (m_bVertical)
			dMaxTextSize = qMax(dMaxTextSize, fontMetrics.tightBoundingRect(str).height());
		else
			dMaxTextSize = qMax(dMaxTextSize, fontMetrics.tightBoundingRect(str).width());
	}


	m_dMainTickStep = _GetMainStep(dMaxTextSize);
	m_nMinorTickNum = _GetMinorTickNum(m_dMainTickStep);
}

int CX2DAxisHelper::_GetMinorTickNum(double dStep)
{
	vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(4);
	vec.push_back(9);

	double dSignificant = _GetSignificant(dStep);
	int nStep = static_cast<int>(dSignificant);
	int nTickNum = 0;

	if (nStep == 1)
	{
		nTickNum = 4;
	}
	else
	{
		for (int i = vec.size() - 1; i >= 0; --i)
		{
			nTickNum = vec[i];
			if (nStep % (nTickNum + 1) == 0)
				break;
		}
	}

	return nTickNum;
}

double CX2DAxisHelper::_GetSignificant(double dStep)
{
	dStep = qAbs(dStep);

	if (dStep < M_DEPS)
		return 0.;

	while (dStep >= 10.)
		dStep /= 10.;

	while (dStep < 1.)
		dStep *= 10.;

	return dStep;
}

double CX2DAxisHelper::_GetMainStep(double dMaxTxtLength)
{
	if (!m_rect.isValid())
	{
		return 0.;
	}

	if (qAbs(m_dDataEnd - m_dDataStart) < M_DEPS)
	{
		return 0.;
	}

	if (dMaxTxtLength <= 0)
	{
		return 0.0;
	}
	if (m_bVertical)
	{
		double dStrCount = m_rect.height()*1.0 / (dMaxTxtLength + 8.);
		dStrCount = qMin(m_rect.height()*1.0 / 20, dStrCount);

		return _GetProperStep(qAbs(m_dDataEnd - m_dDataStart) / dStrCount);
	}
	else
	{
		double dStrCount = m_rect.width()*1.0 / (dMaxTxtLength + 8);
		dStrCount = qMin(m_rect.width()*1.0 / 20, dStrCount);

		return _GetProperStep(qAbs(m_dDataEnd - m_dDataStart) / dStrCount);
	}
}

double CX2DAxisHelper::_GetProperStep(double dStep)
{
	// if dValue == 0.0, return invalid data 9999.0
	if (qAbs(dStep) <= M_DEPS)
	{
		return 9999.0;
	}

	// get step list
	vector<double> vecResult;
	vecResult.push_back(1.0);
	vecResult.push_back(2.0);
	vecResult.push_back(5.0);
	vecResult.push_back(10.0);

	// calculate step, e.g. 56.0 = 5.6*10, dFactor = 5.6, dMultiple = 10
	double dFactor = qAbs(dStep);
	double dMultiple = 1.0;
	while (dFactor > 10.0 || dFactor < 1.0)
	{
		if (dFactor > 10.0 + M_DEPS)
		{
			dFactor /= 10.0;
			dMultiple *= 10.0;
		}
		else
		{
			dFactor *= 10.0;
			dMultiple /= 10.0;
		}
	}

	// find proper step
	double dTempStep = 0.;
	double dFrontStep = vecResult.front();
	double dBackStep = vecResult.back();

	if (dFactor <= dFrontStep)
	{
		dTempStep = dFrontStep;
	}
	else if (dFactor >= dBackStep)
	{
		dTempStep = dBackStep;
	}
	else
	{
		for (int i = 0; i<vecResult.size() - 1; i++)
		{
			if (dFactor >= vecResult[i] && dFactor < vecResult[i + 1])
			{
				dTempStep = vecResult[i + 1];
				break;
			}
		}
	}

	return dTempStep*dMultiple;
}

