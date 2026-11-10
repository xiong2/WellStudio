#include <qpainter.h>
#include "xlvitemwell.h"
#include "xlvitemcurve.h"
#include "xlvscene.h"
#include "xlvwindowinfo.h"
#include "xviewinfolpwell.h"
#include "xwell.h"
#include "xglobal.h"

CXLVItemWell::CXLVItemWell(CXLVScene *pScene, QUuid objectID, CXViewInfoObject *pViewInfo, QGraphicsItem *parent)
	: QGraphicsRectItem(parent), m_objectID(objectID), m_pScene(pScene)
{
	m_pWinInfo = (CXLVWindowInfo *)m_pScene->GetWindowViewInfo();
	m_pViewInfo = (CXViewInfoLPWell *)pViewInfo;

	Configure();
}

void CXLVItemWell::Configure(qreal lastX)
{
	CXWell *pWell = dynamic_cast<CXWell *>(::GetObjectByID(m_objectID));
	qreal dSZ = m_pViewInfo->GetStartDepth();
	qreal dEZ = m_pViewInfo->GetEndDepth();

	qreal x, y, width, height;
	if (lastX == -999.25)
		x = m_pScene->GetRightEdge() + m_pWinInfo->m_iHIntv;
	else
		x = lastX + m_pWinInfo->m_iHIntv;

	if (m_pWinInfo->m_bUniqueDepth)
		y = (dSZ - m_pWinInfo->m_dSDepth) *  m_pWinInfo->m_dVScale + MARGIN;
	else
		y = MARGIN;

	width = m_pViewInfo->GetDepthTrackWidth();
	height = (dEZ - dSZ) * m_pWinInfo->m_dVScale + 2 * m_pWinInfo->m_iHeaderHeight;

	setRect(x, y, width, height);

	QList<QGraphicsItem *> listGItem = childItems();
	foreach(QGraphicsItem *pGItem, listGItem)
	{
		CXLVItemCurve *pCItem = dynamic_cast<CXLVItemCurve *>(pGItem);
		pCItem->Configure();
	}
}

void CXLVItemWell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(QColor("Black"), 2));
	QRectF rect = this->rect();

	painter->drawRect(rect.toRect());

	painter->setBrush(QBrush(QColor("gray")));
	rect.setBottom(rect.top() + m_pWinInfo->m_iHeaderHeight);
	painter->drawRect(rect.toRect());
	painter->drawText(rect, Qt::AlignCenter, ::GetObjectByID(m_objectID)->GetObjectName());

	rect.translate(0, m_pWinInfo->m_iHeaderHeight);
	rect.setRight(rect.left() + m_pViewInfo->GetDepthTrackWidth());
	painter->setBrush(QBrush(QColor("lightGray")));
	painter->drawRect(rect.toRect());
	painter->drawText(rect, Qt::AlignCenter, "Depth\n(m)");

	CXWell *pWell = dynamic_cast<CXWell *>(::GetObjectByID(m_objectID));
	qreal dSZ = m_pViewInfo->GetStartDepth();
	qreal dEZ = m_pViewInfo->GetEndDepth();
	int iZ = ((int)(dSZ / 100) + 1) * 100;
	if (m_pWinInfo->m_bUniqueDepth)
		dSZ = m_pWinInfo->m_dSDepth;
	while (iZ < dEZ)
	{
		qreal y = (iZ - dSZ) * m_pWinInfo->m_dVScale + 1.5 * m_pWinInfo->m_iHeaderHeight;
		rect.moveTop(y);
		painter->drawText(rect, Qt::AlignCenter, QString::number(iZ));
		iZ += 100;
	}
}