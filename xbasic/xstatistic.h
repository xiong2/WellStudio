#pragma once
#include "xbasic_global.h"
#include <limits>

class XBASIC_EXPORT XStatistic
{
public:
	void Append(double v);
	double Mean() const;
	double SSerror() const;
	double StdDev() const;

private:
	int m_count = 0;
	double m_min = std::numeric_limits<double>::max();
	double m_max = std::numeric_limits<double>::min();
	double m_sum = 0.0;
	double m_sum2 = 0.0;
};