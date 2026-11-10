#ifndef _CXObjectITEM_H__
#define _CXObjectITEM_H__

#include <qgraphicsitem.h>
#include <quuid.h>
#include "xgui_global.h"
#include "xobjecttype.h"

#define CURVEITEMWIDTH 120
#define HEADERHEIGHT 40
#define VSPACE 5

class CXViewInfoObject;

enum ERLItemType
{
	eNone			= 0,

	eLPWell			= 1,	//	Well header on logplot.
	eLPTrack		= 2,	//	Track header on logplot.
	eLPCurve		= 3,	//	Curve on logplot.
	eLPFillCurve	= 4,	//	Filled curve on logplot.
	eLPWellTops		= 5,	//	Well tops on logplot.
	eLPRegions		= 6,	//	Regions sent by crossplot.

	eCPPoints		= 11,	//	Points on crossplot.
	eCPPolygon		= 12,	//	Polygon on crossplot.

	eHisto			= 21,	//	Histogram.
};

class XGUI_EXPORT CXObjectItem: public QGraphicsRectItem
{
public:
	CXObjectItem(QUuid objectID, CXViewInfoObject *pViewInfo, QGraphicsItem *parent = 0);

	QUuid GetObjectID()
	{
		return m_objectID;
	}
	EXObjectType GetObjectType();
	ERLItemType GetItemType()
	{
		return m_eItemType;
	}

	QString GetObjectName();
	  
	CXViewInfoObject* GetObjectViewInfo()
	{
		return m_pViewInfo;
	}
	void SetWindowViewInfo(CXViewInfoObject*pViewInfo )
	{
		 m_pWindowViewInfo = pViewInfo;
	}
	CXViewInfoObject* GetWindowViewInfo()
	{
		return m_pWindowViewInfo;
	}
	void Repaint()
	 {
	 };
protected:
	virtual bool _InitData() {return true;}
	QUuid					m_objectID;
	ERLItemType				m_eItemType;
private:
	CXViewInfoObject*		m_pWindowViewInfo;
	CXViewInfoObject*		m_pViewInfo;
};

#endif