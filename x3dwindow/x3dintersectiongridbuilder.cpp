#include "x3dintersectiongridbuilder.h"

#include <cassert>

#include <osg/Geometry>
#include <osg/LineWidth>

#include "x3dbuilderfactory.h"
#include "xintersectiongrid.h"
#include "xintersectedgridcell.h"
#include "xglobal.h"
#include "xviewinfo3dgridmodel.h"
#include "xgridcell.h"
#include "x3dglobalcoordmap.h"
#include "x3dwindow.h"
#include "x3dgridmodelbuilder.h"
#include "xpropertymodel.h"
#include "xgridmodel.h"
#include "xcolormap.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DIntersectionGridBuilder)
{EXIntersectionGrid, e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CX3DIntersectionGridBuilder)

CX3DIntersectionGridBuilder::CX3DIntersectionGridBuilder() : 
	m_pViewInfo( nullptr ),
	m_pGrid( nullptr ), 
	m_pVecCompleteIJK( nullptr ), 
	m_pCompleteCellGeom( nullptr ), 
	m_pCompleteGridGeom( nullptr ), 
	m_pCompleteVertices( nullptr ), 
	m_pVecIntersectedIJK( nullptr ), 
	m_pIntersectedVertices( nullptr ),
	m_pIntersectedGridGeom( nullptr )
{
}

CX3DIntersectionGridBuilder::~CX3DIntersectionGridBuilder()
{
	// remove the Toolbar of gridmodel
	CX3DWindow* pWin = dynamic_cast<CX3DWindow*>(m_pCurWin);
	pWin->SetGridModelControl(false);
}

osg::ref_ptr<osg::Group> CX3DIntersectionGridBuilder::Build(QUuid objId)
{
	// add the Toolbar of intersection grid
	m_pOSGWindow = dynamic_cast<CX3DWindow*>( m_pCurWin );
	m_pOSGWindow->SetGridModelControl( true );

	if ( m_pBuilderNode == nullptr )
		m_pBuilderNode = new osg::Group;

	// Get object
	m_pGrid = dynamic_cast<CXIntersectionGrid*>( ::GetObjectByID( objId ) );
	if ( !m_pGrid )
		return nullptr;

	// Get viewinfo
	m_pViewInfo = dynamic_cast<CXViewInfo3DGridModel*>( m_pCurWin->GetObjectViewInfo( objId ) );
	if ( !m_pViewInfo )
		return nullptr;

	m_pCompleteCellGeom = new osg::Geometry;
	m_pCompleteCellGeom->setName( "Intersected grid complete cells" );
	m_pCompleteCellGeom->setUseVertexBufferObjects( true );

	m_pCompleteGridGeom = new osg::Geometry;
	m_pCompleteGridGeom->setName( "Intersected grid border line" );
	m_pCompleteGridGeom->setUseVertexBufferObjects( true );

	m_pIntersectedCellGeom = new osg::Geometry;
	m_pIntersectedCellGeom->setName("Intersected grid intersected cells");
	m_pIntersectedCellGeom->setUseVertexBufferObjects(true);

	m_pIntersectedGridGeom = new osg::Geometry;
	m_pIntersectedGridGeom->setName("Intersected grid border line");
	m_pIntersectedGridGeom->setUseVertexBufferObjects(true);

	_CalcCompleteVertices();
	_CalcCompleteIndices( true );
	_CalcCompleteNormal();

	_CalcIntersectionVertices();
	_CalcIntersectionIndices( true );
	_CalcIntersectionNormal();

	_CalcColor();

	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	pGeode->setName( m_pGrid->GetObjectName().toLatin1().data() );
	pGeode->addDrawable( m_pCompleteCellGeom.get() );
	pGeode->addDrawable( m_pCompleteGridGeom.get() );
	pGeode->addDrawable( m_pIntersectedCellGeom.get() );
	pGeode->addDrawable( m_pIntersectedGridGeom.get() );
	m_pBuilderNode->addChild( pGeode.get() );

	return m_pBuilderNode.get();
}

void CX3DIntersectionGridBuilder::UpdateNode(EEventType eType)
{
	if (eType == EInfoChanged || eType == EColormapChanged)
	{
		_CalcColor();
		_CalcPropertyIndicesAndColor();
	}
}

void CX3DIntersectionGridBuilder::_CalcIntersectionNormal()
{
	osg::ref_ptr<osg::Vec3Array> pNormalize = new osg::Vec3Array;

	for ( auto pIntersectionCell : m_pGrid->GetIntersectedCells() ) // each cell
	{
		const int nVertexNum = pIntersectionCell->GetVertexNum();
		if ( 0 == nVertexNum ) continue;

		const double* pVertex = pIntersectionCell->GetVertex();
		const std::vector<std::vector<unsigned>>& vecFaces = pIntersectionCell->GetFace();
		osg::ref_ptr<osg::Vec3Array> pVecVertex = new osg::Vec3Array( nVertexNum );

		for ( auto j = 0; j != nVertexNum; ++j ) { // each vertex
			osg::Vec3 vecLocelCoord;
			m_pCoordMap->MapWorldToLocal( osg::Vec3d( pVertex[j * 3], pVertex[j * 3 + 1], pVertex[j * 3 + 2] ), vecLocelCoord );
			(*pVecVertex)[j].set( vecLocelCoord );
		}

		for ( auto vecFace : vecFaces)
		{
			if (vecFace.empty()) continue;
			assert( vecFace.size() >= 3 );

			const int iI = vecFace.at( 0 );
			const int iJ = vecFace.at( 1 );
			const int iK = vecFace.at( 2 );

			osg::Vec3 vecFaceNorm = (pVecVertex->at( iJ ) - pVecVertex->at( iI )) ^ (pVecVertex->at( iK ) - pVecVertex->at( iI ));
			vecFaceNorm.normalize();

			pNormalize->push_back(vecFaceNorm);
		}

		//const int nVertexNum = pIntersectionCell->GetVertexNum();
		//if ( 0 == nVertexNum ) continue;

		//const double* pVertex = pIntersectionCell->GetVertex();
		//const std::vector<std::vector<unsigned>>& vecFaces = pIntersectionCell->GetFace();
		//osg::ref_ptr<osg::Vec3Array> pVecVertex = new osg::Vec3Array( nVertexNum );

		//for ( auto j = 0; j != nVertexNum; ++j ) { // each vertex
		//	osg::Vec3 vecLocelCoord;
		//	m_pCoordMap->MapWorldToLocal( osg::Vec3d( pVertex[j * 3], pVertex[j * 3 + 1], pVertex[j * 3 + 2] ), vecLocelCoord );
		//	(*pVecVertex)[j].set( vecLocelCoord );
		//}

		//QMap<unsigned, osg::Vec3> mapVertex2Normal;
		//QList<unsigned> lstExist;

		//// debug
		////std::ofstream ofs("map.txt", std::ios::app);

		//for ( auto iterFace = vecFaces.cbegin(); iterFace != vecFaces.cend(); ++iterFace ) // each face
		//{
		//	if ( iterFace->empty() ) continue;
		//	assert( iterFace->size() >= 3 );

		//	const int iI = iterFace->at( 0 );
		//	const int iJ = iterFace->at( 1 );
		//	const int iK = iterFace->at( 2 );

		//	osg::Vec3 vecFaceNorm = (pVecVertex->at( iJ ) - pVecVertex->at( iI )) ^ (pVecVertex->at( iK ) - pVecVertex->at( iI ));
		//	vecFaceNorm.normalize();

		//	// match to vertex
		//	if ( std::next( iterFace ) != vecFaces.cend() ) {
		//		auto iMinVertex = UINT_MAX;
		//		foreach (unsigned u, *iterFace) {
		//			if ( lstExist.contains( u ) ) continue;
		//			iMinVertex = qMin( iMinVertex, u );
		//		}
		//		mapVertex2Normal.insert( iMinVertex, vecFaceNorm );
		//		lstExist << iMinVertex;
		//		//ofs << iMinVertex << ": " << std::distance(vecFaces.cbegin(), iterFace) << "\n";
		//	}
		//	else {
		//		foreach(unsigned u, *iterFace) {
		//			mapVertex2Normal[u] = vecFaceNorm;
		//			//ofs << u << ": " << std::distance(vecFaces.cbegin(), iterFace) << "\n";
		//		}
		//	}
		//}

		////ofs << "=====================================\n";

		//for ( size_t i = 0; i != pVecVertex->size(); ++i ) {
		//	pNormalize->push_back( mapVertex2Normal.value( i ) );
		//}
	}

	//m_pIntersectedCellGeom->setNormalArray( pNormalize.get(), osg::Array::BIND_PER_VERTEX );
	m_pIntersectedCellGeom->setNormalArray( pNormalize.get(), osg::Array::BIND_PER_PRIMITIVE_SET );
}

void CX3DIntersectionGridBuilder::_CalcCompleteNormal()
{
	osg::ref_ptr<osg::Vec3Array> pNormalize = new osg::Vec3Array;

	for (int i=0; i<m_pVecCompleteIJK->size(); ++i)
	{
		// Calculate the normal vector, number is the following line index.
		//	     __ __
		// top^	/    /| 
		//    |/_  _/_|
		//	   |    | | 
		//	   |____|/|
		//            v
		//			  below

		osg::Vec3 normal_top = (m_pCompleteVertices->at(8*i+1) - m_pCompleteVertices->at(8*i+0)) ^ (m_pCompleteVertices->at(8*i+3) - m_pCompleteVertices->at(8*i+0));
		osg::Vec3 normal_blw = (m_pCompleteVertices->at(8*i+5) - m_pCompleteVertices->at(8*i+6)) ^ (m_pCompleteVertices->at(8*i+7) - m_pCompleteVertices->at(8*i+6));

		normal_top.normalize();
		normal_blw.normalize();

		// Each Cell have 8 normal vector
		pNormalize->push_back(normal_top);
		pNormalize->push_back(normal_top);
		pNormalize->push_back(normal_top);
		pNormalize->push_back(normal_top);
		pNormalize->push_back(normal_blw);
		pNormalize->push_back(normal_blw);
		pNormalize->push_back(normal_blw);
		pNormalize->push_back(normal_blw);
	}

	m_pCompleteCellGeom->setNormalArray(pNormalize.get(), osg::Array::BIND_PER_VERTEX);
}

void CX3DIntersectionGridBuilder::_CalcIntersectionVertices()
{
	const QList<CXIntersectedGridCell*>& listCells = m_pGrid->GetIntersectedCells();

	m_pIntersectedVertices = new osg::Vec3Array;
	m_pVecIntersectedIJK = new osg::Vec3usArray(listCells.size());

	for (auto i = 0; i != listCells.size(); ++i) { // each cell
		unsigned short usI, usJ, usK;
		listCells.at(i)->GetIJK(usI, usJ, usK);

		(*m_pVecIntersectedIJK)[i]._v[0] = usI;
		(*m_pVecIntersectedIJK)[i]._v[1] = usJ;
		(*m_pVecIntersectedIJK)[i]._v[2] = usK;

		const int nVertexNum = listCells.at(i)->GetVertexNum();
		double *dVertexCoord = listCells.at(i)->GetVertex();

		for (auto j = 0; j != nVertexNum; ++j) { // each vertex
			osg::Vec3 vecLocelCoord;
			m_pCoordMap->MapWorldToLocal( osg::Vec3d( dVertexCoord[j * 3], dVertexCoord[j * 3 + 1], dVertexCoord[j * 3 + 2]), vecLocelCoord );
			m_pIntersectedVertices->push_back( vecLocelCoord );
		}
	}

	m_pIntersectedGridGeom->setVertexArray( m_pIntersectedVertices.get() );
	m_pIntersectedCellGeom->setVertexArray( m_pIntersectedVertices.get() );
}

void CX3DIntersectionGridBuilder::_CalcCompleteVertices()
{
	const QList<CXGridCell*> &listCells = m_pGrid->GetAllCells();

	m_pCompleteVertices = new osg::Vec3Array;
	m_pVecCompleteIJK = new osg::Vec3usArray( listCells.size() );

	for ( int i = 0; i != listCells.size(); ++i ) {
		unsigned short usI, usJ, usK;
		listCells[i]->GetIJK( usI, usJ, usK );

		(*m_pVecCompleteIJK)[i]._v[0] = usI;
		(*m_pVecCompleteIJK)[i]._v[1] = usJ;
		(*m_pVecCompleteIJK)[i]._v[2] = usK;

		double* d = listCells[i]->GetVertex();

		for ( int j = 0; j < 24; j += 3 ) {
			osg::Vec3 vecLocal;
			m_pCoordMap->MapWorldToLocal( osg::Vec3d( d[j], d[j + 1], d[j + 2] ), vecLocal );
			m_pCompleteVertices->push_back( vecLocal );
		}
	}

	m_pCompleteCellGeom->setVertexArray( m_pCompleteVertices.get() );
	m_pCompleteGridGeom->setVertexArray( m_pCompleteVertices.get() );
}

void CX3DIntersectionGridBuilder::_CalcColor()
{
	QColor geomColor = m_pViewInfo->GetGeomColor();
	QColor lineColor = m_pViewInfo->GetLineColor();

	// Geometry
	osg::ref_ptr<osg::Vec4Array> pGeomColor = new osg::Vec4Array(1);
	(*pGeomColor)[0].set(geomColor.redF(), geomColor.greenF(), geomColor.blueF(), geomColor.alphaF());
	m_pCompleteCellGeom->setColorArray(pGeomColor);
	m_pCompleteCellGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
	m_pIntersectedCellGeom->setColorArray(pGeomColor);
	m_pIntersectedCellGeom->setColorBinding(osg::Geometry::BIND_OVERALL);

	// Grid line
	auto funcColoringLine = [lineColor](osg::ref_ptr<osg::Geometry> &rpGeom)
	{
		osg::Vec4Array* pLineColor = dynamic_cast<osg::Vec4Array *>( rpGeom->getColorArray() );
		if ( pLineColor ) {
			osg::Vec4& color = pLineColor->at( 0 );
			color.set( lineColor.redF(), lineColor.greenF(), lineColor.blueF(), lineColor.alphaF() );
		}
		else {
			pLineColor = new osg::Vec4Array( 1 );
			(*pLineColor)[0].set( lineColor.redF(), lineColor.greenF(), lineColor.blueF(), lineColor.alphaF() );
			rpGeom->setColorArray( pLineColor );
			rpGeom->setColorBinding( osg::Geometry::BIND_OVERALL );

			// Grid line width
			rpGeom->getOrCreateStateSet()->setMode( GL_LINE_SMOOTH, osg::StateAttribute::ON );
			osg::LineWidth* linewidth = new osg::LineWidth();
			linewidth->setWidth( 1.0f );
			rpGeom->getOrCreateStateSet()->setAttributeAndModes( linewidth, osg::StateAttribute::ON );
		}
	};

	funcColoringLine(m_pCompleteGridGeom);
	funcColoringLine(m_pIntersectedGridGeom);
}

void CX3DIntersectionGridBuilder::_CalcPropertyIndicesAndColor()
{
	CXPropertyModel *pPropModel = dynamic_cast<CXPropertyModel*>(::GetObjectByID(m_pViewInfo->GetAttributeObjID()));
	if ( nullptr == pPropModel ) {
		_CalcCompleteIndices();
		_CalcIntersectionIndices();
		return;
	}

	unsigned uMinI = m_pViewInfo->GetMinI()-1;
	unsigned uMinJ = m_pViewInfo->GetMinJ()-1;
	unsigned uMinK = m_pViewInfo->GetMinK()-1;
	unsigned uMaxI = m_pViewInfo->GetMaxI()-1;
	unsigned uMaxJ = m_pViewInfo->GetMaxJ()-1;
	unsigned uMaxK = m_pViewInfo->GetMaxK()-1;

	unsigned nNum;
	double *pData = pPropModel->GetData( nNum );
	CXGridModel *pGridModel = dynamic_cast<CXGridModel*>(m_pGrid->GetParent());
	const QList<CXGridCell *>& listGridCell = pGridModel->GetAllCells();
	assert ( pGridModel && nNum == listGridCell.size() );

	QHash<unsigned, double> hashIJK2Value;
	for (auto i = 0; i != nNum; ++i) {
		CXGridCell * const pGridCell = listGridCell.at(i);
		unsigned short usI, usJ, usK;
		pGridCell->GetIJK(usI, usJ, usK);

		if ( ::g_dInvalidData == pData[i] || usK > uMaxK || usK < uMinK || usJ > uMaxJ || usJ < uMinJ || usI > uMaxI || usI < uMinI )
			continue;

		unsigned uKey = usI * 1000000 + usJ * 1000 + usK;
		hashIJK2Value.insert(uKey, pData[i]);
	}
	
	bool bDisplayGrid = m_pViewInfo->GetDisplayLine();

	//
	//	complete cell
	//

	// geometry
	osg::ref_ptr<osg::DrawElementsUInt> pCellCompletePrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	osg::ref_ptr<osg::DrawElementsUInt> pGridCompletePrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);

	// Color
	double dMin = m_pViewInfo->GetDisplayDataMin();
	double dMax = m_pViewInfo->GetDisplayDataMax();
	double dRange = dMax - dMin;
	CXColormap *pColorMap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());

	osg::ref_ptr<osg::Vec4Array> pPropCompleteColor = new osg::Vec4Array(m_pCompleteVertices->size());
	
	for (auto i = 0; i != m_pVecCompleteIJK->size(); ++i)
	{
		const osg::Vec3us &vec = m_pVecCompleteIJK->at(i);
		const unsigned uKey = vec.x() * 1000000 + vec.y() * 1000 + vec.z();

		QColor color = m_pViewInfo->GetGeomColor();

		QHash<unsigned, double>::const_iterator iFound = hashIJK2Value.find( uKey );
		if ( iFound != hashIJK2Value.end() ) {
			// Draw the grid geometry
			for (auto j = 0; j != 24; ++j) {
				pCellCompletePrimitive->push_back( CX3DGridModelBuilder::m_arrayIndex[j] + 8*i);
				if (bDisplayGrid)
					pGridCompletePrimitive->push_back( CX3DGridModelBuilder::m_arrayLines[j] + 8*i);
			}
			// Color
			double dPercent = (iFound.value() - dMin)/dRange;
			color = pColorMap->GetColorAt(255 * dPercent);
		}
		
		for (int j=0; j<8; ++j)
			(*pPropCompleteColor.get())[i*8+j].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	}

	m_pCompleteCellGeom->setPrimitiveSet(0, pCellCompletePrimitive.get());
	m_pCompleteGridGeom->setPrimitiveSet(0, pGridCompletePrimitive.get());
	m_pCompleteCellGeom->setColorArray(pPropCompleteColor.get());
	m_pCompleteCellGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	
	//
	//	intersection cell
	//

	// geometry
	osg::ref_ptr<osg::DrawElementsUInt> pGridIntersectedPrimitive = new osg::DrawElementsUInt( osg::PrimitiveSet::LINES, 0 );
	m_pIntersectedCellGeom->getPrimitiveSetList().clear();
	// color
	osg::ref_ptr<osg::Vec4Array> pPropIntersectedColor = new osg::Vec4Array(m_pCompleteVertices->size());

	const QList<CXIntersectedGridCell*>& listCells = m_pGrid->GetIntersectedCells();
	auto nStartIndex = 0;
	for (auto i = 0; i != listCells.size(); ++i) { // each cell
		const osg::Vec3us& vec = m_pVecIntersectedIJK->at( i );
		const unsigned uKey = vec.x() * 1000000 + vec.y() * 1000 + vec.z();

		QColor color = m_pViewInfo->GetGeomColor();

		QHash<unsigned, double>::const_iterator iFound = hashIJK2Value.find( uKey );
		if ( iFound != hashIJK2Value.end() ) {
			// Geometry
			const std::vector<std::vector<unsigned> > &vecFace = listCells.at(i)->GetFace();
			for ( auto vecFaceIndices : vecFace ) // each face
			{
				if ( vecFaceIndices.empty() ) continue;
				osg::ref_ptr<osg::DrawElementsUInt> pCellPrimitivePtr = new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLE_STRIP, vecFaceIndices.size() );
                std::for_each(vecFaceIndices.begin(), vecFaceIndices.end(), [nStartIndex](unsigned &ui){ ui += nStartIndex; });
                pCellPrimitivePtr->swap( vecFaceIndices );
				m_pIntersectedCellGeom->addPrimitiveSet( pCellPrimitivePtr.get() );
			}
			
			if ( bDisplayGrid ) {
				vector<unsigned> vecLineIndices = listCells.at(i)->GetBorderIndices();
				std::for_each( vecLineIndices.begin(), vecLineIndices.end(), [nStartIndex](unsigned &ui){ ui += nStartIndex; });
				//pGridIntersectedPrimitive->insert(pGridIntersectedPrimitive->end(), vecLineIndices.begin(), vecLineIndices.end());
                std::for_each(vecLineIndices.cbegin(), vecLineIndices.cend(), [pGridIntersectedPrimitive](unsigned ui){ pGridIntersectedPrimitive->push_back(ui);  });
            }	
			// Color
			double dPercent = (iFound.value() - dMin)/dRange;
			color = pColorMap->GetColorAt(255 * dPercent);
		}

		const int nVertexNum = listCells.at(i)->GetVertexNum();

		for (auto j = 0; j != nVertexNum; ++j)
			(*pPropIntersectedColor.get())[nStartIndex + j].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());

		nStartIndex += nVertexNum;
	}

	m_pIntersectedGridGeom->setPrimitiveSet( 0, pGridIntersectedPrimitive.get() );
	m_pIntersectedCellGeom->setColorArray(pPropIntersectedColor.get());
	m_pIntersectedCellGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
}

void CX3DIntersectionGridBuilder::_CalcIntersectionIndices(bool bInit)
{
	unsigned uMinI = m_pViewInfo->GetMinI() - 1;
	unsigned uMinJ = m_pViewInfo->GetMinJ() - 1;
	unsigned uMinK = m_pViewInfo->GetMinK() - 1;
	unsigned uMaxI = m_pViewInfo->GetMaxI() - 1;
	unsigned uMaxJ = m_pViewInfo->GetMaxJ() - 1;
	unsigned uMaxK = m_pViewInfo->GetMaxK() - 1;

	bool bDisplayGrid = m_pViewInfo->GetDisplayLine();

	osg::ref_ptr<osg::DrawElementsUInt> pGridPrimitive = new osg::DrawElementsUInt( osg::PrimitiveSet::LINES, 0 );
	if ( bInit )
		m_pIntersectedGridGeom->addPrimitiveSet( pGridPrimitive.get() );
	else
		m_pIntersectedGridGeom->setPrimitiveSet( 0, pGridPrimitive.get() );

	m_pIntersectedCellGeom->getPrimitiveSetList().clear();

	const QList<CXIntersectedGridCell*>& listCells = m_pGrid->GetIntersectedCells();
	auto nStartIndex = 0;
	for (auto i = 0; i != listCells.size(); ++i) { // each cell
		const osg::Vec3us& vec = m_pVecIntersectedIJK->at( i );

		if ( vec.z() <= uMaxK && vec.z() >= uMinK && vec.y() <= uMaxJ && vec.y() >= uMinJ && vec.x() <= uMaxI && vec.x() >= uMinI ) { // visiable cell
			const std::vector<std::vector<unsigned> > &vecFace = listCells.at(i)->GetFace();
			for ( auto vecFaceIndices : vecFace ) // each face
			{
				if ( vecFaceIndices.empty() ) continue;
				osg::ref_ptr<osg::DrawElementsUInt> pCellPrimitivePtr = new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLE_STRIP, vecFaceIndices.size() );
                std::for_each(vecFaceIndices.begin(), vecFaceIndices.end(), [nStartIndex](unsigned &ui){ ui += nStartIndex; });
                pCellPrimitivePtr->swap( vecFaceIndices );
				m_pIntersectedCellGeom->addPrimitiveSet( pCellPrimitivePtr.get() );
			}
			// if just show intersection face
			/*if ( !vecFace.back().empty()) {
				auto vecFaceIndices = vecFace.back();
				osg::ref_ptr<osg::DrawElementsUInt> pCellPrimitivePtr = new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLE_STRIP, vecFaceIndices.size() );
				pCellPrimitivePtr->swap( vecFaceIndices );
			  	std::for_each( pCellPrimitivePtr->begin(), pCellPrimitivePtr->end(), [nStartIndex](unsigned &ui){ ui += nStartIndex; });
			  	m_pIntersectedCellGeom->addPrimitiveSet( pCellPrimitivePtr.get() );
			}*/
			
			if ( bDisplayGrid ) {
				vector<unsigned> vecLineIndices = listCells.at(i)->GetBorderIndices();
				std::for_each( vecLineIndices.begin(), vecLineIndices.end(), [nStartIndex](unsigned &ui){ ui += nStartIndex; });
				//pGridPrimitive->insert(pGridPrimitive->end(), vecLineIndices.begin(), vecLineIndices.end());
                std::for_each(vecLineIndices.cbegin(), vecLineIndices.cend(), [pGridPrimitive](unsigned ui){ pGridPrimitive->push_back(ui);  });
            }
		}

		const int nVertexNum = listCells.at(i)->GetVertexNum();
		nStartIndex += nVertexNum;
	}
}

void CX3DIntersectionGridBuilder::_CalcCompleteIndices(bool bInit)
{
	unsigned uMinI = m_pViewInfo->GetMinI()-1;
	unsigned uMinJ = m_pViewInfo->GetMinJ()-1;
	unsigned uMinK = m_pViewInfo->GetMinK()-1;
	unsigned uMaxI = m_pViewInfo->GetMaxI()-1;
	unsigned uMaxJ = m_pViewInfo->GetMaxJ()-1;
	unsigned uMaxK = m_pViewInfo->GetMaxK()-1;

	bool bDisplayGrid = m_pViewInfo->GetDisplayLine();

	osg::ref_ptr<osg::DrawElementsUInt> pCellPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	if (bInit)
		m_pCompleteCellGeom->addPrimitiveSet(pCellPrimitive.get());
	else
		m_pCompleteCellGeom->setPrimitiveSet(0, pCellPrimitive.get());

	osg::ref_ptr<osg::DrawElementsUInt> pGridPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
	if (bInit)
		m_pCompleteGridGeom->addPrimitiveSet(pGridPrimitive.get());
	else
		m_pCompleteGridGeom->setPrimitiveSet(0, pGridPrimitive.get());

	for (int i=0; i<m_pVecCompleteIJK->size(); ++i)
	{
		const osg::Vec3us &vec = m_pVecCompleteIJK->at(i);

		if (vec.z() <= uMaxK && vec.z() >= uMinK && vec.y() <= uMaxJ && vec.y() >= uMinJ && vec.x() <= uMaxI && vec.x() >= uMinI)
		{
			// Draw the grid geometry
			for (int j=0; j<24; ++j)
			{
				pCellPrimitive->push_back( CX3DGridModelBuilder::m_arrayIndex[j] + 8*i);
				if (bDisplayGrid)
					pGridPrimitive->push_back( CX3DGridModelBuilder::m_arrayLines[j] + 8*i);
			}
		}
	}
}