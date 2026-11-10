#include "xisolines.h"
#include "xgeometry.h"
#include "xmath.h"
#include <array>
#include <cassert>
#include <unordered_map>

class CXIsolines::Impl
{
public:
    using Segment = std::pair<XVec2d, XVec2d>;

    Impl();
    void FillLevels(double dFirstLevel, double dInterval, int no);
    void CalcSegmentInOneTriangle(XTriangle3d tri);
    size_t LevelCount() const;
    bool HasSegments(size_t index);
    const std::set<Segment>& GetSegments(size_t index);
	void ClearContourTable();

    friend std::istream& operator>>(std::istream& is, CXIsolines& isolines);
    friend std::ostream& operator<<(std::ostream& os, const CXIsolines& isolines);

private:
    enum LevelIntersectionCase
    {
        eNone,
        eAllBelow,
        eTwoBelowOneOnLine,
        eTwoBelowOneAbove,
        eOneBelowTwoOnLine,
        eOneBelowOneOnOneAbove,
        eOneBelowTwoAbove,
        eAllOnLine,
        eTwoOnLineOneAbove,
        eOneOnLineTwoAbove,
        eAllAbove
    };

    static void sortXY(XVec2d& p1, XVec2d& p2);
    static int cmpZ(double z1, double z2);
    static XVec2d intersectZ(const XVec3d& p1, const XVec3d& p2, double z);

    std::array<std::array<std::array<LevelIntersectionCase, 3>, 3>, 3> m_caseList;
    std::vector<double> m_levels;
    std::unordered_map<size_t, std::set<Segment>> m_tableLevelContour;
};

CXIsolines::CXIsolines()
    : m_pImpl(new Impl())
{
}

CXIsolines::~CXIsolines()
{
    delete m_pImpl;
}

void CXIsolines::SetLevel(double dMin, double dMax, int nLevel)
{
    double dContourInterval = XMath::NiceInterval(dMin, dMax, nLevel);

    double dFirstLevel;
    int no;
    XMath::NiceLevel(dContourInterval, dMin, dMax, &dFirstLevel, &no, true);
    m_pImpl->FillLevels(dFirstLevel, dContourInterval, no);
}

void CXIsolines::CalculateWithTriangleMeshes(const std::vector<XTriangle3d>& meshes)
{
    for (auto&& tri : meshes)
    {
        m_pImpl->CalcSegmentInOneTriangle(tri);
    }
}

size_t CXIsolines::LevelCount() const
{
    return m_pImpl->LevelCount();
}

const std::set<std::pair<XVec2d, XVec2d>>* CXIsolines::GetSegments(size_t index) const
{
    if (!m_pImpl->HasSegments(index))
        return nullptr;

    return &m_pImpl->GetSegments(index);
}

void CXIsolines::Clear()
{
	m_pImpl->ClearContourTable();
}

CXIsolines::Impl::Impl()
{
    m_caseList[0][0][0] = eAllBelow;
    m_caseList[0][0][1] = eTwoBelowOneOnLine;
    m_caseList[0][0][2] = eTwoBelowOneAbove;
    m_caseList[0][1][1] = eOneBelowTwoOnLine;
    m_caseList[0][1][2] = eOneBelowOneOnOneAbove;
    m_caseList[0][2][2] = eOneBelowTwoAbove;
    m_caseList[1][1][1] = eAllOnLine;
    m_caseList[1][1][2] = eTwoOnLineOneAbove;
    m_caseList[1][2][2] = eOneOnLineTwoAbove;
    m_caseList[2][2][2] = eAllAbove;
}

void CXIsolines::Impl::FillLevels(double dFirstLevel, double dInterval, int no)
{
    m_levels.clear();
    for (int i = 0; i < no; ++i)
    {
        m_levels.push_back(dFirstLevel + i * dInterval);
    }
}

void CXIsolines::Impl::CalcSegmentInOneTriangle(XTriangle3d tri)
{
    tri.ZSort();

    // Calculate the start level
    auto greaterThanFirstVertex = std::upper_bound(m_levels.begin(), m_levels.end(), tri.Vertex(0).z());
    if (greaterThanFirstVertex == m_levels.end())
        return;

    auto smallerThanFirstVertex = greaterThanFirstVertex == m_levels.begin() ? greaterThanFirstVertex : std::prev(greaterThanFirstVertex);

    for (auto iter = smallerThanFirstVertex; iter != m_levels.end(); ++iter)
    {
        double z     = *iter;
        size_t index = std::distance(m_levels.begin(), iter);
        int c1       = cmpZ(tri.Vertex(0).z(), z);
        int c2       = cmpZ(tri.Vertex(1).z(), z);
        int c3       = cmpZ(tri.Vertex(2).z(), z);

        LevelIntersectionCase intersectionCase = m_caseList[c1][c2][c3];
        XVec2d p1, p2;
        switch (intersectionCase)
        {
        case eAllBelow:
        case eTwoBelowOneOnLine:
        case eOneOnLineTwoAbove:
        case eAllAbove:
        case eAllOnLine:
            continue;
        case eTwoBelowOneAbove:
            p1 = intersectZ(tri.Vertex(0), tri.Vertex(2), z);
            p2 = intersectZ(tri.Vertex(1), tri.Vertex(2), z);
            break;
        case eOneBelowTwoAbove:
            p1 = intersectZ(tri.Vertex(0), tri.Vertex(1), z);
            p2 = intersectZ(tri.Vertex(0), tri.Vertex(2), z);
            break;
        case eOneBelowTwoOnLine:
            p1 = tri.Vertex(1).ToVec2();
            p2 = tri.Vertex(2).ToVec2();
            break;
        case eOneBelowOneOnOneAbove:
            p1 = intersectZ(tri.Vertex(0), tri.Vertex(2), z);
            p2 = tri.Vertex(1).ToVec2();
            break;
        case eTwoOnLineOneAbove:
            p1 = tri.Vertex(0).ToVec2();
            p2 = tri.Vertex(1).ToVec2();
            break;
        default:
            assert(!"error case");
        }
        sortXY(p1, p2);
        m_tableLevelContour[index].emplace(p1, p2);
    }
}

size_t CXIsolines::Impl::LevelCount() const
{
    return m_levels.size();
}

bool CXIsolines::Impl::HasSegments(size_t index)
{
    return m_tableLevelContour.find(index) != m_tableLevelContour.end();
}

const std::set<std::pair<XVec2d, XVec2d>>& CXIsolines::Impl::GetSegments(size_t index)
{
    return m_tableLevelContour.at(index);
}

void CXIsolines::Impl::ClearContourTable()
{
	m_tableLevelContour.clear();
}

void CXIsolines::Impl::sortXY(XVec2d& p1, XVec2d& p2)
{
    if (p1.x() > p2.x())
    {
        std::swap(p1, p2);
    }
    else if (p1.x() == p2.x())
    {
        if (p1.y() > p2.y())
            std::swap(p1, p2);
        else
            ; // do nothing
    }
    else
        ; // do nothing
}

int CXIsolines::Impl::cmpZ(double z1, double z2)
{
    if (z1 > z2)
        return 2;
    if (z1 < z2)
        return 0;
    return 1;
}

XVec2d CXIsolines::Impl::intersectZ(const XVec3d& p1, const XVec3d& p2, double z)
{
    double r = (z - p1.z()) / (p2.z() - p1.z());
    assert(r >= 0.0);
    assert(r <= 1.0);

    double x = p1.x() + r * (p2.x() - p1.x());
    double y = p1.y() + r * (p2.y() - p1.y());
    return XVec2d(x, y);
}

std::istream& operator>>(std::istream& is, CXIsolines& isolines)
{
    CXIsolines::Impl* pImpl = isolines.m_pImpl;

	// levels
	size_t levelSize;
	is >> levelSize;

	pImpl->m_levels.resize(levelSize);
	for (auto&& level : pImpl->m_levels)
	{
		double l;
		is >> l;
		level = l;
	}

	// level contours
	size_t contoursSize;
	is >> contoursSize;

	pImpl->m_tableLevelContour.clear();
	auto contourHint = pImpl->m_tableLevelContour.begin();
	for (size_t i = 0; i < contoursSize; ++i)
	{
		size_t key, valueSize;
		is >> key >> valueSize;

		std::set<std::pair<XVec2d, XVec2d>> segments;
		auto segmentsHint = segments.begin();
		for (size_t j = 0; j < valueSize; ++j)
		{
			double x1, y1, x2, y2;
			is >> x1 >> y1 >> x2 >> y2;
			segmentsHint = segments.emplace_hint(segmentsHint, std::make_pair(XVec2d(x1, y1), XVec2d(x2, y2)));
		}

		contourHint = pImpl->m_tableLevelContour.emplace_hint(contourHint, key, segments);
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const CXIsolines& isolines){
    
	CXIsolines::Impl* pImpl = isolines.m_pImpl;

	// levels
	os << pImpl->m_levels.size();
	for (auto level : pImpl->m_levels)
	{
		os << level;
	}

	// level contours
	os << pImpl->m_tableLevelContour.size();
	for (auto iter : pImpl->m_tableLevelContour)
	{
		os << iter.first << iter.second.size();
		for (auto segment : iter.second)
		{
			os << segment.first.x() << segment.first.y() << segment.second.x() << segment.second.y();
		}
	}

	return os;
}
