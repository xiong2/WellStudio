#ifndef _CXWellPATH_H__
#define _CXWellPATH_H__

#include "xdata_global.h"
#include "xobject.h"
#include "xglobal.h"
#include <QVector3D>
#include <QMutex>
///@brief	The class used to represent a well bore.
///@author	Xiong Xiong
///@date	Mar, 2014
///@see		
struct XDATA_EXPORT CXPoint3
{
	double x;
	double y;
	double z;
};
class XDATA_EXPORT CXWellPath: public CXObject
{
public:
	CXWellPath();
	CXWellPath(double dX, double dY, double dZ = 0.);
	~CXWellPath();

	//	Return the X, Y coordinate of the well.
	void GetWellPosition(double& dX, double& dY);

	//	set the X, Y coordinate of the well.
	void SetWellPosition(double dX, double dY);

	//	Populate the data.
	void ResetData(double* pData, unsigned int iNumber, double *pMDData = NULL);

	//	Get top and bottom depth (SSTVD)
	void GetDepth(double& dTopDepth, double& dBottomDepth);

	double* GetMdData();

	double*	GetTWTData();

	//	This will clear the twt data, force recalculate from TD.
	void CleanTWTData();

	//Map Attribute point To coordinate.
	bool MapAttrPointToCoord(double dMD, QVector3D &coord);
	bool MapAttrPointToCoord(double dMD, CXPoint3 &coord);

	double Md2Tvd(const float &md);

	double Tvd2Md(const float &tvd);

protected:
	virtual void _SetSelfDimension();

private:
	double *m_pMdData;		//	m_pData records X, Y, Z, this array is corresponding MD values.
	double *m_pTWT;			//	This array is correspoinding TWT values, if available.

	QMap<float, float> mapMd2Tvd; // »º´æ
	QMap<float, float> mapTvd2Md; // »º´æ
	QMutex mutex;
};

#endif
