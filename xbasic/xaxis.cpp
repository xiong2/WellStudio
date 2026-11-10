#include "xaxis.h"
#include <math.h>
#include <float.h>
#include <sstream>
#include <iomanip>

CXAxis::CXAxis(double dBegin, double dEnd, const QRect& sceneRect, int nStepUnit)

{	
	m_eType = YAxis;
	m_dBegin = dBegin;
	m_dEnd = dEnd;
	m_sceneRect = sceneRect;
	m_nStepUnit = nStepUnit;
	m_dGroundTickInterval = 0.0f;
	m_bGroundChanged = false;
}

CXAxis::~CXAxis()
{
}
double CXAxis::GetBaseNum(double dValue, double dBase)
{
	if (dValue == 0.0)
	{
		return 0;
	}
	else if (dValue < 0.0)
	{
		return GetBaseNum(-1*dValue, dBase);
	}


	double dResult = dValue / dBase;

	while (dResult > 10.00000 || dResult < 1.00000)
	{
		if (dResult > 10.0000000001)
			dBase *= 10;
		else if (dResult < 0.9999999999)
			dBase *= 0.1;
		else
			break;

		dResult = dValue / dBase;
	}

	if (fabs(dResult-10.0) < 0.0001)
	{
		return dBase*10.0;
	}
	else if (dResult >= 1.0 && dResult < 10.0)
	{
		return dBase;
	}

	return dResult;
}

 double CXAxis::_Round(double dValue, double dInterval)
{
	if (fabs(dInterval) < FLT_EPSILON)
		return 0;

	double dTemp = (dValue > 0) ? floor(dValue/dInterval + 0.5) : ceil(dValue/dInterval - 0.5);
	double dResult = dTemp*dInterval;

	return dResult;
}

 double CXAxis::_Round(double dValue, int nPrecision)
{
	std::stringstream stream;

	stream << std::setprecision(nPrecision) << std::setiosflags(std::ios_base::fixed) << dValue;
	stream >> dValue;

	return dValue;
}




int CXAxis::GetTickCount()
{ 
	if (fabs(m_dGroundTickInterval) < FLT_EPSILON)
		return 0;
	double dGroundRange = fabs(m_dEnd - m_dBegin);
	return dGroundRange/m_dGroundTickInterval;
}
double CXAxis::GetGroundTickInterval()
{
	return m_dGroundTickInterval;
}
double CXAxis::calculatorGroundTickInterval()
{
	double dGroundRange = fabs(m_dEnd - m_dBegin);
	if (fabs(dGroundRange) < FLT_EPSILON)
		return 0.0 ;

	double dBaseNum = GetBaseNum(dGroundRange, m_nStepUnit);
	double dBaseValue = dGroundRange/dBaseNum;
	int nRange = m_sceneRect.height();
	if (m_eType == XAxis)
	{
		nRange = m_sceneRect.width();
	}
	while (nRange / dBaseValue > (m_eType == XAxis ? 2*m_nMinTickInterval : m_nMinTickInterval))	// solving the congestion of x axis.
	{
		dBaseNum /= m_nStepUnit;
		dBaseValue = dGroundRange / dBaseNum;
	}
	dBaseNum *= m_nStepUnit;
	m_dGroundTickInterval = dBaseNum;	
	return m_dGroundTickInterval;

}

// algorithm
// we can use another calculation function, nRange/m_nMinTickInterval
int CXAxis::GetSceneTickInterval()
{
	int dTickCount = GetTickCount();
	if (dTickCount == 0)
		return 0;

	int nRange = m_sceneRect.height();
	if (m_eType == XAxis)
	{
		nRange = m_sceneRect.width();
	}
	double dInterval = nRange / dTickCount;
	return dInterval;
}

double CXAxis::GetGroundGradValue(int nIndex)
{
	if (fabs(m_dGroundTickInterval) < FLT_EPSILON)
		return 0;

	double dBegin = _Round(m_dBegin, m_dGroundTickInterval);

	double dValue = dBegin + nIndex * m_dGroundTickInterval;

	return dValue;
}

int CXAxis::MapGroundToScene(double dGroundValue,bool bReverse)
{
	double dRange = fabs(m_dEnd - m_dBegin);
	if (fabs(dRange) < FLT_EPSILON)
		return m_sceneRect.top();

	double dPercent =(dGroundValue-m_dBegin)/dRange;
	if (bReverse)
	{
		dPercent = 1.0- dPercent;
	}
	if (m_eType == XAxis)
	{
		return m_sceneRect.left()+m_sceneRect.width()*dPercent;
	}else
	{
		return m_sceneRect.top()+m_sceneRect.height()*dPercent;
	}
	
}

double CXAxis::MapSceneToGround(int nValue,bool bReverse)
{
	int nRange = m_sceneRect.height();
	if (m_eType == XAxis)
	{
		nRange = m_sceneRect.width();
	}
	if (nRange <= 0)
		return 0;
    double dPercent;
	if (m_eType == XAxis)
	{
		dPercent = (nValue-m_sceneRect.left())*1.0/nRange;
	}
	else
	{
		dPercent = (nValue-m_sceneRect.top())*1.0/nRange;
	}
	if (bReverse)
	{
		dPercent = 1.0- dPercent;
	}
	return m_dBegin+(m_dEnd - m_dBegin)*dPercent;
}

bool CXAxis::IsMainTick(double dGroundValue)
{   
	double dRound = _Round(dGroundValue, m_dGroundTickInterval*10);
	if (fabs(dGroundValue-dRound) < FLT_EPSILON)
		return true;

	return false;
}

void CXAxis::SychonizePosition(const CXAxis* pRuler)
{
	m_dBegin = pRuler->GetBegin();
	m_dEnd = pRuler->GetEnd();
	m_bGroundChanged = true;
}

void CXAxis::SychonizeScale(const CXAxis* pRuler)
{
	// scale is value range divided by height and height is identical
	double dRange = pRuler->GetValueRange();
	Zoom(dRange);
}

void CXAxis::Zoom(double dValueRange)
{
	if (dValueRange > 0)
	{
		double dMidPos = 0.5*(m_dEnd + m_dBegin);

		m_dBegin = dMidPos - 0.5*dValueRange;
		m_dEnd = dMidPos + 0.5*dValueRange;
		m_bGroundChanged = true;
	}
}




