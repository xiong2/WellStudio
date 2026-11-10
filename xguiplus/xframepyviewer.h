#pragma once
#include <qframe.h>

class XFramePyViewer : public QFrame
{
public:
	XFramePyViewer(QWidget *parent = NULL);
	~XFramePyViewer() = default;

	int SetVar(double *pVar);

	void SetImage(QImage image)
	{
		m_image = image;
	}

protected:
	virtual void paintEvent(QPaintEvent *) override;
	void drawVar();

	double	m_dMin;
	double	m_dMax;
	int		m_iMax;
	double*	m_pVar = nullptr;
	QImage	m_image;
};