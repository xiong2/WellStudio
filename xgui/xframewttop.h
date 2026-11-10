#pragma once
#include <qframe.h>

class CXFrameWellTie;
class CXWavelet;

class CXFrameWTTop : public QFrame
{
public:
	CXFrameWTTop(CXFrameWellTie*, QWidget *parent = NULL);
	~CXFrameWTTop();

	void Populate(QString sDVName, QString sACName, QString sDenName, CXWavelet* pWavelet, double dSTime, double dETime);

protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent) override;

	void showWavelet(qreal);

	CXWavelet*		m_pWavelet;

	QString			m_sDVName;
	QString			m_sACName;
	QString			m_sDenName = "";
	int				m_iSTime;
	int				m_iETime;

	CXFrameWellTie*	m_pWTFrame;
};