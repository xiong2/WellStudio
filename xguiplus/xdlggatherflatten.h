#pragma once

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlggatherflatten.h"

class CXSeismicDataVolume;

class XGUIPLUS_EXPORT XDlgGatherFlatten : public QDialog
{
	Q_OBJECT

public:
	XDlgGatherFlatten(CXSeismicDataVolume *, QWidget *parent = Q_NULLPTR);
	~XDlgGatherFlatten();

	virtual void accept() override;

private:
	void initGUI();

	Ui::XDlgGatherFlatten ui;

	CXSeismicDataVolume*	m_pDV = nullptr;
};
