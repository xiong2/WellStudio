#ifndef XPAGELOADSEGYUTMVIEW_H
#define XPAGELOADSEGYUTMVIEW_H

#include "xframeaxisview.h"
#include "xgui_global.h"

/*!
 *	@class:	CXPageLoadSegyUtmView in the file "kepageloadsegyutmview.h"
 *	@brief:	The class provides the glance of UTM Survey Rectange.
 *	@author:pezy
 *	@date:	2017-06-09
 *	@see:
 */
class XGUI_EXPORT CXPageLoadSegyUtmView : public CXFrameAxisView
{
    Q_OBJECT

public:
    CXPageLoadSegyUtmView(QWidget* parent);
    ~CXPageLoadSegyUtmView();

	//@brief: the order should be FIFX -> FILX -> LIFX -> LILX
	void SetPoints(std::vector<QPointF> vecPoints, std::vector<int> vecIndex = {1, 2, 3, 4});
protected:
    virtual void _DrawGraphics(QPainter* pDC, QRect& rect) override;
    virtual QRect _CalcRect() override;
    virtual void wheelEvent(QWheelEvent *pWheelEvent) override{}
private:
    std::vector<QPointF> m_vecPoints;
	std::vector<int> m_vecIndex;
    QRect m_squareGridRect;
};

#endif // KEPAGELOADSEGYUTMVIEW_H
