#ifndef XPICKHANDEL_H_H
#define XPICKHANDEL_H_H

#include "x3dwindow_global.h"
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/View>
#include "xobject.h"

class CX3DWindow;

class X3DWINDOW_EXPORT CXPickhandle :public osgGA::GUIEventHandler
{
public:
	CXPickhandle();
	virtual ~CXPickhandle();

	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
	virtual void pick(osgViewer::View *view, const osgGA::GUIEventAdapter &ea);

	CXObject * GetCurPickedObj(){ return m_pPickedObj; }
	void ResetPickedObject(CXObject* pObject);
	int GetPrimitiveIndex(){ return m_PrimitiveIndex; }

private:
	void _ResetPickedNodeStatus();
	void _ShowVolumeToolbar(bool bVisible);

protected:
	osg::ref_ptr<osg::Group> m_pPickedNode;
	CXObject *m_pPickedObj;
	int m_PrimitiveIndex;
	float m_xNorm;
	float m_yNorm;

private:
	CX3DWindow* m_pWin;
};

#endif
