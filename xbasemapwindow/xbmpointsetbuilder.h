#ifndef XBMPOINTSETBUILDER_H
#define XBMPOINTSETBUILDER_H

/*!
*	@brief	display of point set in basemap
*	@author	pezy
*	@date	2016-05-26
*	@see
*/

#include "x3dbuilder.h"

namespace osg { class Geometry; }
class CXViewInfo3DPoints;

class CXBMPointSetBuilder : public CX3DBuilderAbstract
{
public:
	CXBMPointSetBuilder();
	~CXBMPointSetBuilder();

	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;

private:
	CXViewInfo3DPoints* m_pViewInfo = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeometry;
};

#endif // KEBMPOINTSETBUILDER_H
