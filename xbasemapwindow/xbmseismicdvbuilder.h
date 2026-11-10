#ifndef XBMSEISMICDV_H
#define XBMSEISMICDV_H

/*!
 *	@brief	display of seismic data volume.
 *	@author	pezy
 *	@date	2016-08-01
 *	@see
 */

#include "x3dbuilder.h"
#include "xseismicutmtool.h"
#include <osg/Group>
#include <osg/Geometry>

class CXSeismicDataVolume;
class CXViewInfoSeismicDV;

class CXBMSeismicDVBuilder : public CX3DBuilderAbstract
{
public:
	CXBMSeismicDVBuilder();
	~CXBMSeismicDVBuilder();

	osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;

private:
	osg::Vec3 _IJToLocal(double dI, double dJ, double dZ);

	osg::Geometry* _BuildFoldMapGeometry();
	osg::Geometry* _BuildFrameGeometry();
	void _UpdateFrameInfo();
	void _UpdateFoldMapColormap();
	void _UpdateDVData();

private:
	CXSeismicDataVolume* m_pDV;
	CXViewInfoSeismicDV* m_pViewInfo;
	osg::ref_ptr<osg::Geometry> m_pGeomFoldMap;
	osg::ref_ptr<osg::Geometry> m_pGeomFrame;

	CXSeismicUTMTool m_utm;
	int m_nI;
	int m_nJ;
	double m_dZMin;
	double m_dZMax;
	double m_dZInterval;
};

#endif // KEBMSEISMICDV_H
