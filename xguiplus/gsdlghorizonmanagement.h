#ifndef GSHORIZONMANAGEMENT_H
#define GSHORIZONMANAGEMENT_H

#include <QDialog>
#include "ui_gsdlghorizonmanagement.h"
#include "xguiplus_global.h"

class CXObject;
class CX3DSurvey;

class XGUIPLUS_EXPORT GSDlgHorizonManagement : public QDialog
{
	Q_OBJECT

public:
	GSDlgHorizonManagement(QWidget *parent = 0);
	~GSDlgHorizonManagement();

	virtual void accept() override;

protected:
	void initialUI();
	void refreshTable(int);
	void readVolFile();
	void _DeleteObj(CXObject* pObj);

	void resampleHorizons(CX3DSurvey *pSurvey);
	void updateHorizonsWithFaults(CX3DSurvey* pSurvey);
	void calculateIsoHorizonFaultTraces(CX3DSurvey* pSurvey);
	void updateDepthHorizons(CX3DSurvey *pSurvey);

private:
	Ui::GSDlgHorizonManagement ui;
};

#endif // GSHORIZONMANAGEMENT_H
