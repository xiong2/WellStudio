#include "xgmmethod.h"
#include "xfaultsticks.h"
#include "xgmfault.h"
#include "xgm.h"
#include "xgeneralfolder.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xtree.h"
#include "xwaitcursor.h"

void CXGMMethod::ExtractFaultPillars(CXObject* pFaultFolder)
{
	if (!pFaultFolder)
		return;

	if (pFaultFolder->GetObjectType() != EXFaultFolder)
		return;

	QList<CXObject*> listFault = pFaultFolder->GetChildren(EXFaultSticks, true);
	if (listFault.empty())
		return;

	// new model faults
	QList<CXGMFault*> listModelFault;
	for (int i=0; i<listFault.size(); ++i)
	{
		CXGMFault* pModelFault = new CXGMFault(listFault.at(i)->GetObjectName());
		pModelFault->SetColor(listFault.at(i)->GetColor());
		CXFaultSticks* pSticks = dynamic_cast<CXFaultSticks*>(listFault.at(i));
		assert(pSticks);
		pModelFault->ExtractPillarFromSticks(pSticks);
		listModelFault.append(pModelFault);
	}

	// create a geological model
	CXGM* pModel = new CXGM("Model");
	QString strModelName = ::GetProject()->GetUnallocatedName(pModel->GetObjectName());
	pModel->SetObjectName(strModelName);

	CXGeneralFolder* pModelFaultFolder = new CXGeneralFolder("Modeled Faults");
	pModelFaultFolder->SetObjectType(EXGMFaultFolder);
	pModelFaultFolder->SetIconName("FaultFolder.png");

	// Add data	
	for (int i=0; i<listModelFault.size(); ++i)
	{
		pModelFaultFolder->AddChild(listModelFault.at(i));
	}
	pModel->AddChild(pModelFaultFolder);
	::GetProject()->AddChild(pModel);

	// Add to the tree
	::AddObjectEvent(pModel);

}

void CXGMMethod::AutoConnectFaults(CXObject* pModelFaultFolder)
{
	if (!pModelFaultFolder)
		return;

	if (pModelFaultFolder->GetObjectType() != EXGMFaultFolder)
		return;

	QList<CXObject*> listObj = pModelFaultFolder->GetChildren(EXGMFault, true);
	QList<CXGMFault*> listFault;
	for (int i=0; i<listObj.size(); ++i)
	{
		CXGMFault* pFault = dynamic_cast<CXGMFault*>(listObj.at(i));
		assert(pFault);

		listFault.append(pFault);
	}

	CXWaitCursor wait;

	// clear all existing connection
	for (int i=0; i<listFault.size();++i)
	{
		listFault.at(i)->RemoveConnectionInfo();
	}


	// Extend two sides of each fault
	for (int i=0; i<listFault.size();++i)
	{
		listFault.at(i)->ExtendFault();
	}

	// intersect
	for (int i=0; i<listFault.size(); ++i)
	{
		CXGMFault* pFaultOne = listFault.at(i);

		for (int j=i+1; j<listFault.size(); ++j)
		{
			CXGMFault* pFaultTwo = listFault.at(j);

			pFaultOne->Intersect(pFaultTwo);
		}
	}

	// Rearrage data
	for (int i=0; i<listFault.size(); ++i)
	{
		listFault.at(i)->RearrageData();		
	}

	// Rearrage data
	for (int i=0; i<listFault.size(); ++i)
	{
		listFault.at(i)->RemoveExtraPillars();
		listFault.at(i)->SetModifiedFlag();
	}
}

bool CXGMMethod::CalcVerticesAndIndex(CXGMFault* pFault, std::vector<osg::Vec3d>& vecVertices, 
		                             vector<vector<int> >& vecVecIndex, vector<int>& vecCount, double dDistance)
{
	if (!pFault)
		return false;

	QList<CXGMPillar*> listPillar = pFault->GetPillars();
	QList<CXGMPillar*> listIntersectPillar = pFault->GetIntersectPillars();
	QList<std::vector<int> >& listIntersectNodeIndex = pFault->GetIntersectNodeIndex();

	if (listPillar.empty())
		return false;

	int nK = listPillar.front()->size();
	int nPillarNum = listPillar.size();
	int nIntersectPillarNum = listIntersectPillar.size();

	if (nIntersectPillarNum == 0)
	{
		// Init index
		vector<int> vecIndex(nK);
		vecVecIndex.resize(nPillarNum);
		for (int i=0; i<nPillarNum; ++i)
		{
			vecVecIndex[i] = vecIndex;
		}		
		
		osg::Vec3d vecWorld;
		vecCount.push_back(0);
		for (int k=0; k<nK; ++k)
		{
			for (int i=0; i<nPillarNum; ++i)
			{
				vecWorld.set(listPillar.at(i)->at(k).m_dX, listPillar.at(i)->at(k).m_dY, listPillar.at(i)->at(k).m_dZ);
				vecVertices.push_back(vecWorld);

				vecVecIndex[i][k] = k*nPillarNum + i;
			}

			vecCount.push_back(vecVertices.size());
		}
		return true;
	}

	// sort all points
	CXGMPoint  point;
	vector<CXGMPoint> vecPoint;
	vecCount.push_back(0);
	for (int k=0; k<nK; ++k)
	{
		// bewtween -1 and nPillarNum-1		
		int index=0;
		for (int iIndex=0; iIndex<=nPillarNum; ++iIndex)
		{
			if (iIndex != 0)
			{
				point = listPillar.at(iIndex-1)->at(k);
				vecVertices.push_back(osg::Vec3d(point.m_dX, point.m_dY, point.m_dZ));
			}

			vecPoint.clear();
			while (index<listIntersectNodeIndex.size() && listIntersectNodeIndex.at(index).at(k) < iIndex)
			{
				vecPoint.push_back(listIntersectPillar.at(index)->at(k));
				++index;
			}

			if (!vecPoint.empty())
			{
				if (iIndex == 0)
					point = listPillar.at(iIndex)->at(k);
				else
					point = listPillar.at(iIndex-1)->at(k);
						
				for (int i=0; i<vecPoint.size(); ++i)
				{
					for (int j=i+1; j<vecPoint.size(); ++j)
					{
						if (iIndex == 0)
						{
							if (point.Distance2(vecPoint[i]) < point.Distance2(vecPoint[j]))
							{
								qSwap(vecPoint[i], vecPoint[j]);
							}
						}
						else
						{												
							if (point.Distance2(vecPoint[i]) > point.Distance2(vecPoint[j]))
							{
								qSwap(vecPoint[i], vecPoint[j]);
							}
						}
					}
				}
			}

			for (int i=0; i<vecPoint.size(); ++i)
			{
				vecVertices.push_back(osg::Vec3d(vecPoint[i].m_dX, vecPoint[i].m_dY, vecPoint[i].m_dZ));
			}
		}

		vecCount.push_back(vecVertices.size());
	}

	// remove head or tail if necessary	
	vector<int> vecIndex(nK, 0);	
	CXGMPoint pointIntersect;
	bool bRemoveHead = false;
	bool bRemoveTail = false;

	// remove head
	if (listIntersectNodeIndex.front() == vecIndex && nPillarNum > 2)
	{
		vecPoint.clear();

		for (int k=0; k<nK; ++k)
		{
			point = listPillar.front()->at(k);
			for (int i=vecCount[k]; i<vecCount[k+1]; ++i)
			{
				pointIntersect.m_dX = vecVertices[i][0];
				pointIntersect.m_dY = vecVertices[i][1];
				pointIntersect.m_dZ = vecVertices[i][2];

				if (!point.IsEqual(pointIntersect))
				{
					vecPoint.push_back(pointIntersect);
					break;
				}
			}
		} // k

		bRemoveHead = false;
		for (int k=0; k<nK; ++k)
		{
			if (vecPoint[k].Distance( listPillar.front()->at(k)) < dDistance)
			{
				bRemoveHead = true;
				break;
			}
		}
		if (bRemoveHead)
		{
			for (int k=0; k<nK; ++k)
			{
				point = listPillar.front()->at(k);
				for (int i=vecCount[k]; i<vecCount[k+1]; ++i)
				{
					if (point.IsEqual(CXGMPoint(vecVertices[i][0], vecVertices[i][1], vecVertices[i][2])))
					{
						vecVertices.erase(vecVertices.begin()+i);
						for (int kk=k+1; kk<nK; ++kk)
							vecCount[kk] -= 1;

						break;
					}
				}
			} // k
		}
	}

	// remove tail
	vecIndex.resize(nK, nPillarNum-2);
	if (listIntersectNodeIndex.back() == vecIndex && nPillarNum > 2)
	{
		vecPoint.clear();

		for (int k=0; k<nK; ++k)
		{
			point = listPillar.back()->at(k);
			for (int i=vecCount[k+1]-1; i>=vecCount[k]; --i)
			{
				pointIntersect.m_dX = vecVertices[i][0];
				pointIntersect.m_dY = vecVertices[i][1];
				pointIntersect.m_dZ = vecVertices[i][2];

				if (!point.IsEqual(pointIntersect))
				{
					vecPoint.push_back(pointIntersect);
					break;
				}
			}
		} // k

		bRemoveTail = false;
		for (int k=0; k<nK; ++k)
		{
			if (vecPoint[k].Distance( listPillar.back()->at(k)) > dDistance)
			{
				bRemoveTail = true;
				break;
			}
		}
		if (bRemoveTail)
		{
			for (int k=0; k<nK; ++k)
			{
				point = listPillar.back()->at(k);
				for (int i=vecCount[k+1]-1; i>=vecCount[k]; --i)
				{
					if (point.IsEqual(CXGMPoint(vecVertices[i][0], vecVertices[i][1], vecVertices[i][2])))
					{
						vecVertices.erase(vecVertices.begin()+i);
						for (int kk=k+1; kk<nK; ++kk)
							vecCount[kk] -= 1;

						break;
					}
				}
			} // k
		}
	}


	// Calculate index
	
	// Init index	
	if (bRemoveHead)
		listPillar.pop_front();
	if (bRemoveTail)
		listPillar.pop_back();

	listPillar.append(listIntersectPillar);	
	
	vecVecIndex.resize(listPillar.size(), vecIndex);	
	for (int i=0; i<listPillar.size(); ++i)
	{
		for (int k=0; k<nK; ++k)
		{
			point = listPillar.at(i)->at(k);

			for (int ii=vecCount[k]; ii<vecCount[k+1]; ++ii)
			{
				if (point.IsEqual(CXGMPoint(vecVertices[ii][0], vecVertices[ii][1], vecVertices[ii][2])))
				{
					vecVecIndex[i][k] = ii;
					break;
				}
			}			
		}
	}

	return true;
}