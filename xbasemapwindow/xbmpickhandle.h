#ifndef XBMPICKHANDEL_H
#define XBMPICKHANDEL_H

/*!
 *	@breif	pick handle on base map.
 *	@author	caoweishi
 *	@update	pezy
 *	@date	Aug. 2015
 *	@see
 */

#include "xpickhandle.h"
class CXBaseMapWindow;
class CXSeismicSection;

class CXBMPickhandle : public CXPickhandle
{
public:
    CXBMPickhandle();
    ~CXBMPickhandle();

    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;
	void ResetPickedNodeStatus();

private:
	static bool _IsRandomSection(CXObject* pObj);
	static bool _IsPolygon(CXObject* pObj);

	bool _IsSectionLine(CXObject* pObj);
	bool _IsInScene(const osg::Vec2& posXY);
	bool _IsSeismicTimeslicePicked();

	void _UpdateStatusBar(const osg::Vec2& posXY, const osg::Vec2& normalizedXY);
	bool _IsObject(const osg::Vec2& normalizedXY, QString& strObjName);
	void _ResetStatus();

	void _PickObj(float fX, float fY);
	void _DragObj(float fX, float fY);
	void _OptDone(float fX, float fY);

	void _UpdateSeismicSection(const osg::Vec2& posXY);
	void _UpdateRandomSection(const osg::Vec2& posXY);
	void _UpdatePolygon(const osg::Vec2& posXY);
	
	osg::Vec3d _ScreenPosToWorld(const osg::Vec2& posXY);

private:
	CXBaseMapWindow* m_pWin = nullptr;
	osg::Camera* m_pCamera = nullptr;

	int m_iPivotIndex = -1;
};

#endif // KEBMPICKHANDEL_H
