#ifndef X2DAXISHELPER_H
#define X2DAXISHELPER_H

#include "xsectionwindow_global.h"
#include <QRect>
#include <qfont.h>
#include <vector>
#include "xviewutility.h"
#include <qvector.h>


using std::vector;
using namespace NXViewUtility;

class XSECTIONWINDOW_EXPORT CX2DAxisHelper
{
public:
	CX2DAxisHelper(double dDataStart, double dDataEnd, double dStep, bool bVertical, const vector<int>& vecKeyIndex= vector<int>());
	~CX2DAxisHelper();

	///@brief Set the font and rendering rect
	void SetFontandRect(const QFont& font, const QRectF& rect, double dLeft, double dTop, const vector<double>& vecValue);

	///@brief Get display precision of double format data
	int GetPrecision() { return m_nPrecision; }

	bool IsMainTick(double dValue);
	bool IsMinorTick(double dValue);

	double GetPositionFromData(double dData);
	double GetDataFromPositon(double dPosition);

	void GetAxisRange(double& dDataStart, double& dDataEnd, double& dDataStep)
	{
		dDataStart = m_dDataStart;
		dDataEnd = m_dDataEnd;
		dDataStep = m_dDataStep;
	}

	void GetAxisRange(double& dDataStart, double& dDataEnd)
	{
		dDataStart = m_dDataStart;
		dDataEnd = m_dDataEnd;
	}

	bool IsKeyPoint(int index);

private:
	void _CalcTicks();
	void _AddConstraint();

	int _GetValidDecimalNum(double dData);

	double _GetMainStep(double dMaxTxtLength);
	double _GetProperStep(double dStep);

	int _GetMinorTickNum(double dStep);
	double _GetSignificant(double dStep);

	bool _IsMainTick(double dValue);
	bool _IsMinorTick(double dValue);

private:
	// input
	double m_dDataStart, m_dDataEnd, m_dDataStep;
	QVector<int> m_vecKeyIndex;
	vector<double> m_vecValue; // values for calculating font size

	bool m_bVertical;

	QFont m_font;
	QRectF m_rect;

	double m_dLeft, m_dTop;


private:
	//calc
	int m_nPoint;
	int m_nPrecision;

	double m_dMainTickStep;
	int m_nMinorTickNum, m_nTotalTickNum;

	int m_nPixNumPerTick;

	CXLinearMap<double>* m_pLinearMap;
	
	vector<unsigned char> m_vecOut;
};

#endif // KE2DAXISHELPER_H

