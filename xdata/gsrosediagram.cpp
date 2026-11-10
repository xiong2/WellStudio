#include "xobjectfactory.h"
#include "gsrosediagram.h"
#include "gsstressmap.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSRoseDiagram)
EXGSRoseDiagram
END_REGISTER_OBJECT_TO_FACTORY(GSRoseDiagram)

GSRoseDiagram::GSRoseDiagram(const QString& sName, QPolygonF polygon): CXObject(sName)
{
	SetIconName("RoseDiagram.png");
	SetObjectType(EXGSRoseDiagram);
	m_iMode = 1;
	m_polygon = polygon;
}

GSRoseDiagram::GSRoseDiagram(const QString& sName, QPointF centre, double dRadius): CXObject(sName)
{
	SetIconName("RoseDiagram.png");
	SetObjectType(EXGSRoseDiagram);
	m_iMode = 0;
	m_centre = centre;
	m_dRadius = dRadius;
}

bool GSRoseDiagram::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_iMode;
		ar << m_centre;
		ar << m_dRadius;
		ar << m_polygon;
		ar << m_vecData;
	}
	else
	{
		ar >> m_iMode;
		ar >> m_centre;
		ar >> m_dRadius;
		ar >> m_polygon;
		ar >> m_vecData;
	}

	return true;
}

QString GSRoseDiagram::GetTypeString()
{
	return "Rose diagram for stress direction";
}

QStringList GSRoseDiagram::GetDescription()
{
	QStringList sList;
	if (m_iMode == 0)
	{
		sList << "Range defined by " << "Circle";
		sList << "Rangle circle centre" << QString::number(m_centre.x(), 'f', 0) + ", " + QString::number(m_centre.y(), 'f', 0);
		sList << "Rangle circle radius" << QString::number(m_dRadius, 'f', 0);
	}
	else
		sList << "Rangle defined by " << "Polygon";

	return sList;
}

QVector<float>& GSRoseDiagram::GetPetalVector(int iNum)
{
	if(m_vecPetal.size() == iNum)
		return m_vecPetal;

	int i, iNumData = m_vecData.size();
	m_vecPetal.fill(0, iNum);
	for (i = 0; i < iNumData; i++)
	{
		int iIDX = (int)(m_vecData[i] / 180 * iNum + 0.5);
		if(iIDX >= iNum)
			iIDX = 0;

		m_vecPetal[iIDX]++;
	}

	for(i = 0; i < iNum; i++)
		m_vecPetal[i] = m_vecPetal[i] / iNumData;

	return m_vecPetal;
}