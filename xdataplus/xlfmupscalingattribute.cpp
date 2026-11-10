#include "xlfmupscalingattribute.h"
#include <cassert>
#include <QtCore/QFile>
#include "xlfmupscalinggeometry.h"

#include "xglobal.h"
#include "xobjectfactory.h"
#include "xregulardatareader.h"
#include "xfunctiontemplate.h"
#include "xlfmgeometry.h"
#include "xparameterlfmintersecton.h"
#include "xparametermanager.h"
#include "xmathmacro.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXLFMUpscalingAttribute)
EXLFMUpscalingAttribute
END_REGISTER_OBJECT_TO_FACTORY(CXLFMUpscalingAttribute)

CXLFMUpscalingAttribute::CXLFMUpscalingAttribute()
{
	_Init();
}

CXLFMUpscalingAttribute::CXLFMUpscalingAttribute(CXLFMUpscalingGeometry* pGeo, const QString& strName)
	:CXObject(strName)
{
	_Init();
	m_uuidGeometry = pGeo->GetObjectID();
}

CXLFMUpscalingAttribute::~CXLFMUpscalingAttribute()
{
	_FreeMemory();
}

void CXLFMUpscalingAttribute::_Init()
{
	SetObjectType(EXLFMUpscalingAttribute);
	SetIconName("UpscaleResult.png");
}

CXLFMUpscalingGeometry* CXLFMUpscalingAttribute::GetUpscalingGeometry()
{
	return dynamic_cast<CXLFMUpscalingGeometry*>(::GetObjectByID(m_uuidGeometry));
}


void CXLFMUpscalingAttribute::_FreeMemory()
{
	m_mapWellToCellNum.clear();

	QMap<QUuid, double*>::iterator it;
	for (it = m_mapWellToData.begin(); it != m_mapWellToData.end(); ++it)
	{
		delete[]it.value();
	}
	m_mapWellToData.clear();	
}

void CXLFMUpscalingAttribute::AddOneWell(const QUuid& uuidWell, vector<double>& vecData)
{
	if (m_mapWellToCellNum.contains(uuidWell))
		return;

	int nCellNum = (int)vecData.size();

	if (nCellNum != GetUpscalingGeometry()->GetCellNum(uuidWell))
		return;

	double* pData = new double[nCellNum];
	memcpy(pData, &vecData[0], sizeof(double)*nCellNum);

	m_mapWellToCellNum.insert(uuidWell, nCellNum);

	m_mapWellToData.insert(uuidWell, pData);
}

void CXLFMUpscalingAttribute::GetOneWellInfo(const QUuid& uuidWell, vector<double>& vecData)
{
	if (!m_mapWellToCellNum.contains(uuidWell))
		return;

	int nCellNum = m_mapWellToCellNum.value(uuidWell);
	if (nCellNum < 1)
		return;

	vecData.resize(nCellNum);

	memcpy(&vecData[0], m_mapWellToData.value(uuidWell), sizeof(double)*nCellNum);
}


bool CXLFMUpscalingAttribute::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		// LFM
		ar << m_uuidGeometry;

		QList<QUuid> listID = m_mapWellToCellNum.keys();

		ar << listID.size();

		for (int i = 0; i < listID.size(); ++i)
		{
			ar << listID[i];

			int nCellNum = m_mapWellToCellNum.value(listID[i]);

			ar << nCellNum;

			ar.writeRawData((char*)m_mapWellToData.value(listID[i]), sizeof(qint64) * nCellNum);
		}
	}
	else
	{
		_FreeMemory();

		// LFM
		ar >> m_uuidGeometry;

		int nWellNum;
		ar >> nWellNum;

		QUuid uuidWell;
		int nCellNum;
		for (int i = 0; i < nWellNum; ++i)
		{
			ar >> uuidWell;
			ar >> nCellNum;

			qint64* pIndex = new qint64[nCellNum];
			double* pData = new double[nCellNum];

			ar.readRawData((char*)pData, sizeof(double) * nCellNum);

			m_mapWellToCellNum.insert(uuidWell, nCellNum);
			m_mapWellToData.insert(uuidWell, pData);
		}
	}

	return true;
}

float* CXLFMUpscalingAttribute::_GetHistogramData(int& nDataNum, bool& bDeleted)
{
	nDataNum = 0;

	if (m_mapWellToCellNum.isEmpty())
	{
		bDeleted = false;
		return false;
	}

	int nTotalCell = GetUpscalingGeometry()->GetTotalCellNum();
	float* pData = new float[nTotalCell];

	nDataNum = 0;
	QMap<QUuid, double*>::iterator it;
	for (it = m_mapWellToData.begin(); it != m_mapWellToData.end(); ++it)
	{
		int nCellNum = m_mapWellToCellNum.value(it.key());
		for (int i = 0; i < nCellNum; ++i)
		{
			pData[nDataNum + i] = *(it.value() + i);
		}

		nDataNum += nCellNum;
	}

	bDeleted = true;
	return pData;
}

bool CXLFMUpscalingAttribute::GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	if (!GetUpscalingGeometry())
		return false;
	else
		return GetUpscalingGeometry()->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);

}

CXObject* CXLFMUpscalingAttribute::GetGeometryObject()
{
	return GetUpscalingGeometry();
}

QStringList CXLFMUpscalingAttribute::GetDescription()
{
	QStringList list;
	list << "Number of Wells" << QString::number(m_mapWellToCellNum.size())
		<< "Number of Total Cells" << QString::number(GetUpscalingGeometry()->GetTotalCellNum());

	return list;
}

bool CXLFMUpscalingAttribute::GetOneSliceInfo(int iSliceIndex, int& nCellNum, int* pIndex, double* pX, double* pY, double* pValue)
{
	if (m_mapWellToCellNum.isEmpty())
		return false;

	CXLFMUpscalingGeometry* pUpscalingGeo = this->GetUpscalingGeometry();
	if (!pUpscalingGeo)
		return false;

	CXLFMGeometry* pLFMGeo = pUpscalingGeo->GetLFMGeometry();
	if (!pLFMGeo)
		return false;

	CXSeismicUTMTool& utm = pLFMGeo->GetUTM();

	int nI = utm.GetNI();
	int nJ = utm.GetNJ();
	int nK = pLFMGeo->GetNK();
	if (iSliceIndex < 0 || iSliceIndex >= nK)
		return false;

	QMap<QUuid, qint64*>& mapToIndex = pUpscalingGeo->GetWellMapToIndex();
	double dInvEPS = ::GetEPSofInvalidData(::g_dInvalidData);
	qint64 nIJSize = nI*nJ;

	nCellNum = 0;
	double dX, dY;
	int iI, iJ, iK;
	QMap<QUuid, int>::iterator it;
	for (it = m_mapWellToCellNum.begin(); it != m_mapWellToCellNum.end(); ++it)
	{
		int nWellCellNum = it.value();
		if (nWellCellNum == 0)
			continue;

		qint64* pMapIndex = mapToIndex.value(it.key());
		double* pCellValue = m_mapWellToData.value(it.key());

		for (int i = 0; i < nWellCellNum; ++i)
		{
			if (qAbs(pCellValue[i] - ::g_dInvalidData) < dInvEPS)
				continue;

			iK = static_cast<int>(pMapIndex[i] / nIJSize);
			if (iK == iSliceIndex)
			{
				iI = (pMapIndex[i] % nIJSize) / nJ;
				iJ = (pMapIndex[i] % nIJSize) % nJ;

				utm.IJToXY(iI, iJ, dX, dY);

				pIndex[nCellNum] = iI*nJ + iJ;
				pX[nCellNum] = dX;
				pY[nCellNum] = dY;
				pValue[nCellNum++] = pCellValue[i];
			}
		}
	}

	return true;
}



