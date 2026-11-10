#pragma once
#include <qgraphicsscene.h>
#include <qvector4d.h>
#include "xviewinfogather.h"

class CXSectionBuilder;
class CXPreStackGather;
class XViewGather;
class XItemFB;

class XSceneGather : public QGraphicsScene
{
public:
	XSceneGather(QObject *parent = NULL);
	~XSceneGather();

	void BuildSection(CXPreStackGather* pGather, int iShotID);

	void ClearSection();

	void InitOpenGLBuilder();

	//	Need not re-read data, but draw section again.
	void RedrawSection();

	void CreateFBItem(CXPreStackGather*);

	void RemoveFBItem();

	void RedrawFB();

	void SetView(XViewGather* pView)
	{
		m_pView = pView;
	}

	int GetCurrentShotID()
	{
		return m_iShotID;
	}

	void GetZInfo(float& fStartZ, float& fZInc)
	{
		fStartZ = m_fStartZ;
		fZInc = m_fZInc;
	}

	void GetSectionSize(int& iWidth, int& iHeight)
	{
		iWidth = m_iTraceNum;
		iHeight = m_iSampleNum;
	}

	void GetCanvasSize(int& iWidth, int& iHeight);

	CXViewInfoGather* GetViewInfo()
	{
		return &m_viewInfo;
	}

	void UpdateROI(float fLeft, float fRight, float fBottom, float fTop);

protected:
	virtual void drawBackground(QPainter * painter, const QRectF & rect) override;

	void calVI();
	void calVA();

	void calWiggleData(float* pData);

	XViewGather*			m_pView = nullptr;
	CXSectionBuilder*		m_pBuilder = nullptr;
	QVector4D				m_colors[256];

	XItemFB*				m_pItemFB = nullptr;

	int						m_iShotID = -1;
	int						m_iTraceNum = 0;
	int						m_iSampleNum = 0;

	float					m_fStartZ = -999.25;
	float					m_fZInc = 0.;

	float*					m_pData = nullptr;
	unsigned int*			m_pImgData = nullptr;
	std::vector<int>		m_vecAreaCount;
	float					m_fDMin = 99999.;
	float					m_fDMax = -99999;

	CXViewInfoGather		m_viewInfo;
};