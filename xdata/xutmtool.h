#ifndef XUTMTOOL_H
#define XUTMTOOL_H

#include "xdata_global.h"
#include "xarchive.h"


/**
*@class		CXUTMTool "rlutmtool.h"
*@brief		This class holds a regular 2-D grid's UTM.
*			This class holds a regular 2-D grid's UTM X and Y coordinate. 
*/
class XDATA_EXPORT CXUTMTool
{
public:
	///@brief	Constructor and destructor
	CXUTMTool();
	CXUTMTool(const CXUTMTool& other);
    virtual ~CXUTMTool();

	/**@brief	Initialize the size.
	*@param[in]	nI:	Size in I direction.
	*@param[in]	nJ:	Size in J direction.
	*/
	bool InitSize(int nI, int nJ);

	/**@brief	Intialize the coordinates by 3 input points, user should initialize size before call this function.
	*	This 3 points are not necessary the 3 corners, but should not belong to one beeline,
	*	unless the size of I or J is only 1, in which case only the frist 2 points be used.
	*/
	virtual bool InitCoordinates(int i0, int j0, double x0, double y0,
		int i1, int j1, double x1, double y1,
		int i2, int j2, double x2, double y2);

	///@brief	Is the input UTM compatible with current one?
	virtual bool IsCompatible(CXUTMTool *pUTM);

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	/**
	*@brief		Create a new UTM based on current one and input parameters.
	*@param[in]	i0:	The minimum I index of new one corresponding to current one (maybe negative).
	*@param[in]	j0: The minimum J index of new one corresponding to current one (maybe negative).
	*@param[in]	nI:	Size of I direction.
	*@param[in]	nJ:	Size of J direction.
	*@param[in]	nIInterval:	Step of I direction, 3 means skip 3 lines of each current grid's step, -2 means insert 2 new lines of each current grid's step.
	*@param[in]	nJInterval:	Step of J direction, 3 means skip 3 lines of each current grid's step, -2 means insert 2 new lines of each current grid's step.
	*return		The new created UTM.
	*/
    virtual CXUTMTool* GenerateNewUTM(int i0, int j0, int nI, int nJ, int nIInterval = 0, int nJInterval = 0);

	///@brief	Copy everything from the source UTM.
	virtual void Copy(CXUTMTool *pSourceUTM);

	///@brief	Get size in I direction.
	int GetNI() const { return m_nI; }

	///@brief	Get size in J direction.
	int GetNJ() const { return m_nJ; }

	///@brief	Input X, Y and get the corresponding I, J.
	///@return	Always can get I, J (maybe negative), so:
	///-true	The input X, Y locates inside the grid. 
	///-false	The input X, Y locates outside the grid.
	bool XYToIJ(double x, double y, int& i, int& j);

	bool XYToIJ(double x, double y, float &i, float &j );

	///@brief	Input i, j and get the corresponding X, Y.
	///@return	Always can get X, Y (input i, j maybe negative), so:
	///-true	The input I, J locates inside the grid. 
	///-false	The input I, J locates outside the grid.
	bool IJToXY(int i, int j, double& x, double&y) const;

	bool IJToXY2(double i,double j,double &x,double &y) const;

	///@brief	Get the interval in I direction.
	double GetIInterval() const;

	///@brief	Get the interval in J direction.
	double GetJInterval() const;	

	///@brief	Get the bounding box's corners coordinates.
	void GetDimensionRange(double& fXMin, double& fXMax, double& fYMin, double& fYMax);

	///@brief	Get the I direction, counter-clockwise with horizontal line, value: [0, 360)
	double GetIDirection();

	///@brief	Get the J direction, counter-clockwise with horizontal line, value: [0, 360)
	double GetJDirection();

	/// @brief	rescale the x and y
	void ChangeUnit(double factor);

	/// @brief Tell if two UTM's are equal
	///@return true if equal, false otherwise
	virtual bool Equals(CXUTMTool *pOther);

    /// @brief Tell if two UTM's intersect
    ///@return true if intersecting, false otherwise
    bool IsIntersecting(CXUTMTool *pOther) const;

	///	@brief	Get the delta increments of each cell.
	void GetDeltaIncrement(double& fDIX, double& fDIY, double& fDJX, double& fDJY)
	{
		fDIX = m_fDIX;
		fDIY = m_fDIY;
		fDJX = m_fDJX;
		fDJY = m_fDJY;
	}

	//	Cut the 1st 2 digits of the X coordinate if it's 8 digits. 
	void RemoveXStrip();

protected:
	//	To resize current UTMTool, but still compatible with original one.
	bool _resize(int i0, int j0, int ni, int nj, double iInc, double jInc);

	int	m_nI;		//	Number in I direction, range from 0 to m_nI - 1.
	int	m_nJ;		//	Number in J direction, range from 0 to m_nJ - 1.

	double			m_fX0;		//	X coordinate of original point (i = 0, j = 0).
	double			m_fY0;		//	Y coordinate of original point (i = 0, j = 0).

	double			m_fDIX;		//	Delta X caused by I crease 1.
	double			m_fDIY;		//	Delta Y caused by I crease 1.
	double			m_fDJX;		//	Delta X caused by J crease 1.
	double			m_fDJY;		//	Delta Y caused by J crease 1.
};

#endif // RLUTMTOOL_H
