#include "xfaultsticks.h"
#include "xobjectfactory.h"
#include "xglobal.h"
#include "xseismicutmtool.h"
#include <QFile>
#include <qpoint.h>

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXFaultSticks)
EXFaultSticks
END_REGISTER_OBJECT_TO_FACTORY(CXFaultSticks)

CXFaultStick::CXFaultStick()
{
	m_pData			= NULL;
	m_pTraceNumber	= NULL;
	m_iNumPoint		= 0;

	m_lineID		= QUuid();
	m_iSecNumber	= -1;
	m_eFSType		= eFTRandom;
}

CXFaultStick::~CXFaultStick()
{
	if(m_pData)
		delete []m_pData;

	if (m_pTraceNumber)
		delete[]m_pTraceNumber;

	m_vecPoints.clear();
}

bool CXFaultStick::ResetData(double* pData, unsigned int iNumPoint, EFaultStickType eType, QUuid lineID, int iSecNumber, int* pTraceNumber)
{
	if (iNumPoint < 2)
		return false;

	if(m_pData)
		delete m_pData;
	if (m_pTraceNumber)
		delete m_pTraceNumber;
	m_vecPoints.clear();

	m_pData			= pData;
	m_iNumPoint		= iNumPoint;
	m_eFSType		= eType;
	m_lineID		= lineID;
	m_iSecNumber	= iSecNumber;
	m_pTraceNumber	= pTraceNumber;

	for (int i = 0; i < iNumPoint; i++)
	{
		m_vecPoints.emplace_back(pData[3 * i], pData[3 * i + 1], pData[3 * i + 2]);
	}

	return true;
}

void CXFaultStick::CheckStickType(CXSeismicUTMTool *pUTM)
{
	m_eFSType = eFTRandom;
	m_iSecNumber = -1;
	if (m_pTraceNumber)
	{
		delete[]m_pTraceNumber;
		m_pTraceNumber = NULL;
	}

	//	Stick on random section need not more check.
	if (!m_lineID.isNull())
	{
		return;
	}

	bool bNotInline = false, bNotXline = false;
	int i, iInline1, iXline1, iInline2, iXline2;
	pUTM->XYToLine(m_pData[0], m_pData[1], iInline1, iXline1);
	for (i = 1; i < m_iNumPoint; i++)
	{
		pUTM->XYToLine(m_pData[3 * i], m_pData[3 * i + 1], iInline2, iXline2);
		if (iInline2 != iInline1)
			bNotInline = true;
		if (iXline2 != iXline1)
			bNotXline = true;

		if (bNotInline && bNotXline)
			break;
	}

	if (!bNotInline)
	{
		//	The stick on inline!
		m_eFSType = eFTInline;
		m_iSecNumber = iInline1;

		m_pTraceNumber = new int[m_iNumPoint];
		for (i = 0; i < m_iNumPoint; i++)
		{
			pUTM->XYToLine(m_pData[3 * i], m_pData[3 * i + 1], iInline2, iXline2);
			m_pTraceNumber[i] = iXline2;
		}
	}
	else if (!bNotXline)
	{
		//	The stick on xline
		m_eFSType = eFTCrossline;
		m_iSecNumber = iXline1;

		m_pTraceNumber = new int[m_iNumPoint];
		for (i = 0; i < m_iNumPoint; i++)
		{
			pUTM->XYToLine(m_pData[3 * i], m_pData[3 * i + 1], iInline2, iXline2);
			m_pTraceNumber[i] = iInline2;
		}
	}
}

double* CXFaultStick::GetXYZData(unsigned int& iNumPoint)
{
	iNumPoint = m_iNumPoint;
	return m_pData;
}

std::vector<XPoint>::iterator CXFaultStick::begin()
{
	return m_vecPoints.begin();
}

std::vector<XPoint>::const_iterator CXFaultStick::begin() const
{
	return m_vecPoints.cbegin();
}

std::vector<XPoint>::iterator CXFaultStick::end()
{
	return m_vecPoints.end();
}

std::vector<XPoint>::const_iterator CXFaultStick::end() const
{
	return m_vecPoints.cend();
}

size_t CXFaultStick::PointsNum() const
{
	return m_vecPoints.size();
}

void CXFaultStick::Clear()
{
	m_vecPoints.clear();
}

bool CXFaultStick::IsEmpty()
{
	return m_vecPoints.empty();
}

const XPoint& CXFaultStick::First() const
{
	return m_vecPoints.front();
}

const XPoint& CXFaultStick::Last() const
{
	return m_vecPoints.back();
}

QPointF CXFaultStick::AvgXY() const
{
	double sumX = 0.0;
	double sumY = 0.0;

	for (auto&& p : m_vecPoints)
	{
		sumX += p.x;
		sumY += p.y;
	}

	return QPointF(sumX / m_vecPoints.size(), sumY / m_vecPoints.size());
}

QDataStream& operator<<(QDataStream& stream, const CXFaultStick& stick)
{
	size_t size = stick.m_vecPoints.size();
	stream << size;

	for (size_t i = 0; i != size; ++i)
	{
		const auto& xyz = stick.m_vecPoints.at(i);
		stream << xyz.x << xyz.y << xyz.z;
	}

	return stream;
}

QDataStream& operator>>(QDataStream& stream, CXFaultStick& stick)
{
	size_t size;
	stream >> size;

	stick.Clear();
	for (size_t i = 0; i != size; ++i)
	{
		double dX, dY, dZ;
		stream >> dX >> dY >> dZ;
		stick.m_vecPoints.emplace_back(dX, dY, dZ);
	}

	return stream;
}

CXFaultSticks::CXFaultSticks(QString strName, QUuid surveyID): CXObject(strName)
{
	SetObjectType(EXFaultSticks);
	SetIconName("Fault.png");
	m_surveyID = surveyID;
}

void CXFaultSticks::_freeMemory()
{
	for(int i = 0; i < m_listSticks.size(); i++)
		delete m_listSticks.at(i);

	m_listSticks.clear();
}

bool CXFaultSticks::SerializeData(CXArchive& ar)
{
	CXObject::SerializeData(ar);
	if (ar.IsSaving())
	{
		ar << m_surveyID;
	}
	else
	{
		ar >> m_surveyID;
	}

	return true;
}

void CXFaultSticks::_WriteData()
{
	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
	return;

	QDataStream stream(&qFile);
	int i, j, nSticksNum;
	nSticksNum = m_listSticks.size();
	stream<<nSticksNum;
		
	for (i = 0; i < nSticksNum; ++i)
	{
		unsigned int iNumPoint;
		double* pData = m_listSticks[i]->GetXYZData(iNumPoint);
		stream << iNumPoint;
		if (iNumPoint == 0)
			continue;

		stream.writeRawData((char *)pData, sizeof(double) * 3 * iNumPoint);

		j = (int)(m_listSticks[i]->GetStickType());
		stream << j;
		stream << m_listSticks[i]->GetLineID();
		stream << m_listSticks[i]->GetSecNumber();
		int *pTraceNumber = m_listSticks[i]->GetTraceNumber();
		if (pTraceNumber)
			stream.writeRawData((char *)pTraceNumber, sizeof(int) * iNumPoint);
	}

	qFile.close();
}

void CXFaultSticks::_ReadData()
{
	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	QDataStream stream(&qFile);
	_freeMemory();

	int i, j, nSticksNum, iSecNumber;
	QUuid lineID;

	stream >> nSticksNum;
	for (i = 0; i < nSticksNum; i++)
	{
		unsigned int iNumPoint;
		stream >> iNumPoint;
		if (iNumPoint == 0)
			continue;

		double *pXYZData = new double[3 * iNumPoint];
		stream.readRawData((char *)pXYZData, iNumPoint * 3 * sizeof(double));
		stream >> j;
		stream >> lineID;
		stream >> iSecNumber;

		int *pTraceNumber = NULL;
		if (iSecNumber != -1)
		{
			pTraceNumber = new int[iNumPoint];
			stream.readRawData((char *)pTraceNumber, iNumPoint * sizeof(int));
		}

		CXFaultStick *pStick = new CXFaultStick;
		pStick->ResetData(pXYZData, iNumPoint, (EFaultStickType)j, lineID, iSecNumber, pTraceNumber);

		m_listSticks << pStick;
	}

	qFile.close();
}

QStringList CXFaultSticks::GetDescription()
{
	if (m_listSticks.isEmpty())
		LoadData();

	QStringList strList;

	if(::UsingChinese())
	{
		strList<<GetTr("¶Ï²ã¶ÎÊýÄ¿")<<QString::number(m_listSticks.size());
	}
	else
	{
		strList<<"Number of sticks"<<QString::number(m_listSticks.size());
	}

	return strList;
}

void CXFaultSticks::_SetSelfDimension()
{
	if (m_listSticks.isEmpty())
		LoadData();

	int i, j, iSize = m_listSticks.size();
	if(iSize == 0)
		return;

	//sortSticks();

    double dXMin = -999., dXMax = 0.0, dYMin = 0.0, dYMax = 0.0, dZMin = 0.0, dZMax = 0.0;

	for(i = 0; i < iSize; i++)
	{
		unsigned int iNum;
		double *pData;
		pData = m_listSticks[i]->GetXYZData(iNum);

		if(dXMin == -999.)
		{
			//	First stick.
			dXMin = dXMax = pData[0];
			dYMin = dYMax = pData[1];
			dZMin = dZMax = pData[2];
		}

		for(j = 1; j < iNum; j++)
		{
			dXMin = dXMin < pData[3 * j] ? dXMin : pData[3 * j];
			dXMax = dXMax > pData[3 * j] ? dXMax : pData[3 * j];
			dYMin = dYMin < pData[3 * j + 1] ? dYMin : pData[3 * j + 1];
			dYMax = dYMax > pData[3 * j + 1] ? dYMax : pData[3 * j + 1];
			dZMin = dZMin < pData[3 * j + 2] ? dZMin : pData[3 * j + 2];
			dZMax = dZMax > pData[3 * j + 2] ? dZMax : pData[3 * j + 2];
		}
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

//Get all sticks belong to a specified section.
void CXFaultSticks::GetSticksOnSection(int iSectionNum, EXSectionType eSectionType, QList<CXFaultStick *>& listStick)
{
	EFaultStickType eType = eFTRandom;
	if (eSectionType == eInlineSection)
		eType = eFTInline;
	else if (eSectionType == eCrosslineSection)
		eType = eFTCrossline;
	else
		return;

	if (m_listSticks.isEmpty())
		LoadData();

	foreach(CXFaultStick *pStick, m_listSticks)
	{
		if (pStick->GetStickType() == eType && pStick->GetSecNumber() == iSectionNum)
			listStick << pStick;
	}
}

//@brief Get all sticks belong to a specified random section.
void CXFaultSticks::GetSticksOnSection(QUuid sectionID, QList<CXFaultStick *>& listStick)
{
	if (m_listSticks.isEmpty())
		LoadData();

	foreach(CXFaultStick *pStick, m_listSticks)
	{
		if (pStick->GetStickType() == eFTRandom && pStick->GetLineID() == sectionID)
			listStick << pStick;
	}
}

//@brief Get all sticks intersect to a specified section.
void CXFaultSticks::GetSticksIntersectSection(int iSectionNum, EXSectionType eSectionType, QList<QPointF>& listPoint, QList<CXFaultStick *>& listStick)
{
	EFaultStickType eType = eFTRandom;
	if (eSectionType == eInlineSection)
		eType = eFTCrossline;
	else if (eSectionType == eCrosslineSection)
		eType = eFTInline;
	else
		return;

	if (m_listSticks.isEmpty())
		LoadData();

	foreach(CXFaultStick *pStick, m_listSticks)
	{
		if (pStick->GetStickType() != eType)
			continue;

		unsigned int iNumPoints;
		double *pXYZData = pStick->GetXYZData(iNumPoints);
		int *pTraceNumber = pStick->GetTraceNumber();
		if (!pXYZData || !pTraceNumber)
			continue;

		for (int i = 0; i < iNumPoints - 1; i++)
		{
			if (pTraceNumber[i] == pTraceNumber[i + 1] && pTraceNumber[i] == iSectionNum)
			{
				listPoint << QPointF(qreal(pStick->GetSecNumber()), pXYZData[3 * i + 2]);
				listStick << pStick;

				continue;
			}

			if ((iSectionNum - pTraceNumber[i]) * (iSectionNum - pTraceNumber[i + 1]) >= 0)
				continue;

			qreal dY = pXYZData[3 * i + 2] + (pXYZData[3 * i + 5] - pXYZData[3 * i + 2]) * (iSectionNum - pTraceNumber[i]) / (pTraceNumber[i + 1] - pTraceNumber[i]);
			listPoint << QPointF(qreal(pStick->GetSecNumber()), dY);
			listStick << pStick;
		}
	}
}

//	Add one stick, if it not already exist.
void CXFaultSticks::AddOneStick(CXFaultStick *pStick)
{
	if (!m_listSticks.contains(pStick))
	{
		m_listSticks.append(pStick);
		SetNeedCalcDimension();
		SetModifiedFlag();
	}
}

//	Remove on stick, if it exists.
void CXFaultSticks::RemoveOneStick(CXFaultStick *pStick)
{
	if (m_listSticks.contains(pStick))
	{
		m_listSticks.removeOne(pStick);
		SetNeedCalcDimension();
	}
}

uint qHash(const QPointF& p, uint seed = 0)
{
	return qHash(qMakePair(p.x(), p.y()), seed);
}

void CXFaultSticks::sortSticks()
{
	//	First we create a hash of the sticks, with the key of the mid point of each stick's first and last point.
	QHash<QPointF, CXFaultStick *> hashSticks;
	unsigned int iNumPoint, iCount = 0;
	double *pStickData;
	QPointF avMidPoint, remotePoint;
	foreach(CXFaultStick *pStick, m_listSticks)
	{
		pStickData = pStick->GetXYZData(iNumPoint);
		QPointF midPoint(float(pStickData[0] + pStickData[3 * iNumPoint - 3]), float(pStickData[1] + pStickData[3 * iNumPoint - 2])) ;
		avMidPoint += midPoint;
		hashSticks.insert(midPoint, pStick);
		iCount++;
	}

	//	The approximately average middle point of all sticks.
	if (iCount <= 0)
		return;
	avMidPoint /= iCount;

	//	Then we calculate each stick's distance to this middle point, to find the most remote one.
	float fD = 0;
	QHash<QPointF, CXFaultStick *>::iterator it = hashSticks.begin();
	while (it != hashSticks.end())
	{
		QPointF point = it.key();
		float fDis = (point.x() - avMidPoint.x()) * (point.x() - avMidPoint.y()) + (point.y() - avMidPoint.y()) * (point.x() - avMidPoint.y());

		if (fDis > fD)
		{
			fD = fDis;
			remotePoint = point;
		}

		it++;
	}

	it = hashSticks.begin();

	QMap<float, CXFaultStick *> mapSticks;
	while (it != hashSticks.end())
	{
		QPointF point = it.key();
		fD = (point.x() - remotePoint.x()) * (point.x() - remotePoint.y()) + (point.y() - remotePoint.y()) * (point.x() - remotePoint.y());
		mapSticks.insert(fD, it.value());
		it++;
	}

	//	Save the sticks in the map (sorted) back to the member list.
	m_listSticks.clear();
	m_listSticks = mapSticks.values();
}

//	Add for GSM
CXFaultStick* CXFaultSticks::GetStick(size_t index)
{
	if (m_listSticks.isEmpty())
		LoadData();

	if (index >= m_listSticks.size())
		return nullptr;
	else
		return m_listSticks.at(index);
}

size_t CXFaultSticks::GetStickNum()
{
	if (m_listSticks.isEmpty())
		LoadData();

	return m_listSticks.size();
}
