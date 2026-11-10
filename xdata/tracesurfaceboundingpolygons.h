#pragma once

#include <qpolygon.h>
#include "xdata_global.h"
#include "xutmtool.h"

class XDATA_EXPORT TraceSurfaceBoundingPolygons
{
public:
	TraceSurfaceBoundingPolygons(CXUTMTool utm, float *pData);
	~TraceSurfaceBoundingPolygons();

	void TracePolygons();

	QVector<QPolygonF>& GetPolygons()
	{
		return m_vecPolygons;
	}

private:
	QPolygon traceOnePolygon(int i, int j);
	QPolygon shrinkPolygon(QPolygon);
	int getDir(QPoint, QPoint);
	void addOnePolygon(QPolygon);
	void splitPolygon(QPolygon&);

	bool tracing(int& i, int& j, int& iDir);	// iDir = 0: left;  1: up;  2: right;  3: down; -1: no direction.

	CXUTMTool			m_utm;
	int					m_nI;
	int					m_nJ;
	unsigned char*		m_pMask = NULL;
	QVector<QPolygonF>	m_vecPolygons;
};