#ifndef XFAULTSTICKSVISPAGE_H
#define XFAULTSTICKSVISPAGE_H

#include "xbasepropertypage.h"
#include "xgui_global.h"
#include "ui_xfaultsticksvispage.h"

class CXViewInfoObject;

///@brief	The class provides a visualization page for 3-D display of fault sticks
///@author	Yong Shu
///@date	Jun. 13th, 2014
///@see

class XGUI_EXPORT CXFaultSticksVisPage : public CXBasePropertyPage
{
    Q_OBJECT

public:
    CXFaultSticksVisPage(QWidget *parent, CXViewInfoObject* pViewInfo);
    ~CXFaultSticksVisPage();

    virtual void Apply();

    public slots:
    void slotSlider(int);
    void slotChangeOpacity();

private:
    void _Init();
    void _InitData();

private:
    Ui::RLFaultSticksVisPage m_ui;

	CXViewInfoObject* m_pViewInfo;

};

#endif // RLFAULTSTICKSVISPAGE_H
