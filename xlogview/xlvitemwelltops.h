#pragma once
#include <qgraphicsitem.h>
#include <quuid.h>
#include "xlogview_global.h"

class CXViewInfoObject;
class CXViewInfoLPWellTops;
class CXLVWindowInfo;
class CXLVScene;

class CXLVItemWellTops : public QGraphicsRectItem
{
public:
	CXLVItemWellTops(CXLVScene *, QUuid objectID, CXViewInfoObject *pViewInfo, QGraphicsItem *parent = 0);
	QUuid GetObjectID()
	{
		return m_objectID;
	}

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

	QUuid						m_objectID;
	CXLVScene*					m_pScene;
	CXLVWindowInfo*				m_pWinInfo;
	CXViewInfoLPWellTops*		m_pViewInfo;

	QStringList					m_sListFormation;
	QList<QColor>				m_listColor;
};