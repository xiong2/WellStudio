#ifndef XBMSURVEYCALLBACK_H
#define XBMSURVEYCALLBACK_H

#include <osg/Callback>
#include <osg/Array>
#include <vector>
#include <qvector.h>
#include <quuid.h>

namespace osg { class Camera; class Geode; class Geometry; };
class CXBaseMapWindow;
class CXObject;

class CXBMSurveyCallback : public osg::NodeCallback
{
public:
	CXBMSurveyCallback(osg::Camera* pHUDCamera, CXBaseMapWindow* pBMWindow);
	~CXBMSurveyCallback();

	void operator()(osg::Node* node, osg::NodeVisitor* nv) override;

	void UpdateVertexWhileScroll();
	void GetXYofTuringPoint(std::vector<double>& vecX, std::vector<double>& vecY);
	void GetData(double* &pData, int& nSize);
	QUuid GetCombinedLineID() { return m_clUid; }

private:
	void _Process(osg::Node* node, osg::NodeVisitor* nv);
	
	osg::Geode* _BuildPointLinesGeode();
	osg::Geometry* _BuildPointLinesGeometry();

	GLenum _GetShapeType();
	void _SetReady(bool bReady);

	void _Append(const osg::Vec2& newPos);
	void _Aim(const osg::Vec2& movePos);
	void _Pop();
	void _Clear();
	void _Done();
	void _Update();

	void _FinishCreateCombinedLine();

private:
	CXBaseMapWindow* m_pWin = nullptr;
	osg::Camera* m_pHUDCamera = nullptr;
	osg::Camera* m_pCamera = nullptr;

	float m_x = -100000.f;
	float m_y = -100000.f;

	osg::ref_ptr<osg::Geometry> m_pGeom;
	osg::ref_ptr<osg::Vec3Array> m_pVertex;

	std::vector<osg::Vec3> m_vLocal;

	QVector<CXObject *>	m_vecObj;	//	Only for combined line.
	QUuid	m_clUid;
};

#endif // KEBMSURVEYCALLBACK_H
