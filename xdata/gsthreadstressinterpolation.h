#ifndef GSTHREADSTRESSINTERPOLATION_H
#define GSTHREADSTRESSINTERPOLATION_H

#include "xbasethread.h"
#include <memory>
#include <unordered_map>
#include <array>
#include <QVector>
#include <vector>
#include "xvec.h"
#include "xdata_global.h"

class CXSeismicUTMTool;
class CXKDTree;
class GSStressMap;
class GSGrid;
class XMatrix;

class XDATA_EXPORT GSThreadStressInterpolation : public CXBaseThread
{
public:
	GSThreadStressInterpolation(CXSeismicUTMTool& utm, const QVector<double>& vecStressData, GSStressMap* pStressMap);
	~GSThreadStressInterpolation();

	const std::vector<float>& GetResult() const;
	void SetObjectName(const QString& name);

protected:
	void RunThread() override;

private:
	void gridFDiff(GSGrid& grid, const std::vector<XPoint>& xyz);
	std::vector<XPoint> GetControlPoints(const XMatrix& indexMatrix, const std::vector<XPoint>& xyz);

	void fillBoundary(std::vector<XPoint>& vecMag, double dXMin, double dXMax, double dYMin, double dYMax, double minZ);

	double gridStressMagLowerBoundary(double dMin, int iStep = 1);
	double gridStressMagUpperBoundary(double dMax);

	static int magTypeFromMag(double mag);
	static int magTypeBelow(int magType);

private:
	CXSeismicUTMTool* m_pUTM = nullptr;
	const QVector<double>& m_vecStressData;
	GSStressMap* m_pStressMap = nullptr;

	std::vector<float> m_vecData;
	QString m_strObjectName;
};

#endif // GSTHREADSTRESSINTERPOLATION_H
