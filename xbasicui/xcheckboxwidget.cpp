#include "xcheckboxwidget.h"
#include <QCheckBox>
#include <QHBoxLayout>

CXCheckBoxWidget::CXCheckBoxWidget(QWidget* parent)
    : QWidget(parent), m_pCheckBox(new QCheckBox())
{
    auto pHorizonLayout = new QHBoxLayout();
    pHorizonLayout->setAlignment(Qt::AlignHCenter);
    pHorizonLayout->addWidget(m_pCheckBox);
    setLayout(pHorizonLayout);

    connect(m_pCheckBox, &QCheckBox::stateChanged, this, &CXCheckBoxWidget::StateChanged);
}

CXCheckBoxWidget::~CXCheckBoxWidget()
{
}

bool CXCheckBoxWidget::IsChecked() const
{
    return m_pCheckBox->isChecked();
}

void CXCheckBoxWidget::SetChecked(bool bChecked)
{
    m_pCheckBox->setChecked(bChecked);
}
