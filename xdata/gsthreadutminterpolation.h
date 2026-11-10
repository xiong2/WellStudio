#ifndef GSTHREADUTMINTERPOLATION_H
#define GSTHREADUTMINTERPOLATION_H

#include "xbasethread.h"
#include <memory>
#include <unordered_map>
#include "xdata_global.h"

class CXSeismicUTMTool;
class CXKDTree;

class XDATA_EXPORT GSThreadUTMInterpolation : public CXBaseThread
{
public:
	GSThreadUTMInterpolation(CXSeismicUTMTool& newUTM, float* pZ, const CXSeismicUTMTool& oldUTM, int iSearchRadius = 10);
	GSThreadUTMInterpolation(CXSeismicUTMTool& utm, const std::vector<double>& vecPoints, int iSearchRadius = 10);
	~GSThreadUTMInterpolation();

	const std::vector<float>& GetResult() const;
	void SetObjectName(const QString& name);

protected:
	void RunThread() override;

private:
	void fillSeedPoint(double dX, double dY, double dZ);

	bool interpolateWithIDP(double dSearchRadius, int nMaxNearest);
	bool initKDTree();

private:
	std::unique_ptr<CXKDTree> m_pKDTree;
	CXSeismicUTMTool* m_pUTM = nullptr;

	std::vector<float> m_vecData;

	std::unordered_map<int, double> m_tableAlreadyExist;
	std::vector<double> m_vecX;
	std::vector<double> m_vecY;
	std::vector<double> m_vecZ;

	int m_nInputNum = 0;
	int m_iSearchRadius;
	QString m_strObjectName;
};

#endif // GSTHREADUTMINTERPOLATION_H
