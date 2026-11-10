#ifndef __RLLINEARITYMAP_H__
#define __RLLINEARITYMAP_H__

#include "xbasic_global.h"


class XBASIC_EXPORT CXLinearityMap
{
public:
	CXLinearityMap( double dInputMin,double dInputMax,double dOutputMin,double dOutputMax,double dInputInvalidValue = -99999999,double dOutputInvalidValue = -99999999);
	double GetOutputValue( double dInputValue );
	double GetInputValue( double dOutPutValue );
private:
  double m_k;
  double m_b;
  double m_xInvalidValue;
  double m_yInvalidValue;
  double m_X1;
  double m_Y1;
};

#endif // __RLLINEARITYMAP_H__
