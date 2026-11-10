#ifndef _GSDEF_H__
#define _GSDEF_H__

#include "xdata_global.h"

//	Below MACRO for structure type.
#define STRUCTURE_NULL			0
#define STRUCTURE_THICK			1
#define STRUCTURE_SYNCLINE		1
#define STRUCTURE_THIN			2
#define STRUCTURE_ANTICLINE		2
#define STRUCTURE_NORMAL_FAULT	3
#define STRUCTURE_REVERSE_FAULT 4
#define STRUCTURE_SPE_FAULT		5

//	Below MACRO for stress magnitude state.
#define MAG_NULL		-1
#define MAG_NORMAL		0
#define MAG_LOADING		1
#define MAG_UPLIFT		2
#define MAG_ESS			3
#define MAG_SS			4
#define MAG_CSS			5
#define MAG_REVERSE		6

#define THROW_CUTOFF_R20	20.
#define THROW_CUTOFF_R15	100.
#define THROW_CUTOFF_R10	500.

//	Define the stress magnitude range of reach type.
static struct XDATA_EXPORT GSStressMagRange
{
	float Upper()
	{
		return gStressMagRange[m_iStressState + 1].m_fSHMagLower;
	}

	int		m_iStressState;	//	Range -1~6, NULL, Normal to reverse.
	float	m_fOldLower;
	float	m_fOldUpper;
	float	m_fOldMag;
	float	m_fSHMag;		//	SH/Sv magnitude for this stress state.
	float	m_fSHMagLower;	//	SH/Sv lower cutoff magnitude for this stress state.
	float	m_fShMag;		//	Sh/Sv magnitude for this stress state.
	float	m_fShMagLower;	//	Sh/Sv lower cutoff magnitude for this stress state.
}

gStressMagRange[] = 
{
	{ MAG_NORMAL,	0.00f, 0.93f, 0.90f, 0.7f,  0.675f, 0.70f, 0.650f },
	{ MAG_LOADING,	0.93f, 0.99f, 0.96f, 0.85f, 0.825f, 0.75f, 0.725f },
	{ MAG_UPLIFT,	0.99f, 1.02f, 1.01f, 1.00f, 0.875f, 0.80f, 0.775f },
	{ MAG_ESS,		1.02f, 1.10f, 1.06f, 1.05f, 1.010f, 0.85f, 0.825f },
	{ MAG_SS,		1.10f, 1.15f, 1.12f, 1.10f, 1.075f, 0.90f, 0.875f },
	{ MAG_CSS,		1.15f, 1.30f, 1.25f, 1.30f, 1.200f, 0.95f, 0.925f },
	{ MAG_REVERSE,  1.30f, 3.00f, 1.50f, 1.50f, 1.397f, 1.05f, 1.000f },
	{ MAG_NULL,		3.00f, 9999.f, 9999.f, 9999.f, 3.000f, 1.50f, 1.500f }
};

static float gSHToSh(float fSH)
{
	float fSh = 0.;

	for (int i = 0; i < 8; i++)
	{
		if (fSH >= gStressMagRange[i].m_fSHMagLower && fSH <= gStressMagRange[i].m_fSHMag)
		{
			float fRatio = (fSH - gStressMagRange[i].m_fSHMagLower) / (gStressMagRange[i].m_fSHMag - gStressMagRange[i].m_fSHMagLower);
			fSh = gStressMagRange[i].m_fShMagLower + fRatio * (gStressMagRange[i].m_fShMag - gStressMagRange[i].m_fShMagLower);
			return fSh;
		}
		else if (fSH < gStressMagRange[i].m_fSHMagLower && i > 1)
		{
			float fRatio = (fSH - gStressMagRange[i - 1].m_fSHMag) / (gStressMagRange[i].m_fSHMagLower - gStressMagRange[i - 1].m_fSHMag);
			fSh = gStressMagRange[i - 1].m_fShMag + fRatio * (gStressMagRange[i].m_fShMagLower - gStressMagRange[i - 1].m_fShMag);
			return fSh;
		}
	}

	return fSh;
};

#endif