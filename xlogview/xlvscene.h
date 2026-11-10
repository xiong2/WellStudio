#pragma once
#include "xscene.h"
#include "xlogview_global.h"
#include "xobjectitem.h"

class CXWindow;
class CXLVItemWell;
class CXLVItemWellTops;
class CXLVWindowInfo;

class XLOGVIEW_EXPORT CXLVScene : public CXScene
{
	Q_OBJECT

public:
	CXLVScene(CXWindow * pWindow, QObject *pParent = NULL);
	~CXLVScene();
	
	virtual bool CreateItem(QUuid objectID, CXViewInfoObject *pViewInfo) override;
	virtual bool DeleteItem(QUuid objectID) override;

	qreal GetRightEdge();
	qreal GetBottomEdge();

	QVector<CXLVItemWell *>& GetAllWellItems()
	{
		return m_vecWellItem;
	}

	CXLVItemWellTops* GetWellTopsItem()
	{
		return m_pTopsItem;
	}

public slots:
	void update();

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;

	CXLVItemWell*	findWellItem(QUuid);

	QVector<CXLVItemWell *>		m_vecWellItem;
	CXLVItemWellTops*			m_pTopsItem = NULL;
};