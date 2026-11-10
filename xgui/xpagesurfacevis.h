#ifndef CXPAGESURFACEVIS_H
#define CXPAGESURFACEVIS_H

#include "ui_xpagesurfacevisualization.h"
#include "xbasepropertypage.h"
#include "xviewinfoobject.h"
#include "xviewinfosurface.h"
#include "xobject.h"
#include "xdef.h"

class CXPageSurfaceVis :public CXBasePropertyPage
{
	Q_OBJECT
public:
	CXPageSurfaceVis(QWidget *parent, CXViewInfoObject* pViewInfo, CXObject *pObj, EXWindowType typeWin);
	~CXPageSurfaceVis();
	
	virtual void Apply();

private slots:
	void slotFillColorChange(int nindex);
	void slotFillAdd();
	void slotFillDel();
	void slotFillNum();
	void slotFillColormapChange(int nindex);
	void slotContourIncValidChecking();
	void slotContourFillIncChanged();
	void slotChangeAttribute(int nindex);
	void slotChangedTableItem(int row, int colum);

private:
	void _InitUI();
	void _InitFillWidget();
	void _InitContour();
	void _UpdateContourTableByRowNum(int nRow);
	void _GetDefaultDataSegment(float& fStart, float& fEnd, float& fInc);
	void _InitAttributeList();

private:
	Ui::CXSurfVisualizationPage m_ui;
	CXViewInfoSurface *m_pViewInfo;
	CXObject *m_pObj;
	EXWindowType m_typeWin;
};

#endif // CXPAGESURFACEVIS_H
