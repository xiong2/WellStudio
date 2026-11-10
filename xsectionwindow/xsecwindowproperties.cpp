#include "xsecwindowproperties.h"
#include "xwindowinfosection.h"
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <QGridLayout>
#include <QDialogButtonBox>
#include "x2dsectionwindow.h"
#include "xsectionscene.h"

CXSecWindowProperties::CXSecWindowProperties(QWidget *parent, CXWindowInfoSection*pViewInfo) :QDialog(parent)
{
	m_UI.setupUi(this);
	QGridLayout *pMainLayout = new QGridLayout(this);
	pMainLayout->addLayout(m_UI.gridLayout,0,0);
	m_pWindowViewInfo = pViewInfo;
	this->setAttribute(Qt::WA_DeleteOnClose);
	_InitUI();
	m_UI.buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
	QObject::connect(m_UI.buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(OnApply()));
	QObject::connect(m_UI.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	this->setWindowTitle("Properties for" + parent->windowTitle());
}


CXSecWindowProperties::~CXSecWindowProperties(void)
{
}

void CXSecWindowProperties:: _InitUI()
{
	connect(m_UI.m_pCmbContent,SIGNAL(currentIndexChanged ( int )),this,SLOT(slotContensChanged(int)));
	QStringList listContens;
	listContens<<"2D Section"<<"Random Section";
	m_UI.m_pCmbContent->addItems(listContens);
	for(int i = 0 ; i < m_UI.m_pLstHorAnn->count(); ++i)
	{
		QListWidgetItem *pItem = m_UI.m_pLstHorAnn->item(i);
		if (m_pWindowViewInfo->GetShowContents().contains(pItem->text()))
		{
			pItem->setCheckState(Qt::Checked);
		}
		else
		{
			pItem->setCheckState(Qt::Unchecked);
		}
	}

	m_UI.m_pHorAnnColor->SetColor(m_pWindowViewInfo->GetHorAnnColor());
	m_UI.m_pSpbHorSize->setValue(m_pWindowViewInfo->GetHorAnnSize());
	m_UI.m_pRdoHorAuto->setChecked(m_pWindowViewInfo->GetHorAuto());
	m_UI.m_pRdoHorManual->setChecked(!m_pWindowViewInfo->GetHorAuto());
	m_UI.m_pHorFont->setCurrentIndex(m_UI.m_pHorFont->findText(m_pWindowViewInfo->GetHorAnnFont()));
	m_UI.m_pEdtHorInc->setText(QString::number(m_pWindowViewInfo->GetHorIncTraces()));
	m_UI.m_pEdtIncOfMinor->setText(QString::number(m_pWindowViewInfo->GetHorIncofMinor()));
	m_UI.m_pSpinHorMargin->setValue(m_pWindowViewInfo->GetHorAxisMargin());

	m_UI.m_pVerAnnColor->SetColor(m_pWindowViewInfo->GetVerAnnColor());
	m_UI.m_pSpbVerAnnSize->setValue(m_pWindowViewInfo->GetVerAnnSize());
	m_UI.m_pRdoVerAuto->setChecked(m_pWindowViewInfo->GetVerAuto());
	m_UI.m_pRdoVerManual->setChecked(!m_pWindowViewInfo->GetVerAuto());
	m_UI.m_pVerAnnFont->setCurrentIndex(m_UI.m_pVerAnnFont->findText(m_pWindowViewInfo->GetVerAnnFont()));
	m_UI.m_pEdtVerInc->setText(QString::number(m_pWindowViewInfo->GetVerIncTraces()));
	m_UI.m_pEdtVerIncOfMinor->setText(QString::number(m_pWindowViewInfo->GetVerIncofMinor()));
	m_UI.m_pSpbVerMargin->setValue(m_pWindowViewInfo->GetVerAxisMargin());
	m_UI.m_pChkShowMajorLine->setChecked(m_pWindowViewInfo->GetShowMajorLine());

	m_UI.m_pEdtCliping->setText(QString::number(m_pWindowViewInfo->GetCliping()));
	m_UI.m_pEdtTraceStep->setText(QString::number(m_pWindowViewInfo->GetTraceStep()));
	m_UI.m_pEdtExcursion->setText(QString::number(m_pWindowViewInfo->GetExcursion()));

	//	Scale.
	float fHScale = getDPI(true) / (m_pWindowViewInfo->GetTraceScale() * 2.54);
	float fVScale = getDPI(false) / (m_pWindowViewInfo->GetVerScale() * 2.54);
	m_UI.m_pEdtScale->setText(QString::number(fHScale, 'f', 1));
	m_UI.m_pEdtVerScale->setText(QString::number(fVScale, 'f', 1));

	m_UI.lm_pEdtSearchRadius->setText(QString::number(m_pWindowViewInfo->GetSearchingRadius()));
}

void CXSecWindowProperties:: slotContensChanged(int nIdx)
{
	m_UI.m_pLstHorAnn->clear();
	QStringList lstLabels;
	if (nIdx == 0)
	{
		lstLabels<<"Section Name"<<"CDP"<<"X"<<"Y";
	}else
	{
		lstLabels<<"Section Name"<<"X"<<"Y";
	}
	m_UI.m_pLstHorAnn->addItems(lstLabels);

}

void CXSecWindowProperties::OnApply()
{
	m_pWindowViewInfo->SetHorAnnColor(m_UI.m_pHorAnnColor->GetColor());
	m_pWindowViewInfo->SetHorAnnSize(m_UI.m_pSpbHorSize->value());
	m_pWindowViewInfo->SetHorAuto(m_UI.m_pRdoHorAuto->isChecked());
	m_pWindowViewInfo->SetHorAuto(!m_UI.m_pRdoHorManual->isChecked());
	m_pWindowViewInfo->SetHorAnnFont(m_UI.m_pHorFont->currentText());
	m_pWindowViewInfo->SetHorIncTraces(m_UI.m_pEdtHorInc->text().toInt());
	m_pWindowViewInfo->SetHorIncofMinor(m_UI.m_pEdtIncOfMinor->text().toInt());
	m_pWindowViewInfo->SetHorAxisMargin(m_UI.m_pSpinHorMargin->value());

	m_pWindowViewInfo->SetVerAnnColor(m_UI.m_pVerAnnColor->GetColor());
	m_pWindowViewInfo->SetVerAnnSize(m_UI.m_pSpbVerAnnSize->value());
	m_pWindowViewInfo->SetVerAuto(m_UI.m_pRdoVerAuto->isChecked());
	m_pWindowViewInfo->SetVerAuto(!m_UI.m_pRdoVerManual->isChecked());
	m_pWindowViewInfo->SetVerAnnFont(m_UI.m_pVerAnnFont->currentText());
	m_pWindowViewInfo->SetVerIncTraces(m_UI.m_pEdtVerInc->text().toInt());
	m_pWindowViewInfo->SetVerIncofMinor(m_UI.m_pEdtIncOfMinor->text().toInt());
	m_pWindowViewInfo->SetVerAxisMargin(m_UI.m_pSpbVerMargin->value());
	m_pWindowViewInfo->SetShowMajorLine(m_UI.m_pChkShowMajorLine->isChecked());

	m_pWindowViewInfo->SetCliping(m_UI.m_pEdtCliping->text().toFloat());
	m_pWindowViewInfo->SetTraceStep(m_UI.m_pEdtTraceStep->text().toFloat());
	m_pWindowViewInfo->SetExcursion(m_UI.m_pEdtExcursion->text().toFloat());

	bool bWellSearchingRadiusChanged = false;
	if (m_UI.lm_pEdtSearchRadius->text().toFloat() != m_pWindowViewInfo->GetSearchingRadius())
		bWellSearchingRadiusChanged = true;
	m_pWindowViewInfo->SetSearchingRadius(m_UI.lm_pEdtSearchRadius->text().toFloat());

	//	scale.
	float fHScale = m_UI.m_pEdtScale->text().toFloat();
	fHScale = getDPI(true) / (fHScale * 2.54);
	m_pWindowViewInfo->SetTraceScale(fHScale);
	float fVScale = m_UI.m_pEdtVerScale->text().toFloat();
	fVScale = getDPI(false) / (fVScale * 2.54);
	m_pWindowViewInfo->SetVerScale(fVScale);

	CX2DSectionWindow *pWindow = dynamic_cast<CX2DSectionWindow *>(parent());
	if (pWindow)
	{
		pWindow->ChangeDisplayParameter();

		//	The well searching radius changed need be special processed, since it calls well item data changed.
		if (bWellSearchingRadiusChanged)
		{
			CXSectionScene * pScene = (CXSectionScene *)pWindow->GetScene();
			pScene->UpdateItems(EDataChanged);
		}
	}

	QDialog::accept();
}

float CXSecWindowProperties::getDPI(bool bHorizontal)
{
	QWidget* pDesktop = QApplication::desktop();

	if (bHorizontal)
		return pDesktop->physicalDpiX();
	else
		return pDesktop->physicalDpiY();
}