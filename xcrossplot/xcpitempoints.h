#pragma once
#include <QGraphicsRectItem>

class CXAxis;

class CXCPItemPoints : public QGraphicsRectItem
{
public:
	CXCPItemPoints(QRectF, CXAxis *, CXAxis *, unsigned int iNum, double *pHData, double *pVData,
		QColor penColor, QColor fillColor, int iSize, int iShape, bool bNeedFree = false, QGraphicsItem *parent = 0);
	CXCPItemPoints(QRectF, CXAxis *, CXAxis *, CXAxis *, unsigned int iNum, double *pHData, double *pVData, double *pCData,
		QColor penColor, int iCIDX, int iSize, int iShape, bool bNeedFree = false, QGraphicsItem *parent = 0);
	~CXCPItemPoints();

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

	CXAxis	*m_pAxisX = NULL;
	CXAxis	*m_pAxisY = NULL;
	CXAxis	*m_pAxisC = NULL;

	bool	m_bNeedFree;
	unsigned int	m_iNum;
	double*	m_pHData;
	double*	m_pVData;
	double*	m_pCData;

	QColor	m_penColor;
	QColor	m_fillColor;
	int		m_iSize;
	int		m_iShape;
	int		m_iColormapIDX = -1;
};