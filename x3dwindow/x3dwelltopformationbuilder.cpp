#include "x3dwelltopformationbuilder.h"

#include <cassert>

#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osg/Shape>

#include "x3dbuilderfactory.h"
#include "x3dwindow.h"
#include "xglobal.h"
#include "x3dpoints.h"
#include "xwelltopformation.h"
#include "x3dglobalcoordmap.h"
#include "xviewinfo3dwelltopformation.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DWellTopFormationBuilder)
{EXWellTopFormation,e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CX3DWellTopFormationBuilder)

CX3DWellTopFormationBuilder::CX3DWellTopFormationBuilder()
: CX3DBuilderAbstract(), m_fZScale(1), m_curMode(CXViewInfo3DWellTopFormation::WT_SPHERE)
{
	m_bScalable = false;
}

osg::ref_ptr<osg::Group> CX3DWellTopFormationBuilder::Build(QUuid objId)
{
	///> Brief Get ZScale's value
	m_pOSGWindow = dynamic_cast<CX3DWindow*>(m_pCurWin);
	assert(m_pOSGWindow);
	m_fZScale = static_cast<float>(m_pOSGWindow->GetZScale());

	///> Brief Get point's coordinate array.
	m_pWellTopFormation = dynamic_cast<CXWellTopFormation*>(::GetObjectByID(objId));
	if (m_pWellTopFormation == nullptr) return nullptr; 

	CX3DPoints *pPoint = m_pWellTopFormation->GetAllPoints();
	if (pPoint == nullptr) return nullptr;

	unsigned int nCoord = 0;
	double* pDPoint = pPoint->GetData(nCoord);
	if (pDPoint == nullptr || nCoord == 0) return nullptr;

	///> Brief Get view info
	m_pViewInfo = dynamic_cast<CXViewInfo3DWellTopFormation*>(m_pCurWin->GetObjectViewInfo(objId));
	m_curMode = m_pViewInfo->GetDisplayMode();
	float fRadius = m_pViewInfo->GetRadius() * 5;
	QColor colorFmt = m_pViewInfo->GetWellTopFormationColor();

	///> Brief Build LOD
	m_pLOD = new osg::LOD;
	m_pLOD->setRangeMode(osg::LOD::DISTANCE_FROM_EYE_POINT);
	
	// Build Sphere/DISK/CUBE.
	osg::ref_ptr<osg::Geode> pGeodeSubtle = new osg::Geode;
	osg::ref_ptr<osg::Geode> pGeodeRough = new osg::Geode;
	m_pVecPosition = new osg::Vec3Array();
	for (unsigned i=0; i!=nCoord; i+=3)
	{
		// Translate the world coordinate to local coordinate.
		osg::Vec3 vecLocal;
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(pDPoint[i], pDPoint[i+1], pDPoint[i+2]), vecLocal);
		vecLocal.z() *= m_fZScale;
		m_pVecPosition->push_back(vecLocal);

		// Switch shapes.
		osg::ref_ptr<osg::Shape> pShape;
		switch (m_curMode)
		{
		case CXViewInfo3DWellTopFormation::WT_SPHERE:
			pShape = new osg::Sphere(vecLocal, fRadius);
			break;
		case CXViewInfo3DWellTopFormation::WT_DISK:
			pShape = new osg::Cylinder(vecLocal, fRadius, 1.f);
			break;
		case CXViewInfo3DWellTopFormation::WT_CUBE:
			pShape = new osg::Box(vecLocal, fRadius);
			break;
		default:assert(!"Error mode");
		}

		osg::ref_ptr<osg::TessellationHints> pHintsSubtle = new osg::TessellationHints;
		osg::ref_ptr<osg::TessellationHints> pHintsRough = new osg::TessellationHints;
		pHintsSubtle->setDetailRatio(1.f);
		pHintsRough->setDetailRatio(.5f);

		osg::ref_ptr<osg::ShapeDrawable> pDrawableSubtle = new osg::ShapeDrawable(pShape.get(), pHintsSubtle.get());
		pDrawableSubtle->setColor(osg::Vec4(colorFmt.redF(), colorFmt.greenF(), colorFmt.blueF(), 1.f));

		osg::ref_ptr<osg::ShapeDrawable> pDrawableRough = new osg::ShapeDrawable(pShape.get(), pHintsRough.get());
		pDrawableRough->setColor(osg::Vec4(colorFmt.redF(), colorFmt.greenF(), colorFmt.blueF(), 1.f));

		pGeodeSubtle->addDrawable(pDrawableSubtle.get());
		pGeodeRough->addDrawable(pDrawableRough.get());
	}
	m_pLOD->addChild(pGeodeSubtle.get(), 0, 10000);
	m_pLOD->addChild(pGeodeRough.get(), 10000, FLT_MAX);

	delete pPoint;

	return m_pLOD;
}

void CX3DWellTopFormationBuilder::UpdateNode(EEventType eType)
{
	osg::Geode *pGeodeSubtle = m_pLOD->getChild(0)->asGeode();
	osg::Geode *pGeodeRough = m_pLOD->getChild(1)->asGeode();

	if (!pGeodeSubtle || !pGeodeRough) return;

	if (eType == EDataChanged)
	{
		float fZScale = m_pOSGWindow->GetZScale();

		for(unsigned int i=0; i<pGeodeSubtle->getNumDrawables(); ++i)
		{
			(*m_pVecPosition)[i]._v[2] = (*m_pVecPosition)[i]._v[2]/m_fZScale*fZScale;
			
			switch(m_curMode)
			{
			case CXViewInfo3DWellTopFormation::WT_SPHERE:
				dynamic_cast<osg::Sphere*>(pGeodeSubtle->getDrawable(i)->getShape())->setCenter(m_pVecPosition->at(i));
				dynamic_cast<osg::Sphere*>(pGeodeRough->getDrawable(i)->getShape())->setCenter(m_pVecPosition->at(i));
				break;
			case CXViewInfo3DWellTopFormation::WT_DISK:
				dynamic_cast<osg::Cylinder*>(pGeodeSubtle->getDrawable(i)->getShape())->setCenter(m_pVecPosition->at(i));
				dynamic_cast<osg::Cylinder*>(pGeodeRough->getDrawable(i)->getShape())->setCenter(m_pVecPosition->at(i));
				break;
			case CXViewInfo3DWellTopFormation::WT_CUBE:
				dynamic_cast<osg::Box*>(pGeodeSubtle->getDrawable(i)->getShape())->setCenter(m_pVecPosition->at(i));
				dynamic_cast<osg::Box*>(pGeodeRough->getDrawable(i)->getShape())->setCenter(m_pVecPosition->at(i));
				break;
			}
		}

		m_fZScale = fZScale;
	}
	else if (eType == EInfoChanged)
	{
		float fRadius = m_pViewInfo->GetRadius() * 5;
		m_curMode = m_pViewInfo->GetDisplayMode();
		QColor colorFmt = m_pViewInfo->GetWellTopFormationColor();

		// Subtle and rough have same drawable number.
		for (unsigned i=0; i!=pGeodeSubtle->getNumDrawables(); ++i)
		{
			// Switch shapes.
			osg::ref_ptr<osg::Shape> pShape;
			switch (m_curMode)
			{
			case CXViewInfo3DWellTopFormation::WT_SPHERE:
				pShape = new osg::Sphere(m_pVecPosition->at(i), fRadius);
				break;
			case CXViewInfo3DWellTopFormation::WT_DISK:
				pShape = new osg::Cylinder(m_pVecPosition->at(i), fRadius, 1.f);
				break;
			case CXViewInfo3DWellTopFormation::WT_CUBE:
				pShape = new osg::Box(m_pVecPosition->at(i), fRadius);
				break;
			default:assert(!"Error mode");
			}

			osg::ref_ptr<osg::TessellationHints> pHintsSubtle = new osg::TessellationHints;
			osg::ref_ptr<osg::TessellationHints> pHintsRough = new osg::TessellationHints;
			pHintsSubtle->setDetailRatio(1.f);
			pHintsRough->setDetailRatio(.5f);

			osg::ref_ptr<osg::ShapeDrawable> pDrawableSubtle = new osg::ShapeDrawable(pShape.get(), pHintsSubtle.get());
			pDrawableSubtle->setColor(osg::Vec4(colorFmt.redF(), colorFmt.greenF(), colorFmt.blueF(), 1.f));

			osg::ref_ptr<osg::ShapeDrawable> pDrawableRough = new osg::ShapeDrawable(pShape.get(), pHintsRough.get());
			pDrawableRough->setColor(osg::Vec4(colorFmt.redF(), colorFmt.greenF(), colorFmt.blueF(), 1.f));

			pGeodeSubtle->setDrawable(i, pDrawableSubtle.get());
			pGeodeRough->setDrawable(i, pDrawableRough.get());
		}

		m_pLOD->setChild(0, pGeodeSubtle);
		m_pLOD->setChild(1, pGeodeRough);
	}
}
