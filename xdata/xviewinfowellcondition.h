#ifndef XWELLCONDITIONVIEWINFO_H
#define XWELLCONDITIONVIEWINFO_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

//!@brief	View info of well condition
//!@author	Pezy
//!@date	Feb. 3, 2015
//!@see		CXWindow
//!@see		CXWellConditionVisPage
//!@see		CX3DWellConditionBuilder

class XDATA_EXPORT CXViewInfoWellCondition : public CXViewInfoObject
{
public:
	CXViewInfoWellCondition();
	
	///@brief Set object ID
	virtual void SetViewObjectID(const QUuid& objID);

	///@brief Gird line
	X_PROPERTY(bool, DisplayLine)
	X_PROPERTY(QColor, LineColor)

	///@brief Geometry
	X_PROPERTY(QColor, GeomColor)

	///@brief Well list
	X_PROPERTY(std::vector<QUuid>, WellList)
	X_PROPERTY(std::vector<int>, WellVisibleList)
};

#endif // RLWELLCONDITIONVIEWINFO_H
