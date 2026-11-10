#ifndef _GSTHREADSURFACECURVATURE_H__
#define _GSTHREADSURFACECURVATURE_H__

#include <qvector.h>
#include "xbasethread.h"
#include "xdata_global.h"

class CX3DHorizon;
class CXSeismicUTMTool;

class XDATA_EXPORT GSThreadSurfaceCurvature: public CXBaseThread
{
public:
	GSThreadSurfaceCurvature(CX3DHorizon *, QVector<int> vecPara);
	~GSThreadSurfaceCurvature();

	QVector<CX3DHorizon *> GetOutputHorizons()
	{
		return m_vecOutputHor;
	}

	QStringList GetAttributesName()
	{
		return m_sListAtt;
	}

	static QStringList	m_sListAtt;		//	All candidate attributes.

protected:
	virtual void RunThread() override;
	bool calculate();

	void createOutputHor();
	bool prepareInputData();

	bool getLineBuffer(int iIndex, int nWinNI);
	bool calcOneLineCoef(int iIndex, int nWinNI, int nWinNJ, CXSeismicUTMTool* pUTM);
	bool quadSurfaceFitting(unsigned int n, double* pOneCoef);
	void calcOneLineCurvature(float* pData, int nType);

	int		m_nI, m_nJ;			//	Size of the surface.

	float* m_pInputData;
	float* m_pOutputData;
	float* m_pWinBuff;
	bool* m_pValidMap;

	float** m_p2DLineData;	

	double *m_pX, *m_pY, *m_pZ;

	double** m_pA;
	double** m_pAInv;
	double** m_p2DTmp;
	double** m_p2DCoeff;

	double* m_pB;
	double* m_pEigenValue;
	double* m_p1DTmp;

	CX3DHorizon*			m_pHorizon;
	int						m_nWinNI, m_nWinNJ;
	QVector<int>			m_vecAttType;
	QVector<CX3DHorizon *>	m_vecOutputHor;
};

#endif