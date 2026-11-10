#ifndef _CXGRAPHICVIEWINFO_H__
#define _CXGRAPHICVIEWINFO_H__

#include "xgui_global.h"
#include <qcolor.h>
#include "xio.h"

class XGUI_EXPORT CXGraphicViewInfo: public IKEIO
{
public:
	CXGraphicViewInfo();

	bool	m_bHAxisAuto;		//	Whether horizontal axis range auto-defined.
	double	m_dHMinValue;		//	Below 3 members only used while manually define horizontal axis.
	double	m_dHMaxValue;
	double	m_dHStep;
	bool	m_bHAxisGrid;		//	Whether show horizontal axis' grid (vertical ones.)
	QColor	m_hAxisGridColor;
	int		m_iHAxisGridWidth;
	int		m_iHAxisGridStyle;

	bool	m_bVAxisAuto;		//	Whether vertical axis range auto-defined.
	double	m_dVMinValue;		//	Below 3 members only used while manually define vertical axis.
	double	m_dVMaxValue;
	double	m_dVStep;
	bool	m_bVAxisGrid;		//	Whether show horizontal axis' grid (vertical ones.)
	QColor	m_vAxisGridColor;
	int		m_iVAxisGridWidth;
	int		m_iVAxisGridStyle;
};

#endif