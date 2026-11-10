#pragma once
#include <QObject>
#include <QUuid>
#include "xdef.h"
#include "xdata_global.h"

class XDATA_EXPORT CXHorizonTrackPar: public QObject 
{
public:
    CXHorizonTrackPar();
    virtual ~CXHorizonTrackPar();
public:
    //track Mode
    X_PROPERTY(int, TrackMode);			//	0: Event,		1: Waveform.
    X_PROPERTY(int, Technique);			//	0: 1x1 Check,	1: 3x3 Check,	2: 3x3 Expand,	3: 5x5 Advanced.

    //Snap
    X_PROPERTY(int, SnapType);				//	0: None,	1: Peak,	2: Trough,	3: Zero Cross -/+,	4: Zero Cross +/-.
    X_PROPERTY(int, Method);				//	0: Closest,	1: Largest.

    //Search window
    X_PROPERTY(int, SearchTop);		
    X_PROPERTY(int, SearchBottom);
    X_PROPERTY(int, SearchDelta);

    //Parameter
    X_PROPERTY(int, WindowTop);
    X_PROPERTY(int, WindowBottom);
    X_PROPERTY(float, QualityFactory);

	X_PROPERTY(bool, OverWrite);
};