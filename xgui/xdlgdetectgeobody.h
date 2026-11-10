#ifndef XDLGDETECTGEOBODY_H
#define XDLGDETECTGEOBODY_H

#include <QDialog>
#include "ui_xdlgdetectgeobody.h"
#include "xgui_global.h"

class CXSeismicDataVolume;
class CXBaseParameter;
class CXObject;
class CXParametersGeobodyDetection;

class XGUI_EXPORT CXDlgDetectGeobody : public QDialog
{
	Q_OBJECT

public:
	CXDlgDetectGeobody(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent);
    ~CXDlgDetectGeobody();

public slots:
	virtual void accept();

private slots:
	void slotLineEditValueChanged();
	void slotSliderValueChanged(int);
	void slotPushButtonClicked();
	void slotRadioButtonClicked();
	void slotThresholdRangeChanged(double dMin, double dMax);

private:
	void initialize();

	Ui::DlgDetectGeobody ui;

	CXSeismicDataVolume *m_pDV;

	CXParametersGeobodyDetection* m_pPara;
};

#endif // KEDLGDETECTGEOBODY_H
