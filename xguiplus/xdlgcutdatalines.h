#pragma once

#include <QDialog>
#include "ui_xdlgcutdatalines.h"
#include "xguiplus_global.h"

class CXObject;
class CX2DSurvey;

class XGUIPLUS_EXPORT XDlgCutDataLines : public QDialog
{
	Q_OBJECT

public:
	XDlgCutDataLines(CXObject *pSurvey, QWidget *parent = Q_NULLPTR);
	~XDlgCutDataLines();

	void accept() override;

private:
	void initGUI();

	Ui::XDlgCutDataLines ui;

	CX2DSurvey*	m_pSurvey = nullptr;
};
