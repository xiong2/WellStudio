#pragma once
#include <qscrollarea.h>

class CXScrollArea : public QScrollArea
{
public:
	CXScrollArea(QWidget *parent = nullptr) : QScrollArea(parent)
	{
	}

protected:
	virtual void wheelEvent(QWheelEvent *e) override;
};