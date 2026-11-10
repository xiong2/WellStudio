#include <qline.h>
#include <qfile.h>
#include "gssection.h"
#include "xobjectfactory.h"
#include "xglobal.h"
#include "x3dsurvey.h"
#include "x3dhorizon.h"
#include "gsstressmap.h"
#include "gsdef.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSSection)
EXGSSection
END_REGISTER_OBJECT_TO_FACTORY(GSSection)

GSSection::GSSection()
{

}

GSSection::GSSection(CX3DSurvey *pSurvey, const QString& sName, QPolygonF polyline): CXObject(sName)
{
	SetIconName("Section.png");
	SetObjectType(EXGSSection);
	m_turnPoints = polyline;
	populateHorizons(pSurvey);

	CX3DHorizon *pHor = (CX3DHorizon *)(GetObjectByID(m_listHID[0]));
	m_utm.Copy(const_cast<CXSeismicUTMTool*>(&(pHor->GetUTM())));

	calculateTraces();
}

GSSection::~GSSection()
{
	if (m_pDataInMem)
	{
		delete[]m_pDataInMem;
		m_pDataInMem = NULL;
	}

	if (m_pStessData)
	{
		delete []m_pStessData;
		m_pStessData = NULL;
	}
}

bool GSSection::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_turnPoints;
		ar << m_traces;
		ar << m_listHID;
	}
	else
	{
		ar >> m_turnPoints;
		ar >> m_traces;
		ar >> m_listHID;
	}


	return m_utm.SerializeData(ar);
}

QStringList GSSection::GetDescription()
{
	QStringList sList;

	sList << "Intersected horizons " << QString::number(m_listHID.size());

	return sList;
}

//	Get each section's length, i = -1 means get the total length.
double GSSection::GetSectionLength(int iInd)
{
	double dLen = 0.;
	if (iInd < -1 || iInd >= m_turnPoints.size() - 1)
		return dLen;

	int i;
	if (iInd == -1)
	{
		for (i = 0; i < m_turnPoints.size() - 1; i++)
		{
			QLineF line(m_turnPoints[i], m_turnPoints[i + 1]);
			dLen += line.length();
		}
	}
	else
	{
		QLineF line(m_turnPoints[iInd], m_turnPoints[iInd + 1]);
		dLen += line.length();
	}

	return dLen;
}

//	Exactly is the height of the survey.
double GSSection::GetSectionHeight()
{
	double dXMax, dXMin, dYMax, dYMin, dZMax, dZMin;
	CXObject *pSurvey = GetParent()->GetParent();
	pSurvey->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	
	return dZMax;
}

void GSSection::calculateTraces()
{
	m_traces.clear();

	float fDeltaI, fDeltaJ, fSumI, fSumJ;
	int m, i, j, i1, j1, i2, j2, dI, dJ, iTNum = m_turnPoints.size();
	for (m = 0; m < iTNum - 1; m++)
	{
		m_utm.XYToIJ(m_turnPoints[m].x(), m_turnPoints[m].y(), i1, j1);
		m_utm.XYToIJ(m_turnPoints[m + 1].x(), m_turnPoints[m + 1].y(), i2, j2);
		m_traces << QPoint(i1, j1);

		dI = i1 > i2 ? -1 : 1;
		dJ = j1 > j2 ? -1 : 1;

		fDeltaI = 0;
		if (qAbs(i2 - i1) > 0)
			fDeltaI = 1. / qAbs(i2 - i1);
		fDeltaJ = 0;
		if (qAbs(j2 - j1) > 0)
			fDeltaJ = 1. / qAbs(j2 - j1);
		fSumI = fDeltaI;
		fSumJ = fDeltaJ;

		i = i1;
		j = j1;
		while (1)
		{
			if (fDeltaI == 0 || fSumI >= fSumJ)
			{
				j += dJ;
				fSumJ += fDeltaJ;
			}
			else
			{
				i += dI;
				fSumI += fDeltaI;
			}

			if (i == i2 && j == j2)
				break;

			m_traces << QPoint(i, j);
		}
	}

	m_traces << QPoint(i2, j2);

}

void GSSection::populateHorizons(CX3DSurvey *pSurvey)
{
	m_listHID.clear();

	QList<CXObject *> listF = pSurvey->GetChildren(EXGSFolderHorizon, true);
	foreach(CXObject *pF, listF)
	{
		QList<CXObject *> listH = pF->GetChildren(EXGS3DHorizonDepth);
		if (!listH.empty())
			m_listHID << listH.first()->GetObjectID();
	}
}

float* GSSection::GetData()
{
	if (!m_pDataInMem)
		LoadData();

	if (!m_pDataInMem)
	{
		calculateData();
	}

	return m_pDataInMem;
}

void GSSection::calculateData()
{
	if (m_pDataInMem)
		delete m_pDataInMem;

	int m, n, nJ = m_utm.GetNJ(), iLen = m_traces.size();
	m_pDataInMem = new float[m_listHID.size() * m_traces.size()];
	for(m = 0; m < m_listHID.size(); m++)
	{
		CX3DHorizon *pHor = (CX3DHorizon *)GetObjectByID(m_listHID[m]);
		float *pData = pHor->GetData();

		for (n = 0; n < iLen; n++)
		{
			m_pDataInMem[m * iLen + n] = pData[m_traces[n].x() * nJ + m_traces[n].y()];
		}
	}
}

void GSSection::_WriteData()
{
	if (!m_pDataInMem)
		return;

	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;

	int nSize = m_listHID.size() * m_traces.size();
	qFile.write((char*)m_pDataInMem, sizeof(float)*nSize);
}

void GSSection::_ReadData()
{
	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	int nSize = m_listHID.size() * m_traces.size();
	if (!m_pDataInMem)
	{
		m_pDataInMem = new float[nSize];
	}

	qFile.read((char*)m_pDataInMem, sizeof(float)*nSize);
}

char* GSSection::GetStressData()
{
	if(m_pStessData)
		return m_pStessData;

	CXObject *pSurvey = GetParent()->GetParent();
	QList<CXObject *> listF = pSurvey->GetChildren(EXGSFolderHorizon);
	if(listF.size() <= 1)
		return NULL;

	CXSeismicUTMTool utm;
	int m, n, k, nJ = m_utm.GetNJ(), iLen = m_traces.size();
	m_pStessData = new char[(listF.size() - 1) * iLen];
	for(m = 0; m < listF.size() - 1; m++)
	{
		QList<CXObject *> listH = listF[m]->GetChildren(EXGSStressMap);
		if (listH.empty())
		{
			for (n = 0; n < iLen; n++)
			{
				m_pStessData[m * iLen + n] = -1;
			}
		}
		else
		{
			GSStressMap *pMap = (GSStressMap *)listH.last();
			float *pData = pMap->GetData();

			for (n = 0; n < iLen; n++)
			{
				float fMag = pData[4 * m_traces[n].x() * nJ + 2 * m_traces[n].y()];
				for(k = 6; k >= 0; k--)
				{
					if(fMag > gStressMagRange[k].m_fSHMagLower)
						break;
				}

				m_pStessData[m * iLen + n] = k;
			}
		}
	}

	return m_pStessData;
}

void GSSection::_SetSelfDimension()
{
	double dXMin, dXMax, dYMin, dYMax;
	dXMin = m_turnPoints[0].x();
	dXMax = m_turnPoints[0].x();
	dYMin = m_turnPoints[0].y();
	dYMax = m_turnPoints[0].y();

	foreach(QPointF point, m_turnPoints)
	{
		dXMin = dXMin < point.x() ? dXMin : point.x();
		dXMax = dXMax > point.x() ? dXMax : point.x();
		dYMin = dYMin < point.y() ? dYMin : point.y();
		dYMax = dYMax > point.y() ? dYMax : point.y();
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, 0, 0);
}