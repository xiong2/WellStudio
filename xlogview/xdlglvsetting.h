#pragma once

#include <QDialog>
#include "ui_xdlglvsetting.h"

class CXLVScene;
class CXLogView;

class XDlgLVSetting : public QDialog
{
	Q_OBJECT

public:
	XDlgLVSetting(CXLVScene *, QWidget *parent = Q_NULLPTR);
	~XDlgLVSetting();

	virtual void accept() override;

private slots:
	void apply();

private:
	void initUI();

	Ui::XDlgLVSetting ui;

	CXLVScene*	m_pScene;
	CXLogView*	m_pWindow;
};
