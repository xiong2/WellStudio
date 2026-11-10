#ifndef _CXViewInfoObject_H__
#define _CXViewInfoObject_H__

#include "xdata_global.h"
#include <qcolor.h>
#include <quuid.h>
#include <qstring.h>
#include "xio.h"
#include "xbaseparameter.h"

class XDATA_EXPORT CXViewInfoObject : public CXBaseParameter
{
public:
	CXViewInfoObject();

	CXViewInfoObject(const CXViewInfoObject& other);

	CXViewInfoObject& operator=(const CXViewInfoObject&);

	///@breif Set object ID
	virtual void SetViewObjectID(const QUuid& objID);

	///@brief Set attribute object ID
	X_PROPERTY(QUuid, AttributeObjID)

	///@brief Log scale
	X_PROPERTY(bool, BLogScale)

	///@breif color
	X_PROPERTY(QColor, Color)

	///@brief Visibility
	X_PROPERTY(bool, Visible)

	///@brief Colormap name
	X_PROPERTY(QString, ColormapName)

	///@brief display data min and data max 
	X_PROPERTY(bool, BAutoCalcRange)
	X_PROPERTY(double, DisplayDataMin)
	X_PROPERTY(double, DisplayDataMax)
	X_PROPERTY(bool, BZeroIsInvalid)

	///@brief need display with colormap
	X_PROPERTY(bool, NeedColormap)

	virtual void SerializeTemplate(QDataStream&, bool bSave);

	///@brief Apply some of other view info into current one
	virtual bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo);

	void CheckColormapNameValid();
};

#endif