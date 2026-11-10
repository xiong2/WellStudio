#include "xwellnmr.h"

#include <vector>
#include <QFile>
#include <qfileinfo.h>

#include "xglobal.h"
#include "xobjectfactory.h"
#include "xproject.h"
#include "xregulardatareader.h"
#include "xseismicrandomsection.h"
#include "xseismicirregularreader.h"
#include "xseismicsection.h"
#include "xeventconsole.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellNMR)
EXWellNMR
END_REGISTER_OBJECT_TO_FACTORY(CXWellNMR)

CXWellNMR::CXWellNMR()
{

	m_dSamplingStart = 0;
	m_dSamplingRate = 0.1;
	m_nTraceNum = 0;
	m_Num_2D = 0;

	m_pTraceData = NULL;
}

CXWellNMR::CXWellNMR(double dSamplingStart, double dSamplingRate, int dSamplingNum,
	double dHorizontalStart, double dHorizontalRate, int Num_2D, const QString& strName )
{
	SetIconName("SeismicDataVolume.png");
	SetObjectType(EXWellNMR);
	SetObjectName(strName);

	m_dSamplingStart = dSamplingStart;
	m_dSamplingRate = dSamplingRate;
	m_nTraceNum = dSamplingNum;
	m_Num_2D = Num_2D;
	m_dHorizontalRate = dHorizontalRate;
	m_dHorizontalStart = dHorizontalStart;

	m_pTraceData = NULL;
}

CXWellNMR::~CXWellNMR()
{
	delete m_pTraceData;
	CloseFile();
}

QString CXWellNMR::GetTypeString()
{
	return "Well NMR";
}

void CXWellNMR::CloseFile()
{
	if (m_fileTrace.isOpen())
	{
		m_fileTrace.close();
	}
}
float* CXWellNMR::GetDataCache()//仅获取缓存
{
	if (!m_pTraceData)
		m_pTraceData = new float[GetSamplingQty()];
	return m_pTraceData;
}

float* CXWellNMR::ReadTraceData(int iIndex, float* pCopyData)
{
	if (iIndex < 0 || iIndex >= GetTraceNumber())
	{
		return NULL;
	}
	if (!m_pTraceData)
		m_pTraceData = new float[GetSamplingQty()];

	if (m_fileTrace.isOpen()==false)
	{
		m_fileTrace.setFileName(GetTraceFileName());
		if (!m_fileTrace.open(QIODevice::ReadOnly))
		{
			//qWarning() << "Open file " << GetTraceFileName() << "failed";
			return NULL;
		}
	}
	const int datalen = 4 * m_Num_2D;
	if (m_fileTrace.pos() != iIndex*datalen)
	{
		m_fileTrace.seek(iIndex*datalen);
	}
	QByteArray array0 = m_fileTrace.read(datalen);
	if (array0.size() != datalen)
	{
		return NULL;
	}
	if (pCopyData)
	{
		memcpy(pCopyData, array0.data(), datalen);
		return pCopyData;
	}
	else {
		memcpy(m_pTraceData, array0.data(), datalen);
		return m_pTraceData;
	}
}
bool CXWellNMR::WriteTraceData(int iIndex)
{
	if (!m_pTraceData)
	{
		return false;
	}
	if (m_fileTrace.isOpen() == false)
	{
		m_fileTrace.setFileName(GetTraceFileName());
		if (!m_fileTrace.open(QIODevice::ReadWrite))
		{
			//qWarning() << "Open file " << GetTraceFileName() << "failed";
			return false;
		}
	}
	const int datalen = 4 * m_Num_2D;
	if (m_fileTrace.pos() != iIndex*datalen)
	{
		m_fileTrace.seek(iIndex * datalen);
	}
	if (datalen != m_fileTrace.write((char*)m_pTraceData, datalen))
	{
		return false;
	}

	return true;
}

QString CXWellNMR::GetTraceFileName()
{
	QString strFileName = ::GetProject()->GetProjectDataPath() + this->GetObjectID().toString() + ".tra";
	return strFileName;
}

QString CXWellNMR::GetTraceInfoFileName()
{
	QString strFileName= ::GetProject()->GetProjectDataPath() + this->GetObjectID().toString() + ".inf";
	return strFileName;
}

bool CXWellNMR::SerializeData(CXArchive &ar)
{
	CXObject::SerializeData(ar);

	if (ar.IsSaving())
	{
		ar << m_dSamplingStart;
		ar << m_dSamplingRate;
		ar << m_nTraceNum;
		ar << m_Num_2D;
		ar << m_dHorizontalStart;
		ar << m_dHorizontalRate;
	}
	else
	{
		ar >> m_dSamplingStart;
		ar >> m_dSamplingRate;
		ar >> m_nTraceNum;
		ar >> m_Num_2D;
		ar >> m_dHorizontalStart;
		ar >> m_dHorizontalRate;
	}

	return true;
}

QStringList CXWellNMR::GetDescription()
{
	QStringList strList;

	//if(::UsingChinese())
	//{
	//	strList<<GetTr("主测线范围")<<QString::number(iFirstInline) + " ~ " + QString::number(iLastInline);
	//	strList<<GetTr("主测线步长")<<QString::number(iInlineInc);
	//	strList<<GetTr("主测线数")<<QString::number(m_utm.GetNI());
	//	strList<<GetTr("联络测线范围")<<QString::number(iFirstCrossline) + " ~ " + QString::number(iLastCrossline);
	//	strList<<GetTr("联络测线步长")<<QString::number(iCrosslineInc);
	//	strList<<GetTr("联络测线数")<<QString::number(m_utm.GetNJ());

	//	strList<<GetTr("起始深度")<<QString::number(m_dSamplingStart);
	//	strList<<GetTr("终止深度")<<QString::number(m_dSamplingEnd);
	//	strList<<GetTr("采样间隔")<<QString::number(m_dSamplingRate);
	//	strList<<GetTr("样点数")<<QString::number(GetSamplingQty());
	//}
	//else
	//{
	strList << "Depth range:" << QString::number(m_dSamplingStart) + " ~ " + QString::number(m_dSamplingStart+m_dSamplingRate*m_nTraceNum);
	strList << "Depth step:" << QString::number(m_dSamplingRate);
	strList << "Depth number:" << QString::number(m_nTraceNum);

	strList << "Num_2D:" << QString::number(m_Num_2D);
	//}

	return strList;
}


float CXWellNMR::GetMaxValue()
{
	double dMin, dMax;
	GetDataRange(dMin, dMax);
	return qMax(qAbs(dMin), qAbs(dMax));
}

void CXWellNMR::_SetSelfDimension()
{
	float  dZMin, dZMax;
	bool bFirst = true;
	for (int i = 0; i < GetTraceNumber(); i++)
	{
		ReadTraceData(i);
		float* pData = GetDataCache();
		for (int j = 0; j < GetSamplingQty(); j++)
		{
			if (bFirst)
			{
				dZMin = dZMax = pData[j];
				bFirst = false;
			}
			dZMin = qMin(dZMin, pData[j]);
			dZMax = qMax(dZMax, pData[j]);
		}
	}
// 	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
// 	m_utm.GetDimensionRange(dXMin, dXMax, dYMin, dYMax);
// 
// 	GetDataRange(dZMin, dZMax);
// 
 	_SetDimension(0, 0, 0, 0, dZMin, dZMax);
}
