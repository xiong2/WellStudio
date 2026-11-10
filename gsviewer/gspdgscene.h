#ifndef _GSPDGSCENE_H__
#define _GSPDGSCENE_H__

#include "stdafx.h"
#include <QGraphicsScene>
#include <QMouseEvent>

#include "gsviewer_global.h"
#include "gsobjitem.h"

#define TOP_MARGIN	80
#define	LEFT_MARGIN	240
#define	RIGHT_MARGIN 60
#define BOTTOM_MARGIN 80

class GSPDGWindow;
class CXObject;
class GSObjItem;

class GSVIEWER_EXPORT GSPDGScene : public QGraphicsScene
{
	Q_OBJECT

public:
	GSPDGScene(GSPDGWindow * pWindow, QObject * parent = Q_NULLPTR);
	~GSPDGScene();

	void AddObjectItem(CXObject *);
	void RemoveObjectItem(CXObject * = NULL);

	void GetScale(double& dHScale, double& dVScale)
	{
		dHScale = m_dHScale;
		dVScale = m_dVScale;
	}

	void SetScale(double dHScale, double dVScale);

	void UpdateView();

	//	Coordinate transform.
	int ZToSceneY(float);
	float SceneYToZ(int);
	bool SceneXToXY(int iX, double& dX, double& dY);

	void HandleMouseEvent(QMouseEvent* event, EXGSMouseEventType);

protected:
	GSPDGWindow*	m_pWindow;
	GSObjItem*		m_pPDGItem;
	double			m_dHScale;
	double			m_dVScale;
};

#endif