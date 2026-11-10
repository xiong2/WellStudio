#ifndef XPAGEPRESTACKGATHERVIS_H
#define XPAGEPRESTACKGATHERVIS_H

#include "xbasepropertypage.h"
#include "ui_xpageprestackgathervis.h"

class CXViewInfoPreStackGather;
class CXViewInfoObject;
class CXObject;

/**
@class CXPagePreStackGatherVis provided in the file "xpageprestackgathervis.h"
@brief The class provides visualization page for CXPreStackGather
@author pezy
@date 2017-10-09
@sa CXPreStackGather CXViewInfoPreStackGather
*/
class CXPagePreStackGatherVis : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPagePreStackGatherVis(CXViewInfoObject *pViewInfo, CXObject *pObj, QWidget *parent = 0);
	~CXPagePreStackGatherVis();

	void Apply() override;

private:
	void _Init();

	Ui::CXPagePreStackGatherVis ui;
	CXViewInfoPreStackGather* m_pViewInfo = nullptr;
};

#endif // XPAGEPRESTACKGATHERVIS_H
