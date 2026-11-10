#ifndef _GSITEMPDG_H__
#define _GSITEMPDG_H__

#include "stdafx.h"
#include "gsobjitem.h"
#include "gspdg.h"
#include "gsviewer_global.h"

class CXViewInfoObject;

class GSVIEWER_EXPORT GSItemPDG : public GSObjItem
{
public:
	GSItemPDG(GSPDG *, CXViewInfoObject *, QGraphicsItem *parent = 0);

	virtual QUuid GetObjectID()
	{
		return m_pPDG->GetObjectID();
	}

	bool SceneXToXY(int iX, double& dX, double& dY);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	GSPDG*	m_pPDG;
};

#endif