#pragma warning (push, 0)
#include "xparapageavocssinversion.h"
#include "xprocessfactory.h"
#include "xseismicdatavolume.h"
#include "xparameter3terminversion.h"
#include <cassert>
#include "xglobal.h"

#pragma warning pop

BEGIN_REGISTER_PROCESS_WIDGET_TO_FACTORY(CXParaPageAVOCSSInversion)
EAVOSSInversion
END_REGISTER_RPOCESS_WIDGET_TO_FACTORY(CXParaPageAVOCSSInversion)

CXParaPageAVOCSSInversion::CXParaPageAVOCSSInversion(CXBaseParameter* pPara, CXObject* pParentObj, QWidget* parent)
	:QWidget(parent)
{
	m_pPara = dynamic_cast<CXParameter3TermInversion*>(pPara);
	m_pObject = pParentObj;
	assert(m_pPara && m_pObject);

	m_ui.setupUi(this);

	_Init();

}

CXParaPageAVOCSSInversion::~CXParaPageAVOCSSInversion()
{

}

void CXParaPageAVOCSSInversion::_Init()
{
	// parameters
	m_ui.m_pLineEdtTol->setText(QString::number(m_pPara->GetTolerance(), 'g', 6));
	m_ui.m_pLineEdtMaxLoopNum->setText(QString::number(m_pPara->GetMaxLoopNum()));

	m_ui.m_pLineEdtLamda->setText(QString::number(m_pPara->GetLambda(), 'f', 2));
	m_ui.m_pLineEdtBeta->setText(QString::number(m_pPara->GetBeta(), 'f', 2));
	m_ui.m_pLineEdtSigma->setText(QString::number(m_pPara->GetSigma(), 'f', 2));
	m_ui.m_pLineEdtAlpha->setText(QString::number(m_pPara->GetAlpha(), 'f', 2));
	m_ui.m_pLineEdtGamma->setText(QString::number(m_pPara->GetGamma(), 'f', 2));

	// frequency
	m_ui.m_pLineEdtLowCut->setText(QString::number(m_pPara->GetLowCut(), 'f', 2));
	m_ui.m_pLineEdtLowOverlap->setText(QString::number(m_pPara->GetLowOverlap(), 'f', 2));
	m_ui.m_pLineEdtHighCut->setText(QString::number(m_pPara->GetHighCut(), 'f', 2));
	m_ui.m_pLineEdtHighOverlap->setText(QString::number(m_pPara->GetHighOverlap(), 'f', 2));

	// model
	CXObject* pZp = ::GetObjectByID(m_pPara->GetZpID());
	if (pZp)
		m_ui.m_pLineEdtZp->setText(pZp->GetObjectName());

	CXObject* pZs = ::GetObjectByID(m_pPara->GetZsID());
	if (pZs)
		m_ui.m_pLineEdtZs->setText(pZp->GetObjectName());

	CXObject* pRho = ::GetObjectByID(m_pPara->GetRhoID());
	if (pRho)
		m_ui.m_pLineEdtRho->setText(pRho->GetObjectName());

	// seismic
	std::vector<float> vecAngel = m_pPara->GetVecAngleValue();
	std::vector<QUuid> vecID = m_pPara->GetVecDVID();
	QStringList listWavelet = m_pPara->GetListWaveletFileName();

	m_ui.m_pTable->setRowCount(listWavelet.size());

	for (int i = 0; i < listWavelet.size(); ++i)
	{
		// dv
		CXObject* pDV = ::GetObjectByID(vecID[i]);
		if (pDV)
		{
			QTableWidgetItem* pDVItem = new QTableWidgetItem;
			pDVItem->setText(pDV->GetObjectName());
			pDVItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			m_ui.m_pTable->setItem(i, 0, pDVItem);
		}

		// angle
		QTableWidgetItem* pAngleItem = new QTableWidgetItem;
		pAngleItem->setText(QString::number(vecAngel[i], 'f', 2));
		pAngleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 1, pAngleItem);

		// wavelet
		QTableWidgetItem* pWaveletItem = new QTableWidgetItem;
		pWaveletItem->setText(listWavelet.at(i));
		pWaveletItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 2, pWaveletItem);
	}
}
