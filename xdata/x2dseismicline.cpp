#include "x2dseismicline.h"
#include "xobjectfactory.h"
#include "xseismicdataline.h"
#include "xgraphicsapi.h"
#include "xglobal.h"
#include "xseismicsection.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CX2DSeismicLine)
EX2DSeismicLine
END_REGISTER_OBJECT_TO_FACTORY(CX2DSeismicLine)

CX2DSeismicLine::CX2DSeismicLine(QString sLineName) : CXObject(sLineName)
{
	SetObjectType(EX2DSeismicLine);
	SetIconName("2DLine.png");

	m_numTraces = 0;
	m_pCDP = NULL;
	m_pX = NULL;
	m_pY = NULL;
}

CX2DSeismicLine::~CX2DSeismicLine()
{
	freeMemory();
}

void CX2DSeismicLine::freeMemory()
{
	if (m_numTraces > 0)
	{
		m_numTraces = 0;

		delete[]m_pCDP;
		delete[]m_pX;
		delete[]m_pY;
	}

	m_numTraces = 0;
	m_pCDP = NULL;
	m_pX = NULL;
	m_pY = NULL;
	m_listInflexionInd.clear();
}

void CX2DSeismicLine::PopulateData(unsigned int numTraces, unsigned int* pCDP, double *pX, double *pY)
{
	freeMemory();

	m_numTraces = numTraces;
	m_pCDP = pCDP;
	m_pX = pX;
	m_pY = pY;

	calculateInflexions();
}

QStringList CX2DSeismicLine::GetDescription()
{
	QStringList sListDes;

	sListDes << "Number of traces " << QString::number(m_numTraces);
	sListDes << "The first trace " << QString::number(m_pCDP[0]);
	sListDes << "The last trace " << QString::number(m_pCDP[m_numTraces - 1]);

	return sListDes;
}

bool CX2DSeismicLine::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_numTraces;
		ar.writeRawData((char *)m_pCDP, m_numTraces * sizeof(int));
		ar.writeRawData((char *)m_pX, m_numTraces * sizeof(double));
		ar.writeRawData((char *)m_pY, m_numTraces * sizeof(double));

		ar << m_listInflexionInd.size();
		for (int i = 0; i < m_listInflexionInd.size(); i++)
		{
			ar << m_listInflexionInd[i];
		}
	}
	else
	{
		freeMemory();

		ar >> m_numTraces;

		m_pCDP = new unsigned int[m_numTraces];
		m_pX = new double[m_numTraces];
        m_pY = new double[m_numTraces];

		ar.readRawData((char *)m_pCDP, m_numTraces * sizeof(int));
		ar.readRawData((char *)m_pX, m_numTraces * sizeof(double));
		ar.readRawData((char *)m_pY, m_numTraces * sizeof(double));

		int iSize, iValue;
		ar >> iSize; 
		for (int i = 0; i < iSize; i++)
		{
			ar >> iValue;
			m_listInflexionInd << iValue;
		}
	}

	return true;
}

CXSeismicDataLine* CX2DSeismicLine::GetDefaultSection(bool bIncludePrestack)
{
	for (auto pObj : GetChildren(EXSeismicDataLine, true))
	{
		auto pSection = dynamic_cast<CXSeismicDataLine*>(pObj);
		if (pSection && (bIncludePrestack || (!bIncludePrestack && !pSection->IsPrestack())))
			return pSection;
	}

	return nullptr;
}

void CX2DSeismicLine::_SetSelfDimension()
{
	if (m_numTraces == 0)
		return;

	double fMinX = m_pX[0], fMaxX = m_pX[0], fMinY = m_pY[0], fMaxY = m_pY[0];

	for (int i = 1; i < m_numTraces; i++)
	{
		fMinX = fMinX < m_pX[i] ? fMinX : m_pX[i];
		fMaxX = fMaxX > m_pX[i] ? fMaxX : m_pX[i];
		fMinY = fMinY < m_pY[i] ? fMinY : m_pY[i];
		fMaxY = fMaxY > m_pY[i] ? fMaxY : m_pY[i];
	}

	_SetDimension(fMinX, fMaxX, fMinY, fMaxY, 0., 0.);
}

bool CX2DSeismicLine::GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	if (!m_bDimensionCalculated)
		_SetSelfDimension();

	QList<CXObject*> listChild = GetChildrenList();
	for (int i = 0; i < listChild.size(); ++i)
	{
		CXSeismicDataLine *pSection = dynamic_cast<CXSeismicDataLine *>(listChild[i]);
		if (!pSection)
			continue;

		double fStartZ, fEndZ, fInc;
		pSection->GetSamplingRange(fStartZ, fEndZ, fInc);

		m_dZMax = m_dZMax > fEndZ ? m_dZMax : fEndZ;
		m_dZMin = m_dZMin < fStartZ ? m_dZMin : fStartZ;
	}

	dXMin = m_dXMin;
	dXMax = m_dXMax;
	dYMin = m_dYMin;
	dYMax = m_dYMax;
	dZMin = m_dZMin;
	dZMax = m_dZMax;

	return true;
}

void CX2DSeismicLine::calculateInflexions()
{
	if (m_numTraces < 2 || m_pX == NULL || m_pY == 0)
		return;

	m_listInflexionInd.clear();

	std::vector<int> vecVertexIndices;
	CXGraphicsAPI::GetSegmentVertexIndices(vecVertexIndices, m_numTraces, m_pX, m_pY, 0.000001f);

	for (int i = 0; i<vecVertexIndices.size(); ++i)
	{
		m_listInflexionInd << vecVertexIndices.at(i);
	}
}