#include <qpainter.h>
#include "xlvitemwelltops.h"
#include "xlvitemwell.h"
#include "xlvscene.h"
#include "xlvwindowinfo.h"
#include "xviewinfolpwelltops.h"
#include "xwell.h"
#include "xwelltops.h"
#include "xglobal.h"

CXLVItemWellTops::CXLVItemWellTops(CXLVScene *pScene, QUuid objectID, CXViewInfoObject *pViewInfo, QGraphicsItem *parent)
	: QGraphicsRectItem(parent), m_objectID(objectID), m_pScene(pScene)
{
	m_pWinInfo = (CXLVWindowInfo *)m_pScene->GetWindowViewInfo();
	m_pViewInfo = (CXViewInfoLPWellTops *)pViewInfo;

	CXWellTops *pTops = dynamic_cast<CXWellTops *>(::GetObjectByID(m_objectID));

	QList<CXObject *> listFor = pTops->GetChildren(EXWellTopFormation);
	foreach(CXObject *pF, listFor)
	{
		m_sListFormation << pF->GetObjectName();
		m_listColor << pF->GetColor();
	}

	setRect(m_pScene->sceneRect());

	setZValue(2);
}

void CXLVItemWellTops::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QVector<CXLVItemWell *>& vecItemWell = m_pScene->GetAllWellItems();
	if (vecItemWell.isEmpty())
		return;

	CXWellTops *pTops = dynamic_cast<CXWellTops *>(::GetObjectByID(m_objectID));

	double dY, dLeftY, dStart, dEnd;
	for (int i = 0; i < m_sListFormation.size(); i++)
	{
		dLeftY = -1;
		for (int j = 0; j < vecItemWell.size(); j++)
		{
			CXLVItemWell *pWItem = vecItemWell[j];
			QRectF rect = pWItem->rect();
			CXWell *pWell = (CXWell *)::GetObjectByID(pWItem->GetObjectID());
			pWell->GetDepthRange(dStart, dEnd);
			double dMD = pTops->GetOneRecord(pWell->GetObjectName(), m_sListFormation[i]);
			if (dMD == ::g_dInvalidData || dMD < dStart || dMD > dEnd)
			{
				dLeftY = -1;
				continue;
			}

			QPen pen(m_listColor[i]);
			pen.setWidth(m_pViewInfo->GetLineWidth());
			pen.setStyle((Qt::PenStyle)(m_pViewInfo->GetLineStyle()));
			painter->setPen(pen);
			dY = rect.y() + (dMD - dStart) * m_pWinInfo->m_dVScale + 2 * m_pWinInfo->m_iHeaderHeight;
			painter->drawLine(rect.x(), dY, rect.right(), dY);

			if (dLeftY != -1 && m_pViewInfo->GetConnect())
				painter->drawLine(rect.x(), dY, rect.x() - m_pWinInfo->m_iHIntv, dLeftY);
			else if (m_pViewInfo->GetShowNameOnLeft())
			{
				QRectF textRect = QRectF(rect.x() - 100, dY - 10, 90, 20);
				painter->drawText(textRect, Qt::AlignRight, m_sListFormation[i]);
			}

			if (m_pViewInfo->GetShowNameOnRight() && (!m_pViewInfo->GetConnect() || j == vecItemWell.size() - 1))
			{
				QRectF textRect = QRectF(rect.right() + 10, dY - 10, 90, 20);
				painter->drawText(textRect, Qt::AlignLeft, m_sListFormation[i]);
			}

			dLeftY = dY;
		}
	}
}