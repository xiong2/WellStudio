#pragma once

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgfracgridintr.h"

class CXObject;
class CXFracturePatch;

class XGUIPLUS_EXPORT CXDlgFracGridIntr : public QDialog
{
	Q_OBJECT

public:
	CXDlgFracGridIntr(CXObject*, QWidget *parent = Q_NULLPTR);
	~CXDlgFracGridIntr();

	void accept() override;

private:
	Ui::CXDlgFracGridIntr ui;

	CXFracturePatch*	m_pObj;
};
