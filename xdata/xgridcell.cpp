#include "xgridcell.h"

#include <algorithm>
#include <vector>

CXGridCell::CXGridCell(unsigned short iI, unsigned short iJ, unsigned short iK, unsigned char iSegIndex)
{
	m_iI			= iI;
	m_iJ			= iJ;
	m_iK			= iK;
	m_iSegmentIndex	= iSegIndex;
}

CXGridCell::~CXGridCell()
{
}

void CXGridCell::GetBoundingBox(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	std::vector<double> vecX, vecY, vecZ;
	for (int i=0; i<24; i+=3)
	{
		vecX.push_back(m_pVertex[i]);
		vecY.push_back(m_pVertex[i+1]);
		vecZ.push_back(m_pVertex[i+2]);
	}
	dXMin = *std::min_element(vecX.cbegin(), vecX.cend());
	dXMax = *std::max_element(vecX.cbegin(), vecX.cend());
	dYMin = *std::min_element(vecY.cbegin(), vecY.cend());
	dYMax = *std::max_element(vecY.cbegin(), vecY.cend());
	dZMin = *std::min_element(vecZ.cbegin(), vecZ.cend());
	dZMax = *std::max_element(vecZ.cbegin(), vecZ.cend());
}