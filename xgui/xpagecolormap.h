#ifndef XPAGECOLORMAP_H
#define XPAGECOLORMAP_H

#include "xbasepropertypage.h"
#include "ui_xpagecolormap.h"
#include <memory>
#include "xhistogram.h"

///@brief	The property page for setting color map.
///@author	PEZY
///@date	2014-08-11
///@review	2016-03-01
///@see

class CXObject;
class CXViewInfoObject;

class CXPageColormap : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageColormap(QWidget *parent, CXObject* pObj);
	CXPageColormap(QWidget *parent, CXObject* pObj, const CXHistogram& rHistogram);

	void Apply() override;

protected:
	virtual void keyPressEvent(QKeyEvent* pEvent) override;

private:
	void _InitUI();
	void _SetHistogram();
	bool _IsRealtime();
	void _SaveCustomizedColormap();
	void _SwitchToCustom();
	void _ConvertToCustomizedColormap();
	void _SetInvalidColor(const QColor& color);

private slots:
	void slotUpdateEditor();
	void slotTemplateChanged(const QString & text);
	void slotRetrieve();
	void slotSaveAs();
	void slotAutoCalculateDataRange(bool bAuto);
	void slotSetDisplayMin(double dMin);
	void slotSetDisplayMax(double dMax);
	void slotChangeDisplayMinMax();
	void slotSetDefaultDataRange();
	void slotSetInvalidColorTransparent();
	void slotSetInvalidColor(const QColor& color);
	void slotZeroIsInvalid(bool bChecked);

private:
	Ui::CXPageColormap m_ui;
	CXObject* m_pObj;
	CXViewInfoObject* m_pViewInfo;
	const CXHistogram& m_rHistogram;
};

#endif // RLPAGECOLORMAP_H
