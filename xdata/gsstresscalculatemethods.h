#ifndef _GSSTRESSCALCULATEMETHODS_H__
#define _GSSTRESSCALCULATEMETHODS_H__

#include "xdata_global.h"

class CXObject;
class CX3DHorizon;
class GSAnticline;
class GSStructure;
class GSStressParameters;
class GS3DHorizonFaultTraces;

class XDATA_EXPORT GSStressCalculateMethods
{
public:
	GSStressCalculateMethods(CX3DHorizon *pHor)
	{
		m_pHorizon = pHor;
	}

	QList<GSAnticline *> Calculate(bool bAnti, double dRR, double dLength, double dHeight, double dRadius, unsigned char *, unsigned char *);

	QVector<QVector<double> > SearchPoints(bool bAnti, double dHeight, double dRadius, unsigned char *, unsigned char *);

	QList<GSAnticline *> GenerateAnticlines(QVector<QVector<double> >, int iShape, GSStressParameters *);

	QList<GSAnticline *> RemoveAnticlinesByFaults(QList<GSAnticline *>, QList<GSStructure *>, double dLength);

	//	Used by John.
	QList<GSStructure *> CreateStructuresByFaults(GSStressParameters *);
	
	//	Used by Xiong.
	QList<GSStructure *> CreateStructuresByFaults(GSStressParameters *, QList<GS3DHorizonFaultTraces *>);

	QList<GSStructure *> StructuresAdjust(QList<GSStructure *>&, GSStressParameters *);

protected:
	QList<GSStructure *> mergeOverlapCapsules(QList<GSStructure *>, double dOverlap, double dAngle);

	QList<GSStructure *> removeOverlapPart(QList<GSStructure *>);

	QList<GSAnticline *> removeOverlapAnticlines(QList<GSAnticline *>, double dWidth = 2000, double dOverlapRatio = 0.3);

	///	Calculate one point on the isopach whether belong an anticline along one direction.
	bool calculateOnePoint(int i, int j, int iHStep, int iVStep, int iCell, float fHTh, bool bAnti);

	//	Expand the anticline points.
	void flatExpand(int i, int j, int iVStep, int iHStep, float fHTh, unsigned char *pBuff);

	//	From a seed point, find out points within one anticline by recursion function.
	void findAnticlinePoints(unsigned char *pData, unsigned char *pMap, int i, int j, QVector<double>&);

	//	To guarantee all the points has the same direction.
	void anticlinePointsDirectionFilter(unsigned char *, QVector<double>&, float fRadi);

	CX3DHorizon*	m_pHorizon;
};

#endif // !_GSSTRESSCALCULATEMETHODS_H__

