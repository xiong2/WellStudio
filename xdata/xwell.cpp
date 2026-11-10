#include <qdebug.h>
#include "xwell.h"
#include "xwellpath.h"
#include "xwelltd.h"
#include "xdbio.h"
#include "xobjectfactory.h"
#include "xglobal.h"
#include "xwellcomp.h"
#include "xwellcurve.h"
#include "xmathmacro.h"
#include "xutility.h"
#include "xproject.h"
#include <QUndoGroup>
#include "xgeneralfolder.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWell)
EXWell
END_REGISTER_OBJECT_TO_FACTORY(CXWell)


QStringList CXWell::m_staSListAttribute;
QStringList CXWell::m_staSListWellIcon;

CXWell::CXWell()
{
	m_dKB = 0;
}

CXWell::CXWell(QString sName, double dX, double dY): CXObject(sName)
{
	SetObjectType(EXWell);

	m_dStep		= 0.;
	m_dStart	= 9999.;
	m_dEnd		= 0.;

	m_dKB = 0;

	//	Create the well path instance.
	CXWellPath *pWellPath = new CXWellPath(dX, dY);
	AddChild(pWellPath);

	SetIconName("Well.png");

}

CXObject* CXWell::GetFolder(EXObjectType eObjType, bool bCreate)
{
	const auto& listObj = GetChildren(eObjType);
	if (listObj.isEmpty())
	{
		if (!bCreate)
			return NULL;

		CXGeneralFolder *pFolder;
		if (eObjType == EXNMRFolder)
			pFolder = new CXGeneralFolder("2d", EXNMRFolder, "SeismicDVFolder.png");
		else
			return NULL;

		AddChild(pFolder);

		::AddObjectEvent(pFolder);

		return pFolder;
	}

	return listObj.at(0);
}


bool CXWell::RemoveOneChild(CXObject *pChild)
{
	//	Do not allow remove well path child.
	if (pChild->GetObjectType() == EXWellPath)
		return false;

	return CXObject::RemoveOneChild(pChild);
}

void CXWell::GetWellPosition(double& dX, double& dY)
{
	dX = g_dInvalidData;
	dY = g_dInvalidData;

	CXWellPath *pWellPath = GetWellPath();
	if (pWellPath)
	{
		pWellPath->GetWellPosition(dX, dY);
	}
}

void CXWell::SetWellPosition(double dX, double dY)
{
	CXWellPath *pWellPath = GetWellPath();
	pWellPath->SetWellPosition(dX, dY);
}
//	Add one attribute to this well, return false if it's not a standard attribute.
bool CXWell::AddAttribute(QString sAttName, QString sAttValue)
{
	//	Not allow empty attribute.
	if(sAttValue.isEmpty())
		return false;

	const QStringList sListStandardAtt = getStandardAttributes();
	if(!sListStandardAtt.contains(sAttName))
		return false;

	m_mapAttributes.insert(sAttName, sAttValue);

	SetModifiedFlag();

	return true;
}

CXWellPath* CXWell::GetWellPath()
{
	QList<CXObject *> listChild = GetChildren(EXWellPath);
	if(listChild.size() != 1)
	{
		qDebug()<<"Well "<<this->GetObjectName()<<" does not has one path instance, something error!";
		return NULL;
	}

	return (CXWellPath *)listChild.first();
}

CXWellTD* CXWell::GetWellTD()
{
	if (m_sTD.isEmpty())
		return NULL;

	CXObject *pObj = GetChild(m_sTD, EXWellTD);

	if (pObj)
		return (CXWellTD *)(pObj);
	else
		return NULL;
}

CXWellComp* CXWell::GetWellComp()
{
	QList<CXObject *> listChild = GetChildren(EXWellComp);
	if (listChild.size() <1)
	{

		CXWellComp *pWellTD = new CXWellComp();
		AddChild(pWellTD);
		return pWellTD;
	}
	return (CXWellComp*)listChild.first();
}


void CXWell::updateTDWellPath(CXWellCurve* pTimeTrack2222, CXWellCurve* pTvdTrack,
	CXWellCurve* pDevXTrack, CXWellCurve* pDevYTrack,
	CXWellCurve* pAbsXTrack, CXWellCurve* pAbsYTrack,
	CXWellCurve* pAziTrack, CXWellCurve* pDipTrack)
{
	int i;
// 	bool bUpdateWellTrack = false;
// 	if (pTvdTrack && pDevYTrack && pDevXTrack)
// 	{
// 		bUpdateWellTrack = true;
// 	}
// 	else if (pTvdTrack && pAbsXTrack && pAbsYTrack)
// 	{
// 		bUpdateWellTrack = true;
// 	}
	
	if (1)
	{
		CXWellPath* pTrack = this->GetWellPath();
		
		//m_model = (QStandardItemModel* )m_Ui.m_pTable->model();
		bool bD, bX, bY;
		double dep, md, tvd;
		double x, y;

		 if (pAziTrack && pDipTrack)//md azi dip
		{
			double x0, y0;
			this->GetWellPosition(x0, y0);
			double *pmd = new double[pAziTrack->GetCount()];
			double *ptvd = new double[pAziTrack->GetCount()];
			double *px = new double[pAziTrack->GetCount()];
			double *py = new double[pAziTrack->GetCount()];
			double* dataDip = new double[pAziTrack->GetCount()];//倾角
			double* dataAzi = new double[pAziTrack->GetCount()];//方位角
			int nValid = 0;
			for (i = 0; i < pAziTrack->GetCount(); i++)
			{
				md = pAziTrack->GetDepth(i);
				x = pAziTrack->GetData(i);
				y = pDipTrack->GetData(i);
				if (CXWellCurve::IsValid(md) == false
					|| CXWellCurve::IsValid(x) == false
					|| CXWellCurve::IsValid(y) == false)
				{
					continue;
				}
				pmd[nValid] = md;
				dataAzi[nValid] = x*M_PI / 180.;
				dataDip[nValid] = y*M_PI / 180.;

				nValid++;
			}



			double preabsx = x0;
			double preabsy = y0;
			double premd = 0;
			double pretvd = 0;
			double ri, mapr, dx, dy;
			for (i = 0; i < nValid; i++)
			{
				ri = pmd[i] - premd;
				if (dataDip[i] >= M_PI / 2.0)
				{
					ptvd[i] = pretvd - ri*cos(M_PI - dataDip[i]);
				}
				else{
					ptvd[i] = pretvd + ri*cos(dataDip[i]);
				}
				mapr = sqrt((ptvd[i] - pretvd) * (ptvd[i] - pretvd) + ri*ri - 2.0*ri* fabs(ptvd[i] - pretvd) * cos(dataDip[i]));
				dx = mapr*sin(dataAzi[i]);
				dy = mapr*cos(dataAzi[i]);
				px[i] = preabsx + dx;
				py[i] = preabsy + dy;
				preabsx = px[i];
				preabsy = py[i];
				pretvd = ptvd[i];
				premd = pmd[i];
			}




			double* pData = new double[(nValid + 1) * 3];
			pData[0 * 3] = 0 + x0;
			pData[0 * 3 + 1] = 0 + y0;
			pData[0 * 3 + 2] = 0;
			for (i = 1; i < nValid + 1; i++)
			{
				pData[i * 3] = px[i - 1];
				pData[i * 3 + 1] = py[i - 1];
				pData[i * 3 + 2] = ptvd[i - 1];
			}
			pTrack->ResetData(pData, (nValid + 1) * 3);
			delete pmd;// = new double[pTvdTrack->GetCount()];
			delete ptvd;//  = new double[pTvdTrack->GetCount()];
			delete px;//  = new double[pTvdTrack->GetCount()];
			delete py;//  = new double[pTvdTrack->GetCount()];
		}
		else if (pTvdTrack && pDevYTrack && pDevXTrack)//tvd dx dy
		{
			double x0, y0;
			this->GetWellPosition(x0, y0);
			double *pmd = new double[pTvdTrack->GetCount()];
			double *ptvd = new double[pTvdTrack->GetCount()];
			double *px = new double[pTvdTrack->GetCount()];
			double *py = new double[pTvdTrack->GetCount()];
			int nValid = 0;
			for (i = 0; i < pTvdTrack->GetCount(); i++)
			{
				md = pTvdTrack->GetDepth(i);
				tvd = pTvdTrack->GetData(i);
				x = pDevXTrack->GetData(i);
				y = pDevYTrack->GetData(i);

				if (CXWellCurve::IsValid(tvd) == false
					|| CXWellCurve::IsValid(x) == false
					|| CXWellCurve::IsValid(y) == false)
				{
					continue;
				}
				pmd[nValid] = md;
				ptvd[nValid] = tvd;
				px[nValid] = x;
				py[nValid] = y;

				nValid++;
			}

			double* pData = new double[(nValid + 1) * 3];
			pData[0 * 3] = 0 + x0;
			pData[0 * 3 + 1] = 0 + y0;
			pData[0 * 3 + 2] = 0;
			for (i = 1; i < nValid + 1; i++)
			{
				pData[i * 3] = px[i - 1] + x0;
				pData[i * 3 + 1] = py[i - 1] + y0;
				pData[i * 3 + 2] = ptvd[i - 1];
			}
			pTrack->ResetData(pData, (nValid + 1) * 3);

			delete pmd;// = new double[pTvdTrack->GetCount()];
			delete ptvd;//  = new double[pTvdTrack->GetCount()];
			delete px;//  = new double[pTvdTrack->GetCount()];
			delete py;//  = new double[pTvdTrack->GetCount()];
		}
		else if (pTvdTrack && pAbsXTrack && pAbsYTrack)//tvd x y
		{
			double x0, y0;
			this->GetWellPosition(x0, y0);
			double *pmd = new double[pTvdTrack->GetCount()];
			double *ptvd = new double[pTvdTrack->GetCount()];
			double *px = new double[pTvdTrack->GetCount()];
			double *py = new double[pTvdTrack->GetCount()];
			int nValid = 0;
			for (i = 0; i < pTvdTrack->GetCount(); i++)
			{
				md = pTvdTrack->GetDepth(i);
				tvd = pTvdTrack->GetData(i);
				x = pAbsXTrack->GetData(i);
				y = pAbsYTrack->GetData(i);
				if (CXWellCurve::IsValid(tvd) == false
					|| CXWellCurve::IsValid(x) == false
					|| CXWellCurve::IsValid(y) == false)
				{
					continue;
				}
				pmd[nValid] = md;
				ptvd[nValid] = tvd;
				px[nValid] = x;
				py[nValid] = y;

				nValid++;
			}

			double* pData = new double[(nValid + 1) * 3];
			pData[0 * 3] = 0 + x0;
			pData[0 * 3 + 1] = 0 + y0;
			pData[0 * 3 + 2] = 0;
			for (i = 1; i < nValid + 1; i++)
			{
				pData[i * 3] = px[i - 1];
				pData[i * 3 + 1] = py[i - 1];
				pData[i * 3 + 2] = ptvd[i - 1];
			}
			pTrack->ResetData(pData, (nValid + 1) * 3);
			delete pmd;// = new double[pTvdTrack->GetCount()];
			delete ptvd;//  = new double[pTvdTrack->GetCount()];
			delete px;//  = new double[pTvdTrack->GetCount()];
			delete py;//  = new double[pTvdTrack->GetCount()];
		}
		else if (pTvdTrack && pAziTrack && pDipTrack)
		{
			double x0, y0;
			this->GetWellPosition(x0, y0);
			double *pmd = new double[pTvdTrack->GetCount()];
			double *ptvd = new double[pTvdTrack->GetCount()];
			double *px = new double[pTvdTrack->GetCount()];
			double *py = new double[pTvdTrack->GetCount()];
			double* dataDip = new double[pTvdTrack->GetCount()];//倾角
			double* dataAzi = new double[pTvdTrack->GetCount()];//方位角
			int nValid = 0;
			for (i = 0; i < pTvdTrack->GetCount(); i++)
			{
				md = pTvdTrack->GetDepth(i);
				tvd = pTvdTrack->GetData(i);
				x = pAziTrack->GetData(i);
				y = pDipTrack->GetData(i);
				if (CXWellCurve::IsValid(tvd) == false
					|| CXWellCurve::IsValid(x) == false
					|| CXWellCurve::IsValid(y) == false)
				{
					continue;
				}
				pmd[nValid] = md;
				ptvd[nValid] = tvd;
				dataAzi[nValid] = x*M_PI / 180.;
				dataDip[nValid] = y*M_PI / 180.;

				nValid++;
			}



			double preabsx = x0;
			double preabsy = y0;
			double premd = 0;
			double pretvd = 0;
			double ri, mapr, dx, dy;
			for (i = 0; i < nValid; i++)
			{
				mapr = (ptvd[i]-pretvd)*tan(dataDip[i]);
				dx = mapr*sin(dataAzi[i]);
				dy = mapr*cos(dataAzi[i]);
				px[i] = preabsx + dx;
				py[i] = preabsy + dy;
				preabsx = px[i];
				preabsy = py[i];
				pretvd = ptvd[i];
			}




			double* pData = new double[(nValid + 1) * 3];
			pData[0 * 3] = 0 + x0;
			pData[0 * 3 + 1] = 0 + y0;
			pData[0 * 3 + 2] = 0;
			for (i = 1; i < nValid + 1; i++)
			{
				pData[i * 3] = px[i - 1];
				pData[i * 3 + 1] = py[i - 1];
				pData[i * 3 + 2] = ptvd[i - 1];
			}
			pTrack->ResetData(pData, (nValid + 1) * 3);
			delete pmd;// = new double[pTvdTrack->GetCount()];
			delete ptvd;//  = new double[pTvdTrack->GetCount()];
			delete px;//  = new double[pTvdTrack->GetCount()];
			delete py;//  = new double[pTvdTrack->GetCount()];
		}
		//以下是没有tvd的
		else if (pDevYTrack && pDevXTrack)
		{
			double x0, y0;
			this->GetWellPosition(x0, y0);
			double *pmd = new double[pDevYTrack->GetCount()];
			double *ptvd = new double[pDevYTrack->GetCount()];
			double *px = new double[pDevYTrack->GetCount()];
			double *py = new double[pDevYTrack->GetCount()];
			int nValid = 0;
			for (i = 0; i < pDevYTrack->GetCount(); i++)
			{
				md = pDevYTrack->GetDepth(i);
				x = pDevXTrack->GetData(i);
				y = pDevYTrack->GetData(i);

				if (CXWellCurve::IsValid(md) == false
					|| CXWellCurve::IsValid(x) == false
					|| CXWellCurve::IsValid(y) == false)
				{
					continue;
				}
				pmd[nValid] = md;
				px[nValid] = x;
				py[nValid] = y;
				nValid++;
			}

			double mapr, r, predx, predy,pretvd,premd;
			premd = pretvd = predx = predy = 0;
			for (i = 0; i < nValid ; i++)
			{
				mapr = sqrt((predx - px[i])*(predx - px[i])
					+ (predy - py[i])*(predy - py[i]));
				ptvd[i] = pretvd + sqrt((pmd[i] - premd) * (pmd[i] - premd) - mapr*mapr);
				predx = px[i];
				predy = py[i];
				pretvd = ptvd[i];
				premd = pmd[i];
			}


			double* pData = new double[(nValid + 1) * 3];
			pData[0 * 3] = 0 + x0;
			pData[0 * 3 + 1] = 0 + y0;
			pData[0 * 3 + 2] = 0;
			for (i = 1; i < nValid + 1; i++)
			{
				pData[i * 3] = px[i - 1] + x0;
				pData[i * 3 + 1] = py[i - 1] + y0;
				pData[i * 3 + 2] = ptvd[i - 1];
			}
			pTrack->ResetData(pData, (nValid + 1) * 3);

			delete pmd;// = new double[pTvdTrack->GetCount()];
			delete ptvd;//  = new double[pTvdTrack->GetCount()];
			delete px;//  = new double[pTvdTrack->GetCount()];
			delete py;//  = new double[pTvdTrack->GetCount()];
		}
		else if ( pAbsXTrack && pAbsYTrack)
		{
			double x0, y0;
			this->GetWellPosition(x0, y0);
			double *pmd = new double[pAbsXTrack->GetCount()];
			double *ptvd = new double[pAbsXTrack->GetCount()];
			double *px = new double[pAbsXTrack->GetCount()];
			double *py = new double[pAbsXTrack->GetCount()];
			int nValid = 0;
			for (i = 0; i < pAbsXTrack->GetCount(); i++)
			{
				md = pAbsXTrack->GetDepth(i);
				x = pAbsXTrack->GetData(i);
				y = pAbsYTrack->GetData(i);
				if (CXWellCurve::IsValid(md) == false
					|| CXWellCurve::IsValid(x) == false
					|| CXWellCurve::IsValid(y) == false)
				{
					continue;
				}
				pmd[nValid] = md;
				px[nValid] = x;
				py[nValid] = y;

				nValid++;
			}

			double mapr, r, predx, predy,pretvd,premd;
			pretvd = 0;
			predx = x0;
			predy = y0;
			premd = 0;
			for (i = 0; i < nValid; i++)
			{
				mapr = sqrt((predx - px[i])*(predx - px[i])
					+ (predy - py[i])*(predy - py[i]));
				ptvd[i] = pretvd + sqrt((pmd[i] - premd) * (pmd[i] - premd) - mapr*mapr);
				predx = px[i];
				predy = py[i];
				pretvd = ptvd[i];
				premd = pmd[i];
			}


			double* pData = new double[(nValid + 1) * 3];
			pData[0 * 3] = 0 + x0;
			pData[0 * 3 + 1] = 0 + y0;
			pData[0 * 3 + 2] = 0;
			for (i = 1; i < nValid + 1; i++)
			{
				pData[i * 3] = px[i - 1];
				pData[i * 3 + 1] = py[i - 1];
				pData[i * 3 + 2] = ptvd[i - 1];
			}
			pTrack->ResetData(pData, (nValid + 1) * 3);
			delete pmd;// = new double[pTvdTrack->GetCount()];
			delete ptvd;//  = new double[pTvdTrack->GetCount()];
			delete px;//  = new double[pTvdTrack->GetCount()];
			delete py;//  = new double[pTvdTrack->GetCount()];
		}

	}

	if (this &&  this->GetWellPath() && pTimeTrack2222)
	{

		CXWellPath *pwelltrack = this->GetWellPath();
		CXWellTD* pNewVsp = this->GetWellTD();
		//pNewVsp->setObjectName(pWellLog->GetObjectName()	);
		CXWellCurve * pTimeTrack = pTimeTrack2222;
		int datacount = pTimeTrack->GetPointNumber();
		double tvd;
		double *ptvd = new double[datacount];
		double *ptime = new double[datacount];
		int nValid = 0;
		int i;
		double dDataMin,dDataMax;
		pTimeTrack->GetDataRange(dDataMin, dDataMax);

		double divunit = 1.0;
		if (fabs(dDataMin - dDataMax)<10 && qMax(dDataMin , dDataMax)<10)//很小，则表示是s，需要转为ms
		{
			divunit = 1000;
		}
		for (i = 0; i < datacount; i++)
		{
			if (CXWellCurve::IsValid(pTimeTrack->GetData(i)) == false)
			{
				continue;
			}
			ptvd[nValid] = pwelltrack->Md2Tvd(pTimeTrack->GetDepth(i));
			ptime[nValid] = pTimeTrack->GetData(i)*divunit;
			nValid++;
		}

		double* pData = new double[nValid * 2];
		for (i = 0; i < nValid; i++)
		{
			pData[i * 2] = ptvd[i];
			pData[i * 2 + 1] = ptime[i];
		}
		pNewVsp->ResetData(pData, nValid * 2);
		delete ptvd;// = new double[datacount];
		delete ptime;// = new double[datacount];

	}
}

//	Get one attribute, return "" if not found.
QString CXWell::GetAttribute(QString sAttName) const
{
	return m_mapAttributes.value(sAttName, "");
}

//	Get what attributes were added.
QStringList CXWell::GetExistAttribute()
{
	return m_mapAttributes.keys();
}

const QStringList& CXWell::getStandardAttributes()
{
	if(m_staSListAttribute.size() == 0)
	{
		m_staSListAttribute
			<<"Company"		//	Company.
			<<"Field"		//	Field.
			<<"Location"	//	Location.
			<<"Service"		//	Service company.
			<<"Country"		//	Contry.
			<<"Date"		//	Service date.
			<<"API"			//	API.
			<<"UWI"			//	UWI.
			<<"State"		//	State.
			<<"County"		//	County.
			<<"Province"	//	Province.
			<<"License"		//	License.
			<<"Step"		//	Step of samples.
			<<"Type"		//	Well Type
		<< "ViewTempelet";	//	View tempelet
	}

	return m_staSListAttribute;
}

CXWellCurve* CXWell::getCurve(QString strName)
{
	if (strName.isEmpty())
	{
		return NULL;
	}
	while (strName.size()>=1&& strName.right(1) == " ")
	{
		strName.resize(strName.size() - 1);
	}
	strName = strName.toLower();
	QList<CXObject*> lst = GetChildren(EXWellCurve);
	for (int i = 0; i < lst.count(); i++)
	{
		if (lst[i]->GetObjectName().toLower() == strName)
		{
			return (CXWellCurve*)lst[i];
		}
	}
	QMap<QString, QStringList>::iterator it;
	QMap<QString, QStringList>& mapalias = GetProject()->GetCurveAlias();
	for (it = mapalias.begin(); it != mapalias.end(); it++)
	{
		if (it.key().toLower()!= strName)
		{
			continue;
		}
		QStringList &lstValue = it.value();
		for (int z = 0; z < lstValue.count(); z++)
		{
			strName = lstValue[z].toLower();
			for (int i = 0; i < lst.count(); i++)
			{
				if (lst[i]->GetObjectName().toLower() == strName)
				{
					return (CXWellCurve*)lst[i];
				}
			}
		}
	}
	return NULL;
}

CXWellNMR* CXWell::getNMR(QString strName)
{
	if (strName.isEmpty())
	{
		return NULL;
	}
	while (strName.size() >= 1 && strName.right(1) == " ")
	{
		strName.resize(strName.size() - 1);
	}
	strName = strName.toLower();
	QList<CXObject*> lst = GetChildren(EXWellNMR,true);
	for (int i = 0; i < lst.count(); i++)
	{
		if (lst[i]->GetObjectName().toLower() == strName)
		{
			return (CXWellNMR*)lst[i];
		}
	}
	QMap<QString, QStringList>::iterator it;
	QMap<QString, QStringList>& mapalias = GetProject()->GetCurveAlias();
	for (it = mapalias.begin(); it != mapalias.end(); it++)
	{
		if (it.key().toLower() != strName)
		{
			continue;
		}
		QStringList &lstValue = it.value();
		for (int z = 0; z < lstValue.count(); z++)
		{
			strName = lstValue[z].toLower();
			for (int i = 0; i < lst.count(); i++)
			{
				if (lst[i]->GetObjectName().toLower() == strName)
				{
					return (CXWellNMR*)lst[i];
				}
			}
		}
	}
	return NULL;
}
bool KEWellCurveLessThan(const CXWellCurve* p1, const CXWellCurve* p2)
{
	return p1->GetObjectName().toLower()  < p2->GetObjectName().toLower();
}

QList<CXWellCurve*> CXWell::getCurveList()
{
	QList<CXWellCurve*> lst0;
	QList<CXObject*> lst = GetChildren(EXWellCurve);
	for (int i = 0; i < lst.count();i++)
	{
		lst0.append((CXWellCurve*)lst[i]);
	}
	qSort(lst0.begin(), lst0.end(), KEWellCurveLessThan);

	return lst0;
}

QString CXWell::GetIconName() const
{
	if(m_staSListWellIcon.size() != 15)
	{
		m_staSListWellIcon.clear();
		m_staSListWellIcon<<"Well.png";
		m_staSListWellIcon<<"WellOil.png";
		m_staSListWellIcon<<"WellGas.png";
		m_staSListWellIcon<<"WellLowOil.png";
		m_staSListWellIcon<<"WellLowGas.png";
		m_staSListWellIcon<<"WellOG.png";
		m_staSListWellIcon<<"WellWater.png";
		m_staSListWellIcon<<"WellBorefoot.png";
		m_staSListWellIcon<<"WellDry.png";
		m_staSListWellIcon<<"WellAbo.png";
		m_staSListWellIcon<<"WellDrilling.png";
		m_staSListWellIcon<<"WellGeology.png";
		m_staSListWellIcon<<"WellDisPro.png";
		m_staSListWellIcon<<"WellPrePro.png";
		m_staSListWellIcon<<"WellEst.png";
	}

	int iType = 0;
	QString strType = GetAttribute("Type");
	if(strType != "")
	{
		iType = strType.toInt();
		iType = iType < 1 ? 1 : iType;
		iType = iType > 14 ? 14 : iType;
	}

	return m_staSListWellIcon[iType];
}
// 
// void CXWell::SetWellStep(double fStep)
// {
// 	if(fStep < 0.0001)
// 		return;
// 
// 	if(fStep == m_dStep)
// 		return;
// 
// 	m_dStep = fStep;
// 
// 	//	Adapt the end point to new step.
// 	m_dEnd = m_dStart + (int)((m_dEnd - m_dStart) / m_dStep) * m_dStep;
// 
// 	SetModifiedFlag();
// 
// 	//	Re-sample the exist curves.
// }

unsigned CXWell::GetWellCurveSample()
{
	QList<CXWellCurve*> lstCurves = getCurveList();
	if (lstCurves.count()>0)
	{
		return lstCurves[0]->GetPointNumber();
	}
	return (m_dEnd - m_dStart) / m_dStep + 1.9;
}
//	Initialize well range.
// void CXWell::InitializeRange(double dStart, double dStop)
// {
// 	m_dStart = dStart;
// 	m_dEnd = dStop;
// 
// 	SetModifiedFlag();
// }
//#define M_FEPS 2.0E-5
extern void ints8r(int nxin, double dxin, double fxin, double yin[],
double yinl, double yinr, int nxout, double xout[], double yout[]);
//	Expand the start and end, no changing if the range within exist range.
void CXWell::ExpandWellRange(double fStart, double fEnd, double dStep)
{
// 	m_dStart = fStart;
// 	m_dEnd = fEnd;
	if (m_dStart == 9999. &&m_dEnd == 0)
	{
		m_dStart = fStart;
		m_dEnd = fEnd;
	}
	else{
		m_dStart = qMin(m_dStart, fStart);
		m_dEnd = qMax(m_dEnd, fEnd);
	}
	m_dStep = dStep;
	unsigned finalCount = (m_dEnd - m_dStart) / m_dStep + 1.9;
	m_dEnd = m_dStart + m_dStep*finalCount;

	int i;
	QList<CXWellCurve*> lstCurves = getCurveList();
	unsigned newCount = (m_dEnd - m_dStart) / m_dStep + 1.9;
	for (i = 0; i < lstCurves.count(); i++)
	{
		CXWellCurve* pCurve = lstCurves[i];
		if (pCurve->GetStart() == m_dStart
			&& pCurve->GetStop() == m_dEnd
			&& pCurve->GetStep() == m_dStep
			&& pCurve->GetPointNumber() == newCount)
		{
			continue;
		}


		pCurve->ResetDataByResample(pCurve->GetStart(), pCurve->GetStep(), pCurve->GetPointNumber(), pCurve->GetData());
//
//		double* newData = new double[newCount];
//// 		if (pCurve->GetStep() == m_dStep)//间隔相同的地方
//// 		{
//// 			pCurve->GetData(newData, m_dStart, newCount);		
//// 		}
//// 		else//间隔不同
//		{
//			double* intsDataTime = NULL;//第一次插值数据
//			double* srcDataTime = NULL;//第一次插值数据
//			//unsigned intsCount = (pCurve->GetStop() - pCurve->GetStart()) / m_dStep + 1.9;//第一次重采样个数
//			//if (!intsDataTime)
//			{
//				int z;
//				intsDataTime = new double[newCount];
//				for ( z = 0; z < newCount; z++)
//				{
//					intsDataTime[z] = z*m_dStep+m_dStart;
//				}
//				int oldCount = pCurve->GetPointNumber();
//				srcDataTime = new double[oldCount];
//				double oldstep = pCurve->GetStep();
//				double oldstart = pCurve->GetStart();
//				for (z = 0; z < oldCount; z++)
//				{
//					srcDataTime[z] = z*oldstep + oldstart;
//				}
//			}
//			double* intsData = new double[newCount];
//
//			//重采样
//			reSampleCurve(pCurve->GetPointNumber(), srcDataTime, pCurve->GetData()
//				, newCount, intsDataTime, intsData
//				, g_dInvalidData);
//			if (intsDataTime)
//			{
//				delete[]intsDataTime;
//				delete[]srcDataTime;
//			}
//
//			pCurve->ResetData(m_dStart, m_dStep, newCount, intsData);
//			pCurve->GetData(newData, m_dStart, newCount);
//		}
//		if (pCurve->GetObjectName().toLower()=="depth")
//		{
//			for (int z = 0; z < newCount; z++)
//			{
//				newData[z] = m_dStart + z*m_dStep;
//			}
//		}
//		pCurve->ResetData(m_dStart, m_dStep, newCount, newData);
	}

	GetWellComp()->ReomveAllWellCompData();
	SetModifiedFlag();
}

bool CXWell::Serialize(bool bSave)
{
	// base object
	if (!CXObject::Serialize(bSave))
		return false;

	QString strTable = "well";

	// save
	if (bSave)
	{
		QStringList strFieldList;
		strFieldList<<"ID";	
		strFieldList<<"AttributeMapKey";	
		strFieldList<<"AttributeMapValue";
		strFieldList<<"Start";
		strFieldList<<"End";
		strFieldList<<"Step";
		strFieldList<<"KB";

		QList<QVariant> vtList;

		vtList.append(GetObjectID().toString());

		// map
		QStringList listKeys (m_mapAttributes.keys()),listValues;
		for (int i=0; i<listKeys.size(); ++i)
			listValues.append(m_mapAttributes.value(listKeys.at(i)));

		QString strKeys, strValues;

		strKeys = listKeys.join("\r");
		strValues = listValues.join("\r");

		vtList.append(strKeys);
		vtList.append(strValues);

		vtList.append(m_dStart);
		vtList.append(m_dEnd);
		vtList.append(m_dStep);
		vtList.append(m_dKB);

		return ::GetDBIO()->UpdateInsert(strTable, strFieldList, vtList, GetObjectID().toString());
	}
	else
	{
		QStringList strFieldList;
		strFieldList<<"AttributeMapKey";	
		strFieldList<<"AttributeMapValue";
		strFieldList<<"Start";
		strFieldList<<"End";
		strFieldList<<"Step";
		strFieldList << "KB";

		QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());

		if( query.first() )
		{
			int nIndex = -1;

			QString strKeys = query.value(++nIndex).toString();
			QString strValues = query.value(++nIndex).toString();
			QStringList strListKeys = strKeys.split("\r");
			QStringList strListValues = strValues.split("\r");

			for (int i=0; i<strListKeys.size(); ++i)
			{
				m_mapAttributes.insert(strListKeys.at(i), strListValues.at(i));
			}
			
			m_dStart = query.value(++nIndex).toDouble();
			m_dEnd = query.value(++nIndex).toDouble();
			m_dStep = query.value(++nIndex).toDouble();
			m_dKB = query.value(++nIndex).toDouble();
		}

		return true;
	}
}

bool CXWell::SerializeData(CXArchive& ar)
{
	if (!CXObject::SerializeData(ar))
		return false;

	if (ar.IsSaving())
	{
		ar << m_sTD;
	}
	else
	{
		ar >> m_sTD;
	}

	return true;
}

QStringList CXWell::GetDescription()
{
	QStringList strListDesc;

	double dX, dY;
	this->GetWellPosition(dX, dY);
	QString strPos = "X: " + QString::number(dX) + "	Y: " + QString::number(dY, 'f', 0);
	QList<CXObject *> listCurve = GetChildren(EXWellCurve);

	if(::UsingChinese())
	{
		strListDesc<<GetTr("井口坐标")<<strPos;
		if(!listCurve.isEmpty())
			strListDesc<<GetTr("测井曲线数目")<<QString::number(listCurve.size());
	}
	else
	{
		strListDesc<<"Well header position"<<strPos;
		if(!listCurve.isEmpty())
			strListDesc<<GetTr("Log curve count")<<QString::number(listCurve.size());
	}

	QStringList sListApp = this->GetExistAttribute();
	for(int i = 0; i < sListApp.size(); i++)
	{
		strListDesc<<sListApp[i]<<this->GetAttribute(sListApp[i]);
	}

	return strListDesc;
}

QList<CXObject *> CXWell::GetSpecialCurveList(unsigned int iTemplateID)
{
	QList<CXObject *> listCurve;
	QList<CXObject *> listAllCurves = GetChildren(EXWellCurve);

	for each (CXObject *pCurve in listAllCurves)
	{
		if (pCurve->GetTemplateID() == iTemplateID)
			listCurve << pCurve;
	}

	return listCurve;
}

bool CXWell::GetXYAndTWT(vector<double>& vecX, vector<double>& vecY, vector<double>& vecTWT, vector<double>& vecMD)
{
	CXWellPath* pWellPath = this->GetWellPath();

	// get X Y Z from path
	unsigned int nPathDataNum;
	double* pPathData = pWellPath->GetData(nPathDataNum);
	double* pMDData = pWellPath->GetMdData();
	double* pTWTData = pWellPath->GetTWTData();

	if(!pTWTData)
		return false;

	// get well path data
	int nPathPointNum = nPathDataNum / 3;
	vecX.resize(nPathPointNum);
	vecY.resize(nPathPointNum);
	vecTWT.resize(nPathPointNum);
	vecMD.resize(nPathPointNum);

	for (int i = 0; i < nPathPointNum; i++)
	{
		vecX[i] = pPathData[3 * i];
		vecY[i] = pPathData[3 * i + 1];
	}

	memcpy(&vecMD[0], pMDData, sizeof(double) * nPathPointNum);
	memcpy(&vecTWT[0], pTWTData, sizeof(double) * nPathPointNum);

	return true;
}

void CXWell::SetKB(double dKB)
{
	if (m_dKB == dKB)
		return;

	m_dKB = dKB;
	this->SetModifiedFlag();
}

#include "xwellcurvealias.h"
#include "xtemplate.h"
CXWellCurve* CXWell::findOrCreateTrack( QString strName)
{
	if (strName.isEmpty())
	{
		strName = "noName";
	}
	CXWellCurve* pF = this->getCurve(strName);
	if (pF)
	{
		return pF;
	}

	double dStart, dEnd, dStep;

	this->GetDepthRange(dStart, dEnd);
	dStep = this->GetWellStep();
	unsigned nNum = (dEnd - dStart) / dStep + 1.9;
	nNum = this->GetWellCurveSample();
	double *pNewData = new double[nNum];
	for (int i = 0; i < nNum; i++)
	{
		pNewData[i] = g_dInvalidData;
	}

	CXWellCurve *pNewCurve = new CXWellCurve(strName);
	pNewCurve->ResetData(dStart, dStep, nNum, pNewData);
	this->AddChild(pNewCurve);

	CXObject *pAlias = CXWellCurveAlias::GetAlias(strName);
	CXTemplate *pTemplate = CXTemplate::GetTemplate(strName);
	pAlias->SetTemplateID(pTemplate->GetID());
	pNewCurve->SetAliasID(pAlias->GetObjectID());
	pNewCurve->AddEvent(EAdded);

	return pNewCurve;
}
CXWellCurve* CXWell::CoypCurve(CXWellCurve* pOri, QString strName)
{
	CXWellCurve *pCurve = this->findOrCreateTrack(strName);
	double* pNewData = new double[pOri->GetCount()];
	memcpy(pNewData, pOri->GetData(), sizeof(double)*pOri->GetCount());
	pCurve->ResetData(pOri->GetStart(), pOri->GetStep(), pOri->GetCount(), pNewData);
	return pCurve;
}

void CXWell::SetActivatedTDName(QString sTDName)
{
	m_sTD = sTDName;
	SetModifiedFlag();

	//	This will force the wellpath to re-calcualte TWT.
	CXWellPath *pPath = GetWellPath();
	pPath->CleanTWTData();
}