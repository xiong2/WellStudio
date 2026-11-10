#ifndef _CXCrossPlotSCENE_H__
#define _CXCrossPlotSCENE_H__

#include "xcrossplot_global.h"
#include "xscene.h"
#include "xglobal.h"
#include <quuid.h>

class CXObject;
class CXAxis;
class CXViewInfoObject;
class CXCrossPlot;
class CXHistItemAnno;
class CXAxisTitleItem;

#define SCENEMARGIN 20

class XCROSSPLOT_EXPORT CXCrossPlotScene: public CXScene
{
	Q_OBJECT

public:
	CXCrossPlotScene(CXWindow * pCrossPlot, QObject *pParent = NULL);

	void SetColormapIDX(int iIDX)
	{
		m_iColormapIDX = iIDX;
	}

    virtual bool CreateItem(QUuid objectID, CXViewInfoObject *pViewInfo) override;

	void CreateItem(CXObject *, CXObject *, QColor, QColor, int, int, int iResample = 0, double dSZ = ::g_dInvalidData, double dEZ = ::g_dInvalidData);
	void CreateItem(CXObject *, CXObject *, CXObject *, QColor, int, int, int iResample = 0, double dSZ = ::g_dInvalidData, double dEZ = ::g_dInvalidData);

	void SetRange(QString sHTitle, QString sVTitle, double dXMin, double dXMax, double dYMin, double dYMax, double dCMin, double dCMax);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;

	int		m_iColormapIDX = -1;

	CXAxis	*m_pAxisX = NULL;
	CXAxis	*m_pAxisY = NULL;
	CXAxis	*m_pAxisC = NULL;

	CXHistItemAnno*			m_pAnnoItem = NULL;
	CXAxisTitleItem*		m_pHTitleItem = NULL;
	CXAxisTitleItem*		m_pVTitleItem = NULL;
};

#endif