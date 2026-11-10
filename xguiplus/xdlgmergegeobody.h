#ifndef XDLGMERGEGEOBODY_H
#define XDLGMERGEGEOBODY_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgmergegeobody.h"

class CXGeobodyCollection;

class XGUIPLUS_EXPORT CXDlgMergeGeobody : public QDialog
{
	Q_OBJECT

public:
	CXDlgMergeGeobody(CXGeobodyCollection *pGCollection, QWidget *parent = 0);
	~CXDlgMergeGeobody();
	
public slots:
	virtual void accept();

private:
	void initialize();

	CXGeobodyCollection*	m_pGCollection;
	
	Ui::CXDlgMergeGeobody	ui;
};

#endif // KEDLGMERGEGEOBODY_H
