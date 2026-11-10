#include "xlfmupscalinggeometry.h"
#include <cassert>
#include <QtCore/QFile>

#include "xglobal.h"
#include "xobjectfactory.h"
#include "xregulardatareader.h"
#include "xfunctiontemplate.h"
#include "xlfmgeometry.h"
#include "xparameterlfmintersecton.h"
#include "xparametermanager.h"
#include "xmathmacro.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXLFMUpscalingGeometry)
EXLFMUpscalingGeometry
END_REGISTER_OBJECT_TO_FACTORY(CXLFMUpscalingGeometry)

CXLFMUpscalingGeometry::CXLFMUpscalingGeometry()
{
	_Init();
}

CXLFMUpscalingGeometry::CXLFMUpscalingGeometry(CXLFMGeometry* pLFM, const QString& strName)
	:CXObject(strName)
{
	_Init();
	m_uuidLFM = pLFM->GetObjectID();
}

CXLFMUpscalingGeometry::~CXLFMUpscalingGeometry()
{
	_FreeMemory();
}

void CXLFMUpscalingGeometry::_Init()
{
	SetObjectType(EXLFMUpscalingGeometry);
	SetIconName("UpscaleGeometry.png");
}

void CXLFMUpscalingGeometry::_FreeMemory()
{
	m_mapWellToCellNum.clear();

	QMap<QUuid, qint64*>::iterator it1;
	for (it1 = m_mapWellToDIndex.begin(); it1 != m_mapWellToDIndex.end(); ++it1)
	{
		delete[]it1.value();
	}
	m_mapWellToDIndex.clear();

	QMap<QUuid, double*>::iterator it2;
	for (it2 = m_mapWellToData.begin(); it2 != m_mapWellToData.end(); ++it2)
	{
		delete[]it2.value();
	}
	m_mapWellToData.clear();


}

void CXLFMUpscalingGeometry::AddOneWell(const QUuid& uuidWell, int nCellNum, qint64* pIndex, double* pXYZ, double* pTopZ, double* pBotZ)
{
	if (nCellNum == 0)
		return;

	if (m_mapWellToCellNum.contains(uuidWell))
		return;

	// index
	qint64* pIndexNew = new qint64[nCellNum];
	memcpy(pIndexNew, pIndex, sizeof(qint64)*nCellNum);
	m_mapWellToDIndex.insert(uuidWell, pIndexNew);

	// cell number
	m_mapWellToCellNum.insert(uuidWell, nCellNum);

	// xyz vertices + topz + bottomz
	double* pData = new double[(24 + 2) * nCellNum];

	// xyz
	memcpy(pData, pXYZ, sizeof(double) * 24 * nCellNum);

	// topz
	memcpy(pData + 24 * nCellNum, pTopZ, sizeof(double)*nCellNum);

	// bottom z
	memcpy(pData + 25 * nCellNum, pBotZ, sizeof(double)*nCellNum);

	m_mapWellToData.insert(uuidWell, pData);
}

void CXLFMUpscalingGeometry::GetOneWellInfo(const QUuid& uuidWell, vector<qint64>& vecIndex, vector<double>& vecXYZ, vector<double>& vecTopZ, vector<double>& vecBotZ)
{
	if (!m_mapWellToCellNum.contains(uuidWell))
		return;

	int nCellNum = m_mapWellToCellNum.value(uuidWell);
	if (nCellNum < 1)
		return;

	vecIndex.resize(nCellNum);
	vecXYZ.resize(24 * nCellNum);
	vecTopZ.resize(nCellNum);
	vecBotZ.resize(nCellNum);

	memcpy(&vecIndex[0], m_mapWellToDIndex.value(uuidWell), sizeof(qint64)*nCellNum);

	double* pData = m_mapWellToData.value(uuidWell);
	memcpy(&vecXYZ[0], pData, sizeof(double) * 24 * nCellNum);

	memcpy(&vecTopZ[0], pData + 24 * nCellNum, sizeof(double) * nCellNum);

	memcpy(&vecBotZ[0], pData + 25 * nCellNum, sizeof(double) * nCellNum);
}

void CXLFMUpscalingGeometry::GetOneWellInfo(const QUuid& uuidWell, vector<double>& vecTopZ, vector<double>& vecBotZ)
{
	if (!m_mapWellToCellNum.contains(uuidWell))
		return;

	int nCellNum = m_mapWellToCellNum.value(uuidWell);
	if (nCellNum < 1)
		return;

	vecTopZ.resize(nCellNum);
	vecBotZ.resize(nCellNum);


	double* pData = m_mapWellToData.value(uuidWell);

	memcpy(&vecTopZ[0], pData + 24 * nCellNum, sizeof(double) * nCellNum);

	memcpy(&vecBotZ[0], pData + 25 * nCellNum, sizeof(double) * nCellNum);
}


bool CXLFMUpscalingGeometry::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		// LFM
		ar << m_uuidLFM;

		QList<QUuid> listID = m_mapWellToCellNum.keys();

		ar << listID.size();

		for (int i = 0; i < listID.size(); ++i)
		{
			ar << listID[i];

			int nCellNum = m_mapWellToCellNum.value(listID[i]);
			
			ar << nCellNum;

			ar.writeRawData((char*)m_mapWellToDIndex.value(listID[i]), sizeof(qint64)*nCellNum);

			ar.writeRawData((char*)m_mapWellToData.value(listID[i]), sizeof(double)*26*nCellNum);
		}
	}
	else
	{
		_FreeMemory();

		// LFM
		ar >> m_uuidLFM;

		int nWellNum;
		ar >> nWellNum;

		QUuid uuidWell;
		int nCellNum;
		for (int i = 0; i < nWellNum; ++i)
		{
			ar >> uuidWell;
			ar >> nCellNum;

			qint64* pIndex = new qint64[nCellNum];
			double* pData = new double[(24 + 2) * nCellNum];

			ar.readRawData((char*)pIndex, sizeof(qint64)*nCellNum);
			ar.readRawData((char*)pData, sizeof(double) * 26 * nCellNum);

			m_mapWellToCellNum.insert(uuidWell, nCellNum);
			m_mapWellToDIndex.insert(uuidWell, pIndex);
			m_mapWellToData.insert(uuidWell, pData);
		}
	}

	return true;
}

float* CXLFMUpscalingGeometry::_GetHistogramData(int& nDataNum, bool& bDeleted)
{
	nDataNum = 0;

	if (m_mapWellToCellNum.isEmpty())
	{
		bDeleted = false;
		return false;
	}

	int nTotalCell = GetTotalCellNum();
	float* pData = new float[nTotalCell];

	nDataNum = 0;
	QMap<QUuid, double*>::iterator it;
	for (it = m_mapWellToData.begin(); it != m_mapWellToData.end(); ++it)
	{
		int nCellNum = m_mapWellToCellNum.value(it.key());
		for (int i = 0; i < nCellNum; ++i)
		{
			pData[nDataNum + i] = *(it.value() + 24 * nCellNum + i);
		}

		nDataNum += nCellNum;
	}

	bDeleted = true;
	return pData;
}

CXLFMGeometry* CXLFMUpscalingGeometry::GetLFMGeometry()
{
	return dynamic_cast<CXLFMGeometry*>(::GetObjectByID(m_uuidLFM));
}


bool CXLFMUpscalingGeometry::GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	if (!GetLFMGeometry())
		return false;
	else
		return GetLFMGeometry()->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}


QStringList CXLFMUpscalingGeometry::GetDescription()
{
	QStringList list;
	list << "Number of Wells" << QString::number(m_mapWellToCellNum.size())
		 << "Number of Total Cells" << QString::number(GetTotalCellNum());

	CXParameterLFMIntersecton* pPara = dynamic_cast<CXParameterLFMIntersecton*>(CXParameterManager::Instance().GetParameterByID(this->GetObjectID()));
	if (pPara)
	{
		std::vector<QUuid> vecWellID = pPara->GetVecWellID();
		QStringList ListWellName = pPara->GetListWellName();
		for (int i = 0; i < ListWellName.size(); ++i)
		{
			list << QString("Well: ") + CXBaseParameter::GetTrueName(vecWellID[i], ListWellName[i]) 
				<< QString("Cell number: ") + QString::number(m_mapWellToCellNum.value(vecWellID[i]));
		}
	}

	return list;
}

int CXLFMUpscalingGeometry::GetTotalCellNum()
{
	int nCellNum = 0;
	QMap<QUuid, int>::iterator it;
	
	for (it = m_mapWellToCellNum.begin(); it != m_mapWellToCellNum.end(); ++it)
	{
		nCellNum += it.value();
	}

	return nCellNum;
}

QList<QUuid> CXLFMUpscalingGeometry::GetAllWellID()
{
	return m_mapWellToCellNum.keys();
}


