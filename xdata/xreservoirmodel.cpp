#include "xreservoirmodel.h"
#include "xgridmodel.h"
#include "xobjectfactory.h"
#include "xglobal.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXReservoirModel)
EXReservoirModel
END_REGISTER_OBJECT_TO_FACTORY(CXReservoirModel)

CXReservoirModel::CXReservoirModel(CXGridModel *pGridModel, QString strName): CXObject(strName)
{
	SetObjectType(EXReservoirModel);
	SetIconName("ReservoirModel.png");

	AddChild(pGridModel);

	if(strName == "")
		SetObjectName(pGridModel->GetObjectName());
}

CXGridModel* CXReservoirModel::GetGridModel()
{
	return (CXGridModel *)GetChildren(EXGridModel).at(0);
}

QStringList CXReservoirModel::GetDescription()
{
	QStringList strListDesc = GetChildren(EXGridModel).at(0)->GetDescription();

	strListDesc<<GetTr("属性模型数目")<<QString::number(GetChildren(EXPropertyModel).size());

	return strListDesc;
}

CXObject* CXReservoirModel::GetGeometryObject()
{
	 return GetGridModel();
}