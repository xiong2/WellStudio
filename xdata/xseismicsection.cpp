#include "xseismicsection.h"
#include "xobjectfactory.h"
#include "x3dsurvey.h"
#include "xseismicdatavolume.h"
#include "xglobal.h"
#include "xgeneralfolder.h"


BEGIN_REGISTER_OBJECT_TO_FACTORY(CXSeismicSection)
EXSeismicSection
END_REGISTER_OBJECT_TO_FACTORY(CXSeismicSection)

CXSeismicSection::CXSeismicSection(EXSectionType eSectionType, double dLineNumber)
: m_eSectionType(eSectionType), m_dSectionLineNumber(dLineNumber)
{
	SetObjectType(EXSeismicSection);

	if(eSectionType == eInlineSection)
	{
		SetObjectName("Inline " + QString::number(static_cast<int>(dLineNumber)));
		SetIconName("Inline.png");
	}
	else if(eSectionType == eCrosslineSection)
	{
		SetObjectName("Crossline " + QString::number(static_cast<int>(dLineNumber)));
		SetIconName("Crossline.png");
	}
	else if(eSectionType == eTimeSlice)
	{
		SetObjectName("Time Slice " + QString::number(static_cast<int>(dLineNumber)));
		SetIconName("TimeSlice.png");
	}
	else if(eSectionType == eInlineProfile)
	{
		SetObjectName("Inline Profile " + QString::number(static_cast<int>(dLineNumber)));
		SetIconName("InlinePic.png");
	}

	m_sPictureFile	= "";
	m_iStartTrace	= -1;
	m_iEndTrace		= -1;
	m_dStartTime	= 0;
	m_dEndTime		= 0;
}

CXSeismicSection::CXSeismicSection(QString strPictureFile, int iLineID, int iStartTrace, int iEndTrace, double dStartTime, double dEndTime)
: m_eSectionType(eInlineProfile), m_dSectionLineNumber(iLineID)
{
	SetObjectType(EXSeismicSection);
	SetObjectName("Inline Profile " + QString::number(iLineID));
	SetIconName("InlinePic.png");

	m_sPictureFile	= strPictureFile;
	m_iStartTrace	= iStartTrace;
	m_iEndTrace		= iEndTrace;
	m_dStartTime	= dStartTime;
	m_dEndTime		= dEndTime;
}

QString CXSeismicSection::GetTypeString()
{
	if (m_eSectionType == eInlineSection)
		return "Inline Section";
	else if (m_eSectionType == eCrosslineSection)
		return "Crossline Section";
	else if (m_eSectionType == eTimeSlice)
		return "Time Slice";
	else
		return "Inline Profile";
}

void CXSeismicSection::SetSectionNumber(double lineNumber)
{
	QString objName = GetObjectName();
	QString sectionNumber = QString::number(m_dSectionLineNumber);
	int pos = objName.indexOf(sectionNumber);
	if (pos != -1)
	{
		objName.replace(pos, sectionNumber.size(), QString::number(lineNumber));
		SetObjectName(objName);
	}

	m_dSectionLineNumber = lineNumber;
}

QUuid CXSeismicSection::GetSurveyID()
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

CXSeismicUTMTool CXSeismicSection::GetUTM()
{
	CXObject* pParentObj = this->GetParent();

	while (pParentObj)
	{
		if(pParentObj->GetObjectType() == EX3DSurvey)
		{
			CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(pParentObj);
			return pSurvey->GetUTM();
		}

		pParentObj = pParentObj->GetParent();
	}

	Q_ASSERT(false);

	return CXSeismicUTMTool();
}

double CXSeismicSection::GetLineStep()
{
	CXSeismicUTMTool utm = GetUTM();

	if (m_eSectionType == eInlineSection)
		return utm.GetCrosslineIncrement();
	else if (m_eSectionType == eCrosslineSection)
		return utm.GetInlineIncrement();
	else if (m_eSectionType == eTimeSlice)
	{
		CXSeismicDataVolume* pDV = this->GetDefaultDataVolume();
		if (pDV)
			return pDV->GetSampleInterval();
		else
			return 1.;
	}
	else
		return 1.;

}

CXSeismicDataVolume* CXSeismicSection::GetDefaultDataVolume(bool bIncludePrestack)
{
	if (m_eSectionType == eInlineProfile) return nullptr;

	CX3DSurvey* pSurvey = nullptr;
	auto pParentObj = this->GetParent();

	while (pParentObj)
	{
		if (pParentObj->GetObjectType() == EX3DSurvey)
		{
			pSurvey = dynamic_cast<CX3DSurvey *>(pParentObj);
			break;
		}

		pParentObj = pParentObj->GetParent();
	}

	if (!pSurvey) return nullptr;
	
	return pSurvey->GetDefaultDV(bIncludePrestack);
}

bool CXSeismicSection::GetProfileGeometry(int& iLineNum, int& iStartTrace, int& iEndTrace, double& dStartTime, double& dEndTime)
{
	if(m_eSectionType != eInlineProfile)
		return false;

	iLineNum		= static_cast<int>(m_dSectionLineNumber);
	iStartTrace		= m_iStartTrace;
	iEndTrace		= m_iEndTrace;
	dStartTime		= m_dStartTime;
	dEndTime		= m_dEndTime;

	return true;
}

bool CXSeismicSection::SerializeData(CXArchive &ar)
{
	int iType = m_eSectionType;
	if (ar.IsSaving())
	{
		ar<<iType;
		ar<<m_dSectionLineNumber;

		ar<<m_iStartTrace;
		ar<<m_iEndTrace;
		if(m_eSectionType == eInlineProfile)
		{
			ar<<m_sPictureFile;
			ar<<m_dStartTime;
			ar<<m_dEndTime;
		}
	}
	else
	{
		ar>>iType;
		ar>>m_dSectionLineNumber;
		ar>>m_iStartTrace;
		ar>>m_iEndTrace;

		m_eSectionType = static_cast<EXSectionType>(iType);
		if(m_eSectionType == eInlineProfile)
		{
			ar>>m_sPictureFile;
			ar>>m_dStartTime;
			ar>>m_dEndTime;
		}
	}

	return true;
}

int CXSeismicSection::GetSectionIndex()
{
    return static_cast<int>(GetSectionIndexF());
}

double CXSeismicSection::GetSectionIndexF()
{
    auto utm = GetUTM();
    if (eInlineSection == m_eSectionType)
        return (m_dSectionLineNumber - utm.GetFirstInline()) / utm.GetInlineIncrement();
    if (eCrosslineSection == m_eSectionType)
        return (m_dSectionLineNumber - utm.GetFirstCrossline()) / utm.GetCrosslineIncrement();

    Q_ASSERT(!"unknown section type.");
    return -1.0;
}

void CXSeismicSection::_SetSelfDimension()
{
	double xmin, xmax, ymin, ymax, zmin, zmax;
	CXSeismicUTMTool utm = GetUTM();
	utm.GetDimensionRange(xmin, xmax, ymin, ymax);

	auto pDV = dynamic_cast<CXSeismicDataVolume *>(GetDefaultDataVolume());
	if (pDV)
	{
		double zInc;
		pDV->GetSamplingRange(zmin, zmax, zInc);
	}
	else if(m_eSectionType == eInlineProfile)
	{
		zmin = m_dStartTime;
		zmax = m_dEndTime;
	}
	else
	{
		zmin = zmax = 0.;
	}

	_SetDimension(xmin, xmax, ymin, ymax, zmin, zmax);	
}

CXObject* CXSeismicSection::_GetHistogramObject()
{
	return GetDefaultDataVolume();
}
