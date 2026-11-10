#ifndef _GSSECTIONSCENE_H__
#define _GSSECTIONSCENE_H__

#include <QGraphicsScene>
#include <QMouseEvent>

#include "gsobjitem.h"

#define TOP_MARGIN	80
#define	LEFT_MARGIN	60
#define	RIGHT_MARGIN 60
#define BOTTOM_MARGIN 60

class GSSectionWindow;
class CXObject;
class GSItemProfile;

class GSSectionScene : public QGraphicsScene 
{
	Q_OBJECT

public:
	GSSectionScene(GSSectionWindow * pWindow, QObject * parent = Q_NULLPTR);
	~GSSectionScene();

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
	GSSectionWindow*	m_pWindow;
	GSItemProfile*		m_pProfileItem;
	double				m_dHScale;
	double				m_dVScale;
};

#endif