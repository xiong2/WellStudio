#ifndef XPAGEWELLCONDITIONUPSCALE_H
#define XPAGEWELLCONDITIONUPSCALE_H

#include <QDialog>
#include "xgui_global.h"
#include "xobject.h"

namespace Ui {class CXPageWellConditionUpscale;};

//!@brief	The class provides a upscale page for WellCondition of Reservoirmodel
//!@author	Pezy
//!@date	Feb. 4th, 2015
//!@see     CXWellCondition

class CXWellCondition;

class XGUI_EXPORT CXPageWellConditionUpscale : public QDialog
{
	Q_OBJECT

public:
	CXPageWellConditionUpscale(CXWellCondition *pWellConditoin, QWidget *parent = 0);
	~CXPageWellConditionUpscale();

	virtual void accept(void);

private:
	void _Init(void);
	void _InitData(void);

private slots:
	void slotSelectAll(void);
	void slotDisSelectAll(void);

private:
	Ui::CXPageWellConditionUpscale *m_pUi;
	CXWellCondition *m_pWellCondition;
	QList<CXObject *> m_listLogAlias;
	
};

#endif // RLPAGEWELLCONDITIONUPSCALE_H
