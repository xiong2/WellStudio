#ifndef XFRAMEAXISVIEW_H
#define XFRAMEAXISVIEW_H

#include <qframe.h>
#include <qrect.h>
#include "xaxis.h"
#include "xgui_global.h"

/**
* @class CXFrameAxisView rlframeaxisview.h
* @brief The CXFrameAxisView class define a axis viewport
* @author daily 
* @date 4/24/2014
* @see QFrame
*/

class CXAxis;

class XGUI_EXPORT CXFrameAxisView : public QFrame
{
public:
	explicit CXFrameAxisView(QWidget *parent);

	~CXFrameAxisView() {}

	void SetXAxisRange(double dMin, double dMax) { m_dXMin = dMin; m_dXMax = dMax; }
	void SetYAxisRange(double dMin, double dMax) { m_dYMin = dMin; m_dYMax = dMax; }
	void SetGridEnable(bool bEnabled) { m_bGridEnabled = bEnabled; }
	void SetYAxisZoomEnabled(bool bEnabled) { m_bYZoomEnabled = bEnabled; }
protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent) override;
	virtual void wheelEvent(QWheelEvent *pWheelEvent) override;

	virtual void _DrawGraphics(QPainter *pDC, QRect& rect) = 0;
	virtual QRect _CalcRect();
	
	QRect _UpdateAxies();
	
protected:
	CXAxis *m_pXAxis;
	CXAxis *m_pYAxis;
	int m_iOffsetX = 40;

private:
	void _DrawXAxis(QPainter *pDC, QRect rect);
	void _DrawYAxis(QPainter *pDC, QRect rect);
	void _CalcXAxis(QRect sceneRect);
	void _CalcYAxis(QRect sceneRect);
	
private:
	double m_dXMin;
	double m_dYMin;
	double m_dXMax;
	double m_dYMax;
	bool m_bGridEnabled;
	bool m_bYZoomEnabled;
};

#endif // RLFRAMEAXISVIEW_H
