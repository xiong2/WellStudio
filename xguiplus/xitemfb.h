#pragma once
#include <qgraphicsitem.h>

class XSceneGather;

class XItemFB : public QGraphicsItem
{
public:
	XItemFB(XSceneGather*, QGraphicsItem* parent = nullptr);
	~XItemFB();

	virtual QRectF boundingRect() const override;

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

	void UpdateData(float* pData, int iNumTrace);

	void MapToScene();

private:
	int				m_iNumTrace = 0;
	float*			m_pData = nullptr;
	QPolygonF		m_points;
	XSceneGather*	m_pScene;
};