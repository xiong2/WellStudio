#include <QString>
#include <QFile>
#include <QApplication>
#include <qtextstream.h>
#include <QDomDocument>
#include "xthreadwellhorizonintersect.h"
#include "xparameterwellhorzionintersect.h"
#include "xregulardatawriter.h"
#include <cassert>
#include "xutility.h"
#include "xglobal.h"
#include "x3dsurface.h"
#include "xproject.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xgraphicsapi.h"
#include "xfunctiontemplate.h"


CXThreadWellHorizonIntersect::CXThreadWellHorizonIntersect(CXWell* pWell, CXParameterWellHorzionIntersect* pPara)
{
	m_pWell = pWell;
	m_pPara = pPara;

	assert(pWell && m_pPara);

	_Init();
	
	// Lock
	if (m_pWell)
		LockRead(m_pWell);
	for (int i=0; i<m_vecInputSurface.size(); ++i)
	{
		LockRead(m_vecInputSurface.at(i));
	}

}


CXThreadWellHorizonIntersect::~CXThreadWellHorizonIntersect()
{
	this->wait();

	if (m_pWell)
		UnlockRead(m_pWell);
	for (int i=0; i<m_vecInputSurface.size(); ++i)
	{
		UnlockRead(m_vecInputSurface.at(i));
	}
}

void CXThreadWellHorizonIntersect::_Init()
{
	std::vector<QUuid> vecHorizonID = m_pPara->GetvecHorizonID();
	for (int i=0; i<vecHorizonID.size(); ++i)
	{
		CX3DSurface* pSurface = dynamic_cast<CX3DSurface*>(::GetObjectByID(vecHorizonID[i]));
		if (pSurface)
		{
			m_vecInputSurface.push_back(pSurface);
		}
	}
}

void CXThreadWellHorizonIntersect::RunThread()
{
	if (IsStopped())
		return;

	if (!m_pWell)
	{
		QString strErrorMsg = "Cannot find the selected well.";
		EmitGeneralErrorMsg(strErrorMsg);
		return; 
	}

	if (m_vecInputSurface.empty())
	{
		QString strErrorMsg = "Cannot find the selected 3-D surface.";
		EmitGeneralErrorMsg(strErrorMsg);
		return; 
	}

	this->EmitSetWindowName("Intersection between the vertical well profile and 3-D horionz.");
	this->EmitSetTaskName("Calculating...");
	this->EmitStartComputing();
	qApp->processEvents();

	_CalcIntersection();

}

void CXThreadWellHorizonIntersect::_CalcIntersection()
{
	CXWellPath* pWellPath = m_pWell->GetWellPath();
	if (!pWellPath)
		return;

	unsigned int nDataNum = 0;
	double* pPathData = pWellPath->GetData(nDataNum);
	if (nDataNum == 0 || !pPathData)
		return;

	// Get well top and bottom postion
	double x1, y1, x2, y2;
	x1 = pPathData[0];
	y1 = pPathData[1];

	x2 = pPathData[nDataNum-3];
	y2 = pPathData[nDataNum-2];

	// Calculate intersection
	std::vector<std::vector<double> > vecVecIntersect;
	for (int iSurface=0; iSurface<m_vecInputSurface.size(); ++iSurface)
	{
		if (IsStopped())
			return;
		else
		{			
			this->EmitUpdateProgress(iSurface, m_vecInputSurface.size());
		}

		std::vector<double> vecIntersect;
		float* pSurfaceData = m_vecInputSurface.at(iSurface)->GetData();
		assert(pSurfaceData);

		m_utm = m_vecInputSurface[iSurface]->GetUTM();
		int nI = m_utm.GetNI();
		int nJ = m_utm.GetNJ();

		int iI1, iJ1, iI2, iJ2;
		float fI1, fJ1, fI2, fJ2;
		m_utm.XYToIJ(x1, y1, fI1, fJ1);
		m_utm.XYToIJ(x2, y2, fI2, fJ2);

		if (fI1 < fI2)
		{
			iI1 = static_cast<int>(ceil(fI1));
			iI2 = static_cast<int>(floor(fI2));
		}
		else
		{
			iI1 = static_cast<int>(floor(fI1));
			iI2 = static_cast<int>(ceil(fI2));
		}

		if (fJ1 < fJ2)
		{
			iJ1 = static_cast<int>(ceil(fJ1));
			iJ2 = static_cast<int>(floor(fJ2));
		}
		else
		{
			iJ1 = static_cast<int>(floor(fJ1));
			iJ2 = static_cast<int>(ceil(fJ2));
		}

		// Along I
		double x3, y3, x4, y4, x, y, z;
		if (qAbs(iI1 - iI2) > qAbs(iJ1 - iJ2))
		{
			int iSign = Sign(iI2 - iI1);
			int i = iI1;
			do
			{
				m_utm.IJToXY(i, 0, x3, y3);
				m_utm.IJToXY(i, nJ-1, x4, y4);
				
				if (!CXGraphicsAPI::IntersectionOfTwoLines(x1,y1, x2,y2, x3,y3,x4,y4,x,y))
				{
					x = x1;
					y = y1;
				}
				if (_CalcZ(x, y, pSurfaceData, z))
				{
					vecIntersect.push_back(x);
					vecIntersect.push_back(y);
					vecIntersect.push_back(z);
				}

				i += iSign;

			}while(i != iI2);
		}
		else
		{
			int jSign = Sign(iJ2 - iJ1);
			int j = iJ1;
			do
			{
				m_utm.IJToXY(0, j, x3, y3);
				m_utm.IJToXY(nI-1, j, x4, y4);

				if (!CXGraphicsAPI::IntersectionOfTwoLines(x1,y1, x2,y2, x3,y3,x4,y4,x,y))
				{
					x = x1;
					y = y1;
				}
				if (_CalcZ(x, y, pSurfaceData, z))
				{
					vecIntersect.push_back(x);
					vecIntersect.push_back(y);
					vecIntersect.push_back(z);
				}

				j += jSign;

			}while(j != iJ2);
		}

		vecVecIntersect.push_back(vecIntersect);
	}

	_WriteToFile(x1, y1, m_pWell, vecVecIntersect);
}


bool CXThreadWellHorizonIntersect::_CalcZ(double x, double y, float* pData, double& z)
{
	float fI, fJ;
	if (!m_utm.XYToIJ(x, y, fI, fJ))
		return false;

	int iMin, iMax, jMin, jMax;
	iMin = static_cast<int>(floor(fI));
	iMax = static_cast<int>(ceil(fI));
	jMin = static_cast<int>(floor(fJ));
	jMax = static_cast<int>(ceil(fJ));

	if (iMin == iMax)
	{
		if (iMin == 0)
			++iMax;
		else 
			--iMin;
	}
	if (jMin == jMax)
	{
		if (jMin == 0)
			++jMax;
		else
			--jMin;
	}

	double z1, z2, z3, z4;
	int nJ = m_utm.GetNJ();
	z1 = pData[iMin*nJ + jMin];
	z2 = pData[iMin*nJ + jMax];
	z3 = pData[iMax*nJ + jMin];
	z4 = pData[iMax*nJ + jMax];

	double z5 = (jMax - fJ)*z1 + (fJ - jMin)*z2;
	double z6 = (jMax - fJ)*z3 + (fJ - jMin)*z4;

	z = (iMax - fI)*z5 + (fI - iMin)*z6;

	return true;
}


void CXThreadWellHorizonIntersect::_WriteToFile(double x0, double y0, CXWell* pWell, std::vector<std::vector<double> >& vecVecIntersect)
{
	// get output file name
	QString strName = ::GetProject()->GetProjectDataPath() + pWell->GetObjectName(); 
	int i = 1;
	QString strFileName = strName + QString::number(i);
	while (QFile::exists(strFileName + ".xml"))
	{
		strFileName  = strName + QString::number(++i);
	} 

	strFileName += ".xml";
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;
	QTextStream out(&qFile);
    out.setCodec("UTF-8");

	// open file
	QDomDocument qDoc;

	QDomProcessingInstruction xmlProcessingInstruction = qDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"GB2312\"");
	qDoc.appendChild(xmlProcessingInstruction);

	QDomElement root = qDoc.createElement("Root");
	qDoc.appendChild(root);

	QDomElement fileInfo = qDoc.createElement("FileInfo");
	root.appendChild(fileInfo);

	// File Mark
	QDomElement fileMark = qDoc.createElement("FileMark");
	fileInfo.appendChild(fileMark);

	QDomText textFileMark = qDoc.createTextNode("@RICHFIT@");
	fileMark.appendChild(textFileMark);
	
	// horizons number
	QDomElement horizonNum = qDoc.createElement("HorizonNumber");
	fileInfo.appendChild(horizonNum);

	QDomText textHorizonNum = qDoc.createTextNode(QString::number(vecVecIntersect.size()));
	horizonNum.appendChild(textHorizonNum);

	// Horizons
	QDomElement horizons = qDoc.createElement("Horizons");
	root.appendChild(horizons);

	QStringList strHorizonNameList = m_pPara->GetHorizonNameList();
	QStringList strRockNameList = m_pPara->GetRockNameList();
	strRockNameList.append(GetTr("Пе"));

	for (int i=0; i<vecVecIntersect.size(); ++i)
	{
		QDomElement horizon = qDoc.createElement("Horizon");
		horizons.appendChild(horizon);
		
		int nPointNum = vecVecIntersect[i].size()/3;
		// name
		QDomElement horizonName = qDoc.createElement("HorizonName");
		horizon.appendChild(horizonName);

		QDomText textHorizonName = qDoc.createTextNode(strHorizonNameList.at(i));
		horizonName.appendChild(textHorizonName);

		// rock
		QDomElement rockName = qDoc.createElement("RockName");
		horizon.appendChild(rockName);

		QDomText textRockName = qDoc.createTextNode(strRockNameList.at(i));
		rockName.appendChild(textRockName);

		// pointNumber
		QDomElement pointNumber = qDoc.createElement("PointNumber");
		horizon.appendChild(pointNumber);

		QDomText textPointNumber = qDoc.createTextNode(QString::number(nPointNum));
		pointNumber.appendChild(textPointNumber);

		QString strPoints;
		QTextStream streamData(&strPoints);
		double x, y, z, dist;
		for (int j=0; j<nPointNum; ++j)
		{
			x = vecVecIntersect[i][3*j ];
			y = vecVecIntersect[i][3*j+1];
			z = vecVecIntersect[i][3*j+2];
			dist = sqrt(SQR(x-x0) + SQR(y-y0));

			streamData << QString::number(dist, 'f', 6) << "," << QString::number(z, 'f', 6) << ";";
		}

		QDomElement points = qDoc.createElement("Points");
		horizon.appendChild(points);

		QDomText textPoints = qDoc.createTextNode(strPoints);
		points.appendChild(textPoints);
	}

	out << qDoc.toString();
}

	
