#include "xseismicrandomsection.h"
#include "xobjectfactory.h"
#include "x3dsurvey.h"
#include "xseismicdatavolume.h"
#include <cassert>
#include "xglobal.h"
#include "xgeneralfolder.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXSeismicRandomSection)
EXRandomSection
END_REGISTER_OBJECT_TO_FACTORY(CXSeismicRandomSection)

CXSeismicRandomSection::CXSeismicRandomSection(const QString& strName)
: CXObject(strName)
{
	SetObjectType(EXRandomSection);
	SetIconName("RandomSection.png");
}

CXSeismicRandomSection::~CXSeismicRandomSection()
{
}

CXSeismicDataVolume* CXSeismicRandomSection::GetDefaultDataVolume(bool bIncludePrestack)
{
	CX3DSurvey *pSurvey = nullptr;
	auto pParentObj = this->GetParent();

	while (pParentObj)
	{
		if(pParentObj->GetObjectType() == EX3DSurvey)
		{
			pSurvey = dynamic_cast<CX3DSurvey *>(pParentObj);
			break;
		}

		pParentObj = pParentObj->GetParent();
	}

	if (!pSurvey) return nullptr;
	
	return pSurvey->GetDefaultDV(bIncludePrestack);
}

QUuid CXSeismicRandomSection::GetSurveyID()
{
	CXObject* pParentObj = this->GetParent();

	while (pParentObj)
	{
		if (pParentObj->GetObjectType() == EX3DSurvey)
		{
			CX3DSurvey* pSurvey = dynamic_cast<CX3DSurvey*>(pParentObj);
			return pSurvey->GetObjectID();
		}
	}

	return QUuid();
}

CXSeismicUTMTool CXSeismicRandomSection::GetUTM()
{
	CXObject* pParentObj = this->GetParent();

	while (pParentObj)
	{
		if (pParentObj->GetObjectType() == EX3DSurvey)
		{
			CX3DSurvey* pSurvey = dynamic_cast<CX3DSurvey*>(pParentObj);
			return pSurvey->GetUTM();
		}
	}

	Q_ASSERT(false);

	return CXSeismicUTMTool();
}

bool CXSeismicRandomSection::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << (unsigned int)m_vecTurningPoint.size();
		for (auto turningPoint : m_vecTurningPoint) 
			ar << turningPoint;
	}
	else
	{
		unsigned int nSize;
		ar >> nSize;

		m_vecTurningPoint.resize(nSize);
		for (auto &turningPoint : m_vecTurningPoint)
			ar >> turningPoint;
	}

	return true;
}

void CXSeismicRandomSection::_SetSelfDimension()
{
	auto pDV = dynamic_cast<CXSeismicDataVolume*>(GetDefaultDataVolume());
	if (!pDV)
		return;

	double xmin, xmax, ymin, ymax, zmin, zmax;
	pDV->GetDimension(xmin, xmax, ymin, ymax, zmin, zmax);

	this->_SetDimension(xmin, xmax, ymin, ymax, zmin, zmax);	
}

void CXSeismicRandomSection::SetPolyline(const vector<double>& vecX, const vector<double>& vecY)
{
	if (vecX.empty() || vecY.empty())
		return;

	if (vecX.size() != vecY.size())
		return;

	m_vecTurningPoint.clear();
	m_vecTPTraceIndex.clear();
	m_vecTraceLocation.clear();

	int nSize = (int) vecX.size();

	for (int i=0; i<nSize; ++i)
	{	
		m_vecTurningPoint.push_back (vecX[i]);
		m_vecTurningPoint.push_back (vecY[i]);	
		
	}

	_CreateTraceLocations();

	SetModifiedFlag();
}

void CXSeismicRandomSection::Append(double dX, double dY)
{
	m_vecTurningPoint.push_back(dX);
	m_vecTurningPoint.push_back(dY);

	_CreateTraceLocations();

	SetModifiedFlag();
}

bool CXSeismicRandomSection::SetXYByIndex(uint i, double dX, double dY)
{
	if (i >= m_vecTurningPoint.size())
		return false;

	m_vecTurningPoint[i * 2] = dX;
	m_vecTurningPoint[i * 2 + 1] = dY;

	_CreateTraceLocations();

	SetModifiedFlag();

	return true;
}

void CXSeismicRandomSection::_AddOneTurningPoint(CXSeismicUTMTool& UTM, double dXNext, double dYNext)
{

	if (m_vecTraceLocation.empty() )
	{
		int iInlineNum, iXlineNum;
		UTM.XYToLine (dXNext, dYNext, iInlineNum, iXlineNum);
		STraceLocation traceLocation(iInlineNum, iXlineNum, dXNext, dYNext);
		m_vecTraceLocation.push_back (traceLocation);
		m_vecTPTraceIndex.push_back (0);
	}
	else
	{
		double dX, dY;
		int iInlineNum, iXlineNum, iInlineNumNext, iXlineNumNext, nInlineInc, nXlineInc;

		// first point
		int nSize = (int)m_vecTraceLocation.size();
		dX = m_vecTraceLocation.at(nSize-1).m_dX;
		dY = m_vecTraceLocation.at(nSize-1).m_dY;
		iInlineNum = m_vecTraceLocation.at(nSize-1).m_iInlineNum;
		iXlineNum = m_vecTraceLocation.at(nSize-1).m_iXlineNum;

		// next point
		UTM.XYToLine (dXNext, dYNext, iInlineNumNext, iXlineNumNext);
		nInlineInc = UTM.GetInlineIncrement();
		nXlineInc = UTM.GetCrosslineIncrement();

		// trace between first and next
		int nInlineStepNum = qAbs ((iInlineNumNext - iInlineNum)/nInlineInc);
		int nXlineStepNum = qAbs ((iXlineNumNext - iXlineNum)/nXlineInc );
		int nStepNum = qMax(nInlineStepNum,  nXlineStepNum);

		int iCountIndex = m_vecTPTraceIndex.at(m_vecTPTraceIndex.size()-1);

		if (nStepNum != 0)
		{
			double dXInc = (dXNext - dX)/nStepNum;
			double dYInc = (dYNext - dY)/nStepNum;
			for (int k=1; k<nStepNum; ++k)
			{
				dX +=  dXInc;
				dY += dYInc;
				UTM.XYToLine (dX, dY, iInlineNum, iXlineNum);
				STraceLocation traceLocationTmp(iInlineNum, iXlineNum, dX, dY);
				m_vecTraceLocation.push_back (traceLocationTmp);
				iCountIndex++;
			}
		}

		// next point
		STraceLocation traceLocationNext(iInlineNumNext, iXlineNumNext, dXNext, dYNext);
		m_vecTraceLocation.push_back (traceLocationNext);
		m_vecTPTraceIndex.push_back (iCountIndex+1);
	}
}

void CXSeismicRandomSection::_CreateTraceLocations()
{
	auto pDV = dynamic_cast<CXSeismicDataVolume*>(GetDefaultDataVolume());
	if (!pDV)
		return;

	CXSeismicUTMTool& utm = pDV->GetUTM();

	m_vecTraceLocation.clear();
	int nPointNum  = (int) m_vecTurningPoint.size()/2;

	for (int i=0; i<nPointNum; ++i)
	{
		double dX = m_vecTurningPoint.at(2*i);
		double dY = m_vecTurningPoint.at(2*i+1);
		_AddOneTurningPoint (utm, dX, dY);
	}	
}

//@brief Get the X and Y of the turning points
void CXSeismicRandomSection::GetXYofTuringPoint(vector<double>& vecX, vector<double>& vecY)
{
	int nPointNum  = (int) m_vecTurningPoint.size()/2;
	vecX.resize(nPointNum);
	vecY.resize(nPointNum);

	for (int i=0; i<nPointNum; ++i)
	{
		vecX[i] = m_vecTurningPoint[2*i];
		vecY[i] = m_vecTurningPoint[2*i+1];
	}
}

//Get the inline an xline numbers
void CXSeismicRandomSection::GetLineNumbers(vector<int>& vecInline, vector<int>& vecXline)
{
	if (m_vecTraceLocation.empty()) _CreateTraceLocations();

	vecInline.resize(m_vecTraceLocation.size());
	vecXline.resize(m_vecTraceLocation.size());

	for (size_t i = 0; i != m_vecTraceLocation.size(); ++i)
	{
		vecInline[i] = m_vecTraceLocation[i].m_iInlineNum;
		vecXline[i] = m_vecTraceLocation[i].m_iXlineNum;
	}
}

// Get the X and Y
void CXSeismicRandomSection::GetXY(vector<double>& vecX, vector<double>& vecY)
{
	if (m_vecTraceLocation.empty()) _CreateTraceLocations();

	vecX.resize(m_vecTraceLocation.size());
	vecY.resize(m_vecTraceLocation.size());

	for (size_t i = 0; i != m_vecTraceLocation.size(); ++i)
	{
		vecX[i] = m_vecTraceLocation[i].m_dX;
		vecY[i] = m_vecTraceLocation[i].m_dY;
	}
}

//Get the trace number
int CXSeismicRandomSection::GetTraceNum(CXSeismicDataVolume *pDV)
{
	if (m_vecTraceLocation.empty()) 
		_CreateTraceLocations();

	if (!pDV)
		return static_cast<int>(m_vecTraceLocation.size());
	else
		return pDV->GetRandomSectionTraceQty(this);
}

//Get the position of the turing point
int CXSeismicRandomSection::GetTPTraceIndex(int iPoint)
{
	if (m_vecTPTraceIndex.empty()) _CreateTraceLocations();
	assert(iPoint >=0 && iPoint < m_vecTPTraceIndex.size());
	return m_vecTPTraceIndex[iPoint];
}

bool CXSeismicRandomSection::IsTPTraceIndex(int index)
{
	if (m_vecTPTraceIndex.empty()) _CreateTraceLocations();
	auto iterFound = std::find(m_vecTPTraceIndex.cbegin(), m_vecTPTraceIndex.cend(), index);
	return iterFound != m_vecTPTraceIndex.end();
}

CXObject* CXSeismicRandomSection::_GetHistogramObject()
{
	return GetDefaultDataVolume();
}

bool CXSeismicRandomSection::GetTraceInfo(int iIDX, int& iLine, int& iCDP, double& dX, double& dY)
{
	if (m_vecTraceLocation.empty()) _CreateTraceLocations();
	if (iIDX < 0 || iIDX >= m_vecTraceLocation.size())
		return false;

	iLine = m_vecTraceLocation[iIDX].m_iInlineNum;
	iCDP = m_vecTraceLocation[iIDX].m_iXlineNum;
	dX = m_vecTraceLocation[iIDX].m_dX;
	dY = m_vecTraceLocation[iIDX].m_dY;

    return true;
}

QStringList CXSeismicRandomSection::GetDescription()
{
	QStringList sList;
	if (m_vecTraceLocation.empty())
		_CreateTraceLocations();

	sList << "Number of turn points:" << QString::number(m_vecTurningPoint.size() / 2);
	sList << "Number of CDP:" << QString::number(m_vecTraceLocation.size());

	return sList;
}
