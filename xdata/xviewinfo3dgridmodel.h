#ifndef X3DGRIDMODELVIEWINFO_H
#define X3DGRIDMODELVIEWINFO_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

///@brief	View info of grid model
///@author	pezy
///@date	Nov. 27, 2014
///@see		CXWindow (148L)
///			CXSubGridSetting
///			CX3DGridModelBuilder

class XDATA_EXPORT CXViewInfo3DGridModel : public CXViewInfoObject
{
public:
	CXViewInfo3DGridModel();

	///@brief Set object ID
	virtual void SetViewObjectID(const QUuid& objID) override;

	///@brief Sub grid
	X_PROPERTY(unsigned, MinI);
	X_PROPERTY(unsigned, MaxI);
	X_PROPERTY(unsigned, MinJ);
	X_PROPERTY(unsigned, MaxJ);
	X_PROPERTY(unsigned, MinK);
	X_PROPERTY(unsigned, MaxK);

	///@brief Gird line
	X_PROPERTY(bool, DisplayLine);
	X_PROPERTY(QColor, LineColor);

	///@brief Geometry
	X_PROPERTY(QColor, GeomColor);
};

#endif // RL3DGRIDMODELVIEWINFO_H
