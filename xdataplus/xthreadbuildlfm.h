#ifndef XTHREADBUILDLFM_H
#define XTHREADBUILDLFM_H

#include <vector>
#include <QBitArray>
#include "xbasethread.h"
#include "xdataplus_global.h"
#include "xseismicutmtool.h"

class CXParameterBuildLFM;
class CXLFMGeometry;
class CX3DHorizon;

/**
* @class CXThreadBuildLFM provided in the file "kethreadbuildlfm.h"
* @brief The Class provides a thread to build geometry of a low frequency model
*
* @author Yong Shu
* @date 11/19/2015
* @see
* @bug	No Known bugs so far
*/

class XDATAPLUS_EXPORT CXThreadBuildLFM : public CXBaseThread
{
public:
	///@brief Constructor
	CXThreadBuildLFM(CXParameterBuildLFM* pPara);

	///@brief Destructor
	virtual ~CXThreadBuildLFM();

	///@brief Get the strata-grid
	CXLFMGeometry* GetLFM() { return m_pLFM; }

protected:
	/// Reimplementation of run()
	virtual void RunThread();

private:
	// Initialization
	bool _Initialization();

	// Create strata model
	bool _CreateUTM();

	// Get valid map
	bool _GetValidMap();
	// Apply the boundary polygon
	bool _ApplyPolygon();

	// Get an array of data matrix
	bool _GetVecDataMatrix();

	// Set the index for input surface
	bool _SetInputSurfaceIndex();
	// Shift values
	void _ShiftTopAndBottomValues();

	// Set slice data
	bool _SetSliceData();
	// Create strata-grid
	bool _CreateStrataGrid();

	// smoothing
	bool _Smoothing(CX3DHorizon* pHorizon);

private:
	CXParameterBuildLFM* m_pPara;

	std::vector<CX3DHorizon*> m_vecInput3DHorizon;

	// polygon info
	unsigned int m_nPolygonDataNum;
	double* m_pPolygonData;

	CXSeismicUTMTool m_utmLFM;

	QBitArray m_bitMap;	
	
	float** m_2DRawData;
	int m_nRawNum;	

	float** m_p2DData;
	int m_nTotalSlice;

	//	Location of input horizon's indices among slices.
	QList<unsigned short> m_listSurfaceIndex;

	// output
	CXLFMGeometry* m_pLFM;
};

#endif // KETHREADBUILDLFM_H
