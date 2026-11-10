#pragma once
#include <vector>
#include <limits>
#include "gsfaulttrace.h"
#include "xgeometry.h"
#include "xdata_global.h"

class CXUTMTool;

struct XDATA_EXPORT GSSectionPoint
{
	GSSectionPoint() = default;
	GSSectionPoint(double stn_, double z_): stn(stn_), z(z_) {}

	double stn;
	double z;
};

class XDATA_EXPORT GSFaultInterpStick
{
public:
	GSFaultInterpStick(std::vector<XPoint>::const_iterator beg, std::vector<XPoint>::const_iterator end);

	double GetDipAngle();

	std::vector<XPoint>::const_iterator begin() const;
	std::vector<XPoint>::const_iterator end() const;
	std::vector<XPoint>::iterator begin();
	std::vector<XPoint>::iterator end();
	std::vector<XPoint>::const_reverse_iterator rbegin() const;
	std::vector<XPoint>::const_reverse_iterator rend() const;
	std::vector<XPoint>::reverse_iterator rbegin();
	std::vector<XPoint>::reverse_iterator rend();

private:
	static const int m_nInterpNum = 16;
	std::vector<XPoint> m_vecInterpPoints;
	double m_dipAngle = std::numeric_limits<double>::quiet_NaN();
};

class XDATA_EXPORT GSHorizonFault
{
	enum SectionType {eInline, eCrossline, eRandomline}; // inline, xline, randomline

public:
	GSHorizonFault(CXUTMTool& utm, float* pHorzData, GSFaultInterpStick& faultStick);

	GSFaultTrace GetFaultTrace(double dFaultTol);

private:
	void determineSectionType();
	void buildSectionLeftAndRightLine();
	QPolygonF buildFaultTracePolygon(double dFaultTol);
	XPoint zInterp(double z, bool bSetZ = true);
	bool sectionPointIsLeft(double idx, double z);
	bool isThePointsTooFarAwayFromIntersection(const GSSectionPoint& hp1, const GSSectionPoint& hp2, const GSFaultTrace& ft);
	void calcThrows(double dFaultTol);
	XVec2d getHorzLocByStn(int stn);
	float getFaultStickPointStn(double x, double y);

private:
	GSFaultInterpStick& m_faultInterpStick;
	CXUTMTool& m_utm;
	float* m_pHorzData = nullptr;

	std::vector<GSSectionPoint> m_vecSecPoints;
	XLine2d m_leftLine;
	XLine2d m_rightLine;

	int m_lineNo = -1;
	SectionType m_secType = eInline;

	GSFaultTrace m_ft;
};

namespace NGSFault
{
	XDATA_EXPORT void SortFaultTrace(std::vector<GSFaultTrace>* vecTraces);
}