#include "xstatistic.h"
#include <algorithm>

void XStatistic::Append(double v)
{
    ++m_count;
    m_min = std::min(m_min, v);
    m_max = std::max(m_max, v);
    m_sum += v;
    m_sum2 += v * v;
}

double XStatistic::Mean() const
{
    if (m_count > 0)
        return m_sum / m_count;
    else
        return std::numeric_limits<double>::quiet_NaN();
}

double XStatistic::SSerror() const
{
	if (m_count > 0)
		return m_sum2 - (m_sum * m_sum) / m_count;
	else
		return std::numeric_limits<double>::quiet_NaN();
}

double XStatistic::StdDev() const
{
	if (m_count > 0)
		return std::sqrt(SSerror() / (m_count - 1));
	else
		return std::numeric_limits<double>::quiet_NaN();
}
