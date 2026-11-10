#pragma once
#include <qframe.h>

class CXFrameTDCurve : public QFrame
{
public:
	CXFrameTDCurve(QWidget *parent = NULL);
	~CXFrameTDCurve();

	void Populate(double *, int);

protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent) override;

	void drawAnno();
	void drawCurve();

	double*	m_pDData = NULL;
	double*	m_pTData = NULL;
	double	m_dVScale;
	double	m_dHScale;
	int		m_iNum = 0;
};
