#include "xmicroseismicbuilder.h"

#include <osg/Group>

#include "x3dbuilderfactory.h"
#include "xmicroseismicdata.h"
#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include "x3dwindow.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXMicroSeismicBuilder)
{ EXMicroSeismicData, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CXMicroSeismicBuilder)

CXMicroSeismicBuilder::CXMicroSeismicBuilder()
{
	m_bScalable = false;
	_InitColorList();
}

CXMicroSeismicBuilder::~CXMicroSeismicBuilder()
{
}

osg::ref_ptr<osg::Group> CXMicroSeismicBuilder::Build(QUuid objId)
{
	SetObjectID(objId);
	if (!_UpdateData())
		return nullptr;

	_UpdateInfo();

	m_pGeode = new osg::Geode;

	for (int i = 0; i != m_nNum; ++i)
		m_pGeode->addDrawable(_BuildSphere(i));

	return m_pGeode.get();
}

void CXMicroSeismicBuilder::UpdateNode(EEventType eType)
{
	if (EDataChanged == eType)
	{
		if (_UpdateData())
		{
			_UpdateInfo();

			m_pGeode->removeDrawables(0, m_nNum);
			for (int i = 0; i != m_nNum; ++i)
				m_pGeode->addDrawable(_BuildSphere(i));
		}
	}
}

bool CXMicroSeismicBuilder::_UpdateData()
{
	auto pData = dynamic_cast<CXMicroSeismicData*>(::GetObjectByID(m_objID));
	if (!pData)
		return false;

	pData->GetPointPosition(m_vecX, m_vecY, m_vecZ);
	pData->GetOtherAttribute("Stage", m_vecStage);
	pData->GetOtherAttribute("Magnitude", m_vecMagnitude);

	m_nNum = pData->GetPointNum();

	if (0 == m_nNum)
		return false;

	if (m_vecStage.empty() || m_vecStage.begin()->type() == QVariant::Invalid)
		m_vecStage.assign(m_nNum, 0);
	if (m_vecMagnitude.empty() || m_vecMagnitude.begin()->type() == QVariant::Invalid)
		m_vecMagnitude.assign(m_nNum, 10);

	auto minMax = std::minmax_element(m_vecMagnitude.begin(), m_vecMagnitude.end(), [](const QVariant& a, const QVariant& b) {
		return a.toDouble() < b.toDouble();
	});

	m_dMagnitudeMin = (*minMax.first).toDouble();
	m_dMagnitudeMax = (*minMax.second).toDouble();
	m_dMagnitudeStep = (m_dMagnitudeMax - m_dMagnitudeMin) / 10;

	return true;
}

void CXMicroSeismicBuilder::_UpdateInfo()
{
	auto p3DWindow = dynamic_cast<CX3DWindow*>(m_pCurWin);
	m_fZScale = static_cast<float>(p3DWindow->GetZScale());
}

void CXMicroSeismicBuilder::_InitColorList()
{
	m_vecColors.push_back(osg::Vec4(0.75, 0.75, 0.75, 1.0));	///> Silver
	m_vecColors.push_back(osg::Vec4(0.50, 0.50, 0.50, 1.0));	///> Gray
	m_vecColors.push_back(osg::Vec4(0.50, 0.0f, 0.0f, 1.0));	///> Maroon
	m_vecColors.push_back(osg::Vec4(0.50, 0.50, 0.0f, 1.0));	///> Olive
	m_vecColors.push_back(osg::Vec4(0.0f, 0.50, 0.0f, 1.0));	///> Green
	m_vecColors.push_back(osg::Vec4(0.50, 0.0f, 0.50, 1.0));	///> Purple
	m_vecColors.push_back(osg::Vec4(0.0f, 0.50, 0.50, 1.0));	///> Teal
	m_vecColors.push_back(osg::Vec4(0.0f, 0.0f, 0.50, 1.0));	///> Navy
}

float CXMicroSeismicBuilder::_GetRadius(int iIndex)
{
	double dCurrMagnitude = m_vecMagnitude.at(iIndex).toFloat();

	if (m_dMagnitudeStep == 0)
		return dCurrMagnitude;

	float fRadius = (dCurrMagnitude - m_dMagnitudeMin) / m_dMagnitudeStep;
	return ceil(fRadius) + 1.f;
}

osg::Vec3 CXMicroSeismicBuilder::_GetCenter(int iIndex)
{
	osg::Vec3 center;
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(m_vecX[iIndex], m_vecY[iIndex], m_vecZ[iIndex]), center);
	center.z() *= m_fZScale;

	return center;
}

osg::ShapeDrawable * CXMicroSeismicBuilder::_BuildSphere(int iIndex)
{
	osg::TessellationHints* pHints = new osg::TessellationHints;
	pHints->setDetailRatio(0.3f);

	auto pSphere = new osg::ShapeDrawable(new osg::Sphere(_GetCenter(iIndex), _GetRadius(iIndex)), pHints);
	pSphere->setColor(m_vecColors.at(qBound(0, m_vecStage.at(iIndex).toInt() - 1, 7)));

	return pSphere;
}
