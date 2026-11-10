#include "xpagesurfacevis.h"
#include <cassert>
#include <QDoubleValidator>
#include <QIcon>
#include "xglobal.h"
#include <QInputDialog>
#include "xbaseconsole.h"
#include "xglobal.h"
#include "xautogrid.h"
#include "xcolormap.h"
#include "x3dsurface.h"

CXPageSurfaceVis::CXPageSurfaceVis(QWidget *parent, CXViewInfoObject* pViewInfo, CXObject *pObj, EXWindowType typeWin)
	: CXBasePropertyPage(parent), m_pObj(pObj), m_typeWin(typeWin)
{
	m_ui.setupUi(this);
	m_pViewInfo = dynamic_cast<CXViewInfoSurface*>(pViewInfo);

	_InitUI();
	_InitFillWidget();
	_InitContour();
}

CXPageSurfaceVis::~CXPageSurfaceVis()
{
}

void CXPageSurfaceVis::Apply()
{
	if (!m_pViewInfo)
		return;

	m_pViewInfo->SetDisplayMode(m_ui.m_pModeButtonGroup->checkedId());

	switch (m_ui.m_pModeButtonGroup->checkedId())
	{
	case 0: // Point
		m_pViewInfo->SetPointColorType(m_ui.m_pPointColorBtn->ColorType());
		m_pViewInfo->SetPointColor(m_ui.m_pPointColorBtn->GetColor());
		m_pViewInfo->SetPointSize(m_ui.spinBox_pointSize->value());
		break;
	case 1: // Surface
		m_pViewInfo->SetFillColorType(m_ui.m_pFillColorBtn->ColorType());

		m_pViewInfo->SetMaxLevel(m_ui.m_pEdtMaxLevel->text().toFloat());
		m_pViewInfo->SetMinLevel(m_ui.m_pEdtMinLevel->text().toFloat());
		m_pViewInfo->SetIncLevel(m_ui.m_pEdtFillInc->text().toFloat());
		m_pViewInfo->SetReverseColormap(m_ui.m_pReverseColorMap->isChecked());

		m_pViewInfo->SetDiscreteFillColorName(m_ui.m_pCombFillColorBar->currentText());

		m_pViewInfo->SetContourVisible(m_ui.m_pContourVisible->isChecked());
		m_pViewInfo->SetContourStart(m_ui.m_pEdtContourStart->text().toFloat());
		m_pViewInfo->SetContourEnd(m_ui.m_pEdtContourEnd->text().toFloat());
		m_pViewInfo->SetContourInc(m_ui.m_pEdtContourInc->text().toFloat());

		if (m_ui.m_pFillColorBtn->ColorType() == 3)
		{
			int nRowCount = m_ui.m_pFillColorTable->rowCount();
			if (nRowCount > 0)
			{
				m_pViewInfo->ClearDiscreteContourFillColor();
				for (int i = 0; i < nRowCount; ++i)
				{
					CXButtonColorEdit* pBtnColor = (CXButtonColorEdit*)m_ui.m_pFillColorTable->cellWidget(i, 2);
					if (pBtnColor)
					{
						const QString& strStart = m_ui.m_pFillColorTable->item(i, 0)->text();
						const QString& strLast = m_ui.m_pFillColorTable->item(i, 1)->text();
						m_pViewInfo->AddDiscreteContourFillColor(strStart.toFloat(), strLast.toFloat(), pBtnColor->GetColor());
					}
				}
			}
		}
		else
		{
			m_pViewInfo->SetFillColor(m_ui.m_pFillColorBtn->GetColor());
		}
		break;
	case 2: // Fracture
		m_pViewInfo->SetFracColorType(m_ui.m_pFracColorBtn->ColorType());
		m_pViewInfo->SetFracColor(m_ui.m_pFracColorBtn->GetColor());
		m_pViewInfo->SetFracAzimuth(m_ui.m_pCbbFracAzimuth->currentData().toUuid());
		m_pViewInfo->SetFracDensity(m_ui.m_pCbbFracDensity->currentData().toUuid());
		m_pViewInfo->SetFracDX(m_ui.m_editFracDx->text().toInt());
		m_pViewInfo->SetFracDY(m_ui.m_editFracDy->text().toInt());
		m_pViewInfo->SetFracScale(m_ui.m_editFracScale->text().toFloat());
		m_pViewInfo->SetFracMinThreshold(m_ui.m_editFracMinThreshold->text().toInt() / 100.f);
		m_pViewInfo->SetFracMaxThreshold(m_ui.m_editFracMaxThreshold->text().toInt() / 100.f);
		m_pViewInfo->SetFracWidth(m_ui.m_editFracWidth->text().toInt());
		m_pViewInfo->SetFracHeight(m_ui.m_editFracHeight->text().toInt());
		m_pViewInfo->SetFracOffset(m_ui.m_editFracOffset->text().toFloat());
		break;
	default:
		Q_ASSERT(!"no this mode");
	}
}

void CXPageSurfaceVis::_InitUI()
{
	m_ui.m_pModeButtonGroup->setId(m_ui.m_DispModPointradioBtn, 0);
	m_ui.m_pModeButtonGroup->setId(m_ui.m_DispModSurfaceradioBtn, 1);
	m_ui.m_pModeButtonGroup->setId(m_ui.m_DispModFracradioBtn, 2);

	m_ui.m_pFracGroupBox->hide();
	m_ui.m_pPointGroupBox->hide();
	m_ui.m_pWgtFill->hide();

	m_ui.m_DispModFracradioBtn->setDisabled(m_pViewInfo->GetFracAzimuth().isNull() || m_pViewInfo->GetFracDensity().isNull());

	if (EX3DSurface == m_pObj->GetObjectType())
	{
		m_ui.m_pDisplayModeGroupBox->hide();
	}

	if (m_typeWin != e3DWindow)
	{
		m_ui.m_pLblFracHeight->hide();
		m_ui.m_editFracHeight->hide();
	}

	if (!m_pViewInfo)
		return;

	m_ui.m_pModeButtonGroup->button(m_pViewInfo->GetDisplayMode())->setChecked(true);

	m_ui.m_pPointColorBtn->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui.m_pPointColorBtn->AddColormapButton();
	m_ui.m_pPointColorBtn->SetColor(m_pViewInfo->GetPointColorType(), m_pViewInfo->GetPointColor());
	m_ui.spinBox_pointSize->setValue(m_pViewInfo->GetPointSize());

	m_ui.m_pFillColorBtn->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui.m_pFillColorBtn->AddColormapButton();
	m_ui.m_pFillColorBtn->AddButton("Discrete contour fill", QColor::Invalid);
	m_ui.m_pFillColorBtn->AddButton("Bitmap", QColor::Invalid);
	m_ui.m_pFillColorBtn->SetColor(m_pViewInfo->GetFillColorType(), m_pViewInfo->GetFillColor());

	m_ui.m_pMajorLineColorBtn->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui.m_pMinorLineColorBtn->AddObjectColorButton(m_pViewInfo->GetColor());

	m_ui.m_pContourVisible->setChecked(m_pViewInfo->GetContourVisible());

	_InitAttributeList();
	
	int iFracAzimuteIndex = m_ui.m_pCbbFracAzimuth->findData(m_pViewInfo->GetFracAzimuth());
	if (iFracAzimuteIndex != -1)
	{
		m_ui.m_pCbbFracAzimuth->setCurrentIndex(iFracAzimuteIndex);
	}
	
	int iFracDensityIndex = m_ui.m_pCbbFracDensity->findData(m_pViewInfo->GetFracDensity());
	if (iFracDensityIndex != -1)
	{
		m_ui.m_pCbbFracDensity->setCurrentIndex(iFracDensityIndex);
	}

	m_ui.m_pFracColorBtn->AddButton("Density Color map", QColor::Invalid);
	m_ui.m_pFracColorBtn->SetColor(m_pViewInfo->GetFracColorType(), m_pViewInfo->GetFracColor());
	m_ui.m_editFracDx->setText(QString::number(m_pViewInfo->GetFracDX()));
	m_ui.m_editFracDy->setText(QString::number(m_pViewInfo->GetFracDY()));
	m_ui.m_editFracScale->setText(QString::number(m_pViewInfo->GetFracScale()));
	m_ui.m_editFracMinThreshold->setText(QString::number(m_pViewInfo->GetFracMinThreshold() * 100));
	m_ui.m_editFracMaxThreshold->setText(QString::number(m_pViewInfo->GetFracMaxThreshold() * 100));
	m_ui.m_editFracWidth->setText(QString::number(m_pViewInfo->GetFracWidth()));
	m_ui.m_editFracHeight->setText(QString::number(m_pViewInfo->GetFracHeight()));
	m_ui.m_editFracOffset->setText(QString::number(m_pViewInfo->GetFracOffset()));

	QDoubleValidator* pContourIncValidator = new QDoubleValidator(0.01, 10000.0, 2, m_ui.m_pEdtContourInc);
	pContourIncValidator->setNotation(QDoubleValidator::StandardNotation);
	m_ui.m_pEdtContourInc->setValidator(pContourIncValidator);

	QDoubleValidator* pContourStartValidator = new QDoubleValidator(-100000.0, 10000.0, 2, m_ui.m_pEdtContourStart);
	pContourStartValidator->setNotation(QDoubleValidator::StandardNotation);
	m_ui.m_pEdtContourStart->setValidator(pContourStartValidator);

	QDoubleValidator* pContourEndValidator = new QDoubleValidator(-100000.0, 10000.0, 2, m_ui.m_pEdtContourStart);
	pContourEndValidator->setNotation(QDoubleValidator::StandardNotation);
	m_ui.m_pEdtContourEnd->setValidator(pContourEndValidator);

	connect(m_ui.m_pEdtContourInc, SIGNAL(editingFinished()), SLOT(slotContourIncValidChecking()));
	connect(m_ui.m_pEdtFillInc, SIGNAL(editingFinished()), SLOT(slotContourFillIncChanged()));
	connect(m_ui.m_pBtnFillAdd, &QPushButton::pressed, this, &CXPageSurfaceVis::slotFillAdd);
	connect(m_ui.m_pBtnFillDel, &QPushButton::pressed, this, &CXPageSurfaceVis::slotFillDel);
	connect(m_ui.m_pBtnFillNum, &QPushButton::pressed, this, &CXPageSurfaceVis::slotFillNum);
	connect(m_ui.m_pFillColorBtn, SIGNAL(ColorTypeChanged(int)), SLOT(slotFillColorChange(int)));
	connect(m_ui.m_pCombFillColorBar, SIGNAL(currentIndexChanged(int)), SLOT(slotFillColormapChange(int)));
	connect(m_ui.m_pComboBoxAttr, SIGNAL(currentIndexChanged(int)), SLOT(slotChangeAttribute(int)));
	connect(m_ui.m_pFillColorTable, SIGNAL(cellChanged(int, int)), this, SLOT(slotChangedTableItem(int, int)));
}

void CXPageSurfaceVis::_InitFillWidget()
{
	float fLevelStart = m_pViewInfo->GetMinLevel();
	float fLevelEnd = m_pViewInfo->GetMaxLevel();
	float fLevelInc = m_pViewInfo->GetIncLevel();

	_GetDefaultDataSegment(fLevelStart, fLevelEnd, fLevelInc);

	m_ui.m_pEdtMinLevel->setText(QString::number(fLevelStart));
	m_ui.m_pEdtMaxLevel->setText(QString::number(fLevelEnd));
	m_ui.m_pEdtFillInc->setText(QString::number(fLevelInc));
	m_ui.m_pReverseColorMap->setChecked(m_pViewInfo->GetReverseColormap());

	m_ui.m_pCombFillColorBar->blockSignals(true);
	m_ui.m_pCombFillColorBar->SetCurrentText(m_pViewInfo->GetDiscreteFillColorName());
	m_ui.m_pCombFillColorBar->blockSignals(false);

	const QMap<CXRange<float>, QColor>& rangeColor = m_pViewInfo->GetDiscreteContourFillColor();
	if (rangeColor.empty())
	{
		_UpdateContourTableByRowNum(qRound((fLevelEnd - fLevelStart) / fLevelInc));
		return;
	}

	m_ui.m_pFillColorTable->blockSignals(true);
	m_ui.m_pFillColorTable->setRowCount(rangeColor.size());

	for (auto iter = rangeColor.cbegin(); iter != rangeColor.cend(); ++iter)
	{
		int index = std::distance(rangeColor.cbegin(), iter);
		auto pItemStart = new QTableWidgetItem(QString::number(iter.key().min));
		auto pItemLast = new QTableWidgetItem(QString::number(iter.key().max));
		pItemStart->setFlags(Qt::NoItemFlags);
		if (iter == std::prev(rangeColor.cend()))
		{
			pItemLast->setFlags(Qt::NoItemFlags);
		}
		m_ui.m_pFillColorTable->setItem(index, 0, pItemStart);
		m_ui.m_pFillColorTable->setItem(index, 1, pItemLast);
		m_ui.m_pFillColorTable->setCellWidget(index, 2, new CXButtonColorEdit(this, iter.value()));
	}

	m_ui.m_pFillColorTable->resizeRowsToContents();
	m_ui.m_pFillColorTable->blockSignals(false);
}

void CXPageSurfaceVis::_InitContour()
{
	float fContourStart = m_pViewInfo->GetContourStart();
	float fContourEnd = m_pViewInfo->GetContourEnd();
	float fContourInc = m_pViewInfo->GetContourInc();

	_GetDefaultDataSegment(fContourStart, fContourEnd, fContourInc);

	m_ui.m_pEdtContourStart->setText(QString::number(fContourStart));
	m_ui.m_pEdtContourEnd->setText(QString::number(fContourEnd));
	m_ui.m_pEdtContourInc->setText(QString::number(fContourInc));
	m_ui.m_pContourVisible->setChecked(m_pViewInfo->GetContourVisible());
}

void CXPageSurfaceVis::_UpdateContourTableByRowNum(int nRow)
{
	if (nRow < 1)
		return;

	m_ui.m_pFillColorTable->blockSignals(true);
	m_ui.m_pFillColorTable->clearContents();
	m_ui.m_pFillColorTable->setRowCount(nRow);

	const float fMinLevel = m_ui.m_pEdtMinLevel->text().toFloat();
	const float fMaxLevel = m_ui.m_pEdtMaxLevel->text().toFloat();
	float fIncLevel = (fMaxLevel - fMinLevel) / nRow;
	CXColormap *pColormap = CXColormap::GetColormap(m_ui.m_pCombFillColorBar->currentText());
	Q_ASSERT(pColormap);

	m_ui.m_pEdtFillInc->setText(QString::number(fIncLevel));

	for (int i = 0; i < nRow; ++i)
	{
		float fStart = fMinLevel + i * fIncLevel;

		auto pItemStart = new QTableWidgetItem(QString::number(fStart));
		auto pItemEnd = new QTableWidgetItem(QString::number(fStart + fIncLevel));

		pItemStart->setFlags(Qt::NoItemFlags);
		pItemEnd->setFlags(i == nRow - 1 ? Qt::NoItemFlags : Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);

		m_ui.m_pFillColorTable->setItem(i, 0, pItemStart);
		m_ui.m_pFillColorTable->setItem(i, 1, pItemEnd);
		
		auto pItemColorBtn = new CXButtonColorEdit;
		int iColorIndex = qRound(i * 1.f / (nRow - 1) * (pColormap->GetColorNum() - 1));
		pItemColorBtn->SetColor(pColormap->ColorAt(m_ui.m_pReverseColorMap->isChecked() ? (pColormap->GetColorNum() - iColorIndex - 1) : iColorIndex));
		
		m_ui.m_pFillColorTable->setCellWidget(i, 2, pItemColorBtn);
	}

	m_ui.m_pFillColorTable->resizeRowsToContents();
	m_ui.m_pFillColorTable->blockSignals(false);
}

void CXPageSurfaceVis::_GetDefaultDataSegment(float & fStart, float & fEnd, float & fInc)
{
	if (!qFuzzyCompare(fStart, 0.f) || !qFuzzyCompare(fEnd, 0.f) || !qFuzzyCompare(fInc, 0.f))
		return;

	// default division
	double dMin, dMax, dUnitStart, dUnitStop, dUnitStep;
	m_pObj->GetDataRange(dMin, dMax);
	if (dMin == dMax)
		return;

	CXAutoGrid::AutoGrid(dMin, dMax, 15, dUnitStart, dUnitStop, dUnitStep);

	fStart = dUnitStart;
	fEnd = dUnitStop;
	fInc = dUnitStep;
}

void CXPageSurfaceVis::_InitAttributeList()
{
	m_ui.m_pCbbFracAzimuth->clear();
	m_ui.m_pCbbFracDensity->clear();

	for (CXObject* pObj : m_pObj->GetChildren(EX3DHorizonAtt, true))
	{
		double dMin, dMax;
		pObj->GetDataRange(dMin, dMax);

		if (0.0 <= dMin && dMax <= 360.0 || -180.0 <= dMin && dMax <= 180.0)
		{
			m_ui.m_pCbbFracAzimuth->addItem(QIcon(::GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID());
		}

		m_ui.m_pCbbFracDensity->addItem(QIcon(::GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID());
	}
}

void CXPageSurfaceVis::slotFillColorChange(int nindex)
{
	bool bDiscreteContourFill = nindex == 3;
	m_ui.m_pWgtFill->setVisible(bDiscreteContourFill);
	m_ui.label_attri->setVisible(!bDiscreteContourFill);
	m_ui.m_pComboBoxAttr->setVisible(!bDiscreteContourFill);
	m_ui.label_start->setVisible(!bDiscreteContourFill);
	m_ui.label_end->setVisible(!bDiscreteContourFill);
	m_ui.label_inc->setVisible(!bDiscreteContourFill);
	m_ui.m_pEdtContourStart->setVisible(!bDiscreteContourFill);
	m_ui.m_pEdtContourEnd->setVisible(!bDiscreteContourFill);
	m_ui.m_pEdtContourInc->setVisible(!bDiscreteContourFill);
}

void CXPageSurfaceVis::slotChangeAttribute(int nIndex)
{
	auto pAttribute = dynamic_cast<CX3DSurface*>(::GetObjectByID(m_ui.m_pComboBoxAttr->itemData(nIndex).toUuid()));

	double dMin, dMax;
	pAttribute->GetDataRange(dMin, dMax);

	m_ui.m_pEdtContourStart->setText(QString::number(dMin));
	m_ui.m_pEdtContourEnd->setText(QString::number(dMax));
	m_ui.m_pEdtContourInc->setText(QString::number(0.05 * (dMax - dMin)));
}

void CXPageSurfaceVis::slotChangedTableItem(int row, int col)
{
	QTableWidgetItem* pTableItemStart = m_ui.m_pFillColorTable->item(row, col - 1);
	QTableWidgetItem* pTableItemEnd = m_ui.m_pFillColorTable->item(row, col);
	QTableWidgetItem* pTableItemNextStart = m_ui.m_pFillColorTable->item(row + 1, col - 1);
	QTableWidgetItem* pTableItemNextEnd = m_ui.m_pFillColorTable->item(row + 1, col);

	float fMin = pTableItemStart->text().toFloat();
	float fMax = pTableItemNextEnd->text().toFloat();
	float fCur = pTableItemEnd->text().toFloat();

	if (fCur <= fMin || fCur >= fMax)
		return;

	m_ui.m_pFillColorTable->blockSignals(true);
	pTableItemNextStart->setText(QString::number(fCur));
	m_ui.m_pFillColorTable->blockSignals(false);
}

void CXPageSurfaceVis::slotFillColormapChange(int nIndex)
{
	CXColormap* pColormap = CXColormap::GetColormap(nIndex);
	Q_ASSERT(pColormap);

	for (int i = 0; i < m_ui.m_pFillColorTable->rowCount(); i++)
	{
		int iColorIndex = qRound(i * 1.f / (m_ui.m_pFillColorTable->rowCount() - 1) * (pColormap->GetColorNum() - 1));
		auto pItemColorBtn = dynamic_cast<CXButtonColorEdit*>(m_ui.m_pFillColorTable->cellWidget(i, 2));
		pItemColorBtn->SetColor(pColormap->ColorAt(m_ui.m_pReverseColorMap->isChecked() ? (pColormap->GetColorNum() - iColorIndex - 1) : iColorIndex));
	}
}

void CXPageSurfaceVis::slotContourFillIncChanged()
{
	float fEnd = m_ui.m_pEdtMaxLevel->text().toFloat();
	float fStart = m_ui.m_pEdtMinLevel->text().toFloat();
	float fInc = m_ui.m_pEdtFillInc->text().toFloat();
	
	if (fInc <= 0.0f || fEnd - fStart < fInc)
	{
		fInc = (fEnd - fStart) / 50.0f;
		m_ui.m_pEdtFillInc->setText(QString::number(fInc));
	}

	_UpdateContourTableByRowNum(qRound((fEnd - fStart) / fInc));
}

void CXPageSurfaceVis::slotContourIncValidChecking()
{
	float fInc = m_ui.m_pEdtContourInc->text().toFloat();
	float fStart = m_ui.m_pEdtContourStart->text().toFloat();
	float fEnd = m_ui.m_pEdtContourEnd->text().toFloat();
	if (fInc <= 0.0f || fEnd - fStart < fInc)
	{
		m_ui.m_pEdtContourInc->setText(QString::number((fEnd - fStart) / 50.0f));
	}
}

void CXPageSurfaceVis::slotFillAdd()
{
	int nNewRowCount = m_ui.m_pFillColorTable->rowCount() + 1;
	m_ui.m_pFillColorTable->setRowCount(nNewRowCount);
	_UpdateContourTableByRowNum(nNewRowCount);
}

void CXPageSurfaceVis::slotFillDel()
{
	int nNewRowCount = m_ui.m_pFillColorTable->rowCount() - 1;
	if (nNewRowCount < 0)
		return;
	
	m_ui.m_pFillColorTable->setRowCount(nNewRowCount);
	_UpdateContourTableByRowNum(nNewRowCount);
}

void CXPageSurfaceVis::slotFillNum()
{
	float fIncFill = m_ui.m_pEdtFillInc->text().toFloat();

	if (fIncFill <= 0)
		return;

	bool bOK = false;
	int nNewRowCount = QInputDialog::getInt(this, tr("Contour Lever Number:"),
		tr("Please input contour lever number:"), m_ui.m_pFillColorTable->rowCount(), 1, 256, 1, &bOK);

	if (!bOK || nNewRowCount == m_ui.m_pFillColorTable->rowCount())
		return;

	_UpdateContourTableByRowNum(nNewRowCount);
}