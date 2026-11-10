#ifndef XMICROSEISMICBUILDER_H
#define XMICROSEISMICBUILDER_H

#include <osg/Geode>
#include <osg/Array>
#include <osg/Vec4>
#include <osg/ShapeDrawable>

#include "x3dbuilder.h"
#include "xmicroseismicdata.h"

///
///@brief	use spheres to display micro seismic data.
///@author	PEZY
///@date	Sept. 2014
///@see		class CX3DBuilderAbstract;
///
class CX3DWindow;

class CXMicroSeismicBuilder : public CX3DBuilderAbstract
{
public:
	CXMicroSeismicBuilder();
	~CXMicroSeismicBuilder();

	///@brief	override functions.
	virtual osg::ref_ptr<osg::Group> Build(QUuid objId);
	virtual void UpdateNode(EEventType eType);

private:
	bool _UpdateData();
	void _UpdateInfo();

	///@brief	init color list for stage.(!!!TEMP!!!)
	void _InitColorList();
	///@brief	get sphere's radius by magnitude.
	float _GetRadius(int iIndex);
	osg::Vec3 _GetCenter(int iIndex);
	osg::ShapeDrawable* _BuildSphere(int iIndex);

private:
	osg::ref_ptr<osg::Geode> m_pGeode;
	vector<osg::Vec4> m_vecColors;

	vector<double> m_vecX;
	vector<double> m_vecY;
	vector<double> m_vecZ;

	vector<QVariant> m_vecStage;
	vector<QVariant> m_vecMagnitude;

	int m_nNum = 0;
	float m_fZScale = 0.f;
	double m_dMagnitudeMin = 0.0, m_dMagnitudeMax = 0.0, m_dMagnitudeStep = 0.0;
};

#endif // RLMICROSEISMICBUILDER_H
