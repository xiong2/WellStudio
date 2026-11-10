#ifndef GSBASEMAPSCENE_H
#define GSBASEMAPSCENE_H

#include <QGraphicsScene>
#include <vector>
#include <QStack>

class QGraphicsLineItem;
class CXGlobalCoordTransform;
class CX3DSurvey;
class GSRSItemCompose;

class GSBMItemDefineRose;

class GSBasemapScene : public QGraphicsScene
{
	Q_OBJECT

public:
	enum Mode { eNone, eCreateSection, eCreatePDG, eCreateRoseDiagram, eZoomByRect, eRegionalStress };

	GSBasemapScene(const CXGlobalCoordTransform& coord, QObject *parent = nullptr);
	~GSBasemapScene();

	void SetMode(Mode mode, QGraphicsRectItem* = NULL);
	double GetRealPixelSize(int size);
	void UndoLastZoom();

	CX3DSurvey* GetCurrentSurvey();
	void SetCurrentSurvey(CX3DSurvey* pSurvey);

	GSBMItemDefineRose* CreateDefineRoseItem(double);
	void RemoveDefineRoseItem();

signals:
	void AddThisObjToTree(const QUuid& objID);
	void ShowThisObj(const QUuid& objID);
	void EnableZoomUndo(bool isEnable);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
	bool isInCurrentSurvey(const QPointF& pos);
	bool isSameIJInCurrentSurvey(const QPointF& lhs, const QPointF& rhs);

private:
	Mode m_mode = eNone;
	std::vector<QGraphicsLineItem*> m_vecBuildingItem;
	QGraphicsRectItem* m_pZoomRectItem = nullptr;
	QStack<QRectF> m_zoomRectStack;
	const CXGlobalCoordTransform& m_coord;
	CX3DSurvey* m_pCurrentSurvey = nullptr;

	GSBMItemDefineRose*	m_pDefineRoseItem = nullptr;

	GSRSItemCompose*	m_pCompItem = nullptr;
};

#endif // GSBASEMAPSCENE_H
