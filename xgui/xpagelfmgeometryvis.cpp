#include "xpagelfmgeometryvis.h"
#include "xviewinfolfmgeometry.h"
#include "xeventconsole.h"
#include "xlfmgeometry.h"

CXPageLFMGeometryVis::CXPageLFMGeometryVis(QWidget *parent, CXViewInfoObject* pViewInfo, CXObject* pObj, EXWindowType winType)
    : CXBasePropertyPage(parent), m_typeWin(winType)
{
    m_ui.setupUi(this);

    m_pViewInfo = dynamic_cast<CXViewInfoLFMGeometry*>(pViewInfo);
    Q_ASSERT(m_pViewInfo);

	m_pObj = dynamic_cast<CXLFMGeometry*>(pObj);

    _Init();
    _InitData();
}

CXPageLFMGeometryVis::~CXPageLFMGeometryVis()
{

}

void CXPageLFMGeometryVis::slotInlineValueChanged()
{
    m_pViewInfo->SetMinInline(m_ui.m_pSliderInline->GetMinValue());
    m_pViewInfo->SetMaxInline(m_ui.m_pSliderInline->GetMaxValue());

    CXProcessEvent processEvent;
    m_pObj->AddEvent(EInfoChanged);
}

void CXPageLFMGeometryVis::slotCrosslineValueChanged()
{
    m_pViewInfo->SetMinCrossline(m_ui.m_pSliderCrossline->GetMinValue());
    m_pViewInfo->SetMaxCrossline(m_ui.m_pSliderCrossline->GetMaxValue());

    CXProcessEvent processEvent;
    m_pObj->AddEvent(EInfoChanged);
}

void CXPageLFMGeometryVis::slotCheckChanged(QTableWidgetItem * pItem)
{
	if (pItem->column() != 0)
		return;

	m_ui.m_pTableZone->cellWidget(pItem->row(), 1)->setEnabled(Qt::Checked == pItem->checkState());
	m_ui.m_pTableZone->cellWidget(pItem->row(), 2)->setEnabled(Qt::Checked == pItem->checkState());

	std::vector<bool> vecZoneDisplay = m_pViewInfo->GetVecZoneDisplay();
	vecZoneDisplay.at(pItem->row()) = Qt::Checked == pItem->checkState();
	m_pViewInfo->SetVecZoneDisplay(vecZoneDisplay);

	CXProcessEvent processEvent;
	m_pObj->AddEvent(EInfoChanged);
}

void CXPageLFMGeometryVis::slotColorChanged(const QColor & color)
{
	std::vector<QRgb> m_colors;

	for (int r = 0; r != m_ui.m_pTableZone->rowCount(); ++r)
	{
		auto pColorBtn = dynamic_cast<CXButtonColorEdit*>(m_ui.m_pTableZone->cellWidget(r, 1));
		Q_ASSERT(pColorBtn);

		m_colors.push_back(pColorBtn->GetColor().rgba());
	}

	m_pViewInfo->SetVecZoneColor(m_colors);

	CXProcessEvent processEvent;
	m_pObj->AddEvent(EInfoChanged);
}

void CXPageLFMGeometryVis::slotRangeChanged()
{
	std::vector<int> m_vecMinSlice, m_vecMaxSlice;

	for (int r = 0; r != m_ui.m_pTableZone->rowCount(); ++r)
	{
		auto pSlider = dynamic_cast<CXSliderComplex*>(m_ui.m_pTableZone->cellWidget(r, 2));
		Q_ASSERT(pSlider);

		m_vecMinSlice.push_back(pSlider->GetMinValue());
		m_vecMaxSlice.push_back(pSlider->GetMaxValue());
	}

	m_pViewInfo->SetVecZoneMinSlice(m_vecMinSlice);
	m_pViewInfo->SetVecZoneMaxSlice(m_vecMaxSlice);

	CXProcessEvent processEvent;
	m_pObj->AddEvent(EInfoChanged);
}

void CXPageLFMGeometryVis::Apply()
{
    m_pViewInfo->SetMinInline(m_ui.m_pSliderInline->GetMinValue());
    m_pViewInfo->SetMaxInline(m_ui.m_pSliderInline->GetMaxValue());
    m_pViewInfo->SetMinCrossline(m_ui.m_pSliderCrossline->GetMinValue());
    m_pViewInfo->SetMaxCrossline(m_ui.m_pSliderCrossline->GetMaxValue());

    m_pViewInfo->SetDisplayTopAndBottomLine(m_ui.m_pChkTopAndBottomLine->checkState() == Qt::Checked);
    m_pViewInfo->SetDisplayHorizontalSideLine(m_ui.m_pChkHorizontalSlice->checkState() == Qt::Checked);
    m_pViewInfo->SetDisplayVerticalSideLine(m_ui.m_pChkVerticalSlice->checkState() == Qt::Checked);

    m_pViewInfo->SetLineColor(m_ui.m_pClrBtnLine->GetColor());
    m_pViewInfo->SetLineSize(m_ui.m_pCmbLineSize->GetLineWidth());
	m_pViewInfo->SetVerticalLineSpacing(m_ui.m_pCmbVerticalLineSpacing->currentText().toInt());
}

void CXPageLFMGeometryVis::_Init()
{
    m_ui.m_pSliderInline->SetSliderName("Inline");
    m_ui.m_pSliderCrossline->SetSliderName("Crossline");

    connect(m_ui.m_pSliderInline, SIGNAL(SliderReleased()), this, SLOT(slotInlineValueChanged()));
    connect(m_ui.m_pSliderCrossline, SIGNAL(SliderReleased()), this, SLOT(slotCrosslineValueChanged()));

	if (eSectionWindow == m_typeWin || eSectionWindowBlank == m_typeWin)
	{
		m_ui.gbxDisplayRange->hide();
		m_ui.m_pChkTopAndBottomLine->hide();
		m_ui.m_pChkHorizontalSlice->hide();
		m_ui.m_pChkVerticalSlice->hide();
		m_ui.lblVerticalLineSpacing->hide();
		m_ui.m_pCmbVerticalLineSpacing->hide();
	}
}

void CXPageLFMGeometryVis::_InitData()
{
	const CXSeismicUTMTool& utm = m_pObj->GetUTM();

    m_ui.m_pSliderInline->SetRangeAndPrecision(utm.GetFirstInline(), utm.GetLastInline(), utm.GetInlineIncrement());
    m_ui.m_pSliderCrossline->SetRangeAndPrecision(utm.GetFirstCrossline(), utm.GetLastCrossline(), utm.GetCrosslineIncrement());

	m_ui.m_pSliderInline->SetMinPosition(m_pViewInfo->GetMinInline());
	m_ui.m_pSliderInline->SetMaxPosition(m_pViewInfo->GetMaxInline());
	m_ui.m_pSliderCrossline->SetMinPosition(m_pViewInfo->GetMinCrossline());
	m_ui.m_pSliderCrossline->SetMaxPosition(m_pViewInfo->GetMaxCrossline());
    
    m_ui.m_pChkTopAndBottomLine->setCheckState(m_pViewInfo->GetDisplayTopAndBottomLine() ? Qt::Checked : Qt::Unchecked);
    m_ui.m_pChkHorizontalSlice->setCheckState(m_pViewInfo->GetDisplayHorizontalSideLine() ? Qt::Checked : Qt::Unchecked);
    m_ui.m_pChkVerticalSlice->setCheckState(m_pViewInfo->GetDisplayVerticalSideLine() ? Qt::Checked : Qt::Unchecked);

    m_ui.m_pClrBtnLine->SetColor(m_pViewInfo->GetLineColor());
    m_ui.m_pCmbLineSize->SetLineWidth(m_pViewInfo->GetLineSize());
	m_ui.m_pCmbVerticalLineSpacing->setCurrentText(QString::number(m_pViewInfo->GetVerticalLineSpacing()));

	QStringList listZoneName = m_pObj->GetZoneNameList();
	std::vector<int> vecIndex = m_pObj->GetHorizonIndex();

	Q_ASSERT(listZoneName.size() + 1 == vecIndex.size());

	m_ui.m_pTableZone->setRowCount(listZoneName.size());
	m_ui.m_pTableZone->setColumnCount(3);

	std::vector<bool> vecZoneDisplay = m_pViewInfo->GetVecZoneDisplay();
	std::vector<QRgb> vecZoneColor = m_pViewInfo->GetVecZoneColor();
	std::vector<int> vecZoneMinSlice = m_pViewInfo->GetVecZoneMinSlice();
	std::vector<int> vecZoneMaxSlice = m_pViewInfo->GetVecZoneMaxSlice();

	for (int i = 0; i != listZoneName.size(); ++i)
	{
		auto pItemZoneName = new QTableWidgetItem(listZoneName.at(i));
		pItemZoneName->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
		pItemZoneName->setCheckState(vecZoneDisplay.at(i) ? Qt::Checked : Qt::Unchecked);

		auto pClrZone = new CXButtonColorEdit;
		pClrZone->SetColor(QColor(vecZoneColor.at(i)));

		auto pSliderSlice = new CXSliderComplex;
		pSliderSlice->SetNameVisible(false);
		pSliderSlice->SetRangeAndPrecision(vecIndex.at(i), vecIndex.at(i + 1), 1);
		pSliderSlice->SetMinPosition(vecZoneMinSlice.at(i));
		pSliderSlice->SetMaxPosition(vecZoneMaxSlice.at(i));

		m_ui.m_pTableZone->setItem(i, 0, pItemZoneName);
		m_ui.m_pTableZone->setCellWidget(i, 1, pClrZone);
		m_ui.m_pTableZone->setCellWidget(i, 2, pSliderSlice);

		connect(pClrZone, &CXButtonColorEdit::ColorSelected, this, &CXPageLFMGeometryVis::slotColorChanged);
		connect(pSliderSlice, &CXSliderComplex::SliderReleased, this, &CXPageLFMGeometryVis::slotRangeChanged);
	}

	m_ui.m_pTableZone->setHorizontalHeaderLabels({"Zone", "Color", "Slice Range"});
	m_ui.m_pTableZone->resizeColumnsToContents();
	connect(m_ui.m_pTableZone, &QTableWidget::itemClicked, this, &CXPageLFMGeometryVis::slotCheckChanged);
}