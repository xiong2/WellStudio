#ifndef XDLGSEGYTRACEHEADER_H
#define XDLGSEGYTRACEHEADER_H

#include <QDialog>
#include "ui_xdlgsegytraceheader.h"

class CXSEGYLoadParameters;
class CXSEGYTraceHeader;

class CXDlgSEGYTraceHeader : public QDialog
{
	Q_OBJECT

public:
	CXDlgSEGYTraceHeader(CXSEGYLoadParameters *pParameters, QWidget *parent = 0);
	~CXDlgSEGYTraceHeader();

	bool OKForAll() { return m_bOKForAll; }

public slots:
	virtual void accept();
	virtual void acceptAll();

private slots:
	void slotTraceNumberChanged(int nValue);

private:
	void initialize();

	Ui::CXDlgSEGYTraceHeader ui;

	bool	m_bOKForAll;

	CXSEGYLoadParameters*		m_pParameters;
	CXSEGYTraceHeader*			m_pTraceHeader;
};

#endif // KEDLGSEGYTRACEHEADER_H
