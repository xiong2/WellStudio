#ifndef XDLGLFMTOHORIZON_H
#define XDLGLFMTOHORIZON_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlglfmtohorizon.h"

class CXObject;
class CXLFMGeometry;

class XGUIPLUS_EXPORT CXDlgLFMToHorizon : public QDialog
{
	Q_OBJECT

public:
	CXDlgLFMToHorizon(CXObject* pParentObj, QWidget *parent = 0);
	~CXDlgLFMToHorizon();

private slots:
	void slotButtonClicked();
	virtual void accept();

private:
	Ui::CXDlgLFMToHorizon ui;

	CXLFMGeometry*		m_pLFMGeometry;

	void initialize();
};

#endif // KEDLGLFMTOHORIZON_H
