#pragma once
#include <qframe.h>

class CXFrameCorrelation : public QFrame
{
public:
	CXFrameCorrelation(QWidget *parent = NULL){}
	~CXFrameCorrelation() {}

	void Populate(int iHalfWin, double dStep, float *pData);

protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent) override;

	void showGrid();
	void adjustCurve();

	QRect			m_rect;
	QPolygonF		m_poly;
	float			m_fMaxPos;
	float			m_fMaxCor;
	qreal			m_dPos;
	float			m_fZeroCor;
	int				m_iHalfWin = 100;
};