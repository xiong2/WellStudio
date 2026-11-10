#ifndef _CXDLGCALCULATOR_H__
#define _CXDLGCALCULATOR_H__

#include <qdialog.h>
#include <quuid.h>
#include "xgui_global.h"
#include "ui_xcalculator.h"

class QToolButton;
class QTreeWidgetItem;
class QListWidgetItem;
class CXObjCalculator;

class XGUI_EXPORT CXDlgCalculator :public QDialog 
{
	Q_OBJECT
public:
	CXDlgCalculator(QUuid objectID, QWidget *parent = NULL);
	~CXDlgCalculator();

protected slots:
	void slotTbnClicked();
	void slotEnterClicked();//operator enter clicked
	void slotLsClearClicked();//result list view clear button clicked
	void slotClearClicked();
	void slotBackspace();
	void slotBrowseClicked();
	void slotCopyClicked();
	void slotVariableItemClicked( QTreeWidgetItem * pItem);
	void slotVariableItemEntered();//This slot is called when the mouse cursor enters an item over the specified column
	void slotDisplayCorPosChanged();
	void slotResultItemClicked(QListWidgetItem * pItem);
	void slotSetOutputTemplate(int);
	void slotDegTypeClicked();

protected:
	Ui::DlgCalculator			ui;
	QUuid						m_objectID;
	CXObjCalculator*			m_pCalculator;
	QMap<QToolButton*,QString>	m_MapToText;
	QString						m_strDisplaySelectedText;
	int							m_nCurPos;//current position on dispaly edit.
	int							m_nStartPos;//the index of the first selected character in the display edit, -1 if no text is selected.

	virtual void    closeEvent(QCloseEvent * pEvent);
	void initVariableTree();
	void addAnItemToVaribleTree(QUuid);

	void _setDisplayFocus(QString strTbnText);//reset display edit mouse position.
	void connectTbnSignal();
	void initTextMap();//Tool button maped button text.
	void _readHistory();
	void _writeHistory();
};

#endif