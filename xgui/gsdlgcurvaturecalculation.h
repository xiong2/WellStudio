#pragma once
#include <QDialog>
#include "ui_gsdlgcurvaturecalculation.h"
#include "xgui_global.h"

class CXObject;

class XGUI_EXPORT GSDlgCurvatureCalculation : public QDialog {
	Q_OBJECT

public:
	GSDlgCurvatureCalculation(CXObject *, QWidget * parent = Q_NULLPTR);
	~GSDlgCurvatureCalculation();

	virtual void accept() override;

protected:
	void initialUI();

private:
	Ui::GSDlgCurvatureCalculation ui;

	CXObject *			m_pHorizon;
};
