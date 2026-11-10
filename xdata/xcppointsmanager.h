#ifndef _CXPOINTSMANAGER_H__
#define	_CXPOINTSMANAGER_H__

#include "xdata_global.h"
#include <quuid.h>
#include <qvector.h>
#include <qlist.h>

class CXCPPoints;

///@brief	This static object manage the points send out by cross plot window and need be mapped on other windows.
///@author	Xiong Xiong
///@date	Aug, 2015
class XDATA_EXPORT CXCPPointsManager
{
public:
	static CXCPPoints* GetCPPoints(QUuid objectID);
	static CXCPPoints* GetCPPoints(QUuid rangeID, QUuid CPObjectID);
	static QList<CXCPPoints *> GetCPPointsOfPolygon(QUuid rangeID);
	static QList<CXCPPoints *> GetCPPointsOfObject(QUuid CPObjectID);
	static void AddCPPoints(CXCPPoints *);

private:
	static QVector<CXCPPoints *>	m_vecCPPoints;
};

#endif