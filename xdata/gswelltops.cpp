#include <qfile.h>
#include <qdatastream.h>
#include "gswelltops.h"
#include "xobjectfactory.h"
#include "xglobal.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSWellTops)
EXGSWellTops
END_REGISTER_OBJECT_TO_FACTORY(GSWellTops)

GSWellTop::GSWellTop(double x, double y, double z): m_pos(x, y), m_dZ(z)
{
	m_dDir = g_dInvalidData;
	m_dSHMax = g_dInvalidData;
	m_dShmin = g_dInvalidData;
	m_dSV = g_dInvalidData;
	m_dPp = g_dInvalidData;
}

void GSWellTops::_WriteData()
{
    QString strFileName = GetDataFileName();
    QFile file(strFileName);
    if (!file.open(QIODevice::WriteOnly))
        return;

    QDataStream stream(&file);

    size_t sticksSize = m_mapTops.size();
    stream << sticksSize;

	QMapIterator<QUuid, GSWellTop> it(m_mapTops);
	while(it.hasNext())
    {
		it.next();

		GSWellTop top = it.value();
        stream << it.key();
		stream << top.m_pos;
		stream << top.m_dZ;
		stream << top.m_dDir;
		stream << top.m_dSHMax;
		stream << top.m_dShmin;
		stream << top.m_dSV;
		stream << top.m_dPp;
    }
}

void GSWellTops::_ReadData()
{
    QString strFileName = GetDataFileName();
    QFile file(strFileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QDataStream stream(&file);

    size_t topSize;
    stream >> topSize;

    m_mapTops.clear();
    for (size_t i = 0; i < topSize; ++i)
    {
		QUuid wellID;
		GSWellTop top;

        stream >> wellID;
		stream >> top.m_pos;
		stream >> top.m_dZ;
		stream >> top.m_dDir;
		stream >> top.m_dSHMax;
		stream >> top.m_dShmin;
		stream >> top.m_dSV;
		stream >> top.m_dPp;

		m_mapTops.insert(wellID, top);
    }
}