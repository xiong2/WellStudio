#ifndef GSPAGEBMVIS3DHORIZON_H
#define GSPAGEBMVIS3DHORIZON_H

#include "xgui_global.h"
#include "xbasepropertypage.h"
#include "ui_gsbm3dhorizonvispage.h"

class CXViewInfoObject;
class GS3DHorizonViewInfo;

class XGUI_EXPORT GSBM3DHorizonVisPage : public CXBasePropertyPage
{
	Q_OBJECT

public:
	GSBM3DHorizonVisPage(CXViewInfoObject* pViewInfo, QWidget *parent = 0);
	~GSBM3DHorizonVisPage();

	void Apply() override;

private:
	Ui::GSBM3DHorizonVisPage ui;
	GS3DHorizonViewInfo* m_pViewInfo;
};

#endif // GSPAGEBMVIS3DHORIZON_H
