#ifndef GS3DHORIZONVIEWINFO_H
#define GS3DHORIZONVIEWINFO_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT GS3DHorizonViewInfo : public CXViewInfoObject
{
public:
	GS3DHorizonViewInfo();
	~GS3DHorizonViewInfo();

	void SetViewObjectID(const QUuid& objID) override;

	X_PROPERTY(bool, IsolineDisplay)
	X_PROPERTY(double, IsolineLevelFirst)
	X_PROPERTY(double, IsolineLevelLast)
	X_PROPERTY(int, IsolineLevelNum)
	X_PROPERTY(bool, IsolineLevelChanged)
	X_PROPERTY(QColor, IsolineCoarseColor)
	X_PROPERTY(int, IsolineCoarseWidth)
	X_PROPERTY(int, IsolineCoarseFreq)
	X_PROPERTY(QColor, IsolineNormalColor)
	X_PROPERTY(int, IsolineNormalWidth)
	X_PROPERTY(QColor, IsolineAnnotationColor)
	X_PROPERTY(QString, IsolineAnnotationFontName)
	X_PROPERTY(int, IsolineAnnotationFontSize)
};

#endif // GS3DHORIZONVIEWINFO_H
