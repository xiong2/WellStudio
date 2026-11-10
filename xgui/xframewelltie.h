#pragma once
#include <qframe.h>
#include <qpainterpath.h>

class CXObject;
class CXWell;
class CXWellTD;
class CXWellCurve;
class CXSeismicDataVolume;
class CXDlgWellTie;

enum EXTrack
{
	eAC = 0b00000001,
	eDen = 0b00000010,
	eRC = 0b00000100,
	eTD = 0b00001000,
	eDrift = 0b00010000,
	eSyn = 0b00100000,
	eNTrace = 0b01000000,
	eNSec = 0b10000000
};

struct SLayout
{
public:
	int		m_iShowTracks = 7;	//	AC | Den | RC
	int		m_iNumTraces = 9;
	int		m_iLType = 0;		//	TWT
	int		m_iRType = 3;		//	SSTVD
	int		m_iSnap = 0;		//	P/T, Peak, Trough, None.
};

class CXFrameWellTie : public QFrame
{
public:
	CXFrameWellTie(CXWell *, CXDlgWellTie *, QWidget *parent = NULL);
	~CXFrameWellTie();

	void Populate(CXObject *pDV, CXWellCurve *pAC, CXWellCurve *pDen, CXWellCurve *pRC, float *pSyn, double dSTime, double dStep, unsigned int iNum);

	void SetCorRect(int iSTime = -999, int iETime = -999);

	int GetTrackPos(EXTrack);
	int GetCanvasWidth();

	SLayout& GetSLayout()
	{
		return m_sLayout;
	}

	void RefreshLayout();

	///	iSta = 0: Reset.  1: Clear Last pick.  2: Clear all picks.  3: Stretched.
	///	4: Pick on syn.  5: Pick on WT.  6: Undo.  7: Redo
	void Interact(int iSta);

	QPolygonF GetStretchPairs();

protected:
	virtual void mousePressEvent(QMouseEvent *) override;

	virtual void mouseMoveEvent(QMouseEvent *) override;

	void calCurvePath(CXWellCurve *, QPainterPath&, qreal x);

	void calCurvePath(double *, int iNumSample, double dSTime, double dStep, QPainterPath&, qreal x);

	QPolygonF calATrace(qreal x, float *pData, int iNumSample, QVector<QPolygon>&, double dSTime = -999.25, double dStep = 0.);

	void updateDTLines();

	virtual void paintEvent(QPaintEvent *pPaintEvent) override;

	//	Time and TVD anno.
	void drawAnno();

	//	Log curves.
	void drawCurves();

	//	Syn & real traces.
	void drawTraces();

	void drawStretchLines();

	int snap(int, bool bSyn = true);
	void findKP(int, bool bSyn, int& i1, qreal& dV1, int& i2, qreal& dV2);	//	Find keen point nearby.

	CXDlgWellTie*			m_pDlg;

	CXSeismicDataVolume*	m_pDV = NULL;
	CXWell*					m_pWell;

	float					m_fVScale = 1.;

	SLayout					m_sLayout;

	QPainterPath			m_acPath;
	QPainterPath			m_denPath;
	QPainterPath			m_rcPath;
	QLineF					m_dtI;
	QPolygonF				m_dtC;
	QPolygonF				m_driLine;

	int						m_iDTSTime;
	int						m_iDTETime;

	int						m_iSSynTime = -999;
	int						m_iESynTime;
	QRectF					m_recCorr;

	QPolygonF				m_SynPoly;
	QVector<QPolygon>		m_vecSynPolygon;
	QPolygonF				m_WTPoly;
	QVector<QPolygon>		m_vecWTPolygon;
	QVector<QPolygonF>		m_vecSecPoly;
	QVector<QPolygon>		m_vecSecPolygon;

	//	Below for interact on Syn & WT.
	int						m_iSta = 0;
	bool					m_bPeak;			//	Whether on peak of the left track.
	QVector<QLineF>			m_vecSynLines;
	QVector<QLineF>			m_vecWTLines;
	QPointF					m_pos;
};
