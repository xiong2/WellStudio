#ifndef GSDLGSELECTHORIZON_H
#define GSDLGSELECTHORIZON_H

#include <QDialog>
#include "xgui_global.h"
#include "ui_gsdlgselecthorizon.h"

class CXObject;
class GSGeologicStage;

class XGUI_EXPORT GSDlgSelectHorizon : public QDialog
{
	Q_OBJECT

public:
	GSDlgSelectHorizon(CXObject *pSurvey, GSGeologicStage *pGStage, QWidget *parent = 0);
	~GSDlgSelectHorizon();

public slots:
	virtual void accept();

private:
	Ui::GSDlgSelectHorizon ui;

	CXObject*			m_pSurvey;
	GSGeologicStage*	m_pStage;
};

#endif // GSDLGSELECTHORIZON_H
