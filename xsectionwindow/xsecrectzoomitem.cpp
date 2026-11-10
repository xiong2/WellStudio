#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qdebug.h>
#include "xsectionscene.h"
#include "xsecrectzoomitem.h"
#include "x2dsectionview.h"
#include "x2dsectionwindow.h"
#include "xsectionscene.h"
#include "xcoordtransformer.h"

CXSecRectZoomItem::CXSecRectZoomItem(CX2DSectionWindow *pWindow, QGraphicsItem* parent) : QGraphicsItem(parent)
{
	setZValue(5);
	setOpacity(0.4);
	m_topLeft = QPoint(-999, -1);
	m_pWindow = pWindow;
}

void CXSecRectZoomItem::HandleMouseEvent(QMouseEvent *pEvent, EXMouseEventType eType)
{
	if (eType == eSecButtonPress && pEvent->button() == Qt::LeftButton)
		_leftButtonPressed(pEvent);
	else if (eType == eSecMouseMove)
		_mouseMoving(pEvent);
	else if (eType == eSecButtonRelease)
		_buttonRelease();
}

QRectF CXSecRectZoomItem::boundingRect() const
{
	double sceneX1, sceneY1, sceneX2, sceneY2;
	sceneX1 = qMin(m_topLeft.x(), m_bottomRight.x());
	sceneY1 = qMin(m_topLeft.y(), m_bottomRight.y());
	sceneX2 = qMax(m_topLeft.x(), m_bottomRight.x());
	sceneY2 = qMax(m_topLeft.y(), m_bottomRight.y());

	return  QRectF(QPointF(sceneX1, sceneY1), QPointF(sceneX2, sceneY2));
}

void CXSecRectZoomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_topLeft.x() == -999.)
		return;

	if(qAbs(m_topLeft.x() - m_bottomRight.x()) < 50 || qAbs(m_topLeft.y() - m_bottomRight.y()) < 50)
		painter->fillRect(QRectF(m_topLeft, m_bottomRight), Qt::red);
	else
		painter->fillRect(QRectF(m_topLeft, m_bottomRight), Qt::green);
}

void CXSecRectZoomItem::_leftButtonPressed(QMouseEvent *pEvent)
{
	CXSectionScene* pScene = (CXSectionScene*)m_pWindow->GetScene();
	CXCoordTransformer transformer(pScene);

	double sceneX, sceneY;
	transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), sceneX, sceneY);

	m_topLeft = QPointF(sceneX, sceneY);
	m_bottomRight = QPointF(sceneX, sceneY);
}

void CXSecRectZoomItem::_mouseMoving(QMouseEvent *pEvent)
{
	CXSectionScene* pScene = (CXSectionScene*)m_pWindow->GetScene();
	CXCoordTransformer transformer(pScene);

	double sceneX, sceneY;
	transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), sceneX, sceneY);


	m_bottomRight = QPointF(sceneX, sceneY);

	update();
}

void CXSecRectZoomItem::_buttonRelease()
{
	double sceneX1, sceneY1, sceneX2, sceneY2;
	sceneX1 = qMin(m_topLeft.x(), m_bottomRight.x());
	sceneY1 = qMin(m_topLeft.y(), m_bottomRight.y());
	sceneX2 = qMax(m_topLeft.x(), m_bottomRight.x());
	sceneY2 = qMax(m_topLeft.y(), m_bottomRight.y());

	m_topLeft = QPointF(-999, -1);

	CXSectionScene* pScene = (CXSectionScene*)m_pWindow->GetScene();
	CXCoordTransformer transformer(pScene);

	double ratiox1, ratioy1, ratiox2, ratioy2;
	transformer.Scene2Ratio(sceneX1, sceneY1, ratiox1, ratioy1);
	transformer.Scene2Ratio(sceneX2, sceneY2, ratiox2, ratioy2);

	if(sceneX2 - sceneX1 > 50 && sceneY2 - sceneY1 > 50)
		m_pWindow->RectZoomIn(QRectF(QPointF(ratiox1, ratioy1), QPointF(ratiox2, ratioy2)));
}