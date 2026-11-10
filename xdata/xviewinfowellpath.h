#ifndef XWELLPATHVIEWINFO_H_H
#define XWELLPATHVIEWINFO_H_H 

#include <QString>
#include "xdata_global.h"
#include "xviewinfoobject.h"

class XDATA_EXPORT CXViewInfoWellPath :public CXViewInfoObject
{
public:
	CXViewInfoWellPath();
	~CXViewInfoWellPath();

	///@breif Set object ID
	virtual void SetViewObjectID(const QUuid& objID);

	///@brief well name
	X_PROPERTY(bool, WellNameVisible);
	X_PROPERTY(QColor, WellNameColor);
	X_PROPERTY(bool, WellNameUseObjColor);
	X_PROPERTY(int, WellNameFontSize);
	X_PROPERTY(QString, WellNameFontFamily);
	X_PROPERTY(int, WellNamePosition);

	///@brief wellpath
	X_PROPERTY(bool, WellPathVisible);
	X_PROPERTY(QColor, WellPathColor);
	X_PROPERTY(bool, WellPathUseObjColor);
	X_PROPERTY(int, WellPathRadius);

	///@brief well symbol
    X_PROPERTY(bool, WellSymbolVisible);
    X_PROPERTY(QColor, WellSymbolColor);
	X_PROPERTY(bool, WellSymbolUseObjColor);
    X_PROPERTY(int, WellSymbolRadius);

    virtual bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo);
};
#endif