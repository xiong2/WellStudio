#pragma once

#include <qgraphicsitem.h>
#include <qevent.h>
#include "xguiplus_global.h"

class XScenePyramid;

class XItemPyRect : public QGraphicsItem
{
public:
	XItemPyRect(XScenePyramid *, QGraphicsItem* parent = 0);

	virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget* = 0) override;
	virtual QRectF boundingRect() const override;
	virtual void HandleMouseEvent(QMouseEvent *);

private:
	QPolygonF		m_polygon;

	enum EStatus
	{
		ePreEdit,
		eEditing,
		eEdited,
	};
	EStatus		m_eSta = ePreEdit;

	XScenePyramid*	m_pScene;
};