#include <qpainter.h>
#include "xhistitemname.h"

CXHistItemName::CXHistItemName(QRectF rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent)
{
}

void CXHistItemName::AddItem(QUuid objID, QString sName, QColor color)
{
	foreach(SNameItem item, m_vecNameItem)
	{
		if (item.m_objID == objID)
			return;
	}

	SNameItem newItem;
	newItem.m_objID = objID;
	newItem.m_sName = sName;
	newItem.m_color = color;
	m_vecNameItem.append(newItem);
}

void CXHistItemName::RemoveItem(QUuid objID)
{
	for (int i = 0; i < m_vecNameItem.size(); i++)
	{
		if (m_vecNameItem[i].m_objID == objID)
		{
			m_vecNameItem.removeAt(i);
			return;
		}
	}
}

void CXHistItemName::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	if (m_vecNameItem.isEmpty())
		return;

	QFont font = painter->font();
	font.setPixelSize(16);
	painter->setFont(font);
	QRectF rect = boundingRect();

	for (int i = 0; i < m_vecNameItem.size(); i++)
	{
		painter->setPen(m_vecNameItem[i].m_color);
		painter->drawText(rect.left() + 60, rect.top() + 30 + i * 20, m_vecNameItem[i].m_sName);
	}
}