#include "xthreadmodelintersecion.h"

#include <cassert>
#include <algorithm>
//#include <fstream>

#include <QApplication>
#include <QDebug>

#include "xparametermodelintersecion.h"
#include "xgridmodel.h"
#include "xgridcell.h"
#include <qvector3d.h>
#include "xmath3d.h"
#include "xintersectiongrid.h"
#include "xintersectedgridcell.h"

CXThreadModelIntersection::CXThreadModelIntersection(CXGridModel *pModel, CXParameterModelIntersection *pPara) : m_pModel( pModel ), m_pPara( pPara )
{
	assert(m_pModel && m_pPara);

	if (m_pModel && m_pPara) {
		_InitLock();
		_CreateObj();
	}
}

void CXThreadModelIntersection::_CreateObj()
{
	unsigned uI, uJ, uK;
	m_pModel->GetIJKDimentionInfo( uI, uJ, uK );

	for (auto i = 0; i != 2; ++i) m_vecOutput.push_back(new CXIntersectionGrid( uI, uJ, uK, m_pModel->GetSegment() ));
}

CXThreadModelIntersection::~CXThreadModelIntersection()
{
	if ( IsStopped() ) {
		qDeleteAll(m_vecOutput);
		m_vecOutput.clear();
	}
}

void CXThreadModelIntersection::RunThread()
{
	if ( IsStopped() ) return;
	if ( m_vecOutput.empty() ) {
		EmitGeneralErrorMsg("Cannot create new intersection grid.");
		return;
	}

	const std::vector<double>& vecX = m_pPara->GetVecX();
	const std::vector<double>& vecY = m_pPara->GetVecY();

	if ( vecX.size() != 2 && vecY.size() != 2 ) {
		EmitGeneralErrorMsg( "Intersection cannot support more than two turning-points until now." );
		return;
	}

	this->EmitSetWindowName("Intersection.");
	this->EmitSetTaskName("intersected grid model...");
	this->EmitStartComputing();
	qApp->processEvents();

	// Progress info
	m_nTotalStep = m_pModel->GetValidCellNumber();
	m_iCurrent = 0;

	// Get the incised grids.
	if ( _IncisedGrid(vecX, vecY) ) return;

	if (IsStopped())
		return;

	this->EmitResetProgressBar();
	this->EmitSetTaskName("Calculating intersection...");
	qApp->processEvents();
}

void CXThreadModelIntersection::_InitLock()
{
	if ( m_pModel )
        LockRead(m_pModel);
}

void CXThreadModelIntersection::_Indices2Lines(std::vector<int>::const_iterator beg, std::vector<int>::const_iterator end, QSet<QPair<int, int>>& setLines)
{
	for ( auto iter = beg; true; ++iter ) {
		auto next = std::next(iter);
		if ( next == end ) {
			setLines << (*iter > *beg ? qMakePair( *beg, *iter ) : qMakePair( *iter, *beg ));
			break;
		}
		setLines << (*iter > *next ? qMakePair( *next, *iter ) : qMakePair( *iter, *next ));
	}
}

bool CXThreadModelIntersection::_CheckIntersectionFaceClosure(std::vector<std::pair<unsigned, unsigned> > &listPair, std::vector<unsigned> &vecRet)
{
	auto iterFound = listPair.begin();
	while ( iterFound != listPair.end() ) {
		const auto& pairFound = *iterFound;
		vecRet.push_back(pairFound.first);
		iterFound = std::find_if(listPair.begin(), listPair.end(), [&pairFound](const std::pair<unsigned, unsigned> &pair) {
			return pairFound.second == pair.first;
		});
		if ( iterFound == listPair.end() ) {
			iterFound = std::find_if(listPair.begin(), listPair.end(), [&pairFound](const std::pair<unsigned, unsigned> &curr)
			{
				return curr.first != pairFound.first && curr.second == pairFound.second;
			});
			if ( iterFound != listPair.end() ) 
				std::swap(iterFound->first, iterFound->second);
			else {
				vecRet.clear();
				return false;
			}
				
		}

		if (iterFound->first == listPair.front().first) return true;
	}

	return false;
}

bool CXThreadModelIntersection::_IncisedGrid(const std::vector<double>& vecX, const std::vector<double>& vecY)
{
	// Get plane normal
	QVector3D vecPlane1(vecX[0], vecY[0], 0);
	QVector3D vecPlane2(vecX[0], vecY[0], 1);
	QVector3D vecPlane3(vecX[1], vecY[1], 1);

	double pNorm[3];
	double pVecP[3];
	NXMath3D::QVector2Array(QVector3D::normal(vecPlane1, vecPlane2, vecPlane3), pNorm);
	NXMath3D::QVector2Array(vecPlane1, pVecP);
	double dD = NXMath3D::Vec3Dot( pVecP, pNorm );

	int cubeIndices[6][4] = {
		{0, 1, 2, 3}, {4, 5, 6, 7}, {0, 1, 5, 4}, {1, 2, 6, 5}, {2, 3, 7, 6}, {0, 3, 7, 4}
	};

	int cubeVerxNum = sizeof(*cubeIndices) / sizeof(int);
	int cubeFaceNum = sizeof(cubeIndices) / sizeof(*cubeIndices);

	auto dXMin0 = 9999999., dXMax0 = -9999999., dYMin0 = 9999999., dYMax0 = -9999999., dZMin0 = 9999999., dZMax0 = -9999999.;
	auto dXMin1 = 9999999., dXMax1 = -9999999., dYMin1 = 9999999., dYMax1 = -9999999., dZMin1 = 9999999., dZMax1 = -9999999.;

	// debug
	//std::ofstream os("log.txt");

	// each cell
	const QList<CXGridCell*>& listCells = m_pModel->GetAllCells();
	foreach (auto pCell, listCells)
	{
		this->EmitUpdateProgress(++m_iCurrent, m_nTotalStep);
		assert( pCell );

		// minimum and maximum vertices
		double pMin[3], pMax[3];
		pCell->GetBoundingBox(pMin[0], pMax[0], pMin[1], pMax[1], pMin[2], pMax[2]);

		auto funcCellDimension = [&pMin, &pMax](double &dXMin, double &dXMax, double &dYMin, double &dYMax, double &dZMin, double &dZMax)
		{
			dXMin = dXMin < pMin[0] ? dXMin : pMin[0];
			dXMax = dXMax > pMax[0] ? dXMax : pMax[0];
			dYMin = dYMin < pMin[1] ? dYMin : pMin[1];
			dYMax = dYMax > pMax[1] ? dYMax : pMax[1];
			dZMin = dZMin < pMin[2] ? dZMin : pMin[2];
			dZMax = dZMax > pMax[2] ? dZMax : pMax[2];
		};

		auto funcCalcBounding = [&pNorm](double (&p1)[3], double (&p2)[3]) -> double 
		{
			auto ret = 0.0;
			for (auto pos = 0; pos != 3; ++pos)
				ret += (pNorm[pos] >= 0 ? p1[pos] : p2[pos]) * pNorm[pos];
			return ret;
		};
		

		if		( funcCalcBounding( pMin, pMax ) > dD ) {// cube located on the one side of the plane
			m_vecOutput[0]->GetAllCells() << new CXGridCell(*pCell); // need copy for base class destructor.
			funcCellDimension(dXMin0, dXMax0, dYMin0, dYMax0, dZMin0, dZMax0);
		}
		else if ( funcCalcBounding( pMax, pMin ) < dD ) {// cube located on the other side of the plane
			m_vecOutput[1]->GetAllCells() << new CXGridCell(*pCell); // need copy for base class destructor.
			funcCellDimension(dXMin1, dXMax1, dYMin1, dYMax1, dZMin1, dZMax1);
		}
		else {
			// cube intersected with the plane
			unsigned short uI, uJ, uK;
			pCell->GetIJK(uI, uJ, uK);
			double *pVertices = pCell->GetVertex();
			/*os << "================================================";
			os << "Cell: " << uI << ", " << uJ << ", " << uK << "\n";*/

			// new intersected cell
			auto pIntersectedCell0 = new CXIntersectedGridCell(uI, uJ, uK);
			auto pIntersectedCell1 = new CXIntersectedGridCell(uI, uJ, uK);

			// vertices
			double	*pVertices0	= pIntersectedCell0->GetVertex();
			double	*pVertices1	= pIntersectedCell1->GetVertex();
			int		&nVertex0	= pIntersectedCell0->GetVertexNum();
			int		&nVertex1	= pIntersectedCell1->GetVertexNum();

			// faces
			vector<vector<unsigned> >	&vecFaces0			= pIntersectedCell0->GetFace();
			vector<vector<unsigned> >	&vecFaces1			= pIntersectedCell1->GetFace();
			vector<unsigned>			&vecLineIndices0	= pIntersectedCell0->GetBorderIndices();
			vector<unsigned>			&vecLineIndices1	= pIntersectedCell1->GetBorderIndices();

			// states
			enum State {Side0 = -1, OnTheFace, Side1};
			QHash<int, State> hashState;

			// line strip
			QSet<QPair<int, int> > setLines0;
			QSet<QPair<int, int> > setLines1;

			// origin index to order index map
			QMap<int, int> mapIndex0;
			QMap<int, int> mapIndex1;
			QMap<int, int> mapEdgeIndex0;
			QMap<int, int> mapEdgeIndex1;

			// foreach vertex
			for (auto i = 0; i != 8; ++i) {
				double pVertex[3];
				for (auto offset = 0; offset != 3; ++offset) 
					pVertex[offset] = pVertices[i * 3 + offset];

				double dVertexD = NXMath3D::Vec3Dot(pVertex, pNorm);
				if ( std::fabs (dVertexD - dD) < DBL_EPSILON ) {	// vertex located on the plane.
					hashState[i] = OnTheFace;

					// vertex coordinates
					for (auto offset = 0; offset != 3; ++offset) {
						pVertices0[nVertex0 * 3 + offset] = pVertex[offset];
						pVertices1[nVertex1 * 3 + offset] = pVertex[offset];
					}

					mapIndex0[i] = nVertex0++;
					mapIndex1[i] = nVertex1++;
				} else if ( dVertexD > dD ) {						// vertex located on the one side of the plane
					hashState[i] = Side0;
					for (auto offset = 0; offset != 3; ++offset) 
						pVertices0[nVertex0 * 3 + offset] = pVertex[offset];
					mapIndex0[i] = nVertex0++;
				} else if ( dVertexD < dD ) {						// vertex located on the other side of the plane
					hashState[i] = Side1;
					for (auto offset = 0; offset != 3; ++offset) 
						pVertices1[nVertex1 * 3 + offset] = pVertex[offset];
					mapIndex1[i] = nVertex1++;
				}
			}

			/*os << "0 Vertices: \n";
			QMapIterator<int, int> iterMap0(mapIndex0);
			while (iterMap0.hasNext()) {
				iterMap0.next();
				os << "\t" << iterMap0.key() << ": " << iterMap0.value() << "\n";
			}
			os << "1 Vertices: \n";
			QMapIterator<int, int> iterMap1(mapIndex1);
			while (iterMap1.hasNext()) {
				iterMap1.next();
				os << "\t" << iterMap1.key() << ": " << iterMap1.value() << "\n";
			}*/

			// intersection face
			vector<std::pair<unsigned, unsigned> > vecLineIntersection0;
			vector<std::pair<unsigned, unsigned> > vecLineIntersection1;

			// foreach faces
			for (auto i = 0; i != cubeFaceNum; ++i) {
				int sumState = 0;
				for (auto j = 0; j != cubeVerxNum; ++j)
					sumState += hashState.value(cubeIndices[i][j]);

				auto funcNotIntersection = [&](QMap<int, int> const& mapIndex, vector<vector<unsigned> > &vecFaces, QSet<QPair<int, int> > &setLines) {
					// Triangle strips
					int quadTriangleStrip[4];
					NXMath3D::QuadTriangleStrips(cubeIndices[i], quadTriangleStrip);
					std::for_each(std::begin(quadTriangleStrip), std::end(quadTriangleStrip), [&mapIndex](int &elem) { elem = mapIndex[elem]; });
					vecFaces.push_back(vector<unsigned>(std::begin(quadTriangleStrip), std::end(quadTriangleStrip)));
					// Lines
					vector<int> vecLines(std::begin(cubeIndices[i]), std::end(cubeIndices[i]));
					std::for_each(vecLines.begin(), vecLines.end(), [&mapIndex](int &elem){ elem = mapIndex[elem]; });
					_Indices2Lines(vecLines.cbegin(), vecLines.cend(), setLines);
				};

				int nOnTheFace = std::count_if(std::begin(cubeIndices[i]), std::end(cubeIndices[i]), [&hashState](int v) {return 0 == hashState[v]; });

				if			( -4 == sumState || ( -3 == sumState && 1 == nOnTheFace ) || ( -2 == sumState && 2 == nOnTheFace ) ) { 
					// this face located on the one side of the plane   || one vertex on the plane || one edge on the plane
					funcNotIntersection(mapIndex0, vecFaces0, setLines0);
				} else if	(  4 == sumState || (  3 == sumState && 1 == nOnTheFace ) || (  2 == sumState && 2 == nOnTheFace ) ) {
					// this face located on the other side of the plane || one vertex on the plane || one edge on the plane
					funcNotIntersection(mapIndex1, vecFaces1, setLines1);
				} else { 
					// this face intersected with the plane
					
					// foreach edge
					std::vector<unsigned> vecFaceIndices0;
					std::vector<unsigned> vecFaceIndices1;
					std::vector<int> vecIntersection0;
					std::vector<int> vecIntersection1;

					for (auto j = 0; j != cubeVerxNum; ++j)
					{
						int idx = cubeIndices[i][j];
						if ( 0 == hashState[idx] ) {
							vecIntersection0.push_back( mapIndex0.value(idx) );
							vecIntersection1.push_back( mapIndex1.value(idx) );
						}
					}

					for (auto start = 0; start != cubeVerxNum; ++start) {
						auto end = (start + 1 == cubeVerxNum) ? 0 : start + 1;

						int idxStart = cubeIndices[i][start];
						int idxEnd = cubeIndices[i][end];

						if ( 0 > hashState[idxStart] + hashState[idxEnd] ) { // this edge located on the one side of the plane
							int idxNewStart = mapIndex0.value( idxStart );
							int idxNewEnd	= mapIndex0.value( idxEnd );

							if ( vecFaceIndices0.empty() || idxNewStart != vecFaceIndices0.back() ) vecFaceIndices0.push_back( idxNewStart );
							if ( idxNewEnd != vecFaceIndices0.front() ) vecFaceIndices0.push_back( idxNewEnd );
							setLines0 << ( idxNewStart < idxNewEnd ? qMakePair( idxNewStart, idxNewEnd ) : qMakePair( idxNewEnd, idxNewStart ) );
						}
						else if ( 0 < hashState[idxStart] + hashState[idxEnd] ) { // this edge located on the other side of the plane
							int idxNewStart = mapIndex1.value( idxStart );
							int idxNewEnd	= mapIndex1.value( idxEnd );

							if ( vecFaceIndices1.empty() || idxNewStart != vecFaceIndices1.back() ) vecFaceIndices1.push_back( idxNewStart );
							if ( idxNewEnd != vecFaceIndices1.front() ) vecFaceIndices1.push_back( idxNewEnd );
							setLines1 << ( idxNewStart < idxNewEnd ? qMakePair( idxNewStart, idxNewEnd ) : qMakePair( idxNewEnd, idxNewStart ) );
						}
						else { // this edge intersected with the plane
							// get vertex coordinate
							double p0[3], p1[3], pIntersection[3];
							for ( auto offset = 0; offset != 3; ++offset ) {
								p0[offset] = pVertices[idxStart * 3 + offset];
								p1[offset] = pVertices[idxEnd * 3 + offset];
							}
							if ( 1 != NXMath3D::Intersect_SegmentPlane( p0, p1, pVecP, pNorm, pIntersection ) ) throw "Intersection failed.";

							// add intersection point to map and vertices list.
							int iKey = idxStart > idxEnd ? idxEnd * 10 + idxStart : idxStart * 10 + idxEnd;
							if ( !mapEdgeIndex0.contains( iKey ) ) {
								for ( auto offset = 0; offset != 3; ++offset )
									pVertices0[nVertex0 * 3 + offset] = pIntersection[offset];
								mapEdgeIndex0[iKey] = nVertex0++;
							}
							if ( !mapEdgeIndex1.contains( iKey ) ) {
								for ( auto offset = 0; offset != 3; ++offset )
									pVertices1[nVertex1 * 3 + offset] = pIntersection[offset];
								mapEdgeIndex1[iKey] = nVertex1++;
							}

							int idxNewStart0	= mapIndex0.value( idxStart );
							int idxNewEnd0		= mapIndex0.value( idxEnd );
							int idxNewStart1	= mapIndex1.value( idxStart );
							int idxNewEnd1		= mapIndex1.value( idxEnd );
							int idxIntersection0 = mapEdgeIndex0.value( iKey );
							int idxIntersection1 = mapEdgeIndex1.value( iKey );

							if ( hashState[idxStart] == Side0 ) {
								setLines0 << qMakePair( idxNewStart0, idxIntersection0 );
								if ( vecFaceIndices0.empty() || idxNewStart0 != vecFaceIndices0.back() ) vecFaceIndices0.push_back( idxNewStart0 );
								vecFaceIndices0.push_back( idxIntersection0 );

								setLines1 << qMakePair( idxNewEnd1, idxIntersection1 );
								vecFaceIndices1.push_back( idxIntersection1 );
								if ( idxNewEnd1 != vecFaceIndices1.front() ) vecFaceIndices1.push_back( idxNewEnd1 );
							}
							else { // Side1
								setLines1 << qMakePair( idxNewStart1, idxIntersection1 );
								if ( vecFaceIndices1.empty() || idxNewStart1 != vecFaceIndices1.back() ) vecFaceIndices1.push_back( idxNewStart1 );
								vecFaceIndices1.push_back( idxIntersection1 );

								setLines0 << qMakePair( idxNewEnd0, idxIntersection0 );
								vecFaceIndices0.push_back( idxIntersection0 );
								if ( idxNewEnd0 != vecFaceIndices0.front() ) vecFaceIndices0.push_back( idxNewEnd0 );
							}

							vecIntersection0.push_back( idxIntersection0 );
							vecIntersection1.push_back( idxIntersection1 );
						}
					}

					if ( 2 != vecIntersection0.size() || 2 != vecIntersection1.size() ) throw "the face intersection point number isn't equal 2.";

					vecLineIntersection0.push_back(std::make_pair(vecIntersection0.at(0), vecIntersection0.at(1)));
					vecLineIntersection1.push_back(std::make_pair(vecIntersection1.at(0), vecIntersection1.at(1)));

					std::sort( vecIntersection0.begin(), vecIntersection0.end() );
					std::sort( vecIntersection1.begin(), vecIntersection1.end() );

					setLines0 << qMakePair( vecIntersection0.at( 0 ), vecIntersection0.at( 1 ) );
					setLines1 << qMakePair( vecIntersection1.at( 0 ), vecIntersection1.at( 1 ) );

					if ( vecFaceIndices0.size() > 5 || vecFaceIndices1.size() > 5 ) throw "intersection part have more than 5 edges.";

					if ( 4 == vecFaceIndices0.size() || 5 == vecFaceIndices0.size() ) NXMath3D::TriangleStrips(vecFaceIndices0);
					if ( 4 == vecFaceIndices1.size() || 5 == vecFaceIndices1.size() ) NXMath3D::TriangleStrips(vecFaceIndices1);
					
					vecFaces0.push_back(vecFaceIndices0);
					vecFaces1.push_back(vecFaceIndices1);
				}	
			}

			// Lines Indices
			foreach (auto pair, setLines0)
			{
				vecLineIndices0.push_back(pair.first);
				vecLineIndices0.push_back(pair.second);
			}

			foreach (auto pair, setLines1)
			{
				vecLineIndices1.push_back(pair.first);
				vecLineIndices1.push_back(pair.second);
			}

			// Intersection Face Indices
			vector<unsigned> vecFaceIntersectionIndices0;
			vector<unsigned> vecFaceIntersectionIndices1;

			_CheckIntersectionFaceClosure(vecLineIntersection0, vecFaceIntersectionIndices0);
			_CheckIntersectionFaceClosure(vecLineIntersection1, vecFaceIntersectionIndices1);

			if ( vecFaceIntersectionIndices0.size() > 6 || vecFaceIntersectionIndices1.size() > 6 ) throw "intersection face have more than 6 edges.";

			if ( vecFaceIntersectionIndices0.size() > 3 ) NXMath3D::TriangleStrips( vecFaceIntersectionIndices0 );
			if ( vecFaceIntersectionIndices1.size() > 3 ) NXMath3D::TriangleStrips( vecFaceIntersectionIndices1 );

			vecFaces0.push_back(vecFaceIntersectionIndices0);
			vecFaces1.push_back(vecFaceIntersectionIndices1);

			/*os << "0 vertices num: " << nVertex0 << "\n";
			os << "1 vertices num: " << nVertex1 << "\n";
			os << "0 face indices: ";
			std::ostream_iterator<unsigned> out_iter(os, ", ");
			std::for_each(vecFaces0.cbegin(), vecFaces0.cend(), [&out_iter, &os](const std::vector<unsigned>& vec)
			{
				std::copy(vec.cbegin(), vec.cend(), out_iter);
				os << "\n";
			});
			os << "1 face indices: ";
			std::for_each(vecFaces1.cbegin(), vecFaces1.cend(), [&out_iter, &os](const std::vector<unsigned>& vec)
			{
				std::copy(vec.cbegin(), vec.cend(), out_iter);
				os << "\n";
			});
			os << "\n";*/

			// Dimension
			pIntersectedCell0->GetBoundingBox(pMin[0], pMax[0], pMin[1], pMax[1], pMin[2], pMax[2]);
			funcCellDimension(dXMin0, dXMax0, dYMin0, dYMax0, dZMin0, dZMax0);
			
			pIntersectedCell1->GetBoundingBox(pMin[0], pMax[0], pMin[1], pMax[1], pMin[2], pMax[2]);
			funcCellDimension(dXMin1, dXMax1, dYMin1, dYMax1, dZMin1, dZMax1);

			// result
			m_vecOutput[0]->GetIntersectedCells() << pIntersectedCell0;
			m_vecOutput[1]->GetIntersectedCells() << pIntersectedCell1;
		}
	}

	m_vecOutput[0]->SetDimension(dXMin0, dXMax0, dYMin0, dYMax0, dZMin0, dZMax0);
	m_vecOutput[1]->SetDimension(dXMin1, dXMax1, dYMin1, dYMax1, dZMin1, dZMax1);

	return true;
}

