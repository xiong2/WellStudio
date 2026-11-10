#include "xviewinfoobject.h"
#include "xglobal.h"
#include "xobject.h"
#include "xtemplate.h"
#include "xcolormap.h"

CXViewInfoObject::CXViewInfoObject()
{	
	SetBLogScale(false);

	SetColor(QColor("green"));

	SetVisible(false);

	SetColormapName("red_white_dkblue");

	SetBAutoCalcRange(false);
	SetBZeroIsInvalid(false);

	SetNeedColormap(true);
}

CXViewInfoObject::CXViewInfoObject(const CXViewInfoObject& other)
{
	*this = other;
}

CXViewInfoObject& CXViewInfoObject::operator=(const CXViewInfoObject& other)
{
	CXBaseParameter::operator=(other);

	return *this;
}

void CXViewInfoObject::SetViewObjectID(const QUuid& objID)
{
	CXObject *pObj = dynamic_cast<CXObject*>(GetObjectByID(objID));
	if(pObj)
	{
		CXTemplate *pTemplate = CXTemplate::GetTemplate(pObj->GetTemplateID());
		SetBLogScale(pTemplate->UseLogarithmicScale());

		SetColor(pObj->GetColor());
		SetAttributeObjID(pObj->GetObjectID());

		if (pObj->HasHistogram())
		{
			double dMin, dMax;
			pObj->GetDataRange(dMin, dMax);
			SetDisplayDataMin(dMin);
			SetDisplayDataMax(dMax);
		}
	}
	else
	{
		SetBLogScale(false);
	}
}


void CXViewInfoObject::SerializeTemplate(QDataStream& stream, bool bSave)
{
	if(bSave)
	{
		stream<<GetColor();
		stream<<GetVisible();
		stream<<GetBLogScale();
	}
	else
	{
		QColor color;
		stream>>color;
		SetColor(color);

		bool bVisible;		
		stream>>bVisible;
		SetVisible(bVisible);

		bool bLogScale;
		stream>>bLogScale;
		SetBLogScale(bLogScale);
	}
}

bool CXViewInfoObject::ApplyToCurrentViewInfo(const CXViewInfoObject* pOther)
{
	// Colormap

	SetColormapName(pOther->GetColormapName());
	SetBAutoCalcRange(pOther->GetBAutoCalcRange());
	SetBZeroIsInvalid(pOther->GetBZeroIsInvalid());
	SetDisplayDataMin(pOther->GetDisplayDataMin());
	SetDisplayDataMax(pOther->GetDisplayDataMax());

	return true;
}

void CXViewInfoObject::CheckColormapNameValid()
{
	QString colormapName = GetColormapName();
	CXColormap *pColormap = CXColormap::GetColormap(colormapName);
	
	if (!pColormap)
	{
		SetColormapName("probability_smooth");
	}
}