#include "x3dsurvey.h"
#include "xobjectfactory.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xseismicsubvolume.h"
#include "xseismicdatavolume.h"
#include "xseismicdataline.h"
#include "xgeneralfolder.h"
#include "xtree.h"
#include "xglobal.h"
#include "xdbio.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CX3DSurvey)
EX3DSurvey
END_REGISTER_OBJECT_TO_FACTORY(CX3DSurvey)

CX3DSurvey::CX3DSurvey()
{
	m_dDatum = 0.;
	m_dRepVel = 2000;
}

CX3DSurvey::CX3DSurvey(const CXSeismicUTMTool& utm, const QString& strName) :CXObject(strName)
{
	m_utm.Copy(const_cast<CXSeismicUTMTool*>(&utm));
	SetIconName("3DSurveyFolder.png");
	SetObjectType(EX3DSurvey);

	m_dDatum = 0.;
	m_dRepVel = 2000;
}

bool CX3DSurvey::SerializeData(CXArchive& ar)
{
	m_utm.SerializeData(ar);

	return true;
}

CXSeismicDataVolume* CX3DSurvey::GetDefaultDV(bool bIncludePrestack)
{
	auto pDVFolder = dynamic_cast<CXGeneralFolder*>(GetFolder(EXSeismicDVFolder));
	if (!pDVFolder) return nullptr;

	auto listDV = pDVFolder->GetChildren(EXSeismicDataVolume, true);
	if (listDV.isEmpty()) return nullptr;

	if (bIncludePrestack)
		return dynamic_cast<CXSeismicDataVolume*>(listDV.front());

	for (auto pObj : listDV)
	{
		auto pDV = dynamic_cast<CXSeismicDataVolume*>(pObj);
		if (pDV && !pDV->IsPrestack()) return pDV;
	}

	return nullptr;
}
CXSeismicSubVolume* CX3DSurvey::CreateDefaultSubVolume()
{
	CXSeismicDataVolume *pDV = GetDefaultDV(false);
	if (!pDV)
		return NULL;

	CXSeismicUTMTool& utm = pDV->GetUTM();
	int iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc;
	utm.GetLineNumRange(iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc);

	int iStartInline = iFirstInline + iInlineInc * (utm.GetNI() / 4);
	int iEndInline = iFirstInline + 3 * iInlineInc * (utm.GetNI() / 4);
	int iStartXline = iFirstCrossline + iCrosslineInc * (utm.GetNJ() / 4);
	int iEndXline = iFirstCrossline + 3 * iCrosslineInc * (utm.GetNJ() / 4);
	double dSTime = -999., dETime, dSampleInv;
	if (!pDV->IsPrestack())
		pDV->GetSamplingRange(dSTime, dETime, dSampleInv);
	double dStartTime = dSTime + dSampleInv * (pDV->GetSamplingQty() / 4);
	double dEndTime = dSTime + 3 * dSampleInv * (pDV->GetSamplingQty() / 4);
	QString sName = "Sub Volume";
	sName = GetUnallocatedName(sName);
	CXSeismicSubVolume *pSubVolume = new CXSeismicSubVolume(sName, iStartInline, iEndInline, iStartXline, iEndXline, dStartTime, dEndTime);
	CXObject *pSectionFolder = GetFolder(EXSeismicSectionFolder);
	pSectionFolder->AddChild((CXObject *)pSubVolume);

	return pSubVolume;
}

CXSeismicSection* CX3DSurvey::CreateDefaultSection(EXSectionType eSectionType)
{
	int iIDX = -999, iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc;
	m_utm.GetLineNumRange(iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc);

	if (eSectionType == eInlineSection)
	{
		iIDX = iFirstInline + iInlineInc * (m_utm.GetNI() / 2);
	}
	else if (eSectionType == eCrosslineSection)
	{
		iIDX = iFirstCrossline + iCrosslineInc * (m_utm.GetNJ() / 2);
	}
	else if (eSectionType == eTimeSlice)
	{
		QList<CXObject*> listDV = GetChildren(EXSeismicDataVolume, true);

		if (!listDV.isEmpty())
		{
			CXSeismicDataVolume* pDV = (CXSeismicDataVolume *)listDV[0];
			double dSTime, dETime, dSampleInv;
			pDV->GetSamplingRange(dSTime, dETime, dSampleInv);
			pDV->GetSamplingQty();
			iIDX = (int)(dSTime + dSampleInv * (pDV->GetSamplingQty() / 2));
		}
	}

	if (iIDX == -999)
		return NULL;

	CXSeismicSection *pSection = new CXSeismicSection(eSectionType, (double)iIDX);
	CXObject *pSectionFolder = GetFolder(EXSeismicSectionFolder);
	pSectionFolder->AddChild((CXObject *)pSection);

	return pSection;
}

CXObject* CX3DSurvey::GetFolder(EXObjectType eObjType, bool bCreate)
{
	const auto& listObj = GetChildren(eObjType);
	if (listObj.isEmpty())
	{
		if (!bCreate)
			return NULL;

		CXGeneralFolder *pFolder;
		if (eObjType == EXSeismicDVFolder)
			pFolder = new CXGeneralFolder("Seismic Data Volumes", EXSeismicDVFolder, "SeismicDVFolder.png");
		else if (eObjType == EXSeismicDataLineFolder)
			pFolder = new CXGeneralFolder("Seismic Data Lines", EXSeismicDataLineFolder, "SeismicSectionFolder.png");
		else if (eObjType == EXSeismicSectionFolder)
			pFolder = new CXGeneralFolder("Seismic Sections", EXSeismicSectionFolder, "SeismicSectionFolder.png");
		else if (eObjType == EXHorizonFolder)
			pFolder = new CXGeneralFolder("Horizons", EXHorizonFolder, "HorizonFolder.png");
		else if (eObjType == EXFaultFolder)
			pFolder = new CXGeneralFolder("Faults", EXFaultFolder, "FaultFolder.png");
		else if (eObjType == EXGSFolder)
			pFolder = new CXGeneralFolder("Stress", EXGSFolder, "StressFolder.png");
		else
			return NULL;

		AddChild(pFolder);

		::AddObjectEvent(pFolder);

		return pFolder;
	}

	return listObj.at(0);
}

QStringList CX3DSurvey::GetDescription()
{
	QStringList strList;

	int iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc;
	m_utm.GetLineNumRange(iFirstInline, iLastInline, iInlineInc, iFirstCrossline, iLastCrossline, iCrosslineInc);
	strList << "Inline range:" << QString::number(iFirstInline) + " ~ " + QString::number(iLastInline);
	strList << "Inline step:" << QString::number(iInlineInc);
	strList << "Inline number:" << QString::number(m_utm.GetNI());
	strList << "Crossline range:" << QString::number(iFirstCrossline) + " ~ " + QString::number(iLastCrossline);
	strList << "Crossline step:" << QString::number(iCrosslineInc);
	strList << "Crossline number:" << QString::number(m_utm.GetNJ());

	return strList;
}

QList<CXObject*> CX3DSurvey::FetchAllSections()
{
	QList<CXObject*> listSection;
	
	for (auto pObj : GetChildren(EXSeismicSection))
		listSection << pObj;

	for (auto pObj : GetChildren(EXRandomSection))
		listSection << pObj;

	for (auto pObj : GetChildren(EXSeismicSubVolume))
		listSection << pObj;

	return listSection;
}

bool CX3DSurvey::Serialize(bool bSave)
{
	// base object
	if (!CXObject::Serialize(bSave))
		return false;

	QString strTable = "survey3d";

	// save
	if (bSave)
	{
		QStringList strFieldList;
		strFieldList << "ID";
		strFieldList << "Datum";
		strFieldList << "RepVel";

		QList<QVariant> vtList;

		vtList.append(GetObjectID().toString());
		vtList.append(m_dDatum);
		vtList.append(m_dRepVel);

		return ::GetDBIO()->UpdateInsert(strTable, strFieldList, vtList, GetObjectID().toString());
	}
	else
	{
		QStringList strFieldList;
		strFieldList << "Datum";
		strFieldList << "RepVel";

		QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());

		if (query.first())
		{
			int nIndex = -1;

			m_dDatum = query.value(++nIndex).toDouble();
			m_dRepVel = query.value(++nIndex).toDouble();
		}

		return true;
	}
}

void CX3DSurvey::SetDatum(double dDatum)
{
	if (m_dDatum == dDatum)
		return;

	m_dDatum = dDatum;
	this->SetModifiedFlag();
}
void CX3DSurvey::SetRepVelocity(double dRepVel)
{
	if (m_dRepVel == dRepVel)
		return;

	m_dRepVel = dRepVel;
	this->SetModifiedFlag();
}
void CX3DSurvey::GetDatumAndRepVelocity(double& dDatum, double &dRepVel)
{
	dDatum = m_dDatum;
	dRepVel = m_dRepVel;
}

QList<CXObject *> CX3DSurvey::GetAllCandidates(CXObject *pObj)
{
	int i;
	QList<CXObject *> listResults;
	CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(pObj);
	CXSeismicRandomSection *pRSection = dynamic_cast<CXSeismicRandomSection *>(pObj);

	//	First check all data volumes.
	QList<CXObject *> listDV = GetChildren(EXSeismicDataVolume, true);
	foreach(CXObject *pCan, listDV)
	{
		CXSeismicDataVolume *pDV = (CXSeismicDataVolume *)pCan;
		CXSeismicUTMTool& utm = pDV->GetUTM();
		
		if (pObj->GetObjectType() == EXSeismicSection)
		{
			int iInline, iCrossline;

			if (pSection->GetSectionType() == eInlineSection)
			{
				iInline = (int)pSection->GetSectionNumber();
				iCrossline = utm.GetFirstCrossline();
			}
			else
			{
				iInline = utm.GetFirstInline();
				iCrossline = (int)pSection->GetSectionNumber();
			}

			if (utm.GetIndexOfOneNode(iInline, iCrossline) != -1)
			{
				listResults.append(pCan);
			}
		}
		else if (pObj->GetObjectType() == EXRandomSection)
		{
			vector<int> vecInline, vecCrossline;
			pRSection->GetLineNumbers(vecInline, vecCrossline);

			for (i = 0; i < vecInline.size(); i++)
			{
				if (utm.GetIndexOfOneNode(vecInline[i], vecCrossline[i]) == -1)
					break;
			}

			if (i >= vecInline.size())
				listResults.append(pCan);
		}
	}
	
	//	Then check all data lines.
	QList<CXObject *> listDL = GetChildren(EXSeismicDataLine, true);
	if (pObj->GetObjectType() == EXSeismicSection)
	{
		foreach(CXObject *pCan, listDL)
		{
			CXSeismicDataLine *pDL = (CXSeismicDataLine *)pCan;
			if (pDL->GetDataLineType() != pSection->GetSectionType())
				continue;

			if (pDL->GetLineNumber() == pSection->GetSectionNumber())
				listResults.append(pCan);
		}
	}
	else if (pObj->GetObjectType() == EXRandomSection)
	{
		foreach(CXObject *pCan, listDL)
		{
			CXSeismicDataLine *pDL = (CXSeismicDataLine *)pCan;
			if (pDL->GetDataLineType() != eRandomSection)
				continue;

			if (pDL->GetRefID() == pRSection->GetObjectID())
				listResults.append(pCan);
		}
	}

	return listResults;
}