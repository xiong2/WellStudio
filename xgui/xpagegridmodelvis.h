#ifndef XPAGEGRIDMODELVIS_H
#define XPAGEGRIDMODELVIS_H

#include "xgui_global.h"
#include "xbasepropertypage.h"

namespace Ui {class CXPageGridModelVis;};

///@brief	The class provides a visualization page for 3-D display of grid model geometry
///@author	PEZY
///@date	Dec. 3th, 2014
///@see

class CXViewInfo3DGridModel;
class CXViewInfoObject;

class XGUI_EXPORT CXPageGridModelVis : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageGridModelVis(QWidget *parent, CXViewInfoObject* pViewInfo);
	~CXPageGridModelVis();

	virtual void Apply();

private:
	void _InitData();

private:
	Ui::CXPageGridModelVis *m_pUi;
    CXViewInfo3DGridModel *m_pViewInfo;
};

#endif // RLPAGEGRIDMODELVIS_H
