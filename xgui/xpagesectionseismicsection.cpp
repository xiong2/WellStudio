#include "xpagesectionseismicsection.h"
#include "xseismicsection.h"
#include "xeventconsole.h"

CXPageSectionSeismicSection::CXPageSectionSeismicSection(QWidget *parent, CXObject *pObj)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);

	m_pSection = dynamic_cast<CXSeismicSection*>(pObj);
	Q_ASSERT(m_pSection);

	_Init();
}

CXPageSectionSeismicSection::~CXPageSectionSeismicSection()
{

}

void CXPageSectionSeismicSection::Apply()
{
	m_pSection->SetSectionRange(m_ui.m_sliderSectionRange->GetMinValue(), m_ui.m_sliderSectionRange->GetMaxValue());
	
	CXProcessEvent processEvent;
	m_pSection->AddEvent(EDataChanged);
}

void CXPageSectionSeismicSection::_Init()
{
	_InitBySectionType();

	int iSTrace, iETrace;
	m_pSection->GetSectionRange(iSTrace, iETrace);
	
	if (iSTrace != -1)
	{
		m_ui.m_sliderSectionRange->SetMinPosition(iSTrace);
	}

	if (iETrace != -1)
	{
		m_ui.m_sliderSectionRange->SetMaxPosition(iETrace);
	}
}

void CXPageSectionSeismicSection::_InitBySectionType()
{
	const CXSeismicUTMTool& utm = m_pSection->GetUTM();
	EXSectionType type = m_pSection->GetSectionType();

	if (type == eInlineSection)
	{
		m_ui.m_sliderSectionRange->SetSliderName("CDP: ");
		m_ui.m_sliderSectionRange->SetRangeAndPrecision(utm.GetFirstCrossline(), utm.GetLastCrossline(), utm.GetCrosslineIncrement());
	}
	else if (type == eCrosslineSection)
	{
		m_ui.m_sliderSectionRange->SetSliderName("Inline: ");
		m_ui.m_sliderSectionRange->SetRangeAndPrecision(utm.GetFirstInline(), utm.GetLastInline(), utm.GetInlineIncrement());
	}
	else
	{
		throw std::logic_error("There is no such section.");
	}
}