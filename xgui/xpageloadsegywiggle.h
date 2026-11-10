#ifndef XPAGELOADSEGYWIGGLE_H
#define XPAGELOADSEGYWIGGLE_H

#include "xframeaxisview.h"

/*!
* @class	CXPageLoadSegyHistogram in kepageloadsegyhistogram.h
* @brief	The class define a axis viewport for load seg-y data step1 wiggle preview
* @author	pezy
* @date	2016-07-21
* @see		CXFrameAxisView
*/

class CXPageLoadSegyWiggle : public CXFrameAxisView
{
public:
	CXPageLoadSegyWiggle(QWidget *parent);
	~CXPageLoadSegyWiggle();
	void SetTraceData(float *, int nSampleNumber);

protected:
	virtual void _DrawGraphics(QPainter *pDC, QRect& rect) override;

private:
	float *m_pTraceData = nullptr;
	int m_nSampleNumber = 0;
};

#endif // RLPAGELOADSEGYWIGGLE_H
