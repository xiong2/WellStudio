#ifndef _CXDLGSEGYLINEHEADER_H__
#define _CXDLGSEGYLINEHEADER_H__

#include "xgui_global.h"

#include <qdialog.h>
#include "ui_xdlgsegylineheader.h"

class CXSEGYLineHeader;

class XGUI_EXPORT CXDlgSEGYLineHeader : public QDialog
{
	Q_OBJECT
public:
	CXDlgSEGYLineHeader(QWidget *parent) :QDialog(parent)
	{
		m_bIsFlip = false;
		m_pLineHeader = NULL;
		m_LineHeaderViewUi.setupUi(this);
		m_LineHeaderViewUi.m_LineHeaderView->setColumnWidth(0, 70);
		m_LineHeaderViewUi.m_LineHeaderView->setColumnWidth(1, 240);
		m_LineHeaderViewUi.m_LineHeaderView->setColumnWidth(2, 60);
		m_LineHeaderViewUi.m_LineHeaderView->header()->setStretchLastSection(true);
		m_LineHeaderViewUi.m_LineHeaderView->setSelectionMode(QAbstractItemView::SingleSelection);
		connect(m_LineHeaderViewUi.m_ChkFlip, SIGNAL(clicked()), this, SLOT(slotFlipData()));
	}
	~CXDlgSEGYLineHeader()
	{

	}
public:
	void initTreeView();
	void setLineHeaderData(CXSEGYLineHeader* pLineHeader);
	private slots:
	void slotFlipData();
signals:
	void lineHeaderDataFliped(bool);
private:
	CXSEGYLineHeader* m_pLineHeader;
	bool m_bIsFlip;//flip line header data./
	Ui_UILineHeader m_LineHeaderViewUi;
};

#endif
