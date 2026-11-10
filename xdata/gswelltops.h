#ifndef GSWELLTOPS_H__
#define GSWELLTOPS_H__

#include "xdata_global.h"
#include <qvector.h>
#include "xobject.h"

class XDATA_EXPORT GSWellTop
{
public:
	QPoint	m_pos;
	double	m_dZ;
	double	m_dDir;			//	Start from north, clockwise.
	double	m_dSHMax;
	double	m_dShmin;
	double	m_dSV;
	double	m_dPp;

	GSWellTop() = default;
	GSWellTop(double, double, double);
};

class XDATA_EXPORT GSWellTops : public CXObject
{
public:
	GSWellTops(): CXObject("WellTops")
	{
		SetObjectType(EXWellTops);
		SetNodeFlag(false);
	}

	void AddOneTop(QUuid wellID, GSWellTop &top)
	{
		if(m_mapTops.isEmpty())
			LoadData();
			
		m_mapTops.insert(wellID, top);
	}

	QMap<QUuid, GSWellTop>& GetAllTops()
	{
		if(m_mapTops.isEmpty())
			LoadData();

		return m_mapTops;
	}

protected:
	void _WriteData() override;
	void _ReadData() override;

	QMap<QUuid, GSWellTop>	m_mapTops;
};

#endif