#pragma once
#include <QGraphicsRectItem>
#include "xhistogram.h"

class CXAxis;

class CXHistItem : public QGraphicsRectItem
{
public:
	CXHistItem(const CXHistogram& histogram, QRectF, CXAxis *, CXAxis *, int iBinNum = 256, QGraphicsItem *parent = 0);
	~CXHistItem();

	void SetBinNum(int);

	double Get2ndMaxValue();

	void SetColor(QColor color)
	{
		m_color = color;
	}

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

	const CXHistogram& m_histogram;
	std::vector<double>		m_vecX;
	std::vector<double>		m_vecY;
	
	QColor	m_color = QColor("green");
	double m_dBinWidth = 0.0;
	CXAxis	*m_pAxisX = NULL;
	CXAxis	*m_pAxisY = NULL;
};