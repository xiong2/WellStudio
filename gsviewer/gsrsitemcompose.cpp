#include "stdafx.h"
#include <qapplication.h>
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qgraphicssceneevent.h>
#include <qdebug.h>
#include "xglobalcoordtransform.h"
#include "gsutilities.h"
#include "gsrsitemcompose.h"
#include "xmathmacro.h"
#include "gsdlgrsa.h"
#include "gsstressmap.h"

GSRSItemCompose::GSRSItemCompose(GSDlgRSA *pDlgRSA, QList<QPointF> listP, CXGlobalCoordTransform *pCT, QGraphicsItem *parent)
	: QGraphicsRectItem(parent)
{
	m_vecCorners = listP.toVector();
	m_pDlgRSA = pDlgRSA;
	m_pCoordTransform = pCT;
	this->setZValue(5);
}

void GSRSItemCompose::AddOneSource(qreal x, qreal y, qreal dAzi)
{
	QPointF pos(x, y);
	QLineF line0(pos, m_vecCorners[0]);
	QLineF line1(pos, m_vecCorners[1]);
	QLineF line2(pos, m_vecCorners[2]);
	QLineF line3(pos, m_vecCorners[3]);

	QList<qreal> listAng;
	listAng << line0.angle() << line1.angle() << line2.angle() << line3.angle();
	qSort(listAng.begin(), listAng.end());

	qreal dRadius = qMax(line0.length(), line1.length());
	dRadius = qMax(dRadius, line2.length());
	dRadius = qMax(dRadius, line3.length());

	m_listSouPoint << x << y << dAzi << dRadius;
	qreal span = listAng[3] - listAng[0];
	if(span > 180)
	{
		span = 360 - listAng[2] + listAng[1];
		m_listSouPoint << 360 * 16 - listAng[1] * 16;
		m_listSouPoint << span * 16;
	}
	else
	{
		m_listSouPoint << 360 * 16 - listAng[3] * 16;
		m_listSouPoint << span * 16;
	}

	compose();
}

bool GSRSItemCompose::RemoveLastSource()
{
	if (m_listSouPoint.count() < 6)
		return false;

	m_listSouPoint.removeLast();
	m_listSouPoint.removeLast();
	m_listSouPoint.removeLast();
	m_listSouPoint.removeLast();
	m_listSouPoint.removeLast();
	m_listSouPoint.removeLast();

	compose();

	return true;
}
	
int GSRSItemCompose::findOneSource(QPointF pos, qreal dTor)
{
	int i, iNum = m_listSouPoint.count() / 6;
	for (i = 0; i < iNum; i++)
	{
		if(qAbs(m_listSouPoint[i * 6] - pos.x()) < dTor && qAbs(m_listSouPoint[i * 6 + 1] - pos.y()) < dTor)
			return i;
	}

	return -1;
}

bool GSRSItemCompose::ModifyOneSource(int iIDX, qreal x, qreal y, qreal dAzi)
{
	if(iIDX < 0 || iIDX >= m_listSouPoint.count() / 6)
		return false;

	QPointF pos(x, y);
	QLineF line0(pos, m_vecCorners[0]);
	QLineF line1(pos, m_vecCorners[1]);
	QLineF line2(pos, m_vecCorners[2]);
	QLineF line3(pos, m_vecCorners[3]);

	QList<qreal> listAng;
	listAng << line0.angle() << line1.angle() << line2.angle() << line3.angle();
	qSort(listAng.begin(), listAng.end());

	qreal dRadius = qMax(line0.length(), line1.length());
	dRadius = qMax(dRadius, line2.length());
	dRadius = qMax(dRadius, line3.length());

	m_listSouPoint[iIDX * 6] = x;
	m_listSouPoint[iIDX * 6 + 1] = y;
	if(dAzi != -999.)
		m_listSouPoint[iIDX * 6 + 2] = dAzi;
	m_listSouPoint[iIDX * 6 + 3] = dRadius;

	qreal span = listAng[3] - listAng[0];
	if(span > 180)
	{
		span = 360 - listAng[2] + listAng[1];
		m_listSouPoint[iIDX * 6 + 4] = 360 * 16 - listAng[1] * 16;
		m_listSouPoint[iIDX * 6 + 5] = span * 16;
	}
	else
	{
		m_listSouPoint[iIDX * 6 + 4] = 360 * 16 - listAng[3] * 16;
		m_listSouPoint[iIDX * 6 + 5] = span * 16;
	}

	compose();
	return true;
}

void GSRSItemCompose::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	setRect(scene()->sceneRect());

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);

	int iNum = m_listSouPoint.count() / 6;
	double dLen = 1000;

	qreal dL = 4000, dS = 2000;
	QPolygonF poly1, poly2;
	for (int i = 0; i < iNum; i++)
	{
		QPointF pos = QPointF(m_listSouPoint[i * 6], m_listSouPoint[i * 6 + 1]);
		qreal dAzi = m_listSouPoint[i * 6 + 2] * M_PI / 180;
		QPointF	locPoint = m_pCoordTransform->World2Local(pos);

		QPointF offset(m_listSouPoint[i * 6 + 3], m_listSouPoint[i * 6 + 3]);
		QPointF topLeft = m_pCoordTransform->World2Local(pos - offset), bottomRight = m_pCoordTransform->World2Local(pos + offset);
		QRectF rect(topLeft, bottomRight);

		QRadialGradient rG(locPoint, rect.width() / 2);
		rG.setColorAt(0, QColor(0, 255, 0, 200));
		rG.setColorAt(1, QColor(0, 255, 0, 50));
		painter->setBrush(QBrush(rG));
		painter->setPen(Qt::NoPen);
		painter->drawPie(rect, m_listSouPoint[i * 6 + 4], m_listSouPoint[i * 6 + 5]);

		painter->setBrush(QBrush(QColor("red")));
		poly1.clear();
		poly2.clear();
		poly1 << locPoint + QPointF(cos(dAzi) * dS, sin(dAzi) * dS)
			<< locPoint + QPointF(sin(dAzi) * dS / 8, -cos(dAzi) * dS / 8)
			<< locPoint + QPointF(-cos(dAzi) * dS, -sin(dAzi) * dS)
			<< locPoint + QPointF(-sin(dAzi) * dS / 8, cos(dAzi) * dS / 8);
		painter->drawPolygon(poly1);

		poly2 << locPoint + QPointF(sin(dAzi) * dL, -cos(dAzi) * dL)
			<< locPoint + QPointF(cos(dAzi) * dL / 8, sin(dAzi) * dL / 8)
			<< locPoint - QPointF(sin(dAzi) * dL, -cos(dAzi) * dL)
			<< locPoint + QPointF(-cos(dAzi) * dL / 8, -sin(dAzi) * dL / 8);
		painter->drawPolygon(poly2);
	}

	painter->setPen(QPen(QColor("blue"), 50));
	painter->drawPath(m_stressLines);

	painter->restore();
}

void GSRSItemCompose::MouseHandler(QGraphicsSceneMouseEvent* pEvent)
{
	if (pEvent->type() == QEvent::GraphicsSceneMousePress && m_iSouID == -1)
	{
		m_iSouID = findOneSource(m_pCoordTransform->Local2World(pEvent->scenePos()));

		if (m_iSouID != -1)
		{
			QApplication::setOverrideCursor(Qt::SizeAllCursor);
		}
	}
	else if (pEvent->type() == QEvent::GraphicsSceneMouseMove && m_iSouID != -1)
	{
		QPointF point = m_pCoordTransform->Local2World(pEvent->scenePos());
		ModifyOneSource(m_iSouID, point.x(), point.y());

		this->scene()->update();
	}
	else if (pEvent->type() == QEvent::GraphicsSceneMouseRelease && m_iSouID != -1)
	{
		QPointF point = m_pCoordTransform->Local2World(pEvent->scenePos());
		m_pDlgRSA->UpdateOneSou(m_iSouID, point);

		m_iSouID = -1;
		QApplication::restoreOverrideCursor();
	}
}

void GSRSItemCompose::compose()
{
	int iNumSou = m_listSouPoint.count() / 6;
	GSStressMap *pMap = m_pDlgRSA->GetCurrentMap();
	if(!pMap)
		return;

	CXSeismicUTMTool utm = pMap->GetUTM();
	double x, y, dTotalDis, dLen = 500.;
	QList<qreal> listWei, listAzi;
	QList<QPointF> listSPoint;

	int i, j, k, nI = utm.GetNI(), nJ = utm.GetNJ();
	for (k = 0; k < iNumSou; k++)
	{
		listSPoint << QPointF(m_listSouPoint[6 * k], m_listSouPoint[6 * k + 1]);
		listAzi << m_listSouPoint[6 * k + 2];
		listWei << 0.;
	}

	float *pData = pMap->GetData();
	float *pMagData = pData;
	pData += (nI * nJ);
    m_stressLines = QPainterPath();

	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			pMagData[i * nJ + j] = 1.;
			dTotalDis = 0;
			utm.IJToXY(i, j, x, y);
			for (k = 0; k < iNumSou; k++)
			{
				qreal dDis = QLineF(listSPoint[k], QPointF(x, y)).length();
				listWei[k] = 1000000. / dDis;
				dTotalDis += 1000000. / dDis;
			}

			dTotalDis = 1 / dTotalDis;
			for (k = 0; k < iNumSou; k++)
			{
				listWei[k] *= dTotalDis;
			}


			double dAzi = listAzi[0], dWei = listWei[0];
			for (k = 1; k < iNumSou; k++)
			{
				double dAzi2 = listAzi[k];
				if (dAzi2 - dAzi > 90)
					dAzi2 -= 180;
				else if (dAzi - dAzi2 > 90)
					dAzi -= 180;

				dAzi = dAzi * dWei + dAzi2 * listWei[k];
				dWei += listWei[k];
			}

			dAzi = 90 - dAzi;
			if (dAzi < 0)
				dAzi += 180;

			pData[i * nJ + j] = dAzi;

			//	Only draw lines one to four.
			if (i % 8 == 0 && j % 8 == 0)
			{
				QPointF p(x, y);
				QPointF p1(x - dLen, y);
				QPointF p2(x + dLen, y);

				QLineF line1(p, p2);
				line1.setAngle(-dAzi);
				QLineF line2(p, p1);
				line2.setAngle(180 - dAzi);

				QPointF line1p2 = m_pCoordTransform->World2Local(line1.p2());
				QPointF line2p2 = m_pCoordTransform->World2Local(line2.p2());

				m_stressLines.moveTo(line1p2);
				m_stressLines.lineTo(line2p2);
			}
		}
	}
}