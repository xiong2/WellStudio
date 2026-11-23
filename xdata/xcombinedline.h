#pragma once
#include "xdata_global.h"
#include "xobject.h"

class CX3DSurvey;
class CX2DSeismicLine;

class CXOneSection
{
public:
	QUuid	m_refID;
	QPolygon		m_vecInd;
	QPolygonF		m_coords;
	qint64			m_iOffset;
};

class XDATA_EXPORT CXCombinedLine : public CXObject
{
public:
	CXCombinedLine(QString strName = "");
	~CXCombinedLine();

	int GetTraceNumber();

	static bool IsTwoObjectIntersect(CXObject*, CXObject*);

	static CXCombinedLine* CreateOneInstance(QVector<CXObject *>, QPolygonF);

private:
	static bool isTwoSurveyIntersect(CX3DSurvey*, CX3DSurvey*);

	static bool isLineIntersectSurvey(CX2DSeismicLine*, CX3DSurvey*);

	static QPolygon createOneSegment(CX3DSurvey *, QPointF, QPointF);

	virtual void _WriteData() override;
	virtual void _ReadData() override;
	virtual void _freeMemory();

	int		m_nSample;
	double	m_dZStart;
	double	m_dZStep;

	QVector<CXOneSection>	m_vecSection;

	float*					m_pDataInMem = nullptr;
};