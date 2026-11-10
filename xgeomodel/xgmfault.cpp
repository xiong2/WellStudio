#include "xgmfault.h"
#include "xobjectfactory.h"
#include <cassert>
#include "xfaultsticks.h"
#include <algorithm>
#include "xfunctiontemplate.h"
#include <cmath>
#include "xgmcurvefitting.h"
#include "xgmcubicspline.h"
#include "xgmutility.h"
#include "xglobal.h"
#include "xmathmacro.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXGMFault)
EXGMFault
END_REGISTER_OBJECT_TO_FACTORY(CXGMFault)


bool CompareTwoPointsByZ(const CXGMPoint& p1, const CXGMPoint& p2)
{
	return p1.m_dZ < p2.m_dZ;	
}

void CXGMPillar::SerializeData(CXArchive& ar, int nCount)
{
	if (ar.IsSaving())
	{
		int nSize = (int) size();
		assert(nSize == nCount);
		for (int i=0; i<nSize; ++i)
		{
			ar<<(*this)[i].m_dX;
			ar<<(*this)[i].m_dY;
			ar<<(*this)[i].m_dZ;
		}
	}
	else
	{
		CXGMPoint point;
		for (int i=0; i<nCount; ++i)
		{
			ar>>point.m_dX;
			ar>>point.m_dY;
			ar>>point.m_dZ;

			push_back(point);
		}
	}
}

void CXGMPillar::GetDimension(double& xmin, double& xmax, double& ymin, double& ymax, double& zmin, double& zmax)
{
	int nSize = (int) size();
	if (nSize < 1)
		return;
	xmin = xmax = (*this)[0].m_dX;
	ymin = ymax = (*this)[0].m_dY;
	zmin = zmax = (*this)[0].m_dZ;

	for (int i=1; i<nSize; ++i)
	{
		xmin = qMin(xmin, (*this)[i].m_dX);
		ymin = qMin(ymin, (*this)[i].m_dY);
		zmin = qMin(zmin, (*this)[i].m_dZ);

		xmax = qMax(xmax, (*this)[i].m_dX);
		ymax = qMax(ymax, (*this)[i].m_dY);
		zmax = qMax(zmax, (*this)[i].m_dZ);
	}

}
CXGMFault::CXGMFault(const QString& strName):
CXObject(strName)
{
	SetIconName("Fault.png");
	SetObjectType(EXGMFault);
}

CXGMFault::~CXGMFault()
{
	_FreeMem();
}

void CXGMFault::_FreeMem()
{
	qDeleteAll(m_listPillar);
	qDeleteAll(m_listIntersectPillar);

	m_listIntersectID.clear();
	m_listIntersectIndex.clear();

}

bool CXGMFault::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		// pillars
		int nSize = m_listPillar.size();
		ar<<nSize;
		int nPillarLength = 0;
		if (nSize > 0)
		{
			nPillarLength = m_listPillar.front()->size();
			ar<<nPillarLength;

			for (int i=0; i<nSize; ++i)
			{
				m_listPillar.at(i)->SerializeData(ar, nPillarLength);
			}
		}

		// intersection
		nSize = m_listIntersectID.size();
		ar<<nSize;
		for (int i=0; i<nSize; ++i)
		{
			ar<<m_listIntersectID.at(i);
			m_listIntersectPillar.at(i)->SerializeData(ar, nPillarLength);
			for (int j=0; j<nPillarLength; ++j)
				ar<<m_listIntersectIndex.at(i).at(j);
		}
	}
	else
	{
		_FreeMem();

		// pillars
		int nSize;
		ar>>nSize;
		int nPillarLength = 0;
		if (nSize > 0)
		{			
			ar>>nPillarLength;

			for (int i=0; i<nSize; ++i)
			{
				CXGMPillar* pPillar = new CXGMPillar;
				pPillar->SerializeData(ar, nPillarLength);
				m_listPillar.append(pPillar);
			}
		}

		// intersect
		ar>>nSize;
		for (int i=0; i<nSize; ++i)
		{
			QUuid uuid;
			ar>>uuid;

			CXGMPillar* pPillar = new CXGMPillar;
			pPillar->SerializeData(ar, nPillarLength);

			int index;
			std::vector<int> vecIndex;
			for (int j=0; j<nPillarLength; ++j)
			{
				ar>>index;
				vecIndex.push_back(index);
			}

			m_listIntersectID.append(uuid);
			m_listIntersectPillar.append(pPillar);
			m_listIntersectIndex.append(vecIndex);

		}
	}

	return true;
}

void CXGMFault::RemoveConnectionInfo()
{
	qDeleteAll(m_listIntersectPillar);
	m_listIntersectPillar.clear();
	
	m_listIntersectID.clear();
	m_listIntersectIndex.clear();
}

QStringList CXGMFault::GetDescription()
{
	QStringList strList;

	strList<<"Number of Pillars:"<<QString::number(m_listPillar.size());

	strList<<"Number of Intersecting Faults:"<<QString::number(m_listIntersectID.size());
	for (int i=0; i<m_listIntersectID.size(); ++i)
	{
		CXObject* pObj = ::GetObjectByID(m_listIntersectID.at(i));
		strList<<"Intersecting Fault:"<<pObj->GetObjectName(); 
	}

	return strList;
}

void CXGMFault::_SetSelfDimension()
{
	int nSize = m_listPillar.size();
	if (nSize < 1)
		return;

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	m_listPillar.front()->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	
	double xmin, xmax, ymin, ymax, zmin, zmax;
	for (int i=1; i<nSize; ++i)
	{
		m_listPillar.at(i)->GetDimension(xmin, xmax, ymin, ymax, zmin, zmax);

		dXMin = qMin(dXMin, xmin);
		dXMax = qMax(dXMax, xmax);

		dYMin = qMin(dYMin, ymin);
		dYMax = qMax(dYMax, ymax);

		dZMin = qMin(dZMin, zmin);
		dZMax = qMax(dZMax, zmax);
	}
	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

bool CXGMFault::ExtractPillarFromSticks(CXFaultSticks* pSticks, double dDistance)
{
	// release memory
	_FreeMem();

	if (!pSticks)
		return false;

	QList<CXFaultStick *>& listSticks = pSticks->GetAllSticks();
	int nSize = listSticks.size();
	if (nSize < 2)
		return false;

	// sort each pillar according to Z (increase)	
	std::vector<CXGMPillar*>vecPillar;	
	std::vector<CXGMPoint> vecPoint;
	CXGMPoint point;
	for (int i=0; i<nSize; ++i)
	{		
		unsigned int nDataNum;
		double* pData = listSticks.at(i)->GetXYZData(nDataNum);
		nDataNum *= 3;
		vecPoint.clear();

		for (int i=0; i<nDataNum; i += 3)
		{
			point.m_dX = pData[i];
			point.m_dY = pData[i+1];
			point.m_dZ = pData[i+2];
			vecPoint.push_back(point);
		}
		std::sort(vecPoint.begin(), vecPoint.end(), CompareTwoPointsByZ);

		CXGMPillar* pPillar = new CXGMPillar;
		int nCount = (int) vecPoint.size();
		int nHalfCount = nCount/2;
		if (nHalfCount % 2 == 1)
		{
			pPillar->push_back(vecPoint.front());
			pPillar->push_back(vecPoint.at(nHalfCount));
			pPillar->push_back(vecPoint.back());
		}
		else
		{
			point.m_dX = (vecPoint[nHalfCount-1].m_dX + vecPoint[nHalfCount].m_dX)/2;
			point.m_dY = (vecPoint[nHalfCount-1].m_dY + vecPoint[nHalfCount].m_dY)/2;
			point.m_dZ = (vecPoint[nHalfCount-1].m_dZ + vecPoint[nHalfCount].m_dZ)/2;

			pPillar->push_back(vecPoint.front());
			pPillar->push_back(point);
			pPillar->push_back(vecPoint.back());
		}
		vecPillar.push_back(pPillar);
	}

	// sort all pillars

	// Set first pillar
	double dXMin = vecPillar.front()->front().m_dX;
	int index=0;
	for (int i=1; i<m_listPillar.size(); ++i)
	{
		if (vecPillar.at(i)->front().m_dX < dXMin)
		{
			dXMin = vecPillar.at(i)->front().m_dX;
			index = i;
		}
	}
	if (index !=0)
		qSwap(vecPillar.at(0), vecPillar.at(index));

	// rest pillars
	double xpre, ypre, x, y, xnext, ynext;
	double dDist, dDistnext;
	for (int i=1; i<vecPillar.size(); ++i)
	{
		xpre = vecPillar.at(i-1)->front().m_dX;
		ypre = vecPillar.at(i-1)->front().m_dY;
		x = vecPillar.at(i)->front().m_dX;
		y = vecPillar.at(i)->front().m_dY;

		dDist = SQR(x-xpre) + SQR(y - ypre);
		index = i;

		for (int j=i+1; j<vecPillar.size(); ++j)
		{
			xnext = vecPillar.at(j)->front().m_dX;
			ynext = vecPillar.at(j)->front().m_dY;

			dDistnext = SQR(xnext-xpre) + SQR(ynext - ypre);
			if (dDistnext < dDist)
			{
				index = j;
			}
		}
		if (index != i)
		{
			qSwap(vecPillar.at(i), vecPillar.at(index));
		}
	}

	// Exact
	double dDistTol = dDistance;
	m_listPillar.append(vecPillar.at(0));

	dDist = 0.;
	xpre = vecPillar.at(0)->front().m_dX;
	ypre = vecPillar.at(0)->front().m_dY;
	for (int i=1; i<vecPillar.size() - 1; ++i)
	{
		x = vecPillar.at(i)->front().m_dX;
		y = vecPillar.at(i)->front().m_dY; 

		dDist += sqrt(SQR(x-xpre) + SQR(y - ypre));

		if (dDist >= dDistTol)
		{
			m_listPillar.append(vecPillar.at(i));
			dDist = 0.f;
		}

		xpre = x;
		ypre = y;
	}

	if (!m_listPillar.back()->front().IsEqual(vecPillar.back()->front()))
		m_listPillar.append(vecPillar.back());

	return true;
}

bool CXGMFault::ExtendFault(double dDistance)
{
	int nK = (int) m_listPillar.front()->size();
	int nSize = m_listPillar.size();

	CXGMPoint pointpre, pointnext, point;
	CXGMPillar* pPillarPre = new CXGMPillar;
	CXGMPillar* pPillarEnd = new CXGMPillar;
	double dDist;

	for (int k=0; k<nK; ++k)
	{	
		// Start point
		pointpre = m_listPillar.at(0)->at(k);
		pointnext = m_listPillar.at(1)->at(k);

		dDist = pointpre.Distance(pointnext);
		point.m_dX = (1.+dDist/dDistance)*pointpre.m_dX - dDist/dDistance*pointnext.m_dX;
		point.m_dY = (1.+dDist/dDistance)*pointpre.m_dY - dDist/dDistance*pointnext.m_dY;
		point.m_dZ = (1.+dDist/dDistance)*pointpre.m_dZ - dDist/dDistance*pointnext.m_dZ;

		pPillarPre->push_back(point);

		// end point
		pointpre = m_listPillar.at(nSize-2)->at(k);
		pointnext = m_listPillar.at(nSize-1)->at(k);

		dDist = pointpre.Distance(pointnext);
		point.m_dX = (1.+dDist/dDistance)*pointnext.m_dX - dDist/dDistance*pointpre.m_dX;
		point.m_dY = (1.+dDist/dDistance)*pointnext.m_dY - dDist/dDistance*pointpre.m_dY;
		point.m_dZ = (1.+dDist/dDistance)*pointnext.m_dZ - dDist/dDistance*pointpre.m_dZ;

		pPillarEnd->push_back(point);		
	}

	m_listPillar.push_front(pPillarPre);
	m_listPillar.append(pPillarEnd);


	return true;
}


bool CXGMFault::Intersect(CXGMFault* pOtherFault)
{
	int nK = m_listPillar.front()->size();
	int nSize = m_listPillar.size();
	int nSizeOther = pOtherFault->m_listPillar.size();

	double x1, y1, x2, y2, x3, y3, x4, y4, xintersect, yintersect, zintersect;

	bool bBreak = false;
	std::vector<int> vecIndex, vecIndexOther;
	double z[2], z1, z2, a, b, c;
	double d, d1;

	CXGMPillar* pPillar= NULL;
	CXGMPoint point;
	for (int k=0; k<nK; ++k)
	{
		bBreak = false;

		for (int i=0; i<nSize-1; ++i)
		{
			x1 = m_listPillar.at(i)->at(k).m_dX;
			y1 = m_listPillar.at(i)->at(k).m_dY;

			x2 = m_listPillar.at(i+1)->at(k).m_dX;
			y2 = m_listPillar.at(i+1)->at(k).m_dY;

			for (int j=0; j<nSizeOther-1; ++j)
			{
				x3 = pOtherFault->m_listPillar.at(j)->at(k).m_dX;
				y3 = pOtherFault->m_listPillar.at(j)->at(k).m_dY;

				x4 = pOtherFault->m_listPillar.at(j+1)->at(k).m_dX;
				y4 = pOtherFault->m_listPillar.at(j+1)->at(k).m_dY;

				if (!NXGMUtility::LineSegIntersect(x1,y1,x2,y2,x3,y3,x4,y4,xintersect,yintersect))
					continue;

				vecIndex.push_back(i-1);
				vecIndexOther.push_back(j-1);

				// intersection along I
				z[0] = m_listPillar.at(i)->at(k).m_dZ;
				z[1] = m_listPillar.at(i+1)->at(k).m_dZ;				

				d  = sqrt(SQR(x2 - x1) + SQR(y2 - y1));
				d1 = sqrt(SQR(xintersect - x1) + SQR(yintersect - y1));
				if (d < M_FEPS)
					z1 = (z[0]+z[1])/2.;
				else
				{
					z1 = z[0]*(1-d1/d) + z[1]*d1/d;
				}

				// intersection along J
				z[0] = pOtherFault->m_listPillar.at(j)->at(k).m_dZ;
				z[1] = pOtherFault->m_listPillar.at(j+1)->at(k).m_dZ;				

				d  = sqrt(SQR(x4 - x3) + SQR(y4 - y3));
				d1 = sqrt(SQR(xintersect - x3) + SQR(yintersect - y3));
				if (d < M_FEPS)
					z2 = (z[0]+z[1])/2.;
				else
				{
					z2 = z[0]*(1-d1/d) + z[1]*d1/d;
				}

				if(i==0 || i==1 || i == nSize - 2 || i == nSize - 3)
				{
					if (j != 0 && j != nSizeOther -2)
						zintersect = z2;
					else
						zintersect = (z1 + z2)/2.;
				}
				else
				{
					if (j==0 || j==1 || j == nSizeOther -2 || j == nSizeOther-3)
						zintersect = z1;
					else
						zintersect = (z1 + z2)/2.;
				}

				//
				point.m_dX = xintersect;
				point.m_dY = yintersect;
				point.m_dZ = zintersect;			

				if (!pPillar)
					pPillar = new CXGMPillar;
				pPillar->push_back(point);

				bBreak = true;
				break;
			}

			if (bBreak)
				break;
		}
	}

	if (pPillar)
	{
		if (vecIndex.size() != m_listPillar.front()->size())
		{
			delete pPillar;
			return false;
		}
	}

	if (pPillar)
	{
		int index = this->m_listIntersectID.indexOf(pOtherFault->GetObjectID());
		if (index != -1)
		{
			this->m_listIntersectIndex[index] = vecIndex;

			delete this->m_listIntersectPillar[index];
			this->m_listIntersectPillar[index] = pPillar;
		}
		else
		{
			this->m_listIntersectID.push_back(pOtherFault->GetObjectID());
			this->m_listIntersectIndex.append(vecIndex);
			this->m_listIntersectPillar.append(pPillar);
		}

		CXGMPillar* pOtherPillar = new CXGMPillar;
		*pOtherPillar = *pPillar;

		index = pOtherFault->m_listIntersectID.indexOf(this->GetObjectID());
		if (index != -1)
		{		
			pOtherFault->m_listIntersectIndex[index] = vecIndexOther;
			delete pOtherFault->m_listIntersectPillar[index];
			pOtherFault->m_listIntersectPillar[index] = pOtherPillar;

		}
		else
		{
			pOtherFault->m_listIntersectID.push_back(this->GetObjectID());
			pOtherFault->m_listIntersectIndex.append(vecIndexOther);
			pOtherFault->m_listIntersectPillar.append(pOtherPillar);
		}
	}


	return true;
}

bool CXGMFault::RearrageData(double dDistance)
{
	// Get rid of head an tailor from the extended list
	CXGMPillar* pHead = m_listPillar.front();
	CXGMPillar* pTail = m_listPillar.back();
	m_listPillar.pop_front();
	m_listPillar.pop_back();

	if (m_listIntersectIndex.empty())
	{
		delete pHead;
		delete pTail;
		return true;
	}

	// sort
	int nSize = m_listIntersectIndex.size();
	for (int i=0; i<nSize; ++i)
	{
		for (int j=i+1; j<nSize; ++j)
		{
			if (m_listIntersectIndex[i][0] > m_listIntersectIndex[j][0])
			{
				std::vector<int> vecIndex = m_listIntersectIndex[i];
				m_listIntersectIndex[i] = m_listIntersectIndex[j];
				m_listIntersectIndex[j] = vecIndex;

				qSwap(m_listIntersectID[i], m_listIntersectID[j]);

				qSwap(m_listIntersectPillar[i], m_listIntersectPillar[j]);
			}
		}
	}

	// Merge to same point if the distance < 0.5
	int nPillarNum = m_listPillar.size();
	int nK = m_listIntersectPillar.at(0)->size();
	std::vector<int> vecIndex;
	CXGMPoint pointpre, pointend, point;
	int iPre, iEnd;
	for (int i=0; i<nSize; ++i)
	{
		vecIndex = m_listIntersectIndex.at(i);
		for (int k=0; k<nK; ++k)
		{
			if (vecIndex[k] = -1)
			{
				pointpre = pHead->at(k);
				pointend = m_listPillar.front()->at(k);
			}
			else if (vecIndex[k] == nPillarNum-1)
			{
				pointpre = m_listPillar.back()->at(k);
				pointend = pTail->at(k);
			}
			else
			{
				pointpre = m_listPillar[vecIndex[k]]->at(k);
				pointend = m_listPillar[vecIndex[k]+1]->at(k);
			}

			point = m_listIntersectPillar.at(i)->at(k);
			if (point.Distance(pointpre) < 1)
			{			
				(*m_listIntersectPillar[i])[k] = pointpre;		
				if (vecIndex[k] == 0 && pointpre.IsEqual(m_listPillar[0]->at(k)))
					m_listIntersectIndex[i][k] = -1;
			}
			else if (point.Distance(pointend) < 1)
			{
				(*m_listIntersectPillar[i])[k] = pointend;
				if (vecIndex[k] == nPillarNum-2 || pointend.IsEqual(m_listPillar[nPillarNum-1]->at(k)))
					m_listIntersectIndex[i][k] = nPillarNum-1;

			}
		}
	}
	delete pHead;
	delete pTail;


	return true;
}

bool CXGMFault::RemoveExtraPillars()
{
	// delete extra intesection pillar at head or tail
	while(m_listIntersectIndex.size() >= 2)
	{
		if (m_listIntersectIndex.at(0).at(0) == -1 && m_listIntersectIndex.at(1).at(0) == -1)
		{
			CXGMFault* pOtherFault = dynamic_cast<CXGMFault*>(::GetObjectByID(m_listIntersectID.at(0)));

			delete m_listIntersectPillar.front();
			m_listIntersectPillar.pop_front();

			m_listIntersectIndex.pop_front();
			m_listIntersectID.pop_front();

			// other
			int index = pOtherFault->m_listIntersectID.indexOf(this->GetObjectID());
			delete pOtherFault->m_listIntersectPillar.at(index);
			pOtherFault->m_listIntersectPillar.removeAt(index);

			pOtherFault->m_listIntersectIndex.removeAt(index);
			pOtherFault->m_listIntersectID.removeAt(index);
		}
		else
		{
			break;
		}

	}

	int nPillarNum = m_listPillar.size();	

	while(m_listIntersectIndex.size() >= 2)
	{
		if (m_listIntersectIndex.back().at(0) == nPillarNum-1 && m_listIntersectIndex.at(m_listIntersectIndex.size()-2).at(0) == nPillarNum-1)
		{
			CXGMFault* pOtherFault = dynamic_cast<CXGMFault*>(::GetObjectByID(m_listIntersectID.back()));

			delete m_listIntersectPillar.back();
			m_listIntersectPillar.pop_back();

			m_listIntersectIndex.pop_back();
			m_listIntersectID.pop_back();

			// other
			int index = pOtherFault->m_listIntersectID.indexOf(this->GetObjectID());
			delete pOtherFault->m_listIntersectPillar.at(index);
			pOtherFault->m_listIntersectPillar.removeAt(index);

			pOtherFault->m_listIntersectIndex.removeAt(index);
			pOtherFault->m_listIntersectID.removeAt(index);
		}
		else
		{
			break;
		}
	}

	return true;

}