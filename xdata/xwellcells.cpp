#include "xwellcells.h"
#include "xwell.h"
#include "xgridmodel.h"
#include "xobjectfactory.h"
#include "xwellpath.h"
#include "xgridcell.h"
#include "x3dtree.h"
#include "xwaitcursor.h"
#include "xreservoirmodel.h"
#include "xutility.h"
#include "xmath3d.h"

#include <cassert>

#define WELLCELLS_CALCULATE_COUNT 50

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellCells)
EXWellCells
END_REGISTER_OBJECT_TO_FACTORY(CXWellCells)

CXWellCells::CXWellCells()
{
}

CXWellCells::CXWellCells(CXWell *pWell)
{
	SetObjectType(EXWellCells);

	m_wellID = pWell->GetObjectID();

	SetObjectName(pWell->GetObjectName());
	SetIconName(pWell->GetIconName());
}

CXWellCells::~CXWellCells()
{
}

CXWellCells* CXWellCells::CreateWellCells(CXGridModel *pModel, CXWell *pWell)
{
	CXWellCells *pWellCells = new CXWellCells(pWell);

	QList<unsigned int>& listCellIDX = pWellCells->GetCellList();
	QList<double>& listCellMD = pWellCells->GetMDList();
	QHash<unsigned int, QList<double> > hashCells;

	//	Calculate here!  The result should be put into listCellIDX and listCellMD.
	/////////////////////////////////////////////////////////////////////////////
	CXWaitCursor *pWaitCursor = new CXWaitCursor;

	// Get WellPath infomations.
	CXWellPath *pWellPath = pWell->GetWellPath();
	unsigned uPathSize;
	double *pPathData = pWellPath->GetData(uPathSize);
	double *pMd = pWellPath->GetMdData();

	// build 3dtree to save the middle point of each cell.
	const QList<CXGridCell*>& listCell = pModel->GetAllCells();
	int pointSize = 3*listCell.size();
	double *cellPoints = new double[pointSize];

	// Get GridCells center point.
	for (int i=0; i<pointSize; i+=3)
	{
		double *dVertex = listCell.at(i/3)->GetVertex();
		cellPoints[i] = cellPoints[i+1] = cellPoints[i+2] = 0.0;
		for(int j=0; j<24; j+=3)
		{
			cellPoints[i]	+= dVertex[j];
			cellPoints[i+1] += dVertex[j+1];
			cellPoints[i+2] += dVertex[j+2];
		}
		for (int j=0; j<3; ++j)
			cellPoints[i+j] /= 8;
	}
	CX3dtree *cellTree = new CX3dtree(cellPoints, pointSize);
	delete [] cellPoints;

	int TriangleIndexes[12][3] = {
		{0, 1, 2}, {0, 2, 3}, {0, 3, 7}, {0, 7, 4}, {0, 4, 5}, {0, 5, 1},
		{6, 2, 3}, {6, 3, 7}, {6, 2, 1}, {6, 1, 5}, {6, 5, 4}, {6, 4, 7}
	};

	// iteration of every line segments of wellpath.
	for (unsigned i=0; i<uPathSize-3; i+=3) 
	{
		int pIndexs[WELLCELLS_CALCULATE_COUNT];
		double dDistances[WELLCELLS_CALCULATE_COUNT];
		QList<unsigned> listIndex;
		listIndex.reserve(WELLCELLS_CALCULATE_COUNT + 1);

		int idxNearestPt = cellTree->nearest(pPathData[i], pPathData[i+1], pPathData[i+2]);
		cellTree->nnearest(idxNearestPt, pIndexs, dDistances, WELLCELLS_CALCULATE_COUNT);

		listIndex << idxNearestPt;
		std::copy(pIndexs, pIndexs+WELLCELLS_CALCULATE_COUNT, std::back_inserter(listIndex));

		foreach (unsigned id, listIndex)
		{
			double *dVertex = listCell.at(id)->GetVertex();
			for (int j=0; j<12; ++j) 
			{
				QVector3D vecLineFront(pPathData[i],  pPathData[i+1], pPathData[i+2]);
				QVector3D vecLineBack(pPathData[i+3], pPathData[i+4], pPathData[i+5]);
				double dDistance = (vecLineBack - vecLineFront).length();
				QVector3D vecNorm = (vecLineBack - vecLineFront).normalized();

				int *pId = TriangleIndexes[j];
				double *v0 = dVertex + 3*pId[0];
				double *v1 = dVertex + 3*pId[1];
				double *v2 = dVertex + 3*pId[2];

				double pb[3], dir[3];
				NXMath3D::QVector2Array(vecLineFront, pb);
				NXMath3D::QVector2Array(vecNorm, dir);
				
				double t = 0.0, u = 0.0, v = 0.0;
				if (NXUtility::Intersect_RayTriangle(pb, dir, v0, v1, v2, &t, &u, &v)) 
				{
					//    t         md - md1
					// -------  == ----------
					// distance     md2 - md1

					// md = (t * md2 + (dist - t) * md1) / dist
					if (t > FLT_EPSILON && t <= dDistance)
					{
						double md = (t * pMd[i/3] + (dDistance - t) * pMd[i/3-1]) / dDistance;
						if (!listCellIDX.contains(id)) listCellIDX << id;
						hashCells[id].push_back(md);
					}
				}
			}
		}
	}

	for (QList<unsigned>::iterator it = listCellIDX.begin(); it != listCellIDX.end(); )
	{
		const QList<double> &lst = hashCells[*it];
		if (lst.size() < 2) 
		{
			it = listCellIDX.erase(it);
		}
		else
		{
			listCellMD << lst.at(0) << lst.at(1);
			++it;
		}
	}

	//	If listCellIDX is empty means the well does not pass through the model at all.
	if(listCellIDX.isEmpty() || listCellIDX.size() * 2 != listCellMD.size())
	{
		delete pWellCells;
		pWellCells = NULL;
	}

	delete pWaitCursor;

	return pWellCells;
}

bool CXWellCells::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_wellID;
		// Count
		ar << m_listCellIDX.size();
		foreach (unsigned id, m_listCellIDX)
			ar << id;
		// Count
		ar << m_listCellMD.size();
		foreach (double d, m_listCellMD)
			ar << d;
	}
	else
	{
		ar >> m_wellID;
		// Count
		int iSizeCellIDX;
		ar >> iSizeCellIDX;
		for (int i=0; i<iSizeCellIDX; ++i)
		{
			unsigned uId;
			ar >> uId;
			m_listCellIDX << uId;
		}	
		// Count
		int iSizeCellMD;
		ar >> iSizeCellMD;
		for (int i=0; i<iSizeCellMD; ++i)
		{
			double dValue;
			ar >> dValue;
			m_listCellMD << dValue;
		}
	}

	return true;
}

void CXWellCells::_SetSelfDimension()
{
	CXReservoirModel *pModel = dynamic_cast<CXReservoirModel*>(GetParent()->GetParent());
	assert(pModel);
	CXGridModel *pGridModel = pModel->GetGridModel();
	assert(pGridModel);

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	// force to load the gird model displayed data.
	pGridModel->LoadData();
	pGridModel->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}