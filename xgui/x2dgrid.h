#ifndef X2DGRID_H
#define X2DGRID_H

#include <QGraphicsItem>

///@brief	2D grid for interpolation inherit from QGraphicsItem
///@author	pezy
///@date	May. 12th, 2014
///@see	

#define DEFAULT_POINTS_NUM 100
#define SCENE_MARGIN_FACTOR 0.2f
#define DEFAULT_LINEOFGRID_NUM 11
#define GRID_ZOOM_FACTOR 0.02F

class CX2DGrid : public QGraphicsItem
{
public:
	CX2DGrid();
	~CX2DGrid();

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */) override;

	void _Init(double spanI, double spanJ, QVector<QPointF> vecPoints);
	void _SetVertex(const QVector<QPointF> vecVertex);

private:

	void _CalculateProportion();

private:
	double m_dSpanI;
	double m_dSpanJ;

	QVector<QPointF> m_vecPoints;
	QVector<QPointF> m_vecVertex;

	int m_nViewWidth, m_nViewHeight;	// GraphicsView's width and height

	double m_dProportion;				// proportion between UTM and scene pixel
};

#endif // RL2DGRID_H
