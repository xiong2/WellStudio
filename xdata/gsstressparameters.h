#ifndef _GSSTRESSPARAMETERS_H__
#define _GSSTRESSPARAMETERS_H__

#include "xarchive.h"
#include "xdata_global.h"

class XDATA_EXPORT GSStressParameters
{
public:
	GSStressParameters();
	
	void Copy(GSStressParameters *);

	virtual bool SerializeData(CXArchive& ar);

	bool	m_bSmooth;
	int		m_iAnti[3];				//	0 unuse, 1 anticline, 2 syncline.
	double	m_dSRadius[3];	
	double	m_dTHeight[3];
	double	m_dCThreshold[3];
	double	m_dLThreshold[3];
	bool	m_bRemoveOverlap;
	double	m_dTWidth;				//	Width of the structure for calculate overlap.
	double	m_dORatio;				//	Ratio to judge wether they are overlaped.
	bool	m_bFaults;
	double  m_dFLinearity;
	double	m_dMinFLength;
	bool	m_bAdjReverse;
	double	m_dNormF;
	double	m_dESSF;
	double	m_dSSF;
	double	m_dCSSF;
	int		m_iLWRatio;				//	Length vs. width of the structure.
	double	m_dMaxRadius;
	bool	m_bMerge;
	int		m_iMergeAngle;
	double	m_dMergeRatio;
	int		m_iLowestStatus;		//	User may specify the lowest status.
	float	m_fThrow;				//	Minimum throw threhshold.
};

#endif