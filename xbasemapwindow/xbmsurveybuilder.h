#ifndef XBMSURVEYBUILDER_H
#define XBMSURVEYBUILDER_H

/*!
 *	@brief	display of seismic 3D survey.
 *	@author	pezy
 *	@date	2016-05-18
 *	@see
 */

#include "x3dbuilder.h"

namespace osgText { class Text; };
class CX3DSurvey;
class CXViewInfo3DSurvey;
class CXBMSurveyBuilder : public CX3DBuilderAbstract
{
public:
	CXBMSurveyBuilder();
	~CXBMSurveyBuilder();

	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	virtual void UpdateNode(EEventType eType) override;

private:
	//! @brief	Line-Trace coordinate to Local coordinate.
	osg::Vec3 _LT2Local(int iInline, int iXline) const;

	//! @brief	Get marks size.
	static float _GetMarkLength(int iMax, const std::string& strFont, int iFontSize, bool isInline = true);

	//! @brief	Calculate how many ticks we should have.
	std::pair<double, double> _CalcTicksGrid(int& iFirstInline, int& iLastInline, int& iInlineStep, int& iFirstXline, int& iLastXline, int& iXlineStep);

	//! @brief	Calculate the vertex of ticks.
	void _CalcTickVerticesAndBuildMarks(int iLineNo, float fTickSize, bool bInline);
	
	osg::Vec3Array* _BuildTickVertexAndMarks();
	osg::Geometry* _BuildBoundaryBox();
	osg::Geometry* _BuildSeismicLine();
	osg::Geometry* _BuildTracePoints();
	osgText::Text* _BuildSurveyLabel();
	osg::Geode* _BuildOrUpdateTickMarks();
	
	void _UpdateBoundaryBox();

private:
	CX3DSurvey* m_pSurvey = nullptr;
	CXViewInfo3DSurvey* m_pViewInfo = nullptr;

	int m_firstInline = -1;
	int m_lastInline = -1;
	int m_firstXline = -1;
	int m_lastXline = -1;

	osg::ref_ptr<osg::Geometry> m_pBoundaryGeom;
	osg::ref_ptr<osg::Geometry> m_pSeismicLineGeom;
	osg::ref_ptr<osg::Geometry> m_pTracePointsGeom;
	osg::ref_ptr<osgText::Text> m_pSurveyLabel;

	osg::ref_ptr<osg::Geode> m_pTickMarksNode;
	osg::ref_ptr<osg::Geode> m_pSurveyNode;

	osg::ref_ptr<osg::Vec3Array> m_pTickVertex;
};

#endif // KEBMSURVEYBUILDER_H
