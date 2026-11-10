#ifndef X2DSECTIONPROJECTOR_H
#define X2DSECTIONPROJECTOR_H

class CXSectionScene;
class CXWell;
class CXObject;
#include "xsectionwindow_global.h"

/*!
 *  @brief  The class offer functions of calculating the projection of seismic section.
 *  @author Xiong
 *  @date   2016-1
 *  @see
 */
class XSECTIONWINDOW_EXPORT CXSectionProjector
{
public:
	///	Use Scene
	CXSectionProjector(CXSectionScene *pScene);

	///	Use Section
	CXSectionProjector(CXObject *pSection);

	///	Return -1 means beyond the projection threhold, otherwise return the plane index. 
	int WellShouldBeDrawn(CXWell *, float fProjThrehold);

	///	Get the end's trace number of specified plane.
	bool GetEndTraceNumber(int iPlaneIDX, float& fLeftTrace, float& fRightTrace);

	///	Get a point's projection trace number on a plane.
	float GetSubPointTraceNumber(double dX, double dY, int iPlaneIDX);

private:
	//	Current section window showing how many plane.
	unsigned short getPlaneNumber();
	
	//	Get the end's coordinates of the given plane.
	bool getPlaneEnds(int iIDX, double& dLeftX, double& dLeftY, double& dRightX, double& dRightY);

	CXSectionScene*	m_pScene;
	CXObject*	m_pSection;
};

#endif