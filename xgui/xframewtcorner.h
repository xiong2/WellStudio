#pragma once
#include <qframe.h>

class CXFrameWTCorner : public QFrame
{
public:
	CXFrameWTCorner(QWidget *parent = NULL);
	~CXFrameWTCorner();

	void ShowTWT(bool bShowTWT)
	{
		m_bShowTWT = bShowTWT;
	}

protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent) override;

	bool	m_bShowTWT = true;
};