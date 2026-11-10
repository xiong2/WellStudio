#ifndef XCANVASROSEDIAGRAM_H
#define XCANVASROSEDIAGRAM_H

#include <QFrame>
#include <qpoint.h>

class CXSeismicIrregularReader;

class CXCanvasRoseDiagram : public QFrame
{
	Q_OBJECT

public:
	CXCanvasRoseDiagram(QWidget *parent);
	~CXCanvasRoseDiagram();
	
	CXSeismicIrregularReader *m_pReader;
	unsigned int m_iNumGather;

	QString	m_strColormap;
	QColor	m_gridColor;
	QColor	m_roseColor;
	bool	m_bRose;
	bool	m_bBins;
	bool	m_bGrid;
	bool	m_bHisto;

	void Refresh(unsigned int iNumRose, int iStartRose, int iEndRose, unsigned int iNumBin);

protected:
	virtual void paintEvent(QPaintEvent *);
	void drawBackground();
	void drawGrid();
	void drawRose();
	void drawBins();
	void drawHisto();

	int		m_iRadius;		//	Radius of the circle.
	QPoint	m_qOriPoint;	//	Origin point of the circle.

	int				m_iStartRose;
	int				m_iEndRose;
	unsigned int	m_iNumRose;
	unsigned int	m_iNumBins;
	unsigned int	m_iMaxTotal;
	unsigned int	m_iMaxRose;
	unsigned int	m_iMaxBin;
	unsigned int*	m_pTotalQuant;	//	Length is m_iNumRose * m_iNumBins, m_iNumBins vary fast.
	unsigned int*	m_pRoseQuant;	//	Length is m_iNumRose.
	unsigned int*	m_pBinQuant;	//	Length is m_iNumBins.
};

#endif // KECANVASROSEDIAGRAM_H