#include <qdebug.h>
#include "xcppointsmanager.h"
#include "xcppoints.h"
 
QVector<CXCPPoints *> CXCPPointsManager::m_vecCPPoints;

CXCPPoints* CXCPPointsManager::GetCPPoints(QUuid objectID)
{
	for (int i = 0; i < m_vecCPPoints.size(); i++)
	{
		if (m_vecCPPoints[i]->GetObjectID() == objectID)
			return m_vecCPPoints[i];
	}

	return NULL;
}

CXCPPoints* CXCPPointsManager::GetCPPoints(QUuid rangeID, QUuid CPObjectID)
{
	for (int i = 0; i < m_vecCPPoints.size(); i++)
	{
		if (m_vecCPPoints[i]->GetRangeID() == rangeID && m_vecCPPoints[i]->GetCPObjectID() == CPObjectID)
			return m_vecCPPoints[i];
	}

	return NULL;
}

QList<CXCPPoints *> CXCPPointsManager::GetCPPointsOfPolygon(QUuid rangeID)
{
	QList<CXCPPoints *> listPoints;
	for (int i = 0; i < m_vecCPPoints.size(); i++)
	{
		if (m_vecCPPoints[i]->GetRangeID() == rangeID)
			listPoints << m_vecCPPoints[i];
	}

	return listPoints;
}

QList<CXCPPoints *> CXCPPointsManager::GetCPPointsOfObject(QUuid CPObjectID)
{
	QList<CXCPPoints *> listPoints;
	for (int i = 0; i < m_vecCPPoints.size(); i++)
	{
		if (m_vecCPPoints[i]->GetCPObjectID() == CPObjectID)
			listPoints << m_vecCPPoints[i];
	}

	return listPoints;
}

void CXCPPointsManager::AddCPPoints(CXCPPoints *pCPPoints)
{
	if (GetCPPoints(pCPPoints->GetRangeID(), pCPPoints->GetCPObjectID()))
	{
		qDebug() << "Something error, the CPPoints already exist!";
		return;
	}

	m_vecCPPoints.append(pCPPoints);
}