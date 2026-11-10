#ifndef _CXLPWELLVIEWINFO_H__
#define _CXLPWELLVIEWINFO_H__

#include "xdata_global.h"
#include "xviewinfoobject.h"

class CXObject;

class XDATA_EXPORT CXViewInfoLPWell : public CXViewInfoObject
{
public:
	CXViewInfoLPWell(CXObject * = NULL);
	CXViewInfoLPWell(const CXViewInfoLPWell&);

	CXViewInfoLPWell& operator=(const CXViewInfoLPWell&);

	X_PROPERTY(double, StartDepth);
	X_PROPERTY(double, EndDepth);

	X_PROPERTY(double, DepthTrackWidth);
	X_PROPERTY(bool, DepthTrackLeft);

	virtual void SerializeTemplate(QDataStream& stream, bool bSave);
};

#endif