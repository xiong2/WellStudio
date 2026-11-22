#include "x2dseismicline.h"
#include "xfunctiontemplate.h"
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

int CX2DSeismicLine::PointOnLine(QPointF& pt, double dTolerance)
{
	if (m_numTraces == 0 || m_pX == NULL || m_pY == NULL)
		return -1;

	// Locate the nearest vertex, to which the point will be snapped
	unsigned int iNearest = 0;
	double dNearestDist2 = SQR(pt.x() - m_pX[0]) + SQR(pt.y() - m_pY[0]);

	for (unsigned int i = 1; i < m_numTraces; ++i)
	{
		double dDist2 = SQR(pt.x() - m_pX[i]) + SQR(pt.y() - m_pY[i]);
		if (dDist2 < dNearestDist2)
		{
			dNearestDist2 = dDist2;
			iNearest = i;
		}
	}

	if (m_numTraces == 1)
	{
		if (dNearestDist2 < dTolerance * dTolerance)
		{
			pt = QPointF(m_pX[0], m_pY[0]);
			return 0;
		}

		return -1;
	}

	// Work out the minimum distance from the point to the segments
	double dMinSegDist2 = dNearestDist2;

	for (unsigned int i = 0; i < m_numTraces - 1; ++i)
	{
		double dX1 = m_pX[i], dY1 = m_pY[i];
		double dDX = m_pX[i + 1] - dX1, dDY = m_pY[i + 1] - dY1;
		double dLen2 = dDX * dDX + dDY * dDY;

		double dT = dLen2 > 0.0 ? ((pt.x() - dX1) * dDX + (pt.y() - dY1) * dDY) / dLen2 : 0.0;
		if (dT < 0.0)
			dT = 0.0;
		else if (dT > 1.0)
			dT = 1.0;

		double dEX = dX1 + dT * dDX - pt.x();
		double dEY = dY1 + dT * dDY - pt.y();

		double dDist2 = dEX * dEX + dEY * dEY;
		if (dDist2 < dMinSegDist2)
			dMinSegDist2 = dDist2;
	}

	if (dMinSegDist2 >= dTolerance * dTolerance)
		return -1;

	pt = QPointF(m_pX[iNearest], m_pY[iNearest]);

	return (int)iNearest;
}

bool CX2DSeismicLine::IsIntersected(CX2DSeismicLine* pLine)
{
	if (pLine == NULL)
		return false;

	if (m_numTraces < 2 || pLine->m_numTraces < 2
		|| m_pX == NULL || m_pY == NULL || pLine->m_pX == NULL || pLine->m_pY == NULL)
		return false;

	// Early rejection with the bounding boxes
	if (!m_bDimensionCalculated)
		_SetSelfDimension();

	if (!pLine->m_bDimensionCalculated)
		pLine->_SetSelfDimension();

	if (m_dXMax < pLine->m_dXMin || pLine->m_dXMax < m_dXMin
		|| m_dYMax < pLine->m_dYMin || pLine->m_dYMax < m_dYMin)
		return false;

	for (unsigned int i = 0; i < m_numTraces - 1; ++i)
	{
		for (unsigned int j = 0; j < pLine->m_numTraces - 1; ++j)
		{
			if (CXGraphicsAPI::AreTwoLineSegmentsIntersecting(
				m_pX[i], m_pY[i], m_pX[i + 1], m_pY[i + 1],
				pLine->m_pX[j], pLine->m_pY[j], pLine->m_pX[j + 1], pLine->m_pY[j + 1]))
				return true;
		}
	}

	return false;
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