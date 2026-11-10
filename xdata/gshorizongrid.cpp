#include "gshorizongrid.h"
#include "x3dhorizon.h"
#include "gsthreadbuildgridcells.h"
#include "xdlgcalculatingprogress.h"
#include "xglobalcoordtransform.h"
#include "xwaitcursor.h"
#include <QPainterPath>
#include <qdebug.h>

GSHorizonGrid::GSHorizonGrid(CX3DHorizon& horizon)
    : m_horizon(horizon)
{
}

GSHorizonGrid::~GSHorizonGrid()
{
}

const std::vector<std::pair<QPolygonF, int>>& GSHorizonGrid::GetOriginCellWithColorIndex()
{
    if (m_vecOriginCellsWithIndex.empty())
    {
        const CXUTMTool& utm = m_horizon.GetUTM();
        float* pData        = m_horizon.GetData();

        int nI = utm.GetNI();
        int nJ = utm.GetNJ();

        for (int i = 0; i < nI - 1; ++i)
        {
            for (int j = 0; j < nJ - 1; ++j)
            {
                QPolygonF cell(4);

                utm.IJToXY(i, j, cell[0].rx(), cell[0].ry());
                utm.IJToXY(i + 1, j, cell[1].rx(), cell[1].ry());
                utm.IJToXY(i + 1, j + 1, cell[2].rx(), cell[2].ry());
                utm.IJToXY(i, j + 1, cell[3].rx(), cell[3].ry());

                double value = pData[i * nJ + j];
                int index    = valueToColorIndex(value);

                m_vecOriginCellsWithIndex.emplace_back(cell, index);
            }
        }
    }

    return m_vecOriginCellsWithIndex;
}

const std::vector<std::pair<QPolygonF, int>>& GSHorizonGrid::GetCellPolygonWithColorIndex(float* pData)
{
    if (m_vecTriangleMeshes.empty())
        buildTriangleMeshesByThread(pData ? pData : m_horizon.GetData());

    if (m_vecCellPolygonWithIndex.empty())
        buildCellPolygonWithColorIndex();

    return m_vecCellPolygonWithIndex;
}

void GSHorizonGrid::Clear()
{
	m_vecTriangleMeshes.clear();
	m_vecCellPolygonWithIndex.clear();
	m_vecOriginCellsWithIndex.clear();
		
	m_dMin = std::numeric_limits<double>::max();
	m_dMax = std::numeric_limits<double>::min();
}

void GSHorizonGrid::GetIsolinesPath(double dLevelFirst, double dLevelLast, int nLevel, int nCoarseFreq, const CXGlobalCoordTransform& trans, QPainterPath* coarsePath, QPainterPath* normalPath, bool needRebuild)
{
    if (m_isolines.LevelCount() == 0 || needRebuild)
    {
        m_isolines.SetLevel(dLevelFirst, dLevelLast, nLevel);
        buildIsolines();
    }

    auto buildPath = [&trans](const std::set<std::pair<XVec2d, XVec2d>>* segments, QPainterPath& path) 
	{
        for (auto&& segment : *segments)
        {
            QPointF firstPoint  = trans.World2Local(QPointF(segment.first.x(), segment.first.y()));
            QPointF secondPoint = trans.World2Local(QPointF(segment.second.x(), segment.second.y()));
            path.moveTo(firstPoint);
            path.lineTo(secondPoint);
        }
    };

    *coarsePath = QPainterPath();
    *normalPath = QPainterPath();

    for (size_t i = 0; i < m_isolines.LevelCount(); ++i)
    {
        const std::set<std::pair<XVec2d, XVec2d>>* pSegments = m_isolines.GetSegments(i);
        if (!pSegments)
            continue;

        buildPath(pSegments, i % nCoarseFreq ? *normalPath : *coarsePath);
    }
}

int GSHorizonGrid::valueToColorIndex(double v)
{
    if (v == M_FINVALID)
        return -1;

	if (m_dMin > m_dMax)
		m_horizon.GetDataRange(m_dMin, m_dMax);

    //Q_ASSERT(m_dMin <= v && v <= m_dMax);
	if (m_dMin > v || v > m_dMax)
	{
		qDebug()<<"Something error!";
	}
    int index = (v - m_dMin) / (m_dMax - m_dMin) * 255;

    return qBound(0, index, 255);
}

void GSHorizonGrid::buildTriangleMeshesByThread(float* pData)
{
    auto pThread = std::make_unique<GSThreadBuildGridCells>(m_horizon.GetObjectName(), m_horizon.GetUTM(), pData, m_vecTriangleMeshes, &m_dMin, &m_dMax);
    pThread->LockRead(&m_horizon);
    auto pProgress = new CXDlgCalculatingProgress(pThread.get());
    pProgress->show();
    pThread->start();
    if (pProgress->exec() == QDialog::Accepted)
    {
        pThread->UnlockRead(&m_horizon);
    }
}

void GSHorizonGrid::buildCellPolygonWithColorIndex()
{
    using CIter      = std::vector<XTriangle3d>::const_iterator;
    auto isSameIndex = [this](CIter begin, CIter end) {
        int lastIndex = -999;

        for (auto it = begin; it != end; ++it)
        {
            int index0 = valueToColorIndex(it->Vertex(0).z());
            int index1 = valueToColorIndex(it->Vertex(1).z());
            int index2 = valueToColorIndex(it->Vertex(2).z());

            if (index0 != index1 || index1 != index2)
                return false;

            if (lastIndex == -999)
                lastIndex = index0;
            else if (lastIndex != index0)
                return false;
        }

        return true;
    };

    m_vecCellPolygonWithIndex.clear();
    m_vecCellPolygonWithIndex.reserve(m_vecTriangleMeshes.size());

    for (auto&& triangles : m_vecTriangleMeshes)
    {
        if (isSameIndex(triangles.begin(), triangles.end()))
        {
            QPolygonF cellSqaure;
            if (triangles.size() == 2)
            {
				cellSqaure << QPointF(triangles.at(1).Vertex(0).x(), triangles.at(1).Vertex(0).y())
						   << QPointF(triangles.at(1).Vertex(1).x(), triangles.at(1).Vertex(1).y())
						   << QPointF(triangles.at(1).Vertex(2).x(), triangles.at(1).Vertex(2).y())
						   << QPointF(triangles.at(0).Vertex(2).x(), triangles.at(0).Vertex(2).y());
			}
			else
			{
				cellSqaure << QPointF(triangles.at(0).Vertex(0).x(), triangles.at(0).Vertex(0).y())
						   << QPointF(triangles.at(12).Vertex(2).x(), triangles.at(12).Vertex(2).y())
						   << QPointF(triangles.at(16).Vertex(1).x(), triangles.at(16).Vertex(1).y())
						   << QPointF(triangles.at(5).Vertex(1).x(), triangles.at(5).Vertex(1).y());
			}
            int iColorIndex = valueToColorIndex(triangles.at(0).Vertex(0).z());
            m_vecCellPolygonWithIndex.emplace_back(cellSqaure, iColorIndex);
        }
        else
        {
            for (auto&& tri : triangles)
            {
                QPolygonF cellTriangle;
                cellTriangle << QPointF(tri.Vertex(0).x(), tri.Vertex(0).y()) << QPointF(tri.Vertex(1).x(), tri.Vertex(1).y()) << QPointF(tri.Vertex(2).x(), tri.Vertex(2).y());
                int iColorIndex = valueToColorIndex(tri.Vertex(0).z());
                m_vecCellPolygonWithIndex.emplace_back(cellTriangle, iColorIndex);
            }
        }
    }
}

void GSHorizonGrid::buildIsolines()
{
	CXWaitCursor waitCursor;
	m_isolines.Clear();
    for (auto&& mesh : m_vecTriangleMeshes)
    {
        m_isolines.CalculateWithTriangleMeshes(mesh);
    }
}

std::istream& operator>>(std::istream& is, GSHorizonGrid& grid)
{
	size_t originCellSize;
	is >> originCellSize;
	grid.m_vecOriginCellsWithIndex.resize(originCellSize);

	for (auto&& cell : grid.m_vecOriginCellsWithIndex)
	{
		int n, index;
        is >> n;
        QPolygonF points(n);
        for (int i = 0; i < n; ++i)
        {
            is >> points[i].rx() >> points[i].ry();
        }
        is >> index;
        cell.first  = std::move(points);
        cell.second = index;
	}

    size_t meshesSize;
    is >> meshesSize;
    grid.m_vecTriangleMeshes.resize(meshesSize);

    for (auto&& mesh : grid.m_vecTriangleMeshes)
    {
        size_t triangleSize;
        is >> triangleSize;
        mesh.resize(triangleSize);
        for (auto&& triangle : mesh)
        {
            is >> triangle;
        }
    }

    size_t cellSize;
    is >> cellSize;
    grid.m_vecCellPolygonWithIndex.resize(cellSize);

    for (auto&& cell : grid.m_vecCellPolygonWithIndex)
    {
        int n, index;
        is >> n;
        QPolygonF points(n);
        for (int i = 0; i < n; ++i)
        {
            is >> points[i].rx() >> points[i].ry();
        }
        is >> index;
        cell.first  = std::move(points);
        cell.second = index;
    }

    is >> grid.m_isolines;

    return is;
}

std::ostream& operator<<(std::ostream& os, const GSHorizonGrid& grid)
{
	os << grid.m_vecOriginCellsWithIndex.size();
	for (auto&& cell : grid.m_vecOriginCellsWithIndex)
	{
		os << cell.first.size();
		for (auto&& p : cell.first)
		{
			os << p.x() << p.y();
		}
		os << cell.second;
	}

    os << grid.m_vecTriangleMeshes.size();
    for (auto&& mesh : grid.m_vecTriangleMeshes)
    {
        os << mesh.size();
        for (auto&& triangle : mesh)
        {
            os << triangle;
        }
    }

    os << grid.m_vecCellPolygonWithIndex.size();
    for (auto&& cell : grid.m_vecCellPolygonWithIndex)
    {
        os << cell.first.size();
        for (auto&& p : cell.first)
        {
            os << p.x() << p.y();
        }
        os << cell.second;
    }

    os << grid.m_isolines;

    return os;
}
