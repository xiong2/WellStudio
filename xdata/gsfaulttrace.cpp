#include "gsfaulttrace.h"
#include "xgeometry.h"

bool GSFaultTrace::IsNull() const
{
	return m_p1.IsNull() || m_p2.IsNull() || m_p1 == m_p2;
}

QPointF GSFaultTrace::CentrePoint() const
{
	double r = 0.5;

	// always use the high side if we can
	if (m_p1.z() < m_p2.z())
		r = 0.01;
	else if (m_p1.z() > m_p2.z())
		r = 0.99;

	XVec3d p = XGeom::Lerp(m_p1, m_p2, r);
	return QPointF(p.x(), p.y());
}

void GSFaultTrace::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_p1.x() << m_p1.y() << m_p1.z() << m_p2.x() << m_p2.y() << m_p2.z() << m_type;
	}
	else
	{
		int type;
		ar >> m_p1.rx() >> m_p1.ry() >> m_p1.rz() >> m_p2.rx() >> m_p2.ry() >> m_p2.rz() >> type;
		m_type = static_cast<GSFaultTrace::EType>(type);
	}
}

QDataStream& operator<<(QDataStream& out, const GSFaultTrace& ft)
{
	out << ft.m_p1.x() << ft.m_p1.y() << ft.m_p1.z() << ft.m_p2.x() << ft.m_p2.y() << ft.m_p2.z() << ft.m_type;
	return out;
}

QDataStream& operator>>(QDataStream& in, GSFaultTrace& ft)
{
	int type;
	in >> ft.m_p1.rx() >> ft.m_p1.ry() >> ft.m_p1.rz() >> ft.m_p2.rx() >> ft.m_p2.ry() >> ft.m_p2.rz() >> type;
	ft.m_type = static_cast<GSFaultTrace::EType>(type);
	return in;
}
