#pragma once
#include <qgraphicsscene.h>
#include <qvector4d.h>

class CXSeismicDataVolume;
class CXSectionBuilder;
class XItemPyRect;

class XScenePyramid : public QGraphicsScene
{
public:
	XScenePyramid(QObject *parent = NULL);
	~XScenePyramid();

	void ClearSection();

	void BuildSection(CXSeismicDataVolume *, int iDir, int iNo, int iAng, bool bFilter);
	void BuildSection(int iAng, bool bFilter);

	void HandleMouseEvent(QMouseEvent *);

	void InitializeRect(bool = true);

	void SetPolygon(QPolygonF);

	//	Get the polygon in IJ coordinate.
	QPolygonF GetPolygon()
	{
		return m_polygon;
	}

protected:
	virtual void drawBackground(QPainter * painter, const QRectF & rect) override;

	CXSectionBuilder*		m_pBuilder = nullptr;
	QVector4D				m_colors[256];
	unsigned int*			m_pImgData = nullptr;
	float*					m_pDataBuff = nullptr;
	float*					m_pDFiltered = nullptr;
	int						m_iImgWid = 0;
	int						m_iImgHei = 0;
	double					m_dMin;
	double					m_dSpan;

	XItemPyRect*			m_pRectItem = nullptr;
	QPolygonF				m_polygon;		//	Interesting region in IJ coordinate.
	double					m_dRatio = 1.;

};