#include "xintersectiongrid.h"

#include <QFile>

#include "xobjectfactory.h"
#include "xglobal.h"
#include "xintersectedgridcell.h"
#include "xgridcell.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXIntersectionGrid)
EXIntersectionGrid
END_REGISTER_OBJECT_TO_FACTORY(CXIntersectionGrid)

CXIntersectionGrid::CXIntersectionGrid()
{	
}

CXIntersectionGrid::CXIntersectionGrid(unsigned uI, unsigned uJ, unsigned uK, unsigned uSegment) : CXGridModel(uI, uJ, uK, uSegment)
{
	SetObjectType(EXIntersectionGrid);
	SetIconName("ResPropertyModel.png");
	SetObjectName( "Intersection" );
}

CXIntersectionGrid::~CXIntersectionGrid()
{
	_ClearIntersectedList();
}

QList<CXIntersectedGridCell*>& CXIntersectionGrid::GetIntersectedCells()
{
	if ( m_listCells.empty() || m_listIntersectedCells.empty() )
		LoadData();

	return m_listIntersectedCells;
}

QStringList CXIntersectionGrid::GetDescription()
{
	auto strListDesc = CXGridModel::GetDescription();

	strListDesc << GetTr( "切割网格数目" ) << QString::number( m_listIntersectedCells.size() );
	strListDesc << GetTr( "切割网格比例（%）" ) << QString::number( m_listIntersectedCells.size() * 100 / (m_nK * m_nI * m_nJ) );

	return strListDesc;
}

void CXIntersectionGrid::_WriteData()
{
	if ( m_listCells.empty() || m_listIntersectedCells.empty() )
		return;

	QString strFileName = GetDataFileName();
	QFile file(strFileName);
	if ( !file.open(QIODevice::WriteOnly) ) 
		return;

	QDataStream dsOut(&file);

	//
	//	complete part
	//
	// cell number
	dsOut << m_listCells.size();

	for (CXGridCell* pCell : m_listCells)
	{
		// i, j, k, segment
		unsigned short usI, usJ, usK;
		pCell->GetIJK(usI, usJ, usK);
		dsOut << usI << usJ << usK;
		dsOut << pCell->GetSegment();

		// vertex
		double *pVertex = pCell->GetVertex();
		for (auto i = 0; i != 24; ++i)
			dsOut << pVertex[i];
	}
	
	// 
	//	intersection part
	//
	// cell number
	dsOut << m_listIntersectedCells.size();

	for (CXIntersectedGridCell* pIntersectedCell : m_listIntersectedCells) // each cell
	{
		// i, j, k, segment
		unsigned short usI, usJ, usK;
		pIntersectedCell->GetIJK(usI, usJ, usK);
		dsOut << usI << usJ << usK;
		dsOut << pIntersectedCell->GetSegmentIndex();

		// vertex
		int nVertex =  pIntersectedCell->GetVertexNum();
		dsOut << nVertex;
		double *pVertex = pIntersectedCell->GetVertex();
		for (auto i = 0; i != nVertex; ++i)
			dsOut << pVertex[i * 3] << pVertex[i * 3 + 1] << pVertex[i * 3 + 2];

		// face
		const std::vector<std::vector<unsigned> >& vecFace = pIntersectedCell->GetFace();
		dsOut << (unsigned int)vecFace.size();
		for (const auto& vecIndices : vecFace)
		{
			dsOut << (unsigned int)vecIndices.size();
			for (auto index : vecIndices)
				dsOut << index;
		}

		// border
		const std::vector<unsigned>& vecBorder = pIntersectedCell->GetBorderIndices();
		dsOut << (unsigned int)vecBorder.size();
		for (auto index : vecBorder)
			dsOut << index;
	}
}

void CXIntersectionGrid::_ReadData()
{
	if ( m_nValidCells == 0 )
		return;

	QString strFileName = GetDataFileName();
	QFile file( strFileName );
	if ( !file.open( QIODevice::ReadOnly ) )
		return;

    _FreeMemory();

	QDataStream dsIn( &file );

	//
	//	Complete part
	//
	int nCompleteCell;
	dsIn >> nCompleteCell;

	for (auto i = 0; i != nCompleteCell; ++i) {
		// i, j, k, segment
		unsigned short usI, usJ, usK;
		dsIn >> usI >> usJ >> usK;
		unsigned char ucSegment;
		dsIn >> ucSegment;
		
		auto pGridCell = new CXGridCell(usI, usJ, usK, ucSegment);

		double *pVertex = pGridCell->GetVertex();
		for (auto j = 0; j != 24; ++j) 
			dsIn >> pVertex[j];

		m_listCells.push_back( pGridCell );
	}

	//
	//	Intersection part
	//

	int nCell;
	dsIn >> nCell;

	for ( auto i = 0; i != nCell; ++i ) {
		// i, j, k, segment
		unsigned short usI, usJ, usK;
		dsIn >> usI >> usJ >> usK;
		unsigned char ucSegment;
		dsIn >> ucSegment;

		CXIntersectedGridCell* pCell = new CXIntersectedGridCell( usI, usJ, usK, ucSegment );

		// vertex
		int& nVertex = pCell->GetVertexNum();
		double* pVertex = pCell->GetVertex();
		dsIn >> nVertex;
		for ( auto j = 0; j != nVertex; ++j )
			dsIn >> pVertex[j * 3] >> pVertex[j * 3 + 1] >> pVertex[j * 3 + 2];

		// face
		unsigned int nFace;
		dsIn >> nFace;
		for ( unsigned int j = 0; j != nFace; ++j ) {
			unsigned int nIndices;
			dsIn >> nIndices;
			std::vector<unsigned> vecIndices( nIndices );
			for ( unsigned int k = 0; k != vecIndices.size(); ++k )
				dsIn >> vecIndices.at( k );
			pCell->GetFace().push_back( vecIndices );
		}

		// border
		unsigned int nBorderIndices;
		dsIn >> nBorderIndices;
		for ( unsigned int j = 0; j != nBorderIndices; ++j ) {
			unsigned index;
			dsIn >> index;
			pCell->GetBorderIndices().push_back( index );
		}

		m_listIntersectedCells.push_back( pCell );
	}
}

void CXIntersectionGrid::_ClearIntersectedList()
{
	if ( m_listIntersectedCells.empty() )
		return;

	foreach (auto pIntersectedCell, m_listIntersectedCells)
		delete pIntersectedCell;

	m_listIntersectedCells.clear();
}

void CXIntersectionGrid::_ClearCompleteList()
{
	if ( m_listCells.empty() )
		return;

	foreach (auto pCell, m_listCells)
		delete pCell;

	m_listCells.clear();
}

void CXIntersectionGrid::_FreeMemory()
{
	_ClearCompleteList();
	_ClearIntersectedList();
}
