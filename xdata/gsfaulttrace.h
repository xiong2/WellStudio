#pragma once
#include "xvec.h"
#include <QPointF>
#include <QDataStream>
#include "xdata_global.h"
#include "xarchive.h"

struct XDATA_EXPORT GSFaultTrace
{
    enum EType
    {
        eReverse,
        eNormal,
        eZero,
        eVertical
    };

	bool IsNull() const;
	QPointF CentrePoint() const;

	void SerializeData(CXArchive&);

    XVec3d m_p1;
    XVec3d m_p2;
    EType m_type;
};

QDataStream& operator<<(QDataStream& out, const GSFaultTrace& ft);
QDataStream& operator>>(QDataStream& in, GSFaultTrace& ft);