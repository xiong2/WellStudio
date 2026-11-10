#ifndef XTABLEFORASCII_H
#define XTABLEFORASCII_H

#include <qtablewidget.h>
#include <QItemDelegate>
#include "xgui_global.h"

class CXSEGYTraceHeaderItem;
class CXPageLoadSegyStep2;
class CXSEGYTraceHeader;

class CXTableForLoadSegyItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	CXTableForLoadSegyItemDelegate(QObject *parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
	private slots:
		void slotEmitFormatTypeChanged(int nType);//format type changed.
signals:
		void formatTypeChanged(int nType);
};

/**
* @class CXTableForLoadSegy gmtableforloadsegy.h
* @brief The CXTableForLoadSegy class provides a framework for load segy data wizard page step2(preview trace header).
* @date 8/03/2010
* @see QTableWidget
*/
class XGUI_EXPORT CXTableForLoadSegy : public QTableWidget
{
	Q_OBJECT
public:
	CXTableForLoadSegy(QWidget *parent);
	virtual ~CXTableForLoadSegy(void);

	void SetParentWidget(QWidget *parentWidget);//Transport parent widget .
	void SetData(CXSEGYTraceHeader* pTraceHeader);//set data to ASCII viewer from load segy data wizard page step 2
	void UpdateTableValue();//Update all table column value.

protected:
	virtual void	contextMenuEvent ( QContextMenuEvent * event );

private:
	void _initAscIIView();//set ASCII view data.
	QList<CXSEGYTraceHeaderItem *> *m_plistTraceHeaderItems;//ASCII view table item value 
	QStringList m_listDescription;//ASCII view column 2 description text
	CXPageLoadSegyStep2 *m_pStepPage2;
	CXSEGYTraceHeader* m_pTraceHeader;

	private slots:
	void slotFormatChanged(int nFormatType);//ASCII View Format Type changed 0 is Int 1 is float.
	void slotSetAsInline();//set inline data from current segy trace header item data .
	void slotSetAsCrossLine();//set cross line  data from current segy trace header item data .
	void slotSetAsOffset();
	void slotSetAsCoordinateX();//set coordinate X data from current segy trace header item data .
	void slotSetAsCoordinateY();//set coordinate Y data from current segy trace header item data .
	void slotSplit2Rows();//Split current trace header item 2 rows  , when current trace header item data length large 2.
	void slotMergeNextRow();//Merge Next trace header item to current header item , when current and next header item data length is 2 bytes
	void slotMergePrevRow();//Merge Previous trace header item to current header item , when current and Previous header item data length is 2 bytes
};

#endif // KETABLEFORASCII_H