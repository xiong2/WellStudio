#include "xdlgextracthorizonatt.h"
#include "xparameterextracthorizonatt.h"
#include "x3dhorizon.h"
#include "x3dsurvey.h"
#include "xseismicdatavolume.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include <QMessageBox>
#include "xprocessfactory.h"
#include <QDoubleValidator>


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgExtractHorizonAtt)
EExtractHorizonAttribute
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgExtractHorizonAtt)

CXDlgExtractHorizonAtt::CXDlgExtractHorizonAtt(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	m_pPara = dynamic_cast<CXParameterExtractHorizonAtt*>(pPara);

	m_p3DHorizon = dynamic_cast<CX3DHorizon*>(pParentObj);
	assert(m_p3DHorizon);
	m_pPara->SetHorizonID(m_p3DHorizon->GetObjectID());

	// two buttons
	QPixmap pixAdd, pixRemove;
	pixAdd.load(::GetIconPath() + "18804.png");
	pixRemove.load(::GetIconPath() + "Delete.png");
	m_ui.m_pBtnAdd->setIcon(QIcon(pixAdd));
	m_ui.m_pBtnRemove->setIcon(QIcon(pixRemove));

	//	Connections
	connect(m_ui.m_pBtnAdd, SIGNAL(clicked()), this, SLOT(slotAddDV()));
	connect(m_ui.m_pBtnRemove, SIGNAL(clicked()), this, SLOT(slotRemoveDV()));

	connect(m_ui.m_pCombMethod, SIGNAL(currentIndexChanged(int)), this, SLOT(slotMethodChange(int)));

	_Init();
}

CXDlgExtractHorizonAtt::~CXDlgExtractHorizonAtt()
{

}

void CXDlgExtractHorizonAtt::_Init()
{
	m_ui.m_pLineTopShift->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineBotShift->setValidator(new QDoubleValidator(this));

	m_ui.m_pLineTopShift->setText(QString::number(0));
	m_ui.m_pLineBotShift->setText(QString::number(0));
}

void CXDlgExtractHorizonAtt::slotMethodChange(int iIndex)
{
	m_pPara->SetMethodType(iIndex);
	if (iIndex == 0)
	{
		// instant
		m_ui.m_pLineTopShift->setText(QString::number(0));
		m_ui.m_pLineBotShift->setText(QString::number(0));
	}
	else
	{
		m_ui.m_pLineTopShift->setText(QString::number(-10));
		m_ui.m_pLineBotShift->setText(QString::number(10));
	}
}


void CXDlgExtractHorizonAtt::slotAddDV()
{
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pDV)
		return;

	if (pDV->IsPrestack())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select one poststack seismic data volume.");
		return;
	}

	if (pDV->GetSurveyID() != m_p3DHorizon->GetSurveyID())
	{
		QMessageBox::warning(this, ::g_strProductName, "The selected data volume must belong to the same survey with the horizon.");
		return;
	}

	//	Update the list view
	QListWidgetItem* pItem = new QListWidgetItem(QIcon(::GetIconPath() + pDV->GetIconName()), pDV->GetObjectName());
	pItem->setData(Qt::UserRole, pDV->GetObjectID().toString());
	m_ui.m_pListDV->addItem(pItem);
}

void CXDlgExtractHorizonAtt::slotRemoveDV()
{
	//	Remove the selected horizon.
	int currentRow = m_ui.m_pListDV->currentRow();
	if (currentRow < 0 || currentRow >= m_ui.m_pListDV->count())		return;


	QListWidgetItem* pWidgetItem = m_ui.m_pListDV->takeItem(currentRow);
	delete pWidgetItem;
}


void CXDlgExtractHorizonAtt::accept()
{
	// DVs
	std::vector<QUuid> vecDVID;
	for (int i = 0; i < m_ui.m_pListDV->count(); ++i)
	{
		vecDVID.push_back(m_ui.m_pListDV->item(i)->data(Qt::UserRole).toString());
	}
	if (vecDVID.empty())
	{
		QMessageBox::warning(this, ::g_strProductName, "At least select one data volume.");
		return;
	}

	m_pPara->SetVecDVID(vecDVID);
	m_pPara->SetMethodType(m_ui.m_pCombMethod->currentIndex());

	m_pPara->SetTopShift(m_ui.m_pLineTopShift->text().toFloat());
	m_pPara->SetBottomShift(m_ui.m_pLineBotShift->text().toFloat());

	QDialog::accept();
}
