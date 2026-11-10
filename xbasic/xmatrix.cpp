#include "xmatrix.h"
#include "xmathmacro.h"
#include <algorithm>
#include <numeric>

XMatrix::XMatrix(int rows, int cols, double init)
    : m_rows(rows), m_cols(cols)
{
    m_v.resize(rows * cols);
    std::fill(m_v.begin(), m_v.end(), init);
}

void XMatrix::Resize(int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;

    m_v.resize(m_rows * m_cols);
}

void XMatrix::Fill(double v)
{
    std::fill(m_v.begin(), m_v.end(), v);
}

void XMatrix::Set(int row, int col, double v)
{
    m_v[row * m_cols + col] = v;
}

void XMatrix::Set(std::initializer_list<double>&& lst)
{
    assert(lst.size() == m_v.size());
    m_v.assign(lst);
}

void XMatrix::Set(const std::vector<double>& vec)
{
	assert(vec.size() == m_v.size());
	std::copy(vec.begin(), vec.end(), m_v.begin());
}

void XMatrix::Scale(double factor)
{
	for (auto& v : m_v)
	{
		v *= factor;
	}
}

double XMatrix::Get(int row, int col) const
{
    return m_v.at(row * m_cols + col);
}

double XMatrix::Get(int idx) const
{
	return m_v.at(idx);
}

int XMatrix::Rows() const
{
	return m_rows;
}

int XMatrix::Cols() const
{
	return m_cols;
}

double* XMatrix::Array()
{
	return &m_v[0];
}

XMatrix XMatrix::T() const
{
    XMatrix mt(m_cols, m_rows);

    for (int r = 0; r != m_rows; ++r)
        for (int c = 0; c != m_cols; ++c)
            mt.Set(c, r, Get(r, c));

    return mt;
}

XMatrix XMatrix::Inv() const
{
    assert(m_rows == m_cols);

    int n = m_rows;
    int m = n * 2;

    XMatrix ret(n, n);

    XMatrix a(n, m);
    for (int i = 0; i < n; ++i)
    {
        a.Set(i, n + i, 1.0);
        for (int j = 0; j < n; ++j)
        {
            a.Set(i, j, Get(i, j));
        }
    }

    std::vector<int> ord(n);
    std::iota(ord.begin(), ord.end(), 0);

	for (int p = 0; p < n; ++p)
	{
		int prow = GaussPivot(a, p, &ord);
		double pVal = fabs(a.Get(prow, p));
		if (pVal <= M_ZERO_TEST)
			return *this;

		for (int i = p; i < m; ++i)
		{
			a.Set(prow, i, a.Get(prow, i) / pVal);
		}

		for (int i = 0; i < n; ++i)
		{
			if (i == p) continue;

			int ii = ord.at(i);
			double r = a.Get(ii, p) / a.Get(prow, p);
			for (int j = p; j < m; ++j)
				a.Set(ii, j, a.Get(ii, j) - r * a.Get(prow, j));
		}
	}

	// Set up the result matrix
	for (int i = 0; i < n; ++i)
	{
		int ii = ord.at(i);
		for (int j = 0; j < n; ++j)
		{
			ret.Set(i, j, a.Get(ii, n + j));
		}
	}

    return ret;
}

void XMatrix::SmoothSavitzkyGolay(int order)
{
    if (m_rows != m_cols || m_rows <= 1)
    {
        assert(!"This algorithm cannot be used on 2D matrix.");
        return;
    }

    order = std::min(order, m_rows - 1);

    // Make sure the window size is odd
    int wSize = m_rows;
    if (wSize % 2 == 0)
    {
        ++wSize;
        Resize(wSize, wSize);
    }
    int wHalfSize = wSize / 2;

    // Calculate the # columns
    int k = 0;
    for (int i = 0; i <= order; ++i)
        for (int j = 0; j <= order - i; ++j)
            ++k;

    XMatrix X(wSize * wSize, k);

    // Set up the source matrix a
    int l = 0;
    for (int y = -wHalfSize; y <= wHalfSize; ++y)
    {
        for (int x = -wHalfSize; x <= wHalfSize; ++x)
        {
            k = 0;
            for (int j = 0; j <= order; ++j)
            {
                for (int i = 0; i <= order - j; ++i)
                {
                    X.Set(l, k++, std::pow(x, i) * std::pow(y, j));
                }
            }
            ++l;
        }
    }

    XMatrix Xt = X.T();
    XMatrix b  = Xt * X;
    XMatrix c  = b.Inv();
    XMatrix C  = c * Xt;

    k = 0;
    for (int j = 0; j < wSize; j++)
    {
        for (int i = 0; i < wSize; i++)
        {
            Set(j, i, C.Get(0, k));
            k++;
        }
    }
}

bool XMatrix::Gauss(const XMatrix& am, const XMatrix& ym, XMatrix* sol, double zeroTest)
{
	int n = am.m_rows;
	int m = n + 1;

	assert(am.m_rows == am.m_cols);
	assert(ym.m_cols == 1);
	assert(ym.m_rows == am.m_rows);
	assert(sol->m_cols == 1);
	assert(sol->m_rows == am.m_rows);

	// Set up the work matrix, it has one extra column with the RHS in it.
	XMatrix a(n, m); // work matrix n, n+1
	for (int i = 0; i < n; ++i)
	{
		a.Set(i, n, ym.Get(i, 0));
		for (int j = 0; j < n; ++j)
		{
			a.Set(i, j, am.Get(i, j));
		}
	}

	// Init the order column vector
	std::vector<int> ord(n);
	std::iota(ord.begin(), ord.end(), 0);

	for (int p = 0; p < n; ++p)
	{
		// Get the pivot row
		int prow = GaussPivot(a, p, &ord);
		// Divide pivot row by the pivot cell
		double pVal = std::fabs(a.Get(prow, p));
		// Check for singular matrix (zero divide)
		if (pVal <= zeroTest)
			return false;

		for (int i = p; i < m; ++i)
			a.Set(prow, i, a.Get(prow, i) / pVal);

		// Elimate the variables
		for (int i = p + 1; i < n; ++i)
		{
			int ii = ord[i];
			double r = a.Get(ii, p) / a.Get(prow, p);
			for (int j = p; j < m; ++j)
				a.Set(ii, j, a.Get(ii, j) - r * a.Get(prow, j));
		}
	}

	// Back substitution
	sol->Set(n - 1, 0, a.Get(ord[n - 1], m - 1) / a.Get(ord[n - 1], n - 1));
	for (int i = n - 2; i >= 0; --i)
	{
		int ii = ord[i];
		double sum = 0.0;
		for (int j = i + 1; j < n; ++j)
			sum += a.Get(ii, j) * sol->Get(j, 0);
		sol->Set(i, 0, (a.Get(ii, m - 1) - sum) / a.Get(ii, i));
	}

	return true;
}

int XMatrix::GaussPivot(const XMatrix& m, int p, std::vector<int>* ord)
{
	int row = p;
	for (int i = p + 1; i < m.m_rows; ++i)
	{
		if (fabs(m.Get(ord->at(i), p)) > fabs(m.Get(ord->at(row), p)))
			row = i;
	}

	if (row != p)
		std::swap((*ord)[p], (*ord)[row]);

	return ord->at(p);
}

bool operator==(const XMatrix& lhs, const XMatrix& rhs)
{
    return lhs.m_rows == rhs.m_rows && lhs.m_cols == rhs.m_cols && lhs.m_v == rhs.m_v;
}

XMatrix operator*(const XMatrix& lhs, const XMatrix& rhs)
{
    assert(lhs.m_cols == rhs.m_rows);

    XMatrix ret(lhs.m_rows, rhs.m_cols);

    for (int i = 0; i < lhs.m_rows; ++i)
        for (int j = 0; j < rhs.m_cols; ++j)
            for (int k = 0; k < lhs.m_cols; ++k)
                ret.Set(i, j, ret.Get(i, j) + lhs.Get(i, k) * rhs.Get(k, j));

    return ret;
}
