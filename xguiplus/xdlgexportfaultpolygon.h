#ifndef XDLGEXPORTFAULTPOLYGON_H
#define XDLGEXPORTFAULTPOLYGON_H

/*!
 *	@class	CXDlgExportFaultPolygon in file "kedlgexportfaultpolygon.h"
 *	@brief	Export fault polygon group as ASCII file.
 *	@author	pezy
 *	@date	2017-04-27
 *	@see
 */

#include <QDialog>
#include "ui_xdlgexportfaultpolygon.h"
#include "xguiplus_global.h"

class CXObject;

class XGUIPLUS_EXPORT CXDlgExportFaultPolygon : public QDialog
{
	Q_OBJECT

public:
	CXDlgExportFaultPolygon(CXObject* pObj, QWidget *parent = 0);
	~CXDlgExportFaultPolygon();

public slots:
	void accept() override;

private slots:
	void slotSelectFile();
	void slotSelectItems();
	void slotConflict(int iState);

private:
	void _Init(CXObject* pObj);

private:
	Ui::CXDlgExportFaultPolygon ui;
};

#endif // KEDLGEXPORTFAULTPOLYGON_H
