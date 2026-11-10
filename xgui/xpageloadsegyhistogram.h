#ifndef XPAGELOADSEGYHISTOGRAM_H
#define XPAGELOADSEGYHISTOGRAM_H

#include "xframeaxisview.h"
#include "xhistogram.h"

/*!
 * @class	CXPageLoadSegyHistogram in kepageloadsegyhistogram.h
 * @brief	The class define a axis viewport for load seg-y data step1 histogram preview
 * @author	pezy
 * @date	2016-07-21
 * @see		CXFrameAxisView
 */

class CXPageLoadSegyHistogram : public CXFrameAxisView
{
public:
	CXPageLoadSegyHistogram(QWidget *parent);
	~CXPageLoadSegyHistogram();

	void SetTraceData(float *, int);

protected:
	virtual void _DrawGraphics(QPainter *pDC, QRect& rect);

private:
	CXHistogram m_histogram;
};

#endif // RLPAGELOADSEGYHISTOGRAM_H
