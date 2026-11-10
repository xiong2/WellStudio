#ifndef XWINDOWINFO3D_H
#define XWINDOWINFO3D_H

#include "xwindowinfo.h"
#include "xdata_global.h"

#include <QBitArray>

class XDATA_EXPORT CXWindowInfo3D : public CXWindowInfo
{
public:
	CXWindowInfo3D();
	~CXWindowInfo3D();

	X_PROPERTY(float, ZScale)
	X_PROPERTY(QUuid, CurrentDV)

	// Lighting
	X_PROPERTY(QBitArray, LightSwitch)
	X_PROPERTY(std::vector<float>, LightAmbient)
	X_PROPERTY(std::vector<uint>, LightColor)
	X_PROPERTY(std::vector<float>, LightDireaction)

	void SetLightSwitch(int id, bool bSwitch);
	void SetLightAmbient(int id, float fAmbient);
	void SetLightColor(int id, uint rgb);
	void SetLightDireaction(int id, float fX, float fY, float fZ);

private:
	static constexpr int LIGHT_NUM = 4;
};

#endif // KEWINDOWINFO3D_H
