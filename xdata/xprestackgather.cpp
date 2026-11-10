#include <QFile>
#include <qmessagebox.h>
#include "xprestackgather.h"
#include "xobjectfactory.h"
#include "xglobal.h"
#include "xdataconvertor.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXPreStackGather)
EXPrestackGather
END_REGISTER_OBJECT_TO_FACTORY(CXPreStackGather)

CXPreStackGather::CXPreStackGather() : CXObject()
{
	SetObjectType(EXPrestackGather);
	SetIconName("Prestack3D.png");
}

CXPreStackGather::CXPreStackGather(QString strName) : CXObject(strName)
{
	SetObjectType(EXPrestackGather);
	SetIconName("Prestack3D.png");
}

QStringList CXPreStackGather::GetDescription()
{
	QStringList strList;

	int iStart, iLast, iNum;
	GetShotIDRange(iStart, iLast, iNum);
	QList<qreal>* listPoints = GetOneShotPoints(iStart);

	strList << "Shot number range:" << QString::number(iStart) + " to " + QString::number(iLast);
	strList << "Number of Shots:" << QString::number(iNum);
	strList << "Number of Detector per Shot:" << QString::number((listPoints->size() - 5) / 4);

	return strList;
}

void CXPreStackGather::GetShotIDRange(int& iStart, int& iLast, int& iNumber)
{
	iStart = iLast = iNumber = 0;
	if (m_mapPoints.isEmpty())
		LoadData();

	if (m_mapPoints.isEmpty())
		return;

	QList<int> listKeys = m_mapPoints.keys();
	iNumber = listKeys.size();
	iStart = listKeys.front();
	iLast = listKeys.back();
}

void CXPreStackGather::FindNearbyShot(int& iShot)
{
	if (m_mapPoints.isEmpty())
		LoadData();

	if (m_mapPoints.isEmpty())
	{
		iShot = -1;
		return;
	}

	QList<int> listKeys = m_mapPoints.keys();
	int iStart = listKeys.front();
	int iLast = listKeys.back();

	if (iShot < iStart)
	{
		iShot = iStart;
		return;
	}
	else if (iShot > iLast)
	{
		iShot = iLast;
		return;
	}

	while (!listKeys.contains(iShot))
	{
		iShot++;
	}
}

QList<int> CXPreStackGather::GetShotList()
{
	if (m_mapPoints.size() == 0)
		LoadData();

	return m_mapPoints.keys();
}

QList<qreal>* CXPreStackGather::GetOneShotPoints(int iShotID, bool bCreate)
{
	if (m_mapPoints.size() == 0)
		LoadData();

	if (!m_mapPoints.contains(iShotID))
	{
		QList<qreal> listBlank;

		if (!bCreate)
			return nullptr;
		else
			m_mapPoints.insert(iShotID, listBlank);
	}
	return &m_mapPoints[iShotID];
}

bool CXPreStackGather::GetOneShotDimension(int iShotID, int& iTraceNum, int& iSampleNum)
{
	if (m_mapPoints.size() == 0)
		LoadData();

	if (m_mapPoints.contains(iShotID))
	{
		iTraceNum = (m_mapPoints.value(iShotID).size() - 5) / 4;
		iSampleNum = m_iZNum;

		//iTraceNum = iTraceNum >500 ? 500 : iTraceNum;

		return true;
	}

	return false;
}

bool CXPreStackGather::ReadOneShot(int iShotID, float* pData)
{
	if (m_mapPoints.size() == 0)
		LoadData();

	if (!m_mapPoints.contains(iShotID))
		return false;

	QList<qreal> listP = m_mapPoints[iShotID];

	QFile qFile(m_sListSEGY[(int)listP[0]]);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(NULL, "Read SEGY File", "Can not open the SEGY file: " + m_sListSEGY[(int)listP[0]] + " to read!");
		return false;
	}

	int iTraceLen = m_iZNum * 4, iTraceNum = (listP.size() - 5) / 4;

	//iTraceNum = iTraceNum > 500 ? 500 : iTraceNum;

	if (m_iDataType == 3)
		iTraceLen = m_iZNum * 2;
	else if (m_iDataType == 4)
		iTraceLen = m_iZNum;
	char *pBuff = new char[iTraceLen];

	qFile.seek((qint64)listP[1]);
	for (int i = 0; i < iTraceNum; i++)
	{
		qFile.seek(qFile.pos() + 240);
		qFile.read(pBuff, iTraceLen);
		ConvertOneTrace(pData, pBuff, m_iDataType, m_iZNum, m_bDataFlip);

		pData += m_iZNum;
	}

	return true;
}

bool CXPreStackGather::ReadOneShotFB(int iShotID, float* pData)
{
	if (m_mapPoints.size() == 0)
		LoadData();

	if (!m_mapPoints.contains(iShotID))
		return false;

	QList<qreal> listP = m_mapPoints[iShotID];
	int i, iTraceNum = (listP.size() - 5) / 4;
	for (i = 0; i < iTraceNum; i++)
	{
		pData[i] = (float)listP[5 + i * 4 + 3];
	}

	return true;
}

bool CXPreStackGather::SerializeData(CXArchive &ar)
{
	if (ar.IsSaving())
	{
		ar << m_fStartZ;
		ar << m_fZInc;
		ar << m_iZNum;
		ar << m_iDataType;
		ar << m_bDataFlip;
		ar << m_sListSEGY;
	}
	else
	{
		ar >> m_fStartZ;
		ar >> m_fZInc;
		ar >> m_iZNum;
		ar >> m_iDataType;
		ar >> m_bDataFlip;
		ar >> m_sListSEGY;
	}

	return true;
}

void CXPreStackGather::PopulateSEGYInfo(float fStartZ, float fZInc, int iZNum, int iDataType, bool bDataFlip)
{
	m_fStartZ = fStartZ;
	m_fZInc = fZInc;
	m_iZNum = iZNum;
	m_iDataType = iDataType;
	m_bDataFlip = bDataFlip;
}

int CXPreStackGather::AddOneSEGYFile(QString sFile)
{
	m_sListSEGY << sFile;
	return m_sListSEGY.size() - 1;
}

void CXPreStackGather::_WriteData()
{
	if (m_mapPoints.isEmpty())
		return;

	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;

	QDataStream stream(&qFile);
	int i, nShots;
	QList<int> listKeys = m_mapPoints.keys();
	nShots = listKeys.size();
	stream << nShots;	//	First int is the number of shots.

	for (i = 0; i < nShots; ++i)
	{
		QList<qreal>& listPoints = m_mapPoints[listKeys[i]];
		stream << listKeys[i];				//	Shot ID.
		stream << listPoints.size();		//	Number of trace for this shot + 1.
		foreach(qreal point, listPoints)
		{
			stream << point;				//	Each point's coordinate, first is the shot, others are receiver.
		}
	}

	qFile.close();
}

void CXPreStackGather::_SetSelfDimension()
{
	if (m_mapPoints.isEmpty())
		LoadData();

	double dXMin = 999999999., dXMax = 0, dYMin = 9999999999, dYMax = 0,
		dZMin = 99999999999, dZMax = -9999999999999;

	//	Iterate all points.
	QMapIterator<int, QList<qreal> > it(m_mapPoints);
	while (it.hasNext())
	{
		it.next();
		QList<qreal> listP = it.value();
		for (int i = 5; i < listP.size(); i += 4)
		{
			dXMin = dXMin < listP[i] ? dXMin : listP[i];
			dXMax = dXMax > listP[i] ? dXMax : listP[i];
			dYMin = dYMin < listP[i + 1] ? dYMin : listP[i + 1];
			dYMax = dYMax > listP[i + 1] ? dYMax : listP[i + 1];
			dZMin = dZMin < listP[i + 2] ? dZMin : listP[i + 2];
			dZMax = dZMax > listP[i + 2] ? dZMax : listP[i + 2];
		}
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

void CXPreStackGather::_ReadData()
{
	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	QDataStream stream(&qFile);
	_freeMemory();

	int i, j, nShots, iShotID, nPoints;
	stream >> nShots;
	if (nShots == 0)
	{
		qFile.close();
		return;
	}

	for (i = 0; i < nShots; i++)
	{
		stream >> iShotID;
		stream >> nPoints;

		QList<qreal> listPoints;
		qreal point;
		for (j = 0; j < nPoints; j++)
		{
			stream >> point;
			listPoints.append(point);
		}

		m_mapPoints.insert(iShotID, listPoints);
	}

	qFile.close();
}