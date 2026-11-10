#ifndef _CXSCENE_H__
#define _CXSCENE_H__

#include <qgraphicsscene.h>
#include "xview.h"
#include "xgui_global.h"
#include <quuid.h>
#include "xobjectitem.h"


class CXWindow;
class CXViewInfoObject;
class CXGraphicViewInfo;

class XGUI_EXPORT CXScene: public QGraphicsScene, public IKEView
{
public:
	CXScene(CXWindow * pWindow, QObject *pParent = NULL);
	~CXScene();

	virtual bool CreateItem(QUuid objectID, CXViewInfoObject *pViewInfo) = 0;

	virtual bool DeleteItem(QUuid objectID);

	///@brief Reimplement function from IRLView
	virtual void UpdateView(const CXEventParameter& eventPara); 

	///	Canvas is the scene excludes the axis.
	virtual qreal GetCanvasWidth();
	virtual qreal GetCanvasHeight();

	///	Find out the 1st item contain the object.
	virtual CXObjectItem* FindItem(QUuid objectID, ERLItemType = eNone);

	///	Find out all items with the specified object type.
	virtual QList<CXObjectItem *> FindAllItems(EXObjectType);

	///	Find out items contain the object.
	virtual QList<CXObjectItem *> FindAllItems(QUuid objectID, ERLItemType = eNone);

	///	To get whether there's interactively move on the scene.
	virtual QPointF GetMoveOffset()
	{
		return m_moveOffset;
	}

	///	To get whether there's interactively zoom in/out on the scene.
	virtual qreal GetZoomScale()
	{
		return m_dZoomScale;
	}

	///	Get the window view info.
	virtual CXGraphicViewInfo* GetWindowViewInfo()
	{
		return m_pWindowViewInfo;
	}

	//	Change the scene zoom scale by delta.
	qreal ChangeZoomScale(qreal dInc)
	{
		m_dZoomScale += dInc;

		if(m_dZoomScale < 0.2)
		{
			m_dZoomScale = 0.2;
			dInc = 0;
		}

		return dInc;
	}

protected:
	CXWindow*					m_pWindow;			//	Pointer to the window.
	CXGraphicViewInfo*			m_pWindowViewInfo;

	qreal						m_dZoomScale;		//	Zoom in/out interactively.
	QPointF						m_moveOffset;		//	Move interactively.
};

#endif