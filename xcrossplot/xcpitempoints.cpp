#include <qpainter.h>
#include "xaxis.h"
#include "xcpitempoints.h"
#include "xcrossplotscene.h"
#include "xglobal.h"
#include "xcolormap.h"

CXCPItemPoints::CXCPItemPoints(QRectF rect, CXAxis *pHAxis, CXAxis *pVAxis, unsigned int iNum, double *pHData, double *pVData,
	QColor penColor, QColor fillColor, int iSize, int iShape, bool bNeedFree, QGraphicsItem *parent)
	: QGraphicsRectItem(rect, parent), m_pAxisX(pHAxis), m_pAxisY(pVAxis), m_iNum(iNum), m_pHData(pHData), m_pVData(pVData),
	m_penColor(penColor), m_fillColor(fillColor), m_iSize(iSize), m_iShape(iShape), m_bNeedFree(bNeedFree)
{

}

CXCPItemPoints::CXCPItemPoints(QRectF rect, CXAxis *pHAxis, CXAxis *pVAxis, CXAxis *pCAxis, unsigned int iNum, double *pHData, double *pVData,
	double *pCData, QColor penColor, int iCIDX, int iSize, int iShape, bool bNeedFree, QGraphicsItem *parent)
	: QGraphicsRectItem(rect, parent), m_pAxisX(pHAxis), m_pAxisY(pVAxis), m_pAxisC(pCAxis), m_iNum(iNum), m_pHData(pHData), m_pVData(pVData), m_pCData(pCData),
	m_penColor(penColor), m_iColormapIDX(iCIDX), m_iSize(iSize), m_iShape(iShape), m_bNeedFree(bNeedFree)
{

}

CXCPItemPoints::~CXCPItemPoints()
{
	if (m_bNeedFree)
	{
		//delete[]m_pHData;
		//delete[]m_pVData;
	}
}

void CXCPItemPoints::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	QRectF rect = scene()->sceneRect();
	rect.adjust(2 * SCENEMARGIN + 30, SCENEMARGIN + 10, -SCENEMARGIN - 10, -2 * SCENEMARGIN - 20);

	QPen pen(m_penColor);
	if (m_iSize > 2)
		pen.setWidth(2);

	painter->setPen(pen);

	qreal x, y;
	if (m_iColormapIDX == -1)
	{
		for (int i = 0; i < m_iNum; i++)
		{
			if (m_pHData[i] == ::g_dInvalidData || m_pVData[i] == ::g_dInvalidData)
				continue;

			x = rect.left() + rect.width() * (m_pHData[i] - m_pAxisX->GetBegin()) / m_pAxisX->GetValueRange();
			y = rect.bottom() - rect.height() * (m_pVData[i] - m_pAxisY->GetBegin()) / m_pAxisY->GetValueRange();

			switch (m_iShape)
			{
			case 0:
			{
				// Point
				painter->drawPoint(x, y);
				break;
			}
			case 1:
			{
				//	Cross.
				painter->drawLine(x - m_iSize, y, x + m_iSize, y);
				painter->drawLine(x, y - m_iSize, x, y + m_iSize);
				break;
			}
			case 2:
			{
				//	Triangle.
				QPoint points[3] = { QPoint(x, y - m_iSize), QPoint(x + m_iSize / 2, y + m_iSize / 2),  QPoint(x - m_iSize / 2, y + m_iSize / 2) };
				painter->drawPolygon(points, 3);
				break;
			}
			case 3:
			{
				//	Diamond.
				QPoint points[4] = { QPoint(x, y - m_iSize), QPoint(x + m_iSize, y),  QPoint(x, y + m_iSize), QPoint(x - m_iSize, y) };
				painter->drawPolygon(points, 4);
				break;
			}
			case 4:
			{
				//	Square.
				QPoint points[4] = { QPoint(x - m_iSize, y - m_iSize), QPoint(x + m_iSize, y - m_iSize),  QPoint(x + m_iSize, y + m_iSize), QPoint(x - m_iSize, y + m_iSize) };
				painter->drawPolygon(points, 4);
				break;
			}
			case 5:
			{
				//	Circle.
				painter->drawEllipse(x - m_iSize, y - m_iSize, 2 * m_iSize + 1, 2 * m_iSize + 1);
				break;
			}
			case 6:
			{
				//	Solid triangle.
				painter->setBrush(QBrush(m_fillColor));
				QPoint points[3] = { QPoint(x, y - m_iSize), QPoint(x + m_iSize / 2, y + m_iSize / 2),  QPoint(x - m_iSize / 2, y + m_iSize / 2) };
				painter->drawPolygon(points, 3);
				break;
			}
			case 7:
			{
				//	Solid diamond.
				painter->setBrush(QBrush(m_fillColor));
				QPoint points[4] = { QPoint(x, y - m_iSize), QPoint(x + m_iSize, y),  QPoint(x, y + m_iSize), QPoint(x - m_iSize, y) };
				painter->drawPolygon(points, 4);
				break;
			}
			case 8:
			{
				//	Solid square.
				painter->setBrush(QBrush(m_fillColor));
				QPoint points[4] = { QPoint(x - m_iSize, y - m_iSize), QPoint(x + m_iSize, y - m_iSize),  QPoint(x + m_iSize, y + m_iSize), QPoint(x - m_iSize, y + m_iSize) };
				painter->drawPolygon(points, 4);
				break;
			}
			case 9:
			{
				//	Solid circle.
				painter->setBrush(QBrush(m_fillColor));
				painter->drawEllipse(x - m_iSize, y - m_iSize, 2 * m_iSize + 1, 2 * m_iSize + 1);
				break;
			}
			}
		}
	}
	else
	{
		CXColormap *pColormap = CXColormap::GetColormap(m_iColormapIDX);
		double dMin = m_pAxisC->GetBegin(), dMax = m_pAxisC->GetEnd();
		double dVar = (dMax - dMin);
		for (int i = 0; i < m_iNum; i++)
		{
			if (m_pHData[i] == ::g_dInvalidData || m_pVData[i] == ::g_dInvalidData || m_pCData[i] == ::g_dInvalidData)
				continue;

			x = rect.left() + rect.width() * (m_pHData[i] - m_pAxisX->GetBegin()) / m_pAxisX->GetValueRange();
			y = rect.bottom() - rect.height() * (m_pVData[i] - m_pAxisY->GetBegin()) / m_pAxisY->GetValueRange();

			int iCIDX = 255 * (m_pCData[i] - dMin) / dVar;
			switch (m_iShape)
			{
			case 0:
			{
				// Point
				painter->drawPoint(x, y);
				break;
			}
			case 1:
			{
				//	Cross.
				painter->drawLine(x - m_iSize, y, x + m_iSize, y);
				painter->drawLine(x, y - m_iSize, x, y + m_iSize);
				break;
			}
			case 2:
			{
				//	Triangle.
				QPoint points[3] = { QPoint(x, y - m_iSize), QPoint(x + m_iSize / 2, y + m_iSize / 2),  QPoint(x - m_iSize / 2, y + m_iSize / 2) };
				painter->drawPolygon(points, 3);
				break;
			}
			case 3:
			{
				//	Diamond.
				QPoint points[4] = { QPoint(x, y - m_iSize), QPoint(x + m_iSize, y),  QPoint(x, y + m_iSize), QPoint(x - m_iSize, y) };
				painter->drawPolygon(points, 4);
				break;
			}
			case 4:
			{
				//	Square.
				QPoint points[4] = { QPoint(x - m_iSize, y - m_iSize), QPoint(x + m_iSize, y - m_iSize),  QPoint(x + m_iSize, y + m_iSize), QPoint(x - m_iSize, y + m_iSize) };
				painter->drawPolygon(points, 4);
				break;
			}
			case 5:
			{
				//	Circle.
				painter->drawEllipse(x - m_iSize, y - m_iSize, 2 * m_iSize + 1, 2 * m_iSize + 1);
				break;
			}
			case 6:
			{
				//	Solid triangle.
				painter->setBrush(QBrush(pColormap->GetColorAt(iCIDX)));
				QPoint points[3] = { QPoint(x, y - m_iSize), QPoint(x + m_iSize / 2, y + m_iSize / 2),  QPoint(x - m_iSize / 2, y + m_iSize / 2) };
				painter->drawPolygon(points, 3);
				break;
			}
			case 7:
			{
				//	Solid diamond.
				painter->setBrush(QBrush(pColormap->GetColorAt(iCIDX)));
				QPoint points[4] = { QPoint(x, y - m_iSize), QPoint(x + m_iSize, y),  QPoint(x, y + m_iSize), QPoint(x - m_iSize, y) };
				painter->drawPolygon(points, 4);
				break;
			}
			case 8:
			{
				//	Solid square.
				painter->setBrush(QBrush(pColormap->GetColorAt(iCIDX)));
				QPoint points[4] = { QPoint(x - m_iSize, y - m_iSize), QPoint(x + m_iSize, y - m_iSize),  QPoint(x + m_iSize, y + m_iSize), QPoint(x - m_iSize, y + m_iSize) };
				painter->drawPolygon(points, 4);
				break;
			}
			case 9:
			{
				//	Solid circle.
				painter->setBrush(QBrush(pColormap->GetColorAt(iCIDX)));
				painter->drawEllipse(x - m_iSize, y - m_iSize, 2 * m_iSize + 1, 2 * m_iSize + 1);
				break;
			}
			}
		}
	}
}