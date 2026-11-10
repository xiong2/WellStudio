#ifndef XDLGVOLUMEINTEGRATION_H
#define XDLGVOLUMEINTEGRATION_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgvolumeintegration.h"

class CXObject;
class CXSeismicDataVolume;
class CXSeismicDataLine;

class XGUIPLUS_EXPORT XDlgVolumeIntegration : public QDialog
{
	Q_OBJECT

public:
	XDlgVolumeIntegration(CXObject *, QWidget *parent = 0);
	~XDlgVolumeIntegration();

private slots:
	virtual void accept();

	void slotRadioBox();
	void slotSetDepth();

private:
	void init();

	void integrateOneTrace(float *pSData, float *pDData, int iNum);

	Ui::XDlgVolumeIntegration ui;

	CXSeismicDataVolume*	m_pDV = NULL;
	CXSeismicDataLine*		m_pDLine = NULL;
};

#endif // XDLGVOLUMEINTEGRATION_H
