#ifndef X3DPICKABLEBUILDERABSTRACT_H
#define X3DPICKABLEBUILDERABSTRACT_H

#include "x3dbuilder.h"
#include "x3dwindow_global.h"

/*!
*	@breif	abstract class for pickable 3D builder.
*	@author	pezy
*	@date	2016-07-08
*	@see
*/

class X3DWINDOW_EXPORT CX3DPickableBuilderAbstract : public CX3DBuilderAbstract
{
public:
	CX3DPickableBuilderAbstract();
	virtual ~CX3DPickableBuilderAbstract();
	virtual bool SetActive(bool bActive) = 0;
	virtual osg::ref_ptr<osg::Vec3Array> GetVertex() const { return nullptr; }
};

#endif // KE3DPICKABLEBUILDERABSTRACT_H
