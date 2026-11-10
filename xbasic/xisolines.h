#pragma once

#include "xbasic_global.h"
#include <vector>
#include <set>
#include "xvec.h"

class XTriangle3d;

/**
@class  CXIsolines provided in the file "xisolines"
@brief  The class provides algorithm about Isolines.
@author pezy
@date   2018-04-17
@sa
*/
class XBASIC_EXPORT CXIsolines
{
public:
	CXIsolines();
	~CXIsolines();

	void SetLevel(double dMin, double dMax, int nLevel);
	void CalculateWithTriangleMeshes(const std::vector<XTriangle3d>& meshes);
	size_t LevelCount() const;
	const std::set<std::pair<XVec2d, XVec2d>>* GetSegments(size_t index) const;
	void Clear();

	friend XBASIC_EXPORT std::istream& operator>>(std::istream& is, CXIsolines& isolines);
	friend XBASIC_EXPORT std::ostream& operator<<(std::ostream& os, const CXIsolines& isolines);

private:
	class Impl;
	Impl* m_pImpl = nullptr;
};

