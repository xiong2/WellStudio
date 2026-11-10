#ifndef XMAINTREEWIDGET_H
#define XMAINTREEWIDGET_H

#include <QTreeWidget>
#include "xconsole_global.h"

#include <QMouseEvent>
class XCONSOLE_EXPORT CXMainTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	CXMainTreeWidget(QWidget *parent = NULL);
	virtual ~CXMainTreeWidget();

private slots:
	void slotItemChanged(QTreeWidgetItem *, int);
	void slotItemActivated(QTreeWidgetItem *, QTreeWidgetItem *);
	void slotDoubleClicked(QTreeWidgetItem *, int);
	void slotItemEditDone();

protected:
	virtual void contextMenuEvent(QContextMenuEvent * e);

	void   mousePressEvent(QMouseEvent *);
	void   mouseMoveEvent(QMouseEvent *);
	void   mouseReleaseEvent(QMouseEvent *);
	QPoint m_PressPos;
	QList<QUuid> m_lstPress;
};

#endif // RLMAINTREEWIDGET_H
