#include "xlsq.h"
#include <algorithm>

XLsq::XLsq(int noVar, int order)
    : m_noVar(noVar), m_order(order), m_n(noVar * order + 1), m_sums(m_n, m_n), m_rhs(m_n, 1), m_sol(m_n, 1)
{
}

XLsq::~XLsq()
{
}

void XLsq::Add(double dVar, const std::vector<double>& vecVars, double weight)
{
    if (weight <= 0.0)
        return;

    std::vector<double> x(m_n, 1.0);

    // Generate all the power term variables
    int k = 1;
    for (int i = 0; i < m_noVar; ++i)
    {
        for (int j = 0; j < m_order; ++j)
        {
            for (int l = 0; l < m_order; ++l)
            {
                if (l <= j)
                {
                    x[k] *= vecVars[i];
                }
            }
            ++k;
        }
    }

    // Set up the RHS
    for (int i = 0; i < m_n; ++i)
    {
        m_rhs.Set(i, 0, m_rhs.Get(i, 0) + dVar * x[i] * weight);
    }

    // Set up the LHS sums
    for (int i = 0; i < m_n; ++i)
    {
        for (int j = 0; j < m_n; ++j)
        {
            m_sums.Set(i, j, m_sums.Get(i, j) + x[j] * x[i] * weight);
        }
    }

    m_sumWeights += weight;
    ++m_count;
}

bool XLsq::Solve()
{
    if (m_count > m_n)
        m_isValid = XMatrix::Gauss(m_sums, m_rhs, &m_sol);
    else
        m_isValid = false;

    return m_isValid;
}

bool XLsq::IsValid() const
{
    return m_isValid;
}

int XLsq::Count() const
{
    return m_count;
}

double XLsq::Eval(const std::vector<double>& vecVars)
{
    double ans = std::numeric_limits<double>::quiet_NaN();

	// Do we have a valid LSQ solution?
	if (!m_isValid)
		return ans;

	std::vector<double> x(m_noVar * m_order + 1, 1);

	int k = 1;
	for (int i = 0; i < m_noVar; ++i)
	{
		for (int j = 0; j < m_order; ++j)
		{
			for (int l = 0; l < m_order; ++l)
			{
				if (l <= j)
					x[k] *= vecVars[i];
			}
			++k;
		}
	}

	ans = 0;
	for (int i = 0; i < m_n; ++i)
		ans += m_sol.Get(i, 0) * x[i];

	return ans;
}

double XLsq::SumWeights() const
{
    return m_sumWeights;
}

const XMatrix& XLsq::Sums() const
{
    return m_sums;
}

const XMatrix& XLsq::Rhs() const
{
    return m_rhs;
}

const XMatrix& XLsq::Solution() const
{
    return m_sol;
}

XLsq3d::XLsq3d(int order)
	: m_lsq(2, order)
{
}

void XLsq3d::Add(double x, double y, double z, double w)
{
	std::vector<double> vecVar{x, y};
	m_lsq.Add(z, vecVar, w);

#ifndef NDEBUG
	m_minX = std::min(m_minX, x);
	m_minY = std::min(m_minY, y);
	m_maxX = std::max(m_maxX, x);
	m_maxY = std::max(m_maxY, y);
#endif
}

bool XLsq3d::Solve()
{
	return m_lsq.Solve();
}

bool XLsq3d::IsValid() const
{
	return m_lsq.IsValid();
}

int XLsq3d::Count() const
{
	return m_lsq.Count();
}

double XLsq3d::XMean()
{
	return m_lsq.Sums().Get(0, 1) / m_lsq.SumWeights();
}

double XLsq3d::YMean()
{
	return m_lsq.Sums().Get(0, 2) / m_lsq.SumWeights();
}

double XLsq3d::ZMean()
{
	return m_lsq.Rhs().Get(0, 0) / m_lsq.SumWeights();
}

double XLsq3d::Eval(double x, double y)
{
	return m_lsq.Eval({x, y});
}
