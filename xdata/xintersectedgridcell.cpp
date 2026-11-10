#include "xintersectedgridcell.h"

#include <algorithm>
#include <vector>

CXIntersectedGridCell::CXIntersectedGridCell(unsigned short usI, unsigned short usJ, unsigned short usK, unsigned char ucSegIndex) : 
m_nNum(0), m_ucSegmentIndex(ucSegIndex), m_usI(usI), m_usJ(usJ), m_usK(usK)
{
}

void CXIntersectedGridCell::GetBoundingBox(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax) const
{
	std::vector<double> vecX;
	std::vector<double> vecY;
	std::vector<double> vecZ;

	for (int i=0; i<m_nNum; i+=3)
	{
		vecX.push_back(m_pVertex[i]);
		vecY.push_back(m_pVertex[i+1]);
		vecZ.push_back(m_pVertex[i+2]);
	}

	if ( vecX.empty() || vecY.empty() || vecZ.empty() )
		return;

	dXMin = *std::min_element(vecX.cbegin(), vecX.cend());
	dXMax = *std::max_element(vecX.cbegin(), vecX.cend());
	dYMin = *std::min_element(vecY.cbegin(), vecY.cend());
	dYMax = *std::max_element(vecY.cbegin(), vecY.cend());
	dZMin = *std::min_element(vecZ.cbegin(), vecZ.cend());
	dZMax = *std::max_element(vecZ.cbegin(), vecZ.cend());
}