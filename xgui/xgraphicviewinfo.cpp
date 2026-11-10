#include "xgraphicviewinfo.h"

CXGraphicViewInfo::CXGraphicViewInfo()
{
	m_bHAxisAuto		= true;
	m_dHMinValue		= -999.;
	m_dHMaxValue		= -999.;
	m_dHStep			= -999.;
	m_bHAxisGrid		= true;
	m_hAxisGridColor	= QColor("Gray");
	m_iHAxisGridWidth	= 1;
	m_iHAxisGridStyle	= 1;

	m_bVAxisAuto		= true;
	m_dVMinValue		= -999.;
	m_dVMaxValue		= -999.;
	m_dVStep			= -999.;
	m_bVAxisGrid		= true;
	m_vAxisGridColor	= QColor("Gray");
	m_iVAxisGridWidth	= 1;
	m_iVAxisGridStyle	= 1;
}