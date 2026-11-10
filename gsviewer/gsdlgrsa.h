#ifndef GSDLGRSA_H
#define GSDLGRSA_H

#include <QDialog>
#include <QGraphicsScene>
#include "ui_gsdlgrsa.h"
#include "xglobalcoordtransform.h"
#include "gs3dhorizonviewinfo.h"
#include "gsbasemapscene.h"

class CX3DSurvey;
class CX3DHorizon;
class GSBMCoordinateItem;
class GSBM3DHorizonItem;
class GSRSItemSource;
class GSRSItemCompose;
class GSGeologicStage;
class GSStressMap;

class GSDlgRSA : public QDialog
{
	Q_OBJECT

public:
	GSDlgRSA(QWidget *parent = 0);
	~GSDlgRSA();

	bool UpdateOneSou(int iIDX, QPointF);

	GSStressMap* GetCurrentMap();

protected:
	void showEvent(QShowEvent*) override;

	void reScale(bool bZoomIn);

private slots:
	void slotGetPosition(const QPoint& pos, QGraphicsItem* pItem);
	void slotSurvey();
	void slotSpinStage();
	void slotCBStage();
	void slotChangeRSSNum();
	void slotSouAzi();
	void slotHorizon();

private:
	void initUI();
	void initView();

	Ui::GSDlgRSA ui;

	GSBasemapScene m_scene;
	CXGlobalCoordTransform m_coordTransform;
	GS3DHorizonViewInfo m_horizonViewInfo;

	GSBMCoordinateItem*		m_pCoordItem = nullptr;
	GSBM3DHorizonItem*		m_pHorizonItem = nullptr;

	GSRSItemCompose*		m_pComItem = nullptr;
	QList<GSRSItemSource *>	m_listRSSItem;

	QPointF			m_center;
	CX3DSurvey		*m_pSurvey = nullptr;
	CX3DHorizon		*m_pHorizon = nullptr;
	GSGeologicStage	*m_pGStage = nullptr;
	int				m_iCurSou = -1;

	float	m_fScale = 0.6;
};

#endif // GSDLGRSA_H
