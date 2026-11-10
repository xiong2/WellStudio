#include "xdlgprojectproperties.h"
#include "xproject.h"
#include "xglobal.h"
#include "xpageprojectproperties.h"

CXDlgProjectProperties::CXDlgProjectProperties(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Properties for [" + ::GetProject()->GetObjectName() + "]");

	connect(m_ui.m_buttonBox, SIGNAL(clicked(QAbstractButton*)), SLOT(slotButtonClicked(QAbstractButton*)));

	_AddMiscPage();
}

CXDlgProjectProperties::~CXDlgProjectProperties()
{

}

void CXDlgProjectProperties::slotButtonClicked(QAbstractButton* pButton)
{
	if (m_ui.m_buttonBox->standardButton(pButton) == QDialogButtonBox::Apply)
	{
		m_pPageMisc->Apply();
	}

	if (m_ui.m_buttonBox->standardButton(pButton) == QDialogButtonBox::Ok)
	{
		m_pPageMisc->Apply();
		QDialog::accept();
	}

	if (m_ui.m_buttonBox->standardButton(pButton) == QDialogButtonBox::Cancel)
	{
		QDialog::reject();
	}
}


void CXDlgProjectProperties::_AddMiscPage()
{
	m_pPageMisc = new CXPageProjectProperties(this);
	m_ui.m_tabWidget->addTab(m_pPageMisc, "Misc.");
}