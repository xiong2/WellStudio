#include "gs3dhorizonfaulttraces.h"
#include <algorithm>
#include <QLineF>
#include "xobjectfactory.h"
#include "xobjecttype.h"
#include "xgeometry.h"
#include "gsutilities.h"
#include "xstatistic.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GS3DHorizonFaultTraces)
EXGSFaultTraces
END_REGISTER_OBJECT_TO_FACTORY(GS3DHorizonFaultTraces)

GS3DHorizonFaultTraces::GS3DHorizonFaultTraces(const QString& name)
{
    SetObjectType(EXGSFaultTraces);
    SetObjectName(name);
}

GS3DHorizonFaultTraces::~GS3DHorizonFaultTraces()
{
}

bool GS3DHorizonFaultTraces::SerializeData(CXArchive& ar)
{
	for (auto&& trace : m_vecTraces)
	{
		trace.SerializeData(ar);
	}

	if (ar.IsSaving())
	{
		ar << m_iStatus;
		ar << m_bActive;
	}
	else
	{
		ar >> m_iStatus;
		ar >> m_bActive;
	}

	return true;
}

QStringList GS3DHorizonFaultTraces::GetDescription()
{
	return QStringList() << "traces count:" << QString::number(m_vecTraces.size());
}

QString GS3DHorizonFaultTraces::GetTypeString()
{
	return "3-D Horizon fault traces";
}

void GS3DHorizonFaultTraces::AddTrace(const GSFaultTrace& trace)
{
    m_vecTraces.push_back(trace);
}

void GS3DHorizonFaultTraces::DelTrace(int iIndex)
{
    m_vecTraces.erase(std::next(m_vecTraces.begin(), iIndex));
}

int GS3DHorizonFaultTraces::TraceCount() const
{
    return m_vecTraces.size();
}

GSFaultTrace* GS3DHorizonFaultTraces::GetTrace(int iIndex)
{
    if (iIndex < 0 || TraceCount() <= iIndex)
        return nullptr;

    return &m_vecTraces.at(iIndex);
}

void GS3DHorizonFaultTraces::Reduce(double dTol, bool bFixNonGenerated)
{
	std::vector<XVec2d> centrePoly;
	for (auto&& trace : m_vecTraces)
	{
		centrePoly.push_back(GSUtil::ToVec(trace.CentrePoint()));
	}

	std::vector<int> use(centrePoly.size(), static_cast<int>(bFixNonGenerated));
	use.front() = use.back() = 1;
	XGeom::Reduce(centrePoly, &use[0], dTol);

	for (size_t i = use.size() - 1; i > 0; --i)
	{
		if (use[i])
			continue;

		auto iterDel = std::next(m_vecTraces.begin(), i);
		m_vecTraces.erase(iterDel);
	}
}

int GS3DHorizonFaultTraces::Dip()
{
	float fDip = 0.;
	int iNum = 0;
	for (auto&& trace : m_vecTraces)
	{
		fDip += XGeom::Dip(trace.m_p1, trace.m_p2);
		iNum++;
	}

	if(iNum == 0)	
		return 0;

	return 90 - (90 * fDip / (iNum * M_PI_2));
}

double GS3DHorizonFaultTraces::Length()
{
	double length = 0.0;
	for (auto ft1 = m_vecTraces.begin(), ft2 = std::next(ft1); ft2 != m_vecTraces.end(); ++ft1, ++ft2)
	{
		QLineF centreLine(ft1->CentrePoint(), ft2->CentrePoint());
		length += centreLine.length();
	}
	return length;
}

double GS3DHorizonFaultTraces::ReversePercent()
{
	if(m_vecTraces.empty())
		return 0.;

	double reverseLen = 0.0;
	double nonReverseLen = 0.0;

	for (auto ft1 = m_vecTraces.begin(), ft2 = std::next(ft1); ft2 != m_vecTraces.end(); ++ft1, ++ft2)
	{
		QLineF centreLine(ft1->CentrePoint(), ft2->CentrePoint());
		if (ft1->m_type == GSFaultTrace::eReverse || ft2->m_type == GSFaultTrace::eReverse)
		{
			reverseLen += centreLine.length();
		}
		else
		{
			nonReverseLen += centreLine.length();
		}
	}

    return reverseLen * 100.0 / (reverseLen + nonReverseLen);
}

double GS3DHorizonFaultTraces::ThrowStdDevPoint(double dStdDev)
{
	XStatistic stats;
	for (auto&& trace : m_vecTraces)
	{
		double dThrow = fabs(trace.m_p1.z() - trace.m_p2.z());
		stats.Append(dThrow);
	}

    return stats.Mean() + dStdDev * stats.StdDev();
}

std::vector<GSFaultTrace>& GS3DHorizonFaultTraces::GetTraces()
{
    return m_vecTraces;
}

double GS3DHorizonFaultTraces::MaxThrow() const
{
	double dMaxThrow = 0.;

	for (int i = 0; i < m_vecTraces.size(); i++)
	{
		GSFaultTrace ft = m_vecTraces[i];
		double dThrow = qAbs(ft.m_p1.z() - ft.m_p2.z());
		dMaxThrow = dMaxThrow > dThrow ? dMaxThrow : dThrow;
	}

	return dMaxThrow;
}

void GS3DHorizonFaultTraces::_SetSelfDimension()
{
    double dXMin = std::numeric_limits<double>::max();
    double dXMax = std::numeric_limits<double>::min();
    double dYMin = std::numeric_limits<double>::max();
    double dYMax = std::numeric_limits<double>::min();

    for (auto&& ft : m_vecTraces)
    {
		dXMin = std::min({ dXMin, ft.m_p1.x(), ft.m_p2.x() });
		dXMax = std::max({ dXMax, ft.m_p1.x(), ft.m_p2.x() });
		dYMin = std::min({ dYMin, ft.m_p1.y(), ft.m_p2.y() });
		dYMax = std::max({ dYMax, ft.m_p1.y(), ft.m_p2.y() });
    }

	_SetDimension(dXMin, dXMax, dYMin, dYMax, std::numeric_limits<double>::max(), std::numeric_limits<double>::min());
}

std::ostream& operator<<(std::ostream& os, const GS3DHorizonFaultTraces& faultTraces)
{
	int iLineID = 0;
	for (auto&& trace : faultTraces.m_vecTraces)
	{
		os << trace.m_p1.x() << "," << trace.m_p1.y() << "," << trace.m_p1.z() << "," << iLineID << "\n";
		os << trace.m_p2.x() << "," << trace.m_p2.y() << "," << trace.m_p2.z() << "," << iLineID << "\n";
		++iLineID;
	}
	return os;
}
