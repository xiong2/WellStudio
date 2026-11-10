#ifndef GSDLGINTERACTIVECALCULATION_H
#define GSDLGINTERACTIVECALCULATION_H

#include <QDialog>
#include <QGraphicsScene>
#include "xglobalcoordtransform.h"
#include "gsbmcoordinateitem.h"
#include "gs3dhorizonviewinfo.h"
#include "ui_gsdlginteractivecalculation.h"
#include "xseismicutmtool.h"

class CXObject;
class CX3DHorizon;
class GSAnticline;
class GS3DHorizonFaultTraces;
class GSStructure;
class GSBM3DHorizonItem;
class GSItemTrapPoints;
class GSItemFaultPolygons;
class GSItemAnticlines;
class GSItemStructures;
class GSItemStress;
class GSStressParameters;
class GSStressMap;

class GSDlgInteractiveCalculation : public QDialog
{
	Q_OBJECT

public:
	GSDlgInteractiveCalculation(CXObject* pObj, QWidget *parent = 0);
	~GSDlgInteractiveCalculation();

protected:
	void showEvent(QShowEvent*) override;

private:
	void initView();
	GSBM3DHorizonItem* getSmoothHorizonItem();

	void slotGetPosition(const QPoint& pos, QGraphicsItem* pItem);
	void slotSmooth(int checkState);

	void slotSetVisible();
	void slotSetColorMode();
	void slotSearchPoints();
	void slotAdjustFaults();
	void slotFitLines();
	void slotCreateStructures();
	void slotCalculate();
	void slotClear();
	void slotAccept();

	void smooth(const CXSeismicUTMTool& utm, float* pData, double dWindowSize);

private:
	Ui::GSDlgInteractiveCalculation ui;
	
	CX3DHorizon* m_pHorizon = nullptr;
	CX3DHorizon* m_pSmoothHorizon = nullptr;

	GSBMCoordinateItem* m_pCoordItem = nullptr;
	GSBM3DHorizonItem* m_pHorizonItem = nullptr;
	GSBM3DHorizonItem* m_pSmoothHorizonItem = nullptr;

	QGraphicsScene m_scene;
	CXGlobalCoordTransform m_coordTransform;
	GS3DHorizonViewInfo m_horizonViewInfo;

	GSStressParameters*		m_pParas;

	GSItemTrapPoints*		m_pTrapPointsItem[3];
	GSItemAnticlines*		m_pAnticlinesItem = nullptr;
	GSItemFaultPolygons*	m_pFaultPolygonsItem = nullptr;
	GSItemStructures*		m_pStructuresItem = nullptr;
	GSItemStress*			m_pStressItem = nullptr;

	QVector<QVector<double> >			m_vecvecTrapPoints[3];
	QList<GS3DHorizonFaultTraces *>		m_listFT;
	QList<GSAnticline *>				m_listAnticline;
	QList<GSStructure *>				m_listStructure;
	GSStressMap*						m_pMap = nullptr;
};

#endif // GSDLGINTERACTIVECALCULATION_H
