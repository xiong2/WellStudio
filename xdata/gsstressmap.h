#ifndef _GSSTRESSMAP_H__
#define _GSSTRESSMAP_H__

#include <QObject>
#include "xdef.h"
#include "xobject.h"
#include "xseismicutmtool.h"
#include "gsstressparameters.h"
#include "xdata_global.h"

class CX3DHorizon;

class XDATA_EXPORT GSStressMap : public CXObject
{
public:
	GSStressMap();
	GSStressMap(const CXSeismicUTMTool& utm, const QString& sName, GSStressParameters *);
	GSStressMap(GSStressMap *, QString sName);
	~GSStressMap();

	virtual CXSeismicUTMTool& GetUTM() { return m_utm; }

	virtual bool SerializeData(CXArchive& ar);
	virtual QString GetTypeString();
	virtual QStringList GetDescription();

	GSStressParameters* GetParas()
	{
		return &m_paras;
	}

	float* GetData();
	QUuid GetSurveyID();
	QVector<double> CalculateStressInsideCapsules();
	QVector<double> CalculateStressInsideCapsulesMethod2();

	//! @brief: return true if the passed point is inside a "normal" structure.
	bool IsInsideNormalStructure(double x, double y);
	//! @brief: return true if the passed point is inside a "reverse" structure.
	bool IsInsideReverseStructure(double x, double y);

	CX3DHorizon* CreateKh();

protected:
	virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);
	virtual void _SetSelfDimension();

	virtual void _WriteData();
	virtual void _ReadData();

	GSStressParameters	m_paras;
	CXSeismicUTMTool	m_utm;
	float*				m_pDataInMem;		//	Double utm, first is magnitude, second is azimuth, in degrees, start from east, counter-clockwise.
};

#endif