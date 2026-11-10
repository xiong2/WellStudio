#include <qglobal.h>
#include "xlinearitymap.h"
CXLinearityMap::CXLinearityMap(double dInputMin,double dInputMax,double dOutputMin,double dOutputMax,double dInputInvalidValue,double dOutputInvalidValue)
{
	if( qAbs( dInputMin - dInputMax) > 0.0001 )
	{
		m_k = (dOutputMin -dOutputMax)/ ( dInputMin- dInputMax) ;
	}else
	{
		m_k = 0;
	}

	m_b = dOutputMin - m_k * dInputMin;
	m_xInvalidValue = dInputInvalidValue;
    m_yInvalidValue = dOutputInvalidValue;
	m_X1 = dInputMin;
	m_Y1 = dOutputMin;
}

double CXLinearityMap::GetOutputValue( double dInputValue )
{
	if(qAbs(dInputValue - m_xInvalidValue) < 0.001)
	{
		return m_Y1;
	}
	return m_k * dInputValue+ m_b;

}

double CXLinearityMap::GetInputValue( double dOutPutValue )
{
	if(qAbs(dOutPutValue - m_yInvalidValue) < 0.001)
	{
		return m_X1;
	}
	return m_k==0 ? m_b : ( dOutPutValue - m_b )/m_k;
}