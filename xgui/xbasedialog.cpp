#include "xbasedialog.h"

#include <QGridLayout>
#include <QDialogButtonBox>
#include <QPushButton>

CXBaseDialog::CXBaseDialog(QWidget *parent):QDialog(parent)
{
	m_pMainLayout = new QGridLayout(this);
	this->setLayout(m_pMainLayout);
	m_pButtonBox = new QDialogButtonBox(this);
	m_pButtonBox->setObjectName(QString::fromUtf8("pButtonBox"));
	m_pButtonBox->setOrientation(Qt::Horizontal);
	m_pButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
	m_pMainLayout->addWidget(m_pButtonBox, 1, 0, 1, 2);

	connect(m_pButtonBox, SIGNAL(accepted()), this, SLOT(slotOKClicked()));
	connect(m_pButtonBox, SIGNAL(rejected()), this, SLOT(slotCancelClicked()));
}	

CXBaseDialog::~CXBaseDialog(void)
{
}

void CXBaseDialog::slotOKClicked()
{
	OnOK();
	QDialog::accept();
}	

void CXBaseDialog::slotCancelClicked()
{
	QDialog::reject();
}

void CXBaseDialog::SetOKEnabled(bool bEnabled)
{
	QPushButton *pTbn = m_pButtonBox->button(QDialogButtonBox::Ok);
	if (pTbn) {
		pTbn->setEnabled(bEnabled);
	}
}