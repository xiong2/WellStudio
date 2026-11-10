#ifndef XDLGEXPORTHORIZONS_H
#define XDLGEXPORTHORIZONS_H

#include <QDialog>
#include "ui_xdlgexporthorizons.h"
#include "xguiplus_global.h"

class CXObject;

class XGUIPLUS_EXPORT CXDlgExportHorizons : public QDialog
{
	Q_OBJECT

public:
	CXDlgExportHorizons(CXObject *, QWidget *parent = 0);
	~CXDlgExportHorizons();

private slots:
	void slotButtonClicked();
	virtual void accept();

private:
	Ui::CXDlgExportHorizons ui;

	void initialize(CXObject *);
	bool exportOneHorizon(CXObject *);

	QList<CXObject *>	m_listObj;
};

#endif // KEDLGEXPORTHORIZONS_H
