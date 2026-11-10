#pragma warning( push ,0 )
#include "xthreadinterpolatedv.h"
#include <QCoreApplication>
#include <qfile.h>
#include "xcubicspline.h"
#include <cassert>
#include "xglobal.h"
#include "xseismicdatavolume.h"
#include "xutility.h"

#pragma warning( pop )

CXThreadInterpolateDV::CXThreadInterpolateDV(CXSeismicDataVolume* pDV):
m_pDV(pDV)
{
	assert(m_pDV);

	m_pOutDV = new CXSeismicDataVolume(*m_pDV);
	m_pOutDV->SetObjectName(m_pDV->GetObjectName() + "_intp");

	LockRead(m_pDV);
}

CXThreadInterpolateDV::~CXThreadInterpolateDV()
{
	wait();

	UnlockRead(m_pDV);

	if (IsStopped())
	{
		delete m_pOutDV;
	}
}

void CXThreadInterpolateDV::RunThread()
{
	if (IsStopped())
		return;

	QFile qInFile(m_pDV->GetTraceFileName());
	qint64 nFileSize = qInFile.size();

	int nK = m_pDV->GetSamplingQty();
	qint64 nTraceNum = nFileSize / (nK * sizeof(float));

	QFile qOutFile(m_pOutDV->GetTraceFileName());

	if (!qInFile.open(QIODevice::ReadOnly) || !qOutFile.open(QIODevice::WriteOnly))
	{
		this->EmitGeneralErrorMsg("Cannot open the file to read.");
		return;
	}

	this->EmitSetWindowName("Interpolate Data Volume");
	this->EmitSetTaskName("Interpolating...");
	this->EmitStartComputing();
	this->EmitCancelEnabled(false);
	QCoreApplication::instance()->processEvents();
	
	float fInvalid = (float)g_dInvalidData;
	float fEPSInvalid = ::GetEPSofInvalidData(fInvalid);

	vector<float> vecIn(nK), vecOut(nK);
	vector<double> vecX(nK), vecY(nK);


	for (qint64 i = 0; i < nTraceNum; ++i)
	{
		if (IsStopped())
			return;
		else
		{
			this->EmitUpdateProgress(i, nTraceNum);
		}

		// read data
		unsigned char* pMapData = qInFile.map(i * nK * sizeof(float), nK * sizeof(float));
		memcpy(&vecIn[0], (float*)pMapData, nK * sizeof(float));
		qInFile.unmap(pMapData);

		// find valid range
		int kmin(0), kmax(0);
		for (int k = 0; k < nK; ++k)
		{
			if (qAbs(vecIn[k] - fInvalid) > fEPSInvalid)
			{
				kmin = k;
				break;
			}
		}
		for (int k = nK - 1; k >= 0; --k)
		{
			if (qAbs(vecIn[k] - fInvalid) > fEPSInvalid)
			{
				kmax = k;
				break;
			}
		}

		// cubic 
		std::copy(vecIn.begin(), vecIn.end(), vecOut.begin());

		if (kmax - kmin > 2)
		{
			int nKK(0);
			for (int k = kmin; k <= kmax; ++k)
			{
				if (qAbs(vecIn[k] - fInvalid) > fEPSInvalid)
				{
					vecX[nKK] = k;
					vecY[nKK] = vecIn[k];
					++nKK;
				}
			}
			if (nKK > 2)
			{
				CXCubicSpline spline(nKK, &vecX[0], &vecY[0]);
				for (int k = kmin + 1; k < kmax; ++k)
				{
					if (qAbs(vecIn[k] - fInvalid) < fEPSInvalid)
					{
						vecOut[k] = (float)spline.GetY(k);
					}
				}
			}
		}

		// write
		qOutFile.write((char*)&vecOut[0], sizeof(float)*nK);
	}

	qInFile.close();
	qOutFile.close();

	// copy info file
	if (QFile::exists(m_pDV->GetTraceInfoFileName()))
	{
		QFile::copy(m_pDV->GetTraceInfoFileName(), m_pOutDV->GetTraceInfoFileName());
	}
}

