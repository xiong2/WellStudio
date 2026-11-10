#include "gsthreadbuildgridcells.h"
#include <QCoreApplication>
#include "xutmtool.h"
#include "xbicubic.h"
#include "xmathmacro.h"
#include "xisolines.h"
#include "xglobal.h"

GSThreadBuildGridCells::GSThreadBuildGridCells(const QString& objName, CXUTMTool& utm, float* pData, std::vector<std::vector<XTriangle3d>>& triangleMeshes, double* dMin, double* dMax)
    : CXBaseThread(), m_strObjName(objName), m_utm(utm), m_pData(pData), m_triangleMeshes(triangleMeshes), m_pMin(dMin), m_pMax(dMax)
{

}

GSThreadBuildGridCells::~GSThreadBuildGridCells()
{
}

void GSThreadBuildGridCells::RunThread()
{
	if (IsStopped())
        return;

	EmitSetWindowName("Calculating grid and isolines");
    EmitSetTaskName("Calculating for " + m_strObjName + "...");
    EmitStartComputing();
    qApp->processEvents();

	m_triangleMeshes.clear();
	m_triangleMeshes.reserve(m_utm.GetNI() * m_utm.GetNJ());

	for (int i = 0; i < m_utm.GetNI() - 1; ++i)
	{
		EmitUpdateProgress(i, m_utm.GetNI());

		for (int j = 0; j < m_utm.GetNJ() - 1; ++j)
		{
			const std::vector<XTriangle3d>& vecTri = buildCellTriangles(i, j);
			if (vecTri.empty()) continue;

			auto dMinZElem = std::min_element(vecTri.begin(), vecTri.end(), [](const XTriangle3d& t1, const XTriangle3d& t2){ return t1.ZMin() < t2.ZMin(); });
			auto dMaxZElem = std::max_element(vecTri.begin(), vecTri.end(), [](const XTriangle3d& t1, const XTriangle3d& t2){ return t1.ZMax() < t2.ZMax(); });
			*m_pMin = std::min(*m_pMin, dMinZElem->ZMin());
			*m_pMax = std::max(*m_pMax, dMaxZElem->ZMax());
			
			m_triangleMeshes.push_back(vecTri);
		}
	}

}

std::array<std::array<XVec3d, 2>, 2> GSThreadBuildGridCells::getCellVertex(int iI, int iJ)
{
	std::array<std::array<XVec3d, 2>, 2> cellVertex;

    m_utm.IJToXY(iI, iJ, cellVertex[0][0].rx(), cellVertex[0][0].ry());
    m_utm.IJToXY(iI + 1, iJ, cellVertex[1][0].rx(), cellVertex[1][0].ry());
    m_utm.IJToXY(iI + 1, iJ + 1, cellVertex[1][1].rx(), cellVertex[1][1].ry());
    m_utm.IJToXY(iI, iJ + 1, cellVertex[0][1].rx(), cellVertex[0][1].ry());

    cellVertex[0][0].rz() = m_pData[iI * m_utm.GetNJ() + iJ];
    cellVertex[1][1].rz() = m_pData[(iI + 1) * m_utm.GetNJ() + iJ + 1];
    cellVertex[1][0].rz() = m_pData[(iI + 1) * m_utm.GetNJ() + iJ];
    cellVertex[0][1].rz() = m_pData[iI * m_utm.GetNJ() + iJ + 1];

    return cellVertex;
}

bool GSThreadBuildGridCells::getCellNeighborValue(int iI, int iJ, std::array<std::array<double, 4>, 4>* pNeighbors)
{
	for (int i = iI - 1, ii = 0; i <= iI + 2; ++i, ++ii)
    {
        int fixedI = qBound(0, i, m_utm.GetNI() - 1);
        for (int j = iJ - 1, jj = 0; j <= iJ + 2; ++j, ++jj)
        {
            int fixedJ = qBound(0, j, m_utm.GetNJ() - 1);

            (*pNeighbors)[ii][jj] = m_pData[fixedI * m_utm.GetNJ() + fixedJ];
			if ((*pNeighbors)[ii][jj] == g_dInvalidData) 
				return false;
        }
    }

	return true;
}

std::vector<XTriangle3d> GSThreadBuildGridCells::buildCellTriangles(int iI, int iJ)
{
	std::vector<XTriangle3d> triangles;

	if (m_pData[iI * m_utm.GetNJ() + iJ] == g_dInvalidData)
		return triangles;

    std::array<std::array<double, 4>, 4> powers;
	if (!getCellNeighborValue(iI, iJ, &powers))
		return triangles;

    if (powers[1][1] == powers[1][2] && powers[2][1] == powers[2][2] && powers[1][1] == powers[2][1])
    {
        std::array<std::array<XVec3d, 2>, 2> cellVertex = getCellVertex(iI, iJ);
        triangles.emplace_back(cellVertex[0][0], cellVertex[1][1], cellVertex[1][0]); // i part
        triangles.emplace_back(cellVertex[0][0], cellVertex[0][1], cellVertex[1][1]); // j part
    }
    else
    {
        CXBicubic bicubic(powers);

        std::array<std::array<XVec3d, 4>, 4> innerVertex;

        for (int i = 0; i < 4; ++i)
        {
            double dI = i / 3.0;
            for (int j = 0; j < 4; ++j)
            {
                double dJ = j / 3.0;
                m_utm.IJToXY2(iI + dI, iJ + dJ, innerVertex[i][j].rx(), innerVertex[i][j].ry());
                innerVertex[i][j].rz() = bicubic.Eval(dI, dJ);
            }
        }

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                triangles.emplace_back(innerVertex[i][j], innerVertex[i + 1][j + 1], innerVertex[i + 1][j]); // i part
                triangles.emplace_back(innerVertex[i][j], innerVertex[i][j + 1], innerVertex[i + 1][j + 1]); // i part
            }
        }
    }

    return triangles;
}
