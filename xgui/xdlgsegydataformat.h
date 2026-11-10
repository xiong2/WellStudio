#ifndef XDLGSEGYDATAFORMAT_H
#define XDLGSEGYDATAFORMAT_H

#include <QDialog>
#include "ui_xdlgsegydataformat.h"

class CXSEGYLoadParameters;

class CXDlgSEGYDataFormat : public QDialog
{
	Q_OBJECT

public:
	CXDlgSEGYDataFormat(CXSEGYLoadParameters *pParameters, QWidget *parent = 0);
	~CXDlgSEGYDataFormat();

	bool OKForAll() { return m_bOKForAll; }

public slots:
	virtual void acceptAll();

private slots:
	void slotTraceNumberChanged(int nValue);
	void slotSelectDisplayMode();
	void slotFlipData();
	void slotSampleFormatChanged(int);

private:
	Ui::CXDlgSEGYDataFormat ui;

	bool	m_bOKForAll;
	float*	m_pTraceData;

	CXSEGYLoadParameters*		m_pParameters;

	void initialize();
	void refreshPreview();
};

#endif // KEDLGSEGYDATAFORMAT_H
