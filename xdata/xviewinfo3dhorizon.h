#ifndef XVIEWINFO3DHORIZON_H
#define XVIEWINFO3DHORIZON_H

#include "xdata_global.h"
#include "xviewinfoobject.h"

/*!
 *	@brief	The class provides data structure for view info of 3-D Horizon
 *	@author	pezy
 *	@date	2016-05-04
 *	@see	
 */

class XDATA_EXPORT CXViewInfo3DHorizon : public CXViewInfoObject
{
public:
	CXViewInfo3DHorizon();
	~CXViewInfo3DHorizon();

	///@brief Set object ID
	virtual void SetViewObjectID(const QUuid& objID);
	///@brief For Apply-all
	virtual bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo);

	///@brief For section window.
	X_PROPERTY(bool, SectionLineUseObjColor);
	X_PROPERTY(QColor, SectionLineColor);
	X_PROPERTY(int, SectionLineWidth);

	X_PROPERTY(bool, SectionAnnotationUseObjColor);
	X_PROPERTY(QColor, SectionAnnotationColor);
	X_PROPERTY(QColor, SectionAnnotationBackgroundColor);
	X_PROPERTY(int, SectionAnnotationSize);

	X_PROPERTY(int, SectionIntersectionPointSize);

	X_PROPERTY(bool, SectionAnnotationLeftVisible);
	X_PROPERTY(bool, SectionAnnotationRightVisible);
	X_PROPERTY(bool, SectionAnnotationBackgroundVisible);

private:
	
};

#endif // KEVIEWINFO3DHORIZON_H
