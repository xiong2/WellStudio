#pragma once
#include <QGraphicsRectItem>
#include <quuid.h>

struct SNameItem
{
	QUuid	m_objID;
	QString	m_sName;
	QColor	m_color;
};

class CXHistItemName : public QGraphicsRectItem
{
public:
	CXHistItemName(QRectF, QGraphicsItem *parent = 0);

	void AddItem(QUuid objID, QString sName, QColor color);
	void RemoveItem(QUuid);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

	QVector<SNameItem>	m_vecNameItem;
};
