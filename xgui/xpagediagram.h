#pragma once
#include <qframe.h>

class CXObject;
class CXWavelet;

class CXPageDiagram : public QFrame
{
public:
	CXPageDiagram(CXObject *pObj, QWidget *parent = NULL);
	CXPageDiagram(QWidget *parent = NULL);
	~CXPageDiagram();

	void SetWavelet(CXWavelet *);

protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent) override;

	void initialize();
	void calAmpPhc();
	void drawAmp();
	void drawFre();
	void drawPha();

	static int calSignalSpectrum(double *pData, int sampleNum, int zeroIndex, double *pAmp, double *pPhase);
	static void unwrap_phase(int n, double w, double *phase);

	CXWavelet*	m_pWavelet = NULL;

	int	m_iSTime;
	int m_iMinAmp;
	int m_iMaxAmp;
	int m_iBinTime;
	double m_dBinAmp;

	double*	m_pAmpData = NULL;
	int		m_iNumAmp;
	int		m_iMaxFrq;
	int		m_iBinFrq;
	double*	m_pPhcData = NULL;
	int		m_iNumPhc;

	double	m_dFreqLow;
	double	m_dFreqHigh;
	double	m_dFreqInterval;
};