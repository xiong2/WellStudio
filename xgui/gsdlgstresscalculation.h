#ifndef GSDLGSTRESSCALCULATION_H
#define GSDLGSTRESSCALCULATION_H

#include <QDialog>
#include "xgui_global.h"
#include "ui_gsdlgstresscalculation.h"

class CXObject;

class XGUI_EXPORT GSDlgStressCalculation : public QDialog
{
	Q_OBJECT

public:
	GSDlgStressCalculation(CXObject * = NULL, QWidget *parent = 0);
	~GSDlgStressCalculation();

	virtual void accept() override;

protected:
	void initialUI();
	void refreshTable(int);	
	void slotCheckBox(int);
	void slotButtonClicked();

private:
	Ui::GSDlgStressCalculation ui;
	CXObject *			m_pIsopach;
	QList<CXObject *>	m_listIsopach;
};

#endif // GSDLGSTRESSCALCULATION_H
