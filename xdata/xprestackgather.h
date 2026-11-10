#ifndef _CXPRESTACKGATHER_H__
#define _CXPRESTACKGATHER_H__

#include "xdata_global.h"
#include "xobject.h"
#include "xdef.h"

///@brief	The class provides data structure for recording shot/receiver location.
///@author	Xiong Xiong
///@date	Sep, 2017
class XDATA_EXPORT CXPreStackGather : public CXObject
{
public:
	CXPreStackGather();
	CXPreStackGather(QString strName);

	virtual QString GetTypeString() { return "PreStack Seismic Gather"; }
	virtual QStringList GetDescription();

	void GetShotIDRange(int& iStart, int& iLast, int& iNumber);

	QList<int> GetShotList();

	QList<qreal>* GetOneShotPoints(int iShotID, bool bCreate = false);

	void GetZInfo(float& fStartZ, float& fZInc)
	{
		fStartZ = m_fStartZ;
		fZInc = m_fZInc;
	}

	bool GetOneShotDimension(int iShotID, int& iTraceNum, int& iSampleNum);

	bool ReadOneShot(int iShotID, float* pData);

	bool ReadOneShotFB(int iShotID, float* pData);

	int AddOneSEGYFile(QString sFile);

	virtual bool SerializeData(CXArchive &ar);

	void PopulateSEGYInfo(float, float, int, int, bool);

	void FindNearbyShot(int&);

protected:
	virtual void _SetSelfDimension();
	virtual void _ReadData();
	virtual void _WriteData();
	virtual void _freeMemory()
	{
		m_mapPoints.clear();
	}

	//	Key is source point number.
	//	The first 5 numbers of the list is the source point's SEGY file Ind, start postion in SEGY file, x, y, z coords, follows are receivers' coord plus first break time.
	QMap<int, QList<qreal> >	m_mapPoints;	

	//	Below information need for reading data from SEGY.
	float	m_fStartZ;
	float	m_fZInc;
	int		m_iZNum;
	int		m_iDataType;
	bool	m_bDataFlip;

	QStringList		m_sListSEGY;
};

#endif