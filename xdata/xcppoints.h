#ifndef _CXCPPOINTS_H__
#define _CXCPPOINTS_H__

#include <quuid.h>
#include <qcolor.h>
#include <qvector.h>
#include "xdata_global.h"
#include "xobjecttype.h"
#include "xio.h"

///@brief	This object holds points send out by cross plot window and need be mapped on other windows.
///@author	Xiong Xiong
///@date	Aug, 2015
class XDATA_EXPORT CXCPPoints: public IKEIO
{
public:
	CXCPPoints(QUuid rangeID, EXObjectType eCPObjType, QUuid cpObjID, QColor color, float fOpacity)
	{
		m_rangeID		= rangeID;
		m_eCPObjType	= eCPObjType;
		m_CPObjID		= cpObjID;
		m_color			= color;
		m_fOpacity		= fOpacity;
	}
	~CXCPPoints() {  }

	EXObjectType GetObjectType() { return m_eCPObjType; }
	QUuid GetRangeID() { return m_rangeID; }
	QUuid GetCPObjectID() { return m_CPObjID; }

	void SetColor(QColor color) { m_color = color; }
	void SetOpacity(float fOpacity) { m_fOpacity = fOpacity; }

	QColor GetColor() { return m_color; }
	float GetOpacity() { return m_fOpacity; }

	QVector<qreal>& GetData() { return m_vecData; }

protected:
	EXObjectType		m_eCPObjType;		//	Type of the object being cross plot.
	QUuid				m_rangeID;			//	The ID of the range(polgyon) which selected the points.
	QUuid				m_CPObjID;			//	The ID of the object being cross plot.
											//	If type is well log, this is the well ID.
	QColor				m_color;
	float				m_fOpacity;			//	
	
	QVector<qreal>		m_vecData;			//	For cross plot well log, consist of pairs of startMD, endMD.
};

#endif