#include "xsubgridsetting.h"

#include <cassert>

#include "ui_xsubgridsetting.h"
#include "x3dwindow.h"
#include "x3dscene.h"
#include "xgridmodel.h"
#include "xglobal.h"
#include "xviewinfo3dgridmodel.h"
#include "xeventconsole.h"

CXSubGridSetting::CXSubGridSetting(QWidget *parent, CX3DWindow *curWin)
	: QDialog(parent)
{
	ui = new Ui::CXSubGridSetting();
	ui->setupUi(this);

	assert(curWin);
	m_curWin = curWin;
	_Init();
}

CXSubGridSetting::~CXSubGridSetting()
{
	delete ui;
}

void CXSubGridSetting::_Init()
{
	for(const QUuid& uid : m_curWin->GetDisplayedObjects())
	{
		m_obj = dynamic_cast<CXGridModel*>(::GetObjectByID(uid));
		m_viewInfo = dynamic_cast<CXViewInfo3DGridModel*>(m_curWin->GetObjectViewInfo(uid));
		if (m_obj) break;
	}

	assert(m_obj);

	unsigned nI, nJ, nK;
	m_obj->GetIJKDimentionInfo(nI, nJ, nK);	

	ui->m_hSliderMinI->setRange(1, nI);
	ui->m_hSliderMinJ->setRange(1, nJ);
	ui->m_hSliderMinK->setRange(1, nK);
	ui->m_hSliderMaxI->setRange(1, nI);
	ui->m_hSliderMaxJ->setRange(1, nJ);
	ui->m_hSliderMaxK->setRange(1, nK);

	ui->m_spinBoxMinI->setRange(1, nI);
	ui->m_spinBoxMinJ->setRange(1, nJ);
	ui->m_spinBoxMinK->setRange(1, nK);
	ui->m_spinBoxMaxI->setRange(1, nI);
	ui->m_spinBoxMaxJ->setRange(1, nJ);
	ui->m_spinBoxMaxK->setRange(1, nK);

	ui->m_hSliderMinI->setValue(m_viewInfo->GetMinI());
	ui->m_hSliderMaxI->setValue(m_viewInfo->GetMaxI());
	ui->m_hSliderMinJ->setValue(m_viewInfo->GetMinJ());
	ui->m_hSliderMaxJ->setValue(m_viewInfo->GetMaxJ());
	ui->m_hSliderMinK->setValue(m_viewInfo->GetMinK());
	ui->m_hSliderMaxK->setValue(m_viewInfo->GetMaxK());

	connect(ui->m_hSliderMinI, SIGNAL(sliderMoved(int)), this, SLOT(slotSetMinILimit(int)));
	connect(ui->m_hSliderMinJ, SIGNAL(sliderMoved(int)), this, SLOT(slotSetMinJLimit(int)));
	connect(ui->m_hSliderMinK, SIGNAL(sliderMoved(int)), this, SLOT(slotSetMinKLimit(int)));

	connect(ui->m_spinBoxMinI, SIGNAL(valueChanged(int)), this, SLOT(slotSetMinI(int)));
	connect(ui->m_spinBoxMinJ, SIGNAL(valueChanged(int)), this, SLOT(slotSetMinJ(int)));
	connect(ui->m_spinBoxMinK, SIGNAL(valueChanged(int)), this, SLOT(slotSetMinK(int)));
	connect(ui->m_spinBoxMaxI, SIGNAL(valueChanged(int)), this, SLOT(slotSetMaxI(int)));
	connect(ui->m_spinBoxMaxJ, SIGNAL(valueChanged(int)), this, SLOT(slotSetMaxJ(int)));
	connect(ui->m_spinBoxMaxK, SIGNAL(valueChanged(int)), this, SLOT(slotSetMaxK(int)));

	connect(ui->m_btReset, SIGNAL(clicked()), this, SLOT(slotReset()));
}

void CXSubGridSetting::slotSetMinILimit(int value)
{
	if (value >= ui->m_hSliderMaxI->value())
		ui->m_hSliderMaxI->setValue(value);
}

void CXSubGridSetting::slotSetMinJLimit(int value)
{
	if (value >= ui->m_hSliderMaxJ->value())
		ui->m_hSliderMaxJ->setValue(value);
}

void CXSubGridSetting::slotSetMinKLimit(int value)
{
	if (value >= ui->m_hSliderMaxK->value())
		ui->m_hSliderMaxK->setValue(value);
}

void CXSubGridSetting::slotSetMinI(int value)
{
	if (value >= ui->m_spinBoxMaxI->value())
		ui->m_spinBoxMaxI->setValue(value);
	m_viewInfo->SetMinI(value);
	CXProcessEvent processEvent;
	m_obj->AddEvent(EInfoChanged);
}

void CXSubGridSetting::slotSetMaxI(int value)
{
	if (value <= ui->m_spinBoxMinI->value())
		ui->m_spinBoxMinI->setValue(value);
	m_viewInfo->SetMaxI(value);
	CXProcessEvent processEvent;
	m_obj->AddEvent(EInfoChanged);
}

void CXSubGridSetting::slotSetMinJ(int value)
{
	if (value >= ui->m_spinBoxMaxJ->value())
		ui->m_spinBoxMaxJ->setValue(value);
	m_viewInfo->SetMinJ(value);
	CXProcessEvent processEvent;
	m_obj->AddEvent(EInfoChanged);
}

void CXSubGridSetting::slotSetMaxJ(int value)
{
	if (value <= ui->m_spinBoxMinJ->value())
		ui->m_spinBoxMinJ->setValue(value);
	m_viewInfo->SetMaxJ(value);
	CXProcessEvent processEvent;
	m_obj->AddEvent(EInfoChanged);
}

void CXSubGridSetting::slotSetMinK(int value)
{
	if (value >= ui->m_spinBoxMaxK->value())
		ui->m_spinBoxMaxK->setValue(value);
	m_viewInfo->SetMinK(value);
	CXProcessEvent processEvent;
	m_obj->AddEvent(EInfoChanged);
}

void CXSubGridSetting::slotSetMaxK(int value)
{
	if (value <= ui->m_spinBoxMinK->value())
		ui->m_spinBoxMinK->setValue(value);
	m_viewInfo->SetMaxK(value);
	CXProcessEvent processEvent;
	m_obj->AddEvent(EInfoChanged);
}

void CXSubGridSetting::slotReset()
{
	unsigned nI, nJ, nK;
	m_obj->GetIJKDimentionInfo(nI, nJ, nK);

	ui->m_hSliderMinI->setValue(1);
	ui->m_hSliderMaxI->setValue(nI);
	ui->m_hSliderMinJ->setValue(1);
	ui->m_hSliderMaxJ->setValue(nJ);
	ui->m_hSliderMinK->setValue(1);
	ui->m_hSliderMaxK->setValue(nK);
}