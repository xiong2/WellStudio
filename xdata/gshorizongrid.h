#ifndef GSHORIZONGRID_H
#define GSHORIZONGRID_H

#include "xisolines.h"
#include <QPolygonF>
#include "xdata_global.h"

class CX3DHorizon;
class QPainterPath;
class CXGlobalCoordTransform;

class XDATA_EXPORT GSHorizonGrid
{
public:
	GSHorizonGrid(CX3DHorizon& horizon);
	~GSHorizonGrid();

	// banned copy and move.
	GSHorizonGrid(const GSHorizonGrid&) = delete;
	GSHorizonGrid& operator=(const GSHorizonGrid&) = delete;
	GSHorizonGrid(GSHorizonGrid&&) = delete;
	GSHorizonGrid& operator=(GSHorizonGrid&&) = delete;

	// serialized
	friend std::istream& operator>>(std::istream& is, GSHorizonGrid& grid);
	friend std::ostream& operator<<(std::ostream& os, const GSHorizonGrid& grid);

	const std::vector<std::pair<QPolygonF, int>>& GetOriginCellWithColorIndex();
	const std::vector<std::pair<QPolygonF, int>>& GetCellPolygonWithColorIndex(float* pData = nullptr);
	void GetIsolinesPath(double dLevelFirst, double dLevelLast, int nLevel, int nCoarseFreq, const CXGlobalCoordTransform& trans, QPainterPath* coarsePath, QPainterPath* normalPath, bool needRebuild = false);

	void Clear();

private:
	int valueToColorIndex(double v);

	void buildTriangleMeshesByThread(float* pData);
	void buildCellPolygonWithColorIndex();
	void buildIsolines();

private:
	CX3DHorizon& m_horizon;
	CXIsolines m_isolines;
	std::vector<std::vector<XTriangle3d>> m_vecTriangleMeshes;
	std::vector<std::pair<QPolygonF, int>> m_vecCellPolygonWithIndex;
	std::vector<std::pair<QPolygonF, int>> m_vecOriginCellsWithIndex;

	double m_dMin = std::numeric_limits<double>::max();
	double m_dMax = std::numeric_limits<double>::min();
};

#endif // GSHORIZONGRID_H
