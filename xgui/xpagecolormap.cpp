#include "xpagecolormap.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>

#include "xviewinfoobject.h"
#include "xcolormap.h"
#include "xglobal.h"
#include "xobject.h"
#include "xeventconsole.h"
#include "xbaseconsole.h"
#include "xdbio.h"
#include "xutility.h"

CXPageColormap::CXPageColormap(QWidget *parent, CXObject* pObj)
	: CXPageColormap(parent, pObj, pObj->GetHistogram())
{
}

CXPageColormap::CXPageColormap(QWidget * parent, CXObject * pObj, const CXHistogram & rHistogram)
	: CXBasePropertyPage(parent), m_pObj(pObj), m_rHistogram(rHistogram)
{
	m_ui.setupUi(this);

	CXBaseConsole *pCurConsol = reinterpret_cast<CXBaseConsole *>(::GetConsole());
	m_pViewInfo = pCurConsol->GetViewInfoForActiveWindow(pObj->GetObjectID());

	connect(m_ui.m_cbbTemplate, SIGNAL(activated(const QString &)), SLOT(slotTemplateChanged(const QString &)));
	connect(m_ui.m_btRetrieve, SIGNAL(pressed()), SLOT(slotRetrieve()));
	connect(m_ui.m_btSaveAs, SIGNAL(pressed()), SLOT(slotSaveAs()));

	connect(m_ui.m_rbAutomatic, SIGNAL(toggled(bool)), SLOT(slotAutoCalculateDataRange(bool)));
	connect(m_ui.m_btDefault, SIGNAL(clicked()), SLOT(slotSetDefaultDataRange()));

	connect(m_ui.m_edMin, SIGNAL(editingFinished()), SLOT(slotChangeDisplayMinMax()));
	connect(m_ui.m_edMax, SIGNAL(editingFinished()), SLOT(slotChangeDisplayMinMax()));
	connect(m_ui.m_cbZeroIsInvalid, SIGNAL(toggled(bool)), SLOT(slotZeroIsInvalid(bool)));
	connect(m_ui.m_btFlip, SIGNAL(pressed()), m_ui.colormapEditor, SLOT(slotFlip()));
	connect(m_ui.m_btReset, SIGNAL(pressed()), m_ui.colormapEditor, SLOT(slotReset()));
	connect(m_ui.m_cbFreeDrawing, SIGNAL(toggled(bool)), m_ui.colormapEditor, SLOT(slotSetOpacityFreeDrawing(bool)));
	connect(m_ui.m_rbTransparent, SIGNAL(pressed()), SLOT(slotSetInvalidColorTransparent()));
	connect(m_ui.m_btColor, SIGNAL(ColorSelected(const QColor&)), SLOT(slotSetInvalidColor(const QColor&)));
	connect(m_ui.colormapEditor, SIGNAL(ColormapChanged()), SLOT(slotUpdateEditor()));
	connect(m_ui.colormapEditor, SIGNAL(ShowMsg(const QString&)), m_ui.m_labelMessage, SLOT(setText(const QString&)));
	connect(m_ui.colormapEditor, SIGNAL(MinValueChanged(double)), SLOT(slotSetDisplayMin(double)));
	connect(m_ui.colormapEditor, SIGNAL(MaxValueChanged(double)), SLOT(slotSetDisplayMax(double)));

	_InitUI();
}

void CXPageColormap::Apply()
{
	m_pViewInfo->SetColormapName(m_ui.m_cbbTemplate->currentText());
	m_pViewInfo->SetDisplayDataMax(m_ui.m_edMax->text().toDouble());
	m_pViewInfo->SetDisplayDataMin(m_ui.m_edMin->text().toDouble());
	m_pViewInfo->SetBAutoCalcRange(m_ui.m_rbAutomatic->isChecked());
	m_pViewInfo->SetBZeroIsInvalid(m_ui.m_cbZeroIsInvalid->isChecked());
	_SetInvalidColor(m_ui.m_rbTransparent->isChecked() ? QColor(255, 255, 255, 0) : m_ui.m_btColor->GetColor());
	
	_SaveCustomizedColormap();

	CXProcessEvent processEvent;
	m_pObj->AddEvent(EColormapChanged);
}

void CXPageColormap::keyPressEvent(QKeyEvent* pEvent)
{
	if (pEvent->type() != QEvent::KeyPress)
		return QWidget::keyPressEvent(pEvent);

	if (pEvent->key() == Qt::Key_Enter || pEvent->key() == Qt::Key_Return)
		focusNextPrevChild(true);
}

void CXPageColormap::_InitUI()
{
	if (!m_pViewInfo)
		return;

	QString strColormapName = m_pViewInfo->GetColormapName();

	m_ui.m_cbbTemplate->setCurrentText(strColormapName);
	m_ui.colormapEditor->SetColormap(strColormapName);
	(m_pViewInfo->GetBAutoCalcRange() ? m_ui.m_rbAutomatic : m_ui.m_rbManual)->setChecked(true);
	m_ui.m_edMin->setText(QString::number(m_pViewInfo->GetDisplayDataMin()));
	m_ui.m_edMax->setText(QString::number(m_pViewInfo->GetDisplayDataMax()));
	m_ui.m_cbZeroIsInvalid->setChecked(m_pViewInfo->GetBZeroIsInvalid());

	CXColormap *pColormap = CXColormap::GetColormap(strColormapName);
	const QColor& invalidColor = pColormap->GetInvalidColor();

	if (invalidColor.alpha() == 0)
	{
		m_ui.m_rbTransparent->setChecked(true);
	}
	else
	{
		m_ui.m_rbSpecified->setChecked(true);
		m_ui.m_btColor->blockSignals(true);
		m_ui.m_btColor->SetColor(invalidColor);
		m_ui.m_btColor->blockSignals(false);
	}

	_SetHistogram();
}

void CXPageColormap::_SetHistogram()
{
	double dMin = m_ui.m_edMin->text().toDouble();
	double dMax = m_ui.m_edMax->text().toDouble();

	if (dMin > dMax)
		return;

	const std::vector<double>& vecHorizontal = m_rHistogram.m_vecHorizontal;
	const std::vector<double>& vecVertical = m_rHistogram.m_vecVertical;

	Q_ASSERT(vecHorizontal.size() == 256 && vecVertical.size() == 256);

	auto begHorizontalIter = std::lower_bound(vecHorizontal.cbegin(), vecHorizontal.cend(), dMin);
	auto endHorizontalIter = std::upper_bound(vecHorizontal.cbegin(), vecHorizontal.cend(), dMax);

	auto begVerticalIter = std::next(vecVertical.cbegin(), std::distance(vecHorizontal.cbegin(), begHorizontalIter));
	auto endVerticalIter = std::next(vecVertical.cbegin(), std::distance(vecHorizontal.cbegin(), endHorizontalIter));

	QMap<double, double> mapPercent;
	auto iterValue = begVerticalIter;

	for (auto iterKey = begHorizontalIter; iterKey != endHorizontalIter; ++iterKey)
	{
		Q_ASSERT(iterValue != endVerticalIter);
		mapPercent.insert(*iterKey, *iterValue);
		++iterValue;
	}

	if (mapPercent.isEmpty())
		return;

	m_ui.colormapEditor->SetHistogram(mapPercent);
}

bool CXPageColormap::_IsRealtime()
{
	return m_ui.m_cbRealtime->checkState() == Qt::Checked;
}

void CXPageColormap::_SaveCustomizedColormap()
{
	if (m_pViewInfo->GetColormapName() != "customized")
		return;
	
	CXColormap *pColormap = CXColormap::GetColormap("customized");
	Q_ASSERT(pColormap);

	pColormap->SaveToProjectDB();
}

void CXPageColormap::_SwitchToCustom()
{
	m_ui.m_cbbTemplate->blockSignals(true);
	m_ui.m_cbbTemplate->UpdateColormapList();
	m_ui.m_cbbTemplate->SetCurrentText("customized");
	m_ui.m_cbbTemplate->UpdateCurrentColormapIcon();
	m_ui.m_cbbTemplate->blockSignals(false);
}

void CXPageColormap::_ConvertToCustomizedColormap()
{
	CXColormap::GetCustomizedColormap(CXColormap::GetColormap(m_ui.m_cbbTemplate->currentText()));

	_SwitchToCustom();
}

void CXPageColormap::_SetInvalidColor(const QColor& color)
{
	CXColormap *pColormap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());
	Q_ASSERT(pColormap);

	pColormap->SetInvalidColor(color);
}

void CXPageColormap::slotUpdateEditor()
{
	_SwitchToCustom();

	if (_IsRealtime())
	{
		m_pViewInfo->SetColormapName("customized");
		_SaveCustomizedColormap();

		CXProcessEvent processEvent;
		m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
	}
}

void CXPageColormap::slotTemplateChanged(const QString & text)
{
	m_ui.colormapEditor->SetColormap(text);

	if (_IsRealtime())
	{
		m_pViewInfo->SetColormapName(text);

		CXProcessEvent processEvent;
		m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
	}
}

void CXPageColormap::slotRetrieve()
{
	QString strFileName = QFileDialog::getOpenFileName(this, "Select colormap", CXDBIO::GetColormapFilePath(), "*.colormap.json");

	if (!strFileName.endsWith(".colormap.json"))
	{
		QMessageBox::warning(0, "Retrieve failed", "The selected file is not a valid colormap file.");
		return;
	}

	if (!CXColormap::ImportColormapFromFile(strFileName))
	{
		QMessageBox::warning(0, "Retrieve failed", "Reading the colormap file failed.");
	}

	m_ui.m_cbbTemplate->blockSignals(true);
	m_ui.m_cbbTemplate->UpdateColormapList();
	m_ui.m_cbbTemplate->blockSignals(false);

	QFileInfo fileInfo(strFileName);
	m_ui.m_cbbTemplate->SetCurrentText(fileInfo.baseName());
}

void CXPageColormap::slotSaveAs()
{
	QString strExportFile = QFileDialog::getSaveFileName(this, "Save colormap to disk", CXDBIO::GetColormapFilePath(), "Colormap file(*.colormap.json)");
	if (strExportFile.isEmpty())
	{
		QMessageBox::warning(0, "Save error", "No selected path.");
		return;
	}

	CXColormap *pColormap = CXColormap::GetColormap(m_ui.m_cbbTemplate->currentText());
	if (pColormap)
	{
		pColormap->SaveAs(strExportFile);
	}
}

void CXPageColormap::slotAutoCalculateDataRange(bool bAuto)
{
	if (!bAuto)
		return;

	double dMin, dMax;
	::GetObjectMinMaxByPercentile(dMin, dMax, 1., 99., m_rHistogram);

	m_ui.m_edMin->setText(QString::number(dMin));
	m_ui.m_edMax->setText(QString::number(dMax));

	_SetHistogram();

	if (_IsRealtime())
	{
		m_pViewInfo->SetBAutoCalcRange(bAuto);
		m_pViewInfo->SetDisplayDataMin(dMin);
		m_pViewInfo->SetDisplayDataMax(dMax);

		CXProcessEvent processEvent;
		m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
	}
}

void CXPageColormap::slotSetDisplayMin(double dValue)
{
	m_ui.m_rbManual->setChecked(true);
	m_ui.m_edMin->setText(QString::number(dValue));
	
	_SetHistogram();

	if (_IsRealtime())
	{
		m_pViewInfo->SetDisplayDataMin(dValue);

		CXProcessEvent processEvent;
		m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
	}
}

void CXPageColormap::slotSetDisplayMax(double dValue)
{
	m_ui.m_rbManual->setChecked(true); 
	m_ui.m_edMax->setText(QString::number(dValue));

	_SetHistogram();

	if (_IsRealtime())
	{
		m_pViewInfo->SetDisplayDataMax(dValue);

		CXProcessEvent processEvent;
		m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
	}
}

void CXPageColormap::slotChangeDisplayMinMax()
{
	QLineEdit* pLineEdit = dynamic_cast<QLineEdit*>(this->sender());
	
	double dMin = m_ui.m_edMin->text().toDouble();
	double dMax = m_ui.m_edMax->text().toDouble();
	
	if (m_ui.m_edMin == pLineEdit && dMin >= dMax)
	{
		m_ui.m_edMin->undo();
		m_ui.m_edMin->setFocus();
		return;
	}
	else if (m_ui.m_edMax == pLineEdit && dMax <= dMin)
	{
		m_ui.m_edMin->undo();
		m_ui.m_edMin->setFocus();
		return;
	}

	_SetHistogram();

	if (_IsRealtime())
	{
		m_pViewInfo->SetDisplayDataMin(dMin);
		m_pViewInfo->SetDisplayDataMax(dMax);

		CXProcessEvent processEvent;
		m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
	}
}

void CXPageColormap::slotSetDefaultDataRange()
{
	m_ui.m_edMin->setText(QString::number(m_rHistogram.m_dDataMin));
	m_ui.m_edMax->setText(QString::number(m_rHistogram.m_dDataMax));

	_SetHistogram();

	if (_IsRealtime())
	{
		m_pViewInfo->SetDisplayDataMin(m_rHistogram.m_dDataMin);
		m_pViewInfo->SetDisplayDataMax(m_rHistogram.m_dDataMax);

		CXProcessEvent processEvent;
		m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
	}
}

void CXPageColormap::slotSetInvalidColorTransparent()
{
	_ConvertToCustomizedColormap();

	if (!_IsRealtime())
		return;

	_SetInvalidColor(QColor(255, 255, 255, 0));

	CXProcessEvent processEvent;
	m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
}

void CXPageColormap::slotSetInvalidColor(const QColor& color)
{
	_ConvertToCustomizedColormap();

	if (!_IsRealtime())
		return;

	_SetInvalidColor(color);

	CXProcessEvent processEvent;
	m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
}

void CXPageColormap::slotZeroIsInvalid(bool bChecked)
{
	if (!_IsRealtime())
		return;

	m_pViewInfo->SetBZeroIsInvalid(bChecked);

	CXProcessEvent processEvent;
	m_pObj->GetGeometryObject()->AddEvent(EColormapChanged);
}