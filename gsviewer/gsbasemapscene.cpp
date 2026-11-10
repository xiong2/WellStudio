#include "stdafx.h"
#include "gsbasemapscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QDebug>
#include "xglobalcoordtransform.h"
#include "xproject.h"
#include "xglobal.h"
#include "x3dsurvey.h"
#include "gsbasemapwindow.h"
#include "gstreenodecreator.h"
#include "gssection.h"
#include "gspdg.h"
#include "gsbmitemdefinerose.h"
#include "gsrsitemcompose.h"

GSBasemapScene::GSBasemapScene(const CXGlobalCoordTransform& coord, QObject *parent)
	: QGraphicsScene(parent), m_coord(coord)
{

}

GSBasemapScene::~GSBasemapScene()
{

}

void GSBasemapScene::SetMode(Mode mode, QGraphicsRectItem *pItem)
{
	m_mode = mode;

	if (pItem)
		m_pCompItem = dynamic_cast<GSRSItemCompose *>(pItem);
	else
		m_pCompItem = NULL;
}

void GSBasemapScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	switch (m_mode)
	{
	case eNone:
		return;
	case eCreateSection:
	{
		if (mouseEvent->button() == Qt::LeftButton)
		{
			if (!isInCurrentSurvey(mouseEvent->scenePos()))
				return;

			if (!m_vecBuildingItem.empty() && isSameIJInCurrentSurvey(m_vecBuildingItem.back()->line().p1(), mouseEvent->scenePos()))
				return;

			auto pBuildingItem = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
			pBuildingItem->setZValue(2);
			pBuildingItem->setPen(QPen(Qt::white, GetRealPixelSize(2)));
			m_vecBuildingItem.push_back(pBuildingItem);
			addItem(pBuildingItem);
		}
		else if (mouseEvent->button() == Qt::MiddleButton)
		{
			removeItem(m_vecBuildingItem.back());
			m_vecBuildingItem.pop_back();
		}

		break;
	}
	case eCreatePDG:
	{
		if (mouseEvent->button() == Qt::LeftButton)
		{
			if (!isInCurrentSurvey(mouseEvent->scenePos()))
				return;

			GSPDG* pPDG = NGSTreeNodeCreator::CreatePDG(m_pCurrentSurvey, m_coord.Local2World(mouseEvent->scenePos()));
			emit ShowThisObj(pPDG->GetObjectID());
		}

		break;
	}
	case eCreateRoseDiagram:
	{
		if (mouseEvent->button() == Qt::LeftButton)
		{
			if (!isInCurrentSurvey(mouseEvent->scenePos()))
				return;

			if (!m_pDefineRoseItem)
				return;

			if (m_pDefineRoseItem->GetMode() == 0)
				m_pDefineRoseItem->SetCentre(m_coord.Local2World(mouseEvent->scenePos()));

			//GSPDG* pPDG = NGSTreeNodeCreator::CreatePDG(m_pCurrentSurvey, m_coord.Local2World(mouseEvent->scenePos()));	
			//emit ShowThisObj(pPDG->GetObjectID());
		}

		break;
	}
	case eZoomByRect:
	{
		if (mouseEvent->button() == Qt::LeftButton)
		{
			m_pZoomRectItem = new QGraphicsRectItem(QRectF(mouseEvent->scenePos(), mouseEvent->scenePos()));
			m_pZoomRectItem->setZValue(2);
			m_pZoomRectItem->setPen(QPen(Qt::white, GetRealPixelSize(2)));
			addItem(m_pZoomRectItem);
		}

		break;
	}
	default:
		;
	}

	if (m_pCompItem)
		m_pCompItem->MouseHandler(mouseEvent);

	QGraphicsScene::mousePressEvent(mouseEvent);
}

void GSBasemapScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	if (eCreateSection == m_mode && !m_vecBuildingItem.empty())
	{
		m_vecBuildingItem.back()->setLine(QLineF(m_vecBuildingItem.back()->line().p1(), mouseEvent->scenePos()));
	}
	else if (eZoomByRect == m_mode && m_pZoomRectItem)
	{
		m_pZoomRectItem->setRect(QRectF(m_pZoomRectItem->rect().topLeft(), mouseEvent->scenePos()));
	}

	if (m_pCompItem)
		m_pCompItem->MouseHandler(mouseEvent);
}

void GSBasemapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	if (eZoomByRect == m_mode)
	{
		QRectF zoomRect = m_pZoomRectItem->rect();
		QGraphicsView* pView = views().front();
		pView->fitInView(zoomRect, Qt::KeepAspectRatio);
		removeItem(m_pZoomRectItem);
		m_pZoomRectItem = nullptr;
		m_zoomRectStack.push(zoomRect);
		EnableZoomUndo(true);
	}

	if (m_pCompItem)
		m_pCompItem->MouseHandler(mouseEvent);
}

void GSBasemapScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
		return;

	QPolygonF pickedPolyline;

	for (auto pBuildingItem : m_vecBuildingItem)
	{
		pickedPolyline << m_coord.Local2World(pBuildingItem->line().p1());
		removeItem(pBuildingItem);
		delete pBuildingItem;
	}
	m_vecBuildingItem.clear();

	GSSection* pNewSection = NGSTreeNodeCreator::CreateSection(m_pCurrentSurvey, pickedPolyline);
	emit ShowThisObj(pNewSection->GetObjectID());
}

bool GSBasemapScene::isInCurrentSurvey(const QPointF& pos)
{
	Q_ASSERT(m_pCurrentSurvey);

	const CXSeismicUTMTool& utm = m_pCurrentSurvey->GetUTM();
	QPolygonF surveyPolygon(4);
	utm.IJToXY(0, 0, surveyPolygon[0].rx(), surveyPolygon[0].ry());
	utm.IJToXY(0, utm.GetNJ() - 1, surveyPolygon[1].rx(), surveyPolygon[1].ry());
	utm.IJToXY(utm.GetNI() - 1, utm.GetNJ() - 1, surveyPolygon[2].rx(), surveyPolygon[2].ry());
	utm.IJToXY(utm.GetNI() - 1, 0, surveyPolygon[3].rx(), surveyPolygon[3].ry());

	surveyPolygon << surveyPolygon.front();
	Q_ASSERT(surveyPolygon.isClosed());

	if (surveyPolygon.containsPoint(m_coord.Local2World(pos), Qt::WindingFill))
		return true;

	return false;
}

bool GSBasemapScene::isSameIJInCurrentSurvey(const QPointF& lhs, const QPointF& rhs)
{
	Q_ASSERT(m_pCurrentSurvey);

	QPointF worldLhs = m_coord.Local2World(lhs);
	QPointF worldRhs = m_coord.Local2World(rhs);

	CXSeismicUTMTool& utm = m_pCurrentSurvey->GetUTM();
	int iL, jL, iR, jR;
	utm.XYToIJ(worldLhs.x(), worldLhs.y(), iL, jL);
	utm.XYToIJ(worldRhs.x(), worldRhs.y(), iR, jR);

	return iL == iR && jL == jR;
}

double GSBasemapScene::GetRealPixelSize(int size)
{
	auto pView = views().front();
	if (!pView)
		return size;

	QPolygonF scenePolygon = pView->mapToScene(QRect(QPoint(0, 0), QSize(size, size)));

	return QLineF(scenePolygon.at(0), scenePolygon.at(1)).length();
}

void GSBasemapScene::UndoLastZoom()
{
	QRectF lastRect = m_zoomRectStack.pop();
	QGraphicsView* pView = views().front();
	pView->fitInView(lastRect, Qt::KeepAspectRatio);
	EnableZoomUndo(!m_zoomRectStack.empty());
}

CX3DSurvey* GSBasemapScene::GetCurrentSurvey()
{
	return m_pCurrentSurvey;
}

void GSBasemapScene::SetCurrentSurvey(CX3DSurvey* pSurvey)
{
	m_pCurrentSurvey = pSurvey;
}

GSBMItemDefineRose* GSBasemapScene::CreateDefineRoseItem(double dRadius)
{
	if (m_pDefineRoseItem)
	{
		removeItem(m_pDefineRoseItem);
		delete m_pDefineRoseItem;
	}

	m_pDefineRoseItem = new GSBMItemDefineRose(this, m_coord, dRadius);
	addItem(m_pDefineRoseItem);

	return m_pDefineRoseItem;
}

void GSBasemapScene::RemoveDefineRoseItem()
{
	if (m_pDefineRoseItem)
	{
		removeItem(m_pDefineRoseItem);
		//delete m_pDefineRoseItem;
		m_pDefineRoseItem = NULL;
	}

	SetMode(GSBasemapScene::eNone);
}