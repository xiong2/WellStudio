#include "gsthreadstressinterpolation.h"
#include "gsdef.h"
#include "gsstressmap.h"
#include "gsstressparameters.h"
#include "gsgrid.h"
#include "xglobal.h"
#include "xkdtree.h"
#include "xmathmacro.h"
#include "xproject.h"
#include "xseismicutmtool.h"
#include "xlsq.h"
#include "xmath.h"
#include <QApplication>
#include <fstream>

GSThreadStressInterpolation::GSThreadStressInterpolation(CXSeismicUTMTool& utm, const QVector<double>& vecStressData, GSStressMap* pStressMap)
	: m_pUTM(&utm), m_vecStressData(vecStressData), m_pStressMap(pStressMap)
{
}

GSThreadStressInterpolation::~GSThreadStressInterpolation()
{
}

const std::vector<float>& GSThreadStressInterpolation::GetResult() const
{
	return m_vecData;
}

void GSThreadStressInterpolation::SetObjectName(const QString& name)
{
	m_strObjectName = name;
}

void GSThreadStressInterpolation::RunThread()
{
	if (IsStopped())
		return;

	EmitSetWindowName("Interpolation");
	EmitSetTaskName("Interpolating " + m_strObjectName + "...");
	EmitStartComputing();
	qApp->processEvents();

	std::vector<XPoint> vecStressX, vecStressY, vecStressMag;
	vecStressX.reserve(m_vecStressData.size());
	vecStressY.reserve(m_vecStressData.size());
	vecStressMag.reserve(m_vecStressData.size());

	double magMin = std::numeric_limits<double>::max();
	double magMax = std::numeric_limits<double>::min();
	double xMin = std::numeric_limits<double>::max();
	double xMax = std::numeric_limits<double>::min();
	double yMin = std::numeric_limits<double>::max();
	double yMax = std::numeric_limits<double>::min();

	for (size_t i = 0; i < m_vecStressData.size(); i += 4)
	{
		double dX = m_vecStressData.at(i);
		double dY = m_vecStressData.at(i + 1);
		double dMag = m_vecStressData.at(i + 2);
		double dDir = m_vecStressData.at(i + 3);

		magMin = std::min(magMin, dMag);
		magMax = std::max(magMax, dMag);
		xMin = std::min(xMin, dX);
		xMax = std::max(xMax, dX);
		yMin = std::min(yMin, dY);
		yMax = std::max(yMax, dY);

		vecStressMag.emplace_back(dX, dY, gridStressMagLowerBoundary(dMag));

		if (dDir == M_FINVALID)
			continue;

		double dRadian = dDir * M_PI / 180;
		vecStressX.emplace_back(dX, dY, std::cos(dRadian));
		vecStressY.emplace_back(dX, dY, std::sin(dRadian));
		//vecStressX.emplace_back(dX, dY, std::cos(dRadian) * dMag);
		//vecStressY.emplace_back(dX, dY, std::sin(dRadian) * dMag);
	}

	double dXMin, dXMax, dYMin, dYMax;
	m_pUTM->GetDimensionRange(dXMin, dXMax, dYMin, dYMax);

	double cellSize = GetProject()->GetCellSize() / 2;
	int rows = qRound((dYMax - dYMin) / cellSize);
	int cols = qRound((dXMax - dXMin) / cellSize);

	GSGrid gridU(dXMin, dYMin, rows, cols, cellSize, cellSize);
	EmitSetTaskName("Gridding X direction of " + m_strObjectName + "...");
	gridFDiff(gridU, vecStressX);

	GSGrid gridV(dXMin, dYMin, rows, cols, cellSize, cellSize);
	EmitSetTaskName("Gridding Y direction of " + m_strObjectName + "...");
	gridFDiff(gridV, vecStressY);

	GSGrid gridDir(dXMin, dYMin, rows, cols, cellSize, cellSize);
	gridDir.Resize(rows, cols);
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			double mag = gridU.GridZ(row, col);
			if (std::isnan(mag))
				continue;

			double dir = gridV.GridZ(row, col);
			if (std::isnan(dir))
				continue;

			gridDir.SetGridZ(row, col, atan2(dir, mag));
		}
	}

	m_vecData.clear();

	m_vecData.reserve(2 * m_pUTM->GetNI() * m_pUTM->GetNJ());

	// Calculate the lower and upper magnitude boundaries
	magMin = gStressMagRange[m_pStressMap->GetParas()->m_iLowestStatus].m_fSHMag;
	//magMin = gridStressMagLowerBoundary(magMin);
	magMax = gridStressMagUpperBoundary(magMax);

	fillBoundary(vecStressMag, xMin, xMax, yMin, yMax, gridStressMagLowerBoundary(magMin));

	GSGrid gridMag(dXMin, dYMin, rows, cols, cellSize, cellSize);
	EmitSetTaskName("Gridding Magnitude of " + m_strObjectName + "...");
	gridFDiff(gridMag, vecStressMag);

	// Now smooth in the real magnitude data
	for (int j = 0; j < 5; ++j)
	{
		// Re-Apply the real stress magnitude data
		for (size_t i = 0; i < m_vecStressData.size(); i += 4)
		{
			double dX = m_vecStressData.at(i);
			double dY = m_vecStressData.at(i + 1);
			double dMag = m_vecStressData.at(i + 2);
			gridMag.SetGridZ(gridMag.NearestRow(dY), gridMag.NearestCol(dX), dMag);
		}

		gridMag.Smooth(GSGrid::eGridSmoothHeat, gridMag.XCellSize() * 2);

		// Apply the min/max magnitude constraints
		gridMag.FetchGrid([&](int row, int col)
		{
			double mag = qBound(magMin, gridMag.GridZ(row, col), magMax);
			// Only allow if inside a normal lineation. LSQ stuffs it.
			if (mag <= gStressMagRange[MAG_NORMAL].Upper() && !m_pStressMap->IsInsideNormalStructure(gridMag.GridX(col), gridMag.GridY(row)))
			{
				mag = gStressMagRange[MAG_NORMAL].Upper() + 0.005;
			}
			// If the mag is less than the minimum for reverse, set it to minimum if it's inside a reverse lineation
			if (mag < gStressMagRange[MAG_REVERSE].m_fSHMagLower && m_pStressMap->IsInsideReverseStructure(gridMag.GridX(col), gridMag.GridY(row)))
			{
				mag = gStressMagRange[MAG_REVERSE].m_fSHMagLower + 0.005;
			}
			// If the mag is greater than the maximum for normal, set it to less than the maximum if it's inside a normal lineation.
			else if (mag >= gStressMagRange[MAG_LOADING].m_fSHMagLower && m_pStressMap->IsInsideNormalStructure(gridMag.GridX(col), gridMag.GridY(row)))
			{
				mag = gStressMagRange[MAG_LOADING].m_fSHMagLower - 0.001;
			}
			gridMag.SetGridZ(row, col, mag);
		});
	}

	for (int i = 0; i < m_pUTM->GetNI(); ++i)
	{
		for (int j = 0; j < m_pUTM->GetNJ(); ++j)
		{
			double x, y;
			m_pUTM->IJToXY(i, j, x, y);

			int row = qBound(0, gridMag.NearestRow(y), gridMag.Rows() - 1);
			int col = qBound(0, gridMag.NearestCol(x), gridMag.Cols() - 1);

			m_vecData.push_back(gridMag.GridZ(row, col));
		}
	}

	for (int i = 0; i < m_pUTM->GetNI(); ++i)
	{
		for (int j = 0; j < m_pUTM->GetNJ(); ++j)
		{
			double x, y;
			m_pUTM->IJToXY(i, j, x, y);

			int row = qBound(0, gridDir.NearestRow(y), gridDir.Rows() - 1);
			int col = qBound(0, gridDir.NearestCol(x), gridDir.Cols() - 1);
			double angle = gridDir.GridZ(row, col) * 180 / M_PI;

			if (angle < 0)
				angle += 180;
			m_vecData.push_back(angle);
		}
	}
}

void GSThreadStressInterpolation::gridFDiff(GSGrid& grid, const std::vector<XPoint>& xyz)
{
	// Store the initial grid geometry
	double left = grid.Left();
	double bottom = grid.Bottom();
	double right = grid.Left() + (grid.Cols() - 1) * grid.XCellSize();
	double top = grid.Bottom() + (grid.Rows() - 1) * grid.YCellSize();
	double cellX = grid.XCellSize();
	double cellY = grid.YCellSize();
	int originRows = grid.Rows();
	int originCols = grid.Cols();
	double winSize = std::sqrt(cellX*cellX + cellY*cellY) * 2.1;

	const int EDGE_EXTRA = 5;
	const int START_ROWS = 10;
	const int START_COLS = 10;

	double startLeft = left - EDGE_EXTRA * cellX;
	double startBottom = bottom - EDGE_EXTRA * cellY;
	double startRight = right + EDGE_EXTRA * cellX;
	double startTop = top + EDGE_EXTRA * cellY;

	int maxRows = qRound((startTop - startBottom) / cellY) + 1;
	int maxCols = qRound((startRight - startLeft) / cellX) + 1;

	grid = GSGrid(startLeft, startRight, startBottom, startTop, START_ROWS + 2 * EDGE_EXTRA, START_COLS + 2 * EDGE_EXTRA);
	grid.Resize(maxRows, maxCols);

	// Fit a trend surface to the data
	// Calculate the trend surface
	XLsq3d trend(3);

	for (auto&& p : xyz)
	{
		trend.Add(p.x - grid.Left(), p.y - grid.Bottom(), p.z);
	}
	if (!trend.Solve())
	{
		qWarning("Cannot calculate the trend surface for this grid.");
		return;
	}

	// Initialize the grid cells
	grid.FetchGrid([&grid, &trend](int row, int col)
	{
		grid.SetGridZ(row, col, trend.Eval(grid.GridX(col) - grid.Left(), grid.GridY(row) - grid.Bottom()));
	});

	// Try a least squares patch
	XMatrix cellCount(grid.Rows(), grid.Cols());
	XMatrix cellValue(grid.Rows(), grid.Cols());
	std::vector<XPoint> trendSeedPoint;

	// Calculate the average for each raw cell
	for (auto&& p : xyz)
	{
		int row = grid.NearestRow(p.y);
		int col = grid.NearestCol(p.x);
		if (row < 0 || row >= grid.Rows() || col < 0 || col >= grid.Cols())
			continue;

		cellValue.Set(row, col, cellValue.Get(row, col) + p.z);
		cellCount.Set(row, col, cellCount.Get(row, col) + 1);
	}

	grid.FetchGridXY([&cellCount, &cellValue, &trendSeedPoint](double x, double y, int row, int col)
	{
		double count = cellCount.Get(row, col);
		if (count <= 0)
			return;

		trendSeedPoint.emplace_back(x, y, cellValue.Get(row, col) / count);
	});

	/*{
		std::ofstream trendXYZFile("trendXYZ");
		for (auto&& p : trendSeedPoint)
			trendXYZFile << p.x << " " << p.y << " " << p.z << "\n";
	}*/

	double distMax = XGeom::Distance(XVec2d(startLeft, startBottom), XVec2d(startRight, startTop));

	grid.FetchGridXY([&](double x, double y, int row, int col)
	{
		XLsq3d trend;
		for (auto&& p : trendSeedPoint)
		{
			double dist = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
			if (dist >= distMax)
				continue;

			trend.Add(p.x - x, p.y - y, p.z, XMath::Weight(dist, distMax, 6));
		}
		trend.Solve();
		if (!trend.IsValid())
			return;

		grid.SetGridZ(row, col, trend.Eval(0.0, 0.0));
	});

	//{
	//	std::ofstream afterPatchFile("AfterPatch");
	//	afterPatchFile << grid;
	//}

	int nSizeNo = -1;
	int nSizeIterationCount = grid.SizeIterationCount(cellX);
	bool isLastSizeIteration = false;

	while (true) // loop here for each smaller cell size
	{
		++nSizeNo;
		EmitUpdateProgress(nSizeNo, nSizeIterationCount);

		XMatrix indexMatrix = grid.GetIndexMatrix(-2, xyz);

		// Now we refine the grid estimates
		grid.FDiffRefine(15, isLastSizeIteration, indexMatrix, GetControlPoints(indexMatrix, xyz));

		if (isLastSizeIteration)
			break;

		// Move to a finer grid size
		if (grid.XCellSize() / 2 > cellX && grid.YCellSize() / 2 > cellY)
		{
			// Normal 1/2 the current cell size
			// Copy current to prev
			grid.ChangeCellSize(std::min(grid.Rows() * 2, maxRows), std::min(grid.Cols() * 2, maxCols));
		}
		else
		{
			XMatrix prev(originRows, originCols);

			// Interpolate from the current to the new grid
			for (int row = 0; row < originRows; ++row)
			{
				double y = bottom + row * cellY;
				for (int col = 0; col < originCols; ++col)
				{
					double x = left + col * cellX;
					prev.Set(row, col, grid.InterpZ(x, y, true));
				}
			}

			// copy prev to current
			grid = GSGrid(left, bottom, originRows, originCols, cellX, cellY);
			grid.Resize(originRows, originCols);
			grid.FetchGrid([&prev, &grid](int row, int col) { grid.SetGridZ(row, col, prev.Get(row, col)); });

			isLastSizeIteration = true;
		}
	}
}

std::vector<XPoint> GSThreadStressInterpolation::GetControlPoints(const XMatrix & indexMatrix, const std::vector<XPoint>& xyz)
{
	std::vector<XPoint> cont;
	cont.reserve(xyz.size());

	for (int row = 0; row < indexMatrix.Rows(); ++row)
	{
		for (int col = 0; col < indexMatrix.Cols(); ++col)
		{
			if (indexMatrix.Get(row, col) < 0)
				continue;

			// Add control point to the control point array
			cont.push_back(xyz.at(qRound(indexMatrix.Get(row, col))));
		}
	}

	return cont;
}

void GSThreadStressInterpolation::fillBoundary(std::vector<XPoint>& vecMag, double dXMin, double dXMax, double dYMin, double dYMax, double zmin)
{
	std::vector<XPoint> vecAdded;
	
#if 1
	int i, j, nI = m_pUTM->GetNI(), nJ = m_pUTM->GetNJ();
	double x, y;
	double dTh = 5 * m_pUTM->GetIInterval();
	double dHDis = (nJ - 1) * m_pUTM->GetJInterval();
	double dVDis = (nI - 1) * m_pUTM->GetIInterval();

	for (i = 0; i < nI; i++)
	{
		m_pUTM->IJToXY(i, 0, x, y);
		XPoint p = XGeom::ClosestPoint(vecMag, x, y);
		double dDis = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
		if (dDis > dTh)
		{
			if (dDis > dHDis)
				dDis = dHDis;
				
			vecAdded.emplace_back(x, y, p.z - (p.z - zmin) * dDis / dHDis);
		}

		m_pUTM->IJToXY(i, nJ - 1, x, y);
		p = XGeom::ClosestPoint(vecMag, x, y);
		dDis = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
		if (dDis > dTh)
		{
			if (dDis > dHDis)
				dDis = dHDis;

			vecAdded.emplace_back(x, y, p.z - (p.z - zmin) * dDis / dHDis);
		}
	}

	for (j = 1; j < nJ - 1; j++)
	{
		m_pUTM->IJToXY(0, j, x, y);
		XPoint p = XGeom::ClosestPoint(vecMag, x, y);
		double dDis = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
		if (dDis > dTh)
		{
			if (dDis > dVDis)
				dDis = dVDis;

			vecAdded.emplace_back(x, y, p.z - dDis * (p.z - zmin) / dVDis);
		}

		m_pUTM->IJToXY(nI - 1, j, x, y);
		p = XGeom::ClosestPoint(vecMag, x, y);
		dDis = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
		if (dDis > dTh)
		{
			if (dDis > dVDis)
				dDis = dVDis;

			vecAdded.emplace_back(x, y, p.z - dDis * (p.z - zmin) / dVDis);
		}
	}

#else
	double left, right, top, bottom;
	m_pUTM->GetDimensionRange(left, right, bottom, top);

	double xc = std::ceil(m_pUTM->GetIInterval()) / 2;
	double yc = std::ceil(m_pUTM->GetJInterval()) / 2;

	// far points for interpolation
	double xl = left - (right - left) / 2;
	double xr = right + (right - left) / 2;
	double yt = top + (top - bottom) / 2;
	double yb = bottom - (top - bottom) / 2;

	zmin = gStressMagRange[MAG_NORMAL].m_fSHMagLower;

	const int f = 10;
	bool needBottom = dYMin > bottom + f * yc;
	bool needTop = dYMax < top - f * yc;
	bool needLeft = dXMin > left + f * xc;
	bool needRight = dXMax < right - f * xc;


	if (needLeft || needRight)
	{
		for (double y = bottom + yc / 2; y < top; y += yc)
		{
			if (needLeft)
			{
				XPoint p = XGeom::ClosestPoint(vecMag, left, y);
				double d1 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(left, y));
				double d2 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(xl, y));
				vecAdded.emplace_back(left + xc, y, p.z - d1 / d2 * (p.z - zmin));
			}
			if (needRight)
			{
				XPoint p = XGeom::ClosestPoint(vecMag, right, y);
				double d1 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(right, y));
				double d2 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(xr, y));
				vecAdded.emplace_back(right - xc, y, p.z - d1 / d2 * (p.z - zmin));
			}
		}
	}

	if (needTop || needBottom)
	{
		for (double x = left + xc / 2; x < right; x += xc)
		{
			if (needTop)
			{
				XPoint p = XGeom::ClosestPoint(vecMag, x, top);
				double d1 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, top));
				double d2 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, yt));
				vecAdded.emplace_back(x, top - yc, p.z - d1 / d2 * (p.z - zmin));
			}
			if (needBottom)
			{
				XPoint p = XGeom::ClosestPoint(vecMag, x, bottom);
				double d1 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, bottom));
				double d2 = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, yb));
				vecAdded.emplace_back(x, bottom + yc, p.z - d1 / d2 * (p.z - zmin));
			}
		}
	}
#endif

	vecMag.insert(vecMag.end(), vecAdded.cbegin(), vecAdded.cend());
}

double GSThreadStressInterpolation::gridStressMagLowerBoundary(double dMin, int iStep)
{
	int magType = magTypeFromMag(dMin);
	for(int i = 0; i < iStep; i++)
		magType = magTypeBelow(magType);
	return XGeom::Lerp(gStressMagRange[magType].m_fSHMagLower, gStressMagRange[magType].Upper(), 0.1);
}

double GSThreadStressInterpolation::gridStressMagUpperBoundary(double dMax)
{
	int magType = magTypeFromMag(dMax);
	return XGeom::Lerp(gStressMagRange[magType].m_fSHMagLower, gStressMagRange[magType].Upper(), 0.9);
}

int GSThreadStressInterpolation::magTypeFromMag(double mag)
{
	if (mag < gStressMagRange[0].Upper())
		return MAG_NORMAL;

	if (mag >= gStressMagRange[MAG_REVERSE].m_fSHMagLower)
		return MAG_REVERSE;

	for (int i = 0; i < sizeof(gStressMagRange) / sizeof(gStressMagRange[0]); ++i)
	{
		if (gStressMagRange[i].m_fSHMagLower <= mag && mag <= gStressMagRange[i].Upper())
			return gStressMagRange[i].m_iStressState;
	}

	return MAG_NULL;
}

int GSThreadStressInterpolation::magTypeBelow(int magType)
{
	return magType > MAG_NORMAL ? magType - 1 : MAG_NORMAL;
}
