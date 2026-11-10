#ifndef XDLGPARTIALSTACK_H
#define XDLGPARTIALSTACK_H

#include <QDialog>
#include "ui_xdlgpartialstack.h"

class CXObject;
class CXBaseParameter;
class CXParametersPartialStack;
class CXSeismicDataVolume;

class CXDlgPartialStack : public QDialog
{
	Q_OBJECT

public:
	CXDlgPartialStack(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent);
	~CXDlgPartialStack();

public slots:
	virtual void accept();

private slots:
	void slotSetStackOption();
	void slotSetOffsetNumber(int);
	void slotSetAzimuthNumber(int);
	void slotSetItemValue(int iRow, int iColumn);

private:
	void _initialize();

	Ui::CXDlgPartialStack ui;

	CXSeismicDataVolume*		m_pOriDV;
	CXParametersPartialStack*	m_pPara;

	int m_iStartOffset;
	int	m_iEndOffset;
	int m_iStartAzimuth;
	int m_iEndAzimuth;
};

#endif // KEDLGPARTIALSTACK_H
