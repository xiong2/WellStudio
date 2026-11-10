#include <qevent.h>
#include <qdebug.h>
#include "xsecfaultpickingitem.h"
#include "xsectionscene.h"
#include "xfaultsticks.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xseismicutmtool.h"
#include "xgraphicsapi.h"
#include "xeventconsole.h"
#include "xglobal.h"
#include "xcoordtransformer.h"

#define FS_PICKINGTHRESHOLD 3

CXSecFaultPickingItem::CXSecFaultPickingItem(CX2DSectionWindow *pWindow, QGraphicsItem *parent): CXAbstractItem(pWindow)
{
	setZValue(2);
	m_eStatus = eSecFaultNull;
}


CXSecFaultPickingItem::~CXSecFaultPickingItem(void)
{
}

void CXSecFaultPickingItem::_UpdateData()
{
	m_pScene = (CXSectionScene *)scene();

	m_listSticks.clear();

	m_listDataLines.clear();
	m_listDrawLines.clear();
	m_listDataPoints.clear();
	m_listDrawPoints.clear();
	m_listIntersectSticks.clear();
	m_activeDataLine.clear();
	m_activeDrawLine.clear();
	m_rubberyLine = QLineF();
	m_eStatus = eSecFaultNull;

	CXFaultSticks *pFS = dynamic_cast<CXFaultSticks *>(GetItemObject());
	if (!pFS)
		return;

	CXObject *pGeoObj = m_pScene->GetBackgroundSection();
	if (!pGeoObj)
		return;

	if (pGeoObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(m_pScene->GetBackgroundSection());
		if (!pSection)
			return;

		if (pSection->GetSurveyID() != pFS->GetSurveyID())
			return;

		pFS->GetSticksOnSection((int)(pSection->GetSectionNumber()), pSection->GetSectionType(), m_listSticks);

		pFS->GetSticksIntersectSection((int)(pSection->GetSectionNumber()), pSection->GetSectionType(), m_listDataPoints, m_listIntersectSticks);
	}

	foreach(CXFaultStick *pStick, m_listSticks)
	{
		unsigned int iNumPoint;
		double *pData = pStick->GetXYZData(iNumPoint);
		int *pTraceNumber = pStick->GetTraceNumber();

		if (iNumPoint < 2 || !pData || !pTraceNumber)
			continue;

		QPolygonF line;
		for (int i = 0; i < iNumPoint; i++)
		{
			line << QPointF((float)pTraceNumber[i], pData[3 * i + 2]);
		}
		m_listDataLines << line;
	}

	MapToScene();
}

void CXSecFaultPickingItem::MapToScene()
{
	m_listDrawLines.clear();
	m_activeDrawLine.clear();
	m_listDrawPoints.clear();
	m_boundRect = QRectF();

	CXCoordTransformer transformer(m_pScene);
	double scenex, sceney;

	foreach(QPolygonF line, m_listDataLines)
	{
		QPolygonF sceneLine;
		int nNum = line.size();
		for (int i = 0; i < nNum; i++)
		{
			QPointF pos = line[i];
			transformer.World2Scene(pos.x(), pos.y(), scenex, sceney);

			sceneLine << QPointF(scenex, sceney);
		}

		m_listDrawLines << sceneLine;
		m_boundRect |= sceneLine.boundingRect();
	}

	int nNum = m_activeDataLine.size();
	for (int i = 0; i < nNum; i++)
	{
		QPointF pos = m_activeDataLine[i];

		transformer.World2Scene(pos.x(), pos.y(), scenex, sceney);
		m_activeDrawLine << QPointF(scenex, sceney);
	}
	m_boundRect |= m_activeDrawLine.boundingRect();

	foreach(QPointF point, m_listDataPoints)
	{
		transformer.World2Scene(point.x(), point.y(), scenex, sceney);
		QPointF scenePoint(scenex, sceney);
		m_listDrawPoints << scenePoint;
		m_boundRect |= QRectF(scenePoint + QPointF(-5, -5), scenePoint + QPointF(5, 5));
	}

	update();
}

void CXSecFaultPickingItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_listDrawLines.isEmpty() && m_activeDrawLine.isEmpty() && m_listDrawPoints.isEmpty())
		return;

	painter->save();
	QPen pen;
	pen.setColor(QColor("yellow"));
	pen.setWidth(3);
	painter->setPen(pen);

	foreach(QPolygonF line, m_listDrawLines)
	{
		painter->drawPolyline(line);
	}

	foreach(QPointF point, m_listDrawPoints)
	{
		painter->drawLine(point.x() - 5, point.y() - 5, point.x() + 5, point.y() + 5);
		painter->drawLine(point.x() - 5, point.y() + 5, point.x() + 5, point.y() - 5);
	}

	painter->drawPolyline(m_activeDrawLine);

	painter->drawLine(m_rubberyLine);

	pen.setWidth(8);
	painter->setPen(pen);
	painter->drawPoints(m_activeDrawLine);
	painter->restore();
}

void CXSecFaultPickingItem::HandleMouseEvent(QMouseEvent *pEvent, EXMouseEventType eType)
{
	if (eType == eSecButtonPress && pEvent->button() == Qt::LeftButton)
		_leftButtonPressed(pEvent);
	else if (eType == eSecButtonPress && pEvent->button() == Qt::MiddleButton)
		_middleButtonPressed(pEvent);
	else if (eType == eSecMouseMove)
		_mouseMoving(pEvent);
	else if (eType == eSecDoubleClick && pEvent->button() == Qt::LeftButton)
		_leftButtonDoubleClicked(pEvent);
	else if (eType == eSecDoubleClick && pEvent->button() == Qt::MiddleButton)
		_middleButtonDoubleClicked(pEvent);
	else if (eType == eSecButtonRelease)
		_buttonRelease();
}

void CXSecFaultPickingItem::_leftButtonPressed(QMouseEvent *pEvent)
{
	if (m_eStatus == eSecFaultNull)
	{
		//	Not picking yet, first is it clicking an active node?
		if (_pressOnActiveNode(pEvent->pos()))
			return;

		//	Begin a new stick, save back current one.
		if (m_pActiveStick)
		{
			m_listDataLines << m_activeDataLine;
			m_listSticks << m_pActiveStick;
		}

		//	create the new stick.
		m_pActiveStick = new CXFaultStick;
		m_activeDataLine.clear();
	}

	CXCoordTransformer transformer(m_pScene);
	double worldx, worldy;
	transformer.View2World(pEvent->pos().x(), pEvent->pos().y(), worldx, worldy);
	QPointF dPoint = QPointF(worldx, worldy);

	m_activeDataLine << dPoint;
	_updateActiveStick();

	m_eStatus = eSecFaultPicking;

	double scenex, sceney;
	transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), scenex, sceney);

	m_rubberyLine = QLineF(scenex, sceney, scenex, sceney);

	MapToScene();
}

void CXSecFaultPickingItem::_middleButtonPressed(QMouseEvent *pEvent)
{
	if (m_eStatus == eSecFaultPicking)
	{
		//	This means undo last point.
		if (m_activeDataLine.size() > 1)
		{
			m_activeDataLine.removeLast();
			m_activeDrawLine.removeLast();
			m_rubberyLine.setP1(m_activeDrawLine.last());

			_updateActiveStick();
		}
		else
		{
			m_activeDataLine.clear();
			m_activeDrawLine.clear();

			m_rubberyLine = QLineF();
			m_eStatus = eSecFaultNull;

			_updateActiveStick();
			delete m_pActiveStick;
			m_pActiveStick = NULL;
		}
	}
	else if (m_eStatus == eSecFaultNull)
	{
		if (_pressOnActiveNode(pEvent->pos()))
		{
			if (m_activeDataLine.size() <= 2)
			{
				//	Clear the stick.
				m_activeDataLine.clear();
				m_activeDrawLine.clear();

				_updateActiveStick();
				delete m_pActiveStick;
				m_pActiveStick = NULL;
			}
			else
			{
				//	Delete the pressed node.
				m_activeDataLine.remove(m_activeNode);
				m_activeDrawLine.remove(m_activeNode);
				_updateActiveStick();
			}
		}
	}

	MapToScene();
}

void CXSecFaultPickingItem::_mouseMoving(QMouseEvent *pEvent)
{
	CXCoordTransformer transformer(m_pScene);

	if (m_eStatus == eSecFaultPicking)
	{
		double scenex, sceney;
		transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), scenex, sceney);
		m_rubberyLine.setP2(QPointF(scenex, sceney));

		MapToScene();
	}
	else if (m_eStatus == eSecFaultMovingNode)
	{
		double worldx, worldy;
		transformer.View2World(pEvent->pos().x(), pEvent->pos().y(), worldx, worldy);
		QPointF dPoint(worldx, worldy);
		m_activeDataLine[m_activeNode] = dPoint;

		MapToScene();
	}
}

void CXSecFaultPickingItem::_buttonRelease()
{
	if (m_eStatus == eSecFaultMovingNode)
	{
		m_activeNode = -1;
		m_eStatus = eSecFaultNull;
		_updateActiveStick();
	}
}

void CXSecFaultPickingItem::_leftButtonDoubleClicked(QMouseEvent *pEvent)
{
	if (m_eStatus == eSecFaultPicking)
	{
		//	re-initialize.
		m_rubberyLine = QLineF();
		m_eStatus = eSecFaultNull;

		//	Double click while picking means finish one stick.
		if (m_activeDataLine.size() < 2)
		{
			//	First erase the effect of the implied mouse pressing.
			m_activeDataLine.clear();
			m_activeDrawLine.clear();
			if (m_pActiveStick)
				delete m_pActiveStick;
			m_pActiveStick = NULL;

			if (_pressOnStick(pEvent->pos()))
			{
				MapToScene();

				return;
			}		
		}
		else  if (m_pActiveStick)
		{
			//	Handle the pre-active stick.
			m_listDataLines << m_activeDataLine;
			m_activeDataLine.clear();

			m_listSticks << m_pActiveStick;

			MapToScene();
			return;
		}
	}
	else if (m_eStatus == eSecFaultNull)
	{
		//	Double click to active a stick?
		if (_pressOnActiveEnd(pEvent->pos()))
		{
			//	Double click to continue a stick.
			return;
		}
	}
}

void CXSecFaultPickingItem::_middleButtonDoubleClicked(QMouseEvent *pEvent)
{
	//	In picking model, ignore middle button double clicked.
	if (m_eStatus == eSecFaultPicking)
		return;

		//	First clear current active one.
	if (!m_activeDataLine.isEmpty() && m_pActiveStick)
	{
		m_listDataLines << m_activeDataLine;
		m_activeDataLine.clear();

		m_listSticks << m_pActiveStick;
	}

	if (_pressOnStick(pEvent->pos()))
	{
		//	Middle button double clicked on one stick, delete it!
		CXFaultSticks *pFS = dynamic_cast<CXFaultSticks *>(GetItemObject());
		if (!pFS)
			return;

		m_activeDataLine.clear();
		if (m_pActiveStick)
		{
			pFS->RemoveOneStick(m_pActiveStick);
			delete m_pActiveStick;
			m_pActiveStick = NULL;

			CXProcessEvent pEvent(m_pScene);
			pFS->AddEvent(EDataChanged);
		}
	}
	else
	{
		//	Let's check whether pressed on an intersect point.
		CXCoordTransformer transformer(m_pScene);
		
		double scenex, sceney;
		transformer.View2Scene(pEvent->pos().x(), pEvent->pos().y(), scenex, sceney);

		QPointF scenePoint(scenex, sceney);

		int iIDX = 0;
		foreach(QPointF point, m_listDrawPoints)
		{
			if (qAbs(point.x() - scenePoint.x()) < FS_PICKINGTHRESHOLD && qAbs(point.y() - scenePoint.y()) < FS_PICKINGTHRESHOLD)
			{
				CXFaultStick *pStick = m_listIntersectSticks[iIDX];

				//	Note this stick may be contained more than one time, since one stick may intersect more than one time.
				while (m_listIntersectSticks.contains(pStick))
				{
					int i = m_listIntersectSticks.indexOf(pStick);
					m_listDataPoints.removeAt(i);
					m_listDrawPoints.removeAt(i);
					m_listIntersectSticks.removeAt(i);
				}

				CXFaultSticks *pFS = dynamic_cast<CXFaultSticks *>(GetItemObject());
				pFS->RemoveOneStick(pStick);
				delete pStick;

				CXProcessEvent pEvent(m_pScene);
				pFS->AddEvent(EDataChanged);

				break;
			}

			iIDX++;
		}
	}

	MapToScene();
}

void CXSecFaultPickingItem::_updateActiveStick()
{
	CXFaultSticks *pFS = dynamic_cast<CXFaultSticks *>(GetItemObject());
	if (!pFS)
		return;

	unsigned int iNumPoint = m_activeDataLine.size();
	if (iNumPoint < 2)
	{
		if (m_pActiveStick)
			pFS->RemoveOneStick(m_pActiveStick);

		CXProcessEvent pEvent(m_pScene);
		pFS->AddEvent(EDataChanged);

		return;
	}

	CXObject *pGeoObj = m_pScene->GetBackgroundSection();
	if (!pGeoObj)
		return;

	EFaultStickType eStickType = eFTRandom;
	double *pXYZData = new double[iNumPoint * 3];
	int iSecNumber = 0;
	QUuid lineID;
	int *pTrace = new int[iNumPoint];
	if (pGeoObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(pGeoObj);

		CXSeismicUTMTool utm = pSection->GetUTM();
		if (pSection->GetSectionType() == eInlineSection)
			eStickType = eFTInline;
		else if (pSection->GetSectionType() == eCrosslineSection)
			eStickType = eFTCrossline;

		iSecNumber = (int)(pSection->GetSectionNumber());
		for (unsigned int i = 0; i < iNumPoint; i++)
		{
			double dX, dY;
			int iLine, iCDP;
			if (eStickType == eFTInline)
			{
				iLine = iSecNumber;
				iCDP = (int)(m_activeDataLine[i].x() + 0.5);
			}
			else
			{
				iCDP = iSecNumber;
				iLine = (int)(m_activeDataLine[i].x() + 0.5);
			}
			utm.LineToXY(iLine, iCDP, dX, dY);

			pXYZData[3 * i] = dX;
			pXYZData[3 * i + 1] = dY;
			pXYZData[3 * i + 2] = m_activeDataLine[i].y();
			pTrace[i] = (int)(m_activeDataLine[i].x() + 0.5);
		}
	}
	else if (pGeoObj->GetObjectType() == EXRandomSection)
	{
		CXSeismicRandomSection *pSection = dynamic_cast<CXSeismicRandomSection *>(pGeoObj);
		vector<double> vecX, vecY;
		pSection->GetXY(vecX, vecY);
		lineID = pSection->GetObjectID();

		for (unsigned int i = 0; i < iNumPoint; i++)
		{
			double dX, dY;
			int iLine, iCDP;

			pXYZData[3 * i] = vecX[(int)(m_activeDataLine[i].x())];
			pXYZData[3 * i + 1] = vecY[(int)(m_activeDataLine[i].x())];
			pXYZData[3 * i + 2] = m_activeDataLine[i].y();
			pTrace[i] = (int)(m_activeDataLine[i].x() + 0.5);
		}
	}

	m_pActiveStick->ResetData(pXYZData, iNumPoint, eStickType, lineID, iSecNumber, pTrace);

	pFS->AddOneStick(m_pActiveStick);

	CXProcessEvent pEvent(m_pScene);
	pFS->AddEvent(EDataChanged);
}

bool CXSecFaultPickingItem::_pressOnActiveNode(QPoint point)
{
	if (m_activeDrawLine.isEmpty())
		return false;

	CXCoordTransformer transformer(m_pScene);

	double scenex, sceney;
	transformer.View2Scene(point.x(), point.y(), scenex, sceney);

	int iIDX = 0;
	QPointF scenePoint(scenex, sceney);
	foreach(QPointF linePoint, m_activeDrawLine)
	{
		if (qAbs(scenePoint.x() - linePoint.x()) < FS_PICKINGTHRESHOLD && qAbs(scenePoint.y() - linePoint.y()) < FS_PICKINGTHRESHOLD)
		{
			m_activeNode = iIDX;
			m_eStatus = eSecFaultMovingNode;
			return true;
		}

		iIDX++;
	}

	return false;
}

bool CXSecFaultPickingItem::_pressOnActiveEnd(QPoint point)
{
	if (m_activeDrawLine.isEmpty())
		return false;

	CXCoordTransformer transformer(m_pScene);

	double scenex, sceney;
	transformer.View2Scene(point.x(), point.y(), scenex, sceney);

	int iIDX = 0;
	QPointF scenePoint(scenex, sceney);

	if (qAbs(scenePoint.x() - m_activeDrawLine.first().x()) < FS_PICKINGTHRESHOLD && qAbs(scenePoint.y() - m_activeDrawLine.first().y()) < FS_PICKINGTHRESHOLD)
	{
		std::reverse(m_activeDataLine.begin(), m_activeDataLine.end());

		m_eStatus = eSecFaultPicking;
		m_rubberyLine = QLineF(m_activeDrawLine.first(), m_activeDrawLine.first());
		return true;
	}
	else if (qAbs(scenePoint.x() - m_activeDrawLine.last().x()) < FS_PICKINGTHRESHOLD && qAbs(scenePoint.y() - m_activeDrawLine.last().y()) < FS_PICKINGTHRESHOLD)
	{
		m_eStatus = eSecFaultPicking;
		m_rubberyLine = QLineF(m_activeDrawLine.last(), m_activeDrawLine.last());
		return true;
	}

	return false;
}

bool CXSecFaultPickingItem::_pressOnStick(QPoint point)
{
	CXCoordTransformer transformer(m_pScene);

	double scenex, sceney;
	transformer.View2Scene(point.x(), point.y(), scenex, sceney);

	QPointF scenePoint(scenex, sceney);

	int iIDX = 0;
	foreach(QPolygonF line, m_listDrawLines)
	{
		int i, iSize = line.size();
		float *pXY = new float[2 * iSize];
		for (i = 0; i < iSize; i++)
		{
			pXY[2 * i] = line[i].x();
			pXY[2 * i + 1] = line[i].y();
		}

		if (CXGraphicsAPI::IsPointOnPolyline(i, scenePoint.x(), scenePoint.y(), pXY, iSize))
		{
			delete[]pXY;

			m_activeDrawLine = m_listDrawLines.takeAt(iIDX);
			m_activeDataLine = m_listDataLines.takeAt(iIDX);

			m_pActiveStick = m_listSticks.takeAt(iIDX);

			return true;
		}

		delete[]pXY;
		iIDX++;
	}

	return false;
}

void CXSecFaultPickingItem::FaultStickAssign(QUuid sourceFaultID, QUuid destFaultID)
{
	if (GetItemObject()->GetObjectID() != sourceFaultID)
	{
		qDebug() << "Somethig wrong about fault stick assign, source is not the active one!";
		return;
	}

	CXFaultSticks *pSFS = dynamic_cast<CXFaultSticks *>(GetItemObject());
	CXFaultSticks *pDFS = dynamic_cast<CXFaultSticks *>(::GetObjectByID(destFaultID));
	if (!pSFS || !pDFS)
	{
		qDebug() << "Somethig wrong about fault stick assign, source or destinate fault can not be found!";
		return;	
	}

	if (!m_pActiveStick)
	{
		qDebug() << "No active stick right now!";
		return;
	}

	//	Remove the active stick from current fault.
	pSFS->RemoveOneStick(m_pActiveStick);
	pDFS->AddOneStick(m_pActiveStick);
	m_activeDataLine.clear();
	m_pActiveStick = NULL;

	MapToScene();

	CXProcessEvent pEvent(m_pScene);
	pSFS->AddEvent(EDataChanged);
	pDFS->AddEvent(EDataChanged);
}