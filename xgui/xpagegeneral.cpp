#include "xpagegeneral.h"
#include "xobject.h"
#include <QTreeWidgetItem>
#include "xwell.h"
#include "xwellcurve.h"
#include "x3dsurvey.h"
#include <cassert>
#include <QDoubleValidator>
#include "xeventconsole.h"
#include "xtemplate.h"
#include "xtree.h"
#include "xtreewidgetitem.h"
#include "x2dseismicline.h"

CXPageGeneral::CXPageGeneral(QWidget *parent,CXObject *pObject)
	: CXBasePropertyPage(parent),m_pObject(pObject)
{
	m_ui.setupUi(this);
		
	connect(m_ui.comboBoxColor, SIGNAL(ColorSelected(const QColor&)), this, SLOT(slotSetColor(QColor)));
	
	initGeneralInfo();
	initDescription();

	_SetSpecificWidget();
}

CXPageGeneral::~CXPageGeneral()
{

}

CXButtonColorEdit* CXPageGeneral::GetObjColorButton()
{
	return m_ui.comboBoxColor;
}

void CXPageGeneral::initGeneralInfo()
{
	m_ui.m_EdtName->setText(m_pObject->GetObjectName());	
	m_ui.lineEditType->setText(m_pObject->GetTypeString());
	m_ui.comboBoxColor->SetColor(m_pObject->GetColor());

	//m_GeneralUi.m_EdtType->setText(m_pObj->GetObjectType());
	double dXMin(0),  dXMax(0),  dYMin(0),  dYMax(0),  dZMin(0),  dZMax(0);
	m_pObject->GetDimension(dXMin,  dXMax,  dYMin,  dYMax,  dZMin,  dZMax);
	m_ui.m_GeneralInfo->setItem(0, 0, new QTableWidgetItem(QString::number(dXMin, 'f', 2)));
	m_ui.m_GeneralInfo->setItem(0, 1, new QTableWidgetItem(QString::number(dXMax, 'f', 2)));
	m_ui.m_GeneralInfo->setItem(0, 2, new QTableWidgetItem(QString::number((dXMax - dXMin), 'f', 2)));
	m_ui.m_GeneralInfo->setItem(1, 0, new QTableWidgetItem(QString::number(dYMin, 'f', 2)));
	m_ui.m_GeneralInfo->setItem(1, 1, new QTableWidgetItem(QString::number(dYMax, 'f', 2)));
	m_ui.m_GeneralInfo->setItem(1, 2, new QTableWidgetItem(QString::number((dYMax - dYMin), 'f', 2)));
	m_ui.m_GeneralInfo->setItem(2, 0, new QTableWidgetItem(QString::number(dZMin, 'f', 2)));
	m_ui.m_GeneralInfo->setItem(2, 1, new QTableWidgetItem(QString::number(dZMax, 'f', 2)));
	m_ui.m_GeneralInfo->setItem(2, 2, new QTableWidgetItem(QString::number((dZMax - dZMin), 'f', 2)));

	for(int nRowIdx = 0; nRowIdx < m_ui.m_GeneralInfo->rowCount(); nRowIdx ++)
	{
		m_ui.m_GeneralInfo->setRowHeight(nRowIdx,20);
	}

}

void CXPageGeneral::_SetSpecificWidget()
{
	m_pCMBTemplate = NULL;
	m_ui.m_pLineEdtKB->setVisible(false);
	m_ui.m_pLabelDatum->setVisible(false);
	m_ui.m_pLineEdtDatum->setVisible(false);
	m_ui.m_pLabelRepVel->setVisible(false);
	m_ui.m_pLineEdtRepVel->setVisible(false);
	m_ui.m_pLabelKB->setVisible(false);
	m_ui.label_XOffset->setVisible(false);
	m_ui.label_YOffset->setVisible(false);
	m_ui.lineEdit_XOffset->setVisible(false);
	m_ui.lineEdit_YOffset->setVisible(false);

	if (m_pObject->GetObjectType() == EXWell)
	{
		m_ui.m_pLabelKB->setVisible(true);
		m_ui.m_pLabelKB->setText("KB");
		m_ui.m_pLineEdtKB->setVisible(true);

		CXWell* pWell = dynamic_cast<CXWell*>(m_pObject);
		assert(pWell);

		m_ui.m_pLineEdtKB->setValidator(new QDoubleValidator(this));
		m_ui.m_pLineEdtKB->setText(QString::number(pWell->GetKB(), 'f', 2));
	}
	else if (m_pObject->GetObjectType() == EXWellCurve)
	{
		m_ui.m_pLabelKB->setVisible(true);
		m_ui.m_pLabelKB->setText("Template");

		m_pCMBTemplate = new QComboBox();
		m_ui.gridLayout->replaceWidget(m_ui.m_pLineEdtKB, m_pCMBTemplate);

		m_pCMBTemplate->addItems(CXTemplate::GetAllTemplates());
		int iIDX = m_pCMBTemplate->findText(CXTemplate::GetTemplateName(m_pObject->GetTemplateID()));
		m_pCMBTemplate->setCurrentIndex(iIDX);
	}
	else if (m_pObject->GetObjectType() == EX3DSurvey)
	{
		m_ui.m_pLabelDatum->setVisible(true);
		m_ui.m_pLineEdtDatum->setVisible(true);
		m_ui.m_pLabelRepVel->setVisible(true);
		m_ui.m_pLineEdtRepVel->setVisible(true);

		CX3DSurvey* pSurvey = dynamic_cast<CX3DSurvey*>(m_pObject);
		assert(pSurvey);

		double dDatum, dRepVel;
		pSurvey->GetDatumAndRepVelocity(dDatum, dRepVel);

		m_ui.m_pLineEdtDatum->setValidator(new QDoubleValidator(this));
		m_ui.m_pLineEdtRepVel->setValidator(new QDoubleValidator(this));

		m_ui.m_pLineEdtDatum->setText(QString::number(dDatum, 'f', 2));
		m_ui.m_pLineEdtRepVel->setText(QString::number(dRepVel, 'f', 2));
	}
	else if (m_pObject->GetObjectType() == EX2DSeismicLine)
	{
#ifdef QT_DEBUG
		m_ui.label_XOffset->setVisible(true);
		m_ui.label_YOffset->setVisible(true);
		m_ui.lineEdit_XOffset->setVisible(true);
		m_ui.lineEdit_YOffset->setVisible(true);

		auto p2DLine = dynamic_cast<CX2DSeismicLine*>(m_pObject);
		Q_ASSERT(p2DLine);

		auto dOffset = p2DLine->GetOffset();
		m_ui.lineEdit_XOffset->setText(QString::number(dOffset.first, 'f', 2));
		m_ui.lineEdit_YOffset->setText(QString::number(dOffset.second, 'f', 2));
#endif
	}
}

void CXPageGeneral::initDescription()
{
	QStringList sListDesp = m_pObject->GetDescription();
	int i, iNumRow = sListDesp.size() / 2;
	m_ui.tableWidget->setRowCount(iNumRow);
	for(int nRowIdx = 0; nRowIdx < m_ui.tableWidget->rowCount(); nRowIdx ++)
	{
		m_ui.tableWidget->setRowHeight(nRowIdx,20);
	}
	for(i = 0; i < iNumRow; i++)
	{
		m_ui.tableWidget->setItem(i, 0, new QTableWidgetItem(sListDesp[2 * i]));
		m_ui.tableWidget->setItem(i, 1, new QTableWidgetItem(sListDesp[2 * i + 1]));
	}
}

void CXPageGeneral::slotSetColor(QColor color)
{
	if (m_pObject != NULL)
	{
		m_pObject->SetColor(color);
		m_pObject->SetModifiedFlag();
	}
		
}

void CXPageGeneral::Apply()
{
	if (m_pObject->GetObjectType() == EXWell)
	{
		CXWell* pWell = dynamic_cast<CXWell*>(m_pObject);
		assert(pWell);

		double dKB = m_ui.m_pLineEdtKB->text().toDouble();
		if (dKB != pWell->GetKB())
		{
			pWell->SetKB(dKB);
			pWell->AddEvent(EDataChanged);
			CXProcessEvent eventProcess;
		}
	}
	else if (m_pObject->GetObjectType() == EX3DSurvey)
	{
		CX3DSurvey* pSurvey = dynamic_cast<CX3DSurvey*>(m_pObject);
		assert(pSurvey);

		double dDatum, dRepVel;
		pSurvey->GetDatumAndRepVelocity(dDatum, dRepVel);

		double dDatumNew = m_ui.m_pLineEdtDatum->text().toDouble();
		double dRepVelNew = m_ui.m_pLineEdtRepVel->text().toDouble();

		if (dDatum != dDatumNew || dRepVel != dRepVelNew)
		{
			pSurvey->SetDatum(dDatumNew);
			pSurvey->SetRepVelocity(dRepVelNew);
			pSurvey->AddEvent(EDataChanged);
			CXProcessEvent eventProcess;
		}
	}
	else if (m_pObject->GetObjectType() == EXWellCurve)
	{
		CXWellCurve *pWCurve = (CXWellCurve *)m_pObject;
		CXTemplate *pTemplate = CXTemplate::GetTemplate(m_pCMBTemplate->currentText());
		CXObject *pAlias = ::GetObjectByID(pWCurve->GetAliasID());
		if (pAlias)
		{
			pAlias->SetTemplateID(pTemplate->GetID());
		}
		else
		{
			pWCurve->SetTemplateID(pTemplate->GetID());
		}

		CXTree::Instance().GetTreeItemFromID(pWCurve->GetObjectID())->setIcon(0, QIcon(::GetIconPath() + pWCurve->GetIconName()));
	}
	else if (m_pObject->GetObjectType() == EX2DSeismicLine)
	{
#ifdef QT_DEBUG
		auto p2DLine = dynamic_cast<CX2DSeismicLine*>(m_pObject);
		p2DLine->SetOffset(m_ui.lineEdit_XOffset->text().toDouble(), m_ui.lineEdit_YOffset->text().toDouble());
#endif
	}
}