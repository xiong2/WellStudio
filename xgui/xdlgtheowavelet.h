#pragma once

#include <QDialog>
#include "xgui_global.h"
#include "ui_xdlgtheowavelet.h"

class CXWavelet;

class XGUI_EXPORT XDlgTheoWavelet : public QDialog
{
	Q_OBJECT

public:
	XDlgTheoWavelet(QWidget *parent = Q_NULLPTR);
	~XDlgTheoWavelet();

	void accept() override;

protected slots:
	void slotWaveletType(int);
	void slotPreview();

private:
	Ui::XDlgTheoWavelet ui;

	CXWavelet*	m_pWavelet = NULL;

	void generateWavelet();
};
