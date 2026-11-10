#include "xobject.h"

#include <QStack>
#include <QSqlQuery>

#include "xproject.h"
#include "xglobal.h"
#include "xthreadmanager.h"
#include "xdbio.h"
#include "xsaveload.h"
#include "xutility.h"

CXObject::CXObject(const QString& strName, const QUuid& uuid)
: IKEIO(uuid),
m_parentID(g_InvalidObjectID),
m_iTemplateID(g_InvalidTemplateID)
{
	m_strObjName = strName.simplified();
	_Init();
	m_color = ::GetRandomColor();
}


CXObject::CXObject(const CXObject& other)
:IKEIO(other)
{
	_CopyOwnData(other);
}

CXObject& CXObject::operator=(CXObject& other)
{
	if (this == &other)
		return *this;

	IKEIO::operator=(other);

	_CopyOwnData(other);

	return *this;
}

void CXObject::_Init()
{
	m_nSamplingNum = 0;
	m_pBaseData = NULL;

	m_dXMin = m_dXMax = m_dYMin = m_dYMax = m_dZMin = m_dZMax = ::g_dInvalidData; 

	m_bHasHistogram = false;
	m_bCalculated = false;
	m_bDimensionCalculated = false;
	m_bDiscrete = false;
	m_bLog = false;
	
	m_bIsNode = true;

	m_nSamplingNum = 0;

	m_bDBHistogram = false;

	m_bDomainType = eTimeDomain;
}

void CXObject::_CopyOwnData(const CXObject& other)
{
	m_nSamplingNum = other.m_nSamplingNum;
	if (m_nSamplingNum != 0 && other.m_pBaseData)
	{
		m_pBaseData = new double[m_nSamplingNum];
		memcpy(m_pBaseData, other.m_pBaseData, sizeof(double)*m_nSamplingNum);
	}
	else
	{
		m_pBaseData = NULL;
	}

	m_parentID = other.m_parentID;
	m_strObjName = other.m_strObjName;
	m_strIconName = other.m_strIconName;
	m_iTemplateID = other.m_iTemplateID;
	m_color = other.m_color;

	m_bIsNode = other.m_bIsNode;

	m_dXMin = other.m_dXMin;
	m_dXMax = other.m_dXMax;
	m_dYMin = other.m_dYMin;
	m_dYMax = other.m_dYMax;
	m_dZMin = other.m_dZMin;
	m_dZMax = other.m_dZMax;

	m_histogram = other.m_histogram;

	m_bHasHistogram = other.m_bHasHistogram;
	m_bCalculated = false;
	m_bDiscrete = other.m_bDiscrete;
	m_bLog = other.m_bLog;

	m_nSamplingNum = other.m_nSamplingNum;	

	m_bDBHistogram = false;

	m_bDomainType = other.m_bDomainType;
}

CXObject::~CXObject()
{
	if (m_pBaseData)
	{
		delete[]m_pBaseData;
		m_pBaseData = NULL;
	}

	qDeleteAll(m_listChildren);
	m_listChildren.clear();

}

bool CXObject::AddChild(CXObject* pChild)
{
	if (!pChild)
		return false;
	else
	{
		Q_ASSERT(!m_listChildren.contains(pChild));

		m_listChildren.append(pChild);
		pChild->SetParent(this);

		if (!g_mapIDToObject.contains(pChild->GetObjectID()))
		{
			g_mapIDToObject.insert(pChild->GetObjectID(), pChild);
		}

		SetModifiedFlag();

		::SetProjectDirty();

		return true;
	}
}

bool CXObject::InsertChild(CXObject* pChild, int index)
{
	if (!pChild)
		return false;
	else
	{
		Q_ASSERT(!m_listChildren.contains(pChild));

		m_listChildren.insert(index, pChild);
		pChild->SetParent(this);

		if (!g_mapIDToObject.contains(pChild->GetObjectID()))
		{
			g_mapIDToObject.insert(pChild->GetObjectID(), pChild);
		}

		SetModifiedFlag();

		::SetProjectDirty();
		
		return true;
	}
}

bool CXObject::RemoveOneChild(CXObject* pChild)
{
	if (!m_listChildren.contains(pChild))
		return false;

	m_listChildren.removeOne(pChild);	

	SetModifiedFlag();

	::SetProjectDirty();

	return true;
}

QList<CXObject*> CXObject::GetChildren(EXObjectType eObjType, bool bIncludingGrandchildren)
{
	QList<CXObject*> list;

	if (!bIncludingGrandchildren)
	{
		for (int i=0; i<m_listChildren.size(); ++i)
		{
			if (m_listChildren.at(i)->GetObjectType() == eObjType)
				list.append(m_listChildren.at(i));
		}
	}
	else
	{
		QStack<CXObject*> stack;
		int nSize = m_listChildren.size();
		for (int i=nSize-1; i>=0; --i)
			stack.push(m_listChildren.at(i));

		while(!stack.empty())
		{
			CXObject* pObj = stack.pop();

			if (pObj->GetObjectType() == eObjType)
				list.append(pObj);

			QList<CXObject*> listChild = pObj->GetChildrenList();
			int size = listChild.size();

			for (int i=size-1; i>=0; --i)
				stack.push(listChild.at(i));
		}
	}

	return list;
}

QStringList CXObject::GetChildrenNames(EXObjectType eObjType, bool bIncludingGrandchildren)
{
	QStringList lstNames;
	QList<CXObject*> list = GetChildren(eObjType,bIncludingGrandchildren);
	for (int i = 0; i < list.count(); i++)
	{
		lstNames.append(list[i]->GetObjectName());
	}
	return lstNames;
}
QString CXObject::GetUnallocatedName(const QString& strName)
{
	QStringList listName;
	int nSize = m_listChildren.size();	
	for (int i=0; i<nSize; ++i)
		listName<<m_listChildren.at(i)->GetObjectName();

	if (!listName.contains(strName, Qt::CaseInsensitive))
		return strName;
	else
	{
		int i = 2;
		QString strNewName = strName + "_" + QString::number(i);
		while (listName.contains(strNewName, Qt::CaseInsensitive))
		{
			strNewName = strName + "_"+ QString::number(++i);
		}
		return strNewName;
	}
}

bool CXObject::SetParent(CXObject* pParent)
{
	if(pParent)
	{
		m_parentID = pParent->GetObjectID();
		return true;
	}
	else
	{
		return false;
	}	
}

CXObject* CXObject::GetParent()
{
	if (m_parentID == g_InvalidObjectID)
		return NULL;
	else
	{
		IKEIO* pBaseObj = g_mapIDToObject.value(m_parentID);
		if (pBaseObj)
			return dynamic_cast<CXObject*>(pBaseObj);
		else
		{
			return NULL;
		}
	}
}

 QStringList CXObject::GetDescription()
{
	QStringList strList;
	return strList;
}

 bool CXObject::IsLocked()
 { 
	 if (CXThreadManager::Instance().IsLocked(this))
		 return true;

	 for (int i=0; i<m_listChildren.size(); ++i)
	 {
		 if (m_listChildren.at(i)->IsLocked())
			 return true;
	 }

	 return false;
 }

 void CXObject::_SetSelfDimension()
 {
 }
	 
void CXObject::_SetDimension(double dXMin, double dXMax, double dYMin, double dYMax, double dZMin, double dZMax)
 {
	 m_dXMin = dXMin; m_dXMax = dXMax;
	 m_dYMin = dYMin; m_dYMax = dYMax;
	 m_dZMin = dZMin; m_dZMax = dZMax;

	 m_bDimensionCalculated = true;
 }

double CXObject::GetZMin()
{
	double xmin, xmax, ymin, ymax, zmin, zmax;
	this->GetDimension(xmin, xmax, ymin, ymax, zmin, zmax);
	return zmin;
}

double CXObject::GetZMax()
{
	double xmin, xmax, ymin, ymax, zmin, zmax;
	this->GetDimension(xmin, xmax, ymin, ymax, zmin, zmax);
	return zmax;
}

bool CXObject::_GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	if (!m_bDimensionCalculated)
		_SetSelfDimension();

	double xMin, xMax, yMin, yMax, zMin, zMax;
	if (m_dXMin != g_dInvalidData)
	{
		dXMin = m_dXMin; dXMax = m_dXMax;
		dYMin = m_dYMin; dYMax = m_dYMax;
		dZMin = m_dZMin; dZMax = m_dZMax;

		for (int i = 0; i < m_listChildren.size(); ++i)
		{
			m_listChildren.at(i)->_SetSelfDimension();
			if (m_listChildren.at(i)->m_dXMin != g_dInvalidData)
			{
				dXMin = qMin(dXMin, m_listChildren.at(i)->m_dXMin);
				dYMin = qMin(dYMin, m_listChildren.at(i)->m_dYMin);
				dZMin = qMin(dZMin, m_listChildren.at(i)->m_dZMin);

				dXMax = qMax(dXMax, m_listChildren.at(i)->m_dXMax);
				dYMax = qMax(dYMax, m_listChildren.at(i)->m_dYMax);
				dZMax = qMax(dZMax, m_listChildren.at(i)->m_dZMax);
			}
			else
			{
				if (m_listChildren.at(i)->_GetDimension(xMin, xMax, yMin, yMax, zMin, zMax) && xMin != g_dInvalidData)
				{
					dXMin = qMin(dXMin, xMin);
					dYMin = qMin(dYMin, yMin);
					dZMin = qMin(dZMin, zMin);

					dXMax = qMax(dXMax, xMax);
					dYMax = qMax(dYMax, yMax);
					dZMax = qMax(dZMax, zMax);
				}
			}
		}
		return true;
	}
	else
	{
		bool bValid = false;
		for (int i = 0; i < m_listChildren.size(); ++i)
		{
			if (!m_listChildren.at(i)->m_bDimensionCalculated)
				m_listChildren.at(i)->_SetSelfDimension();

			if (!bValid)
			{
				if (m_listChildren.at(i)->m_dXMin != g_dInvalidData)
				{
					dXMin = m_listChildren.at(i)->m_dXMin;
					dYMin = m_listChildren.at(i)->m_dYMin;
					dZMin = m_listChildren.at(i)->m_dZMin;

					dXMax = m_listChildren.at(i)->m_dXMax;
					dYMax = m_listChildren.at(i)->m_dYMax;
					dZMax = m_listChildren.at(i)->m_dZMax;

					bValid = true;
				}
				else
				{
					if (m_listChildren.at(i)->_GetDimension(xMin, xMax, yMin, yMax, zMin, zMax) && xMin != g_dInvalidData)
					{
						dXMin = xMin;
						dYMin = yMin;
						dZMin = zMin;

						dXMax = xMax;
						dYMax = yMax;
						dZMax = zMax;

						bValid = true;
					}
				}
			}
			else
			{
				if (m_listChildren.at(i)->m_dXMin != g_dInvalidData)
				{
					dXMin = qMin(dXMin, m_listChildren.at(i)->m_dXMin);
					dYMin = qMin(dYMin, m_listChildren.at(i)->m_dYMin);
					dZMin = qMin(dZMin, m_listChildren.at(i)->m_dZMin);

					dXMax = qMax(dXMax, m_listChildren.at(i)->m_dXMax);
					dYMax = qMax(dYMax, m_listChildren.at(i)->m_dYMax);
					dZMax = qMax(dZMax, m_listChildren.at(i)->m_dZMax);
				}
				else
				{
					if (m_listChildren.at(i)->_GetDimension(xMin, xMax, yMin, yMax, zMin, zMax) && xMin != g_dInvalidData)
					{
						dXMin = qMin(dXMin, xMin);
						dYMin = qMin(dYMin, yMin);
						dZMin = qMin(dZMin, zMin);

						dXMax = qMax(dXMax, xMax);
						dYMax = qMax(dYMax, yMax);
						dZMax = qMax(dZMax, zMax);
					}
				}
			}
		}

		return bValid;
	}
}

 bool CXObject::GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
 {
	 return _GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
 }

 bool CXObject::HasHistogram()
 {
	 if (!m_bDBHistogram && !m_bCalculated)
		 _CalcHistogram();

	 if (!m_bDBHistogram && !m_bCalculated)
	 {
		 CXObject* pHistObj = _GetHistogramObject();
		 if (pHistObj && pHistObj->HasHistogram())
		 {
			 SetHistogram(pHistObj->m_histogram);
		 }
	 }

	 return m_bHasHistogram;
 }

 CXObject* CXObject::_GetHistogramObject()
 {
	 return NULL;
 }

 void CXObject::GetDataRange(double& dDataMin, double& dDataMax)
 {
	 HasHistogram();

	 dDataMin = m_histogram.m_dDataMin;
	 dDataMax = m_histogram.m_dDataMax;
 }

 void CXObject::GetHistogram(vector<double>& vecHorizontal, vector<double>& vecVertical)
 {
	 if (HasHistogram())
	 {
		 vecHorizontal.resize(m_histogram.m_vecHorizontal.size());
		 vecVertical.resize(m_histogram.m_vecVertical.size());

		 std::copy(m_histogram.m_vecHorizontal.begin(), m_histogram.m_vecHorizontal.end(), vecHorizontal.begin());
		 std::copy(m_histogram.m_vecVertical.begin(), m_histogram.m_vecVertical.end(), vecVertical.begin());		 
	 }
 }

 void CXObject::SetHistogram(const CXHistogram& histogram)
 {
	 m_histogram = histogram;

	 m_bHasHistogram = true;
	 m_bCalculated = true;
	 m_bDBHistogram = true;
 }

 float* CXObject::_GetHistogramData(int& nDataNum, bool& bDeleted)
 {
	 nDataNum = 0;
	 bDeleted = false;
	 return NULL;
 }

 void CXObject::_CalcHistogram()
 {
	 int nDataNum;
	 bool bDeleted;
	 float* pData = _GetHistogramData(nDataNum, bDeleted);
	 if (pData)
	 {
		 if (!NXUtility::CalcHistogram<float>(pData, nDataNum, m_histogram))
		 {
			 m_bHasHistogram = false;
			 if (bDeleted)
				 delete[]pData;
			 return;
		 }
		 if (bDeleted)
			 delete[]pData;

		 m_bHasHistogram = true;
		 m_bCalculated = true;
	 }
 }

 QString CXObject::GetDataFileName() const
 {
	 QString strName = ::GetProject()->GetProjectDataPath();
	 return strName + this->GetObjectID().toString() + ".dat";
 } 

 void CXObject::_WriteData()
 {

 }
 void CXObject::_ReadData()
 {

 }

 bool CXObject::Serialize(bool bSave)
{
	// base object
	if (!IKEIO::Serialize(bSave))
		return false;	

	QString strTable = "rlobject";	

	// save
	if (bSave)
	{
		QStringList strFieldList;
		strFieldList<<"ID";	
		strFieldList<<"PID";
		strFieldList<<"ChildrenID";
		strFieldList<<"ObjectName";
		strFieldList<<"IconName";
		strFieldList<<"TemplateID";
		strFieldList<<"Color";
		strFieldList<<"NodeFlag";
		strFieldList<<"DataLength";		
		strFieldList<<"DataBLOB";	
		strFieldList<<"HistFlag";
		strFieldList<<"HistBLOB";
		strFieldList<<"DomainType";

		QList<QVariant> vtList;

		vtList.append(GetObjectID().toString());
		vtList.append(m_parentID.toString());

		// children
		QStringList strChildList;
		for (int i=0; i<m_listChildren.size(); ++i)
			strChildList.append(m_listChildren.at(i)->GetObjectID().toString());
		QString strChildren = strChildList.join("\r");
		vtList.append(strChildren);

		vtList.append(m_strObjName);
		vtList.append(m_strIconName);
		vtList.append(m_iTemplateID);
		vtList.append(m_color.rgba());

		// Node flag
		int iNodeFlag = (m_bIsNode == true ? 1 : 0);
		vtList.append(iNodeFlag);
	
		vtList.append(m_nSamplingNum);
		// data BLOB		
		vtList.append(SaveDataToBLOB(m_pBaseData, m_nSamplingNum));

		// histogram fl67ag
		int iHistFlag = (m_bDBHistogram == true ? 1 : 0);
		vtList.append(iHistFlag);

		// histogram BLOB
		if (m_bDBHistogram)
			vtList.append(m_histogram.SaveToBLOB());
		else
			vtList.append(QVariant());

		// domain type		
		vtList.append((int)m_bDomainType);

		bool b1 =  ::GetDBIO()->UpdateInsert(strTable, strFieldList, vtList, GetObjectID().toString());
	
		_WriteData();

		return b1;
	}
	else
	{
		QStringList strFieldList;
		strFieldList<<"PID";
		strFieldList<<"ObjectName";
		strFieldList<<"IconName";
		strFieldList<<"TemplateID";
		strFieldList<<"Color";
		strFieldList<<"NodeFlag";
		strFieldList<<"DataLength";
		strFieldList<<"HistFlag";
		strFieldList<<"HistBLOB";
		strFieldList<< "DomainType";

		QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());

		if( query.first() )
		{
			int nIndex = -1;

			m_parentID = query.value(++nIndex).toString();
			m_strObjName = query.value(++nIndex).toString();
			m_strIconName = query.value(++nIndex).toString();
			m_iTemplateID = query.value(++nIndex).toUInt();
			m_color = QColor(query.value(++nIndex).toUInt());

			int iNodeFlag = query.value(++nIndex).toInt();
			m_bIsNode = (iNodeFlag == 1 ? true : false);

			m_nSamplingNum = query.value(++nIndex).toUInt();

			// histogram flag
			int iHistFlag = query.value(++nIndex).toInt();
			m_bDBHistogram = (iHistFlag == 1 ? true : false);

			// histogram blob
			if (m_bDBHistogram)
			{
				m_histogram.LoadFromBLOB(query.value(++nIndex));

				m_bCalculated = true;
				m_bHasHistogram = true;
			}
			else
			{
				++nIndex;
			}

			//
			QVariant v = query.value(++nIndex);
			if (v.isValid())
			{
				m_bDomainType = static_cast<EDomainType>(v.toInt());
			}			
		}

		return true;
	}
}

void CXObject::_LoadBaseData()
{
	if (m_nSamplingNum <= 0 || m_pBaseData)
		return;

	QString strTable = "rlobject";
	QStringList strFieldList;
	strFieldList << "DataBLOB";

	QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());

	if (query.first())
	{
		int nIndex = -1;	

		// BLOB
		m_pBaseData = new double[m_nSamplingNum];
		LoadDataFromBLOB(query.value(++nIndex), m_pBaseData, m_nSamplingNum);
	}
}

double* CXObject::GetData(unsigned int& iNumber)
{
	_LoadBaseData();

	iNumber = m_nSamplingNum;
	return m_pBaseData;
}

void CXObject::LoadData()
{
	_ReadData();
}

CXObject* CXObject::GetChild(QString sName, EXObjectType eObjType)
{
	foreach(CXObject *pObj, m_listChildren)
	{
		if (pObj->GetObjectName().toLower() == sName.toLower() && (eObjType == EXBegin || pObj->GetObjectType() == eObjType))
			return pObj;
	}

	//	Not found, return NULL.
	return NULL;
}

CXObject* CXObject::GetChild(QUuid objID)
{
	foreach(CXObject *pObj, m_listChildren)
	{
		if(pObj->GetObjectID() == objID)
			return pObj;
	}

	//	Not found, return NULL.
	return NULL;
}

CXObject* CXObject::GetChild(unsigned int iTemplateID)
{
	foreach(CXObject *pObj, m_listChildren)
	{
		if(pObj->GetTemplateID() == iTemplateID)
			return pObj;
	}

	//	Not found, return NULL.
	return NULL;
}

CXObject* CXObject::GetAncient(EXObjectType eObjType)
{
	CXObject* parent = GetParent();
	while (parent)
	{
		if (parent->GetObjectType() == eObjType)
			break;
		else
			parent = parent->GetParent();
	}

	return parent;
}

QUuid CXObject::GetSurveyID()
{
	CXObject* parent = this;
	while (parent)
	{
		if (parent->GetObjectType() == EX3DSurvey)
			break;
		else
			parent = parent->GetParent();
	}

	if (parent)
		return parent->GetObjectID();
	return QUuid();
}

