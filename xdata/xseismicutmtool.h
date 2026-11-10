#ifndef _CXSeismicUTMTool_H__
#define _CXSeismicUTMTool_H__

#include "xdata_global.h"
#include "xutmtool.h"

/**
*@class		CXSeismicUTMTool "gmseismicutmtool.h"
*@brief		This class holds a seismic grid's UTM.
*			This class holds a seismic grid's UTM X and Y coordinate.  It will take over part of existing UTMTool's job.
*			Because the UTMTool class will be wiped out soon.  Inherit CXUTMTool, it add the Line/CDP number's relationship.
*			We use I of basic class represents inline, use J of basic class represnets crossline.
*@author	Xiong Xiong
*@date		Apr, 2014
*/
class XDATA_EXPORT CXSeismicUTMTool: public CXUTMTool
{
public:
	///@brief	Contructor, nothing initialized.
	CXSeismicUTMTool();
	CXSeismicUTMTool(const CXSeismicUTMTool& other);
	~CXSeismicUTMTool();

	///@brief	Initialize the size.
	bool InitSize(int iFirstInline, int iNumInline, int iInlineInc,
		int iFirstCrossline, int iNumCrossline, int iCrosslineInc);
		
	/**@brief	Intialize the coordinates by 3 input points, user should initialize size before call this function.
	*	This 3 points are not necessary the 3 corners, but should not belong to one beeline,
	*	unless the number of inline or crossline is only 1, in which case only the frist 2 points be used.
	*/
	virtual bool InitCoordinates(int inline0, int crossline0, double x0, double y0,
		int inline1, int crossline1, double x1, double y1,
		int inline2, int crossline2, double x2, double y2);

	///@brief		Create a new UTM based on current one and input parameters.
	CXSeismicUTMTool* GenerateNewUTM(int iFirstInline, int iFirstCrossline,
		int iNumInline, int iNumCrossline, int iInlineInc = 1, int iCrosslineInc = 1);

	///@brief	Resize the inline & crossline range, but not change the coordinate.
	///@param[in]	iFirstInline:		New start inline.
	///@param[in]	iFristCrossline:	New start crossline.
	///@param[in]	iNumInline:			New inline number.
	///@param[in[	iNumCrossline:		New crossline number.
	///@param[in]	iInlineInc:			New inline increament, default 0 means not changed.
	///@param[in]	iCrosslineInc:		New crossline increament, default 0 means not changed.
	bool Resize(int iFirstInline, int iFirstCrossline, int iNumInline, int iNumCrossline,
		int iInlineInc = 0, int iCrosslineInc = 0);

	///@brief	Merge the given UTM into current one. 
	bool MergeUTM(CXSeismicUTMTool& UTM);

	///@brief	Copy everything from the source UTM.
	virtual void Copy(CXUTMTool *pSourceUTM);

	///@brief	Standard way to save/load itself.
	virtual bool SerializeData(CXArchive& ar);

	///@brief	Is the input UTM seismically compatible with current one?
	virtual bool IsCompatible(CXUTMTool *pUTM);

	///@brief	Get number of inline.
	int GetInlineNum() { return m_nI; }

	///@brief	Get first inline.
	int GetFirstInline() const { return m_iFirstInline; }

	///@brief	Get last inline.
	int GetLastInline() const { return m_iFirstInline + m_iInlineInc * (m_nI - 1); }

	///@brief	Get inline increment.
	int GetInlineIncrement() const { return m_iInlineInc; }
		
	///@brief	Get number of crossline.
	int GetCrosslineNum() { return m_nJ; }

	///@brief	Get first crossline.
	int GetFirstCrossline() const { return m_iFirstCrossline; }

	///@brief	Get last crossline.
	int GetLastCrossline() const { return m_iFirstCrossline + m_iCrosslineInc * (m_nJ - 1); }

	///@brief	Get crossline increment.
	int GetCrosslineIncrement() const { return m_iCrosslineInc; }

	///@brief	Get the interval between 2 inline.
	double GetInlineInterval() const { return GetIInterval(); }

	///@brief	Get the interval between 2 crossline.
	double GetCrosslineInterval() const { return GetJInterval(); }

	///@brief	Get inline, crossline number from index.  
	///@return	Return false if outside the grid.
	bool IJToLine(int i, int j, int& iInline, int& iCrossline);

	///@brief	Get I, J index from inline, crossline number.
	///@return	Return false if outside the grid.
	bool LineToIJ(int iInline, int iCrossline, int& i, int& j) const;

	///@brief	Get I, J index from inline, crossline number.
	///@return	Return false if outside the grid.
	bool LineToIJ2(float fInline, float fCrossline, int& i, int& j) const;

	///@brief	Get inline, crossline number from X, Y.  
	///@return	Return false if outside the grid.
	bool XYToLine(double x, double y, int& iInline, int& iCrossline);

	///@brief	Get inline, crossline number from X, Y.  
	///@return	Return false if outside the grid.
	bool XYToLine(double x, double y, float& fInline, float& fCrossline);

	///@brief	Get X, Y coordinate from inline, crossline number.
	///@return	Return false if outside the grid.
	bool LineToXY(int iInline, int iCrossline, double& x, double& y) const;

	///@brief	Get the line range for convenient use.
	void GetLineNumRange(int& iFirstInline, int& iLastInline, int& iInlineInc,
		int& iFirstCrossline, int& iLastCrossline, int& iCrosslineInc);

	/// @brief Tell if two UTM's are equal
	///@return true if equal, false otherwise
	virtual bool Equals(CXUTMTool *pOther);

	///	@brief Get index of input inline/crossline.
	///	@return	-1 means the input inline/crossline not exactly within UTM.
	qint64 GetIndexOfOneNode(int iInline, int iCrossline);

	///@brief Tell if contains another UTM
	bool Contains(CXSeismicUTMTool* other);

	void ChangeCellSize(float);

	QPointF GetCenter();
	QList<QPointF> GetCorners();

private:
	int m_iFirstInline;			//	Line number of original point.
	int m_iFirstCrossline;		//	Crossline number of original point.

	int m_iInlineInc;			//	Inline increment.
	int m_iCrosslineInc;		//	Crossline increment.
};

#endif