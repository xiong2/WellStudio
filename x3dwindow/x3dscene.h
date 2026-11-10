#ifndef X3DSCENE_H_H
#define X3DSCENE_H_H

#include "x3dwindow_global.h"

#include <QList>
#include <QMap>
#include <QBitArray>
#include <osg/Camera>
#include <osg/Node>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>

#include "xview.h"
#include "xviewinfoobject.h"
#include "x3dglobalcoordmap.h"
#include "x3dcompass.h"
#include "x3dcursor.h"
#include "x3dlighting.h"
#include "x3dcolorbar.h"
#include "x3dautocubeaxes.h"

class CX3DWindow;
class CX3DBuilderAbstract;
class CXObject;

class X3DWINDOW_EXPORT CX3dscene : public QObject, public IKEView
{
	Q_OBJECT
public:
	CX3dscene(CX3DWindow* pOSGWindow);
	virtual ~CX3dscene();

	void ReleaseResource();
	virtual void UpdateView(const CXEventParameter& eventPara);

	void InitScene();
	void SetOjbectVisiability(QUuid objID, bool bVisible);
	void ShowCompass(bool bShow);
	void ShowColormap(bool bShow);
	void ShowCoordinate(bool bShow);
	void ShowCoordinateGrid(bool bShow);
	void SetColorbarObjVisible(const QUuid& objID, bool bVisible);

	QList<QUuid> GetAllDisplayObject();
	
	osg::Camera* GetCamera(){ return m_pCamera; }
	CX3DGlobalCoordMap* GetCoordMap() { return &m_coordMap; }

	void UpdateLightingViewInfo(int id);
	void SetLightingSphereVisible(bool bVisible);
	void UpdateLightingPosition();
	void UpdateAttribtue(const QUuid& uuidGeom);

public slots:
	void slotSetProjectionMode(bool bOrtho);
	void slotUpdateZScale(double dZScale);
	void slotUpdateWindowSize(int width, int height);
	void slotChangeBGColor(const QColor&);
	void slotUpdateCompass();

private:
	bool _IsSeismicVolumeChanged(const QUuid& uuidVolume);
	void _RemoveObject(QUuid objID);
	void _CreateObjectNode(CX3DBuilderAbstract* pBuilder, QUuid objID);
	osg::Switch* _GetDisplayObjectSwitch(QUuid objID);

private:
	osg::ref_ptr<osg::Group> m_pRootNode;
	osg::ref_ptr<osg::MatrixTransform> m_pGlobalTransform;
	osg::Camera* m_pCamera;

	QMap<QUuid, CX3DBuilderAbstract*> m_mapObjectToNodeBuilder;
	QList<QUuid> m_listDisplayedObjNode;	// maintenance nodes displayed on the scene.

	CX3DWindow* m_pOSGWindow;
	CX3DGlobalCoordMap m_coordMap;

	bool m_bFirst = true;
	bool m_bOrtho = false;

	CX3DAutoCubeAxes m_axes;
	CX3DColorbar m_colorbar;
	CX3DCompass m_compass;
	CX3DCursor m_cursor;
	CX3DLighting m_lighting;
};

#endif