#include "stdafx.h"
#include <qmessagebox.h>
#include "xutmtool.h"
#include "xglobal.h"
#include "xtree.h"
#include "gsdlgrosediagram.h"
#include "gsstressmap.h"
#include "xproject.h"
#include "xwell.h"
#include "gsbmitemdefinerose.h"
#include "gsbasemapscene.h"
#include "gsrosediagram.h"
#include "gstreenodecreator.h"
#include "x3dsurvey.h"

gsdlgrosediagram::gsdlgrosediagram(GSStressMap *pMap, GSBMItemDefineRose *pItem, QWidget *parent)
	: QDialog(parent)
{
	m_pItem = pItem;
	m_pMap = pMap;
	ui.setupUi(this);

	ui.lineEdit->setText(m_pMap->GetUnallocatedName("Rose diagram"));

	//	Populate radius spinbox.
	int iStep = (int)(m_pMap->GetUTM().GetIInterval());
	ui.spinBoxRadius->setMinimum(2 * iStep);
	ui.spinBoxRadius->setMaximum(40 * iStep);
	ui.spinBoxRadius->setValue(10 * iStep);
	ui.spinBoxRadius->setSingleStep(2 * iStep);

	//	Populate well candidates.
	QStringList sListWells;
	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	m_pMap->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	QList<CXObject *> listWells = GetProject()->GetChildren(EXWell, true);
	foreach(CXObject *pObj, listWells)
	{
		double dX, dY;
		CXWell *pWell = (CXWell *)pObj;
		pWell->GetWellPosition(dX, dY);

		if (dX < dXMin || dX > dXMax || dY < dYMin || dY > dYMax)
			continue;

		sListWells << pWell->GetObjectName();
	}
	if (sListWells.empty())
	{
		ui.radioButtonWell->setDisabled(true);
	}
	else
	{
		ui.comboBoxWells->addItems(sListWells);
	}

	connect(ui.spinBoxRadius, SIGNAL(valueChanged(int)), this, SLOT(slotChangeRadius(int)));
	connect(ui.radioButtonWell, SIGNAL(clicked()), this, SLOT(slotUseWell()));
	connect(ui.radioButtonClick, SIGNAL(clicked()), this, SLOT(slotUseWell()));
	connect(ui.comboBoxWells, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotSelectWell(const QString &)));
}

gsdlgrosediagram::~gsdlgrosediagram()
{

}

void gsdlgrosediagram::accept()
{
	GSBasemapScene *pScene = dynamic_cast<GSBasemapScene *>(m_pItem->scene());
	if(!pScene)
		return;

	QString sName = ui.lineEdit->text();
	sName = m_pMap->GetUnallocatedName(sName);

	//	Now create the new rose diagram!
	if (m_pItem->GetMode() == 0)
	{
		//	Circle.
		QPointF centre = m_pItem->GetCentre();
		if (centre.x() <= 0.)
		{
			QMessageBox::warning(NULL, "Create Rose Diagram", "Please click on the map to define the rose range!");
			return;
		}

		double dRadius = m_pItem->GetRadius();
		GSRoseDiagram *pRose = new GSRoseDiagram(sName, centre, dRadius);

		CXSeismicUTMTool utm = m_pMap->GetUTM();
		int nI = utm.GetNI(), nJ = utm.GetNJ();
		QVector<float>& vecData = pRose->GetVecData();
		float *pData = m_pMap->GetData();

		int i, j, i1, j1, i2, j2, i3, j3, sI, eI, sJ, eJ;
		double dXMin = centre.x() - dRadius;
		double dXMax = centre.x() + dRadius;
		double dYMin = centre.y() - dRadius;
		double dYMax = centre.y() + dRadius;
		utm.XYToIJ(dXMin, dYMin, sI, sJ);
		utm.XYToIJ(dXMin, dYMax, i1, j1);
		utm.XYToIJ(dXMax, dYMax, i2, j2);
		utm.XYToIJ(dXMax, dYMin, i3, j3);
		eI = sI;
		eJ = sJ;
		sI = sI < i1 ? sI : i1;
		sI = sI < i2 ? sI : i2;
		sI = sI < i3 ? sI : i3;
		sI = sI < 0 ? 0 : sI;
		sJ = sJ < j1 ? sJ : j1;
		sJ = sJ < j2 ? sJ : j2;
		sJ = sJ < j3 ? sJ : j3;
		sJ = sJ < 0 ? 0 : sJ;
		eI = eI > i1 ? eI : i1;
		eI = eI > i2 ? eI : i2;
		eI = eI > i3 ? eI : i3;
		eI = eI > nI - 1 ? nI - 1 : eI;
		eJ = eJ > j1 ? eJ : j1;
		eJ = eJ > j2 ? eJ : j2;
		eJ = eJ > j3 ? eJ : j3;
		eJ = eJ > nJ - 1 ? nJ - 1 : eJ;

		float fI, fJ;
		utm.XYToIJ(centre.x(), centre.y(), fI, fJ);
		int delta = (int)((fI - sI) * (fI - sI));

		for (i = sI; i <= eI; i++)
		{
			for (j = sJ; j <= eJ; j++)
			{
				if((i - fI) * (i - fI) + (j - fJ) * (j - fJ) > delta)
					continue;

				vecData << pData[nI * nJ + i * nJ + j];
			}
		}

		if (vecData.isEmpty())
		{
			delete pRose;

			QMessageBox::warning(NULL, "Create Rose Diagram", "No valid data, please define the range again!");
			return;
		}

		m_pMap->AddChild(pRose);
		CXTree::Instance().AddOneObject(m_pMap);

		emit pScene->ShowThisObj(pRose->GetObjectID());
	}

	pScene->RemoveDefineRoseItem();
	
	QDialog::accept();
}

void gsdlgrosediagram::reject()
{
	GSBasemapScene *pScene = dynamic_cast<GSBasemapScene *>(m_pItem->scene());
	if(!pScene)
		return;

	pScene->removeItem(m_pItem);
	delete m_pItem;

	pScene->SetMode(GSBasemapScene::eNone);
		
	QDialog::reject();
}

void gsdlgrosediagram::slotChangeRadius(int iValue)
{
	m_pItem->SetRadius(ui.spinBoxRadius->text().toDouble());
}

void gsdlgrosediagram::slotUseWell()
{
	if (ui.radioButtonClick->isChecked())
	{
		ui.comboBoxWells->setDisabled(true);
	}
	else
	{
		ui.comboBoxWells->setDisabled(false);

		slotSelectWell(ui.comboBoxWells->currentText());
	}
}

void gsdlgrosediagram::slotSelectWell(const QString &sWellName)
{
	QList<CXObject *> listWells = GetProject()->GetChildren(EXWell, true);
	foreach(CXObject *pObj, listWells)
	{
		if(pObj->GetObjectName() != sWellName)
			continue;

		double dX, dY;
		CXWell *pWell = (CXWell *)pObj;
		pWell->GetWellPosition(dX, dY);

		m_pItem->SetCentre(QPointF(dX, dY));
		ui.lineEdit->setText(pWell->GetObjectName());
	}
}