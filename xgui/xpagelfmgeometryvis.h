#ifndef XLFMGEOMETRYVISPAGE_H
#define XLFMGEOMETRYVISPAGE_H

#include "xbasepropertypage.h"
#include "xdef.h"
#include "ui_xpagelfmgeometryvis.h"

class CXViewInfoLFMGeometry;
class CXViewInfoObject;
class CXObject;
class CXLFMGeometry;

class CXPageLFMGeometryVis : public CXBasePropertyPage
{
    Q_OBJECT

public:
    CXPageLFMGeometryVis(QWidget *parent, CXViewInfoObject* pViewInfo, CXObject* pObj, EXWindowType winType);
    ~CXPageLFMGeometryVis();

    virtual void Apply() override;

private slots:
    void slotInlineValueChanged();
    void slotCrosslineValueChanged();
	void slotCheckChanged(QTableWidgetItem *pItem);
	void slotColorChanged(const QColor& color);
	void slotRangeChanged();

private:
    void _Init();
    void _InitData();

	Ui::CXPageLFMGeometryVis m_ui;
    CXViewInfoLFMGeometry* m_pViewInfo;
	CXLFMGeometry* m_pObj;
	EXWindowType m_typeWin;
};

#endif // KELFMGEOMETRYVISPAGE_H
