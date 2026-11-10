#pragma once

#include <qsvgwidget.h>
#include "xguiplus_global.h"

class QPaintEvent;

class XGUIPLUS_EXPORT CXSvgWidget : public QSvgWidget
{
	
public:
	CXSvgWidget(QWidget *parent = 0);
	virtual ~CXSvgWidget();

protected:
	virtual void paintEvent(QPaintEvent *event);

private:
	void slotTableMenuRequest(const QPoint &);

	void slotKeepAspectRatio();
	void slotCancelAspectRatio();

private:
	bool m_nKeepAspectRatio;


};
