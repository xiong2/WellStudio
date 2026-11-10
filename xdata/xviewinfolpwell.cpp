#include "xviewinfolpwell.h"
#include "xwell.h"

CXViewInfoLPWell::CXViewInfoLPWell(CXObject *pObj)
{
	SetDepthTrackWidth(40);
	SetDepthTrackLeft(true);

	double dSZ = -999.25, dEZ = -999.25;
	if (pObj)
	{
		CXWell *pWell = (CXWell *)pObj;

		pWell->GetDepthRange(dSZ, dEZ);
	}

	SetStartDepth(dSZ);
	SetEndDepth(dEZ);
}

CXViewInfoLPWell::CXViewInfoLPWell(const CXViewInfoLPWell& other)
{
	*this = other;
}

CXViewInfoLPWell& CXViewInfoLPWell::operator=(const CXViewInfoLPWell& other)
{
	CXViewInfoObject::operator=(other);
	return *this;
}

void CXViewInfoLPWell::SerializeTemplate(QDataStream& stream, bool bSave)
{
	CXViewInfoObject::SerializeTemplate(stream, bSave);

	if (bSave)
	{
		stream << GetDepthTrackWidth();
		stream << GetDepthTrackLeft();
		stream << GetStartDepth();
		stream << GetEndDepth();
	}
	else
	{
		double dTmp;
		stream >> dTmp;
		SetDepthTrackWidth(dTmp);

		bool bTmp;
		stream >> bTmp;
		SetDepthTrackLeft(bTmp);

		stream >> dTmp;
		SetStartDepth(dTmp);
		stream >> dTmp;
		SetEndDepth(dTmp);
	}
}
