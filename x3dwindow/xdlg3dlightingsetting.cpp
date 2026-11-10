#include "xdlg3dlightingsetting.h"
#include "ui_xdlg3dlightingsetting.h"
#include "x3dwindow.h"
#include "xwindowinfo3d.h"
#include "x3dscene.h"

CXDlg3DLightingSetting::CXDlg3DLightingSetting(QWidget *parent)
	: QDialog(parent)
{
    m_ui = new Ui::CXDlg3DLightingSetting();
	m_ui->setupUi(this);

	m_pWin = dynamic_cast<CX3DWindow*>(parent);
	m_pWinInfo = m_pWin->GetWindowInfo();
	_Init();

	connect(m_ui->m_vsliderAmbient, SIGNAL(valueChanged(int)), this, SLOT(slotAmbientChanged(int)));
	connect(m_ui->m_hsliderX, SIGNAL(valueChanged(int)), this, SLOT(slotDireactionChanged(int)));
	connect(m_ui->m_hsliderY, SIGNAL(valueChanged(int)), this, SLOT(slotDireactionChanged(int)));
	connect(m_ui->m_hsliderZ, SIGNAL(valueChanged(int)), this, SLOT(slotDireactionChanged(int)));
	connect(m_ui->m_groupLight, SIGNAL(buttonClicked(int)), this, SLOT(slotCheckLight(int)));
	connect(m_ui->m_groupStatus, SIGNAL(buttonClicked(int)), this, SLOT(slotCheckStatus(int)));
	connect(m_ui->m_cbbColor1, SIGNAL(ColorSelected(const QColor&)), this, SLOT(slotColorChanged(const QColor &)));
	connect(m_ui->m_cbbColor2, SIGNAL(ColorSelected(const QColor&)), this, SLOT(slotColorChanged(const QColor &)));
	connect(m_ui->m_cbbColor3, SIGNAL(ColorSelected(const QColor&)), this, SLOT(slotColorChanged(const QColor &)));
	connect(m_ui->m_cbbColor4, SIGNAL(ColorSelected(const QColor&)), this, SLOT(slotColorChanged(const QColor &)));
}

CXDlg3DLightingSetting::~CXDlg3DLightingSetting()
{
	delete m_ui;
}

void CXDlg3DLightingSetting::closeEvent(QCloseEvent * event)
{
	m_pWin->GetOSGScene()->SetLightingSphereVisible(false);
}

void CXDlg3DLightingSetting::showEvent(QShowEvent * event)
{
	m_pWin->GetOSGScene()->SetLightingSphereVisible(true);
}

void CXDlg3DLightingSetting::_Init()
{
	// init of control
	m_ui->m_groupLight->setId(m_ui->m_radioLight1, 0);
	m_ui->m_groupLight->setId(m_ui->m_radioLight2, 1);
	m_ui->m_groupLight->setId(m_ui->m_radioLight3, 2);
	m_ui->m_groupLight->setId(m_ui->m_radioLight4, 3);

	m_ui->m_groupStatus->setId(m_ui->m_ckbLight1, 0);
	m_ui->m_groupStatus->setId(m_ui->m_ckbLight2, 1);
	m_ui->m_groupStatus->setId(m_ui->m_ckbLight3, 2);
	m_ui->m_groupStatus->setId(m_ui->m_ckbLight4, 3);

	// default to check the first one.
	slotCheckLight(0);

	// check state
	const QBitArray& lightSwitch = m_pWinInfo->GetLightSwitch();

	for (int i = 0; i != lightSwitch.size(); ++i)
		m_ui->m_groupStatus->button(i)->setChecked(lightSwitch.at(i));
}

void CXDlg3DLightingSetting::slotAmbientChanged(int value)
{
	m_ui->m_editAmbient->setText(QString::number(static_cast<double>(value)/100, 'g', 3));
	m_pWinInfo->SetLightAmbient(m_ui->m_groupLight->checkedId(), static_cast<float>(value) / 100);
	m_pWin->GetOSGScene()->UpdateLightingViewInfo(m_ui->m_groupLight->checkedId());
}

void CXDlg3DLightingSetting::slotDireactionChanged(int value)
{
	auto pSlider = dynamic_cast<QSlider*>(sender());

	if (pSlider == m_ui->m_hsliderX)
	{
		m_ui->m_editX->setText(QString::number(static_cast<float>(value) / 1000));
	}
	else if (pSlider == m_ui->m_hsliderY)
	{
		m_ui->m_editY->setText(QString::number(static_cast<float>(value) / 1000));
	}
	else if (pSlider == m_ui->m_hsliderZ)
	{
		m_ui->m_editZ->setText(QString::number(static_cast<float>(value) / 1000));
	}

	float fX = m_ui->m_editX->text().toFloat();
	float fY = m_ui->m_editY->text().toFloat();
	float fZ = m_ui->m_editZ->text().toFloat();

	m_pWinInfo->SetLightDireaction(m_ui->m_groupLight->checkedId(), fX, fY, fZ);
	m_pWin->GetOSGScene()->UpdateLightingViewInfo(m_ui->m_groupLight->checkedId());
	m_pWin->GetOSGScene()->UpdateLightingPosition();
}

void CXDlg3DLightingSetting::slotCheckLight(int id)
{
	const std::vector<uint>& listColor = m_pWinInfo->GetLightColor();
	const std::vector<float>& listAmbient = m_pWinInfo->GetLightAmbient();
	const std::vector<float>& vecDireaction = m_pWinInfo->GetLightDireaction();

	m_ui->m_cbbColor1->blockSignals(true);
	m_ui->m_cbbColor2->blockSignals(true);
	m_ui->m_cbbColor3->blockSignals(true);
	m_ui->m_cbbColor4->blockSignals(true);

	// Enable of color button.
	m_ui->m_cbbColor1->setEnabled(0 == id);
	m_ui->m_cbbColor2->setEnabled(1 == id);
	m_ui->m_cbbColor3->setEnabled(2 == id);
	m_ui->m_cbbColor4->setEnabled(3 == id);

	// color
	m_ui->m_cbbColor1->SetColor(QColor(listColor.at(0)));
	m_ui->m_cbbColor2->SetColor(QColor(listColor.at(1)));
	m_ui->m_cbbColor3->SetColor(QColor(listColor.at(2)));
	m_ui->m_cbbColor4->SetColor(QColor(listColor.at(3)));

	m_ui->m_cbbColor1->blockSignals(false);
	m_ui->m_cbbColor2->blockSignals(false);
	m_ui->m_cbbColor3->blockSignals(false);
	m_ui->m_cbbColor4->blockSignals(false);

	m_ui->m_vsliderAmbient->blockSignals(true);

	// Ambient
	float fAmbient = listAmbient.at(id);
	m_ui->m_vsliderAmbient->setValue(static_cast<int>(fAmbient * 100));
	m_ui->m_editAmbient->setText(QString::number(fAmbient, 'g', 3));

	m_ui->m_vsliderAmbient->blockSignals(false);

	// Position
	float fxOffset = vecDireaction.at(id * 3);
	float fyOffset = vecDireaction.at(id * 3 + 1);
	float fzOffset = vecDireaction.at(id * 3 + 2);

	m_ui->m_hsliderX->blockSignals(true);
	m_ui->m_hsliderY->blockSignals(true);
	m_ui->m_hsliderZ->blockSignals(true);

	m_ui->m_hsliderX->setValue(fxOffset*1000);
	m_ui->m_hsliderY->setValue(fyOffset*1000);
	m_ui->m_hsliderZ->setValue(fzOffset*1000);

	m_ui->m_editX->setText(QString::number(fxOffset));
	m_ui->m_editY->setText(QString::number(fyOffset));
	m_ui->m_editZ->setText(QString::number(fzOffset));

	m_ui->m_hsliderX->blockSignals(false);
	m_ui->m_hsliderY->blockSignals(false);
	m_ui->m_hsliderZ->blockSignals(false);
}

void CXDlg3DLightingSetting::slotCheckStatus(int id)
{
	QBitArray lightSwitch = m_pWinInfo->GetLightSwitch();

	lightSwitch[id] = m_ui->m_groupStatus->button(id)->isChecked();
	m_pWinInfo->SetLightSwitch(lightSwitch);
	m_pWin->GetOSGScene()->UpdateLightingViewInfo(id);

	// Enable of light radio
	m_ui->m_radioLight1->setEnabled(lightSwitch[0]);
	m_ui->m_radioLight2->setEnabled(lightSwitch[1]);
	m_ui->m_radioLight3->setEnabled(lightSwitch[2]);
	m_ui->m_radioLight4->setEnabled(lightSwitch[3]);
}

void CXDlg3DLightingSetting::slotColorChanged(const QColor &c)
{
	m_pWinInfo->SetLightColor(m_ui->m_groupLight->checkedId(), c.rgba());
	m_pWin->GetOSGScene()->UpdateLightingViewInfo(m_ui->m_groupLight->checkedId());
}