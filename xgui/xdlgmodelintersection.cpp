#include "xdlgmodelintersection.h"
#include "ui_xdlgpropertymodelincision.h"

#include <cassert>

#include "xprocessfactory.h"
#include "xparametermodelintersecion.h"
#include "xglobal.h"
#include "xobject.h"
#include "xproject.h"
#include "xobjecttype.h"
#include "xseismicrandomsection.h"

BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgModelIntersection)
EModelIncision
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgModelIntersection)

CXDlgModelIntersection::CXDlgModelIntersection(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QDialog(parent)
{
	m_pUi = new Ui::CXDlgPropertyModelIncision();
	m_pUi->setupUi(this);
	
	m_pPara = dynamic_cast<CXParameterModelIntersection*>(pPara);
	assert(m_pPara && pParentObj);

	Init();
	InitData();
}

CXDlgModelIntersection::~CXDlgModelIntersection()
{
	delete m_pUi;
}

void CXDlgModelIntersection::Init()
{
	connect(m_pUi->m_pBtnBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(m_pUi->m_pBtnBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void CXDlgModelIntersection::InitData()
{
	m_listObj = ::GetProject()->GetChildren(EXRandomSection, true);
	if (m_listObj.empty()) return;

	foreach (CXObject *pChild, m_listObj)
	{
		m_pUi->m_cbbRS->addItem(QIcon(::GetIconPath() + pChild->GetIconName()), pChild->GetObjectName());
	}
}

void CXDlgModelIntersection::accept()
{
	int index = m_pUi->m_cbbRS->currentIndex();
	auto pRS = dynamic_cast<CXSeismicRandomSection*>(m_listObj.at(index));
	if (!pRS) return;

	vector<double> vecXValue, vecYValue;
	pRS->GetXYofTuringPoint(vecXValue, vecYValue);
	if (vecXValue.empty() || vecYValue.empty()) return;

	m_pPara->SetVecX(vecXValue);
	m_pPara->SetVecY(vecYValue);

	QDialog::accept();
}
