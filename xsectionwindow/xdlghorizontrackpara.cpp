#include "xdlghorizontrackpara.h"

CXDlgHorizonTrackPara::CXDlgHorizonTrackPara(QWidget *parent): CXBaseDialog(parent)
{
	ui.setupUi(this);
	this->GetMainLayout()->addLayout(ui.gridLayout_4, 0, 0, 1, 2);
}

CXDlgHorizonTrackPara::~CXDlgHorizonTrackPara()
{

}

void CXDlgHorizonTrackPara::OnOK()
{

}