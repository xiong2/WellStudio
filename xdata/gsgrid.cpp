#include "gsgrid.h"
#include <algorithm>
#include <fstream>
#include "xmathmacro.h"
#include "xmath.h"
#include "xlsq.h"
#include "xglobal.h"
#include "xproject.h"
#include "xbicubic.h"

GSGrid::GSGrid(double left, double bottom, int rows, int cols, double xCellSize, double yCellSize)
	: m_left(left), m_bottom(bottom), m_rows(rows), m_cols(cols), m_xCellSize(xCellSize), m_yCellSize(yCellSize)
{
}

GSGrid::GSGrid(double left, double right, double bottom, double top, int rows, int cols)
	: m_left(left), m_bottom(bottom), m_rows(rows), m_cols(cols)
{
	m_xCellSize = (right - left) / m_cols;
	m_yCellSize = (top - bottom) / m_rows;
}

void GSGrid::Resize(int rows, int cols, double defaultValue)
{
	m_grid.resize(rows * cols, defaultValue);
}

void GSGrid::ChangeCellSize(int rows, int cols)
{
	XMatrix prev(m_rows, m_cols);
    FetchGrid([&](int row, int col) { prev.Set(row, col, GridZ(row, col)); });

    int prevRows = m_rows;
	int prevCols = m_cols;

	m_rows = rows;
	m_cols = cols;

	m_xCellSize = m_xCellSize * prevRows / m_rows;
	m_yCellSize = m_yCellSize * prevCols / m_cols;

	// Update the new starting grid
	for (int row = 0; row < prevRows; ++row)
	{
		for (int col = 0; col < prevCols; ++col)
		{
			std::array<std::array<double, 2>, 2> g;
			g[0][0] = prev.Get(std::max(0, row - 1), std::max(0, col - 1));
			g[0][1] = prev.Get(std::max(0, row - 1), col < prevCols - 1 ? col + 1 : col);
			g[1][0] = prev.Get(row < prevRows - 1 ? row + 1 : prevRows - 1, std::max(0, col - 1));
			g[1][1] = prev.Get(row < prevRows - 1 ? row + 1 : prevRows - 1, col < prevCols - 1 ? col + 1 : col);

			CXBilinear biLinear(g);
            for (int j = 0; j < 3; j++)
            {
                int jj = row * 2 + j;
                if (jj >= m_rows)
                    continue;
                        
				for (int i = 0; i < 3; i++)
                {
                    int ii = col * 2 + i;
                    if (ii >= m_cols)
                        continue;
                    m_grid[jj * m_cols + ii] = biLinear.Eval(i / 2.0, j / 2.0);
                }
            }
			m_grid[row * 2 * m_cols + col * 2] = prev.Get(row, col);
        }
	}
}

int GSGrid::NearestRow(double y) const
{
	return qRound((y - m_bottom) / m_yCellSize);
}

int GSGrid::NearestCol(double x) const
{
	return qRound((x - m_left) / m_xCellSize);
}

void GSGrid::SetGridZ(int row, int col, double v)
{
	if (row < 0 || m_rows <= row || col < 0 || m_cols <= col)
		return;

	m_grid[row * m_cols + col] = v;
}

double GSGrid::GridZ(int row, int col) const
{
	return m_grid[row * m_cols + col];
}

void GSGrid::FetchGrid(const std::function<void(int row, int col)>& functor)
{
	for (int row = 0; row < m_rows; ++row)
		for (int col = 0; col < m_cols; ++col)
			functor(row, col);
}

void GSGrid::FetchGridXY(const std::function<void(double x, double y, int row, int col)>& functor)
{
	for (int row = 0; row < m_rows; ++row)
	{
		double y = GridY(row);

		for (int col = 0; col < m_cols; ++col)
		{
			double x = GridX(col);

			functor(x, y, row, col);
		}
	}
}

int GSGrid::SizeIterationCount(double lastXCellSize) const
{
	int count = 1;
	for (double xCellSize = m_xCellSize; xCellSize / 2 > lastXCellSize; xCellSize /= 2)
		++count;
	return count;
}

void GSGrid::Smooth(SmoothMethod method, double dSize)
{
	std::vector<double> sg(m_grid.size(), std::numeric_limits<double>::quiet_NaN());

	double cs = std::min(m_xCellSize, m_yCellSize);
	int wSize = (int)std::ceil(dSize / cs);
	int wSize2 = std::max(1, wSize / 2);
	wSize = wSize2 * 2 + 1;

	XMatrix filt(wSize, wSize);
	if (eGridSmoothSavitzkyGolay == method)
	{
		filt.SmoothSavitzkyGolay(3);
	}
	else if (eGridSmoothHeat == method)
	{
		filt = XMatrix(3, 3);
		filt.Set({0, 1, 0, 1, 0, 1, 0, 1, 0});
		filt.Scale(1.0 / 4.0);
		wSize = 3;
		wSize2 = 1;
	}
	else if (eGridSmoothBox == method)
	{
		std::vector<double> oneValue(wSize * wSize, 1.0 / (wSize * wSize));
		filt.Set(oneValue);
	}

    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
			double sum = 0.0;
			double boxSum = 0.0;
			int count = 0;

			double z = m_grid[row * m_cols + col];
			if (std::isnan(z))
				continue;

            for (int j = 0; j < wSize; ++j)
            {
                int jj = qBound(0, row + j - wSize2, m_rows - 1);

                for (int i = 0; i < wSize; ++i)
                {
                    int ii = qBound(0, col + i - wSize2, m_cols - 1);
                    
                    z = m_grid[jj * m_cols + ii];
                    if (std::isnan(z))
                        continue;

                    sum += z * filt.Get(j, i);
                    boxSum += z;
                    ++count;
                }
            }

			sg[row * m_cols + col] = (count == wSize * wSize) ? sum : boxSum / count;
        }
    }

	// Copy smooth grid to the input grid
	std::copy(sg.cbegin(), sg.cend(), m_grid.begin());
}

double GSGrid::XCellSize() const
{
	return m_xCellSize;
}

double GSGrid::YCellSize() const
{
	return m_yCellSize;
}

int GSGrid::Rows() const
{
	return m_rows;
}

int GSGrid::Cols() const
{
	return m_cols;
}

double GSGrid::Left() const
{
	return m_left;
}

double GSGrid::Bottom() const
{
	return m_bottom;
}

double GSGrid::GridX(int col) const
{
	return m_left + col * m_xCellSize;
}

double GSGrid::GridY(int row) const
{
	return m_bottom + row * m_yCellSize;
}

void GSGrid::prevWindow(const XMatrix & m, int crow, int ccol, int wx1, int wy1, int wx2, int wy2, double * v)
{
	int begRow = crow + wy1;
	int endRow = crow + wy2;
	int begCol = ccol + wx1;
	int endCol = ccol + wx2;

	int l = 0;
	for (int row = begRow; row <= endRow; ++row)
	{
		int j = qBound(0, row, m_rows - 1);
		for (int col = begCol; col <= endCol; ++col)
		{
			int i = qBound(0, col, m_cols - 1);

			v[l] = m.Get(j, i);
			++l;
		}
	}
}

XMatrix GSGrid::GetIndexMatrix(int defaultValue, const std::vector<XPoint>& xyz)
{
    XMatrix m(m_rows, m_cols, defaultValue);

    for (size_t i = 0; i != xyz.size(); ++i)
    {
        auto&& p = xyz.at(i);
        int row  = NearestRow(p.y);
        int col  = NearestCol(p.x);
        if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
            continue;

        if (m.Get(row, col) < 0)
        {
            m.Set(row, col, i);
			continue;
        }
        
		auto&& q  = xyz.at(static_cast<size_t>(m.Get(row, col)));
            
		double l1 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(GridX(col), GridY(row)));
        double l2 = XGeom::Distance(XVec2d(q.x, q.y), XVec2d(GridX(col), GridY(row)));
			
		if (l1 < l2) // use the closest point to the cell.
		{
			m.Set(row, col, i);
		}
    }

    return m;
}

void GSGrid::FDiffRefine(int kmax, bool smoothLast, const XMatrix& indexMatrix, const std::vector<XPoint>& cont)
{
	// Init Heat equation matrix.
	XMatrix op(3, 3); // Linear filter
	op.Set({ 0, 1, 0, 1, 0, 1, 0, 1, 0 });
	op.Scale(1.0 / 4.0);

	// Set up the LSQ X & Y coordinates
    std::array<double, 9> lsqX{ -m_xCellSize, 0, m_xCellSize, -m_xCellSize, 0, m_xCellSize, -m_xCellSize, 0, m_xCellSize };
	std::array<double, 9> lsqY{ -m_yCellSize, -m_yCellSize, -m_yCellSize, 0, 0, 0, m_yCellSize, m_yCellSize, m_yCellSize };

    for (int k = 0; k <= kmax; ++k)
	{
		// Copy current to prev
		XMatrix prev(m_rows, m_cols);
		prev.Set(std::vector<double>(m_grid.cbegin(), std::next(m_grid.cbegin(), m_rows * m_cols)));

		// Update any control point nodes
		for (auto&& p : cont)
		{
			int row = NearestRow(p.y);
			int col = NearestCol(p.x);

			// Data point at the grid node?
			if (fabs(p.x - GridX(col)) < M_TOL_SAMEPOINT && fabs(p.y - GridY(row)) < M_TOL_SAMEPOINT)
			{
				SetGridZ(row, col, p.z);
				continue;
			}

			// Fit a Least Squares surface to the control point & grid cell points
			XLsq3d lsq;

			// Add the grid cells to the sums
			std::array<double, 9> dataWin; // data window
			prevWindow(prev, row, col, -1, -1, 1, 1, &dataWin[0]);

			int l = 0;
			for (int j = -1; j <= 1; ++j)
			{
				for (int i = -1; i <= 1; ++i)
				{
					// Don't add the centre cell, and skip if too close to the control point
					if ((0 == j && 0 == i) || (fabs(p.x - lsqX[l]) < M_TOL_SAMEPOINT && fabs(p.y - lsqY[l]) < M_TOL_SAMEPOINT))
					{
						++l;
						continue;
					}

					lsq.Add(lsqX[l], lsqY[l], dataWin[l], 0.001);
					++l;
				}
			}

			// Add the control point to the sums
			lsq.Add(p.x - GridX(col), p.y - GridY(row), p.z, 1.0);
			lsq.Solve();

			// Update the cell
			SetGridZ(row, col, lsq.Eval(0.0, 0.0));
		}

		bool isLast = k == kmax && smoothLast;

		// Update the next iteration
		FetchGrid([isLast, &indexMatrix, &prev, &op, this](int row, int col)
		{
			double newZ = 0.0;

			if (!isLast && qRound(indexMatrix.Get(row, col)) >= 0)
			{
				newZ = GridZ(row, col);
			}
			else
			{
				// Apply the smoothing operator
				std::array<double, 9> dataWin; // data window
				prevWindow(prev, row, col, -1, -1, 1, 1, &dataWin[0]);

				for (int i = 0; i < 9; ++i)
					newZ += dataWin[i] * op.Get(i);
			}

			SetGridZ(row, col, isLast ? newZ : XGeom::Lerp(prev.Get(row, col), newZ, 0.3));
		});
	}
}

double GSGrid::InterpZ(double x, double y, bool ext)
{
	if (ext)
	{
		if (x <= m_left)
			x = m_left + M_TOL_DOUBLE;
		if (x >= m_left + (m_cols - 1) * m_xCellSize)
			x = m_left + (m_cols - 1) * m_xCellSize - M_TOL_DOUBLE;
		if (y <= m_bottom)
			y = m_bottom + M_TOL_DOUBLE;
		if (y >= m_bottom + (m_rows - 1) * m_yCellSize)
			y = m_bottom + (m_rows - 1) * m_yCellSize - M_TOL_DOUBLE;
	}

	int col = static_cast<int>(std::floor((x - m_left) / m_xCellSize));
	int row = static_cast<int>(std::floor((y - m_bottom) / m_yCellSize));

	if (col < 0 || col >= m_cols || row < 0 || row >= m_rows)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}

	double x1 = GridX(col);
	double y1 = GridY(row);
	double x2 = GridX(col + 1);
	double y2 = GridY(row + 1);

	std::array<std::array<double, 4>, 4> g;
	cellWindow(row, col, -1, -1, 2, 2, g);
	CXBicubic bicubic(g);

	double tx = (x - x1) / (x2 - x1);
	if (fabs(tx) < M_TOL_DOUBLE)
		tx = 0.0;
	double ty = (y - y1) / (y2 - y1);
	if (fabs(ty) < M_TOL_DOUBLE)
		ty = 0.0;

	return bicubic.Eval(tx, ty);
}

void GSGrid::cellWindow(int crow, int ccol, int wx1, int wy1, int wx2, int wy2, std::array<std::array<double, 4>, 4>& v)
{
    int begRow = crow + wy1;
    int endRow = crow + wy2;
    int begCol = ccol + wx1;
    int endCol = ccol + wx2;

    // check if we can use the fast code
    if (0 <= begCol && endCol < m_cols)
    {
        for (int row = begRow; row <= endRow; ++row)
        {
            int iRow          = qBound(0, row, m_rows - 1);
            auto iterBeg = std::next(m_grid.cbegin(), iRow * m_cols + begCol);
            auto iterEnd = std::next(m_grid.cbegin(), iRow * m_cols + endCol + 1);
            auto iterV   = std::next(v.begin(), (iRow - begRow));
            std::copy(iterBeg, iterEnd, iterV->begin());
        }
    }
	else
	{
		int l = 0;
		double* p = &v[0][0];
		for (int row = begRow; row <= endRow; ++row)
		{
			int r = qBound(0, row, m_rows - 1);
			for (int col = begCol; col <= endCol; ++col)
			{
				int c = qBound(0, col, m_cols - 1);
				p[l] = m_grid[r * m_cols + c];
				++l;
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, const GSGrid& grid)
{
    for (int row = 0; row < grid.Rows(); ++row)
    {
		double y = grid.GridY(row);
        for (int col = 0; col < grid.Cols(); ++col)
        {
			double x = grid.GridX(col);
			double z = grid.GridZ(row, col);
			if (std::isnan(z))
				continue;

            os << x << " " << y << " " << z << "\n";
        }
    }
	return os;
}
