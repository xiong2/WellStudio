#ifndef _GSITEMFRG_H__
#define _GSITEMFRG_H__

//#include "stdafx.h"
#include "gsobjitem.h"
#include "gsfrg.h"
//#include "gsviewer_global.h"

class CXViewInfoObject;

class GSItemFRG : public GSObjItem
{
public:
	GSItemFRG(GSFRG *, CXViewInfoObject *, QGraphicsItem *parent = 0);

	virtual QUuid GetObjectID()
	{
		return m_pFRG->GetObjectID();
	}

	bool SceneXToXY(int iX, double& dX, double& dY);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	GSFRG*	m_pFRG;
};

#endif