#pragma once

#include <QDialog>
#include <quuid.h>
#include "xguiplus_global.h"
#include "xview.h"
#include "ui_xdlgdatasheet.h"
#include "xobjecttype.h"

class XGUIPLUS_EXPORT CXDlgDataSheet : public QDialog, public IKEView
{
	Q_OBJECT

public:
	CXDlgDataSheet(QUuid, QWidget *parent = Q_NULLPTR);
	~CXDlgDataSheet();

	///	Poupate the spread sheet by the object.
	bool PopulateData();

	///	Which Object it represent.
	QUuid GetObjectID()
	{
		return m_objID;
	}

	///@brief Reimplement function from IRLView
	virtual void UpdateView(const CXEventParameter& eventPara)
	{
	}

	void accept() override;
	void reject() override;

protected slots:
	void slotRowEdit();
	void slotDataChanged();

private:
	Ui::CXDlgDataSheet ui;

	bool				m_bDataChanged = false;
	bool				m_bNeedFlush = false;
	QUuid				m_objID;				//	The object ID.
	QVector<bool>		m_vecColumnEditable;	//	Indicate whether each column could be edited.

	//	iMode = 0: uneditable at all;  1: item editable, not row;  2:  can append rows;  3:  Free edit.
	void setEditable(int iMode);

	bool populate(QStringList sListCName, double *, int iLen);
	bool populate(QStringList sListCName, QStringList sListContents, double*, int iRow);
	bool populate(QStringList sListCName, QStringList sListContents);

	void setNeedFlush(bool bNF)
	{
		m_bNeedFlush = bNF;
	}

	void setTips(EXObjectType);

	bool check();
	bool check(int iColumn, int iDataType);		//	iDataType = 0: double; 1: string.
	void save();
};
