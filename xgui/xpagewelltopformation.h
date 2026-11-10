#ifndef XPAGEWELLTOPSVIS3D_H
#define XPAGEWELLTOPSVIS3D_H

#include "ui_xpagewelltopformation.h"
#include "xbasepropertypage.h"

///@brief	The widget page of well top formation's properties.
///@author	pezy
///@date	2014-06-10
///@see

class CXViewInfoObject;
class CXViewInfo3DWellTopFormation;

class CXPageWellTopFormation : public CXBasePropertyPage
{
	Q_OBJECT

public:
    CXPageWellTopFormation(QWidget *parent, CXViewInfoObject* pViewInfo);

	virtual void Apply();	

private:
	void _InitUI();

private slots:
	void _ChangeLabelName(int id);

private:
	Ui::CXPageWellTopsVis3D m_ui;
    CXViewInfo3DWellTopFormation* m_pViewInfo;
};

#endif // RLPAGEWELLTOPSVIS3D_H
