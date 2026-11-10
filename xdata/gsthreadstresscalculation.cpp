#include <qdebug.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qtextstream.h>
#include "xglobal.h"
#include "xproject.h"
#include "xtree.h"
#include "xgeometry.h"
#include "gsgeometry.h"
#include "x3dhorizon.h"
#include "gsanticline.h"
#include "gsstructure.h"
#include "gsstressmap.h"
#include "gsthreadstresscalculation.h"
#include "gsstresscalculatemethods.h"
#include "gsstressparameters.h"

GSThreadStressCalculation::GSThreadStressCalculation(GSStressParameters *pParas)
{
	m_pIsoHor = NULL;
	m_pParas = pParas;
}

void GSThreadStressCalculation::RunThread()
{
	if (!m_pIsoHor)
		return;
	double dRadius, dHeight;
	static double dHeightArray[] = { 8, 9, 10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,45,50,60,70,80,90,100 };
	CXSeismicUTMTool utm = m_pIsoHor->GetUTM();
	unsigned char *pBuff = new unsigned char[utm.GetNI() * utm.GetNJ()];
	unsigned char *pMap = new unsigned char[utm.GetNI() * utm.GetNJ()];
	QList<GSAnticline *> listResultAnticlines;

	QString strWindowName = "Calculating stress map for " + m_pIsoHor->GetObjectName() + "...";
	EmitSetWindowName(strWindowName);
	EmitStartComputing();

	GSStressCalculateMethods CM(m_pIsoHor);

	QList<GSStructure *> listCapsule;
	if(m_pParas->m_bFaults)
		listCapsule = CM.CreateStructuresByFaults(m_pParas);

	int m, n, nM, nN, p;
	for (p = 0; p < 3; p++)
	{
		if (m_pParas->m_iAnti[p] == 0)
			continue;

		if (m_pParas->m_dTHeight[p] == -1)
		{
			//	Means auto search.
			dHeightArray[0] = 8;
			dRadius = 3 * utm.GetIInterval();
			nM = 24;		//	8, 9, 10, 11, 12, ... ,90, 100.
			nN = (4000 - dRadius) / utm.GetIInterval() + 1;		//	500, 750, ..., 3750, 4000.
		}
		else
		{
			nM = 1;
			nN = 1;
			dHeightArray[0] = m_pParas->m_dTHeight[p];
			dRadius = m_pParas->m_dSRadius[p];
		}

		QString strTaskName = "Tracking Shape" + QString::number(p + 1) + "...";
		EmitSetTaskName(strTaskName);
		EmitResetProgressBar();

		//	Loop each height and radius.
		double dMaxVolume = 0;
		QList<GSAnticline *> listShapeAnticlines;
		for (m = 0; m < nM; m++)
		{
			if (IsStopped())
				break;
			int nPercent = m * 100 / nM;
			EmitUpdateProgress(nPercent, 100);

			for (n = 0; n < nN; n++)
			{
				QList<GSAnticline *> listAnti = CM.Calculate(m_pParas->m_iAnti[p] == 1, m_pParas->m_dCThreshold[p], m_pParas->m_dLThreshold[p], dHeightArray[m], dRadius + n * 250, pBuff, pMap);

				//	Calculate the sum volume of the anticlines.
				double dVolume = 0.;
				foreach(GSAnticline *pAnticline, listAnti)
				{
					dVolume += pAnticline->GetVolume(m_pIsoHor) * pAnticline->GetRmaR();
				}

				if (dVolume > dMaxVolume)
				{
					dMaxVolume = dVolume;
					m_pParas->m_dTHeight[p] = dHeightArray[m];
					m_pParas->m_dSRadius[p] = dRadius + n * 250;

					qDebug() << "Shape " << p << ", height is " << dHeightArray[m] << ", radius is " << m_pParas->m_dSRadius[p];

					//	Save the anticlines.
					foreach(GSAnticline *pAnticline, listShapeAnticlines)
						delete pAnticline;
					listShapeAnticlines = listAnti;
				}
				else
				{
					foreach(GSAnticline *pAnticline, listAnti)
						delete pAnticline;
				}
			}
		}

		foreach(GSAnticline *pAnticline, listShapeAnticlines)
			listResultAnticlines << pAnticline;
	}

	if (IsStopped())
	{
		foreach(GSAnticline *pAnticline, listResultAnticlines)
		{
			delete pAnticline;
		}

		return;
	}

	if (m_pParas->m_bFaults)
		listResultAnticlines = CM.RemoveAnticlinesByFaults(listResultAnticlines, listCapsule, m_pParas->m_dMinFLength);

	foreach(GSAnticline *pAnticline, listResultAnticlines)
	{
		pAnticline->SetNodeFlag(false);
		m_pMap->AddChild(pAnticline);
	}

	//	Now create the capsules.
	int iType = 1;
	QPointF end0, end1;
	foreach(GSAnticline *pAnticline, listResultAnticlines)
	{
		if (pAnticline->IsAnticline())
			iType = 2;
		pAnticline->GetEndPoints(end0, end1);
		GSStructure *pCapsule = new GSStructure(iType, end0, end1);
		listCapsule << pCapsule;
	}

	listCapsule = CM.StructuresAdjust(listCapsule, m_pParas);

	foreach(GSStructure *pCapsule, listCapsule)
	{
		pCapsule->SetNodeFlag(false);
		m_pMap->AddChild(pCapsule);
	}

	m_pIsoHor->GetParent()->AddChild(m_pMap);

	CXTree::Instance().AddOneObject(m_pIsoHor->GetParent());

	delete[]pBuff;
	delete[]pMap;
}