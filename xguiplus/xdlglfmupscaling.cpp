#include "xdlglfmupscaling.h"
#include "xparameterupscaling.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xwell.h"
#include <QMessageBox>
#include "xprocessfactory.h"
#include "xwellcurvealias.h"
#include <QButtonGroup>


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgLFMUpscaling)
ECalculateUpscaling
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgLFMUpscaling)

CXDlgLFMUpscaling::CXDlgLFMUpscaling(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Upscale Well Curve");

	m_pPara = dynamic_cast<CXParameterUpscaling*>(pPara);
	assert(m_pPara);

	_Init();

	m_PBottonGroup = new QButtonGroup(this);
	m_PBottonGroup->addButton(m_ui.m_pRadioAri, CXParameterUpscaling::eArithemtic);
	m_PBottonGroup->addButton(m_ui.m_pRadioGeo, CXParameterUpscaling::eGeometric);
	m_PBottonGroup->addButton(m_ui.m_pRadioRMS, CXParameterUpscaling::eRMS);
	m_PBottonGroup->addButton(m_ui.m_pRadioMedian, CXParameterUpscaling::eMedian);
	m_PBottonGroup->button(m_pPara->GetAverageMethod())->setChecked(true);
}

CXDlgLFMUpscaling::~CXDlgLFMUpscaling()
{
}

void CXDlgLFMUpscaling::_Init()
{
	CXObject* pWellFolderObj = ::GetRootObjectFolder(EXWellFolder, false);
	if (!pWellFolderObj)
		return;

	CXObject* pAliasFolderObj = ::GetRootObjectFolder(EXWellCurveAliasFolder, false);
	if (!pAliasFolderObj)
		return;
	
	QList<CXObject*> listAlias = pAliasFolderObj->GetChildren(EXWellCurveAlias, false);
	if (listAlias.isEmpty())
		return;

	m_ui.m_pListWidget->clear();
	for (int i = 0; i < listAlias.size(); ++i)
	{
		CXWellCurveAlias* pAlias = dynamic_cast<CXWellCurveAlias*>(listAlias[i]);
		if (!pAlias)
			continue;

		QListWidgetItem* pItem = new QListWidgetItem(QIcon(::GetIconPath() + pAlias->GetIconName()), pAlias->GetObjectName());
		pItem->setCheckState(Qt::Unchecked);
		pItem->setData(Qt::UserRole, pAlias->GetObjectID());
		m_ui.m_pListWidget->addItem(pItem);
	}
}

void CXDlgLFMUpscaling::accept()
{
	std::vector<QUuid> vecAliasID;
	for (int i = 0; i < m_ui.m_pListWidget->count(); ++i)
	{
		if (m_ui.m_pListWidget->item(i)->checkState() == Qt::Checked)
		{
			vecAliasID.push_back(QUuid(m_ui.m_pListWidget->item(i)->data(Qt::UserRole).toString()));
		}
	}

	if (vecAliasID.empty())
	{
		QMessageBox::warning(this, ::g_strProductName, "At least one curve alias has to be selected.");
		return;
	}
	else
	{
		m_pPara->SetVecAliasID(vecAliasID);
	}

	// average method
	m_pPara->SetAverageMethod(m_PBottonGroup->checkedId());

	QDialog::accept();
}
