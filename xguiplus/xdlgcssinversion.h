#ifndef XDLGCSSINVERSION_H
#define XDLGCSSINVERSION_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgcssinversion.h"
#include <vector>

using std::vector;

class CXParameterCSSInversion;
/**
*	@class	 CXDlgCSSInversion in the file "kedlgcssinversion.h"
*	@brief	 The class provide a dialog for constrained sparse spike inversion
*	@author	Yong Shu
*	@date	 6/24/2016
*/

class XGUIPLUS_EXPORT CXDlgCSSInversion : public QDialog
{
	Q_OBJECT

public:
	CXDlgCSSInversion(QWidget *parent = NULL);
	~CXDlgCSSInversion();

	void SetData(vector<float>& vecWavelet, vector<float> & vec2DSeismic, vector<float>& vecImp,double rate);

	virtual void accept();

	void GetImpedance(vector<float>& vec);
	void GetImpedanceBP(vector<float>& vec);
	void GetImpedanceMerged(vector<float>& vec);

private:
	void _GetPara();
	void _Calc();
	void _CalcMinMax(int& zMin, int& zMax);

private:
	Ui::DlgCSSInversion m_ui;

	CXParameterCSSInversion* m_pPara;

private:
	int m_nZ;
	vector<float> m_vecWavelet, m_vec2DSeismic, m_vecImpedance;

	// output
	vector<float> m_vecOutImped, m_vecOutBP, m_vecOutMerged;
};

#endif // KEDLGCSSINVERSION_H
