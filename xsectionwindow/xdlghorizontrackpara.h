#ifndef XDLGHORIZONTRACKPARA_H
#define XDLGHORIZONTRACKPARA_H

#include <QWidget>
#include "xbasedialog.h"
#include "ui_xdlghorizontrackpara.h"

class CXDlgHorizonTrackPara : public CXBaseDialog
{
	Q_OBJECT

public:
	CXDlgHorizonTrackPara(QWidget *parent = 0);
	~CXDlgHorizonTrackPara();

	virtual void OnOK();

private:
	void _init();

	Ui::CXDlgHorizonTrackPara ui;
};

#endif // KEDLGHORIZONTRACKPARA_H
