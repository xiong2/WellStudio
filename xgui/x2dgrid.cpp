#include "x2dgrid.h"

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "xglobal.h"

CX2DGrid::CX2DGrid()
{
	m_dSpanI = m_dSpanJ = 0.0f;
	m_nViewWidth = m_nViewHeight = 0;
	m_dProportion = 0.0f;
}

CX2DGrid::~CX2DGrid()
{
}

void CX2DGrid::_Init(double spanI, double spanJ, QVector<QPointF> vecPoints)
{
	m_dSpanI = spanI;
	m_dSpanJ = spanJ;
	m_vecPoints = vecPoints;
}

QRectF CX2DGrid::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(-m_nViewWidth/2 - penWidth/2, -m_nViewHeight/2 - penWidth/2, m_nViewWidth + penWidth, m_nViewHeight + penWidth);
}

void CX2DGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QGraphicsView *view = scene()->views().first();
	m_nViewWidth = view->width();
	m_nViewHeight = view->height();

	_CalculateProportion();

	painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	// draw points
	painter->setPen(QPen(Qt::white, 2));
	for (auto point = m_vecPoints.begin(); point != m_vecPoints.end(); ++point)
	{
		QPointF pixelPoint(-m_dSpanJ/2+(*point).x(), m_dSpanI/2-(*point).y());
		pixelPoint *= m_dProportion;
		painter->drawPoint(pixelPoint);
	}

	// draw boundary
	painter->setPen(QPen(Qt::red, 1));
	painter->drawRect(-m_dSpanJ*m_dProportion/2, -m_dSpanI*m_dProportion/2, m_dSpanJ*m_dProportion, m_dSpanI*m_dProportion);

	// draw grid
	painter->setPen(QPen(Qt::green, 1));
	for (int i=0; i<DEFAULT_LINEOFGRID_NUM; ++i)
	{
		double nLXIIncrement = i*(m_vecVertex[0].x() - m_vecVertex[1].x())/(DEFAULT_LINEOFGRID_NUM-1);
		double nLYIIncrement = i*(m_vecVertex[0].y() - m_vecVertex[1].y())/(DEFAULT_LINEOFGRID_NUM-1);
		double nRXIIncrement = i*(m_vecVertex[2].x() - m_vecVertex[3].x())/(DEFAULT_LINEOFGRID_NUM-1);
		double nRYIIncrement = i*(m_vecVertex[2].y() - m_vecVertex[3].y())/(DEFAULT_LINEOFGRID_NUM-1);

		QPointF pointLeft(m_vecVertex[0].x()-nLXIIncrement, -m_vecVertex[0].y()+nLYIIncrement);
		QPointF pointRight(m_vecVertex[2].x()-nRXIIncrement, -m_vecVertex[2].y()+nRYIIncrement);
		pointLeft *= m_dProportion;
		pointRight *= m_dProportion;

		painter->drawLine(pointLeft, pointRight);

		double nBXJIncrement = i*(m_vecVertex[2].x() - m_vecVertex[0].x())/(DEFAULT_LINEOFGRID_NUM-1);
		double nBYJIncrement = i*(m_vecVertex[0].y() - m_vecVertex[2].y())/(DEFAULT_LINEOFGRID_NUM-1);
		double nTXJIncrement = i*(m_vecVertex[3].x() - m_vecVertex[1].x())/(DEFAULT_LINEOFGRID_NUM-1);
		double nTYJIncrement = i*(m_vecVertex[1].y() - m_vecVertex[3].y())/(DEFAULT_LINEOFGRID_NUM-1);

		QPointF pointBottom(m_vecVertex[0].x()+nBXJIncrement, -m_vecVertex[0].y()+nBYJIncrement);
		QPointF pointTop(m_vecVertex[1].x()+nTXJIncrement, -m_vecVertex[1].y()+nTYJIncrement);
		pointTop *= m_dProportion;
		pointBottom *= m_dProportion;

		painter->drawLine(pointBottom, pointTop);
	}

	// draw description
	painter->setPen(Qt::red);
	painter->drawRect(-m_nViewWidth/2+5, m_nViewHeight/2-25, 30, 20);
	painter->setPen(Qt::white);
	painter->drawText(-m_nViewWidth/2+40, m_nViewHeight/2-10, "Data Boundary");
	painter->setPen(Qt::green);
	painter->drawRect(-m_nViewWidth/2+130, m_nViewHeight/2-25, 30, 20);
	painter->drawLine(-m_nViewWidth/2+130, m_nViewHeight/2-15, -m_nViewWidth/2+160, m_nViewHeight/2-15);
	painter->drawLine(-m_nViewWidth/2+140, m_nViewHeight/2-25, -m_nViewWidth/2+140, m_nViewHeight/2-5);
	painter->drawLine(-m_nViewWidth/2+150, m_nViewHeight/2-25, -m_nViewWidth/2+150, m_nViewHeight/2-5);
	painter->setPen(Qt::white);
	painter->drawText(-m_nViewWidth/2+165, m_nViewHeight/2-10, "New Grid");
}

void CX2DGrid::_CalculateProportion()
{
	double proportionI = m_nViewHeight/((1 + 2*SCENE_MARGIN_FACTOR)*m_dSpanI);	// scaling on I direction
	double proportionJ = m_nViewWidth/((1 + 2*SCENE_MARGIN_FACTOR)*m_dSpanJ);	// scaling on J direction

	m_dProportion = (proportionI < proportionJ) ? proportionI : proportionJ; 
}

void CX2DGrid::_SetVertex(const QVector<QPointF> vecVertex)
{
	m_vecVertex = vecVertex;
	QPointF rightTopPoint(0.0f, 0.0f);
	rightTopPoint += vecVertex[1];
	rightTopPoint += vecVertex[2];
	rightTopPoint -= vecVertex[0];

	m_vecVertex.push_back(rightTopPoint);
}