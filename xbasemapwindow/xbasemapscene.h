#ifndef CXBASEMAPSCENE_H
#define CXBASEMAPSCENE_H

/*!
 *  @class  CXBasemapScene in kebasemapscene.h
 *  @brief  Management all item in basemap scene.
 *  @author caoweishi, pezy
 *  @date   2016-01-14
 *  @see    CX3DScene
 */

#include <QObject>
#include <QMap>
#include <QUuid>
#include <osg/Group>
#include <osg/Camera>
#include <osg/BoundingBox>
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include "xview.h"
#include "x3dglobalcoordmap.h"
#include "xbasemapcoordinate.h"
#include "xbmscale.h"
#include "xbmcompass.h"
#include "x3dcolorbar.h"
#include "x3dcursor.h"

class CXBaseMapWindow;
class CX3DBuilderAbstract;
class CX3DSurvey;

class CXBasemapScene : public QObject, public IKEView
{
    Q_OBJECT
public:
    CXBasemapScene(CXBaseMapWindow* pBaseMapWindow);
    virtual ~CXBasemapScene();

    virtual void UpdateView(const CXEventParameter& eventPara) override;

    void InitScene();
    bool SetOjbectVisiability(QUuid objID, bool bVisible);
    void CreateHudCamera();
    osg::Camera *GetHudCamera(){ return m_pHudCamera; }
	const osg::BoundingBox& GetSceneBoundBox(){ return m_coord.GetBoundBox(); }
    void CreateRandomSection();
    void Create2DPolygon();
	void UpdateHUDWithWindow();
	void SetCursorVisible(bool bVisible);
	void SetColorbarVisible(bool bVisible);
	void SetCompassVisible(bool bVisible);
	void SetScaleVisible(bool bVisible);
	void SetScaleMark(int scale);
	void UpdateCoordinateInfo();
	void UpdateScaleInfo();
	void UpdateCompassInfo();
	void UpdateColorbarInfo();
	void UpdateAttribtue(const QUuid& uuidGeom);
	void SetColorbarObjVisible(const QUuid& objID, bool bVisible);
	bool IsInSurvey(const osg::Vec3d& vecWorld, int& iInline, int& iXline);
	bool IsInSurvey(const osg::Vec2& vecScreen);
    
    CX3DGlobalCoordMap* GetCoordMap() { return &m_coordMap; }

private:
    bool _RemoveObject(QUuid objID);
    void _CreateObjectNode(CX3DBuilderAbstract* pBuilder, QUuid objID);
	void _UpdatePickedTimeSlice(const CXEventParameter& eventPara);
	void _UpdateTrackingToolsStatus();
	void _UpdateBoundingBox();
	bool _IsSeismicDataVolume(const QUuid& uuidGeom);
	QUuid _GetPickedSectionID(const QUuid& uuidDV);

private:
    CXBaseMapWindow *m_pBaseMapWin;
	
    osg::ref_ptr<osg::Group> m_pRootNode = nullptr;
    osg::ref_ptr<osg::Camera> m_pCamera = nullptr;    
    osg::ref_ptr<osg::Camera> m_pHudCamera = nullptr;

    QMap<QUuid, CX3DBuilderAbstract*> m_mapObjectToNodeBuilder;

	CX3DGlobalCoordMap m_coordMap;
	CX3DColorbar m_colorbar;
	CX3DCursor m_cursor;
	CXBasemapCoordinate m_coord;
	CXBMScale m_scale;
	CXBMCompass m_compass;

	bool m_bFirst = true;
};

#endif // CXBASEMAPSCENE_H
