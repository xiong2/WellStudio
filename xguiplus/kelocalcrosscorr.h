#ifndef KELOCALCROSSCORR_H
#define KELOCALCROSSCORR_H

using namespace std;

class CKELocalCrossCorr
{
public:
	CKELocalCrossCorr();
	~CKELocalCrossCorr();

	void setData(int n, float *a, float *b);
	void setPara(int nwin, int ilagmin, int nlag, float threshcc);
	void setTimeGate(int startTimeSam, int endTimeSam);
	void getNormalizedCorrelation(float *lcc);
	void getShifts(float *shift);

private:
	float *m_data1;
	float *m_data2;
	int m_nt;
	int m_lagmin;
	int m_lagmax;
	int m_nlag;

	//Time Gate
	int m_startTimeSam;
	int m_endTimeSam;

	int m_nwhalf;
	float *m_pScale;
	float *m_pProd;
	float *m_pSQRTAA; //auto-correlation: 1/sqrt(a*a)
	float *m_pSQRTBB; //auto-correlation: 1/sqrt(b*b)
	float *m_pAB; //cross-correlation: a*b

	void CrossCorrLocGaussOneLag(int ilag, float *c);
	void NormalizeHalfOneLag(float *a, float *c);
	void NormalizeOneLag(int ilag, float *c);
	void CrossCorrLocGauss();
	void CrossCorrLocGaussNorm();
	void FindShifts(float threshcc);

	//shift time
	float m_threshcc;
	float *m_pShift;

};

#endif // KELOCALCROSSCORR_H
