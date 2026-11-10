#ifndef GSGRID_H
#define GSGRID_H

#include "xgeometry.h"
#include <string>
#include <vector>
#include <numeric>
#include <array>
#include <iostream>
#include <functional>
#include "xdata_global.h"

class XDATA_EXPORT GSGrid
{
public:
	GSGrid() = default;
	GSGrid(double left, double bottom, int rows, int cols, double xCellSize, double yCellSize);
	GSGrid(double left, double right, double bottom, double top, int rows, int cols);

	void Resize(int rows, int cols, double defaultValue = std::numeric_limits<double>::quiet_NaN());
	void ChangeCellSize(int rows, int cols);

	int NearestRow(double y) const;
	int NearestCol(double x) const;
	
	enum SmoothMethod {eGridSmoothBox, eGridSmoothSavitzkyGolay, eGridSmoothHeat};
	void Smooth(SmoothMethod method, double dSize);

	double XCellSize() const;
	double YCellSize() const;

	int Rows() const;
	int Cols() const;

	double Left() const;
	double Bottom() const;

	void SetGridZ(int row, int col, double v);

	double GridX(int col) const;
	double GridY(int row) const;
	double GridZ(int row, int col) const;

	void FetchGrid(const std::function<void(int row, int col)>& functor);
	void FetchGridXY(const std::function<void(double x, double y, int row, int col)>& functor);

	int SizeIterationCount(double lastXCellSize) const;
	void FDiffRefine(int kmax, bool smoothLast, const XMatrix& info, const std::vector<XPoint>& cont);
	double InterpZ(double x, double y, bool ext = false);

	XMatrix GetIndexMatrix(int defaultValue, const std::vector<XPoint>& xyz);

	friend std::ostream& operator<<(std::ostream& os, const GSGrid& grid);

private:
	void prevWindow(const XMatrix& m, int crow, int ccol, int wx1, int wy1, int wx2, int wy2, double* v);
	void cellWindow(int crow, int ccol, int wx1, int wy1, int wx2, int wy2, std::array<std::array<double, 4>, 4>& v);

private:
	double m_left = 0.0;
	double m_bottom = 0.0;
	int m_rows = 0;
	int m_cols = 0;
	double m_xCellSize = 0.0;
	double m_yCellSize = 0.0;

	std::vector<double> m_grid;
};

#endif // GSGRID_H
