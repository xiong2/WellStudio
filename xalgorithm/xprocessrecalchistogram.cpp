#include "xprocessrecalchistogram.h"
#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xglobal.h"
#include <cassert>
#include "xbaseconsole.h"
#include "xseismicdatavolume.h"

#include "xgeneralfolder.h"
#include "xparametermanager.h"
#include "xtree.h"
#include "xseismicdatavolume.h"
#include "xalgorithmutility.h"

#include "xproject.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessRecalcHistogram)
ERecalcHistogram
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessRecalcHistogram)


CXProcessRecalcHistogram::CXProcessRecalcHistogram()
{	
}

CXProcessRecalcHistogram::~CXProcessRecalcHistogram()
{
}

void CXProcessRecalcHistogram::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pParentObject = pParentObj;

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	if (!pDV)
		return;

	CXAlgorithmUtility::CalculateHistogram(pDV->GetTraceFileName(), pDV->GetSamplingQty(), pDV);


}

void CXProcessRecalcHistogram::slotFinishedComputing()
{
	m_pParentObject->SetModifiedFlag();

}




