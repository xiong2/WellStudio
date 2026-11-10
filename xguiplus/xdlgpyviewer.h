#pragma once

#include <qtimer.h>
#include <QDialog>
#include "ui_xdlgpyviewer.h"


class XDlgPyViewer : public QDialog
{
	Q_OBJECT

public:
	XDlgPyViewer(QWidget *parent = Q_NULLPTR);
	~XDlgPyViewer();

	void ResizeFrame(int, int, int, int, float *);

	void accept() override;

private slots:
	void slotPlay();
	void slotSpeed();
	void slotSetAng();

private:
	Ui::XDlgPyViewer ui;

	int		m_iAng = 90;
	int		m_iAStep = 1;
	int		m_iWidth;
	int		m_iHeight;

	QTimer			m_qTimer;
	unsigned int	m_iTimeIntv = 100;

	unsigned int*	m_pImgData = nullptr;
	float*			m_pData = nullptr;
	float*			m_pFData = nullptr;

	double			m_pVariance[360];

	void updateView();
	void calVariance();
};
