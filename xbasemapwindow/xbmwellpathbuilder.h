#ifndef XBMWELLPATHBUILDER_H
#define XBMWELLPATHBUILDER_H

/*!
 *	@brief	display of wellpath.
 *	@author	pezy
 *	@date	2016-03-21
 *	@see
 */

#include "x3dbuilder.h"

namespace osg { class AutoTransform; };
namespace osgText { class Text; };

class CXViewInfoWellPath;

class CXBMWellPathBuilder : public CX3DBuilderAbstract
{
public:
	CXBMWellPathBuilder();
	~CXBMWellPathBuilder();

	osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;

private:
	osg::Geode* _BuildWellPath();
	osg::Node* _BuildWellSymbol();

	osg::Geometry* _BuildSymbolGeometry();
	osgText::Text* _BuildLabelGeometry(const std::string& wellName);

	bool _UpdateLatestWellData();
	bool _UpdateLatestWellPathData();

	void _UpdateWellInfo();

private:
	std::string m_wellName;
	osg::Vec3 m_vecWellPos;
	osg::ref_ptr<osg::Vec3Array> m_pWellPathVertex;
	CXViewInfoWellPath* m_pViewInfo = nullptr;

	osg::ref_ptr<osg::AutoTransform> m_pWellSymbolAutoTransform;
	osg::ref_ptr<osgText::Text> m_pWellNameLegend;
	osg::ref_ptr<osg::Geode> m_pSymbolNode;
	osg::ref_ptr<osg::Geometry> m_pWellSymbolGeom;
	osg::ref_ptr<osg::Geode> m_pWellPathNode;
};

#endif // KEBMWELLPATHBUILDER_H
