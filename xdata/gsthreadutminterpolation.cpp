#include "gsthreadutminterpolation.h"

#include "xglobal.h"
#include "xkdtree.h"
#include "xmathmacro.h"
#include "xseismicutmtool.h"
#include <QCoreApplication>
#include <QDebug>

GSThreadUTMInterpolation::GSThreadUTMInterpolation(CXSeismicUTMTool& newUTM, float* pZ, const CXSeismicUTMTool& oldUTM, int iSearchRadius)
    : m_pUTM(&newUTM), m_iSearchRadius(iSearchRadius)
{
    Q_ASSERT(pZ);

    m_vecData.resize(m_pUTM->GetNI() * m_pUTM->GetNJ(), M_FINVALID);

    m_nInputNum = oldUTM.GetNI() * oldUTM.GetNJ();

    m_vecX.reserve(m_nInputNum);
    m_vecY.reserve(m_nInputNum);
    m_vecZ.reserve(m_nInputNum);

    double dEPSInvalid = GetEPSofInvalidData(M_FINVALID);
    for (int i = 0; i != oldUTM.GetNI(); ++i)
    {
        for (int j = 0; j != oldUTM.GetNJ(); ++j)
        {
            double dX, dY;
            oldUTM.IJToXY(i, j, dX, dY);
            if (qAbs(dX - g_dInvalidData) < dEPSInvalid || qAbs(dY - g_dInvalidData) < dEPSInvalid)
                continue;

            double dZ = pZ[i * oldUTM.GetNJ() + j];
            if (qAbs(dZ - g_dInvalidData) < dEPSInvalid)
                continue;

            fillSeedPoint(dX, dY, dZ);
        }
    }

    m_nInputNum = m_vecX.size();
}

GSThreadUTMInterpolation::GSThreadUTMInterpolation(CXSeismicUTMTool& utm, const std::vector<double>& vecPoints, int iSearchRadius)
    : m_pUTM(&utm), m_iSearchRadius(iSearchRadius)
{
    m_vecData.resize(m_pUTM->GetNI() * m_pUTM->GetNJ(), M_FINVALID);

    m_vecX.reserve(vecPoints.size());
    m_vecY.reserve(vecPoints.size());
    m_vecZ.reserve(vecPoints.size());

    double dEPSInvalid = GetEPSofInvalidData(g_dInvalidData);
    for (size_t i = 0; i < vecPoints.size(); i += 3)
    {
        double dX = vecPoints.at(i);
        double dY = vecPoints.at(i + 1);
        double dZ = vecPoints.at(i + 2);
        if (qAbs(dX - g_dInvalidData) < dEPSInvalid || qAbs(dY - g_dInvalidData) < dEPSInvalid || qAbs(dZ - g_dInvalidData) < dEPSInvalid)
            continue;

        fillSeedPoint(dX, dY, dZ);
    }

    m_nInputNum = m_vecX.size();
}

GSThreadUTMInterpolation::~GSThreadUTMInterpolation()
{
}

const std::vector<float>& GSThreadUTMInterpolation::GetResult() const
{
    return m_vecData;
}

void GSThreadUTMInterpolation::SetObjectName(const QString& name)
{
    m_strObjectName = name;
}

void GSThreadUTMInterpolation::RunThread()
{
    if (IsStopped())
        return;

    EmitSetWindowName("Interpolation");
    EmitSetTaskName("Interpolating " + m_strObjectName + "...");
    EmitStartComputing();
    qApp->processEvents();

    if (!initKDTree())
        return;

	int nMaxNearest = std::min(8, m_nInputNum - 1);
	double dIInterval = m_pUTM->GetIInterval();
    double dJInterval = m_pUTM->GetJInterval();
    double dInterval  = sqrt(dIInterval * dIInterval + dJInterval * dJInterval) / 2.;

    interpolateWithIDP(dInterval * m_iSearchRadius, nMaxNearest);
}

void GSThreadUTMInterpolation::fillSeedPoint(double dX, double dY, double dZ)
{
    m_vecX.push_back(dX);
    m_vecY.push_back(dY);
    m_vecZ.push_back(dZ);

    float fI, fJ;
    if (m_pUTM->XYToIJ(dX, dY, fI, fJ))
    {
        int iI = static_cast<int>(fI + 0.001);
        int iJ = static_cast<int>(fJ + 0.001);

        if (qAbs(fI - iI) < 0.00001 && qAbs(fJ - iJ) < 0.00001)
        {
            m_tableAlreadyExist.emplace(iI * m_pUTM->GetNJ() + iJ, dZ);
        }
    }
}

bool GSThreadUTMInterpolation::interpolateWithIDP(double dSearchRadius, int nMaxNearest)
{
    int nI = m_pUTM->GetNI();
    int nJ = m_pUTM->GetNJ();

    for (int i = 0; i != nI; ++i)
    {
        if (IsStopped())
            return false;

        EmitUpdateProgress(i, nI);

        for (int j = 0; j != nJ; ++j)
        {
            auto foundAlreadyExist = m_tableAlreadyExist.find(i * nJ + j);
            if (foundAlreadyExist != m_tableAlreadyExist.end())
            {
                m_vecData[foundAlreadyExist->first] = foundAlreadyExist->second;
                continue;
            }

            double dX, dY;
            m_pUTM->IJToXY(i, j, dX, dY);

            std::vector<int> indices(m_nInputNum);
            std::vector<double> distances(nMaxNearest);

            int iResult = m_pKDTree->NNearest(dX, dY, &indices[0], &distances[0], nMaxNearest);

            if (iResult == 0)
            {
                m_vecData[i * nJ + j] = static_cast<float>(m_vecZ.at(indices.front()));
                continue;
            }

			int nCount        = 0;
            double dSumWeight = 0.;
            double dSumValue  = 0.;
			for (int i = 0; i != nMaxNearest; ++i)
			{
				int index = indices.at(i);
				double distance = distances.at(i);

				if (distance > dSearchRadius)
					continue;

				double dWeight = std::pow(1. / distance, 2);

				++nCount;
				dSumWeight += dWeight;
				dSumValue += dWeight * m_vecZ.at(index);
			}

			if (nCount == 0)
			{
				m_vecData[i * nJ + j] = M_FINVALID;
			}
			else
			{
				m_vecData[i * nJ + j] = static_cast<float>(dSumValue / dSumWeight);
			}
        }
    }

    return true;
}

bool GSThreadUTMInterpolation::initKDTree()
{
    if (m_nInputNum < 2)
    {
        qFatal("You do not have enough data points to interpolate");
        return false;
    }

    m_pKDTree = std::make_unique<CXKDTree>(&m_vecX[0], &m_vecY[0], m_nInputNum);
    if (!m_pKDTree->CreateKDTree())
    {
        qFatal("Cannot create the K-D tree.");
        return false;
    }

    return true;
}
