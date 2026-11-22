#pragma once
#include "xdata_global.h"
#include "xobject.h"

class CX3DSurvey;
class CX2DSeismicLine;

class CXOneSection
{
public:
	QUuid	m_refID;
	int		m_nTrace;
	QVector<int>	m_vecI1;
	QVector<int>	m_vecI2;
	QPolygonF		m_coords;

};

class XDATA_EXPORT CXCombinedLine : public CXObject
{
public:
	CXCombinedLine(QString strName = "");

	static bool IsTwoObjectIntersect(CXObject*, CXObject*);

private:
	static bool isTwoSurveyIntersect(CX3DSurvey*, CX3DSurvey*);

	static bool isLineIntersectSurvey(CX2DSeismicLine*, CX3DSurvey*);

	int		m_nSample;
	double	m_dZStart;
	double	m_dZStep;
};