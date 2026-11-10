#ifndef XSECTIONVIEWINFO_H
#define XSECTIONVIEWINFO_H

#include "xviewinfoobject.h"
#include "xdata_global.h"
#include <QString>

class XDATA_EXPORT CXWindowInfoSection : public CXViewInfoObject
{
public:
	CXWindowInfoSection();
	~CXWindowInfoSection(){}

	X_PROPERTY(float, Excursion);
	X_PROPERTY(float, Cliping);
	X_PROPERTY(float, TraceStep);
	X_PROPERTY(float, TraceScale);
	X_PROPERTY(float, VerScale);

	X_PROPERTY(bool, VariableIntensity);
	X_PROPERTY(bool, WiggleVariableArea);
	X_PROPERTY(bool, Wiggle);
	X_PROPERTY(QString, 2ndDataVolumeName);
	X_PROPERTY(QString, ForeColormapName);
	X_PROPERTY(bool, ForeVariableIntensity);
	X_PROPERTY(bool, ForeWiggleVariableArea);
	X_PROPERTY(bool, ForeWiggle);
	X_PROPERTY(float, ForeAlpha);

	X_PROPERTY(QStringList,ShowContents);
	X_PROPERTY(QColor , HorAnnColor);
	X_PROPERTY(int , HorAnnSize);
	X_PROPERTY(QString ,HorAnnFont);
	X_PROPERTY(bool , HorAuto);
	X_PROPERTY(int ,HorIncTraces);
	X_PROPERTY(int ,HorIncofMinor);
	X_PROPERTY(int ,HorAxisMargin);
	
	X_PROPERTY(bool ,ShowMajorLine);
	X_PROPERTY(QColor,VerAnnColor);
	X_PROPERTY(int , VerAnnSize);
	X_PROPERTY(QString ,VerAnnFont);
	X_PROPERTY(bool , VerAuto);
	X_PROPERTY(int ,VerIncTraces);
	X_PROPERTY(int ,VerIncofMinor);
	X_PROPERTY(int, VerAxisMargin);

	X_PROPERTY(float ,SearchingRadius);
};

#endif // RLSECTIONVIEWINFO_H