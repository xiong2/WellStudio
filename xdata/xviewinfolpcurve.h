#ifndef _CXViewInfoLPCurve_H__
#define _CXViewInfoLPCurve_H__

#include "xdata_global.h"
#include "xviewinfoobject.h"

class CXObject;

class XDATA_EXPORT CXViewInfoLPCurve : public CXViewInfoObject
{
public:
	CXViewInfoLPCurve(CXObject * = NULL);
	CXViewInfoLPCurve(const CXViewInfoLPCurve&);

	///@brief Copy assignment operator
	CXViewInfoLPCurve& operator=(const CXViewInfoLPCurve&);

	X_PROPERTY(int, LineWidth);
	X_PROPERTY(int, LineStyle);

	X_PROPERTY(double, FillFrom);
	X_PROPERTY(QColor, FFColor);
	X_PROPERTY(int, FFPattern);
	X_PROPERTY(double, FillTo);
	X_PROPERTY(QColor, FTColor);
	X_PROPERTY(int, FTPattern);

	virtual void SerializeTemplate(QDataStream& stream, bool bSave);
};

#endif