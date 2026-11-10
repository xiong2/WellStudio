#pragma warning (push, 0)
#include "xparameterbuildlfm.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"
#include "xglobal.h"
#include "xobject.h"
#include "xproject.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterBuildLFM)
EBuildLowFreuqencyModel
END_REGISTER_OBJECT_TO_FACTORY(CXParameterBuildLFM)

CXParameterBuildLFM::CXParameterBuildLFM()
{
	SetLFMName("Low Frequency Model");

	SetSurveyID(0);

	SetTopShift(0.0f);
	SetBottomShift(0.0f);

	SetPolygonID(0);

	SetLFMName("LFM-");
}

void CXParameterBuildLFM::Initialize()
{
	std::vector<QUuid> vecHorizonID = GetVecHorizonID();
	if (vecHorizonID.empty())
		return;
	else
	{
		QStringList strHorizonNameList;
		QStringList strZoneNameList;
		std::vector<int> vecContactType;
		std::vector<int> vecSliceNum;
		std::vector<float> vecThickness;

		float fThickness = 10.f;

		if (vecHorizonID.size() == 1)
		{
			CXObject* pObj = ::GetObjectByID(vecHorizonID.front());
			strHorizonNameList << pObj->GetObjectName();
			QString strName = pObj->GetObjectName();
			strZoneNameList << strName;
			vecContactType.push_back(eProportional);
			vecSliceNum.push_back(10);

			vecThickness.push_back(fThickness);
		}
		else
		{
			for (int i = 0; i < vecHorizonID.size() - 1; ++i)
			{
				CXObject* pTopObj = ::GetObjectByID(vecHorizonID.at(i));
				CXObject* pBottomObj = ::GetObjectByID(vecHorizonID.at(i + 1));
				strHorizonNameList << pTopObj->GetObjectName();
				if (i == vecHorizonID.size() - 2)
					strHorizonNameList << pBottomObj->GetObjectName();

				QString strName = pTopObj->GetObjectName();
				strZoneNameList << strName;
				vecContactType.push_back(eProportional);
				vecSliceNum.push_back(10);

				vecThickness.push_back(fThickness);
			}
		}

		this->SetHorizonNameList(strHorizonNameList);
		this->SetZoneNameList(strZoneNameList);
		this->SetVecContactType(vecContactType);
		this->SetVecSliceNum(vecSliceNum);
		this->SetVecThickness(vecThickness);
	}
}

QString CXParameterBuildLFM::GetContactName(int nContactType)
{
	EContactType eType = static_cast<EContactType>(nContactType);
	QString strName;
	switch (eType)
	{
	case eProportional:
		strName = "Proportional";
		break;
	case eTopConformable:
		strName = "Top Conformable";
		break;
	case eBottomConformable:
		strName = "Bottom Conformable";
		break;
		break;
	default:
		break;
	}
	return strName;
}
