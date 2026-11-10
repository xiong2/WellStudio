#pragma once
#include <QDialog>
#include <QGraphicsScene>
#include "xvec.h"
#include "xglobalcoordtransform.h"
#include "gs3dhorizonviewinfo.h"
#include "ui_gsdlginteractivecurvatureanalysis.h"

class CXObject;
class CX3DHorizon;
class GSStructure;
class GSStressMap;
class GS3DHorizonFaultTraces;
class GSStressParameters;
class GSBMCoordinateItem;
class GSBM3DHorizonItem;
class GSItemSticks;
class GSItemFaultPolygons;
class GSItemStructures;
class GSItemStress;
class GSItemWells;

class GSDlgInteractiveCurvatureAnalysis : public QDialog 
{
	Q_OBJECT

public:
	GSDlgInteractiveCurvatureAnalysis(CXObject *, QWidget * parent = Q_NULLPTR);
	~GSDlgInteractiveCurvatureAnalysis();

	virtual void accept() override;

protected:
	void showEvent(QShowEvent*) override;

private:
	void initUI();
	void initView();
	void freeMaps(int iOpp = 0);

	void refreshFaultTable();
	void refreshWellTable();

	void interpolateMag(std::vector<XPoint>&);
	void interpolateDir(std::vector<XPoint>&, std::vector<XPoint>&);

	void slotGetPosition(const QPoint& pos, QGraphicsItem* pItem);
	void slotCalculate();
	void slotBlender();
	void slotChangeView();
	void slotShowSticks();
	void slotShowFaults();
	void slotSelectFaults();
	void slotCreateStructures();
	void slotShowWells();
	void slotCalStress();
	void slotClear();

	Ui::GSDlgInteractiveCurvatureAnalysis ui;

	GSBMCoordinateItem*		m_pCoordItem = nullptr;
	GSBM3DHorizonItem*		m_pHorizonItem = nullptr;
	GSBM3DHorizonItem*		m_pMPCItem = nullptr;
	GSBM3DHorizonItem*		m_pMNCItem = nullptr;
	GSBM3DHorizonItem*		m_pAziItem = nullptr;
	GSBM3DHorizonItem*		m_pBleItem = nullptr;
	GSItemSticks*			m_pSticksItem = nullptr;
	GSItemFaultPolygons*	m_pFPsItem = nullptr;
	GSItemStructures*		m_pStrItem = nullptr;
	GSItemStress*			m_pStressItem = nullptr;
	GSItemWells*			m_pWellsItem = nullptr;

	QGraphicsScene m_scene;
	CXGlobalCoordTransform m_coordTransform;
	GS3DHorizonViewInfo m_horizonViewInfo;

	CX3DHorizon *m_pHorizon = nullptr;
	CX3DHorizon *m_pMPC = nullptr;
	CX3DHorizon *m_pMNC = nullptr;
	CX3DHorizon *m_pAzi = nullptr;
	CX3DHorizon *m_pBle = nullptr;

	GSStressParameters*		m_pParas;
	QList<GSStructure *>	m_listStructure;
	GSStressMap*			m_pMap = nullptr;

	QList<GS3DHorizonFaultTraces *>	m_listHF;
	QList<GS3DHorizonFaultTraces *>	m_listSHF;

	int m_nI, m_nJ;
};
