#pragma once

#include "xlogview_global.h"
#include "xwindow.h"

class XLOGVIEW_EXPORT CXLogView: public CXWindow
{
	Q_OBJECT

public:
	CXLogView(QString sWindowName, QWidget *parent = 0, Qt::WindowFlags f = Qt::Window);
	
	virtual CXScene* GetScene() override;

	void InitWindow() override;

	void ShowStatus(QString);

private slots:
	void slotSetting();
};
