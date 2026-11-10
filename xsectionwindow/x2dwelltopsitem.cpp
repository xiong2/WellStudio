#include <QVector2D>
#include "x2dwelltopsitem.h"
#include "xwelltopformation.h"
#include "xglobal.h"
#include "x2dsectionwindow.h"
#include "xviewinfo3dwelltopformation.h"
#include "xautogrid.h"
#include "xsectionscene.h"
#include "x2dwellitem.h"
#include "xcoordtransformer.h"

CX2DWelltopsItem::CX2DWelltopsItem(CX2DSectionWindow *pWindow,QGraphicsItem *parent):CXAbstractItem(pWindow)
{
	this->setZValue(3);
}


CX2DWelltopsItem::~CX2DWelltopsItem(void)
{
}
QRectF CX2DWelltopsItem::boundingRect() const
{
	return scene()->sceneRect();
}

void  CX2DWelltopsItem::_UpdateData()
{	
	MapToScene();
}

void CX2DWelltopsItem::MapToScene()
{
	CXSectionScene* pScene = (CXSectionScene*)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;


	m_VecPoints.clear();
	CXWellTopFormation *pFormation = dynamic_cast<CXWellTopFormation*>(GetItemObject());
	CXViewInfo3DWellTopFormation *pFormationViewInfo = dynamic_cast<CXViewInfo3DWellTopFormation*>(m_pViewInfo);

	//	Check wells showing right now!
	QList<CXAbstractItem *> listWellItem = pScene->FindAllAbsItems(EXWell);

	int i, iWidth = (int)pFormationViewInfo->GetRadius();
	foreach(CXAbstractItem *pObjItem, listWellItem)
	{
		CX2DWellItem *pWellItem = (CX2DWellItem *)pObjItem;
		QString sWellName = pWellItem->GetItemObject()->GetObjectName();
		QVector<QPointF> vecPathData = pWellItem->GetPathData();
		QVector<double> vecPathMD = pWellItem->GetPathMD();
		double dDepth = pFormation->GetDepthOnWell(sWellName);

		for (i = 0; i < vecPathMD.size() - 1; i++)
		{
			if (vecPathMD[i] < dDepth && vecPathMD[i + 1] > dDepth)
			{
				float dMDIntval = vecPathMD[i + 1] - vecPathMD[i];

				float fX = vecPathData[i].x() + (dDepth - vecPathMD[i]) * (vecPathData[i + 1].x() - vecPathData[i].x()) / dMDIntval;
				float fY = vecPathData[i].y() + (dDepth - vecPathMD[i]) * (vecPathData[i + 1].y() - vecPathData[i].y()) / dMDIntval;

				transformer.World2Scene(vecPathData[i].x(), vecPathData[i].y(), scenex, sceney);
				QPointF FirstPointF(scenex, sceney);

				transformer.World2Scene(vecPathData[i + 1].x(), vecPathData[i + 1].y(), scenex, sceney);
				QPointF LastPointF(scenex, sceney);

				QLineF LineAB(FirstPointF, LastPointF);
				QLineF LineArr = LineAB.normalVector();

				QVector2D vecA(LineArr.x1(), LineArr.y1());
				QVector2D vecB(LineArr.x2(), LineArr.y2());
				QVector2D vecBA = vecB - vecA;
				vecBA.normalize();
				QVector2D len = vecBA*iWidth;
				QPointF offsetPoint = len.toPointF();

				transformer.World2Scene(fX, fY, scenex, sceney);

				QPointF pos(scenex, sceney);

				m_VecPoints << pos - offsetPoint;
				m_VecPoints << pos + offsetPoint;

				break;
			}
		}
	}
	
	update();
}

void CX2DWelltopsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	CXViewInfo3DWellTopFormation *pFormationViewInfo = dynamic_cast<CXViewInfo3DWellTopFormation*>(m_pViewInfo);
	QString sFName = GetItemObject()->GetObjectName();

	QPen pen;
	pen.setWidth(pFormationViewInfo->GetHeight());
	painter->setFont(QFont(pFormationViewInfo->GetFormationAnnFont(), pFormationViewInfo->GetFormationAnnSize()));
	QRect rect = CXAutoGrid::TextRect(QFont(pFormationViewInfo->GetFormationAnnFont()), sFName);

	for (int i = 0; i < m_VecPoints.size(); i += 2)
	{
		pen.setColor(pFormationViewInfo->GetWellTopFormationColor());
		painter->setPen(pen);
		painter->drawLine(m_VecPoints[i], m_VecPoints[i + 1]);

		if (pFormationViewInfo->GetFormationAnnVisible())
		{
			pen.setColor(pFormationViewInfo->GetFormationAnnColor());
			painter->setPen(pen);

			QColor bgColor = pFormationViewInfo->GetFormationBgrColor();
			bgColor.setAlpha((int)(255 - 2.55 * pFormationViewInfo->GetFormationBgrTrans()));

			QRect rec1t(m_VecPoints[i + 1].x() + 8, m_VecPoints[i + 1].y() - rect.height() / 2, rect.width(), rect.height());
			painter->fillRect(rec1t, bgColor);
			painter->drawText(rec1t, Qt::AlignCenter, sFName);
		}
	}
}