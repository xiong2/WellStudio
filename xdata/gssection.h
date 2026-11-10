#ifndef _GSSECTION_H__
#define _GSSECTION_H__

#include <qpolygon.h>
#include "xobject.h"
#include "xseismicutmtool.h"
#include "xdata_global.h"

class CX3DSurvey;

class XDATA_EXPORT GSSection : public CXObject
{
public:
	GSSection();
	GSSection(CX3DSurvey *, const QString& sName, QPolygonF polyline);
	~GSSection();

	virtual bool SerializeData(CXArchive& ar);
	virtual QStringList GetDescription();

	///	Get each section's length, i = -1 means get the total length.
	double GetSectionLength(int i = -1);

	///	Exactly is the height of the survey.
	double GetSectionHeight();

	QPolygonF GetTurnPoints()
	{
		return m_turnPoints;
	}

	QPolygon GetTraces()
	{
		return m_traces;
	}

	QList<QUuid> GetHorizonsID()
	{
		return m_listHID;
	}

	CXSeismicUTMTool& GetUTM() { return m_utm; }

	float* GetData();
	const QPolygonF& GetTurnPoints() const
	{
		return m_turnPoints;
	}

	char* GetStressData();

protected:
	void calculateTraces();
	void populateHorizons(CX3DSurvey *);
	void calculateData();
	virtual void _SetSelfDimension();

	virtual void _WriteData();
	virtual void _ReadData();

	CXSeismicUTMTool		m_utm;
	QPolygonF		m_turnPoints;	
	QPolygon		m_traces;					//	Each point's x, y is the i, j of the utm.
	QList<QUuid>	m_listHID;					//	The list of horizon ID that intersect the section.

	float*			m_pDataInMem = nullptr;		//	Size = m_listHID.size() * m_traces.size().
	char*			m_pStessData = nullptr;
};

#endif