#include "xdlgnewobject.h"
#include "x3dsurvey.h"
#include <qmessagebox.h>
#include "xglobal.h"
#include "xtree.h"
#include "xgeneralfolder.h"
#include "xfaultsticks.h"
#include "x3dhorizon.h"

CXDlgNewObject::CXDlgNewObject(CX3DSurvey *pSurvey, EXObjectType eType, QWidget *parent)
	: CXBaseDialog(parent)
{
	ui.setupUi(this);
	this->GetMainLayout()->addLayout(ui.gridLayout, 0, 0, 1, 2);

	m_pSurvey = pSurvey;
	m_eObjType = eType;

	_init();
}

CXDlgNewObject::~CXDlgNewObject()
{
}

void CXDlgNewObject::_init()
{
	if (m_eObjType == EXFaultSticks)
	{
		setWindowTitle("Create New Fault");
		ui.label_name->setText("Fault Name:");
		ui.label_color->setText("Fault Color:");
		QString sFaultName = "F";
		CXGeneralFolder *pFaultFolder = (CXGeneralFolder *)(m_pSurvey->GetFolder(EXFaultFolder, false));
		if (pFaultFolder)
			sFaultName = pFaultFolder->GetUnallocatedName(sFaultName);
		ui.lineEdit->setText(sFaultName);
	}
	else if (m_eObjType == EX3DHorizon)
	{
		setWindowTitle("Create New Horizon");
		ui.label_name->setText("Horizon Name:");
		ui.label_color->setText("Horizon Color:");
		QString sFaultName = "Horizon";
		CXGeneralFolder *pFaultFolder = (CXGeneralFolder *)(m_pSurvey->GetFolder(EXHorizonFolder, false));
		if (pFaultFolder)
			sFaultName = pFaultFolder->GetUnallocatedName(sFaultName);
		ui.lineEdit->setText(sFaultName);
	}

	QColor cor = ::GetRandomColor();
	ui.pushButton->SetColor(cor);
}

void CXDlgNewObject::OnOK()
{
	if (ui.lineEdit->text().isEmpty())
	{
		QMessageBox::warning(NULL, "Create New Object", "Please give a name!");
		return;
	}

	if (m_eObjType == EXFaultSticks)
	{
		CXGeneralFolder *pFaultFolder = (CXGeneralFolder *)(m_pSurvey->GetFolder(EXFaultFolder));
		QString sFaultName = ui.lineEdit->text();
		sFaultName = pFaultFolder->GetUnallocatedName(sFaultName);
		CXFaultSticks *pFSticks = new CXFaultSticks(sFaultName, m_pSurvey->GetObjectID());

		pFaultFolder->AddChild(pFSticks);
		::AddObjectEvent(pFSticks);
	}
	else if (m_eObjType == EX3DHorizon)
	{
		CXGeneralFolder *pHorizonFolder = (CXGeneralFolder *)(m_pSurvey->GetFolder(EXHorizonFolder));
		QString strName = ui.lineEdit->text();
		strName = pHorizonFolder->GetUnallocatedName(strName);
		CX3DHorizon*pNewHorizon = new CX3DHorizon(m_pSurvey->GetObjectID(), m_pSurvey->GetUTM(), strName);

		pHorizonFolder->AddChild(pNewHorizon);
		::AddObjectEvent(pNewHorizon);
	}
}