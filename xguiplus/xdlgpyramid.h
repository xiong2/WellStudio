#pragma once

#include <QDialog>
#include <QGraphicsScene>
#include "xguiplus_global.h"
#include "ui_xdlgpyramid.h"

class CXSeismicDataVolume;
class XScenePyramid;

class XGUIPLUS_EXPORT XDlgPyramid : public QDialog
{
	Q_OBJECT

public:
	XDlgPyramid(CXSeismicDataVolume *, QWidget *parent = Q_NULLPTR);
	~XDlgPyramid();

	void accept() override;

	void CalVar(float*, int iWWidth, int iWHeight, int iIWidth, int iIHeight);

	void SetSugAng(QString);

private slots:
	void slotSection();
	void slotDirection();
	void slotDegree();
	void slotArea();
	void slotOutside();

private:
	void initUI();
	void initView();
	void flushSection(bool bOnlyAngle = false);
	void resetODVName();

	Ui::XDlgPyramid ui;

	CXSeismicDataVolume*	m_pDV;
	XScenePyramid*			m_pScene;
};
