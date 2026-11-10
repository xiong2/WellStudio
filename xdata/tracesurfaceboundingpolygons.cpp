#include "tracesurfaceboundingpolygons.h"
#include "xglobal.h"

TraceSurfaceBoundingPolygons::TraceSurfaceBoundingPolygons(CXUTMTool utm, float *pData)
	:m_utm(utm)
{
	m_nI = m_utm.GetNI();
	m_nJ = m_utm.GetNJ();
	m_pMask = new unsigned char[m_nI * m_nJ];

	int i, j, iCount = 0;
	for (i = 0; i < m_nI; i++)
	{
		for (j = 0; j < m_nJ; j++)
		{
			if (pData[iCount] == g_dInvalidData)
				m_pMask[iCount] = 0;
			else
			{
				if (i == 0 || i == m_nI - 1 || j == 0 || j == m_nJ - 1)
					m_pMask[iCount] = 1;
				else if (pData[(i - 1) * m_nJ + j] == g_dInvalidData
					|| pData[(i + 1) * m_nJ + j] == g_dInvalidData
					|| pData[i * m_nJ + j - 1] == g_dInvalidData
					|| pData[i * m_nJ + j + 1] == g_dInvalidData
					|| pData[(i - 1) * m_nJ + j - 1] == g_dInvalidData
					|| pData[(i + 1) * m_nJ + j - 1] == g_dInvalidData
					|| pData[(i - 1) * m_nJ + j + 1] == g_dInvalidData
					|| pData[(i + 1) * m_nJ + j + 1] == g_dInvalidData)
					m_pMask[iCount] = 1;
				else
					m_pMask[iCount] = 0;
			}

			iCount++;
		}
	}
}

TraceSurfaceBoundingPolygons::~TraceSurfaceBoundingPolygons()
{
	if (m_pMask)
		delete[]m_pMask;
}

void TraceSurfaceBoundingPolygons::TracePolygons()
{
	int i, j;
	for (i = 0; i < m_nI - 1; i++)
	{
		for (j = 0; j < m_nJ; j++)
		{
			if (m_pMask[i * m_nJ + j] != 1)
				continue;
			
			//if(i == 50 && j == 329)
			//	return;

			QPolygon polygon = traceOnePolygon(i, j);
			addOnePolygon(polygon);
		}
	}
}

void TraceSurfaceBoundingPolygons::addOnePolygon(QPolygon polygon)
{
	foreach(QPoint point, polygon)
	{
		m_pMask[point.x() * m_nJ + point.y()] = 0;
	}

	if (polygon.size() <= 2)
		return;

	polygon = shrinkPolygon(polygon);
	QPolygonF polygonF;
	foreach(QPoint point, polygon)
	{
		double x, y;
		m_utm.IJToXY(point.x(), point.y(), x, y);
		polygonF << QPointF(x, y);
	}

	m_vecPolygons << polygonF;
}

QPolygon TraceSurfaceBoundingPolygons::traceOnePolygon(int i, int j)
{
	QPolygon polygon;

	QPoint p0(i, j);
	polygon << p0;
	m_pMask[i * m_nJ + j] = 2;

	if (m_pMask[(i + 1) * m_nJ + j] != 1)
		return polygon;

	i++;		
	m_pMask[i * m_nJ + j] = 2;
	polygon << QPoint(i, j);
	int iDir = 1;
	while(1)
	{
		if (!tracing(i, j, iDir))
		{
			qDebug() << "Something error!";
		}

		QPoint p1(i, j);
		polygon << p1;
	
		if (qAbs(p0.x() - p1.x()) + qAbs(p0.y() - p1.y()) <= 1)
			break;
	}

	//QPoint p0 = polygon.first(), p1 = polygon.last();
	//if (qAbs(p0.x() - p1.x()) + qAbs(p0.y() - p1.y()) > 1)
	//{
	//	//splitPolygon(polygon);
	//	//p1 = polygon.last();
	//	while (polygon.size() > 3 && qAbs(p0.x() - p1.x()) + qAbs(p0.y() - p1.y()) > 1)
	//	{
	//		polygon.removeLast();
	//		p1 = polygon.last();
	//		if (qAbs(p0.x() - p1.x()) + qAbs(p0.y() - p1.y()) <= 1)
	//		{
	//			break;
	//		}

	//		tracing(polygon, p1.x(), p1.y());

	//		p1 = polygon.last();
	//		if (qAbs(p0.x() - p1.x()) + qAbs(p0.y() - p1.y()) <= 1)
	//		{
	//			break;
	//		}
	//		//splitPolygon(polygon);
	//	}
	//}

	return polygon;
}

bool TraceSurfaceBoundingPolygons::tracing(int& i, int& j, int& iDir)
{
	if (iDir == 0)
	{
		if (i > 0 && m_pMask[(i - 1) * m_nJ + j] == 1)
		{
			i--;
			iDir = 3;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
		else if (j > 0 && m_pMask[i * m_nJ + j - 1] == 1)
		{
			j--;
			iDir = 0;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
		else if (i < m_nI - 1 && m_pMask[(i + 1) * m_nJ + j] == 1)
		{
			i++;
			iDir = 1;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}		
	}
	else if (iDir == 1)
	{
		if (j > 0 && m_pMask[i * m_nJ + j - 1] == 1)
		{
			j--;
			iDir = 0;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
		else if (i < m_nI - 1 && m_pMask[(i + 1) * m_nJ + j] == 1)
		{
			i++;
			iDir = 1;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
		else if (j < m_nJ - 1 && m_pMask[i * m_nJ + j + 1] == 1)
		{
			j++;
			iDir = 2;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
	}
	else if (iDir == 2)
	{
		if (i < m_nI - 1 && m_pMask[(i + 1) * m_nJ + j] == 1)
		{
			i++;
			iDir = 1;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
		else if (j < m_nJ - 1 && m_pMask[i * m_nJ + j + 1] == 1)
		{
			j++;
			iDir = 2;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
		else if (i > 0 && m_pMask[(i - 1) * m_nJ + j] == 1)
		{
			i--;
			iDir = 3;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
	}
	else if (iDir == 3)
	{
		if (j < m_nJ - 1 && m_pMask[i * m_nJ + j + 1] == 1)
		{
			j++;
			iDir = 2;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
		else if (i > 0 && m_pMask[(i - 1) * m_nJ + j] == 1)
		{
			i--;
			iDir = 3;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
		else if (j > 0 && m_pMask[i * m_nJ + j - 1] == 1)
		{
			j--;
			iDir = 0;
			m_pMask[i * m_nJ + j] = 2;
			return true;
		}
	}

	if (iDir == 0)
	{
		if (i > 0 && m_pMask[(i - 1) * m_nJ + j] == 2)
		{
			i--;
			iDir = 3;
			return true;
		}
		else if (j > 0 && m_pMask[i * m_nJ + j - 1] == 2)
		{
			j--;
			iDir = 0;
			return true;
		}
		else if (i < m_nI - 1 && m_pMask[(i + 1) * m_nJ + j] == 2)
		{
			i++;
			iDir = 1;
			return true;
		}		
		else if (j < m_nJ - 1 && m_pMask[i * m_nJ + j + 1] == 2)
		{
			j++;
			iDir = 2;
			return true;
		}		
	}
	else if (iDir == 1)
	{
		if (j > 0 && m_pMask[i * m_nJ + j - 1] == 2)
		{
			j--;
			iDir = 0;
			return true;
		}
		else if (i < m_nI - 1 && m_pMask[(i + 1) * m_nJ + j] == 2)
		{
			i++;
			iDir = 1;
			return true;
		}		
		else if (j < m_nJ - 1 && m_pMask[i * m_nJ + j + 1] == 2)
		{
			j++;
			iDir = 2;
			return true;
		}		
		else if (i > 0 && m_pMask[(i - 1) * m_nJ + j] == 2)
		{
			i--;
			iDir = 3;
			return true;
		}
	}
	else if (iDir == 2)
	{
		if (i < m_nI - 1 && m_pMask[(i + 1) * m_nJ + j] == 2)
		{
			i++;
			iDir = 1;
			return true;
		}		
		else if (j < m_nJ - 1 && m_pMask[i * m_nJ + j + 1] == 2)
		{
			j++;
			iDir = 2;
			return true;
		}		
		else if (i > 0 && m_pMask[(i - 1) * m_nJ + j] == 2)
		{
			i--;
			iDir = 3;
			return true;
		}
		else if (j > 0 && m_pMask[i * m_nJ + j - 1] == 2)
		{
			j--;
			iDir = 0;
			return true;
		}
	}
	else if (iDir == 3)
	{
		if (j < m_nJ - 1 && m_pMask[i * m_nJ + j + 1] == 2)
		{
			j++;
			iDir = 2;
			return true;
		}		
		else if (i > 0 && m_pMask[(i - 1) * m_nJ + j] == 2)
		{
			i--;
			iDir = 3;
			return true;
		}
		else if (j > 0 && m_pMask[i * m_nJ + j - 1] == 2)
		{
			j--;
			iDir = 0;
			return true;
		}
		else if (i < m_nI - 1 && m_pMask[(i + 1) * m_nJ + j] == 2)
		{
			i++;
			iDir = 1;
			return true;
		}		
	}

	return false;
}

QPolygon TraceSurfaceBoundingPolygons::shrinkPolygon(QPolygon sPolygon)
{
	QPolygon dPolygon;

	QPoint p0 = sPolygon.takeFirst();
	dPolygon << p0;
	QPoint p1 = sPolygon.takeFirst();
	int oDir = getDir(p0, p1), nDir;

	while (sPolygon.size() > 1)
	{
		QPoint p2 = sPolygon.takeFirst();
		nDir = getDir(p1, p2);

		if (nDir != oDir)
		{
			dPolygon << p1;
			oDir = nDir;
		}
		p1 = p2;
	}

	dPolygon << sPolygon.last();

	return dPolygon;
}

int TraceSurfaceBoundingPolygons::getDir(QPoint p0, QPoint p1)
{
	if (p0.x() > p1.x())
		return 0;
	else if (p0.y() < p1.y())
		return 1;
	else if ((p0.x() < p1.x()))
		return 2;
	else
		return 3;
}

void TraceSurfaceBoundingPolygons::splitPolygon(QPolygon& polygon)
{
	int i, j, iSize = polygon.size();
	if (iSize < 6)
		return;

	QPoint p0 = polygon.last();
	for (i = 1; i < iSize - 3; i++)
	{
		if (qAbs(p0.x() - polygon[i].x()) + qAbs(p0.y() - polygon[i].y()) <= 1)
		{
			break;
		}
	}

	if (i < iSize - 3)
	{
		QPolygon subPolygon;
		int iNSize = iSize - i;
		for (j = 0; j < iNSize; j++)
		{
			subPolygon << polygon.takeLast();
		}

		addOnePolygon(subPolygon);
	}
}