#ifndef XTHREADINTERSECTLFM_H
#define XTHREADINTERSECTLFM_H

#include <QList>
#include <vector>
#include <QMap>
#include "xbasethread.h"
#include "xdataplus_global.h"
#include "xvector3d.h"
#include "xseismicutmtool.h"

class CXWell;
class CXParameterLFMIntersecton;
class CXLFMUpscalingGeometry;
class CXObject;
class CXLFMGeometry;
class CXLFMCell;


/**
* @class CXThreadIntersectLFM provided in the file "kethreadintersectlfm.h"
* @brief The Class provides a thread to calculate intersection between well and low frequency model
*
* @author Yong Shu
* @date 11/23/2015
* @see
* @bug	No Known bugs so far
*/


class XDATAPLUS_EXPORT CXThreadIntersectLFM : public CXBaseThread
{
public:
	///@brief Constructor
	CXThreadIntersectLFM(CXParameterLFMIntersecton* pPara, CXObject* pParent);

	///@brief Destructor
	virtual ~CXThreadIntersectLFM();

	CXObject* GetOutputObj();

	static void CalculateOneCellXYZ(CXSeismicUTMTool& utm, double** p2DData, float fInvalid, int nI, int nJ, int nK, int i, int j, int k, double* X, double* Y, double* TopZ, double* BottomZ);

protected:
	///@brief Reimplementation of run()
	virtual void RunThread();

private:
	bool _Init();
	void _LockObj();
	void _CreateObj();
	bool _InitData();
	void _UpscaleAllWells();

	bool _PrepareOneWellData(CXWell* pWell);
	void _IntersectionOneSegment(const CXVector3D& p1, const CXVector3D& p2, int index);
	bool _UpscalingOneWellLog(int iWell);

	static int _GetZ(int iTop, int iMiddle, int iBottom, double** p2DData, double* Z, int dataIndex, float fInvalid, float fInvalidEPS);
	inline bool _IsBound(double* X, double* Y, double* TopZ, double* BottomZ, const CXVector3D& p1, const CXVector3D& p2);

private:
	CXLFMGeometry *m_pLFM; 

	std::vector<CXWell*> m_vecWell;
	
	CXParameterLFMIntersecton* m_pPara;

	std::vector<CXWell*> m_vecValidWell;

private:
	int m_nI, m_nJ, m_nK;

	CXSeismicUTMTool m_utm;

	CXLFMUpscalingGeometry* m_pUpscalingGeometry;

	std::vector<double> m_vecX, m_vecY, m_vecTWT, m_vecMD;
	int m_nLength;

	double** m_p2DGeoData;

	QMap<qint64, CXLFMCell*> m_mapIndexToCell;
};

#endif // KETHREADINTERSECTLFM_H
