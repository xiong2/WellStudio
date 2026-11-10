#include "xwellcurvealias.h"
#include "xglobal.h"
#include "xobjectfactory.h"
#include "xtemplate.h"
#include "xwellcurve.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellCurveAlias)
EXWellCurveAlias
END_REGISTER_OBJECT_TO_FACTORY(CXWellCurveAlias)


CXWellCurveAlias::CXWellCurveAlias(QString sName): CXObject(sName)
{
	this->SetObjectType(EXWellCurveAlias);
}

void CXWellCurveAlias::GetAssociatedCurves(QList<CXObject *>& listCurves)
{
	QUuid aliasID = GetObjectID();

	CXObject *pWells = GetParent()->GetParent();
	QList<CXObject *> pListWells = pWells->GetChildren(EXWell);

	foreach(CXObject *pWell, pListWells)
	{
		QList<CXObject *> pListCurve = pWell->GetChildren(EXWellCurve);
		foreach(CXObject *pChild, pListCurve)
		{
			CXWellCurve *pCurve = dynamic_cast<CXWellCurve *>(pChild);
			if(pCurve && pCurve->GetAliasID() == aliasID)
			{
				listCurves << pCurve;
			}
		}
	}
}

CXObject* CXWellCurveAlias::GetAlias(QString sAliasName)
{
	//	Find the alias folder frist.
	CXObject *pAliasFolder = ::GetRootObjectFolder(EXWellCurveAliasFolder);

	CXObject *pAlias = pAliasFolder->GetChild(sAliasName);

	//	Create one if not found.
	if(!pAlias)
	{
		pAlias = new CXWellCurveAlias(sAliasName);
		pAliasFolder->AddChild(pAlias);
	}

	return pAlias;
}

QString CXWellCurveAlias::GetIconName() const
{
	CXTemplate *pTemplate = CXTemplate::GetTemplate(GetTemplateID());
	if(pTemplate)
		return pTemplate->GetIcon();
	else
		return CXObject::GetIconName();
}

void CXWellCurveAlias::_SetSelfDimension()
{
	QList<CXObject *> listCurves;
	GetAssociatedCurves(listCurves);
	if (listCurves.isEmpty())
		return;

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	int i = 0;
	while (i < listCurves.size())
	{
		if (listCurves[i]->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax))
			break;
		else
			++i;
	}

	if (i >= listCurves.size())
		return;

	double xMin, xMax, yMin, yMax, zMin, zMax;
	for (int j = i + 1; j < listCurves.size(); ++j)
	{
		if (listCurves[i]->GetDimension(xMin, xMax, yMin, yMax, zMin, zMax))
		{
			dXMin = qMin(dXMin, xMin);
			dYMin = qMin(dYMin, yMin);
			dZMin = qMin(dZMin, zMin);

			dXMax = qMax(dXMax, xMax);
			dYMax = qMax(dYMax, yMax);
			dZMax = qMax(dZMax, zMax);
		}
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}