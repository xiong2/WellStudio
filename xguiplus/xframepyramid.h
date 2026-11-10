#pragma once
#include <qframe.h>
#include <qpainterpath.h>

class CXFramePyramid : public QFrame
{
public:
	CXFramePyramid(QWidget *parent = NULL);
	~CXFramePyramid() = default;

protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent) override;

	void drawAnno();
};