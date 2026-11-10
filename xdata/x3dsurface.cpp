#include "x3dsurface.h"

#include <cassert>
#include <QtCore/QFile>
#include <qpolygon.h>

#include "xglobal.h"
#include "xobjectfactory.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xseismicutmtool.h"
#include "xseismicdatavolume.h"
#include "xmathmacro.h"
#include "x2dpolygon.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CX3DSurface)
EX3DSurface,
EX3DSurfaceAtt
END_REGISTER_OBJECT_TO_FACTORY(CX3DSurface)

CX3DSurface::CX3DSurface()
{
	m_pDataInMem = NULL;
}

CX3DSurface::CX3DSurface(const CXUTMTool& utm, const QString& strName)
	:CXObject(strName)
{
	m_utm.Copy(const_cast<CXUTMTool*>(&utm));
	SetIconName("Surface.png");
	SetObjectType(EX3DSurface);

	m_pDataInMem = NULL;
}

CX3DSurface::CX3DSurface(const CX3DSurface& other)
	:CXObject(other)
{
	m_utm = other.m_utm;

	int nSize = m_utm.GetNI()*m_utm.GetNJ();
	m_pDataInMem = new float[nSize];

	memcpy(m_pDataInMem, const_cast<CX3DSurface&>(other).GetData(), sizeof(float)*nSize);
}

CX3DSurface::~CX3DSurface()
{
	if (m_pDataInMem)
	{
		delete []m_pDataInMem;
		m_pDataInMem = NULL;
	}
}
bool CX3DSurface::SerializeData(CXArchive& ar)
{

	return m_utm.SerializeData(ar);
}

void CX3DSurface::SetData(float* pData)
{
	if (!pData)
		return;

	int nSize = m_utm.GetNI()*m_utm.GetNJ();
	if (!m_pDataInMem)
	{
		m_pDataInMem = new float[nSize];
	}

	memcpy(m_pDataInMem, pData,sizeof(float)*nSize);
	SetModifiedFlag();

}

float* CX3DSurface::GetData()
{
	if (!m_pDataInMem)
		LoadData();

	if (!m_pDataInMem)
	{
		int nSize = m_utm.GetNI()*m_utm.GetNJ();
		m_pDataInMem = new float[nSize];

		for (int i=0; i<nSize; ++i)
			m_pDataInMem[i] = ::g_dInvalidData;
	}

	return m_pDataInMem;
}

float* CX3DSurface::_GetHistogramData(int& nDataNum, bool& bDeleted)
{
	if (!m_pDataInMem)
		LoadData();

	bDeleted = false;
	if (!m_pDataInMem)
	{
		nDataNum = 0;		
		return NULL;
	}
	else
	{
		nDataNum = m_utm.GetNI()*m_utm.GetNJ();
		return  m_pDataInMem;
	}	
}

void CX3DSurface::_SetSelfDimension()
{
	if (this->GetObjectType() == EX3DSurface || this->GetObjectType() == EX3DHorizon
		|| this->GetObjectType() == EXGS3DHorizonTWT || this->GetObjectType() == EXGS3DHorizonDepth
		|| this->GetObjectType() == EXGS3DHorizonIso || this->GetObjectType() == EXGS3DHorizonAtt)
	{
		double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
		m_utm.GetDimensionRange(dXMin, dXMax, dYMin, dYMax);

		GetDataRange(dZMin, dZMax);

		_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	}
}

bool CX3DSurface::GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax)
{
	if (this->GetObjectType() == EX3DSurface || this->GetObjectType() == EX3DHorizon
		|| this->GetObjectType() == EXGS3DHorizonTWT || this->GetObjectType() == EXGS3DHorizonDepth 
		|| this->GetObjectType() == EXGS3DHorizonIso || this->GetObjectType() == EXGS3DHorizonAtt)
	{
		return CXObject::GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	}
	else
	{
		return this->GetGeometryObject()->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	}
}

void CX3DSurface::_WriteData()
{
	if (!m_pDataInMem)
		return;

	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;

	int nSize = m_utm.GetNI()*m_utm.GetNJ();
	qFile.write((char*)m_pDataInMem, sizeof(float)*nSize);

}
void CX3DSurface::_ReadData()
{
	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	int nSize = m_utm.GetNI()*m_utm.GetNJ();
	if (!m_pDataInMem)
	{
		m_pDataInMem = new float[nSize];
	}
	
	qFile.read((char*)m_pDataInMem, sizeof(float)*nSize);
}

QString CX3DSurface::GetTypeString()
{
	if (this==nullptr)
		return QString();

	if (this->GetObjectType() == EX3DSurface)
		return "3-D Surface";
	else
		return "3-D Surface Attribute";
}

QStringList CX3DSurface::GetDescription()
{
	QStringList strList;

	if(::UsingChinese())
	{
		strList<<GetTr("I方向数目")<<QString::number(m_utm.GetNI());
		strList<<GetTr("I方向步长")<<QString::number(m_utm.GetIInterval());
		strList<<GetTr("J方向数目")<<QString::number(m_utm.GetNJ());
		strList<<GetTr("J方向步长")<<QString::number(m_utm.GetJInterval());
	}
	else
	{
		strList<<"Number in I direction"<<QString::number(m_utm.GetNI());
		strList<<"Step in I direction"<<QString::number(m_utm.GetIInterval());
		strList<<"Number in J direction"<<QString::number(m_utm.GetNJ());
		strList<<"Step in J direction"<<QString::number(m_utm.GetJInterval());
	}

	return strList;
}

void CX3DSurface::SetData(int i, int j, float fData)
{
	if (!m_pDataInMem)
		LoadData();

	if (!m_pDataInMem)
		return;
	m_pDataInMem[i*m_utm.GetNJ() + j] = fData;
	
	SetModifiedFlag();

}

void CX3DSurface::CalcIntersection(vector<double>& vecZ, CX3DSurface* p3DSurface, CXObject* pSection)
{
	assert(p3DSurface && pSection);
	CXUTMTool& utm = p3DSurface->GetUTM();
	float* pData = p3DSurface->GetData();
	assert(pData);
	CXSeismicSection* pSeismicSection = dynamic_cast<CXSeismicSection*>(pSection);
	CXSeismicRandomSection* pRandSection = dynamic_cast<CXSeismicRandomSection*>(pSection);
	if (pSeismicSection)
	{
		int iInlineNum, iXlineNum, iI, iJ;
		CXSeismicUTMTool SeismicUTM = pSeismicSection->GetUTM();
		int nI = SeismicUTM.GetNI();
		int nJ = SeismicUTM.GetNJ();
		int nJSurf = utm.GetNJ();
		double dX, dY;
		if (pSeismicSection->GetSectionType() == eInlineSection)
		{
			iInlineNum = static_cast<int>(pSeismicSection->GetSectionNumber());
			int iXlineStart = SeismicUTM.GetFirstCrossline();
			int iXlineInc = SeismicUTM.GetCrosslineIncrement();			
			for (int j=0; j<nJ; ++j)
			{
				SeismicUTM.LineToXY(iInlineNum, iXlineStart+j*iXlineInc, dX, dY);
				if (utm.XYToIJ(dX, dY, iI, iJ))
				{
					vecZ.push_back(pData[iI*nJSurf + iJ]);
				}
				else
				{
					vecZ.push_back(::g_dInvalidData);
				}
			}		
		}
		else if (pSeismicSection->GetSectionType() == eCrosslineSection)
		{
			iXlineNum = static_cast<int>(pSeismicSection->GetSectionNumber());
			int iInlineStart = SeismicUTM.GetFirstInline();
			int iInlineInc = SeismicUTM.GetInlineIncrement();
			for (int i=0; i<nI; ++i)
			{
				SeismicUTM.LineToXY(iInlineStart+i*iInlineInc, iXlineNum, dX, dY);
				if (utm.XYToIJ(dX, dY, iI, iJ))
				{
					vecZ.push_back(pData[iI*nJSurf + iJ]);
				}
				else
				{
					vecZ.push_back(::g_dInvalidData);
				}
			}
		}
		else
		{
			assert(false);
		}
	}
	else if (pRandSection)
	{
		CXSeismicUTMTool SeismicUTM = pRandSection->GetUTM();
		int iI, iJ;
		//int nJ = SeismicUTM.GetNJ();
		double dX, dY;
		vector<int> vecInline, vecXline;
		pRandSection->GetLineNumbers(vecInline, vecXline);
		int nSize = static_cast<int>(vecInline.size());
		int nJSurf = utm.GetNJ();
		for (int i=0; i<nSize; ++i)
		{
			SeismicUTM.LineToXY(vecInline[i], vecXline[i], dX, dY);
			if (utm.XYToIJ(dX, dY, iI, iJ))
			{
				vecZ.push_back(pData[iI*nJSurf + iJ]);
			}
			else
			{
				vecZ.push_back(::g_dInvalidData);
			}
		}
	}
	else
	{
		assert(false);
	}
}

CX3DSurface * CX3DSurface::GetGeometryObject()
{
	if (this == nullptr)
		return nullptr;

	if (this->GetObjectType() == EX3DSurface)
		return this;
	else if (this->GetObjectType() == EX3DSurfaceAtt)
	{
		return dynamic_cast<CX3DSurface*>(this->GetAncient(EX3DSurface));
	}
	else
		return nullptr;
}

void CX3DSurface::TraceBoundaryPolygons()
{
	int i, j, k, nI = m_utm.GetNI(), nJ = m_utm.GetNJ();
	int nIJ = nI * nJ;
	bool *pTraced = new bool[nIJ];
	for (i = 0; i < nIJ; i++)
		pTraced[i] = false;

	float *pData = GetData();

	QPolygon polygon;
	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			pTraced[i * nJ + j] = true;
			if (pData[i * nJ + j] == g_dInvalidData)
				continue;

			polygon << QPoint(i, j);
		}
	}
}