#include <qdebug.h>
#include "xgeobody.h"
#include "xseismicutmtool.h"
#include "xparametersgeobodydetection.h"
#include "xobjectfactory.h"
#include "xparametermanager.h"
#include "xgeobodycollection.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXGeobody)
EXGeobody
END_REGISTER_OBJECT_TO_FACTORY(CXGeobody)

CXGeobody::CXGeobody()
{
	SetObjectType(EXGeobody);

	m_iSkinCellNumber = 0;
	m_iTotalCellNumber = 0;
	m_pCells = NULL;
}

CXGeobody::CXGeobody(CXSeismicUTMTool *pUTM, float fSZ, float fEZ, float fZInc, bool bWhole)
{
	SetObjectType(EXGeobody);
	m_bMerged		= bWhole;

	if (bWhole)
		SetIconName("GeobodyWhole.png");
	else
		SetIconName("Geobody.png");

	m_iSkinCellNumber = 0;
	m_iTotalCellNumber = 0;
	m_utm.Copy(pUTM);
	m_fStartZ = fSZ;
	m_fEndZ = fEZ;
	m_fZInc = fZInc;
	m_pCells = NULL;
}

CXGeobody::~CXGeobody()
{
	if (m_pCells)
		delete m_pCells;
}

void CXGeobody::indexToIJK(qint64 iIndex, int &i, int &j, int &k)
{
	int nJ = m_utm.GetNJ();
	int nZ = (m_fEndZ - m_fStartZ) / m_fZInc + 1;

	i = iIndex / (nJ * nZ);
	j = (iIndex % (nJ * nZ)) / nZ;
	k = iIndex % nZ;
}

void CXGeobody::_ReadData()
{
	if (m_pCells)
	{
		delete []m_pCells;
		m_pCells = NULL;
	}
	
	if (m_iSkinCellNumber == 0)
		return;
	m_pCells = new qint64[m_iSkinCellNumber];

	QString strDataFile = GetDataFileName();
	QFile qFile(strDataFile);
	qFile.open(QIODevice::ReadOnly);

	qFile.read((char *)m_pCells, m_iSkinCellNumber * sizeof(qint64));
	qFile.close();
}

qint64* CXGeobody::GetAllCells(unsigned int& iNumberCell)
{
	iNumberCell = 0;

	if (!m_pCells)
		LoadData();

	if (m_pCells)
		iNumberCell = m_iSkinCellNumber;

	return m_pCells;
}

void CXGeobody::PopulateData(QString sFile, unsigned int iSkinCellNumber)
{
	QString strDataFile = GetDataFileName();
	QFile::rename(sFile, strDataFile);

	CXSortOnDisk<qint64> sortCellID(strDataFile);
	sortCellID.Sort();

	m_iSkinCellNumber = iSkinCellNumber;
	m_iTotalCellNumber = iSkinCellNumber;
}

bool CXGeobody::SerializeData(CXArchive& ar)
{
	m_utm.SerializeData(ar);

	if (ar.IsSaving())
	{
		ar << m_bMerged;
		ar << m_iTotalCellNumber;
		ar << m_iSkinCellNumber;
		ar << m_fStartZ;
		ar << m_fEndZ;
		ar << m_fZInc;

		ar << m_dXMin;
		ar << m_dXMax;
		ar << m_dYMin;
		ar << m_dYMax;
		ar << m_dZMin;
		ar << m_dZMax;
	}
	else
	{
		ar >> m_bMerged;
		ar >> m_iTotalCellNumber;
		ar >> m_iSkinCellNumber;
		ar >> m_fStartZ;
		ar >> m_fEndZ;
		ar >> m_fZInc;

		ar >> m_dXMin;
		ar >> m_dXMax;
		ar >> m_dYMin;
		ar >> m_dYMax;
		ar >> m_dZMin;
		ar >> m_dZMax;
	}

	return true;
}

void CXGeobody::Unite(CXGeobody *pOtherGeobody)
{

}

float CXGeobody::GetZByK(int k)
{
	return m_fStartZ + k * m_fZInc;
}

int CXGeobody::GetNZ()
{
	return (int)((m_fEndZ - m_fStartZ) / m_fZInc) + 1;
}

///@brief Overwrite the basic implement to offer more info.
QStringList CXGeobody::GetDescription()
{
	QStringList listStr;

	qint64 iVolume = m_utm.GetCrosslineInterval() * m_utm.GetInlineInterval();
	iVolume *= (1.8 * m_fZInc * m_iTotalCellNumber);

	listStr << "Cell Number" << QString::number(m_iTotalCellNumber);
	listStr << "Geobody Volume (m^3, while seismic velocity is 3600m/s)" << QString::number(iVolume);

	return listStr;
}

//	Get the central position of a specific cell.
void CXGeobody::GetCellCentralPosition(qint64 iCellIndex, double& x, double& y, double& z)
{
	int i, j, k;
	indexToIJK(iCellIndex, i, j, k);

	m_utm.IJToXY(i, j, x, y);
	z = m_fStartZ + k * m_fZInc;
}

//	Get the top and bottom surface of the geobody.
bool CXGeobody::GetTopBottomSurface(CX3DSurface *pTopSurface, CX3DSurface *pBottomSurface)
{
	return false;
}

void CXGeobody::_findSelfLimit()
{

}

void CXGeobody::SetDimension(double dXMin, double dXMax, double dYMin, double dYMax, double dZMin, double dZMax)
{
	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

CXParametersGeobodyDetection *	CXGeobody::GetDetectParameter()
{
	return dynamic_cast<CXParametersGeobodyDetection*>(CXParameterManager::Instance().GetParameterByID(this->GetObjectID()));
}