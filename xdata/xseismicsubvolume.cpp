#include "xseismicsubvolume.h"
#include "xobjectfactory.h"
#include "x3dsurvey.h"
#include "xseismicdatavolume.h"
#include "xglobal.h"
#include <cassert>

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXSeismicSubVolume)
EXSeismicSubVolume
END_REGISTER_OBJECT_TO_FACTORY(CXSeismicSubVolume)

CXSeismicSubVolume::CXSeismicSubVolume(QString sName, int iStartInline, int iEndInline, int iStartXline, int iEndXline, double dStartTime, double dEndTime)
:CXObject(sName), m_iStartInline(iStartInline), m_iEndInline(iEndInline), m_iStartXline(iStartXline), m_iEndXline(iEndXline), m_dStartTime(dStartTime), m_dEndTime(dEndTime)
{
	SetObjectType(EXSeismicSubVolume);
	SetIconName("SubVolume.png");
}

QUuid CXSeismicSubVolume::GetSurveyID()
{
	CXObject* pParentObj = this->GetParent();

	QUuid surveyID;

	while (pParentObj)
	{
		if(pParentObj->GetObjectType() == EX3DSurvey)
		{
			surveyID =  pParentObj->GetObjectID();
			break;
		}

		pParentObj = pParentObj->GetParent();
	}

	return surveyID;	
}

CXSeismicUTMTool CXSeismicSubVolume::GetUTM()
{
	CXObject* pParentObj = this->GetParent();

	while (pParentObj)
	{
		if(pParentObj->GetObjectType() == EX3DSurvey)
		{
			CX3DSurvey *pSurvey = (CX3DSurvey *)pParentObj;
			return pSurvey->GetUTM();
		}

		pParentObj = pParentObj->GetParent();
	}

	assert(false);

	return CXSeismicUTMTool();
}

CXSeismicDataVolume* CXSeismicSubVolume::GetDefaultDataVolume()
{
	CX3DSurvey *pSurvey = NULL;
	CXObject* pParentObj = this->GetParent();

	while (pParentObj)
	{
		if(pParentObj->GetObjectType() == EX3DSurvey)
		{
			pSurvey = (CX3DSurvey *)pParentObj;
			break;
		}

		pParentObj = pParentObj->GetParent();
	}

	if(!pSurvey)
		return NULL;

	// return the first data volume
	for (CXObject *pObj : pSurvey->GetChildren(EXSeismicDataVolume, true))
	{
		auto pDV = dynamic_cast<CXSeismicDataVolume*>(pObj);
		if (pDV && !pDV->IsPrestack())
		{
			return pDV;
		}
	}

	return NULL;
}

bool CXSeismicSubVolume::SerializeData(CXArchive &ar)
{
	if (ar.IsSaving())
	{
		ar<<m_iStartInline;
		ar<<m_iEndInline;
		ar<<m_iStartXline;
		ar<<m_iEndXline;
		ar<<m_dStartTime;
		ar<<m_dEndTime;
	}
	else
	{
		ar>>m_iStartInline;
		ar>>m_iEndInline;
		ar>>m_iStartXline;
		ar>>m_iEndXline;
		ar>>m_dStartTime;
		ar>>m_dEndTime;
	}

	return true;
}

void CXSeismicSubVolume::_SetSelfDimension()
{
	CXSeismicDataVolume* pDV  = GetDefaultDataVolume();
	if (!pDV)
		return;

	double xmin, xmax, ymin, ymax, zmin, zmax;
	pDV->GetDimension(xmin, xmax, ymin, ymax, zmin, zmax);

	this->_SetDimension(xmin, xmax, ymin, ymax, zmin, zmax);	
}

void CXSeismicSubVolume::GetDataRange(int& iStartInline, int& iEndInline, int& iStartXline, int& iEndXline, double& dStartTime, double& dEndTime)
{
	if (m_dStartTime == -999.)
		_SetSelfDimension();

	iStartInline	= m_iStartInline;
	iEndInline		= m_iEndInline;
	iStartXline		= m_iStartXline;
	iEndXline		= m_iEndXline;
	dStartTime		= m_dStartTime;
	dEndTime		= m_dEndTime;
}

//	Change data range, iType from 0 to 5, means start/end inline/xline/time, dVal is the new value. 
//	Return false while iType beyond 0~5 or new end inline less than start inline and so on...
bool CXSeismicSubVolume::SetDataRange(unsigned char iType, double dVal)
{
	if(iType == 0)
	{
		if(dVal > m_iEndInline)
			return false;
		
		m_iStartInline = (int)dVal;
	}
	else if(iType == 1)
	{
		if(dVal < m_iStartInline)
			return false;
		
		m_iEndInline = (int)dVal;
	}
	else if(iType == 2)
	{
		if(dVal > m_iEndXline)
			return false;
		
		m_iStartXline = (int)dVal;
	}
	else if(iType == 3)
	{
		if(dVal < m_iStartXline)
			return false;
		
		m_iEndXline = (int)dVal;
	}
	else if(iType == 4)
	{
		if(dVal > m_dEndTime)
			return false;
		
		m_dStartTime = dVal;
	}
	else if(iType == 5)
	{
		if(dVal < m_dStartTime)
			return false;
		
		m_dEndTime = dVal;
	}
	else
		return false;

	return true;
}

QStringList CXSeismicSubVolume::GetDescription()
{
	QStringList strListDesc;

	if(::UsingChinese())
	{
		strListDesc<<GetTr("起始主测线")<<QString::number(m_iStartInline);
		strListDesc<<GetTr("终止主测线")<<QString::number(m_iEndInline);
		strListDesc<<GetTr("起始联络测线")<<QString::number(m_iStartXline);
		strListDesc<<GetTr("终止联络测线")<<QString::number(m_iEndXline);
		strListDesc<<GetTr("起始时间")<<QString::number(m_dStartTime);
		strListDesc<<GetTr("终止时间")<<QString::number(m_dEndTime);
	}
	else
	{
		strListDesc<<"Start Inline"<<QString::number(m_iStartInline);
		strListDesc<<"End Inline"<<QString::number(m_iEndInline);
		strListDesc<<"Start Crossline"<<QString::number(m_iStartXline);
		strListDesc<<"End Crossline"<<QString::number(m_iEndXline);
		strListDesc<<"Start Time"<<QString::number(m_dStartTime);
		strListDesc<<"End Time"<<QString::number(m_dEndTime);
	}

	return strListDesc;
}

CXObject* CXSeismicSubVolume::_GetHistogramObject()
{
	return GetDefaultDataVolume();
}
