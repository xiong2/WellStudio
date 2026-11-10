#pragma once
#include <qframe.h>

class CXSeismicDataVolume;
class CXWellTD;

class CXFrameWTAnno : public QFrame
{
public:
	CXFrameWTAnno(QWidget *parent = NULL);
	~CXFrameWTAnno();

	void SetType(int iType)
	{
		m_iType = iType;
	}

	void Populate(CXSeismicDataVolume *pDV, CXWellTD *pTD)
	{
		m_pDV = pDV;
		m_pTD = pTD;
	}

protected:
	virtual void paintEvent(QPaintEvent *pPaintEvent) override;

	int		m_iType = 0;	//	0~3 represents TWT, MD, TVD and SSTVD.
	CXSeismicDataVolume*	m_pDV = NULL;
	CXWellTD*				m_pTD = NULL;
};