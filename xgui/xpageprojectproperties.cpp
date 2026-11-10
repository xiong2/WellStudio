#include "xpageprojectproperties.h"
#include <QtCore/QSettings>
#include "xglobal.h"
#include "xproject.h"
#include <qdebug.h>
#include "xwaitcursor.h"
#include "xdbio.h"

CXPageProjectProperties::CXPageProjectProperties(QWidget *parent)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);

    m_ui.m_bAuto->setCheckState(::GetProject()->IsAutoSave() ? Qt::Checked : Qt::Unchecked);
    m_ui.m_nTime->setValue(::GetProject()->GetSaveInterval());
    m_ui.m_nTime->setEnabled(::GetProject()->IsAutoSave());

	QFont currentFont = ::GetProject()->GetFont();
	m_ui.m_fontComboBox->setCurrentFont(currentFont);
	m_ui.m_editFontSize->setText(QString::number(currentFont.pointSize()));
	m_ui.m_checkBoxBold->setCheckState(currentFont.bold() ? Qt::Checked : Qt::Unchecked);
	m_ui.m_checkBoxItalic->setCheckState(currentFont.italic() ? Qt::Checked : Qt::Unchecked);

	connect(m_ui.m_bAuto, SIGNAL(stateChanged(int)), SLOT(slotEnableAutoSave(int)));
	connect(m_ui.m_btnVacuumDB, SIGNAL(pressed()), SLOT(slotVacuumProjectDataBase()));
}

CXPageProjectProperties::~CXPageProjectProperties()
{

}

void CXPageProjectProperties::Apply()
{
	::GetProject()->EnableAutoSave(m_ui.m_bAuto->checkState());
	::GetProject()->SetSaveInterval(m_ui.m_nTime->value());

	QFont font = m_ui.m_fontComboBox->currentFont();
	font.setPointSize(m_ui.m_editFontSize->text().toInt());
	font.setBold(m_ui.m_checkBoxBold->isChecked());
	font.setItalic(m_ui.m_checkBoxItalic->isChecked());
	::GetProject()->SetFont(font);

	QApplication::setFont(font);
}

void CXPageProjectProperties::slotEnableAutoSave(int state)
{
	m_ui.m_nTime->setEnabled(state);
}

void CXPageProjectProperties::slotVacuumProjectDataBase()
{
	CXWaitCursor cursor;
	::GetDBIO()->Vacuum();
}
