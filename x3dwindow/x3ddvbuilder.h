#ifndef CRL3DDATAVOLUMEBUILDER_H
#define CRL3DDATAVOLUMEBUILDER_H

/*!
 *	@brief	display of seismic 3D data volume.
 *	@author	pezy
 *	@date	2016-06-14
 *	@see
 */

#include "x3dwindow_global.h"
#include "x3dbuilder.h"
#include <osg/ref_ptr>

namespace osg { class Group; class Geometry; };
class CXSeismicDataVolume;
class CXViewInfoSeismicDV;

class X3DWINDOW_EXPORT CX3DDataVolumeBuilder : public CX3DBuilderAbstract
{
public:
	CX3DDataVolumeBuilder();
	~CX3DDataVolumeBuilder();

	osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;
	
private:
	osg::Geometry* _BuildGeometry();
	osg::Vec3 _LineToLocal(int iInline, int iXline, double dZ);
	void _UpdateGeometry();

private:
	osg::ref_ptr<osg::Geometry> m_pGeom;
	CXSeismicDataVolume* m_pDV = nullptr;
	CXViewInfoSeismicDV* m_pViewInfo = nullptr;
};

#endif // CRL3DDATAVOLUMEBUILDER_H