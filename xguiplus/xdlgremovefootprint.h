#pragma once

#include <QDialog>
#include "xguiplus_global.h"
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include "ui_xdlgremovefootprint.h"
#include <vector>

using std::vector;

class CXParameterRemoveFootprint;
class CXSeismicDataVolume;
class CXWidgetFPThreshold;

class CXPythonProcess;
class CXThreadPythonProcess;

/**
*	@class	 CXDlgRemoveFootprint in the file "xdlgremovefootprint.h"
*	@brief	 The class provide a dialog to remove footprint of post-stack seismic data
*	@author	Pr
*	@date	 5/17/2025
*/

class XGUIPLUS_EXPORT CXDlgRemoveFootprint : public QDialog
{
	Q_OBJECT

public:
	CXDlgRemoveFootprint(CXParameterRemoveFootprint* para, CXSeismicDataVolume* pDV, QWidget *parent = NULL);
	~CXDlgRemoveFootprint();

	virtual void accept();

private:
	void _Init();
	void _InitConnections();

	void _InitChart();

	void _UpdatePara();
	QString _RetrieveCurrentSliceData();

private:
	void slotSliceChanged(int v);
	void slotSliceLineEdtChanged();
	void slotSliderThresholdChanged(int v);
	void slotSpinThresholdChanged(double v);

	void slotComputeOne();
	void slotComputeAll();

	void slotFinishedOneFP();
	void slotFinishedAllFP();

private:
	Ui::DlgRemoveFootprint m_ui;

	CXParameterRemoveFootprint* m_pPara;

	CXSeismicDataVolume* m_pDV;
	CXSeismicDataVolume* m_pOutDV;

	int m_nI, m_nJ, m_nK;

	double m_dSamplingStart, m_dSamplingRate, m_dSamplingEnd;

	CXWidgetFPThreshold* m_pChartWidget;

	QStringList m_strTmpFileName;
private:
	CXPythonProcess* m_PythonProcess;
	CXThreadPythonProcess* m_pPythonThread;

	QString m_strSVGFileName;
};
