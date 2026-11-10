#ifndef GSTHREADBUILDGRIDCELLS_H
#define GSTHREADBUILDGRIDCELLS_H

#include "xbasethread.h"
#include <vector>
#include <limits>
#include <QPolygonF>
#include "xgeometry.h"
#include "xdata_global.h"

class CXUTMTool;
class CXIsolines;

class XDATA_EXPORT GSThreadBuildGridCells : public CXBaseThread
{
public:
	GSThreadBuildGridCells(const QString& objName, CXUTMTool& utm, float* pData, std::vector<std::vector<XTriangle3d>>& triangleMeshes, double* dMin, double* dMax);
	~GSThreadBuildGridCells();

protected:
	void RunThread() override;

private:
	std::array<std::array<XVec3d, 2>, 2> getCellVertex(int iI, int iJ);
	bool getCellNeighborValue(int iI, int iJ, std::array<std::array<double, 4>, 4>* pNeighbors);
	std::vector<XTriangle3d> buildCellTriangles(int i, int j);

private:
	QString m_strObjName;
	CXUTMTool& m_utm;
	float* m_pData = nullptr;
	std::vector<std::vector<XTriangle3d>>& m_triangleMeshes;
	double* m_pMin = nullptr;
	double* m_pMax = nullptr;
};

#endif // GSTHREADBUILDGRIDCELLS_H
