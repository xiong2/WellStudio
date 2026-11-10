#pragma once

#include <QDialog>
#include <QGraphicsScene>
#include "xguiplus_global.h"
#include "ui_xdlggatherwin.h"

class CXObject;
class CXPreStackGather;
class XSceneGather;
class XViewGather;

class XGUIPLUS_EXPORT XDlgGatherWin : public QDialog
{
	Q_OBJECT

public:
	XDlgGatherWin(CXObject *, QWidget *parent = Q_NULLPTR);
	~XDlgGatherWin();

	XViewGather* GetView()
	{
		return m_pView;
	}

	XSceneGather* GetScene()
	{
		return m_pScene;
	}

	void SetScrollbarPos(bool bChangeScale = false);

protected:
	virtual void resizeEvent(QResizeEvent* event) override;

private slots:
	void slotShow();
	void slotUpdateShotID();
	void slotShowMode();
	void slotShowScale();
	void slotShowExcursion();

	void slotHorizontalScroll(int);
	void slotVerticalScroll(int);

	void slotShowFB();
	void slotFBColor();

private:
	void initUI();

	void flushSection();

	void updateROI();

	Ui::XDlgGatherWin ui;

	bool				m_bInited = false;
	CXPreStackGather*	m_pGather = nullptr;
	XSceneGather*		m_pScene = nullptr;
	XViewGather*		m_pView = nullptr;
};
