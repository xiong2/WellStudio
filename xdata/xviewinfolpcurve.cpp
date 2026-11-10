#include "xviewinfolpcurve.h"
#include "xtemplate.h"
#include "xwellcurve.h"
#include "xautogrid.h"

CXViewInfoLPCurve::CXViewInfoLPCurve(CXObject *pObj)
{
	SetLineWidth(2);
	SetLineStyle(1);		
	SetFillFrom(-999.25);
	SetFFColor(GetColor());
	SetFFPattern(0);
	SetFillTo(-999.25);
	SetFTColor(GetColor());
	SetFTPattern(0);

	if (pObj)
	{
		CXWellCurve *pCurve = (CXWellCurve *)pObj;
		CXTemplate *pTemplate = CXTemplate::GetTemplate(pCurve->GetTemplateID());
		double dMin, dMax;
		pTemplate->GetDisplayRange(dMin, dMax);

		if (dMin == -999.25)
		{
			bool bLog = pTemplate->UseLogarithmicScale();
			double dDMin, dDMax, dStep;
			pCurve->GetDataRange(dDMin, dDMax);
			CXAutoGrid::AutoGrid(dDMin, dDMax, 10, dMin, dMax, dStep, bLog);
		}
		SetDisplayDataMin(dMin);
		SetDisplayDataMax(dMax);
	}
}

CXViewInfoLPCurve::CXViewInfoLPCurve(const CXViewInfoLPCurve& other)
{
	*this = other;
}

CXViewInfoLPCurve& CXViewInfoLPCurve::operator=(const CXViewInfoLPCurve& other)
{
    CXViewInfoObject::operator=(other);
	return *this;
}

void CXViewInfoLPCurve::SerializeTemplate(QDataStream& stream, bool bSave)
{
    CXViewInfoObject::SerializeTemplate(stream, bSave);

	if(bSave)
	{
		stream<<GetLineWidth();
		stream<<GetLineStyle();
		stream << GetFillFrom();
		stream << GetFFColor();
		stream << GetFFPattern();
		stream << GetFillTo();
		stream << GetFTColor();
		stream << GetFTPattern();
	}
	else
	{
		int iTmp;
		stream>>iTmp;
		SetLineWidth(iTmp);

		stream>>iTmp;
		SetLineStyle(iTmp);

		qreal dTmp;
		stream >> dTmp;
		SetFillFrom(dTmp);
		QColor color;
		stream >> color;
		SetFFColor(color);
		stream >> iTmp;
		SetFFPattern(iTmp);

		stream >> dTmp;
		SetFillTo(dTmp);
		stream >> color;
		SetFTColor(color);
		stream >> iTmp;
		SetFTPattern(iTmp);
	}
}