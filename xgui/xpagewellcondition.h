#ifndef XPAGEWELLCONDITION_H
#define XPAGEWELLCONDITION_H

#include <QDialog>
#include "xgui_global.h"

namespace Ui {class CXPageWellCondition;};

//!@brief	The class provides a calculated page for WellCondition of Reservoirmodel
//!@author	Pezy
//!@date	Dec. 18th, 2014
//!@see     CXWellCondition

class CXReservoirModel;
class CXWellCondition;
class CXWell;

class XGUI_EXPORT CXPageWellCondition : public QDialog
{
	Q_OBJECT

public:
	CXPageWellCondition(CXReservoirModel *pModel, QWidget *parent = 0);
	~CXPageWellCondition();

	virtual void accept();

private:
	void _Init();
	void _InitData();

private slots:
	void slotSelectAllCalcItem();
	void slotUnSelectAllCalcItem();
	void slotSelectAllUnCalcItem();
	void slotUnSelectAllUnCalcItem();

private:
	Ui::CXPageWellCondition *m_pUi;
	CXReservoirModel *m_pModel;
	CXWellCondition *m_pWellCondition;

	QList<CXWell*> m_listCalculatedWell;
	QList<CXWell*> m_listUnCalcWell;
};

#endif // RLPAGEWELLCONDITION_H
