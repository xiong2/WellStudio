#include "xsliderlineedit.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QValidator>

CXSliderLineEdit::CXSliderLineEdit(CXSliderLineEditInfo info, QWidget *parent)
    : QWidget(parent), m_info(info)
{
    m_pLabelTitle = new QLabel(info.m_title, this);

    m_pLineEdit = new QLineEdit(this);
    m_pLineEdit->setValidator(new QIntValidator(info.m_iBeg, info.m_iEnd, this));

    m_pLabelMin = new QLabel(QString::number(info.m_iBeg), this);
    m_pLabelMax = new QLabel(QString::number(info.m_iEnd), this);
    
    m_pSlider = new QSlider(this);
    m_pSlider->setMinimumWidth(200);
    m_pSlider->setOrientation(Qt::Horizontal);
    m_pSlider->setRange(info.m_iBeg, info.m_iEnd);
    m_pSlider->setSingleStep(info.m_iStep);

    auto pMainLayout = new QHBoxLayout(this);
    pMainLayout->setMargin(0);
    pMainLayout->setSpacing(6);
    setLayout(pMainLayout);

    pMainLayout->addWidget(m_pLabelTitle);
    pMainLayout->addWidget(m_pLineEdit);
    pMainLayout->addWidget(m_pLabelMin);
    pMainLayout->addWidget(m_pSlider, 2);
    pMainLayout->addWidget(m_pLabelMax);

    _BlockSignals(false);
    connect(m_pSlider, SIGNAL(SliderReleased()), this, SIGNAL(SliderReleased()));
}

CXSliderLineEdit::~CXSliderLineEdit()
{

}

int CXSliderLineEdit::GetValue() const
{
    return m_pSlider->value();
}

void CXSliderLineEdit::SetValue(int value)
{
    _BlockSignals(true);

    m_pSlider->setValue(_GetCorrectValue(value));
    m_pLineEdit->setText(QString::number(value));

    _BlockSignals(false);
}

int CXSliderLineEdit::GetMinValue() const
{
    return m_info.m_iBeg;
}

int CXSliderLineEdit::GetMaxValue() const
{
    return m_info.m_iEnd;
}

void CXSliderLineEdit::SetFixedTitleWidth(int width)
{
    m_pLabelTitle->setFixedWidth(width);
}

void CXSliderLineEdit::SetFixedLineEditWidth(int width)
{
    m_pLineEdit->setFixedWidth(width);
}

void CXSliderLineEdit::_BlockSignals(bool bBlock)
{
    if (bBlock)
    {
        disconnect(m_pSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSliderValueChanged(int)));
		disconnect(m_pLineEdit, SIGNAL(editingFinished()), this, SLOT(slotLineEditChanged()));
    }
    else
    {
        connect(m_pSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSliderValueChanged(int)));
		connect(m_pLineEdit, SIGNAL(editingFinished()), this, SLOT(slotLineEditChanged()));
    }
}

int CXSliderLineEdit::_GetCorrectValue(int value)
{
    auto iFactor = (value - m_info.m_iBeg) / m_info.m_iStep;
    return m_info.m_iBeg + iFactor * m_info.m_iStep;
}

void CXSliderLineEdit::slotLineEditChanged()
{
    _BlockSignals(true);

	auto iCorrectValue = _GetCorrectValue(m_pLineEdit->text().toInt());
    m_pLineEdit->setText(QString::number(iCorrectValue));
    m_pSlider->setValue(iCorrectValue);

    _BlockSignals(false);
    emit ValueChanged(iCorrectValue);
}

void CXSliderLineEdit::slotSliderValueChanged(int iValue)
{
    _BlockSignals(true);

    auto iCorrectValue = _GetCorrectValue(iValue);
    m_pLineEdit->setText(QString::number(iCorrectValue));
    m_pSlider->setValue(iCorrectValue);

    _BlockSignals(false);
    emit ValueChanged(iCorrectValue);
}

/*===============================================================
    CXRangeWidget
===============================================================*/

CXRangeWidget::CXRangeWidget(CXSliderLineEditInfo info, QWidget *parent) 
    : QWidget(parent), m_info(info)
{
    auto info1(m_info);
    info1.m_title = "Start " + info1.m_title;
    m_sliderLineEdit1 = new CXSliderLineEdit(info1);
    m_sliderLineEdit1->SetValue(info.m_iBeg);

    auto info2(m_info);
    info2.m_title = "End " + info2.m_title;
    m_sliderLineEdit2 = new CXSliderLineEdit(info2);
    m_sliderLineEdit2->SetValue(info.m_iEnd);

    auto pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(m_sliderLineEdit1);
    pMainLayout->addWidget(m_sliderLineEdit2);

    setLayout(pMainLayout);
    _BlockSignals(false);
}

CXRangeWidget::~CXRangeWidget()
{
}

CXSliderLineEdit* CXRangeWidget::GetSliderLineEidt1() const
{
    return m_sliderLineEdit1;
}

CXSliderLineEdit* CXRangeWidget::GetSliderLineEidt2() const
{
    return m_sliderLineEdit2;
}

void CXRangeWidget::_BlockSignals(bool bBlock)
{
    if (bBlock)
    {
        disconnect(m_sliderLineEdit1, SIGNAL(ValueChanged(int)), this, SLOT(slotBegValueChanged(int)));
        disconnect(m_sliderLineEdit2, SIGNAL(ValueChanged(int)), this, SLOT(slotEndValueChanged(int)));
        disconnect(m_sliderLineEdit1, SIGNAL(SliderReleased()), this, SLOT(slotValueChanged()));
        disconnect(m_sliderLineEdit2, SIGNAL(SliderReleased()), this, SLOT(slotValueChanged()));
    }
    else
    {
        connect(m_sliderLineEdit1, SIGNAL(ValueChanged(int)), this, SLOT(slotBegValueChanged(int)));
        connect(m_sliderLineEdit2, SIGNAL(ValueChanged(int)), this, SLOT(slotEndValueChanged(int)));
        connect(m_sliderLineEdit1, SIGNAL(SliderReleased()), this, SLOT(slotValueChanged()));
        connect(m_sliderLineEdit2, SIGNAL(SliderReleased()), this, SLOT(slotValueChanged()));
    }
}

void CXRangeWidget::slotBegValueChanged(int iBeg)
{
    _BlockSignals(true);

    m_sliderLineEdit1->SetValue(iBeg);

    if (iBeg > m_sliderLineEdit2->GetValue())
    {
        m_sliderLineEdit2->SetValue(iBeg);
    }

    _BlockSignals(false);
}

void CXRangeWidget::slotEndValueChanged(int iEnd)
{
    _BlockSignals(true);

    m_sliderLineEdit2->SetValue(iEnd);

    if (iEnd < m_sliderLineEdit1->GetValue())
    {
        m_sliderLineEdit1->SetValue(iEnd);
    }

    _BlockSignals(false);
}

void CXRangeWidget::slotValueChanged()
{
    emit ValueChanged(m_sliderLineEdit1->GetValue(), m_sliderLineEdit1->GetValue());
}

/*===============================================================
    CXRangeFrame
===============================================================*/

CXRangeFrame::CXRangeFrame(QWidget* parent, Qt::WindowFlags f) : QFrame(parent, f)
{
    m_pVBoxLayout = new QVBoxLayout;
    setLayout(m_pVBoxLayout);
}

CXRangeFrame::~CXRangeFrame()
{

}

void CXRangeFrame::AddOneLine(QString title, int iBegin, int iEnd, int iStep, bool bPair)
{
    if (iBegin > iEnd || iStep <= 0) return;

    CXSliderLineEditInfo info;
    info.m_title = title;
    info.m_iBeg = iBegin;
    info.m_iEnd = iEnd;
    info.m_iStep = iStep;

    if (!bPair)
    {
        auto pSliderEdit = new CXSliderLineEdit(info);
        m_pVBoxLayout->addWidget(pSliderEdit);
        m_listSliderLineEdit << pSliderEdit;
    }
    else
    {
        auto pRangeWidget = new CXRangeWidget(info);
        m_pVBoxLayout->addWidget(pRangeWidget);
        m_listSliderLineEdit << pRangeWidget->GetSliderLineEidt1();
        m_listSliderLineEdit << pRangeWidget->GetSliderLineEidt2();
    }

    _FormatWidth();
}

void CXRangeFrame::SetDisabled(int index, bool bDisable)
{
    if (index >= m_listSliderLineEdit.size()) return;
    m_listSliderLineEdit.at(index)->setDisabled(bDisable);
}

void CXRangeFrame::SetVisible(int index, bool bVisible)
{
    if (index >= m_listSliderLineEdit.size()) return;
    m_listSliderLineEdit.at(index)->setVisible(bVisible);
}

int CXRangeFrame::GetValueAt(int index) const
{
    if (index >= m_listSliderLineEdit.size()) return -1;
    return m_listSliderLineEdit.at(index)->GetValue();
}

void CXRangeFrame::SetValueAt(int index, int value)
{
    if (index >= m_listSliderLineEdit.size()) return;
    m_listSliderLineEdit.at(index)->SetValue(value);
}

void CXRangeFrame::_FormatWidth()
{
    QFontMetrics metrics(this->font());
    int title_width{ 0 }, value_width{ 0 };
    for (auto pSliderLineEdit : m_listSliderLineEdit)
    {
        title_width = qMax(title_width, metrics.width(pSliderLineEdit->GetInfo().m_title));
        value_width = qMax(value_width, metrics.width(QString::number(pSliderLineEdit->GetInfo().m_iEnd)));
    }
    for (auto pSliderLineEdit : m_listSliderLineEdit)
    {
        pSliderLineEdit->SetFixedTitleWidth(title_width + 5);
        pSliderLineEdit->SetFixedLineEditWidth(value_width + 10);
    }
}