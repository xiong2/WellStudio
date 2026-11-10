#ifndef XPICKCALLBACK_H
#define XPICKCALLBACK_H

/*!
 *	@brief	process cull callback on 3D window.
 *	@author	pezy
 *	@date	2016-10-19
 *	@see
 */

#include <osg/NodeCallback>
#include <osg/NodeVisitor>
#include <osg/Node>
class CX3DPickableBuilderAbstract;

class CXPickCallback : public osg::NodeCallback
{
public:
	CXPickCallback(CX3DPickableBuilderAbstract* pBuilder);
	~CXPickCallback();

	void operator()(osg::Node* node, osg::NodeVisitor* nv) override;

	void SetActive(bool bActive);

private:
	CX3DPickableBuilderAbstract* m_pBuilder;
};

#endif // KEPICKCALLBACK_H