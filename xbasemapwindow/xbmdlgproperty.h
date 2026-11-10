#ifndef XBMDLGPROPERTY_H
#define XBMDLGPROPERTY_H

#include <QDialog>
#include "ui_xbmdlgproperty.h"

class CXWindowInfoBasemap;
class CXBMDlgProperty : public QDialog
{
	Q_OBJECT

public:
	CXBMDlgProperty(QWidget *parent, CXWindowInfoBasemap* pWindowInfo);
	~CXBMDlgProperty();

private slots:
	void slotApply();

private:
	void _InitUI();

private:
	Ui::CXBMDlgProperty m_ui;
	CXWindowInfoBasemap* m_pWindowInfo;
};

#endif // KEBMDLGPROPERTY_H
