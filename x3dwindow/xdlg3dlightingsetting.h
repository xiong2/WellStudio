#ifndef XDLG3DLIGHTINGSETTING_H
#define XDLG3DLIGHTINGSETTING_H

/*!
 * @class	CXDlg3DLightingSetting in "kedlg3dlightingsetting.h"
 * @brief	dialog of lighting properties for 3D window.
 * @author	pezy
 * @date	2016-10-12
 */

#include <QDialog>

namespace Ui { class CXDlg3DLightingSetting; };

class CXWindowInfo3D;
class CX3DWindow;

class CXDlg3DLightingSetting : public QDialog
{
	Q_OBJECT

public:
	CXDlg3DLightingSetting(QWidget *parent);
	~CXDlg3DLightingSetting();

protected:
	void closeEvent(QCloseEvent *event) override;
	void showEvent(QShowEvent *event) override;

private slots:
	void slotAmbientChanged(int value);
	void slotDireactionChanged(int value);
	void slotCheckLight(int id);
	void slotCheckStatus(int id);
	void slotColorChanged(const QColor &c);

private:
	void _Init();

private:
	Ui::CXDlg3DLightingSetting *m_ui;
	CXWindowInfo3D* m_pWinInfo;
	CX3DWindow* m_pWin;
};

#endif // KEDLG3DLIGHTINGSETTING_H
