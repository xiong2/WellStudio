#include "xviewinfoseismicdv.h"
#include "xseismicdatavolume.h"
#include "xglobal.h"
#include "xutility.h"
#include "xseismicsection.h"

CXViewInfoSeismicDV::CXViewInfoSeismicDV()
{
	SetBMUseObjectColor(true);
	SetBMFrameWidth(1);
	SetNeedColormap(false);
}

CXViewInfoSeismicDV::~CXViewInfoSeismicDV()
{

}

void CXViewInfoSeismicDV::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	if (HasFold())
	{
		SetDisplayDataMin(m_histogramFold.m_dDataMin);
		SetDisplayDataMax(m_histogramFold.m_dDataMax);
	}

	SetBMFrameColor(GetColor());
}

void CXViewInfoSeismicDV::CalcFoldHistogram(CXObject* pObjDV)
{
	auto pDV = dynamic_cast<CXSeismicDataVolume*>(pObjDV);

	if (!pDV || !pDV->IsPrestack())
		return;

	const CXSeismicUTMTool& utm = pDV->GetUTM();
	int nI = utm.GetNI();
	int nJ = utm.GetNJ();

	unsigned short* pFoldData = new unsigned short[nI * nJ];
	pDV->GetFoldMap(pFoldData);

	if (!NXUtility::CalcHistogram<unsigned short>(pFoldData, nI * nJ, m_histogramFold))
	{
		CXHistogram defaultHistogram;
		m_histogramFold = defaultHistogram;
	}

	delete[] pFoldData;
}