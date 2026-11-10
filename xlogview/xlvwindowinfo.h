#pragma once

#include "xlogview_global.h"
#include "xgraphicviewinfo.h"

#define MARGIN 5

class XLOGVIEW_EXPORT CXLVWindowInfo : public CXGraphicViewInfo
{
public:
	int			m_iHIntv = 80;				//	Horizontal interval between each well.
	int			m_iHeaderHeight = 40;		//
	bool		m_bUniqueDepth = false;		//	Whether each well uses unique depth.
	bool		m_bShowBinGrid = true;
	qreal		m_dSDepth = 99999.;			//	Start depth (minimum depth of all wells).
	qreal		m_dEDepth = -99999.;			//	Start depth (minimum depth of all wells).
	qreal		m_dVScale = 1;				//	Vertical scale.
	qreal		m_dTrackWidth = 140;		//	Width of log track.
};