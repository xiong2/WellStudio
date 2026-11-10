#include "x3dlighting.h"

#include <osg/PositionAttitudeTransform>
#include <osg/Material>
#include <osg/ShapeDrawable>

#include "xwindowinfo3d.h"
#include "x3dutility.h"

CX3DLighting::CX3DLighting()
{
	m_vecLightSource.resize(LIGHT_NUM);
	m_vecLightSphere.resize(LIGHT_NUM);
	m_vecLight.resize(LIGHT_NUM);
}

CX3DLighting::~CX3DLighting()
{
}

osg::ref_ptr<osg::Group> CX3DLighting::GetLightingNode()
{
	if (!m_pLightGroup.valid())
	{
		m_pLightGroup = new osg::Group;

		for (int i = 0; i != LIGHT_NUM; ++i)
		{
			auto pPosition = new osg::PositionAttitudeTransform;
			pPosition->addChild(_BuildLightSource(i));
			pPosition->setPosition(osg::Vec3());

			m_pLightGroup->addChild(pPosition);
		}
	}

	return m_pLightGroup;
}

void CX3DLighting::SetWindowInfoAndRootStateSet(CXWindowInfo3D * pWinInfo, osg::StateSet * pRootStateSet)
{
	m_pWinInfo = pWinInfo;
	m_pRootStateSet = pRootStateSet;
}

void CX3DLighting::UpdatePosition(const osg::BoundingBox & box)
{
	auto _DirectToCoord = [](float fDirection, float fCoordMin, float fCoordMax)
	{
		// -1 ~ +1 map to min ~ max
		return 0.5f * (fDirection + 1) * (fCoordMax - fCoordMin) + fCoordMin;
	};

	if (!m_pLightGroup.valid() || m_pLightGroup->getNumChildren() == 0)
		return;

	const std::vector<float>& vecDireaction = m_pWinInfo->GetLightDireaction();

	for (int i = 0; i < LIGHT_NUM; ++i)
	{
		osg::Vec3 vecLightPosition;
		vecLightPosition.x() = _DirectToCoord(vecDireaction.at(i * 3), box.xMin(), box.xMax());
		vecLightPosition.y() = _DirectToCoord(vecDireaction.at(i * 3 + 1), box.yMin(), box.yMax());
		vecLightPosition.z() = _DirectToCoord(vecDireaction.at(i * 3 + 2), box.zMin(), box.zMax());

		auto pPositionAttitudeTransform = dynamic_cast<osg::PositionAttitudeTransform*>(m_pLightGroup->getChild(i));
		pPositionAttitudeTransform->setPosition(vecLightPosition);
		m_vecLight.at(i)->setPosition(osg::Vec4(box.center() - vecLightPosition, 0));
	}
}

void CX3DLighting::SetSphereVisible(bool bVisible)
{
	if (!m_pLightGroup.valid() || m_pLightGroup->getNumChildren() == 0)
		return;

	const QBitArray& lightSwitch = m_pWinInfo->GetLightSwitch();

	for (int i = 0; i != LIGHT_NUM; ++i)
	{
		if (lightSwitch.at(i) && bVisible)
		{
			m_pLightGroup->getChild(i)->asTransform()->addChild(_BuildLightSphere(i));
		}
		else
		{
			m_pLightGroup->getChild(i)->asTransform()->removeChild(m_vecLightSphere.at(i));
		}
	}
}

void CX3DLighting::UpdateViewInfo(int id)
{
	if (!m_pLightGroup.valid() || m_pLightGroup->getNumChildren() == 0)
		return;

	const QBitArray& lightSwitch = m_pWinInfo->GetLightSwitch();

	m_pLightGroup->getChild(id)->asTransform()->removeChild(m_vecLightSphere.at(id));
	m_pLightGroup->getChild(id)->asTransform()->removeChild(m_vecLightSource.at(id));

	if (lightSwitch.at(id))
	{
		m_pLightGroup->getChild(id)->asTransform()->addChild(_BuildLightSphere(id));
		m_pLightGroup->getChild(id)->asTransform()->addChild(_BuildLightSource(id));
	}
}

osg::LightSource * CX3DLighting::_BuildLightSource(int id)
{
	m_vecLightSource[id] = new osg::LightSource;

	const QBitArray& lightSwitch = m_pWinInfo->GetLightSwitch();

	m_vecLightSource[id]->setLight(_BuildLight(id));
	m_vecLightSource[id]->setLocalStateSetModes(osg::StateAttribute::ON);
	m_vecLightSource[id]->setStateSetModes(*m_pRootStateSet, lightSwitch.at(id));

	return m_vecLightSource.at(id).get();
}

osg::Geode * CX3DLighting::_BuildLightSphere(int id)
{
	m_vecLightSphere[id] = new osg::Geode;

	const std::vector<uint> listColor = m_pWinInfo->GetLightColor();
	const QColor& color = QColor(listColor.at(id));
	
	osg::ref_ptr<osg::Material> pMaterial = new osg::Material;
	pMaterial->setDiffuse(osg::Material::FRONT, osg::Vec4(0.0, 0.0, 0.0, 1.0));
	pMaterial->setEmission(osg::Material::FRONT, osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));

	m_vecLightSphere[id]->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(), SPHERE_RADIUS)));
	m_vecLightSphere[id]->getOrCreateStateSet()->setAttribute(pMaterial);

	return m_vecLightSphere.at(id).get();
}

osg::Light * CX3DLighting::_BuildLight(int id)
{
	m_vecLight[id] = new osg::Light;

	const std::vector<uint> listColor = m_pWinInfo->GetLightColor();
	const std::vector<float> listAmbient = m_pWinInfo->GetLightAmbient();

	const QColor& color = QColor(listColor.at(id));
	float fAmbient = listAmbient.at(id);

	m_vecLight[id]->setLightNum(id);
	m_vecLight[id]->setPosition(osg::Vec4(1.0, 1.0, 1.0, 0.0));
	m_vecLight[id]->setDiffuse(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	m_vecLight[id]->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	m_vecLight[id]->setAmbient(osg::Vec4(fAmbient, fAmbient, fAmbient, 1.0));

	return m_vecLight.at(id).get();
}
