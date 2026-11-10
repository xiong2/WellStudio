#ifndef CXVIEWUTILITY_H
#define CXVIEWUTILITY_H

class CXWindowInfoSection;
class CXSectionScene;

namespace NXViewUtility
{
	void GetMMPerDPI(float& fMMX, float& fMMY);

	void GetSizeFromViewInfo(CXWindowInfoSection* pViewInfo, CXSectionScene* pScene, double& dWidth, double& dHeight);

	void SetViewInfoFromSize(CXWindowInfoSection* pViewInfo, CXSectionScene* pScene, int nWidth, int nHeight);

	template<typename T>
	class CXLinearMap
	{
	public:
		CXLinearMap(T x1, T x2, T y1, T y2)
		{
			if (qAbs(x1) == qAbs(x2))
			{
				a = 0;
				b = (y1 + y1) / 2.;
			}
			else
			{
				a = (y2 - y1) / (x2 - x1);
				b = y1 - a*x1;
			}
		}

		T GetYFromX(T x)
		{
			return a*x + b;
		}
		T GetXFromY(T y)
		{
			if (a == 0)
				return 0;
			else
				return (y - b) / a;
		}

	private:
		T a, b;
	};

};

#endif