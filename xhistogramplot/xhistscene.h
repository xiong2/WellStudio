#pragma once
#include "xhistogramplot_global.h"
#include "xscene.h"

class CXObject;
class CXAxis;
class CXHistogramPlot;
class CXHistItemAnno;
class CXHistItemName;
class CXHistItem;

class XHISTOGRAMPLOT_EXPORT CXHistScene : public CXScene
{
	Q_OBJECT

public:
	CXHistScene(CXWindow * pWindow, QObject *pParent = NULL);
	~CXHistScene();

	virtual bool CreateItem(QUuid objectID, CXViewInfoObject *pViewInfo) override;
	virtual bool DeleteItem(QUuid objectID) override;

protected:
	void initialize();

	CXHistogramPlot*	m_pWindow;

	int			m_iZValue = 1;
	int			m_iBinNum = 256;
	double		m_dDMin = 99999999.;
	double		m_dDMax = -99999999.;
	double		m_dYMax = -99999999.;

	unsigned int	m_eObjType = EXEnd;

	CXAxis	*m_pAxisX = NULL;
	CXAxis	*m_pAxisY = NULL;
	CXHistItemAnno*				m_pAnnoItem = NULL;
	CXHistItemName*				m_pNameItem = NULL;
	QMap<QUuid, CXHistItem*>	m_mapItem;
};
