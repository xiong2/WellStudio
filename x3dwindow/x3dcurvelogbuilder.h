#pragma once
#include "x3dbuilder.h"
#include <qcolor.h>

/**
* @class CX3DCurveLogBuilder rl3dcurvelogbuilder.h
* @brief The CX3DCurveLogBuilder class define well log curve 3D builder.
* @author daily 
* @date 5/05/2014
* @see CX3DBuilderAbstract
*/
using namespace osg;
using namespace std;
class CXWellCurve;
class CXViewInfoWellCurve;
class CXLinearityMap;
class CX3DCurveLogBuilder : 	public CX3DBuilderAbstract
{
public:
	CX3DCurveLogBuilder(void);
	~CX3DCurveLogBuilder(void);
	ref_ptr<Group> Build(QUuid objId);
	void UpdateNode(EEventType eType);
private:
	QColor _GetVertexColor(double dValue,bool bLineColor = false);
	ref_ptr<Group> _CreateShapeStucture();
	void _CreateCylinderShape(int nCount ,double *pX,double *pY,double *pZ,	double *pValue, vector<pair<int,int> >&vecPathSegments);
	void _InitData();
	void  _BuildCurve(double *pX,double *pY,double *pZ, vector<pair<int,int> >&vecPathSegments);
private:
	CXWellCurve *m_pWellCurve;
	CXViewInfoWellCurve *m_pViewInfo;
	CXLinearityMap *m_pLinearMap;
private:
	osg::ref_ptr<osg::Geode> m_pCurveNode;
	osg::ref_ptr<osg::Geode> m_pCylinderNode;
};

