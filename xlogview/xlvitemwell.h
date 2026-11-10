#pragma once
#include <qgraphicsitem.h>
#include <quuid.h>
#include "xlogview_global.h"

class CXViewInfoObject;
class CXViewInfoLPWell;
class CXLVWindowInfo;
class CXLVScene;

class CXLVItemWell : public QGraphicsRectItem
{
public:
	CXLVItemWell(CXLVScene *, QUuid objectID, CXViewInfoObject *pViewInfo, QGraphicsItem *parent = 0);
	QUuid GetObjectID()
	{
		return m_objectID;
	}

	CXViewInfoLPWell*	GetWellViewInfo()
	{
		return m_pViewInfo;
	}

	void Configure(qreal x = -999.25);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

	QUuid					m_objectID;
	CXLVScene*				m_pScene;
	CXLVWindowInfo*			m_pWinInfo;
	CXViewInfoLPWell*		m_pViewInfo;
};