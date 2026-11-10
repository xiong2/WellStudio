#include <qpainter.h>
#include "xitemfb.h"
#include "xscenegather.h"

XItemFB::XItemFB(XSceneGather* pScene, QGraphicsItem* parent) : QGraphicsItem(parent), m_pScene(pScene)
{
}

XItemFB::~XItemFB()
{
	if (m_pData)
		delete[]m_pData;
}

QRectF XItemFB::boundingRect() const
{
	if (!m_points.isEmpty())
	{
		return m_points.boundingRect();
	}

	return QRectF();
}

void XItemFB::UpdateData(float* pData, int iNumTrace)
{
	if (m_pData)
		delete[]m_pData;

	m_pData = pData;
	m_iNumTrace = iNumTrace;

	MapToScene();
}

void XItemFB::MapToScene()
{
	m_points.clear();

	if (!m_pData)
		return;

	int i, iNumSample;
	m_pScene->GetSectionSize(i, iNumSample);
	float fSZ, fZInc, fEZ;
	m_pScene->GetZInfo(fSZ, fZInc);
	fEZ = fSZ + (iNumSample - 1) * fZInc;

	QRectF rectScene = m_pScene->sceneRect();
	float xIntv = rectScene.width() / m_iNumTrace;
	float yIntv = rectScene.height() / (fEZ - fSZ);

	for (i = 0; i < m_iNumTrace; i++)
	{
		if (m_pData[i] <= -999.)
			continue;

		qreal x = (i + 0.5) * xIntv;
		qreal y = (m_pData[i] - fSZ) * yIntv;
		m_points << QPointF(x, y);
	}

	update();
}

void XItemFB::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_points.isEmpty())
		return;

	CXViewInfoGather *pVInfo = m_pScene->GetViewInfo();
	QPen pen(pVInfo->GetFBColor());
	pen.setWidth(3);
	painter->setPen(pen);
	painter->drawPoints(m_points);
}