#ifndef _GSITEMPROFILE_H__
#define _GSITEMPROFILE_H__

#include "gsobjitem.h"
#include "gssection.h"

class CXViewInfoObject;

class GSItemProfile : public GSObjItem
{
public:
	GSItemProfile(GSSection *, CXViewInfoObject *, QGraphicsItem *parent = 0);

	virtual QUuid GetObjectID()
	{
		return m_pSection->GetObjectID();
	}

	bool SceneXToXY(int iX, double& dX, double& dY);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	GSSection*	m_pSection;
};

#endif