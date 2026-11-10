#include "xwelltops.h"

#include <QSqlQuery>
#include <qsqlrecord.h>

#include "xobjectfactory.h"
#include "xdbinmemory.h"
#include "xglobal.h"
#include "xproject.h"
#include "x3dpoints.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xwelltopformation.h"


BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellTops)
EXWellTops
END_REGISTER_OBJECT_TO_FACTORY(CXWellTops)

CXWellTops::CXWellTops(const QString& strName)
: CXObject(strName)
{
	SetObjectType(EXWellTops);
	SetIconName("WellTops.png");
	if (strName.isEmpty())
	{
		SetObjectName("WellTops");
	}
}

CXWellTops::~CXWellTops()
{
}

void CXWellTops::GenerateFormations()
{
	QStringList strListWell, strListFormation;
	GetWellAndFormation(strListWell, strListFormation);
	for (int i = 0; i < strListFormation.size(); ++i)
	{
		if (GetChild(strListFormation.at(i), EXWellTopFormation) == NULL)
		{
			CXWellTopFormation* pFormation = new CXWellTopFormation(strListFormation.at(i));
			this->AddChild(pFormation);
		}
	}
}

bool CXWellTops::Serialize(bool bSave)
{
	return  CXObject::Serialize(bSave);
}

bool CXWellTops::AddOneRecord(QString strWellName, QString strFormation, double vt)
{
	SetModifiedFlag();

	int index = GetOneRecordIndex(strWellName, strFormation);
	if (index != -1)
	{
		m_lstMD[index] = vt;
		return true;
	}
	m_lstWellNames.append(strWellName);
	m_lstTopNames.append(strFormation);
	m_lstMD.append(vt);
	m_lstXYZ.append(QVector3D());
	return true;
}

bool CXWellTops::AddOneRecord(QString strWellName, QString strFormation, QVector3D vt)
{
	SetModifiedFlag();

	int index = GetOneRecordIndex(strWellName, strFormation);
	if (index != -1)
	{
		m_lstXYZ[index] = vt;
		return true;
	}
	m_lstWellNames.append(strWellName);
	m_lstTopNames.append(strFormation);
	m_lstMD.append(vt.z());
	m_lstXYZ.append(vt);
	return true;
}
bool CXWellTops::DelOneRecord(QString strWellName, QString strFormation)
{

	int index = GetOneRecordIndex(strWellName, strFormation);
	if (index == -1)
	{
		return true;
	}
	SetModifiedFlag();
	m_lstWellNames.removeAt(index);
	m_lstTopNames.removeAt(index);
	m_lstMD.removeAt(index);
	m_lstXYZ.removeAt(index);
	return true;
}
double CXWellTops::GetOneRecord(QString strWellName, QString strFormation)
{
	int index = GetOneRecordIndex(strWellName, strFormation);
	if (index != -1)
	{
		return m_lstMD[index];
	}
	return ::g_dInvalidData;
}

QVector3D CXWellTops::GetOneRecordXYZ(QString strWellName, QString strFormation)
{
	int index = GetOneRecordIndex(strWellName, strFormation);
	if (index != -1)
	{
		return m_lstXYZ[index];
	}
	return QVector3D();
}

QStringList CXWellTops::GetTopsByWell(QString strWellName)
{
	QStringList lstTops;
	strWellName = strWellName.toLower();
	int i;
	for (i = 0; i < m_lstTopNames.count(); i++)
	{
		if (lstTops.contains(m_lstTopNames[i].toLower()) == false
			&& m_lstWellNames[i].toLower() == strWellName)
		{
			lstTops.append(m_lstTopNames[i].toLower());
		}
	}
	return lstTops;
}

int CXWellTops::GetOneRecordIndex(QString strWellName, QString strFormation)
{
	strWellName = strWellName.toLower();
	strFormation = strFormation.toLower();
	for (int i = 0; i < m_lstMD.count(); i++)
	{
		if (m_lstWellNames[i].toLower() == strWellName
			&& m_lstTopNames[i].toLower() == strFormation)
		{
			return i;
		}
	}
	return -1;
}
int CXWellTops::GetRecordNum()
{
	return m_lstMD.size();
}

void CXWellTops::GetWellAndFormation(QStringList& strListWell, QStringList& strListFormation)
{
	strListWell.clear();
	int i;
	for (i = 0; i < m_lstWellNames.count(); i++)
	{
		if (strListWell.contains(m_lstWellNames[i].toLower()) == false)
		{
			strListWell.append(m_lstWellNames[i].toLower());
		}
	}

	strListFormation.clear();
	for (i = 0; i < m_lstTopNames.count(); i++)
	{
		if (strListFormation.contains(m_lstTopNames[i].toLower()) == false)
		{
			strListFormation.append(m_lstTopNames[i].toLower());
		}
	}
}

CX3DPoints* CXWellTops::Get3DPointsFromFormation(const QString& strFormation)
{
	// must have  x y z or depth (MD)
	QStringList strXYZNames;
	strXYZNames.append("X");
	strXYZNames.append("Y");
	strXYZNames.append("Z");

	int nWell = m_lstMD.size();
	std::vector<QVector3D> vecPoint;
	QVector3D point;
	QList<CXObject*> listWellFolder = ::GetProject()->GetChildren(EXWellFolder);
	for (int i = 0; i < nWell; ++i)
	{
		if (m_lstTopNames[i].toLower() != strFormation.toLower())
		{
			continue;
		}
		if (m_lstXYZ[i].isNull()==false)
		{
			vecPoint.push_back(m_lstXYZ[i]);
			continue;
		}
		if (listWellFolder.empty())
		{
			continue;
		}
		CXObject* pWellObj = listWellFolder.front()->GetChild(m_lstWellNames.at(i), EXWell);
		CXWell *pWell = dynamic_cast<CXWell*>(pWellObj);
		if (!pWell)
			continue;

		CXWellPath* pWellPath = pWell->GetWellPath();
		if (!pWellPath)
			continue;

		double dMD = GetOneRecord(m_lstWellNames.at(i), strFormation);
		if (dMD == ::g_dInvalidData)
			continue;


		pWellPath->MapAttrPointToCoord(dMD, point);
		vecPoint.push_back(point);
	}
	


	if (vecPoint.empty())
		return NULL;

	int nPointNum = vecPoint.size();
	double* pData = new double[nPointNum * 3];
	for (int i = 0; i < nPointNum; ++i)
	{
		pData[3 * i] = vecPoint[i].x();
		pData[3 * i + 1] = vecPoint[i].y();
		pData[3 * i + 2] = vecPoint[i].z();
	}

	CX3DPoints* p3DPoints = new CX3DPoints(strFormation);
	p3DPoints->ResetData(pData, nPointNum * 3);

	return p3DPoints;
}

bool CXWellTops::SerializeData(CXArchive& ar)
{
	int flags0 = 201510;
	int flags1;
	if (ar.IsSaving())
	{
		ar << flags0
			<< m_lstWellNames
			<< m_lstTopNames
			<< m_lstMD
			<< m_lstXYZ;
	}
	else
	{
		ar >> flags1
			>> m_lstWellNames
			>> m_lstTopNames
			>> m_lstMD
			>> m_lstXYZ;
	}

	return true;
}
void CXWellTops::ClearData()
{

	m_lstWellNames.clear();
	m_lstTopNames.clear();
	m_lstMD.clear();
	m_lstXYZ.clear();
}

QStringList CXWellTops::GetAllStringRecord()
{
	return m_lstWellNames + m_lstTopNames;
}

double* CXWellTops::GetAllFigureRecord()
{
	int iNum = m_lstMD.size();
	if (iNum <= 0)
		return NULL;

	double *pBuff = new double[4 * iNum];
	for (int i = 0; i < iNum; i++)
	{
		pBuff[i] = m_lstMD[i];
		pBuff[i + iNum] = m_lstXYZ[i].x();
		pBuff[i + 2 * iNum] = m_lstXYZ[i].y();
		pBuff[i + 3 * iNum] = m_lstXYZ[i].z();
	}

	return pBuff;
}