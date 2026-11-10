#ifndef XBMRANDOMSECTIONBUILDER_H
#define XBMRANDOMSECTIONBUILDER_H

/*!
 *	@brief	display of seismic random section line
 *	@author	pezy
 *	@date	2016-07-21
 *	@see
 */

#include "x3dpickablebuilder.h"
#include <osg/Geode>
#include <osg/Geometry>

class CXSeismicRandomSection;
class CXViewInfoRandomSection;

class CXBMRandomSectionBuilder : public CX3DPickableBuilderAbstract
{
public:
	CXBMRandomSectionBuilder();
	~CXBMRandomSectionBuilder();

	osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;
	bool SetActive(bool bActive) override;

	osg::ref_ptr<osg::Vec3Array> GetVertex() const override { return m_pVertex; }
	osg::ref_ptr<osg::Vec4Array> GetPickedColor() const;

private:
	osg::Geometry* _BuildRandomSectionLine();
	osg::Vec3Array* _BuildRandomSectionVertex();

	void _UpdateViewInfo(bool bPicked);

private:
	CXSeismicRandomSection* m_pRandomSection;
	CXViewInfoRandomSection* m_pViewInfo;

	osg::ref_ptr<osg::Geode> m_pGeode;
	osg::ref_ptr<osg::Geometry> m_pGeom;
	osg::ref_ptr<osg::Vec3Array> m_pVertex;
};

#endif // KEBMRANDOMSECTIONBUILDER_H
