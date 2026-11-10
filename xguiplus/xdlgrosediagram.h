#ifndef XDLGROSEDIAGRAM_H
#define XDLGROSEDIAGRAM_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgrosediagram.h"

class CXObject;
class CXSeismicDataVolume;

class XGUIPLUS_EXPORT CXDlgRoseDiagram : public QDialog
{
	Q_OBJECT

public:
	CXDlgRoseDiagram(CXObject *, QWidget *parent = 0);
	~CXDlgRoseDiagram();

private slots:
	void slotRefreshVisPara();
	void slotRefreshData();
	void slotOpanChanged();

private:
	void _InitUI();

	Ui::CXDlgRoseDiagram ui;
	
	CXSeismicDataVolume*	m_pDV;
};

#endif // KEDLGROSEDIAGRAM_H
