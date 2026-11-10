#include "xwindowinfo3d.h"

CXWindowInfo3D::CXWindowInfo3D()
{
	SetZScale(3.0);
	SetCurrentDV(QUuid());

	QBitArray lightSwitch(LIGHT_NUM, false);
	lightSwitch.setBit(0, true);
	lightSwitch.setBit(1, true);

	SetLightSwitch(lightSwitch);
	SetLightColor({ QColor(Qt::white).rgba(), QColor(Qt::white).rgba(), QColor(Qt::white).rgba(), QColor(Qt::white).rgba() });
	SetLightAmbient({0.5f, 0.5f, 0.5f, 0.5f});
	SetLightDireaction({ -1.f, 1.f, -1.f, 1.f, -1.f, 1.f , 1.f, 1.f, -1.f , -1.f, -1.f, 1.f });
}

CXWindowInfo3D::~CXWindowInfo3D()
{

}

void CXWindowInfo3D::SetLightSwitch(int id, bool bSwitch)
{
	QBitArray lightSwitch = GetLightSwitch();
	lightSwitch.setBit(id, bSwitch);
	SetLightSwitch(lightSwitch);
}

void CXWindowInfo3D::SetLightAmbient(int id, float fAmbient)
{
	std::vector<float> listAmbient = GetLightAmbient();
	listAmbient[id] = fAmbient;
	SetLightAmbient(listAmbient);
}

void CXWindowInfo3D::SetLightColor(int id, uint rgb)
{
	std::vector<uint> listColor = GetLightColor();
	listColor[id] = rgb;
	SetLightColor(listColor);
}

void CXWindowInfo3D::SetLightDireaction(int id, float fX, float fY, float fZ)
{
	std::vector<float> listDireaction = GetLightDireaction();
	listDireaction[id * 3] = fX;
	listDireaction[id * 3 + 1] = fY;
	listDireaction[id * 3 + 2] = fZ;
	SetLightDireaction(listDireaction);
}
