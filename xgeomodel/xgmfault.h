#ifndef XGMFAULT_H
#define XGMFAULT_H

#include "xgeomodel_global.h"
#include "xobject.h"
#include <vector>
#include "xgmpoint.h"
#include <qlist.h>

using std::vector;

class CXFaultSticks;


///@brief Data structure for pillars
class XGEOMODEL_EXPORT CXGMPillar : public vector<CXGMPoint>
{
public:
	CXGMPillar() {}
	~CXGMPillar() {}

	void SerializeData(CXArchive& ar, int nCount);

	void GetDimension(double& xmin, double& xmax, double& ymin, double& ymax, double& zmin, double& zmax);
};

///@brief Data structure for faults
class XGEOMODEL_EXPORT CXGMFault : public CXObject
{
public:
	CXGMFault(const QString& strName="");
	~CXGMFault();

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	virtual QStringList GetDescription();

	bool ExtractPillarFromSticks(CXFaultSticks* pSticks, double dDistance=150.);	

	///@brief Extend the data
	bool ExtendFault(double dDistance = 100.);

	///@brief 
	bool Intersect(CXGMFault* pOtherFault);

	///@brief Correct index after remove extension
	bool RearrageData(double dDistance = 50);

	///@brief Remove Extra pillars
	bool RemoveExtraPillars();

	///@brief Remove all existing connection info
	void RemoveConnectionInfo();

	///@brief Get pillars
	QList<CXGMPillar*>& GetPillars() {return m_listPillar;}

	///@brief Get intersection pillars
	QList<CXGMPillar*>& GetIntersectPillars() {return m_listIntersectPillar;}

	///@brief Get Intersection object ID
	QList<QUuid>& GetIntersectObjIDs() {return m_listIntersectID;}

	///@brief GetIntersection node index
	QList<std::vector<int> >& GetIntersectNodeIndex() {return m_listIntersectIndex;}


protected:
	virtual void _SetSelfDimension();

private:
	void _FreeMem();

private:
	QList<CXGMPillar*> m_listPillar;

	QList<QUuid> m_listIntersectID;

	QList<std::vector<int> > m_listIntersectIndex;

	QList<CXGMPillar*> m_listIntersectPillar;
	
};

#endif // RFGMFAULT_H
