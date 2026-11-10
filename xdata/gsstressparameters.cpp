#include "gsstressparameters.h"

GSStressParameters::GSStressParameters()
{
	m_bSmooth = true;

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			m_iAnti[i] = 1;
		else
			m_iAnti[i] = 0;

		m_dSRadius[i] = 3000.;
		m_dTHeight[i] = 12.;
		m_dCThreshold[i] = 0.9;
		m_dLThreshold[i] = 5000.;
	}

	m_bRemoveOverlap = true;
	m_dTWidth = 2000.;
	m_dORatio = 0.3;
	m_bFaults = true;
	m_dFLinearity = 600.;
	m_dMinFLength = 2000.;
	m_bAdjReverse = true;
	m_dNormF = 0.13;
	m_dESSF = 0.29;
	m_dSSF = 0.5;
	m_dCSSF = 0.8;
	m_iLWRatio = 5;
	m_dMaxRadius = 4000.;
	m_bMerge = true;
	m_iMergeAngle = 20;
	m_dMergeRatio = 0.5;
	m_iLowestStatus = 0;
	m_fThrow = 1.;
}

void GSStressParameters::Copy(GSStressParameters *pParas)
{
	m_bSmooth = pParas->m_bSmooth;

	for (int i = 0; i < 3; i++)
	{
		m_iAnti[i] = pParas->m_iAnti[i];
		m_dSRadius[i] = pParas->m_dSRadius[i];
		m_dTHeight[i] = pParas->m_dTHeight[i];
		m_dCThreshold[i] = pParas->m_dCThreshold[i];
		m_dLThreshold[i] = pParas->m_dLThreshold[i];
	}

	m_bRemoveOverlap = pParas->m_bRemoveOverlap;
	m_dTWidth = pParas->m_dTWidth;
	m_dORatio = pParas->m_dORatio;
	m_bFaults = pParas->m_bFaults;
	m_dFLinearity = pParas->m_dFLinearity;
	m_dMinFLength = pParas->m_dMinFLength;
	m_bAdjReverse = pParas->m_bAdjReverse;
	m_dNormF = pParas->m_dNormF;
	m_dESSF = pParas->m_dESSF;
	m_dSSF = pParas->m_dSSF;
	m_dCSSF = pParas->m_dCSSF;
	m_iLWRatio = pParas->m_iLWRatio;
	m_dMaxRadius = pParas->m_dMaxRadius;
	m_bMerge = pParas->m_bMerge;
	m_iMergeAngle = pParas->m_iMergeAngle;
	m_dMergeRatio = pParas->m_dMergeRatio;
	m_iLowestStatus = pParas->m_iLowestStatus;
	m_fThrow = pParas->m_fThrow;
}

bool GSStressParameters::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_bSmooth;

		for (int i = 0; i < 3; i++)
		{
			ar << m_iAnti[i];
			ar << m_dSRadius[i];
			ar << m_dTHeight[i];
			ar << m_dCThreshold[i];
			ar << m_dLThreshold[i];
		}

		ar << m_bRemoveOverlap;
		ar << m_dTWidth;
		ar << m_dORatio;
		ar << m_bFaults;
		ar << m_dFLinearity;
		ar << m_dMinFLength;
		ar << m_bAdjReverse;
		ar << m_dNormF;
		ar << m_dESSF;
		ar << m_dSSF;
		ar << m_dCSSF;
		ar << m_iLWRatio;
		ar << m_dMaxRadius;
		ar << m_bMerge;
		ar << m_iMergeAngle;
		ar << m_dMergeRatio;
		ar << m_iLowestStatus;
		ar << m_fThrow;
	}
	else
	{
		ar >> m_bSmooth;

		for (int i = 0; i < 3; i++)
		{
			ar >> m_iAnti[i];
			ar >> m_dSRadius[i];
			ar >> m_dTHeight[i];
			ar >> m_dCThreshold[i];
			ar >> m_dLThreshold[i];
		}

		ar >> m_bRemoveOverlap;
		ar >> m_dTWidth;
		ar >> m_dORatio;
		ar >> m_bFaults;
		ar >> m_dFLinearity;
		ar >> m_dMinFLength;
		ar >> m_bAdjReverse;
		ar >> m_dNormF;
		ar >> m_dESSF;
		ar >> m_dSSF;
		ar >> m_dCSSF;
		ar >> m_iLWRatio;
		ar >> m_dMaxRadius;
		ar >> m_bMerge;
		ar >> m_iMergeAngle;
		ar >> m_dMergeRatio;
		ar >> m_iLowestStatus;
		ar >> m_fThrow;
	}
		
	return true;
}